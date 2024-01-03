#ifndef UTL_SMALLPTRVECTOR_H_
#define UTL_SMALLPTRVECTOR_H_

#include <algorithm>
#include <cassert>
#include <type_traits>

#include "__base.hpp"
#include "concepts.hpp"
#include "vector.hpp"

namespace utl {

template <typename T, typename Allocator = std::allocator<T>>
class small_ptr_vector {
    static_assert(std::is_pointer_v<T>,
                  "Can only instantiate with pointers as value type");
    static_assert(alignof(std::remove_pointer_t<T>) >= 4,
                  "We need the lowest two bits in the pointer to discriminate "
                  "the empty and single value state");

    using impl_type    = utl::small_vector<T, 6, Allocator>;
    using vector_alloc = typename std::allocator_traits<
        Allocator>::template rebind_alloc<impl_type>;

public:
    using value_type             = typename impl_type::value_type;
    using allocator_type         = typename impl_type::allocator_type;
    using size_type              = typename impl_type::size_type;
    using difference_type        = typename impl_type::difference_type;
    using reference              = typename impl_type::reference;
    using const_reference        = typename impl_type::const_reference;
    using pointer                = typename impl_type::pointer;
    using const_pointer          = typename impl_type::const_pointer;
    using iterator               = value_type*;
    using const_iterator         = value_type const*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// (1)
    small_ptr_vector(): small_ptr_vector(allocator_type()) {}

    /// (2)
    explicit small_ptr_vector(allocator_type const& alloc):
        ptr(empty_state()), alloc(alloc) {}

    /// (3) & (4)
    explicit small_ptr_vector(std::size_t count,
                              T const& value              = T(),
                              allocator_type const& alloc = allocator_type()):
        small_ptr_vector(alloc) {
        switch (count) {
        case 0: break;
        case 1: set_single_value(value); break;
        default: set_heap(new_heap(count, value, alloc)); break;
        }
    }

    /// (5)
    template <utl::input_iterator_for<value_type> InputIt,
              utl::sentinel_for<InputIt> Sentinel>
    small_ptr_vector(InputIt first,
                     Sentinel last,
                     allocator_type const& alloc = allocator_type()):
        small_ptr_vector(alloc) {
        if (first == last) {
            return;
        }
        if constexpr (utl::forward_iterator<InputIt>) {
            impl_type impl(first, last, alloc);
            switch (impl.size()) {
            case 0: __utl_unreachable(); break;
            case 1: set_single_value(impl.front()); break;
            default: set_heap(new_heap(std::move(impl))); break;
            }
        }
        else {
            if (std::next(first) == last) {
                set_single_value(*first);
            }
            else {
                set_heap(new_heap(first, last, alloc));
            }
        }
    }

    void __copy_move_ctor_impl(small_ptr_vector const& other,
                               auto&& heap_case) {
        switch (other.size()) {
        case 0: break;
        case 1: set_single_value(other.front()); break;
        default: heap_case(); break;
        }
    }

    /// (6)
    small_ptr_vector(small_ptr_vector const& other):
        small_ptr_vector(
            std::allocator_traits<allocator_type>::
                select_on_container_copy_construction(other.get_allocator())) {
        __copy_move_ctor_impl(other,
                              [&] { set_heap(new_heap(*other.get_heap())); });
    }

    /// (7)
    small_ptr_vector(small_ptr_vector const& other,
                     allocator_type const& alloc):
        small_ptr_vector(alloc) {
        __copy_move_ctor_impl(other, [&] {
            set_heap(new_heap(*other.get_heap(), alloc));
        });
    }

    /// (8)
    small_ptr_vector(small_ptr_vector&& other) noexcept:
        small_ptr_vector(other.get_allocator()) {
        __copy_move_ctor_impl(other, [&] {
            /// For now
            __utl_assert(alloc == other.alloc);
            set_heap(other.get_heap());
            other.set_empty();
        });
    }

    /// (9)
    small_ptr_vector(small_ptr_vector&& other,
                     allocator_type const& alloc) noexcept:
        small_ptr_vector(alloc) {
        __copy_move_ctor_impl(other, [&] {
            /// For now
            __utl_assert(alloc == other.alloc);
            set_heap(other.get_heap());
            other.set_empty();
        });
    }

    /// (10)
    small_ptr_vector(std::initializer_list<T> init,
                     allocator_type const& alloc = allocator_type()):
        small_ptr_vector(alloc) {
        switch (init.size()) {
        case 0: break;
        case 1: set_single_value(*init.begin()); break;
        default: set_heap(new_heap(init, alloc)); break;
        }
    }

