#include <catch2/catch_test_macros.hpp>
#include <utl/function_view.hpp>

static int g() {
    return 1;
}

TEST_CASE("function_view parameter") {
    auto f = [](utl::function_view<int()> cb) { return cb(); };
    CHECK(f([] { return 0; }) == 0);
    CHECK(f(g) == 1);
    // Member pointers
    struct X {
        int f() const { return 2; }
        int value;
    };
    auto f2 = [](utl::function_view<int(X const&)> cb, X const& x) {
        return cb(x);
    };
    CHECK(f2(&X::f, X{}) == 2);
    CHECK(f2(&X::value, X{ 3 }) == 3);
}

TEST_CASE("function_view references") {
    struct NonCopyable {
        NonCopyable(int n): n(n) {}
        NonCopyable(NonCopyable const&) = delete;
        int n;
    };
    NonCopyable nc(2);
    auto f = [&](utl::function_view<int(NonCopyable&)> cb) { return cb(nc); };
    CHECK(f([](NonCopyable& nc) { return nc.n; }) == 2);
}
