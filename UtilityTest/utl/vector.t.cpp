#include "Catch2.hpp"

#include <concepts>
#include <iosfwd>
#include <list>

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

struct X: utl_test::LifetimeCounter {
    X(TagAllocator<X> alloc = {}): alloc(alloc) {}
    X(int value, TagAllocator<X> alloc = {}): alloc(alloc), value(value) {}

    X(X const& rhs, TagAllocator<X> alloc = {}): alloc(alloc), value(rhs.value) {}
    X(X&& rhs, TagAllocator<X> alloc = {}): alloc(alloc), value(rhs.value) {}

    X& operator=(X const& rhs) {
        value = rhs.value;
        return *this;
    }
    X& operator=(X&& rhs) {
        value = rhs.value;
        return *this;
    }

    bool operator==(X const& rhs) const { return value == rhs.value; }

    TagAllocator<X> alloc;
    int value = 0;

    friend std::ostream& operator<<(std::ostream& str, X const& x) { return str << "{ " << x.value << " }"; }
};

template <typename>
std::size_t constexpr inlineCapacity = 0;

template <typename T, std::size_t N, typename A>
std::size_t constexpr inlineCapacity<utl::small_vector<T, N, A>> = N;

template <typename T>
using TaVector = utl::vector<T, TagAllocator<T>>;

template <typename T, size_t Size = utl::default_inline_capacity<T, TagAllocator<T>>>
using TaSmallVector = utl::small_vector<T, Size, TagAllocator<T>>;

} // namespace

#define VECTOR_TEST_CASE(T, ...)                                                                                       \
    TEMPLATE_TEST_CASE_SIG(__VA_ARGS__,                                                                                \
                           ((typename Vector, bool Small), Vector, Small),                                             \
                           (TaVector<T>, false),                                                                       \
                           (TaSmallVector<T>, true),                                                                   \
                           (TaSmallVector<T, 23>, true))

#define VECTOR_PRODUCT_TEST_CASE(T, ...)                                                                               \
    TEMPLATE_TEST_CASE_SIG(                                                                                            \
        __VA_ARGS__,                                                                                                   \
        ((typename VectorA, typename VectorB, bool SmallA, bool SmallB), VectorA, VectorB, SmallA, SmallB),            \
        (TaVector<T>, TaVector<T>, false, false),                                                                      \
        (TaVector<T>, TaSmallVector<T>, false, true),                                                                  \
        (TaVector<T>, TaSmallVector<T, 23>, false, true),                                                              \
        (TaSmallVector<T>, TaVector<T>, true, false),                                                                  \
        (TaSmallVector<T>, TaSmallVector<T>, true, true),                                                              \
        (TaSmallVector<T>, TaSmallVector<T, 23>, true, true),                                                          \
        (TaSmallVector<T, 23>, TaVector<T>, true, false),                                                              \
        (TaSmallVector<T, 23>, TaSmallVector<T>, true, true),                                                          \
        (TaSmallVector<T, 23>, TaSmallVector<T, 23>, true, true))

