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
	concept copy_constructible = std::copy_constructible<T>;

	template <typename T, typename... Args >
	concept constructible_from = std::constructible_from<T, Args...>;

#else // UTL_STDLIB_HAS_CONCEPTS

	template <typename T>
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
	
	template <typename T>
	concept move_constructible = constructible_from<T, T> && convertible_to<T, T>;
	//
	template <typename T>
	concept copy_constructible =
		move_constructible<T> &&
		constructible_from<T, T&> && convertible_to<T&, T> &&
		constructible_from<T, T const&> && convertible_to<T const&, T> &&
		constructible_from<T, T const> && convertible_to<T const, T>;
	
#endif // UTL_STDLIB_HAS_CONCEPTS
	
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
	
	template <typename T>
	concept __utl_referenceable = std::is_object_v<std::remove_reference_t<T>>;
	
	template <typename T, typename U>
	concept weakly_equality_comparable_with =
		requires(const std::remove_reference_t<T>& t,
				 const std::remove_reference_t<U>& u) {
			{ t == u } -> boolean_testable;
			{ t != u } -> boolean_testable;
			{ u == t } -> boolean_testable;
			{ u != t } -> boolean_testable;
		};
	
	template <typename I>
	concept iterator =
		requires(I i) {
			{   *i } -> __utl_referenceable;
			{  ++i } -> std::same_as<I&>;
			{ *i++ } -> __utl_referenceable;
		} && std::copyable<I>;
	
	template <typename I, typename T>
	concept iterator_for = iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;
	
	template <typename S, typename I>
	concept sentinel_for = iterator<I> && weakly_equality_comparable_with<I, S>;
	
	template <typename I>
	concept input_iterator =
		iterator<I> &&
		std::equality_comparable<I> &&
		requires(I i) {
			typename std::incrementable_traits<I>::difference_type;
			typename std::indirectly_readable_traits<I>::value_type;
			typename std::common_reference_t<std::iter_reference_t<I>&&,
											 typename std::indirectly_readable_traits<I>::value_type&>;
			*i++;
			typename std::common_reference_t<decltype(*i++)&&,
											 typename std::indirectly_readable_traits<I>::value_type&>;
			requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;
		};
	
	template <typename I, typename T>
	concept input_iterator_for = input_iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;
	
	template <typename I>
	concept forward_iterator =
		input_iterator<I> && std::constructible_from<I> &&
		std::is_lvalue_reference_v<std::iter_reference_t<I>> &&
		std::same_as<
			std::remove_cvref_t<std::iter_reference_t<I>>,
			typename std::indirectly_readable_traits<I>::value_type> &&
		requires(I i) {
			{  i++ } -> std::convertible_to<const I&>;
			{ *i++ } -> std::same_as<std::iter_reference_t<I>>;
		};
	
	template <typename I, typename T>
	concept forward_iterator_for = forward_iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;
	
	template <typename I>
	concept bidirectional_iterator =
		forward_iterator<I> && requires(I i) {
			{  --i } -> std::same_as<I&>;
			{  i-- } -> std::convertible_to<const I&>;
			{ *i-- } -> std::same_as<std::iter_reference_t<I>>;
		};
	
	template <typename I, typename T>
	concept bidirectional_iterator_for = bidirectional_iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;
	
	template <typename I>
	concept random_access_iterator =
		bidirectional_iterator<I> && std::totally_ordered<I> &&
		requires(I i, typename std::incrementable_traits<I>::difference_type n) {
			{ i += n } -> std::same_as<I&>;
			{ i -= n } -> std::same_as<I&>;
			{ i +  n } -> std::same_as<I>;
			{ n +  i } -> std::same_as<I>;
			{ i -  n } -> std::same_as<I>;
			{ i -  i } -> std::same_as<decltype(n)>;
			{  i[n]  } -> std::convertible_to<std::iter_reference_t<I>>;
		};
	
	template <typename I, typename T>
	concept random_access_iterator_for = random_access_iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;

	template <typename R>
	concept range = requires(R&& r) {
		{ r.begin() } -> input_iterator;
		{ r.end() } -> sentinel_for<decltype(r.begin())>;
	};
	
}





