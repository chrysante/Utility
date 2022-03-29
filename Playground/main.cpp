#include "utl/__soa_exp.hpp"

#include <iostream>

#include "mtl/mtl.hpp"

namespace worldmachine {

	UTL_SOA_TYPE(Node,
				 (int, id),
				 (float, position)
				 );
	
	UTL_SOA_TYPE(Edge,
				 (int, id),
				 (float, position)
				 );

	struct Network {
		utl::SOA<Node> nodes;
		utl::SOA<Edge> edges;
	};
	
}


int main() {
	worldmachine::Network network;
	network.nodes.push_back({ 1, 0.5 });
	
	auto&& [id, transform] = network.nodes[0];
	
	network.nodes[0] = { -1, 1.5 };
	
	std::cout << network.nodes[0].id << std::endl;
	std::cout << network.nodes[0].transform.position << std::endl;
	
	network.nodes.id(0) = -2;
	network.nodes.transform(0) = { 3.5, 0 };
	
	std::cout << network.nodes[0].id << std::endl;
	std::cout << network.nodes[0].transform.position << std::endl;
}

