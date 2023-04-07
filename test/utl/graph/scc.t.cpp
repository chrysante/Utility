#include <catch/catch2.hpp>

#include <ranges>

#include <utl/__graph/scc.hpp>
#include <utl/vector.hpp>

#include "Vertex.hpp"

namespace {

template <typename T>
struct Set {
    Set(std::initializer_list<T> l): elems(l) {}
    
    utl::small_vector<T> elems;
};

template <typename T>
bool operator==(Set<T> const& s, auto const& rng) {
    if (std::size(rng) != s.elems.size()) {
        return false;
    }
    for (auto&& x: rng) {
        for (auto&& y: s.elems) {
            if (x == y) {
                goto endLoop;
            }
        }
        return false;
    endLoop:
        continue;
    }
    return true;
}

} // namespace

static utl::vector<utl::small_vector<uint16_t>> computeSCCs(
    std::span<utl_test::Vertex const> vertices) {
    utl::small_vector<std::uint16_t> indices(std::views::iota(size_t(0),
                                                              vertices.size()));
    utl::vector<utl::small_vector<uint16_t>> sccs;
    utl::compute_sccs(indices.begin(),
                      indices.end(),
                      [&](std::size_t index) -> auto& {
                          return vertices[index].successors;
                      },
                      [&] { sccs.emplace_back(); },
                      [&](size_t index) { sccs.back().push_back(index); });
    return sccs;
}

TEST_CASE("scc - 1", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 },
        { 1 },
        { 2 },
        { 3 },
        { 4 },
        { 5 },
        { 6 },
        { 7 },
    };
    vertices[0].successors = { 1 };
    vertices[1].successors = { 2, 4 };
    vertices[2].successors = { 3 };
    vertices[3].successors = { 0 };
    vertices[4].successors = { 5 };
    vertices[5].successors = { 6 };
    vertices[6].successors = { 4, 7 };
    vertices[7].successors = {};
    //
    // 0 -> 1 -> 4  <- 6 -> 7
    // ^    |     \    ^
    // |    v      \   |
    // 3 <- 2       -> 5
    //
    auto sccs = computeSCCs(vertices);
    CHECK(sccs == Set{ Set{ 0, 1, 2, 3 }, Set{ 4, 5, 6 }, Set{ 7 } });
}

TEST_CASE("scc - 2", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 },
        { 1 },
        { 2 },
        { 3 },
    };
    vertices[0].successors = { 1 };
    vertices[1].successors = { 2 };
    vertices[2].successors = { 3 };
    vertices[3].successors = { 0 };
    //
    // 0 -> 1 -> 2 -> 3
    // ^              /
    //  \____________/
    //
    auto sccs = computeSCCs(vertices);
    CHECK(sccs == Set<Set<int>>{ Set{ 0, 1, 2, 3 } });
}

TEST_CASE("scc - 3", "[graph]") {
    utl::vector<utl_test::Vertex> vertices = {
        { 0 },
        { 1 },
        { 2 },
        { 3 },
    };
    vertices[0].successors = { 1 };
    vertices[1].successors = { 2 };
    vertices[2].successors = { 3 };
    vertices[3].successors = {};
    //
    // 0 -> 1 -> 2 -> 3
    //
    auto sccs = computeSCCs(vertices);
    CHECK(sccs == Set{ Set{ 0 }, Set{ 1 }, Set{ 2 }, Set{ 3 } });
}
