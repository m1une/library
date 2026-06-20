---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/bounded_flow.hpp
    title: Bounded Flow
  - icon: ':heavy_check_mark:'
    path: flow/bounded_min_cost_flow.hpp
    title: Bounded Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: flow/min_cost_flow.hpp
    title: Min Cost Flow
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/flow/flow_algorithms.test.cpp
    title: verify/flow/flow_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"flow/flow.hpp\"\n\n\n\n#line 1 \"flow/bounded_flow.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\n#line 1\
    \ \"flow/max_flow.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"flow/max_flow.hpp\"\
    \n#include <limits>\n#include <queue>\n#include <utility>\n#line 10 \"flow/max_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap cap;\n\
    \        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n       \
    \ int to;\n        int rev;\n        Cap cap;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n   public:\n\
    \    MaxFlow() : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n\
    \        assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    int edge_count() const {\n        return int(_pos.size());\n   \
    \ }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0 <= from\
    \ && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0) <=\
    \ cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.emplace_back(from, from_id);\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    Edge get_edge(int i) const {\n        assert(0\
    \ <= i && i < int(_pos.size()));\n        auto [from, idx] = _pos[i];\n      \
    \  const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        return Edge{from, e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge>\
    \ edges() const {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n        auto [from, idx] = _pos[i];\n\
    \        auto& e = _g[from][idx];\n        auto& re = _g[e.to][e.rev];\n     \
    \   e.cap = new_cap - new_flow;\n        re.cap = new_flow;\n    }\n\n    Cap\
    \ max_flow(int s, int t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n\n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n\
    \        std::vector<int> level(_n), iter(_n);\n        auto bfs = [&]() -> bool\
    \ {\n            std::fill(level.begin(), level.end(), -1);\n            std::queue<int>\
    \ que;\n            level[s] = 0;\n            que.push(s);\n            while\
    \ (!que.empty()) {\n                int v = que.front();\n                que.pop();\n\
    \                for (const auto& e : _g[v]) {\n                    if (e.cap\
    \ == Cap(0) || level[e.to] != -1) continue;\n                    level[e.to] =\
    \ level[v] + 1;\n                    if (e.to == t) return true;\n           \
    \         que.push(e.to);\n                }\n            }\n            return\
    \ level[t] != -1;\n        };\n\n        auto dfs = [&](auto self, int v, Cap\
    \ up) -> Cap {\n            if (v == t) return up;\n            for (int& i =\
    \ iter[v]; i < int(_g[v].size()); i++) {\n                auto& e = _g[v][i];\n\
    \                if (e.cap == Cap(0) || level[v] >= level[e.to]) continue;\n \
    \               Cap d = self(self, e.to, std::min(up, e.cap));\n             \
    \   if (d == Cap(0)) continue;\n                e.cap -= d;\n                _g[e.to][e.rev].cap\
    \ += d;\n                return d;\n            }\n            return Cap(0);\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter.begin(), iter.end(), 0);\n            while (flow\
    \ < flow_limit) {\n                Cap f = dfs(dfs, s, flow_limit - flow);\n \
    \               if (f == Cap(0)) break;\n                flow += f;\n        \
    \    }\n        }\n        return flow;\n    }\n\n    std::vector<bool> min_cut(int\
    \ s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool> visited(_n,\
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
    \ flow\n}  // namespace m1une\n\n\n#line 1 \"flow/bounded_min_cost_flow.hpp\"\n\
    \n\n\n#line 7 \"flow/bounded_min_cost_flow.hpp\"\n\n#line 1 \"flow/min_cost_flow.hpp\"\
    \n\n\n\n#line 6 \"flow/min_cost_flow.hpp\"\n#include <functional>\n#line 11 \"\
    flow/min_cost_flow.hpp\"\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class\
    \ Cap, class Cost>\nstruct MinCostFlow {\n    struct Edge {\n        int from;\n\
    \        int to;\n        Cap cap;\n        Cap flow;\n        Cost cost;\n  \
    \  };\n\n   private:\n    struct InternalEdge {\n        int to;\n        int\
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
    \ }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 9 \"flow/bounded_min_cost_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap, class Cost>\n\
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
    \ // namespace flow\n}  // namespace m1une\n\n\n#line 8 \"flow/flow.hpp\"\n\n\n"
  code: '#ifndef M1UNE_FLOW_FLOW_HPP

    #define M1UNE_FLOW_FLOW_HPP 1


    #include "bounded_flow.hpp"

    #include "bounded_min_cost_flow.hpp"

    #include "max_flow.hpp"

    #include "min_cost_flow.hpp"


    #endif  // M1UNE_FLOW_FLOW_HPP

    '
  dependsOn:
  - flow/bounded_flow.hpp
  - flow/max_flow.hpp
  - flow/bounded_min_cost_flow.hpp
  - flow/min_cost_flow.hpp
  isVerificationFile: false
  path: flow/flow.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/flow/flow_algorithms.test.cpp
documentation_of: flow/flow.hpp
layout: document
title: Flow
---

## Overview

`flow/flow.hpp` includes flow-network algorithms. Flow networks are directed:
an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, add two directed edges,
`u -> v` and `v -> u`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `flow/bounded_flow.hpp` | Directed flow network | Feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `flow/bounded_min_cost_flow.hpp` | Directed flow network | Minimum-cost feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `flow/max_flow.hpp` | Directed flow network | Dinic maximum flow and minimum cut. |
| `flow/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |
