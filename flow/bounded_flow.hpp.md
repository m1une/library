---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/max_flow.hpp
    title: Max Flow
  _extendedRequiredBy:
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
  bundledCode: "#line 1 \"flow/bounded_flow.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\n#line 1 \"flow/max_flow.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#line 6 \"flow/max_flow.hpp\"\n#include <limits>\n#include <queue>\n\
    #include <utility>\n#line 10 \"flow/max_flow.hpp\"\n\nnamespace m1une {\nnamespace\
    \ flow {\n\ntemplate <class Cap>\nstruct MaxFlow {\n    struct Edge {\n      \
    \  int from;\n        int to;\n        Cap cap;\n        Cap flow;\n    };\n\n\
    \   private:\n    struct InternalEdge {\n        int to;\n        int rev;\n \
    \       Cap cap;\n    };\n\n    int _n;\n    std::vector<std::pair<int, int>>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n   public:\n    MaxFlow()\
    \ : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int\
    \ edge_count() const {\n        return int(_pos.size());\n    }\n\n    int add_edge(int\
    \ from, int to, Cap cap) {\n        assert(0 <= from && from < _n);\n        assert(0\
    \ <= to && to < _n);\n        assert(Cap(0) <= cap);\n        int id = int(_pos.size());\n\
    \        int from_id = int(_g[from].size());\n        int to_id = int(_g[to].size());\n\
    \        if (from == to) to_id++;\n        _pos.emplace_back(from, from_id);\n\
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
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 9 \"flow/bounded_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct BoundedFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap lower;\n\
    \        Cap upper;\n    };\n\n    struct ResultEdge {\n        int from;\n  \
    \      int to;\n        Cap lower;\n        Cap upper;\n        Cap flow;\n  \
    \  };\n\n    struct Result {\n        std::vector<ResultEdge> edges;\n       \
    \ std::vector<Cap> balance;\n\n        ResultEdge get_edge(int i) const {\n  \
    \          assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n\
    \        }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i\
    \ < int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\
    \n   private:\n    int _n;\n    std::vector<Edge> _edges;\n    std::vector<Cap>\
    \ _balance;\n\n   public:\n    BoundedFlow() : BoundedFlow(0) {}\n\n    explicit\
    \ BoundedFlow(int n) : _n(n), _balance(n, Cap(0)) {\n        assert(0 <= n);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    int edge_count()\
    \ const {\n        return int(_edges.size());\n    }\n\n    int add_edge(int from,\
    \ int to, Cap lower, Cap upper) {\n        assert(0 <= from && from < _n);\n \
    \       assert(0 <= to && to < _n);\n        assert(lower <= upper);\n       \
    \ int id = int(_edges.size());\n        _edges.push_back(Edge{from, to, lower,\
    \ upper});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n  \
    \      assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        return _edges;\n    }\n\
    \n    void set_balance(int v, Cap b) {\n        assert(0 <= v && v < _n);\n  \
    \      _balance[v] = b;\n    }\n\n    void add_balance(int v, Cap b) {\n     \
    \   assert(0 <= v && v < _n);\n        _balance[v] += b;\n    }\n\n    void add_supply(int\
    \ v, Cap supply) {\n        assert(Cap(0) <= supply);\n        add_balance(v,\
    \ supply);\n    }\n\n    void add_demand(int v, Cap demand) {\n        assert(Cap(0)\
    \ <= demand);\n        add_balance(v, -demand);\n    }\n\n    Cap balance(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _balance[v];\n\
    \    }\n\n    const std::vector<Cap>& balances() const {\n        return _balance;\n\
    \    }\n\n    std::optional<Result> feasible_flow() const {\n        return feasible_flow(_balance);\n\
    \    }\n\n    std::optional<Result> feasible_flow(const std::vector<Cap>& balance)\
    \ const {\n        assert(int(balance.size()) == _n);\n        int ss = _n, tt\
    \ = _n + 1;\n        MaxFlow<Cap> mf(_n + 2);\n        std::vector<int> edge_ids;\n\
    \        edge_ids.reserve(_edges.size());\n\n        std::vector<Cap> need = balance;\n\
    \        for (const auto& e : _edges) {\n            edge_ids.push_back(mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower));\n            need[e.from] -= e.lower;\n         \
    \   need[e.to] += e.lower;\n        }\n\n        Cap positive_sum = Cap(0), negative_sum\
    \ = Cap(0);\n        for (int v = 0; v < _n; v++) {\n            if (need[v] >\
    \ Cap(0)) {\n                positive_sum += need[v];\n                mf.add_edge(ss,\
    \ v, need[v]);\n            } else if (need[v] < Cap(0)) {\n                negative_sum\
    \ += -need[v];\n                mf.add_edge(v, tt, -need[v]);\n            }\n\
    \        }\n        if (positive_sum != negative_sum) return std::nullopt;\n \
    \       if (mf.max_flow(ss, tt) != positive_sum) return std::nullopt;\n\n    \
    \    Result result;\n        result.balance = balance;\n        result.edges.reserve(_edges.size());\n\
    \        for (int i = 0; i < int(_edges.size()); i++) {\n            auto used\
    \ = mf.get_edge(edge_ids[i]).flow;\n            const auto& e = _edges[i];\n \
    \           result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper,\
    \ e.lower + used});\n        }\n        return result;\n    }\n\n    std::optional<Result>\
    \ feasible_st_flow(int s, int t, Cap flow_value) const {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\
    \        std::vector<Cap> balance = _balance;\n        balance[s] += flow_value;\n\
    \        balance[t] -= flow_value;\n        return feasible_flow(balance);\n \
    \   }\n};\n\ntemplate <class Cap>\nusing BFlow = BoundedFlow<Cap>;\n\n}  // namespace\
    \ flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_BOUNDED_FLOW_HPP\n#define M1UNE_FLOW_BOUNDED_FLOW_HPP\
    \ 1\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\n#include\
    \ \"flow/max_flow.hpp\"\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class\
    \ Cap>\nstruct BoundedFlow {\n    struct Edge {\n        int from;\n        int\
    \ to;\n        Cap lower;\n        Cap upper;\n    };\n\n    struct ResultEdge\
    \ {\n        int from;\n        int to;\n        Cap lower;\n        Cap upper;\n\
    \        Cap flow;\n    };\n\n    struct Result {\n        std::vector<ResultEdge>\
    \ edges;\n        std::vector<Cap> balance;\n\n        ResultEdge get_edge(int\
    \ i) const {\n            assert(0 <= i && i < int(edges.size()));\n         \
    \   return edges[i];\n        }\n\n        Cap flow(int i) const {\n         \
    \   assert(0 <= i && i < int(edges.size()));\n            return edges[i].flow;\n\
    \        }\n    };\n\n   private:\n    int _n;\n    std::vector<Edge> _edges;\n\
    \    std::vector<Cap> _balance;\n\n   public:\n    BoundedFlow() : BoundedFlow(0)\
    \ {}\n\n    explicit BoundedFlow(int n) : _n(n), _balance(n, Cap(0)) {\n     \
    \   assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n   \
    \ }\n\n    int edge_count() const {\n        return int(_edges.size());\n    }\n\
    \n    int add_edge(int from, int to, Cap lower, Cap upper) {\n        assert(0\
    \ <= from && from < _n);\n        assert(0 <= to && to < _n);\n        assert(lower\
    \ <= upper);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, lower, upper});\n        return id;\n    }\n\n    Edge get_edge(int i) const\
    \ {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        return _edges;\n    }\n\
    \n    void set_balance(int v, Cap b) {\n        assert(0 <= v && v < _n);\n  \
    \      _balance[v] = b;\n    }\n\n    void add_balance(int v, Cap b) {\n     \
    \   assert(0 <= v && v < _n);\n        _balance[v] += b;\n    }\n\n    void add_supply(int\
    \ v, Cap supply) {\n        assert(Cap(0) <= supply);\n        add_balance(v,\
    \ supply);\n    }\n\n    void add_demand(int v, Cap demand) {\n        assert(Cap(0)\
    \ <= demand);\n        add_balance(v, -demand);\n    }\n\n    Cap balance(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _balance[v];\n\
    \    }\n\n    const std::vector<Cap>& balances() const {\n        return _balance;\n\
    \    }\n\n    std::optional<Result> feasible_flow() const {\n        return feasible_flow(_balance);\n\
    \    }\n\n    std::optional<Result> feasible_flow(const std::vector<Cap>& balance)\
    \ const {\n        assert(int(balance.size()) == _n);\n        int ss = _n, tt\
    \ = _n + 1;\n        MaxFlow<Cap> mf(_n + 2);\n        std::vector<int> edge_ids;\n\
    \        edge_ids.reserve(_edges.size());\n\n        std::vector<Cap> need = balance;\n\
    \        for (const auto& e : _edges) {\n            edge_ids.push_back(mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower));\n            need[e.from] -= e.lower;\n         \
    \   need[e.to] += e.lower;\n        }\n\n        Cap positive_sum = Cap(0), negative_sum\
    \ = Cap(0);\n        for (int v = 0; v < _n; v++) {\n            if (need[v] >\
    \ Cap(0)) {\n                positive_sum += need[v];\n                mf.add_edge(ss,\
    \ v, need[v]);\n            } else if (need[v] < Cap(0)) {\n                negative_sum\
    \ += -need[v];\n                mf.add_edge(v, tt, -need[v]);\n            }\n\
    \        }\n        if (positive_sum != negative_sum) return std::nullopt;\n \
    \       if (mf.max_flow(ss, tt) != positive_sum) return std::nullopt;\n\n    \
    \    Result result;\n        result.balance = balance;\n        result.edges.reserve(_edges.size());\n\
    \        for (int i = 0; i < int(_edges.size()); i++) {\n            auto used\
    \ = mf.get_edge(edge_ids[i]).flow;\n            const auto& e = _edges[i];\n \
    \           result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper,\
    \ e.lower + used});\n        }\n        return result;\n    }\n\n    std::optional<Result>\
    \ feasible_st_flow(int s, int t, Cap flow_value) const {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\
    \        std::vector<Cap> balance = _balance;\n        balance[s] += flow_value;\n\
    \        balance[t] -= flow_value;\n        return feasible_flow(balance);\n \
    \   }\n};\n\ntemplate <class Cap>\nusing BFlow = BoundedFlow<Cap>;\n\n}  // namespace\
    \ flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_BOUNDED_FLOW_HPP\n"
  dependsOn:
  - flow/max_flow.hpp
  isVerificationFile: false
  path: flow/bounded_flow.hpp
  requiredBy:
  - flow/flow.hpp
  timestamp: '2026-06-17 01:33:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/flow/flow_algorithms.test.cpp
