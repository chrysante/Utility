#include "Catch2.hpp"

#include <utl/iterator.hpp>
#include <vector>
#include <utl/common.hpp>

TEST_CASE("conversion_iterator") {
	std::vector<int> const v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int test = 1;
	for (auto i = utl::conversion_iterator(v.begin(), [](int i) { return i + 1; }); i != v.end(); ++i) {
		CHECK(*i == test);
		++test;
	}
}

TEST_CASE("stride_iterator") {
	std::vector<int> const v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int test = 0;
	for (auto i = utl::stride_iterator(v.begin(), 2); i != v.end(); ++i) {
		CHECK(*i == test);
		test += 2;
	}
}

TEST_CASE("stride_iterator(conversion_iterator)") {
	std::vector<int> const v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	auto stride_itr = utl::stride_iterator(v.begin(), 2);
	auto conv_itr = utl::conversion_iterator(stride_itr, [](int i) { return i + 1; });

	int test = 1;
	for (auto i = conv_itr; i != v.end(); ++i) {
		CHECK(*i == test);
		test += 2;
	}
}

TEST_CASE("stride_iterator fail") {
	std::vector<int> const v = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	CHECK_THROWS([&, test = 0]() mutable {
		for (auto i = utl::stride_iterator(v.begin(), 2); i != v.end(); ++i) {
			if (i.get_underlying_iterator() > v.end()) {
				throw std::runtime_error("past the end");
			}
			CHECK(*i == test);
			test += 2;
		}
	}());
}
