#include <catch/catch2.hpp>

#include <utl/__graph/topsort.hpp>
#include <utl/vector.hpp>
#include <utl/ranges.hpp>

#include "Vertex.hpp"

TEST_CASE("topsort", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 },
        { 1 },
        { 2 },
        { 3 },
        { 4 },
        { 5 },
    };
    vertices[0].dependencies = { 1, 2 };
    vertices[1].dependencies = { 2, 4, 5 };
    vertices[2].dependencies = { 4 };
    vertices[3].dependencies = { 2 };
    vertices[3].dependencies = { 2 };
    
    //
    // 0 ---> 1---\---> 5
    //  \     |    \
    //   \    v     \--\
    //    \-> 2 ------> 4
    //       /
    // 3 ---/
    
    utl::small_vector<std::uint16_t> indices(utl::iota(vertices.size()));
    utl::topsort(indices.begin(), indices.end(), [&](std::size_t index) { return vertices[index].dependencies; });
    /// For each index \p i all indices \p j coming afterwards in the sorted list must not be downstream of \p i
    for (std::size_t i = 0; i < indices.size(); ++i) {
        for (std::size_t j = i + 1; j < indices.size(); ++j) {
            std::size_t const start = indices[i];
            std::size_t const target = indices[j];
            CHECK(!findDownstream(vertices, start, target));
        }
    }
    /// For each pair of indices \p (i,j) \p j must be downstream of \p i only if \p j appears earlier in the sorted list.
    for (std::size_t i = 0; i < indices.size(); ++i) {
        for (std::size_t j = 0; j < indices.size(); ++j) {
            std::size_t const lhs = indices[i];
            std::size_t const rhs = indices[j];
            bool const rhsDownstream = findDownstream(vertices, lhs, rhs);
            if (rhsDownstream) {
                CHECK(j < i);
            }
        }
    }
}
 
