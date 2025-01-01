#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include <array>
#include <concepts>
#include <functional>
#include <memory>
#include <type_traits>

#include "__debug.hpp"
#include "__union.hpp"
#include "common.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace utl {

template <std::size_t... I>
constexpr std::size_t __idx_seq_product(std::index_sequence<I...>) {
    return (... * I);
}

template <typename AxisSizes,
          typename DimI = std::make_index_sequence<AxisSizes::size()>,
          typename FlatI =
              std::make_index_sequence<__idx_seq_product(AxisSizes{})>>
struct __farray_base_impl;

template <std::size_t... AxisSizes>
struct __farray_base:
    __farray_base_impl<std::integer_sequence<std::size_t, AxisSizes...>> {};

template <std::size_t... AxisSizes, std::size_t... DimI, std::size_t... FlatI>
struct __farray_base_impl<std::integer_sequence<std::size_t, AxisSizes...>,
                          std::index_sequence<DimI...>,
                          std::index_sequence<FlatI...>> {
    static_assert(sizeof...(AxisSizes) > 0);
    static_assert(((AxisSizes > 0) && ...));
    static constexpr std::size_t __dim = sizeof...(AxisSizes);
    static constexpr std::array<std::size_t, __dim> __axis_sizes = {
        AxisSizes...
    };
    static constexpr std::size_t __flat_array_size = (... * __axis_sizes[DimI]);

    static constexpr std::size_t
    __flatten_index(std::array<std::size_t, __dim> index) {
        (((void)DimI, __utl_assert(index[DimI] < __axis_sizes[DimI])), ...);
        std::size_t result = 0;
        ([&] {
            result += index[DimI];
            if constexpr (DimI < __dim - 1) {
                result *= __axis_sizes[DimI + 1];
            }
        }(), ...);
        return result;
    }

    static constexpr std::array<std::size_t, __dim>
    __expand_index(std::size_t flat_index) {
        __utl_assert(flat_index < (1 * ... * __axis_sizes[DimI]));
        std::array<std::size_t, __dim> result{};
        ([&] {
            std::size_t const m =
                [&]<std::size_t... J>(std::index_sequence<J...>) {
                std::size_t const I = DimI;
                return (1 * ... * __axis_sizes[1 + I + J]);
            }(std::make_index_sequence<__dim - 1 - DimI>{});
            result[DimI] = flat_index / m;
            flat_index -= result[DimI] * m;
        }(), ...);
        return result;
    }

    template <typename R, typename F, typename... T>
    using __visit_fn = R (*)(F&&, T&&...);

    template <typename ConcreteTypeGetter, typename R, typename F,
              typename... T>
    struct __make_impl {
        template <std::size_t FlatIndex>
        static constexpr R invoke_one(F&& f, T&&... t) {
            constexpr auto index = __expand_index(FlatIndex);
            constexpr bool is_any_void = __any<std::is_same<
                void,
                decltype(ConcreteTypeGetter{}(std::integral_constant<
                                                  std::size_t, index[DimI]>{},
                                              std::declval<T&&>()))>...>;
            if constexpr (is_any_void) {
                std::abort();
            }
#define _UTL_VISIT_CALL_EXPR()                                                 \
    std::invoke(std::forward<F>(f),                                            \
                ConcreteTypeGetter{}(std::integral_constant<std::size_t,       \
                                                            index[DimI]>{},    \
                                     std::forward<T>(t))...);
            else if constexpr (std::same_as<R, void>) {
                _UTL_VISIT_CALL_EXPR();
            }
            else {
                return _UTL_VISIT_CALL_EXPR();
            }
#undef _UTL_VISIT_CALL_EXPR
        }

        static constexpr std::array<__visit_fn<R, F, T...>, __flat_array_size>
        call() {
            static_assert(std::is_empty_v<ConcreteTypeGetter>,
                          "ConcreteTypeGetter must be empty as we don't want "
                          "to capture it.");
            static_assert(sizeof...(T) > 0);
            return { invoke_one<FlatI>... };
        }
    };

    template <typename R, typename F, typename... T,
              typename ConcreteTypeGetter>
    constexpr auto __make(ConcreteTypeGetter) {
        return __make_impl<ConcreteTypeGetter, R, F, T...>::call();
    }
};

template <typename R, typename F, typename Ts, typename AxisSizes>
struct __farray;

template <typename R, typename F, typename... T, typename AxisSizes>
struct __farray<R, F, type_sequence<T...>, AxisSizes>:
    __farray_base_impl<AxisSizes> {
    using __base = __farray_base_impl<AxisSizes>;
    using __visit_fn = typename __base::template __visit_fn<R, F, T...>;
    using __base::__dim;
    using __base::__flat_array_size;

    template <typename ConcreteTypeGetter>
    constexpr explicit __farray(ConcreteTypeGetter getter):
        __data(__base::template __make<R, F, T...>(getter)) {}

    __visit_fn operator[](std::array<std::size_t, __dim> const& index) const {
        return __data[__base::__flatten_index(index)];
    }
    __visit_fn operator[](std::size_t index) const { return __data[index]; }

private:
    std::array<__visit_fn, __flat_array_size> __data;
};

} // namespace utl
