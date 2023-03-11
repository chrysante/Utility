#pragma once

#include <typeinfo>
#include <utility>

#include "__base.hpp"
#include "__debug.hpp"
#include "__farray.hpp"
#include "common.hpp"
#include "utility.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T>
struct __dyncast_type_to_enum_impl;

template <auto EnumValue>
struct __dyncast_enum_to_type_impl;

template <typename T>
struct __dyncast_is_abstract: std::false_type {};

template <typename T>
using __decay_all = std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>;

template <typename T>
decltype(__dyncast_type_to_enum_impl<__decay_all<T>>::value, std::true_type{}) __is_dc_dynamic_impl(int);

template <typename T>
std::false_type __is_dc_dynamic_impl(...);

template <typename T>
concept __dc_dynamic = decltype(__is_dc_dynamic_impl<T>(0))::value;

template <typename To, typename From>
concept __dyn_checkable = __dc_dynamic<From> && __dc_dynamic<To>; // TODO: Check that To and From a part of the same hierarchy.

template <typename To, typename From>
concept __dyn_castable = __dyn_checkable<To, From> && requires(From from) { static_cast<To>(from); };

template <typename T>
using __dc_enum_type = decltype(__dyncast_type_to_enum_impl<std::remove_cvref_t<T>>::value);

} // namespace utl

//---==========================================================================
//---=== Public interface =====================================================
//---==========================================================================

/// Mandatory customization point for the `dyncast` facilities. Every type in the inheritance hierarchy must be
/// uniquely mapped to an enum or integral value. Using an enum is recommended. Use this macro at file scope to
/// identify types in the hierarchy with a unique integral value.
#define UTL_DYNCAST_MAP(type, enum_value)                                                                                      \
    template <>                                                                                                                \
    struct ::utl::__dyncast_type_to_enum_impl<type>: std::integral_constant<decltype(enum_value), enum_value> {}; \
    template <>                                                                                                                \
    struct ::utl::__dyncast_enum_to_type_impl<enum_value>: std::type_identity<type> {};

/// Optional customization point for the `dyncast` facilities. Mark types as abstract. The `visit()` function will
/// not require its function argument to be invocable with abstract types, however it is the responsibility of the user
/// that no objects of abstract runtime type will exist.
#define UTL_DYNCAST_ABSTRACT(type)                                                                                             \
    template <>                                                                                                                \
    struct ::utl::__dyncast_is_abstract<type>: std::true_type {};

/// Opposite of abstract. This is just for symmetry with abstract, types are concrete by default.
#define UTL_DYNCAST_CONCRETE(type)                                                                                             \
    template <>                                                                                                                \
    struct ::utl::__dyncast_is_abstract<type>: std::false_type {};

namespace utl {

// clang-format off

/// Simple customization point for the `dyncast` facilities. If the types in the inheritance hierarchy expose their
/// runtime type identifiers by a `.type()` method, this customiziation point is not needed. Otherwise define a
/// function `dyncast_get_type()` with compatible signature for every type in the same namespace as the type. This can
/// of course be a (constrained) template.
/// Note that for a class hierarchy with root `NS::Base` defining a function `dyncast_get_type(Base const&)` in
/// namespace `NS` does not suffice in general: If a class derived from `Base` satisfies the requirements of the
/// generic `dyncast_get_type()` function defined here, it will be called instead. In practice this may not matter much,
/// but to be safe and generic prefer defining the overload like so:
/// `auto NS::dyncast_get_type(std::convertible_to<Base> auto const&);`
template <typename T>
auto dyncast_get_type(T const& t)
requires requires { { t.type() } -> std::convertible_to<__dc_enum_type<T>>; }
{
    return t.type();
}

// clang-format on

/// Optional second customization point. All fields below must be implemented. If a custom implementation for
/// `dyncast_traits<...>::type(...)` which does not invoke `dyncast_get_type()` is given, the first customization point
/// `dyncast_get_type()` is not used.
template <typename Enum>
struct dyncast_traits {
    static Enum type(auto const& t) { return dyncast_get_type(t); }
    static constexpr Enum first = Enum{ 0 };
    static constexpr Enum last  = Enum::_count;
};

/// Visit the object \p obj as its most derived type.
/// \param obj An object of type `T` which has support for the `dyncast` facilities.
/// \param fn A callable which can be invoked with any of `T`'s derived types. The possible return types of \p fn
///        when invoked with `T`'s derived types must have a common type determined by `std::common_type`.
/// \returns `std::invoke(fn, static_cast<MOST_DERIVED_TYPE>(obj))` where `MOST_DERIVED_TYPE` is the most derived type
///          of \p obj with the same cv-ref qualifications as \p obj.
template <typename T, typename F>
requires __dc_dynamic<T>
decltype(auto) visit(T&& obj, F&& fn);

/// \overload
template <typename T0, typename T1, typename F>
requires __dc_dynamic<T0> && __dc_dynamic<T1>
decltype(auto) visit(T0&& t0, T1&& t1, F&& fn);

/// \overload
template <typename T0, typename T1, typename T2, typename F>
requires __dc_dynamic<T0> && __dc_dynamic<T1> && __dc_dynamic<T2>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, F&& fn);

