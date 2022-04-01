#include "main.hpp"

#include <string>
#include <sstream>
#include <array>

static std::string SOAGenerator();

REGISTER_GENERATOR(SOAGenerator, "utl/__soa_generated.hpp");

namespace {
	struct MemberParams {
		char const* referenceQualifier = "";
	};
	
	struct GetterParams {
		bool referenceIsConst = false;
		bool functionIsConst = false;
	};
}

static void declareMembers(std::stringstream& sstr, int count, MemberParams params = {}) {
	for (int i = 0; i < count; ++i) {
		sstr << "	_UTL_SOA_MEMBER_TYPE(X" << i << ") " << params.referenceQualifier << " _UTL_SOA_MEMBER_NAME(X" << i << "); \\\n";
	}
}

static void writeGetter(std::stringstream& sstr, int count, GetterParams params = {}) {
	sstr << "	template <std::size_t I> requires (I < " << count << ") \\\n";
	sstr << "	auto" << (params.referenceIsConst ? " const" : "") << "& get() " << (params.functionIsConst ? "const" : "") << " { \\\n";
	for (int i = 0; i < count; ++i) {
		sstr << "		" << (i == 0 ? "    ":"else") << " if constexpr (I == " << i << ") return _UTL_SOA_MEMBER_NAME(X" << i << "); \\\n";
	}
	sstr << "	}\\\n";
}

