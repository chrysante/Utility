#pragma once

#include <algorithm>
#include <bit>
#include <compare>
#include <exception>
#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>

#include "__base.hpp"
#include "__memory_resource_base.hpp"
#include "__ranges_base.hpp"
#include "common.hpp"
#include "concepts.hpp"
#include "utility.hpp"

_UTL_SYSTEM_HEADER_

/// MARK: Synopsis
/// ```
/// namespace utl {
///
///     template <typename T, typename A = std::allocator<T>>
///     class vector {
/// ```
///        Implements the interface of `std::vector<T,A>` with the exception that
///        iterator validity is not guaranteed after move operations. This enables the
///        implementation of `small_vector<T,N,A>` (see below).
/// ```
///     };
///
///     template <typename T, std::size_t N = default_inline_capacity<T, std::allocator<T>>,
///               typename A = std::allocator<T>>
///     class small_vector: public vector<T, N> {
/// ```
///        Implements the same constructors and assignment operators as `vector<T, A>`.
///        Inherits the remaining functionality of `vector<T, A>`.
/// ```
///         static constexpr std::size_t inline_capacity() { return N; }
///
///         // Returns true iff contents is stored in local buffer within the object.
///         bool uses_inline_buffer() const noexcept;
///     };
///
///     /// The maximum inline capacity so that `sizeof(small_vector<T, default_inline_capacity<T, A>, A>) == 64`
///     template <typename T, typename A>
///     constexpr std::size_t default_inline_capacity;
///
///     namespace pmr {
///         template <typename T>
///         using vector = utl::vector<T, polymorphic_allocator<T>>;
///         template <typename T>
///         using small_vector = utl::vector<T, default_inline_capacity<T, polymorphic_allocator<T>>,
///                                          polymorphic_allocator<T>>;
///     }
///
/// }
/// ```

namespace utl {

/// Edit or specialize this template to change the maximum capacity of utl::vector.
/// Using 32 bit size type reduces the memory footprint of the vector object from 24 bytes to 16 bytes..
/// With 32 bit size type and 1-byte data types the maximum capacity is 4GB, which might not suffice,
/// so for 1-byte types the default size type is 64 bits wide.
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
struct vector;

template <typename T,
          std::size_t N      = default_inline_capacity<T, std::allocator<T>>,
          typename Allocator = std::allocator<T>>
struct small_vector;

namespace pmr {
template <typename T>
using vector = utl::vector<T, polymorphic_allocator<T>>;
template <typename T, std::size_t N = default_inline_capacity<T, polymorphic_allocator<T>>>
using small_vector = utl::small_vector<T, N, polymorphic_allocator<T>>;
} // namespace pmr

// MARK: - vector
template <typename T, typename Allocator>
struct vector {
    /// MARK: Member Types
    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = typename __vector_config<value_type, allocator_type>::size_type;
    using difference_type = std::ptrdiff_t;

    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    using iterator       = __wrap_iterator<pointer>;
    using const_iterator = __wrap_iterator<const_pointer>;

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using __alloc_traits = std::allocator_traits<allocator_type>;

    // clang-format off
    template <typename... Args>
    static constexpr bool __constructible =
        requires(Args&&... args) { value_type(std::forward<Args>(args)...); } ||
        requires(allocator_type alloc, Args&&... args) { value_type(std::allocator_arg, alloc, std::forward<Args>(args)...); } ||
        requires(allocator_type alloc, Args&&... args) { value_type(std::forward<Args>(args)..., alloc); };
    // clang-format on

    static constexpr bool __value_type_uses_allocator_on_move =
        __alloc_constructible_1<value_type, allocator_type, value_type&&> ||
        __alloc_constructible_2<value_type, allocator_type, value_type&&>;

    /// MARK: Compile time checks
    static_assert(std::is_same_v<value_type, typename __alloc_traits::value_type>);

    /// MARK: Constructors
    /// (X)
    __utl_interface_export constexpr vector(std::size_t count,
                                            std::invocable<value_type*> auto&& f,
                                            allocator_type const& alloc = allocator_type()):
        vector(__private_tag{}, alloc, nullptr, count, count, false) {
        __set_begin(this->__allocate(count));
        for (auto i = __begin(), end = __end(); i != end; ++i) {
            f(i);
        }
    }

    /// (Xa)
    __utl_interface_export constexpr vector(std::size_t count,
                                            utl::invocable_r<value_type> auto&& f,
                                            allocator_type const& alloc = allocator_type()):
        vector(
            count,
            [this, &f](value_type* p) { __construct_at(p, f()); },
            alloc) {}

    /// (1)
    __utl_interface_export constexpr vector() noexcept(
        noexcept(allocator_type())) requires std::constructible_from<allocator_type>: vector(allocator_type()) {}
    /// (2)
    __utl_interface_export constexpr explicit vector(allocator_type const& alloc) noexcept:
        vector(__private_tag{}, alloc, nullptr, 0, 0, false) {}
    /// (3)
    __utl_interface_export constexpr vector(std::size_t count,
                                            value_type const& value,
                                            allocator_type const& alloc = allocator_type()):
        vector(
            count,
            [this, &value]() -> value_type const& { return value; },
            alloc) {}

