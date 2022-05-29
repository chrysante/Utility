#include "Catch2.hpp"
#include "utl/vector.hpp"


TEST_CASE("vector-erase") {
	SECTION("all") {
		utl::vector<int> v = { 0, 1, 2, 3 };
		auto result = v.erase(v.begin(), v.end());
		CHECK(result == v.end());
		CHECK(v.empty());
	}
	
	SECTION("begin range") {
		utl::vector<int> v = { 0, 1, 2, 3 };
		auto result = v.erase(v.begin(), v.begin() + 2);
		CHECK(result == v.begin());
		CHECK(v.size() == 2);
		CHECK(v == utl::vector<int>{ 2, 3 });
	}
	
	SECTION("end range") {
		utl::vector<int> v = { 0, 1, 2, 3, 4 };
		auto result = v.erase(v.begin() + 3, v.end());
		CHECK(result == v.end());
		CHECK(v.size() == 3);
		CHECK(v == utl::vector<int>{ 0, 1, 2 });
	}
	
	SECTION("mid range") {
		utl::vector<int> v = { 0, 1, 2, 3, 4 };
		auto result = v.erase(v.begin() + 1, v.end() - 2);
		CHECK(result == v.begin() + 1);
		CHECK(v.size() == 3);
		CHECK(v == utl::vector<int>{ 0, 3, 4 });
	}
	
	SECTION("empty range") {
		utl::vector<int> v = { 0, 1, 2, 3 };
		auto result = v.erase(v.begin(), v.begin());
		CHECK(result == v.begin());
		CHECK(v.size() == 4);
		CHECK(v == utl::vector<int>{ 0, 1, 2, 3 });
	}
	
}
