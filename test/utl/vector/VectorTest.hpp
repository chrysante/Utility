#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <utl/vector.hpp>

#include "utl/LifetimeCounter.hpp"

namespace utl_test {

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

template <typename>
std::size_t constexpr inlineCapacity = 0;

template <typename T, std::size_t N, typename A>
std::size_t constexpr inlineCapacity<utl::small_vector<T, N, A>> = N;

template <typename T>
using TaVector = utl::vector<T, TagAllocator<T>>;

template <typename T, size_t Size = utl::default_inline_capacity<T, TagAllocator<T>>>
using TaSmallVector = utl::small_vector<T, Size, TagAllocator<T>>;

} // namespace utl_test

template <>
struct utl::is_trivially_relocatable<utl_test::TRX>: std::true_type {};

#define TEST_ARG_LIST(T)                                                                                               \
    (utl_test::TaVector<T>, false), (utl_test::TaSmallVector<T>, true), (utl_test::TaSmallVector<T, 23>, true)

#define PRODUCT_TEST_ARG_LIST(T)                                                                                       \
    (utl_test::TaVector<T>, utl_test::TaVector<T>, false, false),                                                      \
        (utl_test::TaVector<T>, utl_test::TaSmallVector<T, 0>, false, true),                                           \
        (utl_test::TaVector<T>, utl_test::TaSmallVector<T>, false, true),                                              \
        (utl_test::TaVector<T>, utl_test::TaSmallVector<T, 23>, false, true),                                          \
        (utl_test::TaSmallVector<T>, utl_test::TaVector<T>, true, false),                                              \
        (utl_test::TaSmallVector<T>, utl_test::TaSmallVector<T, 0>, true, true),                                       \
        (utl_test::TaSmallVector<T>, utl_test::TaSmallVector<T>, true, true),                                          \
        (utl_test::TaSmallVector<T>, utl_test::TaSmallVector<T, 23>, true, true),                                      \
        (utl_test::TaSmallVector<T, 23>, utl_test::TaVector<T>, true, false),                                          \
        (utl_test::TaSmallVector<T, 23>, utl_test::TaSmallVector<T, 0>, true, true),                                   \
        (utl_test::TaSmallVector<T, 23>, utl_test::TaSmallVector<T>, true, true),                                      \
        (utl_test::TaSmallVector<T, 23>, utl_test::TaSmallVector<T, 23>, true, true),                                  \
        (utl_test::TaSmallVector<T, 0>, utl_test::TaVector<T>, true, false),                                           \
        (utl_test::TaSmallVector<T, 0>, utl_test::TaSmallVector<T, 0>, true, true),                                    \
        (utl_test::TaSmallVector<T, 0>, utl_test::TaSmallVector<T>, true, true),                                       \
        (utl_test::TaSmallVector<T, 0>, utl_test::TaSmallVector<T, 23>, true, true)

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
    TEMPLATE_TEST_CASE_SIG(NAME,                                                                                       \
                           TAGS,                                                                                       \
                           ((typename VectorA, typename VectorB, bool SmallA, bool SmallB),                            \
                            VectorA,                                                                                   \
                            VectorB,                                                                                   \
                            SmallA,                                                                                    \
                            SmallB),                                                                                   \
                           __VA_ARGS__)
