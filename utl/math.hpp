#pragma once

#include <bit>

#include "__base.hpp"
#include "__debug.hpp"
#include "bit.hpp"
#include "concepts.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <std::size_t NumItr = 1>
inline float fast_inv_sqrt(float number) {
    float const x2 = number * 0.5F;
    std::int32_t i = utl::bit_cast<std::int32_t>(number); // evil floating point bit level hacking
    i              = 0x5f3759df - (i >> 1);               // what the fuck?
    float y        = utl::bit_cast<float>(i);
    for (int j = 0; j < NumItr; ++j) {
        y *= 1.5f - (x2 * y * y);
    }
    return y;
}

template <std::integral To, std::integral From>
constexpr To narrow_cast(From x); // fwd decl

template <std::integral T>
constexpr int log2(T x) {
    if constexpr (std::signed_integral<T>) {
        __utl_expect(x > 0, "log2 is not defined for x <= 0");
        return log2((std::make_unsigned_t<T>)x);
    }
    else if constexpr (std::same_as<T, uint64_t>) {
        __utl_expect(std::popcount(x) == 1, "x must be a power of 2");
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_ctzl(x);
#else
        int result = 0;
        while ((x /= 2) != 0) {
            ++result;
        }
        return result;
#endif
    }
    else {
        static_assert(sizeof(T) < 16, "Not implemented for 128 bit integers");
        return log2((uint64_t)x);
    }
}

template <std::unsigned_integral T>
constexpr T fast_div_pow_two(T x, T y) {
    __utl_expect(y >= 0);
    __utl_expect(std::popcount(y) == 1);
    int const e = utl::log2(y);
    return x >> e;
}
template <std::integral T, std::integral U>
requires std::unsigned_integral<std::common_type_t<T, U>>
constexpr std::common_type_t<T, U> fast_div_pow_two(T x, U y) {
    using X = std::common_type_t<T, U>;
    return fast_div_pow_two((X)x, (X)y);
}

template <std::unsigned_integral T>
constexpr T fast_mod_pow_two(T x, T y) {
    __utl_expect(y >= 0);
    __utl_expect(std::popcount(y) == 1);
    int const e  = utl::log2(y);
    T const mask = ~(std::numeric_limits<T>::max() << e); /* eg. for uint8 with e = 3: 00000111  */
    return mask & x;
}
template <std::integral T, std::integral U>
requires std::unsigned_integral<std::common_type_t<T, U>>
constexpr std::common_type_t<T, U> fast_mod_pow_two(T x, U y) {
    using X = std::common_type_t<T, U>;
    return fast_mod_pow_two((X)x, (X)y);
}

template <typename T, typename A>
__utl_nodiscard constexpr T mix(T const& t, T const& u, A const& alpha) {
    return t * (1 - alpha) + u * alpha;
}

constexpr auto __round_up_impl(auto x, auto multiple_of, auto&& modfn) noexcept {
    auto const remainder = modfn(x, multiple_of);
    return remainder == 0 ? x : x + multiple_of - remainder;
}

template <std::integral T, std::integral U>
constexpr auto round_up(T x, U multiple_of) {
    return __round_up_impl(narrow_cast<std::make_unsigned_t<T>>(x),
                           narrow_cast<std::make_unsigned_t<U>>(multiple_of),
                           [](auto x, auto y) { return x % y; });
}

template <std::integral T, std::integral U>
constexpr auto round_up_pow_two(T x, U multiple_of) {
    return __round_up_impl(narrow_cast<std::make_unsigned_t<T>>(x),
                           narrow_cast<std::make_unsigned_t<U>>(multiple_of),
                           [](auto x, auto y) { return fast_mod_pow_two(x, y); });
}

constexpr auto __round_down_impl(auto x, auto multiple_of, auto&& modfn) noexcept {
    auto const remainder = modfn(x, multiple_of);
    return x - remainder;
}

template <std::integral T, std::integral U>
constexpr auto round_down(T x, U multiple_of) {
    return __round_down_impl(narrow_cast<std::make_unsigned_t<T>>(x),
                             narrow_cast<std::make_unsigned_t<U>>(multiple_of),
                             [](auto x, auto y) { return x % y; });
}

template <std::integral T, std::integral U>
constexpr auto round_down_pow_two(T x, U multiple_of) {
    return __round_down_impl(narrow_cast<std::make_unsigned_t<T>>(x),
                             narrow_cast<std::make_unsigned_t<U>>(multiple_of),
                             [](auto x, auto y) { return fast_mod_pow_two(x, y); });
}

template <typename T>
requires requires(T&& t) {
    {
        t* t
        } -> std::convertible_to<T>;
}
constexpr T ipow(T base, int exp) {
    __utl_expect(exp >= 0);
    return exp == 1     ? base :
           exp == 0     ? 1 :
           exp % 2 == 0 ? ipow(base * base, exp / 2) :
                          base * ipow(base * base, exp / 2);
}

} // namespace utl

#include "utility.hpp"
