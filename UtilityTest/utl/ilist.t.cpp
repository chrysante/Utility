#include "Catch2.hpp"

#include <utl/ilist.hpp>
#include <utl/ranges.hpp>

#include "LifetimeCounter.hpp"

namespace {

struct TestType: utl_test::LifetimeCounter, utl::ilist_node_with_parent<TestType, TestType> {
    explicit TestType(): value(0) {}
    TestType(int value): value(value) {}
    
    int value;
};

} // namespace

TEST_CASE("ilist def ctor", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l;
    CHECK(l.empty());
    CHECK(TestType::liveObjects() == 0);
}

TEST_CASE("ilist count value ctor", "[ilist]") {
    TestType::reset();
    {
        utl::ilist<TestType> l(10, -1);
        CHECK(TestType::liveObjects() == 10);
        CHECK(!l.empty());
        CHECK(std::count(l.begin(), l.end(), TestType(-1)) == 10);
        for (auto value: l) {
            CHECK(value.value == -1);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}
    
TEST_CASE("ilist count ctor", "[ilist]") {
    TestType::reset();
    {
        utl::ilist<TestType> l(10);
        CHECK(TestType::liveObjects() == 10);
        CHECK(!l.empty());
        for (auto value: l) {
            CHECK(value.value == 0);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}

TEST_CASE("ilist range ctor", "[ilist]") {
    std::vector<int> data(GENERATE(0, 5, 10));
    std::fill(data.begin(), data.end(), 1);
    TestType::reset();
    {
        utl::ilist<TestType> l(data.begin(), data.end());
        CHECK(TestType::liveObjects() == data.size());
        CHECK(l.empty() == data.empty());
        for (auto value: l) {
            CHECK(value.value == 1);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}

TEST_CASE("ilist copy ctor", "[ilist]") {
    
}

TEST_CASE("ilist move ctor", "[ilist]") {
    
}

TEST_CASE("ilist init_list ctor", "[ilist]") {
    
}

static void testEqual(utl::ilist<TestType> const& l, std::initializer_list<TestType> init_list) {
    auto ilItr = init_list.begin();
    for (auto& elem: l) {
        REQUIRE(ilItr != init_list.end());
        CHECK(elem == *ilItr);
        ++ilItr;
    }
    CHECK(ilItr == init_list.end());
}

TEST_CASE("ilist copy assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l = { 1, 2, 3 };
    utl::ilist<TestType> m = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 7);
    l = m;
    CHECK(TestType::liveObjects() == 8);
    testEqual(l, { 4, 3, 2, 1 });
}

TEST_CASE("ilist move assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l = { 1, 2, 3 };
    utl::ilist<TestType> m = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 7);
    l = std::move(m);
    CHECK(TestType::liveObjects() == 4);
    testEqual(l, { 4, 3, 2, 1 });
}

TEST_CASE("ilist init_list assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l = { 1, 2, 3 };
    CHECK(TestType::liveObjects() == 3);
    l = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 4);
    testEqual(l, { 4, 3, 2, 1 });
}

TEST_CASE("ilist front/back", "[ilist]") {
    utl::ilist<TestType> l = { 1, 2, 3 };
    CHECK(l.front() == TestType(1));
    CHECK(l.back() == TestType(3));
}

// MARK: Modifiers

TEST_CASE("ilist clear", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l(10);
    l.clear();
    CHECK(l.empty());
    CHECK(TestType::liveObjects() == 0);
}

static int sum(utl::ilist<TestType> const& l) {
    return std::accumulate(l.begin(), l.end(), 0, [](int acc, TestType const& rhs) { return acc + rhs.value; });
}

TEST_CASE("ilist insert single value", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType> l(count);
    SECTION("begin") {
        l.insert(l.begin(), 1);
        CHECK(sum(l) == 1);
    }
    SECTION("middle") {
        auto itr = l.begin();
        std::advance(itr, std::min<std::size_t>(count, 3));
        itr = l.insert(itr, 1);
        CHECK(sum(l) == 1);
    }
    SECTION("end") {
        l.insert(l.end(), 1);
        CHECK(sum(l) == 1);
    }
}

TEST_CASE("ilist insert count value", "[ilist]") {
    std::size_t const beginCount = GENERATE(0, 10);
    std::size_t const insertCount = GENERATE(0, 1, 5);
    utl::ilist<TestType> l(beginCount);
    SECTION("begin") {
        l.insert(l.begin(), insertCount, 1);
        for (std::size_t index = 0; auto elem: l) {
            INFO(index);
            CHECK(elem.value == (index < insertCount ? 1 : 0));
            ++index;
        }
        CHECK(sum(l) == insertCount);
    }
    SECTION("middle") {
        auto itr = l.begin();
        std::size_t const insertIndex = std::min<std::size_t>(beginCount, 3);
        std::advance(itr, insertIndex);
        itr = l.insert(itr, insertCount, 1);
        for (std::size_t index = 0; auto elem: l) {
            INFO(index);
            CHECK(elem.value == (index < insertIndex ? 0 : index < insertIndex + insertCount ? 1 : 0));
            ++index;
        }
        CHECK(sum(l) == insertCount);
        
    }
    SECTION("end") {
        l.insert(l.end(), insertCount, 1);
        for (std::size_t index = 0; auto elem: utl::reverse(l)) {
            INFO(index);
            CHECK(elem.value == (index < insertCount ? 1 : 0));
            ++index;
        }
        CHECK(sum(l) == insertCount);
    }
}

TEST_CASE("ilist emplace", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType> l(count);
    std::size_t const insertIndex = std::min<std::size_t>(count, 3);
    l.emplace(std::next(l.begin(), insertIndex), 1);
    for (std::size_t index = 0; auto& elem: l) {
        CHECK(elem.value == (index == insertIndex ? 1 : 0));
        ++index;
    }
}

TEST_CASE("ilist erase", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l = { 0, 1, 2, 3, 3, 4, 5 };
    CHECK(TestType::liveObjects() == 7);
    l.erase(std::next(l.begin(), 3));
    CHECK(TestType::liveObjects() == 6);
    std::size_t index = 0;
    for (auto& elem: l) {
        CHECK(elem.value == index);
        ++index;
    }
    CHECK(index == 6);
}

TEST_CASE("ilist erase range", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType> l = { 0, 1, 1, 1, 1, 1, 2, 3 };
    CHECK(TestType::liveObjects() == 8);
    l.erase(std::next(l.begin(), 2), std::prev(l.end(), 2));
    CHECK(TestType::liveObjects() == 4);
    std::size_t index = 0;
    for (auto& elem: l) {
        CHECK(elem.value == index);
        ++index;
    }
    CHECK(index == 4);
}


TEST_CASE("ilist push_back", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType> l(count);
    if (!l.empty()) {
        CHECK(l.back() == TestType(0));
    }
    l.push_back(1);
    CHECK(l.back() == TestType(1));
}

TEST_CASE("ilist push_front", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType> l(count);
    if (!l.empty()) {
        CHECK(l.front() == TestType(0));
    }
    l.push_front(1);
    CHECK(l.front() == TestType(1));
}


// Other assign() method here
    
//    for (auto elem: l) {
//        std::cout << elem.value << std::endl;
//    }
//
//    for (int i = 0; i < 4; ++i) {
//        l.push_back(new TestType(i));
//    }
//
//    auto itr = l.begin();
//
//    std::advance(itr, 2);
//
//    l.insert(itr, new TestType(10));
//
////    l.erase(itr);
//
//    for (auto elem: l) {
//        std::cout << elem.value << std::endl;
//    }
//
//    l.clear();
//
//    CHECK(l.empty());
//
//}
