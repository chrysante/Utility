#ifndef UTL_METRIC_TABLE_HPP_
#define UTL_METRIC_TABLE_HPP_

#include <algorithm>
#include <alloca.h>
#include <cstdlib>
#include <initializer_list>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>

#include <utl/vector.hpp>

namespace utl {

namespace internal {

template <typename R, typename ValueType>
inline constexpr bool IsArray =
    std::same_as<std::remove_cvref_t<std::ranges::range_value_t<R>>,
                 ValueType> &&
    std::is_array_v<std::remove_cvref_t<R>>;
}

template <typename T>
constexpr size_t arraySize(size_t count) {
    return count * sizeof(T);
}

#define UTL_IMPL_STACK_ALLOC_THRESHOLD 2048 // 2 KB threshold

// Allocate memory on stack (with alloca) or heap (with malloc)
#define UTL_IMPL_STACK_ALLOC(type, count)                                      \
    ((sizeof(type) * (count)) <= UTL_IMPL_STACK_ALLOC_THRESHOLD ?              \
         (type*)alloca(sizeof(type) * (count)) :                               \
         (type*)std::malloc(sizeof(type) * (count)))

// Free memory only if it was allocated with malloc
#define UTL_IMPL_STACK_FREE(ptr, type, count)                                  \
    (((sizeof(type) * (count)) > UTL_IMPL_STACK_ALLOC_THRESHOLD) ?             \
         (std::free(ptr), (void)0) :                                           \
         (void)0)

/// Computes the Levenshtein distance between two ranges.
/// Useful for approximate string comparison.
/// https://en.wikipedia.org/wiki/Levenshtein_distance
template <std::ranges::sized_range R1, std::ranges::sized_range R2,
          typename Cmp = std::equal_to<>>
requires std::invocable<Cmp, std::ranges::range_value_t<R1>,
                        std::ranges::range_value_t<R2>>
size_t levenshtein_distance(R1&& r1, R2&& r2, Cmp cmp = {}) {
    if constexpr (internal::IsArray<R1, char>) {
        return levenshtein_distance(std::string_view{ r1 },
                                    std::forward<R2>(r2), cmp);
    }
    else if constexpr (internal::IsArray<R2, char>) {
        return levenshtein_distance(std::forward<R1>(r1),
                                    std::string_view{ r2 }, cmp);
    }
    else {
        size_t numRows = std::ranges::size(r1) + 1;
        size_t numColumns = std::ranges::size(r2) + 1;
        if (numRows == 1)
            return numColumns - 1;
        if (numColumns == 1)
            return numRows - 1;
        auto* prevRow = UTL_IMPL_STACK_ALLOC(std::uint32_t, 2 * numColumns);
        auto* currRow = prevRow + numColumns;
        std::iota(prevRow, prevRow + numColumns, size_t{});
        auto itr = std::ranges::begin(r1);
        for (std::uint32_t i = 1; i < numRows; ++i, ++itr) {
            currRow[0] = i;
            auto jtr = std::ranges::begin(r2);
            for (size_t j = 1; j < numColumns; ++j, ++jtr) {
                std::uint32_t cost = *itr == *jtr ? 0 : 1;
                currRow[j] = std::min({
                    currRow[j - 1] + 1,   // Insertion
                    prevRow[j] + 1,       // Deletion
                    prevRow[j - 1] + cost // Substitution
                });
            }
            std::swap(prevRow, currRow);
        }
        UTL_IMPL_STACK_FREE(prevRow, std::uint32_t, 2 * numColumns);
        return prevRow[numColumns - 1];
    }
}

#undef UTL_IMPL_STACK_ALLOC_THRESHOLD
#undef UTL_IMPL_STACK_ALLOC
#undef UTL_IMPL_STACK_FREE

template <typename CharT, std::ranges::sized_range R,
          typename Cmp = std::equal_to<>>
requires std::invocable<Cmp, CharT, std::ranges::range_value_t<R>>
size_t levenshtein_distance(CharT const* r1, R&& r2, Cmp cmp = {}) {
    return levenshtein_distance(std::basic_string_view{ r1 },
                                std::forward<R>(r2), cmp);
}

template <typename CharT, std::ranges::sized_range R,
          typename Cmp = std::equal_to<>>
requires std::invocable<Cmp, std::ranges::range_value_t<R>, CharT>
size_t levenshtein_distance(R&& r1, CharT const* r2, Cmp cmp = {}) {
    return levenshtein_distance(std::forward<R>(r1),
                                std::basic_string_view{ r2 }, cmp);
}

template <typename CharT, typename CharU, typename Cmp = std::equal_to<>>
requires std::invocable<Cmp, CharT, CharU>
size_t levenshtein_distance(CharT const* r1, CharU const* r2, Cmp cmp = {}) {
    return levenshtein_distance(std::basic_string_view{ r1 },
                                std::basic_string_view{ r2 }, cmp);
}

namespace internal {

/// Inserts the key-value pair `(key, value)` into \p map
/// This assumes that \p map is ordered on `Container::value_type::first` using
/// `cmp`
template <typename Key, typename Value, typename Container,
          typename Cmp = std::less<>>
std::pair<typename Container::iterator, bool>
map_insert(Container& map, Key&& key, Value&& value, Cmp cmp = {}) {
    auto pos = std::partition_point(map.begin(), map.end(),
                                    [&](auto& p) { return cmp(p.first, key); });
    if (pos != map.end() && !cmp(key, pos->first)) {
        return { pos, false };
    }
    return { map.insert(pos, { key, std::forward<Value>(value) }), true };
}

template <typename Key1, typename Key2, typename Traits>
concept lookup_compatible_with_impl = requires(Key1 a, Key2 b) {
    {
        Traits::distance(a, b)
    } -> std::convertible_to<std::size_t>;
};

template <typename Key1, typename Key2, typename Traits>
concept lookup_compatible_with =
    lookup_compatible_with_impl<Key1, Key2, Traits> &&
    lookup_compatible_with_impl<Key2, Key1, Traits>;

/// Empty tag type to specialize templates for sets
struct bktree_set_value_type {};

template <typename, typename, typename>
struct bktree;

/// `bktree` node for maps
template <typename K, typename V>
struct bktree_node {
    template <typename K_ = K, typename V_ = V>
    bktree_node(K_&& key, V_&& value):
        _key(std::forward<K_>(key)), _value(std::forward<V_>(value)) {}

