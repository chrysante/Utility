#ifndef UTL_DISPATCH_THREADPOOL_HPP
#define UTL_DISPATCH_THREADPOOL_HPP

#include <atomic>
#include <deque>
#include <future>
#include <thread>

#include <utl/__base.hpp>
#include <utl/__debug.hpp>
#include <utl/api.hpp>
#include <utl/concepts.hpp>
#include <utl/functional.hpp>
#include <utl/hashmap.hpp>
#include <utl/type_traits.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

class UTL_API dispatch_item {
public:
    using cancel_handler_type = void (*)(void*);

    dispatch_item(std::invocable auto&& work): work(UTL_FORWARD(work)) {}

    dispatch_item(utl::unique_function<void()>&& work): work(std::move(work)) {}

    dispatch_item(utl::unique_function<void()>&& work,
                  cancel_handler_type cancel_handler,
                  void* cancel_handler_user_pointer):
        work(std::move(work)),
        cancel_handler(cancel_handler),
        cancel_handler_user_pointer(cancel_handler_user_pointer) {}

    void execute() { work(); }

    void run_cancel_handler() {
        if (cancel_handler) {
            cancel_handler(cancel_handler_user_pointer);
        }
    }

private:
    utl::unique_function<void()> work;
    cancel_handler_type cancel_handler = nullptr;
    void* cancel_handler_user_pointer = nullptr;
};

/// \brief Maintains a pool of threads and thus allows submission of tasks to be
/// executed asynchronously. \details Submitted work items are executed in FIFO
/// order.
class UTL_API thread_pool {
public:
    /// \brief Constructs a `thread_pool` with
    /// `std::thread::hardware_concurrency()` threads.
    thread_pool();

    /// \brief Constructs a `thread_pool` with \p thread_count threads.
    explicit thread_pool(std::size_t thread_count);

    ~thread_pool();

    /// \brief Submits \p item to be executed asynchronously.
    /// \details \p item itself may make calls to submit. However behaviour is
    /// undefined and will likely end up dead locking if it waits for the
    /// submitted work to finish executing.
    void submit(dispatch_item item);

    /// \brief Cancels the submitted tasks.
    /// \details Tasks currently executing will finish before this function
    /// returns. \param wait_for_current If true, waits for all currently
    /// executing tasks to finish before returning.
    void cancel_current_tasks(bool wait_for_current = true);

    /// \brief Wait for all submitted tasks to be executed.
    void wait_for_current_tasks();

    /// \brief Number of threads maintained.
    std::size_t num_threads() const { return m_threads.size(); }

private:
    void work_loop(std::size_t index);
    void wait_for_current_tasks(std::unique_lock<std::mutex>);
    bool all_idle() const;

private:
    struct thread_wrapper: std::thread {
        using std::thread::thread;
        bool active = false;
    };

private:
    utl::vector<thread_wrapper> m_threads;
    std::deque<dispatch_item> m_items;
    std::mutex m_mutex;
    std::condition_variable m_loop_cv;
    std::condition_variable m_control_cv;
    bool m_run = true;
};

} // namespace utl

#endif // UTL_DISPATCH_THREADPOOL_HPP
