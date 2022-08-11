#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "common.hpp"
#include <concepts>
#include <cstdint>
#include <new>

namespace utl {
	
	struct __some_vt {
		virtual void* copy_allocate(void const* from) const = 0;
		virtual void copy_construct(void const* from, void* to) const = 0;
		virtual void copy_assign(void const* from, void* to) const = 0;
		
		virtual void* move_allocate(void* from) const = 0;
		virtual void move_construct(void* from, void* to) const = 0;
		virtual void move_assign(void* from, void* to) const = 0;
	};
	
	template <typename T>
	struct __some_vt_impl: __some_vt {
		void* copy_allocate(void const* from) const final {
			return new T(*(T const*)from);
		}
		
		void copy_construct(void const* from, void* to) const final {
			::new (to) T(*(T const*)from);
		}
		
		void copy_assign(void const* from, void* to) const final {
			*(T*)to = *(T const*)from;
		}
		
		void* move_allocate(void* from) const final {
			return new T(std::move(*(T*)from));
		}
		
		void move_construct(void* from, void* to) const final {
			::new (to) T(std::move(*(T const*)from));
		}
		
		void move_assign(void* from, void* to) const final {
			*(T*)to = std::move(*(T const*)from);
		}
		
		inline static __some_vt_impl const instance{};
	};
	
	template <std::size_t SBOSize, typename Base>
	struct basic_some {
		basic_some() = default;
		template <std::derived_from<Base> D>
		basic_some(D&& d) {
			if constexpr (sizeof(D) <= SBOSize && alignof(D) <= 8) {
				__vt = (void const*)((std::uintptr_t)&__some_vt_impl<D>::instance | 1);
				::new ((void*)&__storage) D(std::forward<D>(d));
			}
			else {
				__vt = &__some_vt_impl<D>::instance;
				__obj = new D(UTL_FORWARD(d));
			}
		}
		basic_some(basic_some const& rhs) {
			__vt = rhs.__vt;
			if (rhs.__is_local()) {
				__vtable().copy_construct(&rhs.__storage, &__storage);
			}
			else {
				__obj = (Base*)__vtable().copy_allocate(rhs.__obj);
			}
		}
		basic_some(basic_some&& rhs) noexcept {
			__vt = rhs.__vt;
			if (!__vt) {
				return;
			}
			if (rhs.__is_local()) {
				__vtable().move_construct(&rhs.__storage, &__storage);
			}
			else {
				__obj = (Base*)__vtable().move_allocate(rhs.__obj);
			}
		}
		~basic_some() {
			clear();
		}
		basic_some& operator=(basic_some const& rhs) {
			clear();
			::new (this) basic_some(rhs);
			return *this;
		}
		basic_some& operator=(basic_some&& rhs) noexcept {
			clear();
			::new (this) basic_some(std::move(rhs));
			return *this;
		}
		
		void clear() {
			if (!*this) {
				return;
			}
			__ptr()->~Base();
			if (!__is_local()) {
				delete __ptr();
			}
			__vt = nullptr;
		}
		
		explicit operator bool() const { return !!__vt; }
		
		Base& get() { return *__ptr(); }
		Base const& get() const { return *__ptr(); }
		
		Base* operator->() { return __ptr(); }
		Base const* operator->() const { return __ptr(); }
		
	private:
		bool __is_local() const { return ((std::uintptr_t)__vt) & 1; }
		__some_vt const& __vtable() const { return *(__some_vt const*)((std::uintptr_t)__vt & ~(std::uintptr_t)1); }
		Base* __ptr() { return (Base*)((basic_some const*)this)->__ptr();  }
		Base const* __ptr() const { return __is_local() ? (Base*)&__storage : __obj;  }
	
	private:
		void const* __vt = nullptr;
		union {
			char __storage[SBOSize];
			Base* __obj;
		};
	};
	
	template <typename Base>
	using some = basic_some<56, Base>;
	
}
