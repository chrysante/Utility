#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include <array>
#include <concepts>
#include <memory>
#include <type_traits>

#include "__debug.hpp"
#include "common.hpp"
#include "type_traits.hpp"

namespace utl {

template <typename... Types>
class variant;

// MARK: Type traits

template <typename V> struct __is_variant: std::false_type {};
template <typename... T> struct __is_variant<variant<T...>>: std::true_type {};

template <typename V>
inline constexpr bool __is_variant_v = __is_variant<V>::value;

template <typename Variant>
struct variant_size;

template <typename... T>
struct variant_size<variant<T...>>: std::integral_constant<std::size_t, sizeof...(T)> {};

template <std::size_t I, typename Variant>
struct variant_alternative;

template <std::size_t I, typename... T>
struct variant_alternative<I, variant<T...>> { using type = std::tuple_element_t<I, std::tuple<T...>>; };

template <std::size_t I, typename Variant>
using variant_alternative_t = typename variant_alternative<I, Variant>::type;

template <typename Variant>
inline constexpr std::size_t variant_size_v = variant_size<Variant>::value;

template <typename... Vars>
constexpr std::size_t __variant_product_size_impl() {
    return (... * variant_size_v<Vars>);
}

template <typename... Vars>
struct __variant_product_size: std::integral_constant<std::size_t, __variant_product_size_impl<Vars...>()> {};

template <typename... Vars>
struct __variant_product_size<type_sequence<Vars...>>: __variant_product_size<Vars...> {};

//template <typename... Vars>
//inline constexpr bool __variant_product_size_v = __variant_product_size<Vars...>::value;
//
//template <typename... Vars>
//inline constexpr bool __variant_product_size_v<std::tuple<Vars...>> = __variant_product_size<std::tuple<Vars...>>::value;

// MARK: get

template <std::size_t I, typename V>
constexpr decltype(auto) __variant_get_impl(V&& v) {
    assert(I == v.__index);
    using result_type = copy_cvref_t<V&&, variant_alternative_t<I, std::decay_t<V>>>;
    return reinterpret_cast<result_type>(v.__storage);
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>>& get(variant<T...>& v) {
    return __variant_get_impl<I>(v);
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>> const& get(variant<T...> const& v) {
    return __variant_get_impl<I>(v);
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>>&& get(variant<T...>&& v) {
    return std::move(__variant_get_impl<I>(v));
}

template <std::size_t I, typename... T>
constexpr variant_alternative_t<I, variant<T...>> const&& get(variant<T...> const&& v) {
    return std::move(__variant_get_impl<I>(v));
}

// MARK: visit

template <bool DeducedReturnType,
          typename R,
          typename Visitor,
          typename Variants,
          typename Sizes = make_type_sequence<std::size_t, Variants::size>,
          typename I = std::make_index_sequence<Variants::size>,
          typename FlatI = std::make_index_sequence<__variant_product_size<Variants>::value>>
struct __variant_visit;

template <bool DeducedReturnType, typename R, typename Visitor,
          typename... Variants,
          typename... SizeT,
          std::size_t... I,
          std::size_t... FlatI>
struct __variant_visit<DeducedReturnType, R, Visitor,
                       type_sequence<Variants...>,
                       type_sequence<SizeT...>,
                       std::index_sequence<I...>,
                       std::index_sequence<FlatI...>>
{
    template <std::size_t J>
    using __variant_at_index = std::tuple_element_t<J, std::tuple<Variants...>>;
    
    static constexpr std::size_t __variant_count = sizeof...(Variants);
    static constexpr std::array<std::size_t, __variant_count> __variant_sizes = { variant_size_v<Variants>... };
    
    static constexpr std::size_t __flatten_index(std::tuple<SizeT...> index) {
        (assert(std::get<I>(index) < std::get<I>(__variant_sizes)), ...);
        std::size_t result = 0;
        ([&]{
            result += std::get<I>(index);
            if constexpr (I < sizeof...(SizeT) - 1) {
                result *= std::get<I + 1>(__variant_sizes);
            }
        }(), ...);
        return result;
    }
    
    static constexpr std::tuple<SizeT...> __expand_index(std::size_t flat_index) {
        assert(flat_index < (... * std::get<I>(__variant_sizes)));
        std::tuple<SizeT...> result{};
        ([&]{
            std::size_t const m = [&]<std::size_t... J>(std::index_sequence<J...>){
                std::size_t const I_ = I;
                return (1 * ... * std::get<1 + I_ + J>(__variant_sizes));
            }(std::make_index_sequence<__variant_count - 1 - I>{});
            std::get<I>(result) = flat_index / m;
            flat_index -= std::get<I>(result) * m;
        }(), ...);
        return result;
    }
    
    template <typename Vis, typename... Vars>
    static constexpr decltype(auto) visit(Vis&& visitor, Vars&&... vars) {
        using result_type = void;
        using visit_fn = result_type(*)(Vis&&, Vars&&...);
        constexpr std::size_t flat_array_size = (... * __variant_sizes[I]);
        constexpr std::array<visit_fn, flat_array_size> function = {
            [](Vis&& vis, Vars&&... vars) {
                constexpr auto index = __expand_index(FlatI);
                std::invoke(std::forward<Vis>(vis), get<std::get<I>(index)>(std::forward<Vars>(vars))...);
            }...
        };
        std::size_t const flat_index = __flatten_index({ vars.__index... });
        function[flat_index](std::forward<Vis>(visitor), std::forward<Vars>(vars)...);
    }
};

template <typename Visitor, typename... Variants>
constexpr decltype(auto) visit(Visitor&& vis, Variants&&... vars) {
    __variant_visit<true, void /* ignored */,
                    std::decay_t<Visitor>,
                    type_sequence<std::decay_t<Variants>...>>::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
}

template <typename R, typename Visitor, typename... Variants>
constexpr R visit(Visitor&& vis, Variants&&... vars) {
    
}

template <typename... Types>
class variant {
public:
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
    using __type_at_index = std::tuple_element_t<Index, std::tuple<Types...>>;
    
    // MARK: Lifetime
    // Constructors
    
    // (1)
    constexpr variant()
    noexcept(std::is_nothrow_default_constructible_v<__type_at_index<0>>)
    requires std::is_default_constructible_v<__type_at_index<0>>
    {
        __index = 0;
        __construct<__type_at_index<0>>();
    }
    
    // (2)
    constexpr variant(variant const& rhs) noexcept(std::disjunction_v<std::is_nothrow_copy_constructible<Types>...>)
    {
        __copy_or_move_construct(rhs);
    }
    
    // (3)
    constexpr variant(variant&& rhs) noexcept(std::disjunction_v<std::is_nothrow_move_constructible<Types>...>)
    {
        __copy_or_move_construct(std::move(rhs));
    }
    
    // (4)
    template <typename T>
    constexpr variant(T&& t) noexcept(true /* see below */)
    requires (!std::same_as<variant, std::decay_t<T>>);
    
    // (5)
    template <typename T, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, Args...>
    constexpr explicit variant(std::in_place_type_t<T>, Args&&... args) {
        __index = __index_of<T>;
        __construct<T>(std::forward<Args>(args)...);
    }
    
    // (6)
    template <typename T, typename U, typename... Args>
    requires __contains<T> &&
             (__occurence_count<T> == 1) &&
             std::constructible_from<T, std::initializer_list<U>, Args...>
    constexpr explicit variant(std::in_place_type_t<T>,
                               std::initializer_list<U> il,
                               Args&&... args);
    
    // (7)
    template <std::size_t I, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, Args...>
    constexpr explicit variant(std::in_place_index_t<I>, Args&&... args ) {
        using T = __type_at_index<I>;
        __index = I;
        __construct<T>(std::forward<Args>(args)...);
    }
    
    // (8)
    template <std::size_t I, typename U, typename... Args>
    requires (I < __count) && std::constructible_from<__type_at_index<I>, std::initializer_list<U>, Args...>
    constexpr explicit variant(std::in_place_index_t<I>,
                               std::initializer_list<U> il,
                               Args&&... args);
    
    // Destructor
    
    constexpr ~variant() {
        __destroy();
    }
    
    // operator=
    
    // (1)
    constexpr variant& operator=(variant const& rhs) = delete;
    
    constexpr variant& operator=(variant const& rhs)
    requires (std::copyable<Types> && ...)
    {
        return __copy_or_move_assign(rhs);
    }
    
    constexpr variant& operator=(variant const& rhs)
    requires (std::copyable<Types> && ...) &&
    (std::is_trivially_copy_constructible_v<Types> && ...) &&
    (std::is_trivially_copy_assignable_v<Types> && ...)
    = default;
    
    // (2)
    constexpr variant& operator=(variant&& rhs) = delete;
    
    constexpr variant& operator=(variant&& rhs)
    requires (std::copyable<Types> && ...)
    {
        return __copy_or_move_assign(std::move(rhs));
    }
    
    constexpr variant& operator=(variant&& rhs)
    requires (std::copyable<Types> && ...) &&
    (std::is_trivially_copy_constructible_v<Types> && ...) &&
    (std::is_trivially_copy_assignable_v<Types> && ...)
    = default;
    
    // (3)
    template <typename T>
    constexpr variant& operator=(T&& t) noexcept(true /* see below */)
    requires (!std::same_as<variant, std::decay_t<T>>);
    
    // MARK: Observers
    
    constexpr std::size_t index() const noexcept {
        return __index;
    }
    
    // MARK: Modifiers
    
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
        using T = __type_at_index<I>;
        __destroy();
        __index = __index_of<T>;
        __construct<T>(il, std::forward<Args>(args)...);
    }
    
    // MARK: Internals
    
    template <typename T, typename... Args>
    void __construct(Args&&... args) {
        std::construct_at((T*)&__storage, std::forward<Args>(args)...);
    }
    
    void __destroy() {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (void)((__index == I ? (__destroy_impl<I>(), true) : false) || ...);
        }(std::make_index_sequence<__count>{});
    }
    
    template <std::size_t I>
    void __destroy_impl() {
        using T = __type_at_index<I>;
        std::destroy_at((T*)&__storage);
    }
    
    template <typename V>
    constexpr void __copy_or_move_construct(V&& rhs) {
        __index = rhs.__index;
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            using construct_function = void(*)(variant&, V&&);
            constexpr std::array<construct_function, __count> constructors = {
                [](variant& self, V&& rhs) { self.__construct<Types>(get<I>(std::forward<V>(rhs))); }...
            };
            constructors[__index](*this, std::forward<V>(rhs));
        }(std::make_index_sequence<__count>{});
    }
    
    template <typename V>
    variant& __copy_or_move_assign(V&& rhs) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            using assign_function = void(*)(variant&, V&&);
            if (__index == rhs.__index) {
                static constexpr std::array<assign_function, __count> assign_functions = {
                    [](variant& self, V&& rhs) {
                        get<I>(self) = get<I>(std::forward<V>(rhs));
                    }...
                };
                assign_functions[__index](*this, std::forward<V>(rhs));
            }
            else {
                __destroy();
                __copy_or_move_construct(std::forward<V>(rhs));
            }
        }(std::make_index_sequence<__count>{});
        return *this;
    }
    
    unsigned char __index;
    std::aligned_storage_t<__size, __align> __storage;
};

} // namespace utl
