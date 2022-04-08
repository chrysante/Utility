#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__memory_resource_base.hpp"
#include "__debug.hpp"
#include "common.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#include <cstddef>
#include <new>
#include <memory>
#include <exception>
#include <algorithm>

namespace utl::pmr {

	/// MARK: - monotonic_buffer_resource
	class monotonic_buffer_resource: public memory_resource {
	public:
		/// MARK: Constructors
		/*
		 1-2) Sets the current buffer to null and the next buffer size to an implementation-defined size.
		 3-4) Sets the current buffer to null and the next buffer size to a size no smaller than initial_size.
		 5-6) Sets the current buffer to buffer and the next buffer size to buffer_size (but not less than 1). Then increase the next buffer size by an implementation-defined growth factor (which does not have to be integral).
		 7) Copy constructor is deleted.
		 */
		// (1)
		monotonic_buffer_resource():
			monotonic_buffer_resource(get_default_resource())
		{
			
		}
		// (2)
		explicit monotonic_buffer_resource(memory_resource* upstream):
			_upstream(upstream)
		{
			
		}
		// (3)
		explicit monotonic_buffer_resource(std::size_t initial_size):
			monotonic_buffer_resource(initial_size, get_default_resource())
		{
			
		}
		// (4)
		monotonic_buffer_resource(std::size_t initial_size,
								  memory_resource* upstream):
			_upstream(upstream),
			_local_buffer(nullptr, nullptr, initial_size / __growth_factor, nullptr),
			_head_buffer(&_local_buffer)
		{
			
		}
		// (5)
		monotonic_buffer_resource(void* buffer, std::size_t buffer_size):
			monotonic_buffer_resource(buffer, buffer_size, get_default_resource())
		{
			
		}
		// (6)
		monotonic_buffer_resource(void* buffer, std::size_t buffer_size,
								  memory_resource* upstream):
			_upstream(upstream),
			_local_buffer(buffer, buffer, buffer_size, nullptr),
			_head_buffer(&_local_buffer)
		{
			
		}
		// (7)
		monotonic_buffer_resource(monotonic_buffer_resource const&) = delete;

		/// MARK: Destructor
		~monotonic_buffer_resource() {
			release();
		}
		
		/// MARK: Release
		/*
		 Releases all allocated memory by calling the deallocate function on the upstream memory resource as necessary.
		 Resets current buffer and next buffer size to their initial values at construction.

		 Memory is released back to the upstream resource even if deallocate has not been called for some of the allocated blocks.
		 */
		void release() noexcept {
			__release_impl();
			_local_buffer = { nullptr };
			_head_buffer = &_local_buffer;
		}
		void __release_impl() noexcept {
			__BufferNodeHeader* head = _head_buffer;
			if (!head) {
				return;
			}
			while (true) {
				__BufferNodeHeader* const child = head->prev();
				if (!child) {
					/* not having a child indicates that this buffer is the local buffer and therefore we've hit the end of our list */
					return;
				}
				_upstream->deallocate(head->begin(), head->total_size(), __chunk_align);
				head = child;
			}
		}
		
		/// MARK: Upstream Resource
		memory_resource* upstream_resource() const {
			return _upstream;
		}
	private:
		/// MARK: DoAllocate
		/*
		 Allocates storage.

		 If the current buffer has sufficient unused space to fit a block with the specified size and alignment, allocates the return block from the current buffer.

		 Otherwise, this function allocates a new buffer by calling upstream_resource()->allocate(n, m), where n is not less than the greater of bytes and the next buffer size and m is not less than alignment. It sets the new buffer as the current buffer, increases the next buffer size by an implementation-defined growth factor (which is not necessarily integral), and then allocates the return block from the newly allocated buffer.
		 */
		void* do_allocate(std::size_t size, std::size_t alignment) override {
			__utl_assert_audit(_head_buffer != nullptr,
							   "_head_buffer must always be valid. If"
							   "we have not allocated yet it should point"
							   "to _local_buffer which in turn is empty. ");
			
			if (std::byte* const result = _head_buffer->allocate(size, alignment)) {
				return result;
			}
			/* allocate a new chunk if head buffer doesn't have enough space */
			__allocate_new_chunk(size, alignment);
			
			std::byte* const result = _head_buffer->allocate(size, alignment);
			__utl_assert(result != nullptr);
			return result;
		}

		/// MARK: DoDeallocate
		/*
		 no-op
		 */
		void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {

		}
		
		/// MARK: DoIsEqual
		/*
		 Compare *this with other for identity - memory allocated using a monotonic_buffer_resource can only be deallocated using that same resource.
		 */
		bool do_is_equal(memory_resource const& rhs) const noexcept override {
			this == &rhs;
		}

	public:
		
		/// MARK: Internals
		static constexpr std::size_t __min_chunk_size = 128;
		static constexpr std::size_t __chunk_align = 32; /* something to satisfy most to all requirements */
		static constexpr std::size_t __growth_factor = 2;
		
		void __allocate_new_chunk(std::size_t size_requirement, std::size_t alignment_requirement) {
			alignment_requirement = std::max(alignment_requirement, __chunk_align);
			
			__utl_log("available size: {}", _head_buffer->available_size());
			std::size_t new_chunk_size = __calculate_next_buffer_size(_head_buffer->available_size(),
																	  size_requirement, alignment_requirement);
			/* alignment_requirement >= __chunk_align == sizeof(__BufferNodeHeader) */
			/* This asserts that we have enough space to placement new the Header   */
			/* in the buffer and still allocate required size/alignment.            */
			new_chunk_size += alignment_requirement;
			__utl_log("allocating new chunk of size {}", new_chunk_size);
			
			std::byte* const new_chunk = (std::byte*)upstream_resource()->allocate(new_chunk_size,
																				   /* We still have to use __chunk_align here, because we don't    */
																				   /* store the alignment so we also deallocate with __chunk_align */
																				   /* and the alignment parameter has to match the allocation.     */
																				   /* There is still enough space in the buffer to satisfy the     */
																				   /* alignment requirement.                                       */
																				   __chunk_align);
			_head_buffer = ::new ((void*)new_chunk) __BufferNodeHeader(new_chunk,                              /* buffer begin */
																		   new_chunk + sizeof(__BufferNodeHeader), /* buffer current */
																		   new_chunk_size,                         /* total size */
																		   _head_buffer);
		}
		
