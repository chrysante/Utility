#include "utl/memory_resource.hpp"
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

namespace {

class TrackingResource: public utl::pmr::memory_resource {
public:
    TrackingResource(): TrackingResource(utl::pmr::get_default_resource()) {}
    TrackingResource(utl::pmr::memory_resource* upstream):
        _upstream(upstream) {}
    utl::pmr::memory_resource* upstream() const { return _upstream; }

private:
    struct Allocation {
        std::size_t size;
        std::size_t align;
    };
    std::unordered_map<void*, Allocation> _allocations;

public:
    auto const& allocations() const { return _allocations; }

private:
    void* do_allocate(std::size_t size, std::size_t align) override {
        auto const result = upstream()->allocate(size, align);
        _allocations.insert({ result, { size, align } });
        return result;
    }
    void do_deallocate(void* p, std::size_t size, std::size_t align) override {
        auto const itr = _allocations.find(p);
        __utl_assert(itr != _allocations.end());
        _allocations.erase(itr);
        return upstream()->deallocate(p, size, align);
    }
    bool do_is_equal(memory_resource const& rhs) const noexcept override {
        return false; // for now
    }

private:
    utl::pmr::memory_resource* _upstream;
};

} // namespace

TEST_CASE("monotonic_buffer_resource") {

    //	using namespace utl::pmr;
    //
    //	TrackingResource tracker;
    //
    //	monotonic_buffer_resource buffer(&tracker);
    //
    //	auto p = buffer.allocate(128, 8);
    //	CHECK(utl::is_aligned(p, 8));
    //
    //	CHECK(tracker.allocations().size() == 1);
    //	auto const allocItr = tracker.allocations().find(p);
    //	REQUIRE(allocItr != tracker.allocations().end());
    //	CHECK(allocItr->second.size >= 128);
    //
    //
    //
    //	buffer.deallocate(p, 128, 8);
    //
    //	CHECK(tracker.allocations().size() == 1);
}
