#ifndef UTL_GRAPH_GREEDY_COLOR
#define UTL_GRAPH_GREEDY_COLOR

#include <iterator>
#include <optional>

#include <utl/__base.hpp>
#include <utl/hashset.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

inline std::uint32_t __first_avail(utl::hashset<uint32_t> const& used) {
    for (std::uint32_t i = 0; ; ++i) {
        if (!used.contains(i)) {
            return i;
        }
    }
}

/// Greedily color the graph `([begin, end), neighbours)`
/// Colors are represented by `std::uint32_t`
///
/// \param begin Begin of a range of vertices.
///
/// \param end End of the range of vertices.
///
/// \param neighbours Invocable returning the neighours a vertex `v` as a range of vertices.
///
/// \param assign Invocable taking a vertex and a color. Can be used to assign the color to the vertex.
///
/// \Returns Number of colors used.
template <
    std::input_iterator Itr,
    std::sentinel_for<Itr> S,
    typename Vertex = std::iter_value_t<Itr>,
    std::invocable<Vertex> Neighbours,
    std::invocable<Vertex, size_t> Assign>
size_t greedy_color(Itr begin, S end, Neighbours neighbours, Assign assign) {
    utl::hashmap<Vertex, uint32_t> colors;
    std::int32_t max_col = -1;
    for (auto i = begin; i != end; ++i) {
        auto n = *i;
        utl::hashset<std::uint32_t> used;
        for (auto m: std::invoke(neighbours, n)) {
            auto itr = colors.find(m);
            if (itr != colors.end()) {
                used.insert(itr->second);
            }
        }
        std::uint32_t col = __first_avail(used);
        max_col = std::max(max_col, static_cast<std::int32_t>(col));
        colors.insert({ n, col });
        std::invoke(assign, n, col);
    }
    return static_cast<std::size_t>(max_col + 1);
}

} // namespace utl

#endif // UTL_GRAPH_GREEDY_COLOR
