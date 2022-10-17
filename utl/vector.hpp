#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include "__memory_resource_base.hpp"
#include "common.hpp"
#include "concepts.hpp"
#include "utility.hpp"

#include <algorithm>
#include <bit>
#include <compare>
#include <exception>
#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <type_traits>

/// Synopsis
/*

 namespace utl {

     template <typename T, typename A = std::allocator<T>>
     class vector {
     public:
        // Implements the interface of std::vector<T, A>, with the exception that
        // iterator validity is not guaranteed after move operations. This enables the
        // implementation of small_vector<T, N, A> (see below).
     };

     template <typename T, std::size_t N = default_inline_capacity<T, std::allocator<T>>,
               typename A = std::allocator<T>>
     class small_vector: public vector<T, N> {
        // Implements the same constructors and assignment operators as vector<T, A>.
        // Inherits the remaining functionality of vector<T, A>.

        static constexpr std::size_t inline_capacity() { return N; }

        // returns true iff contents is stored in local buffer within the object.
        bool uses_inline_buffer() const noexcept;
     };

     // The maximum value so that sizeof(small_vector<T, default_inline_capacity<T, A>, A>) == 64
     template <typename T, typename A>
     constexpr std::size_t default_inline_capacity;

    namespace pmr {
        template <typename T>
        using vector = utl::vector<T, polymorphic_allocator<T>>;
        template <typename T>
        using small_vector = utl::vector<T, default_inline_capacity<T, polymorphic_allocator<T>>,
 polymorphic_allocator<T>>;
    }

 }

 */

namespace utl {

/// Edit or specialize this template to change the maximum capacity of utl::vector.
/// Using 32 bit size type reduces the memory footprint of the vector object from 24 bytes to 16 bytes..
/// With 32 bit size type and 1-byte data types the maximum capacity is 4GB, which might not suffice.
/// So for 1-byte types the default size type is 64 bit wide.
template <typename T>
struct vector_size_type_selector {
    using type = std::conditional_t<sizeof(T) == 1, std::size_t, std::uint32_t>;
};

template <typename T, typename A>
struct __vector_config;

/// Just to define it later
template <typename T, typename A>
constexpr std::size_t __small_vector_default_inline_capacity();
template <typename T, typename A>
constexpr std::size_t default_inline_capacity = __small_vector_default_inline_capacity<T, A>();

// MARK: - Forward Declarations
template <typename T, typename Allocator = std::allocator<T>>
class vector;

template <typename T,
          std::size_t N      = default_inline_capacity<T, std::allocator<T>>,
          typename Allocator = std::allocator<T>>
class small_vector;

namespace pmr {
template <typename T>
using vector = utl::vector<T, polymorphic_allocator<T>>;
template <typename T, std::size_t N = default_inline_capacity<T, polymorphic_allocator<T>>>
using small_vector = utl::small_vector<T, N, polymorphic_allocator<T>>;
} // namespace pmr

// MARK: - class vector
template <typename T, typename Allocator>
class vector: private Allocator {
public:
    // clang-format off
    template <typename... Args>
    static constexpr bool __constructible =
        requires(Args&&... args) { T(std::forward<Args>(args)...); } ||
        requires(Allocator alloc, Args&&... args) { T(std::allocator_arg, alloc, std::forward<Args>(args)...); } ||
        requires(Allocator alloc, Args&&... args) { T(std::forward<Args>(args)..., alloc); };
    // clang-format on

    /// MARK: Member Types
    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = typename __vector_config<T, Allocator>::size_type;
    using difference_type = std::ptrdiff_t;

    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = T*;
    using const_pointer   = T const*;

    using iterator       = pointer;
    using const_iterator = const_pointer;

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// MARK: Constructors
    /// (X)
    __utl_interface_export constexpr vector(std::size_t count,
                                            std::invocable<T*> auto&& f,
                                            Allocator const& alloc = Allocator()):
        vector(__private_tag{}, alloc, this->__allocate(count), count, count, false) {
        for (auto i = __begin(), end = __end(); i != end; ++i) {
            f(i);
        }
    }

    /// (Xa)
    __utl_interface_export constexpr vector(std::size_t count,
                                            utl::invocable_r<T> auto&& f,
                                            Allocator const& alloc = Allocator()):
        vector(
            count, [this, &f](T* p) { __construct_at(p, f()); }, alloc) {}

