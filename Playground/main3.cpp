#include <iostream>

#include <utl/vector.hpp>
#include <utl/ilist.hpp>

struct X: utl::ilist_node<X> {
    X(int i): i(i) {}
    int i;
};

int main() {
    
    utl::ilist<X> l = { 1, 2, 3, 4, 5 };
    
    l.push_back(7);
    
    
}
