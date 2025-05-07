#ifndef UTL_PTR_UNION_HPP_
#define UTL_PTR_UNION_HPP_

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>

#include <utl/ipp.hpp>

namespace utl {

///
/// \brief A space-efficient tagged pointer union that stores a pointer along
/// with a type index.
///
/// `ptr_union<Types...>` is a type-safe union for pointers, optimized to store
/// the type index within the lower bits of the pointer itself. This avoids
/// extra storage for a separate discriminator but comes with alignment
/// constraints.
///
/// ## Design:
/// - The type index (discriminator) is encoded in the lower bits of the stored
///   pointer.
/// - This relies on the assumption that all pointer types have sufficient
///   alignment to ensure that at least `log2(sizeof...(Types))` lower bits are
///   zero.
/// - Pointers to incomplete types are allowed, meaning we **cannot** enforce
///   alignment constraints at compile time.
/// - Runtime assertions (in debug builds) check for misalignment, but in
///   release builds, misaligned pointers may cause undefined behavior.
///
/// ## Pitfalls:
/// - **Misalignment Risk:** If any of the stored pointer types is
///   insufficiently aligned, the encoded discriminator may overwrite valid
///   pointer bits, leading to corruption.
/// - **Debug-Only Checking:** Alignment assertions are only active in debug
///   builds (`assert()`).
/// - **No Compile-Time Safety for Alignment:** Since we allow incomplete types,
///   we cannot statically verify alignment, leaving this as a runtime concern.
/// - **Must Only Store Aligned Pointers:** The user is responsible for ensuring
///   that stored pointers are correctly aligned for this encoding scheme to
///   work safely.
///
/// ## Best Practices:
/// - Ensure that all stored types have at least `sizeof...(Types)` alignment.
/// - Always test in debug mode to catch potential alignment issues before
///   deployment.
///
/// \tparam Types... Pointer types to be stored in the union. Must all be
/// pointer types.
///
template <typename... Types>
requires(std::is_pointer_v<Types> && ...)
class ptr_union;

namespace __ptr_union {

template <typename T, typename... Args>
requires(... || std::same_as<T, Args>)
inline constexpr std::size_t index_of = [] {
    std::size_t index = 0;
    (void)(... || (std::same_as<T, Args> ? true : (++index, false)));
    return index;
}();

template <std::size_t I, typename... Args>
using type_at = std::tuple_element_t<I, std::tuple<Args...>>;

template <typename T, typename Union>
struct __construct_base;

template <typename T, typename... Types>
struct __construct_base<T, ptr_union<Types...>> {
    static_assert(std::is_pointer_v<T>);
    using __base = std::remove_pointer_t<T>;
    static constexpr ptr_union<Types...>::__ipp_type impl(T p) {
        return { const_cast<std::remove_cv_t<__base>*>(p),
                 index_of<T, Types...> };
    }
};

template <typename Union>
struct __construct;

template <typename... Types>
struct __construct<ptr_union<Types...>>:
    __construct_base<Types, ptr_union<Types...>>... {
    using __construct_base<Types, ptr_union<Types...>>::impl...;
};

template <typename T, typename Union>
concept __convertible_to = requires(T* p) { __construct<Union>::impl(p); };

} // namespace __ptr_union

// MARK: Visitation

namespace __ptr_union {

enum class __deduce_return_type_tag : int;

template <typename R, typename Vis, typename... Types>
struct __vis_return_type: std::type_identity<R> {};

template <typename Vis, typename... Types>
struct __vis_return_type<__deduce_return_type_tag, Vis, Types...>:
    std::common_reference<std::invoke_result_t<Vis, Types>...> {};

template <typename R, typename Vis, typename... Types>
using __vis_return_type_t = __vis_return_type<R, Vis, Types...>::type;

template <typename T, typename R, typename Vis>
inline constexpr auto __vis_case = +[](Vis&& vis, void* arg) -> R {
    return std::invoke((Vis&&)vis, static_cast<T>(arg));
};

[[noreturn]] inline void unreachable() {
#if defined(__GNUC__)
    __builtin_unreachable();
#else
    assert(false);
#endif
}

} // namespace __ptr_union

template <typename R = __ptr_union::__deduce_return_type_tag, typename Visitor,
          typename... Types>
constexpr __ptr_union::__vis_return_type_t<R, Visitor, Types...>
visit(ptr_union<Types...> u, Visitor&& visitor) {
    using namespace __ptr_union;
    using __union = ptr_union<Types...>;
    using __ret = __vis_return_type_t<R, Visitor, Types...>;
    if constexpr (__union::__num_types > 10) {
        constexpr auto array =
            [&]<std::size_t... I>(std::index_sequence<I...>) {
            return std::array{
                __vis_case<type_at<I, Types...>, __ret, Visitor>...
            };
        }(std::make_index_sequence<__union::__num_types>{});
        return array[u.index()]((Visitor&&)visitor, u.__value.pointer());
    }
    else {
#define UTL_PTR_UNION_SWITCH_CASE(N)                                           \
    case N:                                                                    \
        if constexpr (N < __union::__num_types) {                              \
            using T = type_at<N, Types...>;                                    \
            return std::invoke((Visitor&&)visitor,                             \
                               static_cast<T>(u.__value.pointer()));           \
        }                                                                      \
        else {                                                                 \
            __ptr_union::unreachable();                                        \
        }
        switch (u.index()) {
            UTL_PTR_UNION_SWITCH_CASE(0);
            UTL_PTR_UNION_SWITCH_CASE(1);
            UTL_PTR_UNION_SWITCH_CASE(2);
            UTL_PTR_UNION_SWITCH_CASE(3);
            UTL_PTR_UNION_SWITCH_CASE(4);
            UTL_PTR_UNION_SWITCH_CASE(5);
            UTL_PTR_UNION_SWITCH_CASE(6);
            UTL_PTR_UNION_SWITCH_CASE(7);
            UTL_PTR_UNION_SWITCH_CASE(8);
            UTL_PTR_UNION_SWITCH_CASE(9);
        default: __ptr_union::unreachable();
        }
#undef UTL_PTR_UNION_SWITCH_CASE
    }
}

template <typename... Types>
class ptr_union<Types*...> {
public:
    static_assert(sizeof...(Types) > 0, "Empty ptr_union is ill-formed");
    static constexpr std::size_t __num_types = sizeof...(Types);
    static constexpr std::size_t __log2_num_types = std::bit_width(__num_types);

