#include <numeric>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <utl/dispatch/concurrent_dispatch_queue.hpp>

TEST_CASE("concurrent_dispatch_queue::async(Range) - 1",
          "[concurrent_dispatch_queue]") {
    utl::concurrent_dispatch_queue q;
    std::atomic_int result = 0;
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);
    q.async(v, [&] { result.fetch_add(1); });
    q.wait_for_current_tasks();
    CHECK(result == 10);
}

TEST_CASE("concurrent_dispatch_queue::async(Range) - 2",
          "[concurrent_dispatch_queue]") {
    utl::concurrent_dispatch_queue q;
    std::atomic_int result = 0;
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);
    q.async(v, [&](int value) { result.fetch_add(value); });
    q.wait_for_current_tasks();
    CHECK(result == 9 * 10 / 2);
}
