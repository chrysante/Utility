#pragma once

#include <unordered_map>
#include <unordered_set>

#include "__base.hpp"
#include "__third_party/ankerl/unordered_dense.h"
#include "hash.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename Key, typename Hash = utl::hash<Key>,
          typename KeyEqual = std::equal_to<>,
          typename Allocator = std::allocator<Key>>
using hashset = ankerl::unordered_dense::set<Key, Hash, KeyEqual, Allocator>;

template <typename Key, typename T, typename Hash = utl::hash<Key>,
          typename KeyEqual = std::equal_to<>,
          typename Allocator = std::allocator<std::pair<Key, T>>>
using hashmap = ankerl::unordered_dense::map<Key, T, Hash, KeyEqual, Allocator>;

template <typename Key, typename Hash = utl::hash<Key>,
          typename KeyEqual = std::equal_to<>,
          typename Allocator = std::allocator<Key>>
using node_hashset = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

template <typename Key, typename T, typename Hash = utl::hash<Key>,
          typename KeyEqual = std::equal_to<>,
          typename Allocator = std::allocator<std::pair<Key const, T>>>
using node_hashmap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

} // namespace utl
