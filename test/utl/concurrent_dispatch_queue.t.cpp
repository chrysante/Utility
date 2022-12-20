#include <catch/catch2.hpp>

#include <utl/dispatch/concurrent_dispatch_queue.hpp>
#include <utl/ranges.hpp>

TEST_CASE("concurrent_dispatch_queue::async(Range) - 1", "[concurrent_dispatch_queue]") {
    utl::concurrent_dispatch_queue q;
    std::atomic_int result = 0;
    q.async(utl::iota(10), [&]{
        result.fetch_add(1);
    });
    q.wait_for_current_tasks();
    CHECK(result == 10);
}

TEST_CASE("concurrent_dispatch_queue::async(Range) - 2", "[concurrent_dispatch_queue]") {
    utl::concurrent_dispatch_queue q;
    std::atomic_int result = 0;
    q.async(utl::iota(10), [&](int value){
        result.fetch_add(value);
    });
    q.wait_for_current_tasks();
    CHECK(result == 9 * 10 / 2);
}
