#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_
#include "type_traits.hpp"

namespace utl::_private {
	enum struct named_type_availability {
		unavailable = 0,
		inheritance = 1,
		conversion = 2
	};
	
	template <typename T>
	constexpr named_type_availability named_type_available() {
		if constexpr (std::is_fundamental<T>::value || std::is_pointer<T>::value || std::is_union<T>::value) {
			return named_type_availability::conversion;
		}
		else if constexpr (std::is_class<T>::value) {
			return named_type_availability::inheritance;
		}
		else if constexpr (std::is_enum<T>::value) {
			return named_type_availability::conversion;
		}
		else {
			return named_type_availability::unavailable;
		}
	}
	
}

namespace utl {
	
	template <typename T, typename Name,
			  _private::named_type_availability = _private::named_type_available<T>()>
	struct named_type;
	
	template <typename T, typename Name>
	struct named_type<T, Name, _private::named_type_availability::inheritance>: public T {
	public:
		template <typename... Args> requires (constructible<T, Args...>)
		constexpr named_type<T, Name, _private::named_type_availability::inheritance>(Args&&... args): T(std::forward<Args>(args)...) {}
		constexpr named_type<T, Name, _private::named_type_availability::inheritance>(T const& value): T(value) {}
		constexpr named_type<T, Name, _private::named_type_availability::inheritance>(T&& value) : T(std::move(value)) {}
	};
	
	template <typename T, typename Name>
	struct named_type<T, Name, _private::named_type_availability::conversion> {
	public:
		// default constructors
		named_type<T, Name, _private::named_type_availability::conversion>() = default;
		constexpr named_type<T, Name, _private::named_type_availability::conversion>(T value) noexcept: m_value(value) {}
		
		// union constructor
		template <typename U>
		constexpr named_type<T, Name, _private::named_type_availability::conversion>(U&& u)
			requires (is_list_initializable<T, U>::value && std::is_union<T>::value)
		: m_value{ std::forward<U>(u) } {}
		
		// union member access
		constexpr T* operator->() noexcept requires(std::is_union<T>::value) { return &m_value; }
		constexpr T const* operator->() const noexcept { return &m_value; }
		
		// get
		constexpr T& get() { return m_value; }
		constexpr T const& get() const { return m_value; }
		
		// implicit conversion
		constexpr operator T&() noexcept { return get(); }
		constexpr operator T const&() const noexcept { return get(); }
		
		// explicit conversion (constructor)
		template <typename U> requires (constructible_from<T, U>)
		constexpr explicit named_type<T, Name, _private::named_type_availability::conversion>(U u) noexcept: m_value(static_cast<T>(u)) {}
		template <constructible_from<T> U>
		constexpr explicit operator U() const { return static_cast<U>(get()); }
		
	private:
		T m_value;
	};
	
	template <typename T, typename Name> requires requires(T& t) { { t & t } -> convertible_to<T>; }
	constexpr named_type<T, Name> operator&(named_type<T, Name> const& a, named_type<T, Name> const& b) {
		return a.get() & b.get();
	}
	
	template <typename T, typename Name>  requires requires(T& t) { { t | t } -> convertible_to<T>; }
	constexpr named_type<T, Name> operator|(named_type<T, Name> const& a, named_type<T, Name> const& b) {
		return a.get() | b.get();
	}
	
	template <typename T, typename Name>  requires requires(T& t) { { t ^ t } -> convertible_to<T>; }
	constexpr named_type<T, Name> operator^(named_type<T, Name> const& a, named_type<T, Name> const& b) {
		return a.get() ^ b.get();
	}
	
	template <typename T, typename Name>  requires requires(T& t) { { ~t } -> convertible_to<T>; }
	constexpr named_type<T, Name> operator~(named_type<T, Name> const& a) {
		return ~a.get();
	}
	
	template <typename T, typename Name> requires requires(T& t) { !t; }
	constexpr auto operator!(named_type<T, Name> const& a) {
		return !a.get();
	}
	
	
}
