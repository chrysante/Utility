#pragma once

#include <exception>

#include <utl/__base.hpp>
#include <utl/common.hpp>
#include <utl/concepts.hpp>

namespace utl {

enum class __scope_guard_type { any, success, failure };

template <bool Armed>
struct __scope_guard_base1 {};
template <>
struct __scope_guard_base1<true> {
    bool __armed = true;
};
template <bool Armed, __scope_guard_type Type>
struct __scope_guard_base2: __scope_guard_base1<Armed> {
    int __uncaught_exceptions = std::uncaught_exceptions();
};
template <bool Armed>
struct __scope_guard_base2<Armed, __scope_guard_type::any>:
    __scope_guard_base1<Armed> {};

template <std::invocable F, bool Armed, __scope_guard_type Type>
class __basic_scope_guard: __scope_guard_base2<Armed, Type> {
    F __f;

public:
    constexpr __basic_scope_guard(F const& f) noexcept(
        std::is_nothrow_copy_constructible_v<F>):
        __f(f) {}
    constexpr __basic_scope_guard(F&& f) noexcept(
        std::is_nothrow_move_constructible_v<F>):
        __f(std::move(f)) {}

    constexpr ~__basic_scope_guard() noexcept(Type ==
                                              __scope_guard_type::failure) {
        if constexpr (Armed) {
            if (!this->__armed)
                return;
        }
        if constexpr (Type == __scope_guard_type::success) {
            if (this->__uncaught_exceptions <
                std::uncaught_exceptions()) /// Failure
                return;
        }
        else if constexpr (Type == __scope_guard_type::failure) {
            if (this->__uncaught_exceptions ==
                std::uncaught_exceptions()) /// Success
                return;
        }
        __f();
    }

    constexpr void arm() noexcept
    requires(Armed == true)
    {
        this->__armed = true;
    }
    constexpr void disarm() noexcept
    requires(Armed == true)
    {
        this->__armed = false;
    }
    constexpr void execute() noexcept
    requires(Armed == true)
    {
        __f();
        this->__armed = false;
    }
};

#define _UTL_SCOPE_GUARD_SPECIALIZATION(Name, Armed, Type)                     \
    template <std::invocable F>                                                \
    class Name:                                                                \
        public __basic_scope_guard<F, Armed, __scope_guard_type::Type> {       \
        using base = __basic_scope_guard<F, Armed, __scope_guard_type::Type>;  \
                                                                               \
    public:                                                                    \
        using base::base;                                                      \
    };                                                                         \
    template <typename F>                                                      \
    Name(F)->Name<F>

_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard, false, any);
_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard_success, false, success);
_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard_failure, false, failure);
_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard, true, any);
_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard_success, true, success);
_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard_failure, true, failure);

#undef _UTL_SCOPE_GUARD_SPECIALIZATION

} // namespace utl

#ifdef UTL_DEFER_MACROS

#define utl_defer                                                              \
    ::utl::scope_guard UTL_ANONYMOUS_VARIABLE(                                 \
        __utl_scope_guard_state_) = [&]() -> void
#define utl_defer_failure                                                      \
    ::utl::scope_guard_failure UTL_ANONYMOUS_VARIABLE(                         \
        __utl_scope_guard_state_) = [&]() noexcept -> void
#define utl_defer_success                                                      \
    ::utl::scope_guard_success UTL_ANONYMOUS_VARIABLE(                         \
        __utl_scope_guard_state_) = [&]() -> void

#endif // UTL_DEFER_MACROS
