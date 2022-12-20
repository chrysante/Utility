#include "Catch2.hpp"

#include <utl/ilist.hpp>
#include <utl/ranges.hpp>

#include "LifetimeCounter.hpp"

namespace {

struct TestType: utl_test::LifetimeCounter, utl::ilist_node<TestType> {
    TestType(int value): value(value) {}
    
    int value;
};

} // namespace

#include <iostream>

TEST_CASE("ilist ctor", "[ilist]") {
    
    utl::ilist<TestType> l;
    
    for (auto elem: l) {
        std::cout << elem.value << std::endl;
    }
    
    for (int i = 0; i < 4; ++i) {
        l.push_back(new TestType(i));
    }

    auto itr = l.begin();
    
    std::advance(itr, 2);
 
    l.insert(itr, new TestType(10));
    
//    l.erase(itr);
    
    for (auto elem: l) {
        std::cout << elem.value << std::endl;
    }
    
    l.clear();
    
    CHECK(l.empty());
    
}
