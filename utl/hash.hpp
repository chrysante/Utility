#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_
#include <utility>
#include <string_view>
#include "concepts.hpp"

namespace utl {
	
	template <unsigned_integral T>
	constexpr T __utl_hash_seed = static_cast<T>(0x9e3779b97f4a7c15);
	
	template <typename T>
	_UTL_DISABLE_UBSAN_INTEGER
	void __do_hash_combine(std::size_t& seed, T const& v) {
		seed ^= std::hash<T>{}(v) + __utl_hash_seed<std::size_t> + (seed << 6) + (seed >> 2);
	}

	template <typename Key>
	concept __utl_hashable = std::is_default_constructible_v<std::hash<Key>>;
	
	template <__utl_hashable... Keys>
	std::size_t hash_combine(Keys const&... keys) {
		size_t seed = 0;
		(__do_hash_combine(seed, keys) , ... );
		return seed;
	}
	
	template <input_iterator I, sentinel_for<I> S>
	requires __utl_hashable<typename std::iterator_traits<I>::value_type>
	std::size_t hash_combine_range(I begin, S end) {
		size_t seed = __utl_hash_seed<std::size_t>;
		for (; begin != end; ++begin) {
			__do_hash_combine(seed, *begin);
		}
		return seed;
	}
	
	template <typename T>
	struct hash: std::hash<T> {
		using std::hash<T>::operator();
	};
	
	template <typename T, typename U>
	struct hash<std::pair<T, U>> {
		std::size_t operator()(std::pair<T, U> const& p) const {
			return utl::hash_combine(p.first, p.second);
		}
	};
	
	constexpr std::size_t hash_string(std::string_view str) {
		std::size_t result = 0xcbf29ce484222325; // FNV offset basis

		for (char c : str) {
			result ^= c;
			result *= 1099511628211; // FNV prime
		}

		return result;
	}
	
}


