#ifndef UTL___DEBUG_HPP_
#define UTL___DEBUG_HPP_

#include <cassert>

#include <utl/__base.hpp>
#include <utl/common.hpp>

// __utl_assert
#define __utl_assert(e, ...) assert(e)

// __utl_expect
#define __utl_expect(e, ...) __utl_assert(e)

// __utl_bounds_check
#define __utl_bounds_check(index, lower, upper)                                \
    (__utl_expect(index >= lower), __utl_expect(index < upper))

namespace utl {

[[noreturn]] inline void unreachable() {
#ifndef NDEBUG
    assert(false && "Executed unreachable code path");
#else
#if __clang__ || __GNUC__
    __builtin_unreachable();
#elif _MSC_VER
    __assume(false);
#else

#endif
#endif
}

} // namespace utl

#endif // UTL___DEBUG_HPP_
