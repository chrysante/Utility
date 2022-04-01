#include "utl/__soa.hpp"
#include "mtl/mtl.hpp"
#include <iostream>
#include "utl/typeinfo.hpp"

#include "utl/utility.hpp"

using namespace mtl::short_types;

namespace worldmachine {

	UTL_SOA_TYPE(Node,
				 (int, id),
				 (float3, position),
				 (float2, size)
				 );

}

namespace utl {
	
	template <typename T, T>
	struct __make_id_impl;
	
	template <auto X>
	struct __make_id: __make_id_impl<decltype(X), X> {};
	
	template <auto X> constexpr auto id = typename __make_id<X>::type{};
	
	template <typename MemberType, typename SOAType, auto Value>
	struct __make_id_impl<MemberType SOAType::*, Value> {
		using type = typename SOAType::__utl_soa_meta::template make_id<Value>::type;
	};
}


int main() {
	using namespace worldmachine;
	utl::soa<Node> s;
	s.push_back(Node{ .size = { 1 } });
	
	s.erase(s.end() - 1);
	
}
