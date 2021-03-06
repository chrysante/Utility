#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_
#include "type_traits.hpp"
#include <type_traits>
#include "__memory_resource_base.hpp"
#include <memory>

namespace utl {
	
	template <typename T>
	using ref = std::shared_ptr<T>;
	
	template <typename T, typename ... Args>
	requires (std::is_constructible<T, Args...>::value)
	ref<T> make_ref(Args&&... args) {
		return std::allocate_shared<T>(pmr::polymorphic_allocator<T>(), std::forward<Args>(args)...);
	}
	
	template <typename T>
	ref<utl::remove_cvref_t<T>> make_ref(T&& t) {
		using U = utl::remove_cvref_t<T>;
		return std::allocate_shared<U>(pmr::polymorphic_allocator<U>(), std::forward<T>(t));
	}
	
	template <typename T>
	struct enable_ref_from_this: std::enable_shared_from_this<T> {
		utl::ref<T> ref() { return this->shared_from_this(); }
		utl::ref<T const> ref() const { return this->shared_from_this(); }
	};
	
	template <typename T, typename Deleter = std::default_delete<T>>
	using unique_ref = std::unique_ptr<T, Deleter>;
	
	template <typename T, typename ... Args>
	unique_ref<T> make_unique_ref(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }
	
	template <typename T>
	using weak_ref = std::weak_ptr<T>;
	
}
