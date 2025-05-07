#pragma once

#include <bit>
#include <cstring>
#include <type_traits>

#include <utl/__base.hpp>
#include <utl/common.hpp>

namespace utl {

/// MARK: byte_swap
_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::uint16_t byte_swap(std::uint16_t val) {
    return (val << 8) | (val >> 8);
}

_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::int16_t byte_swap(std::int16_t val) {
    return (val << 8) | ((val >> 8) & 0xFF);
}

_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::uint32_t byte_swap(std::uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::int32_t byte_swap(std::int32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::uint64_t byte_swap(std::uint64_t val) {
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL) |
          ((val >> 8) & 0x00FF00FF00FF00FFULL);
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL) |
          ((val >> 16) & 0x0000FFFF0000FFFFULL);
    return (val << 32) | (val >> 32);
}

_UTL_DISABLE_UBSAN_INTEGER
constexpr inline std::int64_t byte_swap(std::int64_t val) {
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL) |
          ((val >> 8) & 0x00FF00FF00FF00FFULL);
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL) |
          ((val >> 16) & 0x0000FFFF0000FFFFULL);
    return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

} // namespace utl
