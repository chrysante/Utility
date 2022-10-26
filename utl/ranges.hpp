#ifndef UTL_RANGES_HPP
#define UTL_RANGES_HPP

#include "__base.hpp"
#include "__debug.hpp"
#include "__ranges_base.hpp"
#include "concepts.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

/// MARK: __range_view

template <typename Itr, typename S = Itr>
class __range_view {
public:
    using iterator = Itr;
    using const_iterator = iterator;
    
    constexpr explicit __range_view(Itr first, S last):
    __first(first),
    __last(last)
    {}
    constexpr Itr begin() const { return __first; }
    constexpr S end() const { return __last; }
    
    Itr __first;
    S __last;
};

/// MARK: __range_adapter

template <typename Range>
class __range_adapter {
    static_assert(!std::is_reference_v<Range>);
    
public:
    __range_adapter(auto&& range): __r(UTL_FORWARD(range)) {}
    
    constexpr Range& __range() { return __r; }
    constexpr Range const& __range() const { return __r; }
    Range __r;
};

template <typename Range>
class __range_adapter<Range&> {
public:
    constexpr explicit __range_adapter(Range& range): __r(range) {}
    
    constexpr Range& __range() const { return __r; }
    Range& __r;
};

/// MARK: enumerate

template <iterator Itr>
class enumerating_iterator: public __wrap_iterator<Itr, enumerating_iterator<Itr>> {
public:
    using __wrap = __wrap_iterator<Itr, enumerating_iterator>;
    
    using typename __wrap::difference_type;
    using value_type        = std::pair<std::size_t, typename __wrap::value_type>;
    using pointer           = void;
    using reference         = std::pair<std::size_t, typename __wrap::reference>;
    using typename __wrap::iterator_category;
    
    constexpr explicit enumerating_iterator(Itr itr, std::size_t index = 0):
    __wrap(itr),
    __index(index)
    {}
    
    friend constexpr enumerating_iterator operator+(enumerating_iterator itr, difference_type offset) requires random_access_iterator<Itr> {
        itr.__itr += offset;
        itr.__index += offset;
        return itr;
    }
    
    friend constexpr enumerating_iterator operator+(difference_type offset, enumerating_iterator itr) requires random_access_iterator<Itr> {
        return itr + offset;
    }
    
    friend constexpr enumerating_iterator operator-(enumerating_iterator itr, difference_type offset) requires random_access_iterator<Itr> {
        itr.__itr -= offset;
        itr.__index -= offset;
        return itr;
    }
    
    friend constexpr difference_type operator-(enumerating_iterator lhs, enumerating_iterator rhs) requires random_access_iterator<Itr> {
        return lhs.__itr - rhs.__itr;
    }
    
    constexpr enumerating_iterator& operator++() {
        ++this->__itr;
        ++__index;
        return *this;
    }
    
    using __wrap::operator++;
    
    constexpr enumerating_iterator& operator--() requires bidirectional_iterator<Itr> {
        --this->__itr;
        --__index;
        return *this;
    }
    
    using __wrap::operator--;
    
    constexpr std::pair<std::size_t, decltype(*std::declval<Itr>())> operator*() const { return { __index, *this->__itr }; }
    
    std::size_t __index;
};

template <typename Range>
class __enumerated_range: public __range_adapter<Range> {
public:
    using difference_type = std::ptrdiff_t;
    using iterator = enumerating_iterator<iterator_type_t<Range>>;
    using const_iterator = enumerating_iterator<const_iterator_type_t<Range>>;
    using sentinel = enumerating_iterator<sentinel_type_t<Range>>;
    using const_sentinel = enumerating_iterator<const_sentinel_type_t<Range>>;
    
    template <typename R>
    constexpr explicit __enumerated_range(R&& range, std::size_t begin_index): __range_adapter<Range>(UTL_FORWARD(range)), __begin_index(begin_index) {}
    
