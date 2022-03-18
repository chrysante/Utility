#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "common.hpp"

#include <type_traits>
#include <bit>
#include <cstring>


namespace utl {
	
	/// MARK: bit_cast
	template<typename To, typename From,
			 UTL_ENABLE_IF(sizeof(To) == sizeof(From)),
			 UTL_ENABLE_IF(std::is_trivially_copyable<To>::value),
			 UTL_ENABLE_IF(std::is_trivially_copyable<From>::value)>
	constexpr To bit_cast(From const& from) noexcept {
#if defined(__cpp_lib_bit_cast)
		return std::bit_cast<To>(from);
#else
		typename std::aligned_storage<sizeof(To), alignof(To)>::type storage;
		std::memcpy(&storage, &from, sizeof(To));
		return reinterpret_cast<To&>(storage);
#endif
	}
	
	/// MARK: unsafe_bit_cast
	template<typename To, typename From,
			 UTL_ENABLE_IF(sizeof(To) == sizeof(From))>
	constexpr To unsafe_bit_cast(From const& from) noexcept {
		typename std::aligned_storage<sizeof(To), alignof(To)>::type storage;
		std::memcpy(&storage, &from, sizeof(To));
		return reinterpret_cast<To&>(storage);
	}
	
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
		val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
		return (val << 16) | (val >> 16);
	}
	
	_UTL_DISABLE_UBSAN_INTEGER
	constexpr inline std::int32_t byte_swap(std::int32_t val) {
		val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
		return (val << 16) | ((val >> 16) & 0xFFFF);
	}

	_UTL_DISABLE_UBSAN_INTEGER
	constexpr inline std::uint64_t byte_swap(std::uint64_t val) {
		val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
		val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
		return (val << 32) | (val >> 32);
	}

	_UTL_DISABLE_UBSAN_INTEGER
	constexpr inline std::int64_t byte_swap(std::int64_t val) {
		val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
		val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
		return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
	}
	
}

