#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <string>

#include "common.hpp"
#include "__fmt/format.h"
#include "__fmt/ostream.h"


namespace utl {
	
	constexpr decltype(auto) __utl_pointer_to_void(auto&& x) { return UTL_FORWARD(x); }
	constexpr auto* __utl_pointer_to_void(auto* p) { return (void const*)p; }
	constexpr char const* __utl_pointer_to_void(char const* p) { return p; }
	
	template <typename... Args>
	__utl_nodiscard std::string format(fmt::format_string<Args...> format_string, Args&&... args) {
		return fmt::format(std::move(format_string), __utl_pointer_to_void(UTL_FORWARD(args))...);
	}
}
