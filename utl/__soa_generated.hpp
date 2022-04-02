#pragma once

#ifndef __UTL_SOA_GENERATED_INCLUDED__
#define __UTL_SOA_GENERATED_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_
#include "common.hpp"

namespace utl {
	auto constexpr __soa_identity = [](auto&& x) -> decltype(auto) { return x; };
}

#define _UTL_SOA_MEMBER_TYPE_IMPL(a, b) a
#define _UTL_SOA_MEMBER_NAME_IMPL(a, b) b

#define _UTL_SOA_MEMBER_TYPE(X) _UTL_SOA_MEMBER_TYPE_IMPL X
#define _UTL_SOA_MEMBER_NAME(X) _UTL_SOA_MEMBER_NAME_IMPL X

#define UTL_SOA_TYPE(Name, ...) UTL_VFUNC(_UTL_SOA_TYPE_, Name __VA_OPT__(,) __VA_ARGS__)

#define _UTL_SOA_TYPE_1(Name) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	/* Typedefs */ \
	using tuple = std::tuple<>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 0; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
\
\
/* Make ID Specialization */ \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return true; \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return true; \
} \

#define _UTL_SOA_TYPE_2(Name, X0) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 1) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 1) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 1; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 1) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 1) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()); \
} \

#define _UTL_SOA_TYPE_3(Name, X0, X1) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 2) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 2) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 2; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 2) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 2) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()); \
} \

#define _UTL_SOA_TYPE_4(Name, X0, X1, X2) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 3) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 3) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 3; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 3) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 3) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()); \
} \

#define _UTL_SOA_TYPE_5(Name, X0, X1, X2, X3) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 4) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 4) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 4; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 4) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 4) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()); \
} \

#define _UTL_SOA_TYPE_6(Name, X0, X1, X2, X3, X4) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 5) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 5) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 5; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 5) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 5) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()); \
} \

#define _UTL_SOA_TYPE_7(Name, X0, X1, X2, X3, X4, X5) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 6) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 6) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 6; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 6) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 6) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()); \
} \

#define _UTL_SOA_TYPE_8(Name, X0, X1, X2, X3, X4, X5, X6) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 7) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 7) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 7; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 7) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 7) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()); \
} \

#define _UTL_SOA_TYPE_9(Name, X0, X1, X2, X3, X4, X5, X6, X7) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 8) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 8) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 8; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 8) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 8) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()); \
} \

#define _UTL_SOA_TYPE_10(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 9) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 9) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 9; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 9) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 9) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()); \
} \

#define _UTL_SOA_TYPE_11(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 10) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 10) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 10; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 10) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 10) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()); \
} \

#define _UTL_SOA_TYPE_12(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 11) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 11) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 11; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 11) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 11) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()); \
} \

#define _UTL_SOA_TYPE_13(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 12) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 12) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 12; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 12) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 12) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()); \
} \

#define _UTL_SOA_TYPE_14(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 13) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 13) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 13; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 13) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 13) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()); \
} \

#define _UTL_SOA_TYPE_15(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 14) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 14) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 14; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 14) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 14) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()); \
} \

#define _UTL_SOA_TYPE_16(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 15) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 15) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 15; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 15) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 15) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()); \
} \

#define _UTL_SOA_TYPE_17(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 16) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 16) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 16; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 16) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 16) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()); \
} \

#define _UTL_SOA_TYPE_18(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 17) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 17) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 17; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 17) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 17) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()); \
} \

#define _UTL_SOA_TYPE_19(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 18) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 18) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 18; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 18) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 18) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()); \
} \

#define _UTL_SOA_TYPE_20(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 19) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 19) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 19; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 19) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 19) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()); \
} \

#define _UTL_SOA_TYPE_21(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18, X19) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19)) { \
	T _UTL_SOA_MEMBER_NAME(X19); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X19)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) & _UTL_SOA_MEMBER_NAME(X19); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 20) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
		std::swap(a.get<19>(), b.get<19>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const& _UTL_SOA_MEMBER_NAME(X19); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 20) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) * _UTL_SOA_MEMBER_NAME(X19); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const* _UTL_SOA_MEMBER_NAME(X19); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
		using _UTL_SOA_MEMBER_NAME(X19) = type<19>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18), _UTL_SOA_MEMBER_TYPE(X19)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 20; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19)  _UTL_SOA_MEMBER_NAME(X19); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 20) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 20) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<19> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X19)> { \
	using type = Name::members::template type<19>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()); \
} \

