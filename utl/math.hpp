#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_


#include "__function_objects.hpp"
#include "concepts.hpp"
#include <bit>

namespace utl {
	
	template <integral T>
	constexpr int log2(T x) {
		if constexpr (signed_integral<T>) {
			__utl_expect(x > 0, "log2 is not defined for x <= 0");
			return log2((std::make_unsigned_t<T>)x);
		}
		else if constexpr (same_as<T, uint64_t>) {
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

	template <integral T>
	constexpr T fast_mod_pow_two(T x, T y) {
		__utl_expect(y >= 0);
		__utl_expect(std::popcount(y) == 1);
		T const e = utl::log2(y);
		return ~(~T{} << e) & x;
	}
	template <integral T, integral U>
	constexpr std::common_type_t<T, U> fast_mod_pow_two(T x, U y) {
		using X = std::common_type_t<T, U>;
		return fast_mod_pow_two((X)x, (X)y);
	}
	
	template <typename T, typename A>
	__utl_nodiscard constexpr T mix(T const& t, T const& u, A const& alpha) {
		return t * (1 - alpha) + u * alpha;
	}
	
	constexpr auto __round_up_impl(auto x, std::size_t multiple_of, auto&& modfn) noexcept {
		auto const remainder = modfn(x, multiple_of);
		return remainder == 0 ? x : x + multiple_of - remainder;
	}
	
	constexpr auto round_up(integral auto x, std::size_t multiple_of) noexcept {
		return __round_up_impl(x, multiple_of, [](auto x, auto y) { return x % y; });
	}
	
	constexpr auto round_up_pow_two(integral auto x, std::size_t multiple_of) noexcept {
		return __round_up_impl(x, multiple_of, [](auto x, auto y) { return fast_mod_pow_two(x, y); });
	}
	
	template <typename T>
	requires requires(T&& t) { { t * t } -> convertible_to<T>; }
	constexpr T ipow(T base, int exp) {
		__utl_expect(exp >= 0);
		return
			exp     == 1 ? base :
			exp     == 0 ? 1 :
			exp % 2 == 0 ? ipow(base * base, exp / 2) :
					base * ipow(base * base, exp / 2);
	}
	
}
