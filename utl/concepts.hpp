#pragma once

#include <utility>
#include <concepts>

#include "__base.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

	/// MARK: - Additional Concepts
	template <typename T>
	concept __boolean_testable = std::convertible_to<T, bool> && requires(T&& t) {
		{ !std::forward<T>(t) } -> std::convertible_to<bool>;
	};
	
	template <typename T>
	concept arithmetic = std::is_arithmetic_v<T>;

	template <typename T>
	concept boolean_testable = requires(T && t) { static_cast<bool>(t); };

	template <typename T, typename U, typename ... V>
	concept any_of = (std::same_as<T, U> || (std::same_as<T, V> || ...));
	
	template <class F, class R, class... Args>
	concept invocable_r = std::convertible_to<std::invoke_result_t<F, Args...>, R>;
	
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
			{ i[n]   } -> std::convertible_to<std::iter_reference_t<I>>;
		};
	
	template <typename I, typename T>
	concept random_access_iterator_for = random_access_iterator<I> && std::convertible_to<typename std::iterator_traits<I>::value_type, T>;

	template <typename R>
	concept range = requires(R&& r) {
		{ r.begin() } -> input_iterator;
		{ r.end() } -> sentinel_for<decltype(r.begin())>;
	};
	
}





