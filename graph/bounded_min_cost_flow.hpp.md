---
data:
  _extendedDependsOn:
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
  - icon: ':heavy_check_mark:'
    path: graph/flow.hpp
    title: Flow
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bounded_min_cost_flow.hpp\"\n\n\n\n#include <cassert>\n\
    #include <optional>\n#include <vector>\n\n#line 1 \"graph/min_cost_flow.hpp\"\n\
    \n\n\n#include <algorithm>\n#line 6 \"graph/min_cost_flow.hpp\"\n#include <functional>\n\
    #include <limits>\n#include <queue>\n#include <utility>\n#line 11 \"graph/min_cost_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cap, class Cost>\n\
    struct MinCostFlow {\n    struct Edge {\n        int from;\n        int to;\n\
    \        Cap cap;\n        Cap flow;\n        Cost cost;\n    };\n\n   private:\n\
    \    struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \        Cost cost;\n    };\n\n    int _n;\n    std::vector<std::pair<int, int>>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n    void init_potential(int\
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
    \ }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 9 \"graph/bounded_min_cost_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cap, class Cost>\n\
    struct BoundedMinCostFlow {\n    struct Edge {\n        int from;\n        int\
    \ to;\n        Cap lower;\n        Cap upper;\n        Cost cost;\n    };\n\n\
    \    struct ResultEdge {\n        int from;\n        int to;\n        Cap lower;\n\
    \        Cap upper;\n        Cap flow;\n        Cost cost;\n    };\n\n    struct\
    \ Result {\n        std::vector<ResultEdge> edges;\n        std::vector<Cap> balance;\n\
    \        Cost cost;\n\n        ResultEdge get_edge(int i) const {\n          \
    \  assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n  \
    \      }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i <\
    \ int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\n\
    \   private:\n    int _n;\n    std::vector<Edge> _edges;\n    std::vector<Cap>\
    \ _balance;\n\n   public:\n    BoundedMinCostFlow() : BoundedMinCostFlow(0) {}\n\
    \n    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {\n    \
    \    assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n  \
    \  }\n\n    int edge_count() const {\n        return int(_edges.size());\n   \
    \ }\n\n    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(lower <= upper);\n        int id = int(_edges.size());\n     \
    \   _edges.push_back(Edge{from, to, lower, upper, cost});\n        return id;\n\
    \    }\n\n    Edge get_edge(int i) const {\n        assert(0 <= i && i < int(_edges.size()));\n\
    \        return _edges[i];\n    }\n\n    std::vector<Edge> edges() const {\n \
    \       return _edges;\n    }\n\n    void set_balance(int v, Cap b) {\n      \
    \  assert(0 <= v && v < _n);\n        _balance[v] = b;\n    }\n\n    void add_balance(int\
    \ v, Cap b) {\n        assert(0 <= v && v < _n);\n        _balance[v] += b;\n\
    \    }\n\n    void add_supply(int v, Cap supply) {\n        assert(Cap(0) <= supply);\n\
    \        add_balance(v, supply);\n    }\n\n    void add_demand(int v, Cap demand)\
    \ {\n        assert(Cap(0) <= demand);\n        add_balance(v, -demand);\n   \
    \ }\n\n    Cap balance(int v) const {\n        assert(0 <= v && v < _n);\n   \
    \     return _balance[v];\n    }\n\n    const std::vector<Cap>& balances() const\
    \ {\n        return _balance;\n    }\n\n    std::optional<Result> min_cost_flow()\
    \ const {\n        return min_cost_flow(_balance);\n    }\n\n    std::optional<Result>\
    \ min_cost_flow(const std::vector<Cap>& balance) const {\n        assert(int(balance.size())\
    \ == _n);\n        int ss = _n, tt = _n + 1;\n        MinCostFlow<Cap, Cost> mcf(_n\
    \ + 2);\n\n        std::vector<Cap> need = balance;\n        std::vector<Cap>\
    \ initial(_edges.size(), Cap(0));\n        std::vector<int> edge_ids(_edges.size(),\
    \ -1);\n        std::vector<char> reversed(_edges.size(), false);\n\n        for\
    \ (int i = 0; i < int(_edges.size()); i++) {\n            const auto& e = _edges[i];\n\
    \            Cap cap = e.upper - e.lower;\n            need[e.from] -= e.lower;\n\
    \            need[e.to] += e.lower;\n            if (e.cost < Cost(0)) {\n   \
    \             initial[i] = cap;\n                need[e.from] -= cap;\n      \
    \          need[e.to] += cap;\n                edge_ids[i] = mcf.add_edge(e.to,\
    \ e.from, cap, -e.cost);\n                reversed[i] = true;\n            } else\
    \ {\n                edge_ids[i] = mcf.add_edge(e.from, e.to, cap, e.cost);\n\
    \            }\n        }\n\n        Cap positive_sum = Cap(0), negative_sum =\
    \ Cap(0);\n        for (int v = 0; v < _n; v++) {\n            if (need[v] > Cap(0))\
    \ {\n                positive_sum += need[v];\n                mcf.add_edge(ss,\
    \ v, need[v], Cost(0));\n            } else if (need[v] < Cap(0)) {\n        \
    \        negative_sum += -need[v];\n                mcf.add_edge(v, tt, -need[v],\
    \ Cost(0));\n            }\n        }\n        if (positive_sum != negative_sum)\
    \ return std::nullopt;\n\n        auto [sent, extra_cost] = mcf.flow(ss, tt, positive_sum);\n\
    \        (void)extra_cost;\n        if (sent != positive_sum) return std::nullopt;\n\
    \n        Result result;\n        result.balance = balance;\n        result.cost\
    \ = Cost(0);\n        result.edges.reserve(_edges.size());\n        for (int i\
    \ = 0; i < int(_edges.size()); i++) {\n            const auto& e = _edges[i];\n\
    \            Cap used = mcf.get_edge(edge_ids[i]).flow;\n            Cap residual_flow\
    \ = reversed[i] ? initial[i] - used : used;\n            Cap flow = e.lower +\
    \ residual_flow;\n            result.cost += Cost(flow) * e.cost;\n          \
    \  result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, flow, e.cost});\n\
    \        }\n        return result;\n    }\n\n    std::optional<Result> min_cost_st_flow(int\
    \ s, int t, Cap flow_value) const {\n        assert(0 <= s && s < _n);\n     \
    \   assert(0 <= t && t < _n);\n        assert(s != t);\n        std::vector<Cap>\
    \ balance = _balance;\n        balance[s] += flow_value;\n        balance[t] -=\
    \ flow_value;\n        return min_cost_flow(balance);\n    }\n};\n\ntemplate <class\
    \ Cap, class Cost>\nusing BMinCostFlow = BoundedMinCostFlow<Cap, Cost>;\n\n} \
    \ // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_BOUNDED_MIN_COST_FLOW_HPP\n#define M1UNE_GRAPH_BOUNDED_MIN_COST_FLOW_HPP\
    \ 1\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\n#include\
    \ \"graph/min_cost_flow.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class Cap, class Cost>\nstruct BoundedMinCostFlow {\n    struct Edge {\n  \
    \      int from;\n        int to;\n        Cap lower;\n        Cap upper;\n  \
    \      Cost cost;\n    };\n\n    struct ResultEdge {\n        int from;\n    \
    \    int to;\n        Cap lower;\n        Cap upper;\n        Cap flow;\n    \
    \    Cost cost;\n    };\n\n    struct Result {\n        std::vector<ResultEdge>\
    \ edges;\n        std::vector<Cap> balance;\n        Cost cost;\n\n        ResultEdge\
    \ get_edge(int i) const {\n            assert(0 <= i && i < int(edges.size()));\n\
    \            return edges[i];\n        }\n\n        Cap flow(int i) const {\n\
    \            assert(0 <= i && i < int(edges.size()));\n            return edges[i].flow;\n\
    \        }\n    };\n\n   private:\n    int _n;\n    std::vector<Edge> _edges;\n\
    \    std::vector<Cap> _balance;\n\n   public:\n    BoundedMinCostFlow() : BoundedMinCostFlow(0)\
    \ {}\n\n    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {\n\
    \        assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    int edge_count() const {\n        return int(_edges.size());\n \
    \   }\n\n    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(lower <= upper);\n        int id = int(_edges.size());\n     \
    \   _edges.push_back(Edge{from, to, lower, upper, cost});\n        return id;\n\
    \    }\n\n    Edge get_edge(int i) const {\n        assert(0 <= i && i < int(_edges.size()));\n\
    \        return _edges[i];\n    }\n\n    std::vector<Edge> edges() const {\n \
    \       return _edges;\n    }\n\n    void set_balance(int v, Cap b) {\n      \
    \  assert(0 <= v && v < _n);\n        _balance[v] = b;\n    }\n\n    void add_balance(int\
    \ v, Cap b) {\n        assert(0 <= v && v < _n);\n        _balance[v] += b;\n\
    \    }\n\n    void add_supply(int v, Cap supply) {\n        assert(Cap(0) <= supply);\n\
    \        add_balance(v, supply);\n    }\n\n    void add_demand(int v, Cap demand)\
    \ {\n        assert(Cap(0) <= demand);\n        add_balance(v, -demand);\n   \
    \ }\n\n    Cap balance(int v) const {\n        assert(0 <= v && v < _n);\n   \
    \     return _balance[v];\n    }\n\n    const std::vector<Cap>& balances() const\
    \ {\n        return _balance;\n    }\n\n    std::optional<Result> min_cost_flow()\
    \ const {\n        return min_cost_flow(_balance);\n    }\n\n    std::optional<Result>\
    \ min_cost_flow(const std::vector<Cap>& balance) const {\n        assert(int(balance.size())\
    \ == _n);\n        int ss = _n, tt = _n + 1;\n        MinCostFlow<Cap, Cost> mcf(_n\
    \ + 2);\n\n        std::vector<Cap> need = balance;\n        std::vector<Cap>\
    \ initial(_edges.size(), Cap(0));\n        std::vector<int> edge_ids(_edges.size(),\
    \ -1);\n        std::vector<char> reversed(_edges.size(), false);\n\n        for\
    \ (int i = 0; i < int(_edges.size()); i++) {\n            const auto& e = _edges[i];\n\
    \            Cap cap = e.upper - e.lower;\n            need[e.from] -= e.lower;\n\
    \            need[e.to] += e.lower;\n            if (e.cost < Cost(0)) {\n   \
    \             initial[i] = cap;\n                need[e.from] -= cap;\n      \
    \          need[e.to] += cap;\n                edge_ids[i] = mcf.add_edge(e.to,\
    \ e.from, cap, -e.cost);\n                reversed[i] = true;\n            } else\
    \ {\n                edge_ids[i] = mcf.add_edge(e.from, e.to, cap, e.cost);\n\
    \            }\n        }\n\n        Cap positive_sum = Cap(0), negative_sum =\
    \ Cap(0);\n        for (int v = 0; v < _n; v++) {\n            if (need[v] > Cap(0))\
    \ {\n                positive_sum += need[v];\n                mcf.add_edge(ss,\
    \ v, need[v], Cost(0));\n            } else if (need[v] < Cap(0)) {\n        \
    \        negative_sum += -need[v];\n                mcf.add_edge(v, tt, -need[v],\
    \ Cost(0));\n            }\n        }\n        if (positive_sum != negative_sum)\
    \ return std::nullopt;\n\n        auto [sent, extra_cost] = mcf.flow(ss, tt, positive_sum);\n\
    \        (void)extra_cost;\n        if (sent != positive_sum) return std::nullopt;\n\
    \n        Result result;\n        result.balance = balance;\n        result.cost\
    \ = Cost(0);\n        result.edges.reserve(_edges.size());\n        for (int i\
    \ = 0; i < int(_edges.size()); i++) {\n            const auto& e = _edges[i];\n\
    \            Cap used = mcf.get_edge(edge_ids[i]).flow;\n            Cap residual_flow\
    \ = reversed[i] ? initial[i] - used : used;\n            Cap flow = e.lower +\
    \ residual_flow;\n            result.cost += Cost(flow) * e.cost;\n          \
    \  result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, flow, e.cost});\n\
    \        }\n        return result;\n    }\n\n    std::optional<Result> min_cost_st_flow(int\
    \ s, int t, Cap flow_value) const {\n        assert(0 <= s && s < _n);\n     \
    \   assert(0 <= t && t < _n);\n        assert(s != t);\n        std::vector<Cap>\
    \ balance = _balance;\n        balance[s] += flow_value;\n        balance[t] -=\
    \ flow_value;\n        return min_cost_flow(balance);\n    }\n};\n\ntemplate <class\
    \ Cap, class Cost>\nusing BMinCostFlow = BoundedMinCostFlow<Cap, Cost>;\n\n} \
    \ // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_BOUNDED_MIN_COST_FLOW_HPP\n"
  dependsOn:
  - graph/min_cost_flow.hpp
  isVerificationFile: false
  path: graph/bounded_min_cost_flow.hpp
  requiredBy:
  - graph/flow.hpp
  - graph/all.hpp
  - graph/directed.hpp
  timestamp: '2026-06-16 02:49:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/bounded_min_cost_flow.hpp
