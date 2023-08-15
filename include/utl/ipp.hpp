#pragma once

#include <concepts>
#include <bit>

#include "__base.hpp"
#include "__debug.hpp"

namespace utl {

/// Int pointer pair
/// Stores the integer in the low bits of the pointer.
/// Size of the integer depends on the alignment of `T`
template <typename T, bool Signed = false>
struct ipp;

/// Signed integer pointer pair
template <typename T>
using sipp = ipp<T, true>;

template <typename T, bool Signed>
struct ipp<T*, Signed> {
    using int_type = std::conditional_t<Signed, std::intptr_t, std::uintptr_t>;
    
    using pointer_type = T*;
    
    using __uint_type = std::make_unsigned_t<int_type>;
    
    static constexpr std::size_t __num_int_bits = std::countr_zero(alignof(T));
    static constexpr __uint_type __ptr_mask = ~__uint_type(0) << __num_int_bits;
    static constexpr __uint_type __int_mask = ~__ptr_mask;
    static constexpr __uint_type __high_bit_mask = (__ptr_mask >> 1) & __int_mask;
    
    static constexpr int_type max_int() {
        if constexpr (Signed) {
            return (int_type)(__int_mask >> 1);
        }
        else {
            return __int_mask;
        }
    }
    
    static constexpr int_type min_int() {
        if constexpr (Signed) {
            return (int_type)(__ptr_mask | __high_bit_mask);
        }
        else {
            return 0;
        }
    }
    
    ipp() = default;
    
    constexpr ipp(int_type value, pointer_type ptr = nullptr) {
        set_integer(value);
        set_pointer(ptr);
    }
    
    constexpr ipp(pointer_type ptr) {
        __ptr = nullptr;
        set_pointer(ptr);
    }
    
    /// Access the integer stored in the pair
    constexpr int_type integer() const {
        if constexpr (Signed) {
            return (int_type)(__get_int() | ((int_type)__get_int() & __high_bit_mask ? __ptr_mask : 0));
        }
        else {
            return __get_int();
        }
    }
    
    /// Access the pointer stored in the pair
    constexpr pointer_type pointer() const {
        return (pointer_type)((__uint_type)__ptr & __ptr_mask);
    }
    
    /// Set the stored integer to \p value
    constexpr void set_integer(int_type value) {
        __utl_assert(value >= min_int());
        __utl_assert(value <= max_int());
        __ptr = (pointer_type)((__uint_type)value | (__uint_type)pointer());
    }
    
    /// Set the stored pointer to \p ptr
    constexpr void set_pointer(pointer_type ptr) {
        __utl_assert(std::countr_zero((__uint_type)ptr) >= __num_int_bits);
        __ptr = (pointer_type)((__uint_type)__get_int() | (__uint_type)ptr);
    }
    
    constexpr __uint_type __get_int() const {
        return (__uint_type)__ptr & __int_mask;
    }
    
    pointer_type __ptr;
};

template <size_t I, typename T, bool Signed>
constexpr auto get(ipp<T*, Signed> p) {
    if constexpr (I == 0) {
        return p.integer();
    }
    else {
        static_assert(I == 2);
        return p.pointer();
    }
}

/// Enum pointer pair
template <typename Enum, typename Pointer>
requires std::is_enum_v<Enum> && std::is_pointer_v<Pointer>
struct epp {
    static constexpr bool __Signed = std::is_signed_v<std::underlying_type_t<Enum>>;
    
    using enum_type = Enum;
    
    using int_type = typename ipp<Pointer, __Signed>::int_type;
    
    using pointer_type = typename ipp<Pointer, __Signed>::pointer_type;
    
    epp() = default;
    
    constexpr epp(enum_type value, pointer_type ptr = nullptr): __impl((int_type)value, ptr) {}
    
    constexpr epp(pointer_type ptr): __impl(ptr) {}
    
    /// Access the integer stored in the pair
    constexpr enum_type enum_value() const {
        return (enum_type)__impl.integer();
    }
    
    /// Access the pointer stored in the pair
    constexpr pointer_type pointer() const {
        return __impl.pointer();
    }
    
    /// Set the stored integer to \p value
    constexpr void set_enum(enum_type value) {
        __impl.set_integer((int_type)value);
    }
    
    /// Set the stored pointer to \p ptr
    constexpr void set_pointer(pointer_type ptr) {
        __impl.set_pointer(ptr);
    }
    
    ipp<pointer_type, __Signed> __impl;
};

template <size_t I, typename E, typename P>
constexpr auto get(epp<E, P> p) {
    if constexpr (I == 0) {
        return p.enum_value();
    }
    else {
        static_assert(I == 2);
        return p.pointer();
    }
}

} // namespace utl

template <typename T, bool Signed>
struct std::tuple_size<utl::ipp<T*, Signed>>:
    std::integral_constant<std::size_t, 2> {};

template <typename T, bool Signed>
struct std::tuple_element<0, utl::ipp<T*, Signed>>:
    std::type_identity<typename utl::ipp<T*, Signed>::int_type> {};

template <typename T, bool Signed>
struct std::tuple_element<1, utl::ipp<T*, Signed>>:
    std::type_identity<typename utl::ipp<T*, Signed>::pointer_type> {};

template <typename E, typename P>
struct std::tuple_size<utl::epp<E, P>>:
    std::integral_constant<std::size_t, 2> {};

template <typename E, typename P>
struct std::tuple_element<0, utl::epp<E, P>>:
    std::type_identity<typename utl::epp<E, P>::enum_type> {};

template <typename E, typename P>
struct std::tuple_element<1, utl::epp<E, P>>:
    std::type_identity<typename utl::epp<E, P>::pointer_type> {};
