#ifndef UTL_IPP_HPP_
#define UTL_IPP_HPP_

#include <bit>
#include <concepts>
#include <memory> // For std::hash

#include <utl/__base.hpp>
#include <utl/__debug.hpp>

namespace utl {

/// Int pointer pair
/// Stores the integer in the low bits of the pointer.
///
/// \param Pointer Any pointer type. Alignment of pointee type must be at least
/// `2 ** NumIntBits`. The alignment requirement is not checked at compile time
/// to allow the pointee type to be incomplete
///
/// \param IntType Must be unsigned integer or enum type. No sign extension is
/// performed when loading the integer
///
/// \param NumIntBits The number of lower bits of the pointer that are reserved
/// for storing the integer. Every pointer stored in an instance of this class
/// must satisfy alignment requirement accordingly
template <typename Pointer, typename IntType, size_t NumIntBits>
class ipp;

template <typename Pointee, typename IntType, size_t NumIntBits>
class ipp<Pointee*, IntType, NumIntBits> {
public:
    static_assert(std::is_unsigned_v<IntType> || std::is_enum_v<IntType>,
                  "See documentation");

    using pointer_type = Pointee*;

    using int_type = IntType;

    using raw_int_type = std::uintptr_t;

    static constexpr size_t num_int_bits = NumIntBits;

    static constexpr raw_int_type pointer_mask = ~raw_int_type(0)
                                                 << num_int_bits;
    static constexpr raw_int_type int_mask = ~pointer_mask;
    static constexpr raw_int_type high_bit_mask =
        (pointer_mask >> 1) & int_mask;

    /// \Returns the largest integer value that can be stored in this class
    static constexpr raw_int_type max_int() { return int_mask; }

    /// \Returns the smallest integer value that can be stored in this class
    static constexpr raw_int_type min_int() { return 0; }

    /// Sets both values to zero
    ipp() = default;

    /// Construct from an integer and a pointer
    constexpr ipp(pointer_type ptr, int_type value) {
        set_integer(value);
        set_pointer(ptr);
    }

    /// Construct from a pointer and set the integer value to zero
    constexpr explicit ipp(pointer_type ptr): ipp(ptr, int_type{}) {}

    /// Construct from an integer and set the pointer to null
    constexpr explicit ipp(int_type value): ipp(nullptr, value) {}

    /// Access the integer stored in the pair
    constexpr int_type integer() const {
        return (int_type)((raw_int_type)_m_ptr & int_mask);
    }

    /// Access the pointer stored in the pair
    constexpr pointer_type pointer() const {
        return (pointer_type)((raw_int_type)_m_ptr & pointer_mask);
    }

    /// Set the stored integer to \p value
    constexpr void set_integer(int_type value) {
        __utl_assert((raw_int_type)value >= min_int());
        __utl_assert((raw_int_type)value <= max_int());
        _m_ptr = (pointer_type)((raw_int_type)value | (raw_int_type)pointer());
    }

    /// Set the stored pointer to \p ptr
    constexpr void set_pointer(pointer_type ptr) {
        __utl_assert(std::countr_zero((raw_int_type)ptr) >= num_int_bits &&
                     "Invalidly aligned pointer");
        _m_ptr = (pointer_type)((raw_int_type)integer() | (raw_int_type)ptr);
    }

    /// The raw packed value
    std::uintptr_t raw_value() const {
        return reinterpret_cast<std::uintptr_t>(_m_ptr);
    }

    constexpr bool operator==(ipp const& rhs) const = default;

private:
    pointer_type _m_ptr = nullptr;
};

template <size_t I, typename Pointer, typename IntType, size_t NumBits>
constexpr auto get(ipp<Pointer, IntType, NumBits> p) {
    if constexpr (I == 0) {
        return p.integer();
    }
    else {
        static_assert(I == 1);
        return p.pointer();
    }
}

} // namespace utl

template <typename Pointer, typename IntType, size_t NumBits>
struct std::tuple_size<utl::ipp<Pointer, IntType, NumBits>>:
    std::integral_constant<std::size_t, 2> {};

template <typename Pointer, typename IntType, size_t NumBits>
struct std::tuple_element<0, utl::ipp<Pointer, IntType, NumBits>>:
    std::type_identity<typename utl::ipp<Pointer, IntType, NumBits>::int_type> {
};

template <typename Pointer, typename IntType, size_t NumBits>
struct std::tuple_element<1, utl::ipp<Pointer, IntType, NumBits>>:
    std::type_identity<
        typename utl::ipp<Pointer, IntType, NumBits>::pointer_type> {};

template <typename Pointer, typename IntType, size_t NumIntBits>
struct std::hash<utl::ipp<Pointer, IntType, NumIntBits>> {
    size_t operator()(utl::ipp<Pointer, IntType, NumIntBits> arg) const {
        return std::hash<uintptr_t>{}(arg.raw_value());
    }
};

#endif // UTL_IPP_HPP_
