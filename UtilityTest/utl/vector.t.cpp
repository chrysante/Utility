#include "Catch2.hpp"

#include <concepts>
#include <iosfwd>
#include <list>
#include <memory>

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
            std::construct_at(ptr, *this, std::forward<Args>(args)...);
        }
        else if constexpr (std::is_constructible_v<T, Args..., TagAllocator>) {
            std::construct_at(ptr, std::forward<Args>(args)..., *this);
        }
        else {
            std::construct_at(ptr, std::forward<Args>(args)...);
        }
    }

    bool operator==(TagAllocator const&) const = default;

    TagAllocator() { tag = Tag{ 0 }; }
    TagAllocator(Tag t) { tag = t; }
    template <typename U>
    TagAllocator(TagAllocator<U> const& rhs) {
        tag = rhs.tag;
    }

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

struct TRX: X {
    TRX(TagAllocator<TRX> alloc = {}): X(alloc) {}
    TRX(int value, TagAllocator<TRX> alloc = {}): X(value, alloc) {}

    TRX(TRX const& rhs, TagAllocator<TRX> alloc = {}): X(rhs, alloc) {}
    TRX(TRX&& rhs, TagAllocator<TRX> alloc = {}): X(std::move(rhs), alloc) {}

    TRX& operator=(TRX const& rhs) {
        this->X::operator=(rhs);
        return *this;
    }
    TRX& operator=(TRX&& rhs) {
        this->X::operator=(std::move(rhs));
        return *this;
    }

    bool operator==(TRX const& rhs) const { return value == rhs.value; }
};

static_assert(std::constructible_from<TRX, TRX const&, TagAllocator<TRX>>);

} // namespace

template <>
struct utl::is_trivially_relocatable<TRX>: std::true_type {};

template <typename>
std::size_t constexpr inlineCapacity = 0;

template <typename T, std::size_t N, typename A>
std::size_t constexpr inlineCapacity<utl::small_vector<T, N, A>> = N;

template <typename T>
using TaVector = utl::vector<T, TagAllocator<T>>;

template <typename T, size_t Size = utl::default_inline_capacity<T, TagAllocator<T>>>
using TaSmallVector = utl::small_vector<T, Size, TagAllocator<T>>;

#define TEST_ARG_LIST(T) (TaVector<T>, false), (TaSmallVector<T>, true), (TaSmallVector<T, 23>, true)
#define PRODUCT_TEST_ARG_LIST(T)                                                                                       \
    (TaVector<T>, TaVector<T>, false, false), (TaVector<T>, TaSmallVector<T, 0>, false, true),                         \
        (TaVector<T>, TaSmallVector<T>, false, true), (TaVector<T>, TaSmallVector<T, 23>, false, true),                \
        (TaSmallVector<T>, TaVector<T>, true, false), (TaSmallVector<T>, TaSmallVector<T, 0>, true, true),             \
        (TaSmallVector<T>, TaSmallVector<T>, true, true), (TaSmallVector<T>, TaSmallVector<T, 23>, true, true),        \
        (TaSmallVector<T, 23>, TaVector<T>, true, false), (TaSmallVector<T, 23>, TaSmallVector<T, 0>, true, true),     \
        (TaSmallVector<T, 23>, TaSmallVector<T>, true, true),                                                          \
        (TaSmallVector<T, 23>, TaSmallVector<T, 23>, true, true), (TaSmallVector<T, 0>, TaVector<T>, true, false),     \
        (TaSmallVector<T, 0>, TaSmallVector<T, 0>, true, true), (TaSmallVector<T, 0>, TaSmallVector<T>, true, true),   \
        (TaSmallVector<T, 0>, TaSmallVector<T, 23>, true, true)

#define VECTOR_TEST_CASE(...)                UTL_VFUNC(VECTOR_TEST_CASE_, __VA_ARGS__)
#define VECTOR_TEST_CASE_3(T, NAME, TAGS)    VECTOR_TEST_CASE_IMPL(NAME, TAGS, TEST_ARG_LIST(T))
#define VECTOR_TEST_CASE_4(T, U, NAME, TAGS) VECTOR_TEST_CASE_IMPL(NAME, TAGS, TEST_ARG_LIST(T), TEST_ARG_LIST(U))

