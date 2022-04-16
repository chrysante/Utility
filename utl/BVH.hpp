#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include "../mtl/shapes.hpp"
#include "../mtl/vector.hpp"
#include "vector.hpp"
#include "mdarray.hpp"
#include "format.hpp"
#include <stack>
#include <cstdint>
#include <type_traits>
#include <new>
#include <memory>
#include <iosfwd>

namespace utl {

	template <typename Derived, typename T, typename BV, bool = std::is_trivial_v<T>>
	struct __bvh_node_value_base;
	
	template <typename T, typename BV = mtl::AABB<>, typename Allocator = std::allocator<T>>
	class BVH {
	public:
		using value_type = T;
		using bounding_volume = BV;
		
		using index_type = std::uint32_t;
		static constexpr index_type invalid_index = index_type(-1);
		
		enum __direction {
			__dir_none = 0, __dir_left, __dir_right
		};
		
		struct __branch_tag{};
		struct __leaf_tag{};
		struct node: __bvh_node_value_base<node, T, BV> {
			using __base = __bvh_node_value_base<node, T, BV>;
			
			node(__branch_tag, bounding_volume const& bv, int height, index_type parent, index_type left, index_type right):
				__union_index(0),
				height(height),
				parent(parent),
				bounding_volume(bv)
			{
				this->left = left;
				this->right = right;
			}
			
			node(__leaf_tag, bounding_volume const& bv, int height, index_type parent, auto&&... args):
				__union_index(1),
				height(height),
				parent(parent),
				bounding_volume(bv)
			{
				::new ((void*)&this->value) T(UTL_FORWARD(args)...);
			}
			
			bool is_branch() const { return __union_index == 0; }
			bool is_leaf() const { return __union_index == 1; }
			
			std::uint8_t __union_index;   // occupying 64 bits in total
			std::int16_t height;          //
			index_type parent;            //
			bounding_volume bounding_volume;
		};
		
		/// MARK: Constructors
		// = default
		
		/// MARK: Assignment
		// = default
		
		/// MARK: Destructor
		// = default
		
		/// MARK: Modifiers
		void insert(bounding_volume const& bv, value_type const& value) {
			__emplace_impl(true, bv, value);
		}
		
		void insert(bounding_volume const& bv, value_type&& value) {
			__emplace_impl(true, bv, std::move(value));
		}
		
		void insert_unbalanced(bounding_volume const& bv, value_type const& value) {
			__emplace_impl(false, bv, value);
		}
		
		void insert_unbalanced(bounding_volume const& bv, value_type&& value) {
			__emplace_impl(false, bv, std::move(value));
		}
		
