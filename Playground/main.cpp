#include <iostream>
#include <utl/common.hpp>
#include <mtl/mtl.hpp>
#include <utl/typeinfo.hpp>

int main() {

	using namespace mtl;
	auto io = utl::iota<int3>(int3(-1), int3{3, 4, 2});

	//auto [i, j, k] = int3(1, 2, 3);

	std::cout << std::tuple_size<int3>::value << std::endl;
	std::cout << utl::nameof<typename std::tuple_element<0, int3>::type> << std::endl;
	std::cout << utl::nameof<typename std::tuple_element<1, int3>::type> << std::endl;

	//for (auto [i, j, k] : io) {
	//	std::cout << int3(i, j, k) << std::endl;
	//}

}