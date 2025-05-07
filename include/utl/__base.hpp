#ifndef UTL___BASE_HPP_
#define UTL___BASE_HPP_

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

#ifdef UTL_CPP // guard here because general purpose header may be included in
               // shader source

/// MARK: Attributes

#if defined(__GNUC__)
#define __utl_noinline __attribute__((noinline))
#else // !defined(__GNUC__)
#define __utl_noinline
#endif // !defined(__GNUC__)

/// MARK: Sanitizers
#if defined(__GNUC__)
#define _UTL_DISABLE_UBSAN_INTEGER __attribute__((no_sanitize("integer")))
#else
#define _UTL_DISABLE_UBSAN_INTEGER
#endif

#define UTL_DEPRECATED(Reason)

#endif // UTL_CPP

#endif // UTL___BASE_HPP_
