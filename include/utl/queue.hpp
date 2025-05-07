#ifndef UTL_QUEUE_HPP_
#define UTL_QUEUE_HPP_

#include <initializer_list>

#include <utl/__debug.hpp>
#include <utl/concepts.hpp>
#include <utl/scope_guard.hpp>
#include <utl/vector.hpp>

namespace utl {

template <typename T,
          std::size_t InlineCapacity =
              default_inline_capacity<T, std::allocator<T>>,
          typename A = std::allocator<T>>
class queue {
public:
    using container_type = small_vector<T, InlineCapacity, A>;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

    queue() = default;
    explicit queue(container_type const& cont): __cont(cont) {}
    explicit queue(container_type&& cont): __cont(std::move(cont)) {}
    template <input_iterator_for<T> It, sentinel_for<It> S>
    explicit queue(It first, S last): __cont(first, last) {}
    queue(std::initializer_list<T> ilist): __cont(ilist) {}

    bool empty() const { return __index == __cont.size(); }

    std::size_t size() const { return __cont.size() - __index; }

    /// MARK: Iterators
    iterator begin() { return __cont.begin() + __index; }
    const_iterator begin() const { return __cont.begin() + __index; }
    iterator end() { return __cont.end(); }
    const_iterator end() const { return __cont.end(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

    /// MARK: Modifiers
    T& push(T const& elem) { return emplace(elem); }
    T& push(T&& elem) { return emplace(std::move(elem)); }
    template <typename... Args>
    requires std::constructible_from<T, Args...>
    T& emplace(Args&&... args) {
        if (__cont.size() == __cont.capacity() &&
            __index >= __cont.capacity() / 2)
        {
            auto i = __cont.begin();
            auto end = i + size();
            auto j = __cont.begin() + __index;
            for (; i < end; ++i) {
                *i = std::move(*j);
            }
            __cont.resize(size());
            __index = 0;
        }
        return __cont.emplace_back(std::forward<Args>(args)...);
    }

    void clear() {
        __cont.clear();
        __index = 0;
    }

    __utl_interface_export T pop() {
        __utl_expect(!empty());
        ++__index;
        return std::move(__cont[__index - 1]);
    }

    T& front() { return __cont[__index]; }

    T const& front() const { return __cont[__index]; }

    T& back() { return __cont.back(); }

    T const& back() const { return __cont.back(); }

    void swap(queue& rhs) {
        __cont.swap(rhs.__cont);
        std::swap(__index, rhs.__index);
    }

private:
    container_type __cont;
    std::size_t __index = 0;
};

} // namespace utl

#endif // UTL_QUEUE_HPP_
