#pragma once

#include <gmp.h>
#include <memory>
#include <string>
#include <exception>
#include <iosfwd>

namespace utl {
	
	struct big_int_error: std::runtime_error {
		using std::runtime_error::runtime_error;
	};
	
	struct big_int_parse_error: big_int_error {
		using big_int_error::big_int_error;
	};
	
	/// MARK: big_int
	struct big_int {
		struct __no_init_tag{};
		
		explicit big_int(__no_init_tag) {}
		
		big_int() { mpz_init(__impl); }
		big_int(std::signed_integral auto i) { mpz_init_set_si(__impl, i); }
		big_int(std::unsigned_integral auto i) { mpz_init_set_ui(__impl, i); }
		~big_int() { mpz_clear(__impl); }
		
		big_int(big_int const& rhs) { mpz_init_set(__impl, rhs.__impl); }
		big_int(big_int&& rhs) { __impl[0] = rhs.__impl[0]; mpz_init(rhs.__impl); }
		
		big_int& operator=(big_int const& rhs) { std::destroy_at(this); std::construct_at(this, rhs); return *this; }
		big_int& operator=(big_int&& rhs) { std::destroy_at(this); std::construct_at(this, std::move(rhs)); return *this; }
		
		[[nodiscard]] static big_int parse(std::string_view str) {
			big_int result;
			int status = mpz_set_str(result.__impl, str.data(), 0);
			if (status != 0) {
				throw big_int_parse_error("Failed to parse string: " + std::string(str));
			}
			return result;
		}
		
		big_int& operator+=(big_int const& rhs)&              { mpz_add(__impl, __impl, rhs.__impl);          return *this; }
		big_int& operator+=(std::signed_integral auto rhs)&   { mpz_add(__impl, __impl, big_int(rhs).__impl); return *this; }
		big_int& operator+=(std::unsigned_integral auto rhs)& { mpz_add_ui(__impl, __impl, rhs);              return *this; }
		
		big_int& operator-=(big_int const& rhs)&              { mpz_sub(__impl, __impl, rhs.__impl);          return *this; }
		big_int& operator-=(std::signed_integral auto rhs)&   { mpz_sub(__impl, __impl, big_int(rhs).__impl); return *this; }
		big_int& operator-=(std::unsigned_integral auto rhs)& { mpz_sub_ui(__impl, __impl, rhs);              return *this; }
		
		big_int& operator*=(big_int const& rhs)&              { mpz_mul(__impl, __impl, rhs.__impl);          return *this; }
		big_int& operator*=(std::signed_integral auto rhs)&   { mpz_mul_si(__impl, __impl, rhs);              return *this; }
		big_int& operator*=(std::unsigned_integral auto rhs)& { mpz_mul_ui(__impl, __impl, rhs);              return *this; }
		
		big_int& operator/=(big_int const& rhs)&              { mpz_div(__impl, __impl, rhs.__impl);          return *this; }
		big_int& operator/=(std::signed_integral auto rhs)&   { mpz_div(__impl, __impl, big_int(rhs).__impl); return *this; }
		big_int& operator/=(std::unsigned_integral auto rhs)& { mpz_div_ui(__impl, __impl, rhs);              return *this; }
		
		big_int& operator%=(big_int const& rhs)&              { mpz_mod(__impl, __impl, rhs.__impl);          return *this; }
		big_int& operator%=(std::signed_integral auto rhs)&   { mpz_mod(__impl, __impl, big_int(rhs).__impl); return *this; }
		big_int& operator%=(std::unsigned_integral auto rhs)& { mpz_mod_ui(__impl, __impl, rhs);              return *this; }
		
		template <std::signed_integral T>
		explicit operator T() const {
			return mpz_get_si(__impl);
		}
		
		template <std::unsigned_integral T>
		explicit operator T() const {
			return mpz_get_ui(__impl);
		}
		
		explicit operator bool() const {
			return (long)*this;
		}
		
		mpz_t __impl;
	};
	
	/// MARK: Operators
	// operator+
	inline big_int operator+(big_int a, big_int const& b) {
		return std::move(a += b);
	}
	
	inline big_int operator+(big_int a, std::signed_integral auto b) {
		return std::move(a += b);
	}
	
	inline big_int operator+(std::signed_integral auto a, big_int b) {
		return std::move(b += a);
	}
	
	inline big_int operator+(big_int a, std::unsigned_integral auto b) {
		return std::move(a += b);
	}
	
	inline big_int operator+(std::unsigned_integral auto a, big_int b) {
		return std::move(b += a);
	}
	
	// operator-
	inline big_int operator-(big_int a, big_int const& b) {
		return std::move(a -= b);
	}
	
	inline big_int operator-(big_int a, std::signed_integral auto b) {
		return std::move(a -= b);
	}
	
	inline big_int operator-(std::signed_integral auto a, big_int const& b) {
		big_int result = a;
		result -= b;
		return result;
	}
	
	inline big_int operator-(big_int a, std::unsigned_integral auto b) {
		return std::move(a -= b);
	}
	
	inline big_int operator-(std::unsigned_integral auto a, big_int b) {
		mpz_ui_sub(b.__impl, a, b.__impl);
		return b;
	}
	
	// operator*
	inline big_int operator*(big_int a, big_int const& b) {
		return std::move(a *= b);
	}
	
	inline big_int operator*(big_int a, std::signed_integral auto b) {
		return std::move(a *= b);
	}
	
	inline big_int operator*(std::signed_integral auto a, big_int b) {
		return std::move(b *= a);
	}
	
	inline big_int operator*(big_int a, std::unsigned_integral auto b) {
		return std::move(a *= b);
	}
	
	inline big_int operator*(std::unsigned_integral auto a, big_int b) {
		return std::move(a *= b);
	}
	
	// operator/
	inline big_int operator/(big_int a, big_int const& b) {
		return std::move(a /= b);
	}
	
	inline big_int operator/(big_int a, std::signed_integral auto b) {
		return std::move(a /= b);
	}
	
	inline big_int operator/(std::signed_integral auto a, big_int const& b) {
		big_int result = a;
		result /= b;
		return result;
		
		return b / a;
	}
	
	inline big_int operator/(big_int a, std::unsigned_integral auto b) {
		return std::move(a /= b);
	}
	
	inline big_int operator/(std::unsigned_integral auto a, big_int const& b) {
		big_int result = a;
		result /= b;
		return result;
	}

	// operator%
	inline big_int operator%(big_int a, big_int const& b) {
		return std::move(a %= b);
	}
	
	inline big_int operator%(big_int a, std::signed_integral auto b) {
		return std::move(a %= b);
	}
	
	inline big_int operator%(std::signed_integral auto a, big_int const& b) {
		big_int result = a;
		result %= b;
		return result;
	}
	
	inline big_int operator%(big_int a, std::unsigned_integral auto b) {
		return std::move(a %= b);
	}
	
	inline big_int operator%(std::unsigned_integral auto a, big_int const& b) {
		big_int result = a;
		result %= b;
		return result;
	}
	
	// operator<<(std::ostream&)
	template <typename CharT>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& str, big_int const& i) {
		char* text;
		[[maybe_unused]] int num_chars = gmp_asprintf(&text, "%Zd", i.__impl);
		str << text;
		void (*freefunc)(void *, size_t) = nullptr;
		mp_get_memory_functions(NULL, NULL, &freefunc);
		freefunc(text, num_chars + 1);
		return str;
	}
	
}
