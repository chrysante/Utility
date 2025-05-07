#ifndef UTL_UTILITY_HPP
#define UTL_UTILITY_HPP

#include <bit>
#include <chrono>
#include <cstddef>
#include <iosfwd>
#include <memory>
#include <thread>

#include <utl/__base.hpp>
#include <utl/__debug.hpp>
#include <utl/concepts.hpp>
#include <utl/math.hpp>
#include <utl/type_traits.hpp>

namespace utl {

struct __nc_assert {
    static constexpr void check(bool condition) { __utl_expect(condition); }
};

/// \brief Performs a checked integral `static_cast`
/// \details Before performing the cast, `narrow_cast` checks if the argument
/// fits into the destination type. Checks can be customized by the `Traits`
/// template parameter. By default assertions are triggered when the cast fails.
template <std::integral To, typename Traits = __nc_assert, std::integral From>
constexpr To narrow_cast(From value) {
    if constexpr (std::is_signed_v<From> && std::is_unsigned_v<To>) {
        /// Casting from `signed` to `unsigned`.
        Traits::check(value >= static_cast<From>(0));
        /// Hand off to `narrow_cast` from `unsigned` to `unsigned`.
        return narrow_cast<To>(static_cast<std::make_unsigned_t<From>>(value));
    }
    else if constexpr (std::is_unsigned_v<From> && std::is_signed_v<To>) {
        /// Casting from `unsigned` to `signed`.
        if constexpr (sizeof(From) <= sizeof(To)) {
            /// Conversion might narrow.
            Traits::check(value <= static_cast<std::make_unsigned_t<To>>(
                                       std::numeric_limits<To>::max()));
        }
        return static_cast<To>(value);
    }
    else {
        /// Both are either `signed` or `unsigned`.
        if constexpr (sizeof(To) < sizeof(From)) {
            Traits::check(value <=
                          static_cast<From>(std::numeric_limits<To>::max()));
            Traits::check(value >=
                          static_cast<From>(std::numeric_limits<To>::min()));
        }
        return static_cast<To>(value);
    }
}

/// \brief Performs a checked floating point `static_cast`
template <std::floating_point To, typename Traits = __nc_assert,
          std::floating_point From>
constexpr To narrow_cast(From value) {
    if constexpr (sizeof(From) <= sizeof(To)) {
        return value;
    }
    else {
        To const result = static_cast<To>(value);
        Traits::check(value == static_cast<From>(result));
        return result;
    }
}

/// \brief Performs a checked downward pointer cast in an inheritance hierarchy.
/// \details Asserts when cast is invalid.
template <typename To, typename From>
requires(std::is_base_of_v<From, std::remove_pointer_t<To>> &&
         std::is_pointer_v<To>)
To down_cast(From* from) noexcept {
    __utl_assert(dynamic_cast<To>(from) != nullptr);
    return static_cast<To>(from);
}

/// \brief Performs a checked downward reference cast in an inheritance
/// hierarchy. \details Asserts when cast is invalid.
template <typename To, typename From>
requires(std::is_base_of_v<From, std::remove_reference_t<To>> &&
         std::is_reference_v<To>)
To down_cast(From& from) noexcept {
    using ToPtr = std::remove_reference_t<To>*;
    __utl_assert(dynamic_cast<ToPtr>(&from) != nullptr);
    return static_cast<To>(from);
}

/// \brief Wrapper around an array to be used as a fixed size buffer on the
/// stack. \details Can be used in conjunction with `monotonic_buffer_resource`
/// as initial buffer.
template <std::size_t Size, std::size_t Alignment = alignof(std::max_align_t)>
class stack_buffer {
public:
    stack_buffer() = default;
    stack_buffer(stack_buffer const&) = default;
    stack_buffer& operator=(stack_buffer const&) = default;

    constexpr void* data() { return &__utl_data[0]; }
    constexpr void const* data() const { return &__utl_data[0]; }
    constexpr std::size_t size() const { return Size; };

    alignas(Alignment) char __utl_data[Size];
};

/// \brief Generic error code.
enum struct exit_state { success, failure, timeout };

template <typename = void>
inline std::ostream& operator<<(std::ostream& str, exit_state s) {
    char const* const names[] = { "success", "failure", "timeout" };
    auto const index = static_cast<int>(s);
    __utl_bounds_check(index, 0, 3);
    auto hti = [](auto&& x) -> decltype(auto) { return UTL_FORWARD(x); };
    return hti(str) << names[index];
}

/// \brief Busily wait for \p predicate to return true.
void busy_wait(std::predicate auto&& predicate) {
    while (!predicate()) {
        std::this_thread::yield();
    }
}

/// \brief Busily wait for \p predicate to return true or \p timeout to elapse.
template <typename R, typename P>
exit_state timed_busy_wait(std::chrono::duration<R, P> timeout,
                           std::predicate auto&& predicate) {
    auto const begin = std::chrono::high_resolution_clock::now();
    while (true) {
        auto const now = std::chrono::high_resolution_clock::now();
        auto const elapsed =
            std::chrono::duration_cast<std::chrono::duration<R, P>>(now -
                                                                    begin);
        if (predicate()) {
            return exit_state::success;
        }
        if (elapsed >= timeout) {
            return exit_state::timeout;
        }
        std::this_thread::yield();
    }
}

/// MARK: Enum Map

// Not sure what to think of this
template <typename E, typename T, std::size_t N = (std::size_t)E::_count>
struct __enum_map {
    constexpr __enum_map(std::pair<E, T> const (&a)[N]): __data{} {
        if constexpr (requires { E::_count; }) {
            static_assert(N == (std::size_t)E::_count);
        }
        for (std::size_t i = 0; i < N; ++i) {
            __utl_assert((std::size_t)a[i].first == i,
                         "Make sure every enum case is handled");
            __data[i] = a[i].second;
        }
    }

    constexpr T const& operator[](E i) const { return __data[(std::size_t)i]; }

    std::array<T, N> __data;
};

template <typename... E, typename... T>
__enum_map(std::pair<E, T>...)
    -> __enum_map<std::common_type_t<E...>, std::common_type_t<T...>>;

#define UTL_MAP_ENUM(__utl_e, T, ...)                                          \
    [&](auto __utl_x) {                                                        \
        using E = ::std::decay_t<decltype(__utl_x)>;                           \
        constexpr ::utl::__enum_map<E, T> __utl_s = { __VA_ARGS__ };           \
        __utl_assert((::std::size_t)__utl_x < __utl_s.__data.size(),           \
                     "Invalid enum case");                                     \
        return __utl_s[__utl_x];                                               \
    }(__utl_e)

#define UTL_SERIALIZE_ENUM(__utl_e, ...)                                       \
    UTL_MAP_ENUM(__utl_e, std::string_view, __VA_ARGS__)

} // namespace utl

#endif // UTL_UTILITY_HPP
