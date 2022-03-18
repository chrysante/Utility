#include "utl/dynamic_dispatch.hpp"
#include "utl/stdio.hpp"
#include "utl/typeinfo.hpp"

#include <tuple>
#include <concepts>

enum class E {
	a, b
};

template <typename T>
void f(std::same_as<T> auto) {
	
}


int main() {
	std::tuple<int, int> t(0, 2);
	f<int>(0);
	
	
}
