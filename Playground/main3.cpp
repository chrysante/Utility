#include <iostream>

#include <utl/ilist.hpp>

struct Node: utl::ilist_node<Node> {
    Node(int value): value(value) {}
    int value;
};

std::ostream& operator<<(std::ostream& str, Node const& node) {
    return str << "{ " << node.value << " }";
}


int main() {
    
    utl::ilist<Node> list = { -2, 1, -1, 2, 3, 4, 5, -7, 6, -8 };
    
    for (auto itr = list.begin(); itr != list.end(); ) {
        if (itr->value < 0) {
            itr = list.erase(itr);
        }
        else {
            ++itr;
        }
    }
    
    for (auto& node: list) {
        std::cout << node << std::endl;
    }
    
}
