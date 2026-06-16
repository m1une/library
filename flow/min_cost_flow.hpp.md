---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: flow/bounded_min_cost_flow.hpp
    title: Bounded Min Cost Flow
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
  bundledCode: "#line 1 \"flow/min_cost_flow.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <functional>\n#include <limits>\n#include <queue>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate\
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
    \ }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_MIN_COST_FLOW_HPP\n#define M1UNE_FLOW_MIN_COST_FLOW_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <limits>\n#include <queue>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace flow {\n\ntemplate <class Cap, class Cost>\nstruct MinCostFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap cap;\n\
    \        Cap flow;\n        Cost cost;\n    };\n\n   private:\n    struct InternalEdge\
    \ {\n        int to;\n        int rev;\n        Cap cap;\n        Cost cost;\n\
    \    };\n\n    int _n;\n    std::vector<std::pair<int, int>> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n    void init_potential(int s, std::vector<Cost>& potential, Cost cost_inf)\
    \ const {\n        potential.assign(_n, cost_inf);\n        potential[s] = Cost(0);\n\
    \        for (int iter = 0; iter < _n - 1; iter++) {\n            bool updated\
    \ = false;\n            for (int v = 0; v < _n; v++) {\n                if (potential[v]\
    \ == cost_inf) continue;\n                for (const auto& e : _g[v]) {\n    \
    \                if (e.cap == Cap(0)) continue;\n                    Cost nd =\
    \ potential[v] + e.cost;\n                    if (nd < potential[e.to]) {\n  \
    \                      potential[e.to] = nd;\n                        updated\
    \ = true;\n                    }\n                }\n            }\n         \
    \   if (!updated) break;\n        }\n        for (int v = 0; v < _n; v++) {\n\
    \            if (potential[v] == cost_inf) potential[v] = Cost(0);\n        }\n\
    \    }\n\n   public:\n    MinCostFlow() : MinCostFlow(0) {}\n\n    explicit MinCostFlow(int\
    \ n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_pos.size());\n    }\n\n    int add_edge(int from, int to, Cap cap, Cost\
    \ cost) {\n        assert(0 <= from && from < _n);\n        assert(0 <= to &&\
    \ to < _n);\n        assert(Cap(0) <= cap);\n        int id = int(_pos.size());\n\
    \        int from_id = int(_g[from].size());\n        int to_id = int(_g[to].size());\n\
    \        if (from == to) to_id++;\n        _pos.emplace_back(from, from_id);\n\
    \        _g[from].push_back(InternalEdge{to, to_id, cap, cost});\n        _g[to].push_back(InternalEdge{from,\
    \ from_id, Cap(0), -cost});\n        return id;\n    }\n\n    Edge get_edge(int\
    \ i) const {\n        assert(0 <= i && i < int(_pos.size()));\n        auto [from,\
    \ idx] = _pos[i];\n        const auto& e = _g[from][idx];\n        const auto&\
    \ re = _g[e.to][e.rev];\n        return Edge{from, e.to, e.cap + re.cap, re.cap,\
    \ e.cost};\n    }\n\n    std::vector<Edge> edges() const {\n        std::vector<Edge>\
    \ result;\n        result.reserve(_pos.size());\n        for (int i = 0; i < int(_pos.size());\
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
    \ }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_MIN_COST_FLOW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/min_cost_flow.hpp
  requiredBy:
  - flow/flow.hpp
  - flow/bounded_min_cost_flow.hpp
  timestamp: '2026-06-17 01:33:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/flow/flow_algorithms.test.cpp
documentation_of: flow/min_cost_flow.hpp
layout: document
title: Min Cost Flow
---

## Overview

`MinCostFlow<Cap, Cost>` sends flow from a source `s` to a sink `t` while
minimizing total cost. Each edge has a capacity and a cost per unit of flow.

This implementation uses the successive shortest augmenting path method with
potentials. It first computes initial potentials with Bellman-Ford, so negative
edge costs are allowed as long as there is no reachable negative-cost cycle
with residual capacity.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap, cost)` can
send flow only from `from` to `to`. For an undirected capacity, add both
directions with the desired costs.

The graph is stateful. Running `flow` or `slope` changes residual capacities and
stores the chosen flow. Use `get_edge` or `edges` afterward to inspect the
result.

## How to Use It

Create `MinCostFlow<Cap, Cost> mcf(n)`, add directed edges with capacity and
cost, and call `mcf.flow(s, t, flow_limit)`.

The returned pair is `{sent_flow, minimum_cost}`. If the requested
`flow_limit` cannot be fully sent, `sent_flow` will be smaller.

Use `slope(s, t, flow_limit)` when you need the minimum cost for every
breakpoint of the amount of flow. The returned vector starts with `{0, 0}` and
then adds one entry after each augmentation.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |
| `cost` | `Cost` | Cost per unit of flow on this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MinCostFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap cap, Cost cost)` | Adds a directed edge and returns its edge id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t)` | Sends as much flow as possible with minimum cost. | $O(NM + FM\log N)$ |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` flow with minimum cost. | $O(NM + FM\log N)$ |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t)` | Returns flow-cost breakpoints while sending as much as possible. | $O(NM + FM\log N)$ |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)` | Returns flow-cost breakpoints up to `flow_limit`. | $O(NM + FM\log N)$ |

Here, `F` is the number of augmentations. The first term initializes potentials
with Bellman-Ford.

## Notes

Costs may be negative, but the residual graph must not contain a reachable
negative-cost cycle. If such a cycle exists, the minimum cost is not
well-defined.

Calling `flow` or `slope` a second time continues from the current residual
state and sends additional flow.

## Example

```cpp
#include "flow/min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto [flow, cost] = mcf.flow(0, 3, 2);
    std::cout << flow << " " << cost << "\n";  // 2 5
}
```
