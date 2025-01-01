#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <utl/callback_iterator.hpp>

TEST_CASE(".", "[callback_iterator]") {
    std::vector<int> values;
    utl::callback_iterator it([&](int i) { values.push_back(i); });
    static_assert(std::output_iterator<decltype(it), int>);
    *it = 0;
    *it = 42;
    *it = 7;
    CHECK(values == std::vector{ 0, 42, 7 });
}
