#include "Catch2.hpp"

#include <utl/dispatch/thread_pool.hpp>


TEST_CASE("thread_pool", "[thread_pool]") {
    utl::thread_pool p(3);
    std::atomic<int> i = 0;
    auto f = [&i]{
        i.fetch_add(1, std::memory_order_relaxed);
    };
    for (int i = 0; i < 50; ++i) {
        p.submit(f);
    }
    p.wait_for_current_tasks();
    CHECK(i == 50);
}

TEST_CASE("thread_pool cancel", "[thread_pool]") {
    std::size_t num_threads = 5;
    utl::thread_pool p(num_threads);
    std::atomic_bool barrier = true;
    std::atomic_int result = 0;
    /// Submit \p num_treads tasks which will not return until the barrier is lifted. This way the entire pool will be busy and anything submitted afterwards will not run yet.
    for (int i = 0; i < num_threads; ++i) {
        p.submit([&]{
            utl::busy_wait([&]{ return !barrier.load(); });
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            /// Do not alter \p result
        });
    }
    /// Submit more work which will alter \p result
    for (int i = 0; i < 10; ++i) {
        /// Do not alter \p result
        p.submit([&]{
            result.store(1);
        });
    }
    /// Cancel tasks. Tasks currently executing, i.e. the ones waiting on the barrier are not canceled.
    p.cancel_current_tasks(/* wait_for_current = */ false);
    /// Lift the barrier.
    barrier.store(false);
    p.wait_for_current_tasks();
    CHECK(result == 0);
}

static void dispatch_from_task(utl::thread_pool& p, std::atomic_int& result, int i) {
    p.submit([&, i]{
        if (i < 10) {
            dispatch_from_task(p, result, i + 1);
        }
        result.fetch_add(1);
    });
}

TEST_CASE("thread_pool dispatch from task", "[thread_pool]") {
    utl::thread_pool p(3);
    std::atomic_int result = 0;
    dispatch_from_task(p, result, 0);
    p.wait_for_current_tasks();
    CHECK(result == 11);
}
