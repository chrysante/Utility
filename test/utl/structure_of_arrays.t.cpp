#include <catch/catch2.hpp>

#include "LifetimeCounter.hpp"

#include "utl/structure_of_arrays.hpp"
#include "utl/utility.hpp"

#include <algorithm>
#include <numeric>
#include <iostream>

using namespace utl_test;

#if !defined(_MSC_VER) // Have weird bugs when compiling with MSVC

namespace {
	
	struct alignas(64) Overaligned {
		bool operator==(Overaligned const&) const = default;
	};
	
	static_assert(sizeof(Overaligned) == 64);
	static_assert(alignof(Overaligned) == 64);
	
	UTL_SOA_TYPE(Particle,
				 (float,  position),
				 (int,    id),
				 (double, color),
				 (int,    size),
				 (LifetimeCounter, counter),
				 (Overaligned,     overaligned)
	);
	
}

static void testAlignment(void const* ptr, std::size_t alignment) {
	CHECK((std::uintptr_t)ptr % alignment == 0);
}

template <typename A>
static void testPushBack(utl::structure_of_arrays<Particle, A> const& s, std::size_t size) {
	CHECK(s.size() == size);
	CHECK(LifetimeCounter::liveObjects() == size);
	testAlignment(s.data().position,    alignof(float));
	testAlignment(s.data().id,          alignof(int));
	testAlignment(s.data().color,       alignof(float));
	testAlignment(s.data().size,        alignof(int));
	testAlignment(s.data().counter,     alignof(LifetimeCounter));
	testAlignment(s.data().overaligned, alignof(Overaligned));
	for (std::size_t i = 0; i < size; ++i) {
		CHECK(s[i].id == (int)i);
	}
}

static void testPushBack(auto& s) {
	LifetimeCounter::reset();
	
	s.push_back({ .id = 0 });
	testPushBack(s, 1);
	s.push_back({ .id = 1 });
	testPushBack(s, 2);
	s.push_back({ .id = 2 });
	testPushBack(s, 3);
	s.push_back({ .id = 3 });
	testPushBack(s, 4);
	s.push_back({ .id = 4 });
	testPushBack(s, 5);
	s.push_back({ .id = 5 });
	testPushBack(s, 6);
}

TEST_CASE("structure_of_arrays::push_back") {
	utl::structure_of_arrays<Particle> s;
	testPushBack(s);
}

TEST_CASE("pmr::structure_of_arrays::push_back") {
	utl::pmr::structure_of_arrays<Particle> s;
	testPushBack(s);
}

TEST_CASE("pmr::structure_of_arrays copy construct (resource equal)") {
	utl::pmr::structure_of_arrays<Particle> s;
	s.push_back({ .id = 0 });
	s.push_back({ .id = 1 });
	
	utl::pmr::structure_of_arrays<Particle> t = s;
	
	CHECK(s.size() == 2);
	CHECK(s.capacity() >= 2);
	CHECK(s[0].id == 0);
	CHECK(s[1].id == 1);
	
	CHECK(t.size() == 2);
	CHECK(t.capacity() >= 2);
	CHECK(t[0].id == 0);
	CHECK(t[1].id == 1);
}

TEST_CASE("pmr::structure_of_arrays move construct (resource equal)") {
	utl::pmr::structure_of_arrays<Particle> s;
	s.push_back({ .id = 0 });
	s.push_back({ .id = 1 });
	
	utl::pmr::structure_of_arrays<Particle> t = std::move(s);
	CHECK(s.size() == 0);
	CHECK(s.capacity() == 0);
	CHECK(t.size() == 2);
	CHECK(t[0].id == 0);
	CHECK(t[1].id == 1);
}

TEST_CASE("pmr::structure_of_arrays move assign (resource equal)") {
	utl::pmr::structure_of_arrays<Particle> s;
	s.push_back({ .id = 0 });
	s.push_back({ .id = 1 });
	
	utl::pmr::structure_of_arrays<Particle> t;
	SECTION("empty") {}
	SECTION("non-empty") {
		t.push_back({});
		t.push_back({});
		t.push_back({});
	}
	t = std::move(s);
	CHECK(s.size() == 0);
	CHECK(s.capacity() == 0);
	CHECK(t.size() == 2);
	CHECK(t[0].id == 0);
	CHECK(t[1].id == 1);
}

