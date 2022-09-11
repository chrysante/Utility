#pragma once

#ifndef __UTL_OPTREF_INCLUDED__
#define __UTL_OPTREF_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "utility.hpp"
#include "bit.hpp"

namespace utl {
	
	template <typename T>
	struct optref {
		optref(): __ptr{ nullptr, false } {}
		optref(T& r): __ptr{ &r, true } {}
		
		bool has_value() const { return __ptr.integer(); }
		T& get() const { __utl_expect(has_value()); return *__ptr.pointer(); }
		
		explicit operator bool() const { return has_value(); }
		operator T&() const { return get(); }
		
		T& operator=(std::add_const_t<T>& rhs) const { return get() = rhs; }
	
		optref<std::remove_const_t<T>> __to_mutable() const requires std::is_const_v<T> {
			using U = optref<std::remove_const_t<T>>;
			return utl::bit_cast<U>(*this);
		}
		
		pointer_int_pair<T*, unsigned, 1> __ptr;
	};
	
}

#endif // __UTL_OPTREF_INCLUDED__
