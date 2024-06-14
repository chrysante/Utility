#include <catch2/catch_test_macros.hpp>
#include <utl/dynamic_library.hpp>

#if defined(__APPLE__)
static constexpr auto* LibName = "libtest-lib.dylib";
#elif defined(_MSC_VER)
static constexpr auto* LibName = "test-lib.dll";
#else
#error Unsupported compiler
#endif

TEST_CASE("Dynamic library", "[dynamic_library]") {
    utl::dynamic_library lib(LibName);
    SECTION("Resolve function") {
        auto* fn = lib.resolve_as<int()>("test_function");
        CHECK(fn() == 42);
    }
    SECTION("Non-existing symbol") {
        CHECK_THROWS(lib.resolve("does_not_exist"));
        std::string err;
        void* handle = lib.resolve("does_not_exist", &err);
        CHECK(handle == nullptr);
        CHECK(!err.empty());
    }
}

#if defined(__GNUC__)
__attribute__((visibility("default"))) extern "C" int
#elif defined(_MSC_VER)
extern "C" int __declspec(dllexport) __stdcall 
#else
#error
#endif
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
