#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "common.hpp"
#include "concepts.hpp"
#include "vector.hpp"
#include "__memory_resource_base.hpp"
#include "../mtl/shapes.hpp"

#include <stack>
#include <variant>

namespace utl {
	
	/// MARK: Fwd Decl
	/*
	 AABB requires the following operations to be available via ADL:
	 enclosing(AABB, AABB) -> AABB
	 volume(AABB) -> floating-point-number
	 do_intersect(AABB, AABB) -> bool (optional)
	 */
	template <typename T, typename AABB = mtl::AABB<>, typename Allocator = std::allocator<T>>
	class aabb_tree;
	
	namespace pmr {
		template <typename T, typename AABB = mtl::AABB<>>
		using aabb_tree = utl::aabb_tree<T, AABB, pmr::polymorphic_allocator<T>>;
	}
	
	/// MARK: - Tree Node
	struct __aabb_branch_tag {};
	struct __aabb_leaf_tag {};
	
	template <typename T, typename AABB>
	struct __aabb_tree_node {
		struct branch_t {
			__aabb_tree_node* left;
			__aabb_tree_node* right;
		};
		
		__aabb_tree_node(AABB const& aabb, __aabb_branch_tag, __aabb_tree_node* left, __aabb_tree_node* right):
			aabb(aabb), __value(branch_t{ left, right })
		{}
		
		__aabb_tree_node(AABB const& aabb, __aabb_leaf_tag, auto&&... args):
			aabb(aabb), __value(std::in_place_type<T>, UTL_FORWARD(args)...)
		{}
		
		bool is_branch() const { return __value.index() == 0; }
		bool is_leaf() const { return __value.index() == 1; }
		
		branch_t& branch() { return std::get<0>(__value); }
		branch_t const& branch() const { return std::get<0>(__value); }
		
		T& leaf() { return std::get<1>(__value); }
		T const& leaf() const { return std::get<1>(__value); }
		
		AABB aabb;
		std::variant<branch_t, T> __value;
	};
	
	template <typename T, typename AABB>
	std::ostream& operator<<(std::ostream& str, __aabb_tree_node<T, AABB> const& node) {
		if (node.is_branch()) {
			return str << "branch{ .aabb = " << node.aabb << ", .left = " << volume(node.branch().left->aabb) << ", .right = " << volume(node.branch().right->aabb) << " }";
		}
		else {
			return str << "leaf{ .aabb = " << node.aabb << ", .value = " << node.leaf() << " }";
		}
	}
	
	/// MARK: - Tree
	template <typename T, typename AABB, typename Allocator>
	class aabb_tree: std::allocator_traits<Allocator>::template rebind_alloc<__aabb_tree_node<T, AABB>> {
	public:
		using value_type = T;
		using aabb_type = AABB;
		using allocator_type = Allocator;
		
		using __node = __aabb_tree_node<T, AABB>;
		
		using __node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<__aabb_tree_node<T, AABB>>;
		using __node_allocator_traits = std::allocator_traits<__node_allocator>;
		
	public:
		/// MARK: Constructors
		aabb_tree() = default;
		aabb_tree(allocator_type const& alloc): __node_allocator(alloc) {}
		
		aabb_tree(aabb_tree const& rhs): aabb_tree(rhs, allocator_type{}) {}
		
		aabb_tree(aabb_tree const& rhs, allocator_type const& alloc): __node_allocator(alloc) {
			if (rhs._root == nullptr) {
				return;
			}
			_root = __deep_copy_rec(rhs._root);
		}
		
		aabb_tree(aabb_tree&& rhs) noexcept: _root(rhs._root) {
			rhs._root = nullptr;
		}
		
		/// MARK: Assignment
		aabb_tree& operator=(aabb_tree const& rhs) {
			if (this == &rhs) {
				return;
			}
			clear();
			if (rhs._root == nullptr) {
				return;
			}
			_root = __deep_copy_rec(rhs._root);
			return *this;
		}
		
		aabb_tree& operator=(aabb_tree&& rhs) noexcept {
			_root = rhs._root;
			rhs._root = nullptr;
			return *this;
		}
		
		/// MARK: Destructor
		~aabb_tree() {
			clear();
		}
		
		/// MARK: Modifiers
		void insert(aabb_type const& aabb, value_type const& value) {
			emplace(aabb, value);
		}
		
		void insert(aabb_type const& aabb, value_type&& value) {
			emplace(aabb, std::move(value));
		}
		
		template <iterator_for<std::pair<aabb_type, value_type>> I, sentinel_for<I> S>
		void insert(I begin, S end) {
			while (begin != end) {
				auto&& p = *begin;
				insert(p.first, p.second);
				++begin;
			}
		}
		
