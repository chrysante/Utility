#pragma once

#include <concepts>
#include <utility>

#include "__base.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

/// MARK: - Additional Concepts
// clang-format off
template <typename T>
concept __boolean_testable = std::convertible_to<T, bool> && requires(T&& t) {
    { !std::forward<T>(t) } -> std::convertible_to<bool>;
};
// clang-format on

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T, typename U, typename... V>
concept any_of = (std::same_as<T, U> || (std::same_as<T, V> || ...));

template <class F, class R, class... Args>
concept invocable_r = std::convertible_to<std::invoke_result_t<F, Args...>, R>;

template <class R, class F, class... Args>
concept regular_invocable_r = invocable_r<R, F, Args...>;

template <class F>
concept any_invocable = is_any_invocable<F>::value;

template <typename T>
concept __utl_referenceable = std::is_object_v<std::remove_reference_t<T>>;

template <typename I, typename T>
concept __iter_for = std::convertible_to<std::iter_value_t<I>, T>;

// clang-format off
template <typename T, typename U>
concept __weakly_equality_comparable_with = requires(std::remove_reference_t<T> const& t,
                                                     std::remove_reference_t<U> const& u) {
    { t == u } -> __boolean_testable;
    { t != u } -> __boolean_testable;
    { u == t } -> __boolean_testable;
    { u != t } -> __boolean_testable;
};

template <typename I>
concept iterator = requires(I i) {
    { *i } -> __utl_referenceable;
    { ++i } -> std::same_as<I&>;
    { *i++ } -> __utl_referenceable;
    /// `utl::transform_iterator` can't satisfy `std::copyable` concept because lambdas are not copy assignable.
    /// `std::copy_constructible` should be enough for most cases though.
} && /* std::copyable<I> */ std::copy_constructible<I>;
// clang-format on

template <typename I, typename T>
concept iterator_for = iterator<I> && __iter_for<I, T>;

template <typename S, typename I>
concept sentinel_for = iterator<I> && __weakly_equality_comparable_with<I, S>;

template <typename I>
concept input_iterator = iterator<I> && std::equality_comparable<I> && requires(I i) {
    typename std::incrementable_traits<I>::difference_type;
    requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;
    typename std::indirectly_readable_traits<I>::value_type;
    typename std::common_reference_t<std::iter_reference_t<I>&&,
                                     typename std::indirectly_readable_traits<I>::value_type&>;
    *i++;
    typename std::common_reference_t<decltype(*i++)&&, typename std::indirectly_readable_traits<I>::value_type&>;
};

template <typename I, typename T>
concept input_iterator_for = input_iterator<I> && __iter_for<I, T>;

template <typename I>
concept output_iterator = iterator<I> && std::equality_comparable<I> && requires(I i, std::iter_value_t<I> value) {
    typename std::incrementable_traits<I>::difference_type;
    requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;
    *i++ = value;
};

template <typename I, typename T>
concept output_iterator_for = output_iterator<I> && __iter_for<I, T>;

template <typename I>
concept inout_iterator = input_iterator<I> && output_iterator<I>;

template <typename I, typename T>
concept inout_iterator_for = inout_iterator<I> && __iter_for<I, T>;

// clang-format off
template <typename I>
concept forward_iterator =
    input_iterator<I> &&
/// These are disabled to allow non referencing iterators. Don't really understand why these should be required in the first place.
//    std::constructible_from<I> &&
//    std::is_lvalue_reference_v<std::iter_reference_t<I>> &&
//    std::same_as<std::remove_cvref_t<std::iter_reference_t<I>>, typename std::indirectly_readable_traits<I>::value_type> &&
    requires(I i) {
        { i++ } -> std::convertible_to<const I&>;
        { *i++ } -> std::same_as<std::iter_reference_t<I>>;
    };
// clang-format on

template <typename I, typename T>
concept forward_iterator_for = forward_iterator<I> && __iter_for<I, T>;

// clang-format off
template <typename I>
concept bidirectional_iterator = forward_iterator<I> && requires(I i) {
    { --i } -> std::same_as<I&>;
    { i-- } -> std::convertible_to<const I&>;
    { *i-- } -> std::same_as<std::iter_reference_t<I>>;
};
// clang-format on

template <typename I, typename T>
concept bidirectional_iterator_for = bidirectional_iterator<I> && __iter_for<I, T>;

// clang-format off
template <typename I>
concept random_access_iterator = bidirectional_iterator<I> && std::totally_ordered<I> &&
    requires(I i, typename std::incrementable_traits<I>::difference_type n) {
    { i += n } -> std::same_as<I&>;
    { i -= n } -> std::same_as<I&>;
    { i + n } -> std::same_as<I>;
    { n + i } -> std::same_as<I>;
    { i - n } -> std::same_as<I>;
    { i - i } -> std::same_as<decltype(n)>;
    { i[n] } -> std::convertible_to<std::iter_reference_t<I>>;
};
// clang-format on

template <typename I, typename T>
concept random_access_iterator_for = random_access_iterator<I> && __iter_for<I, T>;

decltype(auto) __utl_begin(auto& x) requires requires { begin(x); } || requires { std::begin(x); } { using std::begin; return begin(x); }
decltype(auto) __utl_end(auto& x) requires requires { end(x); } || requires { std::end(x); } { using std::end; return end(x); }

// clang-format off
template <typename R>
concept range = requires(R&& r) {
    { __utl_begin(r) } -> iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept range_for = requires(R&& r) {
    { __utl_begin(r) } -> iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept input_range = requires(R&& r) {
    { __utl_begin(r) } -> input_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept input_range_for = requires(R&& r) {
    { __utl_begin(r) } -> input_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept output_range = requires(R&& r) {
    { __utl_begin(r) } -> output_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept output_range_for = requires(R&& r) {
    { __utl_begin(r) } -> output_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept inout_range = requires(R&& r) {
    { __utl_begin(r) } -> inout_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept inout_range_for = requires(R&& r) {
    { __utl_begin(r) } -> inout_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept forward_range = requires(R&& r) {
    { __utl_begin(r) } -> forward_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept forward_range_for = requires(R&& r) {
    { __utl_begin(r) } -> forward_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept bidirectional_range = requires(R&& r) {
    { __utl_begin(r) } -> bidirectional_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept bidirectional_range_for = requires(R&& r) {
    { __utl_begin(r) } -> bidirectional_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R>
concept random_access_range = requires(R&& r) {
    { __utl_begin(r) } -> random_access_iterator;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};

template <typename R, typename T>
concept random_access_range_for = requires(R&& r) {
    { __utl_begin(r) } -> random_access_iterator_for<T>;
    { __utl_end(r) } -> sentinel_for<decltype(__utl_begin(r))>;
};
// clang-format on



} // namespace utl
