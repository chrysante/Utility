#pragma once

#include "__base.hpp"
#include "__robin_hood.h"
#include "hash.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {
	
	template <typename Key, typename Hash = robin_hood::hash<Key>,
			  typename KeyEqual = std::equal_to<Key>>
	using flat_hashset = robin_hood::unordered_flat_set<Key, Hash, KeyEqual>;

	template <typename Key, typename Hash = robin_hood::hash<Key>,
			  typename KeyEqual = std::equal_to<Key>>
	using node_hashset = robin_hood::unordered_node_set<Key, Hash, KeyEqual>;
	
	template <typename Key, typename Hash = robin_hood::hash<Key>,
			  typename KeyEqual = std::equal_to<Key>>
	using hashset = robin_hood::unordered_set<Key, Hash, KeyEqual>;
	
}
