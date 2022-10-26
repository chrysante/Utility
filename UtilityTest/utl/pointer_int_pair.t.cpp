#include "Catch2.hpp"

#include <cstdint>

#include <utl/utility.hpp>

TEST_CASE("pointer_int_pair - int", "[utility]") {
    using i64 = std::int64_t;
    utl::pointer_int_pair<i64*, int> p;
    i64 value;
    p.pointer(&value);
    int const intValue = GENERATE(-4, 0, 3);
    p.integer(intValue);
    CHECK(p.pointer() == &value);
    CHECK(p.integer() == intValue);
    static_assert(sizeof(p) == sizeof(i64*));
}

TEST_CASE("pointer_int_pair", "[utility]") {
    using i16 = std::int16_t;
    utl::pointer_int_pair<i16*, bool> p;
    i16 value;
    p.pointer(&value);
    bool const boolValue = GENERATE(false, true);
    p.integer(boolValue);
    CHECK(p.pointer() == &value);
    CHECK(p.integer() == boolValue);
    static_assert(sizeof(p) == sizeof(i16*));
}
