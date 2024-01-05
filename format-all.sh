cd "$(dirname "$0")"

clang-format -i include/utl/{\
small_ptr_vector.hpp,\
dyncast.hpp\
}

