#include "main.hpp"

#include <iostream>
#include <fstream>

namespace CodeGen {
	std::vector<CodeGenerator>& _registeredGenerators() {
		static std::vector<CodeGenerator> g;
		return g;
	};
}

int main() {
	
	using namespace CodeGen;
	
	for (auto&& generator: _registeredGenerators()) {
		std::fstream file(std::filesystem::path(PROJECT_LOCATION) / generator.outpath,
						  std::ios::out | std::ios::trunc);
		file << generator.function();
	}
	
	
	if (_registeredGenerators().empty()) {
		std::cerr << "No generators registered" << std::endl;
		return -1;
	}
	else {
		auto const count = _registeredGenerators().size();
		std::cout << "Ran " << count << " Generator" << (count == 1 ? "" : "s") << std::endl;
		return 0;
	}
	
}
