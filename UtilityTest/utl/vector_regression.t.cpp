#include "Catch2.hpp"

#include <utl/vector.hpp>

TEST_CASE("nullpointer dereference in vector::__relocate", "[vector]") {
    utl::small_vector<int> v;
    v.push_back(1);
}
