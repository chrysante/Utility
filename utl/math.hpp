#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_


#include "__function_objects.hpp"
#include "concepts.hpp"

namespace utl {

	template <typename T, typename A>
	__utl_nodiscard constexpr T mix(T const& t, T const& u, A const& alpha) {
		return t * (1 - alpha) + u * alpha;
	}
	
	constexpr auto round_up(integral auto x, std::size_t multiple_of) noexcept {
		return x % multiple_of == 0 ? x : x + multiple_of - x % multiple_of;
	}
	
}
