#pragma once

#include <iterator>
#include <type_traits>

#include <utl/__base.hpp>

namespace utl {

constexpr bool is_constant_evaluated() noexcept {
#ifdef __cpp_lib_is_constant_evaluated
    return std::is_constant_evaluated();
#else
    return false;
#endif
}

template <typename... Traits>
using __all_t = std::conjunction<Traits...>;

template <typename... Traits>
using __any_t = std::disjunction<Traits...>;

template <typename... Traits>
inline constexpr bool __all = __all_t<Traits...>::value;

template <typename... Traits>
inline constexpr bool __any = __any_t<Traits...>::value;

namespace _private {
template <typename T, bool = std::is_class_v<T>>
struct _is_any_invocable /* bool = true */ {
    static_assert(!std::is_final_v<T>,
                  "Final classes cannot be used with this facility"
                  "Why do you even make your class final in the fist place?!");

private:
    struct Fallback {
        void operator()();
    };
    struct Derived: T, Fallback {};

    template <typename U, U>
    struct Check;

    template <typename>
    static std::true_type test(...);

    template <typename C>
    static std::false_type test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static constexpr bool value = decltype(test<Derived>(0))::value;
};

template <typename T>
struct _is_any_invocable<T, false> {
    static constexpr bool value = [] {
        if constexpr (std::is_reference_v<T> || std::is_const_v<T>) {
            return _is_any_invocable<std::remove_cvref_t<T>>::value;
        }
        else if constexpr (std::is_scalar_v<T>) {
            return std::is_function_v<std::remove_pointer_t<T>> ||
                   std::is_member_pointer_v<T>;
        }
    }();
};
} // namespace _private

template <typename T>
struct is_any_invocable:
    std::bool_constant<_private::_is_any_invocable<T>::value> {};

} // namespace utl

namespace utl {
namespace _private {
// from
// https://stackoverflow.com/questions/12032771/how-to-check-if-an-arbitrary-type-is-an-iterator
template <typename T>
struct is_iterator_impl {
    static char test(...);
    template <typename U,
              typename = typename std::iterator_traits<U>::difference_type,
              typename = typename std::iterator_traits<U>::pointer,
              typename = typename std::iterator_traits<U>::reference,
              typename = typename std::iterator_traits<U>::value_type,
              typename = typename std::iterator_traits<U>::iterator_category>
    static long test(U&&);
    constexpr static bool value =
        std::is_same<decltype(test(std::declval<T>())), long>::value;
};
} // namespace _private
template <typename T>
struct is_iterator:
    std::integral_constant<bool, _private::is_iterator_impl<T>::value> {};
} // namespace utl

namespace utl::_private {
template <typename T>
constexpr auto has_member_begin(int)
    -> decltype(std::declval<T>().begin(), bool{}) {
    return true;
}
template <typename T>
constexpr auto has_member_begin(...) {
    return false;
}

template <typename T>
constexpr auto has_free_begin(int)
    -> decltype(begin(std::declval<T>()), bool{}) {
    return true;
}
template <typename T>
constexpr auto has_free_begin(...) {
    return false;
}

template <typename T>
constexpr auto has_begin() {
    return has_member_begin<T>(0) || has_free_begin<T>(0);
}

template <typename T>
constexpr auto has_member_end(int)
    -> decltype(std::declval<T>().end(), bool{}) {
    return true;
}
template <typename T>
constexpr auto has_member_end(...) {
    return false;
}

template <typename T>
constexpr auto has_free_end(int) -> decltype(end(std::declval<T>()), bool{}) {
    return true;
}
template <typename T>
constexpr auto has_free_end(...) {
    return false;
}

template <typename T>
constexpr auto has_end() {
    return has_member_end<T>(0) || has_free_end<T>(0);
}

template <typename Range>
constexpr auto is_range() {
    if constexpr (has_begin<Range>() && has_end<Range>()) {
        using T = decltype(std::declval<Range>().begin());
        using U = decltype(std::declval<Range>().end());

        if constexpr (is_iterator<T>::value && is_iterator<U>::value) {
            using T_ = decltype(*std::declval<T>());
            using U_ = decltype(*std::declval<U>());
            return (
                bool)std::is_same<typename std::remove_const<T_>::type,
                                  typename std::remove_const<U_>::type>::value;
        }
    }
    return false;
}
} // namespace utl::_private

