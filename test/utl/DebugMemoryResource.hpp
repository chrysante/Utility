#pragma once

#include <utl/hashmap.hpp>
#include <utl/hashset.hpp>
#include <utl/memory_resource.hpp>

namespace utl_test {
struct Allocation {
    void* address;
    std::size_t size;
    std::size_t alignment;
    bool operator==(Allocation const&) const = default;
};
} // namespace utl_test

template <>
struct std::hash<utl_test::Allocation> {
    std::size_t operator()(utl_test::Allocation const& a) const {
        return std::hash<void*>{}(a.address);
    }
};

namespace utl_test {

class FuzzyAlignmentResource: public utl::pmr::memory_resource {
public:
    FuzzyAlignmentResource(
        utl::pmr::memory_resource* upstream = utl::pmr::get_default_resource()):
        _upstream(upstream) {}

private:
    void* do_allocate(std::size_t size, std::size_t alignment) override {
        __utl_assert(std::popcount(alignment) == 1);
        std::byte* const allocation =
            (std::byte*)_upstream->allocate(size * 2, alignment);
        std::byte* result = allocation;
        std::size_t const next_alignment = alignment * 2;
        while ((std::uintptr_t)result % next_alignment == 0) {
            result += alignment;
        }
        __utl_assert(result - allocation <= size);
        _allocations.insert({ result, allocation });
        return result;
    }

    void do_deallocate(void* p, std::size_t size,
                       std::size_t alignment) noexcept override {
        if (!_allocations.contains(p)) {
            std::terminate();
        }
        void* const actualAllocation = _allocations.at(p);
        _upstream->deallocate(actualAllocation, size * 2, alignment);

        _allocations.erase(p);
    }

private:
    utl::pmr::memory_resource* _upstream;
    utl::hashmap<void*, void*>
        _allocations; // maps results to actual internal allocations
};

class DebugMemoryResource: public utl::pmr::memory_resource {
public:
    DebugMemoryResource(
        utl::pmr::memory_resource* upstream = utl::pmr::get_default_resource()):
        _upstream(upstream) {}

    utl::hashset<Allocation> allocations;

private:
    void* do_allocate(std::size_t size, std::size_t alignment) override {
        auto result = _upstream->allocate(size, alignment);
        allocations.insert({ result, size, alignment });
        return result;
    }

    void do_deallocate(void* p, std::size_t size,
                       std::size_t alignment) noexcept override {
        if (!allocations.contains({ p, size, alignment })) {
            std::terminate();
        }
        allocations.erase({ p, size, alignment });
        _upstream->deallocate(p, size, alignment);
    }

private:
    utl::pmr::memory_resource* _upstream;
};

} // namespace utl_test
