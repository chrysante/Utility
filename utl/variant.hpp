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
#include "utility.hpp"

namespace utl {

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
struct variant_alternative<I, variant<T...>> { using type = std::tuple_element_t<I, std::tuple<T...>>; };

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
    static std::integral_constant<std::size_t, I> call(T);
};

template <typename T, typename I>
struct __index_selector_impl;

template <typename... T, std::size_t... I>
struct __index_selector_impl<type_sequence<T...>, std::index_sequence<I...>>: __index_selector_overload<T, I>... {
    using __index_selector_overload<T, I>::call...;
};

template <typename... T>
struct __index_selector: __index_selector_impl<type_sequence<T...>, std::index_sequence_for<T...>> {};

template <typename T>
concept __copy_constructible = std::is_copy_constructible_v<T>;

template <typename T>
concept __copy_assignable = std::is_copy_assignable_v<T>;

template <typename T>
concept __trivially_copy_constructible = std::is_trivially_copy_constructible_v<T>;

template <typename T>
concept __trivially_copy_assignable = std::is_trivially_copy_assignable_v<T>;

template <typename T>
concept __move_constructible = std::is_move_constructible_v<T>;

template <typename T>
concept __move_assignable = std::is_move_assignable_v<T>;

template <typename T>
concept __trivially_move_constructible = std::is_trivially_move_constructible_v<T>;

template <typename T>
concept __trivially_move_assignable = std::is_trivially_move_assignable_v<T>;

// MARK: get

