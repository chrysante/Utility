#include <iostream>

#include <utl/structure_of_arrays.hpp>
#include <mtl/mtl.hpp>
#include <utl/stdio.hpp>
#include <random>
#include <utl/mdarray.hpp>
#include <utl/typeinfo.hpp>

using namespace mtl::short_types;

namespace mtl {
	

	
}

int main() {
	
	float3 const v = { 1, 0, 0 };
	quaternion_float const q = mtl::make_rotation(mtl::constants<>::pi / 2, { 0, 1, 0 });
	
	utl::print("v = {}\n", v);
	utl::print("q = {}\n", q);
	
	float3 const rotated = mtl::rotate(v, q);
	
	utl::print("rotated = {}\n", rotated);
	
}




#if 0
#define UTL_LOG



#include <utl/BVH.hpp>
#include <utl/stdio.hpp>
#include <iostream>
#include <random>

/// important seeds for unbalanced examples:
/// 0 (left -> right)
/// 2 (left -> left)
/// 20 (right -> right)
/// 21 (right -> left)
///

namespace {

	struct RandomAABBGen {
		mtl::AABB<> operator()() {
			std::uniform_real_distribution<> dist(0, 1);
			auto rand = [&]{ return dist(rng); };
			return mtl::AABB<>(mtl::double3(rand), mtl::double3(rand));
		}
		unsigned seed;
		std::mt19937 rng{ seed };
	};

}

int main() {
	
	using Tree = utl::BVH<int>;
	
	
	
	auto print = [](Tree const& tree) {
		// value and parent index
		utl::draw(std::cout, tree,
				  [](Tree::node const& node, int width) { return utl::format("{:<{}}:{:<{}}", node.is_leaf() ? (int)node.value : -1, 2, node.parent, width - 3); },
				  6);
		
		// volume
		//utl::draw(std::cout, tree, [](Tree::node const& node, int width) { return utl::format("{:^{}}", mtl::volume(node.bounding_volume), width); }, 6);
	};
	
//	for (unsigned _seed = 21; _seed < 1000; ++_seed)
	{
		unsigned const seed = 5;
		Tree tree, unbalancedTree;
		utl::print("{:=^{}}\n", "", 80);
		utl::print("{:=^{}}\n", utl::format("   Seed = {}   ", seed), 80);
		utl::print("{:=^{}}\n", "", 80);
		RandomAABBGen randomAABB{ seed };
		
		for (int i = 0; i < 8; ++i) {
			auto aabb = randomAABB();
//			if (i == 4) {
//				aabb = { aabb.bottom_left(), 100 };
//			}
//			if (i > 4) {
//				aabb = { aabb.bottom_left(), aabb.size() * 100 };
//			}
			unbalancedTree.insert_unbalanced(aabb, i);
			utl::print("{:-^{}}\n", " Unbalanced ", 80);
			utl::print("Added {}. Height = {}. Root Index = {}\n", i, unbalancedTree.height(), unbalancedTree.root_index());
			print(unbalancedTree);
			
//			tree.insert(aabb, i);
//			utl::print("{:-^{}}\n", " Balanced ", 80);
//			utl::print("Added {}. Height = {}. Root Index = {}\n", i, tree.height(), tree.root_index());
//			print(tree);
			
			
//			unbalancedTree = tree;
			
			if (tree.height() != unbalancedTree.height()) {
				
			}
		}
		utl::print("cost: {}\n", unbalancedTree.__cost());
//		tree.recalculate_bounding_volumes();
//		utl::print("{:-^{}}\n", " Recalculated BVs ", 80);
//		print(tree);
	}
}


#endif
























#if 0

#include <iostream>
#include <mtl/mtl.hpp>

#include <utl/aabb_tree.hpp>
#include <utl/memory_resource.hpp>
#include <utl/structure_of_arrays.hpp>
#include <utl/hash.hpp>

#include <random>


struct TreeMetrics {
	int height;
	double loadFactor;
	double totalVolume;
	double avgDist;
};

std::ostream& operator<<(std::ostream& str, TreeMetrics const& metrics) {
	str << "    Height:       " << metrics.height << "\n";
	str << "    Load Factor:  " << metrics.loadFactor << "\n";
	str << "    Total Volume: " << metrics.totalVolume << "\n";
	str << "    Avg Distance: " << metrics.avgDist;
	return str;
}

void compare(TreeMetrics const& a, TreeMetrics const& b) {
	std::cout << "   Height:       " << (b.height/ double(a.height))    * 100 << "%\n";
	std::cout << "   Load Factor:  " << (b.loadFactor  / a.loadFactor)  * 100 << "%\n";
	std::cout << "   Total Volume: " << (b.totalVolume / a.totalVolume) * 100 << "%\n";
	std::cout << "   Avg Distance: " << (b.avgDist     / a.avgDist)     * 100 << "%\n";
}

TreeMetrics calculateTreeMetrics(auto const& tree) {
	TreeMetrics result;
	result.height      = tree.height();
	result.loadFactor  = std::pow(tree.leaf_count(), 1.0 / result.height);
	result.totalVolume = tree.total_volume();
	result.avgDist     = tree.avg_dist();
	return result;
}

int main() {
	
	auto rand = [rng = std::mt19937(std::random_device{}()),
				 dist = std::uniform_real_distribution<float>(0, 1)]() mutable {
		return dist(rng);
	};
	
	int const count = 12;
	
	utl::vector<mtl::AABB<>> aabbs;
	aabbs.reserve(count);
	for (int i = 0; i < count; ++i) {
		aabbs.push_back(mtl::AABB<>(mtl::float3(rand), mtl::float3(rand)));
	}
	std::cout << "generated aabbs\n";
	std::cout << "-----------------------------------\n";
	
	utl::pmr::monotonic_buffer_resource mono_buffer;
	utl::pmr::aabb_tree<int> tree(&mono_buffer);
	
	for (int i = 0; i < count; ++i) {
		tree.insert(aabbs[i], i);
		draw(tree, [](utl::__aabb_tree_node<int, mtl::AABB<>> const* node, int width) {
			return utl::format("{:^{}}", node->height, width);
		});
		std::cout << "-----------------------------------\n";
	}
	
	
	
	TreeMetrics const beforeBalancing = calculateTreeMetrics(tree);
	std::cout << "Before Balancing:\n" << beforeBalancing << std::endl << std::endl;
	utl::draw(tree);
	
	tree.balance();

	TreeMetrics const afterBalancing = calculateTreeMetrics(tree);
	
	
	std::cout << "After Balancing:\n" << afterBalancing << std::endl << std::endl;
	utl::draw(tree);
	std::cout << "Ratio: \n";
	compare(beforeBalancing, afterBalancing);
	
}


#endif
