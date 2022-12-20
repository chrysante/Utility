#include <catch/catch2.hpp>

#include "utl/lazy.hpp"
#include <optional>

TEST_CASE("utl::lazy") {
	auto x = utl::lazy([]{
		return 4;
	});
	auto y = utl::lazy([]{
		return 5;
	});
	auto z = x * y;
	CHECK(z == 20);
}

TEST_CASE("utl::lazy, optional") {
	std::optional<int> const i = 0;
	bool test = true;
	int const j = i.value_or(utl::lazy([&]{ test = false; return 1; }));
	CHECK(j == 0);
	CHECK(test);
}
