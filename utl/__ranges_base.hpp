#ifndef UTL_RANGES_BASE_HPP
#define UTL_RANGES_BASE_HPP

#include "__base.hpp"
#include "concepts.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

/// MARK: distance

auto __utl_distance(auto first, auto last, std::input_iterator_tag) {
    typename std::iterator_traits<decltype(first)>::difference_type result = 0;
    while (first != last) {
        ++first;
        ++result;
    }
    return result;
}

auto __utl_distance(auto first, auto last, std::random_access_iterator_tag) {
    return last - first;
}

/// \brief Distance between two iterators.
/// \details Same as \p std::distance except that it allows \p first and \p last to have different types.
template <iterator Itr, sentinel_for<Itr> S>
typename std::iterator_traits<Itr>::difference_type distance(Itr first, S last) {
    return __utl_distance(first, last,
                          typename std::iterator_traits<Itr>::iterator_category());
}

/// MARK: iterator_type_t etc.

template <typename Range>
using iterator_type_t = decltype(std::declval<Range>().begin());
template <typename Range>
using const_iterator_type_t = decltype(std::declval<std::add_const_t<Range>>().begin());
template <typename Range>
using sentinel_type_t = decltype(std::declval<Range>().end());
template <typename Range>
using const_sentinel_type_t = decltype(std::declval<std::add_const_t<Range>>().end());

/// MARK: __wrap_iterator

/// \brief CRTP wrapper for iterators
template <typename Itr, typename Base = void>
class __wrap_iterator {
public:
    using __itr_traits = std::iterator_traits<Itr>;
    using __base = std::conditional_t<std::is_same_v<Base, void>, __wrap_iterator, Base>;
    
    using size_type         = std::size_t;
    using difference_type   = typename __itr_traits::difference_type;
    using value_type        = typename __itr_traits::value_type;
    using pointer           = typename __itr_traits::pointer;
    using reference         = typename __itr_traits::reference;
    using iterator_category = typename __itr_traits::iterator_category;
    
    __wrap_iterator() = default;
    constexpr __wrap_iterator(Itr itr): __itr(itr) {}
    
    template <std::convertible_to<Itr> Jtr>
    constexpr __wrap_iterator(Jtr jtr): __itr(jtr) {}
    
    template <std::convertible_to<Itr> Jtr>
    constexpr __wrap_iterator(__wrap_iterator<Jtr> rhs): __itr(rhs.__itr) {}
    
    friend constexpr __base operator+(std::same_as<__base> auto base, difference_type offset)
    requires random_access_iterator<Itr>
    {
        base.__itr += offset;
        return base;
    }
    
    friend constexpr __base operator+(difference_type offset, std::same_as<__base> auto base)
    requires random_access_iterator<Itr>
    {
        return base + offset;
    }
    
    friend constexpr __base operator-(std::same_as<__base> auto base, difference_type offset)
    requires random_access_iterator<Itr>
    {
        base.__itr -= offset;
        return base;
    }
    
    template <typename Jtr>
    constexpr difference_type operator-(__wrap_iterator<Jtr> const& rhs) const
        requires random_access_iterator<Itr>
    {
        return __itr - rhs.__itr;
    }
    
    constexpr difference_type operator-(__base const& rhs) const
        requires random_access_iterator<Itr>
    {
        return __itr - rhs.__itr;
    }
    
    
    constexpr __base& operator+=(difference_type offset) requires random_access_iterator<Itr> {
        return __as_base() = __as_base() + offset;
    }
    
    constexpr __base& operator-=(difference_type offset) requires random_access_iterator<Itr> {
        return __as_base() = __as_base() - offset;
    }
    
    constexpr __base& operator++() {
        ++__itr;
        return __as_base();
    }
    
    constexpr __base operator++(int) {
        auto const result = __as_base();
        ++__as_base();
        return result;
    }
    
    constexpr __base& operator--() requires bidirectional_iterator<Itr> {
        --__itr;
        return __as_base();
    }
    
    constexpr __base operator--(int) requires bidirectional_iterator<Itr> {
        auto const result = static_cast<__base&>(*this);
        --__as_base();
        return result;
    }
    
    constexpr decltype(auto) operator[](difference_type index) const requires random_access_iterator<Itr> {
        return *(__as_base() + index);
    }
    
    constexpr decltype(auto) operator*() const { return *__itr; }
    
    friend constexpr bool operator==(__base const& lhs, __base const& rhs) requires std::equality_comparable<Itr> {
        return lhs.__itr == rhs.__itr;
    }
    
    friend constexpr auto operator<=>(__base const& lhs, __base const& rhs) requires std::totally_ordered<Itr> {
        return lhs <=> rhs.__itr;
    }
    
    friend constexpr bool operator==(__base const& lhs, Itr const& itr) requires std::equality_comparable<Itr> {
        return lhs.__itr == itr;
    }
    
    friend constexpr std::strong_ordering operator<=>(__base const& lhs, Itr const& itr) requires std::totally_ordered<Itr> {
        if (lhs.__itr == itr) {
            return std::strong_ordering::equal;
        }
        else if (lhs.__itr < itr) {
            return std::strong_ordering::less;
        }
        else {
            __utl_assert(lhs.__itr > itr);
            return std::strong_ordering::greater;
        }
    }
    
    constexpr Itr underlying_iterator() const { return __itr; }
    
    __base& __as_base() { return static_cast<__base&>(*this); }
    __base const& __as_base() const { return static_cast<__base const&>(*this); }
    
    Itr __itr;
};

}

#endif // UTL_RANGES_BASE_HPP