    K const& key() const { return _key; }

    V& value() { return _value; }
    V const& value() const { return _value; }

private:
    template <typename, typename, typename>
    friend struct bktree;

    K _key;
    V _value;
};

/// `bktree` node for sets
template <typename K>
struct bktree_node<K, bktree_set_value_type> {
    template <typename K_ = K>
    bktree_node(K_&& key, bktree_set_value_type): _key(std::forward<K_>(key)) {}

    K const& key() const { return _key; }

private:
    template <typename, typename, typename>
    friend struct bktree;

    template <typename, typename, typename, typename>
    friend class bktree_iter;

    K _key;
};

/// Common behaviour of `bktree` iterator
template <typename Derived, typename Base>
struct bktree_iter_base {
    using _base = Base;

    Base _it;

    bktree_iter_base(Base it): _it(it) {}

    Derived& operator++() {
        ++_it;
        return static_cast<Derived&>(*this);
    }

    Derived operator++(int) {
        auto tmp = static_cast<Derived const&>(*this);
        ++*this;
        return tmp;
    }

    bool operator==(bktree_iter_base const&) const = default;
};

/// `bktree` iterator for maps
template <typename K, typename V, typename Node, typename Base>
class bktree_iter: bktree_iter_base<bktree_iter<K, V, Node, Base>, Base> {
    template <typename, typename, typename>
    friend struct bktree;

    using base_class = bktree_iter_base<bktree_iter<K, V, Node, Base>, Base>;

