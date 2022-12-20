#pragma once

#include <iterator>

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
    using __derived_type = Derived;
    
    ilist_node(ilist_node* prev = nullptr, ilist_node* next = nullptr): _prev(prev), _next(next) {}
    
    Derived*       prev()       { return static_cast<Derived*      >(_prev); }
    Derived const* prev() const { return static_cast<Derived const*>(_prev); }
    Derived*       next()       { return static_cast<Derived*      >(_next); }
    Derived const* next() const { return static_cast<Derived const*>(_next); }
    
    void set_prev(ilist_node* prev) { _prev = prev; }
    void set_next(ilist_node* next) { _next = next; }
    
private:
    ilist_node* _prev;
    ilist_node* _next;
};

template <typename Derived, typename Parent>
struct ilist_node_with_parent: ilist_node<Derived> {
public:
    ilist_node_with_parent(ilist_node_with_parent* prev = nullptr,
                           ilist_node_with_parent* next = nullptr,
                           Parent* parent = nullptr): ilist_node<Derived>(prev, next), _parent(parent) {}
    
    Parent*       parent()       { return _parent; }
    Parent const* parent() const { return _parent; }
    
    void set_parent(Parent* parent) { _parent = parent; }
    
private:
    Parent* _parent;
};

template <typename T, typename = void>
struct __is_ilist_node: std::false_type {};

template <typename T>
struct __is_ilist_node<T, std::void_t<std::is_convertible<T, typename T::__derived_type>>>:
    __all_t<std::is_base_of<__ilist_node_base, T>,
            std::is_convertible<T, __ilist_node_base>,
            std::is_convertible<T, typename T::__derived_type>>
{};

template <typename T, typename Allocator> requires __is_ilist_node<T>::value
class ilist<T, Allocator> {
public:
    template <typename N>
    struct __iterator_impl {
    private:
        template <typename, typename>
        friend class ilist;
        
        explicit __iterator_impl(__iterator_impl<N const> rhs) requires(!std::is_const_v<N>):
            __node(const_cast<N*>(rhs.__node)) {}
        
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
    ilist(ilist const& rhs) requires std::is_default_constructible_v<allocator_type>: ilist(rhs, allocator_type()) {}
    
    // (7)
    ilist(ilist const& rhs, allocator_type const& alloc): ilist(alloc)
    {
        __utl_debugfail();
    }
    
    // (8)
    ilist(ilist&& rhs) requires std::is_default_constructible_v<allocator_type>: ilist(std::move(rhs), allocator_type()) {}
    
    // (9)
    ilist(ilist&& rhs, allocator_type const& alloc);
    
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
        assign(rhs.begin(), rhs.end());
        return *this;
    }
    
    // (2)
    ilist& operator=(ilist&& rhs) noexcept {
        this->clear();
        this->__sentinel_ = rhs.__sentinel_;
        this->begin()->set_prev(this->__sentinel());
        std::prev(this->end())->set_next(this->__sentinel());
        rhs.__reset();
        return *this;
    }
    
    // (3)
    ilist& operator=(std::initializer_list<T> init_list) {
        assign(init_list);
        return *this;
    }
    
    // (1)
    void assign(size_type count, value_type const& value) {
        clear();
        insert(begin(), count, value);
    }
    
    // (2)
    template <input_iterator_for<value_type> InputIt, sentinel_for<InputIt> Sentinel>
    void assign(InputIt first, Sentinel last) {
        clear();
        insert(begin(), first, last);
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
    iterator end() { return iterator(__sentinel()); }
    const_iterator end() const { return const_iterator(__sentinel()); }
    reverse_iterator rbegin() { return std::reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return std::reverse_iterator(end()); }
    reverse_iterator rend() { return std::reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return std::reverse_iterator(begin()); }
    
    [[nodiscard]] bool empty() const { return begin() == end(); }
    
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
    
    // (b)
    iterator insert(const_iterator pos, ilist&& list);
    
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        return __insert_impl(pos, 1, [&]{
            return __construct(__allocate(), std::forward<Args>(args)...);
        });
    }
    
    // (1)
    iterator erase(const_iterator cpos) {
        iterator pos(cpos);
        std::prev(pos)->set_next(std::next(pos));
        std::next(pos)->set_prev(std::prev(pos));
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
        prev->set_next(last);
        last->set_prev(prev);
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
    
    // (1)
//    void resize(size_type count);
    
    // (2)
//    void resize(size_type count, value_type const& value);
    
    void swap(ilist& rhs) noexcept {
        ilist tmp = std::move(rhs);
        rhs = std::move(*this);
        *this = std::move(tmp);
    }
    
    iterator __insert_impl(const_iterator cpos, size_type count, auto&& get_nodes) {
        return __insert_impl(cpos, [&, i = size_type(0)]() mutable { return i++ < count; }, UTL_FORWARD(get_nodes));
    }
    
    iterator __insert_impl(const_iterator cpos, std::invocable auto&& insert_while, auto&& get_nodes) {
        iterator pos = iterator(cpos);
        iterator prev = std::prev(pos);
        while (insert_while()) {
            value_type* new_node = get_nodes();
            prev->set_next(new_node);
            new_node->set_prev(prev);
            ++prev;
        }
        prev->set_next(pos);
        iterator result = std::prev(pos) == prev ? pos : std::prev(pos);
        pos->set_prev(prev);
        return result;
    }

    pointer __sentinel() { return const_cast<pointer>(static_cast<ilist const*>(this)->__sentinel()); }
    const_pointer __sentinel() const { return static_cast<const_pointer>(&__sentinel_); }
    
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
    void __reset() {
        __sentinel()->set_prev(__sentinel());
        __sentinel()->set_next(__sentinel());
    }
    
    [[no_unique_address]] allocator_type __allocator_;
    __sentinel_type __sentinel_;
};

} // namespace utl
