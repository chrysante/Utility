#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "common.hpp"

#if !defined(UTL_DEBUG_LEVEL)
#if defined(NDEBUG)
#define UTL_DEBUG_LEVEL 0
#else // defined(NDEBUG)
#define UTL_DEBUG_LEVEL 1
#endif // defined(NDEBUG)
#endif // !defined(UTL_DEBUG_LEVEL)

// __utl_assert
#if UTL_DEBUG_LEVEL > 0
#define __utl_assert(COND, ...)                                                \
    (!(COND) ? (__utl_debugbreak("Assertion Failed"), (void)0) : (void)0)
#else // UTL_DEBUG_LEVEL > 0
#define __utl_assert(COND, ...) (void)0
#endif // UTL_DEBUG_LEVEL > 0

#if UTL_DEBUG_LEVEL > 1
#define __utl_assert_audit(COND, ...) __utl_assert(COND)
#else // UTL_DEBUG_LEVEL > 1
#define __utl_assert_audit(COND, ...) (void)0
#endif // UTL_DEBUG_LEVEL > 1

// __utl_expect, __utl_ensure
#define __utl_expect(COND, ...) __utl_assert(COND)
#define __utl_ensure(COND, ...) __utl_assert(COND)

#define __utl_expect_audit(COND, ...) __utl_assert_audit(COND)
#define __utl_ensure_audit(COND, ...) __utl_assert_audit(COND)

// __utl_bounds_check
#define __utl_bounds_check(index, lower, upper)                                \
    (__utl_expect(index >= lower), __utl_expect(index < upper))

// __utl_debugbreak
#if __clang__
#define __utl_debugbreak(...) __builtin_debugtrap()
#elif __GNUC__
#define __utl_debugbreak(...) __builtin_trap()
#elif _MSC_VER
#define __utl_debugbreak(...) __debugbreak()
#else
#error Unknown compiler
#endif

// __utl_debugfail
#if __clang__ || __GNUC__
#define __utl_debugfail(...) __builtin_trap()
#elif _MSC_VER
#define __utl_debugfail(...) __debugbreak()
#else
#error Unknown compiler
#endif

// __utl_unreachable
#if __clang__ || __GNUC__
#define __utl_unreachable(...) (__utl_debugbreak(), __builtin_unreachable())
#elif _MSC_VER
#define __utl_unreachable(...) __debugbreak()
#else
#error Unknown compiler
#endif
