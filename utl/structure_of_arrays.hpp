#pragma once

#ifndef __UTL_STRUCTURE_OF_ARRAYS_HPP_INCLUDED__
#define __UTL_STRUCTURE_OF_ARRAYS_HPP_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__memory_resource_base.hpp"
#include "common.hpp"
#include "algorithm.hpp"
#include "bit.hpp"
#include <tuple>
#include <span>


namespace utl {
	
	template <typename>
	class structure_of_arrays;
	
	template <typename... T>
	requires (type_sequence<T...>::unique)
	class structure_of_arrays<std::tuple<T...>> {
	public:
		template <typename U>
		static constexpr std::size_t index_of = type_sequence<T...>::template index_of<U>;
		
		template <typename U>
		static constexpr bool contains = type_sequence<T...>::template contains<U>;
		
	private:
		template <typename... U>
		class _reference {
			static_assert((std::is_same_v<std::remove_const_t<U>, T> && ...));
		public:
			explicit _reference(U&... t): _ptr(&t...) {}
			
			template <typename V>
			requires(contains<V>)
			auto& get() const { return *std::get<index_of<V>>(_ptr); }
			
			operator _reference<std::add_const_t<U>...>() const {
				return utl::bit_cast<_reference<std::add_const_t<U>...>>(*this);
			}
			
			operator std::tuple<T...>() const {
				return { get<T>()... };
			}
			
		private:
			std::tuple<U*...> _ptr;
		};
		
	public:
		using value_type = std::tuple<T...>;
		using reference = _reference<T...>;
		using const_reference = _reference<T const...>;
		
	public:
		// MARK: - Lifetime
		structure_of_arrays() = default;
		
		structure_of_arrays(pmr::memory_resource* r):
			_alloc(((std::void_t<T>)0, r)...)
		{}
		
		~structure_of_arrays() { _destroy(); }
		
		// MARK: - observers
		std::size_t size() const { return _size; }
		std::size_t capacity() const { return _cap; }
		bool empty() const { return size() == 0; }
		
		// MARK: - modifiers
		void push_back(value_type const& elem) {
			this->push_back(std::get<T>(elem)...);
		}
		void push_back(const_reference elem) {
			this->push_back(elem.template get<T>()...);
		}
		template <typename... U>
		//requires (sizeof...(T) == sizeof...(U)) && (convertible_to<U, T> && ...)
		void push_back(U&&... u) {
			if (this->size() == this->capacity()) {
				_grow();
			}
			//((new (this->template _get_array_ptr<T>() + _size) T(UTL_FORWARD(u))), ...);
			//(__push_back_one<T>(UTL_FORWARD(u)), ...);
			++_size;
		}

		template <typename V, typename U>
		void __push_back_one(U&& u) {
			void* ptr = this->template _get_array_ptr<V>() + _size;
			new (ptr) V(UTL_FORWARD(u));
		}
		
		void reserve(std::size_t n) {
			if (n > capacity()) {
				_grow_to(n);
			}
		}
		
		void pop_back() {
			([&] {
				auto const buffer = this->template _get_array_ptr<T>();
				// _destroy last element
				(buffer + size() - 1)->~T();
			}(), ...);
			--_size;
		}
		
		void erase(std::size_t index) {
			__utl_bounds_check(index, 0, size());
			([&] {
				auto const buffer = this->template _get_array_ptr<T>();
				auto const elem = buffer + index;
				
				// shift following elements
				utl::for_each(elem, buffer + size() - 1, elem + 1, [](auto& a, auto& b) {
					a = std::move(b);
				});
				
				// _destroy last element
				(buffer + size() - 1)->~T();
			}(), ...);
			--_size;
		}
		
		void clear() {
			(for_each<T>([](T& t){
				t.~T();
			}), ...);
			_size = 0;
		}
		
