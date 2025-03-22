#include <utl/projection.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {

struct TestObject {
    int foo;
    int bar;
};

} // namespace

static int project_test_obj(TestObject const& obj) {
    return 2 * obj.bar;
}

TEST_CASE("member projection", "[projection]") {
    TestObject a = { .foo = 42, .bar = 11 };
    TestObject b = { .foo = 0, .bar = 11 };
    auto eq = utl::member_equal_to<&TestObject::bar>{};
    CHECK(eq(a, b));
    auto hash = utl::member_hash<&TestObject::bar>{};
    CHECK(hash(a) == hash(b));
}

TEST_CASE("function projection", "[projection]") {
    TestObject a = { .foo = 42, .bar = 11 };
    TestObject b = { .foo = 0, .bar = 11 };
    auto eq = utl::projection_equal_to<TestObject, project_test_obj>{};
    CHECK(eq(a, b));
    auto hash = utl::projection_hash<TestObject, project_test_obj>{};
    CHECK(hash(a) == hash(b));
}
