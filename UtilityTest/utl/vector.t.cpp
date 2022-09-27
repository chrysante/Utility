#include "Catch2.hpp"

#include <utl/vector.hpp>

#include "LifetimeCounter.hpp"

TEST_CASE("vector-move-construct") {
	utl_test::LifetimeCounter::reset();
	utl::vector<utl_test::LifetimeCounter> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const vCap = v.capacity();
	utl::vector<utl_test::LifetimeCounter> w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(w.capacity() == vCap);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

TEST_CASE("vector-move-construct from small_vector") {
	utl_test::LifetimeCounter::reset();
	utl::small_vector<utl_test::LifetimeCounter, 100> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const vCap = v.capacity();
	utl::vector<utl_test::LifetimeCounter> w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

TEST_CASE("vector-move-assign") {
	utl_test::LifetimeCounter::reset();
	utl::vector<utl_test::LifetimeCounter> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const vCap = v.capacity();
	auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
	utl::vector<utl_test::LifetimeCounter> w(wInitCount);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count + wInitCount);
	w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(w.capacity() >= vCap);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

TEST_CASE("vector-move-assign from small_vector") {
	utl_test::LifetimeCounter::reset();
	utl::small_vector<utl_test::LifetimeCounter, 100> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const vCap = v.capacity();
	auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
	utl::vector<utl_test::LifetimeCounter> w(wInitCount);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count + wInitCount);
	w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

TEST_CASE("vector-copy-construct") {
	utl_test::LifetimeCounter::reset();
	utl::vector<utl_test::LifetimeCounter> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	utl::vector<utl_test::LifetimeCounter> w = v;
	CHECK(w.size() == v.size());
	CHECK(utl_test::LifetimeCounter::liveObjects() == 2 * count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
}

TEST_CASE("vector-copy-assign") {
	utl_test::LifetimeCounter::reset();
	utl::vector<utl_test::LifetimeCounter> v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
	utl::vector<utl_test::LifetimeCounter> w(wInitCount);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count + wInitCount);
	w = v;
	CHECK(w.size() == vSize);
	CHECK(utl_test::LifetimeCounter::liveObjects() == 2 * count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
}

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
		INFO(v);
		CHECK(v[0] == 2);
		CHECK(v[1] == 3);
	}
	
	SECTION("end range") {
		utl::vector<int> v = { 0, 1, 2, 3, 4 };
		auto result = v.erase(v.begin() + 3, v.end());
		CHECK(result == v.end());
		CHECK(v.size() == 3);
		CHECK(v[0] == 0);
		CHECK(v[1] == 1);
		CHECK(v[2] == 2);
	}
	
	SECTION("mid range") {
		utl::vector<int> v = { 0, 1, 2, 3, 4 };
		auto result = v.erase(v.begin() + 1, v.end() - 2);
		CHECK(result == v.begin() + 1);
		CHECK(v.size() == 3);
		CHECK(v[0] == 0);
		CHECK(v[1] == 3);
		CHECK(v[2] == 4);
	}
	
	SECTION("empty range") {
		utl::vector<int> v = { 0, 1, 2, 3 };
		auto result = v.erase(v.begin(), v.begin());
		CHECK(result == v.begin());
		CHECK(v.size() == 4);
		CHECK(v[0] == 0);
		CHECK(v[1] == 1);
		CHECK(v[2] == 2);
		CHECK(v[3] == 3);
	}
	
}
