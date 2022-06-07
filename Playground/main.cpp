#include <semaphore>
#include <iostream>
#include <thread>
#include <array>
#include <optional>
#include <random>
#include <utl/functional.hpp>

#include <utl/stdio.hpp>

class Timer {
public:
	Timer(): begin(std::chrono::high_resolution_clock::now()) {}
	double elapsed() const { return (std::chrono::high_resolution_clock::now() - begin).count() / 1'000'000.0; }
private:
	std::chrono::high_resolution_clock::time_point begin;
};

struct PresentReciept {
	void wait() {
		if (mWaitFn) {
			Timer t;
			mWaitFn();
			utl::print("Waited {}ms for reciept\n", t.elapsed());
			
		}
	}
	utl::function<void()> mWaitFn;
};

struct RenderItem {
	utl::function<void()> encode;
	utl::function<PresentReciept()> present;
};

class RenderUpdateLink {
public:
	RenderUpdateLink(std::size_t numFramesInFlight = 3): numFramesInFlight(numFramesInFlight) {}

	void push(RenderItem item) {
		std::unique_lock lock(mtx);
		// dont want to get to far ahead
		cv.wait(lock, [this] { return producerIndex < consumerIndex + numFramesInFlight || !linked; });
		if (!linked) {
			return;
		}
		buffer[producerIndex % numFramesInFlight] = std::move(item);
		++producerIndex;
		lock.unlock();
		cv.notify_one();
	}

	std::optional<RenderItem> consume() {
		std::unique_lock lock(mtx);
		// dont want to overtake
		cv.wait(lock, [this] { return consumerIndex < producerIndex || !linked; });
		if (!linked) {
			return std::nullopt;
		}
		auto result = std::move(buffer[consumerIndex % numFramesInFlight]);

		++consumerIndex;
		lock.unlock();
		cv.notify_one();
		return result;
	}

	void release() {
		std::unique_lock lock(mtx);
		linked = false;
		lock.unlock();
		cv.notify_all();
	}

private:
	std::array<RenderItem, 3> buffer;
	std::size_t producerIndex = 0;
	std::size_t consumerIndex = 0;
	std::size_t numFramesInFlight = 0;
	bool linked = true;
	std::condition_variable cv;
	std::mutex mtx;
};




thread_local std::mt19937 rng;

std::array<std::chrono::high_resolution_clock::time_point, 12> updateFinishTime;

auto renderTime =         []{ return std::chrono::milliseconds(std::uniform_int_distribution<>(4, 6)(rng)); };
auto presentTime =        []{ return std::chrono::milliseconds(4); };
auto updateTime =         []{ return std::chrono::milliseconds(std::uniform_int_distribution<>(2, 3)(rng)); };
auto displayRefreshTime = []{ return std::chrono::microseconds(16'666); };
auto totalRuntime =       []{ return std::chrono::seconds(1); };

void renderFunction(int numFrame){
	Timer t;
	std::this_thread::sleep_for(renderTime());
	utl::print("Rendered Frame {} in {}ms\n", numFrame, t.elapsed());
	
}

PresentReciept presentFunction(int numFrame) {
	utl::print("Presenting Frame {} {}ms after update finish\n", numFrame, (std::chrono::high_resolution_clock::now() - updateFinishTime[numFrame % 12]).count() / 1'000'000.0);
	auto const now = std::chrono::high_resolution_clock::now();
	return { .mWaitFn = [now]{ std::this_thread::sleep_until(now + presentTime()); } };
}





void testFn() {
	RenderUpdateLink link(1);
	
	std::atomic_bool run = true;
	
	std::thread application([&]{
		for (int i = 0; run; ++i) {
			Timer t;
			std::this_thread::sleep_for(updateTime()); // producer time
			RenderItem renderItem;
			renderItem.encode = [i]{ renderFunction(i); };
			renderItem.present = [i]{ return presentFunction(i); };
			updateFinishTime[i % 12] = std::chrono::high_resolution_clock::now();
			utl::print("Update {} finished in {}ms\n", i, t.elapsed());
			
			link.push(renderItem);
			
		}
	});
	
	std::binary_semaphore frameSemaphore{0};
	std::thread screenDelegate([&]{
		while (run) {
			frameSemaphore.release();
			std::this_thread::sleep_for(displayRefreshTime());
		}
		frameSemaphore.release();
	});
	
	std::thread renderer([&]{
		try {
			RenderItem item[2];
			PresentReciept reciept[2];
			
			for (int i = 0; run; i = (i + 1) % 2) {
				Timer t;
				frameSemaphore.acquire();
				utl::print("Renderer Waited {}ms for semaphore\n", t.elapsed());
				item[i] = link.consume().value();// get     0
				item[i].encode();                // encode  0
				reciept[i].wait();               // wait   -2
				reciept[i] = item[i].present();  // present 0
			}
		}
		catch (std::bad_optional_access const&) { return; }
	});
	
	std::this_thread::sleep_for(totalRuntime());

	run = false;
	
	link.release();
	application.join();
	renderer.join();
	screenDelegate.join();
}


int main() {
	testFn();
}
