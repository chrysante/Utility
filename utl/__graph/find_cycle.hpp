#ifndef UTL_FINDCYCLE_HPP
#define UTL_FINDCYCLE_HPP

#include <utl/__base.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

/// \brief   Finds a cycle in a directed graph.
///
/// \details VertexType must be equality comparable and the set of vertices must be unique, i.e. \code (v == u) <==> (&v == &u) \endcode for all vertices \p v and \p u in the graph.
/// \details Time complexity: \p O(n+m)
/// \details Space complexity: \p O(n)
/// \details where \p n is the number of vertices and \p m is the number of edges in the graph.
///
/// \param   begin Iterator to the beginning of a range vertices.
/// \param   end End of range.
/// \param   edges Invocable retrieving a range of vertices from a vertex representing its edges.
/// \returns The first encountered cycle in the graph as \p utl::small_vector</*VertexType*/>
template <input_iterator Itr, sentinel_for<Itr> S, typename E, std::equality_comparable VertexType = std::decay_t<decltype(*std::declval<Itr>())>>
small_vector<VertexType> find_cycle(Itr begin, S end, E edges);

bool __utl_cycle_contains(auto&& range, auto&& value) {
    return std::find(range.begin(), range.end(), value) != range.end();
}

template <typename T, typename E>
struct __search_cycle_context {
    void find(auto begin, auto end) {
        for (; begin != end; ++begin) {
            if (search(*begin)) {
                return;
            }
        }
    }
    bool search(auto&& node) {
        current_path.push_back(UTL_FORWARD(node));
        for (auto child: std::invoke(edges, current_path.back())) {
            if (__utl_cycle_contains(current_path, child) || search(child)) {
                return true;
            }
        }
        current_path.pop_back();
        return false;
    }
    utl::small_vector<T>& current_path;
    E edges;
};


template <input_iterator Itr, sentinel_for<Itr> S, typename E, std::equality_comparable Vertex>
small_vector<Vertex> find_cycle(Itr begin, S end, E edges) {
    utl::small_vector<Vertex> result;
    __search_cycle_context<Vertex, E> ctx{ result, edges };
    ctx.find(begin, end);
    if (result.empty()) { return result; }
    /// Trim vertices from the beginning which are not part of the cycle.
    size_t begin_index = 0;
    while (!__utl_cycle_contains(std::invoke(edges, result.back()), result[begin_index])) { ++begin_index; }
    result.erase(result.begin(), result.begin() + begin_index);
    return result;
}

}

#endif // UTL_FINDCYCLE_HPP
