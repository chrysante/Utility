#include <catch/catch2.hpp>
#include <utl/type_traits.hpp>

#include "TypeCompare.h"

using namespace utl_test;

TEST_CASE("copy_cvref", "[type_traits]") {
    CHECK(T<utl::copy_cv_t<int, float>> == T<float>);
    CHECK(T<utl::copy_cv_t<int const, float>> == T<float const>);
    CHECK(T<utl::copy_cv_t<int volatile, float>> == T<float volatile>);
    
    CHECK(T<utl::copy_ref_t<int&, float const>> == T<float const&>);
    CHECK(T<utl::copy_ref_t<int&, float>> == T<float&>);
    CHECK(T<utl::copy_ref_t<int&&, float>> == T<float&&>);
    CHECK(T<utl::copy_ref_t<int const&&, float>> == T<float&&>);
    CHECK(T<utl::copy_ref_t<int const&&, float&>> == T<float&>);
    
    CHECK(T<utl::copy_cvref_t<int const&&, float&>> == T<float&>);
    
    CHECK(T<utl::copy_cvref_t<int const&, float>> == T<float const&>);
}
