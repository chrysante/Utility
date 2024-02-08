#ifndef UTL_UUID_HPP_
#define UTL_UUID_HPP_

#include <array>
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <string>

#include <utl/__base.hpp>
#include <utl/api.hpp>
#include <utl/bit.hpp>
#include <utl/hash.hpp>

namespace utl {

class uuid;

class UTL_API uuid {
public:
#if defined(UTL_128_BIT_ARITHMETIC)
    using value_type = utl::uint128_t;
#else
    using value_type = std::array<std::uint64_t, 2>;
#endif

public:
    uuid() = default;
    static uuid generate();
    value_type value() const noexcept { return _value; }

    static uuid construct_from_value(value_type value) { return uuid(value); }

    static uuid from_string(std::string_view);
    static uuid from_string(std::string&&);

    std::string to_string() const;

private:
    uuid(value_type v): _value(v) {}

private:
    value_type _value{};
};

inline bool operator==(uuid a, uuid b) noexcept {
    return a.value() == b.value();
}

inline bool is_null(uuid const& id) {
    return id == uuid{};
}

UTL_API std::ostream& operator<<(std::ostream& str, uuid id);

} // namespace utl

template <>
struct std::hash<utl::uuid> {
    std::size_t operator()(utl::uuid id) const {
#if defined(UTL_128_BIT_ARITHMETIC)
        auto [a, b] = utl::bit_cast<std::array<std::uint64_t, 2>>(id.value());
#else
        auto [a, b] = id.value();
#endif
        auto begin = std::hash<std::uint64_t>{}(a);
        return utl::hash_combine(begin, b);
    }
};

#endif // UTL_UUID_HPP_
