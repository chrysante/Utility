#ifndef UTL_FORMAT_TIME_HPP_
#define UTL_FORMAT_TIME_HPP_

#include <array>
#include <chrono>
#include <sstream>
#include <string>
#include <tuple>

#include <utl/__base.hpp>

namespace utl {

template <typename Duration, class DurationIn>
Duration __break_down_one(DurationIn& d) {
    auto const result = std::chrono::duration_cast<Duration>(d);
    d -= std::chrono::duration_cast<DurationIn>(result);
    return result;
}

template <typename... Durations, typename DurationIn>
std::tuple<Durations...> __break_down_durations(DurationIn d) {
    return { __break_down_one<Durations, DurationIn>(d)... };
}

template <typename... Durations, typename DurationIn>
std::array<long long, sizeof...(Durations)>
__break_down_durations_to_int(DurationIn d) {
    auto ret = __break_down_durations<Durations...>(d);
    return { std::get<Durations>(ret).count()... };
}

template <typename>
inline constexpr auto __dur_ending = nullptr;

template <>
inline constexpr auto __dur_ending<std::chrono::years> = "y";
template <>
inline constexpr auto __dur_ending<std::chrono::months> = "m";
template <>
inline constexpr auto __dur_ending<std::chrono::weeks> = "w";
template <>
inline constexpr auto __dur_ending<std::chrono::days> = "d";
template <>
inline constexpr auto __dur_ending<std::chrono::hours> = "h";
template <>
inline constexpr auto __dur_ending<std::chrono::minutes> = "m";
template <>
inline constexpr auto __dur_ending<std::chrono::seconds> = "s";
template <>
inline constexpr auto __dur_ending<std::chrono::milliseconds> = "ms";
template <>
inline constexpr auto __dur_ending<std::chrono::microseconds> = "us";
template <>
inline constexpr auto __dur_ending<std::chrono::nanoseconds> = "ns";

/// Format duration \p dur to following format:
/// ```
/// "y:m:d:h:m:s:ms:us:ns"
/// ```
/// where all but the first \p Prec non-zero entries are omitted.
template <size_t Prec, typename Rep, typename Period>
std::string format_duration(std::chrono::duration<Rep, Period> dur) {
    using namespace std::chrono;
    std::array parts =
        __break_down_durations_to_int<years, months, days, hours, minutes,
                                      seconds, milliseconds, microseconds,
                                      nanoseconds>(dur);
    static constexpr std::array __dur_endings{ "y", "m",  "d",  "h", "m",
                                               "s", "ms", "us", "ns" };
    size_t k = 0;
    for (; k < parts.size() && parts[k] == 0; ++k) {
    }
    if (k == parts.size()) {
        return "0";
    }
    std::stringstream str;
    for (size_t i = k, end = std::min(parts.size(), k + Prec); i < end; ++i) {
        auto p = parts[i];
        auto e = __dur_endings[i];
        if (p == 0) {
            continue;
        }
        if (i != k) {
            str << ":";
        }
        str << p << e;
    }
    return std::move(str).str();
}

/// Format duration \p dur to specified durations or automatically if none are
/// specified.
template <typename... Durations, typename Rep, typename Period>
std::string format_duration(std::chrono::duration<Rep, Period> dur) {
    if constexpr (sizeof...(Durations) == 0) {
        return format_duration<3>(dur);
    }
    else {
        std::tuple<Durations...> parts =
            __break_down_durations<Durations...>(dur);
        std::stringstream str;
        bool first = true;
        ((str << (first ? (void)(first = false), "" : ":")
              << std::get<Durations>(parts).count() << __dur_ending<Durations>),
         ...);
        return std::move(str).str();
    }
}

} // namespace utl

#endif // UTL_FORMAT_TIME_HPP_
