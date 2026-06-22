---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/ordered_set/binary_trie.test.cpp
    title: verify/ds/ordered_set/binary_trie.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/ordered_set/binary_trie.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <initializer_list>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename UInt\
    \ = std::uint32_t, int BitWidth = std::numeric_limits<UInt>::digits>\nstruct BinaryTrie\
    \ {\n    static_assert(std::is_integral_v<UInt>);\n    static_assert(std::is_unsigned_v<UInt>);\n\
    \    static_assert(!std::is_same_v<UInt, bool>);\n    static_assert(0 < BitWidth);\n\
    \    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\n    using\
    \ node_id = int;\n    static constexpr node_id null_node = -1;\n\n    struct Node\
    \ {\n        node_id child[2];\n        int count;\n\n        Node() : child{null_node,\
    \ null_node}, count(0) {}\n    };\n\n   private:\n    std::vector<Node> nodes;\n\
    \    UInt lazy_xor;\n\n    static constexpr int bit(UInt value, int position)\
    \ {\n        return int((value >> position) & UInt(1));\n    }\n\n    static constexpr\
    \ UInt value_mask() {\n        if constexpr (BitWidth == std::numeric_limits<UInt>::digits)\
    \ {\n            return std::numeric_limits<UInt>::max();\n        } else {\n\
    \            return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n   \
    \ static constexpr bool valid_value(UInt value) {\n        return (value & ~value_mask())\
    \ == UInt(0);\n    }\n\n    node_id new_node() {\n        nodes.emplace_back();\n\
    \        return int(nodes.size()) - 1;\n    }\n\n    int subtree_size(node_id\
    \ node) const {\n        return node == null_node ? 0 : nodes[node].count;\n \
    \   }\n\n    node_id find_node(UInt value) const {\n        node_id node = 0;\n\
    \        value ^= lazy_xor;\n        for (int position = BitWidth - 1; position\
    \ >= 0; --position) {\n            node = nodes[node].child[bit(value, position)];\n\
    \            if (node == null_node || nodes[node].count == 0) {\n            \
    \    return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    BinaryTrie() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrie(std::initializer_list<UInt>\
    \ init) : BinaryTrie() {\n        for (UInt value : init) insert(value);\n   \
    \ }\n\n    template <typename Iterator>\n    BinaryTrie(Iterator first, Iterator\
    \ last) : BinaryTrie() {\n        while (first != last) {\n            insert(*first);\n\
    \            ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ nodes[0].count;\n    }\n\n    bool empty() const {\n        return size() ==\
    \ 0;\n    }\n\n    node_id root() const {\n        return 0;\n    }\n\n    const\
    \ Node& node(node_id id) const {\n        assert(0 <= id && std::size_t(id) <\
    \ nodes.size());\n        return nodes[id];\n    }\n\n    node_id find(UInt value)\
    \ const {\n        assert(valid_value(value));\n        return find_node(value);\n\
    \    }\n\n    std::size_t node_count() const {\n        return nodes.size();\n\
    \    }\n\n    void reserve(std::size_t node_capacity) {\n        nodes.reserve(node_capacity);\n\
    \    }\n\n    UInt xor_mask() const {\n        return lazy_xor;\n    }\n\n   \
    \ void clear() {\n        nodes.clear();\n        nodes.emplace_back();\n    \
    \    lazy_xor = 0;\n    }\n\n    node_id insert(UInt value, int multiplicity =\
    \ 1) {\n        assert(valid_value(value));\n        assert(multiplicity > 0);\n\
    \        value ^= lazy_xor;\n        node_id node = 0;\n        nodes[node].count\
    \ += multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            const int direction = bit(value, position);\n            if (nodes[node].child[direction]\
    \ == null_node) {\n                const node_id child = new_node();\n       \
    \         nodes[node].child[direction] = child;\n            }\n            node\
    \ = nodes[node].child[direction];\n            nodes[node].count += multiplicity;\n\
    \        }\n        return node;\n    }\n\n    int count(UInt value) const {\n\
    \        assert(valid_value(value));\n        const node_id node = find_node(value);\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    bool\
    \ contains(UInt value) const {\n        return count(value) > 0;\n    }\n\n  \
    \  bool erase_one(UInt value) {\n        assert(valid_value(value));\n       \
    \ if (!contains(value)) return false;\n        value ^= lazy_xor;\n        int\
    \ node = 0;\n        --nodes[node].count;\n        for (int position = BitWidth\
    \ - 1; position >= 0; --position) {\n            node = nodes[node].child[bit(value,\
    \ position)];\n            --nodes[node].count;\n        }\n        return true;\n\
    \    }\n\n    bool erase(UInt value) {\n        return erase_one(value);\n   \
    \ }\n\n    int erase_all(UInt value) {\n        assert(valid_value(value));\n\
    \        const int multiplicity = count(value);\n        if (multiplicity == 0)\
    \ return 0;\n        value ^= lazy_xor;\n        int node = 0;\n        nodes[node].count\
    \ -= multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            node = nodes[node].child[bit(value, position)];\n           \
    \ nodes[node].count -= multiplicity;\n        }\n        return multiplicity;\n\
    \    }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n\
    \        lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size = subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_less_xor(UInt value, UInt upper) const\
    \ {\n        assert(valid_value(value));\n        if (!valid_value(upper)) return\
    \ size();\n        const UInt effective_xor = lazy_xor ^ value;\n        int result\
    \ = 0;\n        int node = 0;\n        for (int position = BitWidth - 1; position\
    \ >= 0 && node != -1; --position) {\n            const int zero = bit(effective_xor,\
    \ position);\n            if (bit(upper, position) == 1) {\n                result\
    \ += subtree_size(nodes[node].child[zero]);\n                node = nodes[node].child[zero\
    \ ^ 1];\n            } else {\n                node = nodes[node].child[zero];\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_xor_less(UInt\
    \ value, UInt upper) const {\n        return count_less_xor(value, upper);\n \
    \   }\n\n    int count_xor_less_equal(UInt value, UInt upper) const {\n      \
    \  assert(valid_value(value));\n        assert(valid_value(upper));\n        if\
    \ (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ value) const {\n        return count_less_xor(0, value);\n    }\n\n    int count_less(UInt\
    \ value) const {\n        return order_of_key(value);\n    }\n\n    int count_less_equal(UInt\
    \ value) const {\n        assert(valid_value(value));\n        if (value == value_mask())\
    \ return size();\n        return count_less(value + UInt(1));\n    }\n\n    int\
    \ count_greater(UInt value) const {\n        return size() - count_less_equal(value);\n\
    \    }\n\n    int count_greater_equal(UInt value) const {\n        return size()\
    \ - count_less(value);\n    }\n\n    std::vector<UInt> to_vector() const {\n \
    \       std::vector<UInt> result;\n        result.reserve(size());\n        for\
    \ (int k = 0; k < size(); ++k) {\n            result.push_back(kth(k));\n    \
    \    }\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_BINARY_TRIE_HPP\n#define M1UNE_DS_BINARY_TRIE_HPP 1\n\n\
    #include <cassert>\n#include <cstdint>\n#include <initializer_list>\n#include\
    \ <limits>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <typename UInt = std::uint32_t, int BitWidth = std::numeric_limits<UInt>::digits>\n\
    struct BinaryTrie {\n    static_assert(std::is_integral_v<UInt>);\n    static_assert(std::is_unsigned_v<UInt>);\n\
    \    static_assert(!std::is_same_v<UInt, bool>);\n    static_assert(0 < BitWidth);\n\
    \    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\n    using\
    \ node_id = int;\n    static constexpr node_id null_node = -1;\n\n    struct Node\
    \ {\n        node_id child[2];\n        int count;\n\n        Node() : child{null_node,\
    \ null_node}, count(0) {}\n    };\n\n   private:\n    std::vector<Node> nodes;\n\
    \    UInt lazy_xor;\n\n    static constexpr int bit(UInt value, int position)\
    \ {\n        return int((value >> position) & UInt(1));\n    }\n\n    static constexpr\
    \ UInt value_mask() {\n        if constexpr (BitWidth == std::numeric_limits<UInt>::digits)\
    \ {\n            return std::numeric_limits<UInt>::max();\n        } else {\n\
    \            return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n   \
    \ static constexpr bool valid_value(UInt value) {\n        return (value & ~value_mask())\
    \ == UInt(0);\n    }\n\n    node_id new_node() {\n        nodes.emplace_back();\n\
    \        return int(nodes.size()) - 1;\n    }\n\n    int subtree_size(node_id\
    \ node) const {\n        return node == null_node ? 0 : nodes[node].count;\n \
    \   }\n\n    node_id find_node(UInt value) const {\n        node_id node = 0;\n\
    \        value ^= lazy_xor;\n        for (int position = BitWidth - 1; position\
    \ >= 0; --position) {\n            node = nodes[node].child[bit(value, position)];\n\
    \            if (node == null_node || nodes[node].count == 0) {\n            \
    \    return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    BinaryTrie() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrie(std::initializer_list<UInt>\
    \ init) : BinaryTrie() {\n        for (UInt value : init) insert(value);\n   \
    \ }\n\n    template <typename Iterator>\n    BinaryTrie(Iterator first, Iterator\
    \ last) : BinaryTrie() {\n        while (first != last) {\n            insert(*first);\n\
    \            ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ nodes[0].count;\n    }\n\n    bool empty() const {\n        return size() ==\
    \ 0;\n    }\n\n    node_id root() const {\n        return 0;\n    }\n\n    const\
    \ Node& node(node_id id) const {\n        assert(0 <= id && std::size_t(id) <\
    \ nodes.size());\n        return nodes[id];\n    }\n\n    node_id find(UInt value)\
    \ const {\n        assert(valid_value(value));\n        return find_node(value);\n\
    \    }\n\n    std::size_t node_count() const {\n        return nodes.size();\n\
    \    }\n\n    void reserve(std::size_t node_capacity) {\n        nodes.reserve(node_capacity);\n\
    \    }\n\n    UInt xor_mask() const {\n        return lazy_xor;\n    }\n\n   \
    \ void clear() {\n        nodes.clear();\n        nodes.emplace_back();\n    \
    \    lazy_xor = 0;\n    }\n\n    node_id insert(UInt value, int multiplicity =\
    \ 1) {\n        assert(valid_value(value));\n        assert(multiplicity > 0);\n\
    \        value ^= lazy_xor;\n        node_id node = 0;\n        nodes[node].count\
    \ += multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            const int direction = bit(value, position);\n            if (nodes[node].child[direction]\
    \ == null_node) {\n                const node_id child = new_node();\n       \
    \         nodes[node].child[direction] = child;\n            }\n            node\
    \ = nodes[node].child[direction];\n            nodes[node].count += multiplicity;\n\
    \        }\n        return node;\n    }\n\n    int count(UInt value) const {\n\
    \        assert(valid_value(value));\n        const node_id node = find_node(value);\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    bool\
    \ contains(UInt value) const {\n        return count(value) > 0;\n    }\n\n  \
    \  bool erase_one(UInt value) {\n        assert(valid_value(value));\n       \
    \ if (!contains(value)) return false;\n        value ^= lazy_xor;\n        int\
    \ node = 0;\n        --nodes[node].count;\n        for (int position = BitWidth\
    \ - 1; position >= 0; --position) {\n            node = nodes[node].child[bit(value,\
    \ position)];\n            --nodes[node].count;\n        }\n        return true;\n\
    \    }\n\n    bool erase(UInt value) {\n        return erase_one(value);\n   \
    \ }\n\n    int erase_all(UInt value) {\n        assert(valid_value(value));\n\
    \        const int multiplicity = count(value);\n        if (multiplicity == 0)\
    \ return 0;\n        value ^= lazy_xor;\n        int node = 0;\n        nodes[node].count\
    \ -= multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            node = nodes[node].child[bit(value, position)];\n           \
    \ nodes[node].count -= multiplicity;\n        }\n        return multiplicity;\n\
    \    }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n\
    \        lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size = subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_less_xor(UInt value, UInt upper) const\
    \ {\n        assert(valid_value(value));\n        if (!valid_value(upper)) return\
    \ size();\n        const UInt effective_xor = lazy_xor ^ value;\n        int result\
    \ = 0;\n        int node = 0;\n        for (int position = BitWidth - 1; position\
    \ >= 0 && node != -1; --position) {\n            const int zero = bit(effective_xor,\
    \ position);\n            if (bit(upper, position) == 1) {\n                result\
    \ += subtree_size(nodes[node].child[zero]);\n                node = nodes[node].child[zero\
    \ ^ 1];\n            } else {\n                node = nodes[node].child[zero];\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_xor_less(UInt\
    \ value, UInt upper) const {\n        return count_less_xor(value, upper);\n \
    \   }\n\n    int count_xor_less_equal(UInt value, UInt upper) const {\n      \
    \  assert(valid_value(value));\n        assert(valid_value(upper));\n        if\
    \ (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ value) const {\n        return count_less_xor(0, value);\n    }\n\n    int count_less(UInt\
    \ value) const {\n        return order_of_key(value);\n    }\n\n    int count_less_equal(UInt\
    \ value) const {\n        assert(valid_value(value));\n        if (value == value_mask())\
    \ return size();\n        return count_less(value + UInt(1));\n    }\n\n    int\
    \ count_greater(UInt value) const {\n        return size() - count_less_equal(value);\n\
    \    }\n\n    int count_greater_equal(UInt value) const {\n        return size()\
    \ - count_less(value);\n    }\n\n    std::vector<UInt> to_vector() const {\n \
    \       std::vector<UInt> result;\n        result.reserve(size());\n        for\
    \ (int k = 0; k < size(); ++k) {\n            result.push_back(kth(k));\n    \
    \    }\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_DS_BINARY_TRIE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/ordered_set/binary_trie.hpp
  requiredBy: []
  timestamp: '2026-06-22 15:33:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/ordered_set/binary_trie.test.cpp
documentation_of: ds/ordered_set/binary_trie.hpp
layout: document
title: Binary Trie
---

## Overview

`BinaryTrie` is a multiset of unsigned integers represented by their binary
digits. It supports insertion, deletion, order statistics, and minimum or
maximum xor queries in time proportional to the configured bit width.

Duplicate values are stored separately. `xor_all(value)` lazily applies xor to
every value already in the trie.

## Template Parameters

* `UInt`: An unsigned integer type. Defaults to `std::uint32_t`.
* `BitWidth`: The number of low bits used by the trie. Defaults to all bits of
  `UInt`. Every inserted value and xor operand must fit in these bits.

An exclusive `upper` bound may be larger than the largest representable
`BitWidth`-bit value when that bound fits in `UInt`. For example, with
`BitWidth == 30`, passing `1U << 30` includes every possible value.

## Methods

Let $B$ be `BitWidth`.

| Method | Description | Complexity |
| --- | --- | --- |
| `BinaryTrie()` | Constructs an empty trie. | $O(1)$ |
| `BinaryTrie(std::initializer_list<UInt> init)` | Constructs a trie containing `init`. | $O(NB)$ |
| `BinaryTrie(Iterator first, Iterator last)` | Constructs a trie from a range. | $O(NB)$ |
| `int size() const` | Returns the number of values, including duplicates. | $O(1)$ |
| `bool empty() const` | Returns whether the trie is empty. | $O(1)$ |
| `node_id root() const` | Returns the root node handle. | $O(1)$ |
| `node_id find(UInt value) const` | Returns the leaf handle for `value`, or `null_node` if absent. | $O(B)$ |
| `const Node& node(node_id id) const` | Returns a read-only view of a node. | $O(1)$ |
| `size_t node_count() const` | Returns allocated nodes, including the root. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for approximately `n` nodes. | $O(K)$ |
| `UInt xor_mask() const` | Returns the current lazy xor mask. | $O(1)$ |
| `void clear()` | Removes every value and resets the lazy xor. | $O(1)$ |
| `node_id insert(UInt value, int multiplicity = 1)` | Inserts copies of `value` and returns its leaf handle. | $O(B)$ |
| `bool erase_one(UInt value)`, `bool erase(UInt value)` | Removes one copy and returns whether one existed. | $O(B)$ |
| `int erase_all(UInt value)` | Removes every copy and returns the number removed. | $O(B)$ |
| `int count(UInt value) const` | Returns the multiplicity of `value`. | $O(B)$ |
| `bool contains(UInt value) const` | Returns whether `value` exists. | $O(B)$ |
| `void xor_all(UInt value)` | Applies xor with `value` to every stored value. | $O(1)$ |
| `UInt kth(int k) const` | Returns the 0-indexed `k`-th smallest stored value. | $O(B)$ |
| `UInt min() const`, `UInt max() const` | Returns the smallest or largest value. Requires a nonempty trie. | $O(B)$ |
| `UInt kth_xor(int k, UInt value) const` | Returns the 0-indexed `k`-th smallest result among `stored_value ^ value`. | $O(B)$ |
| `UInt min_xor(UInt value) const`, `UInt max_xor(UInt value) const` | Returns the minimum or maximum result among `stored_value ^ value`. Requires a nonempty trie. | $O(B)$ |
| `int order_of_key(UInt value) const`, `int count_less(UInt value) const` | Returns the number of stored values strictly less than `value`. | $O(B)$ |
| `int count_less_equal(UInt value) const` | Returns the number of stored values less than or equal to `value`. | $O(B)$ |
| `int count_greater(UInt value) const` | Returns the number of stored values strictly greater than `value`. | $O(B)$ |
| `int count_greater_equal(UInt value) const` | Returns the number of stored values greater than or equal to `value`. | $O(B)$ |
| `int count_xor_less(UInt value, UInt upper) const` | Counts stored values for which `(stored_value ^ value) < upper`. | $O(B)$ |
| `int count_xor_less_equal(UInt value, UInt upper) const` | Counts stored values for which `(stored_value ^ value) <= upper`. | $O(B)$ |
| `int count_xor_greater(UInt value, UInt lower) const` | Counts stored values for which `(stored_value ^ value) > lower`. | $O(B)$ |
| `int count_xor_greater_equal(UInt value, UInt lower) const` | Counts stored values for which `(stored_value ^ value) >= lower`. | $O(B)$ |
| `int count_xor_range(UInt value, UInt lower, UInt upper) const` | Counts stored values for which `lower <= (stored_value ^ value) < upper`. | $O(B)$ |
| `std::vector<UInt> to_vector() const` | Returns all values in sorted order, including duplicates. | $O(NB)$ |

`count_less_xor(value, upper)` is a compatibility alias for
`count_xor_less(value, upper)`.

`node_id` is an integer handle and `null_node` is its invalid value. A `Node`
exposes `child[2]` and `count`. Handles remain valid across insertions and
erasures and can index user-owned metadata; `clear()` invalidates every old
handle except the root. References returned by `node()` may be invalidated by
insertion, `reserve()`, or `clear()`.

The child links describe the physically stored bit paths. After `xor_all`,
logical values differ by `xor_mask()`; `find(value)` accounts for this mask
automatically.

Here $K$ is the allocated node count. Erasing does not reclaim nodes.

## Example

```cpp
#include "ds/ordered_set/binary_trie.hpp"

#include <cstdint>
#include <iostream>

int main() {
    m1une::ds::BinaryTrie<std::uint32_t, 20> trie;
    trie.insert(2);
    trie.insert(7);
    trie.insert(7);

    std::cout << trie.min_xor(5) << "\n";  // min(2 ^ 5, 7 ^ 5) = 2
    std::cout << trie.kth(1) << "\n";      // 7

    trie.xor_all(3);
    std::cout << trie.min() << "\n";       // min(2 ^ 3, 7 ^ 3) = 1
    std::cout << trie.count(4) << "\n";    // 2
}
```
