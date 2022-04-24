#include "UUID.hpp"

#include <atomic>
#include <ostream>
#include <sstream>
#include "format.hpp"

#include <random>
#include <array>
#include "bit.hpp"

namespace utl {

	static UUID::value_type _generate() {
		std::mt19937_64 rng(std::random_device{}());
		std::array<utl::uint64_t, 2> value = { rng(), rng() };
		
#if defined(UTL_128_BIT_ARITHMETIC)
		static_assert(std::is_same_v<typename UUID::value_type, utl::uint128_t>);
		return utl::bit_cast<typename UUID::value_type>(value);
#else
		return value;
#endif
	}
	
	UUID UUID::generate() {
		return UUID(_generate());
	}
	
	UUID UUID::from_string(std::string_view str) {
		return from_string(std::string(str));
	}
	
	UUID UUID::from_string(std::string&& str) {
		std::istringstream sstr(std::move(str));
		std::array<std::uint32_t, 4> ints;
		
		std::hex(sstr);
		
		for (int i = 0; i < 4; ++i) {
			sstr >> ints[i];
		}
		return utl::bit_cast<UUID>(ints);
	}
	
	std::string UUID::to_string() const {
		auto const data = utl::bit_cast<std::array<std::uint32_t, 4>>(this->value());
		return utl::format("{:x} {:x} {:x} {:x}", data[0], data[1], data[2], data[3]);
	}
	
	std::ostream& operator<<(std::ostream& str, UUID id) {
		return str << id.to_string();
	}
	
}