layout: document
title: Bounded Min Cost Flow
---

## Overview

`BoundedMinCostFlow<Cap, Cost>` finds a minimum-cost feasible flow with lower
and upper bounds on each edge. It is the costed version of `BoundedFlow<Cap>`.
`BMinCostFlow<Cap, Cost>` is an alias of
`BoundedMinCostFlow<Cap, Cost>`.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`. The cost is still `flow * cost`, so a negative flow can
contribute a negative or positive value depending on `cost`.

## Graph Orientation

Directed flow network. An edge added by
`add_edge(from, to, lower, upper, cost)` has the signed direction
`from -> to`.

## How It Works

First, lower bounds are subtracted. For an edge `u -> v` with lower bound `L`,
upper bound `U`, and cost `C`, the solver sends `L` units as a fixed part and
leaves residual capacity `U - L`.

Then it handles costs. If a residual edge has negative cost, the solver starts
by saturating it, because that can only improve the cost before balance
constraints are repaired. This may make vertex balances wrong, so the remaining
problem is solved on the residual graph with a super source and super sink.
All residual costs in that repair step are non-negative.

The returned `Result::cost` is the total cost on the original edges:

```cpp
sum(edge.flow * edge.cost)
```

If the balance constraints cannot be satisfied, the solver returns
`std::nullopt`.

## How to Use It

Use `add_edge(from, to, lower, upper, cost)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `min_cost_flow()`. It returns `std::nullopt` if no feasible flow
exists.