/// \overload
template <typename T0, typename T1, typename T2, typename T3, typename F>
requires __dc_dynamic<T0> && __dc_dynamic<T1> && __dc_dynamic<T2> && __dc_dynamic<T3>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, F&& fn);

/// \overload
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename F>
requires __dc_dynamic<T0> && __dc_dynamic<T1> && __dc_dynamic<T2> && __dc_dynamic<T3> && __dc_dynamic<T4>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, F&& fn);

/// \overload
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename F>
requires __dc_dynamic<T0> && __dc_dynamic<T1> && __dc_dynamic<T2> && __dc_dynamic<T3> && __dc_dynamic<T4> && __dc_dynamic<T5>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, F&& fn);

/// Check if \p from 's dymamic type is `To` or derived from `To`.
template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
isa(From* from);

/// Check if \p from 's dymamic type is `To` or derived from `To`.
template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
isa(From& from);

/// Downward cast of \p from in its class hierarchy.
/// \param from Pointer to an object of type `From`. Pointer must not be null.
/// \returns A pointer of derived type `To` or null if \p *from is not of type `To`.
template <typename To, typename From>
requires __dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To dyncast(From* from);

/// Downward cast of \p from in its class hierarchy.
/// \param from Reference to an object of type `From`.
/// \returns A Reference to the object of derived type `To`.
/// \throws `std::bad_cast` if \p from is not of type `To`.
template <typename To, typename From>
requires __dyn_castable<To, From&> && std::is_lvalue_reference_v<To>
constexpr To dyncast(From& from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Pointer to an object of type `From`. Pointer must not be null.
/// \returns A pointer of derived type `To`.
/// \warning Traps if \p *from is not of type `To`.
template <typename To, typename From>
requires __dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To cast(From* from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Reference to an object of type `From`.
/// \returns A reference of derived type `To`.
/// \warning Traps if \p from is not of type `To` .
template <typename To, typename From>
requires __dyn_castable<To, From&> && std::is_lvalue_reference_v<To>
constexpr To cast(From& from);

} // namespace utl

//---==========================================================================
//---=== Implementation =======================================================
//---==========================================================================

namespace utl {

template <typename T>
inline constexpr auto __dyncast_type_to_enum = __dyncast_type_to_enum_impl<T>::value;

template <auto EnumValue>
using __dyncast_enum_to_type = typename __dyncast_enum_to_type_impl<EnumValue>::type;

// clang-format off
template <typename Enum>
struct __dyncast_traits_impl: dyncast_traits<Enum> {
public:
    using dyncast_traits<Enum>::type;
    using dyncast_traits<Enum>::first;
    using dyncast_traits<Enum>::last;
    static constexpr size_t numElements = static_cast<size_t>(last) - static_cast<size_t>(first);

    template <Enum TestType>
    static bool is(auto const& t) {
        return isa_dispatch_array[static_cast<size_t>(TestType)][static_cast<size_t>(type(t))];
    }

private:
    template <Enum CurrentTestType, Enum TargetTestType, typename ActualType>
    requires std::is_convertible_v<ActualType*, __dyncast_enum_to_type<CurrentTestType>*>
    static constexpr bool is_exactly() { return CurrentTestType == TargetTestType; }

    template <Enum CurrentTestType, Enum TargetTestType, typename ActualType>
    static constexpr bool is_exactly() {
        return false;
    }

    template <Enum TargetTestType, typename ActualType, size_t... I>
    static constexpr bool walk_tree(std::index_sequence<I...>) {
        constexpr bool result = (... || is_exactly<Enum{ I }, TargetTestType, ActualType>());
        return result;
    }

    template <Enum TargetTestType, typename ActualType>
    static constexpr bool is_impl() {
        return walk_tree<TargetTestType, ActualType>(std::make_index_sequence<numElements>{});
    }

    /// Build a 2D boolean matrix at compile time indicating if a dynamic cast is possible for every origin-destination
    /// pair.
    static constexpr auto make_isa_dispatch_array() {
        return []<size_t... I>(std::index_sequence<I...>) {
            return std::array{
                []<Enum TestType, size_t... J>(std::index_sequence<J...>) {
                    return std::array{ is_impl<TestType, __dyncast_enum_to_type<Enum{ J }>>()... };
                }.template operator()<Enum{ I }>(std::make_index_sequence<numElements>{})...
            };
        }(std::make_index_sequence<numElements>{});
    }
    static constexpr auto isa_dispatch_array = make_isa_dispatch_array();
};
// clang-format on

/// This machinery is needed to make visiting subtrees of the entire inheritance hierarchy possible. Without it,
/// `std::invoke_result` would fail to compile on code paths that are never executed.

template <typename Derived, typename Base>
inline constexpr bool __dc_is_properly_derived_from_impl = requires (Base* base) { static_cast<Derived*>(base); } && !std::is_convertible_v<Base*, Derived*>;

template <typename Derived, typename Base>
inline constexpr bool __dc_is_properly_derived_from = __dc_is_properly_derived_from_impl<std::remove_cvref_t<Derived>, std::remove_cvref_t<Base>>;

/// Tag type to indicate that a function is not invocable for given parameters.
enum class __not_invocable;

/// Wrapper for `std::is_reference` to ignore `__not_invocable`.
template <typename T, bool DefCase>
struct __is_ref_wrapper: std::is_reference<T> {};

template <bool DefCase>
struct __is_ref_wrapper<__not_invocable, DefCase>: std::bool_constant<DefCase> {};

/// Wrapper that evaluates to `__not_invocable` if `F` is not invocable with `Args...`
template <typename F, typename... Args>
struct __dc_invoke_result {
    template <typename G, typename... T>
    static auto impl(int) -> decltype(std::invoke(std::declval<G>(), std::declval<T>()...));
    template <typename G, typename... T>
    static __not_invocable impl(...);
    
    using type = decltype(impl<F, Args...>(0));
};

template <typename F, typename... Args>
using __dc_invoke_result_t = typename __dc_invoke_result<F, Args...>::type;

/// Wrapper for `std::common_type` or `std::common_reference` to ignore `__not_invocable`.
template <bool IsRef, typename...>
struct __dc_common_type_wrapper_impl;

template <bool IsRef>
struct __dc_common_type_wrapper_impl<IsRef> {};

template <bool IsRef, typename A, typename B, typename... Rest>
struct __dc_common_type_wrapper_impl<IsRef, A, B, Rest...> {
    using trait_result = typename std::conditional_t<IsRef, std::common_reference<A, B>, std::common_type<A, B>>::type;
    using type = typename __dc_common_type_wrapper_impl<IsRef, trait_result, Rest...>::type;
};

template <bool IsRef, typename... Rest, typename B>
struct __dc_common_type_wrapper_impl<IsRef, __not_invocable, B, Rest...> {
    using type = typename __dc_common_type_wrapper_impl<IsRef, B, Rest...>::type;
};

template <bool IsRef, typename A, typename... Rest>
struct __dc_common_type_wrapper_impl<IsRef, A, __not_invocable, Rest...> {
    using type = typename __dc_common_type_wrapper_impl<IsRef, A, Rest...>::type;
};

template <bool IsRef, typename... Rest>
struct __dc_common_type_wrapper_impl<IsRef, __not_invocable, __not_invocable, Rest...> {
    using type = typename __dc_common_type_wrapper_impl<IsRef, Rest...>::type;
};

template <bool IsRef, typename A>
struct __dc_common_type_wrapper_impl<IsRef, A> {
    using type = A;
};

template <typename... T>
struct __dc_common_type_wrapper: __dc_common_type_wrapper_impl<__all<__is_ref_wrapper<T, true>...>, T...> {
    static_assert( __all<__is_ref_wrapper<T, true>...> ||
                  !__any<__is_ref_wrapper<T, false>...>,
                  "Either all or no cases must return references. "
                  "This rule is in place to prevent unindented copies or dangling references "
                  "when one case does not return a reference while another does, as we have "
                  "to agree on one common return type.");
};

template <typename Enums>
struct __dc_enum_sizes_impl;

template <typename Enums>
using __dc_enum_sizes = typename __dc_enum_sizes_impl<Enums>::type;

template <typename... E>
struct __dc_enum_sizes_impl<type_sequence<E...>> {
    using type = std::index_sequence<static_cast<std::size_t>(__dyncast_traits_impl<E>::last)...>;
};

template <typename Enums,
          typename GivenTypes,
          typename F,
          typename FArrayBase = __farray_base_impl<__dc_enum_sizes<Enums>>,
          typename DimI = std::make_index_sequence<Enums::size>,
          typename FlatI = std::make_index_sequence<FArrayBase::__flat_array_size>>
struct __dispatch_return_type;

template <typename... Enums, typename... GivenTypes, typename F, typename FArrayBase, std::size_t... DimI, size_t... FlatI>
struct __dispatch_return_type<type_sequence<Enums...>, type_sequence<GivenTypes...>, F, FArrayBase, std::index_sequence<DimI...>, std::index_sequence<FlatI...>> {
    static constexpr std::size_t __dim = sizeof...(Enums);
    
    template <std::size_t FlatIndex, std::size_t DimIndex>
    using type_at = __dyncast_enum_to_type<typename type_sequence<Enums...>::template at<DimIndex>{ FArrayBase::__expand_index(FlatIndex)[DimIndex] }>;

    template <std::size_t FlatIndex>
    static constexpr bool we_care = (... && __dc_is_properly_derived_from<type_at<FlatIndex, DimI>,
                                                                          typename type_sequence<GivenTypes...>::template at<DimI>>);
    
    template <std::size_t DimIndex, std::size_t FlatIndex>
    using qualified_concrete_type_at =
        utl::copy_cvref_t<typename type_sequence<GivenTypes...>::template at<DimIndex>,
                          __dyncast_enum_to_type<typename type_sequence<Enums...>::template at<DimIndex>{
                              FArrayBase::__expand_index(FlatIndex)[DimIndex] }>>;

    template <std::size_t FlatIndex>
    using invoke_result_wrapped = __dc_invoke_result<F, qualified_concrete_type_at<DimI, FlatIndex>...>;
    
    template <std::size_t FlatIndex>
    using invoke_result = typename std::conditional_t<we_care<FlatIndex>,
                                                      invoke_result_wrapped<FlatIndex>,
                                                      std::type_identity<__not_invocable>>::type;
    
    using type = typename __dc_common_type_wrapper<invoke_result<FlatI>...>::type;
};

template <typename T>
using __dc_traits = __dyncast_traits_impl<__dc_enum_type<T>>;

template <typename R, typename F, typename... T>
constexpr R __visit(F&& f, T&&... t) {
    auto constexpr getter = []<std::size_t TargetTypeIdx, typename U>(std::integral_constant<std::size_t, TargetTypeIdx>, U&& t) -> decltype(auto) {
        using enum_type = __dc_enum_type<U>;
        using target_type_raw = __dyncast_enum_to_type<enum_type{ TargetTypeIdx }>;
        using target_type = copy_cvref_t<U, target_type_raw>;
        constexpr bool staticallyCastable = requires { static_cast<target_type>(t); };
        static_assert(std::is_reference_v<target_type>, "To avoid copies when performing static_cast.");
        if constexpr (!staticallyCastable) {
            /// If we can't even `static_cast` there is no way this can be invoked.
            __utl_unreachable();
        }
        else if constexpr (std::is_convertible_v<U&&, target_type> && !std::is_same_v<U&&, target_type>) {
            /// If we can cast implicitly but destination type is not the same, this means we go up the hierarchy.
            /// Since we are dispatching on the most derived type, this path should be unreachable.
            __utl_unreachable();
        }
        else if constexpr (__dyncast_is_abstract<__decay_all<target_type>>::value) {
            __utl_unreachable();
        }
        else {
            return static_cast<target_type>(t);
        }
    };
    constexpr __farray<R,
                       F,
                       type_sequence<T...>,
                       std::integer_sequence<std::size_t, __dc_traits<T>::numElements...>> vis(getter);
    return vis[{ static_cast<std::size_t>(dyncast_get_type(t))... }](std::forward<F>(f), std::forward<T>(t)...);
}

template <typename F, typename... T>
constexpr decltype(auto) __visit(F&& f, T&&... t) {
    using return_type = typename __dispatch_return_type<type_sequence<__dc_enum_type<T>...>, type_sequence<T&&...>, F&&>::type;
    return __visit<return_type>(std::forward<F>(f), std::forward<T>(t)...);
}

} // namespace utl

template <typename T, typename F>
requires utl::__dc_dynamic<T>
decltype(auto) utl::visit(T&& t, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T>(t));
}

