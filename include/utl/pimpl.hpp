#pragma once

#include <concepts>
#include <cstddef>
#include <new>
#include <type_traits>

#include <utl/__base.hpp>
#include <utl/common.hpp>

namespace utl {

template <typename T>
struct derived_tag_t {
    using type = T;
};

template <typename T>
constexpr derived_tag_t<T> derived_tag = derived_tag_t<T>{};

/// Pimpl without memory indirection. \p Size and \p Alignment must be specified
/// manually because this class is meant to be instantiated with an incomplete
/// \p Impl type.
/// The canonical use case is a class like `Insulated` below,
/// where the special member functions are defined out-of-line after definition
/// of `Insulated::Impl`.
///  The insulation doesn't allow to use `requires` clauses
/// in the special member functions of `local_pimpl`, because they are checked
/// on instantiation of the class, before instantiation of the special member
/// functions themselves. That's why the checks are implemented as
/// `static_assert`'s.
///
///     struct Insulated {
///         Insulated();
///         Insulated(Insulated const&);
///         Insulated& operator=(Insulated const&);
///         ~Insulated();
///
///         struct Impl;
///         utl::local_pimpl<Impl> impl;
///     };
///
/// \Note For move-only types the copy operations have to be explicitly deleted.
template <typename Impl, std::size_t Size,
          std::size_t Alignment = alignof(std::max_align_t)>
class local_pimpl {
public:
    local_pimpl() {
        static_assert(std::is_default_constructible_v<Impl>);
        _construct();
    }

    template <typename... Args>
    local_pimpl(Args&&... args) {
        static_assert(std::is_constructible_v<Impl, Args...>);
        _construct(UTL_FORWARD(args)...);
    }

    template <std::derived_from<Impl> Derived, typename... Args>
    local_pimpl(derived_tag_t<Derived>, Args&&... args) {
        static_assert(std::is_constructible_v<Derived, Args...>);
        _construct<Derived>(UTL_FORWARD(args)...);
    }

    local_pimpl(local_pimpl const& rhs) {
        static_assert(std::is_copy_constructible_v<Impl>);
        _construct(*rhs);
    }

    local_pimpl(local_pimpl&& rhs) noexcept {
        static_assert(std::is_move_constructible_v<Impl>);
        _construct(std::move(*rhs));
    }

    local_pimpl& operator=(local_pimpl const& rhs) {
        static_assert(std::is_copy_assignable_v<Impl>);
        pointer()->operator=(*rhs);
        return *this;
    }

    local_pimpl& operator=(local_pimpl&& rhs) noexcept {
        static_assert(std::is_move_assignable_v<Impl>);
        pointer()->operator=(std::move(*rhs));
        return *this;
    }

    ~local_pimpl() {
        static_assert(sizeof(Impl) <= Size);
        static_assert(alignof(Impl) <= Alignment);
        std::destroy_at(pointer());
    }

    Impl* pointer() noexcept {
        return const_cast<Impl*>(std::as_const(*this).pointer());
    }
    Impl const* pointer() const noexcept {
        return reinterpret_cast<Impl const*>(_buffer);
    }

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
