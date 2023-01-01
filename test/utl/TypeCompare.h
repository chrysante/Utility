#pragma once

#include <iosfwd>

#include <utl/typeinfo.hpp>

namespace utl_test {

template <typename>
struct TagType {};

template <typename A, typename B>
bool operator==(TagType<A>, TagType<B>) { return std::is_same_v<A, B>; }

template <typename T>
std::ostream& operator<<(std::ostream& str, TagType<T>) {
    return str << utl::nameof<T>;
}

template <typename T>
inline constexpr TagType<T> T;

} // namespace utl_test
