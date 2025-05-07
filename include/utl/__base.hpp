#pragma once

/// MARK: Detect Language
#if defined(__METAL_VERSION__)
#define UTL_METAL 1
#elif defined(__cplusplus)
#define UTL_CPP 1
#ifndef _MSVC_LANG
#if __cplusplus < 202002L
#error Requires C++20
#endif
#else // _MSVC_LANG defined
#if _MSVC_LANG < 202002L
#error Requires C++20
#endif
#endif // _MSVC_LANG
#else
#error Unsupported Language
#endif

/// MARK: Systems
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define UTL_POSIX 1
#endif

/// MARK: System Header
#define _UTL_SYSTEM_HEADER_

/// MARK: UTL_DEBUG_LEVEL
#ifndef UTL_DEBUG_LEVEL
#ifdef NDEBUG
#define UTL_DEBUG_LEVEL 0
#else
#define UTL_DEBUG_LEVEL 1
#endif
#endif

#ifdef UTL_CPP // guard here because general purpose header may be included in
               // shader source

/// MARK: Attributes
/*
 UTL_LIKELY and UTL_UNLIKELY attributes are used like this:
 if UTL_LIKELY (x == 0) { ... }
 if UTL_UNLIKELY (x == 1) { ... }
 */
#if defined(__GNUC__)
#define UTL_LIKELY(...)   (__builtin_expect(bool(__VA_ARGS__), 1))
#define UTL_UNLIKELY(...) (__builtin_expect(bool(__VA_ARGS__), 0))
#else
#define UTL_LIKELY(...)   (__VA_ARGS__)
#define UTL_UNLIKELY(...) (__VA_ARGS__)
#endif

#if defined(__GNUC__)

#define __utl_pure      __attribute__((const))
#define __utl_nodiscard [[nodiscard]]

#define __utl_always_inline // This only exists because I'm too lazy to remove
                            // it from the source code

#define __utl_noinline __attribute__((noinline))
#if UTL_DEBUG_LEVEL > 1
#define __utl_interface_export
#else // UTL_DEBUG_LEVEL > 1
#define __utl_interface_export
#endif // UTL_DEBUG_LEVEL > 1

#else // !defined(__GNUC__)

#define __utl_pure
#define __utl_nodiscard
#define __utl_mathfunction
#if UTL_DEBUG_LEVEL > 1
#define __utl_always_inline
#else // UTL_DEBUG_LEVEL > 1
#define __utl_always_inline
#endif // UTL_DEBUG_LEVEL > 1

#define __utl_noinline
#if UTL_DEBUG_LEVEL > 1
#define __utl_interface_export
#else // UTL_DEBUG_LEVEL > 1
#define __utl_interface_export
#endif // UTL_DEBUG_LEVEL > 1

#endif // !defined(__GNUC__)

/// MARK: Sanitizers
#if defined(__GNUC__)
#define _UTL_DISABLE_UBSAN_INTEGER __attribute__((no_sanitize("integer")))
#else
#define _UTL_DISABLE_UBSAN_INTEGER
#endif

#define UTL_DEPRECATED(Reason)

#endif // UTL_CPP
