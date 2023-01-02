#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include <array>
#include <concepts>
#include <memory>
#include <type_traits>

#include "__debug.hpp"
#include "__union.hpp"
#include "__farray.hpp"
#include "common.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace utl {

template <typename F, typename... Args>
constexpr decltype(auto) __invoke(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <typename... Types>
class variant;

// MARK: Type traits

template <typename Variant>
struct variant_size;

template <typename... T>
struct variant_size<variant<T...>>: std::integral_constant<std::size_t, sizeof...(T)> {};

template <typename... T>
struct variant_size<variant<T...> const>: variant_size<variant<T...>> {};

template <std::size_t I, typename Variant>
struct variant_alternative;

template <std::size_t I, typename... T>
struct variant_alternative<I, variant<T...>> { using type = typename type_sequence<T...>:: template at<I>; };

template <std::size_t I, typename Variant>
using variant_alternative_t = typename variant_alternative<I, Variant>::type;

template <typename Variant>
inline constexpr std::size_t variant_size_v = variant_size<Variant>::value;

template <typename... Vars>
constexpr std::size_t __variant_product_size_impl() {
    return (1 * ... * variant_size_v<Vars>);
}

template <typename Var>
struct __is_variant_impl: std::false_type {};

template <typename... T>
struct __is_variant_impl<variant<T...>>: std::true_type {};

template <typename Var>
inline constexpr bool __is_variant = __is_variant_impl<std::decay_t<Var>>::value;

template <typename... Vars>
struct __variant_product_size: std::integral_constant<std::size_t, __variant_product_size_impl<Vars...>()> {};

template <typename... Vars>
struct __variant_product_size<type_sequence<Vars...>>: __variant_product_size<std::decay_t<Vars>...> {};

template <typename T, std::size_t I>
struct __index_selector_overload {
    static std::integral_constant<std::size_t, I> __call(T);
};

template <typename T, typename I>
struct __index_selector_impl;

template <typename... T, std::size_t... I>
struct __index_selector_impl<type_sequence<T...>, std::index_sequence<I...>>: __index_selector_overload<T, I>... {
    using __index_selector_overload<T, I>::__call...;
};

template <typename... T>
struct __index_selector: __index_selector_impl<type_sequence<T...>, std::index_sequence_for<T...>> {};

//template <typename T>
//concept __copy_constructible = std::is_copy_constructible_v<T>;
//
//template <typename T>
//concept __copy_assignable = std::is_copy_assignable_v<T>;
//
//template <typename T>
//concept __trivially_copy_constructible = std::is_trivially_copy_constructible_v<T>;
//
//template <typename T>
//concept __trivially_copy_assignable = std::is_trivially_copy_assignable_v<T>;
//
//template <typename T>
//concept __move_constructible = std::is_move_constructible_v<T>;
//
//template <typename T>
//concept __move_assignable = std::is_move_assignable_v<T>;
//
//template <typename T>
//concept __trivially_move_constructible = std::is_trivially_move_constructible_v<T>;
//
//template <typename T>
//concept __trivially_move_assignable = std::is_trivially_move_assignable_v<T>;

// MARK: get

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>>& get(variant<T...>& v) {
    return get<I>(v.__data);
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>> const& get(variant<T...> const& v) {
    return get<I>(v.__data);
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>>&& get(variant<T...>&& v) {
    return get<I>(std::move(v.__data));
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>> const&& get(variant<T...> const&& v) {
    return get<I>(std::move(v.__data));
}

template <typename T, typename Var>
concept __has_get_by_type =
    Var::template __contains<T> &&
    (Var::template __occurence_count<T> == 1);

template <typename Type, typename... T>
requires __has_get_by_type<Type, variant<T...>>
constexpr Type& get(variant<T...>& v) {
    constexpr std::size_t I = variant<T...>::template __index_of<Type>;
    return get<I>(v);
}

template <typename Type, typename... T>
requires __has_get_by_type<Type, variant<T...>>
constexpr Type const& get(variant<T...> const& v) {
    constexpr std::size_t I = variant<T...>::template __index_of<Type>;
    return get<I>(v);
}

template <typename Type, typename... T>
requires __has_get_by_type<Type, variant<T...>>
constexpr Type&& get(variant<T...>&& v) {
    constexpr std::size_t I = variant<T...>::template __index_of<Type>;
    return get<I>(std::move(v));
}

template <typename Type, typename... T>
requires __has_get_by_type<Type, variant<T...>>
constexpr Type const&& get(variant<T...> const&& v) {
    constexpr std::size_t I = variant<T...>::template __index_of<Type>;
    return get<I>(std::move(v));
}

// MARK: visit

template <bool DeduceReturnType,
          typename R,
          typename Visitor,
          typename Variants,
          typename Sizes = make_type_sequence<std::size_t, Variants::size>,
          typename I = std::make_index_sequence<Variants::size>,
          typename FlatI = std::make_index_sequence<__variant_product_size<Variants>::value>>
struct __variant_visit;

template <bool DeduceReturnType, typename R, typename Visitor,
          typename... Variants, // cvref qualified as in the call to visit();
          typename... SizeT,
          std::size_t... I, // Indices 0..<N into the list of variants
          std::size_t... FlatI>  // Indices 0..<N into the flattened list of all combinations types in the variants
struct __variant_visit<DeduceReturnType, R, Visitor,
                       type_sequence<Variants...>,
                       type_sequence<SizeT...>,
                       std::index_sequence<I...>,
                       std::index_sequence<FlatI...>>: __farray_base<variant_size_v<std::remove_reference_t<Variants>>...>
{
    using __base = __farray_base<variant_size_v<std::remove_reference_t<Variants>>...>;
    using __base::__flatten_index;
    using __base::__expand_index;
    
    template <std::size_t J>
    using __variant_at_index = typename type_sequence<Variants...>::template at<J>;
    
    static constexpr std::size_t __variant_count = sizeof...(Variants);
    static constexpr std::array<std::size_t, __variant_count> __variant_sizes = { variant_size_v<std::remove_reference_t<Variants>>... };
    
    template <std::size_t FlatIndex>
    using __deduced_return_type_at = std::invoke_result_t<Visitor, decltype(get<__expand_index(FlatIndex)[I]>(std::declval<Variants&&>()))...>;
    
    static constexpr bool __all_are_references = __all<std::is_reference<__deduced_return_type_at<FlatI>>...>;
    static constexpr bool __none_is_reference = !__any<std::is_reference<__deduced_return_type_at<FlatI>>...>;
 
    static_assert(__all_are_references || __none_is_reference,
                  "Either all cases or none must return references. This prevents accidental unintended copies or dangling references to local stack memory.");
    
    using __common_return_type = typename std::conditional_t<
        __none_is_reference,
        std::common_type<__deduced_return_type_at<FlatI>...>,
        std::common_reference<__deduced_return_type_at<FlatI>...>>::type;
    
    static constexpr bool __all_return_types_equal = type_sequence<__deduced_return_type_at<FlatI>...>::all_equal;
    
    using __deduced_return_type = std::conditional_t<__all_return_types_equal, __deduced_return_type_at<0>, __common_return_type>;
    
    using __return_type = std::conditional_t<DeduceReturnType, __deduced_return_type, R>;

    static constexpr __return_type visit(Visitor&& visitor, Variants&&... vars) {
        using visit_fn = __return_type(*)(Visitor&&, Variants&&...);
        constexpr std::size_t flat_array_size = (... * __variant_sizes[I]);
        constexpr std::array<visit_fn, flat_array_size> function = {
            [](Visitor&& vis, Variants&&... vars) -> __return_type {
                constexpr auto index = __expand_index(FlatI);
                if constexpr (std::same_as<__return_type, void>) {
                    std::invoke(std::forward<Visitor>(vis), get<index[I]>(std::forward<Variants>(vars))...);
                }
                else {
                    return std::invoke(std::forward<Visitor>(vis), get<index[I]>(std::forward<Variants>(vars))...);
                }
            }...
        };
        std::size_t const flat_index = __flatten_index({ vars.__index... });
        return function[flat_index](std::forward<Visitor>(visitor), std::forward<Variants>(vars)...);
    }
};

template <typename Visitor, typename... Variants>
requires (__is_variant<Variants> && ...)
constexpr decltype(auto) visit(Visitor&& vis, Variants&&... vars) {
    return __variant_visit<true, void /* ignored */, Visitor,
                           type_sequence<Variants&&...>>::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
}

template <typename R, typename Visitor, typename... Variants>
requires (__is_variant<Variants> && ...)
constexpr R visit(Visitor&& vis, Variants&&... vars) {
    return __variant_visit<false, R, Visitor,
                           type_sequence<Variants&&...>>::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
}

template <typename... T>
constexpr variant<T...>& __variant_cast(variant<T...>& v) { return v; }
template <typename... T>
constexpr variant<T...> const& __variant_cast(variant<T...> const& v) { return v; }
template <typename... T>
constexpr variant<T...>&& __variant_cast(variant<T...>&& v) { return std::move(v); }
template <typename... T>
constexpr variant<T...> const&& __variant_cast(variant<T...> const&& v) { return std::move(v); }

template <typename Visitor, typename... Variants>
constexpr decltype(auto) visit(Visitor&& vis, Variants&&... vars) {
    return visit(std::forward<Visitor>(vis),
                 __variant_cast(std::forward<Variants>(vars))...);
}

template <typename R, typename Visitor, typename... Variants>
constexpr R visit(Visitor&& vis, Variants&&... vars) {
    return visit<R>(std::forward<Visitor>(vis),
                    __variant_cast(std::forward<Variants>(vars))...);
}

// MARK: class variant

template <typename... Types>
class variant {
public:
    static_assert((!std::is_reference_v<Types> && ...));
    static_assert(sizeof...(Types) > 0);
    static_assert(sizeof...(Types) < 256);
    
    static_assert((!std::is_reference_v<Types> && ...),
                  "variant can not have a reference type as an alternative.");
    
    static_assert((!std::is_void_v<Types> && ...),
                  "variant can not have a void type as an alternative.");
    
    static constexpr std::size_t __size = std::max({ sizeof(Types)... });
    static constexpr std::size_t __align = std::max({ alignof(Types)... });
    static constexpr std::size_t __count = sizeof...(Types);
    
    using __type_list = type_sequence<Types...>;
    
    template <typename T>
    static constexpr bool __contains = __type_list::template contains<T>;
    
    template <typename T>
    static constexpr bool __occurence_count = __type_list::template occurence_count<T>;
    
    template <typename T>
    static constexpr std::size_t __index_of = __type_list::template index_of<T>;
    
    template <std::size_t Index>
    using __type_at_index = typename __type_list::template at<Index>;
    
    // MARK: Lifetime
    // Constructors
    
    // (1)
    variant() = delete;
    
    constexpr variant() noexcept(std::is_nothrow_default_constructible_v<__type_at_index<0>>)
    requires std::is_default_constructible_v<__type_at_index<0>>
    {
        __construct<0>();
    }
    
    // (2)
    constexpr variant(variant const& rhs) = delete;

    constexpr variant(variant const& rhs)
    requires __all<std::is_copy_constructible<Types>...> &&
             __all<std::is_trivially_copy_constructible<Types>...>
    = default;
    
    constexpr variant(variant const& rhs) noexcept(__all<std::is_nothrow_copy_constructible<Types>...>)
    requires __all<std::is_copy_constructible<Types>...>
    {
        __copy_or_move_construct(rhs);
    }
    
    // (3)
    constexpr variant(variant&& rhs) = delete;
    
    constexpr variant(variant&& rhs)
    requires __all<std::is_move_constructible<Types>...> &&
             __all<std::is_trivially_move_constructible<Types>...>
    = default;
    
    constexpr variant(variant&& rhs) noexcept(__all<std::is_nothrow_move_constructible<Types>...>)
    requires __all<std::is_move_constructible<Types>...>
    {
        __copy_or_move_construct(std::move(rhs));
    }
    
    // (4)
    template <typename T,
              std::size_t Index = decltype(__index_selector<Types...>::__call(std::declval<T>()))::value>
    requires (!std::same_as<variant, std::decay_t<T>>)
    constexpr variant(T&& t) noexcept(true /* see below */) {
        __construct<Index>(std::forward<T>(t));
    }
    
    // (5)
    template <typename T, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, Args...>
    constexpr explicit variant(std::in_place_type_t<T>, Args&&... args) {
        __construct<__index_of<T>>(std::forward<Args>(args)...);
    }
    
    // (6)
    template <typename T, typename U, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, std::initializer_list<U>, Args...>
    constexpr explicit variant(std::in_place_type_t<T>,
                               std::initializer_list<U> il,
                               Args&&... args)
    {
        __construct<__index_of<T>>(il, std::forward<Args>(args)...);
    }
    
    // (7)
    template <std::size_t I, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, Args...>
    constexpr explicit variant(std::in_place_index_t<I>, Args&&... args ) {
        __construct<__type_at_index<I>>(std::forward<Args>(args)...);
    }
    
    // (8)
    template <std::size_t I, typename U, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, std::initializer_list<U>, Args...>
    constexpr explicit variant(std::in_place_index_t<I>,
                               std::initializer_list<U> il,
                               Args&&... args)
    {
        __construct<__type_at_index<I>>(il, std::forward<Args>(args)...);
    }
    
    // Destructor
//    ~variant() requires __all<std::is_trivially_destructible<Types>...> = default;
    
    constexpr ~variant() {
        __destroy();
    }
    
    // operator=
    
    // (1)
    constexpr variant& operator=(variant const& rhs) = delete;
    
    constexpr variant& operator=(variant const& rhs)
    requires __all<std::is_copy_constructible<Types>...> &&
             __all<std::is_copy_assignable<Types>...>
    {
        return __copy_or_move_assign(rhs);
    }
    
    constexpr variant& operator=(variant const& rhs)
    requires __all<std::is_copy_constructible<Types>...> &&
             __all<std::is_copy_assignable<Types>...> &&
             __all<std::is_trivially_copy_constructible<Types>...> &&
             __all<std::is_trivially_copy_assignable<Types>...>
    = default;
    
    // (2)
    constexpr variant& operator=(variant&& rhs) = delete;
    
    constexpr variant& operator=(variant&& rhs) noexcept(std::conjunction_v<std::is_nothrow_move_constructible<Types>...,
                                                                            std::is_nothrow_move_assignable<Types>...>)
    requires __all<std::is_move_constructible<Types>...> &&
             __all<std::is_move_assignable<Types>...>
    {
        return __copy_or_move_assign(std::move(rhs));
    }
    
    constexpr variant& operator=(variant&& rhs)
    requires __all<std::is_move_constructible<Types>...> &&
             __all<std::is_move_assignable<Types>...> &&
             __all<std::is_trivially_move_constructible<Types>...> &&
             __all<std::is_trivially_move_assignable<Types>...>
    = default;
    
    // (3)
    template <typename T,
              std::size_t Index = decltype(__index_selector<Types...>::__call(std::declval<T>()))::value>
    constexpr variant& operator=(T&& t) noexcept(true /* see below */)
    requires (!std::same_as<variant, std::decay_t<T>>)
    {
        if (__index == Index) {
            utl::get<Index>(*this) = std::forward<T>(t);
        }
        else {
            __destroy();
            __construct<Index>(std::forward<T>(t));
        }
        return *this;
    }
    
    // MARK: Observers
    
    constexpr std::size_t index() const noexcept {
        return __index;
    }
    
    // MARK: Modifiers
    
    // emplace
    
    // (1)
    template <typename T, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, Args...>
    constexpr T& emplace(Args&&... args) {
        emplace<__index_of<T>>(std::forward<Args>(args)...);
    }
    
    // (2)
    template <typename T, typename U, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, std::initializer_list<U>, Args...>
    constexpr T& emplace(std::initializer_list<U> il, Args&&... args) {
        emplace<__index_of<T>>(std::forward<Args>(args)...);
    }
    
    // (3)
    template <std::size_t I, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, Args...>
    constexpr auto& emplace(Args&&... args) {
        using T = __type_at_index<I>;
        __destroy();
        __index = __index_of<T>;
        __construct<T>(std::forward<Args>(args)...);
    }
    
    // (4)
    template <std::size_t I, typename U, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, std::initializer_list<U>, Args...>
    constexpr auto& emplace(std::initializer_list<U> il, Args&&... args) {
        emplace<I, std::initializer_list<U>, Args...>(il, std::forward<Args>(args)...);
    }
    
    // swap
    
    constexpr void swap(variant& rhs) noexcept(((std::is_nothrow_move_constructible_v<Types> &&
                                                 std::is_nothrow_swappable_v<Types>) && ...))
    {
        if (__index == rhs.__index) {
            __visit_with_index(__index, [&]<std::size_t I>(std::integral_constant<std::size_t, I>) {
                std::swap(utl::get<I>(*this), utl::get<I>(rhs));
            });
        }
        else {
            utl::visit([]<typename T, typename U>(T& lhs, U& rhs) {
                auto tmp = std::move(lhs);
                std::destroy_at(&lhs);
                std::construct_at(reinterpret_cast<U*>(&lhs), std::move(rhs));
                std::destroy_at(&rhs);
                std::construct_at(reinterpret_cast<T*>(&rhs), std::move(tmp));
            }, *this, rhs);
            std::swap(__index, rhs.__index);
        }
    }
    
    decltype(auto) visit(auto&& vis) const& {
        return utl::visit(UTL_FORWARD(vis), *this);
    }
    
    decltype(auto) visit(auto&& vis)& {
        return utl::visit(UTL_FORWARD(vis), *this);
    }
    
    decltype(auto) visit(auto&& vis) const&& {
        return utl::visit(UTL_FORWARD(vis), std::move(*this));
    }
    
    decltype(auto) visit(auto&& vis)&& {
        return utl::visit(UTL_FORWARD(vis), std::move(*this));
    }
    
    template <std::size_t I> requires (I < __count)
    variant_alternative<I, variant> const& get() const& { return utl::get<I>(*this); }
    
    template <std::size_t I> requires (I < __count)
    variant_alternative<I, variant>& get()& { return utl::get<I>(*this); }
    
    template <std::size_t I> requires (I < __count)
    variant_alternative<I, variant> const&& get() const&& { return utl::get<I>(std::move(*this)); }
    
    template <std::size_t I> requires (I < __count)
    variant_alternative<I, variant>&& get()&& { return utl::get<I>(std::move(*this)); }
    
    template <typename T> requires __has_get_by_type<T, variant>
    T const& get() const& { return utl::get<T>(*this); }
    
    template <typename T> requires __has_get_by_type<T, variant>
    T& get()& { return utl::get<T>(*this); }
    
    template <typename T> requires __has_get_by_type<T, variant>
    T const&& get() const&& { return utl::get<T>(std::move(*this)); }
    
    template <typename T> requires __has_get_by_type<T, variant>
    T&& get()&& { return utl::get<T>(std::move(*this)); }
    
    template <typename Base>
    requires have_common_base<Base, Types...>::value && std::same_as<std::remove_cvref_t<Base>, Base>
    constexpr Base const& as_base() const& { return __as_base<Base const&>(*this); }
    
    template <typename Base>
    requires have_common_base<Base, Types...>::value && std::same_as<std::remove_cvref_t<Base>, Base>
    constexpr Base& as_base()& { return __as_base<Base&>(*this); }
    
    template <typename Base>
    requires have_common_base<Base, Types...>::value && std::same_as<std::remove_cvref_t<Base>, Base>
    constexpr Base const&& as_base() const&& { return __as_base<Base const&&>(std::move(*this)); }
    
    template <typename Base>
    requires have_common_base<Base, Types...>::value && std::same_as<std::remove_cvref_t<Base>, Base>
    constexpr Base&& as_base()&& { return __as_base<Base&&>(std::move(*this)); }
    
    // MARK: Internals
    
    template <std::size_t I, typename... Args>
    constexpr void __construct(Args&&... args) {
        using T = __type_at_index<I>;
        __index = I;
        std::construct_at(&utl::get<I>(__data), std::forward<Args>(args)...);
    }
    
    constexpr void __destroy() {
        visit([](auto& value) { std::destroy_at(&value); });
    }
    
    template <typename V>
    constexpr void __copy_or_move_construct(V&& rhs) {
        __visit_with_index(rhs.__index, [&]<std::size_t I>(std::integral_constant<std::size_t, I>) {
            __construct<I>(utl::get<I>(std::forward<V>(rhs)));
        });
    }
    
    template <typename V>
    constexpr variant& __copy_or_move_assign(V&& rhs) {
        if (__index == rhs.__index) {
            __visit_with_index(__index, [&]<std::size_t I>(std::integral_constant<std::size_t, I>) {
                utl::get<I>(*this) = utl::get<I>(std::forward<V>(rhs));
            });
        }
        else {
            utl::visit([&]<typename Rhs>(auto& value, Rhs&& r) {
                std::destroy_at(&value);
                std::construct_at(reinterpret_cast<std::decay_t<Rhs>*>(&value), std::forward<Rhs>(r));
            }, *this, std::forward<V>(rhs));
            __index = rhs.__index;
        }
        return *this;
    }
    
    template <typename Base, typename Self>
    static constexpr Base __virtual_as_base(Self&& self) {
        using raw_base = std::remove_cvref_t<Base>;
#if UTL_HAS_COMPILE_TIME_BASE_OFFSET
        return UTL_WITH_INDEX_SEQUENCE((I, __count), {
            constexpr std::array<std::size_t, __count> offsets = {
                compile_time_base_offset<raw_base, __type_at_index<I>>...
            };
            return reinterpret_cast<Base>(*(reinterpret_cast<copy_cv_t<std::remove_reference_t<Base>, char>*>(&self.__data) + offsets[self.__index]));
        });
#else // UTL_HAS_COMPILE_TIME_BASE_OFFSET
        return utl::visit([]<typename T>(T&& value) -> decltype(auto) {
            return static_cast<Base>(value);
        }, std::forward<Self>(self));
#endif // UTL_HAS_COMPILE_TIME_BASE_OFFSET
    }
    
    template <typename Base, typename Self>
    static constexpr Base __as_base(Self&& self) {
        using raw_base = std::remove_cvref_t<Base>;
        static_assert(have_common_base<raw_base, Types...>::value);
#if UTL_HAS_COMPILE_TIME_BASE_OFFSET
        constexpr bool all_offsets_equal = UTL_WITH_INDEX_SEQUENCE((I, __count), {
            return ((compile_time_base_offset<raw_base, __type_at_index<0>> == compile_time_base_offset<raw_base, __type_at_index<I>>) && ...);
        });
        if constexpr (all_offsets_equal) {
            constexpr std::size_t offset = compile_time_base_offset<raw_base, __type_at_index<0>>;
            return reinterpret_cast<Base>(*(reinterpret_cast<copy_cv_t<std::remove_reference_t<Base>, char>*>(&self.__data) + offset));
        }
        else { return __virtual_as_base<Base>(UTL_FORWARD(self)); }
    
#else // UTL_HAS_COMPILE_TIME_BASE_OFFSET
        return __virtual_as_base<Base>(UTL_FORWARD(self)); 
#endif // UTL_HAS_COMPILE_TIME_BASE_OFFSET
    }
  
    template <typename F>
    static constexpr decltype(auto) __visit_with_index(std::size_t index, F&& f) {
        return UTL_WITH_INDEX_SEQUENCE((I, __count), {
            using return_type = std::common_type_t<std::invoke_result_t<F, std::integral_constant<std::size_t, I>>...>;
            using function = return_type(*)(F&& f);
            static constexpr std::array<function, __count> functions = {
                [](F&& f) -> return_type {
                    return std::invoke(std::forward<F>(f), std::integral_constant<std::size_t, I>{});
                }...
            };
            return functions[index](std::forward<F>(f));
        });
    }
    
    unsigned char __index;
    __union<Types...> __data;
};

template <typename Base, typename... Types>
requires have_common_base<Base, Types...>::value
class cbvariant: public variant<Types...> {
public:
    using __base = variant<Types...>;
    using __base::__base;
    Base* operator->() { return const_cast<Base*>(static_cast<cbvariant const*>(this)->operator->()); }
    Base const* operator->() const { return &this->template as_base<Base>(); }
    operator Base&()& { return *operator->(); }
    operator Base const&() const& { return *operator->(); }
};

} // namespace utl