		template <typename... Args> requires (std::is_constructible_v<value_type, Args...>)
		void __emplace_impl(bool always_rebalance, bounding_volume const& bv, Args&&... args) {
			index_type const obj_node = __new_leaf(bv, 0, invalid_index, UTL_FORWARD(args)...);
			
			auto const new_obj_cost = volume(bv);
			
			if UTL_UNLIKELY (_nodes.size() == 1) {
				return;
			}
			
			index_type head_index = root_index();
			bounding_volume enclosing_volume;
			__direction descend_dir = __dir_none;
			
			// walk down
			while (_nodes[head_index].is_branch()) {
				auto& head = _nodes[head_index];
				
				constexpr double threshold = 0.5;
				
				auto const head_cost = volume(head.bounding_volume);
				if (new_obj_cost >= head_cost * threshold) {
					break;
				}
				
				auto const enclosing_left = enclosing(bv, _nodes[head.left].bounding_volume);
				auto const enclosing_right = enclosing(bv, _nodes[head.right].bounding_volume);
				
				auto const left_cost = volume(enclosing_left);
				auto const right_cost = volume(enclosing_right);
				
				if (left_cost <= right_cost) {
					head_index = head.left;
					enclosing_volume = enclosing_left;
					descend_dir = __dir_left;
				}
				else {
					head_index = head.right;
					enclosing_volume = enclosing_right;
					descend_dir = __dir_right;
				}
			}
			
			index_type const new_branch = __new_branch(enclosing_volume, 1, _nodes[head_index].parent,
													   head_index,
													   obj_node);
			// rewire parent
			if (_nodes[new_branch].parent != invalid_index) { // if new_branch is not the root
				node& parent = _nodes[_nodes[new_branch].parent];
				if (descend_dir == __dir_left) {
					parent.left = new_branch;
				}
				else {
					parent.right = new_branch;
				}
			}
			else {
				_root_index = new_branch;
			}
			
			_nodes[head_index].parent = new_branch;
			_nodes[obj_node].parent = new_branch;
			
//			__utl_assert_audit(_nodes[head_index].height == 0);
			__utl_assert_audit(_nodes[obj_node].height == 0);
			
			head_index = new_branch;
			
			// walk up
			while (head_index != invalid_index) {
				__utl_assert_audit(_nodes[head_index].is_branch());
				node* head_node = &_nodes[head_index];
				__utl_assert_audit(head_node->parent == invalid_index              ||
								   _nodes[head_node->parent].left == head_index    ||
								   _nodes[head_node->parent].right == head_index);

				head_node->height = std::max(_nodes[head_node->left].height,
											 _nodes[head_node->right].height) + 1;
				
				if (false && always_rebalance && std::abs(balance(head_index)) > 1) {
					index_type const old_head = head_index;
					index_type const parent = head_node->parent;
					head_index = __rebalance(head_index);
					head_node = &_nodes[head_index];
					
					if (parent != invalid_index) {
						if (_nodes[parent].left == old_head) {
							_nodes[parent].left = head_index;
						}
						else {
							__utl_assert_audit(_nodes[parent].right == old_head);
							_nodes[parent].right = head_index;
						}
					}
					else {
						_root_index = head_index;
					}
				}
				
				head_node->bounding_volume = enclosing(_nodes[head_node->left].bounding_volume,
													   _nodes[head_node->right].bounding_volume);
				
				__utl_assert_audit(encloses(head_node->bounding_volume, _nodes[head_node->left].bounding_volume));
				__utl_assert_audit(encloses(head_node->bounding_volume, _nodes[head_node->right].bounding_volume));
				
				head_index = head_node->parent;
			}
		}

		void recalculate_bounding_volumes() {
			if (empty()) {
				return;
			}
			__recalculate_bvs(root_index());
		}
		
		void __recalculate_bvs(index_type index) {
			auto&& n = _nodes[index];
			
			if (n.is_leaf()) {
				return;
			}
				
			__recalculate_bvs(n.left);
			__recalculate_bvs(n.right);
			n.bounding_volume = enclosing(_nodes[n.left].bounding_volume,
										  _nodes[n.right].bounding_volume);
		}
		
		void reserve_new_leaves(std::size_t count) {
			_nodes.reserve(_nodes.size() + count * 2);
		}
		
		/// MARK: Queries
		node& operator[](index_type index) { return _nodes[index]; }
		node const& operator[](index_type index) const { return _nodes[index]; }
		
		bool empty() const { return _nodes.empty(); }
		std::size_t node_count() const { return _nodes.size(); }
		std::size_t leaf_count() const { return (_nodes.size() + 1) / 2; }
		
		int height() const { return empty() ? -1 : _nodes[root_index()].height; }
		
		index_type root_index() const { return _root_index; }
		
		int balance(index_type node_index) const {
			node const& n = _nodes[node_index];
			return n.is_leaf() ? 0 : _nodes[n.right].height - _nodes[n.left].height;
		}
		
