#include <set>
#include <unordered_set>

#include <catch2/catch_test_macros.hpp>
#include <utl/overload.hpp>
#include <utl/ptr_union.hpp>

static_assert(utl::ptr_union_size_v<utl::ptr_union<int*, void*>> == 2);
static_assert(sizeof(utl::ptr_union<int*, double*>) == 8);
static_assert(sizeof(utl::ptr_union<int*>) == 8);

static_assert(
    std::same_as<utl::ptr_union_alternative_t<0, utl::ptr_union<int*, void*>>,
                 int*>);

TEST_CASE("default construct", "[ptr-union]") {
    utl::ptr_union<int volatile*, void*> u;
    CHECK(u.index() == 0);
    CHECK(utl::holds_alternative<int volatile*>(u));
}

TEST_CASE("value construct", "[ptr-union]") {
    double d;
    utl::ptr_union<int*, double const*> u = &d;
    CHECK(u.index() == 1);
    CHECK(u.get<1>() == &d);
}

TEST_CASE("in_place_index construct", "[ptr-union]") {
    int i;
    utl::ptr_union<int volatile*, int const*> u(std::in_place_index<1>, &i);
    CHECK(u.index() == 1);
    CHECK(u.get<1>() == &i);
}

TEST_CASE("value assign", "[ptr-union]") {
    double d;
    utl::ptr_union<int*, double const*> u = &d;
    CHECK(u.index() == 1);

    int i;
    u = &i;
    CHECK(u.index() == 0);
}

TEST_CASE("comparison", "[ptr-union]") {
    using U = utl::ptr_union<int*, double*>;
    U u, v;
    CHECK(u == v);
    int i;
    u = &i;
    v = &i;
    CHECK(u == v);
    u = nullptr;
    CHECK(u < v);
}

TEST_CASE("visitation", "[ptr-union]") {
    double d = 42;
    utl::ptr_union<int*, double*> u = &d;
    int result = utl::visit(u, utl::overload{
                                   [](int*) { return 0; },
                                   [](double* d) { return *d; },
                               });
    CHECK(result == 42);
}

namespace {

template <int>
struct Tag {};

struct alignas(16) Double16 {
    double value;
};

} // namespace

TEST_CASE("visitation many cases", "[ptr-union]") {
    Double16 d = { 42 };
    utl::ptr_union<Tag<0>*, Tag<1>*, Tag<2>*, Tag<3>*, Tag<4>*, Tag<5>*,
                   Tag<6>*, Tag<7>*, Tag<8>*, Tag<9>*, Tag<10>*, Double16*>
        u = &d;
    int result = utl::visit(u, utl::overload{
                                   []<int I>(Tag<I>*) { return 0; },
                                   [](Double16* d) { return d->value; },
                               });
    CHECK(result == 42);
    result = u.visit(utl::overload{
        []<int I>(Tag<I>*) { return 0; },
        [](Double16* d) { return d->value; },
    });
    CHECK(result == 42);
}

TEST_CASE("get/try_get", "[ptr-union]") {
    double d;
    utl::ptr_union<int*, double const*> u = &d;
    CHECK(u.get<1>() == &d);
    CHECK(utl::get<1>(u) == &d);
    CHECK(u.try_get<1>() == &d);
    CHECK(utl::try_get<1>(u) == &d);
    CHECK(u.try_get<0>() == nullptr);
    CHECK(utl::try_get<0>(u) == nullptr);

    CHECK(u.get<double const*>() == &d);
    CHECK(utl::get<double const*>(u) == &d);
    CHECK(u.try_get<double const*>() == &d);
    CHECK(utl::try_get<double const*>(u) == &d);
    CHECK(u.try_get<int*>() == nullptr);
    CHECK(utl::try_get<int*>(u) == nullptr);
}

TEST_CASE("nullptr handling", "[ptr-union]") {
    utl::ptr_union<int*, double*> u = nullptr;
    CHECK(u.index() == 0);
    CHECK(u.get<0>() == nullptr);
    CHECK(u.try_get<0>() == nullptr);
    CHECK(u.try_get<1>() == nullptr);
}

namespace {

struct IncompleteA;
struct IncompleteB;

} // namespace

TEST_CASE("incomplete types", "[ptr-union]") {
    utl::ptr_union<IncompleteA*, IncompleteB*> u =
        reinterpret_cast<IncompleteB*>(0xF0);
    CHECK(u.get<1>() == reinterpret_cast<IncompleteB*>(0xF0));
}

TEST_CASE("ordering", "[ptr-union]") {
    std::set<utl::ptr_union<int*, double*>> m;
    int a, b, c;
    double x, y, z;
    m.insert(&a);
    m.insert(&b);
    m.insert(&x);
    CHECK(m.contains(&a));
    CHECK(m.contains(&b));
    CHECK(!m.contains(&c));
    CHECK(m.contains(&x));
    CHECK(!m.contains(&y));
    CHECK(!m.contains(&z));
}

TEST_CASE("hashing", "[ptr-union]") {
    std::unordered_set<utl::ptr_union<int*, double*>> m;
    int a, b, c;
    double x, y, z;
    m.insert(&a);
    m.insert(&b);
    m.insert(&x);
    CHECK(m.contains(&a));
    CHECK(m.contains(&b));
    CHECK(!m.contains(&c));
    CHECK(m.contains(&x));
    CHECK(!m.contains(&y));
    CHECK(!m.contains(&z));
}
