#include <ranges>
#include <numeric>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <utl/vector.hpp>

#include "utl/vector/VectorTest.hpp"

using namespace utl_test;

TEST_CASE("vector object size", "[vector]") {
    CHECK(sizeof(utl::vector<int>) == 2 * 4 + sizeof(void*));
    CHECK((sizeof(utl::vector<char>) == 24 || sizeof(utl::vector<char>) == 16));
}

VECTOR_TEST_CASE(X, TRX, "vector-construct-1", "[vector]") {
    X::reset();
    Vector v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-construct-2", "[vector]") {
    X::reset();
    Vector v(Tag(1));
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-construct-3", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    Vector v(count, T{ 1 }, Tag(1));
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    for (auto& i : v) {
        CHECK(i.alloc.tag == Tag(1));
        CHECK(i.value == 1);
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-construct-4", "[vector]") {
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    Vector v(count, Tag(1));
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    for (auto& i : v) {
        CHECK(i.alloc.tag == Tag(1));
        CHECK(i == X());
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-constructor", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    T data[5]{ { 3, alloc }, { 4, alloc }, { 2, alloc }, { -1, alloc }, { 10, alloc } };
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(std::begin(data), std::end(data), tag2);
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(v[0].alloc.tag == tag2);
    CHECK(v[0].value == 3);
    CHECK(v[1].alloc.tag == tag2);
    CHECK(v[1].value == 4);
    CHECK(v[2].alloc.tag == tag2);
    CHECK(v[2].value == 2);
    CHECK(v[3].alloc.tag == tag2);
    CHECK(v[3].value == -1);
    CHECK(v[4].alloc.tag == tag2);
    CHECK(v[4].value == 10);
    CHECK(X::liveObjects() == 10);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-constructor-2", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    T data[1]{};
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(data, data + 0, tag2);
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 1);
}

namespace {
struct Y {
    int value;
    operator X() const { return X(value); }
    operator TRX() const { return TRX(value); }
};
} // namespace

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-converting-constructor", "[vector]") {
    X::reset();
    Y data[5]{ 3, 4, 2, -1, 10 };
    Vector v(std::begin(data), (std::end(std::as_const(data))), Tag(1));
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(X::liveObjects() == 5);
    for (std::size_t i = 0; i < 5; ++i) {
        CHECK(v[i].alloc.tag == Tag(1));
        CHECK(v[i].value == data[i].value);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-converting-constructor/2", "[vector]") {
    X::reset();
    auto const count = 10;
    Vector v(count);
    std::iota(v.begin(), v.end(), 0);
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    CHECK(X::liveObjects() == count);
    for (std::size_t i = 0; i < count; ++i) {
        CHECK(v[i].value == i);
    }
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-copy-ctor", "[vector]") {
    X::reset();
    VectorA v(Tag{ 1 });
    auto const count = GENERATE(0, 2, 10);
    for (std::size_t i = 0; i < count; ++i) {
        v.emplace_back(i + 1);
    }
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(v, tag2);
    for (int i = 0; i < count; ++i) {
        v[i].alloc.tag = tag2;
        v[i].value     = i + 1;
    }
    CHECK(X::liveObjects() == 2 * count);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-copy-assign", "[vector]") {
    X::reset();
    VectorA v(Tag(1));
    auto const count = GENERATE(0, 2, 5, 10);
    for (std::size_t i = 0; i < count; ++i) {
        v.emplace_back(i + 1);
    }
    auto const wCount = GENERATE(0, 2, 5, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    CHECK(X::liveObjects() == count + wCount);
    w = v;
    REQUIRE(w.size() == count);
    CHECK(w.capacity() >= count);
    for (std::size_t i = 0; i < count; ++i) {
        INFO(v);
        INFO(w);
        CHECK(w[i].alloc.tag == tag2);
        CHECK(w[i].value == i + 1);
    }
    CHECK(X::liveObjects() == 2 * count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-copy-assign-ilist", "[vector]") {
    X::reset();
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    Vector w(wCount, tag2);
    w = { 1, 2, 3 };
    REQUIRE(w.size() == 3);
    CHECK(w.capacity() >= 3);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    CHECK(w[2].alloc.tag == tag2);
    CHECK(w[2].value == 3);
    CHECK(X::liveObjects() == 3);
    w = {};
    REQUIRE(w.size() == 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-move-ctor", "[vector]") {
    X::reset();
    VectorA v({ 1, 2 }, Tag(1));
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    v.clear();
    CHECK(X::liveObjects() == 2);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-move-assign", "[vector]") {
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    VectorA v(Tag(1));
    for (std::size_t i = 0; i < count; ++i) {
        v.emplace_back(i);
    }
    auto const wCount = GENERATE(0, 2, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    w = std::move(v);
    REQUIRE(w.size() == count);
    CHECK(w.capacity() >= count);
    for (std::size_t i = 0; i < count; ++i) {
        CHECK(w[i].alloc.tag == tag2);
        CHECK(w[i].value == i);
    }
    v.clear();
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-ilist", "[vector]") {
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    Vector v({ { 1, alloc }, { 2, alloc }, { 4, alloc } }, Tag{ 2 });
    REQUIRE(v.size() == 3);
    if (!Small) {
        CHECK(v.capacity() == 3);
    }
    CHECK(v[0].alloc.tag == Tag{ 2 });
    CHECK(v[0].value == 1);
    CHECK(v[1].alloc.tag == Tag{ 2 });
    CHECK(v[1].value == 2);
    CHECK(v[2].alloc.tag == Tag{ 2 });
    CHECK(v[2].value == 4);
    CHECK(X::liveObjects() == 3);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-ilist-2", "[vector]") {
    X::reset();
    Vector v({}, Tag{ 2 });
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 0);
}

