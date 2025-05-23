#ifndef UTL___FUNCTION_OBJECTS_HPP_
#define UTL___FUNCTION_OBJECTS_HPP_

#include <algorithm>
#include <cmath>

#include <utl/__base.hpp>
#include <utl/common.hpp>
#include <utl/math.hpp>
#include <utl/type_traits.hpp>

#define _UTL_FUNCTION_OBJECT_DEF(obj_name, impl)                               \
    struct obj_name##_t {                                                      \
        [[nodiscard]] constexpr auto operator() impl                           \
    } inline constexpr obj_name {                                              \
    }

#define _UTL_BIN_FUNCTION_OBJECT_DEF(obj_name, operator_name, op, extendDef)   \
    struct obj_name##_t {                                                      \
        template <typename T, typename U>                                      \
        requires requires(T&& a, U&& b) {                                      \
            UTL_FORWARD(a)                                                     \
            op UTL_FORWARD(b);                                                 \
        }                                                                      \
        [[nodiscard]] constexpr auto operator()(T&& a, U&& b) const {          \
            return UTL_FORWARD(a) op UTL_FORWARD(b);                           \
        }                                                                      \
        template <class T, class U, class... V>                                \
        requires(extendDef)                                                    \
        [[nodiscard]] constexpr auto operator()(T&& a, U&& b,                  \
                                                V&&... c) const {              \
            auto result = (a op b);                                            \
            ((result = (result op c)), ...);                                   \
            return result;                                                     \
        }                                                                      \
    } inline constexpr obj_name {                                              \
    }

