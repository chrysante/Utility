#include <iostream>

#include <utl/vector.hpp>
#include <utl/ilist.hpp>

struct X: utl::ilist_node<X> {
    X(int i): i(i) {}
    int i;
};

[[gnu::weak]]
int main() {
    utl::ilist<X> l;
    l.push_back(X{-1});
    
    int const n = 11;
    
    for (int i = 1; i < n; ++i) {
        l.push_front(X{ i });
    }
    
    for (auto& x: l) {
        std::cout << x.i << std::endl;
    }
}
