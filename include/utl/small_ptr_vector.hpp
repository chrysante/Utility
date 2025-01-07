#include <utl/tiny_ptr_vector.hpp>

/// This file exists for compatibility reasons

namespace utl {

template <typename T, typename Allocator = std::allocator<T>>
using small_ptr_vector = tiny_ptr_vector<T, Allocator>;

}
