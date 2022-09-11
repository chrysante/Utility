#pragma once

#include "__base.hpp"

#include <cstddef>
#include <cstring>

_UTL_SYSTEM_HEADER_

namespace utl {
	
	struct __map_info_buffer {
		void __construct(void* buffer, std::size_t bytes) {
			__buffer = (std::uint8_t*)buffer;
			std::memset(buffer, 0, bytes);
		}
		
		template <typename ValueType>
		static std::size_t __required_size(std::size_t count) {
//			std::size_t const info_size = ceil_divide(ceil_divide(count, 4u), alignof(ValueType)) * alignof(ValueType);
			
			std::size_t result = count / 4 + !!(count % 4);
			constexpr std::size_t align = alignof(ValueType);
			result = result / align + !!(result % align);
			result *= align;
			
			return result;
		}
		
		bool __impl_bit_set(std::size_t index) const {
			return __buffer[index / 8] & 1 << index % 8;
		}
		
		bool __has_element(std::size_t index) const {
			return __impl_bit_set(index * 2);
		}
		bool __is_tombstone(std::size_t index) const {
			return __impl_bit_set(index * 2 + 1);
		}
		bool __has_element_or_is_tombstone(std::size_t index) const {
			index *= 2;
			return __buffer[index / 8] & 0b11 << index % 8;
		}
		
		void __impl_set_bit(std::size_t index, bool value) {
			if (value) {
				__buffer[index / 8] |= 1 << index % 8;
			}
			else {
				__buffer[index / 8] &= ~(1 << index % 8);
			}
		}
		
		void __set_has_element(std::size_t index, bool value) {
			__impl_set_bit(index * 2, value);
		}
		
		void __set_is_tombstone(std::size_t index, bool value) {
			__impl_set_bit(index * 2 + 1, value);
		}
		
		std::uint8_t* __buffer;
	};
	
}
