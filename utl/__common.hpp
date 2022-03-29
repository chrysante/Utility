#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <utility>
#include <type_traits>
#include <cstdint>

/// MARK: UTL_CONCAT
#define _UTL_CONCAT_IMPL(A, B) A##B
#define UTL_CONCAT(A, B) _UTL_CONCAT_IMPL(A, B)


/// MARK: UTL_ANONYMOUS_VARIABLE
#define UTL_ANONYMOUS_VARIABLE(name) UTL_CONCAT(name, __LINE__)


/// MARK: - UTL_TO_STRING
#define _UTL_TO_STRING_IMPL(x) #x
#define UTL_TO_STRING(x) _UTL_TO_STRING_IMPL(x)


/// MARK: UTL_VFUNC
#define _UTL_NARG(...)  _UTL_NARG_I(__VA_ARGS__, _UTL_RSEQ_N())
#define _UTL_NARG_I(...) _UTL_ARG_N(__VA_ARGS__)
#define _UTL_ARG_N( \
	  _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
	 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
	 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
	 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
	 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
	 _61,_62,_63,N,...) N
#define _UTL_RSEQ_N() \
	 63,62,61,60,                   \
	 59,58,57,56,55,54,53,52,51,50, \
	 49,48,47,46,45,44,43,42,41,40, \
	 39,38,37,36,35,34,33,32,31,30, \
	 29,28,27,26,25,24,23,22,21,20, \
	 19,18,17,16,15,14,13,12,11,10, \
	 9,8,7,6,5,4,3,2,1,0
#define _UTL_VFUNC_IMPL(name, n) UTL_CONCAT(name, n)
#define UTL_VFUNC(func, ...) _UTL_VFUNC_IMPL(func, _UTL_NARG(__VA_ARGS__)) (__VA_ARGS__)


/// MARK: UTL_FIRST, UTL_NTH
#define UTL_FIRST(f, ...) f


// MARK: UTL_FORWARD
#define UTL_FORWARD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)


/// MARK: UTL_WITH_INDEX_SEQUENCE
#define UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS(...) \
	UTL_VFUNC(UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS, __VA_ARGS__)
#define UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS2(name1, size1) \
	<::std::size_t... name1>
#define UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS4(name1, size1, name2, size2) \
	<::std::size_t... name1, ::std::size_t... name2>
#define UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS6(name1, size1, name2, size2, name3, size3) \
	<::std::size_t... name1, ::std::size_t... name2, ::std::size_t... name3>

#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS(...) \
	UTL_VFUNC(UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS, __VA_ARGS__)
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS2(name1, size1) \
	(::utl::index_sequence<name1...>)
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS4(name1, size1, name2, size2) \
	(::utl::index_sequence<name1...>, ::utl::index_sequence<name2...>)
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS6(name1, size1, name2, size2, name3, size3) \
	(::utl::index_sequence<name1...>, ::utl::index_sequence<name2...>, ::utl::index_sequence<name3...>)

#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE(...) \
	UTL_VFUNC(UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE, __VA_ARGS__)
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE2(name1, size1) \
	(::utl::make_index_sequence<size1>{})
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE4(name1, size1, name2, size2) \
	(::utl::make_index_sequence<size1>{}, ::utl::make_index_sequence<size2>{})
#define UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE6(name1, size1, name2, size2, name3, size3) \
	(::utl::make_index_sequence<size1>{}, ::utl::make_index_sequence<size2>{}, ::utl::make_index_sequence<size3>{})

#define UTL_WITH_INDEX_SEQUENCE(params, ...) \
	[&] UTL_INTERNAL_INDEX_SEQ_HELPER_TEMPLATE_PARAMS params \
	UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_PARAMS params __VA_ARGS__ \
	UTL_INTERNAL_INDEX_SEQ_HELPER_FUNCTION_INVOKE params


/// MARK: UTL_ENABLE_IF
#define UTL_ENABLE_IF_IMPL(...) typename std::enable_if<__VA_ARGS__, std::nullptr_t>::type
#define UTL_ENABLE_IF(...) UTL_ENABLE_IF_IMPL(__VA_ARGS__) = nullptr
//#define UTL_ENABLE_MEMBER_IF(...) std::nullptr_t UTL_INTERNAL_UNIQUE_NAME(_re2_dummy) = nullptr, typename std::enable_if<!static_cast<void*>(UTL_INTERNAL_UNIQUE_NAME(_re2_dummy)) && (__VA_ARGS__), std::nullptr_t>::type = nullptr

/// MARK: Enum Operators
#if defined(UTL_CPP)
#	define _UTL_NSSTD std
#elif defined(UTL_METAL)
#	define _UTL_NSSTD metal
#else
#	error Unsupported Language
#endif

#define _UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, RESULT_TYPE, OP) \
inline constexpr RESULT_TYPE operator OP(TYPE a) { \
	return static_cast<RESULT_TYPE>(OP static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(a)); \
}
#define _UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, OP) \
inline constexpr TYPE operator OP(TYPE a, TYPE b) { \
	return static_cast<TYPE>(static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(a) OP static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(b)); \
} \
inline constexpr TYPE operator OP(typename _UTL_NSSTD::underlying_type<TYPE>::type a, TYPE b) { \
	return static_cast<TYPE>(a OP static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(b)); \
} \
inline constexpr TYPE operator OP(TYPE a, typename _UTL_NSSTD::underlying_type<TYPE>::type b) { \
	return static_cast<TYPE>(static_cast<typename _UTL_NSSTD::underlying_type<TYPE>::type>(a) OP b); \
}

#if defined(UTL_CPP)
#	define _UTL_ENUM_ASSIGNMENT(TYPE, OP) \
		inline constexpr TYPE& operator OP##=(TYPE& a, TYPE b) { \
			return a = a OP b; \
		}
