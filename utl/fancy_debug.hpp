#pragma once


#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__common.hpp"
#include "__debug.hpp"
#include "log.hpp"
#include "concepts.hpp"
#include "expression_parser.hpp"

/// We allow four signaturs for Assertions:
//  assert(bool)
//  assert(bool, char const*)
//  assert(Level, bool)
//  assert(Level, bool, char const*)

/// MARK: - Interface
#define UTL_FANCY_ASSERT(module_name, debug_level, kind, ...)                      \
(\
::utl::__utl_fassert<debug_level>(::utl::__utl_assertion_kind::kind,               \
								  module_name,                                     \
								  UTL_MAKE_SOURCE_INFO(),                          \
								  _UTL_DEBUG_WRAP_VALUES(__VA_ARGS__),             \
								  _UTL_DEBUG_TO_STRINGS(__VA_ARGS__),              \
								  _UTL_DEBUG_PARSE_EXPRESSIONS(__VA_ARGS__))       \
	? (void)0 : (void)__utl_debugbreak()                                           \
)

#define UTL_FANCY_BOUNDS_CHECK(ModuleName, DebugLevel, index, lower, upper)                        \
UTL_FANCY_ASSERT(ModuleName, DebugLevel, precondition, lower <= index, "Index below lower bound"); \
UTL_FANCY_ASSERT(ModuleName, DebugLevel, precondition, index <  upper, "Index above upper bound")

/// MARK: - Implementation
// _UTL_DEBUG_WRAP_VALUES
#define _UTL_DEBUG_WRAP_VALUE_USING_DECL(...) [&]{ \
	using ::utl::__utl_debug_level::_default;                   \
	using ::utl::__utl_debug_level::audit;                      \
	return __VA_ARGS__;                            \
}
#define _UTL_DEBUG_WRAP_VALUE(...) [&]{            \
	return __VA_ARGS__;                            \
}

#define _UTL_DEBUG_WRAP_VALUE_1(x)       \
	_UTL_DEBUG_WRAP_VALUE_USING_DECL(x)
#define _UTL_DEBUG_WRAP_VALUE_2(x, y)    \
	_UTL_DEBUG_WRAP_VALUE_USING_DECL(x), \
	_UTL_DEBUG_WRAP_VALUE(y)
#define _UTL_DEBUG_WRAP_VALUE_3(x, y, z) \
	_UTL_DEBUG_WRAP_VALUE_USING_DECL(x), \
	_UTL_DEBUG_WRAP_VALUE(y), \
	_UTL_DEBUG_WRAP_VALUE(z)

#define _UTL_DEBUG_WRAP_VALUES(...) UTL_VFUNC(_UTL_DEBUG_WRAP_VALUE_, __VA_ARGS__)

// _UTL_DEBUG_TO_STRING
#define _UTL_DEBUG_TO_STRING_1(x)                 \
	UTL_TO_STRING(x)
#define _UTL_DEBUG_TO_STRING_2(x, y)              \
	UTL_TO_STRING(x),                             \
	UTL_TO_STRING(y)
#define _UTL_DEBUG_TO_STRING_3(x, y, z)           \
	UTL_TO_STRING(x),                             \
	UTL_TO_STRING(y),                             \
	UTL_TO_STRING(z)
#define _UTL_DEBUG_TO_STRINGS(...)                \
	UTL_VFUNC(_UTL_DEBUG_TO_STRING_, __VA_ARGS__)

// _UTL_DEBUG_PARSE_EXPRESSIONS
#define _UTL_DEBUG_PARSE_EXPRESSION(x)            \
	_UTL_DEBUG_WRAP_VALUE(UTL_PARSE_EXPRESSION(x))

#define _UTL_DEBUG_PARSE_EXPRESSION_USING_DECL(x) \
	_UTL_DEBUG_WRAP_VALUE_USING_DECL(UTL_PARSE_EXPRESSION(x))

#define _UTL_DEBUG_PARSE_EXPRESSION_1(x)          \
	_UTL_DEBUG_PARSE_EXPRESSION_USING_DECL(x)
#define _UTL_DEBUG_PARSE_EXPRESSION_2(x, y)       \
	_UTL_DEBUG_PARSE_EXPRESSION_USING_DECL(x),    \
	_UTL_DEBUG_PARSE_EXPRESSION(y)