    constexpr iterator begin() { return iterator(__utl_begin(this->__range()), __begin_index); }
    constexpr const_iterator begin() const { return const_iterator(__utl_begin(this->__range()), __begin_index); }
    constexpr sentinel end() { return sentinel(__utl_end(this->__range()), __begin_index); }
    constexpr const_sentinel end() const { return const_sentinel(__utl_end(this->__range()), __begin_index); }
    
    std::size_t __begin_index;
};


/// \brief Enumerate values between \p first and \p last
/// \returns A range of pairs of indices and the values in the range \p (first,last)
template <iterator Itr, sentinel_for<Itr> Sentinel>
[[nodiscard]] constexpr __enumerated_range<__range_view<Itr, Sentinel>> enumerate(Itr begin, Sentinel end, std::size_t begin_index = 0) {
    return __enumerated_range<__range_view<Itr, Sentinel>>(__range_view(begin, end), begin_index);
}

/// \brief Enumerate all values in \p range
/// \returns A range of pairs of indices and the values in \p range
template <range Range>
[[nodiscard]] constexpr __enumerated_range<Range> enumerate(Range&& range, std::size_t begin_index = 0) {
    return __enumerated_range<Range>(UTL_FORWARD(range), begin_index);
}

/// MARK: transform

/// \brief Wraps an iterator and applies a transform on the values when dereferencing.
template <iterator Itr, typename Transform>
class transform_iterator: public __wrap_iterator<Itr, transform_iterator<Itr, Transform>> {
    static_assert(requires(Itr itr, Transform t) { std::invoke(t, *itr); });
    
public:
    using __wrap = __wrap_iterator<Itr, transform_iterator>;
    
    using typename __wrap::difference_type;
    using value_type        = decltype(std::declval<Transform>()(*std::declval<Itr>()));
    using pointer           = void;
    using reference         = void;
    using typename __wrap::iterator_category;
    
    constexpr decltype(auto) operator*() const { return __transform(*this->__itr); }
    
    constexpr explicit transform_iterator(Itr itr, Transform const& transform): __wrap(itr), __transform(transform) {}
    constexpr explicit transform_iterator(Itr itr, Transform&& transform): __wrap(itr), __transform(std::move(transform)) {}
    
    [[no_unique_address]] Transform __transform;
};

template <typename Range, typename Transform>
class __transform_range: public __range_adapter<Range> {
public:
    using iterator = transform_iterator<iterator_type_t<Range>, Transform>;
    using const_iterator = transform_iterator<const_iterator_type_t<Range>, Transform>;
    using sentinel = transform_iterator<sentinel_type_t<Range>, Transform>;
    using const_sentinel = transform_iterator<const_sentinel_type_t<Range>, Transform>;
    
    template <typename R, typename T>
    constexpr explicit __transform_range(R&& range, T&& transform): __range_adapter<Range>(UTL_FORWARD(range)), __transform(UTL_FORWARD(transform)) {}
    
    constexpr iterator begin() { return iterator(__utl_begin(this->__range()), __transform); }
    constexpr const_iterator begin() const { return const_iterator(__utl_begin(this->__range()), __transform); }
    constexpr sentinel end() { return sentinel(__utl_end(this->__range()), __transform); }
    constexpr const_sentinel end() const { return const_sentinel(__utl_end(this->__range()), __transform); }
    
    [[no_unique_address]] Transform __transform;
};

/// \brief View over a transformed range.
/// \details Transform is applied lazily on traversal.
template <iterator Itr, sentinel_for<Itr> Sentinel>
[[nodiscard]] constexpr auto transform(Itr begin, Sentinel end, std::invocable<decltype(*begin)> auto&& transform_fn) {
    return __transform_range<__range_view<Itr, Sentinel>, std::decay_t<decltype(transform_fn)>>(__range_view(begin, end), UTL_FORWARD(transform_fn));
}

/// \brief View over a transformed range.
/// \details Transform is applied lazily on traversal.
template <range Range>
[[nodiscard]] constexpr auto transform(Range&& range, std::invocable<decltype(*__utl_begin(range))> auto&& transform_fn) {
    return __transform_range<Range, std::decay_t<decltype(transform_fn)>>(UTL_FORWARD(range), UTL_FORWARD(transform_fn));
}

