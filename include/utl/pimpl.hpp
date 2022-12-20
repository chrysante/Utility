#pragma once

#include "__base.hpp"

_UTL_SYSTEM_HEADER_

#include "common.hpp"

#include <concepts>
#include <cstddef>
#include <new>
#include <type_traits>

namespace utl {

template <typename T>
struct derived_tag_t {
    using type = T;
};

template <typename T>
constexpr derived_tag_t<T> derived_tag = derived_tag_t<T>{};

template <typename Impl, std::size_t Size, std::size_t Alignment = alignof(std::max_align_t)>
class local_pimpl {
public:
    local_pimpl() requires(std::is_default_constructible_v<Impl>) { _construct(); }

    template <typename... Args>
    local_pimpl(Args&&... args) requires(std::is_constructible_v<Impl, Args...>) {
        _construct(UTL_FORWARD(args)...);
    }

    template <std::derived_from<Impl> Derived, typename... Args>
    requires(std::is_constructible_v<Derived, Args...>) local_pimpl(derived_tag_t<Derived>, Args&&... args) {
        _construct<Derived>(UTL_FORWARD(args)...);
    }

    local_pimpl(local_pimpl const& rhs) requires(std::is_copy_constructible_v<Impl>) { _construct(*rhs); }

    local_pimpl(local_pimpl&& rhs) noexcept requires(std::is_move_constructible_v<Impl>) {
        _construct(std::move(*rhs));
    }

    local_pimpl& operator=(local_pimpl const& rhs) requires(std::is_copy_assignable_v<Impl>) {
        pointer()->operator=(*rhs);
        return *this;
    }

    local_pimpl& operator=(local_pimpl&& rhs) noexcept requires(std::is_move_assignable_v<Impl>) {
        pointer()->operator=(std::move(*rhs));
        return *this;
    }

    ~local_pimpl() {
        static_assert(sizeof(Impl) <= Size);
        static_assert(alignof(Impl) <= Alignment);
        std::destroy_at(pointer());
    }

    local_pimpl(no_init_t) noexcept {}

    template <std::derived_from<Impl> Derived = Impl, typename... Args>
    requires(std::is_constructible_v<Derived, Args...>) void construct(Args&&... args) {
        _construct<Derived>(UTL_FORWARD(args)...);
    }

    Impl* pointer() noexcept { return const_cast<Impl*>(utl::as_const(*this).pointer()); }
    Impl const* pointer() const noexcept { return reinterpret_cast<Impl const*>(_buffer); }

    Impl* operator->() noexcept { return pointer(); }
    Impl const* operator->() const noexcept { return pointer(); }

    Impl& operator*() noexcept { return *pointer(); }
    Impl const& operator*() const noexcept { return *pointer(); }

private:
    template <typename Derived = Impl>
    void _construct(auto&&... args) {
        static_assert(sizeof(Derived) <= Size);
        static_assert(alignof(Derived) <= Alignment);
        ::new ((void*)_buffer) Derived(UTL_FORWARD(args)...);
    }

private:
    alignas(Alignment) char _buffer[Size];
};

} // namespace utl