		template <typename... Args> requires (std::is_constructible_v<value_type, Args...>)
		void emplace(aabb_type const& aabb, Args&&... args) {
			__node* const obj_node = __new_leaf(aabb, UTL_FORWARD(args)...);
			
			if UTL_UNLIKELY (_root == nullptr) {
				_root = obj_node;
				return;
			}
			
			__node** head_location = &_root;
			__node* head = _root;

			std::stack<__node*, utl::small_vector<__node*, 8>> ancestors;

			aabb_type enclosing_aabb;
			
			// walk down
			while (head->is_branch()) {
				ancestors.push(head);

				auto const enclosing_left = enclosing(aabb, head->branch().left->aabb);
				auto const enclosing_right = enclosing(aabb, head->branch().right->aabb);
				
				auto const left_cost = volume(enclosing_left);
				auto const right_cost = volume(enclosing_right);
				
				if (left_cost <= right_cost) {
					head_location = &head->branch().left;
					enclosing_aabb = enclosing_left;
				}
				else {
					head_location = &head->branch().right;
					enclosing_aabb = enclosing_right;
				}
				head = *head_location;
			}
			
			*head_location = __new_branch(enclosing_aabb, obj_node, head);
			
			// walk up
			while (!ancestors.empty()) {
				head = ancestors.top();
				ancestors.pop();
				__utl_assert(head->is_branch());
				head->aabb = enclosing(head->branch().left->aabb,
									   head->branch().right->aabb);
			}
		
		}
		
		void clear() {
			if (_root == nullptr) {
				return;
			}
			__clear_rec(_root);
			_root = nullptr;
		}
		
		void __clear_rec(__node* node) {
			if (node->is_branch()) {
				__clear_rec(node->branch().left);
				__clear_rec(node->branch().right);
			}
			__delete_node(node);
		}
		
		/// MARK: Queries
		utl::small_vector<value_type> values_intersecting(aabb_type const& aabb) const
			requires requires { { do_intersect(aabb, aabb) } -> std::convertible_to<bool>; }
		{
			return values_satisfying([&](aabb_type const& rhs){ return do_intersect(aabb, rhs); });
		}
		
		utl::small_vector<value_type> values_satisfying(std::predicate<aabb_type> auto&& predicate) const {
			utl::small_vector<value_type> result;
			if UTL_LIKELY (_root != nullptr) {
				__satisfying_rec(predicate, _root, result);
			}
			return result;
		}
		
		void __satisfying_rec(auto const& pred, __node* head, utl::small_vector<value_type>& result) const {
			if (pred(head->aabb)) {
				if (head->is_leaf()) {
					result.push_back(head->leaf());
				}
				else {
					__intersecting_rec(pred, head->branch().left, result);
					__intersecting_rec(pred, head->branch().right, result);
				}
			}
		}
		
		bool empty() const { return _root == nullptr; }
		
		int height() const {
			if (empty()) {
				return 0;
			}
			int result = -1;
			__height_rec(1, result, _root);
			return result;
		}
		
		static void __height_rec(int current_height, int& max_value, __node* head) {
			if (head->is_leaf()) {
				max_value = std::max(max_value, current_height);
			}
			else {
				__height_rec(current_height + 1, max_value, head->branch().left);
				__height_rec(current_height + 1, max_value, head->branch().right);
			}
		}
		
	private:
		__node* __deep_copy_rec(__node const* from) {
			if (from->is_branch()) {
				return __new_branch(from->aabb,
									__deep_copy_rec(from->branch().left),
									__deep_copy_rec(from->branch().right));
			}
			else {
				return __new_leaf(from->aabb, from->leaf());
			}
		}
		
		template <typename... Args>
		__node* __new_leaf(aabb_type const& aabb, Args&&... args) {
			return __new_node_(aabb, __aabb_leaf_tag{}, UTL_FORWARD(args)...);
		}
		
		__node* __new_branch(aabb_type const& aabb, __node* left, __node* right) {
			return __new_node_(aabb, __aabb_branch_tag{}, left, right);
		}
		
		template <typename... Args>
		__node* __new_node_(Args&&... args) {
			__node* result = __node_allocator_traits::allocate(*this, 1);
			__node_allocator_traits::construct(*this, result, UTL_FORWARD(args)...);
			return result;
		}
		
		void __delete_node(__node* ptr) {
			__node_allocator_traits::destroy(*this, ptr);
			__node_allocator_traits::deallocate(*this, ptr, 1);
		}
		
	private:
		__node* _root = nullptr;
	};
	
}
