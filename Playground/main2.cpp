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
    
    int const count = 10;
    int index = 0;
    for (auto&& [index, value]: utl::enumerate(utl::vector<std::unique_ptr<int>>(utl::transform(utl::iota(count), [](int value) { return std::make_unique<int>(value); })))) {
        std::cout << *value << std::endl;
        ++index;
    }
}

