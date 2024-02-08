#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "__memory_resource_base.hpp"
#include "common.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <memory>
#include <new>

namespace utl::pmr {

class monotonic_buffer_resource: public memory_resource {
public:
    /// \fn `monotonic_buffer_resource`
    /// 1-2) Sets the current buffer to null and the next buffer size to an
    /// implementation-defined size. 3-4) Sets the current buffer to null and
    /// the next buffer size to a size no smaller than `initial_size`. 5-6) Sets
    /// the current buffer to `buffer` and the next buffer size to `buffer_size`
    /// (but not less than 1). Then increase the next buffer size by an
    /// implementation-defined growth factor (which does not have to be
    /// integral). 7) Copy constructor is deleted.
    ///
    // (1)
    monotonic_buffer_resource():
        monotonic_buffer_resource(get_default_resource()) {}
    // (2)
    explicit monotonic_buffer_resource(memory_resource* upstream):
        __upstream(upstream) {}
    // (3)
    explicit monotonic_buffer_resource(std::size_t initial_size):
        monotonic_buffer_resource(initial_size, get_default_resource()) {}
    // (4)
    monotonic_buffer_resource(std::size_t initial_size,
                              memory_resource* upstream):
        __upstream(upstream),
        __local_buffer(nullptr, nullptr, initial_size / __growth_factor,
                       nullptr),
        __head_buffer(&__local_buffer) {}
    // (5)
    monotonic_buffer_resource(void* buffer, std::size_t buffer_size):
        monotonic_buffer_resource(buffer, buffer_size, get_default_resource()) {
    }
    // (6)
    monotonic_buffer_resource(void* buffer, std::size_t buffer_size,
                              memory_resource* upstream):
        __upstream(upstream),
        __local_buffer(buffer, buffer, buffer_size, nullptr),
        __head_buffer(&__local_buffer) {}
    // (7)
    monotonic_buffer_resource(monotonic_buffer_resource const&) = delete;

    ~monotonic_buffer_resource() { release(); }

    /// \brief
    ///  Releases all allocated memory by calling the deallocate function on the
    ///  upstream memory resource as necessary. Resets current buffer and next
    ///  buffer size to their initial values at construction. Memory is released
    ///  back to the upstream resource even if deallocate has not been called
    ///  for some of the allocated blocks.
    void release() noexcept {
        __release_impl();
        __local_buffer = { nullptr };
        __head_buffer = &__local_buffer;
    }

    void __release_impl() noexcept {
        __BufferNodeHeader* head = __head_buffer;
        if (!head) {
            return;
        }
        while (true) {
            __BufferNodeHeader* const child = head->prev();
            if (!child) {
                /// Not having a child indicates that this buffer is the local
                /// buffer and therefore we've hit the end of our list
                return;
            }
            __upstream->deallocate(head->begin(), head->total_size(),
                                   __chunk_align);
            head = child;
        }
    }

    memory_resource* upstream_resource() const { return __upstream; }

    // Internals
    static constexpr std::size_t __min_chunk_size = 128;
    static constexpr std::size_t __chunk_align =
        32; /* something to satisfy most to all requirements */
    static constexpr std::size_t __growth_factor = 2;

    void __allocate_new_chunk(std::size_t size_requirement,
                              std::size_t alignment_requirement) {
        alignment_requirement = std::max(alignment_requirement, __chunk_align);
        std::size_t new_chunk_size =
            __calculate_next_buffer_size(__head_buffer->available_size(),
                                         size_requirement,
                                         alignment_requirement);
        /// `alignment_requirement >= __chunk_align ==
        /// sizeof(__BufferNodeHeader)` This asserts that we have enough space
        /// to construct the Header in the buffer and still allocate required
        /// `size / alignment`.
        new_chunk_size += alignment_requirement;
        std::byte* const new_chunk =
            (std::byte*)upstream_resource()
                ->allocate(new_chunk_size,
                           /// We still have to use `__chunk_align` here,
                           /// because we don't store the alignment so we also
                           /// deallocate with `__chunk_align` and the alignment
                           /// parameter has to match the allocation. There is
                           /// still enough space in the buffer to satisfy the
                           /// alignment requirement.
                           __chunk_align);
        __head_buffer = ::new ((void*)new_chunk)
            __BufferNodeHeader(new_chunk, /// buffer begin
                               new_chunk +
                                   sizeof(
                                       __BufferNodeHeader), /// buffer current
                               new_chunk_size,              /// total size
                               __head_buffer);
    }

