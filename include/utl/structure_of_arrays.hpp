//
// Generic Structure of Arrays Class
// Value Types need to be declared with the UTL_SOA_TYPE macro.
// Example:
//		namespace ... [optional] {
//			UTL_SOA_TYPE( Particle,
//				(int, id),
//				(float2, position),
//				(float2, position),
//				(float4, color)
//			);
//		}
//
//	The UTL_SOA_TYPE macro then defines multiple structures, especially the following:
//
//		struct Particle {
//			int    id;
//			float2 position;
//			float2 position;
//			float4 color;
//
//			using reference = __Particle_reference;
//			using const_reference = __Particle_const_reference;
//
//			struct members {
//				using id       = /* implementation defined */;
//				using position = /* implementation defined */;
//				using position = /* implementation defined */;
//				using color    = /* implementation defined */;
//			};
//
//			template <std::size_t I>
//			auto& get();
//			template <std::size_t I>
//			auto const& get() const;
//		};
//
//		struct __Particle_reference { [exposition only]
//			int&    id;
//			float2& position;
//			float2& position;
//			float4& color;
//
//			template <std::size_t I>
//			auto& get() const;
//		};
//
//		struct __Particle_const_reference { [exposition only]
//			int const&    id;
//			float2 const& position;
//			float2 const& position;
//			float4 const& color;
//
//			template <std::size_t I>
//			auto const& get() const;
//		};
//
//	It also defines additional template machinery used by the utl::structure_of_arrays<Particle> class.
//	Subset Types and Subset Reference/Pointer Types of the Particle structure are also provided.
//
//	utl::structure_of_arrays<Particle> then behaves similarly to std::vector<Particle>, however all
//	members of Particle are stored in seperate arrays to improve cache locality when iterating over
//	individual members or subsets of the entire Particle structure.
//	Allocations are batched, so for the above Particle structure one allocation is performed
//	for the for arrays in utl::structure_of_arrays<Particle>.
//	All STL Algorithms should work with utl::structure_of_arrays<...>.
//
//

#pragma once

#ifndef __UTL_STRUCTURE_OF_ARRAYS_INCLUDED__
#define __UTL_STRUCTURE_OF_ARRAYS_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "__soa_generated.hpp"
#include "__memory_resource_base.hpp" /* only for utl::pmr::structure_of_array typedef */
#include "__function_objects.hpp"
#include "common.hpp"
#include "math.hpp"
#include "concepts.hpp"

#include <tuple>
#include <memory>
#include <algorithm>
#include <span>
#include <compare>
#include <exception>

namespace utl {

	template <typename T>
	concept __soa_type = requires{ typename T::__utl_soa_meta; };

	struct __utl_soa_options {
		bool view = false;
	};
	
	/// MARK: - Declarations
	template <__soa_type ST, typename Allocator = std::allocator<ST>>
	class structure_of_arrays;
	
	namespace pmr {
		template <__soa_type ST>
		using structure_of_arrays = utl::structure_of_arrays<ST, polymorphic_allocator<ST>>;
	}
	
	template <__soa_type, typename... Members>
	class soa_view;

	/// MARK: Generic Member Getter
	template <std::size_t I, typename T>
	auto& __soa_get_member(T& t) { return t.template get<I>(); }
	template <std::size_t I, typename T>
	auto const& __soa_get_member(T const& t) { return t.template get<I>(); }
	template <std::size_t I, typename T>
	auto&& __soa_get_member(T&& t) { return std::move(t.template get<I>()); }
	
	/// MARK: - Partial Types
	enum struct __soa_type_kind {
		value, reference, const_reference, pointer, const_pointer
	};
	template <__soa_type_kind, typename>
	struct __soa_type_mapper;
	
	template <typename T>
	struct __soa_type_mapper<__soa_type_kind::value, T> { using type = T; };
	template <typename T>
	struct __soa_type_mapper<__soa_type_kind::reference, T> { using type = T&; };
	template <typename T>
	struct __soa_type_mapper<__soa_type_kind::const_reference, T> { using type = T const&; };
	template <typename T>
	struct __soa_type_mapper<__soa_type_kind::pointer, T> { using type = T*; };
	template <typename T>
	struct __soa_type_mapper<__soa_type_kind::const_pointer, T> { using type = T const*; };
	
	template <typename Meta, typename>
	struct __soa_is_full: std::false_type{};
	template <typename Meta, typename... T>
	struct __soa_is_full<Meta, std::tuple<T...>>: std::bool_constant<
		std::is_same_v<
			std::make_index_sequence<Meta::member_count>,
			std::index_sequence<T::index...>
		>
		&& (!std::is_const_v<T> && ...)
	>{};
	
	template <typename Meta,
			  typename Members,
			  __soa_type_kind,
			  bool IsFull = __soa_is_full<Meta, Members>::value>
	struct __soa_type_maker;
	
	/// 'Full' Case: Use generated Value, Reference and Pointer  Types
	template <typename Meta, typename _>
	struct __soa_type_maker<Meta, _, __soa_type_kind::value, true> {
		using type = typename Meta::value_type;
	};
	template <typename Meta, typename _>
	struct __soa_type_maker<Meta, _, __soa_type_kind::reference, true> {
		using type = typename Meta::reference;
	};
	template <typename Meta, typename _>
	struct __soa_type_maker<Meta, _, __soa_type_kind::const_reference, true> {
		using type = typename Meta::const_reference;
	};
	template <typename Meta, typename _>
	struct __soa_type_maker<Meta, _, __soa_type_kind::pointer, true> {
		using type = typename Meta::pointer;
	};
	template <typename Meta, typename _>
	struct __soa_type_maker<Meta, _, __soa_type_kind::const_pointer, true> {
		using type = typename Meta::const_pointer;
	};
	
	/// Partial Case
	template <typename Meta, std::size_t J>
	using __soa_element_type = std::tuple_element_t<J, typename Meta::tuple>;
	
