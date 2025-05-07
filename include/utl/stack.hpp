#pragma once

#include <concepts>
#include <initializer_list>

#include <utl/__base.hpp>
#include <utl/concepts.hpp>
#include <utl/vector.hpp>

namespace utl {

template <typename T,
          std::size_t InlineCapacity =
              default_inline_capacity<T, std::allocator<T>>,
          typename A = std::allocator<T>>
class stack: private small_vector<T, InlineCapacity, A> {
public:
    using container_type = small_vector<T, InlineCapacity, A>;

public:
    /// MARK: Constructors
    __utl_interface_export stack() = default;
    __utl_interface_export explicit stack(container_type const& cont):
        container_type(cont) {}
    __utl_interface_export explicit stack(container_type&& cont):
        container_type(std::move(cont)) {}
    template <input_iterator_for<T> It, sentinel_for<It> S>
    __utl_interface_export explicit stack(It first, S last):
        container_type(first, last) {}
    __utl_interface_export stack(std::initializer_list<T> ilist):
        container_type(ilist) {}

    /// MARK: Queries
    using container_type::empty;
    [[deprecated]] explicit operator bool() const { return !empty(); }
    using container_type::size;
    __utl_nodiscard __utl_interface_export container_type const&
    container() const& {
        return *this;
    }
    __utl_nodiscard __utl_interface_export container_type& container() & {
        return *this;
    }
    __utl_nodiscard __utl_interface_export container_type const&&
    container() const&& {
        return std::move(*this);
    }
    __utl_nodiscard __utl_interface_export container_type&& container() && {
        return std::move(*this);
    }

    /// MARK: Iterators
    using container_type::begin;
    using container_type::cbegin;
    using container_type::cend;
    using container_type::crbegin;
    using container_type::crend;
    using container_type::end;
    using container_type::rbegin;
    using container_type::rend;

    /// MARK: Modifiers
    T& push(T const& elem) { return this->push_back(elem); }
    T& push(T&& elem) { return this->push_back(std::move(elem)); }
    template <typename... Args>
    requires std::constructible_from<T, Args...>
    T& emplace(Args&&... args) {
        return this->emplace_back(UTL_FORWARD(args)...);
    }

    using container_type::clear;

    __utl_interface_export T pop() {
        T result = top();
        this->pop_back();
        return result;
    }

    __utl_interface_export T& top() { return this->back(); }

    __utl_interface_export T const& top() const { return this->back(); }

    __utl_interface_export void swap(stack& rhs) {
        this->container_type::swap(static_cast<container_type&>(rhs));
    }
};

} // namespace utl
