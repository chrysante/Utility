#pragma once

#include <type_traits>
#include <typeinfo>
#include <utility>

#include "__base.hpp"
#include "__debug.hpp"
#include "utility.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T>
struct __dyncast_type_to_enum_impl;

template <auto EnumValue>
struct __dyncast_enum_to_type_impl;

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

/// Mandatory customization point for the \p dyncast facilities. Every object in the inheritance hierarchy must be
/// uniquely mapped to an enum or integral value. Using an enum is recommended. Use this macro at file scope to
/// identify types in the hierarchy with a unique integral value.
#define UTL_DYNCAST_MAP(type, enum_value)                                                                                      \
    template <>                                                                                                                \
    struct ::utl::__dyncast_type_to_enum_impl<type>: std::integral_constant<decltype(enum_value), enum_value> {}; \
    template <>                                                                                                                \
    struct ::utl::__dyncast_enum_to_type_impl<enum_value>: std::type_identity<type> {}

namespace utl {

// clang-format off

/// Simple customization point for the \p dyncast facilities. If the types in the inheritance hierarchy expose their
/// runtime type identifiers by a \p .type() method, this customiziation point is not needed. Otherwise define a
/// function \p dyncast_get_type() with compatible signature for every type in the same namespace as the type. This can
/// of course be a (constrained) template.
/// Note that for a class hierarchy with root \p NS::Base defining a function \p dyncast_get_type(Base \p const&) in
/// namespace \p NS does not suffice in general: If a class derived from \p Base satisfies the requirements of the
/// generic \p dyncast_get_type() function defined here, it will be called instead. In practice this may not matter much,
/// but to be safe and generic prefer defining the overload like so:
/// \code auto NS::dyncast_get_type(std::convertible_to<Base> auto const&); \endcode
template <typename T>
auto dyncast_get_type(T const& t)
requires requires { { t.type() } -> std::convertible_to<__dc_enum_type<T>>; }
{
    return t.type();
}

// clang-format on

/// Optional second customization point. All fields below must be implemented. If a custom implementation for
/// \p dyncast_traits<...>::type(...) which does not invoke \p dyncast_get_type() is given, the first customization point
/// \p dyncast_get_type() is not used.
template <typename Enum>
struct dyncast_traits {
    static Enum type(auto const& t) { return dyncast_get_type(t); }
    static constexpr Enum first = Enum{ 0 };
    static constexpr Enum last  = Enum::_count;
};

/// Visit the object \p obj as its most derived type.
/// \param obj An object of type \p T which has support for the \p dyncast facilities.
/// \param fn A callable which can be invoked with any of \p T 's derived types. The possible return types of \p fn
///        when invoked with \p T 's derived types must have a common type determined by \p std::common_type.
/// \returns \p std::invoke(fn,static_cast<MOST_DERIVED_TYPE>(obj)) where \p MOST_DERIVED_TYPE is the most derived type
///          of \p obj with the same cv-ref qualifications as \p obj.
template <typename T, typename F>
requires __dc_dynamic<T> decltype(auto)
visit(T&& obj, F&& fn);

/// Check if \p from 's dymamic type is \p To or derived from \p To.
template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
isa(From* from);

/// Check if \p from 's dymamic type is \p To or derived from \p To.
template <typename To, typename From>
requires utl::__dyn_checkable<To, From> bool
isa(From& from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Pointer to an object of type \p From. Pointer must not be null.
/// \returns A pointer of derived type \p To or null if \p *from is not of type \p To.
template <typename To, typename From>
requires __dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To dyncast(From* from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Reference to an object of type \p From.
/// \returns A Reference to the object of derived type \p T.o
/// \throws \p std::bad_cast if \p from is not of type \p To.
template <typename To, typename From>
requires __dyn_castable<To, From&> && std::is_lvalue_reference_v<To>
constexpr To dyncast(From& from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Pointer to an object of type \p From. Pointer must not be null.
/// \returns A pointer of derived type \p To.
/// \warning Traps if \p *from is not of type \p To.
template <typename To, typename From>
requires __dyn_castable<To, From*> && std::is_pointer_v<To>
constexpr To cast(From* from);

/// Downwards cast of \p from in its class hierarchy.
/// \param from Reference to an object of type \p From .
/// \returns A reference of derived type \p To .
/// \warning Traps if \p from is not of type \p To .
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
using DyncastEnumToType = typename __dyncast_enum_to_type_impl<EnumValue>::type;

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
    requires std::is_convertible_v<ActualType*, DyncastEnumToType<CurrentTestType>*>
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
                    return std::array{ is_impl<TestType, DyncastEnumToType<Enum{ J }>>()... };
                }.template operator()<Enum{ I }>(std::make_index_sequence<numElements>{})...
            };
        }(std::make_index_sequence<numElements>{});
    }
    static constexpr auto isa_dispatch_array = make_isa_dispatch_array();
};
// clang-format on