namespace utl {

template <typename T>
struct is_range: std::integral_constant<bool, _private::is_range<T>()> {};

template <typename R, bool = utl::is_range<R>::value>
struct range_traits;

template <typename R>
struct range_traits<R, true> {
private:
    static auto _begin() {
        if constexpr (_private::has_member_begin<R>(0)) {
            return std::declval<R>().begin();
        }
        else {
            static_assert(_private::has_free_begin<R>(0));
            return begin(std::declval<R>());
        }
    }

public:
    using iterator_type = decltype(_begin());
    using reference_type = decltype(*_begin());
};

} // namespace utl

namespace utl::_private {

template <typename U, typename... T>
constexpr bool contains_impl() {
    return (std::is_same<U, T>::value || ...);
}

template <typename T, typename... U>
constexpr bool is_unique_impl() {
    if constexpr (sizeof...(U) == 0)
        return true;
    else {
        return ((!std::is_same<T, U>::value) && ...) && is_unique_impl<U...>();
    }
}

template <std::size_t index, typename U, typename First, typename... Rest>
constexpr std::size_t first_index_of_impl() {
    static_assert(contains_impl<U, First, Rest...>());
    if constexpr (std::is_same<U, First>::value)
        return index;
    else
        return first_index_of_impl<index + 1, U, Rest...>();
}

} // namespace utl::_private

namespace utl {

template <typename T>
inline constexpr bool template_true = true;

template <typename T>
inline constexpr bool template_false = false;

template <typename T>
struct is_arithmetic: std::is_arithmetic<T> {};

template <typename T>
struct is_scalar: is_arithmetic<T> {};

namespace _private {
template <typename T, typename U>
auto _do_promote2(int)
    -> decltype(bool{} ? std::declval<T>() : std::declval<U>());

template <typename T>
T _do_promote();
template <typename T, typename U, typename... Rest>
auto _do_promote() {
    return _do_promote<std::remove_reference_t<decltype(_do_promote2<T, U>(0))>,
                       Rest...>();
}

template <typename T, typename U>
auto _can_promote2(int)
    -> decltype(bool{} ? std::declval<T>() : std::declval<U>(),
                std::true_type{});
template <typename T, typename U>
std::false_type _can_promote2(...);
template <typename T, typename U, typename... Rest>
constexpr bool _can_promote(...) {
    if constexpr (decltype(_can_promote2<T, U>(0))::value) {
        if constexpr (sizeof...(Rest) > 0) {
            return _can_promote<
                std::remove_reference_t<decltype(_do_promote2<T, U>(0))>,
                Rest...>(0);
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}
} // namespace _private

template <typename T, typename... U>
struct promote;

template <typename T, typename U>
requires(_private::_can_promote<T, U>(0))
struct promote<T, U> {
    using type =
        std::remove_reference_t<decltype(_private::_do_promote<T, U>())>;
};

template <typename T, typename U, typename... V>
requires(_private::_can_promote<T, U, V...>(0))
struct promote<T, U, V...> {
    using type = typename promote<typename promote<T, U>::type, V...>::type;
};

template <typename T>
struct underlying_type {
    using type = T;
};

template <typename... T>
struct to_floating_point {
    using type = typename promote<typename to_floating_point<T>::type...>::type;
};

template <typename T>
struct to_floating_point<T>;

template <>
struct to_floating_point<char> {
    using type = double;
};
template <>
struct to_floating_point<unsigned char> {
    using type = double;
};
template <>
struct to_floating_point<short> {
    using type = double;
};
template <>
struct to_floating_point<unsigned short> {
    using type = double;
};
template <>
struct to_floating_point<int> {
    using type = double;
};
template <>
struct to_floating_point<unsigned int> {
    using type = double;
};
template <>
struct to_floating_point<long> {
    using type = double;
};
template <>
struct to_floating_point<unsigned long> {
    using type = double;
};
template <>
struct to_floating_point<long long> {
    using type = double;
};
template <>
struct to_floating_point<unsigned long long> {
    using type = double;
};

template <>
struct to_floating_point<float> {
    using type = float;
};
template <>
struct to_floating_point<double> {
    using type = double;
};
template <>
struct to_floating_point<long double> {
    using type = long double;
};

template <typename T>
struct remove_cvref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

template <typename T>
struct is_relocatable:
    std::conjunction<std::is_move_constructible<T>, std::is_destructible<T>> {};

template <typename T>
struct is_trivially_relocatable:
    std::conjunction<std::is_trivially_move_constructible<T>,
                     std::is_trivially_destructible<T>> {};

template <typename T, typename U>
struct copy_cv {
    using __type0 =
        std::conditional_t<std::is_const<T>::value, std::add_const_t<U>, U>;
    using __type1 = std::conditional_t<std::is_volatile<T>::value,
                                       std::add_volatile_t<__type0>, __type0>;

    using type = __type1;
};

template <typename T, typename U>
using copy_cv_t = typename copy_cv<T, U>::type;

template <typename T, typename U>
struct copy_ref {
    using __type0 = std::conditional_t<std::is_lvalue_reference<T>::value,
                                       std::add_lvalue_reference_t<U>, U>;
    using __type1 =
        std::conditional_t<std::is_rvalue_reference<T>::value,
                           std::add_rvalue_reference_t<__type0>, __type0>;

    using type = __type1;
};

template <typename T, typename U>
using copy_ref_t = typename copy_ref<T, U>::type;

template <typename T, typename U>
struct copy_cvref {
    using __type0 = copy_cv_t<std::remove_reference_t<T>, U>;
    using __type1 = copy_ref_t<T, __type0>;

    using type = __type1;
};

template <typename T, typename U>
using copy_cvref_t = typename copy_cvref<T, U>::type;

} // namespace utl

namespace utl {

template <typename>
struct __strip_signature;

template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...)> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) volatile> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const volatile> {
    using type = R(Args...);
};

template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...)&> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const&> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) volatile&> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const volatile&> {
    using type = R(Args...);
};

