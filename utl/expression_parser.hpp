#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <type_traits>
#include "format.hpp"

namespace utl {
	
	struct expression_parser {
		std::string expression;
	};
	
	
#define UTL_PARSE_EXPRESSION(...) ((::utl::expression_parser{} ->* __VA_ARGS__).expression)
	
	namespace _private {
		struct _expression_parser {
			std::string expression;
		};
	}
	
	namespace _private {
		template <typename T>
		_expression_parser operator_impl(auto&& p, T&& rhs, char const* name) {
			if constexpr (std::is_same_v<std::decay_t<T>, bool>)
				return { utl::format("{}{}{}", UTL_FORWARD(p).expression, name, rhs ? "true" : "false") };
			else
			{
				if constexpr (requires(std::ostream& str, T t) { str << t; }) {
					return { utl::format("{}{}{}", UTL_FORWARD(p).expression, name, rhs) };
				}
				else {
					return { utl::format("{}{}{}", UTL_FORWARD(p).expression, name, "???") };
				}
			}
		}
	}
	
	// init
	template <typename T>
	_private::_expression_parser operator->*(expression_parser const& p, T&& rhs) {
		return _private::operator_impl(p, UTL_FORWARD(rhs), "");
	}
	template <typename T>
	_private::_expression_parser operator->*(expression_parser&& p, T&& rhs) {
		return _private::operator_impl(std::move(p), UTL_FORWARD(rhs), "");
	}
	
#define _UTL_EXPRESSION_PARSER_OP_IMPL(op) \
	template <typename T> \
_private::_expression_parser operator op(_private::_expression_parser const& p, T&& rhs) { \
		return _private::operator_impl(p, UTL_FORWARD(rhs), " "#op" "); \
	} \
	template <typename T> \
_private::_expression_parser operator op(_private::_expression_parser&& p, T&& rhs) { \
		return _private::operator_impl(std::move(p), UTL_FORWARD(rhs), " "#op" "); \
	}
	
	namespace _private {
	
		_UTL_EXPRESSION_PARSER_OP_IMPL(->*);
		_UTL_EXPRESSION_PARSER_OP_IMPL(+);
		_UTL_EXPRESSION_PARSER_OP_IMPL(-);
		_UTL_EXPRESSION_PARSER_OP_IMPL(*);
		_UTL_EXPRESSION_PARSER_OP_IMPL(/);
		_UTL_EXPRESSION_PARSER_OP_IMPL(%);
		_UTL_EXPRESSION_PARSER_OP_IMPL(&&);
		_UTL_EXPRESSION_PARSER_OP_IMPL(||);
		_UTL_EXPRESSION_PARSER_OP_IMPL(&);
		_UTL_EXPRESSION_PARSER_OP_IMPL(|);
		_UTL_EXPRESSION_PARSER_OP_IMPL(^);
		_UTL_EXPRESSION_PARSER_OP_IMPL(<<);
		_UTL_EXPRESSION_PARSER_OP_IMPL(>>);
		_UTL_EXPRESSION_PARSER_OP_IMPL(==);
		_UTL_EXPRESSION_PARSER_OP_IMPL(!=);
		_UTL_EXPRESSION_PARSER_OP_IMPL(<);
		_UTL_EXPRESSION_PARSER_OP_IMPL(<=);
		_UTL_EXPRESSION_PARSER_OP_IMPL(>);
		_UTL_EXPRESSION_PARSER_OP_IMPL(>=);
		
	}
	
}
