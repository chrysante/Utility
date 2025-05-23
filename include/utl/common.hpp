#ifndef UTL_COMMON_HPP_
#define UTL_COMMON_HPP_

#include <concepts>
#include <memory>

#include <utl/__base.hpp>

/// MARK: UTL_CONCAT

#define _UTL_CONCAT_IMPL(A, B) A##B
#define UTL_CONCAT(A, B)       _UTL_CONCAT_IMPL(A, B)

/// MARK: UTL_UNIQUE_NAME

#define UTL_UNIQUE_NAME(name)        UTL_CONCAT(name, __LINE__)
#define UTL_ANONYMOUS_VARIABLE(name) UTL_UNIQUE_NAME(name)

/// MARK: UTL_VFUNC

#define _UTL_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,     \
                   _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, \
                   _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
                   _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
                   _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
                   _62, _63, N, ...)                                           \
    N

#ifdef _MSC_VER

#define _UTL_MSVC_CALL(X, Y)  X Y
#define _UTL_MSVC_EXPAND(...) __VA_ARGS__
#define _UTL_NARG_I(...)                                                       \
    _UTL_MSVC_EXPAND(_UTL_ARG_N(__VA_ARGS__, 63, 62, 61, 60, 59, 58, 57, 56,   \
                                55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45,    \
                                44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34,    \
                                33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23,    \
                                22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,    \
                                11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define _UTL_NARG(...) _UTL_MSVC_CALL(_UTL_NARG_I, (__VA_OPT__(, ) __VA_ARGS__))

#else

#define _UTL_NARG(...)   _UTL_NARG_I(__VA_ARGS__, _UTL_RSEQ_N())
#define _UTL_NARG_I(...) _UTL_ARG_N(__VA_ARGS__)
#define _UTL_RSEQ_N()                                                          \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,    \
        45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,    \
        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,    \
        11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#endif

#define _UTL_VFUNC_IMPL(name, n) UTL_CONCAT(name, n)
#define UTL_VFUNC(func, ...)                                                   \
    _UTL_VFUNC_IMPL(func, _UTL_NARG(__VA_ARGS__))(__VA_ARGS__)

/// MARK: UTL_FIRST, UTL_NTH

#define UTL_FIRST(f, ...) f

// MARK: UTL_FORWARD

#define UTL_FORWARD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

// MARK: UTL_MACRO_INVOKE

/// std::invoke equivalent for macros. Can be used to force evaluation of
/// arguments before passing to another macro.
#define UTL_INVOKE_MACRO(macro, ...) macro(__VA_ARGS__)

/// MARK: UTL_WITH_INDEX_SEQUENCE

#define _UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS(...)                             \
    UTL_VFUNC(_UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS, __VA_ARGS__)
#define _UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS2(name1, size1)                   \
<::std::size_t... name1>
#define _UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS4(name1, size1, name2, size2)     \
<::std::size_t... name1, ::std::size_t... name2>
#define _UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS6(name1, size1, name2, size2,     \
                                               name3, size3)                   \
<::std::size_t... name1, ::std::size_t... name2, ::std::size_t... name3>

#define _UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS(...)                             \
    UTL_VFUNC(_UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS, __VA_ARGS__)
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS2(name1, size1)                   \
    (::std::index_sequence<name1...>)
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS4(name1, size1, name2, size2)     \
    (::std::index_sequence<name1...>, ::std::index_sequence<name2...>)
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS6(name1, size1, name2, size2,     \
                                               name3, size3)                   \
    (::std::index_sequence<name1...>, ::std::index_sequence<name2...>,         \
     ::std::index_sequence<name3...>)

#define _UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE(...)                             \
    UTL_VFUNC(_UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE, __VA_ARGS__)
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE2(name1, size1)                   \
    (::std::make_index_sequence<size1>{})
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE4(name1, size1, name2, size2)     \
    (::utl::make_index_sequence<size1>{}, ::std::make_index_sequence<size2>{})
#define _UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE6(name1, size1, name2, size2,     \
                                               name3, size3)                   \
    (::std::make_index_sequence<size1>{}, ::std::make_index_sequence<size2>{}, \
     ::std::make_index_sequence<size3>{})