namespace utl {
struct plus_t {
    template <typename T>
    requires requires(T&& t) { +t; }
    [[nodiscard]] constexpr auto operator()(T&& a) const {
        return +UTL_FORWARD(a);
    }
    template <typename T, typename U>
    requires requires(T&& t, U&& u) { t + u; }
    [[nodiscard]] constexpr auto operator()(T&& a, U&& b) const {
        return UTL_FORWARD(a) + UTL_FORWARD(b);
    }
    template <class T, class U, class... V>
    [[nodiscard]] constexpr auto operator()(T&& a, U&& b, V&&... c) const {
        auto result = (a + b);
        ((result = (result + c)), ...);
        return result;
    }
} inline constexpr plus{};
struct minus_t {
    template <typename T>
    requires requires(T&& t) { -t; }
    [[nodiscard]] constexpr auto operator()(T&& a) const {
        return -UTL_FORWARD(a);
    }
    template <typename T, typename U>
    requires requires(T&& t, U&& u) { t - u; }
    [[nodiscard]] constexpr auto operator()(T&& a, U&& b) const {
        return UTL_FORWARD(a) - UTL_FORWARD(b);
    }
} inline constexpr minus{};

_UTL_FUNCTION_OBJECT_DEF(logical_not, (auto const& x) const { return !x; });

_UTL_FUNCTION_OBJECT_DEF(bitwise_not, (auto const& x) const { return ~x; });

_UTL_FUNCTION_OBJECT_DEF(negate, (auto const& x) const { return -x; });

_UTL_BIN_FUNCTION_OBJECT_DEF(multiplies, multiply, *, true);
_UTL_BIN_FUNCTION_OBJECT_DEF(divides, divide, /, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(modulo, modulo, %, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(equals, equals, ==, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(less, less, <, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(less_eq, less_eq, <=, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(greater, greater, >, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(greater_eq, greater_eq, >=, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(unequals, unequals, !=, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(logical_and, logical_and, &&, true);
_UTL_BIN_FUNCTION_OBJECT_DEF(logical_or, logical_or, ||, true);
_UTL_BIN_FUNCTION_OBJECT_DEF(leftshift, leftshift, <<, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(rightshift, rightshift, >>, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(bitwise_and, bitwise_and, &, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(bitwise_or, bitwise_or, |, false);
_UTL_BIN_FUNCTION_OBJECT_DEF(bitwise_xor, bitwise_xor, ^, false);

#undef _UTL_BIN_FUNCTION_OBJECT_DEF

namespace __utl_function_objects_impl {

template <typename T>
requires std::is_arithmetic_v<T>
[[nodiscard]] constexpr auto signed_sqrt(T x) {
    if (std::signbit(x)) {
        return -std::sqrt(-x);
    }
    else {
        return std::sqrt(x);
    }
}

template <typename T, typename U>
requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr auto signed_pow(T x, U y) {
    if (std::signbit(x)) {
        return -std::pow(-x, y);
    }
    else {
        return std::pow(x, y);
    }
}

[[nodiscard]] constexpr auto ceil_divide(std::integral auto a,
                                         std::integral auto b) {
    __utl_expect(a >= 0);
    __utl_expect(b >= 0);
    return (a / b) + !!(a % b);
}

[[nodiscard]] constexpr auto ceil_divide_pow_two(std::integral auto a,
                                                 std::integral auto b) {
    __utl_expect(a >= 0);
    __utl_expect(b >= 0);
    return fast_div_pow_two(a, b) + !!fast_mod_pow_two(a, b);
}

[[nodiscard]] constexpr auto fract(std::floating_point auto f) {
    decltype(f) i;
    auto const result = std::modf(f, &i);
    return (result < 0) + result;
}

[[nodiscard]] constexpr auto mod(std::floating_point auto f,
                                 std::floating_point auto r) {
    return fract(f / r) * r;
}
} // namespace __utl_function_objects_impl

_UTL_FUNCTION_OBJECT_DEF(abs, (auto const& x) const {
    using ::std::abs;
    return abs(x);
});

_UTL_FUNCTION_OBJECT_DEF(sqrt, (auto const& x) const {
    using ::std::sqrt;
    return sqrt(x);
});

_UTL_FUNCTION_OBJECT_DEF(signed_sqrt, (auto const& x) const {
    using __utl_function_objects_impl::signed_sqrt;
    return signed_sqrt(x);
});

_UTL_FUNCTION_OBJECT_DEF(signed_pow, (auto const& x, auto const& y) const {
    using __utl_function_objects_impl::signed_pow;
    return signed_pow(x, y);
});

_UTL_FUNCTION_OBJECT_DEF(exp, (auto const& x) const {
    using ::std::exp;
    return exp(x);
});

_UTL_FUNCTION_OBJECT_DEF(min, (auto const& x, auto const& y) const {
    using ::std::min;
    return min(x, y);
});
_UTL_FUNCTION_OBJECT_DEF(max, (auto const& x, auto const& y) const {
    using ::std::max;
    return max(x, y);
});

_UTL_FUNCTION_OBJECT_DEF(screen_blend, (auto const& x, auto const& y) const {
    return 1 - (1 - x) * (1 - y);
});

_UTL_FUNCTION_OBJECT_DEF(one_minus, (auto const& x) const { return 1 - x; });

_UTL_FUNCTION_OBJECT_DEF(ceil_divide, (auto const& x, auto const& y) const {
    using __utl_function_objects_impl::ceil_divide;
    return ceil_divide(x, y);
});

_UTL_FUNCTION_OBJECT_DEF(ceil_divide_pow_two, (auto const& x,
                                               auto const& y) const {
    using __utl_function_objects_impl::ceil_divide_pow_two;
    return ceil_divide_pow_two(x, y);
});

_UTL_FUNCTION_OBJECT_DEF(floor, (auto const& x) const {
    using std::floor;
    return floor(x);
});

_UTL_FUNCTION_OBJECT_DEF(ceil, (auto const& x) const {
    using std::ceil;
    return ceil(x);
});

_UTL_FUNCTION_OBJECT_DEF(fract, (auto const& x) const {
    using __utl_function_objects_impl::fract;
    return fract(x);
});

_UTL_FUNCTION_OBJECT_DEF(mod, (auto const& x, auto const& y) const {
    using __utl_function_objects_impl::mod;
    return mod(x, y);
});

_UTL_FUNCTION_OBJECT_DEF(arithmetic_leftshift, (auto const& x, auto const& y)
                                                   const { return x << y; });

_UTL_FUNCTION_OBJECT_DEF(arithmetic_rightshift, (auto const& x,
                                                 auto const& y) const {
    using S = std::make_signed_t<std::remove_cvref_t<decltype(x)>>;
    if (S(x) < 0 && y > 0)
        return S(x) >> y | ~(~S(0) >> y);
    else
        return S(x) >> y;
});

_UTL_FUNCTION_OBJECT_DEF(is_positive, (auto const& x) const { return x > 0; });
_UTL_FUNCTION_OBJECT_DEF(is_non_positive,
                         (auto const& x) const { return x <= 0; });
_UTL_FUNCTION_OBJECT_DEF(is_negative, (auto const& x) const { return x < 0; });
_UTL_FUNCTION_OBJECT_DEF(is_non_negative,
                         (auto const& x) const { return x >= 0; });

_UTL_FUNCTION_OBJECT_DEF(identity, (auto&& x) const->decltype(auto) {
    return UTL_FORWARD(x);
});

_UTL_FUNCTION_OBJECT_DEF(deref,
                         (auto&& x) const->decltype(auto) { return *x; });

_UTL_FUNCTION_OBJECT_DEF(noop, (auto&&...) const {

                               });

} // namespace utl

#endif // UTL___FUNCTION_OBJECTS_HPP_