#define _UTL_DEBUG_PARSE_EXPRESSION_3(x, y, z)    \
	_UTL_DEBUG_PARSE_EXPRESSION_USING_DECL(x),    \
	_UTL_DEBUG_PARSE_EXPRESSION(y),               \
	_UTL_DEBUG_PARSE_EXPRESSION(z)
#define _UTL_DEBUG_PARSE_EXPRESSIONS(...)         \
	UTL_VFUNC(_UTL_DEBUG_PARSE_EXPRESSION_, __VA_ARGS__)

namespace utl {

	enum struct __utl_assertion_kind {
		assertion, precondition, postcondition
	};
	struct __utl_assert_level {};
	
	namespace __utl_debug_level {
		struct default_t: __utl_assert_level {} inline constexpr _default{};
		struct audit_t: __utl_assert_level {} inline constexpr audit{};
	}
	
	template <typename T>
	inline constexpr bool __utl_is_audit = std::is_same_v<T, __utl_debug_level::audit_t>;
	
	std::false_type __utl_report_assertion_failure(__utl_assertion_kind,
												   char const* module_name,
												   source_info,
												   char const* expression,
												   std::string expanded_expression,
												   char const* message) _UTL_NORETURN;
	
	constexpr bool __utl_is_debug_active(int debug_level, bool audit) {
		return debug_level > 0 && (!audit || debug_level > 1);
	}
	
	template <int DebugLevel, bool audit>
	constexpr bool __utl_fassert_impl(__utl_assertion_kind kind,
									  char const* module_name,
									  source_info data,
									  auto&& condition,
									  char const* expr,
									  auto&& expanded,
									  char const* message)
	{
		if constexpr (__utl_is_debug_active(DebugLevel, audit)) {
			return condition() || __utl_report_assertion_failure(kind,
																 module_name,
																 data,
																 expr,
																 expanded(),
																 message);
		}
		else {
			return true;
		}
	}
	
	
	// assert(cond)
	template <int DebugLevel>
	constexpr bool __utl_fassert(__utl_assertion_kind kind,
								 char const* module_name,
								 source_info data,
								 invocable_r<bool> auto&& cond,
								 char const* expr,
								 auto&& expanded)
	{
		return __utl_fassert_impl<DebugLevel, false>(kind,
													 module_name,
													 data,
													 UTL_FORWARD(cond),
													 expr,
													 UTL_FORWARD(expanded),
													 nullptr);
	}
	
	// assert(cond, message)
	template <int DebugLevel>
	constexpr bool __utl_fassert(__utl_assertion_kind kind,
								 char const* module_name,
								 source_info data,
								 invocable_r<bool> auto&& cond,
								 invocable_r<char const*> auto&& message,
								 char const* cond_expr,
								 char const*,
								 auto&& cond_expanded,
								 auto&&)
	{
		return __utl_fassert_impl<DebugLevel, false>(kind,
													 module_name,
													 data,
													 UTL_FORWARD(cond),
													 cond_expr,
													 UTL_FORWARD(cond_expanded),
													 message());
	}
	
	// assert(level, cond)
	template <int DebugLevel>
	constexpr bool __utl_fassert(__utl_assertion_kind kind,
								 char const* module_name,
								 source_info data,
								 invocable_r<__utl_assert_level> auto&& level,
								 invocable_r<bool> auto&& cond,
								 char const*,
								 char const* cond_expr,
								 auto&&,
								 auto&& cond_expanded)
	{
		
		return __utl_fassert_impl<DebugLevel,
								  __utl_is_audit<decltype(level())>>(kind,
																	 module_name,
																	 data,
																	 UTL_FORWARD(cond),
																	 cond_expr,
																	 UTL_FORWARD(cond_expanded),
																	 nullptr);
	}

	// assert(level, cond, message)
	template <int DebugLevel>
	constexpr bool __utl_fassert(__utl_assertion_kind kind,
								 char const* module_name,
								 source_info data,
								 invocable_r<__utl_assert_level> auto&& level,
								 invocable_r<bool> auto&& cond,
								 invocable_r<char const*> auto&& message,
								 char const*,
								 char const* expr,
								 char const*,
								 auto&&,
								 auto&& expanded,
								 auto&&)
	{
		return __utl_fassert_impl<DebugLevel,
								  __utl_is_audit<decltype(level())>>(kind,
																	 module_name,
																	 data,
																	 UTL_FORWARD(cond),
																	 expr,
																	 UTL_FORWARD(expanded),
																	 message());
	}
	
}

