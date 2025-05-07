#ifndef UTL_TYPECOMPARE_H_
#define UTL_TYPECOMPARE_H_

#include <iosfwd>

#include <utl/typeinfo.hpp>

namespace utl_test {

template <typename>
struct TagType {};

template <typename A, typename B>
bool operator==(TagType<A>, TagType<B>) {
    return std::is_same_v<A, B>;
}

template <typename T>
std::ostream& operator<<(std::ostream& str, TagType<T>) {
    return str << utl::nameof<T>;
}

template <typename U>
inline constexpr TagType<U> T;

} // namespace utl_test

#endif // UTL_TYPECOMPARE_H_