TEST_CASE("structure_of_arrays::view") {
	utl::structure_of_arrays<Particle> const s = {
		Particle{ .position = 1, .id = 2, .color = 3, .size = 4 },
		Particle{},
		Particle{}
	};
	CHECK(s.size() == 3);
	CHECK(s.capacity() >= 3);
	CHECK(s[0] == Particle{ 1, 2, 3, 4 });
}

TEST_CASE("structure_of_arrays::iterator") {
	utl::structure_of_arrays<Particle> s;
	int const size = GENERATE(0, 1, 10, 42);
	for (int i = 0; i < size; ++i) {
		s.push_back(Particle{ .position = (rand() % 1024) / 1024.0f, .id = rand() % 1024 });
	}
	SECTION("Arithmetic") {
		CHECK(s.end() - s.begin() == size);
		CHECK(s.begin() + size == s.end());
		CHECK(s.end() - size == s.begin());
	}
	SECTION("Reverse Arithmetic") {
		CHECK(s.rend() - s.rbegin() == size);
		CHECK(s.rbegin() + size == s.rend());
		CHECK(s.rend() - size == s.rbegin());
	}
	SECTION("Increment") {
		auto itr = s.begin();
		for (int i = 0; i < size; ++i) {
			++itr;
		}
		CHECK(itr == s.end());
	}
}

TEST_CASE("std::sort(structure_of_arrays)") {
	utl::structure_of_arrays<Particle> s;
	int const size = GENERATE(0, 1, 10, 42);
	std::vector<int> values(size);
	std::iota(values.begin(), values.end(), 0);
	std::shuffle(values.begin(), values.end(), std::mt19937_64(std::random_device{}()));
	for (int i: values) {
		s.push_back(Particle{ .position = (float)i, .id = size - 1 - i });
	}
	SECTION("forward") {
		// sort by id
		std::sort(s.begin(), s.end(), [](auto&& a, auto&& b) { return a.id < b.id; });
	}
	SECTION("reverse") {
		// sort by id
		std::sort(s.rbegin(), s.rend(), [](auto&& a, auto&& b) { return a.id > b.id; });
	}
	for (int i = 0; auto [position, id]: s.view<Particle::members::position, Particle::members::id>()) {
		CHECK(id == i);
		CHECK(position == size - 1 - i);
		++i;
	}
}

TEST_CASE("structure_of_arrays::insert") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s;
	for (int i = 0; i < 3; ++i) {
		s.push_back(Particle{ .id = i });
	}
	REQUIRE(s.size() == 3);
	SECTION("insert front") {
		s.insert(0, Particle{ .id = -1 });
		CHECK(s.size() == 4);
		CHECK(s.capacity() >= 4);
		CHECK(s[0].id == -1);
		CHECK(s[1].id == 0);
		CHECK(s[2].id == 1);
		CHECK(s[3].id == 2);
		CHECK(LifetimeCounter::liveObjects() == 4);
	}
	SECTION("insert center") {
		s.insert(1, Particle{ .id = -1 });
		CHECK(s.size() == 4);
		CHECK(s.capacity() >= 4);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == -1);
		CHECK(s[2].id == 1);
		CHECK(s[3].id == 2);
		CHECK(LifetimeCounter::liveObjects() == 4);
	}
	SECTION("insert back") {
		s.insert(3, Particle{ .id = -1 });
		CHECK(s.size() == 4);
		CHECK(s.capacity() >= 4);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 1);
		CHECK(s[2].id == 2);
		CHECK(s[3].id == -1);
		CHECK(LifetimeCounter::liveObjects() == 4);
	}
}