    /// (1)
    __utl_interface_export constexpr vector() noexcept(
        noexcept(Allocator())) requires std::constructible_from<Allocator>: vector(Allocator()) {}
    /// (2)
    __utl_interface_export constexpr explicit vector(Allocator const& alloc) noexcept:
        vector(__private_tag{}, alloc, nullptr, 0, 0, false) {}
    /// (3)
    __utl_interface_export constexpr vector(std::size_t count, T const& value, Allocator const& alloc = Allocator()):
        vector(
            count, [this, &value]() -> T const& { return value; }, alloc) {}

    /// (4)
    __utl_interface_export constexpr explicit vector(std::size_t count, Allocator const& alloc = Allocator()):
        vector(
            count, [this](T* p) { __construct_at(p); }, alloc) {}

    /// (4a)
    __utl_interface_export constexpr explicit vector(
        std::size_t count, utl::no_init_t, Allocator const& alloc = Allocator()) requires(std::is_trivial_v<T>):
        vector(
            count, [](T*) {}, alloc) {}

    /// (5)
    template <input_iterator_for<T> InputIt>
    __utl_interface_export
        __utl_always_inline constexpr vector(InputIt first, InputIt last, Allocator const& alloc = Allocator()):
        vector(
            std::distance(first, last), [this, first]() mutable -> decltype(auto) { return *first++; }, alloc) {}

    /// (6)
    __utl_interface_export constexpr vector(vector const& rhs) requires std::constructible_from<Allocator>:
        vector(rhs, Allocator()) {}

    /// (7)
    __utl_interface_export constexpr vector(vector const& rhs, Allocator const& alloc):
        vector(
            rhs.size(), [this, i = rhs.begin()]() mutable -> T const& { return *i++; }, alloc) {}

    /// (8)
    __utl_interface_export constexpr vector(vector&& rhs) noexcept(std::is_nothrow_move_constructible_v<T>):
        vector(std::move(rhs), Allocator()) {}

    /// (9)
    __utl_interface_export constexpr vector(vector&& rhs,
                                            Allocator const& alloc) noexcept(std::is_nothrow_move_constructible_v<T>):
        Allocator(alloc) {
        __move_constr_impl(std::move(rhs));
    }

    /// (10)
    __utl_interface_export constexpr vector(std::initializer_list<T> ilist, Allocator const& alloc):
        vector(
            ilist.size(), [this, i = ilist.begin()]() mutable -> T const& { return *i++; }, alloc) {}

    /// (10a)
    __utl_interface_export constexpr vector(std::initializer_list<T> ilist) requires(
        std::constructible_from<Allocator>):
        vector(ilist, Allocator()) {}

    /// MARK: Destructor
    __utl_interface_export constexpr ~vector() {
        __destroy_elems();
        if (!this->__uses_inline_buffer()) {
            this->__deallocate(this->__begin(), this->capacity());
        }
    }

    /// MARK: operator=
    /// (1)
    __utl_interface_export constexpr vector& operator=(vector const& rhs) & // clang-format off
        requires(std::assignable_from<T&, T const&> && std::constructible_from<T, T const&>)  // clang-format on
    {
        if UTL_UNLIKELY (&rhs == this) {
            return *this;
        }
        if (rhs.size() <= this->capacity()) {
            // No need to allocate
            auto const _rhs_mid_end = std::min(rhs.begin() + this->size(), rhs.end());
            // Assign all we have already constructed in this
            std::copy(rhs.begin(), _rhs_mid_end, this->begin());
            // Copy construct the rest from rhs
            __construct_range(_rhs_mid_end, rhs.end(), this->end());
            // Destroy our rest
            auto const _old_end = this->end();
            this->__set_size(rhs.size());
            __destroy_elems(end(), _old_end);
        }
        else {
            __destroy_elems();
            if (!this->__uses_inline_buffer()) {
                __deallocate(this->__begin(), capacity());
            }
            this->__set_begin(this->__allocate(rhs.size()));
            this->__set_size(rhs.size());
            this->__set_cap(rhs.size());
            this->__set_uses_inline_buffer(false);
            __construct_range(rhs.__begin(), rhs.__end(), this->__begin());
        }
        return *this;
    }

