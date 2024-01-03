#ifndef UTL_SMALLPTRVECTOR_H_
#define UTL_SMALLPTRVECTOR_H_

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
    using iterator               = pointer;
    using const_iterator         = const_pointer;
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
            case 0: assert(false); break;
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
    small_ptr_vector(small_ptr_vector&& other):
        small_ptr_vector(other.get_allocator()) {
        __copy_move_ctor_impl(other, [&] {
            /// For now
            __utl_assert(alloc == other.alloc);
            set_heap(other.get_heap());
            other.set_empty();
        });
    }

    /// (9)
    small_ptr_vector(small_ptr_vector&& other, allocator_type const& alloc):
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
                     allocator_type const& alloc):
        small_ptr_vector(alloc) {
        switch (init.size()) {
        case 0: break;
        case 1: set_single_value(init.front()); break;
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
    allocator_type get_allocator() const { return alloc; }

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
    bool empty() const { return is_empty(); }

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
        assert(is_aligned(value));
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
        assert(is_heap());
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

} // namespace utl

#endif // UTL_SMALLPTRVECTOR_H_
