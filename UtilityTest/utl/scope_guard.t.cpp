#include "Catch2.hpp"

#include <utl/scope_guard.hpp>

TEST_CASE("scope_guard", "[scope_guard]") {
    int i = 0;
    { utl::scope_guard g = [&]{ i = 1; }; }
    CHECK(i == 1);
}

TEST_CASE("armed_scope_guard", "[scope_guard]") {
    int i = 0;
    {
        utl::armed_scope_guard g = [&]{ i += 1; };
        g.disarm();
        SECTION("rearm") {
            i -= 1;
            g.arm();
        }
        SECTION("no-rearm");
    }
    CHECK(i == 0);
}

TEST_CASE("scope_guard_failure", "[scope_guard]") {
    int i = 0;
    bool const _throw = GENERATE(true, false);
    try {
        utl::scope_guard_failure g = [&]{ ++i; };
        if (_throw) {
            throw 0;
        }
    }
    catch (...) {}
    CHECK(i == (_throw ? 1 : 0));
}

TEST_CASE("scope_guard_success", "[scope_guard]") {
    int i = 0;
    bool const _throw = GENERATE(true, false);
    try {
        utl::scope_guard_success g = [&]{ ++i; };
        if (_throw) {
            throw 0;
        }
    }
    catch (...) {}
    CHECK(i == (_throw ? 0 : 1));
}