    /// (2)
    __utl_interface_export constexpr vector& operator=(vector&& rhs) & {
        if UTL_UNLIKELY (&rhs == this) {
            return *this;
        }
        if (rhs.__uses_inline_buffer() || __alloc() != rhs.__alloc() ||
            (__uses_inline_buffer() && rhs.__size() <= __cap())) {
            // We cannot steal the buffer
            if (rhs.size() <= capacity()) {
                // No need to allocate
                auto const _rhs_mid_end = std::min(rhs.__begin() + __size(), rhs.__end());
                // Assign all we have already constructed in this
                std::move(rhs.__begin(), _rhs_mid_end, __begin());
                // Copy construct the rest from rhs
                __construct_range(std::move_iterator(_rhs_mid_end), rhs.__move_end(), __end());
                // Destroy our rest
                auto const _old_end = __end();
                this->__set_size(rhs.__size());
                __destroy_elems(__end(), _old_end);
            }
            else {
                // We need to allocate
                this->~vector();
                this->__set_begin(this->__allocate(rhs.__size()));
                this->__set_size(rhs.size());
                this->__set_cap(rhs.size());
                this->__set_uses_inline_buffer(false);
                __construct_range(rhs.__move_begin(), rhs.__move_end(), __begin());
            }
        }
        else {
            // We can steal the buffer
            this->~vector();
            this->__set_begin(rhs.__begin());
            this->__set_size(rhs.__size());
            this->__set_cap(rhs.__cap());
            this->__set_uses_inline_buffer(false);
            rhs.__set_begin(nullptr);
            rhs.__set_size(0);
            rhs.__set_cap(0);
        }
        return *this;
    }

    /// (3)
    __utl_interface_export constexpr vector& operator=(std::initializer_list<T> ilist) & {
        if (ilist.size() <= this->capacity()) {
            // no need to allocate
            std::size_t const assign_count = std::min<std::size_t>(ilist.size(), __size());
            std::copy(ilist.begin(), ilist.begin() + assign_count, this->__begin());
            __construct_range(ilist.begin() + assign_count, ilist.end(), this->__end());
            auto const old_end = this->end();
            this->__set_size(ilist.size());
            __destroy_elems(end(), old_end);
        }
        else {
            this->~vector();
            this->__set_begin(this->__allocate(ilist.size()));
            this->__set_size(ilist.size());
            this->__set_cap(ilist.size());
            this->__set_uses_inline_buffer(false);
            __construct_range(ilist.begin(), ilist.end(), this->begin());
        }
        return *this;
    }

    /// MARK: get_allocator
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr allocator_type get_allocator() const noexcept {
        return *this;
    }

