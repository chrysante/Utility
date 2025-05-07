#ifndef UTL_DISPATCH_CONCURRENT_DISPATCH_QUEUE_HPP_
#define UTL_DISPATCH_CONCURRENT_DISPATCH_QUEUE_HPP_

#include <future>
#include <ranges>

#include <utl/__base.hpp>
#include <utl/concepts.hpp>
#include <utl/dispatch/thread_pool.hpp>
#include <utl/functional.hpp>

namespace utl {

/// Thin wrapper around `utl::thread_pool`
class concurrent_dispatch_queue {
public:
    concurrent_dispatch_queue() = default;
    explicit concurrent_dispatch_queue(std::size_t thread_count):
        m_pool(thread_count) {}

    /// Run \p fn asynchronously. Effectivly calls `utl::thread_pool::submit()`
    void async(utl::function<void()> fn) { m_pool.submit(std::move(fn)); }

    /// Run \p fn asynchronously on each item of \p range
    template <std::ranges::input_range R, typename F>
    void async(R&& range, F&& fn)
    requires std::invocable<F> ||
             std::invocable<F, std::ranges::range_value_t<R>>
    {
        for (auto&& elem : range) {
            m_pool.submit([f = UTL_FORWARD(fn), elem = UTL_FORWARD(elem)] {
                if constexpr (std::invocable<F, decltype(elem)>) {
                    std::invoke(f, elem);
                }
                else {
                    std::invoke(f);
                }
            });
        }
    }

    void cancel_current_tasks() { m_pool.cancel_current_tasks(); }

    void wait_for_current_tasks() { m_pool.wait_for_current_tasks(); }

private:
    thread_pool m_pool;
};

} // namespace utl

#endif // UTL_DISPATCH_CONCURRENT_DISPATCH_QUEUE_HPP_