	constexpr __soa_type_kind __make_soa_reference_const_if(bool condition, __soa_type_kind k) {
		if (!condition) {
			return k;
		}
		if (k == __soa_type_kind::reference) {
			return __soa_type_kind::const_reference;
		}
		if (k == __soa_type_kind::pointer) {
			return __soa_type_kind::const_pointer;
		}
		return k;
	}
	
	template <typename Meta, typename Member, __soa_type_kind Kind>
	using __soa_element_member_base = typename Meta::template member_base<
		Member::index>::template type<
			typename __soa_type_mapper<
				__make_soa_reference_const_if(std::is_const_v<Member>, Kind), __soa_element_type<Meta, Member::index>
			>::type
		>;
	
	template <typename Meta, typename Members, __soa_type_kind Kind>
	struct __soa_partial_element;
	
	template <typename Meta, typename... Members, __soa_type_kind Kind>
	struct __soa_partial_element<Meta, std::tuple<Members...>, Kind>: __soa_element_member_base<Meta, Members, Kind>... {
		static constexpr std::size_t __member_count = sizeof...(Members);
		
		static constexpr bool __this_is_value = Kind == __soa_type_kind::value;
		static constexpr bool __this_is_reference = Kind == __soa_type_kind::reference || Kind == __soa_type_kind::const_reference;
		static constexpr bool __this_is_pointer = Kind == __soa_type_kind::pointer || Kind == __soa_type_kind::const_pointer;
		
		static constexpr auto __reference_kind = []{
			if (Kind == __soa_type_kind::reference || Kind == __soa_type_kind::value || Kind == __soa_type_kind::pointer) {
				return __soa_type_kind::reference;
			}
			else {
				return __soa_type_kind::const_reference;
			}
		}();
		
		static constexpr auto __pointer_kind = []{
			if (Kind == __soa_type_kind::reference || Kind == __soa_type_kind::value || Kind == __soa_type_kind::pointer) {
				return __soa_type_kind::pointer;
			}
			else {
				return __soa_type_kind::const_pointer;
			}
		}();
		
		__soa_partial_element() = default;
		
		template <typename M>
		using __member_base = __soa_element_member_base<Meta, M, Kind>;
		
		template <typename M>
		static constexpr auto __add_ref_helper() {
			// handle pointer case first
			if (Kind == __soa_type_kind::pointer || Kind == __soa_type_kind::const_pointer) {
				if (std::is_const_v<M>) {
					return __soa_type_kind::const_pointer;
				}
				return Kind;
			}
			if (Kind == __soa_type_kind::value) {
				return __soa_type_kind::const_reference;
			}
			if (std::is_const_v<M>) {
				return __soa_type_kind::const_reference;
			}
			return Kind;
		};
		
		template <typename M, typename T>
		using __add_ref = typename __soa_type_mapper<__add_ref_helper<M>(), T>::type;
		
		constexpr __soa_partial_element(__add_ref<Members, __soa_element_type<Meta, Members::index>>... members): __member_base<Members>{ members }... {}
		
		template <__soa_type_kind K>
		using __corresponding_type = typename __soa_type_maker<Meta, std::tuple<Members...>, K>::type;
		
		/// Operator=
		constexpr __soa_partial_element& operator=(__corresponding_type<__soa_type_kind::const_reference> const& rhs)
			requires(Kind != __soa_type_kind::const_reference)
		{
			((this->__member_base<Members>::__get() = rhs.__corresponding_type<__soa_type_kind::const_reference>::template __member_base<Members>::__get()), ...);
			return *this;
		}
		
		/// Conversion to const_reference
		constexpr operator __corresponding_type<__soa_type_kind::const_reference>() const requires(!__this_is_pointer) {
			return { __member_base<Members>::__get()... };
		}
		
		/// Operator&
		constexpr __corresponding_type<__pointer_kind> operator&() const requires(__this_is_reference) {
			return UTL_WITH_INDEX_SEQUENCE((I, __member_count), {
				return __corresponding_type<__pointer_kind>{
					&get<I>()...
				};
			});
		}
		constexpr __soa_partial_element* operator&() requires(__this_is_value) {
			return this;
		}
		constexpr __soa_partial_element const* operator&() const requires(__this_is_value) {
			return this;
		}
		
		/// Operator*
		constexpr __corresponding_type<__reference_kind> operator*() const requires(__this_is_pointer) {
			return UTL_WITH_INDEX_SEQUENCE((I, __member_count), {
				return __corresponding_type<__reference_kind>{
					*get<I>()...
				};
			});
		}
		
		template <std::size_t I>
		auto& get() requires (Kind == __soa_type_kind::value) {
			using M = std::tuple_element_t<I, std::tuple<Members...>>;
			return __member_base<M>::__get();
		}
		
		template <std::size_t I>
		auto& get() const {
			using M = std::tuple_element_t<I, std::tuple<Members...>>;
			if constexpr (Kind == __soa_type_kind::value) {
				return as_const(__member_base<M>::__get());
			}
			else {
				return __member_base<M>::__get();
			}
		}
	};
	
	template <typename Meta, typename... Members, __soa_type_kind Kind>
	struct __soa_type_maker<Meta, std::tuple<Members...>, Kind, false> {
		using type = __soa_partial_element<Meta, std::tuple<Members...>, Kind>;
	};
	
	// Partial Case One Member
	template <typename Meta, typename Member>
	struct __soa_type_maker<Meta, std::tuple<Member>, __soa_type_kind::value, false> {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = _T;
	};
	template <typename Meta, typename Member>
	struct __soa_type_maker<Meta, std::tuple<Member>, __soa_type_kind::reference, false> {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = std::conditional_t<std::is_const_v<Member>, _T const&, _T&>;
	};
	template <typename Meta, typename Member>
	struct __soa_type_maker<Meta, std::tuple<Member>, __soa_type_kind::const_reference, false> {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = _T const&;
	};
	template <typename Meta, typename Member>
	struct __soa_type_maker<Meta, std::tuple<Member>, __soa_type_kind::pointer, false> {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = std::conditional_t<std::is_const_v<Member>, _T const*, _T*>;
	};
	template <typename Meta, typename Member>
	struct __soa_type_maker<Meta, std::tuple<Member>, __soa_type_kind::const_pointer, false> {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = _T const*;
	};
	
}

