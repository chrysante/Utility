#pragma once

#include "__base.hpp"
#include "__debug.hpp"
#include "concepts.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

	/// MARK: conversion
	template <utl::input_iterator I, std::invocable<typename std::iterator_traits<I>::value_type> Conversion>
	class conversion_iterator {
	public:
		using __I_traits     = std::iterator_traits<I>;
		using __I_value_type = typename __I_traits::value_type;
		
		using difference_type   = typename __I_traits::difference_type;
		using value_type        = std::invoke_result_t<Conversion, __I_value_type>;
		using pointer           = typename __I_traits::pointer;
		using reference         = typename __I_traits::reference;
		using iterator_category = typename __I_traits::iterator_category;
		
		static_assert(!std::same_as<value_type, void>);
		
		conversion_iterator(I itr, Conversion const& conversion_function): __itr(itr), __conv(conversion_function) {}
		conversion_iterator(I itr, Conversion&& conversion_function): __itr(itr), __conv(std::move(conversion_function)) {}
		
		conversion_iterator& operator++() {
			++__itr;
			return *this;
		}
		
		conversion_iterator operator++(int) {
			conversion_iterator result = *this;
			++__itr;
			return result;
		}
		
		I get_underlying_iterator() const { return __itr; }
		
		value_type operator*() const { return __conv(*__itr); }
		
		I __itr;
		[[no_unique_address]] Conversion __conv;
	};
	
	template <typename I, typename C>
	bool operator==(conversion_iterator<I, C> const& lhs, conversion_iterator<I, C> const& rhs) {
		return lhs.__itr == rhs.__itr;
	}
	
	template <typename I, typename C, typename J>
	bool operator==(conversion_iterator<I, C> const& lhs, J const& rhs) requires requires { lhs.__itr == rhs; }
	{
		return lhs.__itr == rhs;
	}
	
	/// MARK: stride_iterator
	template <utl::random_access_iterator I>
	class stride_iterator {
	public:
		using __I_traits     = std::iterator_traits<I>;
		
		using difference_type   = typename __I_traits::difference_type;
		using value_type        = typename __I_traits::value_type;
		using pointer           = typename __I_traits::pointer;
		using reference         = typename __I_traits::reference;
		using iterator_category = typename __I_traits::iterator_category;
		
		stride_iterator(I itr, std::size_t stride): __itr(itr), __stride(stride) {
			__utl_expect(stride > 0, "stride must be positive");
		}
		
		stride_iterator& operator++() {
			__itr += __stride;
			return *this;
		}
		
		stride_iterator operator++(int) {
			stride_iterator result;
			__itr += __stride;
			return result;
		}
		
		I get_underlying_iterator() const { return __itr; }
		
		reference operator*() const { return *__itr; }
		
		I __itr;
		std::size_t __stride;
	};
	
	template <typename I>
	bool operator==(stride_iterator<I> const& lhs, stride_iterator<I> const& rhs) {
		return lhs.__itr == rhs.__itr;
	}
	
	template <typename I, typename J>
	bool operator==(stride_iterator<I> const& lhs, J const& rhs) requires requires { lhs.__itr == rhs; }
	{
		return lhs.__itr == rhs;
	}

    auto __distance(auto first, auto last, std::input_iterator_tag) {
        typename std::iterator_traits<decltype(first)>::difference_type result = 0;
        while (first != last) {
            ++first;
            ++result;
        }
        return result;
    }

    auto __distance(auto first, auto last, std::random_access_iterator_tag) {
        return last - first;
    }

    template <typename Itr, typename S>
    auto distance(Itr first, S last) {
        return __distance(first, last,
                          typename std::iterator_traits<Itr>::iterator_category());
    }
    
}