#define _UTL_SOA_TYPE_22(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18, X19, X20) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19)) { \
	T _UTL_SOA_MEMBER_NAME(X19); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X19)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20)) { \
	T _UTL_SOA_MEMBER_NAME(X20); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X20)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) & _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) & _UTL_SOA_MEMBER_NAME(X20); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 21) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
		std::swap(a.get<19>(), b.get<19>()); \
		std::swap(a.get<20>(), b.get<20>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const& _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const& _UTL_SOA_MEMBER_NAME(X20); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 21) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) * _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) * _UTL_SOA_MEMBER_NAME(X20); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const* _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const* _UTL_SOA_MEMBER_NAME(X20); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
		using _UTL_SOA_MEMBER_NAME(X19) = type<19>; \
		using _UTL_SOA_MEMBER_NAME(X20) = type<20>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18), _UTL_SOA_MEMBER_TYPE(X19), _UTL_SOA_MEMBER_TYPE(X20)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 21; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19)  _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20)  _UTL_SOA_MEMBER_NAME(X20); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 21) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 21) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<19> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<20> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X19)> { \
	using type = Name::members::template type<19>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X20)> { \
	using type = Name::members::template type<20>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()); \
} \

#define _UTL_SOA_TYPE_23(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18, X19, X20, X21) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19)) { \
	T _UTL_SOA_MEMBER_NAME(X19); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X19)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20)) { \
	T _UTL_SOA_MEMBER_NAME(X20); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X20)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21)) { \
	T _UTL_SOA_MEMBER_NAME(X21); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X21)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) & _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) & _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) & _UTL_SOA_MEMBER_NAME(X21); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 22) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
		std::swap(a.get<19>(), b.get<19>()); \
		std::swap(a.get<20>(), b.get<20>()); \
		std::swap(a.get<21>(), b.get<21>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const& _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const& _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const& _UTL_SOA_MEMBER_NAME(X21); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 22) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) * _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) * _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) * _UTL_SOA_MEMBER_NAME(X21); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const* _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const* _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const* _UTL_SOA_MEMBER_NAME(X21); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
		using _UTL_SOA_MEMBER_NAME(X19) = type<19>; \
		using _UTL_SOA_MEMBER_NAME(X20) = type<20>; \
		using _UTL_SOA_MEMBER_NAME(X21) = type<21>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18), _UTL_SOA_MEMBER_TYPE(X19), _UTL_SOA_MEMBER_TYPE(X20), _UTL_SOA_MEMBER_TYPE(X21)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 22; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19)  _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20)  _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21)  _UTL_SOA_MEMBER_NAME(X21); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 22) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 22) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<19> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<20> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<21> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X19)> { \
	using type = Name::members::template type<19>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X20)> { \
	using type = Name::members::template type<20>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X21)> { \
	using type = Name::members::template type<21>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()); \
} \

#define _UTL_SOA_TYPE_24(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18, X19, X20, X21, X22) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19)) { \
	T _UTL_SOA_MEMBER_NAME(X19); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X19)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20)) { \
	T _UTL_SOA_MEMBER_NAME(X20); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X20)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21)) { \
	T _UTL_SOA_MEMBER_NAME(X21); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X21)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X22)) { \
	T _UTL_SOA_MEMBER_NAME(X22); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X22)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) & _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) & _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) & _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) & _UTL_SOA_MEMBER_NAME(X22); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 23) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
		std::swap(a.get<19>(), b.get<19>()); \
		std::swap(a.get<20>(), b.get<20>()); \
		std::swap(a.get<21>(), b.get<21>()); \
		std::swap(a.get<22>(), b.get<22>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const& _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const& _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const& _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) const& _UTL_SOA_MEMBER_NAME(X22); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 23) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) * _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) * _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) * _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) * _UTL_SOA_MEMBER_NAME(X22); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const* _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const* _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const* _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) const* _UTL_SOA_MEMBER_NAME(X22); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
		using _UTL_SOA_MEMBER_NAME(X19) = type<19>; \
		using _UTL_SOA_MEMBER_NAME(X20) = type<20>; \
		using _UTL_SOA_MEMBER_NAME(X21) = type<21>; \
		using _UTL_SOA_MEMBER_NAME(X22) = type<22>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18), _UTL_SOA_MEMBER_TYPE(X19), _UTL_SOA_MEMBER_TYPE(X20), _UTL_SOA_MEMBER_TYPE(X21), _UTL_SOA_MEMBER_TYPE(X22)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 23; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19)  _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20)  _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21)  _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22)  _UTL_SOA_MEMBER_NAME(X22); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 23) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 23) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<19> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<20> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<21> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<22> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X22))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X19)> { \
	using type = Name::members::template type<19>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X20)> { \
	using type = Name::members::template type<20>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X21)> { \
	using type = Name::members::template type<21>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X22)> { \
	using type = Name::members::template type<22>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21), \
		&_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21), \
		&_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21), \
		*_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21), \
		*_UTL_SOA_MEMBER_NAME(X22) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()); \
} \

