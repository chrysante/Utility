#pragma once

#ifndef __UTL_MAP_INCLUDED__
#define __UTL_MAP_INCLUDED__

#include "__base.hpp"

#include "concepts.hpp"
#include "utility.hpp"
#include "optref.hpp"
#include "__function_objects.hpp"
#include "__prime.hpp"

#include <memory>
#include <iosfwd>

#ifdef _UTL_MAP_DEBUG_PRINT
#include <iostream>
#include <iomanip>
#endif

_UTL_SYSTEM_HEADER_

namespace utl {

	template <typename Key, typename Map>
	concept __heterogenous_key = requires(typename Map::key_equal eq,
										  typename Map::hash hash,
										  Key&& a,
										  typename Map::key_type const& b)
	{
		{ eq(a, b) } -> __boolean_testable;
		{ hash(a) } -> std::convertible_to<std::size_t>;
	};
	
	template <typename T>
	using __utl_aligned_storage_for = std::aligned_storage_t<sizeof(T), alignof(T)>;
	
	template <typename T>
	std::size_t __good_hash(T const& t) {
		return std::hash<T>{}(t);
	}
	
	inline std::size_t __good_hash(std::uint64_t x) {
		x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
		x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
		x = x ^ (x >> 31);
		return x;
	}

	inline std::size_t __good_hash(std::int64_t x) {
		return __good_hash((std::uint64_t)x);
	}
	
	inline std::size_t __good_hash(std::uint32_t x) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}
	
	inline std::size_t __good_hash(std::int32_t x) {
		return __good_hash((std::uint32_t)x);
	}
	
	template <typename T>
	struct good_hash {
		std::size_t operator()(T const& t) const { return __good_hash(t); }
	};
	
	/// MARK: class map
	template <typename Key, typename Value, typename KeyHash = good_hash<Key>, typename KeyEq = std::equal_to<Key>, typename Allocator = std::allocator<void>>
	class map: KeyHash, KeyEq, std::allocator_traits<Allocator>::template rebind_alloc<std::uint8_t> {
	public:
		using key_type = Key;
		using value_type = Value;
		using key_equal = KeyEq;
		using hash = KeyHash;
		using __self = map;
		using __allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<std::uint8_t>;
		
		static constexpr double __max_load_factor = 0.8;
		
		struct __pair_type {
			key_type key;
			value_type value;
		};
		
		template <typename>
		struct __lookup_result;
		using lookup_result = __lookup_result<value_type>;
		using const_lookup_result = __lookup_result<value_type const>;
		
		struct insert_result;
		
		struct remove_result;
		
		template <typename>
		struct __iterator;
		using iterator = __iterator<value_type>;
		using const_iterator = __iterator<value_type const>;
		
	public:
		/// MARK: Lifetime
		map() = default;
		map(map&&);
		~map();
		
		/// MARK: lookup
		auto lookup(__heterogenous_key<__self> auto&& key)           -> lookup_result;
		auto lookup(__heterogenous_key<__self> auto&& key) const     -> const_lookup_result;
		
		/// MARK: insert
		auto insert(__heterogenous_key<__self> auto&& key,
					value_type const&)                                 -> insert_result;
		auto insert(__heterogenous_key<__self> auto&& key,
					value_type&&)                                      -> insert_result;
		auto insert(__heterogenous_key<__self> auto&& key,
					invocable_r<value_type> auto&& f)                  -> insert_result;
		auto insert(__heterogenous_key<__self> auto&& key,
					std::invocable<value_type*> auto&& f)              -> insert_result;
		
		/// MARK: emplace
		template <typename... Args>
		auto emplace(__heterogenous_key<__self> auto&& key,
					 Args&&...)                                        -> insert_result;
		
		/// MARK: update
		auto update(__heterogenous_key<__self> auto&& key,
					value_type const&)                                 -> insert_result;
		auto update(__heterogenous_key<__self> auto&& key,
					value_type&&)                                      -> insert_result;
		auto update(__heterogenous_key<__self> auto&& key,
					invocable_r<value_type> auto&& f)                  -> insert_result;
		
		/// MARK: remove
		auto remove(__heterogenous_key<__self> auto&& key)             -> remove_result;
		
		/// MARK: erase
		auto erase(__heterogenous_key<__self> auto&& key)              -> bool;
		
		/// MARK: reserve
		auto reserve(std::size_t capacity)                             -> void;
		
		/// MARK: operator[]
		auto operator[](__heterogenous_key<__self> auto&& key)         -> optref<value_type>;
		auto operator[](__heterogenous_key<__self> auto&& key) const   -> optref<value_type const>;
		
		/// MARK: contains
		auto contains(__heterogenous_key<__self> auto&& key) const     -> bool;
		
		/// MARK: begin/end
		auto begin()                                                   -> iterator;
		auto end()                                                     -> iterator;
		
		auto begin() const                                             -> const_iterator;
		auto end() const                                               -> const_iterator;
		
		auto cbegin() const                                            -> const_iterator;
		auto cend() const                                              -> const_iterator;
		
		/// MARK: size
		auto size() const                                              -> std::size_t;
	
		/// MARK: Private statics
		auto __allocate(std::size_t count) -> std::tuple<std::uint8_t*, __pair_type*>;
		auto __deallocate(void* buffer, std::size_t count);
		auto __calc_array_occ_size(std::size_t count) -> std::tuple<std::size_t, std::size_t>;
		
		auto __hash(__heterogenous_key<__self> auto&& key) const -> std::size_t;
		auto __compare(auto&& a, auto&& b) const -> bool;
		auto __recommend_size(std::size_t min) const -> std::size_t;
		
		/// MARK: Private modifiers
		auto __set_has_element(std::size_t index, bool) -> void;
		auto __destroy() -> void;
		auto __rebuild(std::size_t size) -> void;
		template <bool Safe, bool Update = false>
		auto __insert_impl(auto&& key, auto&& f) -> std::conditional_t<Safe, insert_result, void>;
		template <bool Remove>
		auto __remove_impl(auto&& key) -> std::conditional_t<Remove, remove_result, bool>;
		
		/// MARK: Private queries
		auto __has_element(std::size_t index) const -> bool;
		auto __is_tombstone(std::size_t index) const -> bool;
		auto __get_key(std::size_t index) const -> key_type const&;
		auto __get_value(std::size_t index) -> value_type&;
		auto __get_value(std::size_t index) const -> value_type const&;
		auto __load_factor() const -> double;
		auto __calc_offset(std::size_t index) const -> std::size_t;
		auto __sum_of_offsets() const -> std::size_t;
		
#ifdef _UTL_MAP_DEBUG_PRINT
		auto __debug_print() const -> void;
#endif
		
		/// MARK: Private data
		struct __data_members {
			std::uint32_t size, cap;
		};
		__data_members __data{};
		std::uint8_t* __occ_buffer = nullptr;
		__pair_type* __buffer = nullptr;
	};
	
