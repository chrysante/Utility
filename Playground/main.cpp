#include <iostream>
#include <span>
#include <string>
#include <random>

#include <utl/vector.hpp>
#include <utl/utility.hpp>
#include <utl/structure_of_arrays.hpp>
#include <utl/graph/topsort.hpp>

UTL_SOA_TYPE(Node,
             (std::string, name),
             (utl::small_vector<std::uint16_t>, dependencies)
             );

int main() {
    
    utl::structure_of_arrays<Node> nodes = {
        Node{ "X" },
        Node{ "f" },
        Node{ "Y" },
        Node{ "X.y" },
        Node{ "Z" },
        Node{ "X.z" },
    };
    
    std::size_t const X   = 0;
    std::size_t const f   = 1;
    std::size_t const Y   = 2;
    std::size_t const X_y = 3;
    std::size_t const Z   = 4;
    std::size_t const X_z = 5;

    nodes[X].dependencies = { X_y, X_z };
    nodes[X_y].dependencies = { Y };
    nodes[X_z].dependencies = { Z };
    nodes[f].dependencies = { X, Y, Z };

    utl::iota indices(nodes.size());
    utl::small_vector<std::uint16_t> nodeIndices(indices.begin(), indices.end());

    for (int i = 0; i < 5; ++i) {
        std::shuffle(nodeIndices.begin(), nodeIndices.end(), std::mt19937(std::random_device()()));
        utl::topsort(nodeIndices.begin(), nodeIndices.end(), [&](std::size_t index) { return nodes[index].dependencies; });
        for (auto const index: nodeIndices) {
            std::cout << nodes[index].name << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << nodes[0].dependencies.inline_capacity() << std::endl;
    
}
