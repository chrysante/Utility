#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "type_traits.hpp"
#include <utility>

#define UTL_STDLIB_HAS_CONCEPTS (_LIBCPP_VERSION >= 13000 || _MSC_VER >= 1923)

#if UTL_STDLIB_HAS_CONCEPTS
#include <concepts>
#endif // UTL_STDLIB_HAS_CONCEPTS

namespace utl {
	
	/// MARK: - Standard Concepts
#if UTL_STDLIB_HAS_CONCEPTS
	
	template <typename T>
	concept integral = std::integral<T>;
	
	template <typename T>
	concept signed_integral = std::signed_integral<T>;
	
	template <typename T>
	concept unsigned_integral = std::unsigned_integral<T>;
	
	template <typename T>
	concept floating_point = std::floating_point<T>;
	
	template <class From, class To>
	concept convertible_to = std::convertible_to<From, To>;
	
	template <typename Derived, typename Base>
	concept derived_from = std::derived_from<Derived, Base>;
	 
	template <class T, class U>
	concept same_as = std::same_as<T, U>;
	
	template <class F, class... Args>
	concept invocable = std::invocable<F, Args...>;
	
	template <class F, class... Args>
	concept regular_invocable = std::regular_invocable<F, Args...>;
	
#else // UTL_STDLIB_HAS_CONCEPTS
	
	template <typename T>
	concept integral = std::is_integral_v<T>;
	
	template <typename T>
	concept signed_integral = std::is_signed_v<T>;
	
	template <typename T>
	concept unsigned_integral = std::is_unsigned_v<T>;
	
	template <typename T>
	concept floating_point = std::is_floating_point_v<T>;
	
	template <class From, class To>
	concept convertible_to =
		std::is_convertible_v<From, To> &&
		requires {
			static_cast<To>(std::declval<From>());
		};
	
	template <typename Derived, typename Base>
	concept derived_from =
	  std::is_base_of_v<Base, Derived> &&
	  std::is_convertible_v<const volatile Derived*, const volatile Base*>;
	
	template <class T, class U>
	concept __utl_same_helper = std::is_same_v<T, U>;
	 
	template <class T, class U>
	concept same_as = __utl_same_helper<T, U> && __utl_same_helper<U, T>;
	
	template <class F, class... Args>
	concept invocable = template_true<std::invoke_result_t<F, Args...>>;
	
	template <class F, class... Args>
	concept regular_invocable = invocable<F, Args...>;
	
#endif // UTL_STDLIB_HAS_CONCEPTS
	
	template <typename T>
	concept arithmetic = std::is_arithmetic_v<T>;
	
	/// MARK: - Additional Concepts
	template <typename T>
	concept boolean_testable = requires(T&& t) {  static_cast<bool>(t); };
	
	template <typename T, typename U, typename ... V>
	concept any_of = (same_as<T, U> || ... || same_as<T, V>);
	
	template <class F, class R, class... Args>
	concept invocable_r = convertible_to<std::invoke_result_t<F, Args...>, R>;
	
	template <class R, class F, class... Args>
	concept regular_invocable_r = invocable_r<R, F, Args...>;

	template <class F>
	concept any_invocable = is_any_invocable<F>::value;
	
	template <typename I>
	concept input_iterator = requires(I&& i) {
		{ i != i } -> convertible_to<bool>;
		{ *i }     -> convertible_to<typename std::iterator_traits<I>::value_type>;
		{ ++i }    -> same_as<I&>;
	};
	
	template <typename I, typename T>
	concept input_iterator_for = input_iterator<I> && requires(I&& i) {
		{ *i } -> convertible_to<T>;
	};
	
}