#define _UTL_NOTHING
#define _UTL_MAP_METHOD_PROLOG_IMPL(RETURN_TYPE, ...) \
template <typename Key, typename Value, typename KeyHash, typename KeyEq, typename Allocator> \
__VA_ARGS__ \
RETURN_TYPE map<Key, Value, KeyHash, KeyEq, Allocator>

	/// MARK: Member types
#define _UTL_MAP_MEMBER_PROLOG(...) _UTL_MAP_METHOD_PROLOG_IMPL(__VA_ARGS__)
	
	_UTL_MAP_MEMBER_PROLOG(struct, template <typename VT>)::__lookup_result {
		__lookup_result() = default;
		explicit __lookup_result(__pair_type const& p): __pair(const_cast<__pair_type*>(&p)) {}
		
		explicit operator bool() const { return __pair != nullptr; }
		
		key_type const& key() { return __pair->key; }
		VT& value() { return __pair->value; }
		
		__lookup_result<std::remove_const_t<VT>> __to_mutable() const {
			return __lookup_result<std::remove_const_t<VT>>{ *__pair };
		}
		
		__pair_type* __pair = nullptr;
	};

	_UTL_MAP_MEMBER_PROLOG(struct)::insert_result {
		insert_result() = default;
		insert_result(bool inserted, __pair_type& p): __key_inserted(&p.key, inserted), __value(&p.value) {}

		explicit operator bool() const { return __key_inserted.integer(); }

		key_type const& key() { return *__key_inserted.pointer(); }
		value_type& value() { return *__value; }

		pointer_int_pair<key_type const*, unsigned, 1> __key_inserted = { nullptr, false };
		value_type* __value;
	};

	_UTL_MAP_MEMBER_PROLOG(struct)::remove_result {
		remove_result() = default;
		remove_result(key_type&& k, value_type&& v): __removed(true) {
			std::construct_at(&key(), std::move(k));
			std::construct_at(&value(), std::move(v));
		}
		~remove_result() {
			if (*this) {
				std::destroy_at(&key());
				std::destroy_at(&value());
			}
		}

		explicit operator bool() const { return __removed; }

		key_type& key() { __utl_expect(*this); return reinterpret_cast<key_type&>(__key); }
		value_type& value() { __utl_expect(*this); return reinterpret_cast<value_type&>(__value); }

		bool __removed = false;
		__utl_aligned_storage_for<key_type> __key;
		__utl_aligned_storage_for<value_type> __value;
	};
	
	_UTL_MAP_MEMBER_PROLOG(struct, template <typename VT>)::__iterator {
		
	};
	
