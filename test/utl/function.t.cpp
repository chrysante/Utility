#include <array>
#include <iostream>
#include <memory>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <utl/functional.hpp>
#include <utl/typeinfo.hpp>

TEST_CASE("utl::function nullfunction", "[function]") {
    using namespace utl;

    function<void()> functions[] = { function<void()>{}, nullfunction };

    for (auto& f : functions) {
        CHECK(!f);
        CHECK(f == nullfunction);
        CHECK(nullfunction == f);
    }
}

TEST_CASE("utl::function local function", "[function]") {
    using namespace utl;

    function<int()> f = [i = 3]() { return i; };

    CHECK(f);
    CHECK(f != nullfunction);
    auto result = f();
    CHECK(result == 3);
}

TEST_CASE("utl::function local function rvalue reference argument",
          "[function]") {
    using namespace utl;

    int moveCount = 0;

    struct X {
        X(int& i): pi(&i) {}
        X(X&& x) { ++(*x.pi); }
        int* pi;
    };

    function<void(X&&)> f = [](X&& x) mutable {
        X const y = std::move(x);
        (void)y;
    };

    f(X{ moveCount });

    CHECK(moveCount == 1);
}

// static_assert(sizeof(utl::function<void()>) == sizeof(void*) *
// UTL_FUNCTION_TARGET_SIZE_IN_WORDS);

namespace {

struct OperationCounter {
    static void resetCounters() {
        defaultConstructionCount = 0;
        copyConstructionCount = 0;
        moveConstructionCount = 0;
        copyAssignmentCount = 0;
        moveAssignmentCount = 0;
        destructionCount = 0;
    }

    static inline int defaultConstructionCount = 0;
    static inline int copyConstructionCount = 0;
    static inline int moveConstructionCount = 0;
    static inline int copyAssignmentCount = 0;
    static inline int moveAssignmentCount = 0;
    static inline int destructionCount = 0;
    OperationCounter() { ++defaultConstructionCount; }
    OperationCounter(OperationCounter const&) { ++copyConstructionCount; }
    OperationCounter(OperationCounter&&) noexcept { ++moveConstructionCount; }
    ~OperationCounter() { ++destructionCount; }
    OperationCounter& operator=(OperationCounter const&) {
        ++copyAssignmentCount;
        return *this;
    }
    OperationCounter& operator=(OperationCounter&&) noexcept {
        ++moveAssignmentCount;
        return *this;
    }
};

} // namespace

namespace {
class Big {
    char data[128]{};
};
class Small {};

template <typename T, typename U>
U testFunctionAdd(T a, U& b) {
    return static_cast<U>(a + b);
}
long testFunctionMultiply(long a, int& b) {
    return a * b;
}
} // namespace

TEMPLATE_TEST_CASE("utl::function function operation count", "[utl::function]",
                   Big, Small) {
    {
        using namespace utl;
        OperationCounter::resetCounters();

        function<int()> f = [x = OperationCounter(), y = TestType{}] {
            return 3;
        };

        function<int()> g = f;

        CHECK(g);
        CHECK(g != nullfunction);
        CHECK(g() == 3);

        function<int()> h = std::move(g);

        h = f;

        h = std::move(f);

        CHECK(!f);

        CHECK(h);
        h = nullfunction;
        CHECK(!h);
        h = [] { return 4; };
        CHECK(h);

        f = []() { return 3; };
        CHECK(f);
    }
    //	if constexpr (std::is_same_v<TestType, Small>) {
    //		CHECK(OperationCounter::defaultConstructionCount == 1);
    //		CHECK(OperationCounter::copyConstructionCount == 3);
    //		CHECK(OperationCounter::moveConstructionCount == 2);
    //		CHECK(OperationCounter::destructionCount == 6);
    //	}
    //	else {
    //		static_assert(std::is_same_v<TestType, Big>);
    //		CHECK(OperationCounter::defaultConstructionCount == 1);
    //		CHECK(OperationCounter::copyConstructionCount == 3);
    //		CHECK(OperationCounter::moveConstructionCount == 0);
    //		CHECK(OperationCounter::destructionCount == 4);
    //	}
}

TEST_CASE("utl::function function ptr", "[function]") {
    using namespace utl;
    OperationCounter::resetCounters();

    function<int(long, int&)> f = testFunctionAdd;
    auto i = 2;
    CHECK(f(1, i) == 3);

    function<int(long, int&)> g = f;

    CHECK(g);
    CHECK(g != nullfunction);
    CHECK(g(1, i) == 3);

    function<int(long, int&)> h = std::move(g);

    h = f;

    h = std::move(f);

    CHECK(!f);

    CHECK(h);
    h = nullfunction;
    CHECK(!h);
    h = testFunctionMultiply;
    CHECK(h);
    CHECK(h(2, i) == 4);

    f = [](auto i, auto& j) { return i * j; };
    CHECK(f);
    CHECK(f(1, i) == 2);

    function<void()> k = nullptr;
    CHECK(k == nullptr);
}

TEMPLATE_TEST_CASE("utl::unique_function function operation count",
                   "[utl::unique_function]", Big, Small) {
    {
        using namespace utl;
        OperationCounter::resetCounters();

        unique_function<int()> f = [x = OperationCounter(), y = TestType{}] {
            return 3;
        };

        unique_function<int()> g = std::move(f);

        CHECK(g);
        CHECK(g != nullfunction);
        CHECK(g() == 3);

        unique_function<int()> h = std::move(g);

        CHECK(!f);

        CHECK(h);
        g = std::move(h);
        CHECK(g);
        CHECK(g() == 3);
        h = nullfunction;
        CHECK(!h);
        h = [] { return 4; };
        CHECK(h);

        f = []() { return 3; };
        CHECK(f);
    }

    if constexpr (std::is_same_v<TestType, Small>) {
        CHECK(OperationCounter::defaultConstructionCount == 1);
        CHECK(OperationCounter::copyConstructionCount == 0);
        CHECK(OperationCounter::moveConstructionCount == 4);
        CHECK(OperationCounter::destructionCount == 5);
    }
    else {
        static_assert(std::is_same_v<TestType, Big>);
        CHECK(OperationCounter::defaultConstructionCount == 1);
        CHECK(OperationCounter::copyConstructionCount == 0);
        CHECK(OperationCounter::moveConstructionCount == 1);
        CHECK(OperationCounter::destructionCount == 2);
    }
}

TEST_CASE("utl::unique_function function ptr", "[function]") {
    using namespace utl;
    OperationCounter::resetCounters();

    unique_function<int(long, int&)> f = testFunctionAdd;
    auto i = 2;
    CHECK(f(1, i) == 3);

    unique_function<int(long, int&)> g = std::move(f);
    CHECK(g);
    CHECK(g != nullfunction);
    CHECK(!f);

    CHECK(g(1, i) == 3);

    unique_function<int(long, int&)> h = std::move(g);

    CHECK(h);
    h = nullfunction;
    CHECK(!h);
    h = testFunctionMultiply;
    CHECK(h);
    CHECK(h(2, i) == 4);

    f = [](auto i, auto& j) { return i * j; };
    CHECK(f);
    CHECK(f(1, i) == 2);
}
