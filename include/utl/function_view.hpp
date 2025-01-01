#pragma once

#include <functional>

#include "__base.hpp"
#include "__debug.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename Signature>
class function_view;

template <bool IsNoexcept, typename R, typename... Args>
class __function_view_impl {
    using __sig =
        std::conditional_t<IsNoexcept, R(Args...) noexcept, R(Args...)>;

public:
    __function_view_impl() = default;

    template <typename F>
    requires __all<std::is_invocable_r<R, F, Args...>,
                   __any_t<std::bool_constant<!IsNoexcept>,
                           std::is_nothrow_invocable_r<R, F, Args...>>,
                   std::negation<std::is_same<function_view<__sig>,
                                              std::remove_cvref_t<F>>>>
    constexpr __function_view_impl(F&& f) noexcept:
        __invoke_ptr(&__static_invoke<std::remove_reference_t<F>>),
        __state_ptr(
            const_cast<void*>(reinterpret_cast<void const volatile*>(&f))) {}

    constexpr R operator()(Args... args) const noexcept(IsNoexcept) {
        __utl_expect(__invoke_ptr);
        return __invoke_ptr(__state_ptr, std::forward<Args>(args)...);
    }

    explicit constexpr operator bool() const { return __invoke_ptr != nullptr; }

private:
    template <typename F>
    constexpr static R __static_invoke(void const* state, Args... args) {
        if constexpr (std::is_same_v<R, std::invoke_result_t<F, Args...>>) {
            if constexpr (std::is_function_v<F>) {
                return std::invoke((F*)state, std::forward<Args>(args)...);
            }
            else {
                return std::invoke(*(F*)state, std::forward<Args>(args)...);
            }
        }
        else {
            if constexpr (std::is_function_v<F>) {
                return static_cast<R>(
                    std::invoke((F*)state, std::forward<Args>(args)...));
            }
            else {
                return static_cast<R>(
                    std::invoke(*(F*)state, std::forward<Args>(args)...));
            }
        }
    }

    using __invoke_ptr_type = R (*)(void const*, Args...);
    __invoke_ptr_type __invoke_ptr = nullptr;
    void const* __state_ptr = nullptr;
};

template <typename R, typename... Args>
class function_view<R(Args...)>:
    public __function_view_impl<false, R, Args...> {
    using __base = __function_view_impl<false, R, Args...>;

public:
    using __base::__base;
    using __base::operator();
};

template <typename R, typename... Args>
class function_view<R(Args...) noexcept>:
    public __function_view_impl<true, R, Args...> {
    using __base = __function_view_impl<true, R, Args...>;

public:
    using __base::__base;
    using __base::operator();
};

} // namespace utl
