#include <mtl/mtl.hpp>
#include <tuple>
#include <array>
#include <iostream>

struct MyVector {
	int x, y;
};

using namespace mtl;

int main() {
	
	for (auto i: utl::iota<mtl::int3>{ { 0, 0, -4 }, { 2, 2, 3 } }) {
		std::cout << i << std::endl;
	}
}
