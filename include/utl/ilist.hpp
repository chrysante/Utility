#pragma once

#include <iterator>
#include <iosfwd>

#include "__base.hpp"
#include "__memory_resource_base.hpp"
#include "__ranges_base.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T, typename Allocator = std::allocator<T>>
class ilist;

template <typename>
class __ilist_node_base2;

template <typename, bool>
class ilist_node;

struct __ilist_node_base {
protected:
    __ilist_node_base(__ilist_node_base* prev = nullptr, __ilist_node_base* next = nullptr):
        __prev(prev), __next(next) {}
    
    /// Copy operations are no-ops, as we don't want to propagate sibling relationship with copying.
    __ilist_node_base(__ilist_node_base const&): __ilist_node_base() {}
    
    __ilist_node_base& operator=(__ilist_node_base const&) { return *this; }
    
private:
    template <typename, typename>
    friend class ilist;
    
    template <typename>
    friend class __ilist_node_base2;
    
    template <typename, bool>
    friend class ilist_node;
    
    /// Instead of copy construction and assignment we provide a special function to be used by ilist to copy relationship information.
    void __assign(__ilist_node_base const& rhs) {
        __prev = rhs.__prev;
        __next = rhs.__next;
    }
    
    __ilist_node_base* __prev;
    __ilist_node_base* __next;
};

template <typename Derived>
class __ilist_node_base2: public __ilist_node_base {
public:
    Derived*       prev()       { return static_cast<Derived*      >(this->__prev); }
    Derived const* prev() const { return static_cast<Derived const*>(this->__prev); }
    Derived*       next()       { return static_cast<Derived*      >(this->__next); }
    Derived const* next() const { return static_cast<Derived const*>(this->__next); }
};

template <typename Derived, bool AllowSetSiblings = false>
class ilist_node /* AllowSetSiblings = false */: public __ilist_node_base2<Derived> {};

template <typename Derived>
class ilist_node<Derived, /* AllowSetSiblings = */ true>: public __ilist_node_base2<Derived> {
public:
    void set_prev(Derived* next) { return this->__next = next; }
    void set_next(Derived* prev) { return this->__prev = prev; }
};

template <typename T, typename Allocator>
class ilist {
public:
    using __alloc_traits = std::allocator_traits<Allocator>;
    using __sentinel_type = __ilist_node_base;
    static constexpr bool __alloc_always_eq = __alloc_traits::is_always_equal::value;
    
    template <typename N>
    struct __iterator_impl {
    private:
        template <typename, typename>
        friend class ilist;
        
        explicit operator __iterator_impl<std::remove_const_t<N>>()
            requires std::is_const_v<N>
        {
            using MutN = std::remove_const_t<N>;
            return __iterator_impl<MutN>(const_cast<MutN*>(__node));
        }

        explicit __iterator_impl(copy_cv_t<N, __sentinel_type>* node):
            __node(static_cast<N*>(node)) {}
        
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = N;
        using pointer = N*;
        using reference = N&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        __iterator_impl(): __node(nullptr) {}
        
        explicit __iterator_impl(pointer node): __node(node) {}
        
        operator __iterator_impl<std::add_const_t<N>>() const
            requires(!std::is_const_v<N>)
        {
            return __iterator_impl<std::add_const_t<N>>(__node);
        }

        /// Get the address of the object this iterator points to.
        pointer to_address() const { return __node; }
        
        explicit operator pointer() const { return to_address(); }
        
        pointer operator->() const { return to_address(); }
        
        __iterator_impl& operator++() {
            __node = static_cast<pointer>(__node->__next);
            return *this;
        }
        
        __iterator_impl operator++(int) {
            auto result = *this;
            ++*this;
            return result;
        }
        
        __iterator_impl& operator--() {
            __node = static_cast<pointer>(__node->prev());
            return *this;
        }
        
        __iterator_impl operator--(int) {
            auto result = *this;
            --*this;
            return result;
        }
        
        bool operator==(__iterator_impl const& rhs) const = default;
        bool operator==(__iterator_impl<std::add_const_t<N>> const& rhs) const requires (!std::is_const_v<N>) { return __node == rhs.__node; }
        bool operator==(__iterator_impl<std::remove_const_t<N>> const& rhs) const requires std::is_const_v<N> { return __node == rhs.__node; }
        
        reference operator*() const { return *__node; }
        
