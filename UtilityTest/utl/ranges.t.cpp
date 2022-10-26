#include "Catch2.hpp"

#include <vector>
#include <list>
#include <forward_list>

#include <utl/ranges.hpp>
#include <utl/vector.hpp>

namespace {
enum class E {
    _0, _1, _2, _3, _4, _5, _6,
};
}

TEST_CASE("enumerate enum - 1", "[utility][ranges]") {
    int index = 0;
    for (E const value: utl::enumerate<E>(0, (int)E::_6 + 1)) {
        CHECK((int)value == index);
        ++index;
    }
    CHECK(index == 7);
}

namespace {
enum class F {
    _0, _1, _2, _3, _4, _5, _6, _count
};
}

TEST_CASE("enumerate enum - 2", "[utility][ranges]") {
    int count = 0;
    for (auto const [index, value]: utl::enumerate(utl::enumerate<F>())) {
        CHECK((int)value == index);
        ++count;
    }
    CHECK(count == (int)F::_count);
}


TEST_CASE("enumerating_iterator", "[utility][ranges]") {
    int const count = GENERATE(0, 10);
    utl::vector<std::unique_ptr<int>> v(utl::transform(utl::iota(count), [](int value) { return std::make_unique<int>(value); }));
    int i = 0;
    for (auto itr = utl::enumerating_iterator(v.begin()); itr != v.end(); ++itr) {
        auto&& [index, value] = *itr;
        CHECK(*value == *v[index]);
        ++i;
    }
    CHECK(i == v.size());
}


TEST_CASE("enumerate_range", "[utility][ranges]") {
    int const count = GENERATE(0, 10);
    utl::vector<std::unique_ptr<int>> v(utl::transform(utl::iota(count), [](int value) { return std::make_unique<int>(value); }));
    int i = 0;
    for (auto&& [index, value]: utl::enumerate(v)) {
        CHECK(*value == *v[index]);
        ++i;
    }
    CHECK(i == count);
}

TEST_CASE("enumerate_range owning", "[utility][ranges]") {
    int const count = GENERATE(0, 10);
    int i = 0;
    for (auto&& [index, value]: utl::enumerate(utl::vector<std::unique_ptr<int>>(utl::transform(utl::iota(count), [](int value) { return std::make_unique<int>(value); })))) {
        CHECK(*value == index);
        ++i;
    }
    CHECK(i == count);
}

TEST_CASE("transform_iterator", "[utility][ranges]") {
    utl::small_vector<int> const v(utl::iota(10));
    int test = 1;
    for (auto i = utl::transform_iterator(v.begin(), [](int i) { return i + 1; }); i != v.end(); ++i) {
        CHECK(*i == test);
        ++test;
    }
    CHECK(test == 11);
}

TEST_CASE("transform_range", "[utility][ranges]") {
    utl::vector<std::unique_ptr<int>> const v(utl::transform(utl::iota(10), [](int i) { return std::make_unique<int>(3 * i); }));
    int i = 0;
    for (int const j: utl::transform(v.begin(), v.end(), [](auto&& p) { return *p; })) {
        CHECK(i == j);
        i += 3;
    }
    CHECK(i == 30);
    i = 0;
    for (int const j: utl::transform(v, [](auto&& p) { return *p; })) {
        CHECK(i == j);
        i += 3;
    }
}

TEST_CASE("transform_range owning", "[utility][ranges]") {
    int i = 0;
    for (int const j: utl::transform(utl::vector<std::unique_ptr<int>>(utl::transform(utl::iota(10), [](int i) { return std::make_unique<int>(3 * i); })), [](auto&& p) { return *p; })) {
        CHECK(i == j);
        i += 3;
    }
    CHECK(i == 30);
}

TEST_CASE("stride_iterator") {
    utl::small_vector<int> const v(utl::iota(10));
    int test = 0;
    for (auto i = utl::stride_iterator(v.begin(), 2); i != v.end(); ++i) {
        CHECK(*i == test);
        test += 2;
    }
    CHECK(test == 10);
}

TEST_CASE("stride_range") {
    utl::small_vector<int> const v(utl::iota(10));
    int test = 0;
    for (int const i: utl::stride(v, 2)) {
        CHECK(i == test);
        test += 2;
    }
    CHECK(test == 10);
}

