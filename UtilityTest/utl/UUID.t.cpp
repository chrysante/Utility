#include "Catch2.hpp"
#include "StdoutReroute.hpp"
#include <utl/UUID.hpp>

TEST_CASE("UUID Serialize") {
	for (int i = 0; i < 50; ++i) {
		utl::UUID const original = utl::UUID::generate();
		std::string const text = original.to_string();
		utl::UUID const read = utl::UUID::from_string(text);
		CHECK(read == original);
	}
}
