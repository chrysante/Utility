#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "type_traits.hpp"
#include <utility>

#if defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 13000
#	define UTL_STDLIB_HAS_CONCEPTS 1
#elif defined(_MSC_VER) && _MSC_VER >= 1923
#	define UTL_STDLIB_HAS_CONCEPTS 1
#else 
#	define UTL_STDLIB_HAS_CONCEPTS 0 
#endif

#if UTL_STDLIB_HAS_CONCEPTS
#include <concepts>
#endif // UTL_STDLIB_HAS_CONCEPTS

namespace utl {

	/// MARK: - Standard Concepts
#if UTL_STDLIB_HAS_CONCEPTS
<<<<<<< HEAD
	
=======

>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
	template <typename T>
	concept integral = std::integral<T>;

	template <typename T>
	concept signed_integral = std::signed_integral<T>;

	template <typename T>
	concept unsigned_integral = std::unsigned_integral<T>;

	template <typename T>
	concept floating_point = std::floating_point<T>;

	template <typename Derived, typename Base>
	concept derived_from = std::derived_from<Derived, Base>;

	template <class T, class U>
	concept same_as = std::same_as<T, U>;

	template <class F, class... Args>
	concept invocable = std::invocable<F, Args...>;

	template <class F, class... Args>
	concept regular_invocable = std::regular_invocable<F, Args...>;

	template <class From, class To>
	concept convertible_to = std::convertible_to<From, To>;

	template <typename T>
<<<<<<< HEAD
=======
	concept copy_constructible = std::copy_constructible<T>;

	template <typename T, typename... Args >
	concept constructible_from = std::constructible_from<T, Args...>;

#else // UTL_STDLIB_HAS_CONCEPTS

	template <typename T>
>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
	concept integral = std::is_integral_v<T>;

	template <typename T>
	concept signed_integral = std::is_signed_v<T>;

	template <typename T>
	concept unsigned_integral = std::is_unsigned_v<T>;

	template <typename T>
	concept floating_point = std::is_floating_point_v<T>;

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

	template <typename T>
	concept destructible = std::is_nothrow_destructible_v<T>;

	template <typename T, typename... Args >
	concept constructible_from =
		destructible<T> && std::is_constructible_v<T, Args...>;

	template <class From, class To>
	concept convertible_to =
		std::is_convertible_v<From, To> &&
		requires {
		static_cast<To>(std::declval<From>());
	};
	//
	//	template <typename LHS, typename RHS>
	//	concept assignable_from =
	//	  std::is_lvalue_reference_v<LHS> &&
	//	  std::common_reference_with<
	//		const std::remove_reference_t<LHS>&,
	//		const std::remove_reference_t<RHS>&> &&
	//	  requires(LHS lhs, RHS&& rhs) {
	//		{ lhs = std::forward<RHS>(rhs) } -> std::same_as<LHS>;
	//	  };
	//
	template <typename T>
	concept move_constructible = constructible_from<T, T> && convertible_to<T, T>;
	//
	template <typename T>
	concept copy_constructible =
		move_constructible<T> &&
		constructible_from<T, T&> && convertible_to<T&, T> &&
		constructible_from<T, T const&> && convertible_to<T const&, T> &&
		constructible_from<T, T const> && convertible_to<T const, T>;
	//
	//	template <typename T>
	//	concept movable =
	//	  std::is_object_v<T> &&
	//	  move_constructible<T> &&
	//	  assignable_from<T&, T> &&
	//	  swappable<T>;
	//
	//
	//	template <typename T>
	//	concept copyable =
	//		copy_constructible<T> &&
	//		movable<T> &&
	//		assignable_from<T&, T&> &&
	//		assignable_from<T&, const T&> &&
	//		assignable_from<T&, const T>;
	//
	//	template <typename T>
	//	concept default_initializable =
	//
	//
	//	template <typename T, typename U>
	//	concept __utl_weakly_equality_comparable_with =
	//		requires(std::remove_reference_t<T> const& t,
	//				 std::remove_reference_t<U> const& u) {
	//			{ t == u } -> convertible_to<bool>;
	//			{ t != u } -> convertible_to<bool>;
	//			{ u == t } -> convertible_to<bool>;
	//			{ u != t } -> convertible_to<bool>;
	//		};
	//
	//	template <typename T>
	//	concept equality_comparable = __utl_weakly_equality_comparable_with<T, T>;
	//
	//	template <typename T>
	//	concept semi_regular = copyable<T> && default_initializable<T>;

	//	template <typename T, typename U> /* too hard too implement */
	//	concept equality_comparable_with =
	//		equality_comparable<T> &&
	//		equality_comparable<U> &&
	//		common_reference_with<
	//			const std::remove_reference_t<T>&,
	//			const std::remove_reference_t<U>&> &&
	//		equality_comparable<
	//			common_reference_t<
	//				const std::remove_reference_t<T>&,
	//				const std::remove_reference_t<U>&>> &&
	//			__utl_weakly_equality_comparable_with<T, U>;

#endif // UTL_STDLIB_HAS_CONCEPTS
<<<<<<< HEAD
	
	template <typename T>
	concept arithmetic = std::is_arithmetic_v<T>;
	
=======

>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
	/// MARK: - Additional Concepts
	template <typename T>
	concept arithmetic = std::is_arithmetic_v<T>;

	template <typename T>
	concept boolean_testable = requires(T && t) { static_cast<bool>(t); };

	template <typename T, typename U, typename ... V>
	concept any_of = (same_as<T, U> || (same_as<T, V> || ...));
	
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





