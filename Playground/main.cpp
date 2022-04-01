#include "utl/structure_of_arrays.hpp"
#include "mtl/mtl.hpp"
#include <iostream>
#include "utl/typeinfo.hpp"
#include "utl/concepts.hpp"

#include "utl/utility.hpp"
#include "utl/vector.hpp"
#include <random>

namespace myLib {

	template <typename T, typename U>
	concept __same_as_impl = std::is_same_v<T, U>;
	
	template <typename T, typename U>
	concept same_as = __same_as_impl<T, U> && __same_as_impl<U, T>;
	
}

template <typename T>
concept hasOffset = requires(T t) {
	{ t.offset } -> myLib::same_as<mtl::double2&>;
};


struct Event {
	mtl::double2 offset;
};

int main() {

	std::cout << hasOffset<Event> << std::endl;
	
}