    /// (4)
    __utl_interface_export constexpr explicit vector(std::size_t count, allocator_type const& alloc = allocator_type()):
        vector(
            count,
            [this](value_type* p) { __construct_at(p); },
            alloc) {}

    /// (4a)
    __utl_interface_export constexpr explicit vector(
        std::size_t count,
        utl::no_init_t,
        allocator_type const& alloc = allocator_type()) requires(std::is_trivial_v<value_type>):
        vector(
            count,
            [](value_type*) {},
            alloc) {}

    /// (5)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    __utl_interface_export __utl_always_inline constexpr vector(InputIt first,
                                                                Sentinel last,
                                                                allocator_type const& alloc = allocator_type()):
        vector(
            distance(first, last),
            [this, first]() mutable -> decltype(auto) { return *first++; },
            alloc) {}
    
    /// (5a)
    template <input_range_for<value_type> Range>
    requires (!std::derived_from<std::remove_cvref_t<Range>, vector>)
    __utl_interface_export __utl_always_inline constexpr vector(Range&& range,
                                                                allocator_type const& alloc = allocator_type()):
        vector(__utl_begin(range), __utl_end(range), alloc) {}

    /// (6)
    __utl_interface_export constexpr vector(vector const& rhs) requires std::constructible_from<allocator_type> &&
        (std::is_copy_constructible_v<value_type>):
        vector(rhs, allocator_type()) {}

    /// (7)
    __utl_interface_export constexpr vector(vector const& rhs, allocator_type const& alloc) requires(
        std::is_copy_constructible_v<value_type>):
        vector(
            rhs.size(),
            [this, i = rhs.begin()]() mutable -> value_type const& { return *i++; },
            alloc) {}

    /// (8)
    __utl_interface_export constexpr vector(vector&& rhs) noexcept(std::is_nothrow_move_constructible_v<value_type>):
        vector(std::move(rhs), allocator_type()) {}

    /// (8a)
    template <std::size_t N>
    __utl_interface_export constexpr vector(small_vector<value_type, N, allocator_type>&& rhs) noexcept(
        std::is_nothrow_move_constructible_v<value_type>):
        vector(std::move(rhs), allocator_type()) {}

    /// (9)
    __utl_interface_export constexpr vector(vector&& rhs, allocator_type const& alloc) noexcept(
        std::is_nothrow_move_constructible_v<value_type>):
        __alloc_(alloc) {
        __move_constr_impl(std::move(rhs));
    }

    /// (9a)
    template <std::size_t N>
    __utl_interface_export constexpr vector(
        small_vector<value_type, N, allocator_type>&& rhs,
        allocator_type const& alloc) noexcept(std::is_nothrow_move_constructible_v<value_type>):
        __alloc_(alloc) {
        __move_constr_impl(std::move(rhs));
    }

    /// (10)
    __utl_interface_export constexpr vector(
        std::initializer_list<value_type> ilist,
        allocator_type const& alloc) requires(std::is_copy_constructible_v<value_type>):
        vector(
            ilist.size(),
            [this, i = ilist.begin()]() mutable -> value_type const& { return *i++; },
            alloc) {}

    /// (10a)
    __utl_interface_export constexpr vector(std::initializer_list<value_type> ilist) requires(
        std::constructible_from<allocator_type>):
        vector(ilist, allocator_type()) {}

    /// MARK: Destructor
    __utl_interface_export constexpr ~vector() { __destroy_and_deallocate(); }

    /// MARK: operator=
    /// (1)
    __utl_interface_export constexpr vector& operator=(vector const& rhs) & // clang-format off
        requires(std::is_copy_assignable_v<value_type> && std::is_copy_constructible_v<value_type>) // clang-format on
    {
        if UTL_UNLIKELY (&rhs != this) {
            __assign_impl(rhs.__size(), [i = rhs.__begin()]() mutable -> T const& { return *i++; });
        }
        return *this;
    }

    /// (2)
    __utl_interface_export constexpr vector& operator=(vector&& rhs) & { return __move_assign_impl(rhs); }

    /// (2a)
    template <std::size_t N>
    __utl_interface_export constexpr vector& operator=(small_vector<value_type, N, allocator_type>&& rhs) & {
        return __move_assign_impl(rhs);
    }

    /// (3)
    __utl_interface_export constexpr vector& operator=(std::initializer_list<value_type> ilist) & {
        assign(ilist);
        return *this;
    }

    /// MARK: assign
    /// (1)
    constexpr void assign(std::size_t count, T const& value) {
        __assign_impl(count, [&value]() -> decltype(auto) { return value; });
    }

    /// (2)
    template <typename It> requires requires(It it) {
        { *it } -> std::convertible_to<value_type>;
        { it++ } -> std::same_as<It&>;
    }
    constexpr void assign(It first, It last) {
        __assign_impl(distance(first, last), [i = first]() mutable -> decltype(auto) { return *i++; });
    }

    /// (3)
    __utl_interface_export constexpr void assign(std::initializer_list<T> ilist) {
        __assign_impl(ilist.size(), [i = ilist.begin()]() mutable -> decltype(auto) { return *i++; });
    }

    /// MARK: get_allocator
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr allocator_type get_allocator() const noexcept {
        return __alloc();
    }