#elif defined(UTL_METAL)
#	define _UTL_ENUM_ASSIGNMENT(TYPE, OP) // Not supported in Metal
#else
#	error
#endif

#define UTL_ENUM_OPERATORS(TYPE) \
	_UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, &) \
	_UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, |) \
	_UTL_ENUM_BINARY_PREFIX_OPERATOR(TYPE, ^) \
	_UTL_ENUM_ASSIGNMENT(TYPE, &) \
	_UTL_ENUM_ASSIGNMENT(TYPE, |) \
	_UTL_ENUM_ASSIGNMENT(TYPE, ^) \
	_UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, TYPE, ~) \
	_UTL_ENUM_UNARY_PREFIX_OPERATOR(TYPE, bool, !) \
	constexpr bool test(TYPE value) noexcept { return !!value; }




#ifdef UTL_CPP // Guard here because general purpose header may be included in shader source

namespace utl {
	
	/// MARK: Integer Typedefs
#if (__GNUC__ || __clang__) // && ...
#	define UTL_128_BIT_ARITHMETIC
#endif
	
	using uint8_t   = std::uint8_t;
	using uint16_t  = std::uint16_t;
	using uint32_t  = std::uint32_t;
	using uint64_t  = std::uint64_t;
	
	using int8_t    = std::int8_t;
	using int16_t   = std::int16_t;
	using int32_t   = std::int32_t;
	using int64_t   = std::int64_t;
#ifdef UTL_128_BIT_ARITHMETIC
	using uint128_t = __uint128_t;
	using int128_t  = __int128_t;
#endif // UTL_128_BIT_ARITHMETIC
	
	/// MARK: Tags
	struct __private_tag{};
	struct no_init_t{} constexpr no_init{};
	
	template <typename T>
	struct tag { using type = T; };
	
	// MARK: as_const / as_mutable
	template <typename T>
	constexpr typename std::add_const<T>::type& as_const(T& t) noexcept {
		return t;
	}
	template <typename T>
	void as_const(const T&&) = delete;
//	template <typename T>
//	constexpr T const* as_const(T* t) noexcept {
//		return t;
//	}
	
	template <typename T>
	constexpr typename std::remove_const<T>::type& as_mutable(T& t) noexcept {
		return const_cast<typename std::remove_const<T>::type&>(t);
	}
	template <typename T>
	void as_mutable(const T&&) = delete;
//	template <typename T>
//	constexpr T* as_mutable(T const* t) noexcept {
//		return const_cast<T*>(t);
//	}
	
//	template <typename T>
//	constexpr T* as_mutable_ptr(T const* a) noexcept {
//		return const_cast<T*>(a);
//	}
//	template <typename T>
//	constexpr T* as_mutable_ptr(T* a) noexcept {
//		return a;
//	}
	
	/// MARK: strlen
	/// because constexpr
	constexpr std::size_t strlen(char const* str) {
		if (!str)
			return 0;
		std::size_t result = 0;
		while (*str != '\0') {
			++str;
			++result;
		}
		return result;
	}
	
	/// MARK: destroy
	template <typename T>
	void destroy(T& t) noexcept {
		t.~T();
	}
	
	/// MARK: index_sequence
	template <std::size_t... I>
	using index_sequence = std::index_sequence<I...>;
	
	template <std::size_t N>
	using make_index_sequence = std::make_index_sequence<N>;
	
	/// MARK: type_sequence
	template <typename... T>
	struct type_sequence {};
	
	template <typename T, std::size_t N, typename... R>
	struct __utl_make_type_sequence_impl {
		using type = typename __utl_make_type_sequence_impl<T, N - 1, R..., T>::type;
	};
	
	template <typename T, typename... R>
	struct __utl_make_type_sequence_impl<T, 0, R...> {
		using type = type_sequence<R...>;
	};
	
	template <typename T, std::size_t N>
	using make_type_sequence = typename __utl_make_type_sequence_impl<T, N>::type;
	
	/// MARK: UTL_CTPRINT
	template <auto...> struct ctprint;
	#define UTL_CTPRINT(...) ::utl::ctprint<__VA_ARGS__> UTL_ANONYMOUS_VARIABLE(_UTL_CTPRINT)

	/// MARK: Iota
	template <typename>
	class iota;
	
	template <typename T, typename U>
	requires(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>)
	iota(T, U) -> iota<std::common_type_t<T, U>>;
	
	template <typename T>
	requires (std::is_integral_v<T>)
	class iota<T> {
	public:
		using value_type = T;
		using size_type = std::conditional_t<std::is_signed_v<T>, std::ptrdiff_t, std::size_t>;
		
	public:
		class iterator {
			template <typename>
			friend class iota;
			constexpr explicit iterator(value_type i):
				_i(i) {}
			
		public:
			__utl_interface_export
			constexpr value_type operator*() const { return _i; }
			__utl_interface_export
			constexpr iterator& operator++() {
				++_i;
				return *this;
			}
			__utl_interface_export
			constexpr bool operator!=(iterator const& rhs) const {
				return _i != rhs._i;
			}
			
		private:
			value_type _i;
		};
		
	public:
		__utl_interface_export
		constexpr iota(value_type first, value_type last): _first(first), _last(last) {}
		
		__utl_interface_export
		constexpr iterator begin() const {
			return iterator(_first);
		}
		__utl_interface_export
		constexpr iterator end() const {
			return iterator(_last);
		}
		
		__utl_interface_export
		constexpr size_type size() const { return _last - _first; }
		
	private:
		value_type _first, _last;
	};
	
}

#endif // UTL_CPP
