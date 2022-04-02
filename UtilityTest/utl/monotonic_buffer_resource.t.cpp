//#define UTL_LOG

#include "Catch2.hpp"
#include "utl/memory_resource.hpp"
#include "DebugMemoryResource.hpp"

TEST_CASE("monotonic_buffer_resource [repeated allocations]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);

	SECTION("_") {
		utl::pmr::monotonic_buffer_resource buffer(80, &debugResource);
		int const count = 10 + 20 + 40 + 80;
		for (int i = 0; i < count; ++i) {
			buffer.allocate(8, 8);
		}
		CHECK(debugResource.allocations.size() == 4);
		buffer.release();
		CHECK(debugResource.allocations.empty());
	}
	
	SECTION("geometric series base two") {
		utl::pmr::monotonic_buffer_resource buffer(&debugResource);
		int const count = 4 + 8 + 16 + 32; /* 4 terms of geometric series base two */
		for (int i = 0; i < count; ++i) {
			buffer.allocate(8, 8);
		}
		CHECK(debugResource.allocations.size() == 4);
		buffer.release();
		CHECK(debugResource.allocations.empty());
	}
}

TEST_CASE("monotonic_buffer_resource [constructor 2]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);
	
	utl::pmr::monotonic_buffer_resource buffer(&debugResource);
	
	void* ptr = buffer.allocate(8, 8);
	CHECK((std::uintptr_t)ptr % 8 == 0);
	void* ptr2 = buffer.allocate(8, 8);
	CHECK((std::uintptr_t)ptr2 % 8 == 0);
	
	CHECK(debugResource.allocations.size() == 1);
	
	buffer.release();
	CHECK(debugResource.allocations.empty());
}

TEST_CASE("monotonic_buffer_resource [constructor 2, no-op]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);
	
	utl::pmr::monotonic_buffer_resource buffer(&debugResource);
	
	CHECK(debugResource.allocations.empty());
	buffer.release();
	CHECK(debugResource.allocations.empty());
}

TEST_CASE("monotonic_buffer_resource [constructor 4]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);
	
	utl::pmr::monotonic_buffer_resource buffer(256, &debugResource);
	
	void* ptr = buffer.allocate(256, 8);
	CHECK((std::uintptr_t)ptr % 8 == 0);
	void* ptr2 = buffer.allocate(128, 8);
	CHECK((std::uintptr_t)ptr2 % 8 == 0);
	
	CHECK(debugResource.allocations.size() == 2);
	
	buffer.release();
	CHECK(debugResource.allocations.empty());
}

TEST_CASE("monotonic_buffer_resource [constructor 6]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);
	
	char localBuffer[256];
	utl::pmr::monotonic_buffer_resource buffer(localBuffer, 256, &debugResource);
	
	void* ptr = buffer.allocate(256, 8);
	CHECK((std::uintptr_t)ptr % 8 == 0);
	CHECK(debugResource.allocations.size() == 0);
	void* ptr2 = buffer.allocate(128, 8);
	CHECK((std::uintptr_t)ptr2 % 8 == 0);
	
	CHECK(debugResource.allocations.size() == 1);
	
	buffer.release();
	CHECK(debugResource.allocations.empty());
}

TEST_CASE("monotonic_buffer_resource [overaligned allocations]") {
	utl_test::FuzzyAlignmentResource fuzzyResource;
	utl_test::DebugMemoryResource debugResource(&fuzzyResource);
	
	utl::pmr::monotonic_buffer_resource buffer(&debugResource);
	{
		void* const ptr = buffer.allocate(128, 128);
		CHECK((std::uintptr_t)ptr % 128 == 0);
		CHECK(debugResource.allocations.size() == 1);
	}  {
		void* const ptr = buffer.allocate(256, 128);
		CHECK((std::uintptr_t)ptr % 128 == 0);

		CHECK(debugResource.allocations.size() == 2);
	}
	
	
	buffer.release();
	CHECK(debugResource.allocations.empty());
}

