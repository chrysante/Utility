#include <catch/catch2.hpp>

#include <tuple>
#include <iostream>

#if 0

#include <utl/variant.hpp>
#include <utl/typeinfo.hpp>
#include <utl/utility.hpp>


namespace {

template <typename... T>
std::ostream& operator<<(std::ostream& str, std::tuple<T...> const& t) {
    str << "(";
    [&]<std::size_t... I>(std::index_sequence<I...>) {
        ([&]{
            if constexpr (I > 0) { str << ", "; }
            str << std::get<I>(t);
        }(), ...);
    }(std::index_sequence_for<T...>{});
    return str << ")";
}


} // namespace

template <std::size_t> struct tag{
    tag() {}
    tag(tag const&) {}
    tag(tag&&) noexcept {}
    tag& operator=(tag const&) { return *this; }
    tag& operator=(tag&&) noexcept { return *this; }
    ~tag() {}
};

TEST_CASE("variant default construct", "[variant]") {
    utl::variant<int, float> v;
    REQUIRE(v.index() == 0);
    CHECK(utl::get<0>(v) == 0);
}

TEST_CASE("variant in_place construct", "[variant]") {
    utl::variant<int, float> v(std::in_place_type<float>, 1.0f);
    REQUIRE(v.index() == 1);
    CHECK(utl::get<1>(v) == 1.0f);
}

TEST_CASE("variant value initialize", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    REQUIRE(v.index() == 2);
    CHECK(utl::get<2>(v) == 1.0f);
}

TEST_CASE("variant copy construct", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w = v;
    CHECK(w.index() == 2);
    CHECK(get<2>(w) == 1.0f);
}

TEST_CASE("variant copy assign", "[variant]") {
    utl::variant<tag<0>, int, float> v = 1.0f;
    utl::variant<tag<0>, int, float> w;
    w = v;
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
    auto v = [](auto...) {};
    using VisitHelper = utl::__variant_visit<true, void, decltype(v),
                                             utl::type_sequence<utl::variant<float, int, int>,
                                                                utl::variant<char, std::nullptr_t, char, std::nullptr_t>,
                                                                utl::variant<char, std::nullptr_t>>>;
    CHECK(std::same_as<VisitHelper::__variant_at_index<0>, utl::variant<float, int, int>>);
    CHECK(std::same_as<VisitHelper::__variant_at_index<1>, utl::variant<char, std::nullptr_t, char, std::nullptr_t>>);
    CHECK(std::same_as<VisitHelper::__variant_at_index<2>, utl::variant<char, std::nullptr_t>>);
    CHECK(VisitHelper::__variant_count == 3);
    auto const size = VisitHelper::__variant_sizes;
    CHECK(size[0] == 3);
    CHECK(size[1] == 4);
    CHECK(size[2] == 2);
    for (std::size_t i = 0; i < size[0]; ++i) {
        for (std::size_t j = 0; j < size[1]; ++j) {
            for (std::size_t k = 0; k < size[2]; ++k) {
                std::size_t const flat = VisitHelper::__flatten_index({ i, j, k });
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
    utl::variant<float, std::nullptr_t> w(std::in_place_type<std::nullptr_t>, nullptr);
    auto result = utl::visit(utl::overload{
        [&](auto...) { return 0; },
        [&](tag<2>, int, std::nullptr_t) { return 1; }
    }, u, v, w);
    CHECK(std::same_as<decltype(result), int>);
    CHECK(result == 1);
    // Test instantiation of visitation with visitor with different but similar return types
    auto d = utl::visit(utl::overload{
        [&](auto...) { return 0.0; },
        [&](tag<2>, int, std::nullptr_t) { return 1; }
    }, u, v, w);
    CHECK(std::same_as<decltype(d), double>);
    // Test instantiation of void visitation with non void visitor
    utl::visit<void>(utl::overload{
        [&](auto...) { return 0; },
        [&](tag<2>, int, std::nullptr_t) { return 1; }
    }, u, v, w);
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


}

TEST_CASE("variant trivial lifetime", "[variant]") {
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
