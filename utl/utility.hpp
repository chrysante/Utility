#pragma once


#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "concepts.hpp"
#include "math.hpp"
#include "type_traits.hpp"
#include <bit>

namespace utl {
	
	template <integral To, integral From>
	constexpr To narrow_cast(From x) {
		if constexpr (std::is_signed_v<From> && std::is_unsigned_v<To>) {
			// casting from signed to unsigned
			__utl_expect(x >= (From)0);
			return narrow_cast<To>((std::make_unsigned_t<From>)x);
		}
		else if constexpr (std::is_unsigned_v<From> && std::is_signed_v<To>) {
			// casting from unsigned to signed
			if constexpr (sizeof(From) <= sizeof(To)) {
				// conversion might narrow
				__utl_expect(x <= (std::make_unsigned_t<To>)std::numeric_limits<To>::max());
			}
			return (To)x;
		}
		else {
			// both are either signed or unsigned
			if constexpr (sizeof(To) < sizeof(From)) {
				__utl_expect(x <= (From)std::numeric_limits<To>::max());
				__utl_expect(x >= (From)std::numeric_limits<To>::min());
			}
			return (To)x;
		}
	}

	template <typename T>
	void uninitialized_relocate(T* from, T* to) {
		if constexpr (utl::is_trivially_relocatable<T>::value) {
			std::memcpy(to, from, sizeof(T));
		}
		else {
			::new ((void*)to) T(std::move(*from));
			std::destroy_at(from);
		}
	}
	
	template <typename InputIter, typename OutputIter>
	void uninitialized_relocate(InputIter inBegin, InputIter inEnd, OutputIter outBegin) {
		using T = std::remove_cvref_t<decltype(*inBegin)>;
		using U = std::remove_reference_t<decltype(*outBegin)>;
		static_assert(std::is_same_v<T, U>);
		constexpr bool triv_reloc = utl::is_trivially_relocatable<T>::value;
		constexpr bool input_contigous  = std::is_pointer_v<InputIter> || std::is_same_v<std::contiguous_iterator_tag, typename std::iterator_traits<InputIter>::iterator_category>;
		constexpr bool output_contigous = std::is_pointer_v<OutputIter> || std::is_same_v<std::contiguous_iterator_tag, typename std::iterator_traits<OutputIter>::iterator_category>;
		if constexpr (triv_reloc && input_contigous && output_contigous) {
			static_assert(std::is_pointer_v<InputIter>,
						  "Other Cases are disabled to make ubsan happy");
			static_assert(std::is_pointer_v<OutputIter>,
						  "Just disable these static_asserts and swap active lines below");
//			std::memcpy(std::addressof(*outBegin), std::addressof(*inBegin), std::distance(inBegin, inEnd) * sizeof(T));
			if (outBegin)
				std::memcpy(outBegin, inBegin, std::distance(inBegin, inEnd) * sizeof(T));
		}
		else {
			for (; inBegin != inEnd; ++inBegin, ++outBegin) {
				utl::uninitialized_relocate(std::addressof(*inBegin), std::addressof(*outBegin));
			}
		}
	}
	
	
	
	template <integral T>
	constexpr T fast_mod_pow_two(T x, T y) {
		__utl_expect(y >= 0);
		__utl_expect(std::popcount(y) == 1);
		T const e = utl::log2(y);
		return ~(~T{} << e) & x;
	}
	template <integral T, integral U>
	constexpr std::common_type_t<T, U> fast_mod_pow_two(T x, U y) {
		using X = std::common_type_t<T, U>;
		return fast_mod_pow_two((X)x, (X)y);
	}
	
	constexpr char* align_to(void* p, std::size_t align) {
		auto const rest = fast_mod_pow_two((std::uintptr_t)p, align);
		if (!rest) {
			return (char*)p;
		}
		return (char*)p + align - rest;
	}
	
}



namespace utl {
	
	template <typename T, typename = int, std::size_t IntWidth = utl::log2(alignof(T))>
	class pointer_int_pair;
	
	template <typename T, integral Int, std::size_t IntWidth>
	class pointer_int_pair<T*, Int, IntWidth> {
	public:
		static constexpr bool fits(Int i) noexcept {
			if constexpr (std::is_signed_v<Int>) {
				// n bits represent { -2^(n-1), ..., 2^(n-1) - 1 }
				return i >= -((long long)(1) << (int_size - 1)) && i < ((long long)(1) << (int_size - 1));
			}
			else {
				// n bits represent { 0, ..., 2^(n) - 1 }
				return i < ((long long)(1) << (int_size));
			}
		}
		
		pointer_int_pair() = default;
		
		pointer_int_pair(T* p, Int i = 0) {
			__utl_expect(fits(i), "integer out of range");
			_p = p;
			_i = i;
		}
		
		T* pointer() const noexcept { return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(_p) & pointer_mask); }
		
		void pointer(T* p) noexcept {
			__utl_expect((reinterpret_cast<std::uintptr_t>(p) & ~pointer_mask) == 0, "pointer alignment not satisfied");
			auto const i =_i;
			_p = p;
			_i = i;
		}
		
		auto integer() const noexcept { return _i; }
		
		void integer(Int i) noexcept {
			_i = i;
		}
		
	private:
		static constexpr auto int_size = IntWidth;
		static constexpr unsigned long pointer_mask = ~((long(1) << int_size) - 1);
		union {
			T* _p;
			Int _i : int_size;
		};
	};
	
	
}


