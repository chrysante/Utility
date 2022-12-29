#include <catch/catch2.hpp>

#include <utl/streammanip.hpp>

#include <sstream>
#include <string>

namespace {

inline constexpr auto myManip = utl::streammanip([](std::ostream& str) { str << "manip"; });

inline constexpr auto myManip2 = utl::streammanip([](std::ostream& str, int i, int j) { str << i << j; });

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

