#define _UTL_MAP_DEBUG_PRINT

#include "Catch2.hpp"
#include <utl/map.hpp>
#include <utl/__map_info_buffer.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <set>

TEST_CASE("__map_info_buffer") {
	
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 1>>(8) == 2);
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 2>>(8) == 2);
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 4>>(8) == 4);
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t<16, 8>>(8) == 8);
	
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 4>>(800) == 200);
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 4>>(801) == 204);
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 4>>(816) == 204);
	
	CHECK(utl::__map_info_buffer::__required_size<std::aligned_storage_t< 8, 4>>(817) == 208);
	
	struct Pair { int key, value; };
	
	std::size_t const numElements = 20;
	
	std::size_t const size = utl::__map_info_buffer::__required_size<Pair>(numElements);
	std::unique_ptr<std::uint8_t[]> buffer = std::make_unique<std::uint8_t[]>(size);
	
	
	utl::__map_info_buffer info;
	for (int x = 0; x < numElements; ++x) {
		for (int y = 0; y < numElements; ++y) {
			info.__construct(buffer.get(), size);
			info.__set_has_element(x, true);
			info.__set_is_tombstone(y, true);
			for (int i = 0; i < numElements; ++i) {
				CHECK(info.__has_element(i) == (i == x));
				CHECK(info.__is_tombstone(i) == (i == y));
				CHECK(info.__has_element_or_is_tombstone(i) == (i == x || i == y));
			}
		}
	}
	
}

TEST_CASE("map") {
	utl::map<int, int> m;

	

	SECTION("insert-lookup-update") {
		std::vector<int> keys;
		int n = 265;
		keys.reserve(n);
		std::generate_n(std::back_inserter(keys), n, [prev = std::set<int>{}, rng = std::mt19937{ std::random_device()() }]() mutable {
			begin:
			int const result = std::uniform_int_distribution<>(0, 1000)(rng);
			if (!prev.insert(result).second) {
				goto begin;
			}
			return result;
		});
		
		for (int i = 0; i < std::size(keys); ++i) {
			auto result = m.insert(keys[i], i);
			CHECK(result);
			CHECK(result.key() == keys[i]);
			CHECK(result.value() == i);
			CHECK(m.contains(keys[i]));
			CHECK(m[keys[i]].has_value());
			CHECK(m[keys[i]] == i);
		}
		for (int i = 0; i < std::size(keys); ++i) {
			auto elem = m.lookup(keys[i]);
			CHECK(elem);
			CHECK(elem.key() == keys[i]);
			CHECK(elem.value() == i);
		}
		for (int i = 0; i < std::size(keys); ++i) {
			auto result = m.update(keys[i], 0);
			CHECK(result);
			CHECK(result.key() == keys[i]);
			CHECK(result.value() == 0);
		}
		CHECK(m.size() == std::size(keys));
	}
}
