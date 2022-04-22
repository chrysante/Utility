#pragma once


#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "concepts.hpp"
#include "math.hpp"
#include "type_traits.hpp"
#include <bit>
#include <memory>
#include <iosfwd>
#include <chrono>
#include <thread>

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

	/// MARK: down_cast
	template <typename To, typename From> requires (std::is_base_of_v<From, std::remove_pointer_t<To>> && std::is_pointer_v<To>)
	To down_cast(From* from) noexcept {
		__utl_assert(dynamic_cast<To>(from) != nullptr);
		return static_cast<To>(from);
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
	
	/// MARK: - stack_buffer
	template <std::size_t Size, std::size_t Alignment = alignof(std::max_align_t)>
	class stack_buffer {
	public:
		stack_buffer() = default;
		stack_buffer(stack_buffer const&) = default;
		stack_buffer& operator=(stack_buffer const&) = default;
		
		void*       data()       { return _data; }
		void const* data() const { return _data; }
		std::size_t size() const { return Size; };
		
	private:
		alignas(Alignment) char _data[Size];
	};
	
	/// MARK: exit_state
	enum struct exit_state {
		success, failure, timeout
	};
	
	template <typename = void>
	inline std::ostream& operator<<(std::ostream& str, exit_state s) {
		char const* const names[] = {
			"success", "failure", "timeout"
		};
		auto const index = static_cast<int>(s);
		__utl_bounds_check(index, 0, 3);
		auto hti = [](auto&& x) -> decltype(auto) { return UTL_FORWARD(x); };
		return hti(str) << names[index];
	}
	
	/// MARK: busy_wait
	void busy_wait(std::predicate auto&& cond) {
		while (!cond()){
			std::this_thread::yield();
		}
	}
	
	/// MARK: timed_busy_wait
	template <typename R, typename P>
	exit_state timed_busy_wait(std::chrono::duration<R, P> timeout, std::predicate auto&& cond) {
		auto const begin = std::chrono::high_resolution_clock::now();
		while (true) {
			auto const now = std::chrono::high_resolution_clock::now();
			auto const elapsed = std::chrono::duration_cast<std::chrono::duration<R, P>>(now - begin);
			if (cond()) {
				return exit_state::success;
			}
			if (elapsed >= timeout) {
				return exit_state::timeout;
			}
			std::this_thread::yield();
		}
	}
	
	/// MARK: Enumerate
	template <typename E> requires (std::is_enum_v<E>)
	class enumerate {
	public:
		using integer = std::underlying_type_t<E>;
		
		enumerate() requires requires { E::_count; }:
			_first(0), _last((integer)E::_count)
		{}
		enumerate(integer last):
			_first(0), _last(last)
		{}
		enumerate(integer first, integer last):
			_first(first), _last(last)
		{}
		
		struct iterator {
			explicit iterator(integer value): _value(value) {}
			iterator& operator++() {
				++_value;
				return *this;
			}
			friend bool operator==(iterator const&, iterator const&) = default;
			E operator*() const { return (E)_value; }
		
		private:
			integer _value;
		};
		
		iterator begin() const { return iterator(_first); }
		iterator end() const { return iterator(_last); }
		
	private:
		integer _first, _last;
	};
	
	/// MARK: Reverse Container Adaptor
	template <typename C>
	class __reverse_adapter {
		static_assert(!std::is_reference_v<C>);
	public:
		__reverse_adapter(auto&& c):
			c(UTL_FORWARD(c))
		{}
		
		auto begin() { return c.rbegin(); }
		auto begin() const { return c.rbegin(); }
		
		auto end() { return c.rend(); }
		auto end() const { return c.rend(); }
		
	private:
		C c;
	};
	
	template <typename C>
	class __reverse_adapter<C&> {
	public:
		template <typename T>
		__reverse_adapter(T&& c):
			c(c)
		{ static_assert(!std::is_rvalue_reference_v<T>); }
		
		auto begin() const { return c.rbegin(); }
		auto end() const { return c.rend(); }
		
	private:
		C& c;
	};
	
	template <typename C>
	auto reverse(C& c) {
		return __reverse_adapter<C&>(c);
	}
	
	template <typename C>
	auto reverse(C const& c) {
		return __reverse_adapter<C const&>(c);
	}
	
	template <typename C>
	auto reverse(C&& c) {
		return __reverse_adapter<C>(std::move(c));
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
				return (std::intmax_t)i >= -((std::intmax_t)(1) << (int_size - 1)) && (std::intmax_t)i < ((std::intmax_t)(1) << (int_size - 1));
			}
			else {
				// n bits represent { 0, ..., 2^(n) - 1 }
				return (std::uintmax_t)i < ((std::uintmax_t)(1) << (int_size));
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
			//auto const i =_i;
			_p = (T*)((std::uintptr_t)p & pointer_mask);
			//_i = i;
		}
		
		auto integer() const noexcept { return _i; }
		
		void integer(Int i) noexcept {
			_i = i;
		}
	
	private:
		static constexpr std::size_t int_size = IntWidth;
		static constexpr std::uintptr_t pointer_mask = ~((std::uintptr_t(1) << int_size) - 1);
		union {
			T* _p;
			Int _i : int_size;
		};
	};
	
	
}


