#ifndef UTL_GRAPH_TOPSORT_HPP
#define UTL_GRAPH_TOPSORT_HPP

#include <iterator>

#include <utl/__base.hpp>
#include <utl/hashset.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

/// \brief   Topologically sorts a directed acyclic graph.
///
/// \details Time complexity: `O(n+m)`
/// Space complexity: `O(n)`
/// where `n` is the number of vertices and `m` is the number of edges in the graph.
///
/// \param   begin Iterator to the beginning of a range vertices.
/// \param   end End of range.
/// \param   edges Invocable retrieving a range of vertices from a vertex representing its edges.
///
/// \warning Behaviour is undefined if the graph has cycles.
template <std::input_iterator Itr, std::sentinel_for<Itr> S, typename Vertex = std::iter_value_t<Itr>, typename E> requires std::output_iterator<Itr, Vertex>
void topsort(Itr begin, S end, E edges);

// Implementation
template <typename T, typename E>
struct __top_sort_context {
    void sort(auto begin, auto end) {
        for (; begin != end; ++begin) {
            T const node = *begin;
            if (visited.contains(node)) { continue; }
            impl(node);
        }
    }
    void impl(T node) {
        visited.insert(node);
        for (auto const n: std::invoke(edges, node)) {
            if (visited.contains(n)) { continue; }
            impl(n);
        }
        result.push_back(node);
    }
    utl::small_vector<T>& result;
    E edges;
    utl::hashset<T> visited;
};

std::size_t __fast_dist_or_zero(auto begin, auto end) requires requires { end - begin; } {
    return end - begin;
}

std::size_t __fast_dist_or_zero(auto, auto) {
    return 0;
}

template <std::input_iterator Itr, std::sentinel_for<Itr> S, typename Vertex, typename E> requires std::output_iterator<Itr, Vertex>
void topsort(Itr begin, S end, E edges) {
    utl::small_vector<Vertex> sorted;
    sorted.reserve(__fast_dist_or_zero(begin, end));
    __top_sort_context<Vertex, E> ctx{ sorted, edges };
    ctx.sort(begin, end);
    for (auto i = sorted.begin(); begin != end; ++begin, ++i) {
        *begin = *i;
    }
}

} // namespace utl

#endif // UTL_GRAPH_TOPSORT_HPP
