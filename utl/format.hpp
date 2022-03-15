#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <string>

#include "__common.hpp"
#include "__fmt/format.h"
#include "__fmt/ostream.h"


namespace utl {
	
	template <typename... Args>
	__utl_nodiscard std::string format(fmt::format_string<Args...> format_string, Args&&... args) {
		return fmt::format(std::move(format_string), UTL_FORWARD(args)...);
	}
}
