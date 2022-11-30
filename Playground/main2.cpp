#include <iostream>
#include <compare>
#include <vector>
#include <list>
#include <forward_list>

#include <experimental/memory_resource>

#include <utl/utility.hpp>
#include <utl/ranges.hpp>
#include <utl/typeinfo.hpp>
#include <utl/vector.hpp>
#include <utl/variant.hpp>

void print(char const* text) { std::cout << text << std::endl; }

//
//struct Z {
//    Z(utl::variant<int, Z> const& v) {}
//};
//
//
//int main() {
//    
//    utl::variant<int, Z> v;
//    utl::variant<int, Z> w = (v);
//    
//    std::cout << decltype(utl::__index_selector<int, Z>::__call(v))::value << std::endl;
//
//    
//}