#define UTL_WITH_INDEX_SEQUENCE(params, ...)                                   \
    [&] _UTL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS params                           \
        _UTL_INDEX_SEQ_HELPER_FUNCTION_PARAMS params                           \
        -> decltype(auto) __VA_ARGS__ _UTL_INDEX_SEQ_HELPER_FUNCTION_INVOKE    \
            params

/// MARK: Enum Operators

#if UTL_CPP
#define _UTL_NSSTD std
#elif UTL_METAL
#define _UTL_NSSTD metal
#endif

#define _UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, RESULT_TYPE, OP)                 \
    inline constexpr RESULT_TYPE operator OP(TYPE a) {                         \
        return static_cast<RESULT_TYPE>(                                       \
            OP static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(  \
                a));                                                           \
    }
#define _UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, OP)                             \
    inline constexpr TYPE operator OP(TYPE a, TYPE b) {                        \
        return static_cast<TYPE>(                                              \
            static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(a)   \
                OP static_cast<                                                \
                    typename _UTL_NSSTD::underlying_type<TYPE>::type>(b));     \
    }                                                                          \
    inline constexpr TYPE                                                      \
    operator OP(typename _UTL_NSSTD::underlying_type<TYPE>::type a, TYPE b) {  \
        return static_cast<TYPE>(                                              \
            a OP static_cast<                                                  \
                typename _UTL_NSSTD::underlying_type<TYPE>::type>(b));         \
    }                                                                          \
    inline constexpr TYPE                                                      \
    operator OP(TYPE a, typename _UTL_NSSTD::underlying_type<TYPE>::type b) {  \
        return static_cast<TYPE>(                                              \
            static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(a)   \
                OP b);                                                         \
    }

#if UTL_CPP
#define _UTL_ENUM_ASSIGNMENT(TYPE, OP)                                         \
    inline constexpr TYPE& operator OP##=(TYPE & a, TYPE b) {                  \
        return a = a OP b;                                                     \
    }
#elif UTL_METAL
#define _UTL_ENUM_ASSIGNMENT(TYPE, OP) // Not supported in Metal
#endif

/// Define bitwise arithmetic operators for \p TYPE
///
/// Defines
///     `operator&`
///     `operator&=`
///     `operator|`
///     `operator|=`
///     `operator^`
///     `operator^=`
///     `operator~`
///     `operator!`
///
/// Also defines a function `bool test(TYPE)` to convert \p TYPE to `bool`.
#define UTL_BITFIELD_OPERATORS(TYPE)                                           \
    _UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, &)                                  \
    _UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, |)                                  \
    _UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, ^)                                  \
    _UTL_ENUM_ASSIGNMENT(TYPE, &)                                              \
    _UTL_ENUM_ASSIGNMENT(TYPE, |)                                              \
    _UTL_ENUM_ASSIGNMENT(TYPE, ^)                                              \
    _UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, TYPE, ~)                             \
    _UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, bool, !)                             \
    constexpr bool test(TYPE value) {                                          \
        return !!value;                                                        \
    }

// For compatibility
#define UTL_ENUM_OPERATORS(TYPE) UTL_BITFIELD_OPERATORS(TYPE)

#if UTL_CPP // Guard here because general purpose header may be included in
            // shader source

#include <array>
#include <cstdint>
#include <ios>
#include <type_traits>
#include <utility>

