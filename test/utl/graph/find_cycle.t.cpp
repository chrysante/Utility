#include <numeric>
#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <utl/__graph/find_cycle.hpp>
#include <utl/vector.hpp>

#include "utl/graph/Vertex.hpp"

TEST_CASE("find_cycle", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        utl_test::Vertex{ 0 }, utl_test::Vertex{ 1 }, utl_test::Vertex{ 2 },
        utl_test::Vertex{ 3 }, utl_test::Vertex{ 4 },
    };
    vertices[0].successors = { 1 };
    vertices[1].successors = { 2 };
    vertices[2].successors = { 0, 3 };
    vertices[3].successors = { 4 };
    vertices[4].successors = { 2 };

    //
    //   /-> 1 -\
    //  /        v
    // 0 <------- 2 <------- 4
    //             \        ^
    //              \-> 3 -/

    auto contains = [](auto&& range, auto&& value) {
        return std::find(std::begin(range), std::end(range), value) !=
               std::end(range);
    };

    utl::small_vector<std::uint16_t> indices(vertices.size());
    for (size_t index = 0; auto& i : indices) {
        i = static_cast<std::uint16_t>(index++);
    }

    auto edgeFn = [&](std::size_t index) -> auto const& {
        return vertices[index].successors;
    };

    SECTION("Default") {
        auto const cycle =
            utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.size() == 3);
        CHECK(contains(cycle, 0));
        CHECK(contains(cycle, 1));
        CHECK(contains(cycle, 2));
    }
    SECTION("Remove 2 -> 1 edge") {
        vertices[2].successors = { 3 };
        auto const cycle =
            utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.size() == 3);
        CHECK(contains(cycle, 2));
        CHECK(contains(cycle, 3));
        CHECK(contains(cycle, 4));
    }
    SECTION("Remove all edges from 2") {
        vertices[2].successors.clear();
        auto const cycle =
            utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.empty());
    }
}