    using base_class::base_class;

public:
    Node& operator*() const { return *this->_it; }

    Node* operator->() const { return std::to_address(this->_it); }

    using base_class::operator++;
    bool operator==(bktree_iter const&) const = default;
};

/// `bktree` iterator for sets
template <typename K, typename V, typename Node, typename Base>
requires std::same_as<std::remove_const_t<V>, bktree_set_value_type>
class bktree_iter<K, V, Node, Base>:
    bktree_iter_base<bktree_iter<K, bktree_set_value_type, Node, Base>, Base> {
    template <typename, typename, typename>
    friend struct bktree;

    using base_class =
        bktree_iter_base<bktree_iter<K, bktree_set_value_type, Node, Base>,
                         Base>;
    using base_class::base_class;

public:
    K& operator*() const { return this->_it->_key; }

    K* operator->() const { return &this->_it->_key; }

    using base_class::operator++;
    bool operator==(bktree_iter const&) const = default;
};

/// Implementation of both `metric_map` and `metric_set`
template <typename K, typename V, typename Traits>
struct bktree: Traits {
    static constexpr bool IsSet = std::is_same_v<V, bktree_set_value_type>;
    static constexpr bool IsMap = !IsSet;

    using node = bktree_node<K, V>;
    using ValueType = std::conditional_t<IsMap, node, K>;

    struct node_impl: node {
        using node::node;
        utl::small_vector<std::pair<std::uint32_t, std::uint32_t>, 3> children;
    };

    using iterator =
        bktree_iter<K, V, node, typename utl::vector<node_impl>::iterator>;
    using const_iterator =
        bktree_iter<K const, V const, node const,
                    typename utl::vector<node_impl>::const_iterator>;
    using reverse_iterator =
        bktree_iter<K, V, node,
                    typename utl::vector<node_impl>::reverse_iterator>;
    using const_reverse_iterator =
        bktree_iter<K const, V const, node const,
                    typename utl::vector<node_impl>::const_reverse_iterator>;

    /// Wrapper around an iterator and a bool. `std::map`/`std::map` would use a
    /// `std::pair<iterator, bool>` for this, for user convenience we provide a
    /// class with a pretty interface
    class insert_result {
        friend class bktree;

        bool _success;
        bktree::iterator itr;

        insert_result(bool success, bktree::iterator itr):
            _success(success), itr(itr) {}

    public:
        /// \Returns true if the insertion was successful
        bool success() const { return _success; }

        /// \Returns `success()`
        explicit operator bool() const { return success(); }

        /// Dereferences the underlying iterator
        node* operator->() const { return itr.operator->(); }

        /// Dereferences the underlying iterator
        node& operator*() const { return *itr; }

        /// \Returns the underlying iterator
        bktree::iterator iterator() const { return itr; }
    };

    bktree() = default;

    explicit bktree(Traits traits): Traits(std::move(traits)) {}

    template <input_iterator_for<ValueType> I, std::sentinel_for<I> S>
    explicit bktree(I begin, S end) {
        if constexpr (std::random_access_iterator<I>) {
            _nodes.reserve(std::distance(begin, end));
        }
        for (; begin != end; ++begin) {
            insert_impl(*begin);
        }
    }

    bktree(std::initializer_list<ValueType> ilist):
        bktree(ilist.begin(), ilist.end()) {}

    template <bool Assign, typename K_, typename VFn>
    insert_result insert_impl(K_&& key, VFn&& vfn) {
        if (_nodes.empty()) {
            _nodes.emplace_back(std::forward<K_>(key),
                                std::invoke(std::forward<VFn>(vfn)));
            return { true, _nodes.end() - 1 };
        }
        auto node = _nodes.begin();
        while (true) {
            size_t dist = Traits::distance(key, node->key());
            if (dist == 0) {
                if constexpr (IsMap && Assign) {
                    node->_value = std::invoke(std::forward<VFn>(vfn));
                }
                return { false, node };
            }
            auto [itr, success] =
                internal::map_insert(node->children, dist, _nodes.size());
            if (success) {
                _nodes.emplace_back(std::forward<K_>(key),
                                    std::invoke(std::forward<VFn>(vfn)));
                return { true, _nodes.end() - 1 };
            }
            node = &_nodes[itr->second];
        }
    }