#define _UTL_SOA_TYPE_25(Name, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, X17, X18, X19, X20, X21, X22, X23) \
\
/* Forward Declarations */ \
struct Name; \
struct __##Name##_soa_reference; \
struct __##Name##_soa_const_reference; \
struct __##Name##_soa_pointer; \
struct __##Name##_soa_const_pointer; \
\
/* Members Bases */ \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0)) { \
	T _UTL_SOA_MEMBER_NAME(X0); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X0)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1)) { \
	T _UTL_SOA_MEMBER_NAME(X1); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X1)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2)) { \
	T _UTL_SOA_MEMBER_NAME(X2); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X2)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3)) { \
	T _UTL_SOA_MEMBER_NAME(X3); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X3)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4)) { \
	T _UTL_SOA_MEMBER_NAME(X4); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X4)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5)) { \
	T _UTL_SOA_MEMBER_NAME(X5); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X5)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6)) { \
	T _UTL_SOA_MEMBER_NAME(X6); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X6)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7)) { \
	T _UTL_SOA_MEMBER_NAME(X7); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X7)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8)) { \
	T _UTL_SOA_MEMBER_NAME(X8); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X8)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9)) { \
	T _UTL_SOA_MEMBER_NAME(X9); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X9)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10)) { \
	T _UTL_SOA_MEMBER_NAME(X10); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X10)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11)) { \
	T _UTL_SOA_MEMBER_NAME(X11); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X11)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12)) { \
	T _UTL_SOA_MEMBER_NAME(X12); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X12)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13)) { \
	T _UTL_SOA_MEMBER_NAME(X13); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X13)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14)) { \
	T _UTL_SOA_MEMBER_NAME(X14); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X14)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15)) { \
	T _UTL_SOA_MEMBER_NAME(X15); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X15)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16)) { \
	T _UTL_SOA_MEMBER_NAME(X16); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X16)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17)) { \
	T _UTL_SOA_MEMBER_NAME(X17); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X17)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18)) { \
	T _UTL_SOA_MEMBER_NAME(X18); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X18)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19)) { \
	T _UTL_SOA_MEMBER_NAME(X19); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X19)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20)) { \
	T _UTL_SOA_MEMBER_NAME(X20); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X20)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21)) { \
	T _UTL_SOA_MEMBER_NAME(X21); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X21)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X22)) { \
	T _UTL_SOA_MEMBER_NAME(X22); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X22)); } \
}; \
template <typename T> \
struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X23)) { \
	T _UTL_SOA_MEMBER_NAME(X23); \
	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X23)); } \
}; \
\
/* Reference */ \
struct __##Name##_soa_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) & _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) & _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) & _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) & _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) & _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) & _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) & _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) & _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) & _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) & _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) & _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) & _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) & _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) & _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) & _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) & _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) & _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) & _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) & _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) & _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) & _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) & _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) & _UTL_SOA_MEMBER_NAME(X22); \
	_UTL_SOA_MEMBER_TYPE(X23) & _UTL_SOA_MEMBER_NAME(X23); \
	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \
	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \
	__##Name##_soa_reference& operator=(Name const&); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 24) \
	auto& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
		else if constexpr (I == 23) return _UTL_SOA_MEMBER_NAME(X23); \
	}\
	operator Name() const; \
	operator __##Name##_soa_const_reference() const; \
	__##Name##_soa_pointer operator&() const; \
	/* Swap */ \
	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
		std::swap(a.get<0>(), b.get<0>()); \
		std::swap(a.get<1>(), b.get<1>()); \
		std::swap(a.get<2>(), b.get<2>()); \
		std::swap(a.get<3>(), b.get<3>()); \
		std::swap(a.get<4>(), b.get<4>()); \
		std::swap(a.get<5>(), b.get<5>()); \
		std::swap(a.get<6>(), b.get<6>()); \
		std::swap(a.get<7>(), b.get<7>()); \
		std::swap(a.get<8>(), b.get<8>()); \
		std::swap(a.get<9>(), b.get<9>()); \
		std::swap(a.get<10>(), b.get<10>()); \
		std::swap(a.get<11>(), b.get<11>()); \
		std::swap(a.get<12>(), b.get<12>()); \
		std::swap(a.get<13>(), b.get<13>()); \
		std::swap(a.get<14>(), b.get<14>()); \
		std::swap(a.get<15>(), b.get<15>()); \
		std::swap(a.get<16>(), b.get<16>()); \
		std::swap(a.get<17>(), b.get<17>()); \
		std::swap(a.get<18>(), b.get<18>()); \
		std::swap(a.get<19>(), b.get<19>()); \
		std::swap(a.get<20>(), b.get<20>()); \
		std::swap(a.get<21>(), b.get<21>()); \
		std::swap(a.get<22>(), b.get<22>()); \
		std::swap(a.get<23>(), b.get<23>()); \
	} \
}; /* End Reference */ \
/* Const Reference */ \
struct __##Name##_soa_const_reference { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const& _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const& _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const& _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const& _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const& _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const& _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const& _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const& _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const& _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const& _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const& _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const& _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const& _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const& _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const& _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const& _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const& _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const& _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const& _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const& _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const& _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const& _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) const& _UTL_SOA_MEMBER_NAME(X22); \
	_UTL_SOA_MEMBER_TYPE(X23) const& _UTL_SOA_MEMBER_NAME(X23); \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 24) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
		else if constexpr (I == 23) return _UTL_SOA_MEMBER_NAME(X23); \
	}\
	operator Name() const; \
	__##Name##_soa_const_pointer operator&() const; \
}; /* End Const Reference */ \
\
/* Pointer */ \
struct __##Name##_soa_pointer { \
	using element_type = Name; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) * _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) * _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) * _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) * _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) * _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) * _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) * _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) * _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) * _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) * _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) * _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) * _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) * _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) * _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) * _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) * _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) * _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) * _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) * _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) * _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) * _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) * _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) * _UTL_SOA_MEMBER_NAME(X22); \
	_UTL_SOA_MEMBER_TYPE(X23) * _UTL_SOA_MEMBER_NAME(X23); \
	__##Name##_soa_reference operator*() const; \
}; /* End Pointer */ \
\
/* Const Pointer */ \
struct __##Name##_soa_const_pointer { \
	using element_type = Name const; \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0) const* _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1) const* _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2) const* _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3) const* _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4) const* _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5) const* _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6) const* _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7) const* _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8) const* _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9) const* _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10) const* _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11) const* _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12) const* _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13) const* _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14) const* _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15) const* _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16) const* _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17) const* _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18) const* _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19) const* _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20) const* _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21) const* _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22) const* _UTL_SOA_MEMBER_NAME(X22); \
	_UTL_SOA_MEMBER_TYPE(X23) const* _UTL_SOA_MEMBER_NAME(X23); \
	__##Name##_soa_const_reference operator*() const; \
}; /* End Const Pointer */ \
\
/* Meta */ \
struct __##Name##_soa_meta { \
	/* struct Members */ \
	struct members { \
		template <std::size_t I> \
		struct type { \
			static constexpr std::size_t index = I; \
			constexpr operator std::size_t() const { return index; } \
		}; \
		using _UTL_SOA_MEMBER_NAME(X0) = type<0>; \
		using _UTL_SOA_MEMBER_NAME(X1) = type<1>; \
		using _UTL_SOA_MEMBER_NAME(X2) = type<2>; \
		using _UTL_SOA_MEMBER_NAME(X3) = type<3>; \
		using _UTL_SOA_MEMBER_NAME(X4) = type<4>; \
		using _UTL_SOA_MEMBER_NAME(X5) = type<5>; \
		using _UTL_SOA_MEMBER_NAME(X6) = type<6>; \
		using _UTL_SOA_MEMBER_NAME(X7) = type<7>; \
		using _UTL_SOA_MEMBER_NAME(X8) = type<8>; \
		using _UTL_SOA_MEMBER_NAME(X9) = type<9>; \
		using _UTL_SOA_MEMBER_NAME(X10) = type<10>; \
		using _UTL_SOA_MEMBER_NAME(X11) = type<11>; \
		using _UTL_SOA_MEMBER_NAME(X12) = type<12>; \
		using _UTL_SOA_MEMBER_NAME(X13) = type<13>; \
		using _UTL_SOA_MEMBER_NAME(X14) = type<14>; \
		using _UTL_SOA_MEMBER_NAME(X15) = type<15>; \
		using _UTL_SOA_MEMBER_NAME(X16) = type<16>; \
		using _UTL_SOA_MEMBER_NAME(X17) = type<17>; \
		using _UTL_SOA_MEMBER_NAME(X18) = type<18>; \
		using _UTL_SOA_MEMBER_NAME(X19) = type<19>; \
		using _UTL_SOA_MEMBER_NAME(X20) = type<20>; \
		using _UTL_SOA_MEMBER_NAME(X21) = type<21>; \
		using _UTL_SOA_MEMBER_NAME(X22) = type<22>; \
		using _UTL_SOA_MEMBER_NAME(X23) = type<23>; \
	}; \
	/* Typedefs */ \
	using tuple = std::tuple<_UTL_SOA_MEMBER_TYPE(X0), _UTL_SOA_MEMBER_TYPE(X1), _UTL_SOA_MEMBER_TYPE(X2), _UTL_SOA_MEMBER_TYPE(X3), _UTL_SOA_MEMBER_TYPE(X4), _UTL_SOA_MEMBER_TYPE(X5), _UTL_SOA_MEMBER_TYPE(X6), _UTL_SOA_MEMBER_TYPE(X7), _UTL_SOA_MEMBER_TYPE(X8), _UTL_SOA_MEMBER_TYPE(X9), _UTL_SOA_MEMBER_TYPE(X10), _UTL_SOA_MEMBER_TYPE(X11), _UTL_SOA_MEMBER_TYPE(X12), _UTL_SOA_MEMBER_TYPE(X13), _UTL_SOA_MEMBER_TYPE(X14), _UTL_SOA_MEMBER_TYPE(X15), _UTL_SOA_MEMBER_TYPE(X16), _UTL_SOA_MEMBER_TYPE(X17), _UTL_SOA_MEMBER_TYPE(X18), _UTL_SOA_MEMBER_TYPE(X19), _UTL_SOA_MEMBER_TYPE(X20), _UTL_SOA_MEMBER_TYPE(X21), _UTL_SOA_MEMBER_TYPE(X22), _UTL_SOA_MEMBER_TYPE(X23)>; \
	using value_type = Name; \
	using reference = __##Name##_soa_reference; \
	using const_reference = __##Name##_soa_const_reference; \
	using pointer = __##Name##_soa_pointer; \
	using const_pointer = __##Name##_soa_const_pointer; \
	static constexpr std::size_t member_count = 24; \
	template <std::size_t Index> \
	struct member_base; \
	template <auto> struct make_id; \
}; /* End Meta */ \
\
struct Name { \
	/* Members */ \
	_UTL_SOA_MEMBER_TYPE(X0)  _UTL_SOA_MEMBER_NAME(X0); \
	_UTL_SOA_MEMBER_TYPE(X1)  _UTL_SOA_MEMBER_NAME(X1); \
	_UTL_SOA_MEMBER_TYPE(X2)  _UTL_SOA_MEMBER_NAME(X2); \
	_UTL_SOA_MEMBER_TYPE(X3)  _UTL_SOA_MEMBER_NAME(X3); \
	_UTL_SOA_MEMBER_TYPE(X4)  _UTL_SOA_MEMBER_NAME(X4); \
	_UTL_SOA_MEMBER_TYPE(X5)  _UTL_SOA_MEMBER_NAME(X5); \
	_UTL_SOA_MEMBER_TYPE(X6)  _UTL_SOA_MEMBER_NAME(X6); \
	_UTL_SOA_MEMBER_TYPE(X7)  _UTL_SOA_MEMBER_NAME(X7); \
	_UTL_SOA_MEMBER_TYPE(X8)  _UTL_SOA_MEMBER_NAME(X8); \
	_UTL_SOA_MEMBER_TYPE(X9)  _UTL_SOA_MEMBER_NAME(X9); \
	_UTL_SOA_MEMBER_TYPE(X10)  _UTL_SOA_MEMBER_NAME(X10); \
	_UTL_SOA_MEMBER_TYPE(X11)  _UTL_SOA_MEMBER_NAME(X11); \
	_UTL_SOA_MEMBER_TYPE(X12)  _UTL_SOA_MEMBER_NAME(X12); \
	_UTL_SOA_MEMBER_TYPE(X13)  _UTL_SOA_MEMBER_NAME(X13); \
	_UTL_SOA_MEMBER_TYPE(X14)  _UTL_SOA_MEMBER_NAME(X14); \
	_UTL_SOA_MEMBER_TYPE(X15)  _UTL_SOA_MEMBER_NAME(X15); \
	_UTL_SOA_MEMBER_TYPE(X16)  _UTL_SOA_MEMBER_NAME(X16); \
	_UTL_SOA_MEMBER_TYPE(X17)  _UTL_SOA_MEMBER_NAME(X17); \
	_UTL_SOA_MEMBER_TYPE(X18)  _UTL_SOA_MEMBER_NAME(X18); \
	_UTL_SOA_MEMBER_TYPE(X19)  _UTL_SOA_MEMBER_NAME(X19); \
	_UTL_SOA_MEMBER_TYPE(X20)  _UTL_SOA_MEMBER_NAME(X20); \
	_UTL_SOA_MEMBER_TYPE(X21)  _UTL_SOA_MEMBER_NAME(X21); \
	_UTL_SOA_MEMBER_TYPE(X22)  _UTL_SOA_MEMBER_NAME(X22); \
	_UTL_SOA_MEMBER_TYPE(X23)  _UTL_SOA_MEMBER_NAME(X23); \
	operator __##Name##_soa_reference(); \
	operator __##Name##_soa_const_reference() const; \
	using __utl_soa_meta = __##Name##_soa_meta; \
	using members = typename __utl_soa_meta::members; \
	using reference = typename __utl_soa_meta::reference; \
	using const_reference = typename __utl_soa_meta::const_reference; \
	/* Generic Getter */ \
	template <std::size_t I> requires (I < 24) \
	auto& get()  { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
		else if constexpr (I == 23) return _UTL_SOA_MEMBER_NAME(X23); \
	}\
	/* Generic Getter (const) */ \
	template <std::size_t I> requires (I < 24) \
	auto const& get() const { \
		     if constexpr (I == 0) return _UTL_SOA_MEMBER_NAME(X0); \
		else if constexpr (I == 1) return _UTL_SOA_MEMBER_NAME(X1); \
		else if constexpr (I == 2) return _UTL_SOA_MEMBER_NAME(X2); \
		else if constexpr (I == 3) return _UTL_SOA_MEMBER_NAME(X3); \
		else if constexpr (I == 4) return _UTL_SOA_MEMBER_NAME(X4); \
		else if constexpr (I == 5) return _UTL_SOA_MEMBER_NAME(X5); \
		else if constexpr (I == 6) return _UTL_SOA_MEMBER_NAME(X6); \
		else if constexpr (I == 7) return _UTL_SOA_MEMBER_NAME(X7); \
		else if constexpr (I == 8) return _UTL_SOA_MEMBER_NAME(X8); \
		else if constexpr (I == 9) return _UTL_SOA_MEMBER_NAME(X9); \
		else if constexpr (I == 10) return _UTL_SOA_MEMBER_NAME(X10); \
		else if constexpr (I == 11) return _UTL_SOA_MEMBER_NAME(X11); \
		else if constexpr (I == 12) return _UTL_SOA_MEMBER_NAME(X12); \
		else if constexpr (I == 13) return _UTL_SOA_MEMBER_NAME(X13); \
		else if constexpr (I == 14) return _UTL_SOA_MEMBER_NAME(X14); \
		else if constexpr (I == 15) return _UTL_SOA_MEMBER_NAME(X15); \
		else if constexpr (I == 16) return _UTL_SOA_MEMBER_NAME(X16); \
		else if constexpr (I == 17) return _UTL_SOA_MEMBER_NAME(X17); \
		else if constexpr (I == 18) return _UTL_SOA_MEMBER_NAME(X18); \
		else if constexpr (I == 19) return _UTL_SOA_MEMBER_NAME(X19); \
		else if constexpr (I == 20) return _UTL_SOA_MEMBER_NAME(X20); \
		else if constexpr (I == 21) return _UTL_SOA_MEMBER_NAME(X21); \
		else if constexpr (I == 22) return _UTL_SOA_MEMBER_NAME(X22); \
		else if constexpr (I == 23) return _UTL_SOA_MEMBER_NAME(X23); \
	}\
};  /* End Value Type */ \
\
/* Member Base Specialization */ \
template<> struct __##Name##_soa_meta::member_base<0> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X0))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<1> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X1))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<2> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X2))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<3> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X3))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<4> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X4))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<5> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X5))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<6> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X6))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<7> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X7))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<8> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X8))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<9> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X9))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<10> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X10))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<11> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X11))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<12> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X12))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<13> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X13))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<14> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X14))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<15> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X15))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<16> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X16))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<17> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X17))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<18> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X18))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<19> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X19))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<20> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X20))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<21> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X21))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<22> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X22))<T>; }; \
template<> struct __##Name##_soa_meta::member_base<23> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X23))<T>; }; \
\
\
/* Make ID Specialization */ \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X0)> { \
	using type = Name::members::template type<0>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X1)> { \
	using type = Name::members::template type<1>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X2)> { \
	using type = Name::members::template type<2>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X3)> { \
	using type = Name::members::template type<3>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X4)> { \
	using type = Name::members::template type<4>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X5)> { \
	using type = Name::members::template type<5>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X6)> { \
	using type = Name::members::template type<6>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X7)> { \
	using type = Name::members::template type<7>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X8)> { \
	using type = Name::members::template type<8>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X9)> { \
	using type = Name::members::template type<9>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X10)> { \
	using type = Name::members::template type<10>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X11)> { \
	using type = Name::members::template type<11>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X12)> { \
	using type = Name::members::template type<12>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X13)> { \
	using type = Name::members::template type<13>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X14)> { \
	using type = Name::members::template type<14>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X15)> { \
	using type = Name::members::template type<15>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X16)> { \
	using type = Name::members::template type<16>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X17)> { \
	using type = Name::members::template type<17>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X18)> { \
	using type = Name::members::template type<18>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X19)> { \
	using type = Name::members::template type<19>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X20)> { \
	using type = Name::members::template type<20>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X21)> { \
	using type = Name::members::template type<21>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X22)> { \
	using type = Name::members::template type<22>; \
}; \
template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X23)> { \
	using type = Name::members::template type<23>; \
}; \
\
/* Reference::operator= */ \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	this->get<23>() = x.get<23>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	this->get<23>() = x.get<23>(); \
	return *this; \
} \
inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \
	this->get<0>() = x.get<0>(); \
	this->get<1>() = x.get<1>(); \
	this->get<2>() = x.get<2>(); \
	this->get<3>() = x.get<3>(); \
	this->get<4>() = x.get<4>(); \
	this->get<5>() = x.get<5>(); \
	this->get<6>() = x.get<6>(); \
	this->get<7>() = x.get<7>(); \
	this->get<8>() = x.get<8>(); \
	this->get<9>() = x.get<9>(); \
	this->get<10>() = x.get<10>(); \
	this->get<11>() = x.get<11>(); \
	this->get<12>() = x.get<12>(); \
	this->get<13>() = x.get<13>(); \
	this->get<14>() = x.get<14>(); \
	this->get<15>() = x.get<15>(); \
	this->get<16>() = x.get<16>(); \
	this->get<17>() = x.get<17>(); \
	this->get<18>() = x.get<18>(); \
	this->get<19>() = x.get<19>(); \
	this->get<20>() = x.get<20>(); \
	this->get<21>() = x.get<21>(); \
	this->get<22>() = x.get<22>(); \
	this->get<23>() = x.get<23>(); \
	return *this; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22), \
		_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Conversion to Value Type */ \