namespace utl {

#if (defined(__GNUC__) || defined(__clang__)) // && ...
#define UTL_128_BIT_ARITHMETIC
#endif

#ifdef UTL_128_BIT_ARITHMETIC
using uint128_t = __uint128_t;
using int128_t = __int128_t;
#endif // UTL_128_BIT_ARITHMETIC

/// MARK: Tags
struct __private_tag {};
struct no_init_t {
} constexpr no_init{};

template <typename T>
struct tag {
    using type = T;
};

/// MARK: to_underlying
template <typename Enum>
requires(std::is_enum_v<Enum>)
constexpr std::underlying_type_t<Enum> to_underlying(Enum t) {
    return static_cast<std::underlying_type_t<Enum>>(t);
}

/// MARK: constexpr_strlen
constexpr std::size_t constexpr_strlen(char const* str) {
    if (!str)
        return 0;
    std::size_t result = 0;
    while (*str != '\0') {
        ++str;
        ++result;
    }
    return result;
}

/// MARK: UTL_CTPRINT
template <auto...>
struct ctprint; /* undefined so instanciating it will give a compiler error like
                   'Implicit instanciation of utl::ctprint<VALUES>' */
#define UTL_CTPRINT(...)                                                       \
    ::utl::ctprint<__VA_ARGS__> UTL_ANONYMOUS_VARIABLE(_UTL_CTPRINT)

/// MARK: UTL_STATIC_INIT
#ifdef __GNUC__
#define UTL_STATIC_INIT                                                        \
    __attribute__((constructor)) static void UTL_ANONYMOUS_VARIABLE(           \
        __utl_static_init_)()
#else

template <typename F>
struct __utl_static_init {
    __utl_static_init(F&& f) { f(); }
};
#define UTL_STATIC_INIT                                                        \
    utl::__utl_static_init UTL_ANONYMOUS_VARIABLE(__utl_static_init_) = []
#endif

/// MARK: UTL_STORE_STREAM_STATE
struct __utl_ios_state_store {
    explicit __utl_ios_state_store(std::ios_base& stream):
        stream(stream), flags(stream.flags()) {}
    ~__utl_ios_state_store() { stream.flags(flags); }
    std::ios_base& stream;
    std::ios_base::fmtflags flags;
};

#define UTL_STORE_STREAM_STATE(stream)                                         \
    ::utl::__utl_ios_state_store UTL_ANONYMOUS_VARIABLE(                       \
        __utl_stream_state_store)(stream)

/// `get_container`
/// (Legal) access to the container of STL container adapters
template <typename ContainerAdapter>
decltype(auto) __utl_get_container_impl(auto&& a) {
    static_assert(std::is_lvalue_reference_v<decltype(a)>);

    using __container_type = typename ContainerAdapter::container_type;

    struct __hack: ContainerAdapter {
        static __container_type& get(ContainerAdapter& a) {
            return a.*&__hack::c;
        }
        static __container_type const& get(ContainerAdapter const& a) {
            return a.*&__hack::c;
        }
    };
    return __hack::get(a);
}

template <class ContainerAdapter>
typename ContainerAdapter::container_type& get_container(ContainerAdapter& a) {
    return __utl_get_container_impl<ContainerAdapter>(a);
}

template <class ContainerAdapter>
typename ContainerAdapter::container_type const&
get_container(ContainerAdapter const& a) {
    return __utl_get_container_impl<ContainerAdapter>(a);
}

template <typename T, typename Allocator, typename... Args>
concept __alloc_constructible_1 =
    std::constructible_from<T, std::allocator_arg_t, Allocator, Args...>;

template <typename T, typename Allocator, typename... Args>
concept __alloc_constructible_2 =
    std::constructible_from<T, Args..., Allocator>;

template <typename T, typename Allocator, typename... Args>
concept __alloc_constructible_3 = std::constructible_from<T, Args...>;

template <typename T, typename Allocator, typename... Args>
concept __alloc_constructible =
    __alloc_constructible_1<T, Allocator, Args...> ||
    __alloc_constructible_2<T, Allocator, Args...> ||
    __alloc_constructible_3<T, Allocator, Args...>;

} // namespace utl

#endif // UTL_CPP

#endif // UTL_COMMON_HPP_
