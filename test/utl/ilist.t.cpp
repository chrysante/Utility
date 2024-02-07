#include <numeric>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <utl/ilist.hpp>

#include "utl/LifetimeCounter.hpp"

namespace {

struct TestType: utl::ilist_node<TestType>, utl_test::LifetimeCounter {
    explicit TestType(): value(0) {}
    TestType(int value): value(value) {}

    friend std::ostream& operator<<(std::ostream& str, TestType const& t) {
        return str << t.value;
    }

    int value;
};

template <typename T>
struct NotPropagatingNeverEqualAllocator: std::allocator<T> {
    using propagate_on_container_move_assignment = std::false_type;
    using is_always_equal = std::false_type;
    bool operator==(NotPropagatingNeverEqualAllocator const&) const {
        return false;
    }
};

template <typename T>
struct NotPropagatingAlwaysEqualAllocator: std::allocator<T> {
    using propagate_on_container_move_assignment = std::false_type;
    using is_always_equal = std::true_type;
    bool operator==(NotPropagatingAlwaysEqualAllocator const&) const {
        return true;
    }
};

template <typename T>
struct PropagatingNeverEqualAllocator: std::allocator<T> {
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::false_type;
    bool operator==(PropagatingNeverEqualAllocator const&) const {
        return false;
    }
};

template <typename T>
static std::ostream& operator<<(std::ostream& str,
                                std::initializer_list<T> ilist) {
    str << "[";
    bool first = true;
    for (auto& i : ilist) {
        if (!first) {
            str << ", ";
        }
        first = false;
        str << i;
    }
    return str << "]";
}

} // namespace

template <typename Allocator>
static void testEqual(utl::ilist<TestType, Allocator> const& l,
                      std::initializer_list<TestType> init_list) {
    auto ilItr = init_list.begin();
    INFO("l = " << l);
    INFO("ref = " << init_list);
    for (auto& elem : l) {
        REQUIRE(ilItr != init_list.end());
        CHECK(elem == *ilItr);
        ++ilItr;
    }
    CHECK(ilItr == init_list.end());
}

#define LIST_TEST_CASE(...)                                                    \
    TEMPLATE_TEST_CASE_SIG(__VA_ARGS__,                                        \
                           ((typename Allocator, int __I), Allocator, __I),    \
                           (std::allocator<::TestType>, 0),                    \
                           (NotPropagatingNeverEqualAllocator<TestType>, 0),   \
                           (NotPropagatingAlwaysEqualAllocator<TestType>, 0),  \
                           (PropagatingNeverEqualAllocator<::TestType>, 0))

LIST_TEST_CASE("ilist def ctor", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l;
    CHECK(l.empty());
    CHECK(TestType::liveObjects() == 0);
}

LIST_TEST_CASE("ilist count value ctor", "[ilist]") {
    TestType::reset();
    {
        utl::ilist<TestType, Allocator> l(10, -1);
        CHECK(TestType::liveObjects() == 10);
        CHECK(!l.empty());
        CHECK(std::count(l.begin(), l.end(), TestType(-1)) == 10);
        for (auto value : l) {
            CHECK(value.value == -1);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}

LIST_TEST_CASE("ilist count ctor", "[ilist]") {
    TestType::reset();
    {
        utl::ilist<TestType, Allocator> l(10);
        CHECK(TestType::liveObjects() == 10);
        CHECK(!l.empty());
        for (auto value : l) {
            CHECK(value.value == 0);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}

LIST_TEST_CASE("ilist range ctor", "[ilist]") {
    std::vector<int> data(GENERATE(0, 5, 10));
    std::fill(data.begin(), data.end(), 1);
    TestType::reset();
    {
        utl::ilist<TestType, Allocator> l(data.begin(), data.end());
        CHECK(TestType::liveObjects() == data.size());
        CHECK(l.empty() == data.empty());
        for (auto value : l) {
            CHECK(value.value == 1);
        }
    }
    CHECK(TestType::liveObjects() == 0);
}

LIST_TEST_CASE("ilist copy ctor", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 };
    utl::ilist<TestType, Allocator> m = l;
    CHECK(TestType::liveObjects() == 8);
    testEqual(m, { 1, 2, 3, 4 });
}

LIST_TEST_CASE("ilist move ctor", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 };
    utl::ilist<TestType, Allocator> m = std::move(l);
    CHECK(TestType::liveObjects() >= 4);
    testEqual(m, { 1, 2, 3, 4 });
}

LIST_TEST_CASE("ilist init_list ctor", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 };
    CHECK(TestType::liveObjects() == 4);
    testEqual(l, { 1, 2, 3, 4 });
}

LIST_TEST_CASE("ilist copy assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3 };
    utl::ilist<TestType, Allocator> m = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 7);
    l = m;
    CHECK(TestType::liveObjects() == 8);
    testEqual(l, { 4, 3, 2, 1 });
}