#define VECTOR_PRODUCT_TEST_CASE(...)             UTL_VFUNC(VECTOR_PRODUCT_TEST_CASE_, __VA_ARGS__)
#define VECTOR_PRODUCT_TEST_CASE_3(T, NAME, TAGS) VECTOR_PRODUCT_TEST_CASE_IMPL(NAME, TAGS, PRODUCT_TEST_ARG_LIST(T))
#define VECTOR_PRODUCT_TEST_CASE_4(T, U, NAME, TAGS)                                                                   \
    VECTOR_PRODUCT_TEST_CASE_IMPL(NAME, TAGS, PRODUCT_TEST_ARG_LIST(T), PRODUCT_TEST_ARG_LIST(U))

#define VECTOR_TEST_CASE_IMPL(NAME, TAGS, ...)                                                                         \
    TEMPLATE_TEST_CASE_SIG(NAME, TAGS, ((typename Vector, bool Small), Vector, Small), __VA_ARGS__)

#define VECTOR_PRODUCT_TEST_CASE_IMPL(NAME, TAGS, ...)                                                                 \
    TEMPLATE_TEST_CASE_SIG(                                                                                            \
        NAME,                                                                                                          \
        TAGS,                                                                                                          \
        ((typename VectorA, typename VectorB, bool SmallA, bool SmallB), VectorA, VectorB, SmallA, SmallB),            \
        __VA_ARGS__)

static_assert(sizeof(utl::vector<int>) == 2 * 4 + sizeof(void*));
static_assert(sizeof(utl::vector<char>) == 24);

/// MARK: Constructors
VECTOR_TEST_CASE(X, TRX, "vector-construct-1", "[vector]") {
    X::reset();
    Vector v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-construct-2", "[vector]") {
    X::reset();
    Vector v(Tag(1));
    CHECK(v.size() == 0);
    CHECK(v.capacity() >= 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-construct-3", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    Vector v(count, T{ 1 }, Tag(1));
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    for (auto& i : v) {
        CHECK(i.alloc.tag == Tag(1));
        CHECK(i.value == 1);
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-construct-4", "[vector]") {
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-constructor", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    T data[5]{ { 3, alloc }, { 4, alloc }, { 2, alloc }, { -1, alloc }, { 10, alloc } };
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-constructor-2", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    T data[1]{};
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    Vector v(data, data + 0, tag2);
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 1);
}

namespace {
struct Y {
    int value;
    operator X() const { return X(value); }
    operator TRX() const { return TRX(value); }
};
} // namespace

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-converting-constructor", "[vector]") {
    X::reset();
    Y data[5]{ 3, 4, 2, -1, 10 };
    Vector v(std::begin(data), (std::end(std::as_const(data))), Tag(1));
    REQUIRE(v.size() == 5);
    CHECK(v.capacity() >= 5);
    CHECK(X::liveObjects() == 5);
    for (std::size_t i = 0; i < 5; ++i) {
        CHECK(v[i].alloc.tag == Tag(1));
        CHECK(v[i].value == data[i].value);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-iterator-converting-constructor/2", "[vector]") {
    X::reset();
    auto const count = 10;
    utl::iota io(count);
    Vector v(io.begin(), io.end());
    REQUIRE(v.size() == count);
    CHECK(v.capacity() >= count);
    CHECK(X::liveObjects() == count);
    for (std::size_t i = 0; i < count; ++i) {
        CHECK(v[i].value == i);
    }
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-copy-ctor", "[vector]") {
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

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-copy-assign", "[vector]") {
    X::reset();
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
        INFO(v);
        INFO(w);
        CHECK(w[i].alloc.tag == tag2);
        CHECK(w[i].value == i + 1);
    }
    CHECK(X::liveObjects() == 2 * count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-copy-assign-ilist", "[vector]") {
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

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-move-ctor", "[vector]") {
    X::reset();
    VectorA v({ 1, 2 }, Tag(1));
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    CHECK(w[0].alloc.tag == tag2);
    CHECK(w[0].value == 1);
    CHECK(w[1].alloc.tag == tag2);
    CHECK(w[1].value == 2);
    v.clear();
    CHECK(X::liveObjects() == 2);
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-allocator-move-assign", "[vector]") {
    X::reset();
    auto const count = GENERATE(0, 2, 10);
    VectorA v(Tag(1));
    for (auto i : utl::iota(count)) {
        v.emplace_back(i);
    }
    auto const wCount = GENERATE(0, 2, 10);
    auto const tag2   = GENERATE(Tag(1), Tag(2));
    VectorB w(wCount, tag2);
    w = std::move(v);
    REQUIRE(w.size() == count);
    CHECK(w.capacity() >= count);
    for (std::size_t i = 0; i < count; ++i) {
        CHECK(w[i].alloc.tag == tag2);
        CHECK(w[i].value == i);
    }
    v.clear();
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-ilist", "[vector]") {
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-ilist-2", "[vector]") {
    X::reset();
    Vector v({}, Tag{ 2 });
    REQUIRE(v.size() == 0);
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-propagate-emplace", "[vector]") {
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-reserve", "[vector]") {
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-resize", "[vector]") {
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

static void reserveAdditional(auto& v, std::size_t count) {
    auto const m = GENERATE(0u, 1u);
    v.reserve(v.size() + count * m);
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-1-2", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, 1);
    T x(-1);
    SECTION("begin") {
        auto const result = v.insert(v.begin(), x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-3", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    T x(-1);
    REQUIRE(X::liveObjects() == 4 + 1);
    SECTION("into-empty") {
        v = Vector{};
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, x, x });
        CHECK(X::liveObjects() == 3 + 1);
    }
    SECTION("into-empty/2") {
        v = Vector{};
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{});
        CHECK(X::liveObjects() == 0 + 1);
    }
    SECTION("begin") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin(), 3, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, x, x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("begin/2") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 0, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("begin/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin(), 1, x);
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ x, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("mid") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, x, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("mid/2") {
        v.push_back(T(4));
        v.push_back(T(5));
        reserveAdditional(v, 3);
        auto const result = v.insert(v.begin() + 1, 3, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, x, x, 1, 2, 3, 4, 5 });
        CHECK(X::liveObjects() == 9 + 1);
    }
    SECTION("mid/3") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.begin() + 1, 0, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("mid/4") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.begin() + 1, 1, x);
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, x, 1, 2, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 1") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end() - 1, 3, x);
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, x, x, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end - 1/2") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.end() - 1, 0, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end - 1/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.end() - 1, 1, x);
        CHECK(result == v.end() - 2);
        CHECK(v == TaVector<T>{ 0, 1, 2, x, 3 });
        CHECK(X::liveObjects() == 5 + 1);
    }
    SECTION("end - 2") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end() - 2, 3, x);
        CHECK(result == v.end() - 5);
        CHECK(v == TaVector<T>{ 0, 1, x, x, x, 2, 3 });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end") {
        reserveAdditional(v, 3);
        auto const result = v.insert(v.end(), 3, x);
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x, x, x });
        CHECK(X::liveObjects() == 7 + 1);
    }
    SECTION("end/2") {
        reserveAdditional(v, 0);
        auto const result = v.insert(v.end(), 0, x);
        CHECK(result == v.end() - 0);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4 + 1);
    }
    SECTION("end/3") {
        reserveAdditional(v, 1);
        auto const result = v.insert(v.end(), 1, x);
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, x });
        CHECK(X::liveObjects() == 5 + 1);
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-4", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    std::size_t const count = GENERATE(0, 3, 10);
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, count);
    std::list<T> data;
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