/// MARK: - Structured Binding Partial Types
template <typename Meta, typename Tuple, utl::__soa_type_kind Kind>
struct std::tuple_size<utl::__soa_partial_element<Meta, Tuple, Kind>>:
	std::integral_constant<std::size_t, std::tuple_size<Tuple>::value>
{};

template <std::size_t N, typename Meta, typename... Members>
struct std::tuple_element<N, utl::__soa_partial_element<Meta, std::tuple<Members...>, utl::__soa_type_kind::value>> {
	using __member = std::tuple_element_t<N, std::tuple<Members...>>;
	using _T = std::tuple_element_t<__member::index, typename Meta::tuple>;
	using type = _T;
};

template <std::size_t N, typename Meta, typename... Members>
struct std::tuple_element<N, utl::__soa_partial_element<Meta, std::tuple<Members...>, utl::__soa_type_kind::reference>> {
	using __member = std::tuple_element_t<N, std::tuple<Members...>>;
	using _T = std::tuple_element_t<__member::index, typename Meta::tuple>;
	
	using type = std::conditional_t<std::is_const_v<__member>, _T const&, _T&>;
};

template <std::size_t N, typename Meta, typename... Members>
struct std::tuple_element<N, utl::__soa_partial_element<Meta, std::tuple<Members...>, utl::__soa_type_kind::const_reference>> {
	using __member = std::tuple_element_t<N, std::tuple<Members...>>;
	using _T = std::tuple_element_t<__member::index, typename Meta::tuple>;
	using type = _T const&;
};


namespace utl {
	
	/// MARK: - Choosing Implementation
	template <typename Meta, typename MemberIndices, typename T, typename I, typename Allocator, __utl_soa_options>
	struct __soa_impl;
	
	/// SOA
	template <typename ST, typename Allocator, typename I = std::make_index_sequence<ST::__utl_soa_meta::member_count>>
	struct __soa_base;
	
	template <typename ST, typename Allocator, std::size_t... I>
	struct __soa_base<ST, Allocator, std::index_sequence<I...>> {
		using type = __soa_impl<
			typename ST::__utl_soa_meta, /* Meta */
			std::tuple<typename ST::__utl_soa_meta::members::template type<I>...>, /* here we want all members mutable in default order */
			typename ST::__utl_soa_meta::tuple,
			std::make_index_sequence<ST::__utl_soa_meta::member_count>,
			Allocator,
			__utl_soa_options{}
		>;
	};
	
	template <__soa_type ST, typename Allocator>
	class structure_of_arrays: public __soa_base<ST, Allocator>::type {
		using __base = typename __soa_base<ST, Allocator>::type;
		using __base::__base;
	};
	
	/// SOA View
	template <typename Meta, typename Member>
	struct __soa_get_member_type {
		using _T = std::tuple_element_t<Member::index, typename Meta::tuple>;
		using type = std::conditional_t<std::is_const_v<Member>, _T const, _T>;
	};
	
	template <__soa_type ST, typename... Members>
	using __soa_view_base = __soa_impl<
		typename ST::__utl_soa_meta, /* Meta */
		std::tuple<Members...>,
		std::tuple<typename __soa_get_member_type<typename ST::__utl_soa_meta, Members>::type...>,
		std::make_index_sequence<sizeof...(Members)>,
		empty, /* Allocator */
		__utl_soa_options{ .view = true }
	>;
	
	template <__soa_type ST, typename... Members>
	class soa_view: public __soa_view_base<ST, Members...> {
		using __base = __soa_view_base<ST, Members...>;
		using __base::__base;
	};

	/// MARK: - Iterator
	template <typename SOAImpl, typename T, typename I, bool IsConst>
	struct __soa_iterator;
	
