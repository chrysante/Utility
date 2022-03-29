#pragma once

/// MARK: Check Compiler Compatibility
#if !(__clang__ || __GNUC__ || _MSC_VER)
#	error Unsupported Compiler
#endif

/// MARK: System Header
#if __GNUC__ || __clang__
#define _UTL_SYSTEM_HEADER_ _Pragma("GCC system_header")
#else
#define _UTL_SYSTEM_HEADER_
#endif

_UTL_SYSTEM_HEADER_

/// MARK: UTL_DEBUG_LEVEL
#ifndef UTL_DEBUG_LEVEL
#	define UTL_DEBUG_LEVEL 0
#endif

/// MARK: UTL_CPP
#if defined(__cplusplus) && !defined(__METAL_VERSION__)
#	define UTL_CPP
#	if __cplusplus < 202002L
#		error Requires c++20
#	endif
#endif

/// MARK: UTL_METAL
#ifdef __METAL_VERSION__
#	define UTL_METAL
#endif

#ifdef UTL_CPP // guard here because general purpose header may be included in shader source

/// MARK: Attributes
#if defined(__GNUC__) || defined(__clang__)
#	define UTL_LIKELY(...)   (__builtin_expect((__VA_ARGS__), 1))
#	define UTL_UNLIKELY(...) (__builtin_expect((__VA_ARGS__), 0))
#else 
#	define UTL_LIKELY(...)   (__VA_ARGS__)
#	define UTL_UNLIKELY(...) (__VA_ARGS__)
#endif

#if defined(__GNUC__) || defined(__clang__)

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

#else // defined(__GNUC__) || defined(__clang__)

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

#endif // defined(__GNUC__) || defined(__clang__)

/// MARK: Sanitizers
#if defined(__GNUC__) || defined(__clang__)
#	define _UTL_DISABLE_UBSAN_INTEGER __attribute__((no_sanitize("integer")))
#else // defined(__GNUC__) || defined(__clang__)
#	define _UTL_DISABLE_UBSAN_INTEGER
#endif // defined(__GNUC__) || defined(__clang__)

#endif // UTL_CPP