        pointer __node;
    };
    
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = value_type const*;
    using reference = value_type&;
    using const_reference = value_type const&;
    using iterator = __iterator_impl<value_type>;
    using const_iterator = __iterator_impl<value_type const>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    // MARK: Constructors
    
    // (1)
    ilist(): __allocator_(), __sentinel_(__sentinel(), __sentinel()) {}
    
    // (2)
    explicit ilist(allocator_type const& alloc): __allocator_(alloc), __sentinel_(__sentinel(), __sentinel()) {}
    
    // (3)
    explicit ilist(size_type count,
                  value_type const& value,
                  allocator_type const& alloc = allocator_type()): ilist(alloc)
    {
        insert(begin(), count, value);
    }
    
    // (4)
    explicit ilist(size_type count, allocator_type const& alloc = allocator_type())
    requires std::is_default_constructible_v<value_type>:
        ilist(alloc)
    {
        __insert_impl(begin(), count, [this]{
            return __construct(__allocate());
        });
    }
    
    // (5)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    ilist(InputIt first, Sentinel last, allocator_type const& alloc = allocator_type()):
        ilist(alloc)
    {
        insert(begin(), first, last);
    }
    
    // (5a)
    template <input_range_for<value_type> Range>
    ilist(Range&& range, allocator_type const& alloc = allocator_type()):
        ilist(__utl_begin(range), __utl_end(range), alloc) {}
    
    // (6)
    ilist(ilist const& rhs) requires std::is_default_constructible_v<allocator_type>:
        ilist(rhs, __alloc_traits::select_on_container_copy_construction(rhs.__allocator_)) {}
    
    // (7)
    ilist(ilist const& rhs, allocator_type const& alloc):
        ilist(alloc)
    {
        insert(begin(), rhs.begin(), rhs.end());
    }
    
    // (8)
    ilist(ilist&& rhs) noexcept requires std::is_default_constructible_v<allocator_type>:
        ilist(std::move(rhs), rhs.__allocator_) {}
    
    // (9)
    ilist(ilist&& rhs, allocator_type const& alloc) noexcept: ilist(alloc) {
        auto fast_path = [&] {
            __move_assign_pointer_swap(rhs.begin(), rhs.end());
            rhs.__reset();
        };
        /// Use `if constexpr` here to prevent the path using `__insert_impl()` from compiling when not needed.
        if constexpr (__alloc_always_eq) {
            fast_path();
        }
        else if (__allocator_ == rhs.__allocator_) {
            fast_path();
        }
        else {
            __insert_impl_itr(begin(), rhs.begin(), rhs.end());
        }
    }
    
    // (10)
    ilist(std::initializer_list<T> init_list, allocator_type const& alloc = allocator_type()): ilist(alloc) {
        insert(begin(), init_list);
    }
    
    // MARK: Destructor
    
    ~ilist() {
        clear();
    }
    
    // MARK: Assignment
    
    // (1)
    ilist& operator=(ilist const& rhs) {
        if constexpr (__alloc_traits::propagate_on_container_copy_assignment::value) {
            if (__allocator_ == rhs.__allocator_) {
                __allocator_ = rhs.__allocator_;
                __assign_element_wise(rhs.begin(), rhs.end());
            }
            else {
                clear();
                __allocator_ = rhs.__allocator_;
                insert(begin(), rhs.begin(), rhs.end());
            }
        }
        else {
            __assign_element_wise(rhs.begin(), rhs.end());
        }
        return *this;
    }
    
    // (2)
    ilist& operator=(ilist&& rhs) noexcept {
        constexpr bool alloc_propagate = __alloc_traits::propagate_on_container_move_assignment::value;
        if (this == &rhs) { return *this; }
        if constexpr (__alloc_always_eq) {
            __move_assign_fast<alloc_propagate>(rhs);
        }
        else {
            if (__alloc_always_eq || __allocator_ == rhs.__allocator_) {
                __move_assign_fast<alloc_propagate>(rhs);
            }
            else {
                __move_assign_slow<alloc_propagate>(rhs);
            }
        }
        return *this;
    }
    
    template <bool AllocProp>
    void __move_assign_fast(ilist& rhs) {
        if constexpr (AllocProp) {
            __allocator_ = rhs.__allocator_;
        }
        __swap_impl<false>(rhs);
    }

    template <bool AllocProp>
    void __move_assign_slow(ilist& rhs) {
        clear();
        if constexpr (AllocProp) {
            __allocator_ = rhs.__allocator_;
        }
        // Assign element-wise, as we must reallocate because unequal allocators.
        __assign_element_wise(std::move_iterator(rhs.begin()), std::move_iterator(rhs.end()));
    }
    
