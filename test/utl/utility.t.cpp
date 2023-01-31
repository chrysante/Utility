#include <catch/catch2.hpp>

#include <utl/utility.hpp>

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

} // namespace

TEST_CASE("narrow_cast unsigned to unsigned", "[utility][narrow_cast]") {
	CHECK_THROWS (testNarrowCast<std::uint8_t>(5'000'000'000ul));
	CHECK_THROWS (testNarrowCast<std::uint8_t>(66'000u));
	CHECK_THROWS (testNarrowCast<std::uint8_t>(512u));
	CHECK_NOTHROW(testNarrowCast<std::uint8_t>(255u));
	
	CHECK_THROWS (testNarrowCast<std::uint16_t>(5'000'000'000ul));
	CHECK_THROWS (testNarrowCast<std::uint16_t>(66'000u));
	CHECK_NOTHROW(testNarrowCast<std::uint16_t>(512u));
	CHECK_NOTHROW(testNarrowCast<std::uint16_t>(255u));
	
	CHECK_THROWS (testNarrowCast<std::uint32_t>(5'000'000'000ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(66'000ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(512ul));
	CHECK_NOTHROW(testNarrowCast<std::uint32_t>(255ul));
}

TEST_CASE("narrow_cast signed to signed", "[utility][narrow_cast]") {	
	/// Positive
	CHECK_THROWS (testNarrowCast<std::int8_t>(5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int8_t>(66'000));
	CHECK_THROWS (testNarrowCast<std::int8_t>(512));
	CHECK_NOTHROW(testNarrowCast<std::int8_t>(127));
	
	CHECK_THROWS (testNarrowCast<std::int16_t>(5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int16_t>(66'000));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(512));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(255));
	
	CHECK_THROWS (testNarrowCast<std::int32_t>(5'000'000'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(32'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(512l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(255l));
	
	/// Negative
	CHECK_THROWS (testNarrowCast<std::int8_t>(-5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int8_t>(-66'000));
	CHECK_THROWS (testNarrowCast<std::int8_t>(-512));
	CHECK_NOTHROW(testNarrowCast<std::int8_t>(-127));
	
	CHECK_THROWS (testNarrowCast<std::int16_t>(-5'000'000'000l));
	CHECK_THROWS (testNarrowCast<std::int16_t>(-66'000));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(-512));
	CHECK_NOTHROW(testNarrowCast<std::int16_t>(-255));
	
	CHECK_THROWS (testNarrowCast<std::int32_t>(-5'000'000'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-32'000l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-512l));
	CHECK_NOTHROW(testNarrowCast<std::int32_t>(-255l));
}

