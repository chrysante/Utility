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

class __ilist_node_base {};

template <typename Derived>
class ilist_node: public __ilist_node_base {
public:
    Derived*       prev()       { return static_cast<Derived*      >(__prev); }
    Derived const* prev() const { return static_cast<Derived const*>(__prev); }
    Derived*       next()       { return static_cast<Derived*      >(__next); }
    Derived const* next() const { return static_cast<Derived const*>(__next); }
    
protected:
    ilist_node(ilist_node* prev = nullptr, ilist_node* next = nullptr):
        __prev(prev), __next(next) {}
    
    /// Copy operatrions are no-ops, as we don't want to propagate sibling relationship with copying.
    ilist_node(ilist_node const&): ilist_node() {}
    
    ilist_node& operator=(ilist_node const&) { return *this; }
    
private:
    template <typename, typename>
    friend class ilist;
    
    /// Instead of copy construction and assignment we provide a special function to be used by ilist to copy relationship information.
    void __assign(ilist_node const& rhs) {
        __prev = rhs.__prev;
        __next = rhs.__next;
    }

    ilist_node*       __weak_prev()       { return __prev; }
    ilist_node const* __weak_prev() const { return __prev; }
    ilist_node*       __weak_next()       { return __next; }
    ilist_node const* __weak_next() const { return __next; }
    
    void __set_prev(ilist_node* prev) { __prev = prev; }
    void __set_next(ilist_node* next) { __next = next; }
    
    ilist_node* __prev;
    ilist_node* __next;
};

template <typename Derived, typename Parent = Derived>
struct ilist_node_with_parent: ilist_node<Derived> {
public:
    ilist_node_with_parent(Parent* parent): _parent(parent) {}

    ilist_node_with_parent(ilist_node_with_parent* prev = nullptr,
                           ilist_node_with_parent* next = nullptr,
                           Parent* parent = nullptr): ilist_node<Derived>(prev, next), _parent(parent) {}
    
    
    Parent*       parent()       { return _parent; }
    Parent const* parent() const { return _parent; }
    
    void set_parent(Parent* parent) { _parent = parent; }
    
private:
    Parent* _parent;
};

// This basically models the std::derived_from concept.
template <typename T>
struct __is_ilist_node:
    __all_t<std::is_base_of<__ilist_node_base, T>,
            std::is_convertible<T, __ilist_node_base>>
{};

template <typename T, typename Allocator>
class ilist {
public:
    template <typename N>
    struct __iterator_impl {
    private:
        template <typename, typename>
        friend class ilist;
        
        explicit __iterator_impl(__iterator_impl<N const> rhs) requires(!std::is_const_v<N>):
            __node(const_cast<N*>(rhs.__node)) {}
        
        explicit __iterator_impl(copy_cv_t<N, ilist_node<std::remove_const_t<N>>>* node):
            __node(static_cast<N*>(node)) {}
        
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = N;
        using pointer = N*;
        using reference = N&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        __iterator_impl(pointer node): __node(node) {}
        __iterator_impl(__iterator_impl<std::remove_const_t<N>> rhs) requires(std::is_const_v<N>):
            __node(rhs.__node) {}
        
        operator pointer() const { return operator->(); }
        
        pointer operator->() const { return __node; }
        
        __iterator_impl& operator++() {
            __node = __node->next();
            return *this;
        }
        
        __iterator_impl operator++(int) {
            auto result = *this;
            ++*this;
            return result;
        }
        
        __iterator_impl& operator--() {
            __node = __node->prev();
            return *this;
        }
        
        __iterator_impl operator--(int) {
            auto result = *this;
            --*this;
            return result;
        }
        
        bool operator==(__iterator_impl const& rhs) const = default;
        
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
    
    using __alloc_traits = std::allocator_traits<allocator_type>;
    using __sentinel_type = ilist_node<value_type>;
    static constexpr bool __alloc_always_eq = __alloc_traits::is_always_equal::value;
    
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
    ilist(ilist&& rhs) requires std::is_default_constructible_v<allocator_type>:
        ilist(std::move(rhs), rhs.__allocator_) {}
    
    // (9)
    ilist(ilist&& rhs, allocator_type const& alloc): ilist(alloc) {
        *this = std::move(rhs);
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
        if (__alloc_always_eq || __allocator_ == rhs.__allocator_) {
            if constexpr (alloc_propagate) {
                __allocator_ = rhs.__allocator_;
            }
            __swap_impl(rhs, false);
        }
        else {
            clear();
            if constexpr (alloc_propagate) {
                __allocator_ = rhs.__allocator_;
            }
            // Assign element-wise, as we must reallocate because unequal allocators.
            __assign_element_wise(std::move_iterator(rhs.begin()), std::move_iterator(rhs.end()));
        }
        return *this;
    }
    
