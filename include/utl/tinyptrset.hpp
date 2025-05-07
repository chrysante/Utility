#ifndef UTL_TINYPTRSET_HPP
#define UTL_TINYPTRSET_HPP

#include <memory>
#include <set>
#include <type_traits>

#include "ipp.hpp"

namespace utl {

namespace internal {

/// Typedef for the allocator type of `cont` rebound to allocator instances of
/// `Cont`
template <typename Cont>
using ContAllocator = typename std::allocator_traits<
    typename Cont::allocator_type>::template rebind_alloc<Cont>;

} // namespace internal

template <typename P, typename LargeSet = std::set<P>>
class tinyptrset: private internal::ContAllocator<LargeSet> {
    using SetAllocator = internal::ContAllocator<LargeSet>;

    enum class State { Empty, Small, Large };

public:
    static_assert(std::is_pointer_v<P>);
    static_assert(alignof(std::remove_pointer_t<P>) % 4 == 0,
                  "Pointee type must be aligned to at least 4 bytes");

    using value_type = P;
    using allocator_type = typename LargeSet::allocator_type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using const_reference = value_type;
    using reference = const_reference;
    using const_pointer = P const*;
    using pointer = const_pointer;

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = tinyptrset::value_type;
        using difference_type = tinyptrset::difference_type;
        using pointer = tinyptrset::pointer;
        using reference = tinyptrset::reference;

        iterator(): _ptr(nullptr), _setItr(), _isEnd(true) {}

        iterator(value_type v): _ptr(v), _setItr(), _isEnd(false) {}

        iterator(typename LargeSet::const_iterator setItr):
            _ptr(nullptr), _setItr(setItr), _isEnd(false) {}

        reference operator*() const { return _ptr ? _ptr : *_setItr; }

        pointer operator->() const { return _ptr ? &_ptr : &*_setItr; }

