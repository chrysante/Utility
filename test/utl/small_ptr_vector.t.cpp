#include <optional>

#include <catch/catch2.hpp>

#include "utl/small_ptr_vector.hpp"

TEST_CASE("small_ptr_vector constructor") {
    SECTION("default") {
        utl::small_ptr_vector<int*> v;
        CHECK(v.empty());
        CHECK(v.size() == 0);
    }
    SECTION("count value") {
        size_t count = GENERATE(0, 1, 2, 5);
        utl::small_ptr_vector<int*> v(count);
        CHECK(v.empty() == (count == 0));
        CHECK(v.size() == count);
        SECTION("copy") {
            auto w = v;
            CHECK(v.empty() == w.empty());
            CHECK(v.size() == w.size());
        }
        SECTION("move") {
            auto w = std::move(v);
            CHECK(w.empty() == (count == 0));
            CHECK(w.size() == count);
            CHECK(v.size() <= 1);
        }
    }
}
