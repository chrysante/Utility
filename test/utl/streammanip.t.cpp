#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <utl/streammanip.hpp>

namespace {

inline constexpr auto myManip =
    utl::streammanip([](std::ostream& str) { str << "manip"; });

inline constexpr auto myManip2 =
    utl::streammanip([](std::ostream& str, int i, int j) { str << i << j; });

} // namespace

TEST_CASE("streammanip", "") {
    std::stringstream sstr;
    sstr << myManip;
    CHECK(sstr.str() == "manip");
}

TEST_CASE("streammanip - 2", "") {
    std::stringstream sstr;
    sstr << myManip2(2, 5);
    CHECK(sstr.str() == "25");
}
