#pragma once

#ifndef __UTL_MESSENGER_HPP_INCLUDED__
#define __UTL_MESSENGER_HPP_INCLUDED__

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <compare>

#include "functional.hpp"
#include "vector.hpp"
#include "hashmap.hpp"
#include "concepts.hpp"
#include "typeinfo.hpp"

namespace utl {

	class messenger;
	template <typename> struct message;
	
	class __message_registry {
	public:
		static __message_registry& get() { return _inst; }
		void add(std::size_t id, std::string name) {
			if (!_names.contains(id)) {
				auto const [itr, success] = _names.insert({ id, std::move(name) });
				__utl_assert(success);
			}
		}
		
		std::string_view name(std::size_t id) const {
			auto const itr = _names.find(id);
			__utl_assert(itr != _names.end());
			return itr->second;
		}
		
	private:
		static __message_registry _inst;
		
	private:
		utl::hashmap<std::size_t, std::string> _names;
	};
	
	/// MARK: - struct message
	struct __message {
		std::strong_ordering operator<=>(__message const&) const = default;
	
		template <typename>
		friend struct message;
		friend class any_message;
		friend class messenger;
		friend struct std::hash<__message>;
		constexpr __message(std::size_t id): _id(id) {}
		
		std::size_t id() const { return _id; }
		std::string_view name() const { return __message_registry::get().name(_id); }
		
	private:
		std::size_t _id;
	};
	
	static constexpr std::size_t __invalid_message_id = static_cast<std::size_t>(-1);
	extern const __message __invalid_message;
	
	template <typename Message>
	constexpr auto __make_message_id = utl::hash_string(utl::nameof<Message>);
	
	template <typename Message>
	struct message: __message {
		message(): __message(__make_message_id<Message>)
		{
			__message_registry::get().add(id(), std::string(utl::nameof<Message>));
		}
	};
	
	template <typename M>
	concept message_type = std::derived_from<std::decay_t<M>, message<std::decay_t<M>>>;
	
	/// MARK: - any_message
	class any_message {
		static constexpr std::size_t _local_buffer_size = sizeof(void*) * 3;
		static constexpr std::size_t _local_buffer_align = alignof(void*);
		
		struct heap_message {
			__message inv = __invalid_message;
			__message* ptr;
			std::size_t size;
		};
		
		static heap_message make_heap_message(message_type auto&& m) {
			using M = std::decay_t<decltype(m)>;
			heap_message heap{};
			heap.ptr = (__message*)std::malloc(sizeof m);
			heap.size = sizeof m;
			static_assert(sizeof _buffer == sizeof heap);
			::new (heap.ptr) M(UTL_FORWARD(m));
			return heap;
		}
		
		static heap_message copy_heap_message(heap_message heap) {
			heap_message result = heap;
			result.ptr = (__message*)std::malloc(heap.size);
			std::memcpy(result.ptr, heap.ptr, heap.size);
			return result;
		}
		
		static void destroy_heap_message(heap_message heap) {
			std::free(heap.ptr);
		}
		
	public:
		any_message(message_type auto&& m) {
			using M = std::decay_t<decltype(m)>;
			static_assert(std::is_trivially_copyable_v<M>);
			if constexpr (sizeof(m) <= _local_buffer_size && alignof(m) <= _local_buffer_align) {
				::new ((void*)_buffer) M(UTL_FORWARD(m));
			}
			else {
				auto const heap = make_heap_message(UTL_FORWARD(m));
				static_assert(sizeof _buffer == sizeof heap);
				std::memcpy(_buffer, &heap, sizeof _buffer);
			}
		}
	
		any_message(any_message const& rhs) {
			if (rhs._is_local()) {
				std::memcpy(_buffer, rhs._buffer, sizeof _buffer);
			}
			else {
				auto const heap = copy_heap_message(rhs._get_heap());
			}
		}
		
		any_message(any_message&& rhs) noexcept {
			std::memcpy(_buffer, rhs._buffer, sizeof _buffer);
			
			if (!rhs._is_local()) {
				rhs._set_heap(heap_message{});
			}
		}
		
		any_message& operator=(any_message const& rhs) noexcept {
			this->~any_message();
			::new ((void*)this) any_message(rhs);
		}
		
		any_message& operator=(any_message&& rhs) noexcept {
			this->~any_message();
			::new ((void*)this) any_message(std::move(rhs));
		}
		
		~any_message() {
			if (!_is_local()) {
				destroy_heap_message(_get_heap());
			}
		}
		
		std::size_t id() const {
			return _get_message().id();
		}
		
		__message& get() { return _get_message(); }
		__message const& get() const { return _get_message(); }
		
	private:
		__message& _get_message() {
			return utl::as_mutable(utl::as_const(*this)._get_message());
		}
		__message const& _get_message() const {
			if (_is_local()) {
				return *reinterpret_cast<__message const*>(_buffer);
			}
			else {
				return *_get_heap_ptr();
			}
		}
		
		std::size_t _local_id() const {
			return reinterpret_cast<__message const*>(_buffer)->_id;
		}
		
		bool _is_local() const {
			return _local_id() != __invalid_message_id;
		}
		