TEST_CASE("structure_of_arrays::insert [range]") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s;
	for (int i = 0; i < 3; ++i) {
		s.push_back(Particle{ .id = i });
	}
	REQUIRE(s.size() == 3);
	Particle p[3] = {
		{ .id = -1, .counter{ false } },
		{ .id = -2, .counter{ false } },
		{ .id = -3, .counter{ false } }
	};
	SECTION("insert front") {
		s.insert(0, p, p + 3);
		CHECK(s.size() == 6);
		CHECK(s.capacity() >= 6);
		CHECK(s[0].id == -1);
		CHECK(s[1].id == -2);
		CHECK(s[2].id == -3);
		CHECK(s[3].id == 0);
		CHECK(s[4].id == 1);
		CHECK(s[5].id == 2);
		CHECK(LifetimeCounter::liveObjects() == 6);
	}
	SECTION("insert center") {
		s.insert(1, p, p + 3);
		CHECK(s.size() == 6);
		CHECK(s.capacity() >= 6);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == -1);
		CHECK(s[2].id == -2);
		CHECK(s[3].id == -3);
		CHECK(s[4].id == 1);
		CHECK(s[5].id == 2);
		CHECK(LifetimeCounter::liveObjects() == 6);
	}
	SECTION("insert back") {
		s.insert(3, p, p + 3);
		CHECK(s.size() == 6);
		CHECK(s.capacity() >= 6);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 1);
		CHECK(s[2].id == 2);
		CHECK(s[3].id == -1);
		CHECK(s[4].id == -2);
		CHECK(s[5].id == -3);
		CHECK(LifetimeCounter::liveObjects() == 6);
	}
}

TEST_CASE("structure_of_arrays::insert [empty]") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s;
	s.insert(0, Particle{ .id = -1 });
	CHECK(s.size() == 1);
	CHECK(s.capacity() >= 1);
	CHECK(s[0].id == -1);
	CHECK(LifetimeCounter::liveObjects() == 1);
}

TEST_CASE("structure_of_arrays::insert [range2]") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s = { Particle{ .id = -1 } };
	Particle p[5] = {
		{ .id = 0, .counter{ false } },
		{ .id = 1, .counter{ false } },
		{ .id = 2, .counter{ false } },
		{ .id = 3, .counter{ false } },
		{ .id = 4, .counter{ false } }
	};
	s.insert(0, p, p + 5);
	CHECK(s.size() == 6);
	CHECK(s.capacity() >= 6);
	CHECK(s[0].id == 0);
	CHECK(s[1].id == 1);
	CHECK(s[2].id == 2);
	CHECK(s[3].id == 3);
	CHECK(s[4].id == 4);
	CHECK(s[5].id == -1);
	CHECK(LifetimeCounter::liveObjects() == 6);
}

TEST_CASE("structure_of_arrays::insert [empty, range]") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s;
	Particle p[5] = {
		{ .id = 0, .counter{ false } },
		{ .id = 1, .counter{ false } },
		{ .id = 2, .counter{ false } },
		{ .id = 3, .counter{ false } },
		{ .id = 4, .counter{ false } }
	};
	s.insert(0, p, p + 5);
	CHECK(s.size() == 5);
	CHECK(s.capacity() >= 5);
	CHECK(s[0].id == 0);
	CHECK(s[1].id == 1);
	CHECK(s[2].id == 2);
	CHECK(s[3].id == 3);
	CHECK(s[4].id == 4);
	CHECK(LifetimeCounter::liveObjects() == 5);
}

TEST_CASE("structure_of_arrays::erase") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s;
	for (int i = 0; i < 4; ++i) {
		s.push_back(Particle{ .id = i });
	}
	CHECK(LifetimeCounter::liveObjects() == 4);
	
	REQUIRE(s.size() == 4);
	SECTION("erase front") {
		s.erase(0);
		CHECK(s.size() == 3);
		CHECK(LifetimeCounter::liveObjects() == 3);
		CHECK(s[0].id == 1);
		CHECK(s[1].id == 2);
		CHECK(s[2].id == 3);
	}
	SECTION("erase center") {
		s.erase(1);
		CHECK(s.size() == 3);
		CHECK(LifetimeCounter::liveObjects() == 3);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 2);
		CHECK(s[2].id == 3);
	}
	SECTION("erase back") {
		s.erase(3);
		CHECK(s.size() == 3);
		CHECK(LifetimeCounter::liveObjects() == 3);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 1);
		CHECK(s[2].id == 2);
	}
}

TEST_CASE("structure_of_arrays::erase to empty") {
	LifetimeCounter::reset();
	utl::structure_of_arrays<Particle> s = { Particle{} };
	CHECK(LifetimeCounter::liveObjects() == 1);
	s.erase(0);
	CHECK(s.size() == 0);
	CHECK(LifetimeCounter::liveObjects() == 0);
}

