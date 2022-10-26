#include <iostream>
#include <compare>
#include <vector>
#include <list>
#include <forward_list>

#include <utl/utility.hpp>
#include <utl/typeinfo.hpp>
#include <utl/vector.hpp>

float f(int) { return {}; }

constexpr auto identity = [](auto&& value) -> decltype(auto) { return UTL_FORWARD(value); };

int main() {
    utl::vector<int> v = { 1, 2, 3 };
    v.insert(v.begin(), 0);
}