For an exact `s-t` flow of value `F`, call `min_cost_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`, then minimizes
the total cost among feasible flows with that exact value.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected minimum-cost flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `cost` | `Cost` | Total cost `sum(flow * cost)` of the selected flow. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected minimum-cost flow. |
| `cost` | `Cost` | Cost per unit of flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedMinCostFlow()` | Creates an empty bounded min-cost-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedMinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper, Cost cost)` | Adds an edge with bounds and cost, then returns its id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow() const` | Solves using stored balances. | $O(NM + FM\log N)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const` | Solves using explicit balances. | $O(NM + FM\log N)$ |
| `min_cost_st_flow` | `std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | $O(NM + FM\log N)$ |

Here, `F` is the number of augmentations made by the internal
`MinCostFlow<Cap, Cost>` repair step.

## Alias

| Alias | Type |
| --- | --- |
| `BMinCostFlow<Cap, Cost>` | `BoundedMinCostFlow<Cap, Cost>` |

## Example

```cpp
#include "graph/bounded_min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::graph::BoundedMinCostFlow<long long, long long> mcf(3);
    int e0 = mcf.add_edge(0, 1, 1, 3, 2);
    int e1 = mcf.add_edge(1, 2, 1, 3, 1);
    int e2 = mcf.add_edge(0, 2, 0, 3, 10);

    auto res = mcf.min_cost_st_flow(0, 2, 3);
    if (!res) return 0;

    std::cout << res->cost << "\n";     // 9
    std::cout << res->flow(e0) << "\n"; // 3
    std::cout << res->flow(e1) << "\n"; // 3
    std::cout << res->flow(e2) << "\n"; // 0
}
```
