#pragma once

#include <concepts>
#include <iosfwd>
#include <functional>

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename T>
struct __strmanip_objwrapper {
    T obj;
};

template <typename T>
struct __strmanip_objwrapper<T&> {
    T& obj;
};

template <typename T>
__strmanip_objwrapper(T&&) -> __strmanip_objwrapper<T>;

template <typename T>
__strmanip_objwrapper(T&) -> __strmanip_objwrapper<T&>;


template <typename F>
struct streammanip {
    constexpr streammanip() requires std::is_default_constructible_v<F> = default;
    constexpr streammanip(F const& f): __f(f) {}
    constexpr streammanip(F&& f): __f(std::move(f)) {}

    template <typename... Args>
    [[nodiscard]] constexpr auto operator()(Args&&... args) const
    requires requires(F& f, std::ostream& ostream) {
        std::invoke(f, ostream, args...);
    } {
        return utl::streammanip(
            [args = std::tuple{ __strmanip_objwrapper{ std::forward<Args>(args) }... },
             f = __f](std::ostream& ostream) {
            std::apply(
                [&](auto&... args) { std::invoke(f, ostream, args.obj...); },
                args);
        });
    }

    template <typename CharT, typename Traits>
    requires std::invocable<F, std::basic_ostream<CharT, Traits>&>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& ostream, streammanip<F> const& manip) {
        std::invoke(manip.__f, ostream);
        return ostream;
    }
    
    F __f;
};

template <typename... Args>
struct vstreammanip: streammanip<std::function<void(std::ostream&, Args...)>> {
    using __base = streammanip<std::function<void(std::ostream&, Args...)>>;
    using __base::__base;
    
    template <typename F>
    vstreammanip(F&& f): __base(std::forward<F>(f)) {}
};

} // namespace utl