        iterator& operator++() {
            if (_ptr) {
                _isEnd = true;
            }
            else {
                ++_setItr;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            if (_ptr) {
                _isEnd = false;
            }
            else {
                --_setItr;
            }
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(iterator const& other) const {
            if (_isEnd && other._isEnd) {
                return true;
            }
            if (_ptr || other._ptr) {
                return _ptr == other._ptr;
            }
            return _setItr == other._setItr;
        }

        bool operator!=(iterator const& other) const {
            return !(*this == other);
        }

    private:
        value_type _ptr;
        typename LargeSet::const_iterator _setItr;
        bool _isEnd;
        friend class tinyptrset;
    };

    using const_iterator = iterator;

    tinyptrset() = default;

    explicit tinyptrset(allocator_type const& alloc):
        SetAllocator(alloc), _ptr(nullptr) {}

    tinyptrset(tinyptrset const& other):
        tinyptrset(other, other.get_allocator()) {}

    tinyptrset(tinyptrset const& other, allocator_type const& alloc):
        SetAllocator(alloc) {
        switch (other._state()) {
        case State::Empty: _ptr = {}; return;
        case State::Small: _ptr = other._ptr; return;
        case State::Large: {
            auto* setPtr = _allocateSet(*other._getSet());
            _assignSet(setPtr);
            return;
        }
        }
        utl::unreachable();
    }

    tinyptrset(tinyptrset&& other):
        tinyptrset(std::move(other), other.get_allocator()) {}

    tinyptrset(tinyptrset&& other, allocator_type const& alloc):
        SetAllocator(alloc) {
        switch (other._state()) {
        case State::Empty: _ptr = {}; return;
        case State::Small: _ptr = other._ptr; return;
        case State::Large:
            _assignSet(other._getSet());
            other._ptr = {};
            return;
        }
        utl::unreachable();
    }

    ~tinyptrset() { _deallocateIfLarge(); }

    tinyptrset& operator=(tinyptrset const& other) {
        if (this == &other) {
            return *this;
        }
        _deallocateIfLarge();
        switch (other._state()) {
        case State::Empty: _ptr = { nullptr, State::Empty }; break;
        case State::Small: _ptr = other._ptr; break;
        case State::Large: {
            auto* setPtr = _allocateSet(*other._getSet());
            _assignSet(setPtr);
            break;
        }
        }
        return *this;
    }

    tinyptrset& operator=(tinyptrset&& other) noexcept {
        if (this == &other) {
            return;
        }
        _deallocateIfLarge();
        switch (other._state()) {
        case State::Empty: _ptr = { nullptr, State::Empty }; break;
        case State::Small: _ptr = other._ptr; break;
        case State::Large:
            // Can't be bothered to implement this
            __utl_assert((SetAllocator&)*this == (SetAllocator&)other);
            _assignSet(other._getSet());
            other._ptr = {};
            break;
        }
        return *this;
    }

    allocator_type get_allocator() const {
        return allocator_type(static_cast<SetAllocator const&>(*this));
    }

    std::pair<iterator, bool> insert(value_type p) {
        switch (_state()) {
        case State::Empty: _ptr = { p, State::Small }; return { begin(), true };
        case State::Small: {
            if (_ptr.pointer() == p) {
                return { begin(), false };
            }
            LargeSet* setPtr = _allocateSet();
            setPtr->insert(_ptr.pointer());
            _assignSet(setPtr);
            auto [itr, inserted] = setPtr->insert(p);
            __utl_assert(inserted);
            return { iterator(itr), true };
        }
        case State::Large: {
            auto [itr, inserted] = _getSet()->insert(p);
            return { iterator(itr), inserted };
        }
        }
        utl::unreachable();
    }

    bool contains(value_type p) const {
        switch (_state()) {
        case State::Empty: return false;
        case State::Small: return _ptr.pointer() == p;
        case State::Large: return _getSet()->contains(p);
        }
        utl::unreachable();
    }

    bool erase(value_type p) {
        switch (_state()) {
        case State::Empty: return false;
        case State::Small:
            if (_ptr.pointer() == p) {
                _ptr = {};
                return true;
            }
            return false;
        case State::Large: {
            auto* set = _getSet();
            bool result = set->erase(p) == 1;
            if (set->size() == 1) {
                _ptr = { *set->begin(), State::Small };
                _deallocateSet(set);
            }
            return result;
        }
        }
        utl::unreachable();
    }

    size_t size() const {
        switch (_state()) {
        case State::Empty: return 0;
        case State::Small: return 1;
        case State::Large: return _getSet()->size();
        }
        utl::unreachable();
    }

    bool empty() const { return _isEmpty(); }

    iterator begin() const {
        switch (_state()) {
        case State::Empty: return iterator();
        case State::Small: return iterator(_ptr.pointer());
        case State::Large: return iterator(_getSet()->cbegin());
        }
        utl::unreachable();
    }

    iterator end() const {
        switch (_state()) {
        case State::Empty: [[fallthrough]];
        case State::Small: return iterator();
        case State::Large: return iterator(_getSet()->cend());
        }
        utl::unreachable();
    }

private:
    ipp<value_type, State, 2> _ptr = {};

    State _state() const { return _ptr.integer(); }

    bool _isEmpty() const { return _state() == State::Empty; }

    bool _isSmall() const { return _state() == State::Small; }

    bool _isLarge() const { return _state() == State::Large; }

    LargeSet* _getSet() const {
        __utl_assert(_isLarge());
        return reinterpret_cast<LargeSet*>(_ptr.pointer());
    }

    template <typename... Args>
    LargeSet* _allocateSet(Args&&... args) {
        LargeSet* setPtr =
            std::allocator_traits<SetAllocator>::allocate(*this, 1);
        std::allocator_traits<
            SetAllocator>::construct(*this, setPtr, std::forward<Args>(args)...,
                                     typename LargeSet::allocator_type(*this));
        return setPtr;
    }

    void _deallocateSet(LargeSet* setPtr) {
        std::allocator_traits<SetAllocator>::destroy(*this, setPtr);
        std::allocator_traits<SetAllocator>::deallocate(*this, setPtr, 1);
    }

    void _assignSet(LargeSet* set) {
        _ptr.set_pointer(reinterpret_cast<value_type>(set));
        _ptr.set_integer(State::Large);
    }

    void _deallocateIfLarge() {
        if (_isLarge()) {
            _deallocateSet(_getSet());
        }
    }
};

} // namespace utl

#endif // UTL_TINYPTRSET_HPP
