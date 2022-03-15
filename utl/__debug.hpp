#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#if defined(UTL_ASSERT_WITH_EXCEPTIONS)
#	include <exception>
#endif

#if defined(__GNUC__) || defined(__clang__)
#	define _UTL_NORETURN __attribute__((analyzer_noreturn))
#else
#	define _UTL_NORETURN
#endif

#ifndef UTL_DEBUG_LEVEL
#	define UTL_DEBUG_LEVEL 0
#endif

// __utl_assert
#if UTL_DEBUG_LEVEL > 0
#	define __utl_assert(COND, ...) (!(COND) ? (__utl_debugbreak("Assertion Failed"), (void)0) : (void)0)
#else // UTL_DEBUG_LEVEL > 0
#	define __utl_assert(COND, ...) (void)0
#endif // UTL_DEBUG_LEVEL > 0

#if UTL_DEBUG_LEVEL > 1
#	define __utl_assert_audit(COND, ...) __utl_assert(COND)
#else // UTL_DEBUG_LEVEL > 1
#	define __utl_assert_audit(COND, ...) (void)0
#endif // UTL_DEBUG_LEVEL > 1

// __utl_expect, __utl_ensure
#define __utl_expect(COND, ...) __utl_assert(COND)
#define __utl_ensure(COND, ...) __utl_assert(COND)

// __utl_bounds_check
#define __utl_bounds_check(index, lower, upper) \
	(__utl_expect(index >= lower), __utl_expect(index < upper))

// __utl_debugbreak
#if defined(UTL_ASSERT_WITH_EXCEPTIONS)
#	define __utl_debugbreak(...) (throw std::runtime_error("Assertion Failed"))
#else // defined(UTL_ASSERT_WITH_EXCEPTIONS)
#	if __GNUC__ || __clang__
#		define __utl_debugbreak(...) __builtin_trap()
#	else // __GNUC__ || __clang__
#		define __utl_debugbreak(...) __debugbreak()
#	endif // __GNUC__ || __clang__
#endif // defined(UTL_ASSERT_WITH_EXCEPTIONS)

// utl_static_assert
#if defined(UTL_CPP)
#define utl_static_assert(...) static_assert(__VA_ARGS__)
#else // UTL(CPP)
#define utl_static_assert(...)
#endif // UTL(CPP)