template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) volatile noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const volatile noexcept> {
    using type = R(Args...);
};

template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) & noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const & noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) volatile & noexcept> {
    using type = R(Args...);
};
template <typename R, typename C, typename... Args>
struct __strip_signature<R (C::*)(Args...) const volatile & noexcept> {
    using type = R(Args...);
};

template <typename>
struct __func_traits_impl;

template <typename F, typename Sig = typename __strip_signature<
                          decltype(&std::remove_cvref_t<F>::operator())>::type>
struct function_traits: __func_traits_impl<Sig> {
    using __mtl_base = __func_traits_impl<Sig>;
    using __mtl_base::argument;
    using __mtl_base::argument_count;
    using typename __mtl_base::result_type;
};

template <typename R, typename... Args>
struct __func_traits_impl<R(Args...)> {
    using result_type = R;
    static constexpr std::size_t argument_count = sizeof...(Args);
    template <std::size_t N>
    requires(N < argument_count)
    using argument = std::tuple_element_t<N, std::tuple<Args...>>;
};

template <typename Base, typename... T>
struct have_common_base:
    std::bool_constant<(std::derived_from<T, Base> && ...)> {};

#if defined(__clang__)

#define UTL_HAS_COMPILE_TIME_BASE_OFFSET 1

#define _UTL_OFFSET_EXPR(BASE, DERIVED)                                        \
    reinterpret_cast<char*>(static_cast<BASE*>((DERIVED*)sizeof(DERIVED))) -   \
        reinterpret_cast<char const volatile*>((DERIVED*)sizeof(DERIVED))

template <typename Base, typename Derived>
inline constexpr std::size_t compile_time_base_offset =
    __builtin_constant_p(_UTL_OFFSET_EXPR(Base, Derived)) ?
        (_UTL_OFFSET_EXPR(Base, Derived)) :
        (_UTL_OFFSET_EXPR(Base, Derived));

#undef _UTL_OFFSET_EXPR

#else

#define UTL_HAS_COMPILE_TIME_BASE_OFFSET 0

#endif

} // namespace utl
