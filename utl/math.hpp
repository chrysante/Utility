#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_


#include "__function_objects.hpp"

namespace utl {

	template <typename T, typename A>
	__utl_nodiscard constexpr T mix(T const& t, T const& u, A const& alpha) {
		return t * (1 - alpha) + u * alpha;
	}
	
}