template <typename T0, typename T1, typename F>
requires utl::__dc_dynamic<T0> && utl::__dc_dynamic<T1>
decltype(auto) utl::visit(T0&& t0, T1&& t1, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T0>(t0), std::forward<T1>(t1));
}

template <typename T0, typename T1, typename T2, typename F>
requires utl::__dc_dynamic<T0> && utl::__dc_dynamic<T1> && utl::__dc_dynamic<T2>
decltype(auto) utl::visit(T0&& t0, T1&& t1, T2&& t2, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2));
}

template <typename T0, typename T1, typename T2, typename T3, typename F>
requires utl::__dc_dynamic<T0> && utl::__dc_dynamic<T1> && utl::__dc_dynamic<T2> && utl::__dc_dynamic<T3>
decltype(auto) utl::visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3));
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename F>
requires utl::__dc_dynamic<T0> && utl::__dc_dynamic<T1> && utl::__dc_dynamic<T2> && utl::__dc_dynamic<T3> && utl::__dc_dynamic<T4>
decltype(auto) utl::visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4));
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename F>
requires utl::__dc_dynamic<T0> && utl::__dc_dynamic<T1> && utl::__dc_dynamic<T2> && utl::__dc_dynamic<T3> && utl::__dc_dynamic<T4> && utl::__dc_dynamic<T5>
decltype(auto) utl::visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, F&& fn) {
    return __visit(std::forward<F>(fn), std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4), std::forward<T5>(t5));
}

