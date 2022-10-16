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
	
	template <std::integral To, std::integral From>
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
	
	template <typename To, typename From> requires (std::is_base_of_v<From, std::remove_reference_t<To>> && std::is_reference_v<To>)
	To down_cast(From& from) noexcept {
		using ToPtr = std::remove_reference_t<To>*;
		__utl_assert(dynamic_cast<ToPtr>(&from) != nullptr);
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
	auto enumerate(std::underlying_type_t<E> first,
									  std::underlying_type_t<E> last)
	{
		class enum_range {
		public:
			using integer = std::underlying_type_t<E>;
			
			struct iterator {
				iterator& operator++() {
					++_value;
					return *this;
				}
				bool operator==(iterator const&) const = default;
				E operator*() const { return (E)_value; }
			
				integer _value;
			};
			
			iterator begin() const { return iterator{ _first }; }
			iterator end() const { return iterator{ _last }; }
			
			integer _first, _last;
		};
		
		return enum_range{ 0, last };
	}
	
	template <typename E> requires (std::is_enum_v<E>)
	auto enumerate(std::underlying_type_t<E> last = to_underlying(E::_count)) {
		return enumerate<E>(0, last);
	}
	
	template <typename Itr, typename Sentinel>
	struct __utl_enumerate_range {
		template <typename I>
		struct iterator {
			iterator& operator++() {
				++itr; ++index;
				return *this;
			}
			
			std::pair<std::size_t, decltype(*std::declval<I>())> operator*() {
				return { index, *itr };
			}
			
			template <typename J>
			bool operator!=(iterator<J> const& rhs) const { return itr != rhs.itr; }
			
			std::size_t index;
			I itr;
		};
		
		iterator<Itr> begin() const { return { 0, _begin }; }
		iterator<Sentinel> end() const { return { 0, _end }; }
		
		Itr _begin;
		[[no_unique_address]] Sentinel _end;
	};
	
	template <typename Itr, typename Sentinel>
	auto enumerate(Itr begin, Sentinel end) {
		return __utl_enumerate_range<Itr, Sentinel>{ begin, end };
	}
	
	template <typename Range>
	auto enumerate(Range&& range)
		requires requires { begin(range); end(range); } ||
				 requires { std::begin(range); std::end(range); } ||
				 requires { range.end(); range.begin(); }
	{
		using std::begin;
		using std::end;
		return enumerate(begin(range), end(range));
	}
	
	/// MARK: Transform Range
	template <typename Itr, typename Sentinel, typename Transform>
	struct __transform_range {
		template <typename I>
		struct iterator {
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = typename I::value_type;
			iterator& operator++()& {
				++itr;
				return *this;
			}
			
			iterator operator++(int)& {
				auto result = *this;
				++itr;
				return result;
			}
						
			decltype(auto) operator*() {
				return std::invoke(transform, *itr);
			}
			
			template <typename J>
			bool operator==(iterator<J> const& rhs) const { return itr == rhs.itr; }
			template <typename J>
			bool operator!=(iterator<J> const& rhs) const { return !(*this == rhs); }
			
			I itr;
			[[no_unique_address]] Transform transform;
		};
		
		iterator<Itr> begin() const { return { _begin, transform }; }
		iterator<Sentinel> end() const { return { _end, transform }; }
		
		Itr _begin;
		[[no_unique_address]] Sentinel _end;
		[[no_unique_address]] Transform transform;
	};
	
	// Not sure what to think of this
	template <typename E, typename T, std::size_t N = (std::size_t)E::_count>
	struct __enum_map {
		constexpr __enum_map(std::pair<E, T> const (&a)[N]): __data{} {
			if constexpr (requires{ E::_count; }) {
				static_assert(N == (std::size_t)E::_count);
			}
			for (std::size_t i = 0; i < N; ++i) {
				__utl_assert((std::size_t)a[i].first == i, "Make sure every enum case is handled");
				__data[i] = a[i].second;
			}
		}
		
		constexpr T const& operator[](E i) const { return __data[(std::size_t)i]; }
		
		std::array<T, N> __data;
	};
	
	template <typename... E, typename... T>
	__enum_map(std::pair<E, T>...) -> __enum_map<std::common_type_t<E...>, std::common_type_t<T...>>;
	
#define UTL_MAP_ENUM(__utl_e, T, ...)                                    \
	[&](auto __utl_x) {                                                 \
		using E = ::std::decay_t<decltype(__utl_x)>;                     \
		constexpr ::utl::__enum_map<E, T> __utl_s = { __VA_ARGS__ };     \
		__utl_assert((::std::size_t)__utl_x < __utl_s.__data.size(),     \
					 "Invalid enum case");                               \
		return __utl_s[__utl_x];                                         \
	}(__utl_e)
	
#define UTL_SERIALIZE_ENUM(__utl_e, ...) UTL_MAP_ENUM(__utl_e, std::string_view, __VA_ARGS__)
	
#ifdef _MSC_VER
	template <typename Itr, typename Sentinel>
	auto transform_range(Itr begin, Sentinel end, auto&& transform) {
		return __transform_range<Itr, Sentinel, std::decay_t<decltype(transform)>>{ begin, end, UTL_FORWARD(transform) };
	}
#else
	template <typename Itr, typename Sentinel>
	auto transform_range(Itr begin, Sentinel end, std::invocable<decltype(*begin)> auto&& transform) {
		return __transform_range<Itr, Sentinel, std::decay_t<decltype(transform)>>{ begin, end, UTL_FORWARD(transform) };
	}
#endif

	auto transform_range(auto&& range, auto&& transform) {
		using std::begin;
		using std::end;
		return transform_range(begin(range), end(range), UTL_FORWARD(transform));
	}
	
	/// MARK: Reverse Range Adaptor
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
	

	
	/// MARK: Lifetime Events
	template <typename Sub>
	struct lifetime;
//	{
//		constexpr void copy_construct(Sub const& from, Sub& to) {}
//		constexpr void copy_assign(Sub const& from, Sub& to) {}
//		constexpr void move_construct(Sub& from, Sub& to) noexcept {}
//		constexpr void move_assign(Sub& from, Sub& to) noexcept {}
//		constexpr void destruct(Sub&) noexcept {}
//	};
	
	template <typename Sub>
	constexpr void __execute_lt_cc(Sub const& from, Sub& to) {
		if constexpr (requires{
			lifetime<Sub>::copy_construct(from, to);
		}) {
			lifetime<Sub>::copy_construct(from, to);
		}
	}
	template <typename Sub>
	constexpr void __execute_lt_ca(Sub const& from, Sub& to) {
		if constexpr (requires{
			lifetime<Sub>::copy_assign(from, to);
		}) {
			lifetime<Sub>::copy_assign(from, to);
		}
	}
	template <typename Sub>
	constexpr void __execute_lt_mc(Sub& from, Sub& to) noexcept {
		if constexpr (requires{
			lifetime<Sub>::move_construct(from, to);
		}) {
			lifetime<Sub>::move_construct(from, to);
		}
	}
	template <typename Sub>
	constexpr void __execute_lt_ma(Sub& from, Sub& to) noexcept {
		if constexpr (requires{
			lifetime<Sub>::move_assign(from, to);
		}) {
			lifetime<Sub>::move_assign(from, to);
		}
	}
	template <typename Sub>
	constexpr void __execute_lt_d(Sub& self) {
		if constexpr (requires{
			lifetime<Sub>::destruct(self);
		}) {
			lifetime<Sub>::destruct(self);
		}
	}
	
	template <typename Sub>
	struct lifetime_events {
		lifetime_events() = default;
		constexpr lifetime_events(lifetime_events const& rhs) {
			__execute_lt_cc(static_cast<Sub const&>(rhs), static_cast<Sub&>(*this));
		}
		constexpr lifetime_events& operator=(lifetime_events const& rhs) {
			__execute_lt_ca(static_cast<Sub const&>(rhs), static_cast<Sub&>(*this));
			return *this;
		}
		constexpr lifetime_events(lifetime_events&& rhs) noexcept {
			__execute_lt_mc(static_cast<Sub&>(rhs), static_cast<Sub&>(*this));
		}
		constexpr lifetime_events& operator=(lifetime_events&& rhs) noexcept {
			__execute_lt_ma(static_cast<Sub&>(rhs), static_cast<Sub&>(*this));
			return *this;
		}
		constexpr ~lifetime_events() noexcept {
			__execute_lt_d(static_cast<Sub&>(*this));
		}
	};

	
	
	template <typename T, typename Int = int, std::size_t IntWidth = utl::log2(alignof(T))>
	class pointer_int_pair;

	template <typename T, typename Int, std::size_t IntWidth>
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
	
	
	template <typename... F>
	struct visitor: F... {
		using F::operator()...;
		constexpr visitor(F... f): F(std::move(f))... {}
	};
	
}


