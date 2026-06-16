---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: flow/bounded_flow.hpp
    title: Bounded Flow
  - icon: ':heavy_check_mark:'
    path: flow/flow.hpp
    title: Flow
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/flow/flow_algorithms.test.cpp
    title: verify/flow/flow_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"flow/max_flow.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct\
    \ MaxFlow {\n    struct Edge {\n        int from;\n        int to;\n        Cap\
    \ cap;\n        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n\
    \        int to;\n        int rev;\n        Cap cap;\n    };\n\n    int _n;\n\
    \    std::vector<std::pair<int, int>> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n   public:\n    MaxFlow() : MaxFlow(0) {}\n\n    explicit MaxFlow(int\
    \ n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_pos.size());\n    }\n\n    int add_edge(int from, int to, Cap cap) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(Cap(0) <= cap);\n        int id = int(_pos.size());\n        int\
    \ from_id = int(_g[from].size());\n        int to_id = int(_g[to].size());\n \
    \       if (from == to) to_id++;\n        _pos.emplace_back(from, from_id);\n\
    \        _g[from].push_back(InternalEdge{to, to_id, cap});\n        _g[to].push_back(InternalEdge{from,\
    \ from_id, Cap(0)});\n        return id;\n    }\n\n    Edge get_edge(int i) const\
    \ {\n        assert(0 <= i && i < int(_pos.size()));\n        auto [from, idx]\
    \ = _pos[i];\n        const auto& e = _g[from][idx];\n        const auto& re =\
    \ _g[e.to][e.rev];\n        return Edge{from, e.to, e.cap + re.cap, re.cap};\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        std::vector<Edge> result;\n\
    \        result.reserve(_pos.size());\n        for (int i = 0; i < int(_pos.size());\
    \ i++) result.push_back(get_edge(i));\n        return result;\n    }\n\n    void\
    \ change_edge(int i, Cap new_cap, Cap new_flow) {\n        assert(0 <= i && i\
    \ < int(_pos.size()));\n        assert(Cap(0) <= new_flow && new_flow <= new_cap);\n\
    \        auto [from, idx] = _pos[i];\n        auto& e = _g[from][idx];\n     \
    \   auto& re = _g[e.to][e.rev];\n        e.cap = new_cap - new_flow;\n       \
    \ re.cap = new_flow;\n    }\n\n    Cap max_flow(int s, int t) {\n        return\
    \ max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\n    Cap max_flow(int\
    \ s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n        assert(0\
    \ <= t && t < _n);\n        assert(s != t);\n\n        std::vector<int> level(_n),\
    \ iter(_n);\n        auto bfs = [&]() -> bool {\n            std::fill(level.begin(),\
    \ level.end(), -1);\n            std::queue<int> que;\n            level[s] =\
    \ 0;\n            que.push(s);\n            while (!que.empty()) {\n         \
    \       int v = que.front();\n                que.pop();\n                for\
    \ (const auto& e : _g[v]) {\n                    if (e.cap == Cap(0) || level[e.to]\
    \ != -1) continue;\n                    level[e.to] = level[v] + 1;\n        \
    \            if (e.to == t) return true;\n                    que.push(e.to);\n\
    \                }\n            }\n            return level[t] != -1;\n      \
    \  };\n\n        auto dfs = [&](auto self, int v, Cap up) -> Cap {\n         \
    \   if (v == t) return up;\n            for (int& i = iter[v]; i < int(_g[v].size());\
    \ i++) {\n                auto& e = _g[v][i];\n                if (e.cap == Cap(0)\
    \ || level[v] >= level[e.to]) continue;\n                Cap d = self(self, e.to,\
    \ std::min(up, e.cap));\n                if (d == Cap(0)) continue;\n        \
    \        e.cap -= d;\n                _g[e.to][e.rev].cap += d;\n            \
    \    return d;\n            }\n            return Cap(0);\n        };\n\n    \
    \    Cap flow = 0;\n        while (flow < flow_limit && bfs()) {\n           \
    \ std::fill(iter.begin(), iter.end(), 0);\n            while (flow < flow_limit)\
    \ {\n                Cap f = dfs(dfs, s, flow_limit - flow);\n               \
    \ if (f == Cap(0)) break;\n                flow += f;\n            }\n       \
    \ }\n        return flow;\n    }\n\n    std::vector<bool> min_cut(int s) const\
    \ {\n        assert(0 <= s && s < _n);\n        std::vector<bool> visited(_n,\
    \ false);\n        std::queue<int> que;\n        visited[s] = true;\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            for (const auto& e : _g[v]) {\n                if (e.cap\
    \ == Cap(0) || visited[e.to]) continue;\n                visited[e.to] = true;\n\
    \                que.push(e.to);\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_MAX_FLOW_HPP\n#define M1UNE_FLOW_MAX_FLOW_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <queue>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate\
    \ <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int from;\n      \
    \  int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n    struct\
    \ InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n    };\n\
    \n    int _n;\n    std::vector<std::pair<int, int>> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n   public:\n    MaxFlow() : MaxFlow(0) {}\n\n    explicit MaxFlow(int\
    \ n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_pos.size());\n    }\n\n    int add_edge(int from, int to, Cap cap) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(Cap(0) <= cap);\n        int id = int(_pos.size());\n        int\
    \ from_id = int(_g[from].size());\n        int to_id = int(_g[to].size());\n \
    \       if (from == to) to_id++;\n        _pos.emplace_back(from, from_id);\n\
    \        _g[from].push_back(InternalEdge{to, to_id, cap});\n        _g[to].push_back(InternalEdge{from,\
    \ from_id, Cap(0)});\n        return id;\n    }\n\n    Edge get_edge(int i) const\
    \ {\n        assert(0 <= i && i < int(_pos.size()));\n        auto [from, idx]\
    \ = _pos[i];\n        const auto& e = _g[from][idx];\n        const auto& re =\
    \ _g[e.to][e.rev];\n        return Edge{from, e.to, e.cap + re.cap, re.cap};\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        std::vector<Edge> result;\n\
    \        result.reserve(_pos.size());\n        for (int i = 0; i < int(_pos.size());\
    \ i++) result.push_back(get_edge(i));\n        return result;\n    }\n\n    void\
    \ change_edge(int i, Cap new_cap, Cap new_flow) {\n        assert(0 <= i && i\
    \ < int(_pos.size()));\n        assert(Cap(0) <= new_flow && new_flow <= new_cap);\n\
    \        auto [from, idx] = _pos[i];\n        auto& e = _g[from][idx];\n     \
    \   auto& re = _g[e.to][e.rev];\n        e.cap = new_cap - new_flow;\n       \
    \ re.cap = new_flow;\n    }\n\n    Cap max_flow(int s, int t) {\n        return\
    \ max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\n    Cap max_flow(int\
    \ s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n        assert(0\
    \ <= t && t < _n);\n        assert(s != t);\n\n        std::vector<int> level(_n),\
    \ iter(_n);\n        auto bfs = [&]() -> bool {\n            std::fill(level.begin(),\
    \ level.end(), -1);\n            std::queue<int> que;\n            level[s] =\
    \ 0;\n            que.push(s);\n            while (!que.empty()) {\n         \
    \       int v = que.front();\n                que.pop();\n                for\
    \ (const auto& e : _g[v]) {\n                    if (e.cap == Cap(0) || level[e.to]\
    \ != -1) continue;\n                    level[e.to] = level[v] + 1;\n        \
    \            if (e.to == t) return true;\n                    que.push(e.to);\n\
    \                }\n            }\n            return level[t] != -1;\n      \
    \  };\n\n        auto dfs = [&](auto self, int v, Cap up) -> Cap {\n         \
    \   if (v == t) return up;\n            for (int& i = iter[v]; i < int(_g[v].size());\
    \ i++) {\n                auto& e = _g[v][i];\n                if (e.cap == Cap(0)\
    \ || level[v] >= level[e.to]) continue;\n                Cap d = self(self, e.to,\
    \ std::min(up, e.cap));\n                if (d == Cap(0)) continue;\n        \
    \        e.cap -= d;\n                _g[e.to][e.rev].cap += d;\n            \
    \    return d;\n            }\n            return Cap(0);\n        };\n\n    \
    \    Cap flow = 0;\n        while (flow < flow_limit && bfs()) {\n           \
    \ std::fill(iter.begin(), iter.end(), 0);\n            while (flow < flow_limit)\
    \ {\n                Cap f = dfs(dfs, s, flow_limit - flow);\n               \
    \ if (f == Cap(0)) break;\n                flow += f;\n            }\n       \
    \ }\n        return flow;\n    }\n\n    std::vector<bool> min_cut(int s) const\
    \ {\n        assert(0 <= s && s < _n);\n        std::vector<bool> visited(_n,\
    \ false);\n        std::queue<int> que;\n        visited[s] = true;\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            for (const auto& e : _g[v]) {\n                if (e.cap\
    \ == Cap(0) || visited[e.to]) continue;\n                visited[e.to] = true;\n\
    \                que.push(e.to);\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_MAX_FLOW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/max_flow.hpp
  requiredBy:
  - flow/flow.hpp
  - flow/bounded_flow.hpp
  timestamp: '2026-06-17 01:33:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/flow/flow_algorithms.test.cpp