VECTOR_TEST_CASE(X, TRX, "vector-allocator-insert-5", "[vector]") {
    using T = typename Vector::value_type;
    X::reset();
    Vector v({ 0, 1, 2, 3 }, Tag(1));
    reserveAdditional(v, 3);
    SECTION("begin") {
        auto const result = v.insert(v.begin(), { -1, -2, -3 });
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ -1, -2, -3, 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("begin/2") {
        auto const result = v.insert(v.begin(), {});
        CHECK(result == v.begin());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("mid") {
        auto const result = v.insert(v.begin() + 1, { -1, -2, -3 });
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, -1, -2, -3, 1, 2, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("mid/2") {
        auto const result = v.insert(v.begin() + 1, {});
        CHECK(result == v.begin() + 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end - 1") {
        auto const result = v.insert(v.end() - 1, { -1, -2, -3 });
        CHECK(result == v.end() - 4);
        CHECK(v == TaVector<T>{ 0, 1, 2, -1, -2, -3, 3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end - 1/2") {
        auto const result = v.insert(v.end() - 1, {});
        CHECK(result == v.end() - 1);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
    SECTION("end") {
        auto const result = v.insert(v.end(), { -1, -2, -3 });
        CHECK(result == v.end() - 3);
        CHECK(v == TaVector<T>{ 0, 1, 2, 3, -1, -2, -3 });
        CHECK(X::liveObjects() == 7);
    }
    SECTION("end/2") {
        auto const result = v.insert(v.end(), {});
        CHECK(result == v.end());
        CHECK(v == TaVector<T>{ 0, 1, 2, 3 });
        CHECK(X::liveObjects() == 4);
    }
}

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-move-construct", "[vector]") {
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

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-move-assign", "[vector]") {
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

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-copy-construct", "[vector]") {
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

VECTOR_PRODUCT_TEST_CASE(X, TRX, "vector-copy-assign", "[vector]") {
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

VECTOR_TEST_CASE(X, TRX, "vector-erase", "[vector]") {
    X::reset();
    Vector v = { 0, 1, 2, 3, 4, 5 };
    REQUIRE(X::liveObjects() == 6);
    SECTION("all") {
        auto result = v.erase(v.begin(), v.end());
        CHECK(result == v.end());
        CHECK(v.empty());
        CHECK(X::liveObjects() == 0);
    }
    SECTION("begin single") {
        auto result = v.erase(v.begin());
        CHECK(result == v.begin());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 1, 2, 3, 4, 5 });
    }
    SECTION("end single") {
        auto result = v.erase(v.end() - 1);
        CHECK(result == v.end());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 1, 2, 3, 4 });
    }
    SECTION("mid single") {
        auto result = v.erase(v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 2, 3, 4, 5 });
    }
    SECTION("begin range") {
        auto result = v.erase(v.begin(), v.begin() + 2);
        CHECK(result == v.begin());
        CHECK(v.size() == 4);
        CHECK(X::liveObjects() == 4);
        CHECK(v == Vector{ 2, 3, 4, 5 });
    }
    SECTION("end range") {
        auto result = v.erase(v.begin() + 3, v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 3);
        CHECK(X::liveObjects() == 3);
        CHECK(v == Vector{ 0, 1, 2 });
    }
    SECTION("mid range") {
        auto result = v.erase(v.begin() + 1, v.end() - 2);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 3);
        CHECK(X::liveObjects() == 3);
        CHECK(v == Vector{ 0, 4, 5 });
    }
    SECTION("empty range") {
        auto result = v.erase(v.begin(), v.begin());
        CHECK(result == v.begin());
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("empty range/2") {
        auto result = v.erase(v.begin() + 1, v.begin() + 1);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("empty range/3") {
        auto result = v.erase(v.end(), v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 6);
        CHECK(X::liveObjects() == 6);
        CHECK(v == Vector{ 0, 1, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range") {
        auto result = v.erase(v.begin(), v.begin() + 1);
        CHECK(result == v.begin());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 1, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range/2") {
        auto result = v.erase(v.begin() + 1, v.begin() + 2);
        CHECK(result == v.begin() + 1);
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 2, 3, 4, 5 });
    }
    SECTION("one-elem-empty range/3") {
        auto result = v.erase(v.end() - 1, v.end());
        CHECK(result == v.end());
        CHECK(v.size() == 5);
        CHECK(X::liveObjects() == 5);
        CHECK(v == Vector{ 0, 1, 2, 3, 4 });
    }
}

VECTOR_TEST_CASE(X, TRX, "vector-at", "[vector]") {
    Vector v = { 0, 1, 2, 3 };
    CHECK(v.at(3) == 3);
    CHECK_THROWS_AS(v.at(4), std::out_of_range);
}

using MoveOnly = std::unique_ptr<X>;

static MoveOnly makeMoveOnly(X x) {
    return std::make_unique<X>(std::move(x));
}

VECTOR_PRODUCT_TEST_CASE(MoveOnly, "vector-move-only", "[vector]") {
    X::reset();
    VectorA v(Tag(1));
    v.push_back(MoveOnly());
    auto const count = GENERATE(0, 5, 200);
    for (int i = 1; i <= count; ++i) {
        v.push_back(makeMoveOnly(i));
    }
    CHECK(v[0] == nullptr);
    for (int i = 1; i <= count; ++i) {
        CHECK(*v[i] == X(i));
    }
    CHECK(X::liveObjects() == count);
    auto const tag2 = GENERATE(Tag(1), Tag(2));
    VectorB w(std::move(v), tag2);
    v.clear();
    CHECK(w[0] == nullptr);
    for (int i = 1; i <= count; ++i) {
        CHECK(*w[i] == X(i));
    }
    CHECK(X::liveObjects() == count);
}

VECTOR_TEST_CASE(X, TRX, "vector-iterate", "[vector]") {
    Vector v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    for (auto [i, x] : utl::enumerate(v)) {
        CHECK(x == X(i));
    }
    int i = 19;
    for (auto itr = v.rbegin(); itr != v.rend(); ++itr, --i) {
        auto&& x = *itr;
        CHECK(x == X(i));
    }
}