		void insert_at(std::size_t index, value_type const& elem) {
			insert_at(index, elem.template get<T>()...);
		}
		void insert_at(std::size_t index, const_reference elem) {
			insert_at(index, elem.template get<T>()...);
		}
		template <typename... U> requires (sizeof...(T) == sizeof...(U) && (std::is_convertible<U, T>::value && ...))
		void insert_at(std::size_t index, U&&... u) {
			if (this->size() == this->capacity()) {
				_grow();
			}
			([&] {
				auto const buffer = this->template _get_array_ptr<T>();
				auto const elem = buffer + index;
				
				auto const back = buffer + size();
				// construct back from back - 1
				new (back) T(std::move(*(back - 1)));
				// shift
				for (auto i = back - 2, j = back - 1; i >= elem; --i, --j) {
					*j = std::move(*i);
				}
				// assign elem
				*elem = std::forward<U>(u);
			}(), ...);
			++_size;
		}
		
		/// MARK: - for_each
		// mutable
		template <typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(invocable<U&, V&...> auto&& f) {
			this->for_each<utl::direction::forward, U, V...>(UTL_FORWARD(f));
		}
		template <typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(invocable<std::size_t, U&, V&...> auto&& f) {
			this->for_each<utl::direction::forward, U, V...>(UTL_FORWARD(f));
		}
		template <utl::direction dir, typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(invocable<U&, V&...> auto&& f) {
			utl::for_each<dir>(UTL_FORWARD(f), this->array<U>(), this->array<V>()...);
		}
		template <utl::direction dir, typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(invocable<std::size_t, U&, V&...> auto&& f) {
			utl::for_each<dir>(UTL_FORWARD(f), this->array<U>(), this->array<V>()...);
		}
		// const
		template <typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(/*invocable<U const&, V const&...>*/ auto&& f) const {
			this->for_each<utl::direction::forward, U, V...>(UTL_FORWARD(f));
		}
//		template <typename U, typename... V> requires (contains<U> && (contains<V> && ...))
//		auto for_each(/*invocable<std::size_t, U const&, V const&...>*/ auto&& f) const {
//			this->for_each<utl::direction::forward, U, V...>(UTL_FORWARD(f));
//		}
		template <utl::direction dir, typename U, typename... V> requires (contains<U> && (contains<V> && ...))
		auto for_each(/*invocable<U const&, V const&...>*/ auto&& f) const {
			utl::for_each<dir>(UTL_FORWARD(f), this->array<U>(), this->array<V>()...);
		}
//		template <utl::direction dir, typename U, typename... V> requires (contains<U> && (contains<V> && ...))
//		auto for_each(/*invocable<std::size_t, U const&, V const&...>*/ auto&& f) const {
//			utl::for_each<dir>(UTL_FORWARD(f), this->array<U>(), this->array<V>()...);
//		}
		
		// reference types
		template <utl::direction dir = utl::direction::forward>
		void for_each(utl::invocable<reference> auto&& f) {
			_for_each_impl(*this, UTL_FORWARD(f));
		}
		
		template <utl::direction dir = utl::direction::forward>
		void for_each(utl::invocable<const_reference> auto&& f) const {
			_for_each_impl(*this, UTL_FORWARD(f));
		}
		
	private:
		template <utl::direction dir = utl::direction::forward>
		static void _for_each_impl(auto&& soa, auto&& f) {
			if constexpr (dir == utl::direction::forward) {
				for (std::size_t i = 0, end = soa.size(); i < end; ++i) {
					f(soa[i]);
				}
			}
			else {
				for (std::size_t i = soa.size(); i > 0;) {
					--i;
					f(soa[i]);
				}
			}
		}
	public:
		
