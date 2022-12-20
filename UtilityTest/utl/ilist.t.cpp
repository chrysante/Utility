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
     
    for (int i = 0; i < 10; ++i) {
        l.push_back(new TestType(i));
    }

    auto itr = l.begin();
    
    std::advance(itr, 3);
 
    l.insert_before(l.erase(std::next(itr)), itr);
    
//    l.erase(itr);
    
    for (auto elem: utl::reverse(l)) {
        std::cout << elem.value << std::endl;
    }
    
    
    
}
