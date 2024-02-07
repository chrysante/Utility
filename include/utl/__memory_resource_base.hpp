#pragma once

#include <cstddef>
#include <exception>
#include <new>

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "concepts.hpp"
#include "type_traits.hpp"

namespace utl::pmr {

class memory_resource;
class monotonic_buffer_resource;
class unsynchronized_pool_resource;
class synchronized_pool_resource;
class monitor_resource;

memory_resource* new_delete_resource() noexcept;
memory_resource* null_memory_resource() noexcept;
memory_resource* get_default_resource();
void set_default_resource(memory_resource*);

} // namespace utl::pmr

namespace utl::pmr {

/// MARK: - memory_resource [interface]
class memory_resource {
public:
    virtual ~memory_resource() = default;

    void* allocate(std::size_t size,
                   std::size_t alignment = alignof(std::max_align_t));
    void deallocate(void* memory, std::size_t size,
                    std::size_t alignment = alignof(std::max_align_t));
    bool is_equal(memory_resource const& rhs) const noexcept;

private:
    virtual void* do_allocate(std::size_t size, std::size_t alignment) = 0;
    virtual void do_deallocate(void* memory, std::size_t size,
                               std::size_t alignment) = 0;
    virtual bool do_is_equal(memory_resource const& rhs) const noexcept {
        return this == &rhs;
    }
};

inline void* memory_resource::allocate(std::size_t size,
                                       std::size_t alignment) {
    return this->do_allocate(size, alignment);
}

inline void memory_resource::deallocate(void* memory, std::size_t size,
                                        std::size_t alignment) {
    this->do_deallocate(memory, size, alignment);
}

inline bool
memory_resource::is_equal(memory_resource const& rhs) const noexcept {
    return this->do_is_equal(rhs);
}

inline bool operator==(memory_resource const& lhs,
                       memory_resource const& rhs) noexcept {
    return &lhs == &rhs || lhs.is_equal(rhs);
}

inline bool operator!=(memory_resource const& lhs,
                       memory_resource const& rhs) noexcept {
    return !(lhs == rhs);
}

/// MARK: - polymorphic_allocator
template <typename T>
class polymorphic_allocator {
public:
    using value_type = T;

public:
    polymorphic_allocator() noexcept: m_resource(get_default_resource()) {}
    polymorphic_allocator(polymorphic_allocator const&) = default;
    template <typename U>
    polymorphic_allocator(polymorphic_allocator<U> const& other) noexcept:
        m_resource(other.resource()) {}
    polymorphic_allocator(memory_resource* resource): m_resource(resource) {}