    /// MARK: at
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T& at(std::size_t pos) {
        return as_mutable(utl::as_const(*this).at(pos));
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T const& at(std::size_t pos) const {
        if (pos >= size()) {
            __throw_out_of_bound_error(pos);
        }
        return __begin()[pos];
    }

    /// MARK: operator[]
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T& operator[](std::size_t pos) {
        return utl::as_mutable(utl::as_const(*this).operator[](pos));
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T const& operator[](std::size_t pos) const {
        __utl_bounds_check(pos, 0, size());
        return __begin()[pos];
    }

    /// MARK: front
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T& front() noexcept {
        return as_mutable(utl::as_const(*this).front());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T const& front() const noexcept {
        __utl_expect(!empty(), "front() called on empty vector.");
        return *__begin();
    }

    /// MARK: back
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T& back() noexcept {
        return as_mutable(utl::as_const(*this).back());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T const& back() const noexcept {
        __utl_expect(!empty(), "back() called on empty vector.");
        return *(__end() - 1);
    }

    /// MARK: data
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T* data() noexcept {
        return const_cast<T*>(utl::as_const(*this).data());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr T const* data() const noexcept {
        return __begin();
    }

    /// MARK: begin
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr iterator begin() noexcept { return __begin(); }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator begin() const noexcept {
        return __begin();
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator cbegin() const noexcept {
        return __begin();
    }

    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr reverse_iterator rbegin() noexcept {
        return reverse_iterator(__end());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator
    rbegin() const noexcept {
        return reverse_Iterator(__end());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator
    crbegin() const noexcept {
        return reverse_Iterator(__end());
    }

    /// MARK: end
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr iterator end() noexcept { return __end(); }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator end() const noexcept {
        return __end();
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator cend() const noexcept {
        return __end();
    }

    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr reverse_iterator rend() noexcept {
        return reverse_iterator(__begin());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator rend() const noexcept {
        return reverse_Iterator(__begin());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator crend() const noexcept {
        return reverse_Iterator(begin());
    }

    /// MARK: empty
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr bool empty() const noexcept { return !size(); }

    /// MARK: size
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr std::size_t size() const noexcept {
        return __size();
    }

    /// MARK: max_size
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr static std::size_t max_size() noexcept {
        return std::numeric_limits<size_type>::max();
    }

    /// MARK: reserve
    __utl_interface_export constexpr void reserve(std::size_t new_cap) {
        if (new_cap <= capacity()) {
            return;
        }
        T* new_buffer = this->__allocate(new_cap);
        __construct_range(this->__move_begin(), this->__move_end(), new_buffer);
        __destroy_elems();
        if (!__uses_inline_buffer()) {
            this->__deallocate(this->__begin(), capacity());
        }
        auto const __size = size();
        this->__set_begin(new_buffer);
        this->__set_size(__size);
        this->__set_cap(new_cap);
        this->__set_uses_inline_buffer(false);
    }

    /// MARK: capacity
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr std::size_t capacity() const noexcept {
        return this->__cap();
    }

    /// MARK: shrink_to_fit
    __utl_interface_export constexpr void shrink_to_fit() {
        // no-op
    }

    /// MARK: clear
    __utl_interface_export constexpr void clear() noexcept {
        __destroy_elems();
        this->__set_size(0);
    }

    /// MARK: insert
    /// (1)
    __utl_interface_export constexpr iterator insert(const_iterator pos, T const& value) {
        return __insert_impl(pos, 1, [&value]() -> T const& { return value; });
    }

    /// (2)
    __utl_interface_export constexpr iterator insert(const_iterator pos, T&& value) {
        return __insert_impl(pos, 1, [&value]() -> T&& { return value; });
    }

    /// (3)
    __utl_interface_export constexpr iterator insert(const_iterator pos, size_type count, T const& value) {
        return __insert_impl(pos, count, [&value]() -> T const& { return value; });
    }

    /// (4)
    template <typename InputIt>
    __utl_interface_export constexpr iterator insert(const_iterator pos, InputIt first, InputIt last) {
        return __insert_impl(pos, std::distance(first, last), [first]() mutable -> decltype(auto) { return *first++; });
    }

    /// (5)
    __utl_interface_export constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return __insert_impl(pos, ilist.size(), [i = ilist.begin()]() mutable -> decltype(auto) { return *i++; });
    }

    /// MARK: push_back
    __utl_interface_export constexpr T& push_back(T const& t) { return emplace_back(t); }
    __utl_interface_export constexpr T& push_back(T&& t) { return emplace_back(std::move(t)); }

    /// MARK: emplace_back
    template <typename... Args>
    requires __constructible<Args...> __utl_interface_export constexpr T& emplace_back(Args&&... args) {
        if UTL_UNLIKELY (size() == capacity()) {
            __grow();
        }
        __construct_at(__end(), std::forward<Args>(args)...);
        this->__set_size(this->__size() + 1);
        return back();
    }

    /// MARK: pop_back
    __utl_interface_export constexpr void pop_back() noexcept {
        __utl_expect(!empty(), "pop_back() called on empty vector");
        this->__set_size(this->__size() - 1);
        __destroy_at(__end());
    }

    /// MARK: erase
    /// (1)
    __utl_interface_export constexpr iterator erase(const_iterator cpos) {
        if (empty()) {
            return end();
        }
        __utl_bounds_check(cpos, begin(), end());
        iterator const pos = const_cast<iterator>(cpos);
        this->__left_shift_range(pos + 1, end(), -1);
        __destroy_elems(end() - 1, end());
        __set_size(size() - 1);
        return pos;
    }
    /// (1a)
    __utl_interface_export constexpr void erase(std::size_t index) { erase(begin() + index); }
    /// (2)
    __utl_interface_export constexpr iterator erase(const_iterator cfirst, const_iterator clast) {
        if (empty()) {
            return end();
        }
        __utl_expect(cfirst <= clast);
        __utl_bounds_check(cfirst, begin(), end() + 1);
        __utl_bounds_check(clast, begin(), end() + 1);

        iterator const first = const_cast<iterator>(cfirst);
        iterator const last  = const_cast<iterator>(clast);

        if (first == last) {
            return last;
        }
        auto const erase_count = last - first;
        this->__left_shift_range(last, end(), -erase_count);
        __destroy_elems(end() - erase_count, end());
        __set_size(size() - erase_count);
        return first;
    }

    /// MARK: resize
    /// (1)
    __utl_interface_export constexpr void resize(std::size_t count) {
        __resize_impl(count, [&](auto i) { __construct_at(i); });
    }
    /// (2)
    __utl_interface_export constexpr void resize(std::size_t count, T const& value) {
        __resize_impl(count, [&](auto i) { __construct_at(i, value); });
    }
    /// (3)
    __utl_interface_export constexpr void resize(std::size_t count, no_init_t) {
        __resize_impl(count, [](auto) {});
    }

    /// MARK: swap
    __utl_interface_export constexpr void swap(vector& rhs) noexcept {
        if (this->__uses_inline_buffer() || rhs.__uses_inline_buffer() || this->_alloc() != rhs._alloc()) {
            // We may _not_ swap buffers.
            // Use naive implementation for now. May suffice in general.
            auto tmp = std::move(*this);
            *this    = std::move(rhs);
            rhs      = std::move(tmp);
        }
        else {
            // We may swap buffers.
            auto const rhsBegin = rhs.__begin();
            auto const rhsSize  = rhs.__size();
            auto const rhsCap   = rhs.__cap();
            rhs.__set_begin(this->__begin());
            rhs.__set_size(this->__size());
            rhs.__set_cap(this->__cap());
            this->__set_begin(rhsBegin);
            this->__set_size(rhsSize);
            this->__set_cap(rhsCap);
        }
    }

    /// MARK: - Private Interface
    template <typename, std::size_t, typename>
    friend class small_vector;

    void __move_constr_impl(vector<T, Allocator>&& rhs) {
        if (rhs.__uses_inline_buffer() || this->__alloc() != rhs.__alloc()) {
            // Here we need to move the individual elements
            this->__set_begin(this->__allocate(rhs.size()));
            this->__set_size(rhs.size());
            this->__set_cap(rhs.size());
            this->__set_uses_inline_buffer(false);
            __construct_range(rhs.__move_begin(), rhs.__move_end(), this->__begin());
        }
        else {
            // We may steal the buffer
            this->__set_begin(rhs.__begin());
            this->__set_size(rhs.size());
            this->__set_cap(rhs.__cap());
            this->__set_uses_inline_buffer(rhs.__uses_inline_buffer());
            rhs.__set_begin(rhs.__storage_begin());
            rhs.__set_size(0);
            rhs.__set_cap(rhs.capacity());
        }
    }

    constexpr iterator __insert_impl(const_iterator cpos, std::size_t count, auto&& f) {
        __utl_bounds_check(cpos, __begin(), __end() + 1);
        size_t const index = cpos - __begin();
        bool const is_end  = cpos == __end();
        if (__size() + count > __cap()) {
            reserve(__recommend(__size() + count));
        }
        if (is_end) {
            auto const pos = __end();
            for (auto i = pos, end = pos + count; i != end; ++i) {
                __construct_at(i, f());
            }
            __set_size(__size() + count);
            return pos;
        }
        else {
            auto const end                   = __end();
            auto const pos                   = __begin() + index;
            size_t const construct_count     = std::min(count, __size() - index);
            auto const construct_range_begin = end - construct_count;
            __construct_range(std::move_iterator(construct_range_begin),
                              std::move_iterator(end),
                              construct_range_begin + count);
            __right_shift_range(pos, construct_range_begin, count);
            std::size_t const init_count = std::min<std::size_t>(count, end - pos);
            auto i                       = pos;
            for (auto const end = pos + init_count; i != end; ++i) {
                *i = f();
            }
            for (auto const end = pos + count; i != end; ++i) {
                __construct_at(i, f());
            }
            __set_size(__size() + count);
            return pos;
        }
    }

    constexpr void __resize_impl(std::size_t count, auto&& constr) {
        if (size() == count) {
            return;
        }
        else if (size() > count) {
            __destroy_elems(begin() + count, end());
            this->__set_size(count);
        }
        else /* we grow */ {
            auto const old_size = size();
            if (count > capacity()) {
                auto const target_cap = __recommend(count);
                auto const new_buffer = this->__allocate(target_cap);
                __construct_range(__move_begin(), __move_end(), new_buffer);
                __destroy_elems();
                if (!__uses_inline_buffer()) {
                    this->deallocate(__begin(), capacity());
                }
                this->__set_begin(new_buffer);
                this->__set_size(count);
                this->__set_cap(target_cap);
                this->__set_uses_inline_buffer(false);
            }
            else {
                this->__set_size(count);
            }
            for (auto i = __begin() + old_size, e = __end(); i < e; ++i) {
                constr(i);
            }
        }
    }

    constexpr std::size_t __recommend(std::size_t new_size) noexcept {
        using conf               = __vector_config<T, Allocator>;
        new_size                 = std::max(new_size, conf::minimum_allocation_count);
        constexpr std::size_t ms = max_size();
        __utl_assert(new_size <= ms, "max_size exceeded");
        auto const cap      = capacity();
        auto const next_cap = cap * conf::growth_factor;
        if UTL_UNLIKELY (next_cap >= ms)
            return ms;
        return std::bit_ceil(std::max<std::size_t>(next_cap, new_size));
    }

    explicit constexpr vector(__private_tag, Allocator const& alloc, no_init_t): Allocator(alloc) {}

    constexpr Allocator& __alloc() noexcept { return static_cast<Allocator&>(*this); }
    constexpr Allocator const& __alloc() const noexcept { return static_cast<Allocator const&>(*this); }

    constexpr T* __allocate(std::size_t n) { return n != 0 ? __alloc().allocate(n) : nullptr; }

    constexpr void __deallocate(T* ptr, std::size_t n) {
        if (ptr) {
            __alloc().deallocate(ptr, n);
        }
    }

    template <typename... Args>
    constexpr void __construct_at(T* address, Args&&... args) {
        std::allocator_traits<Allocator>::construct(*this, address, UTL_FORWARD(args)...);
    }
    constexpr void __destroy_at(T* address) { std::allocator_traits<Allocator>::destroy(*this, address); }

    constexpr void __grow() {
        __utl_expect(capacity() == size(), "no need to grow");
        reserve(__recommend(size() + 1));
    }

    constexpr void __destroy_elems() { __destroy_elems(begin(), end()); }
    constexpr void __destroy_elems(T* begin, T* end) {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            for (auto i = begin; i < end; ++i) {
                __destroy_at(i);
            }
        }
    }

    template <typename Iter>
    constexpr void __construct_range(Iter begin, Iter end, T* out) {
        for (auto i = begin; i != end; ++i, ++out) {
            __construct_at(out, *i);
        }
    }

    constexpr static void __left_shift_range(T* begin, T* end, std::ptrdiff_t offset) {
        __utl_expect(offset <= 0, "offset must non-positive");
        for (auto i = begin + offset, j = begin; j < end; ++i, ++j) {
            *i = std::move(*j);
        }
    }

    constexpr static void __right_shift_range(T* begin, T* end, std::ptrdiff_t offset) {
        __utl_expect(offset >= 0, "offset must be non-negative");
        for (auto i = end + offset - 1, j = end - 1; j >= begin; --i, --j) {
            *i = std::move(*j);
        }
    }

    __utl_noinline void __throw_out_of_bound_error(size_type pos) const {
        throw std::out_of_range("utl::vector out of range");
    }

    constexpr vector(__private_tag, T* begin, std::size_t size, std::size_t capacity, bool inplace) noexcept:
        Allocator(),
        __begin_inline_(begin, inplace),
        __size_((size_type)size),
        __cap_(static_cast<size_type>(capacity)) {}

    constexpr vector(
        __private_tag, auto&& alloc, T* begin, std::size_t size, std::size_t capacity, bool inplace) noexcept:
        Allocator(UTL_FORWARD(alloc)),
        __begin_inline_(begin, inplace),
        __size_((size_type)size),
        __cap_((size_type)capacity) {}

    constexpr pointer __begin() const noexcept { return __begin_inline_.pointer(); }
    constexpr void __set_begin(pointer p) noexcept { __begin_inline_.pointer(p); }
    constexpr auto __size() const noexcept { return __size_; }
    constexpr void __set_size(std::size_t size) noexcept { __size_ = narrow_cast<size_type>(size); }
    constexpr auto __cap() const noexcept { return __cap_; }
    constexpr void __set_cap(std::size_t cap) noexcept { __cap_ = narrow_cast<size_type>(cap); }

    constexpr bool __uses_inline_buffer() const noexcept { return __begin_inline_.integer(); }

    constexpr void __set_uses_inline_buffer(bool b) noexcept { __begin_inline_.integer(b); }
    constexpr pointer __end() const noexcept { return __begin() + __size_; }

    constexpr auto __move_begin() const noexcept { return std::move_iterator(__begin()); }
    constexpr auto __move_end() const noexcept { return std::move_iterator(__end()); }

    pointer_int_pair<T*, bool, 1> __begin_inline_;
    size_type __size_, __cap_;

    pointer __storage_begin() noexcept { return nullptr; }
    pointer __storage_end() noexcept { return nullptr; }

    const_pointer __storage_begin() const noexcept { return nullptr; }
    const_pointer __storage_end() const noexcept { return nullptr; }
};

template <typename T, typename A, typename B>
bool operator==(vector<T, A> const& lhs, vector<T, B> const& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    auto i   = lhs.begin();
    auto j   = rhs.begin();
    auto end = lhs.end();
    for (; i != end; ++i, ++j) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}

template <typename T, typename A> // clang-format off
requires requires(std::ostream& str, T&& t) { { str << t } -> std::convertible_to<std::ostream&>; } // clang-format on
std::ostream& operator<<(std::ostream& _str, utl::vector<T, A> const& v) {
    auto& str = [](auto& x) -> decltype(auto) { return x; }(_str);
    str << "[";
    bool first = true;
    for (auto const& i : v) {
        str << (first ? ((void)(first = false), "") : ", ") << i;
    }
    return str << "]";
}

/// MARK: - class small_vector
template <typename T, std::size_t N, typename Allocator>
class small_vector: public vector<T, Allocator> {
public:
    using __utl_base = vector<T, Allocator>;

    /// MARK: Member Types
    using typename __utl_base::allocator_type;
    using typename __utl_base::difference_type;
    using typename __utl_base::size_type;
    using typename __utl_base::value_type;

    using typename __utl_base::const_pointer;
    using typename __utl_base::const_reference;
    using typename __utl_base::pointer;
    using typename __utl_base::reference;

    using typename __utl_base::const_iterator;
    using typename __utl_base::iterator;

    using typename __utl_base::const_reverse_iterator;
    using typename __utl_base::reverse_iterator;

    /// MARK: Constructors
    /// (1)
    __utl_interface_export constexpr small_vector() noexcept(
        noexcept(Allocator())) requires std::is_default_constructible_v<Allocator>:
        __utl_base(__private_tag{}, __storage_begin(), {}, N, true) {}

    /// (2)
    __utl_interface_export constexpr explicit small_vector(Allocator const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, __storage_begin(), {}, N, true) {}

    /// (3)
    __utl_interface_export constexpr small_vector(std::size_t count,
                                                  T const& value,
                                                  Allocator const& alloc = Allocator()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
        for (auto i = this->begin(); i != this->end(); ++i) {
            this->__construct_at(i, value);
        }
    }

    /// (4)
    __utl_interface_export constexpr explicit small_vector(std::size_t count, Allocator const& alloc = Allocator()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
        for (auto i = this->begin(); i != this->end(); ++i) {
            this->__construct_at(i);
        }
    }

    /// (4a)
    __utl_interface_export constexpr explicit small_vector(
        std::size_t count, utl::no_init_t, Allocator const& alloc = Allocator()) requires(std::is_trivial_v<T>):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
    }

    /// (5)
    template <typename InputIt>
    __utl_interface_export constexpr small_vector(InputIt first,
                                                  InputIt last,
                                                  Allocator const& alloc = Allocator()) // clang-format off
        requires requires { { *first } -> std::convertible_to<T>; }: // clang-format on
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(std::distance(first, last));
        this->__construct_range(first, last, this->begin());
    }

    /// (6)
    __utl_interface_export constexpr small_vector(vector<T, Allocator> const& rhs): small_vector(rhs, Allocator()) {}

    /// (6a)
    __utl_interface_export constexpr small_vector(small_vector const& rhs): small_vector(rhs, Allocator()) {}

    /// (7)
    __utl_interface_export constexpr small_vector(vector<T, Allocator> const& rhs, Allocator const& alloc):
        __utl_base(__private_tag{}, alloc, no_init) {
        __copy_constructor_impl(rhs);
    }

    /// (7a)
    __utl_interface_export constexpr small_vector(small_vector const& rhs, Allocator const& alloc):
        small_vector(static_cast<vector<T, Allocator> const&>(rhs), alloc) {}

    /// (8)
    __utl_interface_export constexpr small_vector(vector<T, Allocator>&& rhs) noexcept:
        small_vector(std::move(rhs), Allocator()) {}
    /// (8a)
    __utl_interface_export constexpr small_vector(small_vector&& rhs) noexcept:
        small_vector(std::move(rhs), Allocator()) {}

    /// (9)
    __utl_interface_export constexpr small_vector(vector<T, Allocator>&& rhs, Allocator const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, no_init) {
        __move_constructor_impl(std::move(rhs));
    }

    /// (9a)
    __utl_interface_export constexpr small_vector(small_vector&& rhs, Allocator const& alloc) noexcept:
        small_vector(static_cast<vector<T, Allocator> const&>(rhs), alloc) {}

    /// (10)
    __utl_interface_export constexpr small_vector(std::initializer_list<T> ilist, Allocator const& alloc = Allocator()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(ilist.size());
        this->__construct_range(ilist.begin(), ilist.end(), this->__begin());
    }

    /// MARK: operator=
    using __utl_base::operator=;
    /// (1)
    __utl_interface_export constexpr small_vector& operator=(small_vector const& other) & {
        static_cast<__utl_base&>(*this) = static_cast<__utl_base const&>(other);
        return *this;
    }
    /// (2)
    __utl_interface_export constexpr small_vector& operator=(small_vector&& other) & noexcept(
        std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
        std::allocator_traits<Allocator>::is_always_equal::value) {
        static_cast<__utl_base&>(*this) = static_cast<__utl_base&&>(other);
        return *this;
    }
    /// (3)
    __utl_interface_export constexpr small_vector& operator=(std::initializer_list<T> ilist) & {
        static_cast<__utl_base&>(*this) = ilist;
        return *this;
    }

    /// MARK: inline_capacity
    __utl_interface_export constexpr static std::size_t inline_capacity() noexcept { return N; }

    /// MARK: - Private Interface
    friend class vector<T, Allocator>;
    template <typename, std::size_t, typename>
    friend class small_vector;

    constexpr void __count_constructor_prep(std::size_t count) {
        if (count <= N) {
            this->__set_begin(this->__storage_begin());
            this->__set_size(count);
            this->__set_cap(N);
            this->__set_uses_inline_buffer(true);
        }
        else {
            this->__set_begin(this->__allocate(count));
            this->__set_size(count);
            this->__set_cap(count);
            this->__set_uses_inline_buffer(false);
        }
    }

    void __copy_constructor_impl(auto const& rhs) {
        if (rhs.size() <= N) {
            this->__set_begin(this->__storage_begin());
            this->__set_size(rhs.size());
            this->__set_cap(N);
            this->__set_uses_inline_buffer(true);
        }
        else {
            this->__set_begin(this->__allocate(rhs.size()));
            this->__set_size(rhs.size());
            this->__set_cap(rhs.size());
            this->__set_uses_inline_buffer(false);
        }
        this->__construct_range(rhs.begin(), rhs.end(), this->begin());
    }

    void __move_constructor_impl(auto&& rhs) {
        if (rhs.size() <= N) /* contents of rhs fits into our local buffer */ {
            this->__set_begin(this->__storage_begin());
            this->__set_size(rhs.size());
            this->__set_cap(N);
            this->__set_uses_inline_buffer(true);
            this->__construct_range(rhs.__move_begin(), rhs.__move_end(), this->__begin());
        }
        else if (rhs.__uses_inline_buffer()) /* rhs uses local buffer, we need to allocate */ {
            __utl_assert(!rhs.empty());
            this->__set_begin(this->__allocate(rhs.size()));
            this->__set_size(rhs.size());
            this->__set_cap(rhs.size());
            this->__set_uses_inline_buffer(false);
            this->__construct_range(rhs.__move_begin(), rhs.__move_end(), this->__begin());
        }
        else /* we can swap buffers */ {
            this->__set_begin(rhs.__begin());
            this->__set_size(rhs.__size());
            this->__set_cap(rhs.__cap());
            this->__set_uses_inline_buffer(rhs.__uses_inline_buffer());
            rhs.__set_begin(rhs.__storage_begin());
            rhs.__set_size(0);
            rhs.__set_cap(rhs.__cap());
            rhs.__set_uses_inline_buffer(rhs.__cap() > 0);
        }
    }

    pointer __storage_begin() noexcept { return reinterpret_cast<pointer>(__storage); }
    pointer __storage_end() noexcept { return reinterpret_cast<pointer>(__storage) + N; }

    const_pointer __storage_begin() const noexcept { return reinterpret_cast<const_pointer>(__storage); }
    const_pointer __storage_end() const noexcept { return reinterpret_cast<const_pointer>(__storage) + N; }

    __utl_base& __as_base() noexcept { return static_cast<__utl_base&>(*this); }
    __utl_base const& __as_base() const noexcept { return static_cast<__utl_base const&>(*this); }

    alignas(N != 0 ? alignof(T) : 1) char __storage[sizeof(T) * N];
};

/// MARK: struct __vector_config
template <typename T, typename A>
struct __vector_config {
    static constexpr std::size_t growth_factor = 2;

    static constexpr std::size_t minimum_allocation_count = 4; // default_inline_capacity<T, A>;

    static constexpr std::size_t small_vector_target_size = 64;

    using size_type = typename vector_size_type_selector<T>::type;
};

template <typename T, typename A>
constexpr std::size_t __small_vector_default_inline_capacity() {
    auto constexpr base_vector_size = sizeof(utl::vector<T, A>);
    std::size_t const target_count  = (__vector_config<T, A>::small_vector_target_size - base_vector_size) / sizeof(T);
    return std::max<std::size_t>(target_count, 0);
}

} // namespace utl
