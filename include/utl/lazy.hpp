#pragma once

#include "__base.hpp"
#include "concepts.hpp"
#include "functional.hpp"
#include "type_traits.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <std::invocable F>
class lazy {
public:
    using value_type = typename std::invoke_result<F>::type;

    constexpr lazy(F f) noexcept: _f(std::move(f)) {}

    constexpr value_type evaluate() const { return std::invoke(_f); }

    constexpr value_type operator()() const { return evaluate(); }

    constexpr operator value_type() const { return evaluate(); }

private:
    F _f;
};

template <typename T>
using any_lazy = lazy<utl::function<T>>;

} // namespace utl
