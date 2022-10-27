#include <utl/concepts.hpp>
#include <utl/vector.hpp>

namespace utl_test {

struct Vertex {
    int value;
    utl::small_vector<std::uint16_t> dependencies;
};

inline bool findDownstream(auto const& graph, std::size_t start, std::size_t target) {
    auto const vertex = graph[start];
    if (auto itr = std::find(vertex.dependencies.begin(), vertex.dependencies.end(), target);
        itr != vertex.dependencies.end())
    {
        return true;
    }
    for (auto const index: vertex.dependencies) {
        if (findDownstream(graph, index, target)) {
            return true;
        }
    }
    return false;
}

}
