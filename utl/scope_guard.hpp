#pragma once


#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "common.hpp"
#include "concepts.hpp"
#include <exception>

namespace utl {
	
	namespace _private {
		enum class scope_guard_type {
			any, success, failure
		};
		
		template <bool Armed> struct scope_guard_base1 {};
		template <> struct scope_guard_base1<true> {
			bool _armed = true;
		};
		template <bool Armed, _private::scope_guard_type Type>
		struct scope_guard_base2: scope_guard_base1<Armed> {
			int _uncaught_exceptions = std::uncaught_exceptions();
		};
		template <bool Armed>
		struct scope_guard_base2<Armed, scope_guard_type::any>: scope_guard_base1<Armed> {};
	
		template <invocable F, bool Armed, _private::scope_guard_type Type>
		class basic_scope_guard: _private::scope_guard_base2<Armed, Type> {
			F _f;
		public:
			constexpr basic_scope_guard(F const& f) noexcept(std::is_nothrow_copy_constructible_v<F>): _f(f) {}
			constexpr basic_scope_guard(F&& f) noexcept(std::is_nothrow_move_constructible_v<F>): _f(std::move(f)) {}
			
			constexpr ~basic_scope_guard() noexcept(Type == _private::scope_guard_type::failure) {
				if constexpr (Armed) {
					if (!this->_armed)
						return;
				}
				if constexpr (Type == _private::scope_guard_type::success) {
					if UTL_UNLIKELY (this->_uncaught_exceptions < std::uncaught_exceptions() /* failure */)
						return;
				}
				else if constexpr (Type == _private::scope_guard_type::failure) {
					if UTL_LIKELY (this->_uncaught_exceptions == std::uncaught_exceptions() /* success */)
						return;
				}
				_f();
			}
			
			constexpr void arm() noexcept requires(Armed == true) { this->_armed = true; }
			constexpr void disarm() noexcept requires(Armed == true) { this->_armed = false; }
			constexpr void execute() noexcept requires(Armed == true) { _f(); this->_armed = false; }
		};
		
	}
	
#define _UTL_SCOPE_GUARD_SPECIALIZATION(Name, Armed, Type) \
	template <invocable F> \
	class Name: public _private::basic_scope_guard<F, Armed, _private::scope_guard_type::Type> { \
		using base = _private::basic_scope_guard<F, Armed, _private::scope_guard_type::Type>; \
	public: \
		using base::base; \
	}; \
	template <typename F> \
	Name(F) -> Name<F>
	
	_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard,               false, any);
	_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard_success,       false, success);
	_UTL_SCOPE_GUARD_SPECIALIZATION(scope_guard_failure,       false, failure);
	_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard,         true,  any);
	_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard_success, true,  success);
	_UTL_SCOPE_GUARD_SPECIALIZATION(armed_scope_guard_failure, true,  failure);
	
#undef _UTL_SCOPE_GUARD_SPECIALIZATION
	
}

#ifdef UTL_DEFER_MACROS

#define utl_defer         \
	::utl::scope_guard         UTL_ANONYMOUS_VARIABLE(_utlScopeGuardState_) = [&]()          -> void
#define utl_defer_failure \
	::utl::scope_guard_failure UTL_ANONYMOUS_VARIABLE(_utlScopeGuardState_) = [&]() noexcept -> void
#define utl_defer_success \
	::utl::scope_guard_success UTL_ANONYMOUS_VARIABLE(_utlScopeGuardState_) = [&]()          -> void

#endif // UTL_DEFER_MACROS

