#pragma once

#include <filesystem>

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

inline bool is_hidden(std::filesystem::path const& p) {
    auto const name = p.filename();
    return name != ".." && name != "." && name.string()[0] == '.';
}

} // namespace utl