LIST_TEST_CASE("ilist move assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3 };
    utl::ilist<TestType, Allocator> m = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 7);
    l = std::move(m);
    CHECK(TestType::liveObjects() >= 4);
    testEqual(l, { 4, 3, 2, 1 });
}

LIST_TEST_CASE("ilist init_list assignment operator", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 1, 2, 3 };
    CHECK(TestType::liveObjects() == 3);
    l = { 4, 3, 2, 1 };
    CHECK(TestType::liveObjects() == 4);
    testEqual(l, { 4, 3, 2, 1 });
}

LIST_TEST_CASE("ilist front/back", "[ilist]") {
    utl::ilist<TestType, Allocator> l = { 1, 2, 3 };
    CHECK(l.front() == TestType(1));
    CHECK(l.back() == TestType(3));
}

// MARK: Modifiers

LIST_TEST_CASE("ilist clear", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l(10);
    l.clear();
    CHECK(l.empty());
    CHECK(TestType::liveObjects() == 0);
}

template <typename Allocator>
static int sum(utl::ilist<TestType, Allocator> const& l) {
    return std::accumulate(l.begin(), l.end(), 0,
                           [](int acc, TestType const& rhs) {
        return acc + rhs.value;
    });
}

LIST_TEST_CASE("ilist insert single value", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType, Allocator> l(count);
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

LIST_TEST_CASE("ilist insert count value", "[ilist]") {
    std::size_t const beginCount = GENERATE(0, 10);
    std::size_t const insertCount = GENERATE(0, 1, 5);
    utl::ilist<TestType, Allocator> l(beginCount);
    SECTION("begin") {
        l.insert(l.begin(), insertCount, 1);
        for (std::size_t index = 0; auto elem : l) {
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
        for (std::size_t index = 0; auto elem : l) {
            INFO(index);
            CHECK(elem.value == (index < insertIndex               ? 0 :
                                 index < insertIndex + insertCount ? 1 :
                                                                     0));
            ++index;
        }
        CHECK(sum(l) == insertCount);
    }
    SECTION("end") {
        l.insert(l.end(), insertCount, 1);
        std::size_t index = 0;
        for (auto itr = l.rbegin(); itr != l.rend(); ++itr) {
            auto elem = *itr;
            INFO(index);
            CHECK(elem.value == (index < insertCount ? 1 : 0));
            ++index;
        }
        CHECK(sum(l) == insertCount);
    }
}

LIST_TEST_CASE("ilist emplace", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType, Allocator> l(count);
    std::size_t const insertIndex = std::min<std::size_t>(count, 3);
    l.emplace(std::next(l.begin(), insertIndex), 1);
    for (std::size_t index = 0; auto& elem : l) {
        CHECK(elem.value == (index == insertIndex ? 1 : 0));
        ++index;
    }
}

LIST_TEST_CASE("ilist erase", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = {
        0, 1, 2, 3, /* >> */ 3, /* << */ 4, 5
    };
    CHECK(TestType::liveObjects() == 7);
    auto itr = l.erase(std::next(l.begin(), 3));
    CHECK(itr == std::next(l.begin(), 3));
    CHECK(*itr == TestType(3));
    CHECK(TestType::liveObjects() == 6);
    std::size_t index = 0;
    for (auto& elem : l) {
        CHECK(elem.value == index);
        ++index;
    }
    CHECK(index == 6);
}

LIST_TEST_CASE("ilist erase - 2", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 0, 1, 2, 3, 4, 5 };
    CHECK(TestType::liveObjects() == 6);
    auto pos = GENERATE(0, 1, 2, 5);
    auto itr = l.erase(std::next(l.begin(), pos));
    CHECK(itr == std::next(l.begin(), pos));
    if (itr != l.end()) {
        CHECK(*itr == TestType(pos));
    }
    CHECK(TestType::liveObjects() == 5);
    std::size_t index = 0;
    INFO("pos = " << pos);
    for (auto& elem : l) {
        if (index == pos) {
            ++index;
        }
        CHECK(elem.value == index);
        ++index;
    }
    CHECK(index == (pos == 5 ? 5 : 6));
}

LIST_TEST_CASE("ilist erase range", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 0, 1, /* >> */ 1, 1,
                                          1, 1, /* << */ 2, 3 };
    CHECK(TestType::liveObjects() == 8);
    auto itr = l.erase(std::next(l.begin(), 2), std::prev(l.end(), 2));
    CHECK(itr == std::prev(l.end(), 2));
    CHECK(*itr == TestType(2));
    CHECK(TestType::liveObjects() == 4);
    std::size_t index = 0;
    for (auto& elem : l) {
        CHECK(elem.value == index);
        ++index;
    }
    CHECK(index == 4);
}

