#pragma once

#include "__base.hpp"
_MTL_SYSTEM_HEADER_

/// This is an implementation of some standard concepts that are not yet implemented in libc++ version < 13

#ifndef __MTL_STD_CONCEPTS_HPP_INCLUDED__
#define __MTL_STD_CONCEPTS_HPP_INCLUDED__

#if defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 13000
#	define MTL_STDLIB_HAS_CONCEPTS 1
#elif defined(_MSC_VER) && _MSC_VER >= 1923
#	define MTL_STDLIB_HAS_CONCEPTS 1
#else 
#	define MTL_STDLIB_HAS_CONCEPTS 0 
#endif

#include <type_traits>

#if MTL_STDLIB_HAS_CONCEPTS
#include <concepts>
#endif // MTL_STDLIB_HAS_CONCEPTS

namespace _VMTL {

	template <typename...> struct __mtl_template_true_type: std::true_type{};
	
#if MTL_STDLIB_HAS_CONCEPTS
	
	template <class From, class To>
	concept convertible_to = std::convertible_to<From, To>;
	
	template <class T, class U>
	concept same_as = std::same_as<T, U>;

	template <class F, class... Args>
	concept invocable = std::invocable<F, Args...>;
	
	template <class F, class... Args>
	concept regular_invocable = std::regular_invocable<F, Args...>;

#else // MTL_STDLIB_HAS_CONCEPTS
	
	template <class From, class To>
	concept convertible_to =
		std::is_convertible_v<From, To> &&
		requires {
			static_cast<To>(std::declval<From>());
		};
	
	template <class T, class U>
	concept __mtl_same_helper = std::is_same_v<T, U>;
	
	template <class T, class U>
	concept same_as = __mtl_same_helper<T, U> && __mtl_same_helper<U, T>;
	
	template <class F, class... Args>
	concept invocable = __mtl_template_true_type<std::invoke_result_t<F, Args...>>::value;
	
	template <class F, class... Args>
	concept regular_invocable = invocable<F, Args...>;
	
#endif // MTL_STDLIB_HAS_CONCEPTS
	
	template <class F, class R, class... Args>
	concept invocable_r = /*invocable<F, Args...> && */ convertible_to<std::invoke_result_t<F, Args...>, R>;
	
	template <class R, class F, class... Args>
	concept regular_invocable_r = invocable_r<R, F, Args...>;
	
}

#endif // __MTL_STD_CONCEPTS_HPP_INCLUDED__
