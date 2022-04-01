#include "utl/structure_of_arrays.hpp"
#include "mtl/mtl.hpp"
#include <iostream>
#include "utl/typeinfo.hpp"
#include "utl/concepts.hpp"

#include "utl/utility.hpp"

#include <random>

using namespace mtl::short_types;

namespace {

	UTL_SOA_TYPE(Node,
				 (int, id),
				 (float3, position),
				 (float2, size)
				 );

}

int main() {
//	utl::structure_of_arrays<Node> s;
//	for (int i = 0; i < 10; ++i) {
//		s.push_back({ .id = i });
//	}
	
	utl::structure_of_arrays<Node> s(10);
	
	std::generate(s.begin(), s.end(), [i = 0]() mutable { return Node{ .id = i++ }; });
	
	std::reverse(s.begin(), s.end());
	
	std::rotate(s.begin(), s.begin() + 3, s.end());
	
	std::shuffle(s.begin(), s.end(), std::mt19937(std::random_device{}()));
	
	std::sort(s.begin(), s.end(), [](Node::reference a, Node::reference b) { return a.id < b.id; });
	
	utl::structure_of_arrays<Node> t;
	
	std::copy(s.begin(), s.end(), std::back_inserter(t));
	
	for (auto id: t.view<Node::members::id>()) {
		std::cout << id << std::endl;
	}
	
	
	
}
