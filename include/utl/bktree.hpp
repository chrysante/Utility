#ifndef UTL_BKTREE_HPP_
#define UTL_BKTREE_HPP_

#include <algorithm>
#include <numeric>
#include <string>
#include <string_view>

#include "__debug.hpp"
#include "lazy.hpp"
#include "vector.hpp"

namespace utl {

/// https://en.wikipedia.org/wiki/Levenshtein_distance
inline size_t levenshtein_distance(std::string_view s1, std::string_view s2) {
    size_t numRows = s1.size() + 1;
    size_t numColumns = s2.size() + 1;
    if (numRows == 1)
        return s2.size();
    if (numColumns == 1)
        return s1.size();
    size_t* prevRow = (size_t*)alloca(numColumns * sizeof(size_t));
    size_t* currRow = (size_t*)alloca(numColumns * sizeof(size_t));
    std::iota(prevRow, prevRow + numColumns, size_t{});
    for (size_t i = 1; i < numRows; ++i) {
        currRow[0] = i;
        for (size_t j = 1; j < numColumns; ++j) {
            size_t cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
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

} // namespace internal

/// Default implementation for the traits customization point of `bktree`
template <typename T>
struct bktree_traits {
    /// The owning string type on which elements are keyed
    using string_type = std::string;

    /// The string-view type, used for lookup
    using string_view_type = std::string_view;

    /// Called on the value when inserting an existing key into the map
    static void update(T&, T&&) {}

    /// The distance function used by the map
    static size_t distance(std::string_view a, std::string_view b) {
        return levenshtein_distance(a, b);
    }
};

template <typename T, typename Traits = bktree_traits<T>>
class bktree: private Traits {
    struct _key {};

public:
    using string_type = typename Traits::string_type;
    using string_view_type = typename Traits::string_view_type;
    using value_type = T;
    using traits_type = Traits;

    class node {
    public:
        template <typename S, typename V>
        node(_key, S&& name, V&& value):
            _name(std::forward<S>(name)), _value(std::forward<V>(value)) {}

        string_type const& name() const { return _name; }

        value_type const& value() const { return _value; }

    private:
        friend class bktree;

        string_type _name;
        value_type _value;
    };

    bktree() = default;

    explicit bktree(traits_type traits): traits_type(std::move(traits)) {}

    node const* insert(string_type name, value_type value = {}) {
        if (_nodes.empty()) {
            return &_nodes.emplace_back(_key{}, std::move(name),
                                        std::move(value));
        }
        auto* node = &_nodes.front();
        while (true) {
            size_t dist = Traits::distance(name, node->name());
            if (dist == 0) {
                Traits::update(node->_value, std::move(value));
                return node;
            }
            auto [itr, success] =
                internal::map_insert(node->children, dist, _nodes.size());
            if (success) {
                return &_nodes.emplace_back(_key{}, std::move(name),
                                            std::move(value));
            }
            node = &_nodes[itr->second];
        }
    }

    template <typename OutItr>
    void lookup(string_view_type query, size_t threshold, OutItr outItr) const {
        if (_nodes.empty()) {
            return;
        }
        auto dfs = [&](auto& dfs, node_impl const* n) -> void {
            size_t dist = Traits::distance(n->name(), query);
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

    small_vector<node const*> lookup(string_view_type query,
                                     size_t threshold) const {
        small_vector<node const*> result;
        lookup(query, threshold, std::back_inserter(result));
        return result;
    }

private:
    struct node_impl: node {
        using node::node;
        utl::small_vector<std::pair<std::uint32_t, std::uint32_t>, 3> children;
    };

    utl::vector<node_impl> _nodes;
};

} // namespace utl

#endif // UTL_BKTREE_HPP_
