#include "Catch2.hpp"

#include <tuple>
#include <iostream>

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

template <std::size_t> struct tag{};

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

TEST_CASE("variant copy constructor", "[variant]") {
    utl::variant<int, float> v(std::in_place_type<float>, 1.0f);
    utl::variant<int, float> w;
    w = v;
    CHECK(w.index() == 1);
    CHECK(get<1>(w) == 1.0f);
}

TEST_CASE("variant visit helper", "[variant]") {
    auto v = [](auto, auto) {};
    using VisitHelper = utl::__variant_visit<true,
                                             void,
                                             decltype(v),
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
    for (int i = 0; i < size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
            for (int k = 0; k < size[2]; ++k) {
                std::size_t const flat = VisitHelper::__flatten_index({ i, j, k });
                CHECK(VisitHelper::__expand_index(flat) == std::tuple(i, j, k));
            }
        }
    }
}

TEST_CASE("variant visit", "[variant]") {
    utl::variant<tag<0>, tag<1>, tag<2>, tag<3>> u(std::in_place_type<tag<2>>);
    utl::variant<int, char> v(std::in_place_type<int>, 1);
    utl::variant<float, std::nullptr_t> w(std::in_place_type<std::nullptr_t>, nullptr);
    bool ran = false;
    utl::visit(utl::overload{
        [&]<typename U, typename V, typename W>(U, V, W) {
            ran = true;
            CHECK(std::same_as<U, tag<2>>);
            CHECK(std::same_as<V, int>);
            CHECK(std::same_as<W, std::nullptr_t>);
        }
    }, u, v, w);
    CHECK(ran);
}