		small_vector<T> elements_satisfying(std::predicate<bounding_volume const&> auto&& pred) const {
			small_vector<T> result;
			if (empty()) {
				return result;
			}
			
			std::stack<index_type, utl::small_vector<index_type, 32>> stack;
			stack.push(root_index());
			
			while (!stack.empty()) {
				index_type const head_index = stack.top();
				stack.pop();
				node const& head = _nodes[head_index];
				if (!pred(head.bounding_volume)) {
					continue;
				}
				if (head.is_branch()) {
					stack.push(head.left);
					stack.push(head.right);
					continue;
				}
				result.push_back(head.value);
			}
			return result;
		}
		
		double __cost() const {
			double cost = 0.0f;
			for (auto& n: _nodes) {
				if (n.is_branch()) {
					cost += surface_area(n.bounding_volume);
				}
			}
			return cost;
		}
		
		/// MARK: Internals
		[[nodiscard]] index_type __rotate_left(index_type node_index) {
			node& n = _nodes[node_index];
			__utl_assert_audit(n.is_branch());
			
			// adjust parent indices
			_nodes[n.right].parent = n.parent;
			_nodes[_nodes[n.right].left].parent = node_index;
			n.parent = n.right;
			
			index_type const right_index = n.right;
			node& r = _nodes[right_index];
			__utl_assert_audit(r.is_branch());
			
			n.right = r.left;
			
			r.left = node_index;

			n.height = std::max(_nodes[n.left].height, _nodes[n.right].height) + 1;
			r.height = std::max(_nodes[r.left].height, _nodes[r.right].height) + 1;

			return right_index;
		}

		[[nodiscard]] index_type __rotate_right(index_type node_index) {
			node& n = _nodes[node_index];
			__utl_assert_audit(n.is_branch());
			
			// adjust parent indices
			_nodes[n.left].parent = n.parent;
			_nodes[_nodes[n.left].right].parent = node_index;
			n.parent = n.left;
			
			index_type const left_index = n.left;
			node& l = _nodes[left_index];
			__utl_assert_audit(l.is_branch());
			
			n.left = l.right;
			l.right = node_index;
			
			n.height = std::max(_nodes[n.left].height, _nodes[n.right].height) + 1;
			l.height = std::max(_nodes[l.left].height, _nodes[l.right].height) + 1;
			
			return left_index;
		}


		[[nodiscard]] index_type __rotate_right_left(index_type node_index) {
			node* n = &_nodes[node_index];
			__utl_assert_audit(n->is_branch());
			n->right = __rotate_right(n->right);
			
			node_index = __rotate_left(node_index);
			n = &_nodes[node_index];
			
			n->height = std::max(_nodes[n->left].height, _nodes[n->right].height) + 1;
			
			return node_index;
		}

		[[nodiscard]] index_type __rotate_left_right(index_type node_index) {
			node* n = &_nodes[node_index];
			__utl_assert_audit(n->is_branch());
			
			n->left = __rotate_left(n->left);
			
			node_index = __rotate_right(node_index);
			n = &_nodes[node_index];
			
			n->height = std::max(_nodes[n->left].height, _nodes[n->right].height) + 1;
			
			return node_index;
		}
		
		[[nodiscard]] index_type __rebalance(index_type node_index) {
			node* n = &_nodes[node_index];
			__utl_expect(n->is_branch());
			
			if (balance(node_index) < -1) {
				node& l = _nodes[n->left];
				if (_nodes[l.left].height >= _nodes[l.right].height) {
					return __rotate_right(node_index);
				}
				else {
					return __rotate_left_right(node_index);
				}
			}
			if (balance(node_index) > 1) {
				node& r = _nodes[n->right];
				if (_nodes[r.left].height <= _nodes[r.right].height) {
					return __rotate_left(node_index);
				}
				else {
					return __rotate_right_left(node_index);
				}
			}
			return node_index;
		}
		
		template <typename... Args>
		index_type __new_leaf(bounding_volume const& bv, int height, index_type parent, Args&&... args) {
			return __new_node(__leaf_tag{}, bv, height, parent, UTL_FORWARD(args)...);
		}
		