/// MARK: Constructors
VECTOR_TEST_CASE(int, "vector-construct-1", "[vector]") {
    X::reset();
    Vector v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, "vector-allocator-construct-2", "[vector]") {
    X::reset();
    Vector v(Tag(1));
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, "vector-allocator-propagate-construct-3", "[vector]") {
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    Vector v(count, X{ 1 }, Tag(1));
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    for (auto& i : v) {
        CHECK(i.alloc.tag == Tag(1));
        CHECK(i.value == 1);
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, "vector-allocator-propagate-construct-4", "[vector]") {
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    Vector v(count, Tag(1));
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    for (auto& i : v) {
        CHECK(i.alloc.tag == Tag(1));
        CHECK(i == X());
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, "vector-allocator-iterator-constructor", "[vector]") {
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    X data[5]{ { 3, alloc }, { 4, alloc }, { 2, alloc }, { -1, alloc }, { 10, alloc } };
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(std::begin(data), std::end(data), tag2);
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(v[0].alloc.tag == tag2);
    CHECK(v[0].value == 3);
    CHECK(v[1].alloc.tag == tag2);
    CHECK(v[1].value == 4);
    CHECK(v[2].alloc.tag == tag2);
    CHECK(v[2].value == 2);
    CHECK(v[3].alloc.tag == tag2);
    CHECK(v[3].value == -1);
    CHECK(v[4].alloc.tag == tag2);
    CHECK(v[4].value == 10);
    CHECK(X::liveObjects() == 10);
}

VECTOR_TEST_CASE(X, "vector-allocator-iterator-constructor-2", "[vector]") {
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    X data[1]{};
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(data, data + 0, tag2);
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 1);
}

namespace {
struct Y {
    int value;
    operator X() const { return X(value); }
};
} // namespace

VECTOR_TEST_CASE(X, "vector-allocator-iterator-converting-constructor", "[vector]") {
    X::reset();
    Y data[5]{ 3, 4, 2, -1, 10 };
    Vector v(std::begin(data), std::end(data), Tag(2));
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(v[0].alloc.tag == Tag(2));
    CHECK(v[0].value == 3);
    CHECK(v[1].alloc.tag == Tag(2));
    CHECK(v[1].value == 4);
    CHECK(v[2].alloc.tag == Tag(2));
    CHECK(v[2].value == 2);
    CHECK(v[3].alloc.tag == Tag(2));
    CHECK(v[3].value == -1);
    CHECK(v[4].alloc.tag == Tag(2));
    CHECK(v[4].value == 10);
    CHECK(X::liveObjects() == 5);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-copy-ctor", "[vector]") {
    X::reset();
    VectorA v(Tag{ 1 });
    auto const count = GENERATE(0, 2, 10);
    for (std::size_t i = 0; i < count; ++i) {
        v.emplace_back(i + 1);
    }
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(v, tag2);
    for (std::size_t i = 0; i < count; ++i) {
        v[i].alloc.tag = tag2;
        v[i].value     = i + 1;
    }
    CHECK(X::liveObjects() == 2 * count);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-copy-assign", "[vector]") {
    VectorA v(Tag(1));
    auto const count = GENERATE(0, 2, 5, 10);
    for (std::size_t i = 0; i < count; ++i) {
        v.emplace_back(i + 1);
    }
    auto const wCount = GENERATE(0, 2, 5, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    CHECK(X::liveObjects() == count + wCount);
    w = v;
    REQUIRE(w.size() == count);
    CHECK(w.capacity() >= count);
    for (std::size_t i = 0; i < count; ++i) {
        CHECK(w[i].alloc.tag == tag2);
        CHECK(w[i].value == i + 1);
    }
    CHECK(X::liveObjects() == 2 * count);
}

VECTOR_TEST_CASE(X, "vector-allocator-copy-assign-ilist", "[vector]") {
    X::reset();
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    Vector w(wCount, tag2);
    w = { 1, 2, 3 };
    REQUIRE(w.size() == 3);
    CHECK(w.capacity() >= 3);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    CHECK(w[2].alloc.tag == tag2);
    CHECK(w[2].value == 3);
    CHECK(X::liveObjects() == 3);
    w = {};
    REQUIRE(w.size() == 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-move-ctor", "[vector]") {
    X::reset();
    VectorA v({ 1, 2 }, Tag(1));
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    if (!SmallA && !SmallB && v.get_allocator() == w.get_allocator()) {
        CHECK(X::liveObjects() == 2);
    }
    else {
        CHECK(X::liveObjects() == 4);
    }
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-allocator-move-assign", "[vector]") {
    X::reset();
    VectorA v({ 1, 2 }, Tag(1));
    auto const wCount = GENERATE(0, 1, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    w = std::move(v);
    REQUIRE(w.size() == 2);
    CHECK(w.capacity() >= 2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    if (v.get_allocator() == w.get_allocator() && !SmallA && (!SmallB || wCount > inlineCapacity<VectorB>)) {
        CHECK(X::liveObjects() == 2);
    }
    else {
        CHECK(X::liveObjects() == 4);
    }
}

VECTOR_TEST_CASE(X, "vector-allocator-ilist", "[vector]") {
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    Vector v({ { 1, alloc }, { 2, alloc }, { 4, alloc } }, Tag{ 2 });
    REQUIRE(v.size() == 3);
    if (!Small) {
        CHECK(v.capacity() == 3);
    }
    CHECK(v[0].alloc.tag == Tag{ 2 });
    CHECK(v[0].value == 1);
    CHECK(v[1].alloc.tag == Tag{ 2 });
    CHECK(v[1].value == 2);
    CHECK(v[2].alloc.tag == Tag{ 2 });
    CHECK(v[2].value == 4);
    CHECK(X::liveObjects() == 3);
}

VECTOR_TEST_CASE(X, "vector-allocator-ilist-2", "[vector]") {
    X::reset();
    Vector v({}, Tag{ 2 });
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, "vector-allocator-propagate-emplace", "[vector]") {
    X::reset();
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
    CHECK(X::liveObjects() == 2);
}

VECTOR_TEST_CASE(X, "vector-allocator-reserve", "[vector]") {
    X::reset();
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    auto const newCap = GENERATE(0, 5, 50);
    v.reserve(newCap);
    REQUIRE(v.size() == size);
    CHECK(X::liveObjects() == size);
    CHECK(v.capacity() >= newCap);
    CHECK(X::liveObjects() == size);
}

VECTOR_TEST_CASE(X, "vector-allocator-resize", "[vector]") {
    X::reset();
    auto const size = GENERATE(0, 5, 50);
    Vector v(size, Tag(1));
    CHECK(X::liveObjects() == size);
    auto const newSize = GENERATE(0, 5, 50);
    v.resize(newSize);
    CHECK(X::liveObjects() == newSize);
    REQUIRE(v.size() == newSize);
    CHECK(v.capacity() >= newSize);
}

VECTOR_TEST_CASE(X, "vector-allocator-insert-1-2", "[vector]") {
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    X x(-1);
    SECTION("begin") {
        auto const result = v.insert(v.begin(), x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<X>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, "vector-allocator-insert-3", "[vector]") {
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    X x(-1);
    REQUIRE(X::liveObjects() == 4 + 1);
    SECTION("into-empty") {
        v                 = Vector{};
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ x, x, x });
        CHECK(X::liveObjects() == 3 + 1);
    }
    SECTION("into-empty/2") {
        v                 = Vector{};
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{});
        CHECK(X::liveObjects() == 0 + 1);
    }
    SECTION("begin") {
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ x, x, x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("begin/2") {
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("begin/3") {
        auto const result = v.insert(v.begin(), 1, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, x, x, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("mid/2") {
        v.push_back(X(4));
        v.push_back(X(5));
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, x, x, x, 1, 2, 3, 4, 5 });
        CHECK(X::liveObjects() == 9 + 1);
    }
    SECTION("mid/3") {
        auto const result = v.insert(v.begin() + 1, 0, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("mid/4") {
        auto const result = v.insert(v.begin() + 1, 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, 3, x);
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<X>{ 0, 1, 2, x, x, x, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end - 1/2") {
        auto const result = v.insert(v.end() - 1, 0, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end - 1/3") {
        auto const result = v.insert(v.end() - 1, 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<X>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 2") {
        auto const result = v.insert(v.end() - 2, 3, x);
        CHECK(result == v.end() - 5);
        CHECK(v == TaVector<X>{ 0, 1, x, x, x, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), 3, x);
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3, x, x, x });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end/2") {
        auto const result = v.insert(v.end(), 0, x);
        CHECK(result == v.end() - 0);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end/3") {
        auto const result = v.insert(v.end(), 1, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, "vector-allocator-insert-4", "[vector]") {
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    std::list<X> data;
    std::size_t const count = GENERATE(0, 3, 10);
    for (std::size_t i = 0; i < count; ++i) {
        data.emplace_back(-(int)(i + 1));
    }
    auto makeRef = [&](int position) {
        assert(position <= 4);
        Vector result;
        int i = 0;
        for (; i < position; ++i) {
            result.push_back(i);
        }
        for (auto& i : data) {
            result.push_back(i);
        }
        for (; i < 4; ++i) {
            result.push_back(i);
        }
        return result;
    };
    SECTION("begin") {
        auto const result = v.insert(v.begin(), std::begin(data), std::end(data));
        CHECK(result == v.begin());
        CHECK(v == makeRef(0));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, std::begin(data), std::end(data));
        CHECK(result == v.begin() + 1);
        CHECK(v == makeRef(1));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, std::begin(data), std::end(data));
        CHECK(result == v.end() - 1 - data.size());
        CHECK(v == makeRef(3));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), std::begin(data), std::end(data));
        CHECK(result == v.end() - data.size());
        CHECK(v == makeRef(4));
        CHECK(X::liveObjects() == 4 + 2 * count);
    }
}

VECTOR_TEST_CASE(X, "vector-allocator-insert-5", "[vector]") {
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    SECTION("begin") {
        auto const result = v.insert(v.begin(), { -1, -2, -3 });
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ -1, -2, -3, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("begin/2") {
        auto const result = v.insert(v.begin(), {});
        CHECK(result == v.begin());
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, { -1, -2, -3 });
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, -1, -2, -3, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("mid/2") {
        auto const result = v.insert(v.begin() + 1, {});
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, { -1, -2, -3 });
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<X>{ 0, 1, 2, -1, -2, -3, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end - 1/2") {
        auto const result = v.insert(v.end() - 1, {});
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), { -1, -2, -3 });
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<X>{ 0, 1, 2, 3, -1, -2, -3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end/2") {
        auto const result = v.insert(v.end(), {});
        CHECK(result == v.end());
        CHECK(v == TaVector<X>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-move-construct", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize = v.size();
    VectorB w        = std::move(v);
    CHECK(w.size() == vSize);
    CHECK(w.capacity() >= w.size());
    CHECK(X::liveObjects() >= count);
    v.clear();
    w.clear();
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-move-assign", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize      = v.size();
    auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
    VectorB w(wInitCount);
    CHECK(X::liveObjects() == count + wInitCount);
    w = std::move(v);
    CHECK(w.size() == vSize);
    CHECK(w.capacity() >= vSize);
    CHECK(X::liveObjects() >= count);
    v.clear();
    w.clear();
    CHECK(X::liveObjects() == 0);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-copy-construct", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    VectorB w = v;
    CHECK(w.size() == v.size());
    CHECK(X::liveObjects() == 2 * count);
    w.clear();
    CHECK(X::liveObjects() == count);
}

VECTOR_PRODUCT_TEST_CASE(X, "vector-copy-assign", "[vector]") {
    X::reset();
    VectorA v;
    auto const count = GENERATE(0, 1, 54, 64, 139);
    for (int i = 0; i < count; ++i) {
        v.emplace_back();
    }
    CHECK(X::liveObjects() == count);
    auto const vSize      = v.size();
    auto const wInitCount = GENERATE(0, 1, 54, 64, 139);
    VectorB w(wInitCount);
    CHECK(X::liveObjects() == count + wInitCount);
    w = v;
    CHECK(w.size() == vSize);
    CHECK(X::liveObjects() == 2 * count);
    w.clear();
    CHECK(X::liveObjects() == count);
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
    SECTION("empty range/2") {
        auto result = v.erase(v.begin() + 1, v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 4);
        CHECK(v[0].value == 0);
        CHECK(v[1].value == 1);
        CHECK(v[2].value == 2);
        CHECK(v[3].value == 3);
    }
    SECTION("empty range/3") {
        auto result = v.erase(v.end(), v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 4);
        CHECK(v[0].value == 0);
        CHECK(v[1].value == 1);
        CHECK(v[2].value == 2);
        CHECK(v[3].value == 3);
    }
}

VECTOR_TEST_CASE(X, "vector-at", "[vector]") {
    Vector v = { 0, 1, 2, 3 };
    CHECK(v.at(3) == 3);
    CHECK_THROWS_AS(v.at(4), std::out_of_range);
}
