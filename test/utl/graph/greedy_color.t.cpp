#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <utl/__graph/chordal.hpp>
#include <utl/__graph/greedy_color.hpp>
#include <utl/vector.hpp>

#include "utl/graph/Vertex.hpp"

TEST_CASE("Greedy color - 1", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 }, { 1 }, { 2 }, { 3 }, { 4 },
    };
    vertices[0].successors = { 1, 3, 4 };
    vertices[1].successors = { 0, 2, 4 };
    vertices[2].successors = { 1, 4 };
    vertices[3].successors = { 0, 4 };
    vertices[4].successors = { 0, 1, 2, 3 };
    
    //  0 --- 1 --- 2
    //  |\    |    /
    //  | \   |   /
    //  |  \  |  /
    //  |   \ | /
    //  |    \|/
    //  3 --- 4
    
    utl::small_vector<std::uint16_t> indices(vertices.size());
    for (size_t index = 0; auto& i : indices) {
        i = static_cast<std::uint16_t>(index++);
    }
    auto neighbours = [&](size_t index) -> auto& { return vertices[index].successors; };
    utl::small_vector<std::uint16_t> lexOrdering;
    lexOrdering.reserve(vertices.size());
    utl::find_lex_ordering(indices.begin(),
                           indices.end(),
                           neighbours,
                           std::back_inserter(lexOrdering));
    bool const isChordal = utl::is_chordal(lexOrdering.begin(), lexOrdering.end(), neighbours);
    REQUIRE(isChordal);
    
    utl::vector<uint32_t> colors(vertices.size());
    utl::greedy_color(lexOrdering.begin(), lexOrdering.end(), neighbours, [&](size_t index, uint32_t color) {
        colors[index] = color;
    });
    for (size_t i = 0; i < vertices.size(); ++i) {
        auto c = colors[i];
        for (auto n: neighbours(i)) {
            CHECK(c != colors[n]);
        }
    }
}
 
