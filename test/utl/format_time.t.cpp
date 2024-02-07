#include <catch2/catch_test_macros.hpp>
#include <utl/format_time.hpp>

TEST_CASE("format_time") {
    using namespace std::chrono_literals;
    CHECK(utl::format_duration(0s) == "0");
    CHECK(utl::format_duration(1s) == "1s");
    CHECK(utl::format_duration(10s) == "10s");
    CHECK(utl::format_duration(60s) == "1m");
    CHECK(utl::format_duration(3601s) == "1h:1s");
}