    ~small_ptr_vector() {
        if (!is_heap()) {
            return;
        }
        delete_heap(get_heap());
    }

    /// (1)
    small_ptr_vector& operator=(small_ptr_vector const& other) {
        if (!other.is_heap()) {
            if (is_heap()) {
                delete_heap(get_heap());
            }
            ptr = other.ptr;
        }
        else {
            if (is_heap()) {
                *get_heap() = *other.get_heap();
            }
            else {
                set_heap(new_heap(*other.get_heap()));
            }
        }
        return *this;
    }

    /// (2)
    small_ptr_vector& operator=(small_ptr_vector&& other) noexcept {
        if (!other.is_heap()) {
            if (is_heap()) {
                delete_heap(get_heap());
            }
            ptr = other.ptr;
        }
        else {
            if (is_heap()) {
                delete_heap(get_heap());
            }
            __utl_assert(alloc == other.alloc);
            set_heap(other.get_heap());
            other.set_empty();
        }
        return *this;
    }

    /// (3)
    small_ptr_vector& operator=(std::initializer_list<value_type> ilist) {
        assign(ilist);
        return *this;
    }

    /// (1)
    void assign(std::size_t count, value_type value) {
        switch (count) {
        case 0: clear(); break;
        case 1:
            clear();
            set_single_value(value);
            break;
        default:
            if (is_heap()) {
                get_heap()->assign(count, value);
            }
            else {
                set_heap(new_heap(count, value));
            }
            break;
        }
    }

    /// (2)
    template <utl::input_iterator_for<value_type> InputIt,
              utl::sentinel_for<InputIt> Sentinel>
    void assign(InputIt first, Sentinel last) {
        if (first == last) {
            clear();
        }
        else if constexpr (utl::forward_iterator<InputIt>) {
            impl_type impl(first, last, alloc);
            switch (impl.size()) {
            case 1:
                if (is_heap()) {
                    delete_heap(get_heap());
                }
                set_single_value(impl.front());
                break;
            default:
                /// Must be greater 1 because we have a special case for 1 and
                /// test for not empty in the beginning of the function
                __utl_assert(impl.size() > 1);
                if (is_heap()) {
                    *get_heap() = std::move(impl);
                }
                else {
                    set_heap(new_heap(std::move(impl)));
                }
            }
        }
        else if (std::next(first) == last) {
            clear();
            set_single_value(*first);
        }
        else {
            if (is_heap()) {
                get_heap()->assign(first, last);
            }
            else {
                set_heap(new_heap(first, last));
            }
        }
    }

    /// (3)
    void assign(std::initializer_list<value_type> ilist) {
        assign(ilist.begin(), ilist.end());
    }

    /// (1)
    allocator_type get_allocator() const { return alloc; }

    /// # Iterators
    iterator begin() {
        return const_cast<iterator>(
            static_cast<small_ptr_vector const*>(this)->begin());
    }
    const_iterator begin() const {
        if (is_empty()) {
            return nullptr;
        }
        if (is_single_value()) {
            return &get_single_value();
        }
        return get_heap()->data();
    }

    iterator end() {
        return const_cast<iterator>(
            static_cast<small_ptr_vector const*>(this)->end());
    }
    const_iterator end() const {
        if (is_empty()) {
            return nullptr;
        }
        if (is_single_value()) {
            return &get_single_value() + 1;
        }
        return get_heap()->data() + get_heap()->size();
    }

    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator crend() const { return rend(); }

    /// # Element access

    reference front() {
        return const_cast<reference>(
            static_cast<small_ptr_vector const*>(this)->front());
    }

    const_reference front() const {
        if (is_single_value()) {
            return get_single_value();
        }
        __utl_assert(is_heap());
        return get_heap()->front();
    }

    reference back() {
        return const_cast<reference>(
            static_cast<small_ptr_vector const*>(this)->back());
    }

    const_reference back() const {
        if (is_single_value()) {
            return get_single_value();
        }
        __utl_assert(is_heap());
        return get_heap()->back();
    }

    reference at(std::size_t pos); // Too lazy to implement

    const_reference at(std::size_t pos) const;

    reference operator[](std::size_t pos) {
        return const_cast<reference>(
            static_cast<small_ptr_vector const&>(*this)[pos]);
    }

    const_reference operator[](std::size_t pos) const {
        if (is_single_value()) {
            __utl_assert(pos == 0);
            return get_single_value();
        }
        __utl_assert(is_heap());
        return (*get_heap())[pos];
    }

