#include "Catch2.hpp"


#include "utl/structure_of_arrays.hpp"

TEST_CASE("structure_of_arrays") {
	
	utl::structure_of_arrays<utl::soa::tuple<float, int>> S;
	
	S.push_back(0.4, 0);
	S.push_back(0.5, 1);
	S.push_back(0.6, 2);
	S.push_back(0.7, 3);
	
	utl::find_if([](auto index, auto f, auto i) {
		CHECK(i == index);
		return false;
	}, S.array<float>(), S.array<int>());
	
	
	S.insert_at(0, 0.3, -1);
	
	S.erase(1);
	S.insert_at(1, 0.4, 0);
	
	
	utl::find_if([](auto index, auto f, auto i) {
		CHECK(i + 1 == index);
		return false;
	}, S.array<float>(), S.array<int>());
	
	S.erase(0);
	
	utl::find_if([](auto index, auto f, auto i) {
		CHECK(i == index);
		return false;
	}, S.array<float>(), S.array<int>());
}

TEST_CASE("structure_of_arrays2") {
	
	utl::structure_of_arrays<utl::soa::tuple<float, int>> S;
	
	S.push_back(0.4, 0);
	S.push_back(0.5, 1);
	S.push_back(0.7, 3);
	S.push_back(0.6, 2);
	
	auto elem = S[2].copy();
	S.erase(2);
	S.push_back(elem);
	
	utl::find_if([](auto index, auto f, auto i) {
		CHECK(i == index);
		return false;
	}, S.array<float>(), S.array<int>());
}
