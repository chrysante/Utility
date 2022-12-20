#include <catch/catch2.hpp>

#include <utl/type_traits.hpp>
#include <utl/typeinfo.hpp>

#include <iosfwd>

namespace {

template <typename>
struct TagType {};

template <typename A, typename B>
bool operator==(TagType<A>, TagType<B>) { return std::is_same_v<A, B>; }

template <typename T>
std::ostream& operator<<(std::ostream& str, TagType<T>) {
    return str << utl::nameof<T>;
}

template <typename T>
static constexpr TagType<T> T;

} // namespace

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
