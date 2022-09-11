#include <utl/map.hpp>
#include <utl/hashmap.hpp>
#include <unordered_map>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

static void escape(void* p) {
	asm volatile("" : : "g"(p) : "memory");
}

static void clobber() {
	asm volatile("" : : : "memory");
}


struct Benchmark {
	Benchmark(std::size_t numElems) {
		data.reserve(numElems);
		std::generate_n(std::back_inserter(data), numElems, [rng = std::mt19937_64{ std::random_device{}() }]() mutable {
			std::uint64_t const r = rng();
			std::pair<int, int> result;
			static_assert(sizeof result == 8);
			std::memcpy(&result, &r, 8);
			return result;
		});
	}
	
	template <typename Map>
	std::size_t execute_impl(bool reserve) {
		auto const begin = std::chrono::high_resolution_clock::now();
		
		Map m;
		
		
		if constexpr (requires { m.reserve(data.size()); }) {
			if (reserve) {
				m.reserve(data.size());
			}
		}
		
		for (auto&& elem: data) {
			if constexpr (requires { m.insert({ elem.first, elem.second }); }) {
				m.insert({ elem.first, elem.second });
			}
			else {
				m.insert(elem.first, elem.second);
			}
		}
		
		escape(&m);
		clobber();
		
		auto const end = std::chrono::high_resolution_clock::now();
		return (end - begin).count();
	}
	
	template <typename Map>
	void execute(bool reserve, char const* name) {
		std::size_t const totalTargetTime = 3 * 1'000'000'000ull; // 3 seconds
		std::size_t numSamples = 0, totalTime = 0;
		for (; totalTime < totalTargetTime; ++numSamples) {
			totalTime += execute_impl<Map>(reserve);
		}
		std::cout << name << ": " << (double)totalTime / 1'000'000 / numSamples << "ms [" << numSamples << " samples run]\n";
 	}
	
	std::vector<std::pair<int, int>> data;
};


int main() {
	Benchmark b(5'000'000);
	
//	b.execute<std::unordered_map<int, int>>(false, "std::unordered_map");
//	b.execute<std::unordered_map<int, int>>(true, "std::unordered_map with reserve");
//	b.execute<utl::map<int, int, std::hash<int>>>(false, "utl::map<std::hash>");
//	b.execute<utl::map<int, int, std::hash<int>>>(true, "utl::map<std::hash> with reserve");
	b.execute<utl::map<int, int, utl::good_hash<int>>>(false, "utl::map<utl::good_hash>");
	b.execute<utl::map<int, int, utl::good_hash<int>>>(true, "utl::map<utl::good_hash> with reserve");
	
	b.execute<utl::hashmap<int, int>>(false, "utl::hashmap");
	b.execute<utl::hashmap<int, int>>(true, "utl::hashmap with reserve");
}
