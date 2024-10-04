#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <utl/tinyptrset.hpp>

namespace {

struct TestObject {
    int value;
    explicit TestObject(int val): value(val) {}
    bool operator<=>(TestObject const&) const = default;
};

} // namespace

static_assert(sizeof(utl::tinyptrset<int*>) == sizeof(void*));

TEST_CASE("Default construction", "[tinyptrset]") {
    utl::tinyptrset<TestObject*> set;
    REQUIRE(set.empty());
    REQUIRE(set.size() == 0);
    REQUIRE(set.begin() == set.end());
}

TEST_CASE("Insert single pointer", "[tinyptrset]") {
    TestObject obj1(1);
    utl::tinyptrset<TestObject*> set;
    auto [itr, inserted] = set.insert(&obj1);
    REQUIRE(inserted);
    REQUIRE(set.size() == 1);
    REQUIRE(!set.empty());
    REQUIRE(set.begin() != set.end());
    REQUIRE(*set.begin() == &obj1);
}

TEST_CASE("Insert duplicate pointer", "[tinyptrset]") {
    TestObject obj1(1);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    auto [itr, inserted] = set.insert(&obj1);
    REQUIRE(!inserted); // Duplicate should not be inserted
    REQUIRE(set.size() == 1);
}

TEST_CASE("Erase pointer", "[tinyptrset]") {
    TestObject obj1(1);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    REQUIRE(set.size() == 1);
    bool erased = set.erase(&obj1);
    REQUIRE(erased);
    REQUIRE(set.empty());
    REQUIRE(set.size() == 0);
}

TEST_CASE("Insert multiple pointers (large set)", "[tinyptrset]") {
    TestObject obj1(1), obj2(2), obj3(3);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    set.insert(&obj2);
    set.insert(&obj3);
    REQUIRE(set.size() == 3);
    REQUIRE(set.contains(&obj1));
    REQUIRE(set.contains(&obj2));
    REQUIRE(set.contains(&obj3));
}

TEST_CASE("Erase from large set", "[tinyptrset]") {
    TestObject obj1(1), obj2(2), obj3(3);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    set.insert(&obj2);
    set.insert(&obj3);
    REQUIRE(set.size() == 3);
    bool erased = set.erase(&obj2);
    REQUIRE(erased);
    REQUIRE(set.size() == 2);
    REQUIRE(!set.contains(&obj2));
    REQUIRE(set.contains(&obj1));
    REQUIRE(set.contains(&obj3));
}

TEST_CASE("Contains function", "[tinyptrset]") {
    TestObject obj1(1), obj2(2);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    REQUIRE(set.contains(&obj1));
    REQUIRE(!set.contains(&obj2));
}

TEST_CASE("Iterator traversal", "[tinyptrset]") {
    TestObject obj0(0), obj1(1), obj2(2), obj3(3);
    std::set<TestObject*> objects{ &obj0, &obj1, &obj2, &obj3 };
    int const count = GENERATE(0, 1, 2, 3);
    auto itr = objects.begin();
    utl::tinyptrset<TestObject*> set;
    for (int i = 0; i < count; ++i, ++itr) {
        set.insert(*itr);
    }
    CHECK(set.size() == count);
    for (auto itr = set.begin(); itr != set.end(); ++itr) {
        REQUIRE(objects.contains(*itr));
    }
}

TEST_CASE("Move constructor", "[tinyptrset]") {
    TestObject obj1(1), obj2(2);
    utl::tinyptrset<TestObject*> set1;
    set1.insert(&obj1);
    set1.insert(&obj2);
    utl::tinyptrset<TestObject*> set2(std::move(set1));
    REQUIRE(set2.size() == 2);
    REQUIRE(set2.contains(&obj1));
    REQUIRE(set2.contains(&obj2));
    REQUIRE(set1.empty());
}

TEST_CASE("Copy constructor", "[tinyptrset]") {
    TestObject obj1(1), obj2(2);
    utl::tinyptrset<TestObject*> set1;
    set1.insert(&obj1);
    set1.insert(&obj2);
    utl::tinyptrset<TestObject*> set2(set1);
    REQUIRE(set2.size() == 2);
    REQUIRE(set2.contains(&obj1));
    REQUIRE(set2.contains(&obj2));
    REQUIRE(set1.size() == 2);
}

TEST_CASE("Mixed small and large set operations", "[tinyptrset]") {
    TestObject obj1(1), obj2(2);
    utl::tinyptrset<TestObject*> set;
    set.insert(&obj1);
    REQUIRE(set.size() == 1);
    set.insert(&obj2);
    REQUIRE(set.size() == 2);
    REQUIRE(set.contains(&obj1));
    REQUIRE(set.contains(&obj2));
    set.erase(&obj2);
    REQUIRE(set.size() == 1);
    REQUIRE(set.contains(&obj1));
    REQUIRE(!set.contains(&obj2));
}

