#include "Catch2.hpp"

#include <concepts>

#include <utl/vector.hpp>

#include "LifetimeCounter.hpp"

namespace {

enum class Tag;

template <typename T>
struct TagAllocator {
    using value_type = T;
    
    template <typename... Args>
    void construct(T* ptr, Args&&... args) {
        if constexpr (std::is_constructible_v<T, std::allocator_arg_t, TagAllocator, Args...>) {
            ::new ((void*)ptr) T(std::allocator_arg, *this, std::forward<Args>(args)...);
        }
        else if constexpr (std::is_constructible_v<T, Args..., TagAllocator>) {
            ::new ((void*)ptr) T(std::forward<Args>(args)..., *this);
        }
        else {
            ::new ((void*)ptr) T(std::forward<Args>(args)...);
        }
    }
    
    bool operator==(TagAllocator const&) const = default;
    
    TagAllocator() { tag = Tag{ 0 }; }
    TagAllocator(Tag t) { tag = t; }
    
    T* allocate(size_t n) { return (T*)::operator new(sizeof(T) * n); }
    void deallocate(T* ptr, size_t n) { ::operator delete(ptr); }
    
    Tag tag;
};

struct X {
    X(TagAllocator<X> alloc = {}): alloc(alloc) {}
    X(int value, TagAllocator<X> alloc = {}): alloc(alloc), value(value) {}
    
    X(X const& rhs, TagAllocator<X> alloc = {}): alloc(alloc), value(rhs.value) {}
    X(X&& rhs, TagAllocator<X> alloc = {}): alloc(alloc), value(rhs.value) {}
    
    X& operator=(X const& rhs) { value = rhs.value; return *this; }
    X& operator=(X&& rhs) { value = rhs.value; return *this; }
    
    bool operator==(X const& rhs) const { return value == rhs.value; }
    
    TagAllocator<X> alloc;
    int value = 0;
};

template <typename T>
using TaVector = utl::vector<T, TagAllocator<T>>;

template <typename T>
using TaSmallVector = utl::small_vector<T, utl::default_inline_capacity<T, TagAllocator<T>>, TagAllocator<T>>;

}

#define VECTOR_TEST_CASE(T, ...) TEMPLATE_TEST_CASE_SIG(__VA_ARGS__, ((typename Vector, int __ignore__), Vector, __ignore__), (TaVector<T>, 0), (TaSmallVector<T>, 0))

#define VECTOR_PRODUCT_TEST_CASE(T, ...) TEMPLATE_TEST_CASE_SIG(__VA_ARGS__, ((typename VectorA, typename VectorB, int __ignore__), VectorA, VectorB, __ignore__), \
    (TaVector<T>, TaVector<T>, 0), (TaVector<T>, TaSmallVector<T>, 0), (TaSmallVector<T>, TaVector<T>, 0), (TaSmallVector<T>, TaSmallVector<T>, 0))

/// MARK: Constructors
VECTOR_TEST_CASE(int, "vector-default-construct", "[vector]") {
    Vector v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
}

VECTOR_TEST_CASE(X, "vector-allocator-default-construct", "[vector]") {
    Vector v(Tag(1));
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
}

VECTOR_TEST_CASE(X, "vector-allocator-propagate", "[vector]") {
    Vector v(2, Tag(1));
    REQUIRE(v.size() == 2);
    CHECK(v.capacity() >= 2);
    CHECK(v[0].alloc.tag == Tag(1));
    CHECK(v[1].alloc.tag == Tag(1));
}

VECTOR_TEST_CASE(X, "vector-allocator-iterator-constructor", "[vector]") {
    TagAllocator<X> alloc(Tag(1));
    X data[5]{
        {  3, alloc },
        {  4, alloc },
        {  2, alloc },
        { -1, alloc },
        { 10, alloc }
    };
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(std::begin(data), std::end(data), tag2);
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(v[0].alloc.tag == tag2);
    CHECK(v[0].value ==  3);
    CHECK(v[1].alloc.tag == tag2);
    CHECK(v[1].value ==  4);
    CHECK(v[2].alloc.tag == tag2);
    CHECK(v[2].value ==  2);
    CHECK(v[3].alloc.tag == tag2);
    CHECK(v[3].value == -1);
    CHECK(v[4].alloc.tag == tag2);
    CHECK(v[4].value == 10);
}

