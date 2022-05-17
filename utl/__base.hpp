#pragma once

/// MARK: Detect Language
#if defined(__METAL_VERSION__)
#	define UTL_METAL 1
#elif defined(__cplusplus)
#	define UTL_CPP 1
#	if __cplusplus < 202002L
#		error Requires C++20
#	endif
#else
#	error Unsupported Language
#endif

/// MARK: Detect Compiler
#if defined(__GNUC__) || defined(__clang__)
#	define UTL_GCC 1
#elif defined(_MSC_VER)
#	define UTL_MSVC 1
#else
#	error Unsupported Compiler
#endif

/// MARK: Systems
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#	define UTL_POSIX 1
#endif

/// MARK: System Header
#if UTL_GCC
#	define _UTL_SYSTEM_HEADER_ _Pragma("GCC system_header")
#else
#	define _UTL_SYSTEM_HEADER_
#endif

_UTL_SYSTEM_HEADER_

/// MARK: UTL_DEBUG_LEVEL
#ifndef UTL_DEBUG_LEVEL
#	ifdef NDEBUG
#		define UTL_DEBUG_LEVEL 0
#	else
#		define UTL_DEBUG_LEVEL 1
#	endif
#endif

#ifdef UTL_CPP // guard here because general purpose header may be included in shader source

/// MARK: Attributes
/*
 UTL_LIKELY and UTL_UNLIKELY attributes are used like this:
 if UTL_LIKELY (x == 0) { ... }
 if UTL_UNLIKELY (x == 1) { ... }
 */
#if UTL_GCC
#	define UTL_LIKELY(...)   (__builtin_expect(bool(__VA_ARGS__), 1))
#	define UTL_UNLIKELY(...) (__builtin_expect(bool(__VA_ARGS__), 0))
#else 
#	define UTL_LIKELY(...)   (__VA_ARGS__)
#	define UTL_UNLIKELY(...) (__VA_ARGS__)
#endif

#if UTL_GCC

#	define __utl_pure                 __attribute__((const))
#	define __utl_nodiscard            [[nodiscard]]
#	if UTL_DEBUG_LEVEL > 1
#		define __utl_always_inline
#	else // UTL_DEBUG_LEVEL > 1
#		define __utl_always_inline     __attribute__((always_inline))
#	endif // UTL_DEBUG_LEVEL > 1

#	define __utl_noinline             __attribute__((noinline))
#	if UTL_DEBUG_LEVEL > 1
#		define __utl_interface_export
#	else // UTL_DEBUG_LEVEL > 1
#		define __utl_interface_export  __attribute__((nodebug))
#	endif // UTL_DEBUG_LEVEL > 1

#else // UTL_GCC

#	define __utl_pure
#	define __utl_nodiscard
#	define __utl_mathfunction
#	if UTL_DEBUG_LEVEL > 1
#		define __utl_always_inline
#	else // UTL_DEBUG_LEVEL > 1
#		define __utl_always_inline
#	endif // UTL_DEBUG_LEVEL > 1

#	define __utl_noinline
#	if UTL_DEBUG_LEVEL > 1
#		define __utl_interface_export
#	else // UTL_DEBUG_LEVEL > 1
#		define __utl_interface_export
#	endif // UTL_DEBUG_LEVEL > 1

#endif // UTL_GCC

/// MARK: Sanitizers
#if UTL_GCC
#	define _UTL_DISABLE_UBSAN_INTEGER __attribute__((no_sanitize("integer")))
#else // UTL_GCC
#	define _UTL_DISABLE_UBSAN_INTEGER
#endif // UTL_GCC

#endif // UTL_CPP
