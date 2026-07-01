---
title: Hash of Tree
documentation_of: ../../tree/tree_hash.hpp
---

## Overview

`m1une::tree::TreeHasher` computes order-independent structural hashes of a
tree. It can hash every rooted subtree, one whole rooted tree, or an unrooted
tree using its one or two centers.

The implementation is iterative and uses two independent coordinates modulo
$2^{61}-1$. Equal rooted trees always receive equal values when the same seed
is used. Different trees can collide with very small probability, so this is
suited to contest algorithms rather than cryptographic use.

The input must be a connected undirected tree built with
`m1une::graph::Graph<T>::add_edge`. Inactive edges are ignored, and edge costs
do not affect the hash.

## Types

| Type | Definition | Description |
| --- | --- | --- |
| `TreeHashValue` | `std::array<std::uint64_t, 2>` | A comparable double hash. |
| `TreeHasher` | Class | Holds the seed used to generate height salts. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `TreeHasher(std::uint64_t seed = ...)` | Creates a hasher. Use the same seed for comparable results. | $O(1)$ |
| `std::uint64_t seed() const` | Returns the configured seed. | $O(1)$ |
| `std::vector<TreeHashValue> hash_subtrees(g, root = 0) const` | Returns the hash of every subtree after rooting `g` at `root`. | $O(N)$ |
| `TreeHashValue hash_rooted(g, root = 0) const` | Returns the hash of the whole tree rooted at `root`. For an empty graph, returns `{0, 0}`. | $O(N)$ |
| `std::vector<TreeHashValue> hash_unrooted(g) const` | Returns the sorted hashes at the tree center or two centers. For an empty graph, returns an empty vector. | $O(N)$ |

Every operation uses $O(N)$ temporary memory except the constructor and
`seed()`.

Two rooted subtrees are isomorphic with high probability exactly when their
`TreeHashValue`s compare equal. Two unrooted trees are isomorphic with high
probability exactly when the vectors returned by `hash_unrooted` compare equal.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/tree_hash.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);

    m1une::tree::TreeHasher hasher;
    auto hash = hasher.hash_subtrees(g, 0);
    std::cout << (hash[1] == hash[2]) << "\n"; // 1
}
```