inline __##Name##_soa_const_reference::operator Name() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22), \
		_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Conversion Reference -> Const Reference */ \
inline __##Name##_soa_reference::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22), \
		_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Conversion Value Type -> Reference */ \
inline Name::operator __##Name##_soa_reference() { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22), \
		_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Conversion Value Type -> Const Reference */ \
inline Name::operator __##Name##_soa_const_reference() const { \
	return { \
		_UTL_SOA_MEMBER_NAME(X0), \
		_UTL_SOA_MEMBER_NAME(X1), \
		_UTL_SOA_MEMBER_NAME(X2), \
		_UTL_SOA_MEMBER_NAME(X3), \
		_UTL_SOA_MEMBER_NAME(X4), \
		_UTL_SOA_MEMBER_NAME(X5), \
		_UTL_SOA_MEMBER_NAME(X6), \
		_UTL_SOA_MEMBER_NAME(X7), \
		_UTL_SOA_MEMBER_NAME(X8), \
		_UTL_SOA_MEMBER_NAME(X9), \
		_UTL_SOA_MEMBER_NAME(X10), \
		_UTL_SOA_MEMBER_NAME(X11), \
		_UTL_SOA_MEMBER_NAME(X12), \
		_UTL_SOA_MEMBER_NAME(X13), \
		_UTL_SOA_MEMBER_NAME(X14), \
		_UTL_SOA_MEMBER_NAME(X15), \
		_UTL_SOA_MEMBER_NAME(X16), \
		_UTL_SOA_MEMBER_NAME(X17), \
		_UTL_SOA_MEMBER_NAME(X18), \
		_UTL_SOA_MEMBER_NAME(X19), \
		_UTL_SOA_MEMBER_NAME(X20), \
		_UTL_SOA_MEMBER_NAME(X21), \
		_UTL_SOA_MEMBER_NAME(X22), \
		_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Reference::operator& */ \
inline __##Name##_soa_pointer __##Name##_soa_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21), \
		&_UTL_SOA_MEMBER_NAME(X22), \
		&_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
inline __##Name##_soa_const_pointer __##Name##_soa_const_reference::operator&() const { \
	return { \
		&_UTL_SOA_MEMBER_NAME(X0), \
		&_UTL_SOA_MEMBER_NAME(X1), \
		&_UTL_SOA_MEMBER_NAME(X2), \
		&_UTL_SOA_MEMBER_NAME(X3), \
		&_UTL_SOA_MEMBER_NAME(X4), \
		&_UTL_SOA_MEMBER_NAME(X5), \
		&_UTL_SOA_MEMBER_NAME(X6), \
		&_UTL_SOA_MEMBER_NAME(X7), \
		&_UTL_SOA_MEMBER_NAME(X8), \
		&_UTL_SOA_MEMBER_NAME(X9), \
		&_UTL_SOA_MEMBER_NAME(X10), \
		&_UTL_SOA_MEMBER_NAME(X11), \
		&_UTL_SOA_MEMBER_NAME(X12), \
		&_UTL_SOA_MEMBER_NAME(X13), \
		&_UTL_SOA_MEMBER_NAME(X14), \
		&_UTL_SOA_MEMBER_NAME(X15), \
		&_UTL_SOA_MEMBER_NAME(X16), \
		&_UTL_SOA_MEMBER_NAME(X17), \
		&_UTL_SOA_MEMBER_NAME(X18), \
		&_UTL_SOA_MEMBER_NAME(X19), \
		&_UTL_SOA_MEMBER_NAME(X20), \
		&_UTL_SOA_MEMBER_NAME(X21), \
		&_UTL_SOA_MEMBER_NAME(X22), \
		&_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
/* Reference::operator* */ \
inline __##Name##_soa_reference __##Name##_soa_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21), \
		*_UTL_SOA_MEMBER_NAME(X22), \
		*_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
inline __##Name##_soa_const_reference __##Name##_soa_const_pointer::operator*() const { \
	return { \
		*_UTL_SOA_MEMBER_NAME(X0), \
		*_UTL_SOA_MEMBER_NAME(X1), \
		*_UTL_SOA_MEMBER_NAME(X2), \
		*_UTL_SOA_MEMBER_NAME(X3), \
		*_UTL_SOA_MEMBER_NAME(X4), \
		*_UTL_SOA_MEMBER_NAME(X5), \
		*_UTL_SOA_MEMBER_NAME(X6), \
		*_UTL_SOA_MEMBER_NAME(X7), \
		*_UTL_SOA_MEMBER_NAME(X8), \
		*_UTL_SOA_MEMBER_NAME(X9), \
		*_UTL_SOA_MEMBER_NAME(X10), \
		*_UTL_SOA_MEMBER_NAME(X11), \
		*_UTL_SOA_MEMBER_NAME(X12), \
		*_UTL_SOA_MEMBER_NAME(X13), \
		*_UTL_SOA_MEMBER_NAME(X14), \
		*_UTL_SOA_MEMBER_NAME(X15), \
		*_UTL_SOA_MEMBER_NAME(X16), \
		*_UTL_SOA_MEMBER_NAME(X17), \
		*_UTL_SOA_MEMBER_NAME(X18), \
		*_UTL_SOA_MEMBER_NAME(X19), \
		*_UTL_SOA_MEMBER_NAME(X20), \
		*_UTL_SOA_MEMBER_NAME(X21), \
		*_UTL_SOA_MEMBER_NAME(X22), \
		*_UTL_SOA_MEMBER_NAME(X23) \
	}; \
} \
\
/* Comparison */ \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(Name const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, Name const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \
template <auto Id = utl::__soa_identity> \
inline bool operator==(__##Name##_soa_const_reference const& a, __##Name##_soa_const_reference const& b) { \
	return \
		Id(a.get<0>()) == Id(b.get<0>()) && \
		Id(a.get<1>()) == Id(b.get<1>()) && \
		Id(a.get<2>()) == Id(b.get<2>()) && \
		Id(a.get<3>()) == Id(b.get<3>()) && \
		Id(a.get<4>()) == Id(b.get<4>()) && \
		Id(a.get<5>()) == Id(b.get<5>()) && \
		Id(a.get<6>()) == Id(b.get<6>()) && \
		Id(a.get<7>()) == Id(b.get<7>()) && \
		Id(a.get<8>()) == Id(b.get<8>()) && \
		Id(a.get<9>()) == Id(b.get<9>()) && \
		Id(a.get<10>()) == Id(b.get<10>()) && \
		Id(a.get<11>()) == Id(b.get<11>()) && \
		Id(a.get<12>()) == Id(b.get<12>()) && \
		Id(a.get<13>()) == Id(b.get<13>()) && \
		Id(a.get<14>()) == Id(b.get<14>()) && \
		Id(a.get<15>()) == Id(b.get<15>()) && \
		Id(a.get<16>()) == Id(b.get<16>()) && \
		Id(a.get<17>()) == Id(b.get<17>()) && \
		Id(a.get<18>()) == Id(b.get<18>()) && \
		Id(a.get<19>()) == Id(b.get<19>()) && \
		Id(a.get<20>()) == Id(b.get<20>()) && \
		Id(a.get<21>()) == Id(b.get<21>()) && \
		Id(a.get<22>()) == Id(b.get<22>()) && \
		Id(a.get<23>()) == Id(b.get<23>()); \
} \


#endif // __UTL_SOA_GENERATED_INCLUDED__ 