documentation_of: flow/max_flow.hpp
layout: document
title: Max Flow
---

## Overview

`MaxFlow<Cap>` computes the maximum amount of flow that can be sent from a
source vertex `s` to a sink vertex `t` in a directed capacitated graph.

This implementation uses Dinic's algorithm. It repeatedly builds a level graph
with BFS and sends blocking flow with DFS. It is the standard choice for many
competitive programming max-flow tasks, including bipartite matching,
edge-disjoint paths, and minimum `s-t` cut problems.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap)` can send flow
only from `from` to `to`. For an undirected capacity, add both directions.

The graph is stateful. Running `max_flow` changes residual capacities and
stores the resulting flow. Use `get_edge` or `edges` after running it to inspect
how much flow passed through each original edge.

## How to Use It

Create `MaxFlow<Cap> mf(n)`, add directed edges with capacities, and call
`mf.max_flow(s, t)`.

Capacities must be non-negative. If you want an undirected capacity between
`u` and `v`, add two directed edges.

You can call `max_flow(s, t, flow_limit)` when only up to `flow_limit` units are
needed.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MaxFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MaxFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap cap)` | Adds a directed edge and returns its edge id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `change_edge` | `void change_edge(int i, Cap new_cap, Cap new_flow)` | Replaces edge `i`'s capacity and current flow. | $O(1)$ |
| `max_flow` | `Cap max_flow(int s, int t)` | Sends maximum flow from `s` to `t`. | $O(N^2M)$ general |
| `max_flow` | `Cap max_flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` additional flow. | $O(N^2M)$ general |
| `min_cut` | `std::vector<bool> min_cut(int s) const` | Returns vertices reachable from `s` in the residual graph. | $O(N+M)$ |

## Minimum Cut

After running max flow, `min_cut(s)` returns the source side of a minimum
`s-t` cut. An original edge crossing from `cut[u] == true` to
`cut[v] == false` is saturated and belongs to some minimum cut boundary.

## Example

```cpp
#include "flow/max_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MaxFlow<long long> mf(4);
    mf.add_edge(0, 1, 2);
    mf.add_edge(0, 2, 1);
    mf.add_edge(1, 2, 1);
    mf.add_edge(1, 3, 1);
    mf.add_edge(2, 3, 2);

    std::cout << mf.max_flow(0, 3) << "\n";  // 3

    for (const auto& e : mf.edges()) {
        std::cout << e.from << " -> " << e.to << ": " << e.flow << "/" << e.cap << "\n";
    }
}
```