		template <typename ... U, typename G> requires ((contains<U> && ...))
		auto find_if(G&& f) {
			return this->find_if<utl::direction::forward, U...>(std::forward<G>(f));
		}
		template <utl::direction dir, typename ... U, typename G> requires ((contains<U> && ...))
		auto find_if(G&& f) {
			return utl::find_if<dir>(std::forward<G>(f), this->array<U>()...);
		}
		template <typename ... U, typename G> requires ((contains<U> && ...))
		auto find_if(G&& f) const {
			return this->find_if<utl::direction::forward, U...>(std::forward<G>(f));
		}
		template <utl::direction dir, typename ... U, typename G> requires ((contains<U> && ...))
		auto find_if(G&& f) const {
			return utl::find_if<dir>(std::forward<G>(f), this->array<U>()...);
		}
		
		// MARK: - accessors
		reference operator[](std::size_t index) {
			__utl_bounds_check(index, 0, size());
			return reference(this->template _get_array_ptr<T>()[index]...);
		}
		
		const_reference operator[](std::size_t index) const {
			__utl_bounds_check(index, 0, size());
			return const_reference(this->template _get_array_ptr<T>()[index]...);
		}

		template <typename U> requires (contains<U>)
		std::span<U> array() {
			return std::span<U>(_get_array_ptr<U>(), size());
		}
		
		template <typename U> requires (contains<U>)
		std::span<U const> array() const {
			return std::span<U const>(_get_array_ptr<U>(), size());
		}
		
		template <typename U> requires (contains<U>)
		U& get(std::size_t index) {
			__utl_bounds_check(index, 0, size());
			return _get_array_ptr<U>()[index];
		}
		
		template <typename U> requires (contains<U>)
		U const& get(std::size_t index) const {
			__utl_bounds_check(index, 0, size());
			return _get_array_ptr<U>()[index];
		}
		
		template <typename U> requires (contains<U>)
		U* data() {
			return this->template _get_array_ptr<U>();
		}
		
		template <typename U> requires (contains<U>)
		U const* data() const {
			return this->template _get_array_ptr<U>();
		}
		
		
	private:
		template <typename T_>
		void _grow_to_one(std::size_t new_cap) {
			bool const is_empty = empty();
			std::size_t const old_cap = capacity();

			auto& alloc = _get_allocator<T_>();
			T_* const new_buffer = static_cast<T_*>(alloc.allocate(new_cap));
			auto const old_buffer = this->template _get_array_ptr<T_>();
			utl::for_each(old_buffer, old_buffer + size(), new_buffer, [&](auto& i, auto& j) {
				new (&j) T_(std::move(i));
				destroy(i);
				});

			if (!is_empty) {
				alloc.deallocate(old_buffer, old_cap);
			}

			this->template _set_array_ptr<T_>(new_buffer);
		}

		void _grow_to(std::size_t const new_cap) {
			(_grow_to_one<T>(new_cap), ...);

			_cap = new_cap;
		}
		
		void _grow() {
			auto constexpr growth_factor = 2;
			std::size_t const new_cap = empty() ? 1 : capacity() * growth_factor;
			_grow_to(new_cap);
		}
		
		void _destroy() {
			if (!empty()) {
				((this->template _get_allocator<T>().deallocate(this->_get_array_ptr<T>(), capacity())), ...);
			}
		}
		
		template <typename U> requires (contains<U>)
		U*& _get_array_ptr() { return std::get<index_of<U>>(_arrays); }
		template <typename U> requires (contains<U>)
		U const* _get_array_ptr() const { return std::get<index_of<U>>(_arrays); }
		
		template <typename U> requires (contains<U>)
		void _set_array_ptr(U* ptr) { std::get<index_of<U>>(_arrays) = ptr; }
		
		template <typename U> requires (contains<U>)
		auto& _get_allocator() { return std::get<index_of<U>>(_alloc); }
						  
	private:
		std::tuple<T*...> _arrays = {};
		std::tuple<pmr::polymorphic_allocator<T>...> _alloc;
		
		std::size_t _size = 0, _cap = 0;
	};
	
}

#endif // __UTL_STRUCTURE_OF_ARRAYS_HPP_INCLUDED__
