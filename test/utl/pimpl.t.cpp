#include <catch2/catch_test_macros.hpp>
#include <utl/pimpl.hpp>

namespace {

struct Base {
    explicit Base(int value): value(value) {}
    virtual ~Base() = default;
    virtual void f(int&) const = 0;
    int value;
};

struct X: Base {
    X(int value): Base(value) {}
    void f(int& x) const override { x = 1; }
};

} // namespace

TEST_CASE("local_pimpl") {
    utl::local_pimpl<Base, 16> p(utl::derived_tag<X>, 1);
    CHECK(p->value == 1);
    int i = 0;
    p->f(i);
    CHECK(i == 1);
}

namespace {

// We declare these classes here and leave them undefined to test that
// `local_pimpl` can be instantiated with an incomplete type

struct TestMove {
    TestMove();
    TestMove(TestMove const&) = delete;
    TestMove(TestMove&&);
    TestMove& operator=(TestMove const&) = delete;
    TestMove& operator=(TestMove&&);
    ~TestMove();

    struct Impl;
    utl::local_pimpl<Impl, 16> impl;
};

struct TestCopy {
    TestCopy();
    TestCopy(TestCopy const&);
    TestCopy& operator=(TestCopy const&);
    ~TestCopy();

    struct Impl;
    utl::local_pimpl<Impl, 16> impl;
};

} // namespace
