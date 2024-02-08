#include <utl/memory_resource.hpp>

#include <iostream>

using namespace utl;
using namespace pmr;

memory_resource* utl::pmr::new_delete_resource() noexcept {
    class __utl_new_delete_resource: public memory_resource {
        void* do_allocate(std::size_t size, std::size_t alignment) final {
            return ::operator new(size,
                                  static_cast<std::align_val_t>(alignment));
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
    static __utl_new_delete_resource resource;
    return &resource;
}

memory_resource* utl::pmr::null_memory_resource() noexcept {
    class __utl_null_memory_resource: public memory_resource {
        void* do_allocate(std::size_t size, std::size_t alignment) final {
            throw std::bad_alloc{};
        }

        void do_deallocate(void* memory, std::size_t size,
                           std::size_t alignment) final {
            __utl_debugbreak(
                "must not be called since this resource never handed "
                "out any memory");
        }

        bool do_is_equal(memory_resource const& rhs) const noexcept final {
            return this == &rhs;
        }
    };

    static __utl_null_memory_resource resource;
    return &resource;
}

static auto& def_resource() {
    static memory_resource* r = utl::pmr::new_delete_resource();
    return r;
}

memory_resource* utl::pmr::get_default_resource() {
    return def_resource();
}

void utl::pmr::set_default_resource(memory_resource* resource) {
    def_resource() = resource;
}

void* monitor_resource::do_allocate(std::size_t size, std::size_t align) {
    void* const result = upstream()->allocate(size, align);
    std::cout << "allocate: [upstream: " << upstream() << ", size: " << size
              << ", align: " << align << "] -> " << result << "\n";
    return result;
}

void monitor_resource::do_deallocate(void* ptr, std::size_t size,
                                     std::size_t align) {
    std::cout << "deallocate: [upstream: " << upstream() << ", ptr: " << ptr
              << ", size: " << size << ", align: " << align << "]\n";
    upstream()->deallocate(ptr, size, align);
}
