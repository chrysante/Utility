#pragma once

/// mtl.hpp

#ifndef __MTL_MTL_HPP_INCLUDED__
#define __MTL_MTL_HPP_INCLUDED__

#pragma once

/// __vector.hpp

#ifndef __MTL_VECTOR_HPP_INCLUDED__
#define __MTL_VECTOR_HPP_INCLUDED__

#pragma once

/// __base.hpp

#ifndef __MTL_BASE_HPP_INCLUDED__
#define __MTL_BASE_HPP_INCLUDED__

// MARK: Check Compiler Compatibility
#if !(__clang__ || __GNUC__ || _MSC_VER)
#	error Unsupported Compiler
#endif

// MARK: System Header
#if __GNUC__ || __clang__
#define _MTL_SYSTEM_HEADER_ _Pragma("GCC system_header")
#else
#define _MTL_SYSTEM_HEADER_
#endif

_MTL_SYSTEM_HEADER_

// MARK: Customization Points
#ifndef MTL_DEBUG_LEVEL
#	ifdef NDEBUG
#		define MTL_DEBUG_LEVEL 0
#	else
#		define MTL_DEBUG_LEVEL 1
#	endif
#endif

#ifndef MTL_SAFE_MATH
#	define MTL_SAFE_MATH 1
#endif

#ifndef MTL_DEFAULT_PACKED
#	define MTL_DEFAULT_PACKED  0
#endif

#ifndef MTL_AVX
#	define MTL_AVX 0
#endif

#ifndef MTL_NAMESPACE_NAME
#	define MTL_NAMESPACE_NAME  mtl
#endif

#ifndef MTL_UNICODE_MATH_PARANTHESES
#	if defined(__APPLE__)
#		define MTL_UNICODE_MATH_PARANTHESES 1
#	else
#		define MTL_UNICODE_MATH_PARANTHESES 0
#	endif
#endif

/// MARK: - Attributes
#if defined(__GNUC__) || defined(__clang__)

#	define __mtl_pure                 __attribute__((const))
#	define __mtl_nodiscard            [[nodiscard]]
#	define __mtl_mathfunction         __mtl_nodiscard
#	if MTL_DEBUG_LEVEL > 1
#		define __mtl_always_inline
#	else // MTL_DEBUG_LEVEL > 1
#		define __mtl_always_inline     __attribute__((always_inline))
#	endif // MTL_DEBUG_LEVEL > 1

#	define __mtl_noinline             __attribute__((noinline))
#	if MTL_DEBUG_LEVEL > 1
#		define __mtl_interface_export
#	else // MTL_DEBUG_LEVEL > 1
#		define __mtl_interface_export  __attribute__((nodebug))
#	endif // MTL_DEBUG_LEVEL > 1

#else

#	define __mtl_pure
#	define __mtl_nodiscard
#	define __mtl_mathfunction
#	if MTL_DEBUG_LEVEL > 1
#		define __mtl_always_inline
#	else // MTL_DEBUG_LEVEL > 1
#		define __mtl_always_inline
#	endif // MTL_DEBUG_LEVEL > 1

#	define __mtl_noinline
#	if MTL_DEBUG_LEVEL > 1
#		define __mtl_interface_export
#	else // MTL_DEBUG_LEVEL > 1
#		define __mtl_interface_export
#	endif // MTL_DEBUG_LEVEL > 1

#endif

/// MARK: - Debug
#if MTL_DEBUG_LEVEL > 0
#	define __mtl_assert(COND) (!(COND) ? (__mtl_debugbreak("Assertion Failed"), (void)0) : (void)0)
#else // MTL_DEBUG_LEVEL > 0
#	define __mtl_assert(COND) (void)0
#endif // MTL_DEBUG_LEVEL > 0

#if MTL_DEBUG_LEVEL > 1
#	define __mtl_assert_audit(COND) __mtl_assert(COND)
#else // MTL_DEBUG_LEVEL > 1
#	define __mtl_assert_audit(COND) (void)0
#endif // MTL_DEBUG_LEVEL > 1


#define __mtl_expect(COND) __mtl_assert(COND)
#define __mtl_ensure(COND) __mtl_assert(COND)



#if defined(__clang__)
#	define __mtl_debugbreak(msg) __builtin_debugtrap()
#elif defined(__GNUC__)
#	define __mtl_debugbreak(msg) __builtin_trap()
#elif defined(_MSC_VER)
#	define __mtl_debugbreak(msg) __debugbreak()
#else 
#	error
#endif

#define __mtl_bounds_check(index, lower, upper) (__mtl_expect(lower <= index), __mtl_expect(index < upper))

/// MARK: Namespace
#ifdef _VMTL
#	error We need this macro name _VMTL
#else
#	define _VMTL MTL_NAMESPACE_NAME
#endif

/// MARK: Safe Arithmetic
#if MTL_SAFE_MATH
#	define __mtl_safe_math_if(...) if (__VA_ARGS__)
#else
#	define __mtl_safe_math_if(...) if constexpr ((0))
#endif

#endif // __MTL_BASE_HPP_INCLUDED__

_MTL_SYSTEM_HEADER_

#pragma once

/// __common.hpp

#ifndef __MTL_COMMON_HPP_INCLUDED__
#define __MTL_COMMON_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_

#include <cmath>
#include <utility>
#include <iosfwd>
#include <concepts>
#include <functional>

#define __MTL_DECLARE_STDINT_TYPEDEFS__
/// __typedefs.hpp

/// DELIBERATELY NO INCLUDE GUARDS! Sections have their own include guards.


_MTL_SYSTEM_HEADER_


	
#ifdef __MTL_DECLARE_STDINT_TYPEDEFS__
#ifndef __MTL_STDINT_TYPEDEFS_INCLUDED__
#define __MTL_STDINT_TYPEDEFS_INCLUDED__
	
#include <cstdint>

namespace _VMTL {
	
	/**
	 These exist so I can conditionally declare 'namespace metal = mtl' in shared header files and use types below as metal::int32_t etc.
	 */

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
	
	using std::size_t;
	using usize = std::size_t;
	using isize = std::ptrdiff_t;
	
}
	
#endif // __MTL_STDINT_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_STDINT_TYPEDEFS__
	
	


namespace _VMTL {
	
	/// MARK: - Complex
#ifdef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#ifndef __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#define __MTL_COMPLEX_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using complex_float   = complex<float>;
		using complex_double  = complex<double>;
		using complex_ldouble = complex<long double>;
		
		using complex_int     = complex<int>;
		using complex_long    = complex<long>;
		using complex_llong   = complex<long long>;
		using complex_uint    = complex<unsigned int>;
		using complex_ulong   = complex<unsigned long>;
		using complex_ullong  = complex<unsigned long long>;
		
	}
	
#endif // __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_COMPLEX_TYPEDEFS__
	
	/// MARK: - Quaternion
#ifdef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#ifndef __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#define __MTL_QUATERNION_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using quaternion_float   = quaternion<float>;
		using quaternion_double  = quaternion<double>;
		using quaternion_ldouble = quaternion<long double>;
		
		using quaternion_int     = quaternion<int>;
		using quaternion_long    = quaternion<long>;
		using quaternion_llong   = quaternion<long long>;
		using quaternion_uint    = quaternion<unsigned int>;
		using quaternion_ulong   = quaternion<unsigned long>;
		using quaternion_ullong  = quaternion<unsigned long long>;
		
	}
	
#endif // __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_QUATERNION_TYPEDEFS__
	
	// MARK: - Vector
#ifdef __MTL_DECLARE_VECTOR_TYPEDEFS__
#ifndef __MTL_VECTOR_TYPEDEFS_INCLUDED__
#define __MTL_VECTOR_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using vector2 = vector<T, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector3 = vector<T, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector4 = vector<T, 4, O>;
	
	inline namespace short_types {
		
		using size2            = vector2<std::size_t>;
		using size3            = vector3<std::size_t>;
		using size4            = vector4<std::size_t>;
		
		using usize2            = vector2<std::size_t>;
		using usize3            = vector3<std::size_t>;
		using usize4            = vector4<std::size_t>;
		
		using isize2            = vector2<std::ptrdiff_t>;
		using isize3            = vector3<std::ptrdiff_t>;
		using isize4            = vector4<std::ptrdiff_t>;
		
		using bool2            = vector2<bool>;
		using bool3            = vector3<bool>;
		using bool4            = vector4<bool>;
		using char2            = vector2<char>;
		using char3            = vector3<char>;
		using char4            = vector4<char>;
		using schar2           = vector2<char>;
		using schar3           = vector3<char>;
		using schar4           = vector4<char>;
		using uchar2           = vector2<unsigned char>;
		using uchar3           = vector3<unsigned char>;
		using uchar4           = vector4<unsigned char>;
		using short2           = vector2<short>;
		using short3           = vector3<short>;
		using short4           = vector4<short>;
		using ushort2          = vector2<unsigned short>;
		using ushort3          = vector3<unsigned short>;
		using ushort4          = vector4<unsigned short>;
		using int2             = vector2<int>;
		using int3             = vector3<int>;
		using int4             = vector4<int>;
		using uint2            = vector2<unsigned int>;
		using uint3            = vector3<unsigned int>;
		using uint4            = vector4<unsigned int>;
		using long2            = vector2<long>;
		using long3            = vector3<long>;
		using long4            = vector4<long>;
		using ulong2           = vector2<unsigned long>;
		using ulong3           = vector3<unsigned long>;
		using ulong4           = vector4<unsigned long>;
		using llong2           = vector2<long long>;
		using llong3           = vector3<long long>;
		using llong4           = vector4<long long>;
		using ullong2          = vector2<unsigned long long>;
		using ullong3          = vector3<unsigned long long>;
		using ullong4          = vector4<unsigned long long>;
		using float2           = vector2<float>;
		using float3           = vector3<float>;
		using float4           = vector4<float>;
		using double2          = vector2<double>;
		using double3          = vector3<double>;
		using double4          = vector4<double>;
		using ldouble2         = vector2<long double>;
		using ldouble3         = vector3<long double>;
		using ldouble4         = vector4<long double>;
		
		using packed_bool2     = vector2<bool,               vector_options{}.packed(true)>;
		using packed_bool3     = vector3<bool,               vector_options{}.packed(true)>;
		using packed_bool4     = vector4<bool,               vector_options{}.packed(true)>;
		using packed_char2     = vector2<char,               vector_options{}.packed(true)>;
		using packed_char3     = vector3<char,               vector_options{}.packed(true)>;
		using packed_char4     = vector4<char,               vector_options{}.packed(true)>;
		using packed_uchar2    = vector2<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar3    = vector3<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar4    = vector4<unsigned char,      vector_options{}.packed(true)>;
		using packed_short2    = vector2<short,              vector_options{}.packed(true)>;
		using packed_short3    = vector3<short,              vector_options{}.packed(true)>;
		using packed_short4    = vector4<short,              vector_options{}.packed(true)>;
		using packed_ushort2   = vector2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3   = vector3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4   = vector4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2      = vector2<int,                vector_options{}.packed(true)>;
		using packed_int3      = vector3<int,                vector_options{}.packed(true)>;
		using packed_int4      = vector4<int,                vector_options{}.packed(true)>;
		using packed_uint2     = vector2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3     = vector3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4     = vector4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2     = vector2<long,               vector_options{}.packed(true)>;
		using packed_long3     = vector3<long,               vector_options{}.packed(true)>;
		using packed_long4     = vector4<long,               vector_options{}.packed(true)>;
		using packed_ulong2    = vector2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3    = vector3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4    = vector4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2    = vector2<long long,          vector_options{}.packed(true)>;
		using packed_llong3    = vector3<long long,          vector_options{}.packed(true)>;
		using packed_llong4    = vector4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2   = vector2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3   = vector3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4   = vector4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2    = vector2<float,              vector_options{}.packed(true)>;
		using packed_float3    = vector3<float,              vector_options{}.packed(true)>;
		using packed_float4    = vector4<float,              vector_options{}.packed(true)>;
		using packed_double2   = vector2<double,             vector_options{}.packed(true)>;
		using packed_double3   = vector3<double,             vector_options{}.packed(true)>;
		using packed_double4   = vector4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2  = vector2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3  = vector3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4  = vector4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2    = vector2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3    = vector3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4    = vector4<bool,               vector_options{}.packed(false)>;
		using aligned_char2    = vector2<char,               vector_options{}.packed(false)>;
		using aligned_char3    = vector3<char,               vector_options{}.packed(false)>;
		using aligned_char4    = vector4<char,               vector_options{}.packed(false)>;
		using aligned_uchar2   = vector2<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar3   = vector3<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar4   = vector4<unsigned char,      vector_options{}.packed(false)>;
		using aligned_short2   = vector2<short,              vector_options{}.packed(false)>;
		using aligned_short3   = vector3<short,              vector_options{}.packed(false)>;
		using aligned_short4   = vector4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2  = vector2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3  = vector3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4  = vector4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2     = vector2<int,                vector_options{}.packed(false)>;
		using aligned_int3     = vector3<int,                vector_options{}.packed(false)>;
		using aligned_int4     = vector4<int,                vector_options{}.packed(false)>;
		using aligned_uint2    = vector2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3    = vector3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4    = vector4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2    = vector2<long,               vector_options{}.packed(false)>;
		using aligned_long3    = vector3<long,               vector_options{}.packed(false)>;
		using aligned_long4    = vector4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2   = vector2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3   = vector3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4   = vector4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2   = vector2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3   = vector3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4   = vector4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2  = vector2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3  = vector3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4  = vector4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2   = vector2<float,              vector_options{}.packed(false)>;
		using aligned_float3   = vector3<float,              vector_options{}.packed(false)>;
		using aligned_float4   = vector4<float,              vector_options{}.packed(false)>;
		using aligned_double2  = vector2<double,             vector_options{}.packed(false)>;
		using aligned_double3  = vector3<double,             vector_options{}.packed(false)>;
		using aligned_double4  = vector4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2 = vector2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3 = vector3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4 = vector4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_VECTOR_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_VECTOR_TYPEDEFS__
	
	/// MARK: - Matrix
#ifdef __MTL_DECLARE_MATRIX_TYPEDEFS__
#ifndef __MTL_MATRIX_TYPEDEFS_INCLUDED__
#define __MTL_MATRIX_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using matrix2x2 = matrix<T, 2, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x3 = matrix<T, 2, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x4 = matrix<T, 2, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x2 = matrix<T, 3, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x3 = matrix<T, 3, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x4 = matrix<T, 3, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x2 = matrix<T, 4, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x3 = matrix<T, 4, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x4 = matrix<T, 4, 4, O>;
	
	inline namespace short_types {
	
		using bool2x2            = matrix2x2<bool,               vector_options{}>;
		using bool2x3            = matrix2x3<bool,               vector_options{}>;
		using bool2x4            = matrix2x4<bool,               vector_options{}>;
		using bool3x2            = matrix3x2<bool,               vector_options{}>;
		using bool3x3            = matrix3x3<bool,               vector_options{}>;
		using bool3x4            = matrix3x4<bool,               vector_options{}>;
		using bool4x2            = matrix4x2<bool,               vector_options{}>;
		using bool4x3            = matrix4x3<bool,               vector_options{}>;
		using bool4x4            = matrix4x4<bool,               vector_options{}>;
		using short2x2           = matrix2x2<short,              vector_options{}>;
		using short2x3           = matrix2x3<short,              vector_options{}>;
		using short2x4           = matrix2x4<short,              vector_options{}>;
		using short3x2           = matrix3x2<short,              vector_options{}>;
		using short3x3           = matrix3x3<short,              vector_options{}>;
		using short3x4           = matrix3x4<short,              vector_options{}>;
		using short4x2           = matrix4x2<short,              vector_options{}>;
		using short4x3           = matrix4x3<short,              vector_options{}>;
		using short4x4           = matrix4x4<short,              vector_options{}>;
		using ushort2x2          = matrix2x2<unsigned short,     vector_options{}>;
		using ushort2x3          = matrix2x3<unsigned short,     vector_options{}>;
		using ushort2x4          = matrix2x4<unsigned short,     vector_options{}>;
		using ushort3x2          = matrix3x2<unsigned short,     vector_options{}>;
		using ushort3x3          = matrix3x3<unsigned short,     vector_options{}>;
		using ushort3x4          = matrix3x4<unsigned short,     vector_options{}>;
		using ushort4x2          = matrix4x2<unsigned short,     vector_options{}>;
		using ushort4x3          = matrix4x3<unsigned short,     vector_options{}>;
		using ushort4x4          = matrix4x4<unsigned short,     vector_options{}>;
		using int2x2             = matrix2x2<int,                vector_options{}>;
		using int2x3             = matrix2x3<int,                vector_options{}>;
		using int2x4             = matrix2x4<int,                vector_options{}>;
		using int3x2             = matrix3x2<int,                vector_options{}>;
		using int3x3             = matrix3x3<int,                vector_options{}>;
		using int3x4             = matrix3x4<int,                vector_options{}>;
		using int4x2             = matrix4x2<int,                vector_options{}>;
		using int4x3             = matrix4x3<int,                vector_options{}>;
		using int4x4             = matrix4x4<int,                vector_options{}>;
		using uint2x2            = matrix2x2<unsigned int,       vector_options{}>;
		using uint2x3            = matrix2x3<unsigned int,       vector_options{}>;
		using uint2x4            = matrix2x4<unsigned int,       vector_options{}>;
		using uint3x2            = matrix3x2<unsigned int,       vector_options{}>;
		using uint3x3            = matrix3x3<unsigned int,       vector_options{}>;
		using uint3x4            = matrix3x4<unsigned int,       vector_options{}>;
		using uint4x2            = matrix4x2<unsigned int,       vector_options{}>;
		using uint4x3            = matrix4x3<unsigned int,       vector_options{}>;
		using uint4x4            = matrix4x4<unsigned int,       vector_options{}>;
		using long2x2            = matrix2x2<long,               vector_options{}>;
		using long2x3            = matrix2x3<long,               vector_options{}>;
		using long2x4            = matrix2x4<long,               vector_options{}>;
		using long3x2            = matrix3x2<long,               vector_options{}>;
		using long3x3            = matrix3x3<long,               vector_options{}>;
		using long3x4            = matrix3x4<long,               vector_options{}>;
		using long4x2            = matrix4x2<long,               vector_options{}>;
		using long4x3            = matrix4x3<long,               vector_options{}>;
		using long4x4            = matrix4x4<long,               vector_options{}>;
		using ulong2x2           = matrix2x2<unsigned long,      vector_options{}>;
		using ulong2x3           = matrix2x3<unsigned long,      vector_options{}>;
		using ulong2x4           = matrix2x4<unsigned long,      vector_options{}>;
		using ulong3x2           = matrix3x2<unsigned long,      vector_options{}>;
		using ulong3x3           = matrix3x3<unsigned long,      vector_options{}>;
		using ulong3x4           = matrix3x4<unsigned long,      vector_options{}>;
		using ulong4x2           = matrix4x2<unsigned long,      vector_options{}>;
		using ulong4x3           = matrix4x3<unsigned long,      vector_options{}>;
		using ulong4x4           = matrix4x4<unsigned long,      vector_options{}>;
		using llong2x2           = matrix2x2<long long,          vector_options{}>;
		using llong2x3           = matrix2x3<long long,          vector_options{}>;
		using llong2x4           = matrix2x4<long long,          vector_options{}>;
		using llong3x2           = matrix3x2<long long,          vector_options{}>;
		using llong3x3           = matrix3x3<long long,          vector_options{}>;
		using llong3x4           = matrix3x4<long long,          vector_options{}>;
		using llong4x2           = matrix4x2<long long,          vector_options{}>;
		using llong4x3           = matrix4x3<long long,          vector_options{}>;
		using llong4x4           = matrix4x4<long long,          vector_options{}>;
		using ullong2x2          = matrix2x2<unsigned long long, vector_options{}>;
		using ullong2x3          = matrix2x3<unsigned long long, vector_options{}>;
		using ullong2x4          = matrix2x4<unsigned long long, vector_options{}>;
		using ullong3x2          = matrix3x2<unsigned long long, vector_options{}>;
		using ullong3x3          = matrix3x3<unsigned long long, vector_options{}>;
		using ullong3x4          = matrix3x4<unsigned long long, vector_options{}>;
		using ullong4x2          = matrix4x2<unsigned long long, vector_options{}>;
		using ullong4x3          = matrix4x3<unsigned long long, vector_options{}>;
		using ullong4x4          = matrix4x4<unsigned long long, vector_options{}>;
		using float2x2           = matrix2x2<float,              vector_options{}>;
		using float2x3           = matrix2x3<float,              vector_options{}>;
		using float2x4           = matrix2x4<float,              vector_options{}>;
		using float3x2           = matrix3x2<float,              vector_options{}>;
		using float3x3           = matrix3x3<float,              vector_options{}>;
		using float3x4           = matrix3x4<float,              vector_options{}>;
		using float4x2           = matrix4x2<float,              vector_options{}>;
		using float4x3           = matrix4x3<float,              vector_options{}>;
		using float4x4           = matrix4x4<float,              vector_options{}>;
		using double2x2          = matrix2x2<double,             vector_options{}>;
		using double2x3          = matrix2x3<double,             vector_options{}>;
		using double2x4          = matrix2x4<double,             vector_options{}>;
		using double3x2          = matrix3x2<double,             vector_options{}>;
		using double3x3          = matrix3x3<double,             vector_options{}>;
		using double3x4          = matrix3x4<double,             vector_options{}>;
		using double4x2          = matrix4x2<double,             vector_options{}>;
		using double4x3          = matrix4x3<double,             vector_options{}>;
		using double4x4          = matrix4x4<double,             vector_options{}>;
		using ldouble2x2         = matrix2x2<long double,        vector_options{}>;
		using ldouble2x3         = matrix2x3<long double,        vector_options{}>;
		using ldouble2x4         = matrix2x4<long double,        vector_options{}>;
		using ldouble3x2         = matrix3x2<long double,        vector_options{}>;
		using ldouble3x3         = matrix3x3<long double,        vector_options{}>;
		using ldouble3x4         = matrix3x4<long double,        vector_options{}>;
		using ldouble4x2         = matrix4x2<long double,        vector_options{}>;
		using ldouble4x3         = matrix4x3<long double,        vector_options{}>;
		using ldouble4x4         = matrix4x4<long double,        vector_options{}>;
	 
		using packed_bool2x2     = matrix2x2<bool,               vector_options{}.packed(true)>;
		using packed_bool2x3     = matrix2x3<bool,               vector_options{}.packed(true)>;
		using packed_bool2x4     = matrix2x4<bool,               vector_options{}.packed(true)>;
		using packed_bool3x2     = matrix3x2<bool,               vector_options{}.packed(true)>;
		using packed_bool3x3     = matrix3x3<bool,               vector_options{}.packed(true)>;
		using packed_bool3x4     = matrix3x4<bool,               vector_options{}.packed(true)>;
		using packed_bool4x2     = matrix4x2<bool,               vector_options{}.packed(true)>;
		using packed_bool4x3     = matrix4x3<bool,               vector_options{}.packed(true)>;
		using packed_bool4x4     = matrix4x4<bool,               vector_options{}.packed(true)>;
		using packed_short2x2    = matrix2x2<short,              vector_options{}.packed(true)>;
		using packed_short2x3    = matrix2x3<short,              vector_options{}.packed(true)>;
		using packed_short2x4    = matrix2x4<short,              vector_options{}.packed(true)>;
		using packed_short3x2    = matrix3x2<short,              vector_options{}.packed(true)>;
		using packed_short3x3    = matrix3x3<short,              vector_options{}.packed(true)>;
		using packed_short3x4    = matrix3x4<short,              vector_options{}.packed(true)>;
		using packed_short4x2    = matrix4x2<short,              vector_options{}.packed(true)>;
		using packed_short4x3    = matrix4x3<short,              vector_options{}.packed(true)>;
		using packed_short4x4    = matrix4x4<short,              vector_options{}.packed(true)>;
		using packed_ushort2x2   = matrix2x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x3   = matrix2x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x4   = matrix2x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x2   = matrix3x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x3   = matrix3x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x4   = matrix3x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x2   = matrix4x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x3   = matrix4x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x4   = matrix4x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2x2      = matrix2x2<int,                vector_options{}.packed(true)>;
		using packed_int2x3      = matrix2x3<int,                vector_options{}.packed(true)>;
		using packed_int2x4      = matrix2x4<int,                vector_options{}.packed(true)>;
		using packed_int3x2      = matrix3x2<int,                vector_options{}.packed(true)>;
		using packed_int3x3      = matrix3x3<int,                vector_options{}.packed(true)>;
		using packed_int3x4      = matrix3x4<int,                vector_options{}.packed(true)>;
		using packed_int4x2      = matrix4x2<int,                vector_options{}.packed(true)>;
		using packed_int4x3      = matrix4x3<int,                vector_options{}.packed(true)>;
		using packed_int4x4      = matrix4x4<int,                vector_options{}.packed(true)>;
		using packed_uint2x2     = matrix2x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x3     = matrix2x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x4     = matrix2x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x2     = matrix3x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x3     = matrix3x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x4     = matrix3x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x2     = matrix4x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x3     = matrix4x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x4     = matrix4x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2x2     = matrix2x2<long,               vector_options{}.packed(true)>;
		using packed_long2x3     = matrix2x3<long,               vector_options{}.packed(true)>;
		using packed_long2x4     = matrix2x4<long,               vector_options{}.packed(true)>;
		using packed_long3x2     = matrix3x2<long,               vector_options{}.packed(true)>;
		using packed_long3x3     = matrix3x3<long,               vector_options{}.packed(true)>;
		using packed_long3x4     = matrix3x4<long,               vector_options{}.packed(true)>;
		using packed_long4x2     = matrix4x2<long,               vector_options{}.packed(true)>;
		using packed_long4x3     = matrix4x3<long,               vector_options{}.packed(true)>;
		using packed_long4x4     = matrix4x4<long,               vector_options{}.packed(true)>;
		using packed_ulong2x2    = matrix2x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x3    = matrix2x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x4    = matrix2x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x2    = matrix3x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x3    = matrix3x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x4    = matrix3x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x2    = matrix4x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x3    = matrix4x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x4    = matrix4x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2x2    = matrix2x2<long long,          vector_options{}.packed(true)>;
		using packed_llong2x3    = matrix2x3<long long,          vector_options{}.packed(true)>;
		using packed_llong2x4    = matrix2x4<long long,          vector_options{}.packed(true)>;
		using packed_llong3x2    = matrix3x2<long long,          vector_options{}.packed(true)>;
		using packed_llong3x3    = matrix3x3<long long,          vector_options{}.packed(true)>;
		using packed_llong3x4    = matrix3x4<long long,          vector_options{}.packed(true)>;
		using packed_llong4x2    = matrix4x2<long long,          vector_options{}.packed(true)>;
		using packed_llong4x3    = matrix4x3<long long,          vector_options{}.packed(true)>;
		using packed_llong4x4    = matrix4x4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2x2   = matrix2x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x3   = matrix2x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x4   = matrix2x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x2   = matrix3x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x3   = matrix3x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x4   = matrix3x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x2   = matrix4x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x3   = matrix4x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x4   = matrix4x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2x2    = matrix2x2<float,              vector_options{}.packed(true)>;
		using packed_float2x3    = matrix2x3<float,              vector_options{}.packed(true)>;
		using packed_float2x4    = matrix2x4<float,              vector_options{}.packed(true)>;
		using packed_float3x2    = matrix3x2<float,              vector_options{}.packed(true)>;
		using packed_float3x3    = matrix3x3<float,              vector_options{}.packed(true)>;
		using packed_float3x4    = matrix3x4<float,              vector_options{}.packed(true)>;
		using packed_float4x2    = matrix4x2<float,              vector_options{}.packed(true)>;
		using packed_float4x3    = matrix4x3<float,              vector_options{}.packed(true)>;
		using packed_float4x4    = matrix4x4<float,              vector_options{}.packed(true)>;
		using packed_double2x2   = matrix2x2<double,             vector_options{}.packed(true)>;
		using packed_double2x3   = matrix2x3<double,             vector_options{}.packed(true)>;
		using packed_double2x4   = matrix2x4<double,             vector_options{}.packed(true)>;
		using packed_double3x2   = matrix3x2<double,             vector_options{}.packed(true)>;
		using packed_double3x3   = matrix3x3<double,             vector_options{}.packed(true)>;
		using packed_double3x4   = matrix3x4<double,             vector_options{}.packed(true)>;
		using packed_double4x2   = matrix4x2<double,             vector_options{}.packed(true)>;
		using packed_double4x3   = matrix4x3<double,             vector_options{}.packed(true)>;
		using packed_double4x4   = matrix4x4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2x2  = matrix2x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x3  = matrix2x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x4  = matrix2x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x2  = matrix3x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x3  = matrix3x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x4  = matrix3x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x2  = matrix4x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x3  = matrix4x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x4  = matrix4x4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2x2    = matrix2x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x3    = matrix2x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x4    = matrix2x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x2    = matrix3x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x3    = matrix3x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x4    = matrix3x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x2    = matrix4x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x3    = matrix4x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x4    = matrix4x4<bool,               vector_options{}.packed(false)>;
		using aligned_short2x2   = matrix2x2<short,              vector_options{}.packed(false)>;
		using aligned_short2x3   = matrix2x3<short,              vector_options{}.packed(false)>;
		using aligned_short2x4   = matrix2x4<short,              vector_options{}.packed(false)>;
		using aligned_short3x2   = matrix3x2<short,              vector_options{}.packed(false)>;
		using aligned_short3x3   = matrix3x3<short,              vector_options{}.packed(false)>;
		using aligned_short3x4   = matrix3x4<short,              vector_options{}.packed(false)>;
		using aligned_short4x2   = matrix4x2<short,              vector_options{}.packed(false)>;
		using aligned_short4x3   = matrix4x3<short,              vector_options{}.packed(false)>;
		using aligned_short4x4   = matrix4x4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2x2  = matrix2x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x3  = matrix2x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x4  = matrix2x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x2  = matrix3x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x3  = matrix3x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x4  = matrix3x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x2  = matrix4x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x3  = matrix4x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x4  = matrix4x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2x2     = matrix2x2<int,                vector_options{}.packed(false)>;
		using aligned_int2x3     = matrix2x3<int,                vector_options{}.packed(false)>;
		using aligned_int2x4     = matrix2x4<int,                vector_options{}.packed(false)>;
		using aligned_int3x2     = matrix3x2<int,                vector_options{}.packed(false)>;
		using aligned_int3x3     = matrix3x3<int,                vector_options{}.packed(false)>;
		using aligned_int3x4     = matrix3x4<int,                vector_options{}.packed(false)>;
		using aligned_int4x2     = matrix4x2<int,                vector_options{}.packed(false)>;
		using aligned_int4x3     = matrix4x3<int,                vector_options{}.packed(false)>;
		using aligned_int4x4     = matrix4x4<int,                vector_options{}.packed(false)>;
		using aligned_uint2x2    = matrix2x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x3    = matrix2x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x4    = matrix2x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x2    = matrix3x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x3    = matrix3x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x4    = matrix3x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x2    = matrix4x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x3    = matrix4x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x4    = matrix4x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2x2    = matrix2x2<long,               vector_options{}.packed(false)>;
		using aligned_long2x3    = matrix2x3<long,               vector_options{}.packed(false)>;
		using aligned_long2x4    = matrix2x4<long,               vector_options{}.packed(false)>;
		using aligned_long3x2    = matrix3x2<long,               vector_options{}.packed(false)>;
		using aligned_long3x3    = matrix3x3<long,               vector_options{}.packed(false)>;
		using aligned_long3x4    = matrix3x4<long,               vector_options{}.packed(false)>;
		using aligned_long4x2    = matrix4x2<long,               vector_options{}.packed(false)>;
		using aligned_long4x3    = matrix4x3<long,               vector_options{}.packed(false)>;
		using aligned_long4x4    = matrix4x4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2x2   = matrix2x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x3   = matrix2x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x4   = matrix2x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x2   = matrix3x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x3   = matrix3x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x4   = matrix3x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x2   = matrix4x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x3   = matrix4x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x4   = matrix4x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2x2   = matrix2x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x3   = matrix2x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x4   = matrix2x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x2   = matrix3x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x3   = matrix3x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x4   = matrix3x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x2   = matrix4x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x3   = matrix4x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x4   = matrix4x4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2x2  = matrix2x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x3  = matrix2x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x4  = matrix2x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x2  = matrix3x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x3  = matrix3x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x4  = matrix3x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x2  = matrix4x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x3  = matrix4x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x4  = matrix4x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2x2   = matrix2x2<float,              vector_options{}.packed(false)>;
		using aligned_float2x3   = matrix2x3<float,              vector_options{}.packed(false)>;
		using aligned_float2x4   = matrix2x4<float,              vector_options{}.packed(false)>;
		using aligned_float3x2   = matrix3x2<float,              vector_options{}.packed(false)>;
		using aligned_float3x3   = matrix3x3<float,              vector_options{}.packed(false)>;
		using aligned_float3x4   = matrix3x4<float,              vector_options{}.packed(false)>;
		using aligned_float4x2   = matrix4x2<float,              vector_options{}.packed(false)>;
		using aligned_float4x3   = matrix4x3<float,              vector_options{}.packed(false)>;
		using aligned_float4x4   = matrix4x4<float,              vector_options{}.packed(false)>;
		using aligned_double2x2  = matrix2x2<double,             vector_options{}.packed(false)>;
		using aligned_double2x3  = matrix2x3<double,             vector_options{}.packed(false)>;
		using aligned_double2x4  = matrix2x4<double,             vector_options{}.packed(false)>;
		using aligned_double3x2  = matrix3x2<double,             vector_options{}.packed(false)>;
		using aligned_double3x3  = matrix3x3<double,             vector_options{}.packed(false)>;
		using aligned_double3x4  = matrix3x4<double,             vector_options{}.packed(false)>;
		using aligned_double4x2  = matrix4x2<double,             vector_options{}.packed(false)>;
		using aligned_double4x3  = matrix4x3<double,             vector_options{}.packed(false)>;
		using aligned_double4x4  = matrix4x4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2x2 = matrix2x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x3 = matrix2x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x4 = matrix2x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x2 = matrix3x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x3 = matrix3x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x4 = matrix3x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x2 = matrix4x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x3 = matrix4x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x4 = matrix4x4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_MATRIX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_MATRIX_TYPEDEFS__
	
}


namespace _VMTL {
	
	/// Just so it exists
	inline namespace literals {}
	
	/// MARK: - struct constants
	template <typename T = double>
	requires std::is_floating_point_v<T>
	struct constants {
		static inline constexpr T pi    = 3.1415926535897932384626433832795028841971693993751058209749445923;
		static inline constexpr T e     = 2.7182818284590452353602874713526624977572470936999595749669676277;
		static inline constexpr T sqrt2 = 1.4142135623730950488016887242096980785696718753769480731766797379;
	};
	
	/// MARK: - struct vector_options
	struct vector_options {
		constexpr bool packed() const { return __packed; }
		constexpr vector_options packed(bool b) const {
			auto result = *this;
			result.__packed = b;
			return result;
		}
		
		bool __packed = MTL_DEFAULT_PACKED;
		
		friend constexpr vector_options combine(std::same_as<vector_options> auto const&... o) {
			return { .__packed = (o.packed() && ...) };
		}
	};
	
	/// MARK: - Forward Declarations
	template <typename>
	struct complex;
	
	template <typename>
	struct quaternion;
	
	template <typename, std::size_t, vector_options = vector_options{}>
	struct vector;
	
	template <typename, std::size_t, std::size_t, vector_options = vector_options{}>
	struct matrix;
	
	/// MARK: - Type Traits
	template <typename T>
	struct is_real_scalar: std::is_arithmetic<T>{};
	
	template <typename T>
	struct is_complex: std::false_type{};
	template <typename T>
	struct is_complex<complex<T>>: std::true_type{};
	template <typename T>
	struct is_complex<complex<T> const>: std::true_type{};
	template <typename T>
	struct is_complex<complex<T> volatile>: std::true_type{};
	template <typename T>
	struct is_complex<complex<T> const volatile>: std::true_type{};
	template <typename T>
	struct is_quaternion: std::false_type{};
	template <typename T>
	struct is_quaternion<quaternion<T>>: std::true_type{};
	template <typename T>
	struct is_quaternion<quaternion<T> const>: std::true_type{};
	template <typename T>
	struct is_quaternion<quaternion<T> volatile>: std::true_type{};
	template <typename T>
	struct is_quaternion<quaternion<T> const volatile>: std::true_type{};

	template <typename T>
	struct is_vector: std::false_type{};
	template <typename T, std::size_t N, vector_options O>
	struct is_vector<vector<T, N, O>>: std::true_type{};
	template <typename T, std::size_t N, vector_options O>
	struct is_vector<vector<T, N, O> const>: std::true_type{};
	template <typename T, std::size_t N, vector_options O>
	struct is_vector<vector<T, N, O> volatile>: std::true_type{};
	template <typename T, std::size_t N, vector_options O>
	struct is_vector<vector<T, N, O> const volatile>: std::true_type{};

	template <typename T>
	struct is_matrix : std::false_type {};
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct is_matrix<matrix<T, R, C, O>> : std::true_type {};
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct is_matrix<matrix<T, R, C, O> const> : std::true_type {};
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct is_matrix<matrix<T, R, C, O> volatile> : std::true_type {};
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct is_matrix<matrix<T, R, C, O> const volatile> : std::true_type {};
	
	template <typename T>
	struct __is_foreign_type_impl: std::conjunction<
		std::negation<is_complex<T>>,
		std::negation<is_quaternion<T>>,
		std::negation<is_vector<T>>,
		std::negation<is_matrix<T>>
	> {};
	
	template <typename T>
	struct __is_foreign_type: __is_foreign_type_impl<std::decay_t<T>> {};
	
	template <typename T>
	concept __foreign_type = __is_foreign_type<T>::value;
	
	template <typename Vector, typename ValueType, std::size_t N, typename = std::make_index_sequence<N>>
	constexpr bool __is_vector_type_v = false;
	
	template <typename Vector, typename ValueType, std::size_t N, std::size_t... I>
	constexpr bool __is_vector_type_v<Vector, ValueType, N, std::index_sequence<I...>> = requires(ValueType&& t) {
		Vector{ (I, t)... };
	};
	
	template <typename V, typename T, std::size_t N>
	concept __foreign_vector_type = __foreign_type<V> && __is_vector_type_v<V, T, N>;
	
	template <typename T>
	struct is_scalar: std::disjunction<is_real_scalar<T>, is_complex<T>, is_quaternion<T>> {};
	
	template <typename>
	struct get_underlying_type;
	
	template <typename T>
	struct get_underlying_type { using type = T; };
	
	template <typename T>
	struct get_underlying_type<complex<T>> { using type = T; };
	template <typename T>
	struct get_underlying_type<complex<T> const> { using type = T const; };
	template <typename T>
	struct get_underlying_type<complex<T> volatile> { using type = T volatile; };
	template <typename T>
	struct get_underlying_type<complex<T> const volatile> { using type = T const volatile; };

	template <typename T>
	struct get_underlying_type<quaternion<T>> { using type = T; };
	template <typename T>
	struct get_underlying_type<quaternion<T> const> { using type = T const; };
	template <typename T>
	struct get_underlying_type<quaternion<T> volatile> { using type = T volatile; };
	template <typename T>
	struct get_underlying_type<quaternion<T> const volatile> { using type = T const volatile; };

	template <typename T, std::size_t N, vector_options O>
	struct get_underlying_type<vector<T, N, O>> { using type = T; };
	template <typename T, std::size_t N, vector_options O>
	struct get_underlying_type<vector<T, N, O> const> { using type = T const; };
	template <typename T, std::size_t N, vector_options O>
	struct get_underlying_type<vector<T, N, O> volatile> { using type = T volatile; };
	template <typename T, std::size_t N, vector_options O>
	struct get_underlying_type<vector<T, N, O> const volatile> { using type = T const volatile; };
	
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct get_underlying_type<matrix<T, R, C, O>> { using type = T; };
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct get_underlying_type<matrix<T, R, C, O> const> { using type = T const; };
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct get_underlying_type<matrix<T, R, C, O> volatile> { using type = T volatile; };
	template <typename T, std::size_t R, std::size_t C, vector_options O>
	struct get_underlying_type<matrix<T, R, C, O> const volatile> { using type = T const volatile; };

	template <typename T, bool = is_complex<T>::value || is_quaternion<T>::value || is_vector<T>::value || is_matrix<T>::value>
	struct get_underlying_type_r /* bool = true */ { using type = typename get_underlying_type<T>::type; };
	template <typename T>
	struct get_underlying_type_r<T, false> { using type = T; };

	template <typename>
	struct get_vector_size;
	
	template <typename T>
	struct get_vector_size: std::integral_constant<std::size_t, 1> {};
	
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_size<vector<T, N, O>>: std::integral_constant<std::size_t, N> {};
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_size<vector<T, N, O> const>: std::integral_constant<std::size_t, N> {};
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_size<vector<T, N, O> volatile>: std::integral_constant<std::size_t, N> {};
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_size<vector<T, N, O> const volatile>: std::integral_constant<std::size_t, N> {};
	
	template <typename>
	struct get_vector_options;
	
	template <typename T>
	struct get_vector_options { static constexpr vector_options value = {}; };
	
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_options<vector<T, N, O>> { static constexpr vector_options value = O; };
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_options<vector<T, N, O> const> { static constexpr vector_options value = O; };
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_options<vector<T, N, O> volatile> { static constexpr vector_options value = O; };
	template <typename T, std::size_t N, vector_options O>
	struct get_vector_options<vector<T, N, O> const volatile> { static constexpr vector_options value = O; };
	
	template <typename...>
	struct __mtl_template_true_type: std::true_type {};
	
	template <typename...>
	struct __mtl_template_false_type: std::false_type {};
	
	/// MARK: Tuple Size
	template <typename T, std::size_t = sizeof(T)>
	std::true_type __is_defined_impl(T *);
	std::false_type __is_defined_impl(...);
	
	template <typename T>
	using __is_defined = decltype(__is_defined_impl(std::declval<T*>()));
	
	template <typename T, std::size_t N>
	concept __tuple_of_size = __is_defined<std::tuple_size<std::decay_t<T>>>::value && (std::tuple_size<std::decay_t<T>>::value == N);
	
	template <typename, typename, typename...>
	struct __tuple_conversion_test;
	
	template <typename T, typename... Args, std::size_t... I>
	struct __tuple_conversion_test<T, std::index_sequence<I...>, Args...> {
		static constexpr bool value = (requires(T&& t) { { get<I>(t) } -> std::convertible_to<Args>; } && ...);
	};
	
	template <typename T, typename... Args>
	concept __tuple_of_types = __tuple_of_size<T, sizeof...(Args)> && __tuple_conversion_test<T, std::index_sequence_for<Args...>, Args...>::value;
	
	/// MARK: - Concepts
	template <typename T>
	concept real_scalar = is_real_scalar<T>::value;
	template <typename T>
	concept scalar      = is_scalar<T>::value;
	
	template <typename T, typename U, typename ... V>
	concept __mtl_any_of = (std::same_as<T, U> || (std::same_as<T, V> || ...));
	
	template <class F, class R, class... Args>
	concept invocable_r = /*invocable<F, Args...> && */ std::convertible_to<std::invoke_result_t<F, Args...>, R>;
	
	template <class R, class F, class... Args>
	concept regular_invocable_r = invocable_r<R, F, Args...>;
	
	/// MARK: __mtl_floatify
#define __mtl_floatify(__type) __mtl_to_float_t<__type>
	
	template <typename>
	struct __mtl_to_float;
	
	template <typename T>
	using __mtl_to_float_t = typename __mtl_to_float<T>::type;
	
	template <typename T> requires std::is_arithmetic_v<T>
	struct __mtl_to_float<T>             { using type = double; };
	template <>
	struct __mtl_to_float<float>         { using type = float; };
	template <>
	struct __mtl_to_float<long double>   { using type = long double; };

	template <typename T>
	struct __mtl_to_float<complex<T>>    { using type = complex<__mtl_to_float_t<T>>; };
	
	template <typename T>
	struct __mtl_to_float<quaternion<T>> { using type = quaternion<__mtl_to_float_t<T>>; };
	
	template <typename>
	struct __mtl_to_complex;
	
	template <typename T>
	using __mtl_to_complex_t = typename __mtl_to_complex<T>::type;
	
	template <typename T> requires std::is_arithmetic_v<T>
	struct __mtl_to_complex<T> { using type = complex<T>; };
	
	template <typename T>
	struct __mtl_to_complex<complex<T>> { using type = complex<T>; };
	
	/// MARK: Stripped Decltype
	#define __mtl_decltype_stripped(...) std::decay_t<decltype(__VA_ARGS__)>
	
	/// MARK: Promotion
#define __mtl_promote(...) ::_VMTL::promote_t<__VA_ARGS__>
	
	template <typename... T>
	struct promote;
	
	template <typename... T>
	using promote_t = typename promote<T...>::type;
	
	template <typename T>
	auto __mtl_do_promote() -> T;
	template <typename T, typename U>
	auto __mtl_do_promote() -> decltype(bool{} ? std::declval<T>() : std::declval<U>());
	template <typename T, typename U, typename V, typename... Rest>
	auto __mtl_do_promote() -> decltype(__mtl_do_promote<std::remove_reference_t<decltype(__mtl_do_promote<T, U>())>, V, Rest...>());
	
	template <typename T, typename U>
	auto __mtl_can_promote(int) -> decltype(bool{} ? std::declval<T>() : std::declval<U>(), std::true_type{});
	template <typename, typename>
	auto __mtl_can_promote(...) -> std::false_type;
	
	template <typename T, typename U>
	requires (decltype(__mtl_can_promote<T, U>(0))::value)
	struct promote<T, U> {
		using type = std::remove_reference_t<decltype(__mtl_do_promote<T, U>())>;
	};
	
	/// If this template is undefined, then T, U, V have no common type
	template <typename T, typename U, typename... V>
	struct promote<T, U, V...>: promote<typename promote<T, U>::type, V...> {};
	
	/// Promote Complex Numbers
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::complex<T>, _VMTL::complex<U>> {
		using type = _VMTL::complex<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::complex<T>, U> {
		using type = _VMTL::complex<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<T, _VMTL::complex<U>> {
		using type = _VMTL::complex<typename _VMTL::promote<T, U>::type>;
	};
	
	/// Promote Quaternions
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::quaternion<T>, _VMTL::quaternion<U>> {
		using type = _VMTL::quaternion<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::quaternion<T>, _VMTL::complex<U>> {
		using type = _VMTL::quaternion<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::quaternion<T>, U> {
		using type = _VMTL::quaternion<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<_VMTL::complex<T>, _VMTL::quaternion<U>> {
		using type = _VMTL::quaternion<typename _VMTL::promote<T, U>::type>;
	};
	template <_VMTL::real_scalar T, _VMTL::real_scalar U>
	struct promote<T, _VMTL::quaternion<U>> {
		using type = _VMTL::quaternion<typename _VMTL::promote<T, U>::type>;
	};
	
	/// Promote Vectors
	template <typename T, typename U, std::size_t Size, vector_options O>
	struct promote<vector<T, Size, O>, U> {
		using type = vector<typename promote<T, U>::type, Size, O>;
	};
	template <typename T, typename U, std::size_t Size, vector_options O>
	struct promote<T, vector<U, Size, O>> {
		using type = vector<typename promote<T, U>::type, Size, O>;
	};
	template <typename T, typename U, std::size_t Size,
			  vector_options O, vector_options P>
	struct promote<vector<T, Size, O>, vector<U, Size, P>> {
		using type = vector<typename promote<T, U>::type, Size, combine(O, P)>;
	};
	template <typename T, typename U, std::size_t S1, std::size_t S2,
			  vector_options O, vector_options P>
	struct promote<vector<T, S1, O>, vector<U, S2, P>>; /// Can't promote these
	 
	/// Promote Matrices
	template <typename T, typename U, std::size_t Rows, std::size_t Columns, vector_options O>
	struct promote<matrix<T, Rows, Columns, O>, U> {
		using type = matrix<typename promote<T, U>::type, Rows, Columns, O>;
	};
	template <typename T, typename U, std::size_t Rows, std::size_t Columns, vector_options O>
	struct promote<T, matrix<U, Rows, Columns, O>> {
		using type = matrix<typename promote<T, U>::type, Rows, Columns, O>;
	};
	template <typename T, typename U, std::size_t Rows, std::size_t Columns,
			  vector_options O, vector_options P>
	struct promote<matrix<T, Rows, Columns, O>, matrix<U, Rows, Columns, P>> {
		using type = matrix<typename promote<T, U>::type, Rows, Columns, combine(O, P)>;
	};
	template <typename T, typename U,
			  std::size_t Rows1, // std::size_t Columns1,
			  std::size_t Rows2, std::size_t Columns2,
			  vector_options O, vector_options P>
	struct promote<matrix<T, Rows1, Columns2, O>, matrix<U, Rows2, Columns2, P>>; /// Can't promote two matrices of different dimensions
	template <typename T, typename U,
			  std::size_t Size, std::size_t Rows, std::size_t Columns,
			  vector_options O, vector_options P>
	struct promote<matrix<T, Rows, Columns, O>, vector<U, Size, P>>;              /// Can't promote matrices with vectors
	template <typename T, typename U,
			  std::size_t Size, std::size_t Rows, std::size_t Columns,
			  vector_options O, vector_options P>
	struct promote<vector<T, Size, P>, matrix<U, Rows, Columns, O>>;              /// Can't promote vectors with matrices
	
	/// MARK: - enum struct handedness
	enum struct handedness {
		left_handed, right_handed
	};
	inline constexpr handedness left_handed = handedness::left_handed;
	inline constexpr handedness right_handed = handedness::right_handed;
	inline constexpr handedness default_handedness = handedness::right_handed;
	
	/// MARK: Basic Algorithms
	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T const& max(T const& a, T const& b) {
		return (a < b) ? b : a;
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T& max(T& a, T& b) {
		return const_cast<T&>(max(const_cast<T const&>(a),
								  const_cast<T const&>(b)));
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T const& max(T const& a, std::same_as<T> auto const& b, std::same_as<T> auto const&... c) {
		return max(max(a, b), c...);
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T& max(T& a, std::same_as<T> auto& b, std::same_as<T> auto&... c) {
		return const_cast<T&>(max(const_cast<T const&>(a),
								  const_cast<T const&>(b),
								  const_cast<T const&>(c)...));
	}
	
	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T const& min(T const& a, T const& b) {
		return (b < a) ? b : a;
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T& min(T& a, T& b) {
		return const_cast<T&>(min(const_cast<T const&>(a),
								  const_cast<T const&>(b)));
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T const& min(T const& a, std::same_as<T> auto const& b, std::same_as<T> auto const&... c) {
		return min(min(a, b), c...);
	}

	template <typename T> requires (std::is_arithmetic_v<T>)
	constexpr T& min(T& a, std::same_as<T> auto& b, std::same_as<T> auto&... c) {
		return const_cast<T&>(min(const_cast<T const&>(a),
								  const_cast<T const&>(b),
								  const_cast<T const&>(c)...));
	}
	
	/// MARK: - __mtl_hash_combine
	template <typename T>
	std::size_t __mtl_hash_combine(std::size_t seed, T const& v) {
		std::hash<T> const hash;
		return seed ^ hash(v) + 0x9e37'79b9'43e3'f411 + (seed << 6) + (seed >> 2);
	}
	
	constexpr std::size_t __mtl_hash_seed = 0x5f23'ef3b'34b5'e321;
	
	/// MARK: - Helpers
#define __mtl_forward(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
	
	// __mtl_with_index_sequence
#define __MTL_PRIV_WIS_FT(I, S) <std::size_t... I>
#define __MTL_PRIV_WIS_FP(I, S) (::std::index_sequence<I...>)
#define __MTL_PRIV_WIS_FI(I, S) (::std::make_index_sequence<S>{})
#define __mtl_with_index_sequence(Index, ...) \
[&] __MTL_PRIV_WIS_FT Index __MTL_PRIV_WIS_FP Index -> decltype(auto) __VA_ARGS__ __MTL_PRIV_WIS_FI Index
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool __mtl_is_unit(T const& x) {
		if constexpr (std::is_floating_point_v<T>) {
			return x != 0;
		}
		else if constexpr (std::is_integral_v<T>) {
			return x == 1 || x == -1;
		}
		else {
			static_assert(!__mtl_template_true_type<T>::value);
		}
	}
	
	template <std::size_t... I>
	using __mtl_index_sequence = std::index_sequence<I...>;
	
	template <std::size_t N>
	using __mtl_make_index_sequence = std::make_index_sequence<N>;
	
	template <typename... T>
	struct __mtl_type_sequence {};
	
	template <typename T, std::size_t N, typename... R>
	struct __mtl_make_type_sequence_impl {
		using type = typename __mtl_make_type_sequence_impl<T, N - 1, R..., T>::type;
	};
	
	template <typename T, typename... R>
	struct __mtl_make_type_sequence_impl<T, 0, R...> {
		using type = __mtl_type_sequence<R...>;
	};
	
	template <typename T, std::size_t N>
	using __mtl_make_type_sequence = typename __mtl_make_type_sequence_impl<T, N>::type;

	
	/// MARK: - class approx	
	template <typename T>
	inline constexpr T __mtl_float_threshold = 0;
	template <>
	inline constexpr float       __mtl_float_threshold<float>       = 0.000000000000001f;
	template <>
	inline constexpr double      __mtl_float_threshold<double>      = 0.000000000000001;
	template <>
	inline constexpr long double __mtl_float_threshold<long double> = 0.000000000000001;
	
	template <typename T>
	requires std::is_floating_point_v<T>
	bool __mtl_nearly_equal(T a, T b, T epsilon = __mtl_float_threshold<T>) {
		T const absA = std::abs(a);
		T const absB = std::abs(b);
		T const diff = std::abs(a - b);

		if (a == b) { // shortcut, handles infinities
			return true;
		}
		else if (a == 0 || b == 0 || (absA + absB < std::numeric_limits<T>::min())) {
			// a or b is zero or both are extremely close to zero
			// relative error is less meaningful here
			return diff < epsilon;
			//return diff < (epsilon * std::numeric_limits<T>::min());
		}
		else { // use relative error
			return diff / _VMTL::min((absA + absB), std::numeric_limits<T>::max()) < epsilon;
		}
	}
	
	template <typename T>
		requires (std::is_arithmetic_v<T>) || requires (T const& t) {
			t.begin(); t.end();
		}
	class approx {
		using U = typename get_underlying_type_r<T>::type;
	public:
		approx(T const& z, U epsilon = __mtl_float_threshold<U>): _value(z), _epsilon(epsilon) {}
		
		bool __mtl_comp_eq(T rhs) const {
			if constexpr (std::is_floating_point_v<T>) {
				return __mtl_nearly_equal(_value, rhs, _epsilon);
			}
			else if constexpr (std::is_integral_v<T>) {
				return _value == rhs;
			}
			else {
				auto i = _value.begin();
				auto j = rhs.begin();
				auto end = _value.end();
				for (; i != end; ++i, ++j) {
					using underlying = typename get_underlying_type<T>::type;
					if (*i != approx<underlying>(*j, _epsilon)) {
						return false;
					}
				}
				return true;
			}
		}
		
		approx& epsilon(U new_epsilon) { _epsilon = new_epsilon;  return *this; }

		friend std::ostream& operator<<(std::ostream& str, approx<T> const& a) {
			return str << a._value;
		}
		
	private:
		T _value;
		U _epsilon;
	};
	
	template <typename T, typename U>
	bool operator==(approx<T> const& r, U const& l) {
		return r.__mtl_comp_eq(l);
	}
	template <typename T, typename U>
	bool operator==(U const& r, approx<T> const& l) {
		return l.__mtl_comp_eq(r);
	}
	
	/// MARK: - Helpers
	template <real_scalar T>
	constexpr __mtl_floatify(T) to_radians(T degrees) {
		using F = __mtl_floatify(T);
		return degrees * constants<F>::pi / 180;
	}
	
	template <std::floating_point T>
	constexpr T to_degrees(T radians) {
		return radians / constants<T>::pi * 180;
	}
	
	/// MARK: - Functions on Builtins
	__mtl_pure __mtl_always_inline
	inline constexpr std::uint32_t __mtl_byte_swap(std::uint32_t val) {
		val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
		return (val << 16) | (val >> 16);
	}
	
	__mtl_pure __mtl_always_inline
	inline /*constexpr*/ float __mtl_fract(float f) {
		float i;
		float result = std::modf(f, &i);
		return (result < 0.0f) + result;
	}
	__mtl_pure __mtl_always_inline
	inline /*constexpr*/ double __mtl_fract(double f) {
		double i;
		double result = std::modf(f, &i);
		return (result < 0.0) + result;
	}
	__mtl_pure __mtl_always_inline
	inline /*constexpr*/ long double __mtl_fract(long double f) {
		long double i;
		long double result = std::modf(f, &i);
		return (result < 0.0l) + result;
	}
	
	template <typename T, typename U = T>
	requires std::is_integral_v<T> && std::is_integral_v<U>
	__mtl_pure __mtl_always_inline
	constexpr __mtl_promote(T, U) __mtl_ceil_divide(T a, U b) {
		return (a / b) + !!(a % b);
	}
	
	
#define MTL_FOR_EACH_BUILTIN_TYPE(F) \
	F(signed   char);                \
	F(unsigned char);                \
	F(signed   short);               \
	F(unsigned short);               \
	F(signed   int);                 \
	F(unsigned int);                 \
	F(signed   long);                \
	F(unsigned long);                \
	F(signed   long long);           \
	F(unsigned long long);           \
	F(float);                        \
	F(double);                       \
	F(long double)
	
#define MTL_FOR_EACH_BUILTIN_ARITHMETIC_TYPE(F) \
	F(signed   int);                            \
	F(unsigned int);                            \
	F(signed   long);                           \
	F(unsigned long);                           \
	F(signed   long long);                      \
	F(unsigned long long);                      \
	F(float);                                   \
	F(double);                                  \
	F(long double)
	
#define MTL_LENGTH_SQUARED(T) \
	__mtl_mathfunction __mtl_pure __mtl_always_inline      \
	inline constexpr T norm_squared(T x) { return x * x; } \
	__mtl_mathfunction __mtl_pure __mtl_always_inline      \
	inline constexpr T length_squared(T x) { return norm_squared(x); }
	MTL_FOR_EACH_BUILTIN_TYPE(MTL_LENGTH_SQUARED);
#undef MTL_LENGTH_SQUARED
	
#define MTL_SQR(T)                                      \
	__mtl_mathfunction __mtl_pure __mtl_always_inline   \
	constexpr inline T __mtl_sqr(T x) { return x * x; }
	MTL_FOR_EACH_BUILTIN_TYPE(MTL_SQR);
#undef MTL_SQR

#define MTL_CONJ(T) \
	__mtl_mathfunction __mtl_pure __mtl_always_inline      \
	inline constexpr T conj(T x) { return x; } 
	MTL_FOR_EACH_BUILTIN_TYPE(MTL_CONJ);
#undef MTL_CONJ
	
#define MTL_IPOW(T)                                  \
	__mtl_mathfunction __mtl_pure                    \
	constexpr inline T __mtl_ipow(T x, int i) {      \
		__mtl_expect(i >= 0);                        \
		if (i == 1)     return x;                    \
		if (i == 0)     return 1;                    \
		if (i % 2 == 0) return __mtl_ipow(x * x, i / 2); \
		return x * __mtl_ipow(x * x, i / 2);             \
	}
	MTL_FOR_EACH_BUILTIN_ARITHMETIC_TYPE(MTL_IPOW);
#undef MTL_IPOW

#undef MTL_FOR_EACH_BUILTIN_ARITHMETIC_TYPE
#undef MTL_FOR_EACH_BUILTIN_TYPE
	
	// MARK: - Hypot
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T fast_hypot(T a, std::same_as<T> auto... b) {
		return std::sqrt(((a * a) + ... + (b * b)));
	}

	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T __mtl_safe_hypot(T a, std::same_as<T> auto b) {
		return std::hypot(a, b);
	}
	
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T __mtl_safe_hypot(T a, std::same_as<T> auto... b) {
		/// Make all arguments positive ...
		  a = std::abs(a);
		((b = std::abs(b)), ...);
		/// ... put the biggest argument into a ...
		std::swap(a, _VMTL::max(a, b...));
		/// ... and do the math:
		/// b / a <= 1 for all b, so the square of b / a is also <= 1,
		/// so the argument to std::sqrt is <= count of arguments, so no  overflow can occur.
		/// Overflow can only occur if the actual result overflows.
		return a * std::sqrt((T(1.0) + ... + __mtl_sqr(b / a)));
	}
	
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure __mtl_always_inline __mtl_interface_export
	inline T __mtl_hypot(T a) { return std::abs(a); }
	
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T __mtl_hypot(T a, std::same_as<T> auto... b) {
		T sum_of_squares = ((a * a) + ... + (b * b));
		/// Only use __mtl_safe_hypot if necessary. This is about 5 times faster on non-overflowing inputs and about 10% slower on always-overflowing inputs
		__mtl_safe_math_if (isinf(sum_of_squares)) {
			return __mtl_safe_hypot(a, b...);
		}
		return std::sqrt(sum_of_squares);
	}

	/// Interface
	template <scalar T, scalar... U>
	__mtl_mathfunction __mtl_pure __mtl_always_inline __mtl_interface_export
	inline auto hypot(T a, U... b) {
		using F = __mtl_floatify(__mtl_promote(T, U...));
		return __mtl_hypot((F)a, (F)b...);
	}
	
	// MARK: - pHypot
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T __mtl_safe_phypot(T p, T a, std::same_as<T> auto... b) {
		  a = std::abs(a);
		((b = std::abs(b)), ...);
		std::swap(a, _VMTL::max(a, b...));
		return a * std::pow((1.0 + ... + std::pow(b / a, p)), T(1) / p);
	}
	
	template <scalar T>
	__mtl_mathfunction __mtl_pure __mtl_always_inline __mtl_interface_export
	inline T __mtl_phypot(T p, T a) { return std::abs(a); }
	
	template <_VMTL::__mtl_any_of<float, double, long double> T>
	__mtl_mathfunction __mtl_pure
	inline T __mtl_phypot(T p, T a, std::same_as<T> auto... b) {
		T sum_of_powers = ((std::pow(std::abs(a), p) + ... + (std::pow(std::abs(b), p))));
		__mtl_safe_math_if (isinf(sum_of_powers)) {
			return __mtl_safe_phypot(p, a, b...);
		}
		return std::pow(sum_of_powers, T(1) / p);
	}

	/// Interface
	template <scalar T, scalar... U>
	__mtl_mathfunction __mtl_pure __mtl_always_inline __mtl_interface_export
	inline auto phypot(scalar auto p, T a, U... b) {
		using F = __mtl_floatify(__mtl_promote(T, U...));
		return __mtl_phypot((F)p, (F)a, (F)b...);
	}
	

	// MARK: - Basic Function Objects
#define _MTL_FUNCOBJ_DEF_(NAME, PARAMS, EXPR)  \
	struct NAME##_t {                          \
		constexpr auto operator() PARAMS const \
		requires requires { EXPR; }            \
		{ return EXPR; }                       \
	} inline constexpr NAME{}
	
	struct __mtl_plus_t {
		constexpr auto operator()(auto const& a) const
		requires requires { +a; }
		{ return +a; }
		constexpr auto operator()(auto const& a, auto const& b) const
		requires requires { a + b; }
		{ return a + b; }
	} inline constexpr __mtl_plus{};
	
	struct __mtl_minus_t {
		constexpr auto operator()(auto const& a) const
		requires requires { -a; }
		{ return -a; }
		constexpr auto operator()(auto const& a, auto const& b) const
		requires requires { a - b; }
		{ return a - b; }
	} inline constexpr __mtl_minus{};
	
	_MTL_FUNCOBJ_DEF_(__mtl_multiplies,  (auto const& a, auto const& b), a * b);
	_MTL_FUNCOBJ_DEF_(__mtl_divides,     (auto const& a, auto const& b), a / b);
	_MTL_FUNCOBJ_DEF_(__mtl_modulo,      (auto const& a, auto const& b), a % b);
	_MTL_FUNCOBJ_DEF_(__mtl_and,         (auto const& a, auto const& b), a & b);
	_MTL_FUNCOBJ_DEF_(__mtl_or,          (auto const& a, auto const& b), a | b);
	_MTL_FUNCOBJ_DEF_(__mtl_xor,         (auto const& a, auto const& b), a ^ b);
	_MTL_FUNCOBJ_DEF_(__mtl_not,         (auto const& a), ~a);
	_MTL_FUNCOBJ_DEF_(__mtl_equals,      (auto const& a, auto const& b), a == b);
	_MTL_FUNCOBJ_DEF_(__mtl_less,        (auto const& a, auto const& b), a < b);
	_MTL_FUNCOBJ_DEF_(__mtl_less_eq,     (auto const& a, auto const& b), a <= b);
	_MTL_FUNCOBJ_DEF_(__mtl_greater,     (auto const& a, auto const& b), a > b);
	_MTL_FUNCOBJ_DEF_(__mtl_greater_eq,  (auto const& a, auto const& b), a >= b);
	_MTL_FUNCOBJ_DEF_(__mtl_logical_and, (auto const& a, auto const& b), a && b);
	_MTL_FUNCOBJ_DEF_(__mtl_logical_or,  (auto const& a, auto const& b), a || b);
	_MTL_FUNCOBJ_DEF_(__mtl_logical_not, (auto const& a), !a);
	
	struct __mtl_abs_t {
		constexpr auto operator()(auto const& a) const {
			using std::abs;
			return abs(a);
		}
	} inline constexpr __mtl_abs{};
	
	struct __mtl_sqrt_t {
		constexpr auto operator()(auto const& a) const {
			using std::sqrt;
			return sqrt(a);
		}
	} inline constexpr __mtl_sqrt{};
	
}

#endif // __MTL_COMMON_HPP_INCLUDED__

#define __MTL_DECLARE_VECTOR_TYPEDEFS__
/// __typedefs.hpp

/// DELIBERATELY NO INCLUDE GUARDS! Sections have their own include guards.


_MTL_SYSTEM_HEADER_


	
#ifdef __MTL_DECLARE_STDINT_TYPEDEFS__
#ifndef __MTL_STDINT_TYPEDEFS_INCLUDED__
#define __MTL_STDINT_TYPEDEFS_INCLUDED__
	
#include <cstdint>

namespace _VMTL {
	
	/**
	 These exist so I can conditionally declare 'namespace metal = mtl' in shared header files and use types below as metal::int32_t etc.
	 */

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
	
	using std::size_t;
	using usize = std::size_t;
	using isize = std::ptrdiff_t;
	
}
	
#endif // __MTL_STDINT_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_STDINT_TYPEDEFS__
	
	


namespace _VMTL {
	
	/// MARK: - Complex
#ifdef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#ifndef __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#define __MTL_COMPLEX_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using complex_float   = complex<float>;
		using complex_double  = complex<double>;
		using complex_ldouble = complex<long double>;
		
		using complex_int     = complex<int>;
		using complex_long    = complex<long>;
		using complex_llong   = complex<long long>;
		using complex_uint    = complex<unsigned int>;
		using complex_ulong   = complex<unsigned long>;
		using complex_ullong  = complex<unsigned long long>;
		
	}
	
#endif // __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_COMPLEX_TYPEDEFS__
	
	/// MARK: - Quaternion
#ifdef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#ifndef __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#define __MTL_QUATERNION_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using quaternion_float   = quaternion<float>;
		using quaternion_double  = quaternion<double>;
		using quaternion_ldouble = quaternion<long double>;
		
		using quaternion_int     = quaternion<int>;
		using quaternion_long    = quaternion<long>;
		using quaternion_llong   = quaternion<long long>;
		using quaternion_uint    = quaternion<unsigned int>;
		using quaternion_ulong   = quaternion<unsigned long>;
		using quaternion_ullong  = quaternion<unsigned long long>;
		
	}
	
#endif // __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_QUATERNION_TYPEDEFS__
	
	// MARK: - Vector
#ifdef __MTL_DECLARE_VECTOR_TYPEDEFS__
#ifndef __MTL_VECTOR_TYPEDEFS_INCLUDED__
#define __MTL_VECTOR_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using vector2 = vector<T, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector3 = vector<T, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector4 = vector<T, 4, O>;
	
	inline namespace short_types {
		
		using size2            = vector2<std::size_t>;
		using size3            = vector3<std::size_t>;
		using size4            = vector4<std::size_t>;
		
		using usize2            = vector2<std::size_t>;
		using usize3            = vector3<std::size_t>;
		using usize4            = vector4<std::size_t>;
		
		using isize2            = vector2<std::ptrdiff_t>;
		using isize3            = vector3<std::ptrdiff_t>;
		using isize4            = vector4<std::ptrdiff_t>;
		
		using bool2            = vector2<bool>;
		using bool3            = vector3<bool>;
		using bool4            = vector4<bool>;
		using char2            = vector2<char>;
		using char3            = vector3<char>;
		using char4            = vector4<char>;
		using schar2           = vector2<char>;
		using schar3           = vector3<char>;
		using schar4           = vector4<char>;
		using uchar2           = vector2<unsigned char>;
		using uchar3           = vector3<unsigned char>;
		using uchar4           = vector4<unsigned char>;
		using short2           = vector2<short>;
		using short3           = vector3<short>;
		using short4           = vector4<short>;
		using ushort2          = vector2<unsigned short>;
		using ushort3          = vector3<unsigned short>;
		using ushort4          = vector4<unsigned short>;
		using int2             = vector2<int>;
		using int3             = vector3<int>;
		using int4             = vector4<int>;
		using uint2            = vector2<unsigned int>;
		using uint3            = vector3<unsigned int>;
		using uint4            = vector4<unsigned int>;
		using long2            = vector2<long>;
		using long3            = vector3<long>;
		using long4            = vector4<long>;
		using ulong2           = vector2<unsigned long>;
		using ulong3           = vector3<unsigned long>;
		using ulong4           = vector4<unsigned long>;
		using llong2           = vector2<long long>;
		using llong3           = vector3<long long>;
		using llong4           = vector4<long long>;
		using ullong2          = vector2<unsigned long long>;
		using ullong3          = vector3<unsigned long long>;
		using ullong4          = vector4<unsigned long long>;
		using float2           = vector2<float>;
		using float3           = vector3<float>;
		using float4           = vector4<float>;
		using double2          = vector2<double>;
		using double3          = vector3<double>;
		using double4          = vector4<double>;
		using ldouble2         = vector2<long double>;
		using ldouble3         = vector3<long double>;
		using ldouble4         = vector4<long double>;
		
		using packed_bool2     = vector2<bool,               vector_options{}.packed(true)>;
		using packed_bool3     = vector3<bool,               vector_options{}.packed(true)>;
		using packed_bool4     = vector4<bool,               vector_options{}.packed(true)>;
		using packed_char2     = vector2<char,               vector_options{}.packed(true)>;
		using packed_char3     = vector3<char,               vector_options{}.packed(true)>;
		using packed_char4     = vector4<char,               vector_options{}.packed(true)>;
		using packed_uchar2    = vector2<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar3    = vector3<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar4    = vector4<unsigned char,      vector_options{}.packed(true)>;
		using packed_short2    = vector2<short,              vector_options{}.packed(true)>;
		using packed_short3    = vector3<short,              vector_options{}.packed(true)>;
		using packed_short4    = vector4<short,              vector_options{}.packed(true)>;
		using packed_ushort2   = vector2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3   = vector3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4   = vector4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2      = vector2<int,                vector_options{}.packed(true)>;
		using packed_int3      = vector3<int,                vector_options{}.packed(true)>;
		using packed_int4      = vector4<int,                vector_options{}.packed(true)>;
		using packed_uint2     = vector2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3     = vector3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4     = vector4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2     = vector2<long,               vector_options{}.packed(true)>;
		using packed_long3     = vector3<long,               vector_options{}.packed(true)>;
		using packed_long4     = vector4<long,               vector_options{}.packed(true)>;
		using packed_ulong2    = vector2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3    = vector3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4    = vector4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2    = vector2<long long,          vector_options{}.packed(true)>;
		using packed_llong3    = vector3<long long,          vector_options{}.packed(true)>;
		using packed_llong4    = vector4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2   = vector2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3   = vector3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4   = vector4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2    = vector2<float,              vector_options{}.packed(true)>;
		using packed_float3    = vector3<float,              vector_options{}.packed(true)>;
		using packed_float4    = vector4<float,              vector_options{}.packed(true)>;
		using packed_double2   = vector2<double,             vector_options{}.packed(true)>;
		using packed_double3   = vector3<double,             vector_options{}.packed(true)>;
		using packed_double4   = vector4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2  = vector2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3  = vector3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4  = vector4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2    = vector2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3    = vector3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4    = vector4<bool,               vector_options{}.packed(false)>;
		using aligned_char2    = vector2<char,               vector_options{}.packed(false)>;
		using aligned_char3    = vector3<char,               vector_options{}.packed(false)>;
		using aligned_char4    = vector4<char,               vector_options{}.packed(false)>;
		using aligned_uchar2   = vector2<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar3   = vector3<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar4   = vector4<unsigned char,      vector_options{}.packed(false)>;
		using aligned_short2   = vector2<short,              vector_options{}.packed(false)>;
		using aligned_short3   = vector3<short,              vector_options{}.packed(false)>;
		using aligned_short4   = vector4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2  = vector2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3  = vector3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4  = vector4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2     = vector2<int,                vector_options{}.packed(false)>;
		using aligned_int3     = vector3<int,                vector_options{}.packed(false)>;
		using aligned_int4     = vector4<int,                vector_options{}.packed(false)>;
		using aligned_uint2    = vector2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3    = vector3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4    = vector4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2    = vector2<long,               vector_options{}.packed(false)>;
		using aligned_long3    = vector3<long,               vector_options{}.packed(false)>;
		using aligned_long4    = vector4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2   = vector2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3   = vector3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4   = vector4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2   = vector2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3   = vector3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4   = vector4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2  = vector2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3  = vector3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4  = vector4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2   = vector2<float,              vector_options{}.packed(false)>;
		using aligned_float3   = vector3<float,              vector_options{}.packed(false)>;
		using aligned_float4   = vector4<float,              vector_options{}.packed(false)>;
		using aligned_double2  = vector2<double,             vector_options{}.packed(false)>;
		using aligned_double3  = vector3<double,             vector_options{}.packed(false)>;
		using aligned_double4  = vector4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2 = vector2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3 = vector3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4 = vector4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_VECTOR_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_VECTOR_TYPEDEFS__
	
	/// MARK: - Matrix
#ifdef __MTL_DECLARE_MATRIX_TYPEDEFS__
#ifndef __MTL_MATRIX_TYPEDEFS_INCLUDED__
#define __MTL_MATRIX_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using matrix2x2 = matrix<T, 2, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x3 = matrix<T, 2, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x4 = matrix<T, 2, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x2 = matrix<T, 3, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x3 = matrix<T, 3, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x4 = matrix<T, 3, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x2 = matrix<T, 4, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x3 = matrix<T, 4, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x4 = matrix<T, 4, 4, O>;
	
	inline namespace short_types {
	
		using bool2x2            = matrix2x2<bool,               vector_options{}>;
		using bool2x3            = matrix2x3<bool,               vector_options{}>;
		using bool2x4            = matrix2x4<bool,               vector_options{}>;
		using bool3x2            = matrix3x2<bool,               vector_options{}>;
		using bool3x3            = matrix3x3<bool,               vector_options{}>;
		using bool3x4            = matrix3x4<bool,               vector_options{}>;
		using bool4x2            = matrix4x2<bool,               vector_options{}>;
		using bool4x3            = matrix4x3<bool,               vector_options{}>;
		using bool4x4            = matrix4x4<bool,               vector_options{}>;
		using short2x2           = matrix2x2<short,              vector_options{}>;
		using short2x3           = matrix2x3<short,              vector_options{}>;
		using short2x4           = matrix2x4<short,              vector_options{}>;
		using short3x2           = matrix3x2<short,              vector_options{}>;
		using short3x3           = matrix3x3<short,              vector_options{}>;
		using short3x4           = matrix3x4<short,              vector_options{}>;
		using short4x2           = matrix4x2<short,              vector_options{}>;
		using short4x3           = matrix4x3<short,              vector_options{}>;
		using short4x4           = matrix4x4<short,              vector_options{}>;
		using ushort2x2          = matrix2x2<unsigned short,     vector_options{}>;
		using ushort2x3          = matrix2x3<unsigned short,     vector_options{}>;
		using ushort2x4          = matrix2x4<unsigned short,     vector_options{}>;
		using ushort3x2          = matrix3x2<unsigned short,     vector_options{}>;
		using ushort3x3          = matrix3x3<unsigned short,     vector_options{}>;
		using ushort3x4          = matrix3x4<unsigned short,     vector_options{}>;
		using ushort4x2          = matrix4x2<unsigned short,     vector_options{}>;
		using ushort4x3          = matrix4x3<unsigned short,     vector_options{}>;
		using ushort4x4          = matrix4x4<unsigned short,     vector_options{}>;
		using int2x2             = matrix2x2<int,                vector_options{}>;
		using int2x3             = matrix2x3<int,                vector_options{}>;
		using int2x4             = matrix2x4<int,                vector_options{}>;
		using int3x2             = matrix3x2<int,                vector_options{}>;
		using int3x3             = matrix3x3<int,                vector_options{}>;
		using int3x4             = matrix3x4<int,                vector_options{}>;
		using int4x2             = matrix4x2<int,                vector_options{}>;
		using int4x3             = matrix4x3<int,                vector_options{}>;
		using int4x4             = matrix4x4<int,                vector_options{}>;
		using uint2x2            = matrix2x2<unsigned int,       vector_options{}>;
		using uint2x3            = matrix2x3<unsigned int,       vector_options{}>;
		using uint2x4            = matrix2x4<unsigned int,       vector_options{}>;
		using uint3x2            = matrix3x2<unsigned int,       vector_options{}>;
		using uint3x3            = matrix3x3<unsigned int,       vector_options{}>;
		using uint3x4            = matrix3x4<unsigned int,       vector_options{}>;
		using uint4x2            = matrix4x2<unsigned int,       vector_options{}>;
		using uint4x3            = matrix4x3<unsigned int,       vector_options{}>;
		using uint4x4            = matrix4x4<unsigned int,       vector_options{}>;
		using long2x2            = matrix2x2<long,               vector_options{}>;
		using long2x3            = matrix2x3<long,               vector_options{}>;
		using long2x4            = matrix2x4<long,               vector_options{}>;
		using long3x2            = matrix3x2<long,               vector_options{}>;
		using long3x3            = matrix3x3<long,               vector_options{}>;
		using long3x4            = matrix3x4<long,               vector_options{}>;
		using long4x2            = matrix4x2<long,               vector_options{}>;
		using long4x3            = matrix4x3<long,               vector_options{}>;
		using long4x4            = matrix4x4<long,               vector_options{}>;
		using ulong2x2           = matrix2x2<unsigned long,      vector_options{}>;
		using ulong2x3           = matrix2x3<unsigned long,      vector_options{}>;
		using ulong2x4           = matrix2x4<unsigned long,      vector_options{}>;
		using ulong3x2           = matrix3x2<unsigned long,      vector_options{}>;
		using ulong3x3           = matrix3x3<unsigned long,      vector_options{}>;
		using ulong3x4           = matrix3x4<unsigned long,      vector_options{}>;
		using ulong4x2           = matrix4x2<unsigned long,      vector_options{}>;
		using ulong4x3           = matrix4x3<unsigned long,      vector_options{}>;
		using ulong4x4           = matrix4x4<unsigned long,      vector_options{}>;
		using llong2x2           = matrix2x2<long long,          vector_options{}>;
		using llong2x3           = matrix2x3<long long,          vector_options{}>;
		using llong2x4           = matrix2x4<long long,          vector_options{}>;
		using llong3x2           = matrix3x2<long long,          vector_options{}>;
		using llong3x3           = matrix3x3<long long,          vector_options{}>;
		using llong3x4           = matrix3x4<long long,          vector_options{}>;
		using llong4x2           = matrix4x2<long long,          vector_options{}>;
		using llong4x3           = matrix4x3<long long,          vector_options{}>;
		using llong4x4           = matrix4x4<long long,          vector_options{}>;
		using ullong2x2          = matrix2x2<unsigned long long, vector_options{}>;
		using ullong2x3          = matrix2x3<unsigned long long, vector_options{}>;
		using ullong2x4          = matrix2x4<unsigned long long, vector_options{}>;
		using ullong3x2          = matrix3x2<unsigned long long, vector_options{}>;
		using ullong3x3          = matrix3x3<unsigned long long, vector_options{}>;
		using ullong3x4          = matrix3x4<unsigned long long, vector_options{}>;
		using ullong4x2          = matrix4x2<unsigned long long, vector_options{}>;
		using ullong4x3          = matrix4x3<unsigned long long, vector_options{}>;
		using ullong4x4          = matrix4x4<unsigned long long, vector_options{}>;
		using float2x2           = matrix2x2<float,              vector_options{}>;
		using float2x3           = matrix2x3<float,              vector_options{}>;
		using float2x4           = matrix2x4<float,              vector_options{}>;
		using float3x2           = matrix3x2<float,              vector_options{}>;
		using float3x3           = matrix3x3<float,              vector_options{}>;
		using float3x4           = matrix3x4<float,              vector_options{}>;
		using float4x2           = matrix4x2<float,              vector_options{}>;
		using float4x3           = matrix4x3<float,              vector_options{}>;
		using float4x4           = matrix4x4<float,              vector_options{}>;
		using double2x2          = matrix2x2<double,             vector_options{}>;
		using double2x3          = matrix2x3<double,             vector_options{}>;
		using double2x4          = matrix2x4<double,             vector_options{}>;
		using double3x2          = matrix3x2<double,             vector_options{}>;
		using double3x3          = matrix3x3<double,             vector_options{}>;
		using double3x4          = matrix3x4<double,             vector_options{}>;
		using double4x2          = matrix4x2<double,             vector_options{}>;
		using double4x3          = matrix4x3<double,             vector_options{}>;
		using double4x4          = matrix4x4<double,             vector_options{}>;
		using ldouble2x2         = matrix2x2<long double,        vector_options{}>;
		using ldouble2x3         = matrix2x3<long double,        vector_options{}>;
		using ldouble2x4         = matrix2x4<long double,        vector_options{}>;
		using ldouble3x2         = matrix3x2<long double,        vector_options{}>;
		using ldouble3x3         = matrix3x3<long double,        vector_options{}>;
		using ldouble3x4         = matrix3x4<long double,        vector_options{}>;
		using ldouble4x2         = matrix4x2<long double,        vector_options{}>;
		using ldouble4x3         = matrix4x3<long double,        vector_options{}>;
		using ldouble4x4         = matrix4x4<long double,        vector_options{}>;
	 
		using packed_bool2x2     = matrix2x2<bool,               vector_options{}.packed(true)>;
		using packed_bool2x3     = matrix2x3<bool,               vector_options{}.packed(true)>;
		using packed_bool2x4     = matrix2x4<bool,               vector_options{}.packed(true)>;
		using packed_bool3x2     = matrix3x2<bool,               vector_options{}.packed(true)>;
		using packed_bool3x3     = matrix3x3<bool,               vector_options{}.packed(true)>;
		using packed_bool3x4     = matrix3x4<bool,               vector_options{}.packed(true)>;
		using packed_bool4x2     = matrix4x2<bool,               vector_options{}.packed(true)>;
		using packed_bool4x3     = matrix4x3<bool,               vector_options{}.packed(true)>;
		using packed_bool4x4     = matrix4x4<bool,               vector_options{}.packed(true)>;
		using packed_short2x2    = matrix2x2<short,              vector_options{}.packed(true)>;
		using packed_short2x3    = matrix2x3<short,              vector_options{}.packed(true)>;
		using packed_short2x4    = matrix2x4<short,              vector_options{}.packed(true)>;
		using packed_short3x2    = matrix3x2<short,              vector_options{}.packed(true)>;
		using packed_short3x3    = matrix3x3<short,              vector_options{}.packed(true)>;
		using packed_short3x4    = matrix3x4<short,              vector_options{}.packed(true)>;
		using packed_short4x2    = matrix4x2<short,              vector_options{}.packed(true)>;
		using packed_short4x3    = matrix4x3<short,              vector_options{}.packed(true)>;
		using packed_short4x4    = matrix4x4<short,              vector_options{}.packed(true)>;
		using packed_ushort2x2   = matrix2x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x3   = matrix2x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x4   = matrix2x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x2   = matrix3x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x3   = matrix3x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x4   = matrix3x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x2   = matrix4x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x3   = matrix4x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x4   = matrix4x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2x2      = matrix2x2<int,                vector_options{}.packed(true)>;
		using packed_int2x3      = matrix2x3<int,                vector_options{}.packed(true)>;
		using packed_int2x4      = matrix2x4<int,                vector_options{}.packed(true)>;
		using packed_int3x2      = matrix3x2<int,                vector_options{}.packed(true)>;
		using packed_int3x3      = matrix3x3<int,                vector_options{}.packed(true)>;
		using packed_int3x4      = matrix3x4<int,                vector_options{}.packed(true)>;
		using packed_int4x2      = matrix4x2<int,                vector_options{}.packed(true)>;
		using packed_int4x3      = matrix4x3<int,                vector_options{}.packed(true)>;
		using packed_int4x4      = matrix4x4<int,                vector_options{}.packed(true)>;
		using packed_uint2x2     = matrix2x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x3     = matrix2x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x4     = matrix2x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x2     = matrix3x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x3     = matrix3x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x4     = matrix3x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x2     = matrix4x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x3     = matrix4x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x4     = matrix4x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2x2     = matrix2x2<long,               vector_options{}.packed(true)>;
		using packed_long2x3     = matrix2x3<long,               vector_options{}.packed(true)>;
		using packed_long2x4     = matrix2x4<long,               vector_options{}.packed(true)>;
		using packed_long3x2     = matrix3x2<long,               vector_options{}.packed(true)>;
		using packed_long3x3     = matrix3x3<long,               vector_options{}.packed(true)>;
		using packed_long3x4     = matrix3x4<long,               vector_options{}.packed(true)>;
		using packed_long4x2     = matrix4x2<long,               vector_options{}.packed(true)>;
		using packed_long4x3     = matrix4x3<long,               vector_options{}.packed(true)>;
		using packed_long4x4     = matrix4x4<long,               vector_options{}.packed(true)>;
		using packed_ulong2x2    = matrix2x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x3    = matrix2x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x4    = matrix2x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x2    = matrix3x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x3    = matrix3x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x4    = matrix3x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x2    = matrix4x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x3    = matrix4x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x4    = matrix4x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2x2    = matrix2x2<long long,          vector_options{}.packed(true)>;
		using packed_llong2x3    = matrix2x3<long long,          vector_options{}.packed(true)>;
		using packed_llong2x4    = matrix2x4<long long,          vector_options{}.packed(true)>;
		using packed_llong3x2    = matrix3x2<long long,          vector_options{}.packed(true)>;
		using packed_llong3x3    = matrix3x3<long long,          vector_options{}.packed(true)>;
		using packed_llong3x4    = matrix3x4<long long,          vector_options{}.packed(true)>;
		using packed_llong4x2    = matrix4x2<long long,          vector_options{}.packed(true)>;
		using packed_llong4x3    = matrix4x3<long long,          vector_options{}.packed(true)>;
		using packed_llong4x4    = matrix4x4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2x2   = matrix2x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x3   = matrix2x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x4   = matrix2x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x2   = matrix3x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x3   = matrix3x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x4   = matrix3x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x2   = matrix4x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x3   = matrix4x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x4   = matrix4x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2x2    = matrix2x2<float,              vector_options{}.packed(true)>;
		using packed_float2x3    = matrix2x3<float,              vector_options{}.packed(true)>;
		using packed_float2x4    = matrix2x4<float,              vector_options{}.packed(true)>;
		using packed_float3x2    = matrix3x2<float,              vector_options{}.packed(true)>;
		using packed_float3x3    = matrix3x3<float,              vector_options{}.packed(true)>;
		using packed_float3x4    = matrix3x4<float,              vector_options{}.packed(true)>;
		using packed_float4x2    = matrix4x2<float,              vector_options{}.packed(true)>;
		using packed_float4x3    = matrix4x3<float,              vector_options{}.packed(true)>;
		using packed_float4x4    = matrix4x4<float,              vector_options{}.packed(true)>;
		using packed_double2x2   = matrix2x2<double,             vector_options{}.packed(true)>;
		using packed_double2x3   = matrix2x3<double,             vector_options{}.packed(true)>;
		using packed_double2x4   = matrix2x4<double,             vector_options{}.packed(true)>;
		using packed_double3x2   = matrix3x2<double,             vector_options{}.packed(true)>;
		using packed_double3x3   = matrix3x3<double,             vector_options{}.packed(true)>;
		using packed_double3x4   = matrix3x4<double,             vector_options{}.packed(true)>;
		using packed_double4x2   = matrix4x2<double,             vector_options{}.packed(true)>;
		using packed_double4x3   = matrix4x3<double,             vector_options{}.packed(true)>;
		using packed_double4x4   = matrix4x4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2x2  = matrix2x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x3  = matrix2x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x4  = matrix2x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x2  = matrix3x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x3  = matrix3x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x4  = matrix3x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x2  = matrix4x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x3  = matrix4x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x4  = matrix4x4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2x2    = matrix2x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x3    = matrix2x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x4    = matrix2x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x2    = matrix3x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x3    = matrix3x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x4    = matrix3x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x2    = matrix4x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x3    = matrix4x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x4    = matrix4x4<bool,               vector_options{}.packed(false)>;
		using aligned_short2x2   = matrix2x2<short,              vector_options{}.packed(false)>;
		using aligned_short2x3   = matrix2x3<short,              vector_options{}.packed(false)>;
		using aligned_short2x4   = matrix2x4<short,              vector_options{}.packed(false)>;
		using aligned_short3x2   = matrix3x2<short,              vector_options{}.packed(false)>;
		using aligned_short3x3   = matrix3x3<short,              vector_options{}.packed(false)>;
		using aligned_short3x4   = matrix3x4<short,              vector_options{}.packed(false)>;
		using aligned_short4x2   = matrix4x2<short,              vector_options{}.packed(false)>;
		using aligned_short4x3   = matrix4x3<short,              vector_options{}.packed(false)>;
		using aligned_short4x4   = matrix4x4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2x2  = matrix2x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x3  = matrix2x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x4  = matrix2x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x2  = matrix3x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x3  = matrix3x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x4  = matrix3x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x2  = matrix4x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x3  = matrix4x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x4  = matrix4x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2x2     = matrix2x2<int,                vector_options{}.packed(false)>;
		using aligned_int2x3     = matrix2x3<int,                vector_options{}.packed(false)>;
		using aligned_int2x4     = matrix2x4<int,                vector_options{}.packed(false)>;
		using aligned_int3x2     = matrix3x2<int,                vector_options{}.packed(false)>;
		using aligned_int3x3     = matrix3x3<int,                vector_options{}.packed(false)>;
		using aligned_int3x4     = matrix3x4<int,                vector_options{}.packed(false)>;
		using aligned_int4x2     = matrix4x2<int,                vector_options{}.packed(false)>;
		using aligned_int4x3     = matrix4x3<int,                vector_options{}.packed(false)>;
		using aligned_int4x4     = matrix4x4<int,                vector_options{}.packed(false)>;
		using aligned_uint2x2    = matrix2x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x3    = matrix2x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x4    = matrix2x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x2    = matrix3x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x3    = matrix3x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x4    = matrix3x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x2    = matrix4x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x3    = matrix4x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x4    = matrix4x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2x2    = matrix2x2<long,               vector_options{}.packed(false)>;
		using aligned_long2x3    = matrix2x3<long,               vector_options{}.packed(false)>;
		using aligned_long2x4    = matrix2x4<long,               vector_options{}.packed(false)>;
		using aligned_long3x2    = matrix3x2<long,               vector_options{}.packed(false)>;
		using aligned_long3x3    = matrix3x3<long,               vector_options{}.packed(false)>;
		using aligned_long3x4    = matrix3x4<long,               vector_options{}.packed(false)>;
		using aligned_long4x2    = matrix4x2<long,               vector_options{}.packed(false)>;
		using aligned_long4x3    = matrix4x3<long,               vector_options{}.packed(false)>;
		using aligned_long4x4    = matrix4x4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2x2   = matrix2x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x3   = matrix2x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x4   = matrix2x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x2   = matrix3x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x3   = matrix3x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x4   = matrix3x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x2   = matrix4x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x3   = matrix4x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x4   = matrix4x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2x2   = matrix2x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x3   = matrix2x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x4   = matrix2x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x2   = matrix3x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x3   = matrix3x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x4   = matrix3x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x2   = matrix4x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x3   = matrix4x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x4   = matrix4x4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2x2  = matrix2x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x3  = matrix2x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x4  = matrix2x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x2  = matrix3x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x3  = matrix3x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x4  = matrix3x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x2  = matrix4x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x3  = matrix4x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x4  = matrix4x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2x2   = matrix2x2<float,              vector_options{}.packed(false)>;
		using aligned_float2x3   = matrix2x3<float,              vector_options{}.packed(false)>;
		using aligned_float2x4   = matrix2x4<float,              vector_options{}.packed(false)>;
		using aligned_float3x2   = matrix3x2<float,              vector_options{}.packed(false)>;
		using aligned_float3x3   = matrix3x3<float,              vector_options{}.packed(false)>;
		using aligned_float3x4   = matrix3x4<float,              vector_options{}.packed(false)>;
		using aligned_float4x2   = matrix4x2<float,              vector_options{}.packed(false)>;
		using aligned_float4x3   = matrix4x3<float,              vector_options{}.packed(false)>;
		using aligned_float4x4   = matrix4x4<float,              vector_options{}.packed(false)>;
		using aligned_double2x2  = matrix2x2<double,             vector_options{}.packed(false)>;
		using aligned_double2x3  = matrix2x3<double,             vector_options{}.packed(false)>;
		using aligned_double2x4  = matrix2x4<double,             vector_options{}.packed(false)>;
		using aligned_double3x2  = matrix3x2<double,             vector_options{}.packed(false)>;
		using aligned_double3x3  = matrix3x3<double,             vector_options{}.packed(false)>;
		using aligned_double3x4  = matrix3x4<double,             vector_options{}.packed(false)>;
		using aligned_double4x2  = matrix4x2<double,             vector_options{}.packed(false)>;
		using aligned_double4x3  = matrix4x3<double,             vector_options{}.packed(false)>;
		using aligned_double4x4  = matrix4x4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2x2 = matrix2x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x3 = matrix2x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x4 = matrix2x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x2 = matrix3x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x3 = matrix3x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x4 = matrix3x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x2 = matrix4x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x3 = matrix4x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x4 = matrix4x4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_MATRIX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_MATRIX_TYPEDEFS__
	
}

#pragma once

/// __arithmetic.hpp

#ifndef __MTL_ARITHMETIC_HPP_INCLUDED__
#define __MTL_ARITHMETIC_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_


#pragma once

/// __intrin.hpp

#ifndef __MTL_INTRIN_HPP_INCLUDED__
#define __MTL_INTRIN_HPP_INCLUDED__

#include <immintrin.h>
#include <cstddef>



namespace mtl {
	
	template <typename T, std::size_t Size, bool Packed>
	struct __simd_type {
		using type = T[Size];
		static T get(type const& array, std::size_t index) { return array[index]; }
		
		static void mul(type& a, type const& b) {
			for (int i = 0; i < Size; ++i) {
				a[i] *= b[i];
			}
		}
		static void div(type& a, type const& b) {
			for (int i = 0; i < Size; ++i) {
				a[i] /= b[i];
			}
		}
	};
	
	template <typename T, std::size_t Size, bool Packed>
	using __simd_type_t = typename __simd_type<T, Size, Packed>::type;
	
	template <> struct __simd_type<float, 4, false> {
		using type = __m128;
		
		static float get(type const& array, std::size_t index) {
#if defined(_MSC_VER)
			return array.m128_f32[index];
#else
			return array[index];
#endif
		}
		
		static void mul(type& a, type const& b) {
			a = _mm_mul_ps(a, b);
		}
		static void div(type& a, type const& b) {
			a = _mm_div_ps(a, b);
		}
	};
	
#if MTL_AVX
	template <> struct __simd_type<double, 4, false> {
		using type = __m256d;
		
		static double get(type const& array, std::size_t index) {
#if defined(_MSC_VER)
			return array.m256d_f64[index];
#else
			return array[index];
#endif
		}
		
		static void mul(type& a, type const& b) {
			a = _mm256_mul_pd(a, b);
		}
		static void div(type& a, type const& b) {
			a = _mm256_div_pd(a, b);
		}
	};
	
#endif
	
}

#endif // __MTL_INTRIN_HPP_INCLUDED__


namespace _VMTL {
	
	template <typename VectorType, typename T, vector_options O>
	VectorType __mtl_load(vector<T, VectorType::size(), O> const& x) {
		return type_cast<typename VectorType::value_type>(x);
	}
	
	template <typename VectorType>
	using __mtl_get_simd_type = __simd_type<typename VectorType::value_type, VectorType::size(), VectorType::options().packed()>;
	
	/// MARK: - Vector Arithmetic
	///
	///
	///
	/// MARK: Plus
	/// Unary Plus(Vector)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O> operator+(vector<T, Size, O> const& v) {
		return v;
	}
	
	/// Add Vector to Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator+(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_plus);
	}
	
	/// Add Scalar to Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator+(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto _a) {
			return _a + b;
		});
	}
	
	/// Add Vector to Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator+(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a + b; });
	}

	/// MARK: Minus
	/// Negate Vector
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O> operator-(vector<T, Size, O> const& v) {
		return map(v, _VMTL::__mtl_minus);
	}
	
	/// Subract Vector from Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator-(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_minus);
	}

	/// Subract Scalar from Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator-(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a - b; });
	}

	/// Subract Vector from Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator-(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a - b; });
	}

	/// MARK: Multiply
	/// Multiply Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator*(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		if (std::is_constant_evaluated()) {
			return map(a, b, _VMTL::__mtl_multiplies);
		}
		
		using result_type = vector<__mtl_promote(T, U), Size, combine(O, P)>;
		using simd_type = __mtl_get_simd_type<result_type>;
		
		result_type result = __mtl_load<result_type>(a);
		simd_type::mul(result.__vec, __mtl_load<result_type>(b).__vec);
		
		return result;
	}

	/// Multiply Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator*(vector<T, Size, O> const& a,
			  U const& b)
	{
		using result_type = vector<__mtl_promote(T, U), Size, O>;
		return a * result_type(b);
	}

	/// Multiply Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator*(T const& a,
			  vector<U, Size, O> const& b)
	{
		using result_type = vector<__mtl_promote(T, U), Size, O>;
		return result_type(a) * b;
	}
	
	/// MARK: Divide
	/// Divide Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator/(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b)
	{
		if (std::is_constant_evaluated()) {
			return map(a, b, _VMTL::__mtl_divides);
		}
		
		using result_type = vector<__mtl_promote(T, U), Size, combine(O, P)>;
		using simd_type = __mtl_get_simd_type<result_type>;
		
		result_type result = __mtl_load<result_type>(a);
		simd_type::div(result.__vec, __mtl_load<result_type>(b).__vec);
		
		return result;
	}

	/// Divide Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator/(vector<T, Size, O> const& a,
			  U const& b)
	{
		using result_type = vector<__mtl_promote(T, U), Size, O>;
		return a / result_type(b);
	}

	/// Divide Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator/(T const& a,
			  vector<U, Size, O> const& b)
	{
		using result_type = vector<__mtl_promote(T, U), Size, O>;
		return result_type(a) / b;
	}

	/// MARK: Modulo
	/// Modulo divide Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	requires requires(T&& t, U&& u) { t % u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator%(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_modulo);
	}

	/// Modulo divide Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t % u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator%(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a % b; });
	}

	/// Modulo divide Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t % u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator%(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a % b; });
	}
	
	/// MARK: Bitwise And
	/// Bitwise and Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	requires requires(T&& t, U&& u) { t & u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator&(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_and);
	}

	/// Bitwise and Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t & u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator&(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a & b; });
	}

	/// Bitwise and Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t & u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator&(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a & b; });
	}
	
	/// MARK: Bitwise Or
	/// Bitwise or Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	requires requires(T&& t, U&& u) { t | u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator|(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_or);
	}

	/// Bitwise and Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t | u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator|(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a | b; });
	}

	/// Bitwise and Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t | u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator|(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a | b; });
	}
	
	/// MARK: Bitwise Xor
	/// Bitwise xor Vector by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	requires requires(T&& t, U&& u) { t ^ u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, combine(O, P)>
	operator^(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, _VMTL::__mtl_xor);
	}

	/// Bitwise and Vector by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t ^ u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator^(vector<T, Size, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a ^ b; });
	}

	/// Bitwise and Scalar by Vector (element-wise)
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { t ^ u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), Size, O>
	operator^(T const& a,
			  vector<U, Size, O> const& b) {
		return map(b, [&a](auto b) { return a ^ b; });
	}
	
	/// MARK: Unary Bitwise Not
	template <typename T, std::size_t Size, vector_options O>
	requires requires(T&& t) { ~t; }
	__mtl_always_inline __mtl_interface_export
	constexpr auto operator~(vector<T, Size, O> const& a) {
		return map(a, __mtl_not);
	}
	
	/// MARK: Unary Logical Not
	template <typename T, std::size_t Size, vector_options O>
	requires requires(T&& t) { !t; }
	__mtl_always_inline __mtl_interface_export
	constexpr auto operator!(vector<T, Size, O> const& a) {
		return map(a, __mtl_logical_not);
	}
	
	/// Bitshift Vector by Vector (element-wise)
	template <std::integral T, std::integral U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator<<(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, [](T t, U u) { return t << u; });
	}
	
	template <std::integral T, std::integral U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator>>(vector<T, Size, O> const& a,
			  vector<U, Size, P> const& b) {
		return map(a, b, [](T t, U u) { return t >> u; });
	}
	
	/// Bitshift Vector by Scalar (element-wise)
	template <std::integral T, std::integral U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator<<(vector<T, Size, O> const& a, U b) {
		return a.map([b](T t) { return t << b; });
	}
	
	template <std::integral T, std::integral U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator>>(vector<T, Size, O> const& a, U b) {
		return a.map([b](T t) { return t >> b; });
	}
	
	/// Bitshift Scalar by Vector (element-wise)
	template <std::integral T, std::integral U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator<<(T a, vector<U, Size, O> const& b) {
		return b.map([a](U u) { return a << u; });
	}
	
	template <std::integral T, std::integral U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O>
	operator>>(T a, vector<U, Size, O> const& b) {
		return b.map([a](U u) { return a >> u; });
	}
	
	/// MARK: - Matrix Arithmetic
	///
	///
	///
	/// MARK: Plus
	/// Unary Plus(Matrix)
	template <scalar T, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<T, Rows, Columns, O> operator+(matrix<T, Rows, Columns, O> const& v) {
		return v;
	}
	
	/// Add Matrix to Matrix
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, combine(O, P)>
	operator+(matrix<T, Rows, Columns, O> const& a,
			  matrix<U, Rows, Columns, P> const& b) {
		return map(a, b, _VMTL::__mtl_plus);
	}
	
	/// MARK: Minus
	/// Negate Matrix
	template <scalar T, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<T, Rows, Columns, O> operator-(matrix<T, Rows, Columns, O> const& v) {
		return map(v, _VMTL::__mtl_minus);
	}
	
	/// Subtract Matrix from Matrix
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, combine(O, P)>
	operator-(matrix<T, Rows, Columns, O> const& a,
			  matrix<U, Rows, Columns, P> const& b) {
		return map(a, b, _VMTL::__mtl_minus);
	}
	
	/// MARK: Multiply
	/// Multiply Matrix by Scalar
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, O>
	operator*(matrix<T, Rows, Columns, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a * b; });
	}
	
	/// Multiply Scalar by Matrix
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, O>
	operator*(T const& a,
			  matrix<U, Rows, Columns, O> const& b) {
		return map(b, [&a](auto b) { return a * b; });
	}
	
	/// Multiply Matrix by Matrix
	template <scalar T, scalar U,
			  std::size_t RowsA, std::size_t ColumnsA, std::size_t ColumnsB,
			  vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), RowsA, ColumnsB, combine(O, P)>
	operator*(matrix<T, RowsA, ColumnsA, O> const& A,
			  matrix<U, ColumnsA, ColumnsB, P> const& B) {
		return matrix<__mtl_promote(T, U), RowsA, ColumnsB, combine(O, P)>([&](std::size_t i, std::size_t j) {
			return __mtl_with_index_sequence((K, ColumnsA), {
				return ((A.__mtl_at(i, K) * B.__mtl_at(K, j)) + ...);
			});
		});
	}

	/// Multiply Matrix by Vector
	template <scalar T, scalar U, std::size_t RowsA, std::size_t ColumnsA, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), RowsA, combine(O, P)>
	operator*(matrix<T, RowsA, ColumnsA, O> const& A,
			  vector<U, ColumnsA, P> const& v) {
		return vector<__mtl_promote(T, U), RowsA, combine(O, P)>([&](std::size_t i) {
			return __mtl_with_index_sequence((K, ColumnsA), {
				return ((A.__mtl_at(i, K) * v.__mtl_at(K)) + ...);
			});
		});
	}

	/// Multiply Vector by Matrix
	template <scalar T, scalar U, std::size_t ColumnsA, std::size_t ColumnsB, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), ColumnsB, combine(O, P)>
	operator*(vector<T, ColumnsA, O> const& v,
			  matrix<U, ColumnsA, ColumnsB, P> const& A) {
		return vector<__mtl_promote(T, U), ColumnsB, combine(O, P)>([&](std::size_t j) {
			return __mtl_with_index_sequence((K, ColumnsA), {
				return ((v.__mtl_at(K) * A.__mtl_at(K, j)) + ...);
			});
		});
	}
	
	/// MARK: Divide
	/// Divide Matrix by Scalar
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, O>
	operator/(matrix<T, Rows, Columns, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a / b; });
	}

	/// MARK: Modulo
	/// Modulo divide Matrix by Scalar (element-wise)
	template <scalar T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O>
	requires requires(T&& t, U&& u) { t % u; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<__mtl_promote(T, U), Rows, Columns, O>
	operator%(matrix<T, Rows, Columns, O> const& a,
			  U const& b) {
		return map(a, [&b](auto a) { return a % b; });
	}
	
}

#endif // __MTL_ARITHMETIC_HPP_INCLUDED__




#include <functional>
#include <iosfwd>

/// MARK: - Synopsis
/*
 
 namespace mtl {
 
	template <typename T, std::size_t Size, vector_options Options>
	class vector {
		// type information:
		value_type = T
		size()      -> std::size_t    // Size
		data_size() -> std::size_t    // Size including padding
		options()   -> vector_options // Options
 
		// data members:
		T x, y, ...;
		T r, g, ...;
	 
		// contructors:
		vector() = default;
		vector(T value);                 -> // vector{ value, value, ... }
		vector(T value0, T value1, ...); -> // vector{ value, value, ... }
		vector(f: () -> T);              -> // vector{ f(), f(), ... }
		vector(f: (std::size_t) -> T);   -> // vector{ f(0), f(1), ... }
		
		// operator[]:
		operator[](std::size_t) -> T&
		operator[](std::size_t) const -> T const&
	 
		// begin, end:
		begin(), end()               -> T*
		begin() const, end() const   -> T const*
		cbegin() const, cend() const -> T const*
	 
		// data:
		data() -> T*
		data() const -> T const*
 
		// swizzle:
		swizzle(std::size_t i0, ...) -> vector<T, N, Options> // vector{ (*this)[i0], ... }
	 
		// map:
		map(f: (T) -> Any) const -> vector<{ deduced type }, Size, Options>
		 
		// fold:
		fold(f: (T, T) -> T) const -> T
		left_fold(f: (T, T) -> T) const -> T
		right_fold(f: (T, T) -> T) const -> T
	 
	 
		/// statics
		// unit:
		unit(std::size_t index, T value = 1) -> vector<T, Size, Options> // vector{ 0..., value [at position 'index'], 0... }
	};
	 
	operator==(vector, vector) -> bool
	map(vector<Ts, Size>..., f: (Ts...) -> fResult) -> vector<fResult, Size>
	fold(vector<T, Size> v, f: (T, T) -> T) -> T       // left_fold(v, f)
	left_fold(vector<T, Size> v, f: (T, T) -> T) -> T  // ...f(f(f(v[0], v[1]), v[2]),  ...)
	right_fold(vector<T, Size> v, f: (T, T) -> T) -> T // f(...f(..., f(v[N-2], v[N-1])))

 }
 
 */

namespace _VMTL {

	/// MARK: Map
	template <typename... T, std::size_t S, vector_options... O, std::invocable<T...> F>
	__mtl_mathfunction __mtl_always_inline
	constexpr auto __map_impl(F&& f, vector<T, S, O> const&... v) {
		using U = std::invoke_result_t<F, T...>;
		if constexpr (std::same_as<U, void>) {
			for (std::size_t i = 0; i < S; ++i) {
				std::invoke(__mtl_forward(f), v.__mtl_vec_at(i)...);
			}
		}
		else {
			constexpr auto P = combine(O...);
			return vector<U, S, P>([&](std::size_t i) { return std::invoke(__mtl_forward(f), v.__mtl_vec_at(i)...); });
		}
	}
	
	template <typename T0, std::size_t S, vector_options O0, std::invocable<T0> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), v0);
	}
	template <typename T0, typename T1, std::size_t S,
			  vector_options O0, vector_options O1,
			  std::invocable<T0, T1> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   vector<T1, S, O1> const& v1,
					   F&& f)
	{
		return __map_impl(__mtl_forward(f), v0, v1);
	}
	template <typename T0, typename T1, typename T2, std::size_t S,
			  vector_options O0, vector_options O1, vector_options O2,
			  std::invocable<T0, T1, T2> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   vector<T1, S, O1> const& v1,
					   vector<T2, S, O2> const& v2,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), v0, v1, v2);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, std::size_t S,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3,
			  std::invocable<T0, T1, T2, T3> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   vector<T1, S, O1> const& v1,
					   vector<T2, S, O2> const& v2,
					   vector<T3, S, O3> const& v3,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), v0, v1, v2, v3);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, std::size_t S,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3, vector_options O4,
			  std::invocable<T0, T1, T2, T3, T4> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   vector<T1, S, O1> const& v1,
					   vector<T2, S, O2> const& v2,
					   vector<T3, S, O3> const& v3,
					   vector<T4, S, O4> const& v4,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), v0, v1, v2, v3, v4);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, std::size_t S,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3, vector_options O4, vector_options O5,
			  std::invocable<T0, T1, T2, T3, T4, T5> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(vector<T0, S, O0> const& v0,
					   vector<T1, S, O1> const& v1,
					   vector<T2, S, O2> const& v2,
					   vector<T3, S, O3> const& v3,
					   vector<T4, S, O4> const& v4,
					   vector<T5, S, O5> const& v5,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), v0, v1, v2, v3, v4, v5);
	}
	
	/// MARK: Fold
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto __left_fold_impl(auto&& f, auto&& a) {
		return a;
	}
	
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto __left_fold_impl(auto&& f, auto&& a, auto&& b) {
		return std::invoke(f, __mtl_forward(a), __mtl_forward(b));
	}
	
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto __left_fold_impl(auto&& f, auto&& a, auto&& b, auto&&... c) {
		return __left_fold_impl(f, std::invoke(f, __mtl_forward(a), __mtl_forward(b)), __mtl_forward(c)...);
	}
	
	template <typename T, std::size_t S, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T left_fold(vector<T, S, O> const& v, F&& f) {
		return __mtl_with_index_sequence((I, S), {
			return __left_fold_impl(f, v.__mtl_at(I)...);
		});
	}
	
	template <typename T, std::size_t S, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T right_fold(vector<T, S, O> const& v, F&& f) {
		return __mtl_with_index_sequence((I, S), {
			return __left_fold_impl(f, v.__mtl_at(S - 1 - I)...);
		});
	}
	
	template <typename T, std::size_t S, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T fold(vector<T, S, O> const& v, F&& f) {
		return _VMTL::left_fold(v, __mtl_forward(f));
	}
	
	template <typename, std::size_t, vector_options, typename, typename>
	struct __vector_base;

	template <typename T, std::size_t Size, vector_options O>
	struct __vector_data;
	
	/// MARK: - struct __vector_data
	template <typename, std::size_t, vector_options>
	struct __vector_data_;
	
	/// MARK: Size = N
	template <typename T, std::size_t Size, vector_options O>
	struct __vector_data_ {
		__vector_data_() = default;
		constexpr __vector_data_(T const& a, T const& b, T const& c, T const& d, auto const&... r) : __data{ a, b, c, d, r... } {
			if constexpr (std::is_same_v<T, float> && Size == 4 && !O.packed()) {
				if (!std::is_constant_evaluated()) {
					alignas(16) float arr[4]{ a, b, c, d };
					__vec = _mm_load_ps(arr);
				}
			}
#if MTL_AVX
			else if constexpr (std::is_same_v<T, double> && Size == 4 && !O.packed()) {
				if (!std::is_constant_evaluated()) {
					alignas(32) double arr[4]{ a, b, c, d };
					__vec = _mm256_load_pd(arr);
				}
			}
#endif
		}
		
		template <typename, std::size_t, vector_options, typename, typename>
		friend struct __vector_base;
		friend struct __vector_data<T, Size, O>;
		friend struct vector<T, Size, O>;
		friend struct quaternion<T>;
		
	private:
		union {
			T __data[Size];
			__simd_type_t<T, Size, O.packed()> __vec;
			struct { T hue, saturation, value, alpha; };
			struct {
				T x;
				union {
					struct {
						T y;
						union {
							struct { T z, w; };
							_VMTL::vector<T, 2, O.packed(true)> zw;
						};
					};
					_VMTL::vector<T, 3, O.packed(true)> yzw;
					_VMTL::vector<T, 2, O.packed(true)> yz;
				};
			};
			_VMTL::vector<T, 3, O.packed(true)> xyz;
			_VMTL::vector<T, 2, O.packed(true)> xy;
			
			//  for quaternion
			struct {
				T real;
				union {
					_VMTL::vector<T, 3, O.packed(true)> vector;
					_VMTL::vector<T, 3, O.packed(true)> imag;
				};
			};
			
			struct {
				T r;
				union {
					struct {
						T g;
						union {
							struct { T b, a; };
							_VMTL::vector<T, 2, O.packed(true)> ba;
						};
					};
					_VMTL::vector<T, 3, O.packed(true)> gba;
					_VMTL::vector<T, 2, O.packed(true)> gb;
				};
			};
			_VMTL::vector<T, 3, O.packed(true)> rgb;
			_VMTL::vector<T, 2, O.packed(true)> rg;
		};
	};
	
	template <typename T, std::size_t Size, vector_options O>
	struct __vector_data: __vector_data_<T, Size, O> {
		using __mtl_base = __vector_data_<T, Size, O>;
		using __mtl_base::__mtl_base;
		
		using __mtl_base::__data;
		using __mtl_base::__vec;
		
		using __mtl_base::x;
		using __mtl_base::xy;
		using __mtl_base::xyz;
		using __mtl_base::y;
		using __mtl_base::yz;
		using __mtl_base::yzw;
		using __mtl_base::z;
		using __mtl_base::zw;
		using __mtl_base::w;
		
		using __mtl_base::r;
		using __mtl_base::rg;
		using __mtl_base::rgb;
		using __mtl_base::g;
		using __mtl_base::gb;
		using __mtl_base::gba;
		using __mtl_base::b;
		using __mtl_base::ba;
		using __mtl_base::a;
		
		using __mtl_base::hue;
		using __mtl_base::saturation;
		using __mtl_base::value;
		using __mtl_base::alpha;
	};
	
	/// MARK: Size = 3
	template <typename T, vector_options O>
	struct __vector_data_<T, 3, O> {
		__vector_data_() = default;
		constexpr __vector_data_(T const& a, T const& b, T const& c): __vec{ a, b, c } {}
		
		template <typename, std::size_t, vector_options, typename, typename>
		friend struct __vector_base;
		friend struct __vector_data<T, 3, O>;
		friend struct vector<T, 3, O>;
		
	private:
		union {
			T __data[3];
			typename __simd_type<T, 3, O.packed()>::type __vec;
			struct { T hue, saturation, value; };
			struct {
				T x;
				union {
					struct { T y, z; };
					vector<T, 2, O.packed(true)> yz;
				};
			};
			vector<T, 2, O.packed(true)> xy;
			
			struct {
				T r;
				union {
					struct { T g, b; };
					vector<T, 2, O.packed(true)> gb;
				};
			};
			vector<T, 2, O.packed(true)> rg;
		};
	};
	
	template <typename T, vector_options O>
	struct __vector_data<T, 3, O>: __vector_data_<T, 3, O> {
		using __mtl_base = __vector_data_<T, 3, O>;
		using __mtl_base::__mtl_base;
		
		using __mtl_base::__data;
		using __mtl_base::__vec;
		
		using __mtl_base::x;
		using __mtl_base::xy;
		using __mtl_base::y;
		using __mtl_base::yz;
		using __mtl_base::z;
		
		using __mtl_base::r;
		using __mtl_base::rg;
		using __mtl_base::g;
		using __mtl_base::gb;
		using __mtl_base::b;
		
		using __mtl_base::hue;
		using __mtl_base::saturation;
		using __mtl_base::value;
	};
	
	/// MARK: Size = 2
	template <typename T, vector_options O>
	struct __vector_data_<T, 2, O> {
		__vector_data_() = default;
		constexpr __vector_data_(T const& a, T const& b): __vec{ a, b } {}
		
		template <typename, std::size_t, vector_options, typename, typename>
		friend struct __vector_base;
		friend struct __vector_data<T, 2, O>;
		friend struct vector<T, 2, O>;
		friend struct complex<T>;
		
	private:
		union {
			T __data[2];
			typename __simd_type<T, 2, O.packed()>::type __vec;
			struct { T x, y; };
			struct { T r, g; };
			//  for complex
			struct { T real, imag; };
		};
	};
	
	template <typename T, vector_options O>
	struct __vector_data<T, 2, O>: __vector_data_<T, 2, O> {
		using __mtl_base = __vector_data_<T, 2, O>;
		using __mtl_base::__mtl_base;
		
		using __mtl_base::__data;
		using __mtl_base::__vec;
		
		using __mtl_base::x;
		using __mtl_base::y;
		
		using __mtl_base::r;
		using __mtl_base::g;
	};
	
	/// MARK: - struct __vector_base
	constexpr std::size_t __calculate_alignment(std::size_t TAlign, std::size_t S, bool Packed) {
		auto const _s = [&]{
			switch (S) {
				case 0: // fallthrough
				case 1:
					__mtl_debugbreak("invalid");
					return -1;
				case 2:
					return 2;
				case 3:
					return 4;
				case 4:
					return 4;
				case 8:
					return 8;
					
				default:
					return 1;
			}
		}();
		
		return TAlign * (Packed ? 1 : _s);
	}
	
	template <typename T, std::size_t Size, vector_options O,
			  typename = __mtl_make_type_sequence<T, Size>,
			  typename = __mtl_make_index_sequence<Size>>
	struct __vector_base;
	
	template <typename T, std::size_t Size, vector_options O,
			  typename... AllT, std::size_t... I>
	class alignas(__calculate_alignment(alignof(T), Size, O.packed()))
	__vector_base<T, Size, O, __mtl_type_sequence<AllT...>, __mtl_index_sequence<I...>>:
		public __vector_data<T, Size, O>
	{
		using __mtl_base = __vector_data<T, Size, O>;
		
	public:
		// constructors:
		__vector_base() = default;
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(T const& x): __mtl_base{ ((void)I, x)... } {}
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(AllT const&... x): __mtl_base{ x... } {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __vector_base(_VMTL::invocable_r<T> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f)>):
			__mtl_base{ ((void)I, std::invoke(f))... } {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __vector_base(_VMTL::invocable_r<T, std::size_t> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f), std::size_t>):
			__mtl_base{ std::invoke(f, I)... } {}
		
		template <std::convertible_to<T> U, vector_options P>
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(vector<U, Size, P> const& rhs): __mtl_base{ static_cast<T>(rhs.__mtl_at(I))... } {}
		
		/// Construct from foreign tuple type
		template <__tuple_of_types<AllT...> Tuple>
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(Tuple&& t)
			requires (_VMTL::__is_foreign_type<Tuple>::value):
			__mtl_base{ get<I>(t)... } {}
		
		/// Construct from foreign vector type
		template <typename VectorType>
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(VectorType&& v)
			requires (Size == 2) && requires {
				{ v.x } -> std::convertible_to<T>;
				{ v.y } -> std::convertible_to<T>;
			} && (_VMTL::__is_foreign_type<VectorType>::value):
			__mtl_base{ v.x, v.y } {}
		template <typename VectorType>
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(VectorType&& v)
			requires (Size == 3) && requires {
				{ v.x } -> std::convertible_to<T>;
				{ v.y } -> std::convertible_to<T>;
				{ v.z } -> std::convertible_to<T>;
			} && (_VMTL::__is_foreign_type<VectorType>::value):
			__mtl_base{ v.x, v.y, v.z } {}
		template <typename VectorType>
		__mtl_always_inline __mtl_interface_export
		constexpr __vector_base(VectorType&& v)
			requires (Size == 4) && requires {
				{ v.x } -> std::convertible_to<T>;
				{ v.y } -> std::convertible_to<T>;
				{ v.z } -> std::convertible_to<T>;
				{ v.w } -> std::convertible_to<T>;
			} && (_VMTL::__is_foreign_type<VectorType>::value):
			__mtl_base{ v.x, v.y, v.z, v.w } {}
		
		/// Convert to foreign vector type
		template <__foreign_vector_type<T, Size> VectorType>
		constexpr operator VectorType() { return const_cast<__vector_base const&>(*this).operator VectorType(); }
		template <__foreign_vector_type<T, Size> VectorType>
		constexpr operator VectorType() const { return VectorType{ this->__data[I]... }; }
	};

	/// MARK: - struct vector
	template <typename T, std::size_t Size, vector_options O>
	struct vector: public __vector_base<T, Size, O> {
		using __mtl_base = __vector_base<T, Size, O>;
	
		__mtl_always_inline
		constexpr T& __mtl_at(std::size_t i)& {
			__mtl_assert_audit(i < Size);
			return this->__data[i];
		}
		__mtl_always_inline
		constexpr T const& __mtl_at(std::size_t i) const& {
			__mtl_assert_audit(i < Size);
			return this->__data[i];
		}
		__mtl_always_inline
		constexpr T&& __mtl_at(std::size_t i)&& {
			__mtl_assert_audit(i < Size);
			return std::move(this->__data[i]);
		}
		__mtl_always_inline
		constexpr T const&& __mtl_at(std::size_t i) const&& {
			__mtl_assert_audit(i < Size);
			return std::move(this->__data[i]);
		}
		
		__mtl_always_inline
		constexpr T __mtl_vec_at(std::size_t i) const {
			__mtl_assert_audit(i < Size);
			if (std::is_constant_evaluated()) {
				return this->__data[i];
			}
			else {
				return __simd_type<T, Size, O.packed()>::get(this->__vec, i);
			}
		}
		
		/// MARK: Public Interface
		using value_type = T;
		__mtl_pure __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    size()      { return Size; }
		__mtl_pure __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    data_size() { return Size + (Size == 3 && !O.packed()); }
		__mtl_pure __mtl_always_inline __mtl_interface_export
		static constexpr vector_options options()   { return O; }
		
		static constexpr vector<T, Size, O> unit(std::size_t index, T const& value = 1) {
			__mtl_bounds_check(index, 0, Size);
			vector<T, Size, O> result{};
			result.__mtl_at(index) = value;
			return result;
		}
		
		/// Inheriting Constructors from __vector_base:
		using __mtl_base::__mtl_base;
		vector() = default;
		
		/// Some more Constructors
		// vector3(vector2, scalar)
		__mtl_always_inline __mtl_interface_export
		constexpr vector(vector<T, 2, O> const& a, T const& b) requires (Size == 3): vector(a.__mtl_at(0), a.__mtl_at(1), b) {}
		// vector3(scalar, vector2)
		__mtl_always_inline __mtl_interface_export
		constexpr vector(T const& a, vector<T, 2, O> const& b) requires (Size == 3): vector(a, b.__mtl_at(0), b.__mtl_at(1)) {}
		// vector4(vector2, s, s)
		__mtl_always_inline __mtl_interface_export
		constexpr vector(vector<T, 2, O> const& a, T const& b, T const& c) requires (Size == 4): vector(a.__mtl_at(0), a.__mtl_at(1), b, c) {}
		// vector4(scalar, vector2, scalar)
		__mtl_always_inline __mtl_interface_export
		constexpr vector(T const& a, vector<T, 2, O> const& b, T const& c) requires (Size == 4): vector(a, b.__mtl_at(0), b.__mtl_at(1), c) {}
		// vector4(scalar, scalar, vector2)
		__mtl_always_inline __mtl_interface_export
		constexpr vector(T const& a, T const& b, vector<T, 2, O> const& c) requires (Size == 4): vector(a, b, c.__mtl_at(0), c.__mtl_at(1)) {}
		// vector4(vector2, vector2)
		__mtl_always_inline __mtl_interface_export
		vector(vector<T, 2, O> const& a, vector<T, 2, O> const& b) requires (Size == 4): vector(a.__mtl_at(0), a.__mtl_at(1), b.__mtl_at(0), b.__mtl_at(1)) {}
		// vector4(vector3, scalar)
		__mtl_always_inline __mtl_interface_export
		vector(vector<T, 3, O> const& a, T const& b) requires (Size == 4): vector(a.__mtl_at(0), a.__mtl_at(1), a.__mtl_at(2), b) {}
		// vector4(scalar, vector3)
		__mtl_always_inline __mtl_interface_export
		vector(T const& a, vector<T, 3, O> const& b) requires (Size == 4): vector(a, b.__mtl_at(0), b.__mtl_at(1), b.__mtl_at(2)) {}
		
		vector& operator=(vector const&)& = default;
		
		/// operator[]:
		__mtl_always_inline __mtl_interface_export
		constexpr T& operator[](std::size_t index)& { return const_cast<T&>(const_cast<vector const&>(*this)[index]); }
		__mtl_always_inline __mtl_interface_export
		constexpr T const& operator[](std::size_t index) const& { __mtl_bounds_check(index, 0, Size); return __mtl_at(index); }
		__mtl_always_inline __mtl_interface_export
		constexpr T&& operator[](std::size_t index)&& { return const_cast<T&&>(const_cast<vector const&&>(*this)[index]); }
		__mtl_always_inline __mtl_interface_export
		constexpr T const&& operator[](std::size_t index) const&& { __mtl_bounds_check(index, 0, Size); return std::move(__mtl_at(index)); }
		
		/// begin, end:
		__mtl_always_inline __mtl_interface_export
		constexpr T* begin()              { return this->__data; }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* begin()  const { return this->__data; }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* cbegin() const { return this->__data; }
		__mtl_always_inline __mtl_interface_export
		constexpr T* end()                { return this->__data + size(); }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* end()  const   { return this->__data + size(); }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* cend() const   { return this->__data + size(); }
		
		/// data:
		__mtl_always_inline __mtl_interface_export
		constexpr T* data() { return this->__data; }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* data() const { return this->__data; }
		
		/// swizzle:
		template <std::convertible_to<std::size_t>... I>
		__mtl_always_inline __mtl_interface_export
		constexpr vector<T, sizeof...(I), O> swizzle(I... i) const { return { (*this)[i]... }; }
		
		/// map:
		__mtl_always_inline __mtl_interface_export
		constexpr auto map(std::invocable<T> auto&& f) const { return _VMTL::map(*this, __mtl_forward(f)); }
		
		/// fold:
		__mtl_always_inline __mtl_interface_export
		constexpr T fold(_VMTL::invocable_r<T, T, T> auto&& f) const { return _VMTL::fold(*this, __mtl_forward(f)); }
		
		/// MARK: Arithmetic Assignment
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator+=(vector const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator+=(T const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator-=(vector const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator-=(T const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator*=(vector const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator*=(T const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator/=(vector const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator/=(T const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator%=(vector const& rhs)& requires std::integral<T> {
			*this = *this % rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator%=(T const& rhs)& requires std::integral<T> {
			*this = *this % rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator&=(vector const& rhs)& {
			*this = *this & rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator|=(vector const& rhs)& {
			*this = *this | rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator^=(vector const& rhs)& {
			*this = *this ^ rhs;
			return *this;
		}
		
		template <std::integral U, vector_options P>
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator<<=(vector<U, Size, P> const& rhs)& {
			*this = *this << rhs;
			return *this;
		}
		
		template <std::integral U, vector_options P>
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator>>=(vector<U, Size, P> const& rhs)& {
			*this = *this >> rhs;
			return *this;
		}
		
		template <std::integral U>
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator<<=(U rhs)& {
			*this = *this << rhs;
			return *this;
		}
		
		template <std::integral U>
		__mtl_always_inline __mtl_interface_export
		constexpr vector& operator>>=(U rhs)& {
			*this = *this >> rhs;
			return *this;
		}
		
		/// MARK: Vector<bool> Members
		__mtl_always_inline __mtl_interface_export
		constexpr bool all() const requires std::convertible_to<T, bool> {
			return fold(__mtl_logical_and);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr bool any() const requires std::convertible_to<T, bool> {
			return fold(__mtl_logical_or);
		}
		
		/// MARK: Min, Max
		__mtl_always_inline __mtl_interface_export
		constexpr T& min() requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::min(__mtl_at(I)...);
			});
		}
		
		__mtl_always_inline __mtl_interface_export
		constexpr T const& min() const requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::min(__mtl_at(I)...);
			});
		}
		
		__mtl_always_inline __mtl_interface_export
		constexpr T& max() requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::max(__mtl_at(I)...);
			});
		}
		
		__mtl_always_inline __mtl_interface_export
		constexpr T const& max() const requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::max(__mtl_at(I)...);
			});
		}
	};
	
	/// deduction guide
	template <typename... T>
	vector(T...) -> vector<__mtl_promote(T...), sizeof...(T)>;
 
	
	/// MARK: - Operators
	/// operator==:
	template <typename T, typename U, std::size_t Size, vector_options O, vector_options P>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(vector<T, Size, O> const& v,
							  vector<U, Size, P> const& w) {
		return _VMTL::fold(_VMTL::map(v, w, _VMTL::__mtl_equals), _VMTL::__mtl_logical_and);
	}
	template <typename T, typename U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(vector<T, Size, O> const& v,
							  U const& w) {
		return _VMTL::fold(_VMTL::map(v, [&](auto i) { return i == w; }), _VMTL::__mtl_logical_and);
	}
	template <typename T, typename U, std::size_t Size, vector_options O>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(U const& w,
							  vector<T, Size, O> const& v) {
		return v == w;
	}
	
	// operator<<(std::ostream&, vector):
	template <typename CharT, typename T, std::size_t Size, vector_options O>
	__mtl_interface_export
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& str, vector<T, Size, O> const& v) {
		str << '(';
		for (bool first = true; auto&& i: v) {
			str << (first ? ((void)(first = false), "") : ", ") << i;
		}
		return str << ')';
	}
	
	/// MARK: - Generic Vector Function
	/// Concatenate Vectors and Scalars, handrolled to go easy on template meta programming
	// (s, s)
	template <scalar T, scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), 2> concat(T const& a, U const& b) {
		return vector<__mtl_promote(T, U), 2>(a, b);
	}
	// (s, s, s)
	template <scalar T, scalar U, scalar V>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U, V), 3> concat(T const& a, U const& b, V const& c) {
		return vector<__mtl_promote(T, U, V), 3>(a, b, c);
	}
	// (s, s, s, s)
	template <scalar T, scalar U, scalar V, scalar W>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U, V, W), 4> concat(T const& a, U const& b, V const& c, W const& d) {
		return vector<__mtl_promote(T, U, V, W), 4>(a, b, c, d);
	}
	// (v2, s)
	template <scalar T, scalar U, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	vector<__mtl_promote(T, U), 3, O> concat(vector<T, 2, O> const& a, U const& b) {
		return vector<__mtl_promote(T, U), 3, O>(a, b);
	}
	// (s, v2)
	template <scalar T, scalar U, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), 3, O> concat(T const& a, vector<U, 2, O> const& b) {
		return vector<__mtl_promote(T, U), 3, O>(a, b);
	}
	// (v2, s, s)
	template <scalar T, scalar U, scalar V, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U, V), 4, O> concat(vector<T, 2, O> const& a, U const& b, V const& c) {
		return vector<__mtl_promote(T, U, V), 4, O>(a, b, c);
	}
	// (s, v2, s)
	template <scalar T, scalar U, scalar V, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U, V), 4, O> concat(T const& a, vector<U, 2, O> const& b, V const& c) {
		return vector<__mtl_promote(T, U, V), 4, O>(a, b, c);
	}
	// (s, s, v2)
	template <scalar T, scalar U, scalar V, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U, V), 4, O> concat(T const& a, U const& b, vector<V, 2, O> const& c) {
		return vector<__mtl_promote(T, U, V), 4, O>(a, b, c);
	}
	// (v2, v2)
	template <scalar T, scalar U, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), 4, O> concat(vector<T, 2, O> const& a, vector<U, 2, P> const& b) {
		return vector<__mtl_promote(T, U), 4, O>(a, b);
	}
	// (v3, s)
	template <scalar T, scalar U, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), 4, O> concat(vector<T, 3, O> const& a, U const& b) {
		return vector<__mtl_promote(T, U), 4, O>(a, b);
	}
	// (s, v3)
	template <scalar T, scalar U, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U), 4, O> concat(T const& a, vector<U, 3, O> const& b) {
		return vector<__mtl_promote(T, U), 4, O>(a, b);
	}
	
	/// Reverse
	template <typename T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O> reverse(vector<T, Size, O> const& v) {
		return vector<T, Size, O>([&](std::size_t i) {
			return v.__mtl_at(Size - 1 - i);
		});
	}
	
	/// Type Cast
	template <typename To, typename T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<To, Size, O> type_cast(vector<T, Size, O> const& v) {
		return vector<To, Size, O>([&](std::size_t i) {
			return static_cast<To>(v.__mtl_at(i));
		});
	}
	
	/// Dimension Cast
	template <std::size_t To, typename T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, To, O> dimension_cast(vector<T, Size, O> const& v) {
		return vector<T, To, O>([&](std::size_t i) {
			if constexpr (To > Size) {
				return i >= Size ? T(0) : v.__mtl_at(i);
			}
			else {
				return v.__mtl_at(i);
			}
		});
	}
	
	/// isnan
	template <typename T, std::size_t Size, vector_options O>
	constexpr vector<bool, Size, O> isnan(vector<T, Size, O> const& m) {
		return vector<bool, Size, O>([&](std::size_t i) {
			using std::isnan;
			return isnan(m.__mtl_at(i));
		});
	}
	
	/// isinf
	template <typename T, std::size_t Size, vector_options O>
	constexpr vector<bool, Size, O> isinf(vector<T, Size, O> const& m) {
		return vector<bool, Size, O>([&](std::size_t i) {
			using std::isinf;
			return isinf(m.__mtl_at(i));
		});
	}
	
	/// isfinite
	template <typename T, std::size_t Size, vector_options O>
	constexpr vector<bool, Size, O> isfinite(vector<T, Size, O> const& m) {
		return vector<bool, Size, O>([&](std::size_t i) {
			using std::isfinite;
			return isfinite(m.__mtl_at(i));
		});
	}
	
	/// isnormal
	template <typename T, std::size_t Size, vector_options O>
	constexpr vector<bool, Size, O> isnormal(vector<T, Size, O> const& m) {
		return vector<bool, Size, O>([&](std::size_t i) {
			using std::isnormal;
			return isnormal(m.__mtl_at(i));
		});
	}
	
	/// MARK: - Vector Math Functions
	/// Dot Product of two Vectors
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto dot(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return fold(a * b, _VMTL::__mtl_plus);
	}
	
	/// Norm Squared of Vector (Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto norm_squared(vector<T, Size, O> const& a) {
		return map(a, [](auto const& x) { return norm_squared(x); }).fold(_VMTL::__mtl_plus);
	}
	
	/// Length Squared of Vector (same as Norm Squared, Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto length_squared(vector<T, Size, O> const& a)
	{
		return norm_squared(a);
	}
	
	/// Norm of Vector (Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto norm(vector<T, Size, O> const& a) {
		if constexpr (real_scalar<T>) {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::hypot(a.__mtl_at(I)...);
			});
		}
		else {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::hypot(norm(a.__mtl_at(I))...);
			});
		}
	}
	
	/// Fast / Unsafe Norm of Vector (Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto fast_norm(vector<T, Size, O> const& a) {
		if constexpr (real_scalar<T>) {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::fast_hypot(a.__mtl_at(I)...);
			});
		}
		else {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::fast_hypot(fast_norm(a.__mtl_at(I))...);
			});
		}
	}
	
	/// pNorm of Vector
	template <scalar F, scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto pnorm(F p, vector<T, Size, O> const& a) {
		if constexpr (real_scalar<T>) {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::phypot(p, a.__mtl_at(I)...);
			});
		}
		else {
			return __mtl_with_index_sequence((I, Size), {
				return _VMTL::phypot(p, pnorm(p, a.__mtl_at(I))...);
			});
		}
	}
	
	///  Sum Norm of vector
	template <typename T, std::size_t Size, vector_options O>
	constexpr auto sum_norm(vector<T, Size, O> const& v) {
		return __mtl_with_index_sequence((I, Size), {
			using std::abs;
			return (abs(v.__mtl_at(I)) + ...);
		});
	}
	
	///  Maximum Norm of vector
	template <typename T, std::size_t Size, vector_options O>
	constexpr auto max_norm(vector<T, Size, O> const& v) {
		return __mtl_with_index_sequence((I, Size), {
			using std::abs;
			return max(abs(v.__mtl_at(I))...);
		});
	}
	
	/// Length of Vector (same as Norm, Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto length(vector<T, Size, O> const& a) {
		return norm(a);
	}
	
	/// Distance Squared between to Points (Euclidian)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto distance_squared(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return norm_squared(a - b);
	}

	/// Distance between to Points (Euclidian)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto distance(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return norm(a - b);
	}
	
	/// Fast / Unsafe Distance between to Points (Euclidian)
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto fast_distance(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return fast_norm(a - b);
	}
	
	/// Normalize Vector (Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto normalize(vector<T, Size, O> const& a) {
		return a / norm(a);
	}
	
	/// Fast / Unsafe Normalize Vector (Euclidian)
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto fast_normalize(vector<T, Size, O> const& a) {
		return a / fast_norm(a);
	}
	
	/// Element-wise Minimum of Vectors
	template <real_scalar T, real_scalar... U, std::size_t Size, vector_options O, vector_options... P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U...), Size, combine(O, P...)> min(vector<T, Size, O> const& v, vector<U, Size, P> const&... w) {
		return map(v, w..., [](auto&&... x) { return _VMTL::min(x...); });
	}
	
	/// Element-wise Maximum of Vectors
	template <real_scalar T, real_scalar... U, std::size_t Size, vector_options O, vector_options... P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_promote(T, U...), Size, combine(O, P...)> max(vector<T, Size, O> const& v, vector<U, Size, P> const&... w) {
		return map(v, w..., [](auto&&... x) { return _VMTL::max(x...); });
	}
	
	/// Element-wise Absolute Value of Vector
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto abs(vector<T, Size, O> const& a) {
		return a.map(_VMTL::__mtl_abs);
	}
	
	/// Element-wise Square Root of Vector
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto sqrt(vector<T, Size, O> const& a) {
		return a.map(_VMTL::__mtl_sqrt);
	}
	
	/// Element-wise Cube Root of Vector
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto cbrt(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::cbrt; return cbrt(a); });
	}
	
	/// Element-wise Pow
	template <scalar T, scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto pow(vector<T, Size, O> const& base, vector<U, Size, P> const& exp) {
		return map(base, exp, [](T const& b, U const& e) { using std::pow; return pow(b, e); });
	}
	
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto pow(vector<T, Size, O> const& base, U const& exp) {
		return base.map([&](T const& b) { using std::pow; return pow(b, exp); });
	}
	
	template <scalar T, scalar U, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto pow(T const& base, vector<U, Size, O> const& exp) {
		return exp.map([&](U const& e) { using std::pow; return pow(base, e); });
	}
	
	/// Element-wise Exponential of Vector
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto exp(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::exp; return exp(a); });
	}
	
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto exp2(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::exp2; return exp2(a); });
	}
	
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto log(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::log; return log(a); });
	}
	
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto log2(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::log2; return log2(a); });
	}
	
	template <scalar T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto log10(vector<T, Size, O> const& a) {
		return a.map([](T const& a) { using std::log10; return log10(a); });
	}
	
	/// Element-wise Ceil Divide of Vector by Vector
	template <typename T, typename U = T, std::size_t Size, vector_options O, vector_options P = O>
	requires std::is_integral_v<T> && std::is_integral_v<U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto ceil_divide(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return map(a, b, [](auto&& x, auto&& y) { return _VMTL::__mtl_ceil_divide(x, y); });
	}
	
	/// Element-wise Ceil Divide of Vector by Scalar
	template <typename T, typename U, std::size_t Size, vector_options O>
	requires std::is_integral_v<T> && std::is_integral_v<U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto ceil_divide(vector<T, Size, O> const& a, U const& b) {
		return a.map([&](auto x){ return _VMTL::__mtl_ceil_divide(x, b); });
	}
	
	/// Element-wise Ceil Divide of Scalar by Vector
	template <typename T, typename U, std::size_t Size, vector_options O>
	requires std::is_integral_v<T> && std::is_integral_v<U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto ceil_divide(T const& a, vector<U, Size, O> const& b) {
		return b.map([&](auto x){ return _VMTL::__mtl_ceil_divide(a, x); });
	}
	
	/// Element-wise Fractional Part of Vector
	template <typename T, std::size_t Size, vector_options O>
	requires std::is_floating_point_v<T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto fract(vector<T, Size, O> const& a) {
		return a.map([](auto&& x){ return _VMTL::__mtl_fract(x); });
	}
	
	/// Element-wise Floor of Vector
	template <typename T, std::size_t Size, vector_options O>
	requires std::is_floating_point_v<T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O> floor(vector<T, Size, O> const& a) {
		return a.map([](auto&& x){ using std::floor; return floor(x); });
	}
	
	/// Element-wise Ceil of Vector
	template <typename T, std::size_t Size, vector_options O>
	requires std::is_floating_point_v<T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, Size, O> ceil(vector<T, Size, O> const& a) {
		return a.map([](auto&& x){ using std::ceil; return ceil(x); });
	}
	
	/// Element-wise Exp of Vector
	template <typename T, std::size_t Size, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<__mtl_floatify(T), Size, O> floor(vector<T, Size, O> const& a) {
		return a.map([](auto&& x){ using std::exp; return exp(x); });
	}
	
	/// Cross Product of two 3-Vectors
	template <real_scalar T, real_scalar U, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<__mtl_promote(T, U), combine(O, P)>
	cross(vector3<T, O> const& a, vector3<U, P> const& b) {
		return {
			a.__mtl_at(1) * b.__mtl_at(2) - a.__mtl_at(2) * b.__mtl_at(1),
			a.__mtl_at(2) * b.__mtl_at(0) - a.__mtl_at(0) * b.__mtl_at(2),
			a.__mtl_at(0) * b.__mtl_at(1) - a.__mtl_at(1) * b.__mtl_at(0)
		};
	}

	/// MARK: Comparison Operators
	template <real_scalar T, real_scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<bool, Size, combine(O, P)>
	operator<(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return map(a, b, __mtl_less);
	}
	
	template <real_scalar T, real_scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<bool, Size, combine(O, P)>
	operator<=(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return map(a, b, __mtl_less_eq);
	}
	
	template <real_scalar T, real_scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<bool, Size, combine(O, P)>
	operator>(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return map(a, b, __mtl_greater);
	}
	
	template <real_scalar T, real_scalar U, std::size_t Size, vector_options O, vector_options P>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector<bool, Size, combine(O, P)>
	operator>=(vector<T, Size, O> const& a, vector<U, Size, P> const& b) {
		return map(a, b, __mtl_greater_eq);
	}
	
}

/// MARK: - std::hash Specialization
template <typename T, std::size_t N, _VMTL::vector_options O>
class std::hash<_VMTL::vector<T, N, O>> {
public:
	std::size_t operator()(_VMTL::vector<T, N, O> const& v) const {
		std::size_t seed = _VMTL::__mtl_hash_seed;
		for (auto& i: v) {
			seed = _VMTL::__mtl_hash_combine(seed, i);
		}
		return seed;
	}
};

/// MARK: - Decomposition
namespace _VMTL {
	
	template <std::size_t I, typename T, std::size_t Size, vector_options O>
	requires (I < Size)
	constexpr T const& get(vector<T, Size, O> const& v) {
		return v.__mtl_at(I);
	}
	template <std::size_t I, typename T, std::size_t Size, vector_options O>
	requires (I < Size)
	constexpr T& get(vector<T, Size, O>& v) {
		return v.__mtl_at(I);
	}
	template <std::size_t I, typename T, std::size_t Size, vector_options O>
	requires (I < Size)
	constexpr T&& get(vector<T, Size, O>&& v) {
		return std::move(v.__mtl_at(I));
	}
	template <std::size_t I, typename T, std::size_t Size, vector_options O>
	requires (I < Size)
	constexpr T const&& get(vector<T, Size, O> const&& v) {
		return std::move(v.__mtl_at(I));
	}
	
}

template <typename T, std::size_t Size, _VMTL::vector_options O>
struct std::tuple_size<_VMTL::vector<T, Size, O>>: std::integral_constant<std::size_t, Size> {};

template <std::size_t I, typename T, std::size_t Size, _VMTL::vector_options O>
struct std::tuple_element<I, _VMTL::vector<T, Size, O>> {
	using type = T;
};

#endif // __MTL_VECTOR_HPP_INCLUDED__

#pragma once

/// __matrix.hpp

#ifndef __MTL_MATRIX_HPP_INCLUDED__
#define __MTL_MATRIX_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_


#define __MTL_DECLARE_MATRIX_TYPEDEFS__
/// __typedefs.hpp

/// DELIBERATELY NO INCLUDE GUARDS! Sections have their own include guards.


_MTL_SYSTEM_HEADER_


	
#ifdef __MTL_DECLARE_STDINT_TYPEDEFS__
#ifndef __MTL_STDINT_TYPEDEFS_INCLUDED__
#define __MTL_STDINT_TYPEDEFS_INCLUDED__
	
#include <cstdint>

namespace _VMTL {
	
	/**
	 These exist so I can conditionally declare 'namespace metal = mtl' in shared header files and use types below as metal::int32_t etc.
	 */

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
	
	using std::size_t;
	using usize = std::size_t;
	using isize = std::ptrdiff_t;
	
}
	
#endif // __MTL_STDINT_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_STDINT_TYPEDEFS__
	
	


namespace _VMTL {
	
	/// MARK: - Complex
#ifdef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#ifndef __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#define __MTL_COMPLEX_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using complex_float   = complex<float>;
		using complex_double  = complex<double>;
		using complex_ldouble = complex<long double>;
		
		using complex_int     = complex<int>;
		using complex_long    = complex<long>;
		using complex_llong   = complex<long long>;
		using complex_uint    = complex<unsigned int>;
		using complex_ulong   = complex<unsigned long>;
		using complex_ullong  = complex<unsigned long long>;
		
	}
	
#endif // __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_COMPLEX_TYPEDEFS__
	
	/// MARK: - Quaternion
#ifdef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#ifndef __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#define __MTL_QUATERNION_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using quaternion_float   = quaternion<float>;
		using quaternion_double  = quaternion<double>;
		using quaternion_ldouble = quaternion<long double>;
		
		using quaternion_int     = quaternion<int>;
		using quaternion_long    = quaternion<long>;
		using quaternion_llong   = quaternion<long long>;
		using quaternion_uint    = quaternion<unsigned int>;
		using quaternion_ulong   = quaternion<unsigned long>;
		using quaternion_ullong  = quaternion<unsigned long long>;
		
	}
	
#endif // __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_QUATERNION_TYPEDEFS__
	
	// MARK: - Vector
#ifdef __MTL_DECLARE_VECTOR_TYPEDEFS__
#ifndef __MTL_VECTOR_TYPEDEFS_INCLUDED__
#define __MTL_VECTOR_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using vector2 = vector<T, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector3 = vector<T, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector4 = vector<T, 4, O>;
	
	inline namespace short_types {
		
		using size2            = vector2<std::size_t>;
		using size3            = vector3<std::size_t>;
		using size4            = vector4<std::size_t>;
		
		using usize2            = vector2<std::size_t>;
		using usize3            = vector3<std::size_t>;
		using usize4            = vector4<std::size_t>;
		
		using isize2            = vector2<std::ptrdiff_t>;
		using isize3            = vector3<std::ptrdiff_t>;
		using isize4            = vector4<std::ptrdiff_t>;
		
		using bool2            = vector2<bool>;
		using bool3            = vector3<bool>;
		using bool4            = vector4<bool>;
		using char2            = vector2<char>;
		using char3            = vector3<char>;
		using char4            = vector4<char>;
		using schar2           = vector2<char>;
		using schar3           = vector3<char>;
		using schar4           = vector4<char>;
		using uchar2           = vector2<unsigned char>;
		using uchar3           = vector3<unsigned char>;
		using uchar4           = vector4<unsigned char>;
		using short2           = vector2<short>;
		using short3           = vector3<short>;
		using short4           = vector4<short>;
		using ushort2          = vector2<unsigned short>;
		using ushort3          = vector3<unsigned short>;
		using ushort4          = vector4<unsigned short>;
		using int2             = vector2<int>;
		using int3             = vector3<int>;
		using int4             = vector4<int>;
		using uint2            = vector2<unsigned int>;
		using uint3            = vector3<unsigned int>;
		using uint4            = vector4<unsigned int>;
		using long2            = vector2<long>;
		using long3            = vector3<long>;
		using long4            = vector4<long>;
		using ulong2           = vector2<unsigned long>;
		using ulong3           = vector3<unsigned long>;
		using ulong4           = vector4<unsigned long>;
		using llong2           = vector2<long long>;
		using llong3           = vector3<long long>;
		using llong4           = vector4<long long>;
		using ullong2          = vector2<unsigned long long>;
		using ullong3          = vector3<unsigned long long>;
		using ullong4          = vector4<unsigned long long>;
		using float2           = vector2<float>;
		using float3           = vector3<float>;
		using float4           = vector4<float>;
		using double2          = vector2<double>;
		using double3          = vector3<double>;
		using double4          = vector4<double>;
		using ldouble2         = vector2<long double>;
		using ldouble3         = vector3<long double>;
		using ldouble4         = vector4<long double>;
		
		using packed_bool2     = vector2<bool,               vector_options{}.packed(true)>;
		using packed_bool3     = vector3<bool,               vector_options{}.packed(true)>;
		using packed_bool4     = vector4<bool,               vector_options{}.packed(true)>;
		using packed_char2     = vector2<char,               vector_options{}.packed(true)>;
		using packed_char3     = vector3<char,               vector_options{}.packed(true)>;
		using packed_char4     = vector4<char,               vector_options{}.packed(true)>;
		using packed_uchar2    = vector2<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar3    = vector3<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar4    = vector4<unsigned char,      vector_options{}.packed(true)>;
		using packed_short2    = vector2<short,              vector_options{}.packed(true)>;
		using packed_short3    = vector3<short,              vector_options{}.packed(true)>;
		using packed_short4    = vector4<short,              vector_options{}.packed(true)>;
		using packed_ushort2   = vector2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3   = vector3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4   = vector4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2      = vector2<int,                vector_options{}.packed(true)>;
		using packed_int3      = vector3<int,                vector_options{}.packed(true)>;
		using packed_int4      = vector4<int,                vector_options{}.packed(true)>;
		using packed_uint2     = vector2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3     = vector3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4     = vector4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2     = vector2<long,               vector_options{}.packed(true)>;
		using packed_long3     = vector3<long,               vector_options{}.packed(true)>;
		using packed_long4     = vector4<long,               vector_options{}.packed(true)>;
		using packed_ulong2    = vector2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3    = vector3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4    = vector4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2    = vector2<long long,          vector_options{}.packed(true)>;
		using packed_llong3    = vector3<long long,          vector_options{}.packed(true)>;
		using packed_llong4    = vector4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2   = vector2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3   = vector3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4   = vector4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2    = vector2<float,              vector_options{}.packed(true)>;
		using packed_float3    = vector3<float,              vector_options{}.packed(true)>;
		using packed_float4    = vector4<float,              vector_options{}.packed(true)>;
		using packed_double2   = vector2<double,             vector_options{}.packed(true)>;
		using packed_double3   = vector3<double,             vector_options{}.packed(true)>;
		using packed_double4   = vector4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2  = vector2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3  = vector3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4  = vector4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2    = vector2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3    = vector3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4    = vector4<bool,               vector_options{}.packed(false)>;
		using aligned_char2    = vector2<char,               vector_options{}.packed(false)>;
		using aligned_char3    = vector3<char,               vector_options{}.packed(false)>;
		using aligned_char4    = vector4<char,               vector_options{}.packed(false)>;
		using aligned_uchar2   = vector2<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar3   = vector3<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar4   = vector4<unsigned char,      vector_options{}.packed(false)>;
		using aligned_short2   = vector2<short,              vector_options{}.packed(false)>;
		using aligned_short3   = vector3<short,              vector_options{}.packed(false)>;
		using aligned_short4   = vector4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2  = vector2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3  = vector3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4  = vector4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2     = vector2<int,                vector_options{}.packed(false)>;
		using aligned_int3     = vector3<int,                vector_options{}.packed(false)>;
		using aligned_int4     = vector4<int,                vector_options{}.packed(false)>;
		using aligned_uint2    = vector2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3    = vector3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4    = vector4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2    = vector2<long,               vector_options{}.packed(false)>;
		using aligned_long3    = vector3<long,               vector_options{}.packed(false)>;
		using aligned_long4    = vector4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2   = vector2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3   = vector3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4   = vector4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2   = vector2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3   = vector3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4   = vector4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2  = vector2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3  = vector3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4  = vector4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2   = vector2<float,              vector_options{}.packed(false)>;
		using aligned_float3   = vector3<float,              vector_options{}.packed(false)>;
		using aligned_float4   = vector4<float,              vector_options{}.packed(false)>;
		using aligned_double2  = vector2<double,             vector_options{}.packed(false)>;
		using aligned_double3  = vector3<double,             vector_options{}.packed(false)>;
		using aligned_double4  = vector4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2 = vector2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3 = vector3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4 = vector4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_VECTOR_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_VECTOR_TYPEDEFS__
	
	/// MARK: - Matrix
#ifdef __MTL_DECLARE_MATRIX_TYPEDEFS__
#ifndef __MTL_MATRIX_TYPEDEFS_INCLUDED__
#define __MTL_MATRIX_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using matrix2x2 = matrix<T, 2, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x3 = matrix<T, 2, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x4 = matrix<T, 2, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x2 = matrix<T, 3, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x3 = matrix<T, 3, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x4 = matrix<T, 3, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x2 = matrix<T, 4, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x3 = matrix<T, 4, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x4 = matrix<T, 4, 4, O>;
	
	inline namespace short_types {
	
		using bool2x2            = matrix2x2<bool,               vector_options{}>;
		using bool2x3            = matrix2x3<bool,               vector_options{}>;
		using bool2x4            = matrix2x4<bool,               vector_options{}>;
		using bool3x2            = matrix3x2<bool,               vector_options{}>;
		using bool3x3            = matrix3x3<bool,               vector_options{}>;
		using bool3x4            = matrix3x4<bool,               vector_options{}>;
		using bool4x2            = matrix4x2<bool,               vector_options{}>;
		using bool4x3            = matrix4x3<bool,               vector_options{}>;
		using bool4x4            = matrix4x4<bool,               vector_options{}>;
		using short2x2           = matrix2x2<short,              vector_options{}>;
		using short2x3           = matrix2x3<short,              vector_options{}>;
		using short2x4           = matrix2x4<short,              vector_options{}>;
		using short3x2           = matrix3x2<short,              vector_options{}>;
		using short3x3           = matrix3x3<short,              vector_options{}>;
		using short3x4           = matrix3x4<short,              vector_options{}>;
		using short4x2           = matrix4x2<short,              vector_options{}>;
		using short4x3           = matrix4x3<short,              vector_options{}>;
		using short4x4           = matrix4x4<short,              vector_options{}>;
		using ushort2x2          = matrix2x2<unsigned short,     vector_options{}>;
		using ushort2x3          = matrix2x3<unsigned short,     vector_options{}>;
		using ushort2x4          = matrix2x4<unsigned short,     vector_options{}>;
		using ushort3x2          = matrix3x2<unsigned short,     vector_options{}>;
		using ushort3x3          = matrix3x3<unsigned short,     vector_options{}>;
		using ushort3x4          = matrix3x4<unsigned short,     vector_options{}>;
		using ushort4x2          = matrix4x2<unsigned short,     vector_options{}>;
		using ushort4x3          = matrix4x3<unsigned short,     vector_options{}>;
		using ushort4x4          = matrix4x4<unsigned short,     vector_options{}>;
		using int2x2             = matrix2x2<int,                vector_options{}>;
		using int2x3             = matrix2x3<int,                vector_options{}>;
		using int2x4             = matrix2x4<int,                vector_options{}>;
		using int3x2             = matrix3x2<int,                vector_options{}>;
		using int3x3             = matrix3x3<int,                vector_options{}>;
		using int3x4             = matrix3x4<int,                vector_options{}>;
		using int4x2             = matrix4x2<int,                vector_options{}>;
		using int4x3             = matrix4x3<int,                vector_options{}>;
		using int4x4             = matrix4x4<int,                vector_options{}>;
		using uint2x2            = matrix2x2<unsigned int,       vector_options{}>;
		using uint2x3            = matrix2x3<unsigned int,       vector_options{}>;
		using uint2x4            = matrix2x4<unsigned int,       vector_options{}>;
		using uint3x2            = matrix3x2<unsigned int,       vector_options{}>;
		using uint3x3            = matrix3x3<unsigned int,       vector_options{}>;
		using uint3x4            = matrix3x4<unsigned int,       vector_options{}>;
		using uint4x2            = matrix4x2<unsigned int,       vector_options{}>;
		using uint4x3            = matrix4x3<unsigned int,       vector_options{}>;
		using uint4x4            = matrix4x4<unsigned int,       vector_options{}>;
		using long2x2            = matrix2x2<long,               vector_options{}>;
		using long2x3            = matrix2x3<long,               vector_options{}>;
		using long2x4            = matrix2x4<long,               vector_options{}>;
		using long3x2            = matrix3x2<long,               vector_options{}>;
		using long3x3            = matrix3x3<long,               vector_options{}>;
		using long3x4            = matrix3x4<long,               vector_options{}>;
		using long4x2            = matrix4x2<long,               vector_options{}>;
		using long4x3            = matrix4x3<long,               vector_options{}>;
		using long4x4            = matrix4x4<long,               vector_options{}>;
		using ulong2x2           = matrix2x2<unsigned long,      vector_options{}>;
		using ulong2x3           = matrix2x3<unsigned long,      vector_options{}>;
		using ulong2x4           = matrix2x4<unsigned long,      vector_options{}>;
		using ulong3x2           = matrix3x2<unsigned long,      vector_options{}>;
		using ulong3x3           = matrix3x3<unsigned long,      vector_options{}>;
		using ulong3x4           = matrix3x4<unsigned long,      vector_options{}>;
		using ulong4x2           = matrix4x2<unsigned long,      vector_options{}>;
		using ulong4x3           = matrix4x3<unsigned long,      vector_options{}>;
		using ulong4x4           = matrix4x4<unsigned long,      vector_options{}>;
		using llong2x2           = matrix2x2<long long,          vector_options{}>;
		using llong2x3           = matrix2x3<long long,          vector_options{}>;
		using llong2x4           = matrix2x4<long long,          vector_options{}>;
		using llong3x2           = matrix3x2<long long,          vector_options{}>;
		using llong3x3           = matrix3x3<long long,          vector_options{}>;
		using llong3x4           = matrix3x4<long long,          vector_options{}>;
		using llong4x2           = matrix4x2<long long,          vector_options{}>;
		using llong4x3           = matrix4x3<long long,          vector_options{}>;
		using llong4x4           = matrix4x4<long long,          vector_options{}>;
		using ullong2x2          = matrix2x2<unsigned long long, vector_options{}>;
		using ullong2x3          = matrix2x3<unsigned long long, vector_options{}>;
		using ullong2x4          = matrix2x4<unsigned long long, vector_options{}>;
		using ullong3x2          = matrix3x2<unsigned long long, vector_options{}>;
		using ullong3x3          = matrix3x3<unsigned long long, vector_options{}>;
		using ullong3x4          = matrix3x4<unsigned long long, vector_options{}>;
		using ullong4x2          = matrix4x2<unsigned long long, vector_options{}>;
		using ullong4x3          = matrix4x3<unsigned long long, vector_options{}>;
		using ullong4x4          = matrix4x4<unsigned long long, vector_options{}>;
		using float2x2           = matrix2x2<float,              vector_options{}>;
		using float2x3           = matrix2x3<float,              vector_options{}>;
		using float2x4           = matrix2x4<float,              vector_options{}>;
		using float3x2           = matrix3x2<float,              vector_options{}>;
		using float3x3           = matrix3x3<float,              vector_options{}>;
		using float3x4           = matrix3x4<float,              vector_options{}>;
		using float4x2           = matrix4x2<float,              vector_options{}>;
		using float4x3           = matrix4x3<float,              vector_options{}>;
		using float4x4           = matrix4x4<float,              vector_options{}>;
		using double2x2          = matrix2x2<double,             vector_options{}>;
		using double2x3          = matrix2x3<double,             vector_options{}>;
		using double2x4          = matrix2x4<double,             vector_options{}>;
		using double3x2          = matrix3x2<double,             vector_options{}>;
		using double3x3          = matrix3x3<double,             vector_options{}>;
		using double3x4          = matrix3x4<double,             vector_options{}>;
		using double4x2          = matrix4x2<double,             vector_options{}>;
		using double4x3          = matrix4x3<double,             vector_options{}>;
		using double4x4          = matrix4x4<double,             vector_options{}>;
		using ldouble2x2         = matrix2x2<long double,        vector_options{}>;
		using ldouble2x3         = matrix2x3<long double,        vector_options{}>;
		using ldouble2x4         = matrix2x4<long double,        vector_options{}>;
		using ldouble3x2         = matrix3x2<long double,        vector_options{}>;
		using ldouble3x3         = matrix3x3<long double,        vector_options{}>;
		using ldouble3x4         = matrix3x4<long double,        vector_options{}>;
		using ldouble4x2         = matrix4x2<long double,        vector_options{}>;
		using ldouble4x3         = matrix4x3<long double,        vector_options{}>;
		using ldouble4x4         = matrix4x4<long double,        vector_options{}>;
	 
		using packed_bool2x2     = matrix2x2<bool,               vector_options{}.packed(true)>;
		using packed_bool2x3     = matrix2x3<bool,               vector_options{}.packed(true)>;
		using packed_bool2x4     = matrix2x4<bool,               vector_options{}.packed(true)>;
		using packed_bool3x2     = matrix3x2<bool,               vector_options{}.packed(true)>;
		using packed_bool3x3     = matrix3x3<bool,               vector_options{}.packed(true)>;
		using packed_bool3x4     = matrix3x4<bool,               vector_options{}.packed(true)>;
		using packed_bool4x2     = matrix4x2<bool,               vector_options{}.packed(true)>;
		using packed_bool4x3     = matrix4x3<bool,               vector_options{}.packed(true)>;
		using packed_bool4x4     = matrix4x4<bool,               vector_options{}.packed(true)>;
		using packed_short2x2    = matrix2x2<short,              vector_options{}.packed(true)>;
		using packed_short2x3    = matrix2x3<short,              vector_options{}.packed(true)>;
		using packed_short2x4    = matrix2x4<short,              vector_options{}.packed(true)>;
		using packed_short3x2    = matrix3x2<short,              vector_options{}.packed(true)>;
		using packed_short3x3    = matrix3x3<short,              vector_options{}.packed(true)>;
		using packed_short3x4    = matrix3x4<short,              vector_options{}.packed(true)>;
		using packed_short4x2    = matrix4x2<short,              vector_options{}.packed(true)>;
		using packed_short4x3    = matrix4x3<short,              vector_options{}.packed(true)>;
		using packed_short4x4    = matrix4x4<short,              vector_options{}.packed(true)>;
		using packed_ushort2x2   = matrix2x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x3   = matrix2x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x4   = matrix2x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x2   = matrix3x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x3   = matrix3x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x4   = matrix3x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x2   = matrix4x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x3   = matrix4x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x4   = matrix4x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2x2      = matrix2x2<int,                vector_options{}.packed(true)>;
		using packed_int2x3      = matrix2x3<int,                vector_options{}.packed(true)>;
		using packed_int2x4      = matrix2x4<int,                vector_options{}.packed(true)>;
		using packed_int3x2      = matrix3x2<int,                vector_options{}.packed(true)>;
		using packed_int3x3      = matrix3x3<int,                vector_options{}.packed(true)>;
		using packed_int3x4      = matrix3x4<int,                vector_options{}.packed(true)>;
		using packed_int4x2      = matrix4x2<int,                vector_options{}.packed(true)>;
		using packed_int4x3      = matrix4x3<int,                vector_options{}.packed(true)>;
		using packed_int4x4      = matrix4x4<int,                vector_options{}.packed(true)>;
		using packed_uint2x2     = matrix2x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x3     = matrix2x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x4     = matrix2x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x2     = matrix3x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x3     = matrix3x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x4     = matrix3x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x2     = matrix4x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x3     = matrix4x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x4     = matrix4x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2x2     = matrix2x2<long,               vector_options{}.packed(true)>;
		using packed_long2x3     = matrix2x3<long,               vector_options{}.packed(true)>;
		using packed_long2x4     = matrix2x4<long,               vector_options{}.packed(true)>;
		using packed_long3x2     = matrix3x2<long,               vector_options{}.packed(true)>;
		using packed_long3x3     = matrix3x3<long,               vector_options{}.packed(true)>;
		using packed_long3x4     = matrix3x4<long,               vector_options{}.packed(true)>;
		using packed_long4x2     = matrix4x2<long,               vector_options{}.packed(true)>;
		using packed_long4x3     = matrix4x3<long,               vector_options{}.packed(true)>;
		using packed_long4x4     = matrix4x4<long,               vector_options{}.packed(true)>;
		using packed_ulong2x2    = matrix2x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x3    = matrix2x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x4    = matrix2x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x2    = matrix3x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x3    = matrix3x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x4    = matrix3x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x2    = matrix4x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x3    = matrix4x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x4    = matrix4x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2x2    = matrix2x2<long long,          vector_options{}.packed(true)>;
		using packed_llong2x3    = matrix2x3<long long,          vector_options{}.packed(true)>;
		using packed_llong2x4    = matrix2x4<long long,          vector_options{}.packed(true)>;
		using packed_llong3x2    = matrix3x2<long long,          vector_options{}.packed(true)>;
		using packed_llong3x3    = matrix3x3<long long,          vector_options{}.packed(true)>;
		using packed_llong3x4    = matrix3x4<long long,          vector_options{}.packed(true)>;
		using packed_llong4x2    = matrix4x2<long long,          vector_options{}.packed(true)>;
		using packed_llong4x3    = matrix4x3<long long,          vector_options{}.packed(true)>;
		using packed_llong4x4    = matrix4x4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2x2   = matrix2x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x3   = matrix2x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x4   = matrix2x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x2   = matrix3x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x3   = matrix3x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x4   = matrix3x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x2   = matrix4x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x3   = matrix4x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x4   = matrix4x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2x2    = matrix2x2<float,              vector_options{}.packed(true)>;
		using packed_float2x3    = matrix2x3<float,              vector_options{}.packed(true)>;
		using packed_float2x4    = matrix2x4<float,              vector_options{}.packed(true)>;
		using packed_float3x2    = matrix3x2<float,              vector_options{}.packed(true)>;
		using packed_float3x3    = matrix3x3<float,              vector_options{}.packed(true)>;
		using packed_float3x4    = matrix3x4<float,              vector_options{}.packed(true)>;
		using packed_float4x2    = matrix4x2<float,              vector_options{}.packed(true)>;
		using packed_float4x3    = matrix4x3<float,              vector_options{}.packed(true)>;
		using packed_float4x4    = matrix4x4<float,              vector_options{}.packed(true)>;
		using packed_double2x2   = matrix2x2<double,             vector_options{}.packed(true)>;
		using packed_double2x3   = matrix2x3<double,             vector_options{}.packed(true)>;
		using packed_double2x4   = matrix2x4<double,             vector_options{}.packed(true)>;
		using packed_double3x2   = matrix3x2<double,             vector_options{}.packed(true)>;
		using packed_double3x3   = matrix3x3<double,             vector_options{}.packed(true)>;
		using packed_double3x4   = matrix3x4<double,             vector_options{}.packed(true)>;
		using packed_double4x2   = matrix4x2<double,             vector_options{}.packed(true)>;
		using packed_double4x3   = matrix4x3<double,             vector_options{}.packed(true)>;
		using packed_double4x4   = matrix4x4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2x2  = matrix2x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x3  = matrix2x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x4  = matrix2x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x2  = matrix3x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x3  = matrix3x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x4  = matrix3x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x2  = matrix4x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x3  = matrix4x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x4  = matrix4x4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2x2    = matrix2x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x3    = matrix2x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x4    = matrix2x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x2    = matrix3x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x3    = matrix3x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x4    = matrix3x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x2    = matrix4x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x3    = matrix4x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x4    = matrix4x4<bool,               vector_options{}.packed(false)>;
		using aligned_short2x2   = matrix2x2<short,              vector_options{}.packed(false)>;
		using aligned_short2x3   = matrix2x3<short,              vector_options{}.packed(false)>;
		using aligned_short2x4   = matrix2x4<short,              vector_options{}.packed(false)>;
		using aligned_short3x2   = matrix3x2<short,              vector_options{}.packed(false)>;
		using aligned_short3x3   = matrix3x3<short,              vector_options{}.packed(false)>;
		using aligned_short3x4   = matrix3x4<short,              vector_options{}.packed(false)>;
		using aligned_short4x2   = matrix4x2<short,              vector_options{}.packed(false)>;
		using aligned_short4x3   = matrix4x3<short,              vector_options{}.packed(false)>;
		using aligned_short4x4   = matrix4x4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2x2  = matrix2x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x3  = matrix2x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x4  = matrix2x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x2  = matrix3x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x3  = matrix3x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x4  = matrix3x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x2  = matrix4x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x3  = matrix4x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x4  = matrix4x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2x2     = matrix2x2<int,                vector_options{}.packed(false)>;
		using aligned_int2x3     = matrix2x3<int,                vector_options{}.packed(false)>;
		using aligned_int2x4     = matrix2x4<int,                vector_options{}.packed(false)>;
		using aligned_int3x2     = matrix3x2<int,                vector_options{}.packed(false)>;
		using aligned_int3x3     = matrix3x3<int,                vector_options{}.packed(false)>;
		using aligned_int3x4     = matrix3x4<int,                vector_options{}.packed(false)>;
		using aligned_int4x2     = matrix4x2<int,                vector_options{}.packed(false)>;
		using aligned_int4x3     = matrix4x3<int,                vector_options{}.packed(false)>;
		using aligned_int4x4     = matrix4x4<int,                vector_options{}.packed(false)>;
		using aligned_uint2x2    = matrix2x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x3    = matrix2x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x4    = matrix2x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x2    = matrix3x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x3    = matrix3x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x4    = matrix3x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x2    = matrix4x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x3    = matrix4x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x4    = matrix4x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2x2    = matrix2x2<long,               vector_options{}.packed(false)>;
		using aligned_long2x3    = matrix2x3<long,               vector_options{}.packed(false)>;
		using aligned_long2x4    = matrix2x4<long,               vector_options{}.packed(false)>;
		using aligned_long3x2    = matrix3x2<long,               vector_options{}.packed(false)>;
		using aligned_long3x3    = matrix3x3<long,               vector_options{}.packed(false)>;
		using aligned_long3x4    = matrix3x4<long,               vector_options{}.packed(false)>;
		using aligned_long4x2    = matrix4x2<long,               vector_options{}.packed(false)>;
		using aligned_long4x3    = matrix4x3<long,               vector_options{}.packed(false)>;
		using aligned_long4x4    = matrix4x4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2x2   = matrix2x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x3   = matrix2x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x4   = matrix2x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x2   = matrix3x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x3   = matrix3x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x4   = matrix3x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x2   = matrix4x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x3   = matrix4x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x4   = matrix4x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2x2   = matrix2x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x3   = matrix2x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x4   = matrix2x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x2   = matrix3x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x3   = matrix3x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x4   = matrix3x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x2   = matrix4x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x3   = matrix4x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x4   = matrix4x4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2x2  = matrix2x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x3  = matrix2x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x4  = matrix2x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x2  = matrix3x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x3  = matrix3x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x4  = matrix3x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x2  = matrix4x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x3  = matrix4x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x4  = matrix4x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2x2   = matrix2x2<float,              vector_options{}.packed(false)>;
		using aligned_float2x3   = matrix2x3<float,              vector_options{}.packed(false)>;
		using aligned_float2x4   = matrix2x4<float,              vector_options{}.packed(false)>;
		using aligned_float3x2   = matrix3x2<float,              vector_options{}.packed(false)>;
		using aligned_float3x3   = matrix3x3<float,              vector_options{}.packed(false)>;
		using aligned_float3x4   = matrix3x4<float,              vector_options{}.packed(false)>;
		using aligned_float4x2   = matrix4x2<float,              vector_options{}.packed(false)>;
		using aligned_float4x3   = matrix4x3<float,              vector_options{}.packed(false)>;
		using aligned_float4x4   = matrix4x4<float,              vector_options{}.packed(false)>;
		using aligned_double2x2  = matrix2x2<double,             vector_options{}.packed(false)>;
		using aligned_double2x3  = matrix2x3<double,             vector_options{}.packed(false)>;
		using aligned_double2x4  = matrix2x4<double,             vector_options{}.packed(false)>;
		using aligned_double3x2  = matrix3x2<double,             vector_options{}.packed(false)>;
		using aligned_double3x3  = matrix3x3<double,             vector_options{}.packed(false)>;
		using aligned_double3x4  = matrix3x4<double,             vector_options{}.packed(false)>;
		using aligned_double4x2  = matrix4x2<double,             vector_options{}.packed(false)>;
		using aligned_double4x3  = matrix4x3<double,             vector_options{}.packed(false)>;
		using aligned_double4x4  = matrix4x4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2x2 = matrix2x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x3 = matrix2x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x4 = matrix2x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x2 = matrix3x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x3 = matrix3x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x4 = matrix3x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x2 = matrix4x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x3 = matrix4x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x4 = matrix4x4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_MATRIX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_MATRIX_TYPEDEFS__
	
}





#include <iosfwd>
#include <sstream>
#include <iomanip>
#include <array>

/// MARK: - Synopsis
/*
 
 namespace mtl {
 
	struct rows_tag{}    inline constexpr rows{};
	struct columns_tag{} inline constexpr columns{};
 
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options Options>
	class matrix {
		// type information:
		value_type  = T
		rows_type   = vector<T, Columns, Options>
		column_type = vector<T, Rows, Options>
		size()     -> std::size_t    // Rows * Columns
		rows()     -> std::size_t    // Rows
		columns()  -> std::size_t    // Columns
		options()  -> vector_options // Options
 
		// value constructors:
		matrix() = default;
		matrix(T value);                                      -> // diag(value)
		matrix(T value0, T value1, ...);                      -> // matrix{ value0, value1, ... }
		matrix(rows_tag,    row_type...);
		matrix(columns_tag, column_type...);
 
		// functional constructors:
		matrix(f: () -> T);                                   -> // matrix{ f(), f(), ... }
		matrix(f: (std::size_t) -> T);                        -> // matrix{ f(0), f(1), ... }
		matrix(f: (std::size_t, std::size_t) -> T);           -> // matrix{ f(0, 0), f(1, 0), ...
																	        f(1, 0), f(1, 1), ...
																	        ...,     ...,     ... }
		matrix(rows_tag,    f: (std::size_t) -> row_type);    -> // matrix(rows,    f(0), f(1), ...)
		matrix(columns_tag, f: (std::size_t) -> column_type); -> // matrix(columns, f(0), f(1), ...)
		
		// operator[]:
		operator[](std::size_t) -> T&
		operator[](std::size_t) const -> T const&
 
		// operator(): (double index subscript)
		operator()(std::size_t, std::size_t) -> T&
		operator()(std::size_t, std::size_t) const -> T const&
	 
		// row, column:
		row(std::size_t) const;
		column(std::size_t) const;
		set_row(std::size_t, row_type);
		set_column(std::size_t, column_type);
 
		// begin, end:
		begin(), end()               -> iterator
		begin() const, end() const   -> const_iterator
		cbegin() const, cend() const -> const_iterator
 
		// swizzle:
		row_swizzle(std::size_t i0, ...) -> matrix<T, N, Columns, Options>
		column_swizzle(std::size_t i0, ...) -> matrix<T, Rows, N, Options>
	 
		// map:
		map(f: (T) -> Any) const -> matrix<{ deduced type }, Rows, Columns, Options>
		 
		// fold: (in data layout order / row major)
		fold(f: (T, T) -> T) const -> T
		left_fold(f: (T, T) -> T) const -> T
		right_fold(f: (T, T) -> T) const -> T
	 
	 
		// statics
		unit(std::size_t row, std::size_t column, T value = 1) -> matrix<T, Rows, Columns, Options>
				// matrix{ 0..., value [at position [row, column]], 0... }
		diag(T value) -> matrix<T, Rows, Colums, Options>
	};
	 
	operator==(matrix, matrix) -> bool
	operator!=(matrix, matrix) -> bool (synthesized)
	map(matrix<Ts, Rows, Columns>..., f: (Ts...) -> fResult) -> matrix<fResult, Rows, Columns>
	
	// fold: (all in data layout order / row major)
	fold(matrix<T, Rows, Columns> m, f: (T, T) -> T) -> T       // left_fold(m, f)
	left_fold(matrix<T, Rows, Columns> m, f: (T, T) -> T) -> T  // ...f(f(f(m[0], m[1]), m[2]),  ...)
	right_fold(matrix<T, Rows, Columns> m, f: (T, T) -> T) -> T // f(...f(..., f(m[N-2], m[N-1])))

	// transpose:
	transpose(matrix<T, Rows, Columns, Options>) -> matrix<T, Columns, Rows, Options>
 
 }
 
 */


namespace _VMTL {
	
	/// Tag type to select matrix row constructor
	struct rows_tag{};
	/// Tag to select matrix row constructor
	inline constexpr rows_tag rows{};
	/// Tag type to select matrix column constructor
	struct columns_tag{};
	/// Tag to select matrix column constructor
	inline constexpr columns_tag columns{};

	/// MARK: Map
	template <typename... T, std::size_t R, std::size_t C, vector_options... O, std::invocable<T...> F>
	__mtl_mathfunction __mtl_always_inline
	constexpr auto __map_impl(F&& f, matrix<T, R, C, O> const&... m) {
		using U = std::invoke_result_t<F, T...>;
		if constexpr (std::same_as<U, void>) {
			for (std::size_t i = 0; i < R * C; ++i) {
				std::invoke(__mtl_forward(f), m.__mtl_vec_at(i)...);
			}
		}
		else {
			constexpr auto P = combine(O...);
			return matrix<U, R, C, P>([&](std::size_t i) { return std::invoke(__mtl_forward(f), m.__mtl_vec_at(i)...); });
		}
	}
	
	/// Map the unary function object f onto the matrix m0
	template <typename T0, std::size_t R, std::size_t C, vector_options O0, std::invocable<T0> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), m0);
	}
	
	/// Map the binary function object f onto the matrices m0 and m1
	template <typename T0, typename T1, std::size_t R, std::size_t C,
			  vector_options O0, vector_options O1,
			  std::invocable<T0, T1> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   matrix<T1, R, C, O1> const& m1,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), m0, m1);
	}
	
	/// Map the ternary function object f onto the matrices m0, m1, m2
	template <typename T0, typename T1, typename T2, std::size_t R, std::size_t C,
			  vector_options O0, vector_options O1, vector_options O2,
			  std::invocable<T0, T1, T2> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   matrix<T1, R, C, O1> const& m1,
					   matrix<T2, R, C, O2> const& m2,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), m0, m1, m2);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, std::size_t R, std::size_t C,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3,
			  std::invocable<T0, T1, T2, T3> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   matrix<T1, R, C, O1> const& m1,
					   matrix<T2, R, C, O2> const& m2,
					   matrix<T3, R, C, O3> const& m3,
					   F&& f) 
	{
		return __map_impl(__mtl_forward(f), m0, m1, m2, m3);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, std::size_t R, std::size_t C,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3, vector_options O4,
			  std::invocable<T0, T1, T2, T3, T4> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   matrix<T1, R, C, O1> const& m1,
					   matrix<T2, R, C, O2> const& m2,
					   matrix<T3, R, C, O3> const& m3,
					   matrix<T4, R, C, O4> const& m4,
					   F&& f)
	{
		return __map_impl(__mtl_forward(f), m0, m1, m2, m3, m4);
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, std::size_t R, std::size_t C,
			  vector_options O0, vector_options O1, vector_options O2, vector_options O3, vector_options O4, vector_options O5,
			  std::invocable<T0, T1, T2, T3, T4, T5> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr auto map(matrix<T0, R, C, O0> const& m0,
					   matrix<T1, R, C, O1> const& m1,
					   matrix<T2, R, C, O2> const& m2,
					   matrix<T3, R, C, O3> const& m3,
					   matrix<T4, R, C, O4> const& m4,
					   matrix<T5, R, C, O5> const& m5,
					   F&& f)
	{
		return __map_impl(__mtl_forward(f), m0, m1, m2, m3, m4, m5);
	}
	
	/// MARK: Fold
	template <typename T, std::size_t R, std::size_t C, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T left_fold(matrix<T, R, C, O> const& m, F&& f) {
		return __mtl_with_index_sequence((I, R * C), {
			return __left_fold_impl(f, m.__mtl_at(I)...);
		});
	}
	
	template <typename T, std::size_t R, std::size_t C, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T right_fold(matrix<T, R, C, O> const& m, F&& f) {
		return __mtl_with_index_sequence((I, R * C), {
			return __left_fold_impl(f, m.__mtl_at(R * C - 1 - I)...);
		});
	}
	
	template <typename T, std::size_t R, std::size_t C, vector_options O, _VMTL::invocable_r<T, T, T> F>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T fold(matrix<T, R, C, O> const& m, F&& f) {
		return _VMTL::left_fold(m, __mtl_forward(f));
	}
	
	/// MARK: - struct __matrix_data
	template <typename T, std::size_t Rows, std::size_t Columns, bool Packed>
	struct __matrix_data;
	
	constexpr std::size_t __calculate_aligned_size(std::size_t S) {
		return S == 3 ? 4 : S;
	}
	
	constexpr std::size_t __calculate_columns_in_data(std::size_t C, vector_options O) {
		return O.packed() ? C : __calculate_aligned_size(C);
	}
	
	/// MARK: Size = N x N
	template <typename T, std::size_t Rows, std::size_t Columns, bool Packed>
	struct __matrix_data {
		static constexpr std::size_t __columns_in_data = Columns;
		static constexpr std::size_t __size_in_data = Rows * Columns;
		union {
			T __data[__size_in_data];
			__simd_type_t<T, Columns, Packed> __vec[Rows];
		};
		
		__mtl_always_inline
		constexpr T& __mtl_at(std::size_t i)& {
			__mtl_assert_audit(i < Rows * Columns);
			return __data[i];
		}
		__mtl_always_inline
		constexpr T const& __mtl_at(std::size_t i) const& {
			__mtl_assert_audit(i < Rows * Columns);
			return __data[i];
		}
		__mtl_always_inline
		constexpr T&& __mtl_at(std::size_t i)&& {
			__mtl_assert_audit(i < Rows * Columns);
			return (T&&)(__data[i]);
		}
		__mtl_always_inline
		constexpr T const&& __mtl_at(std::size_t i) const&& {
			__mtl_assert_audit(i < Rows * Columns);
			return (T const&&)(__data[i]);
		}
		
		__mtl_always_inline
		constexpr T __mtl_vec_at(std::size_t i) const {
			__mtl_assert_audit(i < Rows * Columns);
			return __vec[i / Columns][i % Columns];
		}
		
		__mtl_always_inline
		constexpr T& __mtl_at(std::size_t i, std::size_t j)& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < Columns);
			return __data[i * Columns + j];
		}
		__mtl_always_inline
		constexpr T const& __mtl_at(std::size_t i, std::size_t j) const& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < Columns);
			return __data[i * Columns + j];
		}
		__mtl_always_inline
		constexpr T&& __mtl_at(std::size_t i, std::size_t j)&& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < Columns);
			return (T&&)(__data[i * Columns + j]);
		}
		__mtl_always_inline
		constexpr T const&& __mtl_at(std::size_t i, std::size_t j) const&& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < Columns);
			return (T const&&)(__data[i * Columns + j]);
		}
		
		__mtl_always_inline
		constexpr T __mtl_vec_at(std::size_t i, std::size_t j) const {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < Columns);
			return __vec[i][j];
		}
	};
	
	/// MARK: Size = N x 3, Packed = false
	/// Only this case is special, since we only properly support up to 4x4 matrices.
	template <typename T, std::size_t Rows>
	struct __matrix_data<T, Rows, 3, false> {
		static constexpr std::size_t __columns_in_data = 4;
		static constexpr std::size_t __size_in_data = __columns_in_data * Rows;
		union {
			T __data[__size_in_data];
			__simd_type_t<T, 4, false> __vec[Rows];
		};
		__mtl_pure __mtl_always_inline
		static constexpr std::size_t __index(std::size_t i, std::size_t j) {
			return i * 4 + j;
		}
		
		__mtl_always_inline
		constexpr T& __mtl_at(std::size_t index)& {
			__mtl_assert_audit(index < Rows * 3);
			return __data[__index(index / 3, index % 3)];
		}
		__mtl_always_inline
		constexpr T const& __mtl_at(std::size_t index) const& {
			__mtl_assert_audit(index < Rows * 3);
			return __data[__index(index / 3, index % 3)];
		}
		__mtl_always_inline
		constexpr T&& __mtl_at(std::size_t index)&& {
			__mtl_assert_audit(index < Rows * 3);
			return (T&&)(__data[__index(index / 3, index % 3)]);
		}
		__mtl_always_inline
		constexpr T const&& __mtl_at(std::size_t index) const&& {
			__mtl_assert_audit(index < Rows * 3);
			return (T const&&)(__data[__index(index / 3, index % 3)]);
		}
		
		__mtl_always_inline
		constexpr T __mtl_vec_at(std::size_t index) const {
			__mtl_assert_audit(index < Rows * 3);
			return __vec[index / 3][index % 3];
		}
		
		__mtl_always_inline
		constexpr T& __mtl_at(std::size_t i, std::size_t j)& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < 3);
			return __data[__index(i, j)];
		}
		__mtl_always_inline
		constexpr T const& __mtl_at(std::size_t i, std::size_t j) const& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < 3);
			return __data[__index(i, j)];
		}
		__mtl_always_inline
		constexpr T&& __mtl_at(std::size_t i, std::size_t j)&& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < 3);
			return (T&&)(__data[__index(i, j)]);
		}
		__mtl_always_inline
		constexpr T const&& __mtl_at(std::size_t i, std::size_t j) const&& {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < 3);
			return (T const&&)(__data[__index(i, j)]);
		}
		
		__mtl_always_inline
		constexpr T __mtl_vec_at(std::size_t i, std::size_t j) const {
			__mtl_assert_audit(i < Rows);
			__mtl_assert_audit(j < 3);
			return __vec[i][j];
		}
		
		__matrix_data() = default;
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12) requires(Rows == 2):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22) requires(Rows == 3):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22,
								T const& _30, T const& _31, T const& _32) requires(Rows == 4):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0,
				_30, _31, _32, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22,
								T const& _30, T const& _31, T const& _32,
								T const& _40, T const& _41, T const& _42) requires(Rows == 5):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0,
				_30, _31, _32, 0,
				_40, _41, _42, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22,
								T const& _30, T const& _31, T const& _32,
								T const& _40, T const& _41, T const& _42,
								T const& _50, T const& _51, T const& _52) requires(Rows == 6):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0,
				_30, _31, _32, 0,
				_40, _41, _42, 0,
				_50, _51, _52, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22,
								T const& _30, T const& _31, T const& _32,
								T const& _40, T const& _41, T const& _42,
								T const& _50, T const& _51, T const& _52,
								T const& _60, T const& _61, T const& _62) requires(Rows == 7):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0,
				_30, _31, _32, 0,
				_40, _41, _42, 0,
				_50, _51, _52, 0,
				_60, _61, _62, 0
			}
		{}
		__mtl_always_inline
		constexpr __matrix_data(T const& _00, T const& _01, T const& _02,
								T const& _10, T const& _11, T const& _12,
								T const& _20, T const& _21, T const& _22,
								T const& _30, T const& _31, T const& _32,
								T const& _40, T const& _41, T const& _42,
								T const& _50, T const& _51, T const& _52,
								T const& _60, T const& _61, T const& _62,
								T const& _70, T const& _71, T const& _72) requires(Rows == 8):
			__data{
				_00, _01, _02, 0,
				_10, _11, _12, 0,
				_20, _21, _22, 0,
				_30, _31, _32, 0,
				_40, _41, _42, 0,
				_50, _51, _52, 0,
				_60, _61, _62, 0,
				_70, _71, _72, 0
			}
		{}
	};
	

	/// MARK: - struct __matrix_base
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O,
			  typename AllT     = __mtl_make_type_sequence <T, Rows * Columns>,
			  typename AllI     = __mtl_make_index_sequence<Rows * Columns>,
			  typename RowT     = __mtl_make_type_sequence <T, Rows>,
			  typename RowI     = __mtl_make_index_sequence<Rows>,
			  typename ColumnT  = __mtl_make_type_sequence <T, Columns>,
			  typename ColumnI  = __mtl_make_index_sequence<Columns>,
			  typename DiagT    = __mtl_make_type_sequence <T, _VMTL::min(Rows, Columns)>,
			  typename DiagI    = __mtl_make_index_sequence<_VMTL::min(Rows, Columns)>
	>
	struct __matrix_base;
	
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O,
			  typename...    AllT,
			  std::size_t... AllI,
			  typename...    RowT,
			  std::size_t... RowI,
			  typename...    ColumnT,
			  std::size_t... ColumnI,
			  typename...    DiagT,
			  std::size_t... DiagI
	>
	struct alignas(__calculate_alignment(alignof(T), Columns, O.packed()))
	__matrix_base<T, Rows, Columns, O,
			      __mtl_type_sequence <AllT...>,
			      __mtl_index_sequence<AllI...>,
				  __mtl_type_sequence <RowT...>,
				  __mtl_index_sequence<RowI...>,
			      __mtl_type_sequence <ColumnT...>,
				  __mtl_index_sequence<ColumnI...>,
				  __mtl_type_sequence <DiagT...>,
				  __mtl_index_sequence<DiagI...>
	>: public __matrix_data<T, Rows, Columns, O.packed()>
	{
	public:
		using __mtl_base = __matrix_data<T, Rows, Columns, O.packed()>;
		using __mtl_base::__mtl_at;
		
		using row_type    = vector<T, Columns, O>;
		using column_type = vector<T, Rows, O>;
		
	public:
		/// MARK: Public Interface
		/// Value Constructors
		__mtl_interface_export
		__matrix_base() = default;
		__mtl_always_inline __mtl_interface_export
		constexpr __matrix_base(T x):
			__mtl_base{
				(AllI / Columns == AllI % Columns ? x : T(0))...
			} {}
		__mtl_always_inline __mtl_interface_export
		constexpr __matrix_base(AllT... x): __mtl_base{ x... } {}
		__mtl_always_inline __mtl_interface_export
		constexpr __matrix_base(rows_tag, vector<RowT, Columns, O> const&... rows): __mtl_base{}
		{
			([&](std::size_t j){
				((__mtl_at(RowI, j) = rows[j]), ...);
			}(ColumnI), ...);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr __matrix_base(columns_tag, vector<ColumnT, Rows, O> const&... columns): __mtl_base{}
		{
			([&](std::size_t j){
				((__mtl_at(j, ColumnI) = columns[j]), ...);
			}(RowI), ...);
		}
		
		/// Functional Constructors
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __matrix_base(_VMTL::invocable_r<T> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f)>):
			__mtl_base{ ((void)AllI, (T)std::invoke(f))... } {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __matrix_base(_VMTL::invocable_r<T, std::size_t> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f), std::size_t>):
			__mtl_base{ (T)std::invoke(f, AllI)... } {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __matrix_base(_VMTL::invocable_r<T, std::size_t, std::size_t> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f), std::size_t, std::size_t>):
			__mtl_base{
				(T)std::invoke(f, AllI / Columns, AllI % Columns)...
		} {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __matrix_base(rows_tag, _VMTL::invocable_r<row_type, std::size_t> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f), std::size_t>):
			__matrix_base(rows, std::invoke(f, RowI)...) {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr __matrix_base(columns_tag, _VMTL::invocable_r<column_type, std::size_t> auto&& f) noexcept(std::is_nothrow_invocable_v<decltype(f), std::size_t>):
			__matrix_base(columns, std::invoke(f, ColumnI)...) {}
		
		/// Conversion Constructor
		template <std::convertible_to<T> U, vector_options P>
		__mtl_always_inline __mtl_interface_export
		constexpr __matrix_base(matrix<U, Rows, Columns, P> const& rhs): __mtl_base{ static_cast<T>(rhs.__mtl_at(AllI))... } {}
		
		/// set_row, set_column
		__mtl_always_inline __mtl_interface_export
		constexpr matrix<T, Rows, Columns, O>& set_row(std::size_t i, RowT const&... row) {
			__mtl_bounds_check(i, 0, Rows);
			((this->__mtl_at(i, RowI) = row), ...);
			return (matrix<T, Rows, Columns, O>&)*this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr matrix<T, Rows, Columns, O>& set_column(std::size_t j, ColumnT const&... column) {
			__mtl_bounds_check(j, 0, Columns);
			((this->__mtl_at(ColumnI, j) = column), ...);
			return (matrix<T, Rows, Columns, O>&)*this;
		}
		
		/// Static Functions
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr matrix<T, Rows, Columns, O> diag(T value) {
			return { value };
		}
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr matrix<T, Rows, Columns, O> diag(vector<T, _VMTL::min(Rows, Columns), O> const& values) {
			return diag(values.__mtl_at(DiagI)...);
		}
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr matrix<T, Rows, Columns, O> diag(DiagT... value) {
			matrix<T, Rows, Columns, O> result{};
			std::size_t i = 0;
			(((void)(result.__mtl_at(i, i) = value), ++i), ...);
			return result;
		}
	};
	
	/// MARK: - struct matrix
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	struct matrix: public __matrix_base<T, Rows, Columns, O> {
		using __mtl_base = __matrix_base<T, Rows, Columns, O>;
		using __mtl_base::__columns_in_data;
		using __mtl_base::__size_in_data;
		using __mtl_base::__data;
		
		template <typename U>
		struct __iterator_base_special {
			U* __ptr_;
			std::size_t __row_index_ = 0;
		};
		template <typename U>
		struct __iterator_base {
			U* __ptr_;
		};
		
		template <typename U, bool IsSpecial = !O.packed() && Columns == 3>
		struct __iterator: std::conditional_t<IsSpecial, __iterator_base_special<U>, __iterator_base<U>>
		{
			using __mtl_base = std::conditional_t<IsSpecial, __iterator_base_special<U>, __iterator_base<U>>;
			using __mtl_base::__ptr_;
			__mtl_always_inline __mtl_interface_export
			constexpr __iterator(U* __ptr): __mtl_base{ __ptr } {}
			__mtl_always_inline __mtl_interface_export
			constexpr __iterator& operator++()& {
				if constexpr (IsSpecial) {
					if (++this->__row_index_ == 3) {
						this->__row_index_ = 0;
						++__ptr_;
					}
				}
				++__ptr_;
				return *this;
			}
			
			__mtl_always_inline __mtl_interface_export
			constexpr U& operator*() const
			{ return *__ptr_; }
			
			__mtl_always_inline __mtl_interface_export
			constexpr U* operator->() const { return __ptr_; }
			
			template <typename U_>
			requires(std::is_same_v<std::remove_cv_t<U>, std::remove_cv_t<U_>>)
			__mtl_always_inline __mtl_interface_export
			constexpr bool operator==(__iterator<U_> const& __that) const
			{ return this->__ptr_ == __that.__ptr_; }
		};
		
		using iterator       = __iterator<T>;
		using const_iterator = __iterator<T const>;
		
		/// MARK: Public Interface
		using value_type = T;
		using typename __mtl_base::row_type;
		using typename __mtl_base::column_type;
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    size()      { return Rows * Columns; }
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    data_size() { return __size_in_data; }
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    rows()      { return Rows; }
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr std::size_t    columns()   { return Columns; }
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr vector_options options()   { return O; }
		
		__mtl_mathfunction __mtl_always_inline __mtl_interface_export
		static constexpr matrix<T, Rows, Columns, O> unit(std::size_t i, std::size_t j, T const& value = 1) {
			__mtl_bounds_check(i, 0, Rows);
			__mtl_bounds_check(j, 0, Columns);
			matrix<T, Rows, Columns, O> result{};
			result.__mtl_at(i, j) = value;
			return result;
		}
		
		/// Inheriting interface from __matrix_base:
		using __mtl_base::__mtl_base;
		using __mtl_base::diag;
		
		matrix& operator=(matrix const&)& = default;
		
		/// operator[](std::size_t):
		__mtl_always_inline __mtl_interface_export
		constexpr T& operator[](std::size_t index)& {
			return const_cast<T&>(const_cast<matrix const&>(*this)[index]);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const& operator[](std::size_t index) const& {
			__mtl_bounds_check(index, 0, Rows * Columns);
			return this->__mtl_at(index);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T&& operator[](std::size_t index)&& {
			return std::move(this->operator[](index));
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const&& operator[](std::size_t index) const&& {
			return std::move(this->operator[](index));
		}
		/// operator[](usize2):
		__mtl_always_inline __mtl_interface_export
		constexpr T& operator[](usize2 index)& {
			return const_cast<T&>(const_cast<matrix const&>(*this)[index]);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const& operator[](usize2 index) const& {
			__mtl_bounds_check(index.__mtl_at(0), 0, Rows);
			__mtl_bounds_check(index.__mtl_at(1), 0, Columns);
			return this->__mtl_at(index.__mtl_at(0), index.__mtl_at(1));
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T&& operator[](size2 index)&& {
			return std::move(this->operator[](index));
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const&& operator[](size2 index) const&& {
			return std::move(this->operator[](index));
		}
		
		/// operator(): [As a substitute for multi argument subscript]
		__mtl_always_inline __mtl_interface_export
		constexpr T& operator()(std::size_t i, std::size_t j)& {
			return const_cast<T&>(const_cast<matrix const&>(*this)(i, j));
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const& operator()(std::size_t i, std::size_t j) const& {
			__mtl_bounds_check(i, 0, Rows);
			__mtl_bounds_check(j, 0, Columns);
			return this->__mtl_at(i, j);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T&& operator()(std::size_t i, std::size_t j)&& {
			return std::move(this->operator()(i, j));
		}
		__mtl_always_inline __mtl_interface_export
		constexpr T const&& operator()(std::size_t i, std::size_t j) const&& {
			return std::move(this->operator()(i, j));
		}
		
		/// row, column:
		__mtl_always_inline __mtl_interface_export
		constexpr row_type row(std::size_t i) const {
			__mtl_bounds_check(i, 0, Rows);
			return row_type([this, i](std::size_t j) { return this->__mtl_at(i, j); });
		}
		__mtl_always_inline __mtl_interface_export
		constexpr column_type column(std::size_t j) const {
			__mtl_bounds_check(j, 0, Columns);
			return column_type([this, j](std::size_t i) { return this->__mtl_at(i, j); });
		}
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& set_row(std::size_t i, row_type const& row) {
			__mtl_bounds_check(i, 0, Rows);
			__mtl_with_index_sequence((J, Columns), {
				((this->__mtl_at(i, J) = row.__mtl_at(J)), ...);
			});
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& set_column(std::size_t j, column_type const& column) {
			__mtl_bounds_check(j, 0, Columns);
			__mtl_with_index_sequence((I, Rows), {
				((this->__mtl_at(I, j) = column.__mtl_at(I)), ...);
			});
			return *this;
		}
		using __mtl_base::set_row;
		using __mtl_base::set_column;
		
		/// begin, end:
		__mtl_always_inline __mtl_interface_export
		constexpr iterator begin()              { return __data; }
		__mtl_always_inline __mtl_interface_export
		constexpr const_iterator begin()  const { return __data; }
		__mtl_always_inline __mtl_interface_export
		constexpr const_iterator cbegin() const { return __data; }
		__mtl_always_inline __mtl_interface_export
		constexpr iterator end()                { return __data + __size_in_data; }
		__mtl_always_inline __mtl_interface_export
		constexpr const_iterator end()  const   { return __data + __size_in_data; }
		__mtl_always_inline __mtl_interface_export
		constexpr const_iterator cend() const   { return __data + __size_in_data; }
		
		/// data
		__mtl_always_inline __mtl_interface_export
		constexpr T* data() { return this->__data; }
		__mtl_always_inline __mtl_interface_export
		constexpr T const* data() const { return this->__data; }
		
		/// swizzle:
		template <std::convertible_to<std::size_t>... I>
		__mtl_always_inline __mtl_interface_export
		constexpr matrix<T, sizeof...(I), Columns, O> row_swizzle(I... i) const
		requires(sizeof...(I) > 0)
		{
			return { _VMTL::rows, row(i)... };
		}
		template <std::convertible_to<std::size_t>... I>
		__mtl_always_inline __mtl_interface_export
		constexpr matrix<T, Rows, sizeof...(I), O> column_swizzle(I... i) const
		requires(sizeof...(I) > 0)
		{
			return { _VMTL::columns, column(i)... };
		}
		
		/// Map
		__mtl_always_inline __mtl_interface_export
		constexpr auto map(std::invocable<T> auto&& f) const { return _VMTL::map(*this, __mtl_forward(f)); }
		
		/// Fold
		__mtl_always_inline __mtl_interface_export
		constexpr T fold(_VMTL::invocable_r<T, T, T> auto&& f) const { return _VMTL::fold(*this, __mtl_forward(f)); }
		
		/// MARK: Arithmetic Assignment
		/// this + Matrix
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator+=(matrix const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		/// this - Matrix
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator-=(matrix const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		/// this * Matrix
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator*=(matrix<T, Columns, Columns, O> const& rhs)&
		{
			*this = *this * rhs;
			return *this;
		}
		/// this * Scalar
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator*=(T const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		/// this / Scalar
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator/=(T const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
		/// this % Scalar
		__mtl_always_inline __mtl_interface_export
		constexpr matrix& operator%=(T const& rhs)& requires(std::is_integral_v<T>) {
			*this = *this % rhs;
			return *this;
		}
		
		/// MARK: Matrix<bool> Members
		__mtl_always_inline __mtl_interface_export
		constexpr bool all() const requires std::convertible_to<T, bool> {
			return fold(__mtl_logical_and);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr bool any() const requires std::convertible_to<T, bool> {
			return fold(__mtl_logical_or);
		}
		__mtl_always_inline __mtl_interface_export
		constexpr auto operator!() const requires requires(T&& t) { !t; } {
			return map(__mtl_logical_not);
		}
		
		/// MARK: Min, Max
		__mtl_always_inline __mtl_interface_export
		constexpr T min() const requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Rows * Columns), {
				return min(this->__mtl_at(I)...);
			});
		}
		
		__mtl_always_inline __mtl_interface_export
		constexpr T max() const requires real_scalar<T> {
			return __mtl_with_index_sequence((I, Rows * Columns), {
				return max(this->__mtl_at(I)...);
			});
		}

	};
 
	/// MARK: - Operators
	template <typename T, typename U = T, std::size_t Rows, std::size_t Columns, vector_options O, vector_options P = O>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(matrix<T, Rows, Columns, O> const& m,
							  matrix<U, Rows, Columns, P> const& n)
	{
		return _VMTL::fold(_VMTL::map(m, n, _VMTL::__mtl_equals), _VMTL::__mtl_logical_and);
	}
	
	template <typename T, scalar U, std::size_t Rows, std::size_t Columns, vector_options O>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(matrix<T, Rows, Columns, O> const& m,
							  U const& x)
	{
		return m == _VMTL::matrix<U, Rows, Columns, O>(x);
	}
	
	template <scalar T, typename U, std::size_t Rows, std::size_t Columns, vector_options O>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(T const& x,
							  matrix<U, Rows, Columns, O> const& m)
	{
		return m == x;
	}
	
	template <typename CharT, typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	requires std::is_arithmetic_v<T> && requires(T&& t, std::ostream& str) { { str << t } -> std::convertible_to<std::ostream&>; }
	__mtl_interface_export
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& str, matrix<T, Rows, Columns, O> const& m) {
		std::basic_stringstream<CharT> s;
		std::size_t len[Columns]{};
		// hacky way to iterate over a matrix
		(void)matrix<char, Rows, Columns, O>([&](std::size_t i, std::size_t j) {
			s << m(i, j);
			len[j] = max(s.str().size(), len[j]);
			s.str({});
			return 0;
		});
		constexpr CharT const* brackets[6] = {
#if MTL_UNICODE_MATH_PARANTHESES
			"⎛", "⎜", "⎝", "⎞", "⎥", "⎠"
#else // MTL_UNICODE_MATH_PARANTHESES
			"|", "|", "|", "|", "|", "|"
#endif // MTL_UNICODE_MATH_PARANTHESES
		};
		vector<CharT const*, Rows> left_bracket = brackets[1];
		left_bracket[0] = brackets[0];
		left_bracket[Rows - 1] = brackets[2];
		vector<CharT const*, Rows> right_bracket = brackets[4];
		right_bracket[0] = brackets[3];
		right_bracket[Rows - 1] = brackets[5];
		
		for (std::size_t i = 0; i < Rows; ++i) {
			str << left_bracket[i];
			bool first = true;
			for (std::size_t j = 0; j < Columns; ++j) {
				str << (first ? ((void)(first = false), "") : "  ") << std::setw(len[j]) << m(i, j);
			}
			str << right_bracket[i] << (i == Rows - 1 ? "" : "\n");
		}
		return str;
	}

	/// MARK: - Generic Matrix Functions
	/// Transpose
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options Options>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<T, Columns, Rows, Options> transpose(matrix<T, Rows, Columns, Options> const& m) {
		return matrix<T, Columns, Rows, Options>([&](std::size_t i, std::size_t j) {
			return m.__mtl_at(j, i);
		});
	}
	
	/// Conjugate Transpose
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options Options>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<T, Columns, Rows, Options> conj_transpose(matrix<T, Rows, Columns, Options> const& m) {
		return matrix<T, Columns, Rows, Options>([&](std::size_t i, std::size_t j) {
			return conj(m.__mtl_at(j, i));
		});
	}
	
	/// Submatrix
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	matrix<T, Rows - 1, Columns - 1, O> submatrix(matrix<T, Rows, Columns, O> const& m,
												  std::size_t x, std::size_t y)
	{
		__mtl_bounds_check(x, 0, Rows);
		__mtl_bounds_check(y, 0, Columns);
		return matrix<T, Rows - 1, Columns - 1, O>([&](std::size_t i, std::size_t j) {
			return m.__mtl_at(i + (i >= x), j + (j >= y));
		});
	};
	
	/// Type Cast
	template <typename To, typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<To, Rows, Columns, O> type_cast(matrix<T, Rows, Columns, O> const& v) {
		return matrix<To, Rows, Columns, O>([&](std::size_t i, std::size_t j) {
			return static_cast<To>(v.__mtl_at(i, j));
		});
	}
	
	/// Dimension Cast
	template <std::size_t ToRows, std::size_t ToColumns, typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr matrix<T, ToRows, ToColumns, O> dimension_cast(matrix<T, Rows, Columns, O> const& v) {
		return matrix<T, ToRows, ToColumns, O>([&](std::size_t i, std::size_t j) {
			return i < Rows && j < Columns ? v.__mtl_at(i, j) : T(0);
		});
	}

	/// isnan
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr matrix<bool, Rows, Columns, O> isnan(matrix<T, Rows, Columns, O> const& m) {
		return matrix<bool, Rows, Columns, O>([&](std::size_t i) {
			using std::isnan;
			return isnan(m.__mtl_at(i));
		});
	}
	
	/// isinf
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr matrix<bool, Rows, Columns, O> isinf(matrix<T, Rows, Columns, O> const& m) {
		return matrix<bool, Rows, Columns, O>([&](std::size_t i) {
			using std::isinf;
			return isinf(m.__mtl_at(i));
		});
	}
	
	/// isfinite
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr matrix<bool, Rows, Columns, O> isfinite(matrix<T, Rows, Columns, O> const& m) {
		return matrix<bool, Rows, Columns, O>([&](std::size_t i) {
			using std::isfinite;
			return isfinite(m.__mtl_at(i));
		});
	}
	
	/// isnormal
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr matrix<bool, Rows, Columns, O> isnormal(matrix<T, Rows, Columns, O> const& m) {
		return matrix<bool, Rows, Columns, O>([&](std::size_t i) {
			using std::isnormal;
			return isnormal(m.__mtl_at(i));
		});
	}
	
	/// MARK: - Matrix Math Functions
	/// Row Sum Norm
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr auto row_sum_norm(matrix<T, Rows, Columns, O> const& m) {
		return __mtl_with_index_sequence((I, Columns), {
			return max(sum_norm(m.row(I))...);
		});
	}
	
	/// Column Sum Norm
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr auto column_sum_norm(matrix<T, Rows, Columns, O> const& m) {
		return __mtl_with_index_sequence((I, Columns), {
			return max(sum_norm(m.column(I))...);
		});
	}
	
	/// Maximum Norm
	template <typename T, std::size_t Rows, std::size_t Columns, vector_options O>
	constexpr auto max_norm(matrix<T, Rows, Columns, O> const& m) {
		return __mtl_with_index_sequence((I, Rows * Columns), {
			using std::abs;
			return max(abs(m.__mtl_at(I))...);
		});
	}
	
	/// Determinant
	template <scalar T, vector_options O>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T det(matrix2x2<T, O> const& A) {
		return A.__mtl_at(0) * A.__mtl_at(3) - A.__mtl_at(2) * A.__mtl_at(1);
	}
	template <scalar T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr T det(matrix3x3<T, O> const& A) {
		return A.__mtl_at(0, 0) * (A.__mtl_at(1, 1) * A.__mtl_at(2, 2) - A.__mtl_at(2, 1) * A.__mtl_at(1, 2)) -
			   A.__mtl_at(0, 1) * (A.__mtl_at(1, 0) * A.__mtl_at(2, 2) - A.__mtl_at(1, 2) * A.__mtl_at(2, 0)) +
			   A.__mtl_at(0, 2) * (A.__mtl_at(1, 0) * A.__mtl_at(2, 1) - A.__mtl_at(1, 1) * A.__mtl_at(2, 0));
	}
	template <scalar T, std::size_t N, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr T det(matrix<T, N, N, O> const& m) {
		auto constexpr sign = [](std::size_t i, std::size_t j) {
			return (int)((i + j + 1) % 2) * 2 - 1;
		};
		return __mtl_with_index_sequence((I, N), {
			return  ((m.__mtl_at(I, 0) * sign(I, 0) * _VMTL::det(submatrix(m, I, 0))) + ...);
		});
	}
	
	/// Trace
	template <scalar T, std::size_t N, vector_options O>
	constexpr T trace(matrix<T, N, N, O> const& m) {
		return __mtl_with_index_sequence((I, N), {
			return (m.__mtl_at(I, I) + ...);
		});
	}
	
	/// Inverse
	template <scalar T, vector_options O>
	constexpr matrix2x2<T, O> __mtl_inverse(matrix2x2<T, O> const& m) {
		T const d = det(m);
		__mtl_expect(__mtl_is_unit(d));
		return matrix2x2<T, O>{
			 m.__mtl_at(3), -m.__mtl_at(1),
			-m.__mtl_at(2),  m.__mtl_at(0)
		} / d;
	}
	template <scalar T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix2x2<__mtl_floatify(T), O> inverse(matrix2x2<T, O> const& m) {
		if constexpr (std::is_floating_point_v<T>) {
			return __mtl_inverse(m);
		}
		else {
			return __mtl_inverse(type_cast<__mtl_floatify(T)>(m));
		}
	}
	template <typename T, vector_options O> requires (std::is_integral_v<T>)
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix2x2<__mtl_floatify(T), O> integral_inverse(matrix2x2<T, O> const& m) {
		return __mtl_inverse(m);
	}
	template <scalar T, vector_options O>
	constexpr matrix3x3<T, O> __mtl_inverse(matrix3x3<T, O> const& m) {
		T const d = det(m);
		__mtl_expect(__mtl_is_unit(d));
		return matrix3x3<T, O>{
			m.__mtl_at(1, 1) * m.__mtl_at(2, 2) - m.__mtl_at(2, 1) * m.__mtl_at(1, 2),
			m.__mtl_at(0, 2) * m.__mtl_at(2, 1) - m.__mtl_at(0, 1) * m.__mtl_at(2, 2),
			m.__mtl_at(0, 1) * m.__mtl_at(1, 2) - m.__mtl_at(0, 2) * m.__mtl_at(1, 1),
			m.__mtl_at(1, 2) * m.__mtl_at(2, 0) - m.__mtl_at(1, 0) * m.__mtl_at(2, 2),
			m.__mtl_at(0, 0) * m.__mtl_at(2, 2) - m.__mtl_at(0, 2) * m.__mtl_at(2, 0),
			m.__mtl_at(1, 0) * m.__mtl_at(0, 2) - m.__mtl_at(0, 0) * m.__mtl_at(1, 2),
			m.__mtl_at(1, 0) * m.__mtl_at(2, 1) - m.__mtl_at(2, 0) * m.__mtl_at(1, 1),
			m.__mtl_at(2, 0) * m.__mtl_at(0, 1) - m.__mtl_at(0, 0) * m.__mtl_at(2, 1),
			m.__mtl_at(0, 0) * m.__mtl_at(1, 1) - m.__mtl_at(1, 0) * m.__mtl_at(0, 1)
		} / d;
	}
	template <scalar T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix3x3<__mtl_floatify(T), O> inverse(matrix3x3<T, O> const& m) {
		if constexpr (std::is_floating_point_v<T>) {
			return __mtl_inverse(m);
		}
		else {
			return __mtl_inverse(type_cast<__mtl_floatify(T)>(m));
		}
	}
	template <typename T, vector_options O> requires (std::is_integral_v<T>)
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix3x3<__mtl_floatify(T), O> integral_inverse(matrix3x3<T, O> const& m) {
		return __mtl_inverse(m);
	}
	template <scalar T, vector_options O>
	constexpr matrix4x4<T, O> __mtl_inverse(matrix4x4<T, O> const& m) {
		matrix4x4<T, O> const int_result = {
			m.__mtl_at( 5) * m.__mtl_at(10) * m.__mtl_at(15) -
			m.__mtl_at( 5) * m.__mtl_at(11) * m.__mtl_at(14) -
			m.__mtl_at( 9) * m.__mtl_at( 6) * m.__mtl_at(15) +
			m.__mtl_at( 9) * m.__mtl_at( 7) * m.__mtl_at(14) +
			m.__mtl_at(13) * m.__mtl_at( 6) * m.__mtl_at(11) -
			m.__mtl_at(13) * m.__mtl_at( 7) * m.__mtl_at(10),
			
			-m.__mtl_at( 1)  * m.__mtl_at(10) * m.__mtl_at(15) +
			 m.__mtl_at( 1)  * m.__mtl_at(11) * m.__mtl_at(14) +
			 m.__mtl_at( 9)  * m.__mtl_at( 2) * m.__mtl_at(15) -
			 m.__mtl_at( 9)  * m.__mtl_at( 3) * m.__mtl_at(14) -
			 m.__mtl_at(13)  * m.__mtl_at( 2) * m.__mtl_at(11) +
			 m.__mtl_at(13)  * m.__mtl_at( 3) * m.__mtl_at(10),

			m.__mtl_at( 1) * m.__mtl_at(6) * m.__mtl_at(15) -
			m.__mtl_at( 1) * m.__mtl_at(7) * m.__mtl_at(14) -
			m.__mtl_at( 5) * m.__mtl_at(2) * m.__mtl_at(15) +
			m.__mtl_at( 5) * m.__mtl_at(3) * m.__mtl_at(14) +
			m.__mtl_at(13) * m.__mtl_at(2) * m.__mtl_at( 7) -
			m.__mtl_at(13) * m.__mtl_at(3) * m.__mtl_at( 6),
			
			-m.__mtl_at(1) * m.__mtl_at(6) * m.__mtl_at(11) +
			 m.__mtl_at(1) * m.__mtl_at(7) * m.__mtl_at(10) +
			 m.__mtl_at(5) * m.__mtl_at(2) * m.__mtl_at(11) -
			 m.__mtl_at(5) * m.__mtl_at(3) * m.__mtl_at(10) -
			 m.__mtl_at(9) * m.__mtl_at(2) * m.__mtl_at( 7) +
			 m.__mtl_at(9) * m.__mtl_at(3) * m.__mtl_at( 6),
			
			-m.__mtl_at(4)  * m.__mtl_at(10) * m.__mtl_at(15) +
			 m.__mtl_at(4)  * m.__mtl_at(11) * m.__mtl_at(14) +
			 m.__mtl_at(8)  * m.__mtl_at( 6) * m.__mtl_at(15) -
			 m.__mtl_at(8)  * m.__mtl_at( 7) * m.__mtl_at(14) -
			 m.__mtl_at(12) * m.__mtl_at( 6) * m.__mtl_at(11) +
			 m.__mtl_at(12) * m.__mtl_at( 7) * m.__mtl_at(10),
			
			m.__mtl_at( 0) * m.__mtl_at(10) * m.__mtl_at(15) -
			m.__mtl_at( 0) * m.__mtl_at(11) * m.__mtl_at(14) -
			m.__mtl_at( 8) * m.__mtl_at( 2) * m.__mtl_at(15) +
			m.__mtl_at( 8) * m.__mtl_at( 3) * m.__mtl_at(14) +
			m.__mtl_at(12) * m.__mtl_at( 2) * m.__mtl_at(11) -
			m.__mtl_at(12) * m.__mtl_at( 3) * m.__mtl_at(10),
			
			-m.__mtl_at( 0) * m.__mtl_at(6) * m.__mtl_at(15) +
			 m.__mtl_at( 0) * m.__mtl_at(7) * m.__mtl_at(14) +
			 m.__mtl_at( 4) * m.__mtl_at(2) * m.__mtl_at(15) -
			 m.__mtl_at( 4) * m.__mtl_at(3) * m.__mtl_at(14) -
			 m.__mtl_at(12) * m.__mtl_at(2) * m.__mtl_at( 7) +
			 m.__mtl_at(12) * m.__mtl_at(3) * m.__mtl_at( 6),
			
			m.__mtl_at(0) * m.__mtl_at(6) * m.__mtl_at(11) -
			m.__mtl_at(0) * m.__mtl_at(7) * m.__mtl_at(10) -
			m.__mtl_at(4) * m.__mtl_at(2) * m.__mtl_at(11) +
			m.__mtl_at(4) * m.__mtl_at(3) * m.__mtl_at(10) +
			m.__mtl_at(8) * m.__mtl_at(2) * m.__mtl_at( 7) -
			m.__mtl_at(8) * m.__mtl_at(3) * m.__mtl_at( 6),


			m.__mtl_at( 4) * m.__mtl_at( 9) * m.__mtl_at(15) -
			m.__mtl_at( 4) * m.__mtl_at(11) * m.__mtl_at(13) -
			m.__mtl_at( 8) * m.__mtl_at( 5) * m.__mtl_at(15) +
			m.__mtl_at( 8) * m.__mtl_at( 7) * m.__mtl_at(13) +
			m.__mtl_at(12) * m.__mtl_at( 5) * m.__mtl_at(11) -
			m.__mtl_at(12) * m.__mtl_at( 7) * m.__mtl_at( 9),
			
			-m.__mtl_at( 0) * m.__mtl_at( 9) * m.__mtl_at(15) +
			 m.__mtl_at( 0) * m.__mtl_at(11) * m.__mtl_at(13) +
			 m.__mtl_at( 8) * m.__mtl_at( 1) * m.__mtl_at(15) -
			 m.__mtl_at( 8) * m.__mtl_at( 3) * m.__mtl_at(13) -
			 m.__mtl_at(12) * m.__mtl_at( 1) * m.__mtl_at(11) +
			 m.__mtl_at(12) * m.__mtl_at( 3) * m.__mtl_at( 9),
			
			m.__mtl_at( 0) * m.__mtl_at(5) * m.__mtl_at(15) -
			m.__mtl_at( 0) * m.__mtl_at(7) * m.__mtl_at(13) -
			m.__mtl_at( 4) * m.__mtl_at(1) * m.__mtl_at(15) +
			m.__mtl_at( 4) * m.__mtl_at(3) * m.__mtl_at(13) +
			m.__mtl_at(12) * m.__mtl_at(1) * m.__mtl_at( 7) -
			m.__mtl_at(12) * m.__mtl_at(3) * m.__mtl_at( 5),
			
			-m.__mtl_at(0) * m.__mtl_at(5) * m.__mtl_at(11) +
			 m.__mtl_at(0) * m.__mtl_at(7) * m.__mtl_at( 9) +
			 m.__mtl_at(4) * m.__mtl_at(1) * m.__mtl_at(11) -
			 m.__mtl_at(4) * m.__mtl_at(3) * m.__mtl_at( 9) -
			 m.__mtl_at(8) * m.__mtl_at(1) * m.__mtl_at( 7) +
			 m.__mtl_at(8) * m.__mtl_at(3) * m.__mtl_at( 5),

			-m.__mtl_at( 4) * m.__mtl_at( 9) * m.__mtl_at(14) +
			 m.__mtl_at( 4) * m.__mtl_at(10) * m.__mtl_at(13) +
			 m.__mtl_at( 8) * m.__mtl_at( 5) * m.__mtl_at(14) -
			 m.__mtl_at( 8) * m.__mtl_at( 6) * m.__mtl_at(13) -
			 m.__mtl_at(12) * m.__mtl_at( 5) * m.__mtl_at(10) +
			 m.__mtl_at(12) * m.__mtl_at( 6) * m.__mtl_at( 9),

			m.__mtl_at( 0) * m.__mtl_at( 9) * m.__mtl_at(14) -
			m.__mtl_at( 0) * m.__mtl_at(10) * m.__mtl_at(13) -
			m.__mtl_at( 8) * m.__mtl_at( 1) * m.__mtl_at(14) +
			m.__mtl_at( 8) * m.__mtl_at( 2) * m.__mtl_at(13) +
			m.__mtl_at(12) * m.__mtl_at( 1) * m.__mtl_at(10) -
			m.__mtl_at(12) * m.__mtl_at( 2) * m.__mtl_at( 9),

			-m.__mtl_at( 0) * m.__mtl_at(5) * m.__mtl_at(14) +
			 m.__mtl_at( 0) * m.__mtl_at(6) * m.__mtl_at(13) +
			 m.__mtl_at( 4) * m.__mtl_at(1) * m.__mtl_at(14) -
			 m.__mtl_at( 4) * m.__mtl_at(2) * m.__mtl_at(13) -
			 m.__mtl_at(12) * m.__mtl_at(1) * m.__mtl_at( 6) +
			 m.__mtl_at(12) * m.__mtl_at(2) * m.__mtl_at( 5),

			m.__mtl_at(0) * m.__mtl_at(5) * m.__mtl_at(10) -
			m.__mtl_at(0) * m.__mtl_at(6) * m.__mtl_at( 9) -
			m.__mtl_at(4) * m.__mtl_at(1) * m.__mtl_at(10) +
			m.__mtl_at(4) * m.__mtl_at(2) * m.__mtl_at( 9) +
			m.__mtl_at(8) * m.__mtl_at(1) * m.__mtl_at( 6) -
			m.__mtl_at(8) * m.__mtl_at(2) * m.__mtl_at( 5)
		};
					
		T const d = m.__mtl_at(0) * int_result.__mtl_at(0) + m.__mtl_at(1) * int_result.__mtl_at(4) + m.__mtl_at(2) * int_result.__mtl_at(8) + m.__mtl_at(3) * int_result.__mtl_at(12);

		__mtl_expect(__mtl_is_unit(d));
		
		return int_result / d;
	}
	template <scalar T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<__mtl_floatify(T), O> inverse(matrix4x4<T, O> const& m) {
		if constexpr (std::is_floating_point_v<T>) {
			return __mtl_inverse(m);
		}
		else {
			return __mtl_inverse(type_cast<__mtl_floatify(T)>(m));
		}
	}
	template <typename T, vector_options O> requires (std::is_integral_v<T>)
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<__mtl_floatify(T), O> integral_inverse(matrix4x4<T, O> const& m) {
		return __mtl_inverse(m);
	}
	
}

#endif // __MTL_MATRIX_HPP_INCLUDED__

#pragma once

/// __complex.hpp

#ifndef __MTL_COMPLEX_HPP_INCLUDED__
#define __MTL_COMPLEX_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_


#define __MTL_DECLARE_COMPLEX_TYPEDEFS__
/// __typedefs.hpp

/// DELIBERATELY NO INCLUDE GUARDS! Sections have their own include guards.


_MTL_SYSTEM_HEADER_


	
#ifdef __MTL_DECLARE_STDINT_TYPEDEFS__
#ifndef __MTL_STDINT_TYPEDEFS_INCLUDED__
#define __MTL_STDINT_TYPEDEFS_INCLUDED__
	
#include <cstdint>

namespace _VMTL {
	
	/**
	 These exist so I can conditionally declare 'namespace metal = mtl' in shared header files and use types below as metal::int32_t etc.
	 */

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
	
	using std::size_t;
	using usize = std::size_t;
	using isize = std::ptrdiff_t;
	
}
	
#endif // __MTL_STDINT_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_STDINT_TYPEDEFS__
	
	


namespace _VMTL {
	
	/// MARK: - Complex
#ifdef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#ifndef __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#define __MTL_COMPLEX_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using complex_float   = complex<float>;
		using complex_double  = complex<double>;
		using complex_ldouble = complex<long double>;
		
		using complex_int     = complex<int>;
		using complex_long    = complex<long>;
		using complex_llong   = complex<long long>;
		using complex_uint    = complex<unsigned int>;
		using complex_ulong   = complex<unsigned long>;
		using complex_ullong  = complex<unsigned long long>;
		
	}
	
#endif // __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_COMPLEX_TYPEDEFS__
	
	/// MARK: - Quaternion
#ifdef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#ifndef __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#define __MTL_QUATERNION_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using quaternion_float   = quaternion<float>;
		using quaternion_double  = quaternion<double>;
		using quaternion_ldouble = quaternion<long double>;
		
		using quaternion_int     = quaternion<int>;
		using quaternion_long    = quaternion<long>;
		using quaternion_llong   = quaternion<long long>;
		using quaternion_uint    = quaternion<unsigned int>;
		using quaternion_ulong   = quaternion<unsigned long>;
		using quaternion_ullong  = quaternion<unsigned long long>;
		
	}
	
#endif // __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_QUATERNION_TYPEDEFS__
	
	// MARK: - Vector
#ifdef __MTL_DECLARE_VECTOR_TYPEDEFS__
#ifndef __MTL_VECTOR_TYPEDEFS_INCLUDED__
#define __MTL_VECTOR_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using vector2 = vector<T, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector3 = vector<T, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector4 = vector<T, 4, O>;
	
	inline namespace short_types {
		
		using size2            = vector2<std::size_t>;
		using size3            = vector3<std::size_t>;
		using size4            = vector4<std::size_t>;
		
		using usize2            = vector2<std::size_t>;
		using usize3            = vector3<std::size_t>;
		using usize4            = vector4<std::size_t>;
		
		using isize2            = vector2<std::ptrdiff_t>;
		using isize3            = vector3<std::ptrdiff_t>;
		using isize4            = vector4<std::ptrdiff_t>;
		
		using bool2            = vector2<bool>;
		using bool3            = vector3<bool>;
		using bool4            = vector4<bool>;
		using char2            = vector2<char>;
		using char3            = vector3<char>;
		using char4            = vector4<char>;
		using schar2           = vector2<char>;
		using schar3           = vector3<char>;
		using schar4           = vector4<char>;
		using uchar2           = vector2<unsigned char>;
		using uchar3           = vector3<unsigned char>;
		using uchar4           = vector4<unsigned char>;
		using short2           = vector2<short>;
		using short3           = vector3<short>;
		using short4           = vector4<short>;
		using ushort2          = vector2<unsigned short>;
		using ushort3          = vector3<unsigned short>;
		using ushort4          = vector4<unsigned short>;
		using int2             = vector2<int>;
		using int3             = vector3<int>;
		using int4             = vector4<int>;
		using uint2            = vector2<unsigned int>;
		using uint3            = vector3<unsigned int>;
		using uint4            = vector4<unsigned int>;
		using long2            = vector2<long>;
		using long3            = vector3<long>;
		using long4            = vector4<long>;
		using ulong2           = vector2<unsigned long>;
		using ulong3           = vector3<unsigned long>;
		using ulong4           = vector4<unsigned long>;
		using llong2           = vector2<long long>;
		using llong3           = vector3<long long>;
		using llong4           = vector4<long long>;
		using ullong2          = vector2<unsigned long long>;
		using ullong3          = vector3<unsigned long long>;
		using ullong4          = vector4<unsigned long long>;
		using float2           = vector2<float>;
		using float3           = vector3<float>;
		using float4           = vector4<float>;
		using double2          = vector2<double>;
		using double3          = vector3<double>;
		using double4          = vector4<double>;
		using ldouble2         = vector2<long double>;
		using ldouble3         = vector3<long double>;
		using ldouble4         = vector4<long double>;
		
		using packed_bool2     = vector2<bool,               vector_options{}.packed(true)>;
		using packed_bool3     = vector3<bool,               vector_options{}.packed(true)>;
		using packed_bool4     = vector4<bool,               vector_options{}.packed(true)>;
		using packed_char2     = vector2<char,               vector_options{}.packed(true)>;
		using packed_char3     = vector3<char,               vector_options{}.packed(true)>;
		using packed_char4     = vector4<char,               vector_options{}.packed(true)>;
		using packed_uchar2    = vector2<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar3    = vector3<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar4    = vector4<unsigned char,      vector_options{}.packed(true)>;
		using packed_short2    = vector2<short,              vector_options{}.packed(true)>;
		using packed_short3    = vector3<short,              vector_options{}.packed(true)>;
		using packed_short4    = vector4<short,              vector_options{}.packed(true)>;
		using packed_ushort2   = vector2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3   = vector3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4   = vector4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2      = vector2<int,                vector_options{}.packed(true)>;
		using packed_int3      = vector3<int,                vector_options{}.packed(true)>;
		using packed_int4      = vector4<int,                vector_options{}.packed(true)>;
		using packed_uint2     = vector2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3     = vector3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4     = vector4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2     = vector2<long,               vector_options{}.packed(true)>;
		using packed_long3     = vector3<long,               vector_options{}.packed(true)>;
		using packed_long4     = vector4<long,               vector_options{}.packed(true)>;
		using packed_ulong2    = vector2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3    = vector3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4    = vector4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2    = vector2<long long,          vector_options{}.packed(true)>;
		using packed_llong3    = vector3<long long,          vector_options{}.packed(true)>;
		using packed_llong4    = vector4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2   = vector2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3   = vector3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4   = vector4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2    = vector2<float,              vector_options{}.packed(true)>;
		using packed_float3    = vector3<float,              vector_options{}.packed(true)>;
		using packed_float4    = vector4<float,              vector_options{}.packed(true)>;
		using packed_double2   = vector2<double,             vector_options{}.packed(true)>;
		using packed_double3   = vector3<double,             vector_options{}.packed(true)>;
		using packed_double4   = vector4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2  = vector2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3  = vector3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4  = vector4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2    = vector2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3    = vector3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4    = vector4<bool,               vector_options{}.packed(false)>;
		using aligned_char2    = vector2<char,               vector_options{}.packed(false)>;
		using aligned_char3    = vector3<char,               vector_options{}.packed(false)>;
		using aligned_char4    = vector4<char,               vector_options{}.packed(false)>;
		using aligned_uchar2   = vector2<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar3   = vector3<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar4   = vector4<unsigned char,      vector_options{}.packed(false)>;
		using aligned_short2   = vector2<short,              vector_options{}.packed(false)>;
		using aligned_short3   = vector3<short,              vector_options{}.packed(false)>;
		using aligned_short4   = vector4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2  = vector2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3  = vector3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4  = vector4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2     = vector2<int,                vector_options{}.packed(false)>;
		using aligned_int3     = vector3<int,                vector_options{}.packed(false)>;
		using aligned_int4     = vector4<int,                vector_options{}.packed(false)>;
		using aligned_uint2    = vector2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3    = vector3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4    = vector4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2    = vector2<long,               vector_options{}.packed(false)>;
		using aligned_long3    = vector3<long,               vector_options{}.packed(false)>;
		using aligned_long4    = vector4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2   = vector2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3   = vector3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4   = vector4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2   = vector2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3   = vector3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4   = vector4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2  = vector2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3  = vector3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4  = vector4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2   = vector2<float,              vector_options{}.packed(false)>;
		using aligned_float3   = vector3<float,              vector_options{}.packed(false)>;
		using aligned_float4   = vector4<float,              vector_options{}.packed(false)>;
		using aligned_double2  = vector2<double,             vector_options{}.packed(false)>;
		using aligned_double3  = vector3<double,             vector_options{}.packed(false)>;
		using aligned_double4  = vector4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2 = vector2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3 = vector3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4 = vector4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_VECTOR_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_VECTOR_TYPEDEFS__
	
	/// MARK: - Matrix
#ifdef __MTL_DECLARE_MATRIX_TYPEDEFS__
#ifndef __MTL_MATRIX_TYPEDEFS_INCLUDED__
#define __MTL_MATRIX_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using matrix2x2 = matrix<T, 2, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x3 = matrix<T, 2, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x4 = matrix<T, 2, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x2 = matrix<T, 3, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x3 = matrix<T, 3, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x4 = matrix<T, 3, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x2 = matrix<T, 4, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x3 = matrix<T, 4, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x4 = matrix<T, 4, 4, O>;
	
	inline namespace short_types {
	
		using bool2x2            = matrix2x2<bool,               vector_options{}>;
		using bool2x3            = matrix2x3<bool,               vector_options{}>;
		using bool2x4            = matrix2x4<bool,               vector_options{}>;
		using bool3x2            = matrix3x2<bool,               vector_options{}>;
		using bool3x3            = matrix3x3<bool,               vector_options{}>;
		using bool3x4            = matrix3x4<bool,               vector_options{}>;
		using bool4x2            = matrix4x2<bool,               vector_options{}>;
		using bool4x3            = matrix4x3<bool,               vector_options{}>;
		using bool4x4            = matrix4x4<bool,               vector_options{}>;
		using short2x2           = matrix2x2<short,              vector_options{}>;
		using short2x3           = matrix2x3<short,              vector_options{}>;
		using short2x4           = matrix2x4<short,              vector_options{}>;
		using short3x2           = matrix3x2<short,              vector_options{}>;
		using short3x3           = matrix3x3<short,              vector_options{}>;
		using short3x4           = matrix3x4<short,              vector_options{}>;
		using short4x2           = matrix4x2<short,              vector_options{}>;
		using short4x3           = matrix4x3<short,              vector_options{}>;
		using short4x4           = matrix4x4<short,              vector_options{}>;
		using ushort2x2          = matrix2x2<unsigned short,     vector_options{}>;
		using ushort2x3          = matrix2x3<unsigned short,     vector_options{}>;
		using ushort2x4          = matrix2x4<unsigned short,     vector_options{}>;
		using ushort3x2          = matrix3x2<unsigned short,     vector_options{}>;
		using ushort3x3          = matrix3x3<unsigned short,     vector_options{}>;
		using ushort3x4          = matrix3x4<unsigned short,     vector_options{}>;
		using ushort4x2          = matrix4x2<unsigned short,     vector_options{}>;
		using ushort4x3          = matrix4x3<unsigned short,     vector_options{}>;
		using ushort4x4          = matrix4x4<unsigned short,     vector_options{}>;
		using int2x2             = matrix2x2<int,                vector_options{}>;
		using int2x3             = matrix2x3<int,                vector_options{}>;
		using int2x4             = matrix2x4<int,                vector_options{}>;
		using int3x2             = matrix3x2<int,                vector_options{}>;
		using int3x3             = matrix3x3<int,                vector_options{}>;
		using int3x4             = matrix3x4<int,                vector_options{}>;
		using int4x2             = matrix4x2<int,                vector_options{}>;
		using int4x3             = matrix4x3<int,                vector_options{}>;
		using int4x4             = matrix4x4<int,                vector_options{}>;
		using uint2x2            = matrix2x2<unsigned int,       vector_options{}>;
		using uint2x3            = matrix2x3<unsigned int,       vector_options{}>;
		using uint2x4            = matrix2x4<unsigned int,       vector_options{}>;
		using uint3x2            = matrix3x2<unsigned int,       vector_options{}>;
		using uint3x3            = matrix3x3<unsigned int,       vector_options{}>;
		using uint3x4            = matrix3x4<unsigned int,       vector_options{}>;
		using uint4x2            = matrix4x2<unsigned int,       vector_options{}>;
		using uint4x3            = matrix4x3<unsigned int,       vector_options{}>;
		using uint4x4            = matrix4x4<unsigned int,       vector_options{}>;
		using long2x2            = matrix2x2<long,               vector_options{}>;
		using long2x3            = matrix2x3<long,               vector_options{}>;
		using long2x4            = matrix2x4<long,               vector_options{}>;
		using long3x2            = matrix3x2<long,               vector_options{}>;
		using long3x3            = matrix3x3<long,               vector_options{}>;
		using long3x4            = matrix3x4<long,               vector_options{}>;
		using long4x2            = matrix4x2<long,               vector_options{}>;
		using long4x3            = matrix4x3<long,               vector_options{}>;
		using long4x4            = matrix4x4<long,               vector_options{}>;
		using ulong2x2           = matrix2x2<unsigned long,      vector_options{}>;
		using ulong2x3           = matrix2x3<unsigned long,      vector_options{}>;
		using ulong2x4           = matrix2x4<unsigned long,      vector_options{}>;
		using ulong3x2           = matrix3x2<unsigned long,      vector_options{}>;
		using ulong3x3           = matrix3x3<unsigned long,      vector_options{}>;
		using ulong3x4           = matrix3x4<unsigned long,      vector_options{}>;
		using ulong4x2           = matrix4x2<unsigned long,      vector_options{}>;
		using ulong4x3           = matrix4x3<unsigned long,      vector_options{}>;
		using ulong4x4           = matrix4x4<unsigned long,      vector_options{}>;
		using llong2x2           = matrix2x2<long long,          vector_options{}>;
		using llong2x3           = matrix2x3<long long,          vector_options{}>;
		using llong2x4           = matrix2x4<long long,          vector_options{}>;
		using llong3x2           = matrix3x2<long long,          vector_options{}>;
		using llong3x3           = matrix3x3<long long,          vector_options{}>;
		using llong3x4           = matrix3x4<long long,          vector_options{}>;
		using llong4x2           = matrix4x2<long long,          vector_options{}>;
		using llong4x3           = matrix4x3<long long,          vector_options{}>;
		using llong4x4           = matrix4x4<long long,          vector_options{}>;
		using ullong2x2          = matrix2x2<unsigned long long, vector_options{}>;
		using ullong2x3          = matrix2x3<unsigned long long, vector_options{}>;
		using ullong2x4          = matrix2x4<unsigned long long, vector_options{}>;
		using ullong3x2          = matrix3x2<unsigned long long, vector_options{}>;
		using ullong3x3          = matrix3x3<unsigned long long, vector_options{}>;
		using ullong3x4          = matrix3x4<unsigned long long, vector_options{}>;
		using ullong4x2          = matrix4x2<unsigned long long, vector_options{}>;
		using ullong4x3          = matrix4x3<unsigned long long, vector_options{}>;
		using ullong4x4          = matrix4x4<unsigned long long, vector_options{}>;
		using float2x2           = matrix2x2<float,              vector_options{}>;
		using float2x3           = matrix2x3<float,              vector_options{}>;
		using float2x4           = matrix2x4<float,              vector_options{}>;
		using float3x2           = matrix3x2<float,              vector_options{}>;
		using float3x3           = matrix3x3<float,              vector_options{}>;
		using float3x4           = matrix3x4<float,              vector_options{}>;
		using float4x2           = matrix4x2<float,              vector_options{}>;
		using float4x3           = matrix4x3<float,              vector_options{}>;
		using float4x4           = matrix4x4<float,              vector_options{}>;
		using double2x2          = matrix2x2<double,             vector_options{}>;
		using double2x3          = matrix2x3<double,             vector_options{}>;
		using double2x4          = matrix2x4<double,             vector_options{}>;
		using double3x2          = matrix3x2<double,             vector_options{}>;
		using double3x3          = matrix3x3<double,             vector_options{}>;
		using double3x4          = matrix3x4<double,             vector_options{}>;
		using double4x2          = matrix4x2<double,             vector_options{}>;
		using double4x3          = matrix4x3<double,             vector_options{}>;
		using double4x4          = matrix4x4<double,             vector_options{}>;
		using ldouble2x2         = matrix2x2<long double,        vector_options{}>;
		using ldouble2x3         = matrix2x3<long double,        vector_options{}>;
		using ldouble2x4         = matrix2x4<long double,        vector_options{}>;
		using ldouble3x2         = matrix3x2<long double,        vector_options{}>;
		using ldouble3x3         = matrix3x3<long double,        vector_options{}>;
		using ldouble3x4         = matrix3x4<long double,        vector_options{}>;
		using ldouble4x2         = matrix4x2<long double,        vector_options{}>;
		using ldouble4x3         = matrix4x3<long double,        vector_options{}>;
		using ldouble4x4         = matrix4x4<long double,        vector_options{}>;
	 
		using packed_bool2x2     = matrix2x2<bool,               vector_options{}.packed(true)>;
		using packed_bool2x3     = matrix2x3<bool,               vector_options{}.packed(true)>;
		using packed_bool2x4     = matrix2x4<bool,               vector_options{}.packed(true)>;
		using packed_bool3x2     = matrix3x2<bool,               vector_options{}.packed(true)>;
		using packed_bool3x3     = matrix3x3<bool,               vector_options{}.packed(true)>;
		using packed_bool3x4     = matrix3x4<bool,               vector_options{}.packed(true)>;
		using packed_bool4x2     = matrix4x2<bool,               vector_options{}.packed(true)>;
		using packed_bool4x3     = matrix4x3<bool,               vector_options{}.packed(true)>;
		using packed_bool4x4     = matrix4x4<bool,               vector_options{}.packed(true)>;
		using packed_short2x2    = matrix2x2<short,              vector_options{}.packed(true)>;
		using packed_short2x3    = matrix2x3<short,              vector_options{}.packed(true)>;
		using packed_short2x4    = matrix2x4<short,              vector_options{}.packed(true)>;
		using packed_short3x2    = matrix3x2<short,              vector_options{}.packed(true)>;
		using packed_short3x3    = matrix3x3<short,              vector_options{}.packed(true)>;
		using packed_short3x4    = matrix3x4<short,              vector_options{}.packed(true)>;
		using packed_short4x2    = matrix4x2<short,              vector_options{}.packed(true)>;
		using packed_short4x3    = matrix4x3<short,              vector_options{}.packed(true)>;
		using packed_short4x4    = matrix4x4<short,              vector_options{}.packed(true)>;
		using packed_ushort2x2   = matrix2x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x3   = matrix2x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x4   = matrix2x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x2   = matrix3x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x3   = matrix3x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x4   = matrix3x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x2   = matrix4x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x3   = matrix4x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x4   = matrix4x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2x2      = matrix2x2<int,                vector_options{}.packed(true)>;
		using packed_int2x3      = matrix2x3<int,                vector_options{}.packed(true)>;
		using packed_int2x4      = matrix2x4<int,                vector_options{}.packed(true)>;
		using packed_int3x2      = matrix3x2<int,                vector_options{}.packed(true)>;
		using packed_int3x3      = matrix3x3<int,                vector_options{}.packed(true)>;
		using packed_int3x4      = matrix3x4<int,                vector_options{}.packed(true)>;
		using packed_int4x2      = matrix4x2<int,                vector_options{}.packed(true)>;
		using packed_int4x3      = matrix4x3<int,                vector_options{}.packed(true)>;
		using packed_int4x4      = matrix4x4<int,                vector_options{}.packed(true)>;
		using packed_uint2x2     = matrix2x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x3     = matrix2x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x4     = matrix2x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x2     = matrix3x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x3     = matrix3x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x4     = matrix3x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x2     = matrix4x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x3     = matrix4x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x4     = matrix4x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2x2     = matrix2x2<long,               vector_options{}.packed(true)>;
		using packed_long2x3     = matrix2x3<long,               vector_options{}.packed(true)>;
		using packed_long2x4     = matrix2x4<long,               vector_options{}.packed(true)>;
		using packed_long3x2     = matrix3x2<long,               vector_options{}.packed(true)>;
		using packed_long3x3     = matrix3x3<long,               vector_options{}.packed(true)>;
		using packed_long3x4     = matrix3x4<long,               vector_options{}.packed(true)>;
		using packed_long4x2     = matrix4x2<long,               vector_options{}.packed(true)>;
		using packed_long4x3     = matrix4x3<long,               vector_options{}.packed(true)>;
		using packed_long4x4     = matrix4x4<long,               vector_options{}.packed(true)>;
		using packed_ulong2x2    = matrix2x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x3    = matrix2x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x4    = matrix2x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x2    = matrix3x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x3    = matrix3x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x4    = matrix3x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x2    = matrix4x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x3    = matrix4x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x4    = matrix4x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2x2    = matrix2x2<long long,          vector_options{}.packed(true)>;
		using packed_llong2x3    = matrix2x3<long long,          vector_options{}.packed(true)>;
		using packed_llong2x4    = matrix2x4<long long,          vector_options{}.packed(true)>;
		using packed_llong3x2    = matrix3x2<long long,          vector_options{}.packed(true)>;
		using packed_llong3x3    = matrix3x3<long long,          vector_options{}.packed(true)>;
		using packed_llong3x4    = matrix3x4<long long,          vector_options{}.packed(true)>;
		using packed_llong4x2    = matrix4x2<long long,          vector_options{}.packed(true)>;
		using packed_llong4x3    = matrix4x3<long long,          vector_options{}.packed(true)>;
		using packed_llong4x4    = matrix4x4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2x2   = matrix2x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x3   = matrix2x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x4   = matrix2x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x2   = matrix3x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x3   = matrix3x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x4   = matrix3x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x2   = matrix4x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x3   = matrix4x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x4   = matrix4x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2x2    = matrix2x2<float,              vector_options{}.packed(true)>;
		using packed_float2x3    = matrix2x3<float,              vector_options{}.packed(true)>;
		using packed_float2x4    = matrix2x4<float,              vector_options{}.packed(true)>;
		using packed_float3x2    = matrix3x2<float,              vector_options{}.packed(true)>;
		using packed_float3x3    = matrix3x3<float,              vector_options{}.packed(true)>;
		using packed_float3x4    = matrix3x4<float,              vector_options{}.packed(true)>;
		using packed_float4x2    = matrix4x2<float,              vector_options{}.packed(true)>;
		using packed_float4x3    = matrix4x3<float,              vector_options{}.packed(true)>;
		using packed_float4x4    = matrix4x4<float,              vector_options{}.packed(true)>;
		using packed_double2x2   = matrix2x2<double,             vector_options{}.packed(true)>;
		using packed_double2x3   = matrix2x3<double,             vector_options{}.packed(true)>;
		using packed_double2x4   = matrix2x4<double,             vector_options{}.packed(true)>;
		using packed_double3x2   = matrix3x2<double,             vector_options{}.packed(true)>;
		using packed_double3x3   = matrix3x3<double,             vector_options{}.packed(true)>;
		using packed_double3x4   = matrix3x4<double,             vector_options{}.packed(true)>;
		using packed_double4x2   = matrix4x2<double,             vector_options{}.packed(true)>;
		using packed_double4x3   = matrix4x3<double,             vector_options{}.packed(true)>;
		using packed_double4x4   = matrix4x4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2x2  = matrix2x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x3  = matrix2x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x4  = matrix2x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x2  = matrix3x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x3  = matrix3x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x4  = matrix3x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x2  = matrix4x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x3  = matrix4x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x4  = matrix4x4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2x2    = matrix2x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x3    = matrix2x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x4    = matrix2x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x2    = matrix3x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x3    = matrix3x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x4    = matrix3x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x2    = matrix4x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x3    = matrix4x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x4    = matrix4x4<bool,               vector_options{}.packed(false)>;
		using aligned_short2x2   = matrix2x2<short,              vector_options{}.packed(false)>;
		using aligned_short2x3   = matrix2x3<short,              vector_options{}.packed(false)>;
		using aligned_short2x4   = matrix2x4<short,              vector_options{}.packed(false)>;
		using aligned_short3x2   = matrix3x2<short,              vector_options{}.packed(false)>;
		using aligned_short3x3   = matrix3x3<short,              vector_options{}.packed(false)>;
		using aligned_short3x4   = matrix3x4<short,              vector_options{}.packed(false)>;
		using aligned_short4x2   = matrix4x2<short,              vector_options{}.packed(false)>;
		using aligned_short4x3   = matrix4x3<short,              vector_options{}.packed(false)>;
		using aligned_short4x4   = matrix4x4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2x2  = matrix2x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x3  = matrix2x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x4  = matrix2x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x2  = matrix3x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x3  = matrix3x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x4  = matrix3x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x2  = matrix4x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x3  = matrix4x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x4  = matrix4x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2x2     = matrix2x2<int,                vector_options{}.packed(false)>;
		using aligned_int2x3     = matrix2x3<int,                vector_options{}.packed(false)>;
		using aligned_int2x4     = matrix2x4<int,                vector_options{}.packed(false)>;
		using aligned_int3x2     = matrix3x2<int,                vector_options{}.packed(false)>;
		using aligned_int3x3     = matrix3x3<int,                vector_options{}.packed(false)>;
		using aligned_int3x4     = matrix3x4<int,                vector_options{}.packed(false)>;
		using aligned_int4x2     = matrix4x2<int,                vector_options{}.packed(false)>;
		using aligned_int4x3     = matrix4x3<int,                vector_options{}.packed(false)>;
		using aligned_int4x4     = matrix4x4<int,                vector_options{}.packed(false)>;
		using aligned_uint2x2    = matrix2x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x3    = matrix2x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x4    = matrix2x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x2    = matrix3x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x3    = matrix3x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x4    = matrix3x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x2    = matrix4x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x3    = matrix4x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x4    = matrix4x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2x2    = matrix2x2<long,               vector_options{}.packed(false)>;
		using aligned_long2x3    = matrix2x3<long,               vector_options{}.packed(false)>;
		using aligned_long2x4    = matrix2x4<long,               vector_options{}.packed(false)>;
		using aligned_long3x2    = matrix3x2<long,               vector_options{}.packed(false)>;
		using aligned_long3x3    = matrix3x3<long,               vector_options{}.packed(false)>;
		using aligned_long3x4    = matrix3x4<long,               vector_options{}.packed(false)>;
		using aligned_long4x2    = matrix4x2<long,               vector_options{}.packed(false)>;
		using aligned_long4x3    = matrix4x3<long,               vector_options{}.packed(false)>;
		using aligned_long4x4    = matrix4x4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2x2   = matrix2x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x3   = matrix2x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x4   = matrix2x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x2   = matrix3x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x3   = matrix3x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x4   = matrix3x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x2   = matrix4x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x3   = matrix4x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x4   = matrix4x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2x2   = matrix2x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x3   = matrix2x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x4   = matrix2x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x2   = matrix3x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x3   = matrix3x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x4   = matrix3x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x2   = matrix4x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x3   = matrix4x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x4   = matrix4x4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2x2  = matrix2x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x3  = matrix2x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x4  = matrix2x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x2  = matrix3x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x3  = matrix3x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x4  = matrix3x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x2  = matrix4x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x3  = matrix4x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x4  = matrix4x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2x2   = matrix2x2<float,              vector_options{}.packed(false)>;
		using aligned_float2x3   = matrix2x3<float,              vector_options{}.packed(false)>;
		using aligned_float2x4   = matrix2x4<float,              vector_options{}.packed(false)>;
		using aligned_float3x2   = matrix3x2<float,              vector_options{}.packed(false)>;
		using aligned_float3x3   = matrix3x3<float,              vector_options{}.packed(false)>;
		using aligned_float3x4   = matrix3x4<float,              vector_options{}.packed(false)>;
		using aligned_float4x2   = matrix4x2<float,              vector_options{}.packed(false)>;
		using aligned_float4x3   = matrix4x3<float,              vector_options{}.packed(false)>;
		using aligned_float4x4   = matrix4x4<float,              vector_options{}.packed(false)>;
		using aligned_double2x2  = matrix2x2<double,             vector_options{}.packed(false)>;
		using aligned_double2x3  = matrix2x3<double,             vector_options{}.packed(false)>;
		using aligned_double2x4  = matrix2x4<double,             vector_options{}.packed(false)>;
		using aligned_double3x2  = matrix3x2<double,             vector_options{}.packed(false)>;
		using aligned_double3x3  = matrix3x3<double,             vector_options{}.packed(false)>;
		using aligned_double3x4  = matrix3x4<double,             vector_options{}.packed(false)>;
		using aligned_double4x2  = matrix4x2<double,             vector_options{}.packed(false)>;
		using aligned_double4x3  = matrix4x3<double,             vector_options{}.packed(false)>;
		using aligned_double4x4  = matrix4x4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2x2 = matrix2x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x3 = matrix2x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x4 = matrix2x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x2 = matrix3x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x3 = matrix3x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x4 = matrix3x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x2 = matrix4x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x3 = matrix4x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x4 = matrix4x4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_MATRIX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_MATRIX_TYPEDEFS__
	
}




#include <cmath>
#include <iosfwd>

/// MARK: - Synopsis
/*
 
 */

namespace _VMTL {

	inline constexpr vector_options __mtl_complex_vector_options = vector_options{}.packed(false);

	/// MARK: - struct complex
	template <real_scalar T>
	struct complex<T>: public vector<T, 2, vector_options{}.packed(false)> {
		constexpr static vector_options __mtl_options = __mtl_complex_vector_options;
		using __mtl_base = vector<T, 2, __mtl_options>;
		using typename __mtl_base::value_type;
		
		using __vector_data_<T, 2, __mtl_options>::real;
		using __vector_data_<T, 2, __mtl_options>::imag;
		
		/// Value Constructors
		complex() = default;
		__mtl_always_inline __mtl_interface_export
		constexpr complex(T real): __mtl_base(real, 0) {}
		__mtl_always_inline __mtl_interface_export
		constexpr complex(T real, T imag): __mtl_base(real, imag) {}
		__mtl_always_inline __mtl_interface_export
		constexpr complex(vector<T, 2, __mtl_options> const& v): __mtl_base(v) {}
		__mtl_always_inline __mtl_interface_export
		explicit constexpr complex(quaternion<T> const& q): __mtl_base(q.__mtl_at(0), q.__mtl_at(1)) {}
		
		/// Conversion Constructor
		template <std::convertible_to<T> U>
		__mtl_always_inline __mtl_interface_export
		constexpr complex(complex<U> const& rhs): __mtl_base(rhs) {}
		
		complex& operator=(complex const&)& = default;
		
		/// MARK: - Arithmetic Assignment
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator+=(complex const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator+=(T const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator-=(complex const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator-=(T const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator*=(complex const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator*=(T const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator/=(complex const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
		__mtl_always_inline __mtl_interface_export
		constexpr complex& operator/=(T const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
	};
	
	/// MARK: - Misc
	template <real_scalar T>
	complex(T) -> complex<T>;
	template <real_scalar T, real_scalar U>
	complex(T, U) -> complex<__mtl_promote(T, U)>;
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T real(complex<T> const& z) { return z.__mtl_at(0); }
	template <typename T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T imag(complex<T> const& z) { return z.__mtl_at(1); }
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr vector<T, 2, __mtl_complex_vector_options>& __mtl_as_vector(complex<T>& z) {
		return static_cast<vector<T, 2, complex<T>::__mtl_options>&>(z);
	}
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr vector<T, 2, __mtl_complex_vector_options> const& __mtl_as_vector(complex<T> const& z) {
		return static_cast<vector<T, 2, complex<T>::__mtl_options> const&>(z);
	}
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr complex<T> __mtl_mul_by_i(complex<T> const& z) {
		return { -imag(z), real(z) };
	}
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr complex<T> __mtl_sqr(complex<T> const& z) {
		return {
			(real(z) - imag(z)) * (real(z) + imag(z)),
			T(2) * real(z) * imag(z)
		};
	}
	
	/// isnan
	template <typename T>
	constexpr bool isnan(complex<T> const& z) {
		using std::isnan;
		return isnan(z.__mtl_at(0)) || isnan(z.__mtl_at(1));
	}
	
	/// isinf
	template <typename T>
	constexpr bool isinf(complex<T> const& z) {
		using std::isinf;
		return isinf(z.__mtl_at(0)) || isinf(z.__mtl_at(1));
	}
	
	/// isfinite
	template <typename T>
	constexpr bool isfinite(complex<T> const& z) {
		using std::isfinite;
		return isfinite(z.__mtl_at(0)) || isfinite(z.__mtl_at(1));
	}
	
	/// isnormal
	template <typename T>
	constexpr bool isnormal(complex<T> const& z) {
		using std::isnormal;
		return isnormal(z.__mtl_at(0)) || isnormal(z.__mtl_at(1));
	}
	
	/// MARK: - Literals
	inline namespace literals {
		inline namespace quaternion_literals {
			inline namespace complex_literals {
				inline constexpr complex<double>             operator"" _i(long double x)           { return { 0, static_cast<double>(x) }; }
				inline constexpr complex<float>              operator"" _if(long double x)          { return { 0, static_cast<float>(x) }; }
				inline constexpr complex<long double>        operator"" _ild(long double x)         { return { 0, static_cast<long double>(x) }; }
				inline constexpr complex<int>                operator"" _i(unsigned long long x)    { return { 0, static_cast<int>(x) }; }
				inline constexpr complex<long>               operator"" _il(unsigned long long x)   { return { 0, static_cast<long>(x) }; }
				inline constexpr complex<long long>          operator"" _ill(unsigned long long x)  { return { 0, static_cast<long long>(x) }; }
				inline constexpr complex<unsigned int>       operator"" _iu(unsigned long long x)   { return { 0, static_cast<unsigned int>(x) }; }
				inline constexpr complex<unsigned long>      operator"" _iul(unsigned long long x)  { return { 0, static_cast<unsigned long>(x) }; }
				inline constexpr complex<unsigned long long> operator"" _iull(unsigned long long x) { return { 0, static_cast<unsigned long long>(x) }; }
			}
		}
	}
	
	/// MARK: - Complex Arithmetic
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<T> operator+(complex<T> const& z) {
		return z;
	}
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<T> operator-(complex<T> const& z) {
		return { -real(z), -imag(z) };
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator+(complex<T> const& a, complex<U> const& b) {
		return __mtl_as_vector(a) + __mtl_as_vector(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator+(complex<T> const& a, U const& b) {
		return complex<__mtl_promote(T, U)>(real(a) + b, imag(a));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator+(T const& a, complex<U> const& b) {
		return complex<__mtl_promote(T, U)>(a + real(b), imag(b));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator-(complex<T> const& a, complex<U> const& b) {
		return __mtl_as_vector(a) - __mtl_as_vector(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator-(complex<T> const& a, U const& b) {
		return complex<__mtl_promote(T, U)>(real(a) - b, imag(a));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator-(T const& a, complex<U> const& b) {
		return complex<__mtl_promote(T, U)>(a - real(b), -imag(b));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator*(complex<T> const& a, complex<U> const& b) {
		return complex<__mtl_promote(T, U)>(
			real(a) * real(b) - imag(a) * imag(b),
			real(a) * imag(b) + imag(a) * real(b)
		);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator*(complex<T> const& a, U const& b) {
		return complex<__mtl_promote(T, U)>(real(a) * b, imag(a) * b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator*(T const& a, complex<U> const& b) {
		return complex<__mtl_promote(T, U)>(a * real(b), a * imag(b));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator/(complex<T> const& a, complex<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator/(complex<T> const& a, U const& b) {
		return complex<__mtl_promote(T, U)>(real(a) / b, imag(a) / b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_promote(T, U)> operator/(T const& a, complex<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	/// MARK: - operator==
	template <typename T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(complex<T> const& a, complex<U> const& b) {
		return __mtl_as_vector(a) == __mtl_as_vector(b);
	}
	template <typename T, real_scalar U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(complex<T> const& a, U const& b) {
		return real(a) == b && imag(a) == 0;
	}
	template <real_scalar T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(T const& a, complex<U> const& b) {
		return a == real(b) && 0 == imag(b);
	}
	
	/// MARK: - Complex Math Functions
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<T> conj(complex<T> const& z) {
		return { real(z), -imag(z) };
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<T> inverse(complex<T> const& z) {
		return conj(z) / norm_squared(z);
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<T> normalize(complex<T> const& z) {
		return normalize(__mtl_as_vector(z));
	}
	///
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr __mtl_floatify(T) abs(complex<T> const& z) {
		return norm(z);
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr __mtl_floatify(T) arg(complex<T> const& z) {
		return std::atan2(_VMTL::imag(z), _VMTL::real(z));
	}
			
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	complex<T> proj(complex<T> const& z) {
		if (std::isinf(_VMTL::real(z)) || std::isinf(_VMTL::imag(z))) {
			return { INFINITY, std::copysign(T(0), _VMTL::imag(z)) };
		}
		return z;
	}
	
	template <real_scalar T, bool CheckTheta = true>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_floatify(T)> unit_polar(T const& theta) {
		using F = __mtl_floatify(T);
		
		if constexpr (CheckTheta) {
			__mtl_safe_math_if (std::isnan(theta)) {
				return { theta, theta };
			}
			__mtl_safe_math_if (std::isinf(theta)) {
				return { F(NAN), F(NAN) };
			}
		}
		
		return { std::cos(theta), std::sin(theta) };
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_floatify(__mtl_promote(T, U))> polar(T const& _r, U const& _theta) {

		using F = __mtl_floatify(T);
		F const r = _r;
		F const theta = _theta;
		__mtl_safe_math_if (std::isnan(r) || signbit(r))
			return { F(NAN), F(NAN) };
		__mtl_safe_math_if (std::isnan(theta)) {
			__mtl_safe_math_if (std::isinf(r))
				return { r, theta };
			return { theta, theta };
		}
		__mtl_safe_math_if (std::isinf(theta)) {
			__mtl_safe_math_if (std::isinf(r))
				return { r, F(NAN) };
			return { F(NAN), F(NAN) };
		}
		
		return r * unit_polar<T, false>(theta);
	}
	
	/// MARK: Power Functions
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	complex<__mtl_floatify(T)> exp(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		F i = imag(z);
		__mtl_safe_math_if (std::isinf(real(z))) {
			__mtl_safe_math_if (real(z) < F(0)) {
				__mtl_safe_math_if (!std::isinf(i))
					i = F(1);
			}
			else __mtl_safe_math_if (i == 0 || !std::isinf(i)) {
				__mtl_safe_math_if (std::isinf(i))
					i = F(NAN);
				return complex<F>(real(z), i);
			}
		}
		else __mtl_safe_math_if (std::isnan(real(z)) && imag(z) == 0)
			return z;
		F const e = std::exp(real(z));
		return { e * std::cos(i), e * std::sin(i) };
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	complex<__mtl_floatify(T)> log(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_expect(z != 0);
		return { std::log(abs(z)), arg(z) };
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	complex<__mtl_floatify(T)> log10(complex<T> const& z) {
		return log(z) / std::log(T(10));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_floatify(__mtl_promote(T, U))> pow(complex<T> const& x, complex<U> const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_floatify(__mtl_promote(T, U))> pow(T const& x, complex<U> const& y) {
		return _VMTL::exp(y * std::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr complex<__mtl_floatify(__mtl_promote(T, U))> pow(complex<T> const& x, U const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	complex<__mtl_floatify(T)> sqrt(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(imag(z)))
			return complex<F>(F(INFINITY), imag(z));
		__mtl_safe_math_if (std::isinf(real(z))) {
			__mtl_safe_math_if (real(z) > F(0))
				return complex<F>(real(z), std::isnan(imag(z)) ? imag(z) : std::copysign(F(0), imag(z)));
			return complex<F>(std::isnan(imag(z)) ? imag(z) : F(0), std::copysign(real(z), imag(z)));
		}
		return _VMTL::polar(std::sqrt(_VMTL::abs(z)), _VMTL::arg(z) / F(2));
	}
	
	/// MARK: Hyperbolic Functions
	template <real_scalar T>
	complex<__mtl_floatify(T)> sinh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(real(z)) && !std::isinf(imag(z)))
			return complex<F>(real(z), F(NAN));
		__mtl_safe_math_if (real(z) == 0 && !std::isinf(imag(z)))
			return complex<F>(real(z), F(NAN));
		__mtl_safe_math_if (imag(z) == 0 && !std::isinf(real(z)))
			return z;
		return { std::sinh(real(z)) * std::cos(imag(z)), std::cosh(real(z)) * std::sin(imag(z)) };
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> cosh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(real(z)) && !std::isinf(imag(z)))
			return { std::abs(real(z)), F(NAN) };
		__mtl_safe_math_if (real(z) == 0 && !std::isinf(imag(z)))
			return { F(NAN), real(z) };
		__mtl_safe_math_if (real(z) == 0 && imag(z) == 0)
			return { F(1), imag(z) };
		__mtl_safe_math_if (imag(z) == 0 && !std::isinf(real(z)))
			return { std::abs(real(z)), imag(z) };
		return { std::cosh(real(z)) * std::cos(imag(z)), std::sinh(real(z)) * std::sin(imag(z)) };
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> tanh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(real(z))) {
			__mtl_safe_math_if (!std::isinf(imag(z)))
				return { F(1), F(0) };
			return { F(1), std::copysign(F(0), sin(F(2) * imag(z))) };
		}
		__mtl_safe_math_if (std::isnan(real(z)) && imag(z) == 0)
			return z;
		F const _2r   = 2 * real(z);
		F const _2i   = 2 * imag(z);
		F const _d    = std::cosh(_2r) + std::cos(_2i);
		F const _2rsh = std::sinh(_2r);
		__mtl_safe_math_if (std::isinf(_2rsh) && std::isinf(_d))
			return {
				_2rsh > F(0) ? F(1) : F(-1),
				_2i   > F(0) ? F(0) : F(-0.)
			};
		return  { _2rsh / _d, std::sin(_2i) / _d };
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> asinh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(real(z))) {
			__mtl_safe_math_if (std::isnan(imag(z)))
				return z;
			__mtl_safe_math_if (std::isinf(imag(z)))
				return { real(z), std::copysign(_VMTL::constants<F>::pi * F(0.25), imag(z)) };
			return { real(z), std::copysign(F(0), imag(z)) };
		}
		__mtl_safe_math_if (std::isnan(real(z))) {
			__mtl_safe_math_if (std::isinf(imag(z)))
				return complex<F>(imag(z), real(z));
			__mtl_safe_math_if (imag(z) == 0)
				return z;
			return { real(z), real(z) };
		}
		__mtl_safe_math_if (std::isinf(imag(z)))
			return { std::copysign(imag(z), real(z)), std::copysign(_VMTL::constants<F>::pi / F(2), imag(z)) };
		complex<F> const x = _VMTL::log(z + _VMTL::sqrt(__mtl_sqr(z) + F(1)));
		return complex<F>(copysign(real(x), real(z)), std::copysign(imag(x), imag(z)));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> acosh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(real(z))) {
			__mtl_safe_math_if (std::isnan(imag(z)))
				return { std::abs(real(z)), imag(z) };
			__mtl_safe_math_if (std::isinf(imag(z))) {
				__mtl_safe_math_if (real(z) > 0)
					return { real(z), std::copysign(_VMTL::constants<F>::pi * F(0.25), imag(z)) };
				return { -real(z), std::copysign(_VMTL::constants<F>::pi * F(0.75), imag(z)) };
			}
			__mtl_safe_math_if (real(z) < 0)
				return { -real(z), std::copysign(_VMTL::constants<F>::pi, imag(z)) };
			return { real(z), std::copysign(F(0), imag(z)) };
		}
		__mtl_safe_math_if (std::isnan(real(z)))
		{
			__mtl_safe_math_if (std::isinf(imag(z)))
				return { std::abs(imag(z)), real(z) };
			return { real(z), real(z) };
		}
		__mtl_safe_math_if (std::isinf(imag(z)))
			return { std::abs(imag(z)), std::copysign(_VMTL::constants<F>::pi / F(2), imag(z)) };
		complex<F> const x = _VMTL::log(z + _VMTL::sqrt(__mtl_sqr(z) - F(1)));
		return { std::copysign(real(x), F(0)), std::copysign(imag(x), imag(z)) };
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> atanh(complex<T> const& _z) {
		using F = __mtl_floatify(T);
		complex<F> z = _z;
		__mtl_safe_math_if (std::isinf(imag(z))) {
			return { std::copysign(F(0), real(z)), std::copysign(_VMTL::constants<F>::pi / F(2), imag(z)) };
		}
		__mtl_safe_math_if (std::isnan(imag(z))) {
			__mtl_safe_math_if (std::isinf(real(z)) || real(z) == 0)
				return { std::copysign(F(0), real(z)), imag(z) };
			return { imag(z), imag(z) };
		}
		__mtl_safe_math_if (std::isnan(real(z))) {
			return { real(z), real(z) };
		}
		__mtl_safe_math_if (std::isinf(real(z))) {
			return { std::copysign(F(0), real(z)), std::copysign(_VMTL::constants<F>::pi / F(2), imag(z)) };
		}
		__mtl_safe_math_if (std::abs(real(z)) == 1 && imag(z) == 0) {
			return { std::copysign(F(INFINITY), real(z)), std::copysign(F(0), imag(z)) };
		}
		complex<F> const x = _VMTL::log((F(1) + z) / (F(1) - z)) / F(2);
		return { std::copysign(real(x), real(z)), std::copysign(imag(x), imag(z)) };
	}
	
	/// MARK: Trigonometric Functions
	template <real_scalar T>
	complex<__mtl_floatify(T)> sin(complex<T> const& z) {
		return -__mtl_mul_by_i(_VMTL::sinh(__mtl_mul_by_i(z)));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> cos(complex<T> const& z) {
		return _VMTL::cosh(__mtl_mul_by_i(z));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> tan(complex<T> const& z) {
		return -__mtl_mul_by_i(_VMTL::tanh(__mtl_mul_by_i(z)));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> asin(complex<T> const& z) {
		using F = __mtl_floatify(T);
		return -__mtl_mul_by_i(_VMTL::log(__mtl_mul_by_i(z) + _VMTL::sqrt(1 - z * z)));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> acos(complex<T> const& z) {
		using F = __mtl_floatify(T);
		return constants<F>::pi / 2 + __mtl_mul_by_i(_VMTL::log(__mtl_mul_by_i(z) + _VMTL::sqrt(1 - z * z)));
	}
	
	template <real_scalar T>
	complex<__mtl_floatify(T)> atan(complex<T> const& z) {
		return -__mtl_mul_by_i(_VMTL::atanh(__mtl_mul_by_i(z)));
	}
	
}

/// MARK: - Decomposition
namespace _VMTL {

	template <std::size_t I, typename T>
	T const& get(complex<T> const& v) {
		return v.__mtl_at(I);
	}
	template <std::size_t I, typename T>
	T& get(complex<T>& v) {
		return v.__mtl_at(I);
	}
	template <std::size_t I, typename T>
	T&& get(complex<T>&& v) {
		return std::move(v).__mtl_at(I);
	}
	template <std::size_t I, typename T>
	T const&& get(complex<T> const&& v) {
		return std::move(v).__mtl_at(I);
	}
	
}

template <typename T>
struct std::tuple_size<_VMTL::complex<T>>: std::integral_constant<std::size_t, 2> {};

template <std::size_t I, typename T>
struct std::tuple_element<I, _VMTL::complex<T>> {
	using type = T;
};

#endif // __MTL_COMPLEX_HPP_INCLUDED__


#pragma once

/// __quaternion.hpp

#ifndef __MTL_QUATERNION_HPP_INCLUDED__
#define __MTL_QUATERNION_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_


#define __MTL_DECLARE_QUATERNION_TYPEDEFS__
/// __typedefs.hpp

/// DELIBERATELY NO INCLUDE GUARDS! Sections have their own include guards.


_MTL_SYSTEM_HEADER_


	
#ifdef __MTL_DECLARE_STDINT_TYPEDEFS__
#ifndef __MTL_STDINT_TYPEDEFS_INCLUDED__
#define __MTL_STDINT_TYPEDEFS_INCLUDED__
	
#include <cstdint>

namespace _VMTL {
	
	/**
	 These exist so I can conditionally declare 'namespace metal = mtl' in shared header files and use types below as metal::int32_t etc.
	 */

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
	
	using std::size_t;
	using usize = std::size_t;
	using isize = std::ptrdiff_t;
	
}
	
#endif // __MTL_STDINT_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_STDINT_TYPEDEFS__
	
	


namespace _VMTL {
	
	/// MARK: - Complex
#ifdef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#ifndef __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#define __MTL_COMPLEX_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using complex_float   = complex<float>;
		using complex_double  = complex<double>;
		using complex_ldouble = complex<long double>;
		
		using complex_int     = complex<int>;
		using complex_long    = complex<long>;
		using complex_llong   = complex<long long>;
		using complex_uint    = complex<unsigned int>;
		using complex_ulong   = complex<unsigned long>;
		using complex_ullong  = complex<unsigned long long>;
		
	}
	
#endif // __MTL_COMPLEX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_COMPLEX_TYPEDEFS__
	
	/// MARK: - Quaternion
#ifdef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#ifndef __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#define __MTL_QUATERNION_TYPEDEFS_INCLUDED__
	
	inline namespace short_types {
		
		using quaternion_float   = quaternion<float>;
		using quaternion_double  = quaternion<double>;
		using quaternion_ldouble = quaternion<long double>;
		
		using quaternion_int     = quaternion<int>;
		using quaternion_long    = quaternion<long>;
		using quaternion_llong   = quaternion<long long>;
		using quaternion_uint    = quaternion<unsigned int>;
		using quaternion_ulong   = quaternion<unsigned long>;
		using quaternion_ullong  = quaternion<unsigned long long>;
		
	}
	
#endif // __MTL_QUATERNION_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_QUATERNION_TYPEDEFS__
	
	// MARK: - Vector
#ifdef __MTL_DECLARE_VECTOR_TYPEDEFS__
#ifndef __MTL_VECTOR_TYPEDEFS_INCLUDED__
#define __MTL_VECTOR_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using vector2 = vector<T, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector3 = vector<T, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using vector4 = vector<T, 4, O>;
	
	inline namespace short_types {
		
		using size2            = vector2<std::size_t>;
		using size3            = vector3<std::size_t>;
		using size4            = vector4<std::size_t>;
		
		using usize2            = vector2<std::size_t>;
		using usize3            = vector3<std::size_t>;
		using usize4            = vector4<std::size_t>;
		
		using isize2            = vector2<std::ptrdiff_t>;
		using isize3            = vector3<std::ptrdiff_t>;
		using isize4            = vector4<std::ptrdiff_t>;
		
		using bool2            = vector2<bool>;
		using bool3            = vector3<bool>;
		using bool4            = vector4<bool>;
		using char2            = vector2<char>;
		using char3            = vector3<char>;
		using char4            = vector4<char>;
		using schar2           = vector2<char>;
		using schar3           = vector3<char>;
		using schar4           = vector4<char>;
		using uchar2           = vector2<unsigned char>;
		using uchar3           = vector3<unsigned char>;
		using uchar4           = vector4<unsigned char>;
		using short2           = vector2<short>;
		using short3           = vector3<short>;
		using short4           = vector4<short>;
		using ushort2          = vector2<unsigned short>;
		using ushort3          = vector3<unsigned short>;
		using ushort4          = vector4<unsigned short>;
		using int2             = vector2<int>;
		using int3             = vector3<int>;
		using int4             = vector4<int>;
		using uint2            = vector2<unsigned int>;
		using uint3            = vector3<unsigned int>;
		using uint4            = vector4<unsigned int>;
		using long2            = vector2<long>;
		using long3            = vector3<long>;
		using long4            = vector4<long>;
		using ulong2           = vector2<unsigned long>;
		using ulong3           = vector3<unsigned long>;
		using ulong4           = vector4<unsigned long>;
		using llong2           = vector2<long long>;
		using llong3           = vector3<long long>;
		using llong4           = vector4<long long>;
		using ullong2          = vector2<unsigned long long>;
		using ullong3          = vector3<unsigned long long>;
		using ullong4          = vector4<unsigned long long>;
		using float2           = vector2<float>;
		using float3           = vector3<float>;
		using float4           = vector4<float>;
		using double2          = vector2<double>;
		using double3          = vector3<double>;
		using double4          = vector4<double>;
		using ldouble2         = vector2<long double>;
		using ldouble3         = vector3<long double>;
		using ldouble4         = vector4<long double>;
		
		using packed_bool2     = vector2<bool,               vector_options{}.packed(true)>;
		using packed_bool3     = vector3<bool,               vector_options{}.packed(true)>;
		using packed_bool4     = vector4<bool,               vector_options{}.packed(true)>;
		using packed_char2     = vector2<char,               vector_options{}.packed(true)>;
		using packed_char3     = vector3<char,               vector_options{}.packed(true)>;
		using packed_char4     = vector4<char,               vector_options{}.packed(true)>;
		using packed_uchar2    = vector2<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar3    = vector3<unsigned char,      vector_options{}.packed(true)>;
		using packed_uchar4    = vector4<unsigned char,      vector_options{}.packed(true)>;
		using packed_short2    = vector2<short,              vector_options{}.packed(true)>;
		using packed_short3    = vector3<short,              vector_options{}.packed(true)>;
		using packed_short4    = vector4<short,              vector_options{}.packed(true)>;
		using packed_ushort2   = vector2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3   = vector3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4   = vector4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2      = vector2<int,                vector_options{}.packed(true)>;
		using packed_int3      = vector3<int,                vector_options{}.packed(true)>;
		using packed_int4      = vector4<int,                vector_options{}.packed(true)>;
		using packed_uint2     = vector2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3     = vector3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4     = vector4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2     = vector2<long,               vector_options{}.packed(true)>;
		using packed_long3     = vector3<long,               vector_options{}.packed(true)>;
		using packed_long4     = vector4<long,               vector_options{}.packed(true)>;
		using packed_ulong2    = vector2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3    = vector3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4    = vector4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2    = vector2<long long,          vector_options{}.packed(true)>;
		using packed_llong3    = vector3<long long,          vector_options{}.packed(true)>;
		using packed_llong4    = vector4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2   = vector2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3   = vector3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4   = vector4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2    = vector2<float,              vector_options{}.packed(true)>;
		using packed_float3    = vector3<float,              vector_options{}.packed(true)>;
		using packed_float4    = vector4<float,              vector_options{}.packed(true)>;
		using packed_double2   = vector2<double,             vector_options{}.packed(true)>;
		using packed_double3   = vector3<double,             vector_options{}.packed(true)>;
		using packed_double4   = vector4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2  = vector2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3  = vector3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4  = vector4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2    = vector2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3    = vector3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4    = vector4<bool,               vector_options{}.packed(false)>;
		using aligned_char2    = vector2<char,               vector_options{}.packed(false)>;
		using aligned_char3    = vector3<char,               vector_options{}.packed(false)>;
		using aligned_char4    = vector4<char,               vector_options{}.packed(false)>;
		using aligned_uchar2   = vector2<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar3   = vector3<unsigned char,      vector_options{}.packed(false)>;
		using aligned_uchar4   = vector4<unsigned char,      vector_options{}.packed(false)>;
		using aligned_short2   = vector2<short,              vector_options{}.packed(false)>;
		using aligned_short3   = vector3<short,              vector_options{}.packed(false)>;
		using aligned_short4   = vector4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2  = vector2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3  = vector3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4  = vector4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2     = vector2<int,                vector_options{}.packed(false)>;
		using aligned_int3     = vector3<int,                vector_options{}.packed(false)>;
		using aligned_int4     = vector4<int,                vector_options{}.packed(false)>;
		using aligned_uint2    = vector2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3    = vector3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4    = vector4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2    = vector2<long,               vector_options{}.packed(false)>;
		using aligned_long3    = vector3<long,               vector_options{}.packed(false)>;
		using aligned_long4    = vector4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2   = vector2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3   = vector3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4   = vector4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2   = vector2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3   = vector3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4   = vector4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2  = vector2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3  = vector3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4  = vector4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2   = vector2<float,              vector_options{}.packed(false)>;
		using aligned_float3   = vector3<float,              vector_options{}.packed(false)>;
		using aligned_float4   = vector4<float,              vector_options{}.packed(false)>;
		using aligned_double2  = vector2<double,             vector_options{}.packed(false)>;
		using aligned_double3  = vector3<double,             vector_options{}.packed(false)>;
		using aligned_double4  = vector4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2 = vector2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3 = vector3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4 = vector4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_VECTOR_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_VECTOR_TYPEDEFS__
	
	/// MARK: - Matrix
#ifdef __MTL_DECLARE_MATRIX_TYPEDEFS__
#ifndef __MTL_MATRIX_TYPEDEFS_INCLUDED__
#define __MTL_MATRIX_TYPEDEFS_INCLUDED__
	
	template <typename T, vector_options O = vector_options{}>
	using matrix2x2 = matrix<T, 2, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x3 = matrix<T, 2, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix2x4 = matrix<T, 2, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x2 = matrix<T, 3, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x3 = matrix<T, 3, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix3x4 = matrix<T, 3, 4, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x2 = matrix<T, 4, 2, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x3 = matrix<T, 4, 3, O>;
	template <typename T, vector_options O = vector_options{}>
	using matrix4x4 = matrix<T, 4, 4, O>;
	
	inline namespace short_types {
	
		using bool2x2            = matrix2x2<bool,               vector_options{}>;
		using bool2x3            = matrix2x3<bool,               vector_options{}>;
		using bool2x4            = matrix2x4<bool,               vector_options{}>;
		using bool3x2            = matrix3x2<bool,               vector_options{}>;
		using bool3x3            = matrix3x3<bool,               vector_options{}>;
		using bool3x4            = matrix3x4<bool,               vector_options{}>;
		using bool4x2            = matrix4x2<bool,               vector_options{}>;
		using bool4x3            = matrix4x3<bool,               vector_options{}>;
		using bool4x4            = matrix4x4<bool,               vector_options{}>;
		using short2x2           = matrix2x2<short,              vector_options{}>;
		using short2x3           = matrix2x3<short,              vector_options{}>;
		using short2x4           = matrix2x4<short,              vector_options{}>;
		using short3x2           = matrix3x2<short,              vector_options{}>;
		using short3x3           = matrix3x3<short,              vector_options{}>;
		using short3x4           = matrix3x4<short,              vector_options{}>;
		using short4x2           = matrix4x2<short,              vector_options{}>;
		using short4x3           = matrix4x3<short,              vector_options{}>;
		using short4x4           = matrix4x4<short,              vector_options{}>;
		using ushort2x2          = matrix2x2<unsigned short,     vector_options{}>;
		using ushort2x3          = matrix2x3<unsigned short,     vector_options{}>;
		using ushort2x4          = matrix2x4<unsigned short,     vector_options{}>;
		using ushort3x2          = matrix3x2<unsigned short,     vector_options{}>;
		using ushort3x3          = matrix3x3<unsigned short,     vector_options{}>;
		using ushort3x4          = matrix3x4<unsigned short,     vector_options{}>;
		using ushort4x2          = matrix4x2<unsigned short,     vector_options{}>;
		using ushort4x3          = matrix4x3<unsigned short,     vector_options{}>;
		using ushort4x4          = matrix4x4<unsigned short,     vector_options{}>;
		using int2x2             = matrix2x2<int,                vector_options{}>;
		using int2x3             = matrix2x3<int,                vector_options{}>;
		using int2x4             = matrix2x4<int,                vector_options{}>;
		using int3x2             = matrix3x2<int,                vector_options{}>;
		using int3x3             = matrix3x3<int,                vector_options{}>;
		using int3x4             = matrix3x4<int,                vector_options{}>;
		using int4x2             = matrix4x2<int,                vector_options{}>;
		using int4x3             = matrix4x3<int,                vector_options{}>;
		using int4x4             = matrix4x4<int,                vector_options{}>;
		using uint2x2            = matrix2x2<unsigned int,       vector_options{}>;
		using uint2x3            = matrix2x3<unsigned int,       vector_options{}>;
		using uint2x4            = matrix2x4<unsigned int,       vector_options{}>;
		using uint3x2            = matrix3x2<unsigned int,       vector_options{}>;
		using uint3x3            = matrix3x3<unsigned int,       vector_options{}>;
		using uint3x4            = matrix3x4<unsigned int,       vector_options{}>;
		using uint4x2            = matrix4x2<unsigned int,       vector_options{}>;
		using uint4x3            = matrix4x3<unsigned int,       vector_options{}>;
		using uint4x4            = matrix4x4<unsigned int,       vector_options{}>;
		using long2x2            = matrix2x2<long,               vector_options{}>;
		using long2x3            = matrix2x3<long,               vector_options{}>;
		using long2x4            = matrix2x4<long,               vector_options{}>;
		using long3x2            = matrix3x2<long,               vector_options{}>;
		using long3x3            = matrix3x3<long,               vector_options{}>;
		using long3x4            = matrix3x4<long,               vector_options{}>;
		using long4x2            = matrix4x2<long,               vector_options{}>;
		using long4x3            = matrix4x3<long,               vector_options{}>;
		using long4x4            = matrix4x4<long,               vector_options{}>;
		using ulong2x2           = matrix2x2<unsigned long,      vector_options{}>;
		using ulong2x3           = matrix2x3<unsigned long,      vector_options{}>;
		using ulong2x4           = matrix2x4<unsigned long,      vector_options{}>;
		using ulong3x2           = matrix3x2<unsigned long,      vector_options{}>;
		using ulong3x3           = matrix3x3<unsigned long,      vector_options{}>;
		using ulong3x4           = matrix3x4<unsigned long,      vector_options{}>;
		using ulong4x2           = matrix4x2<unsigned long,      vector_options{}>;
		using ulong4x3           = matrix4x3<unsigned long,      vector_options{}>;
		using ulong4x4           = matrix4x4<unsigned long,      vector_options{}>;
		using llong2x2           = matrix2x2<long long,          vector_options{}>;
		using llong2x3           = matrix2x3<long long,          vector_options{}>;
		using llong2x4           = matrix2x4<long long,          vector_options{}>;
		using llong3x2           = matrix3x2<long long,          vector_options{}>;
		using llong3x3           = matrix3x3<long long,          vector_options{}>;
		using llong3x4           = matrix3x4<long long,          vector_options{}>;
		using llong4x2           = matrix4x2<long long,          vector_options{}>;
		using llong4x3           = matrix4x3<long long,          vector_options{}>;
		using llong4x4           = matrix4x4<long long,          vector_options{}>;
		using ullong2x2          = matrix2x2<unsigned long long, vector_options{}>;
		using ullong2x3          = matrix2x3<unsigned long long, vector_options{}>;
		using ullong2x4          = matrix2x4<unsigned long long, vector_options{}>;
		using ullong3x2          = matrix3x2<unsigned long long, vector_options{}>;
		using ullong3x3          = matrix3x3<unsigned long long, vector_options{}>;
		using ullong3x4          = matrix3x4<unsigned long long, vector_options{}>;
		using ullong4x2          = matrix4x2<unsigned long long, vector_options{}>;
		using ullong4x3          = matrix4x3<unsigned long long, vector_options{}>;
		using ullong4x4          = matrix4x4<unsigned long long, vector_options{}>;
		using float2x2           = matrix2x2<float,              vector_options{}>;
		using float2x3           = matrix2x3<float,              vector_options{}>;
		using float2x4           = matrix2x4<float,              vector_options{}>;
		using float3x2           = matrix3x2<float,              vector_options{}>;
		using float3x3           = matrix3x3<float,              vector_options{}>;
		using float3x4           = matrix3x4<float,              vector_options{}>;
		using float4x2           = matrix4x2<float,              vector_options{}>;
		using float4x3           = matrix4x3<float,              vector_options{}>;
		using float4x4           = matrix4x4<float,              vector_options{}>;
		using double2x2          = matrix2x2<double,             vector_options{}>;
		using double2x3          = matrix2x3<double,             vector_options{}>;
		using double2x4          = matrix2x4<double,             vector_options{}>;
		using double3x2          = matrix3x2<double,             vector_options{}>;
		using double3x3          = matrix3x3<double,             vector_options{}>;
		using double3x4          = matrix3x4<double,             vector_options{}>;
		using double4x2          = matrix4x2<double,             vector_options{}>;
		using double4x3          = matrix4x3<double,             vector_options{}>;
		using double4x4          = matrix4x4<double,             vector_options{}>;
		using ldouble2x2         = matrix2x2<long double,        vector_options{}>;
		using ldouble2x3         = matrix2x3<long double,        vector_options{}>;
		using ldouble2x4         = matrix2x4<long double,        vector_options{}>;
		using ldouble3x2         = matrix3x2<long double,        vector_options{}>;
		using ldouble3x3         = matrix3x3<long double,        vector_options{}>;
		using ldouble3x4         = matrix3x4<long double,        vector_options{}>;
		using ldouble4x2         = matrix4x2<long double,        vector_options{}>;
		using ldouble4x3         = matrix4x3<long double,        vector_options{}>;
		using ldouble4x4         = matrix4x4<long double,        vector_options{}>;
	 
		using packed_bool2x2     = matrix2x2<bool,               vector_options{}.packed(true)>;
		using packed_bool2x3     = matrix2x3<bool,               vector_options{}.packed(true)>;
		using packed_bool2x4     = matrix2x4<bool,               vector_options{}.packed(true)>;
		using packed_bool3x2     = matrix3x2<bool,               vector_options{}.packed(true)>;
		using packed_bool3x3     = matrix3x3<bool,               vector_options{}.packed(true)>;
		using packed_bool3x4     = matrix3x4<bool,               vector_options{}.packed(true)>;
		using packed_bool4x2     = matrix4x2<bool,               vector_options{}.packed(true)>;
		using packed_bool4x3     = matrix4x3<bool,               vector_options{}.packed(true)>;
		using packed_bool4x4     = matrix4x4<bool,               vector_options{}.packed(true)>;
		using packed_short2x2    = matrix2x2<short,              vector_options{}.packed(true)>;
		using packed_short2x3    = matrix2x3<short,              vector_options{}.packed(true)>;
		using packed_short2x4    = matrix2x4<short,              vector_options{}.packed(true)>;
		using packed_short3x2    = matrix3x2<short,              vector_options{}.packed(true)>;
		using packed_short3x3    = matrix3x3<short,              vector_options{}.packed(true)>;
		using packed_short3x4    = matrix3x4<short,              vector_options{}.packed(true)>;
		using packed_short4x2    = matrix4x2<short,              vector_options{}.packed(true)>;
		using packed_short4x3    = matrix4x3<short,              vector_options{}.packed(true)>;
		using packed_short4x4    = matrix4x4<short,              vector_options{}.packed(true)>;
		using packed_ushort2x2   = matrix2x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x3   = matrix2x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort2x4   = matrix2x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x2   = matrix3x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x3   = matrix3x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort3x4   = matrix3x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x2   = matrix4x2<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x3   = matrix4x3<unsigned short,     vector_options{}.packed(true)>;
		using packed_ushort4x4   = matrix4x4<unsigned short,     vector_options{}.packed(true)>;
		using packed_int2x2      = matrix2x2<int,                vector_options{}.packed(true)>;
		using packed_int2x3      = matrix2x3<int,                vector_options{}.packed(true)>;
		using packed_int2x4      = matrix2x4<int,                vector_options{}.packed(true)>;
		using packed_int3x2      = matrix3x2<int,                vector_options{}.packed(true)>;
		using packed_int3x3      = matrix3x3<int,                vector_options{}.packed(true)>;
		using packed_int3x4      = matrix3x4<int,                vector_options{}.packed(true)>;
		using packed_int4x2      = matrix4x2<int,                vector_options{}.packed(true)>;
		using packed_int4x3      = matrix4x3<int,                vector_options{}.packed(true)>;
		using packed_int4x4      = matrix4x4<int,                vector_options{}.packed(true)>;
		using packed_uint2x2     = matrix2x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x3     = matrix2x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint2x4     = matrix2x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x2     = matrix3x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x3     = matrix3x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint3x4     = matrix3x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x2     = matrix4x2<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x3     = matrix4x3<unsigned int,       vector_options{}.packed(true)>;
		using packed_uint4x4     = matrix4x4<unsigned int,       vector_options{}.packed(true)>;
		using packed_long2x2     = matrix2x2<long,               vector_options{}.packed(true)>;
		using packed_long2x3     = matrix2x3<long,               vector_options{}.packed(true)>;
		using packed_long2x4     = matrix2x4<long,               vector_options{}.packed(true)>;
		using packed_long3x2     = matrix3x2<long,               vector_options{}.packed(true)>;
		using packed_long3x3     = matrix3x3<long,               vector_options{}.packed(true)>;
		using packed_long3x4     = matrix3x4<long,               vector_options{}.packed(true)>;
		using packed_long4x2     = matrix4x2<long,               vector_options{}.packed(true)>;
		using packed_long4x3     = matrix4x3<long,               vector_options{}.packed(true)>;
		using packed_long4x4     = matrix4x4<long,               vector_options{}.packed(true)>;
		using packed_ulong2x2    = matrix2x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x3    = matrix2x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong2x4    = matrix2x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x2    = matrix3x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x3    = matrix3x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong3x4    = matrix3x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x2    = matrix4x2<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x3    = matrix4x3<unsigned long,      vector_options{}.packed(true)>;
		using packed_ulong4x4    = matrix4x4<unsigned long,      vector_options{}.packed(true)>;
		using packed_llong2x2    = matrix2x2<long long,          vector_options{}.packed(true)>;
		using packed_llong2x3    = matrix2x3<long long,          vector_options{}.packed(true)>;
		using packed_llong2x4    = matrix2x4<long long,          vector_options{}.packed(true)>;
		using packed_llong3x2    = matrix3x2<long long,          vector_options{}.packed(true)>;
		using packed_llong3x3    = matrix3x3<long long,          vector_options{}.packed(true)>;
		using packed_llong3x4    = matrix3x4<long long,          vector_options{}.packed(true)>;
		using packed_llong4x2    = matrix4x2<long long,          vector_options{}.packed(true)>;
		using packed_llong4x3    = matrix4x3<long long,          vector_options{}.packed(true)>;
		using packed_llong4x4    = matrix4x4<long long,          vector_options{}.packed(true)>;
		using packed_ullong2x2   = matrix2x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x3   = matrix2x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong2x4   = matrix2x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x2   = matrix3x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x3   = matrix3x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong3x4   = matrix3x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x2   = matrix4x2<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x3   = matrix4x3<unsigned long long, vector_options{}.packed(true)>;
		using packed_ullong4x4   = matrix4x4<unsigned long long, vector_options{}.packed(true)>;
		using packed_float2x2    = matrix2x2<float,              vector_options{}.packed(true)>;
		using packed_float2x3    = matrix2x3<float,              vector_options{}.packed(true)>;
		using packed_float2x4    = matrix2x4<float,              vector_options{}.packed(true)>;
		using packed_float3x2    = matrix3x2<float,              vector_options{}.packed(true)>;
		using packed_float3x3    = matrix3x3<float,              vector_options{}.packed(true)>;
		using packed_float3x4    = matrix3x4<float,              vector_options{}.packed(true)>;
		using packed_float4x2    = matrix4x2<float,              vector_options{}.packed(true)>;
		using packed_float4x3    = matrix4x3<float,              vector_options{}.packed(true)>;
		using packed_float4x4    = matrix4x4<float,              vector_options{}.packed(true)>;
		using packed_double2x2   = matrix2x2<double,             vector_options{}.packed(true)>;
		using packed_double2x3   = matrix2x3<double,             vector_options{}.packed(true)>;
		using packed_double2x4   = matrix2x4<double,             vector_options{}.packed(true)>;
		using packed_double3x2   = matrix3x2<double,             vector_options{}.packed(true)>;
		using packed_double3x3   = matrix3x3<double,             vector_options{}.packed(true)>;
		using packed_double3x4   = matrix3x4<double,             vector_options{}.packed(true)>;
		using packed_double4x2   = matrix4x2<double,             vector_options{}.packed(true)>;
		using packed_double4x3   = matrix4x3<double,             vector_options{}.packed(true)>;
		using packed_double4x4   = matrix4x4<double,             vector_options{}.packed(true)>;
		using packed_ldouble2x2  = matrix2x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x3  = matrix2x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble2x4  = matrix2x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x2  = matrix3x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x3  = matrix3x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble3x4  = matrix3x4<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x2  = matrix4x2<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x3  = matrix4x3<long double,        vector_options{}.packed(true)>;
		using packed_ldouble4x4  = matrix4x4<long double,        vector_options{}.packed(true)>;
		
		using aligned_bool2x2    = matrix2x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x3    = matrix2x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool2x4    = matrix2x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x2    = matrix3x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x3    = matrix3x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool3x4    = matrix3x4<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x2    = matrix4x2<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x3    = matrix4x3<bool,               vector_options{}.packed(false)>;
		using aligned_bool4x4    = matrix4x4<bool,               vector_options{}.packed(false)>;
		using aligned_short2x2   = matrix2x2<short,              vector_options{}.packed(false)>;
		using aligned_short2x3   = matrix2x3<short,              vector_options{}.packed(false)>;
		using aligned_short2x4   = matrix2x4<short,              vector_options{}.packed(false)>;
		using aligned_short3x2   = matrix3x2<short,              vector_options{}.packed(false)>;
		using aligned_short3x3   = matrix3x3<short,              vector_options{}.packed(false)>;
		using aligned_short3x4   = matrix3x4<short,              vector_options{}.packed(false)>;
		using aligned_short4x2   = matrix4x2<short,              vector_options{}.packed(false)>;
		using aligned_short4x3   = matrix4x3<short,              vector_options{}.packed(false)>;
		using aligned_short4x4   = matrix4x4<short,              vector_options{}.packed(false)>;
		using aligned_ushort2x2  = matrix2x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x3  = matrix2x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort2x4  = matrix2x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x2  = matrix3x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x3  = matrix3x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort3x4  = matrix3x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x2  = matrix4x2<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x3  = matrix4x3<unsigned short,     vector_options{}.packed(false)>;
		using aligned_ushort4x4  = matrix4x4<unsigned short,     vector_options{}.packed(false)>;
		using aligned_int2x2     = matrix2x2<int,                vector_options{}.packed(false)>;
		using aligned_int2x3     = matrix2x3<int,                vector_options{}.packed(false)>;
		using aligned_int2x4     = matrix2x4<int,                vector_options{}.packed(false)>;
		using aligned_int3x2     = matrix3x2<int,                vector_options{}.packed(false)>;
		using aligned_int3x3     = matrix3x3<int,                vector_options{}.packed(false)>;
		using aligned_int3x4     = matrix3x4<int,                vector_options{}.packed(false)>;
		using aligned_int4x2     = matrix4x2<int,                vector_options{}.packed(false)>;
		using aligned_int4x3     = matrix4x3<int,                vector_options{}.packed(false)>;
		using aligned_int4x4     = matrix4x4<int,                vector_options{}.packed(false)>;
		using aligned_uint2x2    = matrix2x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x3    = matrix2x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint2x4    = matrix2x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x2    = matrix3x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x3    = matrix3x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint3x4    = matrix3x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x2    = matrix4x2<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x3    = matrix4x3<unsigned int,       vector_options{}.packed(false)>;
		using aligned_uint4x4    = matrix4x4<unsigned int,       vector_options{}.packed(false)>;
		using aligned_long2x2    = matrix2x2<long,               vector_options{}.packed(false)>;
		using aligned_long2x3    = matrix2x3<long,               vector_options{}.packed(false)>;
		using aligned_long2x4    = matrix2x4<long,               vector_options{}.packed(false)>;
		using aligned_long3x2    = matrix3x2<long,               vector_options{}.packed(false)>;
		using aligned_long3x3    = matrix3x3<long,               vector_options{}.packed(false)>;
		using aligned_long3x4    = matrix3x4<long,               vector_options{}.packed(false)>;
		using aligned_long4x2    = matrix4x2<long,               vector_options{}.packed(false)>;
		using aligned_long4x3    = matrix4x3<long,               vector_options{}.packed(false)>;
		using aligned_long4x4    = matrix4x4<long,               vector_options{}.packed(false)>;
		using aligned_ulong2x2   = matrix2x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x3   = matrix2x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong2x4   = matrix2x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x2   = matrix3x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x3   = matrix3x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong3x4   = matrix3x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x2   = matrix4x2<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x3   = matrix4x3<unsigned long,      vector_options{}.packed(false)>;
		using aligned_ulong4x4   = matrix4x4<unsigned long,      vector_options{}.packed(false)>;
		using aligned_llong2x2   = matrix2x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x3   = matrix2x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong2x4   = matrix2x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x2   = matrix3x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x3   = matrix3x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong3x4   = matrix3x4<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x2   = matrix4x2<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x3   = matrix4x3<long long,          vector_options{}.packed(false)>;
		using aligned_llong4x4   = matrix4x4<long long,          vector_options{}.packed(false)>;
		using aligned_ullong2x2  = matrix2x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x3  = matrix2x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong2x4  = matrix2x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x2  = matrix3x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x3  = matrix3x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong3x4  = matrix3x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x2  = matrix4x2<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x3  = matrix4x3<unsigned long long, vector_options{}.packed(false)>;
		using aligned_ullong4x4  = matrix4x4<unsigned long long, vector_options{}.packed(false)>;
		using aligned_float2x2   = matrix2x2<float,              vector_options{}.packed(false)>;
		using aligned_float2x3   = matrix2x3<float,              vector_options{}.packed(false)>;
		using aligned_float2x4   = matrix2x4<float,              vector_options{}.packed(false)>;
		using aligned_float3x2   = matrix3x2<float,              vector_options{}.packed(false)>;
		using aligned_float3x3   = matrix3x3<float,              vector_options{}.packed(false)>;
		using aligned_float3x4   = matrix3x4<float,              vector_options{}.packed(false)>;
		using aligned_float4x2   = matrix4x2<float,              vector_options{}.packed(false)>;
		using aligned_float4x3   = matrix4x3<float,              vector_options{}.packed(false)>;
		using aligned_float4x4   = matrix4x4<float,              vector_options{}.packed(false)>;
		using aligned_double2x2  = matrix2x2<double,             vector_options{}.packed(false)>;
		using aligned_double2x3  = matrix2x3<double,             vector_options{}.packed(false)>;
		using aligned_double2x4  = matrix2x4<double,             vector_options{}.packed(false)>;
		using aligned_double3x2  = matrix3x2<double,             vector_options{}.packed(false)>;
		using aligned_double3x3  = matrix3x3<double,             vector_options{}.packed(false)>;
		using aligned_double3x4  = matrix3x4<double,             vector_options{}.packed(false)>;
		using aligned_double4x2  = matrix4x2<double,             vector_options{}.packed(false)>;
		using aligned_double4x3  = matrix4x3<double,             vector_options{}.packed(false)>;
		using aligned_double4x4  = matrix4x4<double,             vector_options{}.packed(false)>;
		using aligned_ldouble2x2 = matrix2x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x3 = matrix2x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble2x4 = matrix2x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x2 = matrix3x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x3 = matrix3x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble3x4 = matrix3x4<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x2 = matrix4x2<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x3 = matrix4x3<long double,        vector_options{}.packed(false)>;
		using aligned_ldouble4x4 = matrix4x4<long double,        vector_options{}.packed(false)>;
		
	}
	
#endif // __MTL_MATRIX_TYPEDEFS_INCLUDED__
#endif // __MTL_DECLARE_MATRIX_TYPEDEFS__
	
}





#include <cmath>
#include <iosfwd>

/// MARK: - Synopsis
/*
 
 */

namespace _VMTL {
	
	inline constexpr vector_options __mtl_quaternion_vector_options = vector_options{}.packed(false);

	/// MARK: - struct quaternion
	template <real_scalar T>
	struct quaternion<T>: public vector<T, 4, __mtl_quaternion_vector_options> {
		static constexpr auto __mtl_options = __mtl_quaternion_vector_options;
		using __mtl_base = vector<T, 4, __mtl_options>;
		using typename __mtl_base::value_type;
		
	public:
		using __vector_data_<T, 4, __mtl_options>::real;
		using __vector_data_<T, 4, __mtl_options>::imag;
		using __vector_data_<T, 4, __mtl_options>::vector;
		
		using __imag_t = _VMTL::vector<T, 3, __mtl_options>;
		
	public:
		/// Value Constructors
		quaternion() = default;
		constexpr quaternion(T const& real): __mtl_base(real, 0, 0, 0) {}
		template <vector_options P = __mtl_quaternion_vector_options>
		constexpr quaternion(T const& real,  _VMTL::vector<T, 3, P> const& imag): __mtl_base(real, imag.__mtl_at(0), imag.__mtl_at(1), imag.__mtl_at(2)) {}
		constexpr quaternion(T const& a, T const& b, T const& c, T const& d): __mtl_base(a, b, c, d) {}
		template <std::convertible_to<T> U>
		constexpr quaternion(complex<U> const& z): quaternion(z.__mtl_at(0), z.__mtl_at(1), 0, 0) {}
		template <vector_options P = __mtl_quaternion_vector_options>
		constexpr quaternion(_VMTL::vector<T, 4, P> const& v): __mtl_base(v) {}
		
		/// Conversion Constructor
		template <std::convertible_to<T> U>
		constexpr quaternion(quaternion<U> const& rhs): __mtl_base(rhs) {}
		
		quaternion& operator=(quaternion const&)& = default;
		
		/// MARK: - Arithmetic Assignment
		constexpr quaternion& operator+=(quaternion const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		constexpr quaternion& operator+=(T const& rhs)& {
			*this = *this + rhs;
			return *this;
		}
		constexpr quaternion& operator-=(quaternion const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		constexpr quaternion& operator-=(T const& rhs)& {
			*this = *this - rhs;
			return *this;
		}
		constexpr quaternion& operator*=(quaternion const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		constexpr quaternion& operator*=(T const& rhs)& {
			*this = *this * rhs;
			return *this;
		}
		constexpr quaternion& operator/=(quaternion const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
		constexpr quaternion& operator/=(T const& rhs)& {
			*this = *this / rhs;
			return *this;
		}
	};
	
	/// MARK: - Misc
	template <real_scalar T>
	quaternion(T) -> quaternion<T>;
	template <real_scalar T, real_scalar U, real_scalar V, real_scalar W>
	quaternion(T, U, V, W) -> quaternion<__mtl_promote(T, U, V, W)>;
	template <real_scalar T, real_scalar U, vector_options O = vector_options{}>
	quaternion(T, _VMTL::vector<U, 3, O>) -> quaternion<__mtl_promote(T, U)>;
	
	/// real, imag:
	template <typename T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr T real(quaternion<T> const& z) { return z.__mtl_at(0); }
	template <typename T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr vector<T, 3, __mtl_quaternion_vector_options> imag(quaternion<T> const& z) {
		return {
			z.__mtl_at(1), z.__mtl_at(2), z.__mtl_at(3)
		};
	}
	
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr vector<T, 4, __mtl_quaternion_vector_options>& __mtl_as_vector(quaternion<T>& z) {
		return static_cast<vector<T, 4, quaternion<T>::__mtl_options>&>(z);
	}
	template <typename T>
	__mtl_mathfunction __mtl_always_inline
	constexpr vector<T, 4, __mtl_quaternion_vector_options> const& __mtl_as_vector(quaternion<T> const& z) {
		return static_cast<vector<T, 4, quaternion<T>::__mtl_options> const&>(z);
	}
	
	/// isnan
	template <typename T>
	constexpr bool isnan(quaternion<T> const& z) {
		using std::isnan;
		return isnan(z.__mtl_at(0)) || isnan(z.__mtl_at(1)) || isnan(z.__mtl_at(2)) || isnan(z.__mtl_at(3));
	}
	
	/// isinf
	template <typename T>
	constexpr bool isinf(quaternion<T> const& z) {
		using std::isinf;
		return isinf(z.__mtl_at(0)) || isinf(z.__mtl_at(1)) || isinf(z.__mtl_at(2)) || isinf(z.__mtl_at(3));
	}
	
	/// isfinite
	template <typename T>
	constexpr bool isfinite(quaternion<T> const& z) {
		using std::isfinite;
		return isfinite(z.__mtl_at(0)) || isfinite(z.__mtl_at(1)) || isfinite(z.__mtl_at(2)) || isfinite(z.__mtl_at(3));
	}
	
	/// isnormal
	template <typename T>
	constexpr bool isnormal(quaternion<T> const& z) {
		using std::isnormal;
		return isnormal(z.__mtl_at(0)) || isnormal(z.__mtl_at(1)) || isnormal(z.__mtl_at(2)) || isnormal(z.__mtl_at(3));
	}
	
	/// MARK: - Literals
	inline namespace literals {
		inline namespace quaternion_literals {
			/*
			 _i* literals are defined in complex.hpp and can be used in conjunction with these
			 'using namespace mtl::quaternion_literals;' also pulls in the _i* complex literals
			 */
			inline constexpr quaternion<double>             operator"" _j(long double x) { return { 0, 0, static_cast<double>(x), 0 }; }
			inline constexpr quaternion<float>              operator"" _jf(long double x) { return { 0, 0, static_cast<float>(x), 0 }; }
			inline constexpr quaternion<long double>        operator"" _jld(long double x) { return { 0, 0, static_cast<long double>(x), 0 }; }
			inline constexpr quaternion<int>                operator"" _j(unsigned long long x) { return { 0, 0, static_cast<int>(x), 0 }; }
			inline constexpr quaternion<long>               operator"" _jl(unsigned long long x) { return { 0, 0, static_cast<long>(x), 0 }; }
			inline constexpr quaternion<long long>          operator"" _jll(unsigned long long x) { return { 0, 0, static_cast<long long>(x), 0 }; }
			inline constexpr quaternion<unsigned int>       operator"" _ju(unsigned long long x) { return { 0, 0, static_cast<unsigned int>(x), 0 }; }
			inline constexpr quaternion<unsigned long>      operator"" _jul(unsigned long long x) { return { 0, 0, static_cast<unsigned long>(x), 0 }; }
			inline constexpr quaternion<unsigned long long> operator"" _jull(unsigned long long x) { return { 0, 0, static_cast<unsigned long long>(x), 0 }; }
			inline constexpr quaternion<double>             operator"" _k(long double x) { return { 0, 0, 0, static_cast<double>(x) }; }
			inline constexpr quaternion<float>              operator"" _kf(long double x) { return { 0, 0, 0, static_cast<float>(x) }; }
			inline constexpr quaternion<long double>        operator"" _kld(long double x) { return { 0, 0, 0, static_cast<long double>(x) }; }
			inline constexpr quaternion<int>                operator"" _k(unsigned long long x) { return { 0, 0, 0, static_cast<int>(x) }; }
			inline constexpr quaternion<long>               operator"" _kl(unsigned long long x) { return { 0, 0, 0, static_cast<long>(x) }; }
			inline constexpr quaternion<long long>          operator"" _kll(unsigned long long x) { return { 0, 0, 0, static_cast<long long>(x) }; }
			inline constexpr quaternion<unsigned int>       operator"" _ku(unsigned long long x) { return { 0, 0, 0, static_cast<unsigned int>(x) }; }
			inline constexpr quaternion<unsigned long>      operator"" _kul(unsigned long long x) { return { 0, 0, 0, static_cast<unsigned long>(x) }; }
			inline constexpr quaternion<unsigned long long> operator"" _kull(unsigned long long x) { return { 0, 0, 0, static_cast<unsigned long long>(x) }; }
		}
	}
	
	/// MARK: - Quaternion Arithmetic
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<T> operator+(quaternion<T> const& z) {
		return z;
	}
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<T> operator-(quaternion<T> const& z) {
		return -__mtl_as_vector(z);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator+(quaternion<T> const& a, quaternion<U> const& b) {
		return __mtl_as_vector(a) + __mtl_as_vector(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator+(quaternion<T> const& a, complex<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) + real(b), imag(b) + a.__mtl_at(1), a.__mtl_at(2), a.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator+(quaternion<T> const& a, U const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) + b, a.__mtl_at(1), a.__mtl_at(2), a.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator+(complex<T> const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) + real(b), imag(a) + b.__mtl_at(1), b.__mtl_at(2), b.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator+(T const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(a + real(b), b.__mtl_at(1), b.__mtl_at(2), b.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator-(quaternion<T> const& a, quaternion<U> const& b) {
		return __mtl_as_vector(a) - __mtl_as_vector(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator-(quaternion<T> const& a, complex<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) - real(b), a.__mtl_at(1) - imag(b), a.__mtl_at(2), a.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator-(quaternion<T> const& a, U const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) - b, a.__mtl_at(1), a.__mtl_at(2), a.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator-(complex<T> const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(real(a) - real(b), imag(a) - b.__mtl_at(1), -b.__mtl_at(2), -b.__mtl_at(3));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator-(T const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(a - real(b), -imag(b));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator*(quaternion<T> const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(
			a.__mtl_at(0) * b.__mtl_at(0) - a.__mtl_at(1) * b.__mtl_at(1) - a.__mtl_at(2) * b.__mtl_at(2) - a.__mtl_at(3) * b.__mtl_at(3),  // 1
			a.__mtl_at(0) * b.__mtl_at(1) + a.__mtl_at(1) * b.__mtl_at(0) + a.__mtl_at(2) * b.__mtl_at(3) - a.__mtl_at(3) * b.__mtl_at(2),  // i
			a.__mtl_at(0) * b.__mtl_at(2) - a.__mtl_at(1) * b.__mtl_at(3) + a.__mtl_at(2) * b.__mtl_at(0) + a.__mtl_at(3) * b.__mtl_at(1),  // j
			a.__mtl_at(0) * b.__mtl_at(3) + a.__mtl_at(1) * b.__mtl_at(2) - a.__mtl_at(2) * b.__mtl_at(1) + a.__mtl_at(3) * b.__mtl_at(0)   // k
		);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator*(quaternion<T> const& a, complex<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(
			 a.__mtl_at(0) * b.__mtl_at(0) - a.__mtl_at(1) * b.__mtl_at(1),  // 1
			 a.__mtl_at(0) * b.__mtl_at(1) + a.__mtl_at(1) * b.__mtl_at(0),  // i
			 a.__mtl_at(2) * b.__mtl_at(0) + a.__mtl_at(3) * b.__mtl_at(1),  // j
			-a.__mtl_at(2) * b.__mtl_at(1) + a.__mtl_at(3) * b.__mtl_at(0)   // k
		);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator*(complex<T> const& a, quaternion<U> const& b) {
		return quaternion<__mtl_promote(T, U)>(
			a.__mtl_at(0) * b.__mtl_at(0) - a.__mtl_at(1) * b.__mtl_at(1),  // 1
			a.__mtl_at(0) * b.__mtl_at(1) + a.__mtl_at(1) * b.__mtl_at(0),  // i
			a.__mtl_at(0) * b.__mtl_at(2) - a.__mtl_at(1) * b.__mtl_at(3),  // j
			a.__mtl_at(0) * b.__mtl_at(3) + a.__mtl_at(1) * b.__mtl_at(2)   // k
		);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator*(quaternion<T> const& a, U const& b) {
		return __mtl_as_vector(a) * b;
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator*(T const& a, quaternion<U> const& b) {
		return a * __mtl_as_vector(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator/(quaternion<T> const& a, quaternion<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator/(complex<T> const& a, quaternion<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator/(quaternion<T> const& a, complex<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator/(quaternion<T> const& a, U const& b) {
		return __mtl_as_vector(a) / b;
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_promote(T, U)> operator/(T const& a, quaternion<U> const& b) {
		return a * conj(b) / norm_squared(b);
	}
	
	/// MARK: - operator==
	template <typename T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(quaternion<T> const& a, quaternion<U> const& b) {
		return __mtl_as_vector(a) == __mtl_as_vector(b);
	}
	
	template <typename T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(quaternion<T> const& a, complex<U> const& b) {
		return real(a) == real(b) && a.__mtl_at(1) == imag(b) && a.__mtl_at(2) == 0 && a.__mtl_at(3) == 0;
	}
	
	template <typename T, real_scalar U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(quaternion<T> const& a, U const& b) {
		return real(a) == b && a.__mtl_at(1) == 0 && a.__mtl_at(2) == 0 && a.__mtl_at(3) == 0;
	}
	
	template <typename T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(complex<T> const& a, quaternion<U> const& b) {
		return real(a) == real(b) && imag(a) == b.__mtl_at(1) && 0 == b.__mtl_at(2) && 0 == b.__mtl_at(3);
	}
	
	template <real_scalar T, typename U>
	requires requires(T&& t, U&& u) { { t == u } -> std::convertible_to<bool>; }
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr bool operator==(T const& a, quaternion<U> const& b) {
		return a == real(b) && 0 == b.__mtl_at(1) && 0 == b.__mtl_at(2) && 0 == b.__mtl_at(3);
	}

	
	/// MARK: - Quaternion Math Functions
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<T> conj(quaternion<T> const& z) {
		return { z.__mtl_at(0), -z.__mtl_at(1), -z.__mtl_at(2), -z.__mtl_at(3) };
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<T> inverse(quaternion<T> const& z) {
		return conj(z) / length_squared(z);
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<T> normalize(quaternion<T> const& z) {
		return normalize(__mtl_as_vector(z));
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr __mtl_floatify(T) abs(quaternion<T> const& z) {
		return norm(z);
	}
	
	/// MARK: Power Functions
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	quaternion<__mtl_floatify(T)> exp(quaternion<T> const& z) {
		auto const r_exp = std::exp(real(z));
		if (z.vector == 0) {
			return r_exp;
		}
		auto const _vnorm = norm(z.vector);
		return r_exp * (std::cos(_vnorm) + quaternion{ 0, z.imag } * (std::sin(_vnorm) / _vnorm));
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	quaternion<__mtl_floatify(T)> log(quaternion<T> const& z) {
		__mtl_expect(z != 0);
		auto const _norm = _VMTL::norm(z);
		if (z.vector == 0) {
			return { std::log(_norm), 0, 0, 0 };
		}
		auto const _vnorm = norm(z.vector);
		return { std::log(_norm), z.vector * std::acos(z.real / _norm) / _vnorm };
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	quaternion<__mtl_floatify(T)> log10(quaternion<T> const& z) {
		return _VMTL::log(z) / std::log(T(10));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> pow(quaternion<T> const& x, quaternion<U> const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> pow(complex<T> const& x, quaternion<U> const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> pow(T const& x, quaternion<U> const& y) {
		return _VMTL::exp(y * std::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> pow(quaternion<T> const& x, complex<U> const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T, real_scalar U>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> pow(quaternion<T> const& x, U const& y) {
		return _VMTL::exp(y * _VMTL::log(x));
	}
	
	template <real_scalar T>
	__mtl_mathfunction __mtl_always_inline __mtl_interface_export
	quaternion<__mtl_floatify(T)> sqrt(quaternion<T> const& z) {
		__mtl_expect(real(z) >= 0 || imag(z) != 0);
		auto const r = _VMTL::abs(z);
		return std::sqrt(r) * (z + r) / _VMTL::abs(z + r);
	}
	
	/// MARK: Hyperbolic Functions
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> sinh(quaternion<T> const& _z) {
		using F = __mtl_floatify(T);
		quaternion<F> z = _z;
		auto const v_norm = _VMTL::norm(z.vector);
		__mtl_safe_math_if (std::isinf(real(z)) && !std::isinf(v_norm))
			return complex<F>(real(z), F(NAN));
		__mtl_safe_math_if (real(z) == 0 && !std::isinf(v_norm))
			return complex<F>(real(z), F(NAN));
		__mtl_safe_math_if (v_norm == 0 && !std::isinf(real(z)))
			return z;
		return {
			std::sinh(real(z)) * std::cos(v_norm),
			std::cosh(real(z)) * std::sin(v_norm) / v_norm * z.vector
		};
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> cosh(quaternion<T> const& _z) {
		using F = __mtl_floatify(T);
		quaternion<F> z = _z;
		auto const v_norm = _VMTL::norm(z.vector);
		__mtl_safe_math_if (std::isinf(real(z)) && !std::isinf(v_norm))
			return { std::abs(real(z)), F(NAN), F(NAN), F(NAN) };
		__mtl_safe_math_if (real(z) == 0 && !std::isinf(v_norm))
			return { F(NAN), 0, 0, 0 };
		__mtl_safe_math_if (real(z) == 0 && v_norm == 0)
			return { F(1), 0, 0, 0 };
		__mtl_safe_math_if (v_norm == 0 && !std::isinf(real(z)))
			return { std::abs(real(z)), 0, 0, 0 };
		return {
			std::cosh(real(z)) * std::cos(v_norm),
			std::sinh(real(z)) * std::sin(v_norm) / v_norm * z.vector
		};
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> tanh(quaternion<T> const& z) {
		return _VMTL::sinh(z) / _VMTL::cosh(z);
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> asinh(quaternion<T> const& z);
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> acosh(quaternion<T> const& z);
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> atanh(quaternion<T> const& z);
	
	/// MARK: Trigonometric Functions
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> sin(quaternion<T> const& z) {
		auto const v_norm = norm(z.vector);
		return {
			std::sin(real(z)) * std::cosh(v_norm),
			std::cos(real(z)) * std::sinh(v_norm) / v_norm * z.vector
		};
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> cos(quaternion<T> const& z) {
		auto const v_norm = norm(z.vector);
		return {
			 std::cos(real(z)) * std::cosh(v_norm),
			-std::sin(real(z)) * std::sinh(v_norm) / v_norm * z.vector
		};
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> tan(quaternion<T> const& z) {
		return sin(z) / cos(z);
	}
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> asin(quaternion<T> const& z);
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> acos(quaternion<T> const& z);
	
	template <real_scalar T>
	quaternion<__mtl_floatify(T)> atan(quaternion<T> const& z);
	
	/// MARK: Helpers
	template <real_scalar T, typename U = T, vector_options O = vector_options{}>
	constexpr quaternion<__mtl_floatify(__mtl_promote(T, U))> make_rotation(T angle, vector3<U, O> const& axis) {
		using V = __mtl_floatify(__mtl_promote(T, U));
		return quaternion<V>(std::cos(angle / 2), std::sin(angle / 2) * normalize(axis));
	}
	
	template <real_scalar T = double, typename U = T, vector_options O = vector_options{}>
	constexpr vector3<__mtl_floatify(__mtl_promote(T, U)), O> rotate(vector3<T, O> const& v, quaternion<U> const& q) {
		using V = __mtl_floatify(__mtl_promote(T, U));
		return imag(q * quaternion<V>(0, v) * conj(q));
	}
	
}

/// MARK: - Decomposition
namespace _VMTL {

	template <std::size_t I, typename T> requires (I < 2)
	auto const& get(quaternion<T> const& v) {
		if constexpr (I == 0) {
			return v.__mtl_at(0);
		}
		else {
			return v.imag;
		}
	}
	template <std::size_t I, typename T> requires (I < 2)
	auto& get(quaternion<T>& v) {
		if constexpr (I == 0) {
			return v.__mtl_at(0);
		}
		else {
			return v.imag;
		}
	}
	template <std::size_t I, typename T>
	auto&& get(quaternion<T>&& v) {
		return std::move(get<I>(v));
	}
	template <std::size_t I, typename T>
	auto&& get(quaternion<T> const&& v) {
		return std::move(get<I>(v));
	}
	
}

template <typename T>
struct std::tuple_size<_VMTL::quaternion<T>>: std::integral_constant<std::size_t, 2> {};

template <typename T>
struct std::tuple_element<0, _VMTL::quaternion<T>> {
	using type = T;
};
template <typename T>
struct std::tuple_element<1, _VMTL::quaternion<T>> {
	using type = typename _VMTL::quaternion<T>::__imag_t;
};

#endif // __MTL_QUATERNION_HPP_INCLUDED__

#pragma once

/// __ext.hpp

#ifndef __MTL_EXT_HPP_INCLUDED__
#define __MTL_EXT_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_





#include <cmath>
#include <concepts>
#include <cstring>

namespace _VMTL {

	/// MARK: - 4x4 Matrix Factories
	/// look_at() -> View Matrix
	template <handedness H = default_handedness,
			  typename T = double, vector_options O = vector_options{},
			  typename U = T, vector_options P = O,
			  typename V = T, vector_options Q = O>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<__mtl_promote(T, U, V), combine(O, P, Q)>
	look_at(vector3<T, O> const& eye,
			vector3<U, P> const& center,
			vector3<V, Q> const& up)
	{
		using TT = __mtl_promote(T, U, V);
		auto constexpr OO = combine(O, P, Q);
		
		if constexpr (H == left_handed) {
			vector3<TT, OO> const f = normalize(center - eye);
			vector3<TT, OO> const s = normalize(cross(up, f));
			vector3<TT, OO> const u = cross(f, s);

			matrix4x4<TT, OO> Result(1);
			Result.__mtl_at(0, 0) = s.__mtl_at(0);
			Result.__mtl_at(0, 1) = s.__mtl_at(1);
			Result.__mtl_at(0, 2) = s.__mtl_at(2);
			Result.__mtl_at(1, 0) = u.__mtl_at(0);
			Result.__mtl_at(1, 1) = u.__mtl_at(1);
			Result.__mtl_at(1, 2) = u.__mtl_at(2);
			Result.__mtl_at(2, 0) = f.__mtl_at(0);
			Result.__mtl_at(2, 1) = f.__mtl_at(1);
			Result.__mtl_at(2, 2) = f.__mtl_at(2);
			Result.__mtl_at(0, 3) = -dot(s, eye);
			Result.__mtl_at(1, 3) = -dot(u, eye);
			Result.__mtl_at(2, 3) = -dot(f, eye);
			return Result;
		}
		else {
			static_assert(H == right_handed);
			vector3<TT, OO> const f = normalize(center - eye);
			vector3<TT, OO> const s = normalize(cross(f, up));
			vector3<TT, OO> const u = cross(s, f);

			matrix4x4<TT, OO> Result(1);
			Result.__mtl_at(0, 0) =  s.__mtl_at(0);
			Result.__mtl_at(0, 1) =  s.__mtl_at(1);
			Result.__mtl_at(0, 2) =  s.__mtl_at(2);
			Result.__mtl_at(1, 0) =  u.__mtl_at(0);
			Result.__mtl_at(1, 1) =  u.__mtl_at(1);
			Result.__mtl_at(1, 2) =  u.__mtl_at(2);
			Result.__mtl_at(2, 0) = -f.__mtl_at(0);
			Result.__mtl_at(2, 1) = -f.__mtl_at(1);
			Result.__mtl_at(2, 2) = -f.__mtl_at(2);
			Result.__mtl_at(0, 3) = -dot(s, eye);
			Result.__mtl_at(1, 3) = -dot(u, eye);
			Result.__mtl_at(2, 3) =  dot(f, eye);
			return Result;
		}
	}
	
	/// ortho() -> Orthogonal Projection Matrix
	template <handedness H = default_handedness, real_scalar T, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> ortho(T const& left,
									T const& right,
									T const& bottom,
									T const& top,
									T const& zNear,
									T const& zFar)
	{
		if constexpr (H == left_handed) {
			return {
				T(2) / (right - left), 0,                     0,                     -(right + left) / (right - left),
				0,                     T(2) / (top - bottom), 0,                     -(top + bottom) / (top - bottom),
				0,                     0,                     T(1) / (zFar - zNear), -zNear / (zFar - zNear),
				0,                     0,                     0,                      1
			};
		}
		else {
			static_assert(H == right_handed);
			matrix4x4<T, O> Result(1);
			Result.__mtl_at(0, 0) =   T(2) / (right - left);
			Result.__mtl_at(1, 1) =   T(2) / (top - bottom);
			Result.__mtl_at(2, 2) = - T(1) / (zFar - zNear);
			Result.__mtl_at(0, 3) = - (right + left) / (right - left);
			Result.__mtl_at(1, 3) = - (top + bottom) / (top - bottom);
			Result.__mtl_at(2, 3) = - zNear / (zFar - zNear);
			return Result;
		}
	}
	
	template <handedness H = default_handedness, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr auto ortho(real_scalar auto const& left,
						 real_scalar auto const& right,
						 real_scalar auto const& bottom,
						 real_scalar auto const& top,
						 real_scalar auto const& zNear,
						 real_scalar auto const& zFar)
	{
		using T = __mtl_promote(__mtl_decltype_stripped(left),
								__mtl_decltype_stripped(right),
								__mtl_decltype_stripped(bottom),
								__mtl_decltype_stripped(top),
								__mtl_decltype_stripped(zNear),
								__mtl_decltype_stripped(zFar));
		return ortho<H, T>(left, right, bottom, top, zNear, zFar);
	}
	
	template <handedness H = default_handedness, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr auto infinite_perspective(real_scalar auto const& field_of_view,
										real_scalar auto const& aspect_ratio,
										real_scalar auto const& near)
	{
		using T = __mtl_promote(__mtl_decltype_stripped(field_of_view),
								__mtl_decltype_stripped(aspect_ratio),
								__mtl_decltype_stripped(near));
		T const range = std::tan(field_of_view / T(2)) * near;
		T const left = -range * aspect_ratio;
		T const right = range * aspect_ratio;
		T const bottom = -range;
		T const top = range;
		if constexpr (H == left_handed) {
			matrix<T, 4, 4, O> result{};
			result.__mtl_at(0, 0) = (T(2) * near) / (right - left);
			result.__mtl_at(1, 1) = (T(2) * near) / (top - bottom);
			result.__mtl_at(2, 2) =  T(1);
			result.__mtl_at(3, 2) =  T(1);
			result.__mtl_at(2, 3) = -T(2) * near;
			return result;
		}
		else {
			matrix<T, 4, 4, O> result{};
			result.__mtl_at(0, 0) = (T(2) * near) / (right - left);
			result.__mtl_at(1, 1) = (T(2) * near) / (top - bottom);
			result.__mtl_at(2, 2) = -T(1);
			result.__mtl_at(3, 2) = -T(1);
			result.__mtl_at(2, 3) = -T(2) * near;
			return result;
		}
	}
	
	template <handedness H = default_handedness, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr auto perspective(real_scalar auto const& field_of_view,
							   real_scalar auto const& aspect_ratio,
							   real_scalar auto const& near,
							   real_scalar auto const& far)
	{
		using T = __mtl_promote(__mtl_decltype_stripped(field_of_view),
								__mtl_decltype_stripped(aspect_ratio),
								__mtl_decltype_stripped(near),
								__mtl_decltype_stripped(far));
		__mtl_expect(std::abs(aspect_ratio - std::numeric_limits<T>::epsilon()) > T(0));

		T const tanHalfFovy = std::tan(field_of_view / T(2));
		
		if constexpr (H == left_handed) {
			matrix<T, 4, 4, O> result{};
			result.__mtl_at(0, 0) = T(1) / (aspect_ratio * tanHalfFovy);
			result.__mtl_at(1, 1) = T(1) / (tanHalfFovy);
			result.__mtl_at(2, 2) = far / (far - near);
			result.__mtl_at(3, 2) = T(1);
			result.__mtl_at(2, 3) = -(far * near) / (far - near);
			return result;
		}
		else {
			matrix<T, 4, 4, O> result{};
			result.__mtl_at(0, 0) = T(1) / (aspect_ratio * tanHalfFovy);
			result.__mtl_at(1, 1) = T(1) / (tanHalfFovy);
			result.__mtl_at(2, 2) = far / (near - far);
			result.__mtl_at(3, 2) = - T(1);
			result.__mtl_at(2, 3) = -(far * near) / (far - near);
			return result;
		}
	}

	/// MARK: Transforms
	template <std::floating_point T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> translation(vector3<T, O> const& offset) {
		return {
			T(1), T(0), T(0), offset.__mtl_at(0),
			T(0), T(1), T(0), offset.__mtl_at(1),
			T(0), T(0), T(1), offset.__mtl_at(2),
			T(0), T(0), T(0), T(1)
		};
	}
	
	template <std::floating_point T, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> rotation(quaternion<T> const& q) {
		return {
			2 * (__mtl_sqr(q[0]) + __mtl_sqr(q[1])) - 1, 2 * (q[1] * q[2] - q[0] * q[3]),             2 * (q[1] * q[3] + q[0] * q[2]),             0,
			2 * (q[1] * q[2] + q[0] * q[3]),             2 * (__mtl_sqr(q[0]) + __mtl_sqr(q[2])) - 1, 2 * (q[2] * q[3] - q[0] * q[1]),             0,
			2 * (q[1] * q[3] - q[0] * q[2]),             2 * (q[2] * q[3] + q[0] * q[1]),             2 * (__mtl_sqr(q[0]) + __mtl_sqr(q[3])) - 1, 0,
			0,                                           0,                                           0,                                           1
		};
	}
	
	template <std::floating_point T, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> scale(vector3<T> const& s) {
		return {
			s[0], 0, 0, 0,
			0, s[1], 0, 0,
			0, 0, s[2], 0,
			0, 0, 0,    1
		};
	}
	
	template <std::floating_point T, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> scale(T s) {
		scale({ s, s, s });
	}
	
	template <std::floating_point T, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr matrix4x4<T, O> make_transform(vector3<T, O> const& position, quaternion<T> const& orientation, vector3<T, O> const& s) {
		return translation(position) * rotation(orientation) * scale(s);
	}
	
	__mtl_mathfunction __mtl_interface_export
	constexpr auto to_quaternion(real_scalar auto roll, real_scalar auto pitch, real_scalar auto yaw) {
		// Abbreviations for the various angular functions
		using T = __mtl_floatify(__mtl_promote(decltype(yaw), decltype(pitch), decltype(roll)));
		double cy = std::cos(yaw * T(0.5));
		double sy = std::sin(yaw * T(0.5));
		double cp = std::cos(pitch * T(0.5));
		double sp = std::sin(pitch * T(0.5));
		double cr = std::cos(roll * T(0.5));
		double sr = std::sin(roll * T(0.5));

		return quaternion<T>{
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		};
	}
	
	template <typename T>
	__mtl_mathfunction __mtl_interface_export
	constexpr quaternion<__mtl_floatify(T)> to_quaternion(vector3<T> const& euler) {
		return to_quaternion(euler.__mtl_at(0), euler.__mtl_at(1), euler.__mtl_at(2));
	}
	
	template <std::floating_point T>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<T> to_euler(quaternion<T> const& q) {
		// roll (x-axis rotation)
		T const sinr_cosp = 2 * (q.__mtl_at(0) * q.__mtl_at(1) + q.__mtl_at(2) * q.__mtl_at(3));
		T const cosr_cosp = 1 - 2 * (q.__mtl_at(1) * q.__mtl_at(1) + q.__mtl_at(2) * q.__mtl_at(2));
		T const roll = std::atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		T const sinp = 2 * (q.__mtl_at(0) * q.__mtl_at(2) - q.__mtl_at(3) * q.__mtl_at(1));
		T const pitch = std::abs(sinp) >= 1 ?
			std::copysign(_VMTL::constants<T>::pi / 2, sinp) : // use 90 degrees if out of range
			std::asin(sinp);

		// yaw (z-axis rotation)
		T const siny_cosp = 2 * (q.__mtl_at(0) * q.__mtl_at(3) + q.__mtl_at(1) * q.__mtl_at(2));
		T const cosy_cosp = 1 - 2 * (q.__mtl_at(2) * q.__mtl_at(2) + q.__mtl_at(3) * q.__mtl_at(3));
		T const yaw = std::atan2(siny_cosp, cosy_cosp);

		return { roll, pitch, yaw };
	}
	
	/// MARK: - Matrix Decomposition
	/// Decompose Rotation matrix (special orthogonal / determinant 1) to a quaternion
	template <std::floating_point T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr quaternion<T> decompose_rotation(matrix3x3<T, O> m) {
		T const tr = trace(m);
		if (tr > 0) {
			T const S = std::sqrt(tr + T(1.0)) * 2; // S=4*qw
			return {
				T(0.25) * S,
				(m.__mtl_at(2, 1) - m.__mtl_at(1, 2)) / S,
				(m.__mtl_at(0, 2) - m.__mtl_at(2, 0)) / S,
				(m.__mtl_at(1, 0) - m.__mtl_at(0, 1)) / S
			};
		}
		else if (m.__mtl_at(0, 0) > m.__mtl_at(1, 1) && m.__mtl_at(0, 0) > m.__mtl_at(2, 2)) {
			T const S = std::sqrt(T(1.0) + m.__mtl_at(0, 0) - m.__mtl_at(1, 1) - m.__mtl_at(2, 2)) * 2; // S=4*qx
			return {
				(m.__mtl_at(2, 1) - m.__mtl_at(1, 2)) / S,
				0.25 * S,
				(m.__mtl_at(0, 1) + m.__mtl_at(1, 0)) / S,
				(m.__mtl_at(0, 2) + m.__mtl_at(2, 0)) / S
			};
		}
		else if (m.__mtl_at(1, 1) > m.__mtl_at(2, 2)) {
			T const S = std::sqrt(T(1.0) + m.__mtl_at(1, 1) - m.__mtl_at(0, 0) - m.__mtl_at(2, 2)) * 2; // S=4*qy
			return {
				(m.__mtl_at(0, 2) - m.__mtl_at(2, 0)) / S,
				(m.__mtl_at(0, 1) + m.__mtl_at(1, 0)) / S,
				0.25 * S,
				(m.__mtl_at(1, 2) + m.__mtl_at(2, 1)) / S
			};
		}
		else {
			float S = std::sqrt(T(1.0) + m.__mtl_at(2, 2) - m.__mtl_at(0, 0) - m.__mtl_at(1, 1)) * 2; // S=4*qz
			return {
				(m.__mtl_at(1, 0) - m.__mtl_at(0, 1)) / S,
				(m.__mtl_at(0, 2) + m.__mtl_at(2, 0)) / S,
				(m.__mtl_at(1, 2) + m.__mtl_at(2, 1)) / S,
				T(0.25) * S
			};
		}
	}
	
	/// Deompose a 4x4 affine (what about shearing?) transform matrix into translation, orientation and scale
	template <std::floating_point T, vector_options O>
	__mtl_mathfunction __mtl_interface_export
	constexpr std::tuple<vector3<T, O>, quaternion<T>, vector3<T, O>> decompose_transform(matrix4x4<T, O> t) {
		vector3<T, O> translation = t.column(3).swizzle(0, 1, 2);
		vector3<T, O> scale = {
			norm(t.column(0)),
			norm(t.column(1)),
			norm(t.column(2))
		};
		
		for (int i = 0; i < 3; ++i) {
			t.set_column(i, t.column(i) / scale[i]);
		}
		
		return {
			translation,
			decompose_rotation(dimension_cast<3, 3>(t)),
			scale
		};
	}
	
	/// MARK: - Color
	template <typename = double4> struct colors;
	
	template <typename T, vector_options O>
	requires std::is_floating_point_v<T>
	struct colors<vector<T, 3, O>> {
		static constexpr vector<T, 3, O> hex(std::uint32_t value) {
			return colors<vector<T, 4, O>>::hex(value).swizzle(0, 1, 2);
		}
		
		static constexpr vector<T, 3, O> red    = colors<vector<T, 4, O>>::red.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> orange = colors<vector<T, 4, O>>::orange.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> yellow = colors<vector<T, 4, O>>::yellow.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> green  = colors<vector<T, 4, O>>::green.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> blue   = colors<vector<T, 4, O>>::blue.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> purple = colors<vector<T, 4, O>>::purple.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> pink   = colors<vector<T, 4, O>>::pink.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> black  = colors<vector<T, 4, O>>::black.swizzle(0, 1, 2);
		static constexpr vector<T, 3, O> white  = colors<vector<T, 4, O>>::white.swizzle(0, 1, 2);
	};
	
	template <std::floating_point T, vector_options O>
	struct colors<vector<T, 4, O>> {
		static constexpr vector<T, 4, O> hex(std::uint32_t value) {
			value = _VMTL::__mtl_byte_swap(value);
			vector<std::uint8_t, 4, O> chars;
			std::memcpy(&chars, &value, sizeof(value));
			return vector<T, 4, O>(chars) / T((1 << 8) - 1);
		}
		
		static constexpr vector<T, 4, O> red    = { 1.0, 0.0, 0.0, 1.0 };
		static constexpr vector<T, 4, O> orange = { 1.0, 0.5, 0.0, 1.0 };
		static constexpr vector<T, 4, O> yellow = { 1.0, 1.0, 0.0, 1.0 };
		static constexpr vector<T, 4, O> green  = { 0.0, 1.0, 0.0, 1.0 };
		static constexpr vector<T, 4, O> blue   = { 0.0, 0.0, 1.0, 1.0 };
		static constexpr vector<T, 4, O> purple = { 0.5, 0.0, 1.0, 1.0 };
		static constexpr vector<T, 4, O> pink   = { 1.0, 0.0, 1.0, 1.0 };
		static constexpr vector<T, 4, O> black  = { 0.0, 0.0, 0.0, 1.0 };
		static constexpr vector<T, 4, O> white  = { 1.0, 1.0, 1.0, 1.0 };
		
		static constexpr vector<T, 4, O> clear  = { 0.0, 0.0, 0.0, 0.0 };
	};

	template <real_scalar T = float, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<__mtl_floatify(T), O> rgb_to_hsv(vector3<T, O> const& rgb) {
		using F = __mtl_floatify(T);
		float K = F(0);
		auto [r, g, b] = rgb;
		
		if (g < b)
		{
			std::swap(g, b);
			K = -1.f;
		}
		if (r < g)
		{
			std::swap(r, g);
			K = -2.f / 6.f - K;
		}

		F const chroma = r - (g < b ? g : b);
		F const x = chroma == F(0) ? F(0) : (g - b) / (F(6) * chroma);
		F const s = r == F(0) ? F(0) : chroma / r;
		return {
			std::abs(K + x), s, r
		};
	};
	
	template <real_scalar T, real_scalar U, real_scalar V>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<__mtl_floatify(T)> rgb_to_hsv(T const& r, U const& g, V const& b) {
		return rgb_to_hsv({ r, b, g });
	}
	
	template <real_scalar T = float, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector4<__mtl_floatify(T), O> rgba_to_hsva(vector4<T, O> const& rgba) {
		return { rgb_to_hsv(rgba.swizzle(0, 1, 2)), rgba.__mtl_at(3) };
	}
	
	template <real_scalar T, real_scalar U, real_scalar V, real_scalar W>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector4<__mtl_floatify(T)> rgba_to_hsva(T const& r, U const& g, V const& b, W const& a) {
		return rgba_to_hsva({ r, b, g, a });
	}
	
	template <real_scalar T = float, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<__mtl_floatify(T), O> hsv_to_rgb(vector3<T, O> const& hsv) {
		using V = vector3<__mtl_floatify(T), O>;
		using F = __mtl_floatify(T);
		
		auto [h, s, v] = hsv;
		
		if (s == F(0)) { // gray
			return V(v);
		}

		h = std::fmod(h, F(1)) / (F(60) / F(360));
		int const   i = (int)h;
		F const f = h - (F)i;
		F const p = v * (F(1) - s);
		F const q = v * (F(1) - s * f);
		F const t = v * (F(1) - s * (F(1) - f));

		switch (i) {
			case 0: return { v, t, p };
			case 1: return { q, v, p };
			case 2: return { p, v, t };
			case 3: return { p, q, v };
			case 4: return { t, p, v };
			case 5:
			default: return { v, p, q };
		}
	}

	template <real_scalar T, real_scalar U, real_scalar V>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector3<__mtl_floatify(T)> hsv_to_rgb(T const& h, U const& s, V const& v) {
		return hsv_to_rgb({ h, s, v });
	}
	
	template <real_scalar T = float, vector_options O = vector_options{}>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector4<__mtl_floatify(T), O> hsva_to_rgba(vector4<T, O> const& hsva) {
		return { hsv_to_rgb(hsva.swizzle(0, 1, 2)), hsva.__mtl_at(3) };
	}
	
	template <real_scalar T, real_scalar U, real_scalar V, real_scalar W>
	__mtl_mathfunction __mtl_interface_export
	constexpr vector4<__mtl_floatify(T)> hsva_to_rgba(T const& h, U const& s, V const& v, W const& a) {
		return hsva_to_rgba({ h, s, v, a });
	}
	
}


/// MARK: - utl::iota<mtl::vector<...>>
namespace utl {
	
	template <typename>
	class iota;
	
	template <typename T, std::size_t N, _VMTL::vector_options O>
	requires std::is_integral_v<T>
	iota(_VMTL::vector<T, N, O>) -> iota<_VMTL::vector<T, N, O>>;
	
	template <typename T, typename U, std::size_t N, _VMTL::vector_options O, _VMTL::vector_options P>
	requires std::is_integral_v<T> && std::is_integral_v<U>
	iota(_VMTL::vector<T, N, O>, _VMTL::vector<U, N, P>) -> iota<_VMTL::vector<__mtl_promote(T, U), N, combine(O, P)>>;
	
	template <typename T, std::size_t N, _VMTL::vector_options O>
	requires std::is_integral_v<T>
	class iota<_VMTL::vector<T, N, O>> {
	public:
		using value_type = _VMTL::vector<T, N, O>;
		using size_type = _VMTL::vector<std::conditional_t<std::is_signed_v<T>, std::ptrdiff_t, std::size_t>, N, O>;
		
	public:
		class iterator {
			friend class iota;
			constexpr explicit iterator(value_type begin, value_type last):
				_begin(begin), _current(begin), _last(last) {}
			
		public:
			__mtl_interface_export
			constexpr value_type operator*() const { return _current; }
			__mtl_interface_export
			constexpr iterator& operator++() {
				for (std::size_t i = N - 1;;) {
					if (++_current[i] != _last[i]) {
						break;
					}
					_current[i] = _begin[i];
					
					if (i == 0) {
						_done = true;
						break;
					}
					--i;
				}
				
				return *this;
			}
			__mtl_interface_export
			constexpr bool operator!=(iterator const& rhs) const {
				__mtl_assert_audit(this->_begin == rhs._begin);
				__mtl_assert_audit(this->_last == rhs._last);
				return !_done;
			}
			
		private:
			value_type _begin, _current, _last;
			bool _done = false;
		};
		
	public:
		__mtl_interface_export
		constexpr iota(value_type last): _first(0), _last(last) {}
		__mtl_interface_export
		constexpr iota(value_type first, size_type last): _first(first), _last(last) {}
		
		__mtl_interface_export
		constexpr iterator begin() const {
			return iterator(_first, _last);
		}
		__mtl_interface_export
		constexpr iterator end() const {
			return iterator(_first, _last);
		}
		
		__mtl_interface_export
		constexpr size_type size() const { return _last - _first; }
		
	private:
		value_type _first;
		value_type _last;
	};
	
}

#endif // __MTL_EXT_HPP_INCLUDED__

#pragma once


_MTL_SYSTEM_HEADER_



#include <array>
#include <cmath>


namespace mtl {
	
	/**
	 solve_quadratic
	 solves the equation x^2 + px + q = 0
	 */
	template <typename T, typename U>
	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U))>, 2> solve_quadratic(T const& __p, U const& __q) {
		using F = __mtl_floatify(__mtl_promote(T, U));
		using C = __mtl_to_complex_t<F>;
		
		F const p = F(__p);
		F const q = F(__q);
		
		F const neg_p_halfs = -p / F(2);
		F const discriminant = p * p / F(4) - q;
		
		if constexpr (is_complex<F>::value) {
			F const root_d = _VMTL::sqrt(discriminant);
			return { neg_p_halfs + root_d, neg_p_halfs - root_d };
		}
		else {
			F const root_d = std::sqrt(std::fabs(discriminant));
			if (discriminant >= 0) {
				return { neg_p_halfs + root_d, neg_p_halfs - root_d };
			}
			else {
				return { C{ neg_p_halfs, root_d }, C{ neg_p_halfs, -root_d } };
			}
		}
	}
	
	/**
	 solve_quadratic
	 solves the equation ax^2 + bx + c = 0
	 */
	template <typename T, typename U, typename V>
	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U, V))>, 2> solve_quadratic(T const& __a, U const& __b, V const& __c) {
		using F = __mtl_floatify(__mtl_promote(T, U, V));
		__mtl_expect(__a != T(0));
		return solve_quadratic(__b / F(__a), __c / F(__a));
	}
	
	/**
	 solve_cubic_numeric
	 solves the equation x^3 + ax^2 + bx + c = 0
	 */
//	template <std::arithmetic T, std::arithmetic U, std::arithmetic V>
//	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U, V))>, 3> solve_cubic_numeric(T const& __a, U const& __b, V const& __c) {
//		using F = __mtl_floatify(__mtl_promote(T, U, V));
//		__mtl_expect(__a != T(0));
//		return solve_quadratic(__b / F(__a), __c / F(__a));
//	}
	
}








namespace mtl {
	
#define	TwoPi  6.28318530717958648
const double eps = 1e-14;
	
	// x - array of size 2
	// return 2: 2 real roots x[0], x[1]
	// return 0: pair of complex roots: x[0]±i*x[1]
	
	template <typename T>
	auto __mtl_root3(T x) {
		using F = __mtl_floatify(T);
		return std::copysign(std::pow(std::abs(x), F(1) / F(3)), x);
	}
	
//	template <typename T>
//	std::array<complex<__mtl_floatify(T)>, 2> solve_quadratic(T a, T b) {
//		using F = __mtl_floatify(T);
//		using std::sqrt;
//		F const D = F(0.25) * a * a - b;
//		if (D >= 0) {
//			D = sqrt(D);
//			return {
//				F(-0.5) * a + D,
//				F(-0.5) * a - D
//			};
//		}
//		F const real = F(-0.5) * a;
//		F const imag = sqrt(-D);
//		return {
//			complex<F>(real, imag),
//			complex<F>(real, -imag),
//		};
//	}
	
	template <typename T>
	std::array<complex<__mtl_floatify(T)>, 3> solve_cubic(T a, T b, T c) {	// solve cubic equation x^3 + a*x^2 + b*x + c = 0
		using F = __mtl_floatify(T);
		F const a2 = a * a;
		F const q  = (a2 - 3 * b) / 9;
		F const r  = (a * (2 * a2 - 9 * b) + 27 * c) / 54;
		// equation y^3 - 3q*y + r/2 = 0 where x = y-a/3
		using std::sqrt;
		if (std::fabs(q) < eps) {		// y^3 =-r/2	!!! Thanks to John Fairman <jfairman1066@gmail.com>
			if (std::fabs(r) < eps) {	// three identical roots
				F const result = -a / 3;
				return { result, result, result };
			}
			// y^3 =-r/2
			F const real_root = __mtl_root3(-r / 2);
			F const real = real_root * F(0.5);
			F const imag = real_root * sqrt(F(3)) / 2;
			return { real_root, { real, imag }, { real, -imag } };
		}
		// now favs(q)>eps
		F const r2 = r * r;
		F const q3 = q * q * q;
		if (r2 <= (q3 + eps)) {
			F t = r / std::sqrt(q3);
			if (t < -1)
				t = -1;
			if (t >  1)
				t = 1;
			t = std::acos(t);
			a /= 3;
			F const p = -2 * sqrt(q);
			F const real_root = p * std::cos(t / 3) - a;
			F const real = p * std::cos((t + TwoPi) / 3) - a;
			F const imag = p * std::cos((t - TwoPi) / 3) - a;
			return { real_root, { real, imag }, { real, -imag } };
		}
		else {
			//A =-pow(fabs(r)+sqrt(r2-q3),1./3);
			F A = -__mtl_root3(fabs(r) + sqrt(r2 - q3));
			if (r < 0)
				A = -A;
			F B = (A == 0 ? 0 : q / A);

			a /= 3;
			F const real_root = A + B - a;
			F const real = F(-0.5) * (A + B) - a;
			F const imag = F(0.5) * sqrt(F(3)) * (A - B);
			
			return { real_root, { real, imag }, { real, -imag } };
		}
	}
	
}

#pragma once

/// __shapes.hpp

#ifndef __MTL_SHAPES_HPP_INCLUDED__
#define __MTL_SHAPES_HPP_INCLUDED__


_MTL_SYSTEM_HEADER_



#include <algorithm>
#include <iosfwd>

namespace _VMTL {
	
	/// MARK: - AABB
	template <typename T = double, std::size_t Dim = 3, vector_options O = vector_options{}>
	class AABB {
	public:
		AABB(vector<T, Dim, O> const& lower_bound = 0, vector<T, Dim, O> const& size = 0): _origin(lower_bound), _size(size) {
			__mtl_expect(map(size, [](auto x) { return x >= 0; }).fold(__mtl_logical_and));
		}
		
		vector<T, Dim, O> lower_bound() const { return _origin; };
		vector<T, Dim, O> upper_bound() const { return _origin + _size; };
		
		[[deprecated("Replaced by lower_bound()")]]
		vector<T, Dim, O> bottom_left() const { return lower_bound(); };
		[[deprecated("Replaced by upper_bound()")]]
		vector<T, Dim, O> top_right() const { return upper_bound(); };
		
		vector<T, Dim, O> size() const { return _size; };
		
	private:
		vector<T, Dim, O> _origin;
		vector<T, Dim, O> _size;
	};
	
	template <typename T, std::size_t Dim, vector_options O>
	std::ostream& operator<<(std::ostream& str, AABB<T, Dim, O> const& aabb) {
		return [](auto& x) -> auto& { return x; }(str) << "AABB{ .lower_bound = " << aabb.lower_bound() << ", .upper_bound = " << aabb.upper_bound() << " }";
	}
	
	template <typename... T, std::size_t Dim, vector_options... O>
	constexpr AABB<__mtl_promote(T...), Dim, combine(O...)> enclosing(AABB<T, Dim, O> const&... aabb) {
		auto const lower_bound = map(aabb.lower_bound()..., [](auto&&... bl){ return _VMTL::min(bl...); });
		auto const upper_bound = map(aabb.upper_bound()..., [](auto&&... tr){ return _VMTL::max(tr...); });
		return { lower_bound, upper_bound - lower_bound };
	}
	
	template <typename T, std::size_t Dim, vector_options O>
	constexpr bool encloses(AABB<T, Dim, O> const& bigger, AABB<T, Dim, O> const& smaller) {
		return
			map(bigger.lower_bound(), smaller.lower_bound(), [](auto b, auto s) { return b - T(0.001) <= s; }).fold(__mtl_logical_and) &&
			map(bigger.upper_bound(), smaller.upper_bound(), [](auto b, auto s) { return b + T(0.001) >= s; }).fold(__mtl_logical_and);
	}
	
	template <typename T = double, vector_options O = vector_options{}>
	using rectangle = AABB<T, 2, O>;
	
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool operator==(AABB<T, Dim, O> r, AABB<U, Dim, P> s) {
		return r.lower_bound() == s.lower_bound() && r.size() == s.size();
	}
	
	template <typename T, std::size_t Dim, vector_options O>
	constexpr T volume(AABB<T, Dim, O> const& b) {
		return fold(b.size(), _VMTL::__mtl_multiplies);
	}
	
	template <typename T, std::size_t Dim, vector_options O>
	constexpr T surface_area(AABB<T, Dim, O> const& b) {
		static_assert(Dim >= 1 && Dim <= 3, "Too lazy to implement higher dimensions");
		
		auto size = b.size();
		
		if constexpr (Dim == 1) {
			return size[0];
		}
		else if constexpr (Dim == 2) {
			return 2 * (size[0] + size[1]);
		}
		else if constexpr (Dim == 3) {
			return 2 * (size[0] * size[1] +
						size[1] * size[2] +
						size[2] * size[0]);
		}
	}
	
	template <typename T, vector_options O>
	constexpr T area(rectangle<T, O> const& r) {
		return volume(r);
	}
	
	template <typename T, vector_options O>
	constexpr T circumference(rectangle<T, O> const& r) {
		return surface_area(r);
	}
	
	
	/// MARK: Sphere
	template <typename T = double, std::size_t Dim = 3, vector_options O = vector_options{}.packed(true)>
	struct sphere {
		static_assert(std::is_floating_point<T>::value, "T needs to be floating point");
		static_assert(Dim >= 2);
		static_assert(Dim <= 4);
		
	public:
		sphere(vector<T, Dim, O> const& origin, T radius): _origin(origin), _radius(radius) {}
		
		vector<T, Dim, O> origin() const { return _origin; };
		T radius() const { return _radius; };
		
	private:
		vector<T, Dim, O> _origin;
		T _radius;
	};
	
	template <typename T = double, vector_options O = vector_options{}.packed(true)>
	using disk = sphere<T, 2, O>;
	
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool operator==(sphere<T, Dim, O> const& r, sphere<U, Dim, P> const& s) {
		return r.origin() == s.origin() && r.radius() == s.radius();
	}
	
	template <typename T, std::size_t Dim, vector_options O>
	constexpr T volume(sphere<T, Dim, O> const& s) {
		if constexpr (Dim == 2) {
			return constants<T>::pi * __mtl_sqr(s.radius(), 2);
		}
		else if constexpr (Dim == 3) {
			return T(4.0 / 3.0) * constants<T>::pi * __mtl_sqr(s.radius()) * s.radius();
		}
		else {
			static_assert(Dim == 4);
			return T(0.5) * __mtl_sqr(constants<T>::pi) * __mtl_sqr(__mtl_sqr(s.radius()));
		}
	}
	
	template <typename T, vector_options O>
	constexpr T area(sphere<T, 2, O> const& r) {
		return volume(r);
	}
	
	/// MARK: - Triangle
	template <typename T, std::size_t Dim = 3, vector_options O = vector_options{}>
	class triangle {
	public:
		vector<T, Dim, O>& operator[](std::size_t index) {
			return const_cast<vector<T, Dim, O>&>(const_cast<triangle const*>(this)->operator[](index));
		}
		
		vector<T, Dim, O> const& operator[](std::size_t index) const {
			__mtl_bounds_check(index, 0, 3);
			return _points[index];
		}
		
	private:
		vector<T, Dim, O> _points[3];
	};
	
	/// MARK: - Line Segment
	template <typename T, std::size_t Dim, vector_options O = vector_options{}>
	class line_segment {
	public:
		line_segment(vector<T, Dim, O> const& begin, vector<T, Dim, O> const& end):
			_begin(begin),
			_end(end)
		{}
		
		vector<T, Dim, O> begin() const { return _begin; }
		vector<T, Dim, O> end() const { return _end; }
		
		vector<T, Dim, O> extend() const { return _end - _begin; }
		vector<T, Dim, O> normal() const { return normalize(extend()); }
		auto length() const { return norm(extend()); }
		
	private:
		vector<T, Dim, O> _begin;
		vector<T, Dim, O> _end;
	};
	
	template <typename T = double, vector_options O = vector_options{}>
	using line_segment_2D = line_segment<T, 2, O>;
	
	template <typename T = double, vector_options O = vector_options{}>
	using line_segment_3D = line_segment<T, 3, O>;
	
	template <typename T, typename U, std::size_t Dim, vector_options O, vector_options P>
	auto distance(line_segment<T, Dim, O> const& l, vector<U, Dim, P> const& p) {
		// Return minimum distance between line segment l and point p
		using V = typename promote<T, U>::type;
		
		auto const l2 = distance_squared(l.begin(), l.end());  // i.e. |w-v|^2 -  avoid a sqrt
		if (l2 == V(0)) {
			return distance(p, l.begin());   // v == w case
		}
		
	  // Consider the line extending the segment, parameterized as v + t (w - v).
	  // We find projection of point p onto the line.
	  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
	  // We clamp t to [0,1] to handle points outside the segment vw.
	  auto const t = std::max(T(0), std::min(T(1), dot(p - l.begin(), l.extend()) / l2));
	  auto const projection = l.begin() + t * (l.extend());  // Projection falls on the segment
	  return distance(p, projection);
	}
	
	template <typename T, typename U, std::size_t Dim, vector_options O, vector_options P>
	auto distance(vector<U, Dim, P> const& p, line_segment<T, Dim, O> const& l) {
		return distance(l, p);
	}
	
	/// MARK: - Intersections
	/// Box - Point
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(AABB<T, Dim, O> r, vector<U, Dim, P> const& p) {
		return map(r.lower_bound(), r.size(), p,
				   [](auto o, auto e, auto p) { return p >= o && p <= o + e; }).fold(_VMTL::__mtl_logical_and);
	}
	
	/// Point - Box
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(vector<U, Dim, P> const& p, AABB<T, Dim, O> r) {
		return do_intersect(r, p);
	}
	
	/// Box - Box
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(AABB<T, Dim, O> const& a, AABB<U, Dim, P> const& b) {
		return map(a.lower_bound(), a.upper_bound(),
				   b.lower_bound(), b.upper_bound(),
				   [](auto aMin, auto aMax,
					  auto bMin, auto bMax) { return aMin <= bMax && aMax >= bMin; }).fold(__mtl_logical_and);
	}
	
	
	
	/// Sphere - Point
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(sphere<T, Dim, O> const& r, vector<U, Dim, P> const& p) {
		return distance(r.origin(), p) <= r.radius();
	}
	
	/// Point - Sphere
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(vector<U, Dim, P> const& p, sphere<T, Dim, O> const& r) {
		return do_intersect(r, p);
	}
	
	/// Sphere - Sphere
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(sphere<T, Dim, O> const& a, sphere<U, Dim, P> const& b) {
		return distance(a.origin(), b.origin()) <= a.radius() + b.radius();
	}
	
	/// Sphere - Box
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(sphere<T, Dim, O> const& sphere, AABB<U, Dim, P> const& box) {
		auto const closest_point_to_sphere = map(box.lower_bound(), box.size(), sphere.origin(),
												 [](auto bMin, auto bMax, auto sOrigin) {
			return std::max(bMin, std::min(sOrigin, bMax));
		});
		
		return do_intersect(sphere, closest_point_to_sphere);
	}
	
	/// Box - Sphere
	template <typename T, std::size_t Dim, vector_options O, typename U, vector_options P>
	constexpr bool do_intersect(AABB<U, Dim, P> a, sphere<T, Dim, O> b) {
		return do_intersect(b, a);
	}
	
}

#endif // __MTL_SHAPES_HPP_INCLUDED__


#pragma once

/// __undef.hpp

#ifndef __MTL_UNDEF_HPP_INCLUDED__
#define __MTL_UNDEF_HPP_INCLUDED__

#ifndef __MTL_NO_UNDEF__

#undef _MTL_SYSTEM_HEADER_

#undef MTL_DEBUG_LEVEL
#undef MTL_SAFE_MATH
#undef MTL_DEFAULT_PACKED
#undef MTL_NAMESPACE_NAME
#undef MTL_UNICODE_MATH_PARANTHESES

#undef __mtl_pure
#undef __mtl_nodiscard
#undef __mtl_mathfunction
#undef __mtl_always_inline
#undef __mtl_noinline
#undef __mtl_interface_export

#undef __mtl_assert
#undef __mtl_expect
#undef __mtl_ensure
#undef __mtl_debugbreak
#undef __mtl_bounds_check

#undef _VMTL

#undef __mtl_safe_math_if

#undef __MTL_DECLARE_STDINT_TYPEDEFS__
#undef __MTL_DECLARE_COMPLEX_TYPEDEFS__
#undef __MTL_DECLARE_QUATERNION_TYPEDEFS__
#undef __MTL_DECLARE_VECTOR_TYPEDEFS__
#undef __MTL_DECLARE_MATRIX_TYPEDEFS__

#undef __mtl_floatify

#undef __mtl_forward

#undef __MTL_PRIV_WIS_FT
#undef __MTL_PRIV_WIS_FP
#undef __MTL_PRIV_WIS_FI
#undef __mtl_with_index_sequence

#undef MTL_STDLIB_HAS_CONCEPTS

#endif // __MTL_NO_UNDEF__

#endif // __MTL_UNDEF_HPP_INCLUDED__


#endif // __MTL_MTL_HPP_INCLUDED__



/// MARK: Memory Layout
/// By default memory layout is 'Aligned', implying the following alignments:
//  +-----------------+------------------------------------+
//  | Data Type       | Alignment                          |
//  +-----------------+------------------------------------+
//  | vector<T, 2>    | 2 * alignof(T)                     |
//  | vector<T, 3>    | 4 * alignof(T)                     |
//  | vector<T, 4>    | 4 * alignof(T)                     |
//  | matrix<T, N, 2> | 2 * alignof(T) [where N = 2, 3, 4] |
//  | matrix<T, N, 3> | 4 * alignof(T) [where N = 2, 3, 4] |
//  | matrix<T, N, 4> | 4 * alignof(T) [where N = 2, 3, 4] |
//  +-----------------+------------------------------------+
///
/// With memory layout 'Packed' every data type is aligned as it's underlying fundamental type,
/// e.g. alignof(float3) = 4, alignof(vector4<int64_t>) = 8


/// MARK: - Customization Points
// +------------------------------+-----------------+--------+
// | Macro                        | Possible Values | Default|
// +------------------------------+-----------------+--------+
// | MTL_DEBUG_LEVEL              |              0  |       0|  On Debug Level 0 all assertions and API validations
// |                              |                 |        |  are disabled.
// |                              |                 |        |  Most (small) functions are forced inline.
// |                              |                 |        |  No debug symbols are generated for public API.
// |                              |                 |        |
// |                              |              1  |        |  On Debug Level 1 API validations are enabled, including
// |                              |                 |        |  bounds checks in operator[].
// |                              |                 |        |  Most (small) functions are forced inline.
// |                              |                 |        |  No debug symbols are generated for public API.
// |                              |                 |        |
// |                              |              2  |        |  On Debug Level 2 internel assertions and costly checks
// |                              |                 |        |  also are enabled.
// |                              |                 |        |  No functions are forced inline.
// |                              |                 |        |  Debug symbols are generated for all functions.
// |                              |                 |        |
// +------------------------------+-----------------+--------+
// | MTL_SAFE_MATH                |              0, |       1|  If disabled some math operations like exp(complex),
// |                              |              1  |        |  sin(complex) and norm(vector) don't handle overflow
// |                              |                 |        |  correctly. Disabling this will speed up these
// |                              |                 |        |  operations.
// +------------------------------+-----------------+--------+
// | MTL_DEFAULT_PACKED           |              0, |       0|  If enabled vectors and matrices use 'Packed' memory
// |                              |              1  |        |  layout by default. Otherwise memory layout is 'Aligned'.
// |                              |                 |        |  Regardless of what is specified here, the typedefs
// |                              |                 |        |  aligned_*** and packed_*** are defined and the alignment
// |                              |                 |        |  can also be specified in the vector_options template
// |                              |                 |        |  parameter.
// +------------------------------+-----------------+--------+
// | MTL_NAMESPACE_NAME           |            Any  |     mtl|  Change the name of the 'mtl' namespace. Can be useful
// |                              |                 |        |  to share code between C++ and shader header files.
// +------------------------------+-----------------+--------+
// | MTL_UNICODE_MATH_PARANTHESES |              0, |       1|
// |                              |              1  |        |
// +------------------------------+-----------------+--------+
