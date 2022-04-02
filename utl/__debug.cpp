#include "__debug.hpp"

#include <iostream>

namespace utl {
	void __utl_debug_print(std::string_view text) {
		std::cout << text << "\n";
	}
}
