---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/maximum_clique.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.push_back({{from, idx}});\n        return\
    \ id;\n    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.push_back({{u, u_idx}, {v, v_idx}});\n\
    \        return id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n\
    \        assert(0 <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
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
    \ m1une\n\n\n#line 9 \"graph/maximum_clique.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct MaximumCliqueResult {\n    std::vector<int> vertices;\n\n\
    \    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MaximumIndependentSetResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nnamespace detail {\n\nstruct MaximumCliqueBranchAndBound {\n   \
    \ using Word = unsigned long long;\n\n    int n;\n    int word_count;\n    std::vector<std::vector<Word>>\
    \ adjacent;\n    std::vector<int> current;\n    std::vector<int> best;\n\n   \
    \ explicit MaximumCliqueBranchAndBound(int n_)\n        : n(n_), word_count((n_\
    \ + 63) / 64), adjacent(n_, std::vector<Word>(word_count, Word(0))) {}\n\n   \
    \ static int lowbit_index(Word x) {\n        return __builtin_ctzll(x);\n    }\n\
    \n    bool empty_bits(const std::vector<Word>& bits) const {\n        for (Word\
    \ x : bits) {\n            if (x != Word(0)) return false;\n        }\n      \
    \  return true;\n    }\n\n    int first_vertex(const std::vector<Word>& bits)\
    \ const {\n        for (int i = 0; i < word_count; i++) {\n            if (bits[i]\
    \ != Word(0)) return i * 64 + lowbit_index(bits[i]);\n        }\n        return\
    \ -1;\n    }\n\n    void set_bit(std::vector<Word>& bits, int v) const {\n   \
    \     bits[v >> 6] |= Word(1) << (v & 63);\n    }\n\n    void clear_bit(std::vector<Word>&\
    \ bits, int v) const {\n        bits[v >> 6] &= ~(Word(1) << (v & 63));\n    }\n\
    \n    bool test_bit(const std::vector<Word>& bits, int v) const {\n        return\
    \ (bits[v >> 6] >> (v & 63)) & Word(1);\n    }\n\n    void add_edge(int u, int\
    \ v) {\n        assert(0 <= u && u < n);\n        assert(0 <= v && v < n);\n \
    \       assert(u != v);\n        adjacent[u][v >> 6] |= Word(1) << (v & 63);\n\
    \        adjacent[v][u >> 6] |= Word(1) << (u & 63);\n    }\n\n    std::vector<Word>\
    \ intersect(const std::vector<Word>& a, const std::vector<Word>& b) const {\n\
    \        std::vector<Word> result(word_count);\n        for (int i = 0; i < word_count;\
    \ i++) result[i] = a[i] & b[i];\n        return result;\n    }\n\n    void greedy_color(const\
    \ std::vector<Word>& candidates, std::vector<int>& order, std::vector<int>& color)\
    \ const {\n        order.clear();\n        color.clear();\n\n        std::vector<Word>\
    \ remaining = candidates;\n        int color_count = 0;\n        while (!empty_bits(remaining))\
    \ {\n            color_count++;\n            std::vector<Word> available = remaining;\n\
    \            while (!empty_bits(available)) {\n                int v = first_vertex(available);\n\
    \                order.push_back(v);\n                color.push_back(color_count);\n\
    \n                clear_bit(remaining, v);\n                clear_bit(available,\
    \ v);\n                for (int i = 0; i < word_count; i++) available[i] &= ~adjacent[v][i];\n\
    \            }\n        }\n    }\n\n    void expand(std::vector<Word> candidates)\
    \ {\n        if (empty_bits(candidates)) {\n            if (current.size() > best.size())\
    \ best = current;\n            return;\n        }\n\n        std::vector<int>\
    \ order, color;\n        greedy_color(candidates, order, color);\n\n        for\
    \ (int i = int(order.size()) - 1; i >= 0; i--) {\n            if (int(current.size())\
    \ + color[i] <= int(best.size())) return;\n\n            int v = order[i];\n \
    \           if (!test_bit(candidates, v)) continue;\n\n            current.push_back(v);\n\
    \            auto next = intersect(candidates, adjacent[v]);\n            expand(next);\n\
    \            current.pop_back();\n\n            clear_bit(candidates, v);\n  \
    \      }\n    }\n\n    std::vector<int> solve() {\n        std::vector<Word> candidates(word_count,\
    \ Word(0));\n        for (int v = 0; v < n; v++) set_bit(candidates, v);\n   \
    \     expand(candidates);\n        std::sort(best.begin(), best.end());\n    \
    \    return best;\n    }\n};\n\ntemplate <class T>\nstd::vector<std::vector<char>>\
    \ undirected_adjacency_matrix(const Graph<T>& g) {\n    int n = g.size();\n  \
    \  std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));\n\
    \    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        adjacent[e.from][e.to] = true;\n        adjacent[e.to][e.from] = true;\n\
    \    }\n    return adjacent;\n}\n\n}  // namespace detail\n\ntemplate <class T>\n\
    bool is_clique(const Graph<T>& g, const std::vector<int>& vertices) {\n    auto\
    \ adjacent = detail::undirected_adjacency_matrix(g);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n    }\n    for (int i = 0; i < int(vertices.size());\
    \ i++) {\n        for (int j = i + 1; j < int(vertices.size()); j++) {\n     \
    \       if (!adjacent[vertices[i]][vertices[j]]) return false;\n        }\n  \
    \  }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    MaximumCliqueResult maximum_clique(const Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumCliqueBranchAndBound solver(g.size());\n    for (int i = 0;\
    \ i < g.size(); i++) {\n        for (int j = i + 1; j < g.size(); j++) {\n   \
    \         if (adjacent[i][j]) solver.add_edge(i, j);\n        }\n    }\n    return\
    \ MaximumCliqueResult{solver.solve()};\n}\n\ntemplate <class T>\nint maximum_clique_size(const\
    \ Graph<T>& g) {\n    return maximum_clique(g).size();\n}\n\ntemplate <class T>\n\
    MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g) {\n   \
    \ auto adjacent = detail::undirected_adjacency_matrix(g);\n    detail::MaximumCliqueBranchAndBound\
    \ solver(g.size());\n    for (int i = 0; i < g.size(); i++) {\n        for (int\
    \ j = i + 1; j < g.size(); j++) {\n            if (!adjacent[i][j]) solver.add_edge(i,\
    \ j);\n        }\n    }\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\n}  // namespace graph\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\n#define M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include\
    \ \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct MaximumCliqueResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nstruct MaximumIndependentSetResult {\n    std::vector<int> vertices;\n\
    \n    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nnamespace detail\
    \ {\n\nstruct MaximumCliqueBranchAndBound {\n    using Word = unsigned long long;\n\
    \n    int n;\n    int word_count;\n    std::vector<std::vector<Word>> adjacent;\n\
    \    std::vector<int> current;\n    std::vector<int> best;\n\n    explicit MaximumCliqueBranchAndBound(int\
    \ n_)\n        : n(n_), word_count((n_ + 63) / 64), adjacent(n_, std::vector<Word>(word_count,\
    \ Word(0))) {}\n\n    static int lowbit_index(Word x) {\n        return __builtin_ctzll(x);\n\
    \    }\n\n    bool empty_bits(const std::vector<Word>& bits) const {\n       \
    \ for (Word x : bits) {\n            if (x != Word(0)) return false;\n       \
    \ }\n        return true;\n    }\n\n    int first_vertex(const std::vector<Word>&\
    \ bits) const {\n        for (int i = 0; i < word_count; i++) {\n            if\
    \ (bits[i] != Word(0)) return i * 64 + lowbit_index(bits[i]);\n        }\n   \
    \     return -1;\n    }\n\n    void set_bit(std::vector<Word>& bits, int v) const\
    \ {\n        bits[v >> 6] |= Word(1) << (v & 63);\n    }\n\n    void clear_bit(std::vector<Word>&\
    \ bits, int v) const {\n        bits[v >> 6] &= ~(Word(1) << (v & 63));\n    }\n\
    \n    bool test_bit(const std::vector<Word>& bits, int v) const {\n        return\
    \ (bits[v >> 6] >> (v & 63)) & Word(1);\n    }\n\n    void add_edge(int u, int\
    \ v) {\n        assert(0 <= u && u < n);\n        assert(0 <= v && v < n);\n \
    \       assert(u != v);\n        adjacent[u][v >> 6] |= Word(1) << (v & 63);\n\
    \        adjacent[v][u >> 6] |= Word(1) << (u & 63);\n    }\n\n    std::vector<Word>\
    \ intersect(const std::vector<Word>& a, const std::vector<Word>& b) const {\n\
    \        std::vector<Word> result(word_count);\n        for (int i = 0; i < word_count;\
    \ i++) result[i] = a[i] & b[i];\n        return result;\n    }\n\n    void greedy_color(const\
    \ std::vector<Word>& candidates, std::vector<int>& order, std::vector<int>& color)\
    \ const {\n        order.clear();\n        color.clear();\n\n        std::vector<Word>\
    \ remaining = candidates;\n        int color_count = 0;\n        while (!empty_bits(remaining))\
    \ {\n            color_count++;\n            std::vector<Word> available = remaining;\n\
    \            while (!empty_bits(available)) {\n                int v = first_vertex(available);\n\
    \                order.push_back(v);\n                color.push_back(color_count);\n\
    \n                clear_bit(remaining, v);\n                clear_bit(available,\
    \ v);\n                for (int i = 0; i < word_count; i++) available[i] &= ~adjacent[v][i];\n\
    \            }\n        }\n    }\n\n    void expand(std::vector<Word> candidates)\
    \ {\n        if (empty_bits(candidates)) {\n            if (current.size() > best.size())\
    \ best = current;\n            return;\n        }\n\n        std::vector<int>\
    \ order, color;\n        greedy_color(candidates, order, color);\n\n        for\
    \ (int i = int(order.size()) - 1; i >= 0; i--) {\n            if (int(current.size())\
    \ + color[i] <= int(best.size())) return;\n\n            int v = order[i];\n \
    \           if (!test_bit(candidates, v)) continue;\n\n            current.push_back(v);\n\
    \            auto next = intersect(candidates, adjacent[v]);\n            expand(next);\n\
    \            current.pop_back();\n\n            clear_bit(candidates, v);\n  \
    \      }\n    }\n\n    std::vector<int> solve() {\n        std::vector<Word> candidates(word_count,\
    \ Word(0));\n        for (int v = 0; v < n; v++) set_bit(candidates, v);\n   \
    \     expand(candidates);\n        std::sort(best.begin(), best.end());\n    \
    \    return best;\n    }\n};\n\ntemplate <class T>\nstd::vector<std::vector<char>>\
    \ undirected_adjacency_matrix(const Graph<T>& g) {\n    int n = g.size();\n  \
    \  std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));\n\
    \    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        adjacent[e.from][e.to] = true;\n        adjacent[e.to][e.from] = true;\n\
    \    }\n    return adjacent;\n}\n\n}  // namespace detail\n\ntemplate <class T>\n\
    bool is_clique(const Graph<T>& g, const std::vector<int>& vertices) {\n    auto\
    \ adjacent = detail::undirected_adjacency_matrix(g);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n    }\n    for (int i = 0; i < int(vertices.size());\
    \ i++) {\n        for (int j = i + 1; j < int(vertices.size()); j++) {\n     \
    \       if (!adjacent[vertices[i]][vertices[j]]) return false;\n        }\n  \
    \  }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    MaximumCliqueResult maximum_clique(const Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumCliqueBranchAndBound solver(g.size());\n    for (int i = 0;\
    \ i < g.size(); i++) {\n        for (int j = i + 1; j < g.size(); j++) {\n   \
    \         if (adjacent[i][j]) solver.add_edge(i, j);\n        }\n    }\n    return\
    \ MaximumCliqueResult{solver.solve()};\n}\n\ntemplate <class T>\nint maximum_clique_size(const\
    \ Graph<T>& g) {\n    return maximum_clique(g).size();\n}\n\ntemplate <class T>\n\
    MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g) {\n   \
    \ auto adjacent = detail::undirected_adjacency_matrix(g);\n    detail::MaximumCliqueBranchAndBound\
    \ solver(g.size());\n    for (int i = 0; i < g.size(); i++) {\n        for (int\
    \ j = i + 1; j < g.size(); j++) {\n            if (!adjacent[i][j]) solver.add_edge(i,\
    \ j);\n        }\n    }\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\n}  // namespace graph\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/maximum_clique.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-16 03:14:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/maximum_clique.hpp
