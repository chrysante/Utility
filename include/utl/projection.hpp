#ifndef UTL_PROJECTION_HPP_
#define UTL_PROJECTION_HPP_

#include <utl/__base.hpp>
#include <utl/hash.hpp>

namespace utl {

namespace __proj {

template <typename T, auto MemAcc>
using mem_type = std::invoke_result_t<decltype(MemAcc), T>;

template <typename T, auto MemAcc>
using mem_type_no_cvref = std::remove_cvref_t<mem_type<T, MemAcc>>;

} // namespace __proj

template <typename T, auto... MemAcc>
struct projection_hash;

template <typename T, auto MemAcc>
struct projection_hash<T, MemAcc>: hash<__proj::mem_type_no_cvref<T, MemAcc>> {
    using is_transparent = void;

    using base = hash<__proj::mem_type_no_cvref<T, MemAcc>>;

    using base::operator();

    size_t operator()(T const& arg) const {
        return (*this)(std::invoke(MemAcc, arg));
    }
};

template <typename T, auto... MemAcc>
requires(sizeof...(MemAcc) > 1)
struct projection_hash<T, MemAcc...> {
    using is_transparent = void;

    size_t operator()(T const& arg) const {
        return utl::hash_combine(std::invoke(MemAcc, arg)...);
    }
};

template <auto>
struct member_hash;
template <typename Class, typename Elem, Elem Class::* member>
struct member_hash<member>: projection_hash<Class, member> {};
template <typename Class, typename Elem, Elem (Class::*member)()>
struct member_hash<member>: projection_hash<Class, member> {};

template <typename T, auto... MemAcc>
struct projection_equal_to;

template <typename T, auto MemAcc>
struct projection_equal_to<T, MemAcc> {
    using is_transparent = void;

    using mem_type = __proj::mem_type<T, MemAcc>;

    bool operator()(T const& lhs, T const& rhs) const {
        return std::equal_to<>{}(std::invoke(MemAcc, lhs),
                                 std::invoke(MemAcc, rhs));
    }

    template <std::equality_comparable_with<mem_type> RHS>
    bool operator()(T const& lhs, RHS const& rhs) const {
        return std::equal_to<>{}(std::invoke(MemAcc, lhs), rhs);
    }

    template <std::equality_comparable_with<mem_type> LHS>
    bool operator()(LHS const& lhs, T const& rhs) const {
        return std::equal_to<>{}(lhs, std::invoke(MemAcc, rhs));
    }
};

template <typename T, auto... MemAcc>
requires(sizeof...(MemAcc) > 1)
struct projection_equal_to<T, MemAcc...> {
    using is_transparent = void;

    bool operator()(T const& lhs, T const& rhs) const {
        return ((std::invoke(MemAcc, lhs) == std::invoke(MemAcc, rhs)) && ...);
    }
};

template <auto>
struct member_equal_to;

template <typename Class, typename Elem, Elem Class::* member>
struct member_equal_to<member>: projection_equal_to<Class, member> {};
template <typename Class, typename Elem, Elem (Class::*member)()>
struct member_equal_to<member>: projection_equal_to<Class, member> {};

} // namespace utl

#endif // UTL_PROJECTION_HPP_
