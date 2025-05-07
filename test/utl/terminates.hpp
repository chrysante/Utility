#pragma once

#if UTL_POSIX

#include <atomic>
#include <chrono>
#include <concepts>
#include <functional>
#include <pthread.h>
#include <thread>

#include <utl/utility.hpp>

namespace utl_test {

enum struct exit_state { success, failure, timeout };

template <typename = void>
inline std::ostream& operator<<(std::ostream& str, exit_state s) {
    char const* const names[] = { "success", "failure", "timeout" };
    auto const index = static_cast<int>(s);
    __utl_bounds_check(index, 0, 3);
    auto hti = [](auto&& x) -> decltype(auto) { return UTL_FORWARD(x); };
    return hti(str) << names[index];
}

template <typename R, typename P>
bool terminates(std::chrono::duration<R, P> timeout,
                std::invocable auto&& test_fn) {
    struct Context {
        decltype(test_fn)& _test_fn;
        std::atomic_bool began;
        std::atomic_bool done;
    } context{ test_fn, false, false };

    pthread_t thread;
    pthread_create(&thread, nullptr, [](void* ctx_ptr) -> void* {
        Context& context = *(Context*)ctx_ptr;

        context.began = true;

        std::invoke(context._test_fn);

        context.done = true;

        return nullptr;
    }, &context);

    // wait for the thread to start to get more acurate behaviour for short
    // timeout durations
    utl::busy_wait([&] -> bool { return context.began; });

    using namespace std::chrono_literals;
    // wait for the thread to finish, after the timeout declare it stuck
    auto const state =
        utl::timed_busy_wait(timeout, [&]() -> bool { return context.done; });

    // cleanup
    if (context.done) {
        int const status = pthread_cancel(thread);
        __utl_assert(status == 0);
    }
    void* cancel_status = nullptr;
    int const status = pthread_join(thread, &cancel_status);
    __utl_assert(status == 0);
    __utl_assert(cancel_status == nullptr || cancel_status == PTHREAD_CANCELED);

    switch (state) {
    case utl::exit_state::success: return true;
    case utl::exit_state::timeout: return false;
    default: utl::unreachable();
    }
}

} // namespace utl_test

#endif // UTL_POSIX
