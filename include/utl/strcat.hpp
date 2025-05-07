#ifndef UTL_STRCAT_HPP_
#define UTL_STRCAT_HPP_

#include <sstream>
#include <string>

#include <utl/__base.hpp>
#include <utl/common.hpp>

namespace utl {

template <typename T>
concept __utl_printable = requires(std::ostream& s, T&& t) { s << t; };

[[nodiscard]] std::string strcat(__utl_printable auto&& f,
                                 __utl_printable auto&&... r) {
    std::stringstream sstr;
    sstr << UTL_FORWARD(f);
    ((sstr << UTL_FORWARD(r)), ...);
    return std::move(sstr).str();
}

} // namespace utl

#endif // UTL_STRCAT_HPP_
