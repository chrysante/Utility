#include "Catch2.hpp"

#include <utl/__common.hpp>

TEST_CASE("utl::iota") {
	int j = 0;
	for (int i: utl::iota(0, 10)) {
		CHECK(i == j++);
	}
}
