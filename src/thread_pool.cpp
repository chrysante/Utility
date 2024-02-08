#include <utl/dispatch/thread_pool.hpp>

using namespace utl;

utl::thread_pool::thread_pool():
    thread_pool(std::thread::hardware_concurrency()) {}

utl::thread_pool::thread_pool(std::size_t thread_count) {
    m_threads.reserve(thread_count);
    for (std::size_t i = 0; i < thread_count; ++i) {
        m_threads.emplace_back([this, i] { this->work_loop(i); });
    }
}

utl::thread_pool::~thread_pool() {
    wait_for_current_tasks();
    m_mutex.lock();
    m_run = false;
    m_loop_cv.notify_all();
    m_mutex.unlock();
    for (auto& t : m_threads) {
        t.join();
    }
}

void utl::thread_pool::submit(dispatch_item item) {
    std::unique_lock lock(m_mutex);
    m_items.push_back(std::move(item));
    lock.unlock();
    m_loop_cv.notify_one();
}

void utl::thread_pool::cancel_current_tasks(bool wait_for_current) {
    std::unique_lock lock(m_mutex);
    std::for_each(m_items.begin(), m_items.end(),
                  [](dispatch_item& item) { item.run_cancel_handler(); });
    m_items.clear();
    if (wait_for_current) {
        wait_for_current_tasks(std::move(lock));
    }
}

void utl::thread_pool::work_loop([[maybe_unused]] std::size_t index) {
    std::unique_lock lock(m_mutex);
    while (true) {
        // We enter the loop locked
        if (!m_run) {
            return;
        }
        m_loop_cv.wait(lock, [&] { // Wait for work or destruction
            return !m_items.empty() || !m_run;
        });
        if (!m_items.empty()) {
            auto item = std::move(m_items.front());
            m_items.pop_front();
            m_threads[index].active = true;
            lock.unlock();
            item.execute();
            lock.lock();
            m_threads[index].active = false;
            m_control_cv.notify_one();
        }
        else {
            m_control_cv.notify_one();
        }
    }
}

void utl::thread_pool::wait_for_current_tasks() {
    wait_for_current_tasks(std::unique_lock(m_mutex));
}

void utl::thread_pool::wait_for_current_tasks(
    std::unique_lock<std::mutex> lock) {
    m_control_cv.wait(lock, [this] { return m_items.empty() && all_idle(); });
}

bool utl::thread_pool::all_idle() const {
    for (auto& t : m_threads) {
        if (t.active) {
            return false;
        }
    }
    return true;
}
