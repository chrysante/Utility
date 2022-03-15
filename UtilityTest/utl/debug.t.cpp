#include "Catch2.hpp"

#define UTL_ASSERT_WITH_EXCEPTIONS
#include <utl/fancy_debug.hpp>

#include "StdoutReroute.hpp"

#define Assert(...) UTL_FANCY_ASSERT("UtilityTest", 2, assertion, __VA_ARGS__)
#define BoundsCheck(index, lower, upper) UTL_FANCY_BOUNDS_CHECK("UtilityTest", 2, index, lower, upper)

TEST_CASE("assertions") {
	utl_test::StdoutReroute _;
	
	CHECK_THROWS([]{
		std::size_t i = 19;
		BoundsCheck(i, 0, 10);
	}());
	CHECK_THROWS([]{
		long i = -9;
		BoundsCheck(i, 0, 10);
	}());
	
	CHECK_NOTHROW([]{
		std::size_t i = 9;
		BoundsCheck(i, 0, 10);
	}());
	
	CHECK_THROWS([]{
		int i = 0;
		Assert(i > 0, "i must be positive");
	}());
	
	CHECK_NOTHROW([]{
		int i = 0;
		Assert(i == 0, "i must be zero");
	}());
	
	CHECK_THROWS([]{
		int i = 0;
		Assert(_default, i > 0, "i must be positive");
	}());
	
	CHECK_NOTHROW([]{
		int i = 0;
		Assert(_default, i == 0, "i must be zero");
	}());
	
	CHECK_THROWS([]{
		int i = 0;
		Assert(audit, i > 0, "i must be positive");
	}());
	
	CHECK_NOTHROW([]{
		int i = 0;
		Assert(audit, i == 0, "i must be zero");
	}());
	
}