	template <typename SOAImpl, typename... T, std::size_t... I, bool IsConst>
	struct __soa_iterator<SOAImpl,
						  std::tuple<T...>,
						  std::index_sequence<I...>,
						  IsConst>
	{
		using __soa_ref_type = std::conditional_t<IsConst, typename SOAImpl::const_reference, typename SOAImpl::reference>;
		using __soa_ptr_type = std::tuple<std::conditional_t<IsConst, T const*, T*>...>;
		
		/// Member Types
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = typename SOAImpl::value_type;
		using pointer = std::conditional_t<IsConst, typename SOAImpl::const_pointer, typename SOAImpl::pointer>;
		using reference = std::conditional_t<IsConst, typename SOAImpl::const_reference, typename SOAImpl::reference>;;
		
		/// Constructors
		explicit __soa_iterator(__soa_ptr_type ptr): _ptr(ptr) {}
		__soa_iterator(__private_tag, T*... ptr): _ptr(ptr...) {}
		
		/// Conversion to Const Iterator
		operator __soa_iterator<SOAImpl,
							    std::tuple<T...>,
							    std::index_sequence<I...>,
							    true>() const requires (!IsConst)
		{
			return { __private_tag{}, std::get<I>(_ptr)... };
		}
		
		/// Partial Conversion to Const
		template <typename ...U, bool RHSIsConst>
		requires (std::is_convertible_v<T*, U*> && ...)
		operator __soa_iterator<SOAImpl,
								std::tuple<U...>,
								std::index_sequence<I...>,
								RHSIsConst>() const requires (!IsConst)
		{
			return { __private_tag{}, std::get<I>(_ptr)... };
		}
		
		/// Increment / Decrement
		__soa_iterator& operator++() {
			(++std::get<I>(_ptr), ...);
			return *this;
		}
		
		__soa_iterator& operator--() {
			(--std::get<I>(_ptr), ...);
			return *this;
		}
		
		/// Postfix Increment / Decrement
		__soa_iterator operator++(int) {
			__soa_iterator const tmp = *this;
			(++std::get<I>(_ptr), ...);
			return tmp;
		}
		
		__soa_iterator operator--(int) {
			__soa_iterator const tmp = *this;
			(--std::get<I>(_ptr), ...);
			return tmp;
		}
		
		/// Arithmetic
		difference_type operator-(__soa_iterator const& rhs) const {
			return std::get<0>(_ptr) - std::get<0>(rhs._ptr);
		}
		
		__soa_iterator operator+(difference_type offset) const {
			return __soa_iterator({ (std::get<I>(_ptr) + offset)... });
		}
		
		__soa_iterator operator-(difference_type offset) const {
			return __soa_iterator({ (std::get<I>(_ptr) - offset)... });
		}
		
		__soa_iterator& operator+=(difference_type offset)& {
			*this = *this + offset;
			return *this;
		}
		
		__soa_iterator& operator-=(difference_type offset)& {
			*this = *this - offset;
			return *this;
		}
		
		/// Dereference
		__soa_ref_type operator*() const {
			return { *std::get<I>(_ptr)... };
		}
		
		/**
		 operator-> is not usable. It requires to return a raw pointer, but we can't form a raw pointer to our value type, because of the memory layout.
		 */
		/*
		reference const* operator->() const {
			return reinterpret_cast<reference const*>(this);
		}
		 */
		
		/// Comparison
		bool operator==(__soa_iterator const& rhs) const {
			bool const result = std::get<0>(_ptr) == std::get<0>(rhs._ptr);
			(((void)I, __utl_assert_audit(result == (std::get<I>(_ptr) == std::get<I>(rhs._ptr)))), ...);
			return result;
		}
		
		bool operator!=(__soa_iterator const& rhs) const {
			return !(*this == rhs);
		}
		
		bool operator<(__soa_iterator const& rhs) const {
			return std::get<0>(_ptr) < std::get<0>(rhs._ptr);
		}
		bool operator<=(__soa_iterator const& rhs) const {
			return std::get<0>(_ptr) <= std::get<0>(rhs._ptr);
		}
		bool operator>(__soa_iterator const& rhs) const {
			return std::get<0>(_ptr) > std::get<0>(rhs._ptr);
		}
		bool operator>=(__soa_iterator const& rhs) const {
			return std::get<0>(_ptr) >= std::get<0>(rhs._ptr);
		}
		
	private:
		/// Data
		__soa_ptr_type _ptr;
	};
	
	/// MARK: - SOA Implementation
	template <typename Allocator, typename T>
	struct __soa_rebind_allocator {
		using type = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;
	};
	
	template <typename T>
	struct __soa_rebind_allocator<empty, T> {
		using type = empty;
	};
	
	template <bool IsView, typename... T>
	struct __soa_impl_data /* IsView = true */ {
		std::tuple<T*...> _data = {};
		std::size_t _size = 0;
	};
	template <typename... T>
	struct __soa_impl_data<false, T...> {
		std::tuple<T*...> _data = {};
		std::size_t _size = 0;
		std::size_t _cap = 0;
	};
	
	constexpr std::size_t __soa_max_align = 64;
	struct alignas(__soa_max_align) __soa_max_aligned_storage: std::integral_constant<std::size_t, __soa_max_align> {};
	