TEST_CASE("structure_of_arrays::erase to empty with iterator") {
	LifetimeCounter::reset();
	SECTION("single element") {
		utl::structure_of_arrays<Particle> s = { Particle{} };
		CHECK(LifetimeCounter::liveObjects() == 1);
		s.erase(s.begin());
		CHECK(s.size() == 0);
		CHECK(LifetimeCounter::liveObjects() == 0);
	}
	SECTION("multiple elements") {
		utl::structure_of_arrays<Particle> s(10);
		CHECK(LifetimeCounter::liveObjects() == 10);
		s.erase(s.begin(), s.end());
		CHECK(s.size() == 0);
		CHECK(LifetimeCounter::liveObjects() == 0);
	}
}

TEST_CASE("structure_of_arrays::erase range") {
	utl::structure_of_arrays<Particle> s;
	for (int i = 0; i < 8; ++i) {
		s.push_back(Particle{ .id = i });
	}
	
	REQUIRE(s.size() == 8);
	SECTION("erase front") {
		s.erase(0, 5);
		CHECK(s.size() == 3);
		CHECK(s[0].id == 5);
		CHECK(s[1].id == 6);
		CHECK(s[2].id == 7);
	}
	SECTION("erase center") {
		s.erase(2, 7);
		CHECK(s.size() == 3);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 1);
		CHECK(s[2].id == 7);
	}
	SECTION("erase back") {
		s.erase(3, 8);
		CHECK(s.size() == 3);
		CHECK(s[0].id == 0);
		CHECK(s[1].id == 1);
		CHECK(s[2].id == 2);
	}
}

TEST_CASE("structure_of_arrays::erase range to empty") {
	utl::structure_of_arrays<Particle> s(8);
	s.erase(0, 8);
	CHECK(s.size() == 0);
}

TEST_CASE("structure_of_arrays::swap") {
	utl::structure_of_arrays<Particle> s = {
		Particle{ .id = 0 },
		Particle{ .id = 1 },
		Particle{ .id = 2 }
	};
	utl::structure_of_arrays<Particle> t = {
		Particle{ .id =  0 },
		Particle{ .id = -1 }
	};
	s.swap(t);
	CHECK(t.size() == 3);
	for (int i = 0; i < 3; ++i) {
		CHECK(t[i].id == i);
	}
	CHECK(s.size() == 2);
	for (int i = 0; i < 2; ++i) {
		CHECK(s[i].id == -i);
	}
}

TEST_CASE("structure_of_arrays iterate") {
	utl::structure_of_arrays<Particle> s;
	int const size = GENERATE(0, 1, 10, 42);
	for (int i = 0; i < size; ++i) {
		s.push_back(Particle{ .id = i });
	}
	SECTION("iterate subset view") {
		for (int i = 0;
			 auto [position, id]: s.view<Particle::members::position const, Particle::members::id const>())
		{
			CHECK(id == i);
			++i;
		}
	}
	SECTION("iterate single member with begin/end") {
		int i = 0;
		auto itr = s.begin<Particle::members::id const>();
		auto end = s.end<Particle::members::id>();
		for (; itr != end; ++itr, ++i) {
			CHECK(*itr == i);
		}
	}
}

TEST_CASE("structure_of_arrays with STL algorithms") {
	utl::structure_of_arrays<Particle> s(10);
	std::generate(s.begin(), s.end(), [i = 0]() mutable {
        auto const result = Particle{ .position = static_cast<float>(9 - i), .id = 9 - i };
		++i;
		return result;
	});
	for (int i = 0; i < 10; ++i) {
		CHECK(s[i].id == 9 - i);
		CHECK(s[i].position == 9 - i);
	}
	std::reverse(s.begin(), s.end());
	for (int i = 0; i < 10; ++i) {
		CHECK(s[i].id == i);
		CHECK(s[i].position == i);
	}
	std::rotate(s.begin(), s.begin() + 3, s.end());
	for (int i = 0; i < 10; ++i) {
		CHECK(s[i].id == (i + 3) % 10);
		CHECK(s[i].position == (i + 3) % 10);
	}
	
	std::shuffle(s.begin(), s.end(), std::mt19937(std::random_device{}()));

	std::sort(s.begin(), s.end(), [](auto a, auto b) { return a.id < b.id; });
	for (int i = 0; i < 10; ++i) {
		CHECK(s[i].id == i);
		CHECK(s[i].position == i);
	}
	
	utl::structure_of_arrays<Particle> t;

	std::copy(s.begin(), s.end(), std::back_inserter(t));
	for (int i = 0; i < 10; ++i) {
		CHECK(t[i].id == i);
		CHECK(t[i].position == i);
	}
}

#endif // _MSC_VER
