#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include <concepts>
#include "vector.hpp"

namespace utl {
	
	template <typename T,
			  std::size_t local_size = default_inline_capacity<T, std::allocator<T>>,
			  typename A = std::allocator<T>>
	class stack:
		private small_vector<T, local_size, A>
	{
	public:
		using container_type = small_vector<T, local_size, A>;
		
	public:
		/// MARK: Constructors
		stack() = default;
		
		explicit stack(container_type const& cont): container_type(cont) {}
		explicit stack(container_type&& cont): container_type(std::move(cont)) {}
		template <typename InputIt>
		stack(InputIt first, InputIt last): container_type(first, last) {}
		
		/// MARK: Queries
		using container_type::empty;
		explicit operator bool() const { return !empty(); }
		using container_type::size;
		container_type& container() { return *this; }
		container_type const& container() const { return *this; }
		
		T& peek() { return this->back(); }
		T const& peek() const { return this->back(); }
		
		/// MARK: Modifiers
		void push(T const& elem) { this->push_back(elem); }
		void push(T&& elem) { this->push_back(std::move(elem)); }
		template <typename... Args> requires std::constructible_from<T, Args...>
		void emplace(Args&&... args) { this->emplace_back(UTL_FORWARD(args)...); }
		
		[[ nodiscard ]] T pop() {
			T result = this->back();
			this->pop_back();
			return result;
		}
		
		void swap(stack& rhs) { this->container_type::swap(static_cast<container_type&>(rhs)); }
	};
	
}
