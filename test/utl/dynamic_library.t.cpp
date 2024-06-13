#ifdef __APPLE__

#include <catch2/catch_test_macros.hpp>
#include <utl/dynamic_library.hpp>

static constexpr auto* LibName = "libtest-lib.dylib";

TEST_CASE("Dynamic library", "[dynamic_library]") {
    utl::dynamic_library lib(LibName);
    SECTION("Resolve function") {
        auto* fn = lib.resolve_as<int()>("test_function");
        CHECK(fn() == 42);
    }
    SECTION("Non-existing symbol") {
        CHECK_THROWS(lib.resolve("does_not_exist"));
        std::string_view err;
        void* handle = lib.resolve("does_not_exist", &err);
        CHECK(handle == nullptr);
        CHECK(!err.empty());
    }
}

#if defined(__GNUC__)
__attribute__((visibility("default")))
#else
#error
#endif
extern "C" int
local_test_function(int i) {
    return 2 * i;
}

TEST_CASE("Parent executable", "[dynamic_library]") {
    auto lib = utl::dynamic_library::global();
    auto* fn = lib.resolve_as<int(int)>("local_test_function");
    CHECK(fn(21) == 42);
}

TEST_CASE("Non-existing lib", "[dynamic_library]") {
    CHECK_THROWS(utl::dynamic_library("does_not_exist"));
}

#endif