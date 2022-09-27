#include "Catch2.hpp"

#include <utl/common.hpp>

TEST_CASE("utl::type_sequence") {
	
	CHECK(utl::type_sequence<int, float, long>::unique);
	CHECK(utl::type_sequence<int, float, long>::index_of<int> == 0);
	CHECK(utl::type_sequence<int, float, long>::index_of<float> == 1);
	CHECK(utl::type_sequence<int, float, long>::index_of<char> == -1);
	
}

TEST_CASE("utl::iota") {
	
	for (int j = 0; int i: utl::iota(0, 10)) {
		CHECK(i == j++);
	}
	
	for (int j = -10; int i: utl::iota(-10, 10)) {
		CHECK(i == j++);
	}
	
}

//TEST_CASE("utl::any_of/all_of") {
//	CHECK(9 == utl::any_of{ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//	CHECK(9 != utl::any_of{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });
//	
//	CHECK(9 == utl::all_of{ 9, 9, 9, 9 });
//	CHECK(9 != utl::all_of{ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//}