template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
utl::isa(From* from) {
    using enum_type   = decltype(__dyncast_type_to_enum<std::remove_const_t<From>>);
    using to_stripped = std::remove_const_t<std::remove_pointer_t<To>>;
    return __dyncast_traits_impl<enum_type>::template is<__dyncast_type_to_enum<to_stripped>>(*from);
}

template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
utl::isa(From& from) {
    return isa<To>(&from);
}

template <typename To, typename From>
requires utl::__dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To utl::dyncast(From* from) {
    if (isa<__decay_all<To>>(from)) {
        return static_cast<To>(from);
    }
    return nullptr;
}

template <typename To, typename From>
requires utl::__dyn_castable<To, From&> && std::is_lvalue_reference_v<To>
constexpr To utl::dyncast(From& from) {
    using ToNoRef = std::remove_reference_t<To>;
    if (auto* result = dyncast<ToNoRef*>(&from)) {
        return *result;
    }
    throw std::bad_cast();
}

template <typename To, typename From>
requires utl::__dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To utl::cast(From* from) {
    __utl_assert(dyncast<To>(from) != nullptr, "Cast failed.");
    return static_cast<To>(from);
}

template <typename To, typename From>
requires utl::__dyn_castable<To, From&> && std::is_lvalue_reference_v<To>
constexpr To utl::cast(From& from) {
    using ToNoRef = std::remove_reference_t<To>;
    return *cast<ToNoRef*>(&from);
}
