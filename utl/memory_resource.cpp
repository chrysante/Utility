#include "memory_resource.hpp"

#include "stdio.hpp"

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
		auto const result = upstream()->allocate(size, align);
		utl::print("allocate(size: {}, align: {}) -> {}\n", size, align, result);
		return result;
	}

	void monitor_resource::do_deallocate(void* ptr, std::size_t size, std::size_t align) {
		utl::print("deallocate(ptr: {}, size: {}, align: {})\n", ptr, size, align);
		upstream()->deallocate(ptr, size, align);
	}

}
