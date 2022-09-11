#define _UTL_MAP_DEBUG_PRINT

#include <utl/map.hpp>
#include <utl/typeinfo.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

struct Test {
	Test(std::size_t count, bool unique = false) {
		keys.reserve(count);
		std::generate_n(std::back_inserter(keys), count, [&, prev = std::set<int>{}, rng = std::mt19937{ std::random_device()() }]() mutable {
			begin:
			int const result = std::uniform_int_distribution<>(0, count * 100)(rng);
			if (unique && !prev.insert(result).second) {
				goto begin;
			}
			return result;
		});
	}
	
	
	template <typename Hash>
	utl::map<int, int, Hash> makeMap() const {
		utl::map<int, int, Hash> m;
		for (int i = 0; i < std::size(keys); ++i) {
			m.insert(keys[i], i);
		}
		return m;
	}
	
	template <typename Hash>
	double getEntropy(utl::map<int, int, Hash> const& m) const {
		std::size_t const sum_offsets = m.__sum_of_offsets();
		double const entropy = (double)sum_offsets / m.size();
		return entropy;
	}
	
	std::vector<int> keys;
};

template <typename Hash>
constexpr double lower = 0;
template <typename Hash>
constexpr double upper = 0;

template <>
constexpr double lower<utl::good_hash<int>> = 2;
template <>
constexpr double upper<utl::good_hash<int>> = 2.1;

template <>
constexpr double lower<std::hash<int>> = 1.2;
template <>
constexpr double upper<std::hash<int>> = 1.4;

template <typename Hash>
void test2(std::size_t count) {
	while (true) {
		Test t(count);
		auto const m = t.makeMap<Hash>();
		double const e = t.getEntropy(m);
		if (e >= lower<Hash> && e <= upper<Hash>) {
			m.__debug_print();
			__utl_debugbreak();
			break;
		}
	}
}

int _main() {
	std::size_t numElements = 265;
	
//	if (0)
//	{
//		test2<utl::good_hash<int>>(numElements);
//		test2<std::hash<int>>(numElements);
//
//		return 0;
//	}

	double good_hash = 0, std_hash = 0;
	
	int const numSamples = 10'000;
	for (int i = 0; i < numSamples; ++i) {
		Test t(numElements);
		
		good_hash += t.getEntropy(t.makeMap<utl::good_hash<int>>());
		std_hash += t.getEntropy(t.makeMap<std::hash<int>>());
	}
	
	std::cout << "good_hash: " << good_hash / numSamples << std::endl;
	std::cout << "std_hash:  " << std_hash / numSamples << std::endl;
}
