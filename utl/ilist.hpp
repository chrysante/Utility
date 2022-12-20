#pragma once

#include <iterator>

#include "__base.hpp"
#include "__memory_resource_base.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T, typename Allocator = std::allocator<T>>
class ilist;

template <typename Derived>
class ilist_node {
public:
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

template <typename T, typename Allocator>
class ilist {
    static_assert(std::is_base_of_v<ilist_node<T>, T>);
    
    template <typename N>
    struct _iterator_impl {
        using difference_type = std::ptrdiff_t;
        using value_type = N;
        using pointer = N*;
        using reference = N&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        _iterator_impl(pointer node): _node(node) {}
        
        operator pointer() const { return operator->(); }
        
        pointer operator->() const { return _node; }
        
        _iterator_impl& operator++() {
            _node = _node->next();
            return *this;
        }
        
        _iterator_impl operator++(int) {
            auto result = *this;
            ++*this;
            return result;
        }
        
        _iterator_impl& operator--() {
            _node = _node->prev();
            return *this;
        }
        
        _iterator_impl operator--(int) {
            auto result = *this;
            --*this;
            return result;
        }
        
        bool operator==(_iterator_impl const& rhs) const = default;
        
        reference operator*() const { return *_node; }
        
    private:
        pointer _node;
    };
    
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = value_type const*;
    using reference = value_type&;
    using const_reference = value_type const&;
    using iterator = _iterator_impl<value_type>;
    using const_iterator = _iterator_impl<value_type const>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
public:
    ilist(): _sentinel_(_sentinel(), _sentinel()) {}
    
    // MARK: Observers
    
    iterator begin() { return iterator(_sentinel()->next()); }
    const_iterator begin() const { return const_iterator(_sentinel()->next()); }
    iterator end() { return iterator(_sentinel()); }
    const_iterator end() const { return const_iterator(_sentinel()); }
    reverse_iterator rbegin() { return std::reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return std::reverse_iterator(end()); }
    reverse_iterator rend() { return std::reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return std::reverse_iterator(begin()); }
    
    bool empty() const { return _sentinel()->next() != _sentinel(); }
    
    reference front() { return const_cast<reference>(static_cast<ilist const*>(this)->front()); }
    const_reference front() const { __utl_expect(!empty()); return *begin(); }
    
    reference back() { return const_cast<reference>(static_cast<ilist const*>(this)->back()); }
    const_reference back() const { __utl_expect(!empty()); return *--end(); }
    
    // MARK: Modifiers
    
    void push_front(pointer value) {
        insert_before(value, begin());
    }
    
    void push_back(pointer value) {
        insert_before(value, end());
    }
    
    void insert_before(pointer value, const_pointer before) {
        pointer bef = const_cast<pointer>(before);
        bef->prev()->set_next(value);
        value->set_prev(bef->prev());
        value->set_next(bef);
        bef->set_prev(value);
    }
    
    pointer erase(pointer value) {
        value->prev()->set_next(value->next());
        value->next()->set_prev(value->prev());
        value->set_prev(nullptr);
        value->set_next(nullptr);
        return value;
    }
    
private:
    pointer _sentinel() { return const_cast<pointer>(static_cast<ilist const*>(this)->_sentinel()); }
    const_pointer _sentinel() const { return static_cast<const_pointer>(&_sentinel_); }
    
private:
    ilist_node<value_type> _sentinel_;
};

} // namespace utl
