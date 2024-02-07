#include <catch2/catch_test_macros.hpp>
#include <utl/dynamic_library.hpp>

#ifdef __APPLE__
static constexpr auto* LibName = "libtest-lib.dylib";
#else
#error Unsupported system
#endif

TEST_CASE("dynamic_library") {
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
    SECTION("Close and load") {
        lib.close();
        lib.load(LibName);
        CHECK_NOTHROW(lib.resolve("test_function"));
    }
}

TEST_CASE("dynamic_library non-existing lib") {
    CHECK_THROWS(utl::dynamic_library("does_not_exist"));
}
