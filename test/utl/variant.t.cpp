#ifndef _MSC_VER

#include <iostream>
#include <tuple>

#include <catch2/catch_test_macros.hpp>
#include <utl/overload.hpp>
#include <utl/typeinfo.hpp>
#include <utl/utility.hpp>
#include <utl/variant.hpp>

#include "utl/TypeCompare.h"

using utl_test::T;

template <std::size_t>
struct tag {
    tag() {}
    tag(tag const&) {}
    tag(tag&&) noexcept {}
    tag& operator=(tag const&) { return *this; }
    tag& operator=(tag&&) noexcept { return *this; }
    ~tag() {}
};

TEST_CASE("ctor 1 - variant default construct", "[variant]") {
    utl::variant<int, float> v;
    REQUIRE(v.index() == 0);
    CHECK(utl::get<0>(v) == 0);
}

TEST_CASE("ctor 2 - variant copy construct", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w = v;
    CHECK(w.index() == 2);
    CHECK(get<2>(w) == 1.0f);
}

TEST_CASE("ctor 3 - variant move construct", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w = std::move(v);
    CHECK(w.index() == 2);
    CHECK(get<2>(w) == 1.0f);
}

TEST_CASE("ctor 4 - variant value initialize", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    REQUIRE(v.index() == 2);
    CHECK(utl::get<2>(v) == 1.0f);
}

TEST_CASE("ctor 5 - variant in_place construct", "[variant]") {
    utl::variant<int, float> v(std::in_place_type<float>, 1.0f);
    REQUIRE(v.index() == 1);
    CHECK(utl::get<1>(v) == 1.0f);
}

TEST_CASE("variant copy assign", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w;
    w = v;
    CHECK(w.index() == 2);
    CHECK(get<2>(w) == 1.0f);
}

TEST_CASE("variant move assign", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w;
    w = std::move(v);
    CHECK(w.index() == 2);
    CHECK(get<2>(w) == 1.0f);
}

TEST_CASE("variant value assign", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    REQUIRE(v.index() == 2);
    v = 2;
    CHECK(v.index() == 1);
    CHECK(utl::get<1>(v) == 2);
}

TEST_CASE("variant swap", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f, w = 2;
    REQUIRE(v.index() == 2);
    REQUIRE(w.index() == 1);
    v.swap(w);
    REQUIRE(v.index() == 1);
    REQUIRE(w.index() == 2);
    CHECK(utl::get<1>(v) == 2);
    CHECK(utl::get<2>(w) == 1.0f);
}

TEST_CASE("variant visit helper", "[variant]") {
    auto v = [i = 0](auto...) -> int const& { return i; };
    using VisitHelper = utl::__variant_visit<
        true, void, decltype(v),
        utl::type_sequence<
            utl::variant<float, int, int>,
            utl::variant<char, std::nullptr_t, char, std::nullptr_t>,
            utl::variant<char, std::nullptr_t>>>;
    CHECK(T<VisitHelper::__variant_at_index<0>> ==
          T<utl::variant<float, int, int>>);
    CHECK(T<VisitHelper::__variant_at_index<1>> ==
          T<utl::variant<char, std::nullptr_t, char, std::nullptr_t>>);
    CHECK(T<VisitHelper::__variant_at_index<2>> ==
          T<utl::variant<char, std::nullptr_t>>);
    CHECK(VisitHelper::__variant_count == 3);
    UTL_WITH_INDEX_SEQUENCE((I, 24), {
        (
            [&] {
            CHECK(T<VisitHelper::__deduced_return_type_at<I>> == T<int const&>);
        }(),
            ...);
    });
    CHECK(T<VisitHelper::__common_return_type> == T<int const&>);
    auto const size = VisitHelper::__variant_sizes;
    CHECK(size[0] == 3);
    CHECK(size[1] == 4);
    CHECK(size[2] == 2);
    for (std::size_t i = 0; i < size[0]; ++i) {
        for (std::size_t j = 0; j < size[1]; ++j) {
            for (std::size_t k = 0; k < size[2]; ++k) {
                std::size_t const flat =
                    VisitHelper::__flatten_index({ i, j, k });
                auto const expanded = VisitHelper::__expand_index(flat);
                CHECK(expanded[0] == i);
                CHECK(expanded[1] == j);
                CHECK(expanded[2] == k);
            }
        }
    }
}