    T* data() noexcept {
        return const_cast<T*>(
            static_cast<small_ptr_vector const*>(this)->data());
    }

    T const* data() const {
        if (is_heap()) {
            return get_heap()->data();
        }
        /// No need to check for empty state because the value of `data()` is
        /// undefined if container is empty
        return &get_single_value();
    }

    /// # Capacity

    /// (1)
    bool empty() const {
        if (is_heap()) {
            return get_heap()->empty();
        }
        return is_empty();
    }

    /// (1)
    std::size_t size() const {
        if (is_empty()) {
            return 0;
        }
        if (is_single_value()) {
            return 1;
        }
        return get_heap()->size();
    }

    static constexpr size_type max_size() { return impl_type::max_size(); }

    void reserve(std::size_t new_cap) {
        if (!is_heap()) {
            set_heap(new_heap(alloc));
        }
        get_heap()->reserve(new_cap);
    }

    std::size_t capacity() const {
        if (is_heap()) {
            return get_heap()->capacity();
        }
        return 1;
    }

    void shrink_to_fit() { /* no-op */
    }

    /// # Modifiers

    void clear() {
        if (is_heap()) {
            delete_heap(get_heap());
        }
        set_empty();
    }

    /// Helper function for the insert methods to bring the vector into heap
    /// state
    void __make_heap() {
        if (is_heap()) {
            return;
        }
        if (is_empty()) {
            set_heap(new_heap(alloc));
        }
        else {
            set_heap(new_heap(1, get_single_value(), alloc));
        }
    }

    static typename impl_type::const_iterator
    __to_heap_itr(const_iterator itr) {
        return typename impl_type::const_iterator(itr);
    }

    iterator __insert_heap(const_iterator pos, auto... args) {
        std::size_t index = pos - begin();
        __make_heap();
        return get_heap()->insert(get_heap()->begin() + index, args...).__itr;
    }

    /// (1)
    iterator insert(const_iterator pos, value_type value) {
        if (is_empty()) {
            __utl_assert(pos == begin());
            set_single_value(value);
            return begin();
        }
        else {
            return __insert_heap(pos, value);
        }
    }

    /// (3)
    iterator insert(const_iterator pos, size_type count, value_type value) {
        switch (count) {
        case 0: return const_cast<iterator>(pos);
        case 1: return insert(pos, value);
        default: return __insert_heap(pos, count, value);
        }
    }

    /// (4)
    template <utl::input_iterator_for<value_type> InputIt,
              utl::sentinel_for<InputIt> Sentinel>
    iterator insert(const_iterator pos, InputIt first, Sentinel last) {
        if (first == last) {
            return const_cast<iterator>(pos);
        }
        if constexpr (!utl::forward_iterator<InputIt>) {
            impl_type impl(first, last);
            switch (impl.size()) {
            case 1: return insert(pos, impl.front());
            default:
                __utl_assert(impl.empty());
                return __insert_heap(pos, impl.begin(), impl.end());
            }
        }
        if (std::next(first) == last) {
            return insert(pos, *first);
        }
        return __insert_heap(pos, first, last);
    }

    /// (5)
    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template <typename... Args>
    requires std::constructible_from<value_type, Args...>
    iterator emplace(const_iterator pos, Args&&... args) {
        insert(pos, value_type(std::forward<Args>(args)...));
    }

    /// (1)
    iterator erase(iterator pos) {
        if (is_heap()) {
            return get_heap()->erase(__to_heap_itr(pos)).__itr;
        }
        /// _The iterator pos must be valid and dereferenceable_
        /// (https://en.cppreference.com/w/cpp/container/vector/erase)
        __utl_assert(pos == begin());
        __utl_assert(!is_empty());
        set_empty();
        return end();
    }

    /// (2)
    iterator erase(iterator first, iterator last) {
        if (first == last) {
            return last;
        }
        if (is_heap()) {
            return get_heap()
                ->erase(__to_heap_itr(first), __to_heap_itr(last))
                .__itr;
        }
        /// Only possible values for `first` and `last` because we check for the
        /// empty case above
        __utl_assert(first == begin());
        __utl_assert(last == end());
        __utl_assert(!is_empty());
        set_empty();
        return end();
    }

    value_type& push_back(value_type value) {
        if (is_empty()) {
            set_single_value(value);
            return get_single_value();
        }
        __make_heap();
        return get_heap()->push_back(value);
    }

