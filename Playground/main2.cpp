#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <array>
#include <chrono>
#include <utl/functional.hpp>
#include <utl/stdio.hpp>

class Timer {
public:
	Timer(): begin(std::chrono::high_resolution_clock::now()) {}
	double elapsed() const { return (std::chrono::high_resolution_clock::now() - begin).count() / 1'000'000.0; }
private:
	std::chrono::high_resolution_clock::time_point begin;
};

class Application {
	friend int main();
	
public:
	virtual void update(std::size_t frame) {}
	virtual void render(std::size_t frame) {}
	
	
	
private:
	void updateLoop() {
		for (std::ptrdiff_t frame = -1; !breakCond(); ) {
			std::unique_lock lock(frameCounterMutex);
			frameCV.wait(lock, [&]{ return frame < frameCounter; });
			frame = frameCounter;
			lock.unlock();
			update(frame);
		}
	}
	
	void renderLoop() {
		for (std::ptrdiff_t frame = -1; alive; ) {
			std::unique_lock lock(frameCounterMutex);
			frameCV.wait(lock, [&]{ return frame < frameCounter; });
			frame = frameCounter;
			lock.unlock();
			if (frame > 0) {
				render(frame - 1); // one step behind update
			}
		}
	}
	
	void displayLinkLoop() {
		while (true) {
			std::unique_lock lock(frameCounterMutex);
			++frameCounter;
			utl::print("--- Want Frame {} ---\n", frameCounter);
			lock.unlock();
			frameCV.notify_all();
			
			if (!alive) { return; }
			std::this_thread::sleep_for(std::chrono::nanoseconds(16'666'666));
		}
	}
	
	bool breakCond() const { return std::chrono::high_resolution_clock::now() > endTime;  }
	
	void run() {
		std::thread displayLinkThread([this]{ displayLinkLoop(); });
		std::thread renderThread([this]{ renderLoop(); });
		updateLoop();
		
		alive = false;
		displayLinkThread.join();
		renderThread.join();
	}
	
private:
	std::ptrdiff_t frameCounter = -1;
	std::mutex frameCounterMutex;
	std::condition_variable frameCV;
	
	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	std::atomic_bool alive = true;
};

struct SceneData {
	int baz;
};

class MyApp: public Application {
public:
	void update(std::size_t frame) override {
		static std::mt19937 rng(std::random_device{}());
		Timer t;
		std::this_thread::sleep_for(std::chrono::microseconds(std::uniform_int_distribution<>(2'000, 4'000)(rng)));
		sceneData[frame % 2] = frame;
		
		utl::print("{}Computed Frame {} in {}ms\n", utl::format_codes::green, frame, t.elapsed());
	}
	
	void render(std::size_t frame) override {
		static std::mt19937 rng(std::random_device{}());
		Timer t;
		int scene = sceneData[(frame) % 2];
		std::this_thread::sleep_for(std::chrono::microseconds(std::uniform_int_distribution<>(2'000, 4'000)(rng)));
		
		utl::print("{}Rendered Frame {} in {}ms\n", utl::format_codes::blue, scene, t.elapsed());
	}
	
private:
	int sceneData[2];
};

int main() {
	MyApp theApp;
	theApp.run();
	
	
	
}
