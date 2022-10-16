#pragma once

#include <type_traits>
#include <string>
#include <filesystem>

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {
	
	// MARK: - interface
	class dynamic_library {
	public:
		// constructors
		dynamic_library() = default;
		explicit dynamic_library(std::filesystem::path);
		
		dynamic_library(dynamic_library const&) = default;
		dynamic_library(dynamic_library&&) noexcept;
		
		// destructor
		~dynamic_library();
		
		// assignment
		dynamic_library& operator=(dynamic_library const&)& = default;
		dynamic_library& operator=(dynamic_library&&)& noexcept;
		
		// modifiers
		void reload();
		void load(std::filesystem::path new_path);
		void close() { _destroy(); }
		
		bool is_loaded() const;
		
		// access
		// returns:
		//      T as function pointer, if T is a function signature
		// else T*
		template <typename>
		auto symbol_ptr(std::string_view name) const;
		
		// query
		bool is_open() const noexcept { return !!native_handle(); }
		
		__utl_nodiscard void* native_handle() noexcept { return _handle; }
		__utl_nodiscard void const* native_handle() const noexcept { return _handle; }
		
		std::filesystem::path const& current_path() const noexcept { return _path; }
		
		bool operator==(dynamic_library const& rhs) const {
			return this->_handle == rhs._handle;
		}
		
		// MARK: - implementation
	private:
		__utl_nodiscard void* _load_symbol(std::string_view name) const;
		void _load_lib();
		void _destroy() noexcept;
		void _clear_errors() const;
		void _handle_error(std::string_view) const;
		
	private:
		std::filesystem::path _path;
		void* _handle = nullptr;
	};
	
	namespace _private::dlsym_traits {
		template <typename>
		struct is_func_sig: std::false_type{};
		template <typename R, typename... T>
		struct is_func_sig<R(T...)>: std::true_type{};
		
		template <typename T>
		struct func_sig_to_ptr { using type = T; };
		template <typename R, typename... T>
		struct func_sig_to_ptr<R(T...)> { using type = R(*)(T...); };
	}
	
	template <typename T>
	auto dynamic_library::symbol_ptr(std::string_view name) const {
		using namespace _private::dlsym_traits;
		using ptr_t = std::conditional_t<is_func_sig<T>::value, typename func_sig_to_ptr<T>::type, T*>;
		return reinterpret_cast<ptr_t>(_load_symbol(name));
	}
	
}
