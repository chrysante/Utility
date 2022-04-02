#include "utl/structure_of_arrays.hpp"
#include "mtl/mtl.hpp"
#include <iostream>
#include "utl/typeinfo.hpp"
#include "utl/concepts.hpp"

#include "utl/utility.hpp"
#include "utl/vector.hpp"
#include <random> 

UTL_STATIC_INIT {
	std::cout << "before main()?\n";
};

int main() {
	std::cout << "called main()\n";
}
