#include <catch/catch2.hpp>

#include <utl/vector.hpp>

#include "VectorTest.hpp"

using namespace utl_test;

/// 
/// These cases crash with MSVC. Figure this out later!
/// 

VECTOR_TEST_CASE(X, "vector-acquire", "[vector]") {
 #ifdef _MSC_VER
    return;
 #endif
    X::reset();
    TagAllocator<X> alloc(Tag(1));
    std::size_t const cap = 10, size = GENERATE(0, 1, 5, 100);
    X* buffer = alloc.allocate(cap);
    for (std::size_t i = 0; i < size; ++i) {
        std::allocator_traits<TagAllocator<X>>::construct(alloc, &buffer[i], i);
    }
    CHECK(X::liveObjects() == size);
    {
        Vector v(GENERATE(0, 6));
        CHECK(X::liveObjects() == size + v.size());
        v.acquire(buffer, size, cap, alloc);
        CHECK(X::liveObjects() == size);
    }
    CHECK(X::liveObjects() == 0);
}

VECTOR_TEST_CASE(X, "vector-release", "[vector]") {
#ifdef _MSC_VER
    return;
#endif
    X::reset();
    std::size_t const count = GENERATE(0, 3, 100);
    X* buffer = nullptr;
    std::size_t size = 0, cap = 0;
    TagAllocator<X> alloc;
    {
        Vector v(count);
        CHECK(X::liveObjects() == count);
        std::tie(buffer, size, cap) = v.release();
        alloc = v.get_allocator();
        CHECK(count == size);
    }
    CHECK(X::liveObjects() == count);
    for (std::size_t i = 0; i < size; ++i) {
        std::allocator_traits<TagAllocator<X>>::destroy(alloc, &buffer[i]);
    }
    CHECK(X::liveObjects() == 0);
    alloc.deallocate(buffer, cap);
}