	template <typename Meta,
			  typename ..._Members,
			  typename ...T,
			  std::size_t ...I,
			  typename _Allocator,
			  __utl_soa_options Options>
	struct __soa_impl<Meta,
					  std::tuple<_Members...>,
					  std::tuple<T...>,
					  std::index_sequence<I...>,
					  _Allocator,
					  Options>:
		private __soa_rebind_allocator<_Allocator, __soa_max_aligned_storage>::type,
		private __soa_impl_data<Options.view, T...>
	{
		/// MARK: Internals
		template <typename, typename, typename, typename, typename, __utl_soa_options>
		friend class __soa_impl;
		
		using __soa_type = typename Meta::value_type;
		
		using __allocator = typename __soa_rebind_allocator<_Allocator, __soa_max_aligned_storage>::type;
		using __data_base = __soa_impl_data<Options.view, T...>;
		
		static constexpr bool __is_view = Options.view;
		static constexpr bool __is_container = !__is_view;
		static constexpr std::size_t __member_count = Meta::member_count;
		
		using __member_tuple = std::tuple<T...>;
		using __member_indices = std::index_sequence<_Members::index...>;
		using __members = std::tuple<_Members...>;
		
		static constexpr std::size_t __invalid_index = std::size_t(-1);
		
		static constexpr std::array<std::size_t, __member_count> __make_index_map() {
			std::array<std::size_t, __member_count> result{};
			std::array const member_indices = { _Members::index... };
			for (std::size_t i = 0; i < __member_count; ++i) {
				auto itr = std::find(member_indices.begin(), member_indices.end(), i);
				if (itr == member_indices.end()) {
					result[i] = __invalid_index;
				}
				else {
					result[i] = itr - member_indices.begin();
				}
			}
			return result;
		}
		static constexpr std::array<std::size_t, __member_count> __index_map = __make_index_map();
		
		template <typename Member>
		static constexpr bool __has_member() {
			constexpr std::size_t mapped_index = __index_map[Member::index];
			if (mapped_index == __invalid_index) {
				return false;
			}
			if (!std::is_const_v<Member>) {
				return !std::is_const_v<std::tuple_element_t<mapped_index, __members>>;
			}
			return true;
		}
		
		/// MARK: Member Types
		using value_type = typename __soa_type_maker<Meta, __members, __soa_type_kind::value>::type;
		using allocator_type = _Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = typename __soa_type_maker<Meta, __members, __soa_type_kind::reference>::type;
		using const_reference = typename __soa_type_maker<Meta, __members, __soa_type_kind::const_reference>::type;
		using pointer = typename __soa_type_maker<Meta, __members, __soa_type_kind::pointer>::type;
		using const_pointer = typename __soa_type_maker<Meta, __members, __soa_type_kind::const_pointer>::type;
		using iterator = __soa_iterator<__soa_impl, std::tuple<T...>, std::index_sequence<I...>, false>;
		using const_iterator = __soa_iterator<__soa_impl, std::tuple<T const...>, std::index_sequence<I...>, true>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		
		/// MARK: Constructors
		__soa_impl(): __allocator{} {}
		__soa_impl(__allocator const& alloc): __allocator(alloc) {}
		__soa_impl(std::size_t size, __allocator const& alloc = {}): __allocator(alloc) {
			reserve(size);
			this->_size = size;
			(__construct(__begin<I>(), __end<I>()), ...);
		}
		__soa_impl(std::initializer_list<value_type> ilist, __allocator const& alloc = {}): __allocator(alloc) {
			reserve(ilist.size());
			for (auto const& elem: ilist) {
				push_back(elem);
			}
		}
		
		/// Copy Constructor
		__soa_impl(__soa_impl const& rhs, __allocator const& alloc = {}): __allocator(alloc) {
			if constexpr (__is_container) {
				reserve(rhs._size);
				this->_size = rhs._size;
				(__uninitialized_copy(rhs.__begin<I>(), rhs.__end<I>(), __begin<I>()), ...);
			}
			else {
				__copy_view(rhs);
			}
		}
		void __copy_view(auto const& rhs) {
			this->_data = rhs._data;
			this->_size = rhs._size;
		}
		
		/// Move Constructor
		__soa_impl(__soa_impl&& rhs, __allocator const& alloc = {}): __allocator(alloc) {
			if constexpr (__is_container) {
				if (__get_allocator() == rhs.__get_allocator()) {
					// we can swap
					this->_data = rhs._data;
					this->_size   = rhs._size;
					this->_cap    = rhs._cap;
					rhs._data = {};
					rhs._size = 0;
					rhs._cap = 0;
				}
				else {
					reserve(rhs.size());
					this->_size = rhs.size();
					(__uninitialized_move(rhs.__begin<I>(), rhs.__end<I>(), __begin<I>()), ...);
				}
			}
			else {
				__copy_view(rhs);
			}
		}
		
		/// Private (for construcing views)
		explicit __soa_impl(__private_tag, std::tuple<T*...> ptr, std::size_t size) requires(__is_view): __data_base{ ptr, size } {}
		
		/// MARK: Assignment
		__soa_impl& operator=(__soa_impl const& rhs)& {
			if constexpr (__is_container) {
				clear();
				reserve(rhs.size());
				(__uninitialized_copy(rhs.__begin<I>(), rhs.__end<I>(), __begin<I>()), ...);
			}
			else {
				__copy_view(rhs);
			}
			return *this;
		}
		
		__soa_impl& operator=(__soa_impl&& rhs)& {
			if constexpr (__is_container) {
				if (__get_allocator() == rhs.__get_allocator()) {
					// we can swap pointers
					__destroy_this();
					this->_data = rhs._data;
					this->_size   = rhs._size;
					this->_cap    = rhs._cap;
					rhs._data = {};
					rhs._size = 0;
					rhs._cap = 0;
				}
				else {
					clear();
					reserve(rhs.size());
					(__uninitialized_move(rhs.__begin<I>(), rhs.__end<I>(), __begin<I>()), ...);
				}
			}
			else {
				__copy_view(rhs);
			}
			return *this;
		}
		
 
		/// MARK: Destructor
		~__soa_impl() {
			if constexpr (__is_container) {
				__destroy_this();
			}
		}
		
		/// MARK: Modifiers
		/// Emplace Back
		template <typename ...U>
		void __emplace_back_impl(U&&... u) {
			__grow_to_least(size() + 1);
			(__construct_at(__end<I>(), UTL_FORWARD(u)), ...);
			++this->_size;
		}
		
		template <typename ...U>
		void emplace_back(U&&... u) requires (__is_container) { __emplace_back_impl(UTL_FORWARD(u)...); }
		void emplace_back(T const&... t) requires(__is_container) { __emplace_back_impl(t...); }
		void emplace_back(T&&... t) requires (__is_container) { __emplace_back_impl(std::move(t)...); }
		
		/// Push Back
		void push_back(value_type const& v) requires (__is_container) { emplace_back(v.template get<I>()...); }
		void push_back(value_type&& v) requires (__is_container) { emplace_back(std::move(v.template get<I>())...); }
		
		/// Pop Back
		void pop_back() requires (__is_container) {
			--this->_size;
			(__destroy_at(__end<I>()), ...);
		}
		
        void __uninit_shift_right(auto begin, auto end, std::ptrdiff_t offset) {
            __utl_assert(offset >= 0);
            std::ptrdiff_t const __min_offset = std::min(offset, end - begin);
            for (auto __it = end - __min_offset; __it != end; ++__it) {
                __construct_at(__it + offset, std::move(*__it));
            }
            std::shift_right(begin, end, offset);
        }
        
        template <typename It>
        void __insert_impl(std::size_t index, It begin, It end) {
            __utl_expect(index >= 0);
            __utl_expect(index <= size());
            // somewhat naive implementation, doing unnecesary copies and shifts when reallocating
            auto const count = end - begin;
            __utl_expect(count >= 1);
            __grow_to_least(size() + count);
            (__uninit_shift_right(__begin<I>() + index, __end<I>(), count), ...);
            {
                std::size_t i = index;
                std::size_t const total_end = index + count;
                std::size_t const intermed_end = std::min(total_end, size());
                for (; i < intermed_end; ++i, ++begin) {
                    // here we assign
                    (*this)[i] = *begin;
                }
                for (; i < total_end; ++i, ++begin) {
                    // here we construct
                    (__construct_at(__begin<I>() + i, __soa_get_member<I>(*begin)), ...);
                }
            }
            this->_size += count;
        }
        
        /// Insert
        void insert(std::size_t index, value_type const& value) requires (__is_container) {
			__insert_impl(index, &value, &value + 1);
		}
		
		void insert(std::size_t index, value_type&& value) requires (__is_container) {
			__insert_impl(index, std::make_move_iterator(&value), std::make_move_iterator(&value + 1));
		}
		
		template <input_iterator_for<value_type> It>
		void insert(std::size_t index, It begin, It end) requires (__is_container) {
			__insert_impl(index, begin, end);
		}
		
		void insert(const_iterator itr, value_type const& value) requires (__is_container) {
			insert(__itr_to_index(itr), value);
		}
		
		void insert(const_iterator itr, value_type&& value) requires (__is_container) {
			insert(__itr_to_index(itr), std::move(value));
		}
		
		template <input_iterator_for<value_type> It>
		void insert(const_iterator itr, It begin, It end) requires (__is_container) {
			insert(__itr_to_index(itr), begin, end);
		}

		/// Erase
		void erase(std::size_t position) requires (__is_container) {
			erase(position, position + 1);
		}
		
		void erase(std::size_t first, std::size_t last) requires (__is_container) {
			__utl_expect(first < last);
			__utl_expect(first >= 0);
			__utl_expect(last <= size());
			std::size_t const count = last - first;
			((std::shift_left(__begin<I>() + first, __end<I>(), count),
			  __destroy(__end<I>() - count, __end<I>())),
			 ...);
			this->_size -= count;
		}
		
		void erase(const_iterator itr) requires (__is_container) {
			erase(__itr_to_index(itr));
		}
		
		void erase(const_iterator first, const_iterator const& last) requires (__is_container) {
			erase(__itr_to_index(first), __itr_to_index(last));
		}
		
		/// Reserve
		void reserve(std::size_t new_cap) requires (__is_container) {
			if (this->_cap >= new_cap) {
				return;
			}
			std::tuple<T*...> new_array = __allocate(new_cap);
			(__relocate(__begin<I>(), __end<I>(), std::get<I>(new_array)), ...);
			__deallocate(this->_data, this->_cap);
			this->_data = new_array;
			this->_cap = new_cap;
		}
		
		/// Shrink to fit
		void shrink_to_fit() requires(__is_container) {
			/* no-op */
		}
		
		/// Clear
		void clear() requires (__is_container) {
			(__destroy(__begin<I>(), __end<I>()), ...);
			this->_size = 0;
		}
		
		/// Swap
		void swap(structure_of_arrays<__soa_type>& rhs) requires(__is_container) {
			if (__get_allocator() == rhs.__get_allocator()) {
				// we can swap pointers
				std::swap(this->__member_data(), rhs.__member_data());
			}
			else {
				auto tmp = std::move(*this);
				*this = std::move(rhs);
				rhs = std::move(tmp);
			}
		}
		
		/// MARK: Views
		template <typename ...Members>
		[[nodiscard]] soa_view<__soa_type, Members...> __view_impl() const {
			using view_t = soa_view<__soa_type, Members...>;
			return view_t(__private_tag{}, { __begin<__index_map[Members::index]>()... }, size());
		}
		
		/// Owning
		template <typename ...Members> requires (__has_member<Members>() && ...) && (__is_container)
		[[nodiscard]] auto view() {
			return __view_impl<Members...>();
		}
		template <typename ...Members> requires (__has_member<Members const>() && ...) && (__is_container)
		[[nodiscard]] auto view() const {
			return __view_impl<Members const...>();
		}
		/// Non-Owning
		template <typename ...Members> requires (__has_member<Members>() && ...) && (__is_view)
		[[nodiscard]] auto view() const {
			return __view_impl<Members...>();
		}
		
		/// Experimental
		template <typename ...Members> requires (__has_member<Members>() && ...) && (__is_container)
		[[nodiscard]] auto __view(Members...) {
			return __view_impl<std::remove_const_t<Members>...>();
		}
		
		/// Convert to std::span
		operator std::span<std::tuple_element_t<0, std::tuple<T...>>>() const requires(sizeof...(T) == 1) {
			return std::span<std::tuple_element_t<0, std::tuple<T...>>>(__begin<0>(), size());
		}
		operator std::span<std::tuple_element_t<0, std::tuple<T...>> const>() const requires (sizeof...(T) == 1) && (!std::is_const_v<std::tuple_element_t<0, std::tuple<T...>>>) {
			return std::span<std::tuple_element_t<0, std::tuple<T...>>>(__begin<0>(), size());
		}
		
		/// MARK: Obeservers
		std::size_t size() const { return this->_size; }
		std::size_t capacity() const requires (__is_container) { return this->_cap; }
		bool empty() const { return size() == 0; }
		
		allocator_type get_allocator() const { return allocator_type(__get_allocator()); }
		
		/// MARK: Accessors
		reference front() {
			__utl_expect(!empty());
			return { *__begin<I>()... };
		}
		const_reference front() const {
			__utl_expect(!empty());
			return { *__begin<I>()... };
		}
		reference back() {
			__utl_expect(!empty());
			return { *(__end<I>() - 1)... };
		}
		const_reference back() const {
			__utl_expect(!empty());
			return { *(__end<I>() - 1)... };
		}
		
		template <typename M, bool ForceConst = false>
		auto* __data_impl() const {
			constexpr std::size_t tuple_index = __index_map[M::index];
			using U = std::tuple_element_t<tuple_index, std::tuple<T...>>;
			using V = std::conditional_t<std::is_const_v<M> || ForceConst, U const, U>;
			return const_cast<V*>(__begin<tuple_index>());
		}
		
		template <typename Member> requires (__has_member<Member>()) && (!__is_view)
		auto* data() {
			return __data_impl<Member>();
		}
		
		pointer data() requires(__is_container) {
			return { __data_impl<std::tuple_element_t<I, __members>>()... };
		}
		const_pointer data() const requires(__is_container) {
			return { __data_impl<std::tuple_element_t<I, __members>>()... };
		}
		pointer data() requires(__is_view) {
			return { __data_impl<std::tuple_element_t<I, __members>>()... };
		}
		
		template <typename Member> requires (__has_member<Member>())
		auto* data() const {
			return __data_impl<Member, !__is_view>();
		}
		
		auto* data() const requires (sizeof...(T) == 1) {
			return __data_impl<std::tuple_element_t<0, __members>, !__is_view>();
		}
		
		/// At
		template <std::size_t TypeIndex> requires (__is_container)
		auto& __at_impl(std::size_t index) {
			return __begin<TypeIndex>()[index];
		}
		
		template <std::size_t TypeIndex> requires (__is_container)
		auto const& __at_impl(std::size_t index) const {
			return __begin<TypeIndex>()[index];
		}
		
		template <std::size_t TypeIndex> requires (__is_view)
		auto& __at_impl(std::size_t index) const {
			return __begin<TypeIndex>()[index];
		}
		
		template <typename Reference>
		Reference __at_impl(std::size_t index) {
			return { __begin<I>()[index]... };
		}
		
		template <typename Reference>
		Reference __at_impl(std::size_t index) const {
			return { __begin<I>()[index]... };
		}
		
		template <std::size_t TypeIndex>
		auto& at(std::size_t index) {
			__bounds_check(index);
			return __at_impl<TypeIndex>(index);
		}
		
		reference at(std::size_t index) requires (__is_container) {
			__bounds_check(index);
			return __at_impl<reference>(index);
		}
		
		const_reference at(std::size_t index) const requires (__is_container) {
			__bounds_check(index);
			return __at_impl<const_reference>(index);
		}
		
		reference at(std::size_t index) const requires(__is_view) {
			__bounds_check(index);
			return __at_impl<reference>(index);
		}
		
		/// Operator[]
		reference operator[](std::size_t index) requires (__is_container) {
			__bounds_check_assert(index);
			return __at_impl<reference>(index);
		}
		
		const_reference operator[](std::size_t index) const requires (__is_container) {
			__bounds_check_assert(index);
			return __at_impl<const_reference>(index);
		}
		
		reference operator[](std::size_t index) const requires(__is_view) {
			__bounds_check_assert(index);
			return __at_impl<reference>(index);
		}
		
		/// MARK: Begin, End
		std::tuple<T*...> __data_offset(std::ptrdiff_t offset) requires (__is_container) {
			return { (__begin<I>() + offset)... };
		}
		std::tuple<T const*...> __data_offset(std::ptrdiff_t offset) const requires (__is_container) {
			return { (__begin<I>() + offset)... };
		}
		std::tuple<T*...> __data_offset(std::ptrdiff_t offset) const requires (__is_view) {
			return { (__begin<I>() + offset)... };
		}
		/// Begin
		iterator begin() requires (__is_container)             { return iterator(this->_data); }
		const_iterator begin() const requires (__is_container) { return const_iterator(this->_data); }
		iterator begin() const requires (__is_view)            { return iterator(this->_data); }
		
		/// CBegin
		const_iterator cbegin() const { return const_iterator(this->_data); }
		
		/// RBegin
		reverse_iterator rbegin() requires (__is_container)             { return std::make_reverse_iterator(end()); }
		const_reverse_iterator rbegin() const requires (__is_container) { return std::make_reverse_iterator(end()); }
		reverse_iterator rbegin() const requires (__is_view)            { return std::make_reverse_iterator(end()); }
		
		/// CRBegin
		const_reverse_iterator crbegin() const { return std::make_reverse_iterator(cend()); }
		
		/// End
		iterator end() requires (__is_container) { return iterator(__data_offset(size())); }
		const_iterator end() const requires (__is_container) { return const_iterator(__data_offset(size())); }
		iterator end() const requires (__is_view) { return iterator(__data_offset(size())); }
		
		/// CEnd
		const_iterator cend() const { return const_iterator(__data_offset(size())); }
		
		/// REnd
		reverse_iterator rend() requires (__is_container)             { return std::make_reverse_iterator(begin()); }
		const_reverse_iterator rend() const requires (__is_container) { return std::make_reverse_iterator(begin()); }
		reverse_iterator rend() const requires (__is_view)            { return std::make_reverse_iterator(begin()); }
		
		/// CREnd
		const_reverse_iterator crend() const { return std::make_reverse_iterator(begin()); }
		
		/// MARK: Single Member Begin, End
		/// Begin
		template <typename M>
		auto begin() requires (__is_container)       { return __begin<M::index, std::is_const_v<M>>(); }
		template <typename M>
		auto begin() const requires (__is_container) { return __begin<M::index, true>(); }
		template <typename M>
		auto begin() const requires (__is_view)      { return __begin<M::index, std::is_const_v<M>>(); }
		
		/// CBegin
		template <typename M>
		auto cbegin() const { return __begin<M::index, true>(); }
		
		/// End
		template <typename M>
		auto end() requires (__is_container)       { return __end<M::index, std::is_const_v<M>>(); }
		template <typename M>
		auto end() const requires (__is_container) { return __end<M::index, true>(); }
		template <typename M>
		auto end() const requires (__is_view)      { return __end<M::index, std::is_const_v<M>>(); }
		
		/// CEnd
		template <typename M>
		auto cend() const { return __end<M::index, true>(); }
		
		/// RBegin
		template <typename M>
		auto rbegin() requires (__is_container)       { return std::make_reverse_iterator(end()); }
		template <typename M>
		auto rbegin() const requires (__is_container) { return std::make_reverse_iterator(end()); }
		template <typename M>
		auto rbegin() const requires (__is_view)      { return std::make_reverse_iterator(end()); }
		
		/// CRBegin
		template <typename M>
		auto crbegin() const { return std::make_reverse_iterator(cend()); }
		
		/// REnd
		template <typename M>
		auto rend() requires (__is_container)       { return std::make_reverse_iterator(begin()); }
		template <typename M>
		auto rend() const requires (__is_container) { return std::make_reverse_iterator(begin()); }
		template <typename M>
		auto rend() const requires (__is_view)      { return std::make_reverse_iterator(begin()); }
		
		/// CREnd
		template <typename M>
		auto crend() const { return std::make_reverse_iterator(cbegin()); }
		
		/// MARK: More Internals
		template <std::size_t J, bool ForceConst = false>
		auto* __begin() const {
			using U = std::tuple_element_t<J, std::tuple<T...>>;
			using MaybeConstU = std::conditional_t<ForceConst, std::add_const_t<U>, U>;
			return const_cast<MaybeConstU*>(std::get<J>(this->_data));
		}
		
		template <std::size_t J, bool ForceConst = false>
		auto* __end() const {
			return __begin<J, ForceConst>() + size();
		}
		
		template <std::size_t J, bool ForceConst = false>
		auto* __cap_end() const requires (__is_container) {
			return __begin<J, ForceConst>() + capacity();
		}
		
		std::size_t __itr_to_index(auto itr) const {
			difference_type const index = itr - begin();
			__utl_expect(index >= 0,      "invalid iterator");
			__utl_expect(index <= size(), "invalid iterator");
			return index;
		}
		
		std::size_t __recommend_size(std::size_t new_size) const {
			return std::max(new_size, size() * 2);
		}
		
		void __grow_to_least(std::size_t min_cap) {
			if (this->_cap <= min_cap) {
				reserve(__recommend_size(min_cap));
			}
		}
		
		void __construct(auto begin, auto end, auto&&... args) {
			for (; begin != end; ++begin) {
				__construct_at(begin, UTL_FORWARD(args)...);
			}
		}
		
		void __construct_at(auto address, auto&&... args) {
			std::allocator_traits<__allocator>::construct(__get_allocator(), address, UTL_FORWARD(args)...);
		}
		
		void __destroy(auto begin, auto end) {
			for (; begin != end; ++begin) {
				__destroy_at(begin);
			}
		}
		
		void __destroy_at(auto address) {
			std::allocator_traits<__allocator>::destroy(__get_allocator(), address);
		}
		
		void __uninitialized_move(auto begin, auto end, auto out) {
			for (; begin != end; ++begin, ++out) {
				__construct_at(out, std::move(*begin));
			}
		}
		
		void __uninitialized_copy(auto begin, auto end, auto out) {
			for (; begin != end; ++begin, ++out) {
				__construct_at(out, *begin);
			}
		}
		
		void __relocate(auto begin, auto end, auto out) {
			__uninitialized_move(begin, end, out);
			__destroy(begin, end);
		}
		
		void __destroy_this() {
			static_assert(__is_container);
			(__destroy(__begin<I>(), __end<I>()), ...);
			__deallocate(this->_data, size());
			this->_size = 0;
			this->_cap = 0;
		}
		
		void __bounds_check(std::size_t index) const {
			if (index >= size()) {
				__throw_out_of_bounds_error();
			}
		}
		
		void __bounds_check_assert(std::size_t index) const {
			__utl_bounds_check(index, 0, size());
		}
		
		void __throw_out_of_bounds_error() {
			throw std::logic_error("utl::structure_of_arrays<...>::out_of_bounds");
		}
		
		__data_base& __member_data() { return *this; }
		__data_base const& __member_data() const { return *this; }
		
		/// MARK: Memory Allocation
		struct __buffer_info {
			std::size_t total_size;
			std::size_t base_align;
			std::array<std::size_t, __member_count> member_offset;
		};
		
		static __buffer_info __make_buffer_info(std::size_t obj_count) {
			static constexpr std::array size = { sizeof(T)... };
			static constexpr std::array<std::size_t, __member_count + 1> alignment = {
				alignof(T)..., 1 /* append 1 here to make algorithm below simpler, because we don't have to branch on last element */
			};
			static constexpr std::size_t max_align = *std::max_element(alignment.begin(), alignment.end());
			
			__buffer_info result;
			result.base_align = max_align;
			
			std::size_t total_size = 0;
			for (std::size_t i = 0; i < __member_count; ++i) {
				result.member_offset[i] = total_size;
				std::size_t const i_size = size[i] * obj_count;
				total_size = round_up_pow_two(total_size + i_size, alignment[i + 1]);
			}
			
			result.total_size = total_size;
			return result;
		}
		
		static std::tuple<T*...> __decompose_buffer_pointer(void* ptr, __buffer_info const& info) {
			return { (T*)((char*)ptr + info.member_offset[I])... };
		}
		
		void* __allocate_raw(std::size_t size, std::size_t alignment) {
			__utl_expect(alignment <= __soa_max_align);
			
			size = ceil_divide_pow_two(size, __soa_max_align);
			void* const result = __get_allocator().allocate(size);
			__utl_assert((std::uintptr_t)result % alignment == 0, "memory not aligned");
			
			return result;
		}
		
		void __deallocate_raw(void* ptr, std::size_t size, std::size_t alignment) {
			size = ceil_divide_pow_two(size, __soa_max_align);
			if (ptr == nullptr) {
				__utl_assert(size == 0);
				return;
			}
			__get_allocator().deallocate(reinterpret_cast<__soa_max_aligned_storage*>(ptr), size);
		}
		
		std::tuple<T*...> __allocate(std::size_t obj_count) {
			auto const buffer_info = __make_buffer_info(obj_count);
			void* const buffer = __allocate_raw(buffer_info.total_size, buffer_info.base_align);
			return __decompose_buffer_pointer(buffer, buffer_info);
		}
		
		void __deallocate(std::tuple<T*...> const& ptr, std::size_t obj_count) {
			__deallocate((void*)std::get<0>(ptr), obj_count);
		}
		void __deallocate(void* ptr, std::size_t obj_count) {
			auto const buffer_info = __make_buffer_info(obj_count);
			__deallocate_raw(ptr, buffer_info.total_size, buffer_info.base_align);
		}
		
		__allocator& __get_allocator() {
			return static_cast<__allocator&>(*this);
		}
		__allocator const& __get_allocator() const {
			return static_cast<__allocator const&>(*this);
		}
	};
	
	/// MARK: Free Functions
	template <typename ST, typename Allocator = std::allocator<ST>>
	void swap(structure_of_arrays<ST, Allocator>& a, structure_of_arrays<ST, Allocator>& b) {
		a.swap(b);
	}

	
}

#endif __UTL_STRUCTURE_OF_ARRAYS_INCLUDED__
