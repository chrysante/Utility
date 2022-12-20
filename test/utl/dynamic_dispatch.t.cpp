#include <catch/catch2.hpp>

#include "utl/dynamic_dispatch.hpp"

TEST_CASE("utl::dispatch") {
	
	utl::dispatch(utl::dispatch_arg(1, int{0}, float{1}, char{2}),
				  utl::dispatch_arg(2, int{0}, float{1}, char{2}),
				  utl::dispatch_range<4>(3),
				  utl::dispatch_range<4>(0),
				  utl::dispatch_condition(true),
				  [](auto type_a,
					 auto type_b,
					 auto index_a,
					 auto index_b,
					 auto condition) {
		CHECK(std::is_same_v<decltype(type_a), float>);
		CHECK(std::is_same_v<decltype(type_b), char>);
		CHECK(decltype(index_a)::value == 3);
		CHECK(decltype(index_b)::value == 0);
		CHECK(decltype(condition)::value);
	});

	auto l1 = []{ return -1; };
	auto l2 = []{ return 0; };
	
	utl::dispatch(utl::dispatch_arg(0, l1, l2),
				  [](auto l) {
		CHECK(l() == -1);
	});

}
