#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <utl/__graph/chordal.hpp>
#include <utl/vector.hpp>

#include "utl/graph/Vertex.hpp"

TEST_CASE("Chordal graph - 1", "[graph]") {
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
    auto neighbours = [&](size_t index) -> auto& {
        return vertices[index].successors;
    };
    utl::small_vector<std::uint16_t> lexOrdering;
    lexOrdering.reserve(vertices.size());
    utl::find_lex_ordering(indices.begin(), indices.end(), neighbours,
                           std::back_inserter(lexOrdering));
    bool const isChordal =
        utl::is_chordal(lexOrdering.begin(), lexOrdering.end(), neighbours);
    CHECK(isChordal);
}

TEST_CASE("Chordal graph - 2", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 }, { 1 }, { 2 }, { 3 }, { 4 },
    };
    vertices[0].successors = { 1, 3, 4 };
    vertices[1].successors = { 0, 2 };
    vertices[2].successors = { 1, 4 };
    vertices[3].successors = { 0, 4 };
    vertices[4].successors = { 0, 2, 3 };

    //  0 --- 1 --- 2
    //  |\         /
    //  | \       /
    //  |  \     /
    //  |   \   /
    //  |    \ /
    //  3 --- 4

    utl::small_vector<std::uint16_t> indices(vertices.size());
    for (size_t index = 0; auto& i : indices) {
        i = static_cast<std::uint16_t>(index++);
    }
    auto neighbours = [&](size_t index) -> auto& {
        return vertices[index].successors;
    };
    utl::small_vector<std::uint16_t> lexOrdering;
    lexOrdering.reserve(vertices.size());
    utl::find_lex_ordering(indices.begin(), indices.end(), neighbours,
                           std::back_inserter(lexOrdering));

    bool const isChordal =
        utl::is_chordal(lexOrdering.begin(), lexOrdering.end(), neighbours);
    CHECK(!isChordal);
}

TEST_CASE("Chordal graph - 3", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {};
    utl::small_vector<std::uint16_t> indices(vertices.size());
    for (size_t index = 0; auto& i : indices) {
        i = static_cast<std::uint16_t>(index++);
    }
    auto neighbours = [&](size_t index) -> auto& {
        return vertices[index].successors;
    };
    utl::small_vector<std::uint16_t> lexOrdering;
    lexOrdering.reserve(vertices.size());
    utl::find_lex_ordering(indices.begin(), indices.end(), neighbours,
                           std::back_inserter(lexOrdering));

    bool const isChordal =
        utl::is_chordal(lexOrdering.begin(), lexOrdering.end(), neighbours);
    CHECK(isChordal);
    CHECK(lexOrdering.empty());
}

TEST_CASE("Chordal graph - 4", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 }, { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 6 }, { 7 },
    };
    vertices[0].successors = { 1, 2, 3, 4 };
    vertices[1].successors = { 0, 2, 3, 4 };
    vertices[2].successors = { 0, 1, 3, 4, 5, 6, 7 };
    vertices[3].successors = { 0, 1, 2, 4, 5, 6, 7 };
    vertices[4].successors = { 0, 1, 2, 3, 5, 6, 7 };
    vertices[5].successors = { 2, 3, 4 };
    vertices[6].successors = { 2, 3, 4, 7 };
    vertices[7].successors = { 2, 3, 4, 6 };

    utl::small_vector<std::uint16_t> indices(vertices.size());
    for (size_t index = 0; auto& i : indices) {
        i = static_cast<std::uint16_t>(index++);
    }
    auto neighbours = [&](size_t index) -> auto& {
        return vertices[index].successors;
    };
    utl::small_vector<std::uint16_t> lexOrdering;
    lexOrdering.reserve(vertices.size());
    utl::find_lex_ordering(indices.begin(), indices.end(), neighbours,
                           std::back_inserter(lexOrdering));
    bool const isChordal =
        utl::is_chordal(lexOrdering.begin(), lexOrdering.end(), neighbours);
    CHECK(isChordal);
}