    static std::size_t
    __calculate_next_buffer_size(std::size_t last_buffer_size,
                                 std::size_t size_requirement,
                                 std::size_t alignment_requirement) {
        std::size_t const target_size =
            std::max(last_buffer_size * __growth_factor, size_requirement);
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

    static std::uintptr_t __align_address(std::uintptr_t address,
                                          std::size_t align) {
        std::size_t const remainder = address % align;
        if (remainder == 0) {
            return address;
        }
        else {
            return address + (align - remainder);
        }
    }

    struct __BufferNodeHeader {
        __BufferNodeHeader(std::nullptr_t) {}
        __BufferNodeHeader(void* begin, void* current, std::size_t size,
                           __BufferNodeHeader* prev):
            __prev(prev),
            __begin((std::byte*)begin),
            __current((std::byte*)current),
            __end((std::byte*)((std::uintptr_t)__begin + size)) {
            __utl_expect(__current <= __end);
        }

        std::size_t total_size() const {
            std::ptrdiff_t result = end() - begin();
            __utl_assert_audit(result >= 0);
            return result;
        }

        std::size_t available_size() const {
            return total_size() -
                   ((void*)this == (void*)begin()) * sizeof(*this);
        }

        std::ptrdiff_t free_space() const { return end() - current(); }

        /// Advances `__current` so it is aligned to `alignment`
        /// If this buffer then has space for \p size bytes returns `__current`,
        /// else resets `__current` and returns `nullptr`
        std::byte* allocate(std::size_t size, std::size_t alignment) {
            if (begin() == nullptr) {
                return nullptr;
            }
            std::byte* const old_current = __current;
            /// We do this round trip cast to avoid doing pointer arithmetic on
            /// `nullptr`.
            auto const ucurrent = reinterpret_cast<std::uintptr_t>(__current);
            __current = reinterpret_cast<std::byte*>(
                __align_address(ucurrent, alignment));
            if (free_space() < static_cast<std::ptrdiff_t>(size)) {
                __current = old_current;
                return nullptr;
            }
            std::byte* const result = __current;
            __utl_assert(__current != nullptr);
            __current += size;
            return result;
        }

        __BufferNodeHeader* prev() {
            return const_cast<__BufferNodeHeader*>(as_const(*this).prev());
        }
        __BufferNodeHeader const* prev() const { return __prev; }
        std::byte* begin() {
            return const_cast<std::byte*>(as_const(*this).begin());
        }
        std::byte const* begin() const { return __begin; }
        std::byte* current() {
            return const_cast<std::byte*>(as_const(*this).current());
        }
        std::byte const* current() const { return __current; }
        std::byte const* end() const { return __end; }

    private:
        __BufferNodeHeader* __prev = nullptr;
        std::byte* __begin = nullptr;
        std::byte* __current = nullptr;
        std::byte const* __end = nullptr;
    };

private:
    /// Allocates storage.
    /// If the current buffer has sufficient unused space to fit a block with
    /// the specified size and alignment, allocates the return block from the
    /// current buffer. Otherwise, this function allocates a new buffer by
    /// calling `upstream_resource()->allocate(n, m)` where `n` is not less than
    /// the greater of bytes and the next buffer size and `m` is not less than
    /// alignment. It sets the new buffer as the current buffer, increases the
    /// next buffer size by an implementation-defined growth factor (which is
    /// not necessarily integral), and then allocates the return block from the
    /// newly allocated buffer.
    void* do_allocate(std::size_t size, std::size_t alignment) override {
        __utl_assert_audit(__head_buffer != nullptr,
                           "_head_buffer must always be valid. If"
                           "we have not allocated yet it should point"
                           "to _local_buffer which in turn is empty. ");

        if (std::byte* const result = __head_buffer->allocate(size, alignment))
        {
            return result;
        }
        /// Allocate a new chunk if head buffer doesn't have enough space
        __allocate_new_chunk(size, alignment);
        std::byte* const result = __head_buffer->allocate(size, alignment);
        __utl_assert(result != nullptr);
        return result;
    }

    /// no-op
    void do_deallocate(void* p, std::size_t bytes,
                       std::size_t alignment) override {}

    /// Compare `*this` with \p rhs for identity - memory allocated using a
    /// `monotonic_buffer_resource` can only be deallocated using that same
    /// resource.
    bool do_is_equal(memory_resource const& rhs) const noexcept override {
        return this == &rhs;
    }

    memory_resource* __upstream = nullptr;
    __BufferNodeHeader __local_buffer = nullptr;
    __BufferNodeHeader* __head_buffer = &__local_buffer;
};

static_assert(sizeof(monotonic_buffer_resource::__BufferNodeHeader) ==
              monotonic_buffer_resource::__chunk_align);

struct pool_options {
    std::size_t max_blocks_per_chunk;
    std::size_t largest_required_pool_block;
};

class unsynchronized_pool_resource: public memory_resource {
public:
    unsynchronized_pool_resource():
        unsynchronized_pool_resource(get_default_resource()) {}

    explicit unsynchronized_pool_resource(memory_resource* upstream):
        unsynchronized_pool_resource(pool_options{}, upstream) {}

    explicit unsynchronized_pool_resource(pool_options const& options):
        unsynchronized_pool_resource(options, get_default_resource()) {}

    unsynchronized_pool_resource(pool_options const& options,
                                 memory_resource* upstream):
        _upstream(upstream), _options(__sanitize_options(options)) {}

    unsynchronized_pool_resource(unsynchronized_pool_resource const&) = delete;

    ~unsynchronized_pool_resource() {}

    memory_resource* upstream_resource() const { return _upstream; }

    pool_options options() const { return _options; }

    static pool_options __sanitize_options(pool_options const& options) {
        return options;
    }

private:
    memory_resource* _upstream;
    pool_options _options;
};

/// Logs all allocations and deallocations to `std::cout`
class monitor_resource: public memory_resource {
public:
    monitor_resource(): monitor_resource(get_default_resource()) {}
    explicit monitor_resource(memory_resource* upstream): _upstream(upstream) {}

    memory_resource* upstream() { return _upstream; }
    memory_resource const* upstream() const { return _upstream; }

private:
    void* do_allocate(std::size_t size, std::size_t alignment) override;

    void do_deallocate(void* ptr, std::size_t size,
                       std::size_t alignment) override;

    bool do_is_equal(memory_resource const& rhs) const noexcept override {
        return upstream()->is_equal(rhs);
    }

private:
    memory_resource* _upstream;
};

} // namespace utl::pmr
