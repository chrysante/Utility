#pragma once

#include <concepts>
#include <iosfwd>

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename F>
struct streammanip {
    constexpr streammanip() requires std::is_default_constructible_v<F> = default;
    constexpr streammanip(F const& f): __f(f) {}
    constexpr streammanip(F&& f): __f(std::move(f)) {}

    template <typename... Args>
    constexpr auto operator()(Args&&... args) const {
        return utl::streammanip([=, f = __f](std::ostream& ostream) { std::invoke(f, ostream, args...); });
    }

    template <typename CharT, typename Traits>
    requires std::invocable<F, std::basic_ostream<CharT, Traits>&>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& ostream, streammanip<F> const& manip) {
        std::invoke(manip.__f, ostream);
        return ostream;
    }
    
    F __f;
};

} // namespace utl