    /// MARK: at
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type& at(std::size_t pos) {
        return as_mutable(utl::as_const(*this).at(pos));
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type const& at(std::size_t pos) const {
        if UTL_UNLIKELY (pos >= size()) {
            __throw_out_of_range_error(pos);
        }
        return (*this)[pos];
    }

    /// MARK: operator[]
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type& operator[](std::size_t pos) {
        return utl::as_mutable(utl::as_const(*this).operator[](pos));
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type const&
    operator[](std::size_t pos) const {
        __utl_bounds_check(pos, 0, size());
        return *(__begin() + pos);
    }

    /// MARK: front
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type& front() noexcept {
        return as_mutable(utl::as_const(*this).front());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type const& front() const noexcept {
        __utl_expect(!empty(), "front() called on empty vector.");
        return *__begin();
    }

    /// MARK: back
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type& back() noexcept {
        return as_mutable(utl::as_const(*this).back());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr value_type const& back() const noexcept {
        __utl_expect(!empty(), "back() called on empty vector.");
        return *(__end() - 1);
    }

    /// MARK: data
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr pointer data() noexcept { return __begin(); }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_pointer data() const noexcept {
        return __begin();
    }

    /// MARK: begin
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr iterator begin() noexcept { return iterator(__begin()); }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator begin() const noexcept {
        return const_iterator(__begin());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator cbegin() const noexcept {
        return const_iterator(__begin());
    }

    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr reverse_iterator rbegin() noexcept {
        return reverse_iterator(__end());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator
    rbegin() const noexcept {
        return const_reverse_iterator(__end());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator
    crbegin() const noexcept {
        return const_reverse_iterator(__end());
    }

    /// MARK: end
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr iterator end() noexcept { return iterator(__end()); }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator end() const noexcept {
        return const_iterator(__end());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_iterator cend() const noexcept {
        return const_iterator(__end());
    }

    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr reverse_iterator rend() noexcept {
        return reverse_iterator(__begin());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(__begin());
    }
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(__begin());
    }

    /// MARK: empty
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr bool empty() const noexcept {
        return __size() == 0;
    }

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
        if (new_cap <= __cap()) {
            return;
        }
        __reserve_bigger(new_cap);
    }

    /// MARK: capacity
    __utl_nodiscard __utl_interface_export __utl_always_inline constexpr std::size_t capacity() const noexcept {
        return __cap();
    }

    /// MARK: shrink_to_fit
    __utl_interface_export constexpr void shrink_to_fit() {
        // no-op
    }

    /// MARK: clear
    __utl_interface_export constexpr void clear() noexcept {
        __destroy_elems();
        __set_size(0);
    }

    /// MARK: insert
    /// (1)
    __utl_interface_export constexpr iterator insert(const_iterator pos, value_type const& value) {
        return __insert_impl(pos - __begin(), 1, [&value]() -> value_type const& { return value; });
    }

    /// (1a)
    __utl_interface_export constexpr iterator insert(std::size_t index, value_type const& value) {
        return __insert_impl(index, 1, [&value]() -> value_type const& { return value; });
    }

    /// (2)
    __utl_interface_export constexpr iterator insert(const_iterator pos, value_type&& value) {
        return __insert_impl(pos - begin(), 1, [&value]() -> value_type&& { return std::move(value); });
    }

    /// (2a)
    __utl_interface_export constexpr iterator insert(std::size_t index, value_type&& value) {
        return __insert_impl(index, 1, [&value]() -> value_type&& { return std::move(value); });
    }

    /// (3)
    __utl_interface_export constexpr iterator insert(const_iterator pos, std::size_t count, value_type const& value) {
        return __insert_impl(pos - begin(), count, [&value]() -> value_type const& { return value; });
    }

    /// (3a)
    __utl_interface_export constexpr iterator insert(std::size_t index, std::size_t count, value_type const& value) {
        return __insert_impl(index, count, [&value]() -> value_type const& { return value; });
    }
    
    /// (3b)
    __utl_interface_export constexpr iterator insert(const_iterator pos, std::size_t count, utl::invocable_r<value_type> auto&& f) {
        return __insert_impl(pos - begin(), count, UTL_FORWARD(f));
    }
    
    /// (3c)
    __utl_interface_export constexpr iterator insert(std::size_t index, std::size_t count, utl::invocable_r<value_type> auto&& f) {
        return __insert_impl(index, count, UTL_FORWARD(f));
    }

    /// (4)
    template <typename It>
    __utl_interface_export constexpr iterator insert(const_iterator pos, It first, It last) {
        return __insert_impl(pos - begin(), static_cast<std::size_t>(distance(first, last)), [first]() mutable -> decltype(auto) {
            return *first++;
        });
    }
    
    /// (4a)
    template <input_iterator_for<T> It, sentinel_for<It> S>
    __utl_interface_export constexpr iterator insert(std::size_t index, It first, S last) {
        if constexpr (std::is_same_v<It, iterator> || std::is_same_v<It, const_iterator>) {
            __utl_expect(first < __begin() || first >= __end(), "inserted range may not overlap *this");
            __utl_expect(last < __begin() || last >= __end(), "inserted range may not overlap *this");
        }
        return __insert_impl(index, distance(first, last), [first]() mutable -> decltype(auto) { return *first++; });
    }
    
    /// (4b)
    template <input_range_for<T> Range>
    __utl_interface_export constexpr iterator insert(const_iterator pos, Range&& range) {
        return insert(pos, __utl_begin(range), __utl_end(range));
    }
    
    /// (4c)
    template <input_range_for<T> Range>
    __utl_interface_export constexpr iterator insert(std::size_t index, Range&& range) {
        return insert(index, __utl_begin(range), __utl_end(range));
    }
    
    /// (5)
    __utl_interface_export constexpr iterator insert(const_iterator pos, std::initializer_list<value_type> ilist) {
        return __insert_impl(pos - begin(), ilist.size(), [i = ilist.begin()]() mutable -> decltype(auto) {
            return *i++;
        });
    }

    /// (5a)
    __utl_interface_export constexpr iterator insert(std::size_t index, std::initializer_list<value_type> ilist) {
        return __insert_impl(index, ilist.size(), [i = ilist.begin()]() mutable -> decltype(auto) { return *i++; });
    }

    /// MARK: push_back
    __utl_interface_export constexpr value_type& push_back(value_type const& t) { return emplace_back(t); }
    __utl_interface_export constexpr value_type& push_back(value_type&& t) { return emplace_back(std::move(t)); }

    /// MARK: emplace_back
    template <typename... Args>
    requires __constructible<Args...> __utl_interface_export constexpr value_type& emplace_back(Args&&... args) {
        if UTL_UNLIKELY (__size() == __cap()) {
            __grow();
        }
        __construct_at(__end(), std::forward<Args>(args)...);
        __set_size(__size() + 1);
        return back();
    }

    /// MARK: pop_back
    __utl_interface_export constexpr void pop_back() noexcept {
        __utl_expect(!empty(), "pop_back() called on empty vector");
        __set_size(__size() - 1);
        __destroy_at(__end());
    }

    /// MARK: erase
    /// (1)
    __utl_interface_export constexpr iterator erase(const_iterator cpos) {
        if (empty()) {
            return end();
        }
        __utl_bounds_check(cpos, begin(), end());
        iterator const pos = const_cast<pointer>(cpos.underlying_iterator());
        __left_shift((pos + 1).underlying_iterator(), __end(), -1);
        __destroy_elems(__end() - 1, __end());
        __set_size(__size() - 1);
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
        iterator const first       = const_cast<pointer>(cfirst.underlying_iterator());
        iterator const last        = const_cast<pointer>(clast.underlying_iterator());
        auto const neg_erase_count = first - last;
        __left_shift(last.underlying_iterator(), __end(), neg_erase_count);
        __destroy_elems(__end() + neg_erase_count, __end());
        __set_size(__size() + neg_erase_count);
        return first;
    }

    /// MARK: resize
    /// (1)
    __utl_interface_export constexpr void resize(std::size_t count) {
        __resize_impl(count, [&](auto& i) { __construct_at(std::addressof(i)); });
    }

    /// (2)
    __utl_interface_export constexpr void resize(std::size_t count, value_type const& value) {
        __resize_impl(count, [&](auto& i) { __construct_at(std::addressof(i), value); });
    }

    /// (3)
    __utl_interface_export constexpr void resize(std::size_t count, no_init_t) {
        __resize_impl(count, [](auto&) {});
    }
    
    /// (4)
    template <typename... Args> requires std::constructible_from<value_type, Args const&...>
    __utl_interface_export constexpr void resize_emplace(std::size_t count, Args const&... args) {
        __resize_impl(count, [&](auto& i) { __construct_at(std::addressof(i), args...); });
    }

    /// MARK: swap
    __utl_interface_export constexpr void swap(vector& rhs) noexcept {
        if (__uses_inline_buffer() || rhs.__uses_inline_buffer() || __alloc() != rhs.__alloc()) {
            // We may _not_ swap buffers.
            // Use naive implementation for now. May suffice in general.
            auto tmp = std::move(*this);
            *this    = std::move(rhs);
            rhs      = std::move(tmp);
        }
        else {
            // We may swap buffers.
            std::swap(__data_, rhs.__data_);
        }
    }

    /// MARK: acquire, release
    
    /// _Acquires_ the buffer \p data i.e. takes ownership of the buffer.
    /// Behaviour is undefined if \p data cannot be destroyed and deallocated with \p allocator
    void acquire(pointer data, size_type size, size_type capacity, allocator_type const& allocator = {}) {
        __destroy_and_deallocate();
        __set_data(data, size, capacity, false);
        __alloc_ = allocator;
    }
    
    /// _Releases_ the internal buffer. The caller becomes responsible for destruction of live objects and deallocated of memory.
    /// If this vector uses a local buffer, elements will be moved into another buffer allocated by this vectors allocator and that buffer wil be returned.
    /// \Returns A `std::tuple<pointer, size_type, size_type>` consisting of a data pointer, count of constructed objects and size of the buffer in terms of objects of type `value_type`.
    std::tuple<pointer, size_type, size_type> release() {
        if (!__uses_inline_buffer()) {
            std::tuple<pointer, size_type, size_type> result = { __begin(), __size(), __cap() };
            __set_data(__storage_begin(), 0, 0, false);
            return result;
        }
        pointer buffer = __allocate(__size());
        __relocate(__begin(), __end(), buffer);
        size_type const old_size = __size();
        __set_size(0);
        return { buffer, old_size, old_size };
    }
    
    /// MARK: - Private Interface
    template <typename, std::size_t, typename>
    friend struct small_vector;

    void __move_constr_impl(auto&& rhs) {
        bool const alloc_eq = __alloc() == rhs.__alloc();
        if (rhs.__uses_inline_buffer() || !alloc_eq) {
            // Here we need to allocate and relocate
            __set_data(__allocate(rhs.__size()), rhs.__size(), rhs.__size(), false);
            __relocate_with_alloc(rhs.__begin(), rhs.__end(), __begin(), rhs.__alloc());
            rhs.__set_size(0);
        }
        else {
            // We may steal the buffer
            __set_data(rhs.__begin(), rhs.__size(), rhs.__cap(), false);
            rhs.__set_data(rhs.__storage_begin(), 0, rhs.__inline_cap(), rhs.__has_inline_buffer());
        }
    }

    void __assign_impl(std::size_t count, auto&& f) {
        if (count <= __cap()) {
            // no need to allocate
            std::size_t const assign_count = std::min<std::size_t>(count, __size());
            auto i                         = __begin();
            __fassign(__begin(), __begin() + assign_count, f);
            __fconstruct(__begin() + assign_count, __begin() + count, f);
            auto const old_end = __end();
            __set_size(count);
            __destroy_elems(__end(), old_end);
        }
        else {
            __destroy_and_deallocate();
            __set_data(__allocate(count), count, count, false);
            __fconstruct(__begin(), __end(), f);
        }
    }

    constexpr vector& __move_assign_impl(auto&& rhs) {
        if UTL_UNLIKELY (&rhs.__as_base() == this) {
            return *this;
        }
        bool const alloc_eq = __alloc() == rhs.__alloc();
        if (rhs.__uses_inline_buffer() || (__uses_inline_buffer() && rhs.__size() <= __cap()) || !alloc_eq) {
            // We don't steal the buffer
            if (rhs.size() <= __cap()) {
                // No need to allocate
                auto const rhs_assign_end = rhs.__begin() + std::min(__size(), rhs.__size());
                // Assign all we have already constructed in this
                std::move(rhs.__begin(), rhs_assign_end, __begin());
                // relocate the rest from rhs
                std::size_t const rhs_size = rhs.__size();
                __relocate_with_alloc(rhs_assign_end, rhs.__end(), __end(), rhs.__alloc());
                rhs.__set_size(rhs_assign_end - rhs.__begin());
                // Destroy our rest
                auto const old_end = __end();
                __set_size(rhs_size);
                __destroy_elems(__end(), old_end);
            }
            else {
                // We need to allocate
                __destroy_and_deallocate();
                __set_data(__allocate(rhs.__size()), rhs.size(), rhs.size(), false);
                __relocate_with_alloc(rhs.__begin(), rhs.__end(), __begin(), rhs.__alloc());
                rhs.__set_size(0);
            }
        }
        else {
            // We can steal the buffer
            std::swap(__data_, rhs.__data_);
        }
        return *this;
    }

    __utl_always_inline void __reserve_bigger(std::size_t new_cap) {
        __utl_assert_audit(new_cap > __cap());
        pointer new_buffer = __allocate(new_cap);
        __relocate(__begin(), __end(), new_buffer);
        __deallocate_this();
        __set_data(new_buffer, __size(), new_cap, false);
    }

    __utl_noinline void __grow() { __reserve_bigger(__recommend(__size() + 1)); }

    constexpr iterator __insert_impl(std::size_t index, std::size_t count, auto&& f) {
        __utl_bounds_check(index, 0, __size() + 1);
        if UTL_UNLIKELY (__size() + count > __cap()) {
            return __insert_slow_path(index, count, UTL_FORWARD(f));
        }
        auto const end = __end();
        auto const pos = __begin() + index;
        __right_shift_partial_uninit(pos, end, end, count);
        std::size_t const init_count = std::min<std::size_t>(count, end - pos);
        auto const last_init         = pos + init_count;
        __fassign(pos, last_init, f);
        __fconstruct(last_init, pos + count, f);
        __set_size(__size() + count);
        return pos;
    }

    __utl_noinline constexpr iterator __insert_slow_path(std::size_t index, std::size_t count, auto&& f) {
        std::size_t const new_size = __size() + count;
        std::size_t const new_cap  = __recommend(new_size);
        pointer new_buffer         = __allocate(new_cap);
        auto const nb_insert_begin = new_buffer + index;
        auto const nb_insert_end   = nb_insert_begin + count;
        __relocate(__begin(), __begin() + index, new_buffer);
        __relocate(__begin() + index, __end(), nb_insert_end);
        __fconstruct(nb_insert_begin, nb_insert_end, f);
        __deallocate_this();
        __set_data(new_buffer, new_size, new_cap, false);
        return new_buffer + index;
    }

    constexpr void __resize_impl(std::size_t count, auto&& constr) {
        if (__size() >= count) {
            __destroy_elems(__begin() + count, __end());
            __set_size(count);
        }
        else {
            // We grow
            reserve(count);
            std::for_each(__end(), __begin() + count, constr);
            __set_size(count);
        }
    }

    constexpr std::size_t __recommend(std::size_t new_size) noexcept {
        using conf               = __vector_config<value_type, allocator_type>;
        new_size                 = std::max(new_size, conf::minimum_allocation_count);
        constexpr std::size_t ms = max_size();
        __utl_assert(new_size <= ms, "max_size exceeded");
        auto const cap      = capacity();
        auto const next_cap = cap * conf::growth_factor;
        if UTL_UNLIKELY (next_cap >= ms) {
            return ms;
        }
        return std::bit_ceil(std::max<std::size_t>(next_cap, new_size));
    }

    explicit constexpr vector(__private_tag, allocator_type const& alloc, no_init_t): __alloc_(alloc) {}

    constexpr allocator_type& __alloc() noexcept { return __alloc_; }
    constexpr allocator_type const& __alloc() const noexcept { return __alloc_; }

    constexpr pointer __allocate(std::size_t n) { return n != 0 ? __alloc().allocate(n) : nullptr; }

    constexpr void __deallocate_this() {
        if (!__uses_inline_buffer() && __begin() != nullptr) {
            __alloc().deallocate(__begin(), __cap());
        }
    }

    template <typename... Args>
    constexpr void __construct_at(value_type* address, Args&&... args) {
        __alloc_traits::construct(__alloc(), address, UTL_FORWARD(args)...);
    }
    constexpr void __destroy_at(value_type* address) { __alloc_traits::destroy(__alloc(), address); }

    constexpr void __destroy_and_deallocate() {
        __destroy_elems();
        __deallocate_this();
    }

    constexpr void __destroy_elems() { __destroy_elems(__begin(), __end()); }

    /// Note: \p begin does not have to precede \p end
    constexpr void __destroy_elems(value_type* begin, value_type const* end) {
        if constexpr (!std::is_trivially_destructible_v<value_type>) {
            for (auto i = begin; i < end; ++i) {
                __destroy_at(i);
            }
        }
    }

    constexpr void __copy_uninit(auto begin, auto end, value_type* out) {
        for (; begin != end; ++begin, ++out) {
            __construct_at(out, *begin);
        }
    }

    constexpr void __fconstruct(value_type* begin, value_type const* end, auto&& f) {
        for (; begin != end; ++begin) {
            __construct_at(begin, f());
        }
    }

    constexpr void __fassign(value_type* begin, value_type const* end, auto&& f) {
        for (; begin != end; ++begin) {
            *begin = f();
        }
    }

    constexpr void __relocate_with_alloc(value_type* begin, value_type const* end, value_type* out, allocator_type const& other_alloc) {
        if (__value_type_uses_allocator_on_move && __alloc() != other_alloc) {
            __relocate_by_move(begin, end, out);
        }
        else {
            __relocate(begin, end, out);
        }
    }

    /// Relocation is move followed by destruction. Thus the data in a buffer that has been relocated is garbage.
    constexpr void __relocate(value_type* begin, value_type const* end, value_type* out) {
        if constexpr (is_trivially_relocatable<value_type>::value) {
            std::size_t const size = utl::distance(begin, end) * sizeof(value_type);
            __utl_assert(begin != nullptr || size == 0);
            /// We rely on undefined behaviour of `memcpy` here if `begin == nullptr`
            /// It should however not be a problem since in that case size is zero.
            std::memcpy(out, begin, size);
        }
        else {
            __relocate_by_move(begin, end, out);
        }
    }

    constexpr void __relocate_by_move(value_type* begin, value_type const* end, value_type* out) {
        for (; begin != end; ++begin, ++out) {
            __construct_at(out, std::move(*begin));
            std::destroy_at(std::addressof(*begin));
        }
    }

    constexpr static void __left_shift(value_type* begin, value_type const* end, std::ptrdiff_t offset) {
        __utl_expect(offset <= 0, "offset must non-positive");
        for (auto i = begin + offset, j = begin; j < end; ++i, ++j) {
            *i = std::move(*j);
        }
    }

    constexpr void
    __right_shift_partial_uninit(value_type* begin, value_type* end, value_type* uninit_begin, std::ptrdiff_t offset) {
        __utl_expect(offset >= 0, "offset must be non-negative");
        value_type* const out_begin      = begin + offset;
        value_type* const out_end        = end + offset;
        value_type* const out_assign_end = std::max(std::min(out_end, uninit_begin), out_begin);
        value_type* i                    = out_end;
        value_type* j                    = end;
        __utl_assert_audit(out_assign_end >= out_begin, "");
        for (; i > out_assign_end; --i, --j) {
            __construct_at(i - 1, std::move(*(j - 1)));
        }
        for (; i > out_begin; --i, --j) {
            *(i - 1) = std::move(*(j - 1));
        }
    }

    __utl_noinline void __throw_out_of_range_error(size_type pos) const {
        throw std::out_of_range("utl::vector out of range");
    }

    constexpr vector(__private_tag, pointer begin, std::size_t size, std::size_t cap, bool is_inline) noexcept:
        __alloc_(), __data_{ { begin, is_inline }, narrow_cast<size_type>(size), narrow_cast<size_type>(cap) } {}

    constexpr vector(__private_tag,
                     allocator_type const& alloc,
                     pointer begin,
                     std::size_t size,
                     std::size_t cap,
                     bool is_inline) noexcept:
        __alloc_(alloc), __data_{ { begin, is_inline }, static_cast<size_type>(size), static_cast<size_type>(cap) } {}

    constexpr pointer __begin() const noexcept { return __data_.begin_inline.pointer(); }
    constexpr pointer __end() const noexcept { return __begin() + __size(); }
    constexpr auto __move_begin() const noexcept { return std::move_iterator(__begin()); }
    constexpr auto __move_end() const noexcept { return std::move_iterator(__end()); }
    constexpr auto __size() const noexcept { return __data_.size; }
    constexpr auto __cap() const noexcept { return __data_.cap; }
    constexpr bool __uses_inline_buffer() const noexcept { return __data_.begin_inline.integer(); }

    constexpr void __set_begin(pointer p) noexcept { __data_.begin_inline.pointer(p); }
    constexpr void __set_size(std::size_t size) noexcept { __data_.size = narrow_cast<size_type>(size); }

    struct __data_t {
        static_assert(std::is_same_v<value_type*, pointer>);
        pointer_int_pair<value_type*, bool, 1> begin_inline;
        size_type size; /// These should actually be of type `size_type` however lldb debugger then can't read them.
        size_type cap;
    };

    constexpr __data_t __get_data() const { return __data_; }

    constexpr void __set_data(__data_t data) { __data_ = data; }
    constexpr void __set_data(pointer p, std::size_t size, std::size_t cap, bool is_inline) {
        __data_.begin_inline = { p, is_inline };
        __data_.size         = narrow_cast<size_type>(size);
        __data_.cap          = narrow_cast<size_type>(cap);
    }

    constexpr __data_t __default_data() { return { { nullptr, false }, 0, 0 }; }

    constexpr pointer __storage_begin() { return nullptr; }
    constexpr const_pointer __storage_begin() const { return nullptr; }
    constexpr pointer __storage_end() { return nullptr; }
    constexpr const_pointer __storage_end() const { return nullptr; }

    constexpr std::size_t __inline_cap() const { return 0; }
    constexpr bool __has_inline_buffer() const { return false; }

    auto& __as_base() noexcept { return *this; }
    auto const& __as_base() const noexcept { return *this; }

    [[no_unique_address]] allocator_type __alloc_;
    __data_t __data_;
};

template <typename T, typename A, typename B>
bool operator==(vector<T, A> const& lhs, vector<T, B> const& rhs) {
    if (lhs.__size() != rhs.__size()) {
        return false;
    }
    auto i   = lhs.__begin();
    auto j   = rhs.__begin();
    auto end = lhs.__end();
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

/// MARK: - small_vector
template <typename T, std::size_t N, typename Allocator>
struct small_vector: vector<T, Allocator> {
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

    using typename __utl_base::__alloc_traits;

    /// MARK: Constructors
    /// (1)
    __utl_interface_export constexpr small_vector() noexcept(
        noexcept(allocator_type())) requires std::is_default_constructible_v<allocator_type>:
        __utl_base(__private_tag{}, __storage_begin(), {}, N, true) {}

    /// (2)
    __utl_interface_export constexpr explicit small_vector(allocator_type const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, __storage_begin(), {}, N, true) {}

    /// (3)
    __utl_interface_export constexpr small_vector(std::size_t count,
                                                  value_type const& value,
                                                  allocator_type const& alloc = allocator_type()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
        this->__fconstruct(this->__begin(), this->__end(), [&value]() -> T const& { return value; });
    }

    /// (4)
    __utl_interface_export constexpr explicit small_vector(std::size_t count,
                                                           allocator_type const& alloc = allocator_type()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
        for (auto i = this->__begin(); i != this->__end(); ++i) {
            this->__construct_at(i);
        }
    }

    /// (4a)
    __utl_interface_export constexpr explicit small_vector(
        std::size_t count,
        utl::no_init_t,
        allocator_type const& alloc = allocator_type()) requires(std::is_trivial_v<value_type>):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(count);
    }

    /// (5)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    __utl_interface_export constexpr small_vector(InputIt first,
                                                  Sentinel last,
                                                  allocator_type const& alloc = allocator_type()) // clang-format off
        requires requires { { *first } -> std::convertible_to<value_type>; }: // clang-format on
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(distance(first, last));
        this->__copy_uninit(first, last, this->__begin());
    }
    
    /// (5a)
    template <input_range_for<value_type> Range>
    __utl_interface_export __utl_always_inline constexpr small_vector(Range&& range,
                                                                      allocator_type const& alloc = allocator_type()):
        small_vector(__utl_begin(range), __utl_end(range), alloc) {}

    /// (6)
    __utl_interface_export constexpr small_vector(vector<value_type, allocator_type> const& rhs):
        small_vector(rhs, allocator_type()) {}

    /// (6a)
    __utl_interface_export constexpr small_vector(small_vector const& rhs): small_vector(rhs, allocator_type()) {}

    /// (7)
    __utl_interface_export constexpr small_vector(vector<value_type, allocator_type> const& rhs,
                                                  allocator_type const& alloc):
        __utl_base(__private_tag{}, alloc, no_init) {
        __copy_constructor_impl(rhs);
    }

    /// (7a)
    __utl_interface_export constexpr small_vector(small_vector const& rhs, allocator_type const& alloc):
        small_vector(rhs.__as_base(), alloc) {}

    /// (8)
    __utl_interface_export constexpr small_vector(vector<value_type, allocator_type>&& rhs) noexcept:
        small_vector(std::move(rhs), allocator_type()) {}

    /// (8a)
    __utl_interface_export constexpr small_vector(small_vector&& rhs) noexcept:
        small_vector(std::move(rhs), allocator_type()) {}

    /// (8b)
    template <std::size_t M>
    __utl_interface_export constexpr small_vector(small_vector<value_type, M, allocator_type>&& rhs) noexcept:
        small_vector(std::move(rhs), allocator_type()) {}

    /// (9)
    __utl_interface_export constexpr small_vector(vector<value_type, allocator_type>&& rhs,
                                                  allocator_type const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, no_init) {
        __move_constructor_impl(std::move(rhs));
    }

    /// (9a)
    __utl_interface_export constexpr small_vector(small_vector&& rhs, allocator_type const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, no_init) {
        __move_constructor_impl(std::move(rhs));
    }

    /// (9b)
    template <std::size_t M>
    __utl_interface_export constexpr small_vector(small_vector<value_type, M, allocator_type>&& rhs,
                                                  allocator_type const& alloc) noexcept:
        __utl_base(__private_tag{}, alloc, no_init) {
        __move_constructor_impl(std::move(rhs));
    }

    /// (10)
    __utl_interface_export constexpr small_vector(std::initializer_list<value_type> ilist,
                                                  allocator_type const& alloc = allocator_type()):
        __utl_base(__private_tag{}, alloc, no_init) {
        __count_constructor_prep(ilist.size());
        this->__copy_uninit(ilist.begin(), ilist.end(), this->__begin());
    }

    /// MARK: operator=
    using __utl_base::operator=;

    /// (1)
    __utl_interface_export constexpr small_vector& operator=(small_vector const& rhs) & {
        __as_base() = rhs.__as_base();
        return *this;
    }
    /// (2)
    __utl_interface_export constexpr small_vector&
    operator=(small_vector&& rhs) & noexcept(__alloc_traits::propagate_on_container_move_assignment::value ||
                                             __alloc_traits::is_always_equal::value) {
        __as_base() = std::move(rhs.__as_base());
        return *this;
    }

    /// MARK: inline_capacity
    __utl_interface_export constexpr static std::size_t inline_capacity() noexcept { return N; }

    /// MARK: - Private Interface
    friend struct vector<value_type, allocator_type>;
    template <typename, std::size_t, typename>
    friend struct small_vector;

    constexpr void __count_constructor_prep(std::size_t count) {
        if (count <= N) {
            this->__set_data(this->__storage_begin(), count, N, true);
        }
        else {
            this->__set_data(this->__allocate(count), count, count, false);
        }
    }

    void __copy_constructor_impl(auto const& rhs) {
        __count_constructor_prep(rhs.__size());
        this->__copy_uninit(rhs.__begin(), rhs.__end(), this->__begin());
    }

    void __move_constructor_impl(auto&& rhs) {
        bool const alloc_eq = this->__alloc() == rhs.__alloc();
        if (rhs.size() <= N) {
            // Contents of rhs fits into our local buffer, so we don't steal buffer from rhs
            this->__set_data(__storage_begin(), rhs.__size(), N, true);
            this->__relocate_with_alloc(rhs.__begin(), rhs.__end(), this->__begin(), rhs.__alloc());
            rhs.__set_size(0);
        }
        else if (rhs.__uses_inline_buffer() || !alloc_eq) {
            // rhs uses local buffer or a different allocator, we need to allocate
            __utl_assert(!rhs.empty());
            this->__set_data(this->__allocate(rhs.__size()), rhs.__size(), rhs.__size(), false);
            this->__relocate_with_alloc(rhs.__begin(), rhs.__end(), this->__begin(), rhs.__alloc());
            rhs.__set_size(0);
        }
        else {
            // We can swap buffers
            this->__set_data(rhs.__get_data());
            rhs.__set_data(rhs.__default_data());
        }
    }

    pointer __storage_begin() noexcept { return reinterpret_cast<pointer>(__storage); }
    pointer __storage_end() noexcept { return reinterpret_cast<pointer>(__storage) + N; }

    const_pointer __storage_begin() const noexcept { return reinterpret_cast<const_pointer>(__storage); }
    const_pointer __storage_end() const noexcept { return reinterpret_cast<const_pointer>(__storage) + N; }

    constexpr std::size_t __inline_cap() const { return N; }
    constexpr bool __has_inline_buffer() const { return true; }

    constexpr typename vector<value_type, allocator_type>::__data_t __default_data() {
        return { { __storage_begin(), true }, 0, N };
    }

    __utl_base& __as_base() noexcept { return static_cast<__utl_base&>(*this); }
    __utl_base const& __as_base() const noexcept { return static_cast<__utl_base const&>(*this); }

    alignas(N != 0 ? alignof(value_type) : 1) char __storage[sizeof(value_type) * N];
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
