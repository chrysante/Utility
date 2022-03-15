#pragma once

#include <utl/memory_resource.hpp>
#include <utl/hashset.hpp>

namespace utl_test {
	struct Allocation {
		void* address;
		std::size_t size;
		std::size_t alignment;
		bool operator==(Allocation const&) const = default;
	};
}

template<>
struct std::hash<utl_test::Allocation> {
	std::size_t operator()(utl_test::Allocation const& a) const {
		return std::hash<void*>{}(a.address);
	}
};

namespace utl_test {
	
	class DebugMemoryResource: public utl::pmr::memory_resource {
	public:
		DebugMemoryResource(utl::pmr::memory_resource* upstream = utl::pmr::get_default_resource()):
			_upstream(upstream)
		{}
		
		utl::hashset<Allocation>& allocations() { return _allocations; }
		
	private:
		void* do_allocate(std::size_t size, std::size_t alignment) override {
			auto result = _upstream->allocate(size, alignment);
			_allocations.insert({ result, size, alignment });
			return result;
		}
		
		void do_deallocate(void* p, std::size_t size, std::size_t alignment) noexcept override {
			if (!_allocations.contains({ p, size, alignment })) {
				std::terminate();
			}
			_allocations.erase({ p, size, alignment });
			_upstream->deallocate(p, size, alignment);
		}
		
		
		
	private:
		utl::pmr::memory_resource* _upstream;
		utl::hashset<Allocation> _allocations;
	};
	
}