/// MARK: stride

/// \brief
template <iterator Itr>
class stride_iterator: public __wrap_iterator<Itr, stride_iterator<Itr>> {
public:
    using __wrap = __wrap_iterator<Itr, stride_iterator>;
    
    using typename __wrap::difference_type;
    using value_type        = typename __wrap::value_type;
    using pointer           = typename __wrap::pointer;
    using reference         = typename __wrap::reference;
    using typename __wrap::iterator_category;
    
    constexpr stride_iterator(Itr itr, difference_type stride): __wrap(itr), __stride(stride) {}
    
    friend constexpr stride_iterator operator+(stride_iterator itr, std::ptrdiff_t offset) requires random_access_iterator<Itr> {
        itr.__itr += itr.__stride * offset;
        return itr;
    }
    
    friend constexpr stride_iterator operator+(std::ptrdiff_t offset, stride_iterator itr) requires random_access_iterator<Itr> {
        return itr + offset;
    }
    
    friend constexpr stride_iterator operator-(stride_iterator itr, std::ptrdiff_t offset) requires random_access_iterator<Itr> {
        itr.__itr -= itr.__stride * offset;
        return itr;
    }
    
    friend constexpr difference_type operator-(stride_iterator lhs, stride_iterator rhs) requires random_access_iterator<Itr> {
        __utl_expect(lhs.__stride == rhs.__stride);
        return (lhs.__itr - rhs.__itr) / lhs.__stride;
    }
    
    constexpr stride_iterator& operator++() {
        if constexpr (random_access_iterator<Itr>) {
            this->__itr += __stride;
        }
        else {
            for (std::size_t i = 0; i < __stride; ++i, ++this->__itr);
        }
        return *this;
    }
    
    using __wrap::operator++;
    
    constexpr stride_iterator& operator--() requires bidirectional_iterator<Itr> {
        if constexpr (random_access_iterator<Itr>) {
            this->__itr -= __stride;
        }
        else {
            for (std::size_t i = 0; i < __stride; ++i, --this->__itr);
        }
        return *this;
    }
    
    using __wrap::operator--;
    
    difference_type __stride;
};

template <typename Range>
class __stride_range: public __range_adapter<Range> {
public:
    using difference_type = std::ptrdiff_t;
    using iterator = stride_iterator<iterator_type_t<Range>>;
    using const_iterator = stride_iterator<const_iterator_type_t<Range>>;
    using sentinel = stride_iterator<sentinel_type_t<Range>>;
    using const_sentinel = stride_iterator<const_sentinel_type_t<Range>>;
    
    constexpr explicit __stride_range(auto&& range, difference_type stride): __range_adapter<Range>(UTL_FORWARD(range)), __stride(stride) {}
    
    constexpr iterator begin() { return iterator(__utl_begin(this->__range()), __stride); }
    constexpr const_iterator begin() const { return const_iterator(__utl_begin(this->__range()), __stride); }
    constexpr sentinel end() { return sentinel(__utl_end(this->__range()), __stride); }
    constexpr const_sentinel end() const { return const_sentinel(__utl_end(this->__range()), __stride); }
    
    difference_type __stride;
};

/// \brief Iterate a range with a custom stride.
/// \warning \p stride must be divisible by the distance between \p begin and \p end
template <iterator Itr, sentinel_for<Itr> Sentinel>
[[nodiscard]] constexpr __stride_range<__range_view<Itr, Sentinel>> stride(Itr begin, Sentinel end, std::ptrdiff_t stride) {
    return __stride_range<__range_view<Itr, Sentinel>>(__range_view(begin, end), stride);
}

/// \brief Iterate a range with a custom stride.
/// \warning \p stride must be divisible by the size of \p range
template <utl::range Range>
[[nodiscard]] constexpr __stride_range<Range> stride(Range&& range, std::ptrdiff_t stride) {
    return __stride_range<Range>(UTL_FORWARD(range), stride);
}

/// MARK: reverse

