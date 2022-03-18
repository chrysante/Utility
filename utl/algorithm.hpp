#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "common.hpp"
#include "type_traits.hpp"
#include <cstddef>
#include <tuple>
#include <algorithm>
#include <limits>
#include <iosfwd>
#include "concepts.hpp"

namespace utl {

	template <typename T, std::size_t Size>
	std::size_t array_size(T const(&)[Size]) { return Size; }
	
	
	enum struct direction {
		forward, backward
	};
	
	inline constexpr auto forward = direction::forward;
	inline constexpr auto backward = direction::backward;
	
	template <typename Range,
			  typename F> requires (is_range<Range>::value)
	void for_each(Range& r, F&& f) {
		auto const end = r.end();
		for (auto i = r.begin(); i != end; ++i)
			f(*i);
	}
	
	/*
	 *	f should return true to break, false to continue, or void to not break at all
	 *  returns true if loop has been broken
	 */
	template <direction dir = forward, typename... Range,
			  typename F> requires((is_range<Range>::value && ...))
	auto find_if(F&& f, Range&&... r) {
		auto const invoke_f = [&](std::size_t index, auto&&... args) {
			if constexpr (std::is_invocable<F, decltype(args)...>::value) {
				static_assert(std::is_constructible<bool, decltype(f(std::forward<decltype(args)>(args)...))>::value);
				return f(std::forward<decltype(args)>(args)...);
			}
			else {
				static_assert((std::is_invocable<F, std::size_t, decltype(args)...>::value));
				static_assert(std::is_constructible<bool, decltype(f(std::size_t{}, std::forward<decltype(args)>(args)...))>::value);
				return f(index, std::forward<decltype(args)>(args)...);
			}
		};
		
		auto const empty_invoke_result = [&]{
			return decltype(invoke_f(0, *r.begin()...)){};
		};
		
		if constexpr (dir == direction::forward) {
			return [&](auto... i) {
				auto const end = std::min({ (r.end() - r.begin())... });
				for (std::size_t index = 0; index != end; ++index, (++i, ...)) {
					if (auto result = invoke_f(index, *i...)) {
						return result;
					}
				}
				return empty_invoke_result();
			}(r.begin()...);
		}
		else {
			static_assert(dir == direction::backward);
			return [&](auto... i) {
				auto const begin = std::min({ (r.end() - r.begin())... });
				for (std::ptrdiff_t index = static_cast<std::ptrdiff_t>(begin) - 1;
					 index >= 0;
					 --index, (++i, ...))
				{
					if (auto result = invoke_f(index, *i...)) {
						return result;
					}
				}
				return empty_invoke_result();
			}(std::reverse_iterator(r.end())...);
		}
	}
	
	template <direction dir = forward, typename... Range,
			  typename F> requires((is_range<Range>::value && ...))
	void for_each(F&& f, Range&&... r) {
		auto const invoke_f = [&](std::size_t index, auto&&... args) {
			if constexpr (std::is_invocable<F, decltype(args)...>::value) {
				f(std::forward<decltype(args)>(args)...);
			}
			else {
				static_assert((std::is_invocable<F, std::size_t, decltype(args)...>::value));
				f(index, std::forward<decltype(args)>(args)...);
			}
		};
		
		if constexpr (dir == direction::forward) {
			return [&](auto... i) {
				auto const end = std::min({ (r.end() - r.begin())... });
				for (std::size_t index = 0; index != end; ++index, (++i, ...)) {
					invoke_f(index, *i...);
				}
			}(r.begin()...);
		}
		else {
			static_assert(dir == direction::backward);
			return [&](auto... i) {
				auto const begin = std::min({ (r.end() - r.begin())... }) - 1;
				auto const end   = std::numeric_limits<std::size_t>::max();
				for (std::size_t index = begin; index != end; --index, (++i, ...)) {
					invoke_f(index, *i...);
				}
			}(std::reverse_iterator(r.end())...);
		}
	}
	
	template <typename T, std::size_t Size,
			  typename F>
	void for_each(T (&array)[Size], F&& f) {
		auto const end = array + Size;
		for (auto i = array; i != end; ++i)
			f(*i);
	}
	
	template <typename It, typename F> requires(is_iterator<It>::value)
	void for_each(It begin, It end, F&& f) {
		for (; begin != end; ++begin) {
			f(*begin);
		}
	}
	
	template <typename It1, typename It2, typename F>
	requires(is_iterator<It1>::value && is_iterator<It2>::value)
	void for_each(It1 begin1, It1 end1, It2 begin2, F&& f) {
		for (; begin1 != end1; ++begin1, ++begin2) {
			f(*begin1, *begin2);
		}
	}
	
	
	
	
	
	
}
