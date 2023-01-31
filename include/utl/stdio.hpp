#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "format.hpp"
#include <iostream>

namespace utl {

template <typename... Args>
void print(std::string_view format_string, Args&&... args) {
    std::cout << utl::format(format_string, std::forward<Args>(args)...);
}

} // namespace utl