    template <typename... Args>
    requires std::constructible_from<value_type, Args...>
    value_type& emplace_back(Args&&... args) {
        return push_back(value_type(std::forward<Args>(args)...));
    }

    void pop_back() {
        __utl_assert(!is_empty());
        if (is_heap()) {
            auto* heap = get_heap();
            if (heap->size() == 1) {
                clear();
                return;
            }
            heap->pop_back();
            return;
        }
        set_empty();
    }

    void resize(std::size_t count, value_type value = value_type()) {
        switch (count) {
        case 0: clear(); break;
        case 1: {
            if (!empty()) {
                value = front();
            }
            clear();
            set_single_value(value);
            break;
        }
        default:
            __make_heap();
            get_heap()->resize(count, value);
            break;
        }
    }

    void swap(small_ptr_vector& other) {
        __utl_assert(alloc == other.alloc);
        void* this_state;
        std::memcpy(&this_state, &ptr, sizeof(void*));
        std::memcpy(&ptr, &other.ptr, sizeof(void*));
        std::memcpy(&other.ptr, &this_state, sizeof(void*));
    }

private:
    static bool is_aligned(T value) {
        return (reinterpret_cast<uintptr_t>(value) & 3) == 0;
    }

    /// \Returns the lower two bits of the pointer that represent the state
    uintptr_t state_bits() const {
        return reinterpret_cast<uintptr_t>(ptr) & 3;
    }

    /// \Returns `true` if we are in the empty state
    bool is_empty() const { return state_bits() == 1; }

    /// \Returns `true` if we are in the single value state
    bool is_single_value() const { return state_bits() == 0; }

    /// \Returns `true` if we are in the heap state
    bool is_heap() const { return state_bits() == 2; }

    /// \Returns the value of `ptr` that represents the empty state
    static T empty_state() { return reinterpret_cast<T>(uintptr_t{ 1 }); }

    /// Sets `ptr` to the value of the empty state.
    /// \Warning this function does not destroy any existing state
    void set_empty() { ptr = empty_state(); }

    /// Sets `ptr` to \p value
    /// This function does not modify \p value in any way because the single
    /// value state is the state where the lower bits are all zero. This
    /// property is asserted
    ///
    /// \Warning this function does not destroy any existing state
    void set_single_value(value_type value) {
        __utl_assert(is_aligned(value));
        ptr = value;
    }

    /// This function only exists for consistency. We return by reference so
    /// `data()` and other functions can take the address
    value_type& get_single_value() { return ptr; }

    /// \overload
    value_type const& get_single_value() const { return ptr; }

    /// Sets `heap` to \p impl and sets the lower bits the represent the heap
    /// state \Warning this function does not destroy any existing state
    void set_heap(impl_type* impl) {
        uintptr_t i = reinterpret_cast<uintptr_t>(impl);
        i |= 2;
        heap = reinterpret_cast<impl_type*>(i);
    }

    /// \Returns `heap` with the state bits cleared
    impl_type* get_heap() {
        return const_cast<impl_type*>(
            static_cast<small_ptr_vector const*>(this)->get_heap());
    }

    /// \overload
    impl_type const* get_heap() const {
        __utl_assert(is_heap());
        uintptr_t i = reinterpret_cast<uintptr_t>(heap);
        i &= ~uintptr_t{ 3 };
        return reinterpret_cast<impl_type const*>(i);
    }

    /// \Returns a pointer to a heap allocated implementation vector constructed
    /// with \p args... The current allocator is used to allocate the heap
    /// vector
    template <typename... Args>
    impl_type* new_heap(Args&&... args) {
        using traits    = std::allocator_traits<vector_alloc>;
        impl_type* impl = traits::allocate(alloc, 1);
        traits::construct(alloc, impl, std::forward<Args>(args)...);
        return impl;
    }

    /// Destroys and deallocates the implementation vector \p impl allocated
    /// with `new_heap` \Warning this must be not used with a different
    /// allocator type than the one used to allocate \p impl
    void delete_heap(impl_type* impl) {
        using traits = std::allocator_traits<vector_alloc>;
        traits::destroy(alloc, impl);
        traits::deallocate(alloc, impl, 1);
    }

    union {
        T ptr;
        impl_type* heap;
    };
    [[no_unique_address]] vector_alloc alloc;
};

template <typename T, typename Allocator>
bool operator==(small_ptr_vector<T, Allocator> const& lhs,
                small_ptr_vector<T, Allocator> const& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

} // namespace utl

#endif // UTL_SMALLPTRVECTOR_H_
