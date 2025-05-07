#ifndef UTL___WRAP_ITERATOR_HPP_
#define UTL___WRAP_ITERATOR_HPP_

#include <iterator>

#include <utl/__base.hpp>
#include <utl/__debug.hpp>
#include <utl/concepts.hpp>

namespace utl {

/// MARK: __wrap_iterator

template <typename T>
concept __utl_is_pointer = std::is_pointer_v<T>;

/// \brief CRTP wrapper for iterators
template <typename Itr, typename Base = void>
class __wrap_iterator {
public:
    using __itr_traits = std::iterator_traits<Itr>;
    using __base =
        std::conditional_t<std::is_same_v<Base, void>, __wrap_iterator, Base>;

    using size_type = std::size_t;
    using difference_type = typename __itr_traits::difference_type;
    using value_type = typename __itr_traits::value_type;
    using pointer = typename __itr_traits::pointer;
    using reference = typename __itr_traits::reference;
    using iterator_category = typename __itr_traits::iterator_category;
    using iterator_concept = typename __itr_traits::iterator_concept;

    __wrap_iterator() = default;
    constexpr __wrap_iterator(Itr itr): __itr(itr) {}

    template <std::convertible_to<Itr> Jtr>
    constexpr __wrap_iterator(Jtr jtr): __itr(jtr) {}

    template <std::convertible_to<Itr> Jtr>
    constexpr __wrap_iterator(__wrap_iterator<Jtr> rhs): __itr(rhs.__itr) {}

    friend constexpr __base operator+(std::same_as<__base> auto base,
                                      std::integral auto offset)
    requires std::random_access_iterator<Itr>
    {
        base.__itr += offset;
        return base;
    }

    friend constexpr __base operator+(std::integral auto offset,
                                      std::same_as<__base> auto base)
    requires std::random_access_iterator<Itr>
    {
        return base + offset;
    }

    friend constexpr __base operator-(std::same_as<__base> auto base,
                                      difference_type offset)
    requires std::random_access_iterator<Itr>
    {
        base.__itr -= offset;
        return base;
    }

    template <typename Jtr>
    constexpr difference_type operator-(__wrap_iterator<Jtr> const& rhs) const
    requires std::random_access_iterator<Itr>
    {
        return __itr - rhs.__itr;
    }

    constexpr difference_type operator-(__base const& rhs) const
    requires std::random_access_iterator<Itr>
    {
        return __itr - rhs.__itr;
    }

    constexpr __base& operator+=(difference_type offset)
    requires std::random_access_iterator<Itr>
    {
        return __as_base() = __as_base() + offset;
    }

    constexpr __base& operator-=(difference_type offset)
    requires std::random_access_iterator<Itr>
    {
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

    constexpr __base& operator--()
    requires std::bidirectional_iterator<Itr>
    {
        --__itr;
        return __as_base();
    }

    constexpr __base operator--(int)
    requires std::bidirectional_iterator<Itr>
    {
        auto const result = static_cast<__base&>(*this);
        --__as_base();
        return result;
    }

    constexpr decltype(auto) operator[](difference_type index) const
    requires std::random_access_iterator<Itr>
    {
        return *(__as_base() + index);
    }

    constexpr decltype(auto) operator*() const { return *__itr; }

    auto operator->() const
    requires __utl_is_pointer<Itr> || requires(Itr i) {
        {
            i.operator->()
        } -> __utl_is_pointer;
    }
    {
        return __operator_arrow_impl(*this);
    }

    auto operator->()
    requires __utl_is_pointer<Itr> || requires(Itr i) {
        {
            i.operator->()
        } -> __utl_is_pointer;
    }
    {
        return __operator_arrow_impl(*this);
    }

    template <typename Self>
    static constexpr auto __operator_arrow_impl(Self& self) {
        if constexpr (__utl_is_pointer<Itr>) {
            return self.__itr;
        }
        else {
            return self.__itr.operator->();
        }
    }

    friend constexpr bool operator==(__base const& lhs, __base const& rhs)
    requires std::equality_comparable<Itr>
    {
        return lhs.__itr == rhs.__itr;
    }

    friend constexpr auto operator<=>(__base const& lhs, __base const& rhs)
    requires std::totally_ordered<Itr>
    {
        return lhs <=> rhs.__itr;
    }

    friend constexpr bool operator==(__base const& lhs, Itr const& itr)
    requires std::equality_comparable<Itr>
    {
        return lhs.__itr == itr;
    }

    friend constexpr std::strong_ordering operator<=>(__base const& lhs,
                                                      Itr const& itr)
    requires std::totally_ordered<Itr>
    {
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
    __base const& __as_base() const {
        return static_cast<__base const&>(*this);
    }

    [[no_unique_address]] Itr __itr;
};

} // namespace utl

#endif // UTL___WRAP_ITERATOR_HPP_