#define _UTL_MAP_CTOR_PROLOG() _UTL_MAP_METHOD_PROLOG_IMPL(_UTL_NOTHING)
	
	/// MARK: Lifetime
	_UTL_MAP_CTOR_PROLOG()::map(map&& rhs): __data(rhs.__data), __occ_buffer(rhs.__occ_buffer), __buffer(rhs.__buffer) {
		rhs.__data = {};
		rhs.__occ_buffer = nullptr;
		rhs.__buffer = nullptr;
	}
	
	_UTL_MAP_CTOR_PROLOG()::~map() {
		__destroy();
	}
	
#undef _UTL_NOTHING
#undef _UTL_MAP_CTOR_PROLOG
	
#define _UTL_MAP_METHOD_PROLOG(...) _UTL_MAP_METHOD_PROLOG_IMPL(auto __VA_OPT__(,) __VA_ARGS__)
	
	/// MARK: lookup
	_UTL_MAP_METHOD_PROLOG()::lookup(__heterogenous_key<__self> auto&& key)
	-> lookup_result {
		return const_cast<map const&>(*this).lookup(UTL_FORWARD(key)).__to_mutable();
	}
	
	_UTL_MAP_METHOD_PROLOG()::lookup(__heterogenous_key<__self> auto&& key) const
	-> const_lookup_result {
		std::size_t index = __hash(key);
		while (__has_element(index)) {
			if (__compare(__get_key(index), key)) {
				return const_lookup_result(__buffer[index]);
			}
			index = (index + 1) % __data.cap;
		}
		return const_lookup_result();
	}
	
	/// MARK: insert
	_UTL_MAP_METHOD_PROLOG()::insert(__heterogenous_key<__self> auto&& key,
									 value_type const& value)
	-> insert_result {
		return insert(UTL_FORWARD(key), [&](value_type* ptr) { std::construct_at(ptr, value); });
	}
	
	_UTL_MAP_METHOD_PROLOG()::insert(__heterogenous_key<__self> auto&& key,
									 value_type&& value)
	-> insert_result {
		return insert(UTL_FORWARD(key), [&](value_type* ptr) { std::construct_at(ptr, std::move(value)); });
	}
	
	_UTL_MAP_METHOD_PROLOG()::insert(__heterogenous_key<__self> auto&& key,
									 invocable_r<value_type> auto&& f)
	-> insert_result {
		return insert(UTL_FORWARD(key), [&](value_type* ptr) { std::construct_at(ptr, std::invoke(f)); });
	}
		
	_UTL_MAP_METHOD_PROLOG()::insert(__heterogenous_key<__self> auto&& key,
									 std::invocable<value_type*> auto&& f)
	-> insert_result {
		return __insert_impl<true>(UTL_FORWARD(key), UTL_FORWARD(f));
	}
	

	_UTL_MAP_METHOD_PROLOG(template <typename... Args>)::emplace(__heterogenous_key<__self> auto&& key,
																 Args&&... args)
	-> insert_result {
		return insert(UTL_FORWARD(key), [&](value_type* ptr){ std::construct_at(ptr, UTL_FORWARD(args)...); });
	}
	
	/// MARK: update
	_UTL_MAP_METHOD_PROLOG()::update(__heterogenous_key<__self> auto&& key,
									 value_type const& value)
	-> insert_result {
		return update(UTL_FORWARD(key), [&]{ return value; });
	}
	_UTL_MAP_METHOD_PROLOG()::update(__heterogenous_key<__self> auto&& key,
									 value_type&& value)
	-> insert_result {
		return update(UTL_FORWARD(key), [&]{ return std::move(value); });
	}
	_UTL_MAP_METHOD_PROLOG()::update(__heterogenous_key<__self> auto&& key,
									 invocable_r<value_type> auto&& f)
	-> insert_result {
		return __insert_impl<true, true>(UTL_FORWARD(key), UTL_FORWARD(f));
	}
	
	/// MARK: remove
	_UTL_MAP_METHOD_PROLOG()::remove(__heterogenous_key<__self> auto&& key) -> remove_result {
		return __remove_impl<true>(UTL_FORWARD(key));
	}
	
	/// MARK: erase
	_UTL_MAP_METHOD_PROLOG()::erase(__heterogenous_key<__self> auto&& key) -> bool {
		return __remove_impl<false>(UTL_FORWARD(key));
	}
	
	/// MARK: reserve
	_UTL_MAP_METHOD_PROLOG()::reserve(std::size_t capacity) -> void {
		if (capacity <= __data.cap) {
			return;
		}
		__rebuild(__recommend_size(std::ceil(capacity / __max_load_factor)));
	}
	
	/// MARK: operator[]
	_UTL_MAP_METHOD_PROLOG()::operator[](__heterogenous_key<__self> auto&& key)       -> optref<value_type> {
		return const_cast<__self const*>(this)->operator[](UTL_FORWARD(key)).__to_mutable();
	}
	
	_UTL_MAP_METHOD_PROLOG()::operator[](__heterogenous_key<__self> auto&& key) const -> optref<value_type const> {
		std::size_t const begin_index = __hash(key);
		std::size_t index = begin_index;
		while (true) {
			if (__has_element(index)) {
				if (__compare(__get_key(index), key)) {
					return optref<value_type const>(__get_value(index));
				}
			}
			else if (!__is_tombstone(index)) {
				return optref<value_type const>();
			}
			index = (index + 1) % __data.cap;
			if (index == begin_index) {
				return optref<value_type const>();
			}
		}
	}
	
	/// MARK: contains
	_UTL_MAP_METHOD_PROLOG()::contains(__heterogenous_key<__self> auto&& key) const   -> bool {
		std::size_t const begin_index = __hash(key);
		std::size_t index = begin_index;
		while (true) {
			if (__has_element(index)) {
				if (__compare(__get_key(index), key)) {
					return true;
				}
			}
			else if (!__is_tombstone(index)) {
				return false;
			}
			index = (index + 1) % __data.cap;
			if (index == begin_index) {
				return false;
			}
		}
	}
	
	/// MARK: size
	_UTL_MAP_METHOD_PROLOG()::size() const -> std::size_t {
		return __data.size;
	}
	
	/// MARK: Private statics
	_UTL_MAP_METHOD_PROLOG()::__allocate(std::size_t count) -> std::tuple<std::uint8_t*, __pair_type*> {
		auto const [info_size, array_size] = __calc_array_occ_size(count);
		std::uint8_t* const buffer = static_cast<std::uint8_t*>(__allocator_type::allocate(array_size + info_size));
		__utl_assert(((std::uintptr_t)buffer) % alignof(__pair_type) == 0);
		std::memset(buffer, 0, info_size);
		return { buffer, reinterpret_cast<__pair_type*>(buffer + info_size) };
	}
	
	_UTL_MAP_METHOD_PROLOG()::__deallocate(void* buffer, std::size_t count) {
		auto const [info_size, array_size] = __calc_array_occ_size(count);
		__allocator_type::deallocate(__occ_buffer, info_size + array_size);
	}
	
	_UTL_MAP_METHOD_PROLOG()::__calc_array_occ_size(std::size_t count) -> std::tuple<std::size_t, std::size_t> {
		std::size_t const array_size = sizeof(__pair_type) * count;
		std::size_t const info_size = ceil_divide(ceil_divide(count, (std::size_t)CHAR_BIT), alignof(__pair_type)) * alignof(__pair_type);
		return { info_size, array_size };
	}
	
	_UTL_MAP_METHOD_PROLOG()::__hash(__heterogenous_key<__self> auto&& key) const -> std::size_t {
		return this->KeyHash::operator()(key) % __data.cap;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__compare(auto&& a, auto&& b) const -> bool {
		return this->KeyEq::operator()(UTL_FORWARD(a), UTL_FORWARD(b));
	}
	
	_UTL_MAP_METHOD_PROLOG()::__recommend_size(std::size_t min) const -> std::size_t {
		return __next_prime(std::max((std::size_t)__data.cap * 2, min));
	}

	/// MARK: Private modifiers
	_UTL_MAP_METHOD_PROLOG()::__set_has_element(std::size_t index, bool value) -> void {
		if (value) {
			__occ_buffer[index / CHAR_BIT] |= 1 << index % CHAR_BIT;
		}
		else {
			__occ_buffer[index / CHAR_BIT] &= ~(1 << index % CHAR_BIT);
		}
	}
	
	_UTL_MAP_METHOD_PROLOG()::__destroy() -> void {
		if (__occ_buffer) {
			if constexpr (!std::is_trivially_destructible<__pair_type>::value) {
				for (std::size_t i = 0; i < __data.cap; ++i) {
					if (!__has_element(i)) { continue; }
					std::destroy_at(&__buffer[i]);
				}
			}
			__deallocate(__occ_buffer, __data.cap);
		}
	}

	_UTL_MAP_METHOD_PROLOG()::__rebuild(std::size_t cap) -> void {
		map old = std::move(*this);
		
		std::tie(__occ_buffer, __buffer) = __allocate(cap);
		__data.cap = cap;
		__data.size = old.__data.size;
		
		for (std::size_t i = 0; i < old.__data.cap; ++i) {
			if (!old.__has_element(i)) { continue; }
			__insert_impl<false>(std::move(old.__buffer[i].key), [&](value_type* ptr) {
				std::construct_at(ptr, std::move(old.__buffer[i].value));
			});
		}
	}
	
	_UTL_MAP_METHOD_PROLOG(template <bool Safe, bool Update>)::__insert_impl(auto&& key, auto&& f)
	-> std::conditional_t<Safe, insert_result, void> {
		if constexpr (Safe) {
			if (double lf = __load_factor();
				lf > __max_load_factor)
			{
				__rebuild(__recommend_size(__data.size + 1));
			}
		}
		std::size_t const begin_index = __hash(key);
		std::size_t index = begin_index;
		while (__has_element(index)) {
			if constexpr (Safe) {
				if (__compare(__get_key(index), key)) {
					if constexpr (Update) {
						__get_value(index) = std::invoke(f);
						return insert_result(true, __buffer[index]);
					}
					else {
						return insert_result();
					}
				}
			}
			index = (index + 1) % __data.cap;
			if (index == begin_index) {
				throw;
			}
		}
		auto& element = __buffer[index];
		std::construct_at(&element.key, UTL_FORWARD(key));
		
		if constexpr (!Update) {
			std::invoke(f, &element.value);
		}
		else {
			std::construct_at(&element.value, std::invoke(f));
		}
		
		__set_has_element(index, true);
		
		if constexpr (Safe) {
			++__data.size;
			return insert_result(true, element);
		}
	}
	
//	_UTL_MAP_METHOD_PROLOG(template <bool Remove>)::__remove_impl(auto&& key) -> std::conditional_t<Remove, remove_result, bool> {
//
//	}
	
	/// MARK: Private queries
	_UTL_MAP_METHOD_PROLOG()::__has_element(std::size_t index) const -> bool {
		return __occ_buffer[index / CHAR_BIT] & 1 << index % CHAR_BIT;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__is_tombstone(std::size_t index) const -> bool {
		/// TODO: Implement this
		return false;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__get_key(std::size_t index) const -> key_type const& {
		return __buffer[index].key;
	}

	_UTL_MAP_METHOD_PROLOG()::__get_value(std::size_t index) -> value_type& {
		return __buffer[index].value;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__get_value(std::size_t index) const -> value_type const& {
		return __buffer[index].value;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__load_factor() const -> double {
		auto const result = __data.cap == 0 ? 1.0 : double(__data.size) / __data.cap;
		return result;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__calc_offset(std::size_t index) const -> std::size_t {
		__utl_expect(__has_element(index));
		std::int64_t const hash_value = __hash(__buffer[index].key);
		std::int64_t offset = (std::int64_t)index - hash_value;
		while (offset < 0) { offset += __data.cap; }
		return offset;
	}
	
	_UTL_MAP_METHOD_PROLOG()::__sum_of_offsets() const -> std::size_t {
		std::size_t sum = 0;
		for (std::int64_t i = 0; i < __data.cap; ++i) {
			if (!__has_element(i)) {
				continue;
			}
			sum += __calc_offset(i);
		}
		return sum;
	}
	
#ifdef _UTL_MAP_DEBUG_PRINT
	_UTL_MAP_METHOD_PROLOG()::__debug_print() const -> void {
		std::cout << "/* size = " << size() << ", cap = " << __data.cap << " */ {\n";
		for (std::size_t i = 0; i < __data.cap; ++i) {
			std::cout << "\tslot[" << std::setw(3) << i << "]";
			if (__has_element(i)) {
				std::cout << " = ";
				std::cout << "[offset: " << std::setw(3) << __calc_offset(i) << "] ";
				std::cout << "{ " << std::setw(3) << __buffer[i].key << ", " << std::setw(3) << __buffer[i].value << " }";
			}
			std::cout << "\n";
		}
		std::cout << "}\n";
	}
#endif
	
#undef _UTL_MAP_METHOD_PROLOG
	
}

#endif // __UTL_MAP_INCLUDED__