template <std::size_t I, typename V>
constexpr decltype(auto) __variant_get_impl(V&& v) {
    __utl_expect(I == v.__index);
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

template <bool DeduceReturnType,
          typename R,
          typename Visitor,
          typename Variants,
          typename Sizes = make_type_sequence<std::size_t, Variants::size>,
          typename I = std::make_index_sequence<Variants::size>,
          typename FlatI = std::make_index_sequence<__variant_product_size<Variants>::value>>
struct __variant_visit;

template <bool DeduceReturnType, typename R, typename Visitor,
          typename... Variants,
          typename... SizeT,
          std::size_t... I, // Indices 0..<N into the list of variants
          std::size_t... FlatI>  // Indices 0..<N into the flattened list of all combinations types in the variants
struct __variant_visit<DeduceReturnType, R, Visitor,
                       type_sequence<Variants...>,
                       type_sequence<SizeT...>,
                       std::index_sequence<I...>,
                       std::index_sequence<FlatI...>>
{
    template <std::size_t J>
    using __variant_at_index = std::tuple_element_t<J, std::tuple<Variants...>>;
    
    static constexpr std::size_t __variant_count = sizeof...(Variants);
    static constexpr std::array<std::size_t, __variant_count> __variant_sizes = { variant_size_v<std::remove_reference_t<Variants>>... };
    
    static constexpr std::size_t __flatten_index(std::tuple<SizeT...> index) {
        (__utl_assert(std::get<I>(index) < std::get<I>(__variant_sizes)), ...);
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
        __utl_assert(flat_index < (1 * ... * std::get<I>(__variant_sizes)));
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
    
    template <std::size_t FlatIndex>
    static decltype(auto) __deduced_return_type_helper(Visitor&& vis, Variants&&... vars) {
        constexpr std::tuple index = __expand_index(FlatIndex);
        return std::invoke(std::forward<Visitor>(vis), get<std::get<I>(index)>(std::forward<Variants>(vars))...);
    }
    
    using __deduced_return_type = std::common_type_t<
        decltype(__deduced_return_type_helper<FlatI>(std::declval<Visitor>(), std::declval<Variants>()...))...
    >;
    
    using __return_type = std::conditional_t<DeduceReturnType, __deduced_return_type, R>;

    static constexpr __return_type visit(Visitor&& visitor, Variants&&... vars) {
        using visit_fn = __return_type(*)(Visitor&&, Variants&&...);
        constexpr std::size_t flat_array_size = (... * __variant_sizes[I]);
        constexpr std::array<visit_fn, flat_array_size> function = {
            [](Visitor&& vis, Variants&&... vars) -> __return_type {
                constexpr auto index = __expand_index(FlatI);
                if constexpr (std::same_as<__return_type, void>) {
                    std::invoke(std::forward<Visitor>(vis), get<std::get<I>(index)>(std::forward<Variants>(vars))...);
                }
                else {
                    return std::invoke(std::forward<Visitor>(vis), get<std::get<I>(index)>(std::forward<Variants>(vars))...);
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
                           type_sequence<Variants...>>::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
}

template <typename R, typename Visitor, typename... Variants>
requires (__is_variant<Variants> && ...)
constexpr R visit(Visitor&& vis, Variants&&... vars) {
    return __variant_visit<false, R, Visitor,
                           type_sequence<Variants...>>::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
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
    constexpr variant() noexcept(std::is_nothrow_default_constructible_v<__type_at_index<0>>)
    requires std::is_default_constructible_v<__type_at_index<0>>
    {
        __construct<0>();
    }
    
    // (2)
    constexpr variant(variant const& rhs) = delete;
    
    constexpr variant(variant const& rhs) noexcept(std::conjunction_v<std::is_nothrow_copy_constructible<Types>...>)
    requires (__copy_constructible<Types> && ...)
    {
        __copy_or_move_construct(rhs);
    }
    
    constexpr variant(variant const& rhs)
    requires (__copy_constructible<Types> && ...) &&
             (__trivially_copy_constructible<Types> && ...)
    = default;
    
    // (3)
    constexpr variant(variant&& rhs) = delete;
    
    constexpr variant(variant&& rhs) noexcept(std::conjunction_v<std::is_nothrow_move_constructible<Types>...>)
    requires (__move_constructible<Types> && ...)
    {
        __copy_or_move_construct(std::move(rhs));
    }
    
    constexpr variant(variant&& rhs)
    requires (__move_constructible<Types> && ...) &&
             (__trivially_move_constructible<Types> && ...)
    = default;
    
    // (4)
    template <typename T,
              std::size_t Index = decltype(__index_selector<Types...>::call(std::declval<T>()))::value>
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
    
    constexpr ~variant() {
        __destroy();
    }
    
    // operator=
    
    // (1)
    constexpr variant& operator=(variant const& rhs) = delete;
    
    constexpr variant& operator=(variant const& rhs)
    requires (__copy_constructible<Types> && ...) &&
             (__copy_assignable<Types> && ...)
    {
        return __copy_or_move_assign(rhs);
    }
    
    constexpr variant& operator=(variant const& rhs)
    requires (__copy_constructible<Types> && ...) &&
             (__copy_assignable<Types> && ...) &&
             (__trivially_copy_constructible<Types> && ...) &&
             (__trivially_copy_assignable<Types> && ...)
    = default;
    
    // (2)
    constexpr variant& operator=(variant&& rhs) = delete;
    
    constexpr variant& operator=(variant&& rhs) noexcept(std::conjunction_v<std::is_nothrow_move_constructible<Types>...,
                                                                            std::is_nothrow_move_assignable<Types>...>)
    requires (__move_constructible<Types> && ...) &&
             (__move_assignable<Types> && ...)
    {
        return __copy_or_move_assign(std::move(rhs));
    }
    
    constexpr variant& operator=(variant&& rhs)
    requires (__move_constructible<Types> && ...) &&
             (__move_assignable<Types> && ...) &&
             (__trivially_move_constructible<Types> && ...) &&
             (__trivially_move_assignable<Types> && ...)
    = default;
    
    // (3)
    template <typename T,
              std::size_t Index = decltype(__index_selector<Types...>::call(std::declval<T>()))::value>
    constexpr variant& operator=(T&& t) noexcept(true /* see below */)
    requires (!std::same_as<variant, std::decay_t<T>>)
    {
        if (__index == Index) {
            get<Index>(*this) = std::forward<T>(t);
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
    
    // MARK: Internals
    
    template <std::size_t I, typename... Args>
    void __construct(Args&&... args) {
        using T = __type_at_index<I>;
        __index = I;
        std::construct_at((T*)&__storage, std::forward<Args>(args)...);
    }
    
    void __destroy() {
        visit([](auto& value) { std::destroy_at(&value); }, *this);
    }
    
    template <typename V>
    constexpr void __copy_or_move_construct(V&& rhs) {
        __index = rhs.__index;
        UTL_WITH_INDEX_SEQUENCE((I, __count), {
            using construct_function = void(*)(variant&, V&&);
            constexpr std::array<construct_function, __count> constructors = {
                [](variant& self, V&& rhs) { self.__construct<I>(get<I>(std::forward<V>(rhs))); }...
            };
            constructors[__index](*this, std::forward<V>(rhs));
        });
    }
    
    template <typename V>
    variant& __copy_or_move_assign(V&& rhs) {
        if (__index == rhs.__index) {
            UTL_WITH_INDEX_SEQUENCE((I, __count), {
                using assign_function = void(*)(variant&, V&&);
                static constexpr std::array<assign_function, __count> assign_functions = {
                    [](variant& self, V&& rhs) {
                        get<I>(self) = get<I>(std::forward<V>(rhs));
                    }...
                };
                assign_functions[__index](*this, std::forward<V>(rhs));
            });
        }
        else {
            visit([&]<typename Rhs>(auto& value, Rhs&& r) {
                std::destroy_at(&value);
                std::construct_at(reinterpret_cast<std::decay_t<Rhs>*>(&value), std::forward<Rhs>(r));
            }, *this, std::forward<V>(rhs));
            __index = rhs.__index;
        }
    return *this;
    }
    
    unsigned char __index;
    std::aligned_storage_t<__size, __align> __storage;
};

} // namespace utl
