#include <catch2/catch_test_macros.hpp>
#include <utl/ipp.hpp>

namespace {

template <size_t Align>
struct Object {
    alignas(Align) char data;
};

template <int Value>
struct __static_printer;

} // namespace

#define concat(a, b)      concat_impl(a, b)
#define concat_impl(a, b) a##b

#define static_print(value)                                                    \
    __static_printer<value> concat(__print_var, __LINE__)

TEST_CASE("ipp aggregate init") {
    utl::ipp<int*, unsigned, 2> p{};
    CHECK(p.pointer() == nullptr);
    CHECK(p.integer() == 0);
}

TEST_CASE("ipp") {
    SECTION("int") {
        utl::ipp<int*, unsigned, 2> p = 3;
        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 3);
        p.set_integer(1);
        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 1);
        int x;
        p.set_pointer(&x);
        CHECK(p.pointer() == &x);
        CHECK(p.integer() == 1);
    }
    SECTION("pointer constructor") {
        Object<8> obj;
        utl::ipp<Object<8>*, unsigned, 3> p = &obj;
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 0);
    }
    SECTION("int pointer constructor") {
        Object<8> obj;
        utl::ipp<Object<8>*, unsigned, 3> p = { &obj, 7 };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 7);
    }
    SECTION("extended alignment type") {
        Object<16> obj;
        utl::ipp<Object<16>*, unsigned, 4> p = { &obj, 15 };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 15);
    }
    SECTION("signed ipp") {
        Object<16> obj;
        utl::ipp<Object<16>*, unsigned, 4> p = { &obj, 15 };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 15);
        p.set_integer(7);
        CHECK(p.integer() == 7);
    }
}

namespace {

enum class E { One, Two, Three };

} // namespace

TEST_CASE("ipp with enum") {
    uint64_t x;
    utl::ipp<uint64_t*, E, 3> p = { &x, E::Three };
    CHECK(p.integer() == E::Three);
    CHECK(p.pointer() == &x);
    p.set_integer(E::One);
    CHECK(p.integer() == E::One);
    CHECK(p.pointer() == &x);
    auto [e, q] = p;
    CHECK(e == E::One);
    CHECK(q == &x);
}

namespace {

struct Incomplete;

} // namespace

TEST_CASE("ipp with incomplete pointee type") {
    auto* ptr = reinterpret_cast<Incomplete*>(0xDEAD'BEEF'0);
    utl::ipp<Incomplete*, E, 1> p = { ptr, E::Two };
    CHECK(p.integer() == E::Two);
    CHECK(p.pointer() == ptr);
    p.set_integer(E::One);
    CHECK(p.integer() == E::One);
}