    // (3)
    ilist& operator=(std::initializer_list<T> init_list) {
        assign(init_list);
        return *this;
    }
    
    // (1)
    void assign(size_type count, value_type const& value) {
        __assign_element_wise([&, i = size_type(0)]() mutable { return i != count; }, [&]() -> decltype(auto) { return value; });
    }
    
    // (2)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    void assign(InputIt first, Sentinel last) {
        __assign_element_wise(first, last);
    }
    
    // (2)
    template <input_range_for<value_type> Range>
    void assign(Range&& range) {
        assign(__utl_begin(range), __utl_end(range));
    }

    // (3)
    void assign(std::initializer_list<T> init_list) {
        assign(init_list.begin(), init_list.end());
    }
    
    // MARK: Observers
    
    allocator_type get_allocator() const noexcept { return __allocator_; }
    
    reference front() { return const_cast<reference>(static_cast<ilist const*>(this)->front()); }
    const_reference front() const { __utl_expect(!empty()); return *begin(); }
    
    reference back() { return const_cast<reference>(static_cast<ilist const*>(this)->back()); }
    const_reference back() const { __utl_expect(!empty()); return *--end(); }

    iterator begin() { return iterator(__sentinel()->__next); }
    const_iterator begin() const { return const_iterator(__sentinel()->__next); }
    const_iterator cbegin() const { return begin(); }
    iterator end() { return iterator(__sentinel()); }
    const_iterator end() const { return const_iterator(__sentinel()); }
    const_iterator cend() const { return end(); }
    reverse_iterator rbegin() { return std::reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return std::reverse_iterator(end()); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    reverse_iterator rend() { return std::reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return std::reverse_iterator(begin()); }
    const_reverse_iterator crend() const { return rend(); }
    
    [[nodiscard]] bool empty() const {
        return __sentinel() == __sentinel()->__prev;
    }
    
    // MARK: Modifiers
    
    void clear() noexcept {
        erase(begin(), end());
    }
    
    // (1)
    iterator insert(const_iterator pos, value_type const& value) {
        return __insert_impl(pos, 1, [&]{
            return __construct(__allocate(), value);
        });
    }
    
    // (2)
    iterator insert(const_iterator pos, value_type&& value) {
        return __insert_impl(pos, 1, [&]{
            return __construct(__allocate(), std::move(value));
        });
    }
    
    // (3)
    iterator insert(const_iterator pos, size_type count, value_type const& value) {
        return __insert_impl(pos, count, [&]{
            return __construct(__allocate(), value);
        });
    }
    
    // (4)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    iterator insert(const_iterator pos, InputIt first, Sentinel last) {
        return __insert_impl_itr(pos, first, last);
    }
        
    // (5)
    iterator insert(const_iterator pos, std::initializer_list<T> init_list) {
        return __insert_impl(pos, init_list.size(), [this, itr = init_list.begin()]() mutable {
            return __construct(__allocate(), *itr++);
        });
    }
    
    // (a)
    iterator insert(const_iterator pos, value_type* node) {
        return __insert_impl(pos, 1, [&]{ return node; });
    }
    
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        return __insert_impl(pos, 1, [&]{
            return __construct(__allocate(), std::forward<Args>(args)...);
        });
    }
    
    std::pair<iterator, value_type*> __extract_impl(const_iterator cpos) {
        iterator pos(cpos);
        std::prev(pos)->__next = std::next(pos).to_address();
        auto next = std::next(pos);
        next->__prev = std::prev(pos).to_address();
        return { next, pos.to_address() };
    }
    
    /// Remove an element from the list and take ownership of it.
    __utl_nodiscard value_type* extract(const_iterator cpos) {
        value_type* const result = __extract_impl(cpos).second;
        result->__prev = nullptr;
        result->__next = nullptr;
        return result;
    }
    
    /// \overload
    __utl_nodiscard value_type* extract(value_type const* element) {
        return extract(const_iterator(element));
    }
    
    // (1)
    iterator erase(const_iterator cpos) {
        auto const [next, addr] = __extract_impl(cpos);
        __destroy_and_deallocate(addr);
        return next;
    }
    
    // (1a)
    iterator erase(value_type const* element) {
        return erase(const_iterator(element));
    }
    
    // (2)
    iterator erase(const_iterator cfirst, const_iterator clast) {
        iterator first(cfirst);
        iterator last(clast);
        iterator prev = std::prev(first);
        for (iterator begin = first; begin != last; ) {
            iterator current = begin++;
            __destroy_and_deallocate(current.operator->());
        }
        prev->__next = last.operator->();
        last->__prev = prev.operator->();
        return last;
    }
    
    // (1)
    void push_back(value_type const& value) {
        insert(end(), value);
    }
    
    // (2)
    void push_back(value_type&& value) {
        insert(end(), std::move(value));
    }
    
    // (a)
    void push_back(value_type* node) {
        insert(end(), node);
    }
    
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        return *emplace(end(), std::forward<Args>(args)...);
    }
    
    void pop_back() {
        __utl_expect(!empty());
        erase(std::prev(end()));
    }
    
    // (1)
    void push_front(value_type const& value) {
        insert(begin(), value);
    }
    
    // (2)
    void push_front(value_type&& value) {
        insert(begin(), std::move(value));
    }
    
    // (a)
    void push_front(value_type* node) {
        insert(begin(), node);
    }
    
    template <typename... Args>
    reference emplace_front(Args&&... args) {
        return *emplace(begin(), std::forward<Args>(args)...);
    }
    
    void pop_front() {
        __utl_expect(!empty());
        erase(begin());
    }
    
    /// Resize methods are not available as we don't maintain size.
    
    // (1)
    void resize(size_type count) requires false;
    
    // (2)
    void resize(size_type count, value_type const& value) requires false;
    
    void swap(ilist& rhs) noexcept {
        __swap_impl<__alloc_traits::propagate_on_container_swap::value>(rhs);
    }
    
    /// Insert content of \p rhs into `this` before \p pos. Behaviour is undefined if `this == &rhs`.
    void splice(const_iterator pos, ilist& rhs) {
        __utl_assert(this != &rhs);
        splice(pos, rhs.begin(), rhs.end());
    }

    /// \overload
    void splice(const_iterator pos, ilist&& rhs) {
        splice(pos, static_cast<ilist&>(rhs));
    }
    
    /// Insert range `[begin, end)` into `this` before \p pos. Behaviour is undefined if inserted range is part of `this`.
    void splice(const_iterator pos, iterator begin, const_iterator end) {
        if (begin == end) {
            return;
        }
        value_type* const last = const_cast<value_type*>(pos.to_address());
        value_type* const first = last->prev();
        value_type* const rhs_front = begin.to_address();
        value_type* const rhs_before_front = rhs_front->prev();
        value_type* const rhs_back = const_cast<value_type*>(end->prev());
        first->__next = rhs_front;
        rhs_front->__prev = first;
        last->__prev = rhs_back;
        rhs_back->__next = last;
        value_type* const rhs_end = const_cast<value_type*>(end.to_address());
        rhs_before_front->__next = rhs_end;
        rhs_end->__prev = rhs_before_front;
    }
    
    // MARK: Internals
    
    void __assign_element_wise(std::invocable auto&& insert_while, auto&& get_elems) {
        iterator itr = begin();
        for (;; ++itr) {
            if (itr == end()) {
                goto this_smaller;
            }
            if (!insert_while()) {
                goto rhs_smaller;
            }
            /// We can safely assign because sibling pointers don't propagate on assignment.
            *itr = get_elems();
        }
    this_smaller:
        __insert_impl(end(), insert_while, [&]{ return __construct(__allocate(), get_elems()); });
        return;
    rhs_smaller:
        erase(itr, end());
        return;
    }
    
    void __assign_element_wise(auto rhs_itr, auto rhs_end) {
        __assign_element_wise([&]{ return rhs_itr != rhs_end; }, [&]() -> decltype(auto) { return *rhs_itr++; });
    }
    
    template <bool SwapAllocs>
    void __swap_impl(ilist& rhs) noexcept {
        if constexpr (SwapAllocs || __alloc_always_eq) {
            __fast_swap<SwapAllocs>(rhs);
        }
        else {
            if (__allocator_ == rhs.__allocator_) {
                __fast_swap<SwapAllocs>(rhs);
            }
            else {
                __sentinel_type rhs_copy;
                __move_assign_pointer_swap(rhs_copy, rhs.begin(), rhs.end());
                rhs.__reset();
                rhs.__assign_element_wise(begin(), end());
                __assign_element_wise(iterator(rhs_copy.__next), iterator(static_cast<value_type*>(&rhs_copy)));
            }
        }
    }
    
    template <bool SwapAllocs>
    void __fast_swap(ilist& rhs) {
        if (SwapAllocs) {
            std::swap(__allocator_, rhs.__allocator_);
        }
        __sentinel_type rhs_copy;
        __move_assign_pointer_swap(rhs_copy, rhs.begin(), rhs.end());
        __move_assign_pointer_swap(rhs.__sentinel_, this->begin(), this->end());
        __move_assign_pointer_swap(this->__sentinel_, iterator(rhs_copy.__next), iterator(static_cast<value_type*>(&rhs_copy)));
    }
    
    static void __move_assign_pointer_swap(__sentinel_type& sent, iterator begin, iterator end) {
        if (begin == end) {
            __reset(sent);
        }
        else {
            --end;
            sent.__next = begin.operator->();
            sent.__prev = end.operator->();
            begin->__prev = &sent;
            end->__next = &sent;
        }
        __assert_invariants(sent);
    }
    
    void __move_assign_pointer_swap(iterator begin, iterator end) {
        __move_assign_pointer_swap(__sentinel_, begin, end);
    }
    
    iterator __insert_impl(const_iterator cpos, size_type count, std::invocable auto&& get_nodes) {
        return __insert_impl(cpos, [&, i = size_type(0)]() mutable { return i++ < count; }, UTL_FORWARD(get_nodes));
    }
    
    iterator __insert_impl_itr(const_iterator cpos, auto first, auto last) {
        return __insert_impl(cpos, [&]{ return first != last; }, [&]{
            return __construct(__allocate(), *first++);
        });
    }
    
    iterator __insert_impl(const_iterator cpos, std::invocable auto&& insert_while, std::invocable auto&& get_nodes) {
        iterator pos = iterator(cpos);
        iterator prev = std::prev(pos);
        while (insert_while()) {
            value_type* new_node = get_nodes();
            prev->__next = new_node;
            new_node->__prev = prev.operator->();
            ++prev;
        }
        prev->__next = pos.operator->();
        iterator result = std::prev(pos) == prev ? pos : std::prev(pos);
        pos->__prev = prev.operator->();
        return result;
    }

    __sentinel_type*       __sentinel() { return const_cast<__sentinel_type*>(static_cast<ilist const*>(this)->__sentinel()); }
    __sentinel_type const* __sentinel() const { return &__sentinel_; }
    
    pointer __allocate() { return __alloc_traits::allocate(__allocator_, 1); }
    
    void __deallocate(pointer p) { __alloc_traits::deallocate(__allocator_, p, 1); }
    
    template <typename... Args>
    pointer __construct(pointer p, Args&&... args) {
        __alloc_traits::construct(__allocator_, p, std::forward<Args>(args)...);
        return p;
    }
    
    void __destroy(pointer p) {
        __alloc_traits::destroy(__allocator_, p);
    }
    
    void __destroy_and_deallocate(pointer p) {
        __destroy(p);
        __deallocate(p);
    }
    
    /// Reset this list to an empty list. No elements are destroyed or deallocated.
    static void __reset(__sentinel_type& sent) {
        sent.__sentinel_type::__assign(__sentinel_type(&sent, &sent));
    }
    
    void __reset() {
        __reset(__sentinel_);
    }
    
    static void __assert_invariants(ilist const& l) {
        __assert_invariants(l.__sentinel_);
    }
    
    static void __assert_invariants(__sentinel_type const& s) {
        const_iterator i = const_iterator(s.__next);
        __utl_assert(i->prev() == &s);
        for (std::size_t index = 0; i != const_iterator(&s); ++index) {
            const_iterator next = std::next(i);
            __utl_assert(std::prev(next) == i);
            i = next;
        }
    }
    
    [[no_unique_address]] allocator_type __allocator_;
    __sentinel_type __sentinel_;
};

template <typename CharT, typename Traits, typename T, typename A>
requires requires(std::basic_ostream<CharT, Traits>& ostream, T const& elem) {
    { ostream << elem } -> std::convertible_to<std::basic_ostream<CharT, Traits>&>;
}
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& ostream,
                                              ilist<T, A> const& l)
{
    ostream << "[";
    for (bool first = true; auto& elem: l) {
        ostream << (first ? (void)(first = false), "" : ", ") << elem;
    }
    return ostream << "]";
}

} // namespace utl
