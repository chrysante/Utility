#include <catch/catch2.hpp>

#include "utl/dynamic_library.hpp"

#ifdef __APPLE__
#define LIB_NAME "libtest-library.dylib"
#else
#error Unsupported system
#endif

TEST_CASE("dynamic_library") {
    utl::dynamic_library lib(LIB_NAME);
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
        lib.load(LIB_NAME);
        CHECK_NOTHROW(lib.resolve("test_function"));
    }
}

TEST_CASE("dynamic_library non-existing lib") {
    CHECK_THROWS(utl::dynamic_library("does_not_exist"));
}