TEST_CASE("stride_range owning") {
    int test = 0;
    for (int const i: utl::stride(utl::small_vector<int>(utl::iota(10)), 2)) {
        CHECK(i == test);
        test += 2;
    }
    CHECK(test == 10);
}

TEST_CASE("reverse_range") {
    int const count = GENERATE(0, 10);
    utl::small_vector<int> const v((utl::iota(count)));
    int test = count;
    for (int const i: utl::reverse(v)) {
        --test;
        CHECK(i == test);
    }
    CHECK(test == 0);
}

TEST_CASE("reverse_range owning") {
    int const count = GENERATE(0, 10);
    int test = count;
    for (int const i: utl::reverse(utl::small_vector<int>((utl::iota<int>(count))))) {
        --test;
        CHECK(i == test);
    }
    CHECK(test == 0);
}

TEST_CASE("stride_range(transform_range)") {
    utl::small_vector<int> const v(utl::iota(10));
    int test = 0;
    for (int const i: utl::stride(utl::transform(v, [](int i) { return -i; }), 2)) {
        CHECK(i == test);
        test -= 2;
    }
    CHECK(test == -10);
}

TEST_CASE("iota", "[utility][ranges]") {
    SECTION("Zero to N") {
        int const count = GENERATE(0, 1, 10, 100);
        int sum = 0;
        for (int j = 0; int i: utl::iota(count)) {
            CHECK(i == j++);
            sum += i;
        }
        CHECK(sum == (count == 0 ? 0 : count * (count - 1) / 2));
    }
    SECTION("Negative to positive") {
        int j = -10;
        for (int i: utl::iota(-10, 10)) {
            CHECK(i == j++);
        }
        CHECK(j == 10);
    }
}

/// Only checking compilation.
/// These functions will not be executed.
[[maybe_unused]] static void test_enumrate_enum() {
    auto e = utl::enumerate<F>();
    static_assert(utl::random_access_iterator<decltype(e.begin())>);
}

[[maybe_unused]] static void test_iota() {
    utl::iota io(10);
    static_assert(utl::random_access_iterator<decltype(io.begin())>);
}

[[maybe_unused]] static void test_enumerate() {
    /* Forward */ {
        std::forward_list<std::unique_ptr<int>> v;
        auto e = utl::enumerate(v);
        static_assert(utl::forward_iterator<decltype(e.begin())>);
    }
    /* Bidirectional */ {
        std::list<std::unique_ptr<int>> v;
        auto e = utl::enumerate(v);
        static_assert(utl::bidirectional_iterator<decltype(e.begin())>);
    }
    /* Random access - 1 */ {
        std::vector<std::unique_ptr<int>> v;
        auto e = utl::enumerate(v);
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
    /* Random access - 2 */ {
        utl::iota io(10);
        auto e = utl::enumerate(io);
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
}

[[maybe_unused]] static void test_transform() {
    auto t = [](std::unique_ptr<int>&) { return 0.0; };
    /* Forward */ {
        std::forward_list<std::unique_ptr<int>> v;
        auto e = utl::transform(v, t);
        static_assert(utl::forward_iterator<decltype(e.begin())>);
    }
    /* Bidirectional */ {
        std::list<std::unique_ptr<int>> v;
        auto e = utl::transform(v, t);
        static_assert(utl::bidirectional_iterator<decltype(e.begin())>);
    }
    /* Random access - 1 */ {
        std::vector<std::unique_ptr<int>> v;
        auto e = utl::transform(v, t);
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
    /* Random access - 2 */ {
        utl::iota io(10);
        auto e = utl::transform(io, [](int){ return 0.0; });
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
}

[[maybe_unused]] static void test_stride() {
    /* Forward */ {
        std::forward_list<std::unique_ptr<int>> v;
        auto e = utl::stride(v, 2);
        static_assert(utl::forward_iterator<decltype(e.begin())>);
    }
    /* Bidirectional */ {
        std::list<std::unique_ptr<int>> v;
        auto e = utl::stride(v, 2);
        static_assert(utl::bidirectional_iterator<decltype(e.begin())>);
    }
    /* Random access - 1 */ {
        std::vector<std::unique_ptr<int>> v;
        auto e = utl::stride(v, 2);
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
    /* Random access - 2 */ {
        utl::iota io(10);
        auto e = utl::stride(io, 2);
        static_assert(utl::random_access_iterator<decltype(e.begin())>);
    }
}
