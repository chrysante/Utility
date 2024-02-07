#ifndef UTL_GRAPH_SCC_HPP
#define UTL_GRAPH_SCC_HPP

#include <iterator>

#include <utl/__base.hpp>
#include <utl/hashset.hpp>
#include <utl/hashtable.hpp>
#include <utl/stack.hpp>
#include <utl/vector.hpp>

_UTL_SYSTEM_HEADER_

namespace utl {

/// \brief   Compute strongly connected components of the graph `([vertex_begin,
/// vertex_end), successors)`
///
/// \details Time complexity: `O(n+m)`
/// Space complexity: `O(n)`
/// where `n` is the number of vertices and `m` is the number of edges in the
/// graph.
///
/// \param   vertex_begin Iterator to the beginning of a range vertices.
/// \param   vvertex_end End of range.
/// \param   successors Invocable retrieving a range of vertices from a vertex
///          representing its successors.
/// \param   begin_scc Invocable to call before emitting an SCC.
/// \param   emit_vertex Invocable to call when emitting a vertex into the
///          current SCC. Must store vertex into the SCC created by the last
///          call to \p begin_scc
///
template <std::input_iterator Itr, std::sentinel_for<Itr> S,
          typename Vertex = std::iter_value_t<Itr>, std::invocable<Vertex> E,
          std::invocable BeginSccFn, std::invocable<Vertex> EmitVertexFn>
void compute_sccs(Itr vertex_begin, S vertex_end, E successors,
                  BeginSccFn begin_scc, EmitVertexFn emit_vertex);

/// Algorithm from here:
/// https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

template <typename Itr, typename S, typename Vertex, typename E, typename F1,
          typename F2>
struct __tscca_context {
    struct vertex_data_t {
        uint32_t index : 31 = 0;
        bool defined : 1 = false;
        uint32_t lowlink : 31 = 0;
        bool on_stack : 1 = false;
    };

    using vertex_t = Vertex;

    __tscca_context(Itr begin, S end, E successors, F1 begin_scc,
                    F2 emit_vertex):
        begin(begin),
        end(end),
        successors(successors),
        begin_scc(begin_scc),
        emit_vertex(emit_vertex) {}

    void compute() {
        for (auto itr = begin; itr != end; ++itr) {
            vertex_data[*itr];
        }
        for (auto itr = begin; itr != end; ++itr) {
            if (!vertex_data[*itr].defined) {
                strong_connect(*itr);
            }
        }
    }

    void strong_connect(auto v) {
        auto& v_data = vertex_data[v];
        /// Set the depth index for `v` to the smallest unused index
        v_data.index = index;
        v_data.defined = true;
        v_data.lowlink = index;
        ++index;
        stack.push(v);
        v_data.on_stack = true;
        for (auto w : successors(v)) {
            auto& w_data = vertex_data[w];
            if (!w_data.defined) {
                /// Successor `w` has not yet been visited; recurse on it.
                strong_connect(w);
                v_data.lowlink = std::min(v_data.lowlink, w_data.lowlink);
            }
            else if (w_data.on_stack) {
                /// Successor `w` is in `stack` and hence in the current
                /// SCC. If `w` is not on stack, then `(v, w)` is an edge
                /// pointing to an SCC already found and must be ignored.
                /// Note: The next line may look odd - but is correct. It
                /// says `w_data.index`, not `w_data.lowlink`; that is
                /// deliberate and from the original paper.
                v_data.lowlink = std::min(v_data.lowlink, w_data.index);
            }
        }
        /// If `v` is a root node, pop the stack and generate an SCC.
        if (v_data.lowlink != v_data.index) {
            return;
        }
        std::invoke(begin_scc);
        while (true) {
            auto w = stack.pop();
            auto& w_data = vertex_data[w];
            w_data.on_stack = false;
            std::invoke(emit_vertex, w);
            if (w == v) {
                break;
            }
        }
    }

    Itr begin;
    S end;
    E successors;
    F1 begin_scc;
    F2 emit_vertex;
    utl::stack<vertex_t> stack;
    size_t index = 0;
    utl::hashmap<vertex_t, vertex_data_t> vertex_data;
};

} // namespace utl

template <std::input_iterator Itr, std::sentinel_for<Itr> S, typename Vertex,
          std::invocable<Vertex> E, std::invocable BeginSccFn,
          std::invocable<Vertex> EmitVertexFn>
void utl::compute_sccs(Itr vertex_begin, S vertex_end, E successors,
                       BeginSccFn begin_scc, EmitVertexFn emit_vertex) {
    __tscca_context<Itr, S, Vertex, E, BeginSccFn, EmitVertexFn>
        ctx(vertex_begin, vertex_end, successors, begin_scc, emit_vertex);
    ctx.compute();
}

#endif // UTL_GRAPH_SCC_HPP
