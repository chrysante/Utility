#include <catch/catch2.hpp>
#include <utl/__farray.hpp>
#include <utl/overload.hpp>

#include "TypeCompare.h"

namespace {

struct Base {

};

struct Derived: Base {

};

} // namespace

TEST_CASE("__farray", "[common]") {
    using namespace utl;
    auto f     = overload{ 
        [&](Base, Base) { return 1; },
        [&](Derived, Base){ return 2; },
        [&](Base, Derived) { return 3; },
        [&](Derived, Derived) { return 4; },
    };
    using FArray = __farray</* R = */ int, decltype((f)), type_sequence<Base&&, Base&&>, std::integer_sequence<std::size_t, 2, 2>>;
    FArray myFArray([]<std::size_t I>(std::integral_constant<std::size_t, I>, Base&& x) -> auto&& { 
        if constexpr (I == 0) {
            return std::move(x);
        }
        else {
            static_assert(I == 1);
            return static_cast<Derived&&>(x);
        }
    });
    CHECK(myFArray[{ 0, 0 }](f, Derived{}, Derived{}) == 1);
    CHECK(myFArray[{ 1, 0 }](f, Derived{}, Derived{}) == 2);
    CHECK(myFArray[{ 0, 1 }](f, Derived{}, Derived{}) == 3);
    CHECK(myFArray[{ 1, 1 }](f, Derived{}, Derived{}) == 4);
}
