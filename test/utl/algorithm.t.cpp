//#include <catch/catch2.hpp>
//
//#include "utl/algorithm.hpp"
//
//
//#include <vector>
//
//TEST_CASE("for_each") {
//	
//	std::vector const v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	std::vector const w = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
//	
//	if (auto acc = 0; utl::find_if([&](auto index, auto v, auto w) -> bool {
//		CHECK(v == index);
//		CHECK(w == index + 10);
//		acc += v;
//		return (v == 5);
//	}, v, w)) {
//		CHECK(true);
//		CHECK(acc == 15);
//	}
//	
//	if (utl::find_if<utl::backward>([](auto index, auto v, auto w) -> bool {
//		CHECK(v == index);
//		CHECK(w == index + 10);
//		return (v == 5);
//	}, v, w)) {
//		CHECK(true);
//	}
//	else {
//		CHECK(false);
//	}
//	
//	CHECK(utl::find_if([index = 0](auto i, auto j) mutable -> bool {
//		CHECK(index == i);
//		CHECK(index == j - 10);
//		++index;
//		if (i > 6)
//			return true;
//		else
//			return false;
//	}, v, w));
//	
//}
