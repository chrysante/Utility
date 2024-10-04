#include <catch2/catch_test_macros.hpp>

#include <utl/metric_table.hpp>

TEST_CASE("Levenshtein distance", "[metric_map]") {
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

TEST_CASE("metric_map 1", "[metric_map]") {
    utl::metric_set<std::string> tree;

    // Test 1: Insert a single element and verify it exists
    tree.insert("apple");
    auto results = tree.lookup((char const*)"apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apple");

    // Test 2: Insert another element and verify
    tree.insert("banana");
    results = tree.lookup("banana", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "banana");

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
    CHECK(results[0]->key() == "grapefruit");

    // Test 6: Verify that lookup returns correct nodes with varying thresholds
    tree.insert("mango");
    results =
        tree.lookup("mango", 1); // Looking for "mango" with a threshold of 1
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "mango");

    // Test 7: Lookup with a higher threshold to include more nodes
    results = tree.lookup("mang", 1); // Should return "mango"
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "mango");
}

TEST_CASE("metric_map 2", "[metric_map]") {
    struct Traits: utl::metric_map_traits<std::string, int> {
        static void update(int& existingValue, int newValue) {
            existingValue += newValue;
        }
    };

    utl::metric_map<std::string, int, Traits> tree;

    // Test 1: Insert unique words
    tree.insert("apple", 1);
    tree.insert("banana", 1);
    tree.insert("cherry", 1);

    // Test 2: Lookup exact matches
    auto results = tree.lookup("apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apple");

    // Test 3: Lookup with no matches
    results = tree.lookup("orange", 0);
    CHECK(results.empty());

    // Test 4: Lookup with threshold allowing for one edit
    results = tree.lookup("appl", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apple");

    // Test 5: Insert with merging values (same name)
    tree.insert("apple", 2); // Merging with the existing "apple"
    results = tree.lookup("apple", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apple");
    CHECK(results[0]->value() == 3); // 1 (initial) + 2 (new) = 3

    // Test 6: Lookup with threshold allowing for two edits
    results = tree.lookup("apples", 2);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apple");

    // Test 7: Insert another similar word and check merging
    tree.insert("apples", 1);
    results = tree.lookup("apples", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "apples");

    // Test 8: Check merging on a different word with the same distance
    tree.insert("cherry", 2); // Should merge with "cherry"
    results = tree.lookup("chery", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "cherry");
    CHECK(results[0]->value() == 3);

    // Test 9: Insert a new word that is further away
    tree.insert("grape", 1);
    results = tree.lookup("grape", 1);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "grape");

    // Test 10: Inserting multiple words with the same distance
    tree.insert("mango", 1);
    tree.insert("mangoes", 1);
    results = tree.lookup("mangoes", 0);
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "mangoes");

    // Test 11: Check lookup with threshold larger than actual edit distance
    results = tree.lookup("bananna", 2); // Should match "banana"
    REQUIRE(results.size() == 1);
    CHECK(results[0]->key() == "banana");

    // Test 12: Edge case for empty tree
    utl::metric_map<std::string, int, Traits> emptyTree;
    results = emptyTree.lookup("anything", 1);
    CHECK(results.empty());
}

namespace {

/// Simple metric for testing: counts how many bits differ between two numbers
struct HammingDistance {
    static size_t distance(uint32_t a, uint32_t b) {
        return std::bitset<32>(a ^ b).count();
    }

    void update(auto& existing, auto&& repl) {
        existing = std::forward<decltype(repl)>(repl);
    }
};

} // namespace

TEST_CASE("BK-tree Hamming Distance Metric Set - Insert and Lookup",
          "[bktree]") {
    using Tree = utl::metric_set<uint32_t, HammingDistance>;

    Tree tree = {
        3,  // 0011
        5,  // 0101
        8,  // 1000
        15, // 1111
    };

    SECTION("Exact match lookup") {
        auto result = tree.lookup(3, 0); // Exact match for 3
        REQUIRE(result.size() == 1);
        CHECK(result[0]->key() == 3);

        result = tree.lookup(15, 0); // Exact match for 15
        REQUIRE(result.size() == 1);
        CHECK(result[0]->key() == 15);
    }

    SECTION("Hamming distance within threshold") {
        auto result =
            tree.lookup(3, 2); // Numbers with at most 2 bit difference
        CHECK(
            result.size() ==
            3); // 3 (exact match), 5 (2 bits different), 15 (2 bits different)

        result = tree.lookup(8, 2); // Numbers with at most 2 bit differences
        CHECK(result.size() == 1);  // 8 and 15 (2 bit differences)
    }

    SECTION("Hamming distance outside threshold") {
        auto result = tree.lookup(3, 0); // Exact match
        CHECK(result.size() == 1);

        result = tree.lookup(0, 3); // Numbers with at most 3 bit differences
        CHECK(result.size() == 3);  // 3, 8, 5
    }
}

