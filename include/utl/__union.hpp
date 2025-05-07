#pragma once

#include <utl/__base.hpp>
#include <utl/common.hpp>
#include <utl/type_traits.hpp>

namespace utl {

template <typename...>
union __union_impl;

template <>
union __union_impl<> {};

template <typename T0>
union __union_impl<T0> {
    T0 __t0;
};

template <typename T0, typename T1>
union __union_impl<T0, T1> {
    T0 __t0;
    T1 __t1;
};

template <typename T0, typename T1, typename T2>
union __union_impl<T0, T1, T2> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
};

template <typename T0, typename T1, typename T2, typename T3>
union __union_impl<T0, T1, T2, T3> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
    T3 __t3;
};

template <typename T0, typename T1, typename T2, typename T3, typename T4>
union __union_impl<T0, T1, T2, T3, T4> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
    T3 __t3;
    T4 __t4;
};

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5>
union __union_impl<T0, T1, T2, T3, T4, T5> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
    T3 __t3;
    T4 __t4;
    T5 __t5;
};

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
union __union_impl<T0, T1, T2, T3, T4, T5, T6> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
    T3 __t3;
    T4 __t4;
    T5 __t5;
    T6 __t6;
};

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename... TR>
union __union_impl<T0, T1, T2, T3, T4, T5, T6, T7, TR...> {
    T0 __t0;
    T1 __t1;
    T2 __t2;
    T3 __t3;
    T4 __t4;
    T5 __t5;
    T6 __t6;
    T7 __t7;
    __union_impl<TR...> __tr;
};

template <std::size_t I, typename V>
constexpr decltype(auto) __union_impl_get(V&& v) {
    if constexpr (I == 0) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t0)>>(v.__t0);
    }
    else if constexpr (I == 1) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t1)>>(v.__t1);
    }
    else if constexpr (I == 2) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t2)>>(v.__t2);
    }
    else if constexpr (I == 3) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t3)>>(v.__t3);
    }
    else if constexpr (I == 4) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t4)>>(v.__t4);
    }
    else if constexpr (I == 5) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t5)>>(v.__t5);
    }
    else if constexpr (I == 6) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t6)>>(v.__t6);
    }
    else if constexpr (I == 7) {
        return static_cast<copy_cvref_t<V&&, decltype(v.__t7)>>(v.__t7);
    }
    else {
        return __union_impl_get<I - 8>(std::forward<V>(v).__tr);
    }
}

template <bool DefCtor, bool CopyCtor, bool MoveCtor, bool CopyAssign,
          bool MoveAssign, bool Dtor>
struct __union_traits_impl;

template <typename Traits, typename... T>
struct __union_base;

#define _UTL_UNION_BASE_DEF(DefCtor, CopyCtor, MoveCtor, CopyAssign,           \
                            MoveAssign, Dtor, ...)                             \
    template <typename... T>                                                   \
    struct __union_base<__VA_ARGS__, T...> {                                   \
        DefCtor CopyCtor MoveCtor CopyAssign MoveAssign Dtor union {           \
            __union_impl<T...> __impl;                                         \
        };                                                                     \
    }

#define _UTL_TRIV_CTOR __union_base() = default;
#define _UTL_CTOR                                                              \
    __union_base() {}
#define _UTL_TRIV_COPYCT __union_base(__union_base const&) = default;
#define _UTL_COPYCT                                                            \
    __union_base(__union_base const&) {}
#define _UTL_TRIV_MOVECT __union_base(__union_base&&) = default;
#define _UTL_MOVECT                                                            \
    __union_base(__union_base&&) {}
#define _UTL_TRIV_COPYAS __union_base& operator=(__union_base const&) = default;
#define _UTL_COPYAS                                                            \
    __union_base& operator=(__union_base const&) {                             \
        return *this;                                                          \
    }
#define _UTL_TRIV_MOVEAS __union_base& operator=(__union_base&&) = default;
#define _UTL_MOVEAS                                                            \
    __union_base& operator=(__union_base&&) {                                  \
        return *this;                                                          \
    }
#define _UTL_TRIV_DTOR ~__union_base() = default;
#define _UTL_DTOR                                                              \
    ~__union_base() {}

_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 1, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 1, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 1, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 1, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 0, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 0, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 0, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 0, 1, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_COPYAS, _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 1, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 1, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 1, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 1, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 0, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 0, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 0, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 0, 0, 1, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 1, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 1, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 1, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 1, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 0, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 0, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 0, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 0, 1, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_COPYAS, _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 1, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 1, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 1, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 1, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 1, 0, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 1, 0, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<1, 0, 0, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_TRIV_DTOR,
                    __union_traits_impl<0, 0, 0, 0, 0, 1>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 1, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 1, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 1, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 1, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 0, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 0, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 0, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 0, 1, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_COPYAS, _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 1, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 1, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 1, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 1, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 0, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 0, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 0, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_TRIV_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 0, 0, 1, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 1, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 1, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 1, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 1, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT,
                    _UTL_TRIV_COPYAS, _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 0, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 0, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 0, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_TRIV_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 0, 1, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT,
                    _UTL_COPYAS, _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 1, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 1, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 1, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_TRIV_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 1, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 1, 0, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_TRIV_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 1, 0, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_TRIV_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<1, 0, 0, 0, 0, 0>);
_UTL_UNION_BASE_DEF(_UTL_CTOR, _UTL_COPYCT, _UTL_MOVECT, _UTL_COPYAS,
                    _UTL_MOVEAS, _UTL_DTOR,
                    __union_traits_impl<0, 0, 0, 0, 0, 0>);

#undef _UTL_UNION_BASE_DEF
#undef _UTL_TRIV_CTOR
#undef _UTL_CTOR
#undef _UTL_TRIV_COPYCT
#undef _UTL_COPYCT
#undef _UTL_TRIV_MOVECT
#undef _UTL_MOVECT
#undef _UTL_TRIV_COPYAS
#undef _UTL_COPYAS
#undef _UTL_TRIV_MOVEAS
#undef _UTL_MOVEAS
#undef _UTL_TRIV_DTOR
#undef _UTL_DTOR

template <typename... T>
using __union_traits = __union_traits_impl<
    std::conjunction_v<std::is_trivially_default_constructible<T>...>,
    std::conjunction_v<std::is_trivially_copy_constructible<T>...>,
    std::conjunction_v<std::is_trivially_move_constructible<T>...>,
    std::conjunction_v<std::is_trivially_copy_assignable<T>...>,
    std::conjunction_v<std::is_trivially_move_assignable<T>...>,
    std::conjunction_v<std::is_trivially_destructible<T>...>>;

template <typename... T>
struct __union: __union_base<__union_traits<T...>, T...> {};

template <std::size_t I, typename... T>
constexpr decltype(auto) get(__union<T...> const& u) {
    return __union_impl_get<I>(u.__impl);
}

template <std::size_t I, typename... T>
constexpr decltype(auto) get(__union<T...>& u) {
    return __union_impl_get<I>(u.__impl);
}

template <std::size_t I, typename... T>
constexpr decltype(auto) get(__union<T...> const&& u) {
    return __union_impl_get<I>(std::move(u.__impl));
}

template <std::size_t I, typename... T>
constexpr decltype(auto) get(__union<T...>&& u) {
    return __union_impl_get<I>(std::move(u.__impl));
}

} // namespace utl