static std::string SOAGenerator() {
	std::stringstream sstr;
	sstr << R"(#pragma once

#ifndef __UTL_SOA_GENERATED_INCLUDED__
#define __UTL_SOA_GENERATED_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_
#include "common.hpp"

#define _UTL_SOA_MEMBER_TYPE_IMPL(a, b) a
#define _UTL_SOA_MEMBER_NAME_IMPL(a, b) b

#define _UTL_SOA_MEMBER_TYPE(X) _UTL_SOA_MEMBER_TYPE_IMPL X
#define _UTL_SOA_MEMBER_NAME(X) _UTL_SOA_MEMBER_NAME_IMPL X

#define UTL_SOA_TYPE(Name, ...) UTL_VFUNC(_UTL_SOA_TYPE_, Name __VA_OPT__(,) __VA_ARGS__)

)";
	int const arity = 24;
	for (int count = 0; count <= arity; ++count) {
		sstr << "#define _UTL_SOA_TYPE_" << count + 1 << "(Name";
		for (int i = 0; i < count; ++i) {
			sstr << ", " << "X" << i;
		}
		sstr << ") \\\n";
		
		sstr << "\\\n";
		
		/// MARK: Forward Declarations
		sstr << "/* Forward Declarations */ \\\n";
		sstr << "struct Name; \\\n";
		sstr << "struct __##Name##_soa_reference; \\\n";
		sstr << "struct __##Name##_soa_const_reference; \\\n";
		
		sstr << "\\\n";
		/// MARK: Members Bases
		sstr << "/* Members Bases */ \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "template <typename T> \\\n";
			sstr << "struct UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X" << i << ")) { \\\n";
			sstr << "	T _UTL_SOA_MEMBER_NAME(X" << i << "); \\\n";
			sstr << "	std::add_lvalue_reference_t<T> __get() const { return const_cast<std::add_lvalue_reference_t<T>>(_UTL_SOA_MEMBER_NAME(X" << i << ")); } \\\n";
			sstr << "}; \\\n";
		}
		
		sstr << "\\\n";
		
		/// MARK: Reference
		sstr << "/* Reference */ \\\n";
		sstr << "struct __##Name##_soa_reference { \\\n";
		sstr << "	/* Members */ \\\n";
		declareMembers(sstr, count, { .referenceQualifier = "&" });
		sstr << "	__##Name##_soa_reference& operator=(__##Name##_soa_reference const&); \\\n";
		sstr << "	__##Name##_soa_reference& operator=(__##Name##_soa_const_reference const&); \\\n";
		sstr << "	__##Name##_soa_reference& operator=(Name const&); \\\n";
		if (count > 0) {
			sstr << "	/* Generic Getter */ \\\n";
			writeGetter(sstr, count, { .referenceIsConst = false, .functionIsConst = true });
		}
		
		sstr << "	constexpr operator Name() const; \\\n";
		
		/* Swap */
		sstr << "	/* Swap */ \\\n";
		sstr << "	friend constexpr void swap(__##Name##_soa_reference const& a, __##Name##_soa_reference const& b) { \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "		std::swap(a.get<" << i << ">(), b.get<" << i << ">()); \\\n";
		}
		sstr << "	} \\\n";
		
		/// End
		sstr << "}; /* End Reference */ \\\n";
		
		/// MARK: Const Reference
		sstr << "/* Const Reference */ \\\n";
		sstr << "struct __##Name##_soa_const_reference { \\\n";
		sstr << "	/* Members */ \\\n";
		declareMembers(sstr, count, { .referenceQualifier = "const&" });
		if (count > 0) {
			sstr << "	/* Generic Getter */ \\\n";
			writeGetter(sstr, count, { .referenceIsConst = true, .functionIsConst = true });
		}
		
		sstr << "	constexpr operator Name() const; \\\n";
		/// End
		sstr << "}; /* End Const Reference */ \\\n";
		sstr << "\\\n";
		
		/// MARK: Pointer
		sstr << "/* Pointer */ \\\n";
		sstr << "struct __##Name##_soa_pointer { \\\n";
		sstr << "	using element_type = Name; \\\n";
		sstr << "	/* Members */ \\\n";
		declareMembers(sstr, count, { .referenceQualifier = "*" });
		/// End
		sstr << "}; /* End Pointer */ \\\n";
		sstr << "\\\n";
		
		/// MARK: Const Pointer
		sstr << "/* Const Pointer */ \\\n";
		sstr << "struct __##Name##_soa_const_pointer { \\\n";
		sstr << "	using element_type = Name const; \\\n";
		sstr << "	/* Members */ \\\n";
		declareMembers(sstr, count, { .referenceQualifier = "const*" });
		/// End
		sstr << "}; /* End Const Pointer */ \\\n";
		sstr << "\\\n";
		
		/// MARK: Meta
		sstr << "/* Meta */ \\\n";
		sstr << "struct __##Name##_soa_meta { \\\n";
		/* struct Members */
		sstr << "	/* struct Members */ \\\n";
		if (count > 0) {
			sstr << "	struct members { \\\n";
			sstr << "		template <std::size_t I> \\\n";
			sstr << "		struct type { \\\n";
			sstr << "			static constexpr std::size_t index = I; \\\n";
			sstr << "			constexpr operator std::size_t() const { return index; } \\\n";
			sstr << "		}; \\\n";
			for (int i = 0; i < count; ++i) {
				sstr << "		using _UTL_SOA_MEMBER_NAME(X" << i << ") = type<" << i << ">; \\\n";
			}
			sstr << "	}; \\\n";
		}
		/* Typedefs */
		sstr << "	/* Typedefs */ \\\n";
		sstr << "	using tuple = std::tuple<";
		bool first = true;
		for (int i = 0; i < count; ++i) sstr << (first ? (first = false, "") : ", ") << "_UTL_SOA_MEMBER_TYPE(X" << i << ")";
		sstr << ">; \\\n";
		sstr << "	using value_type = Name; \\\n";
		sstr <<	"	using reference = __##Name##_soa_reference; \\\n";
		sstr <<	"	using const_reference = __##Name##_soa_const_reference; \\\n";
		sstr <<	"	using pointer = __##Name##_soa_pointer; \\\n";
		sstr <<	"	using const_pointer = __##Name##_soa_const_pointer; \\\n";
		sstr << "	static constexpr std::size_t member_count = " << count << "; \\\n";
		
		sstr << "	template <std::size_t Index> \\\n";
		sstr << "	struct member_base; \\\n";
		
		sstr << "	template <auto> struct make_id; \\\n";
		
		sstr << "}; /* End Meta */ \\\n";
		
		sstr << "\\\n";
		
		/// MARK: Value Type
		/* Value Type */
		sstr << "struct Name { \\\n";
		/* Members */
		sstr << "	/* Members */ \\\n";
		declareMembers(sstr, count);
		sstr << "	using __utl_soa_meta = __##Name##_soa_meta; \\\n";
		sstr << "	using members = typename __utl_soa_meta::members; \\\n";
		
		if (count > 0) {
			sstr << "	/* Generic Getter */ \\\n";
			writeGetter(sstr, count, { .referenceIsConst = false, .functionIsConst = false });
			sstr << "	/* Generic Getter (const) */ \\\n";
			writeGetter(sstr, count, { .referenceIsConst = true, .functionIsConst = true });
		}
		
		
		// struct End
		sstr << "};  /* End Value Type */ \\\n";
		
		/// MARK: Member Base Specialization
		sstr << "\\\n";
		sstr << "/* Member Base Specialization */ \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "template<> struct __##Name##_soa_meta::member_base<" << i << "> { template <typename T> using type = UTL_CONCAT(__##Name##_, _UTL_SOA_MEMBER_NAME(X" << i << "))<T>; }; \\\n";
		}
		sstr << "\\\n";
		
		/// MARK: Make ID Specialization
		sstr << "\\\n";
		sstr << "/* Make ID Specialization */ \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "template<> struct __##Name##_soa_meta::make_id<&Name::_UTL_SOA_MEMBER_NAME(X" << i << ")> { \\\n";
			sstr << "	using type = Name::members::template type<" << i << ">; \\\n";
			sstr << "}; \\\n";
		}
		sstr << "\\\n";
		
		/// MARK: Reference::operator=
		sstr << "/* Reference::operator= */ \\\n";
		sstr << "inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_reference const& x) { \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "	this->get<" << i << ">() = x.get<" << i << ">(); \\\n";
		}
		sstr << "	return *this; \\\n";
		sstr << "} \\\n";
		sstr << "inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(__##Name##_soa_const_reference const& x) { \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "	this->get<" << i << ">() = x.get<" << i << ">(); \\\n";
		}
		sstr << "	return *this; \\\n";
		sstr << "} \\\n";
		sstr << "inline __##Name##_soa_reference& __##Name##_soa_reference::operator=(Name const& x) { \\\n";
		for (int i = 0; i < count; ++i) {
			sstr << "	this->get<" << i << ">() = x.get<" << i << ">(); \\\n";
		}
		sstr << "	return *this; \\\n";
		sstr << "} \\\n";
		
		/// MARK: Conversion to Value Type */
		for (std::array const types = { "__##Name##_soa_reference", "__##Name##_soa_const_reference" };
			 auto type: types) {
			sstr << "/* Operator Structure Type */ \\\n";
			sstr << "constexpr " << type << "::operator Name() const { \\\n";
			sstr << "	return { \\\n";
			for (int i = 0; i < count; ++i) {
				sstr << "		_UTL_SOA_MEMBER_NAME(X" << i << ")" << (i != count - 1 ? "," : "") << " \\\n";
			}
			sstr << "	}; \\\n";
			sstr << "} \\\n";
		}
		
		/// MARK: Comparison
		sstr << "\\\n";
		sstr << "/* Comparison */ \\\n";
		
		for (std::array const types = { "Name", "__##Name##_soa_reference", "__##Name##_soa_const_reference" };
			 auto typeI: types) {
			for (auto typeJ: types) {
				sstr << "constexpr bool operator==(" << typeI << " const& a, " << typeJ << " const& b) { \\\n";
				if (count == 0) {
					sstr << "	return true; \\\n";
				}
				else {
					sstr << "	return \\\n";
					for (int k = 0; k < count; ++k) {
						sstr << "		a.get<" << k << ">() == b.get<" << k << ">()" << (k == count - 1 ? ";" : " &&") << " \\\n";
					}
				}
				sstr << "} \\\n";
			}
		}
		
		/// MARK: End
		sstr << "\n";
	}
	sstr << "\n";
	sstr << "#endif // __UTL_SOA_GENERATED_INCLUDED__ \n";
	
	return sstr.str();
}

