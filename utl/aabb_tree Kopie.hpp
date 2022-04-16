#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "__debug.hpp"
#include "common.hpp"
#include "concepts.hpp"
#include "vector.hpp"
#include "__memory_resource_base.hpp"
#include "../mtl/shapes.hpp"
#include "stdio.hpp"
#include "mdarray.hpp"

#include <stack>

namespace utl {
	
	/// MARK: Fwd Decl
	/*
	 AABB requires the following operations to be available (via ADL):
		default and copy construction
		assignment
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
		__aabb_tree_node(int height, AABB const& aabb, __aabb_branch_tag, __aabb_tree_node* left, __aabb_tree_node* right):
			height(height), aabb(aabb), _index(0), left(left), right(right)
		{}
		
		__aabb_tree_node(int height, AABB const& aabb, __aabb_leaf_tag, auto&&... args):
			height(height), aabb(aabb), _index(1), value(UTL_FORWARD(args)...)
		{}
		
		~__aabb_tree_node() {
			if constexpr (!std::is_trivially_destructible_v<T>) {
				__utl_assert(_index == 0 || _index == 1);
				if (_index == 1) {
					std::destroy_at(&value);
				}
			}
		}
		
		bool is_branch() const { return _index == 0; }
		bool is_leaf() const { return _index == 1; }
		
		int balance() const {
			return is_leaf() ? 0 : right->height - left->height;
		}
		
		std::uint8_t _index;
		int height = 0;
		union {
			struct {
				__aabb_tree_node* left;
				__aabb_tree_node* right;
			};
			T value;
		};
		AABB aabb;
	};
	
	template <typename T, typename AABB>
	std::ostream& operator<<(std::ostream& str, __aabb_tree_node<T, AABB> const& node) {
		if (node.is_branch) {
			return str << "branch{ .aabb = " << node.aabb << ", .left = " << volume(node.left->aabb) << ", .right = " << volume(node.right->aabb) << " }";
		}
		else {
			return str << "leaf{ .aabb = " << node.aabb << ", .value = " << node.leaf() << " }";
		}
	}
	
	template <typename T, typename AABB, typename Allocator>
	void print(aabb_tree<T, AABB, Allocator> const&);
	
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
		
		template <typename _T, typename _AABB, typename _A>
		friend void print(aabb_tree<_T, _AABB, _A> const&);
		
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
			__node* const obj_node = __new_leaf(-1, aabb, UTL_FORWARD(args)...);
			
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

				auto const enclosing_left = enclosing(aabb, head->left->aabb);
				auto const enclosing_right = enclosing(aabb, head->right->aabb);
				
				auto const left_cost = volume(enclosing_left);
				auto const right_cost = volume(enclosing_right);
				
				if (left_cost <= right_cost) {
					head_location = &head->left;
					enclosing_aabb = enclosing_left;
				}
				else {
					head_location = &head->right;
					enclosing_aabb = enclosing_right;
				}
				head = *head_location;
			}
			
			
			*head_location = __new_branch(head->height, enclosing_aabb, obj_node, head);
			
			head->height += 1;
			obj_node->height = head->height;
			
			head = *head_location;
			
			
			// walk up
			while (!ancestors.empty()) {
				head = ancestors.top();
				ancestors.pop();
				__utl_assert(head->is_branch());
				
				head->height += 1;
//				if (std::abs(head->balance()) > 1) {
//					__node** head_loc = __get_node_loc(head, ancestors.empty() ? _root : ancestors.top());
//					head = __rebalance(head);
//					*head_loc = head;
//
//				}
//				__utl_assert(std::abs(head->balance()) <= 1);
				
				__utl_log("head->balance = {}", head->balance());
				
				head->aabb = enclosing(head->left->aabb,
									   head->right->aabb);
			}
		}
		
		static __node** __get_node_loc(__node* node, __node* parent) {
			__utl_expect(node->is_branch());
			if (parent->left == node || parent->left == node->left || parent->left == node->right) {
				return &parent->left;
			}
			else {
				__utl_assert(parent->right == node || parent->right == node->left || parent->right == node->right);
				return &parent->right;
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
				__clear_rec(node->left);
				__clear_rec(node->right);
			}
			__delete_node(node);
		}
		
		void balance() {
			if (!_root) {
				return;
			}
			__balance_rec(&_root);
			__recalculate_aabbs(_root);
		}
		
		static __node** __select_child_for_rotation(__node* node) {
			__utl_assert(node->is_branch());
			int lst_height = __height(node->left);
			int rst_height = __height(node->right);
			int balance = lst_height - rst_height;
			if (balance >= 0) {
				return &node->right;
			}
			else {
				return &node->left;
			}
		}
		
		
		
		[[nodiscard]] static __node* __rotate_left(__node* node) {
			__utl_assert(node->is_branch());
			
			__node* right = node->right;
			__utl_assert(right->is_branch());
			
			node->right = right->left;
			
			right->left = node;

//			n.height = max(n.Left.Height(), n.Right.Height()) + 1
//			r.height = max(r.Left.Height(), r.Right.Height()) + 1

			return right;
		}

		[[nodiscard]] static __node* __rotate_right(__node* node) {
			__utl_assert(node->is_branch());
			
			__node* left = node->left;
			__utl_assert(left->is_branch());
			
			node->left = left->right;
			
			left->right = node;
			
//			n.height = max(n.Left.Height(), n.Right.Height()) + 1
//			l.height = max(l.Left.Height(), l.Right.Height()) + 1
			
			return left;
		}


		[[nodiscard]] static __node* __rotate_right_left(__node* node) {
			__utl_assert(node->is_branch());
			node->right = __rotate_right(node->right);
			
			node = __rotate_left(node);
			
//			n.height = max(n.Left.Height(), n.Right.Height()) + 1
			
			return node;
		}

		[[nodiscard]] static __node* __rotate_left_right(__node* node) {
			__utl_assert(node->is_branch());
			node->left = __rotate_left(node->left);
			
			node = __rotate_right(node);
			
//			n.height = max(n.Left.Height(), n.Right.Height()) + 1
			
			return node;
		}
		
		static int __get_balance(__node* node) {
			if (node->is_leaf()) {
				return 0;
			}
			int left_height = __height(node->left);
			int right_height = __height(node->right);
			return right_height - left_height;
		}
		
		[[nodiscard]] static __node* __rebalance(__node* node) {
			__utl_expect(node->is_branch());
			
			if (node->balance() < -1) {
				if (node->left->balance() <= 0) {
					return __rotate_right(node);
				}
				else {
					return __rotate_left_right(node);
				}
			}
			if (node->balance() > 1) {
				if (node->right->balance() >= 0) {
					return __rotate_left(node);
				}
				else {
					return __rotate_right_left(node);
				}
			}
			return node;
		}

//		func (n *Node) rebalance() *Node {
//			fmt.Println("rebalance " + n.Value)
//			n.Dump(0, "")
//			switch {
//
//		Left subtree is too high, and left child has a left child.
//
//			case n.Bal() < -1 && n.Left.Bal() == -1:
//				return n.rotateRight()
//
//		Left subtree is too high, and left child has a right child.
//
//			case n.Bal() < -1 && n.Left.Bal() == 1:
//				return n.rotateLeftRight()
					
					
//		Right subtree is too high, and right child has a right child.
//
//			case n.Bal() > 1 && n.Right.Bal() == 1:
//				return n.rotateLeft()
//

//
//		Right subtree is too high, and right child has a left child.
//
//			case n.Bal() > 1 && n.Right.Bal() == -1:
//				return n.rotateRightLeft()
//			}
//			return n
//		}

		static void __rotate_to_balance(__node** head_loc, int rec_depth) {
			__utl_assert(rec_depth < 100);
			__node* head = *head_loc;
			
			int lst_height = __height(head->left);
			int rst_height = __height(head->right);
			int balance = lst_height - rst_height;
			
			if (std::abs(balance) <= 1) {
				return;
			}
			
			if (balance > 0) {
				// rotate
				__node* left = head->left;
				__utl_assert(left->is_branch(), "must be branch otherwise balance can't be greater than one");
				__node** to_rotate = __select_child_for_rotation(left);
				head->left = *to_rotate;
				*to_rotate = head;
				*head_loc = left;
			}
			else if (balance < 0) {
				// rotate
				__node* right = head->right;
				__utl_assert(right->is_branch(), "must be branch otherwise balance can't be less than minus one");
				__node** to_rotate = __select_child_for_rotation(right);
				head->right = *to_rotate;
				*to_rotate = head;
				*head_loc = right;
			}
			__rotate_to_balance(head_loc, rec_depth + 1);
		}
		
		static void __balance_rec(__node** head_loc) {
			if ((*head_loc)->is_leaf()) {
				return;
			}
			
			__node* head = *head_loc;
			
			__utl_assert(head->is_branch());
			__balance_rec(&head->left);
			__balance_rec(&head->right);
			
			__rotate_to_balance(head_loc, 0);
		}
		
		static void __recalculate_aabbs(__node* head) {
			if (head->is_branch()) {
				__recalculate_aabbs(head->left);
				__recalculate_aabbs(head->right);
				head->aabb = enclosing(head->left->aabb, head->right->aabb);
			}
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
					__intersecting_rec(pred, head->left, result);
					__intersecting_rec(pred, head->right, result);
				}
			}
		}
		
		bool empty() const { return _root == nullptr; }
		
		int height() const {
			if (empty()) {
				return -1;
			}
			return __height(_root);
		}
		
		static int __height(__node* node) {
			__utl_expect(node);
			int result = -1;
			__height_rec(0, result, node);
			return result;
		}
		
		static void __height_rec(int current_height, int& max_value, __node* head) {
			if (head->is_leaf()) {
				max_value = std::max(max_value, current_height);
			}
			else {
				__height_rec(current_height + 1, max_value, head->left);
				__height_rec(current_height + 1, max_value, head->right);
			}
		}
		
		bool balanced() const {
			if (empty()) {
				return true;
			}
			return __balanced(_root);
		}
		
		static bool __balanced(__node* node) {
			if (node->is_leaf()) {
				return true;
			}
			else {
				bool left_balanced = __balanced(node->left);
				bool right_balanced = __balanced(node->right);
				int balance = __height(node->left) - __height(node->right);
				return
					left_balanced &&
					left_balanced &&
					std::abs(balance) <= 1;
			}
		}
		
		double total_volume() const {
			return _root ? __total_volume_rec(_root) : 0.0;
		}
		
		static double __total_volume_rec(__node* head) {
			double v = volume(head->aabb);
			if (head->is_branch()) {
				v += __total_volume_rec(head->left) + __total_volume_rec(head->right);
			}
			return v;
		}
		
		double avg_dist() const {
			if (!_root) {
				return 0;
			}
			auto total = __avg_dist_rec(_root);
			return total.x / total.y;
		}
		
		static auto __aabb_center(aabb_type const& aabb) {
			return aabb.bottom_left() + aabb.size() / 2.0;
		}
		
		static auto __aabb_dist(aabb_type const& a, aabb_type const& b) {
			return distance(__aabb_center(a), __aabb_center(b));
		}
		
		static mtl::double2 __avg_dist_rec(__node* head) {
			if (head->is_leaf()) {
				return 0;
			}
			
			auto left_result = __avg_dist_rec(head->left);
			auto right_result = __avg_dist_rec(head->right);
			return left_result + right_result + mtl::double2{ __aabb_dist(head->left->aabb, head->right->aabb), 1 };
		}

		std::size_t node_count() const {
			return _root ? __node_count_rec(_root) : 0;
		}
		
		static std::size_t __node_count_rec(__node* head) {
			if (head->is_leaf()) {
				return 1;
			}
			return 1 + __node_count_rec(head->left) + __node_count_rec(head->right);
		}
		
		
	private:
		__node* __deep_copy_rec(__node const* from) {
			if (from->is_branch()) {
				return __new_branch(from->aabb,
									__deep_copy_rec(from->left),
									__deep_copy_rec(from->right));
			}
			else {
				return __new_leaf(from->aabb, from->value);
			}
		}
		
		template <typename... Args>
		__node* __new_leaf(int height, aabb_type const& aabb, Args&&... args) {
			return __new_node_(height, aabb, __aabb_leaf_tag{}, UTL_FORWARD(args)...);
		}
		
		__node* __new_branch(int height, aabb_type const& aabb, __node* left, __node* right) {
			return __new_node_(height, aabb, __aabb_branch_tag{}, left, right);
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

	template <typename T, typename AABB>
	void __draw_node(__aabb_tree_node<T, AABB> const* node,
					 bool parent_left,
					 int level,
					 int edge_len,
					 int leaf_width,
					 mdarray<utl::vector<char>, 2>& canvas,
					 mtl::int2 cursor_pos)
	{
		using namespace mtl;
		if (node->is_branch()) {
			if (level == 0) {
				for (int i = 0; i < edge_len; ++i) {
					canvas(cursor_pos + int2{ -i, 3 * i / edge_len }) = '/';
					canvas(cursor_pos + int2{ i + 1, 3 * i / edge_len }) = '\\';
				}
			}
			else if (level == 1) {
				for (int i = 0; i < edge_len; ++i) {
					canvas(cursor_pos + int2{ -i, i / 2 }) = '/';
					canvas(cursor_pos + int2{ i + 1, i / 2 }) = '\\';
				}
			}
			else {
				for (int i = 0; i < edge_len; ++i) {
					canvas(cursor_pos + int2{ -i, i }) = '/';
					canvas(cursor_pos + int2{ i + 1, i }) = '\\';
				}
			}
		}
		else {
			std::string const value = utl::format("{:^{}}", node->value, leaf_width);
			for (int i = 0; i < leaf_width; ++i) {
				int const index_offset_x = i - leaf_width / 2 + 1 + !parent_left;
				auto const index = cursor_pos + int2{ index_offset_x, 0 };
				if (index.x >= canvas.size().x) {
					continue;
				}
				canvas(index) = value[i];
			}
		}
	}
	
	template <typename T, typename AABB>
	void __draw_tree_rec(__aabb_tree_node<T, AABB> const* head,
						 bool parent_left,
						 int level,
						 int edge_len,
						 int leaf_width,
						 mdarray<utl::vector<char>, 2>& canvas,
						 mtl::int2 cursor_pos)
	{
		using namespace mtl;
		__draw_node(head, parent_left, level, edge_len, leaf_width, canvas, cursor_pos);
		if (head->is_branch()) {
			int cursor_offset_y = level == 0 ? 3 : level == 1 ? edge_len / 2 : edge_len;
			__draw_tree_rec(head->left, true, level + 1, edge_len / 2, leaf_width, canvas, cursor_pos + int2{ -edge_len, cursor_offset_y });
			__draw_tree_rec(head->right, false, level + 1, edge_len / 2, leaf_width, canvas, cursor_pos + int2{ edge_len, cursor_offset_y });
		}
	}
	
	template <typename T, typename AABB, typename Allocator>
	void print(aabb_tree<T, AABB, Allocator> const& tree) {
		if (tree.empty()) {
			utl::print("∅\n");
			return;
		}
		
		
		
		int const height = tree.height();
		int const max_leaf_count = ipow(2, height);
		int const leaf_width = 4;
		int const column_count = leaf_width * max_leaf_count;
		
		
		mdarray<utl::vector<char>, 2> canvas(column_count, column_count / 2);
		std::fill(canvas.begin(), canvas.end(), ' ');
		
		int const begin_edge_len = column_count / 4;
		
		using namespace mtl;
		__draw_tree_rec(tree._root, 0, 0, begin_edge_len, leaf_width, canvas, int2{ column_count / 2, 0 });
		
		int y_end = canvas.size().y;
		for (; y_end >= 0; --y_end) {
			for (int x = 0; x < canvas.size().x; ++x) {
				if (canvas(x, y_end - 1) != ' ') {
					goto present;
				}
			}
		}
		
		present:
		for (int y = 0; y < y_end; ++y) {
			for (int x = 0; x < canvas.size().x; ++x) {
				std::cout.put(canvas(x, y));
			}
			std::cout.put('\n');
		}
	}
	
}
