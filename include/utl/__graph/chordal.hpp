#ifndef UTL_GRAPH_CHORDAL_HPP
#define UTL_GRAPH_CHORDAL_HPP

#include <iterator>
#include <optional>

#include <utl/__base.hpp>
#include <utl/hashset.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

/// Finds a lexicographical ordering of the graph `([begin, end), neighbours)`
///
/// \param begin Begin of a range of vertices.
///
/// \param end End of the range of vertices.
///
/// \param neighbours Invocable returning the neighours a vertex `v` as a range
/// of vertices.
///
/// \param result Output iterator to which the lexicographical ordering is
/// written.
template <std::input_iterator Itr, std::sentinel_for<Itr> S,
          typename Vertex = std::iter_value_t<Itr>,
          std::invocable<Vertex> Neighbours, std::output_iterator<Vertex> Out>
void find_lex_ordering(Itr begin, S end, Neighbours neighbours, Out result);

/// Checks wether a graph `([begin, end), neighbours)` is chordal.
///
/// \param begin Beginning to a range of lexicographically sorted vertices.
///
/// \param end End of the range of lexicographically sorted vertices.
///
/// \param neighbours Invocable returning the neighours a vertex `v` as a range
/// of vertices.
///
/// \Returns `true` iff the graph is chordal.
template <std::input_iterator Itr, std::sentinel_for<Itr> S,
          typename Vertex = std::iter_value_t<Itr>,
          std::invocable<Vertex> Neighbours>
bool is_chordal(Itr begin, S end, Neighbours neighbours);

} // namespace utl

namespace utl {

template <typename Vertex, typename Neighbours, typename Out>
struct __lex_bfs_context {
    __lex_bfs_context(auto begin, auto end, Neighbours neighbours, Out outItr):
        sigma{ { 0, utl::hashset<Vertex>(begin, end) } },
        neighbours(neighbours),
        outItr(outItr) {}

    void run() {
        /// If the graph is empty we return early.
        if (sigma.front().second.empty()) {
            return;
        }
        while (!sigma.empty()) {
            auto& [firstID, firstSet] = sigma.front();
            Vertex v = pop(firstSet);
            if (firstSet.empty()) {
                sigma.erase(sigma.begin());
            }
            *outItr++ = v;
            utl::hashset<uint16_t> replaced;
            for (auto w : std::invoke(neighbours, v)) {
                // TODO: Replace this linear search by a constant time algorithm
                auto sItr =
                    std::find_if(sigma.begin(), sigma.end(),
                                 [&](auto& s) { return s.second.contains(w); });
                if (sItr == sigma.end()) {
                    continue;
                }
                auto tItr = sItr;
                if (!replaced.contains(sItr->first)) {
                    replaced.insert(sItr->first);
                    tItr = sigma.insert(sItr, { setID++, {} });
                    sItr = tItr + 1;
                }
                else {
                    --tItr;
                }
                tItr->second.insert(w);
                sItr->second.erase(w);
                if (sItr->second.empty()) {
                    sigma.erase(sItr);
                }
            }
        }
    }

    static Vertex pop(utl::hashset<Vertex>& set) {
        __utl_assert(!set.empty());
        auto itr = set.begin();
        auto result = *itr;
        set.erase(itr);
        return result;
    }

    utl::vector<std::pair<size_t, utl::hashset<Vertex>>> sigma;
    size_t setID = 1;
    Neighbours neighbours;
    Out outItr;
};

} // namespace utl

template <std::input_iterator Itr, std::sentinel_for<Itr> S, typename Vertex,
          std::invocable<Vertex> Neighbours, std::output_iterator<Vertex> Out>
void utl::find_lex_ordering(Itr begin, S end, Neighbours neighbours,
                            Out outItr) {
    __lex_bfs_context<Vertex, Neighbours, Out> ctx(begin, end, neighbours,
                                                   outItr);
    ctx.run();
}

namespace utl {

template <typename Itr, typename S, typename Vertex, typename Neighbours>
struct __is_chordal_context {
    bool run() {
        for (auto vItr = begin; vItr != end; ++vItr) {
            Vertex v = *vItr;
            auto&& neighboursOfV = std::invoke(neighbours, v);
            std::optional<Itr> wItr;
            for (auto j = vItr;;) {
                if (j == begin) {
                    break;
                }
                --j;
                if (std::find(neighboursOfV.begin(), neighboursOfV.end(), *j) !=
                    neighboursOfV.end())
                {
                    wItr = j;
                    break;
                }
            }
            if (!wItr) {
                continue;
            }
            auto SOPNofV = setOfPrevNeighbours(vItr);
            SOPNofV.erase(**wItr);
            auto SOPNofW = setOfPrevNeighbours(*wItr);
            if (!isSubset(SOPNofV, SOPNofW)) {
                return false;
            }
        }
        return true;
    }

    utl::hashset<Vertex> setOfPrevNeighbours(Itr itr) {
        utl::hashset<Vertex> result;
        auto&& neigh = std::invoke(neighbours, *itr);
        while (true) {
            if (itr == begin) {
                break;
            }
            --itr;
            if (std::find(neigh.begin(), neigh.end(), *itr) != neigh.end()) {
                result.insert(*itr);
            }
        }
        return result;
    }

    /// Checks wether \p a is a subset of \p b
    bool isSubset(utl::hashset<Vertex> const& a,
                  utl::hashset<Vertex> const& b) {
        for (auto const& x : a) {
            if (!b.contains(x)) {
                return false;
            }
        }
        return true;
    }

    Itr begin;
    S end;
    Neighbours neighbours;
};

} // namespace utl

template <std::input_iterator Itr, std::sentinel_for<Itr> S, typename Vertex,
          std::invocable<Vertex> Neighbours>
bool utl::is_chordal(Itr begin, S end, Neighbours neighbours) {
    __is_chordal_context<Itr, S, Vertex, Neighbours> ctx{ begin, end,
                                                          neighbours };
    return ctx.run();
}

#endif // UTL_GRAPH_CHORDAL_HPP