LIST_TEST_CASE("ilist erase all", "[ilist]") {
    TestType::reset();
    utl::ilist<TestType, Allocator> l = { 0, 1, 1, 1, 1, 1, 2, 3 };
    CHECK(TestType::liveObjects() == 8);
    auto itr = l.erase(l.begin(), l.end());
    CHECK(itr == l.end());
    CHECK(l.empty());
}

LIST_TEST_CASE("ilist push_back", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType, Allocator> l(count);
    if (!l.empty()) {
        CHECK(l.back() == TestType(0));
    }
    l.push_back(1);
    CHECK(l.back() == TestType(1));
}

LIST_TEST_CASE("ilist push_front", "[ilist]") {
    std::size_t const count = GENERATE(0, 10);
    utl::ilist<TestType, Allocator> l(count);
    if (!l.empty()) {
        CHECK(l.front() == TestType(0));
    }
    l.push_front(1);
    CHECK(l.front() == TestType(1));
    CHECK(l.front().prev() == l.end().to_address());
    size_t size = 0;
    for ([[maybe_unused]] auto& _ : l) {
        ++size;
    }
    CHECK(size == count + 1);
}

LIST_TEST_CASE("ilist swap - empty", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l, m;
    l.swap(m);
    CHECK(l.empty());
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist swap - empty/non-empty", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l, m = { 3, 4 };
    l.swap(m);
    testEqual(l, { 3, 4 });
    testEqual(m, {});
}

LIST_TEST_CASE("ilist swap - non-empty/empty", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2 }, m;
    l.swap(m);
    testEqual(l, {});
    testEqual(m, { 1, 2 });
}

LIST_TEST_CASE("ilist swap - non-empty", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2 }, m = { 3, 4 };
    l.swap(m);
    testEqual(l, { 3, 4 });
    testEqual(m, { 1, 2 });
}

LIST_TEST_CASE("ilist splice", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2 }, m = { 3, 4 };
    l.splice(l.end(), m);
    testEqual(l, { 1, 2, 3, 4 });
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist splice - 2", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2 }, m = { 3, 4 };
    l.splice(std::prev(l.end()), m);
    testEqual(l, { 1, 3, 4, 2 });
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist splice - 3", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2 }, m = { 3, 4 };
    l.splice(l.begin(), m);
    testEqual(l, { 3, 4, 1, 2 });
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist splice - 4", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = {}, m = { 3, 4 };
    l.splice(l.begin(), m);
    testEqual(l, { 3, 4 });
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist splice - 5", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 }, m;
    m.splice(m.begin(), std::next(l.begin(), 2), l.end());
    testEqual(l, { 1, 2 });
    testEqual(m, { 3, 4 });
}

LIST_TEST_CASE("ilist splice - 6", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l, m;
    m.splice(m.begin(), l.begin(), l.end());
    CHECK(l.empty());
    CHECK(m.empty());
}

LIST_TEST_CASE("ilist splice - 7", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 }, m = { 1, 2 };
    m.splice(m.end(), std::next(l.begin(), 2), l.end());
    testEqual(l, { 1, 2 });
    testEqual(m, { 1, 2, 3, 4 });
}

LIST_TEST_CASE("ilist splice - 8", "[ilist][ilist-swap]") {
    utl::ilist<TestType, Allocator> l = { 1, 2, 3, 4 }, m = { 1, 4 };
    m.splice(std::next(m.begin()), std::next(l.begin()), std::prev(l.end()));
    testEqual(l, { 1, 4 });
    testEqual(m, { 1, 2, 3, 4 });
}

namespace {

struct Incomplete;

template <typename T>
using BufferFor = std::aligned_storage_t<sizeof(T), alignof(T)>;

struct UsesIncompleteList {
    UsesIncompleteList() = default;
    UsesIncompleteList(UsesIncompleteList const&) = delete;
    ~UsesIncompleteList();
    utl::ilist<Incomplete> list;
};

struct Incomplete: utl::ilist_node<Incomplete> {};

UsesIncompleteList::~UsesIncompleteList() = default;

} // namespace

namespace {

struct Incomplete2;

} // namespace

TEST_CASE("ilist incomplete type", "[ilist]") {
    using L = utl::ilist<Incomplete2>;
    BufferFor<L> buffer{};
    auto* lPtr = reinterpret_cast<L*>(&buffer);
    lPtr = std::construct_at(lPtr);
    L& l = *lPtr;
    CHECK(l.empty());
}

namespace {

struct Base: public utl::ilist_node<Base> {};
struct Derived: public Base {};

} // namespace

TEST_CASE("ilist with derived type", "[ilist]") {
    utl::ilist<Derived> L;
}