		index_type __new_branch(bounding_volume const& bv, int height, index_type parent, index_type left, index_type right) {
			return __new_node(__branch_tag{}, bv, height, parent, left, right);
		}
		
		template <typename... Args>
		index_type __new_node(Args&&... args) {
			_nodes.emplace_back(UTL_FORWARD(args)...);
			return _nodes.size() - 1;
		}
		
	private:
		using __node_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;
		utl::vector<node, __node_alloc> _nodes;
		index_type _root_index = 0;
	};
	
	template <typename Derived, typename T, typename BV, bool>
	struct __bvh_node_value_base /* trivial = true */ {
		union {
			struct { std::uint32_t left, right; };
			T value;
		};
	};
	
	template <typename Derived, typename T, typename BV, bool>
	struct __bvh_node_value_base<Derived, T, BV, false> {
		__bvh_node_value_base() = default;
		
		__bvh_node_value_base(__bvh_node_value_base const& rhs) {
			__copy_construct_impl(rhs, rhs.value);
		}
		
		__bvh_node_value_base(__bvh_node_value_base&& rhs) noexcept(std::is_nothrow_move_constructible_v<T>) {
			__copy_construct_impl(std::move(rhs), std::move(rhs.value));
		}
		
		void __copy_construct_impl(auto&& rhs, auto&& rhs_value) {
			if (rhs.__as_derived().is_leaf()) {
				::new ((void*)&value) T(UTL_FORWARD(rhs_value));
			}
			else {
				left = rhs.left;
				right = rhs.right;
			}
		}
		
		__bvh_node_value_base& operator=(__bvh_node_value_base const& rhs) {
			return __assign_impl(rhs, rhs.value);
		}
		
		__bvh_node_value_base& operator=(__bvh_node_value_base&& rhs) noexcept(std::is_nothrow_move_assignable_v<T>) {
			return __assign_impl(std::move(rhs), std::move(rhs.value));
		}
		
		__bvh_node_value_base& __assign_impl(auto&& rhs, auto&& rhs_value) {
			if (__as_derived().is_leaf() && rhs.__as_derived().is_leaf()) {
				value = UTL_FORWARD(rhs_value);
			}
			else if (__as_derived().is_branch() && rhs.__as_derived().is_branch()) {
				left = rhs.left;
				right = rhs.right;
			}
			else {
				this->~__node_value_base();
				::new ((void*)this) __bvh_node_value_base(UTL_FORWARD(rhs));
			}
			return *this;
		}
		
		~__bvh_node_value_base() {
			if (__as_derived().is_leaf()) {
				std::destroy_at(&value);
			}
		}
		
		Derived& __as_derived() { return (Derived&)*this; }
		Derived const& __as_derived() const { return (Derived const&)*this; }
		
		union {
			struct { typename Derived::index_type left, right; };
			T value;
		};
	};

	/// MARK: Formatting
	template <typename T, typename BV, typename A, typename Formatter>
	struct __BVH_formatter {
		struct draw_data {
			BVH<T, BV, A> const& tree;
			std::size_t head;
			bool parent_is_left;
			int level;
			int edge_len;
			int leaf_width;
			mdarray<utl::vector<char>, 2>& canvas;
			mtl::int2 cursor_pos;
			Formatter& formatter;
		};
		