		__message* _get_heap_ptr() {
			return const_cast<__message*>(utl::as_const(*this)._get_heap_ptr());
		}
		__message const* _get_heap_ptr() const {
			return *reinterpret_cast<__message* const*>(_buffer + sizeof(void*));
		}
		std::size_t _get_heap_obj_size() const {
			return *reinterpret_cast<std::size_t const*>(_buffer + 2 * sizeof(void*));
		}
		heap_message _get_heap() const {
			heap_message heap;
			static_assert(sizeof heap == sizeof _buffer);
			std::memcpy(&heap, _buffer, sizeof _buffer);
			return heap;
		}
		
		void _set_heap(heap_message heap) {
			static_assert(sizeof heap == sizeof _buffer);
			std::memcpy(_buffer, &heap, sizeof _buffer);
		}
		
	private:
		alignas(_local_buffer_align) char _buffer[_local_buffer_size];
	};

	template <typename F>
	using __msgl_arg0 = typename utl::function_traits<std::decay_t<F>>::template argument<0>;

	/// MARK: - concept listener_function
	template <typename  F>
	concept listener_function =
		utl::any_invocable<F> &&
		utl::function_traits<std::decay_t<F>>::argument_count == 1 &&
		std::is_base_of_v<__message, std::remove_cvref_t<__msgl_arg0<F>>> &&
		!(std::is_lvalue_reference_v<__msgl_arg0<F>> && !std::is_const_v<std::remove_reference_t<__msgl_arg0<F>>>);

	/// MARK: - class listener_id
	class listener_id {
	public:
		listener_id() = default;
		listener_id(listener_id&&);
		listener_id& operator=(listener_id&&);
		~listener_id();
		
		std::strong_ordering operator<=>(listener_id const&) const = default;
		listener_id(__private_tag, std::size_t mid, std::size_t lid):
			_mid(mid),
			_lid(lid)
		{
			
		}
		
	private:
		friend class messenger;
		friend class listener;
		
		listener_id(listener_id const&);
		listener_id& operator=(listener_id const&);
		
		messenger* _messenger = nullptr;
		std::size_t _mid = 0;
		std::size_t _lid = 0;
	};
	
	
	/// MARK: - class listener
	class listener {
	public:
		listener(__private_tag) {}
		listener(listener_function auto&& f);
		
		friend class messenger;
		listener_id id;
		utl::function<void(__message const&)> f;
	};
	
	template <typename Message, utl::invocable<Message> F>
	requires std::is_base_of_v<__message, Message>
	listener make_listener(F&& f) {
		listener result(__private_tag{});
		result.id = listener_id{ __private_tag{}, __make_message_id<Message>, 0 };
		result.f = [=](__message const& msg) {
			f(static_cast<Message const&>(msg));
		};
		return result;
	}
	
	listener make_listener(listener_function auto&& f) {
		using Traits = utl::function_traits<std::decay_t<decltype(f)>>;
		using Message = std::remove_cvref_t<typename Traits::template argument<0>>;
		return make_listener<Message>(UTL_FORWARD(f));
	}
	
	listener::listener(listener_function auto&& f): listener(make_listener(UTL_FORWARD(f))) {}
	
	/// MARK: - class messenger
	class messenger {
	public:
		messenger() = default;
		messenger(messenger const&) = delete;
		
		[[nodiscard]] listener_id register_listener(listener);
		
		[[nodiscard]] listener_id register_listener(listener_function auto&& f) {
			return register_listener(make_listener(UTL_FORWARD(f)));
		}
		
		template <typename Message, utl::invocable<Message> F>
		requires std::is_base_of_v<__message, Message>
		[[nodiscard]] listener_id register_listener(F&& f) {
			return register_listener(make_listener<Message>(UTL_FORWARD(f)));
		}
		
		template <typename It>
		[[nodiscard]] utl::small_vector<listener_id> register_listeners(It begin, It end) {
			utl::small_vector<listener_id> result;
			for (; begin != end; ++begin) {
				result.push_back(register_listener(*begin));
			}
			return result;
		}
		
		void remove_listener(listener_id&);
		
		void send_message(message_type auto const& m) { do_send_message(m); }
		
	protected:
		void do_send_message(__message const&);
		
	private:
		utl::hashmap<std::size_t, utl::vector<listener>> _listeners;
		std::size_t _listener_id = 0;
	};
	
	class buffered_messenger: private messenger {
	public:
		using messenger::messenger;
		using messenger::register_listener;
		using messenger::register_listeners;
		using messenger::remove_listener;
		void send_message(message_type auto const& m) {
			_messages.push_back(m);
		}
		void flush() {
			for (auto&& m: _messages) {
				this->do_send_message(m.get());
			}
			_messages.clear();
		}
		
		std::size_t buffered_messages() const { return _messages.size(); }
		
	private:
		utl::vector<any_message> _messages;
	};
	
	/// MARK: - class listener_id_bag
	class listener_id_bag {
	public:
		void insert(listener_id&& id) {
			_ids.push_back(std::move(id));
		}
	private:
		utl::vector<listener_id> _ids;
	};
	
}



#endif // __UTL_MESSENGER_HPP_INCLUDED__
