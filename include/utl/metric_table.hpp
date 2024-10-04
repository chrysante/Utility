#ifndef UTL_METRICTABLE_HPP_
#define UTL_METRICTABLE_HPP_

#include <algorithm>
#include <initializer_list>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>

#include "vector.hpp"

namespace utl {

namespace internal {

template <typename R, typename ValueType>
inline constexpr bool IsArray =
    std::same_as<std::remove_cvref_t<std::ranges::range_value_t<R>>,
                 ValueType> &&
    std::is_array_v<std::remove_cvref_t<R>>;
}

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
        size_t* prevRow = (size_t*)alloca(numColumns * sizeof(size_t));
        size_t* currRow = (size_t*)alloca(numColumns * sizeof(size_t));
        std::iota(prevRow, prevRow + numColumns, size_t{});
        auto itr = std::ranges::begin(r1);
        for (size_t i = 1; i < numRows; ++i, ++itr) {
            currRow[0] = i;
            auto jtr = std::ranges::begin(r2);
            for (size_t j = 1; j < numColumns; ++j, ++jtr) {
                size_t cost = *itr == *jtr ? 0 : 1;
                currRow[j] = std::min({
                    currRow[j - 1] + 1,   // Insertion
                    prevRow[j] + 1,       // Deletion
                    prevRow[j - 1] + cost // Substitution
                });
            }
            std::swap(prevRow, currRow);
        }
        return prevRow[numColumns - 1];
    }
}

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

struct Empty {};

template <typename, typename, typename>
struct bktree;

template <typename K, typename V>
struct bktree_node_pair {
    template <typename K_, typename V_>
    bktree_node_pair(K_&& key, V_&& value):
        _key(std::forward<K_>(key)), _value(std::forward<V_>(value)) {}

    K const& key() const { return _key; }

    V const& value() const { return _value; }

private:
    template <typename, typename, typename>
    friend struct bktree;

    K _key;
    V _value;
};

template <typename K>
struct bktree_node_pair<K, Empty> {
    template <typename K_>
    bktree_node_pair(K_&& key, Empty): _key(std::forward<K_>(key)) {}

    K const& key() const { return _key; }

private:
    template <typename, typename, typename>
    friend struct bktree;

    K _key;
};

template <typename K, typename V, typename Traits>
struct bktree: Traits {
    static constexpr bool IsSet = std::is_same_v<V, Empty>;
    static constexpr bool IsMap = !IsSet;

    using node = bktree_node_pair<K, V>;
    using ValueType = std::conditional_t<IsMap, node, K>;

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

    struct node_impl: node {
        using node::node;
        utl::small_vector<std::pair<std::uint32_t, std::uint32_t>, 3> children;
    };

    template <typename K_, typename V_>
    node const* insert_impl(K_&& key, V_&& value) {
        if (_nodes.empty()) {
            return &_nodes.emplace_back(std::forward<K_>(key),
                                        std::forward<V_>(value));
        }
        auto* node = &_nodes.front();
        while (true) {
            size_t dist = Traits::distance(key, node->key());
            if (dist == 0) {
                if constexpr (IsMap) {
                    Traits::update(node->_value, std::forward<V_>(value));
                }
                return node;
            }
            auto [itr, success] =
                internal::map_insert(node->children, dist, _nodes.size());
            if (success) {
                return &_nodes.emplace_back(std::forward<K_>(key),
                                            std::forward<V_>(value));
            }
            node = &_nodes[itr->second];
        }
    }

    template <std::convertible_to<ValueType> VT>
    node const* insert_impl(VT&& value) {
        if constexpr (IsSet) {
            return insert_impl(std::forward<VT>(value), Empty{});
        }
        else {
            return insert_impl(std::forward<VT>(value).key(),
                               std::forward<VT>(value).value());
        }
    }

    template <lookup_compatible_with<K, Traits> K_, typename OutItr>
    void lookup(K_&& key, std::size_t threshold, OutItr outItr) const {
        if (_nodes.empty()) {
            return;
        }
        auto dfs = [&](auto& dfs, node_impl const* n) -> void {
            size_t dist = Traits::distance(n->key(), key);
            if (dist <= threshold) {
                *outItr++ = static_cast<node const*>(n);
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
                          [&](auto& p) { dfs(dfs, &_nodes[p.second]); });
        };
        dfs(dfs, &_nodes.front());
    }

    template <typename OutItr>
    void lookup(K const& key, std::size_t threshold, OutItr outItr) const {
        lookup<K const&, OutItr>(key, threshold, outItr);
    }

    template <internal::lookup_compatible_with<K, Traits> K_,
              typename ResultType = small_vector<node const*>>
    ResultType lookup(K_&& key, std::size_t threshold) const {
        ResultType result;
        lookup(std::forward<K_>(key), threshold, std::back_inserter(result));
        return result;
    }

    template <typename ResultType = small_vector<node const*>>
    ResultType lookup(K const& key, std::size_t threshold) const {
        return lookup<K const&, ResultType>(key, threshold);
    }

    size_t size() const { return _nodes.size(); }

    bool empty() const { return _nodes.empty(); }

    void clear() { _nodes.clear(); }

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
struct metric_map_traits: metric_set_traits<K> {
    /// Called on the value when inserting an existing key into the map
    static void update(V&, auto&&) {}
};

///
template <typename K, typename Traits = metric_set_traits<K>>
class metric_set: private internal::bktree<K, internal::Empty, Traits> {
    using impl = internal::bktree<K, internal::Empty, Traits>;

public:
    using key_type = K;
    using traits_type = Traits;

    using impl::clear;
    using impl::empty;
    using impl::impl;
    using impl::lookup;
    using impl::size;
    using typename impl::node;

    template <std::convertible_to<key_type> K_ = K>
    node const* insert(K_&& key) {
        return this->insert_impl(std::forward<K_>(key), internal::Empty{});
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

    using impl::clear;
    using impl::empty;
    using impl::impl;
    using impl::lookup;
    using impl::size;
    using typename impl::node;

    template <std::convertible_to<key_type> K_ = K,
              std::convertible_to<value_type> V_ = V>
    node const* insert(K_&& key, V_&& value) {
        return this->insert_impl(std::forward<K_>(key),
                                 std::forward<V_>(value));
    }
};

} // namespace utl

#endif // UTL_METRICTABLE_HPP_
