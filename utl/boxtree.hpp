//#pragma once
//
//#include "__debug.hpp"
//#include "hashmap.hpp"
//#include "hash.hpp"
//#include "vector.hpp"
//#include "__function_objects.hpp"
//
//#include "../mtl/mtl.hpp"
//
//#include <memory>
//
//namespace utl {
//	
//	template <typename Value, typename VectorType = mtl::float3, typename Allocator = std::allocator<Value>>
//	class boxtree;
//	
//	template <typename T, typename VectorType>
//	struct __bt_treenode {
//		
//	};
//	
//	//template <typename Val, typename Vec, typename Alloc>
//	//using __boxtree_alloc_type = typename std::allocator_traits<Alloc>::template rebind_alloc<__bt_treenode<Val, Vec>>;
//	
//	/// MARK: - boxtree
//	template <typename Value, typename VectorType, typename Allocator>
//	class boxtree: Allocator {
//	public:
//		/// MARK: Public Member Types
//		using value_type = Value;
//		using vector_type = VectorType;
//		
//		using allocator_type = Allocator;
//		
//		using aabb_type = mtl::AABB<typename mtl::get_underlying_type<vector_type>::type, mtl::get_vector_size<vector_type>::value>;
//		
//		struct options {
//			vector_type root_box_size = 1;
//			std::size_t max_objects_per_node = 8;
//		};
//		
//		/// MARK: Internal Member Types
//		using __treenode = __bt_treenode<Value, VectorType>;
//		//using __treenode_allocator_ = __boxtree_alloc_type<Value, VectorType, Allocator>;
//		
//		struct __vector_hash;
//		
//		/// MARK: Constructor
//		explicit boxtree(options opt):
//			_options(opt)
//		{}
//		
//		/// MARK: insert
//		void insert(aabb_type const& aabb, value_type const& value) {
//			emplace(aabb, value);
//		}
//		void insert(aabb_type const& aabb, value_type&& value) {
//			emplace(aabb, std::move(value));
//		}
//		
//		template <typename... Args>
//		void emplace(aabb_type const& aabb, Args&&... args) {
//			__utl_expect(mtl::is_normalized(aabb));
//		}
//		
//	private:
//		bool _is_root_level(aabb_type const& aabb) const {
//			auto const mod_ext = mtl::map(aabb.origin, aabb.extend, _options.root_box_size, [](auto origin, auto extend, auto box_size) {
//				return utl::mod(origin, box_size) + extend <= box_size;
//			}).fold(utl::logical_and);
//			mtl::map(mod_ext, )
//		}
//		
//	private:
//		options _options;
//		hashmap<vector_type, __treenode, __vector_hash> _roots{ 0, __vector_hash(_options.root_box_size) };
//		vector<Value, Allocator> _rootlevel_values;
//	};
//	
//	/// MARK: - __vector_hash
//	template <typename Value, typename VectorType, typename A>
//	struct boxtree<Value, VectorType, A>::__vector_hash {
//		explicit __vector_hash(vector_type const& box_size): _box_size(box_size) {}
//		
//		std::size_t operator()(vector_type const& v) const noexcept {
//			auto const ivec = mtl::map(v, _box_size, [](auto a, auto b){ return std::int64_t(a / b); });
//			return utl::hash_combine_range(ivec.begin(), ivec.end());
//		}
//		
//		vector_type _box_size;
//	};
//	
//}