TEST_CASE("BK-tree Hamming Distance Metric Map - Insert and Lookup",
          "[bktree]") {
    using Tree = utl::metric_map<uint32_t, std::string, HammingDistance>;

    Tree tree = { { 3, "three" },
                  { 5, "five" },
                  { 8, "eight" },
                  { 15, "fifteen" } };

    SECTION("Exact match lookup") {
        auto result = tree.lookup(3, 0); // Exact match for key 3
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == 3);
        REQUIRE(result[0]->value() == "three");

        result = tree.lookup(8, 0); // Exact match for key 8
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == 8);
        REQUIRE(result[0]->value() == "eight");
    }

    SECTION("Hamming distance within threshold") {
        auto result =
            tree.lookup(3, 1); // Find key with at most 1 bit difference
        REQUIRE(result.size() == 1);
        CHECK(result[0]->key() == 3);
        CHECK(result[0]->value() == "three");
    }

    SECTION("Insert same key with updated value") {
        tree.insert(3, "new_three");
        auto result = tree.lookup(3, 0);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == 3);
        REQUIRE(result[0]->value() == "new_three");
    }
}

namespace {

/// Manhattan Distance metric for 2D integer grid points (x, y)
struct ManhattanDistance {
    static size_t distance(std::pair<int, int> const& a,
                           std::pair<int, int> const& b) {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second);
    }

    static void update(std::string& a, std::string&& b) { a = std::move(b); }
};

} // namespace

TEST_CASE("BK-tree Manhattan Distance Metric Set - Insert and Lookup",
          "[BKTree]") {
    using Point2D = std::pair<int, int>;
    using Tree = utl::metric_set<Point2D, ManhattanDistance>;

    Tree tree = { { 0, 0 }, { 2, 3 }, { 5, 5 }, { 10, 10 } };

    SECTION("Exact match lookup") {
        auto result = tree.lookup({ 0, 0 }, 0); // Exact match for (0,0)
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == std::make_pair(0, 0));

        result = tree.lookup({ 5, 5 }, 0); // Exact match for (5,5)
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == std::make_pair(5, 5));
    }

    SECTION("Manhattan distance within threshold") {
        auto result =
            tree.lookup({ 0, 0 },
                        5); // Points within Manhattan distance of 5 from (0,0)
        REQUIRE(result.size() == 2); // (0,0) and (2,3)

        result = tree.lookup({ 5, 6 }, 10); // Points within Manhattan distance
                                            // of 10 from (5,5)
        REQUIRE(result.size() == 3);        // (5,5), (2,3), and (10,10)
    }

    SECTION("Manhattan distance outside threshold") {
        auto result =
            tree.lookup({ 0, 0 },
                        2); // Points within Manhattan distance of 2 from (0,0)
        REQUIRE(result.size() == 1); // Only (0,0)

        result =
            tree.lookup({ 5, 5 },
                        3); // Points within Manhattan distance of 3 from (5,5)
        REQUIRE(result.size() == 1); // Only (5,5)
    }
}

TEST_CASE("BK-tree Manhattan Distance Metric Map - Insert and Lookup",
          "[BKTree]") {
    using Point2D = std::pair<int, int>;
    using Tree = utl::metric_map<Point2D, std::string, ManhattanDistance>;

    Tree tree;

    // Insert some key-value pairs into the BK-tree
    REQUIRE(tree.insert({ 0, 0 }, "origin"));
    REQUIRE(tree.insert({ 2, 3 }, "nearby"));
    REQUIRE(tree.insert({ 5, 5 }, "midpoint"));
    REQUIRE(tree.insert({ 10, 10 }, "farpoint"));

    SECTION("Exact match lookup") {
        auto result = tree.lookup({ 0, 0 }, 0); // Exact match for (0,0)
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == std::make_pair(0, 0));
        REQUIRE(result[0]->value() == "origin");

        result = tree.lookup({ 10, 10 }, 0); // Exact match for (10,10)
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == std::make_pair(10, 10));
        REQUIRE(result[0]->value() == "farpoint");
    }

    SECTION("Manhattan distance within threshold") {
        auto result =
            tree.lookup({ 0, 0 },
                        5); // Points within Manhattan distance of 5 from (0,0)
        REQUIRE(result.size() == 2); // (0,0) and (2,3)
        REQUIRE(result[0]->key() == std::make_pair(0, 0));
        REQUIRE(result[0]->value() == "origin");
        REQUIRE(result[1]->key() == std::make_pair(2, 3));
        REQUIRE(result[1]->value() == "nearby");
    }

    SECTION("Insert same key with updated value") {
        tree.insert({ 0, 0 }, "new_origin");
        auto result = tree.lookup({ 0, 0 }, 0);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0]->key() == std::make_pair(0, 0));
        REQUIRE(result[0]->value() == "new_origin");
    }
}

TEST_CASE("BKTree lookup extreme", "[bktree]") {
    utl::metric_set<std::string> tree;
    tree.insert("test");
    tree.insert("best");
    tree.insert("rest");
    tree.insert("nest");

    // Check with zero threshold (should find only the exact match)
    auto exact_match = tree.lookup("best", 0);
    REQUIRE(exact_match.size() == 1);
    CHECK(exact_match.front()->key() == "best");

    // Check with threshold of one (should find everything)
    auto all_matches = tree.lookup("best", 1);
    CHECK(all_matches.size() == 4); // All strings should be found
}
