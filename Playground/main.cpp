#include <iostream>
#include <span>
#include <string>
#include <random>

#include <utl/vector.hpp>
#include <utl/utility.hpp>
#include <utl/structure_of_arrays.hpp>
#include <utl/graph.hpp>
#include <utl/ranges.hpp>

namespace {
UTL_SOA_TYPE(Node,
             (std::string, name),
             (utl::small_vector<std::uint16_t>, dependencies));
}

[[gnu::weak]] int main() {
    utl::structure_of_arrays<Node> nodes = {
        Node{ "0" },
        Node{ "1" },
        Node{ "2" },
        Node{ "3" },
        Node{ "4" }
    };
    
    
    nodes[0].dependencies = { 1 };
    nodes[1].dependencies = { 2 };
    nodes[2].dependencies = { 0, 3 };
    nodes[3].dependencies = { 4 };
    nodes[4].dependencies = { 2 };
    
    auto printCycle = [](auto const& nodes, auto const& cycle) {
        for (auto i: cycle) {
            std::cout << nodes[i].name << " -> ";
        }
        std::cout << nodes[cycle.front()].name << std::endl;
    };
    
    auto printCycle2 = [](auto const& cycle) {
        for (auto i: cycle) {
            std::cout << i.name << " -> ";
        }
        std::cout << cycle.front().name << std::endl;
    };
    
    {
        utl::small_vector<uint16_t> indices(utl::iota(nodes.size()));
        auto const cycle = utl::find_cycle(indices.begin(), indices.end(), [&](size_t index) -> auto& { return nodes[index].dependencies; });
        if (!cycle.empty()) {
            std::cout << "Have cycle!\n";
            printCycle(nodes, cycle);
        }
    } {
        auto const cycle = utl::find_cycle(nodes.begin(), nodes.end(), [&](auto node){ return utl::transform(node.dependencies, [&](size_t index) { return nodes[index]; }); });
        if (!cycle.empty()) {
            std::cout << "Have cycle!\n";
            printCycle2(cycle);
        }
    }
    
    utl::small_vector<std::uint16_t> nodeIndices(utl::iota(nodes.size()));

    std::shuffle(nodeIndices.begin(),
                 nodeIndices.end(),
                 std::mt19937(std::random_device()()));
    utl::topsort(nodeIndices.begin(),
                 nodeIndices.end(),
                 [&](std::size_t index) -> auto& { return nodes[index].dependencies; });
}