		static void draw_node(draw_data const& data) {
			using namespace mtl;
			if (data.tree[data.head].is_branch()) {
				for (int i = 0; i < data.edge_len; ++i) {
					data.canvas(data.cursor_pos + int2{ -i, i }) = '/';
					data.canvas(data.cursor_pos + int2{ i + 1, i }) = '\\';
				}
				if constexpr (std::invocable<Formatter, T const&, int>) {
					return;
				}
			}
			std::string value;
			if constexpr (std::invocable<Formatter, T const&, int>) {
				value = data.formatter(data.tree[data.head].value, data.leaf_width);
			}
			else {
				static_assert(std::invocable<Formatter, typename BVH<T, BV, A>::node const&, int>);
				value = data.formatter(data.tree[data.head], data.leaf_width);
			}
			
			for (int i = 0; i < data.leaf_width; ++i) {
				int const index_offset_x = i - data.leaf_width / 2 + 1 + !data.parent_is_left;
				auto const index = data.cursor_pos + int2{ index_offset_x, 0 };
				if (index.x >= data.canvas.size().x) {
					continue;
				}
				data.canvas(index) = value[i];
			}
		}
		
		static void draw_rec(draw_data data) {
			using namespace mtl;
			draw_node(data);
			if (data.tree[data.head].is_branch()) {
				int cursor_offset_y = data.level == 0 ? 3 : data.level == 1 ? data.edge_len / 2 : data.edge_len;
				cursor_offset_y = data.edge_len;
				draw_rec({
					.tree = data.tree,
					.head = data.tree[data.head].left,
					.parent_is_left = true,
					.level = data.level + 1,
					.edge_len = data.edge_len / 2,
					.leaf_width = data.leaf_width,
					.canvas = data.canvas,
					.cursor_pos = data.cursor_pos + int2{ -data.edge_len, cursor_offset_y },
					.formatter = data.formatter
				});
				draw_rec({
					.tree = data.tree,
					.head = data.tree[data.head].right,
					.parent_is_left = false,
					.level = data.level + 1,
					.edge_len = data.edge_len / 2,
					.leaf_width = data.leaf_width,
					.canvas = data.canvas,
					.cursor_pos = data.cursor_pos + int2{ data.edge_len, cursor_offset_y },
					.formatter = data.formatter
				});
			}
		}
		
		static void draw(std::ostream& stream, BVH<T, BV, A> const& tree, Formatter& formatter, int leaf_width) {
			using namespace mtl;
			
			if (tree.empty()) {
				stream << "∅\n";
				return;
			}
			
			int const height = tree.height();
			int const max_leaf_count = ipow(2, height);
			int const column_count = leaf_width * max_leaf_count;
			
			mdarray<utl::vector<char>, 2> canvas(column_count + 1, column_count / 2);
			std::fill(canvas.begin(), canvas.end(), ' ');
			
			int const begin_edge_len = column_count / 4;
			int2 const begin_cursor_pos = { column_count / 2, 0 };
			
			draw_rec({
				.tree = tree,
				.head = tree.root_index(),
				.parent_is_left = false,
				.level = 0,
				.edge_len = begin_edge_len,
				.leaf_width = leaf_width,
				.canvas = canvas,
				.cursor_pos = begin_cursor_pos,
				.formatter = formatter
			});
			
			// ignore whitespace lines in the back
			int y_end = canvas.size().y;
//			for (; y_end >= 0; --y_end) {
//				for (int x = 0; x < canvas.size().x; ++x) {
//					if (canvas(x, y_end - 1) != ' ') {
//						goto present;
//					}
//				}
//			}
			
			present:
			for (int y = 0; y < y_end; ++y) {
				for (int x = 0; x < canvas.size().x; ++x) {
					stream.put(canvas(x, y));
				}
				stream.put('\n');
			}
		}
	};
	
	struct __default_bvh_data_formatter {
		template <typename T>
		std::string operator()(T const& data, int leaf_width) const {
			return utl::format("{:^{}}", data, leaf_width);
		}
	};
	
	template <typename Formatter = __default_bvh_data_formatter, typename T, typename BV, typename A>
	void draw(std::ostream& stream, BVH<T, BV, A> const& tree, Formatter formatter = {}, int leaf_width = 4) {
		__BVH_formatter<T, BV, A, Formatter>::draw(stream, tree, formatter, leaf_width);
	}
	
}
