#include <iostream>

#include <utl/ilist.hpp>

#include <utl/typeinfo.hpp>

namespace utl {

template <typename Derived>
Derived __get_derived_type(ilist_node<Derived>&);

void __get_derived_type(...);

template <typename T>
using node_derived_type = decltype(__get_derived_type(std::declval<T&>()));

}

namespace {

struct X: utl::ilist_node<X> {
    
};

}

int main() {
    
    std::cout << utl::nameof<utl::node_derived_type<X>> << std::endl;
    
    
}
