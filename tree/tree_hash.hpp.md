---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/rooted_tree_isomorphism_classification.test.cpp
    title: verify/tree/rooted_tree_isomorphism_classification.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/tree_hash.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#line\
    \ 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n\
    #line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 11 \"tree/tree_hash.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\nusing TreeHashValue = std::array<std::uint64_t, 2>;\n\nclass TreeHasher\
    \ {\n   private:\n    static constexpr std::uint64_t mod = (std::uint64_t(1) <<\
    \ 61) - 1;\n    std::uint64_t _seed;\n\n    static std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n        x += 0x9e3779b97f4a7c15ULL;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n        return x ^ (x >>\
    \ 31);\n    }\n\n    static std::uint64_t mul_mod(std::uint64_t a, std::uint64_t\
    \ b) {\n        __uint128_t product = static_cast<__uint128_t>(a) * b;\n     \
    \   std::uint64_t result = std::uint64_t(product & mod) + std::uint64_t(product\
    \ >> 61);\n        if (mod <= result) result -= mod;\n        return result;\n\
    \    }\n\n    static std::uint64_t add_mod(std::uint64_t a, std::uint64_t b) {\n\
    \        std::uint64_t result = a + b;\n        if (mod <= result) result -= mod;\n\
    \        return result;\n    }\n\n    TreeHashValue salt(int height) const {\n\
    \        std::uint64_t x = static_cast<std::uint64_t>(height);\n        std::uint64_t\
    \ first = splitmix64(_seed ^ (x + 0x243f6a8885a308d3ULL));\n        std::uint64_t\
    \ second = splitmix64(_seed ^ (x + 0x13198a2e03707344ULL));\n        return {first\
    \ % (mod - 1) + 1, second % (mod - 1) + 1};\n    }\n\n    template <class T>\n\
    \    static std::vector<int> tree_centers(const m1une::graph::Graph<T>& g) {\n\
    \        int n = g.size();\n        if (n == 0) return {};\n\n        std::vector<int>\
    \ degree(n, 0);\n        std::vector<int> queue;\n        queue.reserve(n);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) {\n                if (!e.alive) continue;\n\
    \                degree[v]++;\n                active_arcs++;\n            }\n\
    \            if (degree[v] <= 1) queue.push_back(v);\n        }\n        assert(active_arcs\
    \ == 2LL * (n - 1));\n\n        std::vector<char> removed(n, false);\n       \
    \ int remaining = n;\n        int head = 0;\n        while (2 < remaining) {\n\
    \            int layer_end = int(queue.size());\n            assert(head < layer_end);\n\
    \            remaining -= layer_end - head;\n            while (head < layer_end)\
    \ {\n                int v = queue[head++];\n                removed[v] = true;\n\
    \                for (const auto& e : g[v]) {\n                    if (!e.alive\
    \ || removed[e.to]) continue;\n                    if (--degree[e.to] == 1) queue.push_back(e.to);\n\
    \                }\n            }\n        }\n\n        std::vector<int> centers;\n\
    \        for (int v = 0; v < n; v++) {\n            if (!removed[v]) centers.push_back(v);\n\
    \        }\n        assert(1 <= int(centers.size()) && int(centers.size()) <=\
    \ 2);\n        return centers;\n    }\n\n   public:\n    explicit TreeHasher(std::uint64_t\
    \ seed = 0x6a09e667f3bcc909ULL) : _seed(seed) {}\n\n    std::uint64_t seed() const\
    \ {\n        return _seed;\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_subtrees(const m1une::graph::Graph<T>& g, int root = 0) const {\n     \
    \   int n = g.size();\n        if (n == 0) return {};\n        assert(0 <= root\
    \ && root < n);\n\n        std::vector<int> parent(n, -1);\n        std::vector<int>\
    \ order;\n        order.reserve(n);\n        parent[root] = root;\n        order.push_back(root);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) active_arcs += e.alive;\n        }\n  \
    \      assert(active_arcs == 2LL * (n - 1));\n\n        for (int i = 0; i < int(order.size());\
    \ i++) {\n            int v = order[i];\n            for (const auto& e : g[v])\
    \ {\n                if (!e.alive || parent[e.to] != -1) continue;\n         \
    \       parent[e.to] = v;\n                order.push_back(e.to);\n          \
    \  }\n        }\n        assert(int(order.size()) == n);\n\n        std::vector<int>\
    \ height(n, 0);\n        std::vector<TreeHashValue> result(n, TreeHashValue{1,\
    \ 1});\n        for (int i = n - 1; i >= 0; i--) {\n            int v = order[i];\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                height[v] = std::max(height[v], height[e.to]\
    \ + 1);\n            }\n            TreeHashValue random = salt(height[v]);\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                result[v][0] = mul_mod(result[v][0], add_mod(result[e.to][0],\
    \ random[0]));\n                result[v][1] = mul_mod(result[v][1], add_mod(result[e.to][1],\
    \ random[1]));\n            }\n        }\n        return result;\n    }\n\n  \
    \  template <class T>\n    TreeHashValue hash_rooted(const m1une::graph::Graph<T>&\
    \ g, int root = 0) const {\n        if (g.empty()) return {0, 0};\n        return\
    \ hash_subtrees(g, root)[root];\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_unrooted(const m1une::graph::Graph<T>& g) const {\n        std::vector<int>\
    \ centers = tree_centers(g);\n        std::vector<TreeHashValue> result;\n   \
    \     result.reserve(centers.size());\n        for (int center : centers) result.push_back(hash_rooted(g,\
    \ center));\n        std::sort(result.begin(), result.end());\n        return\
    \ result;\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_TREE_HASH_HPP\n#define M1UNE_TREE_TREE_HASH_HPP 1\n\n\
    #include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstdint>\n\
    #include <vector>\n\n#include \"../graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\nusing TreeHashValue = std::array<std::uint64_t, 2>;\n\nclass TreeHasher\
    \ {\n   private:\n    static constexpr std::uint64_t mod = (std::uint64_t(1) <<\
    \ 61) - 1;\n    std::uint64_t _seed;\n\n    static std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n        x += 0x9e3779b97f4a7c15ULL;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n        return x ^ (x >>\
    \ 31);\n    }\n\n    static std::uint64_t mul_mod(std::uint64_t a, std::uint64_t\
    \ b) {\n        __uint128_t product = static_cast<__uint128_t>(a) * b;\n     \
    \   std::uint64_t result = std::uint64_t(product & mod) + std::uint64_t(product\
    \ >> 61);\n        if (mod <= result) result -= mod;\n        return result;\n\
    \    }\n\n    static std::uint64_t add_mod(std::uint64_t a, std::uint64_t b) {\n\
    \        std::uint64_t result = a + b;\n        if (mod <= result) result -= mod;\n\
    \        return result;\n    }\n\n    TreeHashValue salt(int height) const {\n\
    \        std::uint64_t x = static_cast<std::uint64_t>(height);\n        std::uint64_t\
    \ first = splitmix64(_seed ^ (x + 0x243f6a8885a308d3ULL));\n        std::uint64_t\
    \ second = splitmix64(_seed ^ (x + 0x13198a2e03707344ULL));\n        return {first\
    \ % (mod - 1) + 1, second % (mod - 1) + 1};\n    }\n\n    template <class T>\n\
    \    static std::vector<int> tree_centers(const m1une::graph::Graph<T>& g) {\n\
    \        int n = g.size();\n        if (n == 0) return {};\n\n        std::vector<int>\
    \ degree(n, 0);\n        std::vector<int> queue;\n        queue.reserve(n);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) {\n                if (!e.alive) continue;\n\
    \                degree[v]++;\n                active_arcs++;\n            }\n\
    \            if (degree[v] <= 1) queue.push_back(v);\n        }\n        assert(active_arcs\
    \ == 2LL * (n - 1));\n\n        std::vector<char> removed(n, false);\n       \
    \ int remaining = n;\n        int head = 0;\n        while (2 < remaining) {\n\
    \            int layer_end = int(queue.size());\n            assert(head < layer_end);\n\
    \            remaining -= layer_end - head;\n            while (head < layer_end)\
    \ {\n                int v = queue[head++];\n                removed[v] = true;\n\
    \                for (const auto& e : g[v]) {\n                    if (!e.alive\
    \ || removed[e.to]) continue;\n                    if (--degree[e.to] == 1) queue.push_back(e.to);\n\
    \                }\n            }\n        }\n\n        std::vector<int> centers;\n\
    \        for (int v = 0; v < n; v++) {\n            if (!removed[v]) centers.push_back(v);\n\
    \        }\n        assert(1 <= int(centers.size()) && int(centers.size()) <=\
    \ 2);\n        return centers;\n    }\n\n   public:\n    explicit TreeHasher(std::uint64_t\
    \ seed = 0x6a09e667f3bcc909ULL) : _seed(seed) {}\n\n    std::uint64_t seed() const\
    \ {\n        return _seed;\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_subtrees(const m1une::graph::Graph<T>& g, int root = 0) const {\n     \
    \   int n = g.size();\n        if (n == 0) return {};\n        assert(0 <= root\
    \ && root < n);\n\n        std::vector<int> parent(n, -1);\n        std::vector<int>\
    \ order;\n        order.reserve(n);\n        parent[root] = root;\n        order.push_back(root);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) active_arcs += e.alive;\n        }\n  \
    \      assert(active_arcs == 2LL * (n - 1));\n\n        for (int i = 0; i < int(order.size());\
    \ i++) {\n            int v = order[i];\n            for (const auto& e : g[v])\
    \ {\n                if (!e.alive || parent[e.to] != -1) continue;\n         \
    \       parent[e.to] = v;\n                order.push_back(e.to);\n          \
    \  }\n        }\n        assert(int(order.size()) == n);\n\n        std::vector<int>\
    \ height(n, 0);\n        std::vector<TreeHashValue> result(n, TreeHashValue{1,\
    \ 1});\n        for (int i = n - 1; i >= 0; i--) {\n            int v = order[i];\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                height[v] = std::max(height[v], height[e.to]\
    \ + 1);\n            }\n            TreeHashValue random = salt(height[v]);\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                result[v][0] = mul_mod(result[v][0], add_mod(result[e.to][0],\
    \ random[0]));\n                result[v][1] = mul_mod(result[v][1], add_mod(result[e.to][1],\
    \ random[1]));\n            }\n        }\n        return result;\n    }\n\n  \
    \  template <class T>\n    TreeHashValue hash_rooted(const m1une::graph::Graph<T>&\
    \ g, int root = 0) const {\n        if (g.empty()) return {0, 0};\n        return\
    \ hash_subtrees(g, root)[root];\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_unrooted(const m1une::graph::Graph<T>& g) const {\n        std::vector<int>\
    \ centers = tree_centers(g);\n        std::vector<TreeHashValue> result;\n   \
    \     result.reserve(centers.size());\n        for (int center : centers) result.push_back(hash_rooted(g,\
    \ center));\n        std::sort(result.begin(), result.end());\n        return\
    \ result;\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_TREE_TREE_HASH_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/tree_hash.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-07-01 13:39:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/rooted_tree_isomorphism_classification.test.cpp
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/tree_hash.hpp
layout: document
title: Hash of Tree
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
