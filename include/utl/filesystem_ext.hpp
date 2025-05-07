#pragma once

#include <filesystem>

#include <utl/__base.hpp>

namespace utl {

inline bool is_hidden(std::filesystem::path const& p) {
    auto const name = p.filename();
    return name != ".." && name != "." && name.string()[0] == '.';
}

} // namespace utl
