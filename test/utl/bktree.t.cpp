#include <catch2/catch_test_macros.hpp>

#include <utl/bktree.hpp>

TEST_CASE("Levenshtein distance", "[bktree]") {
    auto test = [](std::string_view s1, std::string_view s2, size_t result) {
        CHECK(utl::levenshtein_distance(s1, s2) == result);
        CHECK(utl::levenshtein_distance(s2, s1) == result);
    };
    test("test", "test", 0);
    test("abc", "xyz", 3);
    test("", "hello", 5);
    test("kitten", "sitting", 3);
    test("flaw", "flap", 1);
    test("book", "books", 1);
    test("cats", "cat", 1);
    test("", "", 0);
    test("abcde", "fghij", 5);
    test("abcdefghabcdefghabcdefgh", "a", 23);
}

TEST_CASE("bktree 1", "[bktree]") {
    utl::bktree<int> tree;

    // Test 1: Insert a single element and verify it exists
    tree.insert("apple");
    auto results = tree.lookup("apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apple");

    // Test 2: Insert another element and verify
    tree.insert("banana");
    results = tree.lookup("banana", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "banana");

    // Test 3: Insert multiple elements with similar names
    tree.insert("apply");
    tree.insert("applx");
    results = tree.lookup("appl", 1);
    CHECK(results.size() == 3); // "apple", "apply", "applx"

    // Test 4: Check for non-existing elements
    results = tree.lookup("orange", 0); // Should return empty
    CHECK(results.empty());

    // Test 5: Check distance threshold
    tree.insert("grapefruit");
    results = tree.lookup("grapefruyd",
                          2); // Should return "grape" within distance of 2
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "grapefruit");

    // Test 6: Verify that lookup returns correct nodes with varying thresholds
    tree.insert("mango");
    results =
        tree.lookup("mango", 1); // Looking for "mango" with a threshold of 1
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "mango");

    // Test 7: Lookup with a higher threshold to include more nodes
    results = tree.lookup("mang", 1); // Should return "mango"
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "mango");
}

TEST_CASE("bktree 2", "[bktree]") {
    struct Traits: utl::bktree_traits<int> {
        static void update(int& existingValue, int newValue) {
            existingValue += newValue;
        }
    };

    utl::bktree<int, Traits> tree;

    // Test 1: Insert unique words
    tree.insert("apple", 1);
    tree.insert("banana", 1);
    tree.insert("cherry", 1);

    // Test 2: Lookup exact matches
    auto results = tree.lookup("apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apple");

    // Test 3: Lookup with no matches
    results = tree.lookup("orange", 0);
    CHECK(results.empty());

    // Test 4: Lookup with threshold allowing for one edit
    results = tree.lookup("appl", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apple");

    // Test 5: Insert with merging values (same name)
    tree.insert("apple", 2); // Merging with the existing "apple"
    results = tree.lookup("apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apple");
    CHECK(results[0]->value() == 3); // 1 (initial) + 2 (new) = 3

    // Test 6: Lookup with threshold allowing for two edits
    results = tree.lookup("apples", 2);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apple");

    // Test 7: Insert another similar word and check merging
    tree.insert("apples", 1);
    results = tree.lookup("apples", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "apples");

    // Test 8: Check merging on a different word with the same distance
    tree.insert("cherry", 2); // Should merge with "cherry"
    results = tree.lookup("chery", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "cherry");
    CHECK(results[0]->value() == 3);

    // Test 9: Insert a new word that is further away
    tree.insert("grape", 1);
    results = tree.lookup("grape", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "grape");

    // Test 10: Inserting multiple words with the same distance
    tree.insert("mango", 1);
    tree.insert("mangoes", 1);
    results = tree.lookup("mangoes", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "mangoes");

    // Test 11: Check lookup with threshold larger than actual edit distance
    results = tree.lookup("bananna", 2); // Should match "banana"
    REQUIRE(results.size() == 1);
    CHECK(results[0]->name() == "banana");

    // Test 12: Edge case for empty tree
    utl::bktree<int, Traits> emptyTree;
    results = emptyTree.lookup("anything", 1);
    CHECK(results.empty());
}
