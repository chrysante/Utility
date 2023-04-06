#include <utl/concepts.hpp>
#include <utl/vector.hpp>

namespace utl_test {

struct Vertex {
    int value;
    utl::small_vector<std::uint16_t> successors;
};

inline bool findDownstream(auto const& graph, std::size_t start, std::size_t target) {
    auto const vertex = graph[start];
    if (auto itr = std::find(vertex.successors.begin(), vertex.successors.end(), target);
        itr != vertex.successors.end())
    {
        return true;
    }
    for (auto const index: vertex.successors) {
        if (findDownstream(graph, index, target)) {
            return true;
        }
    }
    return false;
}

}
