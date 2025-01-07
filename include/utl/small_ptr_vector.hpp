#ifndef UTL_SMALL_PTR_VECTOR_H_
#define UTL_SMALL_PTR_VECTOR_H_

#include <utl/tiny_ptr_vector.hpp>

/// This file exists for compatibility reasons

namespace utl {

template <typename T, typename Allocator = std::allocator<T>>
using small_ptr_vector = tiny_ptr_vector<T, Allocator>;

}

#endif UTL_SMALL_PTR_VECTOR_H_
