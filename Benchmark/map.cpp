#include <benchmark/benchmark.h>
#include <utl/map.hpp>
#include <utl/hashmap.hpp>
#include <utl/bit.hpp>

#include <unordered_map>

#include <vector>
#include <random>

template <typename A, typename B>
std::vector<std::pair<A, B>> getData(std::size_t count) {
	static std::mt19937_64 rng(0);
	static std::vector<std::pair<A, B>> data;
	
	data.reserve(count);
	while (data.size() < count) {
//		data.push_back(utl::unsafe_bit_cast<std::pair<A, B>>(rng()));
		data.push_back({ data.size(), data.size() });
	}
	
	std::vector<std::pair<A, B>> result;
	result.reserve(count);
	std::copy(data.begin(), data.end(), std::back_inserter(result));
	return result;
}

template <typename Map, typename A, typename B>
static void benchmark_map(benchmark::State& s) {
	std::size_t const numElems = s.range(0);
	auto const data = getData<A, B>(numElems);
	
	for (auto _: s) {
		Map m;
		m.reserve(data.size());
		for (auto&& elem: data) {
			if constexpr (requires { m.insert({ elem.first, elem.second }); }) {
				m.insert({ elem.first, elem.second });
			}
			else {
				m.insert(elem.first, elem.second);
			}
		}
		benchmark::DoNotOptimize(m);
	}
}

#define MAP_BENCHMARK(...) \
BENCHMARK(benchmark_map<__VA_ARGS__>)->Arg(500'000)->Unit(benchmark::TimeUnit::kMillisecond)

MAP_BENCHMARK(utl::map<int, int>, int, int);
MAP_BENCHMARK(utl::map<int, int, std::hash<int>>, int, int);
MAP_BENCHMARK(utl::hashmap<int, int>, int, int);
MAP_BENCHMARK(std::unordered_map<int, int>, int, int);
