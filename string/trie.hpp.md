---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/trie.test.cpp
    title: verify/string/trie.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/trie.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\n// A multiset trie for a contiguous character alphabet.\n\
    template <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct Trie {\n  \
    \  static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n    static constexpr\
    \ node_id null_node = -1;\n\n    struct Node {\n        std::array<node_id, AlphabetSize>\
    \ child;\n        int subtree_count;\n        int terminal_count;\n\n        Node()\
    \ : subtree_count(0), terminal_count(0) {\n            child.fill(null_node);\n\
    \        }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    int _distinct_size;\n\
    \n    template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id new_node()\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    node_id find_node(const Sequence& sequence)\
    \ const {\n        node_id node = 0;\n        for (const auto& symbol : sequence)\
    \ {\n            node = _nodes[node].child[symbol_index(symbol)];\n          \
    \  if (node == null_node || _nodes[node].subtree_count == 0) {\n             \
    \   return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    Trie() : _nodes(1), _distinct_size(0) {}\n\n    int size() const\
    \ {\n        return _nodes[0].subtree_count;\n    }\n\n    int distinct_size()\
    \ const {\n        return _distinct_size;\n    }\n\n    bool empty() const {\n\
    \        return size() == 0;\n    }\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id\
    \ && std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n\
    \    template <class Sequence>\n    node_id find(const Sequence& sequence) const\
    \ {\n        return find_node(sequence);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            int index = symbol_index(symbol);\n\
    \            node_id child = _nodes[node].child[index];\n            if (child\
    \ == null_node) {\n                child = new_node();\n                _nodes[node].child[index]\
    \ = child;\n            }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored strings beginning with prefix.\n\
    \    template <class Sequence>\n    int prefix_count(const Sequence& prefix) const\
    \ {\n        node_id node = find_node(prefix);\n        return node == null_node\
    \ ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class Sequence>\n\
    \    bool starts_with(const Sequence& prefix) const {\n        return prefix_count(prefix)\
    \ != 0;\n    }\n\n    template <class Sequence>\n    bool erase_one(const Sequence&\
    \ sequence) {\n        node_id terminal = find_node(sequence);\n        if (terminal\
    \ == null_node || _nodes[terminal].terminal_count == 0) {\n            return\
    \ false;\n        }\n\n        int node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        int\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        int node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        node = _nodes[node].child[symbol_index(symbol)];\n            if (node\
    \ == null_node || _nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored string that is a prefix.\n    // Returns -1\
    \ when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_TRIE_HPP\n#define M1UNE_STRING_TRIE_HPP 1\n\n#include\
    \ <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\n// A multiset trie for\
    \ a contiguous character alphabet.\ntemplate <int AlphabetSize = 26, int FirstCharacter\
    \ = 'a'>\nstruct Trie {\n    static_assert(0 < AlphabetSize);\n\n    using node_id\
    \ = int;\n    static constexpr node_id null_node = -1;\n\n    struct Node {\n\
    \        std::array<node_id, AlphabetSize> child;\n        int subtree_count;\n\
    \        int terminal_count;\n\n        Node() : subtree_count(0), terminal_count(0)\
    \ {\n            child.fill(null_node);\n        }\n    };\n\n   private:\n  \
    \  std::vector<Node> _nodes;\n    int _distinct_size;\n\n    template <class Symbol>\n\
    \    static int symbol_index(const Symbol& symbol) {\n        int index = int(symbol)\
    \ - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n   \
    \     return index;\n    }\n\n    node_id new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    template <class Sequence>\n\
    \    node_id find_node(const Sequence& sequence) const {\n        node_id node\
    \ = 0;\n        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            if (node == null_node || _nodes[node].subtree_count == 0) {\n   \
    \             return null_node;\n            }\n        }\n        return node;\n\
    \    }\n\n   public:\n    Trie() : _nodes(1), _distinct_size(0) {}\n\n    int\
    \ size() const {\n        return _nodes[0].subtree_count;\n    }\n\n    int distinct_size()\
    \ const {\n        return _distinct_size;\n    }\n\n    bool empty() const {\n\
    \        return size() == 0;\n    }\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id\
    \ && std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n\
    \    template <class Sequence>\n    node_id find(const Sequence& sequence) const\
    \ {\n        return find_node(sequence);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            int index = symbol_index(symbol);\n\
    \            node_id child = _nodes[node].child[index];\n            if (child\
    \ == null_node) {\n                child = new_node();\n                _nodes[node].child[index]\
    \ = child;\n            }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored strings beginning with prefix.\n\
    \    template <class Sequence>\n    int prefix_count(const Sequence& prefix) const\
    \ {\n        node_id node = find_node(prefix);\n        return node == null_node\
    \ ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class Sequence>\n\
    \    bool starts_with(const Sequence& prefix) const {\n        return prefix_count(prefix)\
    \ != 0;\n    }\n\n    template <class Sequence>\n    bool erase_one(const Sequence&\
    \ sequence) {\n        node_id terminal = find_node(sequence);\n        if (terminal\
    \ == null_node || _nodes[terminal].terminal_count == 0) {\n            return\
    \ false;\n        }\n\n        int node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        int\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        int node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        node = _nodes[node].child[symbol_index(symbol)];\n            if (node\
    \ == null_node || _nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored string that is a prefix.\n    // Returns -1\
    \ when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_TRIE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/trie.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-22 15:33:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/trie.test.cpp
documentation_of: string/trie.hpp
layout: document
title: Trie
---

## Overview

`m1une::string::Trie` is a multiset of strings represented by a prefix tree.
It supports duplicate insertion, deletion, exact lookup, counting strings with
a given prefix, and enumerating stored strings that are prefixes of a query.

Nodes are stored in one contiguous vector. The alphabet must be a contiguous
range of character codes, making transitions constant-time without maps or
per-edge allocations.

## Template Parameters

* `AlphabetSize`: Number of symbols in the alphabet. Defaults to `26`.
* `FirstCharacter`: Character code corresponding to transition `0`. Defaults
  to `'a'`.

The default `Trie<>` accepts lowercase English letters. For decimal digits,
use `Trie<10, '0'>`.

Methods are generic over iterable sequences whose symbols can be converted to
integers, including `std::string`, `std::string_view`, and character vectors.
Every symbol must lie in the configured alphabet.

## Methods

Let $L$ be the sequence length.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of stored strings including duplicates. | $O(1)$ |
| `int distinct_size()` | Returns the number of distinct stored strings. | $O(1)$ |
| `bool empty()` | Returns whether no strings are stored. | $O(1)$ |
| `node_id root()` | Returns the root node handle. | $O(1)$ |
| `node_id find(sequence)` | Returns the node reached by an active path, or `null_node` if it is absent. | $O(L)$ |
| `const Node& node(node_id id)` | Returns a read-only view of a node. | $O(1)$ |
| `size_t node_count()` | Returns allocated nodes, including the root. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for approximately `n` nodes. | $O(K)$ |
| `void clear()` | Removes all strings. | $O(K)$ |
| `node_id insert(sequence, int multiplicity = 1)` | Inserts copies of `sequence` and returns its endpoint node handle. | $O(L)$ |
| `int count(sequence)` | Returns the sequence multiplicity. | $O(L)$ |
| `bool contains(sequence)` | Returns whether the sequence is stored. | $O(L)$ |
| `int prefix_count(prefix)` | Counts stored strings beginning with `prefix`, including duplicates. | $O(L)$ |
| `bool starts_with(prefix)` | Returns whether any stored string begins with `prefix`. | $O(L)$ |
| `bool erase_one(sequence)`, `bool erase(sequence)` | Erases one copy and reports success. | $O(L)$ |
| `int erase_all(sequence)` | Erases all copies and returns the number erased. | $O(L)$ |
| `void for_each_prefix(sequence, callback)` | Calls `callback(length, multiplicity)` for each stored string that is a prefix of `sequence`. | $O(L)$ |
| `int longest_prefix(sequence)` | Returns the longest stored prefix length, or `-1` if none exists. | $O(L)$ |

Here $K$ is the allocated node count. Erasing does not reclaim nodes; `clear`
releases all logical contents at once.

`node_id` is an integer handle and `null_node` is its invalid value. A `Node`
exposes `child`, `subtree_count`, and `terminal_count`. Node handles remain
valid across insertions and erasures, so they can also index user-owned
metadata. `clear()` invalidates every old handle except the root. References
returned by `node()` may be invalidated by insertion, `reserve()`, or `clear()`;
keep the handle rather than the reference.

The empty string is supported. When stored, it is reported by
`for_each_prefix` with length `0`, and `prefix_count("")` equals `size()`.

## Example

```cpp
#include "string/trie.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::string::Trie<> trie;
    trie.insert(std::string("app"));
    trie.insert(std::string("apple"));
    trie.insert(std::string("app"));

    std::cout << trie.count(std::string("app")) << "\n";       // 2
    std::cout << trie.prefix_count(std::string("app")) << "\n"; // 3
    std::cout << trie.longest_prefix(std::string("apples")) << "\n"; // 5
}
```
