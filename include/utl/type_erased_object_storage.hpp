#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <type_traits>
#include <typeinfo>
#include <utility>

#include <utl/ipp.hpp>

namespace utl {

/// Type-erased object storage
/// Stores an object without exposing its concrete type.
///
/// Uses small-buffer optimization for sufficiently small, suitably aligned,
/// nothrow-movable types. Larger or potentially throwing-movable types are
/// allocated on the heap.
///
/// The stored object can be accessed through a `void` pointer returned by
/// `data()`. The pointer remains valid until the object is moved, replaced,
/// or destroyed.
///
/// The storage is move-only and does not support copying.
class type_erased_object_storage {
private:
    static constexpr size_t sbo_size = 3 * sizeof(void*);
    static constexpr size_t sbo_alignment = alignof(std::max_align_t);

    enum class storage_kind : unsigned {
        empty = 0,
        inline_storage = 1,
        heap = 2,
    };

    struct vtable {
        void (*destroy_inline)(void*) noexcept;
        void (*destroy_heap)(void*) noexcept;
        void (*move_inline)(void*, void*) noexcept;
        std::type_info const& (*type)() noexcept;
    };

    union storage {
        alignas(sbo_alignment) char m_inline[sbo_size];
        void* m_heap;
    };

    template <typename T>
    static constexpr bool can_use_sbo =
        sizeof(T) <= sbo_size && alignof(T) <= sbo_alignment &&
        std::is_nothrow_move_constructible_v<T>;

    template <typename T>
    static vtable const* get_vtable() noexcept {
        // clang-format off
        static vtable const table{
            .destroy_inline = [](void* ptr) noexcept {
                static_cast<T*>(ptr)->~T();
            },
            .destroy_heap = [](void* ptr) noexcept {
                delete static_cast<T*>(ptr);
            },
            .move_inline = [](void* destination, void* source) noexcept {
                new (destination) T(std::move(*static_cast<T*>(source)));
                static_cast<T*>(source)->~T();
            },
            .type = []() noexcept -> std::type_info const& {
                return typeid(T);
            },
        };
        // clang-format on
        return &table;
    }

    using vtable_ptr = ipp<vtable const*, storage_kind, 2>;

public:
    type_erased_object_storage() noexcept = default;

    type_erased_object_storage(type_erased_object_storage const&) = delete;

    type_erased_object_storage&
    operator=(type_erased_object_storage const&) = delete;

    type_erased_object_storage(type_erased_object_storage&& other) noexcept {
        move_from(std::move(other));
    }

    type_erased_object_storage&
    operator=(type_erased_object_storage&& other) noexcept {
        if (this != &other) {
            reset();
            move_from(std::move(other));
        }
        return *this;
    }

    ~type_erased_object_storage() { reset(); }

    template <typename T, typename... Args>
    explicit type_erased_object_storage(std::in_place_type_t<T>,
                                        Args&&... args) {
        emplace<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    explicit type_erased_object_storage(T&& value) {
        emplace<std::decay_t<T>>(std::forward<T>(value));
    }

    template <typename T, typename... Args>
    T& emplace(Args&&... args) {
        static_assert(std::is_object_v<T>, "T must be an object type");
        static_assert(std::is_destructible_v<T>, "T must be destructible");
        reset();
        if constexpr (can_use_sbo<T>) {
            new (static_cast<void*>(&m_storage.m_inline))
                T(std::forward<Args>(args)...);
            m_vtable = {
                get_vtable<T>(),
                storage_kind::inline_storage,
            };
            return *static_cast<T*>(data());
        }
        else {
            T* object = new T(std::forward<Args>(args)...);
            m_storage.m_heap = object;
            m_vtable = {
                get_vtable<T>(),
                storage_kind::heap,
            };
            return *object;
        }
    }

    void reset() noexcept {
        switch (kind()) {
        case storage_kind::empty: break;
        case storage_kind::inline_storage:
            m_vtable.pointer()->destroy_inline(
                static_cast<void*>(&m_storage.m_inline));
            break;
        case storage_kind::heap:
            m_vtable.pointer()->destroy_heap(m_storage.m_heap);
            break;
        }
        m_vtable = {};
    }

    [[nodiscard]]
    bool has_value() const noexcept {
        return kind() != storage_kind::empty;
    }

    [[nodiscard]]
    explicit operator bool() const noexcept {
        return has_value();
    }

    [[nodiscard]]
    void* data() noexcept {
        return const_cast<void*>(std::as_const(*this).data());
    }

    [[nodiscard]]
    void const* data() const noexcept {
        switch (kind()) {
        case storage_kind::empty: return nullptr;
        case storage_kind::inline_storage:
            return static_cast<void const*>(&m_storage.m_inline);
        case storage_kind::heap: return m_storage.m_heap;
        }
    }

    [[nodiscard]]
    std::type_info const& type() const noexcept {
        if (!has_value())
            return typeid(void);
        return m_vtable.pointer()->type();
    }

private:
    [[nodiscard]]
    storage_kind kind() const noexcept {
        return m_vtable.integer();
    }

    void move_from(type_erased_object_storage&& other) noexcept {
        m_vtable = other.m_vtable;
        switch (other.kind()) {
        case storage_kind::empty: break;
        case storage_kind::inline_storage:
            m_vtable.pointer()
                ->move_inline(static_cast<void*>(&m_storage.m_inline),
                              static_cast<void*>(&other.m_storage.m_inline));
            break;
        case storage_kind::heap:
            m_storage.m_heap = other.m_storage.m_heap;
            other.m_storage.m_heap = nullptr;
            break;
        }
        other.m_vtable = {};
    }

    storage m_storage;
    vtable_ptr m_vtable;
};

} // namespace utl