TEST_CASE("Insert and erase", "[tinyptrset]") {
    utl::tinyptrset<int*> ptrSet;
    // Test inserting duplicate pointers
    int a = 10;
    int* p1 = &a;
    ptrSet.insert(p1);
    CHECK(ptrSet.size() == 1);
    auto [itr, inserted] = ptrSet.insert(p1);
    CHECK(!inserted); // Duplicate should not be inserted
    CHECK(ptrSet.size() == 1);
    // Test inserting null pointer
    ptrSet.insert(nullptr);
    // Null pointer should insertible like any other pointer
    CHECK(ptrSet.size() == 2);
    // Test erasing non-existent pointer
    int b = 20;
    int* p2 = &b;
    CHECK(!ptrSet.erase(p2)); // Should return false
    // Test erasing from an empty set
    utl::tinyptrset<int*> emptySet;
    CHECK(!emptySet.erase(p1)); // Should return false
    // Test multiple inserts and erases
    int c = 30;
    int* p3 = &c;
    ptrSet.insert(p3);
    CHECK(ptrSet.size() == 3);
    CHECK(ptrSet.erase(p1)); // Erase first pointer
    CHECK(ptrSet.size() == 2);
    CHECK(ptrSet.erase(nullptr)); // Erase null pointer
    CHECK(ptrSet.size() == 1);
    // Test iterator behavior after modification
    ptrSet.insert(p1);
    ptrSet.insert(p2);
    // Test copying and moving
    auto copiedSet = ptrSet; // Copy
    CHECK(copiedSet.size() == ptrSet.size());
    CHECK(copiedSet.contains(p1));
    CHECK(copiedSet.contains(p2));
    auto movedSet = std::move(ptrSet); // Move
    // Should have retained the elements
    CHECK(movedSet.size() == copiedSet.size());
    CHECK(ptrSet.empty());   // Original should be empty
}

TEST_CASE("Assignment operators", "[tinyptrset]") {
    int a = 1, b = 2, c = 3;
    utl::tinyptrset<int*> set1;
    utl::tinyptrset<int*> set2;
    SECTION("Copy assignment operator - empty to empty") {
        set1 = set2;
        CHECK(set1.empty());
        CHECK(set2.empty());
    }
    SECTION("Copy assignment operator - small to empty") {
        set1.insert(&a);
        set2 = set1;
        CHECK(set1.size() == 1);
        CHECK(set1.contains(&a));
        CHECK(set2.size() == 1);
        CHECK(set2.contains(&a));
    }
    SECTION("Copy assignment operator - small to large") {
        set1.insert(&a);
        set2.insert(&b);
        set2.insert(&c);
        set2 = set1;
        CHECK(set2.size() == 1);
        CHECK(set2.contains(&a));
        CHECK(!set2.contains(&b));
        CHECK(!set2.contains(&c));
    }
    SECTION("Copy assignment operator - large to small") {
        set1.insert(&a);
        set1.insert(&b);
        set1.insert(&c);
        set2 = set1; // Assign large to small
        CHECK(set2.size() == 3);
        CHECK(set2.contains(&a));
        CHECK(set2.contains(&b));
        CHECK(set2.contains(&c));
    }
    SECTION("Move assignment operator - empty to empty") {
        set1 = std::move(set2); // Should be no-op
        CHECK(set1.empty());
    }
    SECTION("Move assignment operator - small to empty") {
        set1.insert(&a);
        set2 = std::move(set1); // Move small to empty
        CHECK(set2.size() == 1);
        CHECK(set2.contains(&a));
    }
    SECTION("Move assignment operator - large to small") {
        set1.insert(&a);
        set1.insert(&b);
        set1.insert(&c);
        set2 = std::move(set1); // Move large to small
        CHECK(set2.size() == 3);
        CHECK(set2.contains(&a));
        CHECK(set2.contains(&b));
        CHECK(set2.contains(&c));
        CHECK(set1.empty()); // Ensure set1 is now empty
    }
    SECTION("Self-assignment - small") {
        set1.insert(&a);
        set1 = set1; // Self-assign
        CHECK(set1.size() == 1);
        CHECK(set1.contains(&a));
    }
    SECTION("Self-assignment - large") {
        set1.insert(&a);
        set1.insert(&b);
        set1.insert(&c);
        set1 = set1; // Self-assign
        CHECK(set1.size() == 3);
        CHECK(set1.contains(&a));
        CHECK(set1.contains(&b));
        CHECK(set1.contains(&c));
    }
}