documentation_of: flow/bounded_flow.hpp
layout: document
title: Bounded Flow
---

## Overview

`BoundedFlow<Cap>` finds a feasible flow with lower and upper bounds on each
edge. It also supports `b`-flow constraints by giving each vertex a required
balance. `BFlow<Cap>` is an alias of `BoundedFlow<Cap>`.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, lower, upper)` has
the signed direction `from -> to`.

## How It Works

The library reduces bounded flow to ordinary max flow.

For an edge `u -> v` with lower bound `L` and upper bound `U`, it sends
`L` first and leaves residual capacity `U - L`. This changes the vertex
balances, then a super source and super sink are added to check whether all
remaining balance constraints can be satisfied.

## How to Use It

Use `add_edge(from, to, lower, upper)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `feasible_flow()`. It returns `std::nullopt` if no feasible flow
exists.

For an exact `s-t` flow of value `F`, call `feasible_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected feasible flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected feasible flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedFlow()` | Creates an empty bounded-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper)` | Adds an edge with bounds and returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `feasible_flow` | `std::optional<Result> feasible_flow() const` | Solves using stored balances. | Max flow |
| `feasible_flow` | `std::optional<Result> feasible_flow(const std::vector<Cap>& balance) const` | Solves using explicit balances. | Max flow |
| `feasible_st_flow` | `std::optional<Result> feasible_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | Max flow |

## Alias

| Alias | Type |
| --- | --- |
| `BFlow<Cap>` | `BoundedFlow<Cap>` |

## Example

```cpp
#include "flow/bounded_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::BoundedFlow<long long> bf(3);
    int e0 = bf.add_edge(0, 1, 1, 3);
    int e1 = bf.add_edge(0, 2, 0, 2);
    int e2 = bf.add_edge(1, 2, -1, 2);  // negative flow is allowed

    bf.add_supply(0, 3);
    bf.add_demand(2, 3);

    auto res = bf.feasible_flow();
    if (!res) return 0;

    std::cout << res->flow(e0) << "\n";
    std::cout << res->flow(e1) << "\n";
    std::cout << res->flow(e2) << "\n";
}
```