template <typename Range>
class __reverse_range: __range_adapter<Range> {
public:
    using iterator = std::reverse_iterator<iterator_type_t<Range>>;
    using const_iterator = std::reverse_iterator<const_iterator_type_t<Range>>;
    using sentinel = std::reverse_iterator<sentinel_type_t<Range>>;
    using const_sentinel = std::reverse_iterator<const_sentinel_type_t<Range>>;
    
    constexpr __reverse_range(auto&& range): __range_adapter<Range>(UTL_FORWARD(range)) {}
    
    constexpr iterator begin() { return iterator(__utl_end(this->__range())); }
    constexpr const_iterator begin() const { return iterator(__utl_end(this->__range())); }
    constexpr sentinel end() { return iterator(__utl_begin(this->__range())); }
    constexpr const_sentinel end() const { return iterator(__utl_begin(this->__range())); }
};

/// \brief Reverse view over the range \p (begin,end)
template <iterator Itr, sentinel_for<Itr> S>
[[nodiscard]] constexpr __reverse_range<__range_view<Itr, S>> reverse(Itr begin, S end) {
    return __reverse_range<__range_view<Itr, S>>(__range_view(begin, end));
}

/// \brief Reverse view over \p range
template <range Range>
[[nodiscard]] constexpr __reverse_range<Range> reverse(Range&& range) {
    return __reverse_range<Range>(UTL_FORWARD(range));
}

/// MARK: Iota

/// \brief Ad hoc constructed range of integers
/// \details Unlike \p std::itoa, \p utl::iota is meant to be used e.g. as range argument in a range-based for loop like this:
/// \code for (int i: utl::iota(0, 10) { ... } \endcode
/// as a replacement for
/// \code for (int i = 0; i < 10; ++i) { ... } \endcode
template <typename>
class iota;

template <typename T>
class __iota_iterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = void;
    using reference = value_type;
    using iterator_category = std::random_access_iterator_tag;
    
    __utl_interface_export constexpr explicit __iota_iterator(value_type i = 0):
    __i(i)
    {}
    
    __utl_interface_export friend constexpr __iota_iterator operator+(__iota_iterator itr, difference_type diff) {
        itr.__i += diff;
        return itr;
    }
    
    __utl_interface_export friend constexpr __iota_iterator operator+(difference_type diff, __iota_iterator itr) {
        return itr + diff;
    }
    
    __utl_interface_export friend constexpr __iota_iterator operator-(__iota_iterator itr, difference_type diff) {
        itr.__i -= diff;
        return itr;
    }
    
    __utl_interface_export friend constexpr difference_type operator-(__iota_iterator lhs, __iota_iterator rhs) {
        return lhs.__i - rhs.__i;;
    }
    
    __utl_interface_export constexpr __iota_iterator& operator+=(difference_type diff) {
        return *this = *this + diff;
    }
    
    __utl_interface_export constexpr __iota_iterator& operator-=(difference_type diff) {
        return *this = *this - diff;
    }
    
    __utl_interface_export constexpr __iota_iterator& operator++() {
        ++__i;
        return *this;
    }
    __utl_interface_export constexpr __iota_iterator operator++(int) {
        auto const result = *this;
        ++*this;
        return result;
    }
    
    __utl_interface_export constexpr __iota_iterator& operator--() {
        --__i;
        return *this;
    }
    __utl_interface_export constexpr __iota_iterator operator--(int) {
        auto const result = *this;
        --*this;
        return result;
    }
    
    __utl_interface_export constexpr value_type operator*() const { return __i; }
    
    __utl_interface_export constexpr value_type operator[](difference_type index) const { return *(*this + index); }
    
    __utl_interface_export constexpr std::strong_ordering operator<=>(__iota_iterator const& rhs) const = default;
    
private:
    value_type __i;
};

template <std::integral T>
class iota<T> {
public:
    using value_type = T;
    using size_type = std::conditional_t<std::is_signed_v<T>, std::ptrdiff_t, std::size_t>;
    using iterator = __iota_iterator<T>;
    using const_iterator = iterator;
    
public:
    __utl_interface_export
    constexpr iota(value_type last): __first(0), __last(last) {}
    
