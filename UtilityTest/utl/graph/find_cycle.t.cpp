#include "Catch2.hpp"

#include <utl/__graph/find_cycle.hpp>
#include <utl/vector.hpp>
#include <utl/ranges.hpp>

#include "Vertex.hpp"

TEST_CASE("find_cycle", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 },
        { 1 },
        { 2 },
        { 3 },
        { 4 },
    };
    vertices[0].dependencies = { 1 };
    vertices[1].dependencies = { 2 };
    vertices[2].dependencies = { 0, 3 };
    vertices[3].dependencies = { 4 };
    vertices[4].dependencies = { 2 };
    
    //
    //   /-> 1 -\
    //  /        v
    // 0 <------- 2 <------- 4
    //             \        ^
    //              \-> 3 -/
    
    auto contains = [](auto&& range, auto&& value) {
        return std::find(std::begin(range), std::end(range), value) != std::end(range);
    };
    
    utl::small_vector<std::size_t> indices(utl::iota(vertices.size()));
    
    auto edgeFn = [&](std::size_t index) -> auto const& { return vertices[index].dependencies; };
    
    SECTION("Default") {
        auto const cycle = utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.size() == 3);
        CHECK(contains(cycle, 0));
        CHECK(contains(cycle, 1));
        CHECK(contains(cycle, 2));
    }
    SECTION("Remove 2 -> 1 edge") {
        vertices[2].dependencies = { 3 };
        auto const cycle = utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.size() == 3);
        CHECK(contains(cycle, 2));
        CHECK(contains(cycle, 3));
        CHECK(contains(cycle, 4));
    }
    SECTION("Remove all edges from 2") {
        vertices[2].dependencies.clear();
        auto const cycle = utl::find_cycle(indices.begin(), indices.end(), edgeFn);
        CHECK(cycle.empty());
    }
}

