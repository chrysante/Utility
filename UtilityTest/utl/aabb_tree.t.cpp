#include "Catch2.hpp"

#include <utl/aabb_tree.hpp>


//TEST_CASE("aabb_tree") {
//	utl::aabb_tree<int, mtl::AABB<float, 2>> tree;
//	
//	CHECK(tree.empty());
//	CHECK(tree.height() == -1);
//	
//	tree.insert({ 0, 1 }, 0);
//	
//	CHECK(!tree.empty());
//	CHECK(tree.height() == 0);
//	
//	tree.insert({ 0.2, 1 }, 0);
//	
//	CHECK(tree.height() == 1);
//	
//	CHECK(tree.balanced());
//	
//	auto copy = tree;
//	
//	CHECK(copy.height() == 1);
//	
//	tree.clear();
//	CHECK(tree.empty());
//	CHECK(tree.height() == -1);
//}
