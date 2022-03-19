#define MTL_DEBUG_LEVEL 2

#include <iostream>
#include <utl/vector.hpp>
#include <bitset>

#include <utl/__fmt/format.h>
#include <utl/typeinfo.hpp>
#include <utl/stdio.hpp>
#include <utl/algorithm.hpp>
#include <mtl/mtl.hpp>

int main() {

	using namespace mtl;
	
	std::cout << std::boolalpha;

	std::cout << (0 == 1.38778e-16) << std::endl;

	std::cout << mtl::__mtl_float_threshold<double> * std::numeric_limits<double>::min() << std::endl;
	std::cout << 0.0000001 *std::numeric_limits<double>::min() << std::endl;

	bool value = (0 == mtl::approx(1.38778e-16));

	std::cout << value << std::endl;

}