/// This machinery is needed to make visiting subtrees of the entire inheritance hierarchy possible. Without it,
/// \p std::invoke_result would fail on code paths that are never executed.

/// Tag type to indicate that a function is not invocable for given parameters.
enum class __not_invocable;

/// Wrapper that evaluates to \p __not_invocable if \p F is not invocable with \p Args...
template <typename F, typename... Args>
using __dc_invoke_result = typename std::conditional_t<std::is_invocable_v<F, Args...>,
                                                       std::invoke_result<F, Args...>,
                                                       std::type_identity<__not_invocable>>::type;

/// Wrapper for \p std::common_type to ignore \p __not_invocable .
template <typename...>
struct __dc_common_type_wrapper;

template <typename A, typename B, typename... Rest>
struct __dc_common_type_wrapper<A, B, Rest...> {
    using type = typename __dc_common_type_wrapper<std::common_type_t<A, B>, Rest...>::type;
};

template <typename... Rest, typename B>
struct __dc_common_type_wrapper<__not_invocable, B, Rest...> {
    using type = typename __dc_common_type_wrapper<B, Rest...>::type;
};

template <typename A, typename... Rest>
struct __dc_common_type_wrapper<A, __not_invocable, Rest...> {
    using type = typename __dc_common_type_wrapper<A, Rest...>::type;
};

template <typename... Rest>
struct __dc_common_type_wrapper<__not_invocable, __not_invocable, Rest...> {
    using type = typename __dc_common_type_wrapper<Rest...>::type;
};

template <typename A>
struct __dc_common_type_wrapper<A> {
    using type = A;
};

template <typename Enum,
          typename GivenType,
          typename F,
          typename I = std::make_index_sequence<__dyncast_traits_impl<Enum>::numElements>>
struct __dispatch_return_type;

template <typename Enum, typename GivenType, typename F, size_t... I>
struct __dispatch_return_type<Enum, GivenType, F, std::index_sequence<I...>> {
    using type = typename __dc_common_type_wrapper<
        __dc_invoke_result<F, utl::copy_cvref_t<GivenType, DyncastEnumToType<Enum{ I }>>>...>::type;
};

} // namespace utl

// clang-format off

template <typename T, typename F>
requires utl::__dc_dynamic<T>
decltype(auto) utl::visit(T&& obj, F&& fn) {
    using enum_type = __dc_enum_type<T>;
    using Traits   = __dyncast_traits_impl<enum_type>;
    static_assert(static_cast<size_t>(Traits::first) == 0, "For now, this simplifies the implementation.");
    static constexpr size_t num_elems = Traits::numElements;
    using return_type                 = typename __dispatch_return_type<enum_type, T&&, F&&>::type;
    using dispatch_ptr_type           = return_type(*)(T&&, F&&);
    static constexpr std::array<dispatch_ptr_type, num_elems> dispatchPtrs = [&]<size_t... I>(std::index_sequence<I...>) {
        return std::array<dispatch_ptr_type, num_elems>{ [](T&& t, F&& f) -> return_type {
            using TargetType                  = utl::copy_cvref_t<T&&, DyncastEnumToType<enum_type{ I }>>;
            constexpr bool staticallyCastable = requires { static_cast<TargetType>(t); };
            static_assert(std::is_reference_v<TargetType>, "To avoid copies when performing static_cast.");
            if constexpr (!staticallyCastable) {
                /// If we can't even \p static_cast there is no way this can be invoked.
                /// We need to use \p I in this path also, otherwise we can't fold over this expression later. This
                /// might be a bug in clang.
                (void)I;
                __utl_unreachable();
            }
            else if constexpr (std::is_convertible_v<T&&, TargetType> && !std::is_same_v<T&&, TargetType>) {
                /// If we can cast implicitly but destination type is not the same, this means we go up the hierarchy.
                /// Since we are dispatching on the most derived type, this path should be unreachable.
                (void)I;
                __utl_unreachable();
            }
            else {
                return std::invoke(std::forward<F>(f), static_cast<TargetType>(t));
            }
        }... };
    }(std::make_index_sequence<num_elems>{});
    size_t const index = static_cast<size_t>(dyncast_traits<enum_type>::type(obj));
    auto const dispatchFn = dispatchPtrs[index];
    return dispatchFn(std::forward<T>(obj), std::forward<F>(fn));
}

// clang-format on

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