    template <std::convertible_to<ValueType> VT>
    insert_result insert_impl(VT&& value) {
        if constexpr (IsSet) {
            return insert_impl<false>(std::forward<VT>(value),
                                      [] { return bktree_set_value_type{}; });
        }
        else {
            return insert_impl<false>(std::forward<VT>(value).key(), [&] {
                return std::forward<VT>(value).value();
            });
        }
    }

    // Lookup
    // Axes: { outItr, vector } x { const, mutable } => 4 overloads

    template <typename Itr, typename Self, typename K_, typename OutItr>
    static void lookup_impl(Self&& This, K_&& key, std::size_t threshold,
                            OutItr outItr) {
        if (This._nodes.empty()) {
            return;
        }
        using ItrImpl = typename Itr::_base;
        auto dfs = [&](auto& dfs, ItrImpl n) -> void {
            size_t dist = Traits::distance(n->key(), key);
            if (dist <= threshold) {
                *outItr++ = Itr(n);
            }
            size_t min = (dist > threshold) ? (dist - threshold) : 0;
            size_t max = dist + threshold;
            auto begin =
                std::partition_point(n->children.begin(), n->children.end(),
                                     [&](auto& p) { return p.first < min; });
            auto end =
                std::partition_point(begin, n->children.end(),
                                     [&](auto& p) { return !(max < p.first); });
            std::for_each(begin, end,
                          [&](auto& p) { dfs(dfs, &This._nodes[p.second]); });
        };
        dfs(dfs, This._nodes.begin());
    }

    template <lookup_compatible_with<K, Traits> K_ = K const&,
              std::output_iterator<const_iterator> OutItr>
    void lookup(K_&& key, std::size_t threshold, OutItr outItr) const {
        lookup_impl<const_iterator>(*this, std::forward<K_>(key), threshold,
                                    outItr);
    }

    template <lookup_compatible_with<K, Traits> K_ = K const&,
              std::output_iterator<iterator> OutItr>
    void lookup(K_&& key, std::size_t threshold, OutItr outItr) {
        lookup_impl<iterator>(*this, std::forward<K_>(key), threshold, outItr);
    }

    template <typename ResultType = small_vector<const_iterator>,
              lookup_compatible_with<K, Traits> K_ = K const&>
    ResultType lookup(K_&& key, std::size_t threshold) const {
        ResultType result;
        lookup(std::forward<K_>(key), threshold, std::back_inserter(result));
        return result;
    }

    template <typename ResultType = small_vector<iterator>,
              lookup_compatible_with<K, Traits> K_ = K const&>
    ResultType lookup(K_&& key, std::size_t threshold) {
        ResultType result;
        lookup(std::forward<K_>(key), threshold, std::back_inserter(result));
        return result;
    }

    size_t size() const { return _nodes.size(); }

    bool empty() const { return _nodes.empty(); }

    void clear() { _nodes.clear(); }

    iterator begin() { return _nodes.begin(); }
    const_iterator begin() const { return _nodes.begin(); }
    const_iterator cbegin() const { return _nodes.cbegin(); }

    iterator end() { return _nodes.end(); }
    const_iterator end() const { return _nodes.end(); }
    const_iterator cend() const { return _nodes.cend(); }

    reverse_iterator rbegin() { return _nodes.rbegin(); }
    const_reverse_iterator rbegin() const { return _nodes.rbegin(); }
    const_reverse_iterator crbegin() const { return _nodes.crbegin(); }

    reverse_iterator rend() { return _nodes.rend(); }
    const_reverse_iterator rend() const { return _nodes.rend(); }
    const_reverse_iterator crend() const { return _nodes.crend(); }

