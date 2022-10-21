#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <sstream>
#include <string>

namespace utl {

template <typename T>
concept __utl_printable = requires(std::ostream& s, T&& t) {
    s << t;
};

[[nodiscard]] std::string strcat(__utl_printable auto&& f, __utl_printable auto&&... r) {
    std::stringstream sstr;
    sstr << UTL_FORWARD(f);
    ((sstr << UTL_FORWARD(r)), ...);
    return std::move(sstr).str();
}

} // namespace utl
