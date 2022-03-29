#pragma once
#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__common.hpp"

#include <tuple>
#include <memory>
#include <algorithm>

namespace utl {

	template <typename T>
	concept __soa_type = requires{ typename T::__utl_soa_tuple; };
	
	template <__soa_type T, typename Allocator = std::allocator<void>>
	class SOA;

	template <typename T, typename Tuple, typename I, typename Allocator>
	class __SOA_impl;

	template <typename Type, typename ...T, std::size_t... I, typename Allocator>
	class __SOA_impl<Type, std::tuple<T...>, std::index_sequence<I...>, Allocator>:
		public Type::template __utl_soa_base<SOA<Type, Allocator>>,
		private Allocator
	{
	public:
		using value_type = Type;
		
		using reference = typename Type::__utl_soa_reference;
		using const_reference = typename Type::__utl_soa_const_reference;
		
//		using iterator = typename Type::__utl_soa_iterator;
//		using const_iterator = typename Type::__utl_soa_const_iterator;
		
	public:
		__SOA_impl(): _arrays{} {}
		
		template <typename ...U>
		void __emplace_back(U&&... u) {
			if (_cap == _size) {
				reserve(__recommend(_size + 1));
			}
			((std::get<I>(_arrays)[_size] = std::move(u)), ...);
			++_size;
		}
		
		template <typename ...U>
		void emplace_back(U&&... u) { __emplace_back(UTL_FORWARD(u)...); }
		void emplace_back(T const&... t) { __emplace_back(t...); }
		void emplace_back(T&&... t) { __emplace_back(std::move(t)...); }
		
		void push_back(value_type const& v) { emplace_back(v.template get<I>()...); }
		void push_back(value_type&& v) { emplace_back(std::move(v.template get<I>())...); }
		
		void reserve(std::size_t new_cap) {
			if (_cap >= new_cap) {
				return;
			}
			(__reserve_one<I>(new_cap), ...);
			_cap = new_cap;
		}
		
		template <std::size_t J>
		void __reserve_one(std::size_t new_cap) {
			using U = std::tuple_element_t<J, std::tuple<T...>>;
			U* new_array = __allocate<J>(new_cap);
			std::uninitialized_move(std::get<J>(_arrays), std::get<J>(_arrays) + _cap, new_array);
			std::destroy(std::get<J>(_arrays), std::get<J>(_arrays) + _cap);
			__deallocate<J>(std::get<J>(_arrays), _cap);
			std::get<J>(_arrays) = new_array;
		}
		
		template <std::size_t TypeIndex>
		auto& get(std::size_t index) { return std::get<TypeIndex>(_arrays)[index]; }

		reference operator[](std::size_t index) {
			return { *(std::get<T*>(_arrays) + index)... };
		}
		
		template <std::size_t J>
		auto* __allocate(std::size_t count) {
			return __get_allocator<J>().allocate(count);
		}
		template <std::size_t J>
		void __deallocate(auto* ptr, std::size_t count) {
			__get_allocator<J>().deallocate(ptr, count);
		}
														 
		template <std::size_t J>
		auto __get_allocator() {
			using U = std::tuple_element_t<J, std::tuple<T...>>;
			using U_Alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<U>;
			
			return U_Alloc(static_cast<Allocator>(*this));
		}

		std::size_t __recommend(std::size_t new_size) {
			return std::max(new_size, _size * 2);
		}
		
	private:
		std::tuple<T*...> _arrays;
		std::size_t _size = 0;
		std::size_t _cap = 0;
	};

	template <__soa_type T, typename Allocator>
	class SOA: public __SOA_impl<T, typename T::__utl_soa_tuple, std::make_index_sequence<std::tuple_size_v<typename T::__utl_soa_tuple>>, Allocator> {
		using __base = __SOA_impl<T, typename T::__utl_soa_tuple, std::make_index_sequence<std::tuple_size_v<typename T::__utl_soa_tuple>>, Allocator>;
		using __base::__base;
	};
	
}


#define _UTL_SOA_MEMBER_TYPE_IMPL(a, b) a
#define _UTL_SOA_MEMBER_NAME_IMPL(a, b) b

#define _UTL_SOA_MEMBER_TYPE(X) _UTL_SOA_MEMBER_TYPE_IMPL X
#define _UTL_SOA_MEMBER_NAME(X) _UTL_SOA_MEMBER_NAME_IMPL X
 
#define UTL_SOA_TYPE(Name, A, B) \
struct Name; /* Structure Type Fwd */ \
struct __##Name##_reference { /* Reference */ \
	_UTL_SOA_MEMBER_TYPE(A)& _UTL_SOA_MEMBER_NAME(A); \
	_UTL_SOA_MEMBER_TYPE(B)& _UTL_SOA_MEMBER_NAME(B); \
	__##Name##_reference& operator=(Name const&); \
	template <std::size_t I> auto& get() { \
		 if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(A); \
	else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(B); \
	} \
}; \
struct __##Name##_const_reference { /* Const Reference */ \
	_UTL_SOA_MEMBER_TYPE(A) const& _UTL_SOA_MEMBER_NAME(A); \
	_UTL_SOA_MEMBER_TYPE(B) const& _UTL_SOA_MEMBER_NAME(B); \
	template <std::size_t I> auto const& get() { \
			 if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(A); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(B); \
	} \
}; \
template <typename Derived> \
struct __##Name##_soa_base { /* SOA Base */ \
	_UTL_SOA_MEMBER_TYPE(A)& _UTL_SOA_MEMBER_NAME(A)(std::size_t index) { return static_cast<Derived&>(*this).template get<0>(index); } \
	_UTL_SOA_MEMBER_TYPE(A) const& _UTL_SOA_MEMBER_NAME(A)(std::size_t index) const { return static_cast<Derived const&>(*this).template get<0>(index); } \
	_UTL_SOA_MEMBER_TYPE(B)& _UTL_SOA_MEMBER_NAME(B)(std::size_t index) { return static_cast<Derived&>(*this).template get<1>(index); } \
	_UTL_SOA_MEMBER_TYPE(B) const& _UTL_SOA_MEMBER_NAME(B)(std::size_t index) const { return static_cast<Derived const&>(*this).template get<1>(index); } \
}; \
struct Name { /* Structure Type */\
	_UTL_SOA_MEMBER_TYPE(A) _UTL_SOA_MEMBER_NAME(A); \
	_UTL_SOA_MEMBER_TYPE(B) _UTL_SOA_MEMBER_NAME(B); \
	using __utl_soa_tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(A), _UTL_SOA_MEMBER_TYPE(B)>; \
	using __utl_soa_reference = __##Name##_reference; \
	using __utl_soa_const_reference = __##Name##_const_reference; \
	template <typename D> using __utl_soa_base = __##Name##_soa_base<D>; \
	template <std::size_t I> \
	auto& get() { \
			 if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(A); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(B); \
	} \
	template <std::size_t I> \
	auto const& get() const { \
			 if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(A); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(B); \
	} \
}; \
inline __##Name##_reference& __##Name##_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	return *this; \
} \
