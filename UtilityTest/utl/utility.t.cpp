#define UTL_INTERNAL_ASSERT_WITH_EXCEPTIONS 1

#include "Catch2.hpp"
#include "StdoutReroute.hpp"
#include <utl/utility.hpp>
#include <utl/concepts.hpp>
#include <vector>
#include <random>

static auto makeTestData(std::size_t count, utl::invocable<std::mt19937_64&> auto f) {
	std::mt19937_64 rng(std::random_device{}());
	using T = std::invoke_result_t<decltype(f), decltype((rng))>;
	std::vector<T> result;
	result.reserve(512);
	for (int i = 0; i < count; ++i) {
		result.push_back(f(rng));
	}
	return result;
}

TEMPLATE_TEST_CASE("log2", "", int, long, unsigned int, unsigned long) {
	auto const digits = std::numeric_limits<TestType>::digits;
	auto const data = makeTestData(512, [dist = std::uniform_int_distribution<TestType>(0, digits - 1)](auto& rng) mutable {
		return dist(rng);
	});
	
	for (auto x : data) {
		CHECK(utl::log2(TestType(1) << x) == x);
	}
}

TEMPLATE_TEST_CASE("ipow", "", long) {
	std::uniform_int_distribution<TestType> distBase(0, 30);
	std::uniform_int_distribution<int> distExp(0, 10);
	auto const data = makeTestData(512, [&](auto& rng) {
		return std::pair(distBase(rng), distExp(rng));
	});
	
	for (auto [base, exp] : data) {
		CHECK(utl::ipow(base, exp) == (TestType)std::pow(base, exp));
	}
}

#if 0
TEST_CASE("narrow_cast unsigned to unsigned", "[narrow_cast]") {
	utl_test::StdoutReroute _;
	
	CHECK_THROWS (utl::narrow_cast<utl::uint8_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::uint8_t>(5'000'000'000ul));
	CHECK_THROWS (utl::narrow_cast<std::uint8_t>(66'000u));
	CHECK_THROWS (utl::narrow_cast<std::uint8_t>(512u));
	CHECK_NOTHROW(utl::narrow_cast<std::uint8_t>(255u));
	
	CHECK_THROWS (utl::narrow_cast<utl::uint16_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::uint16_t>(5'000'000'000ul));
	CHECK_THROWS (utl::narrow_cast<std::uint16_t>(66'000u));
	CHECK_NOTHROW(utl::narrow_cast<std::uint16_t>(512u));
	CHECK_NOTHROW(utl::narrow_cast<std::uint16_t>(255u));
	
	CHECK_THROWS (utl::narrow_cast<utl::uint32_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::uint32_t>(5'000'000'000ul));
	CHECK_NOTHROW(utl::narrow_cast<std::uint32_t>(66'000ul));
	CHECK_NOTHROW(utl::narrow_cast<std::uint32_t>(512ul));
	CHECK_NOTHROW(utl::narrow_cast<std::uint32_t>(255ul));
	
	CHECK_THROWS (utl::narrow_cast<utl::uint64_t>((utl::uint128_t)std::numeric_limits<std::uint64_t>::max() + 1));
	CHECK_NOTHROW(utl::narrow_cast<std::uint64_t>((utl::uint128_t)5'000'000'000ull));
	CHECK_NOTHROW(utl::narrow_cast<std::uint64_t>((utl::uint128_t)66'000ull));
	CHECK_NOTHROW(utl::narrow_cast<std::uint64_t>((utl::uint128_t)512ull));
	CHECK_NOTHROW(utl::narrow_cast<std::uint64_t>((utl::uint128_t)255ull));
}

TEST_CASE("narrow_cast signed to signed", "[narrow_cast]") {
	utl_test::StdoutReroute _;
	
	// positive
	CHECK_THROWS (utl::narrow_cast<utl::int8_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(5'000'000'000l));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(66'000));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(512));
	CHECK_NOTHROW(utl::narrow_cast<std::int8_t>(127));
	
	CHECK_THROWS (utl::narrow_cast<utl::int16_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::int16_t>(5'000'000'000l));
	CHECK_THROWS (utl::narrow_cast<std::int16_t>(66'000));
	CHECK_NOTHROW(utl::narrow_cast<std::int16_t>(512));
	CHECK_NOTHROW(utl::narrow_cast<std::int16_t>(255));
	
	CHECK_THROWS (utl::narrow_cast<utl::int32_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_THROWS (utl::narrow_cast<std::int32_t>(5'000'000'000l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(32'000l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(512l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(255l));
	
	CHECK_THROWS (utl::narrow_cast<utl::int64_t>((utl::int128_t)std::numeric_limits<std::int64_t>::max() + 1));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)2'400'000'000ll));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)66'000ull));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)512ull));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)255ull));
	
	// negative
	CHECK_THROWS (utl::narrow_cast<utl::int8_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(-5'000'000'000l));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(-66'000));
	CHECK_THROWS (utl::narrow_cast<std::int8_t>(-512));
	CHECK_NOTHROW(utl::narrow_cast<std::int8_t>(-127));
	
	CHECK_THROWS (utl::narrow_cast<utl::int16_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (utl::narrow_cast<std::int16_t>(-5'000'000'000l));
	CHECK_THROWS (utl::narrow_cast<std::int16_t>(-66'000));
	CHECK_NOTHROW(utl::narrow_cast<std::int16_t>(-512));
	CHECK_NOTHROW(utl::narrow_cast<std::int16_t>(-255));
	
	CHECK_THROWS (utl::narrow_cast<utl::int32_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_THROWS (utl::narrow_cast<std::int32_t>(-5'000'000'000l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(-32'000l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(-512l));
	CHECK_NOTHROW(utl::narrow_cast<std::int32_t>(-255l));
	
	CHECK_THROWS (utl::narrow_cast<utl::int64_t>((utl::int128_t)std::numeric_limits<std::int64_t>::min() - 1));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)-2'400'000'000ll));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)-66'000ll));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)-512ll));
	CHECK_NOTHROW(utl::narrow_cast<std::int64_t>((utl::int128_t)-255ll));
}
#endif
