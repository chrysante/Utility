#ifndef UTL_OVERLOAD_HPP_
#define UTL_OVERLOAD_HPP_

#include <type_traits>

namespace utl {

namespace impl {

/// The `toFunction` functions forward class types as is and wrap function
/// pointers in lambdas so it becomes possible to derive from them. Function
/// object case
template <typename F>
requires std::is_class_v<std::remove_reference_t<F>>
constexpr F&& toFunction(F&& f) {
    return (F&&)f;
}

/// Function pointer case
template <typename R, typename... Args>
constexpr auto toFunction(R (*fptr)(Args...)) {
    return [fptr](Args... args) { return fptr((Args&&)args...); };
}

/// Member function pointer case
template <typename R, typename T, typename... Args>
constexpr auto toFunction(R (T::*fptr)(Args...)) {
    return [fptr](T& object, Args... args) {
        return (object.*fptr)((Args&&)args...);
    };
}

/// Return type of `toFunction`
template <typename F>
using ToFunctionT =
    std::remove_reference_t<decltype(toFunction(std::declval<F>()))>;

} // namespace impl

/// Helper class to create overloaded function object on the fly from multiple
/// lambda expressions or other function objects or (member) function pointers
///
/// Can be used like this:
///
///     auto f = overload{
///         [](int) { /* Do something for ints */ },
///         [](float) { /* Do something for floats */ },
///         [](MyClass const&) { /* Do something for MyClass */ },
///     };
///
template <typename... F>
struct overload: impl::ToFunctionT<F>... {
    template <typename... G>
    constexpr overload(G&&... g):
        impl::ToFunctionT<F>(impl::toFunction((G&&)g))... {}
    using impl::ToFunctionT<F>::operator()...;
};

template <typename... F>
overload(F...) -> overload<F...>;

} // namespace utl

#endif // UTL_OVERLOAD_HPP_
