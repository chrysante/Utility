#include "Catch2.hpp"

#include <utl/dispatch_queue.hpp>

#include "StdoutReroute.hpp"

TEST_CASE("utl::dispatch_queue dispatch_item with handle") {
	utl_test::StdoutReroute _;
	
	utl::concurrent_dispatch_queue queue;
	
	int i = 0;
	
	utl::dispatch_item item = [&]{
		i = 1;
	};
	
	auto handle = item.get_handle();
	
	CHECK(i == 0);
	queue.async(std::move(item));
	
	handle.wait();
	
	CHECK(i == 1);
}


TEST_CASE("utl::dispatch_queue dispatch_item without handle") {
	
	int i = 0;
	
	{
		utl_test::StdoutReroute _;
		utl::concurrent_dispatch_queue queue;
		
		utl::dispatch_item item = [&]{
			i = 1;
		};
		
		CHECK(i == 0);
		queue.async(std::move(item));
	}
	
	CHECK(i == 1);
}


TEST_CASE("utl::dispatch_queue dispatch_group with handle") {
	utl_test::StdoutReroute _;
	utl::concurrent_dispatch_queue queue;
	
	std::atomic<std::size_t> value = 0;
	
	utl::dispatch_group group;
	auto handle = group.get_handle();
	for ([[maybe_unused]] int _: utl::iota(0, 16)) {
		group.add([&]() {
			++value;
		});
	}
	
	
	CHECK(value == 0);
	queue.async(std::move(group));
	
	handle.wait();
	
	CHECK(value == 16);
}

TEST_CASE("utl::dispatch_queue dispatch_group without handle") {
	
	std::atomic<std::size_t> value = 0;
	
	{
		utl_test::StdoutReroute _;
		utl::concurrent_dispatch_queue queue;
		
		utl::dispatch_group group;
		for ([[maybe_unused]] int _: utl::iota(0, 16)) {
			group.add([&]() {
				++value;
			});
		}
		
		CHECK(value == 0);
		queue.async(std::move(group));
	}
	
	CHECK(value == 16);
}

TEST_CASE("utl::dispatch_queue dispatch_group with handle and completion handler") {
	utl_test::StdoutReroute _;
	utl::concurrent_dispatch_queue queue;
	
	bool has_finished = false;
	std::atomic<std::size_t> value = 0;
	
	utl::dispatch_group group;
	
	for ([[maybe_unused]] int _: utl::iota(0, 16)) {
		group.add([&]() {
			++value;
		});
	}
	auto handle = group.get_handle();
	group.on_completion([&]{
		has_finished = true;
	});
	
	CHECK(value == 0);
	queue.async(std::move(group));
	handle.wait();
	CHECK(value == 16);
	CHECK(has_finished);
}

TEST_CASE("utl::dispatch_queue dispatch_group without handle with completion handler") {
	
	std::atomic<std::size_t> value = 0;
	bool has_finished = false;
	{
		utl_test::StdoutReroute _;
		utl::concurrent_dispatch_queue queue;
		
		utl::dispatch_group group;
		for ([[maybe_unused]] int _: utl::iota(0, 16)) {
			group.add([&]() {
				++value;
			});
		}
		group.on_completion([&]{
			has_finished = true;
		});
		CHECK(value == 0);
		queue.async(std::move(group));
	}
	
	CHECK(value == 16);
	CHECK(has_finished);
}


TEST_CASE("utl::dispatch_queue dispatch_group without handle with completion handler/ cancel") {
	
	std::atomic<std::size_t> value = 0;
	bool has_finished = false;
	{
		utl_test::StdoutReroute _;
		utl::concurrent_dispatch_queue queue(3);
		
		utl::dispatch_group group;
		for ([[maybe_unused]] int _: utl::iota(0, 32)) {
			group.add([&]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				++value;
			});
		}
		
		group.on_completion([&]{
			has_finished = true;
		});
		CHECK(value == 0);
		queue.async(std::move(group));
		queue.cancel_current_tasks();
	}
	
	CHECK(value < 32);
	CHECK(!has_finished);
}