layout: document
title: Maximum Clique and Independent Set
---

## Overview

This header solves two exact NP-hard problems on general undirected graphs:

* maximum clique;
* maximum independent set.

A clique is a vertex set where every pair of vertices has an edge. An
independent set is a vertex set where no pair of vertices has an edge.

These problems are still exponential in the worst case. The implementation is
not a naive `2^N` subset scan: it uses a bitset branch-and-bound maximum clique
solver with greedy coloring as an upper bound. The maximum independent set is
computed as a maximum clique in the complement graph.

## Graph Orientation

Direction is ignored. Every active edge of `Graph<T>` is treated as an
undirected edge between its endpoints. Self-loops are ignored because they do
not help a clique or an independent set.

## How It Works

The maximum clique solver keeps a current clique and a candidate set. At each
recursive step, it greedily colors the candidate subgraph. A clique can contain
at most one vertex from each color class, so the number of colors is an upper
bound on how much the current clique can still grow. If that upper bound cannot
beat the best answer, the branch is skipped.

Candidate sets and adjacency are stored as machine-word bitsets, so
intersection with a neighborhood is fast.

For maximum independent set, the solver builds the complement graph: two
vertices are connected in the complement exactly when they are not connected in
the original graph. A clique in the complement is an independent set in the
original graph.

## Result Types

`MaximumCliqueResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum clique. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

`MaximumIndependentSetResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum independent set. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

Returned vertices are sorted in increasing order.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `maximum_clique` | `template <class T> MaximumCliqueResult maximum_clique(const Graph<T>& g)` | Returns one maximum clique. | Exponential worst case |
| `maximum_clique_size` | `template <class T> int maximum_clique_size(const Graph<T>& g)` | Returns the size of a maximum clique. | Exponential worst case |
| `maximum_independent_set` | `template <class T> MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g)` | Returns one maximum independent set. | Exponential worst case |
| `maximum_independent_set_size` | `template <class T> int maximum_independent_set_size(const Graph<T>& g)` | Returns the size of a maximum independent set. | Exponential worst case |
| `is_clique` | `template <class T> bool is_clique(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a clique. | $O(N+M+K^2)$ |
| `is_independent_set` | `template <class T> bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is an independent set. | $O(N+M+K^2)$ |

Here, `K = vertices.size()`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/maximum_clique.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    auto clique = m1une::graph::maximum_clique(g);
    auto independent = m1une::graph::maximum_independent_set(g);

    std::cout << clique.size() << "\n";       // 3
    std::cout << independent.size() << "\n";  // 2
}
```
