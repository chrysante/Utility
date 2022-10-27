#include "uuid.hpp"

#include <ostream>
#include <sstream>
#include <array>
#include <random>

#include "format.hpp"
#include "bit.hpp"

namespace utl {

static uuid::value_type generate_id() {
    std::mt19937_64 rng(std::random_device{}());
    std::array<utl::uint64_t, 2> value = { rng(), rng() };

#if defined(UTL_128_BIT_ARITHMETIC)
    static_assert(std::is_same_v<typename uuid::value_type, utl::uint128_t>);
    return utl::bit_cast<typename uuid::value_type>(value);
#else
    return value;
#endif
}

uuid uuid::generate() {
    return uuid(generate_id());
}

uuid uuid::from_string(std::string_view str) {
    return from_string(std::string(str));
}

uuid uuid::from_string(std::string&& str) {
    std::istringstream sstr(std::move(str));
    std::array<std::uint32_t, 4> ints;

    std::hex(sstr);

    for (std::size_t i = 0; i < 4; ++i) {
        sstr >> ints[i];
    }
    return utl::bit_cast<uuid>(ints);
}

std::string uuid::to_string() const {
    auto const data = utl::bit_cast<std::array<std::uint32_t, 4>>(this->value());
    return utl::format("{:x} {:x} {:x} {:x}", data[0], data[1], data[2], data[3]);
}

std::ostream& operator<<(std::ostream& str, uuid id) {
    return str << id.to_string();
}

} // namespace utl