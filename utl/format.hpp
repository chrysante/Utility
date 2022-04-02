#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <string>

#include "__fmt/format.h"
#include "__fmt/ostream.h"


namespace utl {
	
	template <typename T>
	constexpr decltype(auto) __utl_pointer_to_void(T&& x) { return std::forward<T>(x); }
	constexpr auto* __utl_pointer_to_void(auto* p) { return (void const*)p; }
	constexpr char const* __utl_pointer_to_void(char const* p) { return p; }
	
	template <typename... Args>
	__utl_nodiscard std::string format(std::string_view format_string, Args&&... args) {
		return fmt::format(fmt::runtime(format_string), __utl_pointer_to_void(std::forward<Args>(args))...);
	}
}