    __utl_interface_export
    constexpr iota(value_type first, value_type last): __first(first), __last(last) {}
    
    __utl_interface_export
    constexpr iterator begin() const {
        return iterator(__first);
    }
    __utl_interface_export
    constexpr iterator end() const {
        return iterator(__last);
    }
    
    __utl_interface_export
    constexpr size_type size() const { return __last - __first; }
    
    value_type __first, __last;
};

template <std::integral T>
iota(T) -> iota<T>;

template <std::integral T, std::integral U>
iota(T, U) -> iota<std::common_type_t<T, U>>;

/// MARK: enumerate enum

template <typename E, typename Integer>
struct __enum_iterator {
    using difference_type   = std::ptrdiff_t;
    using value_type        = E;
    using pointer           = void;
    using reference         = void;
    using iterator_category = std::random_access_iterator_tag;
    using integer           = Integer;
    
    friend constexpr __enum_iterator operator+(__enum_iterator itr, std::ptrdiff_t offset) {
        return __enum_iterator{ static_cast<std::make_signed_t<integer>>(itr.__value) + offset };
    }
    
    friend constexpr __enum_iterator operator+(std::ptrdiff_t offset, __enum_iterator itr) {
        return itr + offset;
    }
    
    friend constexpr __enum_iterator operator-(__enum_iterator itr, std::ptrdiff_t offset) {
        return __enum_iterator{ static_cast<std::make_signed_t<integer>>(itr.__value) - offset };
    }
    
    friend constexpr difference_type operator-(__enum_iterator lhs, __enum_iterator rhs) {
        return static_cast<std::make_signed_t<integer>>(lhs.__value) - static_cast<std::make_signed_t<integer>>(rhs.__value);
    }
    
    constexpr __enum_iterator& operator+=(std::ptrdiff_t offset) {
        __value += offset;
        return *this;
    }
    
    constexpr __enum_iterator& operator-=(std::ptrdiff_t offset) {
        __value -= offset;
        return *this;
    }
    
    constexpr __enum_iterator& operator++() {
        ++__value;
        return *this;
    }
    
    constexpr __enum_iterator& operator--() {
        --__value;
        return *this;
    }
    
    constexpr __enum_iterator operator++(int) {
        auto const result = *this;
        ++__value;
        return result;
    }
    
    constexpr __enum_iterator operator--(int) {
        auto const result = *this;
        --__value;
        return result;
    }
    
    constexpr E operator[](std::ptrdiff_t index) const {
        return *(*this + index);
    }
    
    constexpr std::strong_ordering operator<=>(__enum_iterator const&) const = default;
    
    constexpr E operator*() const { return static_cast<E>(__value); }
    
    integer __value;
};

/// \brief Enumerate all values between \p first and \p last in the enum \p E
/// \warning All numeric values between \p first and \p last will be traversed when iterating over the returned range, even if they are not declared in the \p enum.
template <typename E> requires(std::is_enum_v<E>)
[[nodiscard]] constexpr auto enumerate(std::underlying_type_t<E> first, std::underlying_type_t<E> last) {
    class enum_range {
    public:
        using integer = std::underlying_type_t<E>;
        using iterator = __enum_iterator<E, integer>;
        
        constexpr iterator begin() const { return iterator{ _first }; }
        constexpr iterator end() const { return iterator{ _last }; }
        
        integer _first, _last;
    };
    return enum_range{ first, last };
}

/// \brief Enumerate all values between \p 0 and \p last in the enum \p E
/// \warning All numeric values between \p 0 and \p last will be traversed when iterating over the returned range, even if they are not declared in the \p enum.
template <typename E> requires(std::is_enum_v<E>)
[[nodiscard]] constexpr auto enumerate(std::underlying_type_t<E> last = to_underlying(E::_count)) {
    return enumerate<E>(0, last);
}

}

#endif // UTL_RANGES_HPP
