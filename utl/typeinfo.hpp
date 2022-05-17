#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <typeinfo>

#include "static_string.hpp"

namespace utl {
	
	/// Brittle implementation using __PRETTY_FUNCTION__
	/// If it doesn't work correctly, change the 1 below to 0 to
	/// use stable but non-constexpr rtti fallback implementation
#if UTL_GCC
	template <typename T>
	constexpr auto __ctti_nameof_impl() {
		auto constexpr prettySize = std::size(__PRETTY_FUNCTION__);
		auto constexpr beginSize = std::size("auto utl::__ctti_nameof_impl() [T = ") - 1;
		
		utl::basic_static_string pretty = __PRETTY_FUNCTION__;
		return pretty.template substr<prettySize - beginSize-2>(beginSize);
	}
#elif UTL_MSVC
	template <typename T>
	constexpr auto __ctti_nameof_impl() {
		constexpr utl::basic_static_string pretty = __FUNCSIG__;
		auto constexpr prettySize = utl::strlen(pretty.data());
		auto constexpr beginSize = std::size("auto __cdecl utl::__ctti_nameof_impl");

		return pretty.template substr<prettySize - beginSize - 7>(beginSize);
	}
#endif
	
	template <typename T>
	inline constexpr auto __ctti_nameof = __ctti_nameof_impl<T>();
	
	std::string demangle_name(char const*);
	
#if 1
	template <typename T>
	constexpr inline utl::basic_static_string const nameof = __ctti_nameof<T>;
#else // rtti fallback
	template <typename T>
	static inline std::string const nameof = __demangle_name(typeid(T).name());
#endif
	
	template <typename T>
	std::string dynamic_nameof(T& value) {
		return demangle_name(typeid(value).name());
	}
	
	std::string qualified_function_name(std::string_view pretty);
	
}