    polymorphic_allocator& operator=(polymorphic_allocator const&) = delete;

public:
    T* allocate(std::size_t n) {
        return static_cast<T*>(resource()->allocate(n * sizeof(T), alignof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        __utl_expect(p != nullptr, "passing NULL is not allowed");
        resource()->deallocate(p, n * sizeof(T), alignof(T));
    }

    template <typename U, typename... Args>
    requires __alloc_constructible<T, memory_resource*, Args...>
    void construct(U* p, Args&&... args) {
        if constexpr (__alloc_constructible_1<T, memory_resource*, Args...>) {
            std::construct_at(p, std::allocator_arg, resource(),
                              std::forward<Args>(args)...);
        }
        else if constexpr (__alloc_constructible_2<T, memory_resource*,
                                                   Args...>)
        {
            std::construct_at(p, std::forward<Args>(args)..., resource());
        }
        else {
            static_assert(
                __alloc_constructible_3<T, memory_resource*, Args...>);
            std::construct_at(p, std::forward<Args>(args)...);
        }
    }

    void* allocate_bytes(std::size_t size,
                         std::size_t alignment = alignof(std::max_align_t)) {
        return resource()->allocate(size, alignment);
    }

    void deallocate_bytes(void* p, std::size_t size,
                          std::size_t alignment = alignof(std::max_align_t)) {
        resource()->deallocate(p, size, alignment);
    }

    polymorphic_allocator select_on_container_copy_construction() const {
        return polymorphic_allocator{};
    }

    memory_resource* resource() const noexcept { return m_resource; }

private:
    memory_resource* m_resource;
};

template <typename T, typename U>
bool operator==(polymorphic_allocator<T> const& lhs,
                polymorphic_allocator<U> const& rhs) noexcept {
    return *lhs.resource() == *rhs.resource();
}

template <typename T, typename U>
bool operator!=(polymorphic_allocator<T> const& lhs,
                polymorphic_allocator<U> const& rhs) noexcept {
    return !(lhs == rhs);
}

/// MARK: - polymorphic_deleter
template <typename T>
struct polymorphic_deleter {
    template <typename>
    friend struct polymorphic_deleter;

    static_assert(
        !std::is_function<T>::value,
        "polymorphic_deleter cannot be instantiated for function types");

    constexpr polymorphic_deleter() noexcept:
        _resource(get_default_resource()) {}

    constexpr polymorphic_deleter(memory_resource* resource):
        _resource(resource) {}

    template <typename U>
    requires std::convertible_to<U*, T*>
    polymorphic_deleter(polymorphic_deleter<U> const& rhs) noexcept:
        _resource(rhs._resource) {}

    void operator()(T* ptr) const noexcept {
        static_assert(sizeof(T) > 0,
                      "polymorphic_delete cannot deallocate incomplete type");
        std::destroy_at(ptr);
        _resource->deallocate(ptr, sizeof(T), alignof(T));
    }

private:
    memory_resource* _resource;
};

/// MARK: polymorphic_new
template <typename T, typename... Args>
requires(std::is_constructible_v<T, Args...>)
T* polymorphic_new(memory_resource* resource, Args&&... args) {
    void* result = resource->allocate(sizeof(T), alignof(T));
    return std::construct_at(static_cast<T*>(result), UTL_FORWARD(args)...);
}

/// MARK: polymorphic_delete
template <typename T>
void polymorphic_delete(memory_resource* resource, T* address) {
    std::destroy_at(address);
    resource->deallocate(address, sizeof(T), alignof(T));
}

/// MARK: make_unique
template <typename T, typename... Args>
requires __alloc_constructible<T, memory_resource*, Args...>
std::unique_ptr<T, polymorphic_deleter<T>>
make_unique(memory_resource* resource, Args&&... args) {
    if constexpr (__alloc_constructible_1<T, memory_resource*, Args...>) {
        return std::unique_ptr<
            T, polymorphic_deleter<T>>(polymorphic_new<T>(resource,
                                                          std::allocator_arg,
                                                          resource,
                                                          std::forward<Args>(
                                                              args)...),
                                       resource);
    }
    else if constexpr (__alloc_constructible_2<T, memory_resource*, Args...>) {
        return std::unique_ptr<
            T, polymorphic_deleter<T>>(polymorphic_new<T>(resource,
                                                          std::forward<Args>(
                                                              args)...,
                                                          resource),
                                       resource);
    }
    else {
        static_assert(__alloc_constructible_3<T, memory_resource*, Args...>);
        return std::unique_ptr<
            T, polymorphic_deleter<T>>(polymorphic_new<T>(resource,
                                                          std::forward<Args>(
                                                              args)...),
                                       resource);
    }
}

/// MARK: - new_delete_resource
class __utl_new_delete_resource: public memory_resource {
    void* do_allocate(std::size_t size, std::size_t alignment) final {
        return ::operator new(size, static_cast<std::align_val_t>(alignment));
    }

    void do_deallocate(void* memory, std::size_t size,
                       std::size_t alignment) final {
        ::operator delete(memory, size,
                          static_cast<std::align_val_t>(alignment));
    }

    bool do_is_equal(memory_resource const& rhs) const noexcept final {
        return this == &rhs;
    }
};

__utl_new_delete_resource* __utl_get_new_delete_resource() noexcept;

inline memory_resource* new_delete_resource() noexcept {
    return __utl_get_new_delete_resource();
}

/// MARK: - null_memory_resource
class __utl_null_memory_resource: public memory_resource {
    void* do_allocate(std::size_t size, std::size_t alignment) final {
        throw std::bad_alloc{};
    }

    void do_deallocate(void* memory, std::size_t size,
                       std::size_t alignment) final {
        __utl_debugbreak("must not be called since this resource never handed "
                         "out any memory");
    }

    bool do_is_equal(memory_resource const& rhs) const noexcept final {
        return this == &rhs;
    }
};
__utl_null_memory_resource* __utl_get_null_memory_resource() noexcept;

inline memory_resource* null_memory_resource() noexcept {
    return __utl_get_null_memory_resource();
}

// MARK: - get_default_resource
memory_resource*& __utl_get_default_resource() noexcept;

inline memory_resource* get_default_resource() {
    return __utl_get_default_resource();
}

inline void set_default_resource(memory_resource* r) {
    __utl_get_default_resource() = r;
}

} // namespace utl::pmr