    using __ipp_type = ipp<void*, unsigned, __log2_num_types>;

    __ipp_type __value;

    constexpr ptr_union(std::nullptr_t = nullptr) noexcept:
        __value(nullptr, 0) {}

    template <__ptr_union::__convertible_to<ptr_union> T>
    constexpr ptr_union(T* p) noexcept:
        __value(__ptr_union::__construct<ptr_union>::impl(p)) {}

    template <std::size_t I, typename T = __ptr_union::type_at<I, Types...>>
    requires(I < __num_types)
    constexpr explicit ptr_union(std::in_place_index_t<I>, T* p):
        __value(const_cast<std::remove_cv_t<T>*>(p), I) {}

    constexpr std::size_t index() const noexcept { return __value.integer(); }

    template <std::size_t I>
    requires(I < __num_types)
    constexpr __ptr_union::type_at<I, Types*...> get() const {
        __utl_assert(index() == I);
        return static_cast<__ptr_union::type_at<I, Types*...>>(
            __value.pointer());
    }

    template <typename T>
    requires requires { __ptr_union::index_of<T, Types*...>; }
    constexpr T get() const {
        constexpr std::size_t I = __ptr_union::index_of<T, Types*...>;
        return this->template get<I>();
    }

    template <std::size_t I>
    requires(I < __num_types)
    constexpr __ptr_union::type_at<I, Types*...> try_get() const {
        return index() == I ? this->template get<I>() : nullptr;
    }

