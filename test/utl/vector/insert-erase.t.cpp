#include <catch/catch2.hpp>

#include <list>

#include <utl/ranges.hpp>
#include <utl/vector.hpp>

#include "VectorTest.hpp"

using namespace utl_test;

static void reserveAdditional(auto& v, std::size_t count) {
    auto const m = GENERATE(0u, 1u);
    v.reserve(v.size() + count * m);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-1-2", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, 1);
    T x(-1);
    SECTION("begin") {
        auto const result = v.insert(v.begin(), x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-3", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    T x(-1);
    REQUIRE(X::liveObjects() == 4 + 1);
    SECTION("into-empty") {
        v = Vector{};
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, x, x });
        CHECK(X::liveObjects() == 3 + 1);
    }
    SECTION("into-empty/2") {
        v = Vector{};
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{});
        CHECK(X::liveObjects() == 0 + 1);
    }
    SECTION("begin") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, x, x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("begin/2") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("begin/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 1, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, x, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("mid/2") {
        v.push_back(T(4));
        v.push_back(T(5));
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, x, x, 1, 2, 3, 4, 5 });
        CHECK(X::liveObjects() == 9 + 1);
    }
    SECTION("mid/3") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.begin() + 1, 0, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("mid/4") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin() + 1, 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end() - 1, 3, x);
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, x, x, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end - 1/2") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.end() - 1, 0, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end - 1/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.end() - 1, 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 2") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end() - 2, 3, x);
        CHECK(result == v.end() - 5);
        CHECK(v == TaVector<T>{ 0, 1, x, x, x, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end(), 3, x);
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x, x, x });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end/2") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.end(), 0, x);
        CHECK(result == v.end() - 0);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.end(), 1, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-4", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    std::size_t const count = GENERATE(0, 3, 10);
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, count);
    std::list<T> data;
    for (std::size_t i = 0; i < count; ++i) {
        data.emplace_back(-(int)(i + 1));
    }
    auto makeRef = [&](int position) {
        assert(position <= 4);
        Vector result;
        int i = 0;
        for (; i < position; ++i) {
            result.push_back(i);
        }
        for (auto& i: data) {
            result.push_back(i);
        }
        for (; i < 4; ++i) {
            result.push_back(i);
        }
        return result;
    };
    SECTION("begin") {
        auto const result = v.insert(v.begin(), std::begin(data), std::end(data));
        CHECK(result == v.begin());
        CHECK(v == makeRef(0));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, std::begin(data), std::end(data));
        CHECK(result == v.begin() + 1);
        CHECK(v == makeRef(1));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, std::begin(data), std::end(data));
        CHECK(result == v.end() - 1 - data.size());
        CHECK(v == makeRef(3));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), std::begin(data), std::end(data));
        CHECK(result == v.end() - data.size());
        CHECK(v == makeRef(4));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-5", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, 3);
    SECTION("begin") {
        auto const result = v.insert(v.begin(), { -1, -2, -3 });
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ -1, -2, -3, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("begin/2") {
        auto const result = v.insert(v.begin(), {});
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, { -1, -2, -3 });
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, -1, -2, -3, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("mid/2") {
        auto const result = v.insert(v.begin() + 1, {});
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, { -1, -2, -3 });
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<T>{ 0, 1, 2, -1, -2, -3, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end - 1/2") {
        auto const result = v.insert(v.end() - 1, {});
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), { -1, -2, -3 });
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, -1, -2, -3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end/2") {
        auto const result = v.insert(v.end(), {});
        CHECK(result == v.end());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-erase", "[vector]") {
    X::reset();
    Vector v = { 0, 1, 2, 3, 4, 5 };
    REQUIRE(X::liveObjects() == 6);
    SECTION("all") {
        auto result = v.erase(v.begin(), v.end());
        CHECK(result == v.end());
        CHECK(v.empty());
        CHECK(X::liveObjects() == 0);
    }
    SECTION("begin single") {
        auto result = v.erase(v.begin());
        CHECK(result == v.begin());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 1, 2, 3, 4, 5 });
    }
    SECTION("end single") {
        auto result = v.erase(v.end() - 1);
        CHECK(result == v.end());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 1, 2, 3, 4 });
    }
    SECTION("mid single") {
        auto result = v.erase(v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 2, 3, 4, 5 });
    }
    SECTION("begin range") {
        auto result = v.erase(v.begin(), v.begin() + 2);
        CHECK(result == v.begin());
        CHECK(v.size() == 4);
        CHECK(X::liveObjects() == 4);
        CHECK(v == Vector{ 2, 3, 4, 5 });
    }
    SECTION("end range") {
        auto result = v.erase(v.begin() + 3, v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 3);
        CHECK(X::liveObjects() == 3);
        CHECK(v == Vector{ 0, 1, 2 });
    }
    SECTION("mid range") {
        auto result = v.erase(v.begin() + 1, v.end() - 2);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 3);
        CHECK(X::liveObjects() == 3);
        CHECK(v == Vector{ 0, 4, 5 });
    }
    SECTION("empty range") {
        auto result = v.erase(v.begin(), v.begin());
        CHECK(result == v.begin());
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("empty range/2") {
        auto result = v.erase(v.begin() + 1, v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("empty range/3") {
        auto result = v.erase(v.end(), v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range") {
        auto result = v.erase(v.begin(), v.begin() + 1);
        CHECK(result == v.begin());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 1, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range/2") {
        auto result = v.erase(v.begin() + 1, v.begin() + 2);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range/3") {
        auto result = v.erase(v.end() - 1, v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 1, 2, 3, 4 });
    }
}