    utl::vector<node_impl> _nodes;
};

} // namespace internal

/// Default implementation for the traits customization point of `metric_set`
template <typename K>
struct metric_set_traits {
    /// The distance function used by the map
    template <typename R1, typename R2>
    static size_t distance(R1&& a, R2&& b) {
        return utl::levenshtein_distance(std::forward<R1>(a),
                                         std::forward<R2>(b));
    }
};

/// Default implementation for the traits customization point of `metric_map`
template <typename K, typename V>
struct metric_map_traits: metric_set_traits<K> {};

///
template <typename K, typename Traits = metric_set_traits<K>>
class metric_set:
    private internal::bktree<K, internal::bktree_set_value_type, Traits> {
    using impl = internal::bktree<K, internal::bktree_set_value_type, Traits>;

public:
    using key_type = K;
    using value_type = K;
    using traits_type = Traits;

    using impl::begin;
    using impl::clear;
    using impl::crbegin;
    using impl::crend;
    using impl::empty;
    using impl::end;
    using impl::impl;
    using impl::lookup;
    using impl::rbegin;
    using impl::rend;
    using impl::size;
    using typename impl::const_iterator;
    using typename impl::const_reverse_iterator;
    using typename impl::insert_result;
    using typename impl::iterator;
    using typename impl::node;
    using typename impl::reverse_iterator;

    template <typename K_ = K const&>
    requires std::constructible_from<K, K_>
    insert_result insert(K_&& key) {
        return this->template insert_impl<false>(std::forward<K_>(key), [] {
            return internal::bktree_set_value_type{};
        });
    }
};

///
template <typename K, typename V, typename Traits = metric_map_traits<K, V>>
class metric_map: private internal::bktree<K, V, Traits> {
    using impl = internal::bktree<K, V, Traits>;

public:
    using key_type = K;
    using value_type = V;

    using traits_type = Traits;

    using impl::begin;
    using impl::cbegin;
    using impl::clear;
    using impl::crbegin;
    using impl::crend;
    using impl::empty;
    using impl::end;
    using impl::impl;
    using impl::lookup;
    using impl::rend;
    using impl::size;
    using typename impl::const_iterator;
    using typename impl::const_reverse_iterator;
    using typename impl::insert_result;
    using typename impl::iterator;
    using typename impl::node;
    using typename impl::reverse_iterator;

    template <typename K_ = K&&, std::convertible_to<value_type> V_ = V &&>
    requires std::constructible_from<K, K_>
    insert_result insert(K_&& key, V_&& value) {
        return this->template insert_impl<false>(std::forward<K_>(key),
                                                 [&]() -> decltype(auto) {
            return std::forward<V_>(value);
        });
    }

    template <typename K_ = K&&, std::invocable VFn>
    requires std::same_as<std::invoke_result_t<VFn&&>, V> &&
             std::constructible_from<K, K_>
    insert_result insert(K_&& key, VFn&& vfn) {
        return this->template insert_impl<false>(std::forward<K_>(key),
                                                 std::forward<VFn>(vfn));
    }

    template <typename K_ = K&&, std::convertible_to<value_type> V_ = V &&>
    requires std::constructible_from<K, K_>
    insert_result update(K_&& key, V_&& value) {
        return this->template insert_impl<true>(std::forward<K_>(key),
                                                [&]() -> decltype(auto) {
            return std::forward<V_>(value);
        });
    }

    template <typename K_ = K const&, std::invocable VFn>
    requires std::same_as<std::invoke_result_t<VFn&&>, V> &&
             std::constructible_from<K, K_>
    insert_result update(K_&& key, VFn&& vfn) {
        return this->template insert_impl<true>(std::forward<K_>(key),
                                                std::forward<VFn>(vfn));
    }

    template <typename K_ = K&&>
    requires std::constructible_from<K, K_>
    value_type& operator[](K_&& key) {
        return insert(std::forward<K_>(key), [] { return V(); })->value();
    }
};

} // namespace utl

#endif // UTL_METRIC_TABLE_HPP_
