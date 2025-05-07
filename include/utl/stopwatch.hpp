#ifndef UTL_STOPWATCH_HPP_
#define UTL_STOPWATCH_HPP_

#include <atomic>
#include <chrono>

#include <utl/__base.hpp>

namespace utl {

template <typename Clock = std::chrono::high_resolution_clock>
class stopwatch {
public:
    using clock = Clock;
    using time_point = typename clock::time_point;
    using duration = typename clock::duration;

    void pause() {
        if (_paused) {
            return;
        }
        auto now = _now();
        _prev_duration += now - _start_point;
        _paused = true;
    }

    void resume() {
        if (!_paused) {
            return;
        }
        auto now = _now();
        _start_point = now;
        _paused = false;
    }

    void reset() {
        _paused = false;
        auto now = _now();
        _prev_duration = {};
        _start_point = now;
    }

    template <typename Duration = typename Clock::duration>
    typename Duration::rep elapsed_time() const {
        auto now = _now();
        auto dur =
            _paused ? _prev_duration : _prev_duration + (now - _start_point);
        return std::chrono::duration_cast<Duration>(dur).count();
    }

private:
    static typename Clock::time_point _now() {
        std::atomic_thread_fence(std::memory_order_relaxed);
        auto result = Clock::now();
        std::atomic_thread_fence(std::memory_order_relaxed);
        return result;
    }

private:
    typename Clock::duration _prev_duration{};
    bool _paused = false;
    typename Clock::time_point _start_point = Clock::now();
};

using precise_stopwatch = stopwatch<>;
using system_stopwatch = stopwatch<std::chrono::system_clock>;
using steady_stopwatch = stopwatch<std::chrono::steady_clock>;

} // namespace utl

#endif // UTL_STOPWATCH_HPP_
