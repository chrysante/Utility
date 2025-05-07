#ifndef UTL_CONCEPTS_HPP_
#define UTL_CONCEPTS_HPP_

#include <concepts>
#include <utility>

#include <utl/__base.hpp>
#include <utl/type_traits.hpp>

namespace utl {

template <class F, class R, class... Args>
concept invocable_r = std::convertible_to<std::invoke_result_t<F, Args...>, R>;

template <class F>
concept any_invocable = is_any_invocable<F>::value;

template <typename I, typename T>
concept input_iterator_for =
    std::input_iterator<I> && std::convertible_to<std::iter_value_t<I>, T>;

} // namespace utl

#endif // UTL_CONCEPTS_HPP_