    template <typename T>
    requires requires { __ptr_union::index_of<T, Types*...>; }
    constexpr T try_get() const {
        constexpr std::size_t I = __ptr_union::index_of<T, Types*...>;
        return this->template try_get<I>();
    }

    template <typename R = __ptr_union::__deduce_return_type_tag,
              typename Visitor>
    constexpr __ptr_union::__vis_return_type_t<R, Visitor, Types*...>
    visit(Visitor&& visitor) {
        return utl::visit(*this, (Visitor&&)visitor);
    }

    template <typename R = __ptr_union::__deduce_return_type_tag,
              typename Visitor>
    constexpr __ptr_union::__vis_return_type_t<R, Visitor, Types*...>
    visit(Visitor&& visitor) const {
        return utl::visit(*this, (Visitor&&)visitor);
    }
};

template <typename T>
struct ptr_union_size; // undefined

template <typename T>
inline constexpr std::size_t ptr_union_size_v = ptr_union_size<T>::value;

template <typename T>
struct ptr_union_size<T const>: ptr_union_size<T> {};

template <typename... Types>
struct ptr_union_size<ptr_union<Types...>>:
    std::integral_constant<std::size_t, sizeof...(Types)> {};

template <std::size_t I, class T>
struct ptr_union_alternative; // undefined

template <std::size_t I, class T>
using ptr_union_alternative_t = typename ptr_union_alternative<I, T>::type;

template <std::size_t I, class T>
struct ptr_union_alternative<I, T const>:
    std::type_identity<ptr_union_alternative_t<I, T> const> {};

template <std::size_t I, typename... Types>
struct ptr_union_alternative<I, ptr_union<Types...>>:
    std::type_identity<__ptr_union::type_at<I, Types...>> {};

template <typename T, typename... Types>
requires requires { __ptr_union::index_of<T, Types...>; }
constexpr bool holds_alternative(ptr_union<Types...> const& u) noexcept {
    return u.index() == __ptr_union::index_of<T, Types...>;
}

template <std::size_t I, typename... Types>
requires(I < sizeof...(Types))
constexpr ptr_union_alternative_t<I, ptr_union<Types...>>
get(ptr_union<Types...> u) noexcept {
    return u.template get<I>();
}

template <typename T, typename... Types>
requires requires { __ptr_union::index_of<T, Types...>; }
constexpr T get(ptr_union<Types...> u) noexcept {
    return u.template get<T>();
}

template <std::size_t I, typename... Types>
requires(I < sizeof...(Types))
constexpr ptr_union_alternative_t<I, ptr_union<Types...>>
try_get(ptr_union<Types...> u) noexcept {
    return u.template try_get<I>();
}

template <typename T, typename... Types>
requires requires { __ptr_union::index_of<T, Types...>; }
constexpr T try_get(ptr_union<Types...> u) noexcept {
    return u.template try_get<T>();
}

template <typename... Types>
constexpr bool operator==(ptr_union<Types...> a, ptr_union<Types...> b) {
    return std::bit_cast<std::uintptr_t>(a) == std::bit_cast<std::uintptr_t>(b);
}

template <typename... Types>
constexpr std::strong_ordering operator<=>(ptr_union<Types...> a,
                                           ptr_union<Types...> b) {
    return std::bit_cast<std::uintptr_t>(a) <=>
           std::bit_cast<std::uintptr_t>(b);
}

} // namespace utl

template <typename... Types>
struct std::hash<utl::ptr_union<Types...>> {
    constexpr std::size_t operator()(utl::ptr_union<Types...> u) const {
        return std::hash<std::uintptr_t>{}(std::bit_cast<std::uintptr_t>(u));
    }
};

#endif // UTL_PTR_UNION_HPP_
