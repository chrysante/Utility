#pragma once

#include <concepts>
#include <initializer_list>

#include "__base.hpp"
#include "iterator.hpp"
#include "vector.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T,
          std::size_t InlineCapacity = default_inline_capacity<T, std::allocator<T>>,
          typename A                 = std::allocator<T>>
class stack: private small_vector<T, InlineCapacity, A> {
public:
    using container_type = small_vector<T, InlineCapacity, A>;

public:
    /// MARK: Constructors
    __utl_interface_export stack() = default;
    __utl_interface_export explicit stack(container_type const& cont): container_type(cont) {}
    __utl_interface_export explicit stack(container_type&& cont): container_type(std::move(cont)) {}
    __utl_interface_export template <input_iterator_for<T> It, sentinel_for<It> S>
    __utl_interface_export explicit stack(It first, S last): container_type(first, last) {}
    __utl_interface_export stack(std::initializer_list<T> ilist): container_type(ilist) {}

    /// MARK: Queries
    using container_type::empty;
    explicit operator bool() const { return !empty(); }
    using container_type::size;
    __utl_interface_export __utl_nodiscard container_type& container() { return *this; }
    __utl_interface_export __utl_nodiscard container_type const& container() const { return *this; }

    /// MARK: Modifiers
    T const& push(T const& elem) { return this->push_back(elem); }
    T const& push(T&& elem) { return this->push_back(std::move(elem)); }
    template <typename... Args>
    requires std::constructible_from<T, Args...> T const& emplace(Args&&... args) {
        return this->emplace_back(UTL_FORWARD(args)...);
    }

    __utl_interface_export __utl_nodiscard T pop() {
        T result = top();
        this->pop_back();
        return result;
    }

    __utl_interface_export T& top() { return this->back(); }

    __utl_interface_export T const& top() const { return this->back(); }

    __utl_interface_export void swap(stack& rhs) { this->container_type::swap(static_cast<container_type&>(rhs)); }
};

} // namespace utl