namespace {
struct Y {
    int value;
    operator X() const { return X(value); }
};
}

VECTOR_TEST_CASE(X, "vector-allocator-iterator-converting-constructor", "[vector]") {
    Y data[5]{ 3, 4, 2, -1, 10 };
    Vector v(std::begin(data), std::end(data), Tag(2));
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(v[0].alloc.tag == Tag(2));
    CHECK(v[0].value ==  3);
    CHECK(v[1].alloc.tag == Tag(2));
    CHECK(v[1].value ==  4);
    CHECK(v[2].alloc.tag == Tag(2));
    CHECK(v[2].value ==  2);
    CHECK(v[3].alloc.tag == Tag(2));
    CHECK(v[3].value == -1);
    CHECK(v[4].alloc.tag == Tag(2));
    CHECK(v[4].value == 10);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-copy-ctor", "[vector]") {
    VectorA v(Tag{ 1 });
    v.emplace_back(1);
    v.emplace_back(2);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(v, tag2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-copy-assign", "[vector]") {
    VectorA v({ 1, 2 }, Tag(1));
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    w = v;
    REQUIRE(w.size() == 2);
    CHECK(w.capacity() >= 2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
}

VECTOR_TEST_CASE(X, "vector-allocator-copy-assign-ilist", "[vector]") {
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector w(wCount, tag2);
    w = { 1, 2 };
    REQUIRE(w.size() == 2);
    CHECK(w.capacity() >= 2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-move-ctor", "[vector]") {
    VectorA v({ 1, 2 }, Tag(1));
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-move-assign", "[vector]") {
    VectorA v({ 1, 2 }, Tag(1));
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    w = std::move(v);
    REQUIRE(w.size() == 2);
    CHECK(w.capacity() >= 2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
}

VECTOR_TEST_CASE(X, "vector-allocator-ilist", "[vector]") {
    TagAllocator<X> alloc(Tag(1));
    Vector v({ { 1, alloc }, { 2, alloc }, { 4, alloc } }, Tag{ 2 });
    REQUIRE(v.size() == 3);
    CHECK(v.capacity() >= 3);
    CHECK(v[0].alloc.tag == Tag{ 2 });
    CHECK(v[0].value == 1);
    CHECK(v[1].alloc.tag == Tag{ 2 });
    CHECK(v[1].value == 2);
    CHECK(v[2].alloc.tag == Tag{ 2 });
    CHECK(v[2].value == 4);
}

VECTOR_TEST_CASE(X, "vector-allocator-propagate-emplace", "[vector]") {
    Vector v(Tag(1));
    v.emplace_back();
    REQUIRE(v.size() == 1);
    CHECK(v.capacity() >= 1);
    CHECK(v.front().alloc.tag == Tag(1));
    v.emplace_back();
    REQUIRE(v.size() == 2);
    CHECK(v.capacity() >= 2);
    CHECK(v[0].alloc.tag == Tag(1));
    CHECK(v[1].alloc.tag == Tag(1));
}

VECTOR_TEST_CASE(utl_test::LifetimeCounter, "vector-allocator-reserve", "[vector]") {
    utl_test::LifetimeCounter::reset();
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    auto const newCap = GENERATE(0, 5, 50);
    v.reserve(newCap);
    REQUIRE(v.size() == size);
    CHECK(utl_test::LifetimeCounter::liveObjects() == size);
    CHECK(v.capacity() >= newCap);
}

VECTOR_TEST_CASE(utl_test::LifetimeCounter, "vector-allocator-resize", "[vector]") {
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    auto const newSize = GENERATE(0, 5, 50);
    v.resize(newSize);
    CHECK(utl_test::LifetimeCounter::liveObjects() == newSize);
    REQUIRE(v.size() == newSize);
    CHECK(v.capacity() >= newSize);
}

VECTOR_TEST_CASE(X, "vector-allocator-insert", "[vector]") {
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    SECTION("begin") {
        v.insert(v.begin(), -1);
        CHECK(v == TaVector<X>{ -1, 0, 1, 2, 3 });
    }
    SECTION("mid") {
        v.insert(v.begin() + 1, -1);
        CHECK(v == TaVector<X>{ 0, -1, 1, 2, 3 });
    }
    SECTION("end - 1") {
        v.insert(v.end() - 1, -1);
        CHECK(v == TaVector<X>{ 0, 1, 2, -1, 3 });
    }
    SECTION("end") {
        v.insert(v.end(), -1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3, -1 });
    }
}

VECTOR_PRODUCT_TEST_CASE(utl_test::LifetimeCounter, "vector-move-construct", "[vector]") {
	utl_test::LifetimeCounter::reset();
	VectorA v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
    VectorB w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(w.capacity() >= w.size());
	CHECK(utl_test::LifetimeCounter::liveObjects() >= count);
    v.clear();
    w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(utl_test::LifetimeCounter, "vector-move-assign", "[vector]") {
	utl_test::LifetimeCounter::reset();
	VectorA v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
	VectorB w(wInitCount);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count + wInitCount);
	w = std::move(v);
	CHECK(w.size() == vSize);
	CHECK(w.capacity() >= vSize);
	CHECK(utl_test::LifetimeCounter::liveObjects() >= count);
	v.clear();
    w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(utl_test::LifetimeCounter, "vector-copy-construct", "[vector]") {
	utl_test::LifetimeCounter::reset();
	VectorA v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	VectorB w = v;
	CHECK(w.size() == v.size());
	CHECK(utl_test::LifetimeCounter::liveObjects() == 2 * count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
}

VECTOR_PRODUCT_TEST_CASE(utl_test::LifetimeCounter, "vector-copy-assign", "[vector]") {
	utl_test::LifetimeCounter::reset();
	VectorA v;
	auto const count = GENERATE(0, 1, 54, 64, 139);
	for (int i = 0; i < count; ++i) {
		v.emplace_back();
	}
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
	auto const vSize = v.size();
	auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
	VectorB w(wInitCount);
	CHECK(utl_test::LifetimeCounter::liveObjects() == count + wInitCount);
	w = v;
	CHECK(w.size() == vSize);
	CHECK(utl_test::LifetimeCounter::liveObjects() == 2 * count);
	w.clear();
	CHECK(utl_test::LifetimeCounter::liveObjects() == count);
}

VECTOR_TEST_CASE(X, "vector-erase", "[vector]") {
    Vector v = { 0, 1, 2, 3 };

    SECTION("all") {
        auto result = v.erase(v.begin(), v.end());
        CHECK(result == v.end());
        CHECK(v.empty());
    }
    
    SECTION("begin single") {
        auto result = v.erase(v.begin());
        CHECK(result == v.begin());
        CHECK(v.size() == 3);
        CHECK(v[0].value == 1);
        CHECK(v[1].value == 2);
        CHECK(v[2].value == 3);
    }
    
    SECTION("end single") {
        auto result = v.erase(v.end() - 1);
        CHECK(result == v.end());
        CHECK(v.size() == 3);
        CHECK(v[0].value == 0);
        CHECK(v[1].value == 1);
        CHECK(v[2].value == 2);
    }
    
    SECTION("mid single") {
        auto result = v.erase(v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 3);
        CHECK(v[0].value == 0);
        CHECK(v[1].value == 2);
        CHECK(v[2].value == 3);
    }
    
    SECTION("begin range") {
		auto result = v.erase(v.begin(), v.begin() + 2);
		CHECK(result == v.begin());
		CHECK(v.size() == 2);
		CHECK(v[0].value == 2);
		CHECK(v[1].value == 3);
	}
	
	SECTION("end range") {
        v.push_back(4);
		auto result = v.erase(v.begin() + 3, v.end());
		CHECK(result == v.end());
		CHECK(v.size() == 3);
		CHECK(v[0].value == 0);
		CHECK(v[1].value == 1);
		CHECK(v[2].value == 2);
	}
	
	SECTION("mid range") {
        v.push_back(4);
		auto result = v.erase(v.begin() + 1, v.end() - 2);
		CHECK(result == v.begin() + 1);
		CHECK(v.size() == 3);
		CHECK(v[0].value == 0);
		CHECK(v[1].value == 3);
		CHECK(v[2].value == 4);
	}
	
	SECTION("empty range") {
		auto result = v.erase(v.begin(), v.begin());
		CHECK(result == v.begin());
		CHECK(v.size() == 4);
		CHECK(v[0].value == 0);
		CHECK(v[1].value == 1);
		CHECK(v[2].value == 2);
		CHECK(v[3].value == 3);
	}
	
}
