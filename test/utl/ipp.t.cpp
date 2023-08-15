#include <catch/catch2.hpp>

#include <utl/ipp.hpp>

namespace {

template <size_t Align>
struct Object {
    alignas(Align) char data;
};

template <int Value>
struct __static_printer;

} // namespace

#define concat(a, b) concat_impl(a, b)
#define concat_impl(a, b) a##b

#define static_print(value) __static_printer<value> concat(__print_var, __LINE__)

static_assert(utl::sipp<int16_t*>::min_int() == -1);
static_assert(utl::sipp<int16_t*>::max_int() == 0);
static_assert(utl::sipp<int32_t*>::min_int() == -2);
static_assert(utl::sipp<int32_t*>::max_int() == 1);
static_assert(utl::sipp<int64_t*>::min_int() == -4);
static_assert(utl::sipp<int64_t*>::max_int() == 3);

static_assert(utl::ipp<int16_t*>::min_int() == 0);
static_assert(utl::ipp<int16_t*>::max_int() == 1);
static_assert(utl::ipp<int32_t*>::min_int() == 0);
static_assert(utl::ipp<int32_t*>::max_int() == 3);
static_assert(utl::ipp<int64_t*>::min_int() == 0);
static_assert(utl::ipp<int64_t*>::max_int() == 7);


TEST_CASE("ipp aggregate init") {
    utl::ipp<int*> p{};
    CHECK(p.pointer() == nullptr);
    CHECK(p.integer() == 0);
}

TEST_CASE("ipp") {
    SECTION("int") {
        utl::ipp<int*> p = 3;
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
        utl::ipp<Object<8>*> p = &obj;
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 0);
    }
    SECTION("int pointer constructor") {
        Object<8> obj;
        utl::ipp<Object<8>*> p = { 7, &obj };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 7);
    }
    SECTION("extended alignment type") {
        Object<16> obj;
        utl::ipp<Object<16>*> p = { 15, &obj };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == 15);
    }
    SECTION("signed ipp") {
        Object<16> obj;
        utl::sipp<Object<16>*> p = { -8, &obj };
        CHECK(p.pointer() == &obj);
        CHECK(p.integer() == -8);
        p.set_integer(7);
        CHECK(p.integer() == 7);
    }
}

namespace {

enum class E {
    One, Two, Three
};

} // namespace

TEST_CASE("epp") {
    long x;
    utl::epp<E, long*> p = { E::Three, &x };
    CHECK(p.enum_value() == E::Three);
    CHECK(p.pointer() == &x);
    p.set_enum(E::One);
    CHECK(p.enum_value() == E::One);
    CHECK(p.pointer() == &x);
}
