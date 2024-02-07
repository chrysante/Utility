#include <catch2/catch_test_macros.hpp>
#include <utl/common.hpp>

TEST_CASE("utl::type_sequence") {
    CHECK(utl::type_sequence<int, float, long>::unique);
    CHECK(utl::type_sequence<int, float, long>::index_of<int> == 0);
    CHECK(utl::type_sequence<int, float, long>::index_of<float> == 1);
    CHECK(utl::type_sequence<int, float, long>::index_of<char> == -1);
}
