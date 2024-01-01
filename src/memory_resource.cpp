#include <utl/memory_resource.hpp>

#include <iostream>

namespace utl::pmr {

__utl_new_delete_resource* __utl_get_new_delete_resource() noexcept {
    static __utl_new_delete_resource resource;
    return &resource;
}

__utl_null_memory_resource* __utl_get_null_memory_resource() noexcept {
    static __utl_null_memory_resource resource;
    return &resource;
}

memory_resource*& __utl_get_default_resource() noexcept {
    static memory_resource* default_resource = utl::pmr::new_delete_resource();
    return default_resource;
}

void* monitor_resource::do_allocate(std::size_t size, std::size_t align) {
    void* const result = upstream()->allocate(size, align);
    std::cout << "allocate: [upstream: " 
              << upstream() << ", size: " 
              << size << ", align: " << align << "] -> "
              << result << "\n";
    return result;
}

void monitor_resource::do_deallocate(void* ptr, std::size_t size, std::size_t align) {
    std::cout << "deallocate: [upstream: " << upstream() 
              << ", ptr: " << ptr << ", size: " << size 
              << ", align: " << align << "]\n";
    upstream()->deallocate(ptr, size, align);
}

} // namespace utl::pmr