TEST_CASE("variant visit", "[variant]") {
    utl::variant<tag<0>, tag<1>, tag<2>, tag<3>> u(std::in_place_type<tag<2>>);
    utl::variant<int, char> v(std::in_place_type<int>, 1);
    utl::variant<float, std::nullptr_t> w(std::in_place_type<std::nullptr_t>,
                                          nullptr);
    auto result = utl::visit(utl::overload{ [&](auto...) { return 0; },
                                            [&](tag<2>, int, std::nullptr_t) {
        return 1;
    } },
                             u, v, w);
    CHECK(std::same_as<decltype(result), int>);
    CHECK(result == 1);
    // Test instantiation of visitation with visitor with different but similar
    // return types
    auto d = utl::visit(utl::overload{
                            [&](auto...) { return 0.0; },
                            [&](tag<2>, int, std::nullptr_t) { return 1; } },
                        u, v, w);
    CHECK(std::same_as<decltype(d), double>);
    // Test instantiation of void visitation with non void visitor
    utl::visit<void>(utl::overload{
                         [&](auto...) { return 0; },
                         [&](tag<2>, int, std::nullptr_t) { return 1; } },
                     u, v, w);
}

TEST_CASE("variant visit returning references", "[variant]") {
    utl::variant<tag<0>, tag<1>, tag<2>, tag<3>> u(std::in_place_type<tag<2>>);
    utl::variant<int, char> v(std::in_place_type<int>, 1);
    auto vis = utl::overload{
        [&, i = 0](tag<2>&, int&) mutable -> int const& { return i; },
        [&, i = 0](auto&, auto&) mutable -> int& { return i; },
    };
    auto&& result = utl::visit(vis, u, v);
    CHECK(T<decltype(result)> == T<int const&>);
}

namespace {

struct Base {
    int i;
};

int& f(Base& b) {
    return b.i;
}

struct A: Base {
    A(int i, float a): Base{ i }, a(a) {}
    float a;
};

struct B: Base {
    B(int i, long a): Base{ i }, a(a) {}
    long a;
};

struct X {
    int _;
};

struct C: X, B {
    using B::B;
};

} // namespace

static void testCBVariant(auto& v) {
    CHECK(v->i == 1);
    v->i = 3;
    v.visit([](auto& x) { CHECK(x.i == 3); });
    CHECK(f(v) == 3);
    v.visit([](auto& x) { x.a = 1; });
}

TEST_CASE("cbvariant", "[variant]") {
    utl::cbvariant<Base, A, B> v(std::in_place_type<A>, 1, 2);
    testCBVariant(v);
    utl::cbvariant<Base, A, B, C> w(std::in_place_type<C>, 1, 2);
    CHECK(&w->i == &w.get<C>().i);
    testCBVariant(w);
}

namespace {

struct NonTrivial {
    NonTrivial() {}
    NonTrivial(NonTrivial const&) {}
    NonTrivial(NonTrivial&&) noexcept {}
    NonTrivial& operator=(NonTrivial const&) { return *this; }
    NonTrivial& operator=(NonTrivial&&) noexcept { return *this; }
    ~NonTrivial() {}
};

} // namespace

TEST_CASE("variant trivial lifetime", "[variant]") {
    return;
#if defined(__clang__)
    if (__clang_major__ < 15) {
        std::cout << "Clang " __clang_version__
                  << " insufficient for correct lifetime triviality."
                  << std::endl;
        return;
    }
#endif
    using V = utl::variant<int, NonTrivial>;
    CHECK(!std::is_trivially_copy_constructible_v<V>);
    CHECK(!std::is_trivially_move_constructible_v<V>);
    CHECK(!std::is_trivially_copy_assignable_v<V>);
    CHECK(!std::is_trivially_move_assignable_v<V>);
    CHECK(!std::is_trivially_destructible_v<V>);
    using W = utl::variant<int, float>;
    CHECK(std::is_trivially_copy_constructible_v<W>);
    CHECK(std::is_trivially_move_constructible_v<W>);
    CHECK(std::is_trivially_copy_assignable_v<W>);
    CHECK(std::is_trivially_move_assignable_v<W>);
    CHECK(std::is_trivially_destructible_v<W>);
}

#endif
