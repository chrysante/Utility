#include <catch2/catch_test_macros.hpp>
#include <utl/hashtable.hpp>

TEST_CASE("Instantiate node_hashmap", "[hashtable]") {
    utl::node_hashmap<int, int> map;
    (void)map;
}
