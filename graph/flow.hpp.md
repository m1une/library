---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: graph/min_cost_flow.hpp
    title: Min Cost Flow
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/flow.hpp\"\n\n\n\n#line 1 \"graph/max_flow.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <queue>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace graph {\n\
    \ntemplate <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int from;\n\
    \        int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n\
    \    struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \    };\n\n    int _n;\n    std::vector<std::pair<int, int>> _pos;\n    std::vector<std::vector<InternalEdge>>\
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
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/min_cost_flow.hpp\"\
    \n\n\n\n#line 6 \"graph/min_cost_flow.hpp\"\n#include <functional>\n#line 11 \"\
    graph/min_cost_flow.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class Cap, class Cost>\nstruct MinCostFlow {\n    struct Edge {\n        int\
    \ from;\n        int to;\n        Cap cap;\n        Cap flow;\n        Cost cost;\n\
    \    };\n\n   private:\n    struct InternalEdge {\n        int to;\n        int\
    \ rev;\n        Cap cap;\n        Cost cost;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n    void init_potential(int\
    \ s, std::vector<Cost>& potential, Cost cost_inf) const {\n        potential.assign(_n,\
    \ cost_inf);\n        potential[s] = Cost(0);\n        for (int iter = 0; iter\
    \ < _n - 1; iter++) {\n            bool updated = false;\n            for (int\
    \ v = 0; v < _n; v++) {\n                if (potential[v] == cost_inf) continue;\n\
    \                for (const auto& e : _g[v]) {\n                    if (e.cap\
    \ == Cap(0)) continue;\n                    Cost nd = potential[v] + e.cost;\n\
    \                    if (nd < potential[e.to]) {\n                        potential[e.to]\
    \ = nd;\n                        updated = true;\n                    }\n    \
    \            }\n            }\n            if (!updated) break;\n        }\n \
    \       for (int v = 0; v < _n; v++) {\n            if (potential[v] == cost_inf)\
    \ potential[v] = Cost(0);\n        }\n    }\n\n   public:\n    MinCostFlow() :\
    \ MinCostFlow(0) {}\n\n    explicit MinCostFlow(int n) : _n(n), _g(n) {\n    \
    \    assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n  \
    \  }\n\n    int edge_count() const {\n        return int(_pos.size());\n    }\n\
    \n    int add_edge(int from, int to, Cap cap, Cost cost) {\n        assert(0 <=\
    \ from && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0)\
    \ <= cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.emplace_back(from, from_id);\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap, cost});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0),\
    \ -cost});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n  \
    \      assert(0 <= i && i < int(_pos.size()));\n        auto [from, idx] = _pos[i];\n\
    \        const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        return Edge{from, e.to, e.cap + re.cap, re.cap, e.cost};\n    }\n\n \
    \   std::vector<Edge> edges() const {\n        std::vector<Edge> result;\n   \
    \     result.reserve(_pos.size());\n        for (int i = 0; i < int(_pos.size());\
    \ i++) result.push_back(get_edge(i));\n        return result;\n    }\n\n    std::pair<Cap,\
    \ Cost> flow(int s, int t) {\n        return flow(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n\n    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {\n    \
    \    auto result = slope(s, t, flow_limit);\n        return result.back();\n \
    \   }\n\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\n       \
    \ return slope(s, t, std::numeric_limits<Cap>::max());\n    }\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n\n        const Cost\
    \ cost_inf = std::numeric_limits<Cost>::max() / Cost(4);\n        std::vector<Cost>\
    \ potential, dist(_n);\n        std::vector<int> prev_v(_n), prev_e(_n);\n   \
    \     init_potential(s, potential, cost_inf);\n\n        std::vector<std::pair<Cap,\
    \ Cost>> result;\n        result.emplace_back(Cap(0), Cost(0));\n        Cap flow\
    \ = 0;\n        Cost cost = 0;\n\n        while (flow < flow_limit) {\n      \
    \      std::fill(dist.begin(), dist.end(), cost_inf);\n            dist[s] = Cost(0);\n\
    \            using P = std::pair<Cost, int>;\n            std::priority_queue<P,\
    \ std::vector<P>, std::greater<P>> que;\n            que.emplace(Cost(0), s);\n\
    \n            while (!que.empty()) {\n                auto [d, v] = que.top();\n\
    \                que.pop();\n                if (dist[v] != d) continue;\n   \
    \             for (int i = 0; i < int(_g[v].size()); i++) {\n                \
    \    const auto& e = _g[v][i];\n                    if (e.cap == Cap(0)) continue;\n\
    \                    Cost nd = d + e.cost + potential[v] - potential[e.to];\n\
    \                    if (nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    prev_v[e.to] = v;\n                    prev_e[e.to]\
    \ = i;\n                    que.emplace(nd, e.to);\n                }\n      \
    \      }\n\n            if (dist[t] == cost_inf) break;\n            for (int\
    \ v = 0; v < _n; v++) {\n                if (dist[v] != cost_inf) potential[v]\
    \ += dist[v];\n            }\n\n            Cap add = flow_limit - flow;\n   \
    \         for (int v = t; v != s; v = prev_v[v]) {\n                add = std::min(add,\
    \ _g[prev_v[v]][prev_e[v]].cap);\n            }\n            Cost path_cost =\
    \ potential[t] - potential[s];\n            for (int v = t; v != s; v = prev_v[v])\
    \ {\n                auto& e = _g[prev_v[v]][prev_e[v]];\n                e.cap\
    \ -= add;\n                _g[e.to][e.rev].cap += add;\n            }\n\n    \
    \        flow += add;\n            cost += Cost(add) * path_cost;\n          \
    \  result.emplace_back(flow, cost);\n        }\n\n        return result;\n   \
    \ }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 6 \"graph/flow.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_FLOW_HPP

    #define M1UNE_GRAPH_FLOW_HPP 1


    #include "graph/max_flow.hpp"

    #include "graph/min_cost_flow.hpp"


    #endif  // M1UNE_GRAPH_FLOW_HPP

    '
  dependsOn:
  - graph/max_flow.hpp
  - graph/min_cost_flow.hpp
  isVerificationFile: false
  path: graph/flow.hpp
  requiredBy:
  - graph/all.hpp
  - graph/directed.hpp
  timestamp: '2026-06-16 02:16:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/flow.hpp
layout: document
title: Flow
---

## Overview

`graph/flow.hpp` includes flow-network algorithms. Flow networks are directed:
an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, add two directed edges,
`u -> v` and `v -> u`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/max_flow.hpp` | Directed flow network | Dinic maximum flow and minimum cut. |
| `graph/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |
