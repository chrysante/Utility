#include "Catch2.hpp"

#include <utl/utility.hpp>

#include "StdoutReroute.hpp"

namespace {

struct ThrowTraits {
    static void check(bool value) {
        if (!value) {
            throw std::runtime_error("Check failed");
        }
    }
};

template <std::integral To, std::integral From>
To testNarrowCast(From value) {
    return utl::narrow_cast<To, ThrowTraits>(value);
}

}

TEST_CASE("narrow_cast unsigned to unsigned", "[utility][narrow_cast]") {
	utl_test::StdoutReroute _;
	
	CHECK_THROWS (testNarrowCast<utl::uint8_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::uint8_t>(5'000'000'000ul));
	CHECK_THROWS (testNarrowCast<std::uint8_t>(66'000u));
	CHECK_THROWS (testNarrowCast<std::uint8_t>(512u));
	CHECK_NOTHROW(testNarrowCast<std::uint8_t>(255u));
	
	CHECK_THROWS (testNarrowCast<utl::uint16_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::uint16_t>(5'000'000'000ul));
	CHECK_THROWS (testNarrowCast<std::uint16_t>(66'000u));
	CHECK_NOTHROW(testNarrowCast<std::uint16_t>(512u));
	CHECK_NOTHROW(testNarrowCast<std::uint16_t>(255u));
	
	CHECK_THROWS (testNarrowCast<utl::uint32_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::uint32_t>(5'000'000'000ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(66'000ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(512ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(255ul));
	
    CHECK_THROWS (testNarrowCast<utl::uint64_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_NOTHROW(testNarrowCast<std::uint64_t>((utl::uint128_t)5'000'000'000ull));
	CHECK_NOTHROW(testNarrowCast<std::uint64_t>((utl::uint128_t)66'000ull));
	CHECK_NOTHROW(testNarrowCast<std::uint64_t>((utl::uint128_t)512ull));
	CHECK_NOTHROW(testNarrowCast<std::uint64_t>((utl::uint128_t)255ull));
}

TEST_CASE("narrow_cast signed to signed", "[utility][narrow_cast]") {
	utl_test::StdoutReroute _;
	
	/// Positive
	CHECK_THROWS (testNarrowCast<utl::int8_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::int8_t>(5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int8_t>(66'000));
	CHECK_THROWS (testNarrowCast<std::int8_t>(512));
	CHECK_NOTHROW(testNarrowCast<std::int8_t>(127));
	
	CHECK_THROWS (testNarrowCast<utl::int16_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::int16_t>(5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int16_t>(66'000));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(512));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(255));
	
	CHECK_THROWS (testNarrowCast<utl::int32_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (testNarrowCast<std::int32_t>(5'000'000'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(32'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(512l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(255l));
	
	CHECK_THROWS (testNarrowCast<utl::int64_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)2'400'000'000ll));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)66'000ull));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)512ull));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)255ull));
	
	/// Negative
	CHECK_THROWS (testNarrowCast<utl::int8_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (testNarrowCast<std::int8_t>(-5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int8_t>(-66'000));
	CHECK_THROWS (testNarrowCast<std::int8_t>(-512));
	CHECK_NOTHROW(testNarrowCast<std::int8_t>(-127));
	
	CHECK_THROWS (testNarrowCast<utl::int16_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (testNarrowCast<std::int16_t>(-5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int16_t>(-66'000));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(-512));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(-255));
	
	CHECK_THROWS (testNarrowCast<utl::int32_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (testNarrowCast<std::int32_t>(-5'000'000'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-32'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-512l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-255l));
	
	CHECK_THROWS (testNarrowCast<utl::int64_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)-2'400'000'000ll));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)-66'000ll));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)-512ll));
	CHECK_NOTHROW(testNarrowCast<std::int64_t>((utl::int128_t)-255ll));
}

