#include <catch/catch2.hpp>

#include <utl/vector.hpp>

#include "VectorTest.hpp"

using namespace utl_test;

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-emplace", "[vector]") {
    X::reset();
    Vector v(Tag(1));
    v.emplace_back();
    REQUIRE(v.size() == 1);
    CHECK(v.capacity() >= 1);
    CHECK(v.front().alloc.tag == Tag(1));
    v.emplace_back();
    REQUIRE(v.size() == 2);
    CHECK(v.capacity() >= 2);
    CHECK(v[0].alloc.tag == Tag(1));
    CHECK(v[1].alloc.tag == Tag(1));
    CHECK(X::liveObjects() == 2);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-reserve", "[vector]") {
    X::reset();
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    auto const newCap = GENERATE(0, 5, 50);
    v.reserve(newCap);
    REQUIRE(v.size() == size);
    CHECK(X::liveObjects() == size);
    CHECK(v.capacity() >= newCap);
    CHECK(X::liveObjects() == size);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-resize", "[vector]") {
    X::reset();
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    CHECK(X::liveObjects() == size);
    auto const newSize = GENERATE(0, 5, 50);
    v.resize(newSize);
    CHECK(X::liveObjects() == newSize);
    REQUIRE(v.size() == newSize);
    CHECK(v.capacity() >= newSize);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-move-construct", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize = v.size();
    VectorB w        = std::move(v);
    CHECK(w.size() == vSize);
    CHECK(w.capacity() >= w.size());
    CHECK(X::liveObjects() >= count);
    v.clear();
    w.clear();
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-move-assign", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize      = v.size();
    auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
    VectorB w(wInitCount);
    CHECK(X::liveObjects() == count + wInitCount);
    w = std::move(v);
    CHECK(w.size() == vSize);
    CHECK(w.capacity() >= vSize);
    CHECK(X::liveObjects() >= count);
    v.clear();
    w.clear();
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-copy-construct", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    VectorB w = v;
    CHECK(w.size() == v.size());
    CHECK(X::liveObjects() == 2 * count);
    w.clear();
    CHECK(X::liveObjects() == count);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-copy-assign", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize      = v.size();
    auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
    VectorB w(wInitCount);
    CHECK(X::liveObjects() == count + wInitCount);
    w = v;
    CHECK(w.size() == vSize);
    CHECK(X::liveObjects() == 2 * count);
    w.clear();
    CHECK(X::liveObjects() == count);
}



VECTOR_TEST_CASE(X, TRX, "vector-at", "[vector]") {
    Vector v = { 0, 1, 2, 3 };
    CHECK(v.at(3) == 3);
    CHECK_THROWS_AS(v.at(4), std::out_of_range);
}

using MoveOnly = std::unique_ptr<X>;

static MoveOnly makeMoveOnly(X x) {
    return std::make_unique<X>(std::move(x));
}

VECTOR_PRODUCT_TEST_CASE(MoveOnly, "vector-move-only", "[vector]") {
    X::reset();
    VectorA v(Tag(1));
    v.push_back(MoveOnly());
    auto const count = GENERATE(0, 5, 200);
    for (int i = 1; i <= count; ++i) {
        v.push_back(makeMoveOnly(i));
    }
    CHECK(v[0] == nullptr);
    for (int i = 1; i <= count; ++i) {
        CHECK(*v[i] == X(i));
    }
    CHECK(X::liveObjects() == count);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    v.clear();
    CHECK(w[0] == nullptr);
    for (int i = 1; i <= count; ++i) {
        CHECK(*w[i] == X(i));
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-iterate", "[vector]") {
    Vector v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    for (std::size_t i = 0; auto& x : v) {
        CHECK(x == X(i++));
    }
    int i = 19;
    for (auto itr = v.rbegin(); itr != v.rend(); ++itr, --i) {
        auto&& x = *itr;
        CHECK(x == X(i));
    }
    CHECK(i == -1);
}
