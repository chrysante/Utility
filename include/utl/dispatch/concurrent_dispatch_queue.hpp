#ifndef UTL_DISPATCH_CONCURRENTDISPATCHQUEUE_HPP
#define UTL_DISPATCH_CONCURRENTDISPATCHQUEUE_HPP

#include <future>

#include "../__base.hpp"
#include "../functional.hpp"
#include "../concepts.hpp"
#include "thread_pool.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

/// Thin wrapper around \p utl::thread_pool
class concurrent_dispatch_queue {
public:
    concurrent_dispatch_queue() = default;
    explicit concurrent_dispatch_queue(std::size_t thread_count): m_pool(thread_count) {}
    
    /// Run \p fn asynchronously. Effectivly calls \p utl::thread_pool::submit()
    void async(utl::function<void()> fn) { m_pool.submit(std::move(fn)); }
    
    /// Run \p fn asynchronously on each item of \p range
    template <input_range R, typename F>
    void async(R&& range, F&& fn) requires std::invocable<F> || std::invocable<F, decltype(*__utl_begin(range))> {
        for (auto&& elem: range) {
            m_pool.submit([f = UTL_FORWARD(fn), elem = UTL_FORWARD(elem)]{
                if constexpr (std::invocable<F, decltype(elem)>) {
                    std::invoke(f, elem);
                }
                else {
                    std::invoke(f);
                }
            });
        }
    }
    
    void cancel_current_tasks() {
        m_pool.cancel_current_tasks();
    }
    
    void wait_for_current_tasks() {
        m_pool.wait_for_current_tasks();
    }
    
private:
    thread_pool m_pool;
};

}

#endif // UTL_DISPATCH_CONCURRENTDISPATCHQUEUE_HPP