    // (3)
    ilist& operator=(std::initializer_list<T> init_list) {
        assign(init_list);
        return *this;
    }
    
    // (1)
    void assign(size_type count, value_type const& value) {
        __assign_element_wise([&, i = size_type(0)]() mutable { return i != count; }, [&]() { return value; });
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

    iterator begin() { return iterator(__sentinel()->next()); }
    const_iterator begin() const { return const_iterator(__sentinel()->next()); }
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
        /// Avoid using iterators to allow use with incomplete \p value_type
        return __sentinel() == __sentinel()->__weak_prev();
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
        return __insert_impl(pos, [&]{ return first != last; }, [&]{
            return __construct(__allocate(), *first++);
        });
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
    
    // (1)
    iterator erase(const_iterator cpos) {
        iterator pos(cpos);
        std::prev(pos)->__set_next(std::next(pos));
        std::next(pos)->__set_prev(std::prev(pos));
        __destroy_and_deallocate(pos);
    }
    
    // (2)
    iterator erase(const_iterator cfirst, const_iterator clast) {
        iterator first(cfirst);
        iterator last(clast);
        iterator prev = std::prev(first);
        for (iterator begin = first; begin != last; ) {
            iterator current = begin++;
            __destroy_and_deallocate(current);
        }
        prev->__set_next(last);
        last->__set_prev(prev);
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
        __swap_impl(rhs, __alloc_traits::propagate_on_container_swap::value);
    }
    
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
        __assign_element_wise([&]{ return rhs_itr != rhs_end; }, [&]{ return *rhs_itr++; });
    }
    
    void __swap_impl(ilist& rhs, bool swap_allocs) noexcept {
        if (swap_allocs || __alloc_always_eq || __allocator_ == rhs.__allocator_) {
            __fast_swap(rhs, swap_allocs);
        }
        else {
            __sentinel_type rhs_copy;
            __move_assign_pointer_swap(rhs_copy, rhs.begin(), rhs.end());
            rhs.__reset();
            rhs.__assign_element_wise(begin(), end());
            __assign_element_wise(iterator(rhs_copy.next()), iterator(static_cast<value_type*>(&rhs_copy)));
        }
    }
    
    void __fast_swap(ilist& rhs, bool swap_allocs) {
        if (swap_allocs) {
            std::swap(__allocator_, rhs.__allocator_);
        }
        __sentinel_type rhs_copy;
        __move_assign_pointer_swap(rhs_copy, rhs.begin(), rhs.end());
        __move_assign_pointer_swap(rhs.__sentinel_, this->begin(), this->end());
        __move_assign_pointer_swap(this->__sentinel_, rhs_copy.next(), static_cast<value_type*>(&rhs_copy));
    }
    
    static void __move_assign_pointer_swap(__sentinel_type& sent, iterator begin, iterator end) {
        if (begin == end) {
            __reset(sent);
        }
        else {
            --end;
            sent.__set_next(begin);
            sent.__set_prev(end);
            begin->__set_prev(&sent);
            end->__set_next(&sent);
        }
        __assert_invariants(sent);
    }
    
    void __move_assign_pointer_swap(iterator begin, iterator end) {
        __move_assign_pointer_swap(__sentinel_, begin, end);
    }
    
    iterator __insert_impl(const_iterator cpos, size_type count, auto&& get_nodes) {
        return __insert_impl(cpos, [&, i = size_type(0)]() mutable { return i++ < count; }, UTL_FORWARD(get_nodes));
    }
    
    iterator __insert_impl(const_iterator cpos, std::invocable auto&& insert_while, auto&& get_nodes) {
        iterator pos = iterator(cpos);
        iterator prev = std::prev(pos);
        while (insert_while()) {
            value_type* new_node = get_nodes();
            prev->__set_next(new_node);
            new_node->__set_prev(prev);
            ++prev;
        }
        prev->__set_next(pos);
        iterator result = std::prev(pos) == prev ? pos : std::prev(pos);
        pos->__set_prev(prev);
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
        const_iterator i = s.next();
        __utl_assert(i->prev() == &s);
        for (std::size_t index = 0; i != (&s); ++index) {
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