		static std::size_t __calculate_next_buffer_size(std::size_t last_buffer_size, std::size_t size_requirement, std::size_t alignment_requirement) {
			std::size_t const target_size = std::max(last_buffer_size * __growth_factor, size_requirement);
			return round_up(target_size, alignment_requirement);
		}
		
		static std::byte* __align_ptr(std::byte* ptr, std::size_t align) {
			std::size_t const remainder = (std::uintptr_t)ptr % align;
			if (remainder == 0) {
				return ptr;
			}
			else {
				return ptr + (align - remainder);
			}
		}
		
		struct __BufferNodeHeader {
			__BufferNodeHeader(std::nullptr_t) {}
			__BufferNodeHeader(void* begin_, void* current_, std::size_t size_, __BufferNodeHeader* prev_):
				_prev(prev_),
				_begin((std::byte*)begin_),
				_current((std::byte*)current_),
				_end((std::byte*)begin_ + size_)
			{
				__utl_expect(_current <= _end);
			}

			std::size_t total_size() const {
				std::ptrdiff_t result = end() - begin();
				__utl_assert_audit(result >= 0);
				return result;
			}
			
			std::size_t available_size() const {
				return total_size() - ((void*)this == (void*)begin()) * sizeof(*this);
			}

			std::ptrdiff_t free_space() const {
				return end() - current();
			}
			
			/*
			 Advances _current so it is aligned to 'alignment'.
			 If this buffer then has space for 'size' returns _current,
			 else resets _current and returns nullptr
			 */
			std::byte* allocate(std::size_t size, std::size_t alignment) {
				if (begin() == nullptr) {
					return nullptr;
				}
				std::byte* const old_current = _current;
				_current = __align_ptr(_current, alignment);
				if (free_space() < size) {
					_current = old_current;
					return nullptr;
				}
				std::byte* const result = _current;
				_current += size;
				return result;
			}

			__BufferNodeHeader*       prev()          { return const_cast<__BufferNodeHeader*>(as_const(*this).prev()); }
			__BufferNodeHeader const* prev()    const { return _prev; }
			std::byte*                begin()         { return const_cast<std::byte*>(as_const(*this).begin()); }
			std::byte const*          begin()   const { return _begin; }
			std::byte*                current()       { return const_cast<std::byte*>(as_const(*this).current()); }
			std::byte const*          current() const { return _current; }
			std::byte const*          end()     const { return _end; }
			
		private:
			__BufferNodeHeader* _prev    = nullptr;
			std::byte*          _begin   = nullptr;
			std::byte*          _current = nullptr;
			std::byte const*    _end     = nullptr;
		};
		
	private:
		memory_resource*    _upstream     = nullptr;
		__BufferNodeHeader  _local_buffer = nullptr;
		__BufferNodeHeader* _head_buffer  = &_local_buffer;
	};
	
	static_assert(sizeof(monotonic_buffer_resource::__BufferNodeHeader) == monotonic_buffer_resource::__chunk_align);
	
	/// MARK: - pool_options
	struct pool_options {
		std::size_t max_blocks_per_chunk;
		std::size_t largest_required_pool_block;
	};
	
	/// MARK: - unsynchronized_pool_resource
	class unsynchronized_pool_resource: public memory_resource {
	public:
		/// MARK: Constructors
		unsynchronized_pool_resource(): unsynchronized_pool_resource(get_default_resource()) {}
		
		explicit unsynchronized_pool_resource(memory_resource* upstream):
			unsynchronized_pool_resource(pool_options{}, upstream)
		{}
		
		explicit unsynchronized_pool_resource(pool_options const& options):
			unsynchronized_pool_resource(options, get_default_resource())
		{}
		
		unsynchronized_pool_resource(pool_options const& options,
									 memory_resource* upstream):
			_upstream(upstream), _options(__sanitize_options(options))
		{
			
		}
		
		unsynchronized_pool_resource(unsynchronized_pool_resource const&) = delete;
		
		/// MARK: Destructor
		~unsynchronized_pool_resource() {
			
		}
		
		
		
		/// MARK: UpstreamResource
		memory_resource* upstream_resource() const {
			return _upstream;
		}
		
		/// MARK: Options
		pool_options options() const {
			return _options;
		}
		
		static pool_options __sanitize_options(pool_options const& options) {
			return options;
		}
		
	private:
		memory_resource* _upstream;
		pool_options _options;
	};
	
	
	/// MARK: - monitor_resource
	class monitor_resource: public memory_resource {
	public:
		monitor_resource(): monitor_resource(get_default_resource()) {}
		explicit monitor_resource(memory_resource* upstream): _upstream(upstream) {}
		
		memory_resource* upstream() { return _upstream; }
		memory_resource const* upstream() const { return _upstream; }
		
	private:
		void* do_allocate(std::size_t size, std::size_t alignment) override;
		
		void do_deallocate(void* ptr, std::size_t size, std::size_t alignment) override;
		
		bool do_is_equal(memory_resource const& rhs) const noexcept override { return upstream()->is_equal(rhs); }
		
		
	private:
		memory_resource* _upstream;
	};
	
}
