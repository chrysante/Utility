#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <filesystem>

namespace utl {
	
	bool is_hidden(std::filesystem::path const& p) {
		auto const name = p.filename();
		return name != ".." && name != "."  && name.string()[0] == '.';
	}

	
}

