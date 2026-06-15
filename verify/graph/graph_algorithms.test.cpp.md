---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dsu.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/bounded_flow.hpp
    title: Bounded Flow
  - icon: ':heavy_check_mark:'
    path: graph/bounded_min_cost_flow.hpp
    title: Bounded Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/flow.hpp
    title: Flow
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.hpp
    title: General Matching
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/grid.hpp
    title: Grid
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: graph/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: graph/maximum_clique.hpp
    title: Maximum Clique and Independent Set
  - icon: ':heavy_check_mark:'
    path: graph/min_cost_flow.hpp
    title: Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/graph/graph_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <set>\n#include <string>\n#include\
    \ <vector>\n\n#line 1 \"graph/all.hpp\"\n\n\n\n#line 1 \"graph/directed.hpp\"\n\
    \n\n\n#line 1 \"graph/cycle_detection.hpp\"\n\n\n\n#line 6 \"graph/cycle_detection.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n\
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
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.push_back({{from,\
    \ idx}});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost\
    \ = T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.push_back({{u,\
    \ u_idx}, {v, v_idx}});\n        return id;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < _edge_count);\n        for\
    \ (auto [v, idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n\
    \        }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id,\
    \ false);\n    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id,\
    \ true);\n    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <=\
    \ id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n  \
    \      auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
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
    \ m1une\n\n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n  \
    \  }\n};\n\ninline Cycle restore_cycle(int from, int to, int closing_edge, const\
    \ std::vector<int>& parent,\n                           const std::vector<int>&\
    \ parent_edge) {\n    Cycle result;\n    result.vertices.push_back(to);\n\n  \
    \  std::vector<int> middle_vertices;\n    std::vector<int> middle_edges;\n   \
    \ for (int v = from; v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n\
    \        middle_edges.push_back(parent_edge[v]);\n    }\n    std::reverse(middle_vertices.begin(),\
    \ middle_vertices.end());\n    std::reverse(middle_edges.begin(), middle_edges.end());\n\
    \n    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());\n\
    \    result.vertices.push_back(to);\n    result.edge_ids.insert(result.edge_ids.end(),\
    \ middle_edges.begin(), middle_edges.end());\n    result.edge_ids.push_back(closing_edge);\n\
    \    return result;\n}\n\ntemplate <class T>\nCycle find_directed_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v) -> bool {\n        color[v] = 1;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (e.id == pe) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to, e.id)) return true;\n            } else\
    \ if (color[e.to] == 1) {\n                result = restore_cycle(v, e.to, e.id,\
    \ parent, parent_edge);\n                return true;\n            }\n       \
    \ }\n        color[v] = 2;\n        return false;\n    };\n\n    for (int v =\
    \ 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs, v, -1)) break;\n   \
    \ }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n#line 1 \"graph/flow.hpp\"\n\n\n\n#line 1 \"graph/bounded_flow.hpp\"\n\n\n\n\
    #line 5 \"graph/bounded_flow.hpp\"\n#include <optional>\n#line 7 \"graph/bounded_flow.hpp\"\
    \n\n#line 1 \"graph/max_flow.hpp\"\n\n\n\n#line 6 \"graph/max_flow.hpp\"\n#include\
    \ <limits>\n#include <queue>\n#line 10 \"graph/max_flow.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class Cap>\nstruct MaxFlow {\n    struct Edge\
    \ {\n        int from;\n        int to;\n        Cap cap;\n        Cap flow;\n\
    \    };\n\n   private:\n    struct InternalEdge {\n        int to;\n        int\
    \ rev;\n        Cap cap;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
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
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 9 \"graph/bounded_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cap>\nstruct BoundedFlow\
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
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/bounded_min_cost_flow.hpp\"\
    \n\n\n\n#line 7 \"graph/bounded_min_cost_flow.hpp\"\n\n#line 1 \"graph/min_cost_flow.hpp\"\
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
    \ // namespace graph\n}  // namespace m1une\n\n\n#line 8 \"graph/flow.hpp\"\n\n\
    \n#line 1 \"graph/scc.hpp\"\n\n\n\n#line 8 \"graph/scc.hpp\"\n\n#line 10 \"graph/scc.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct SccResult {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n\n    template <class T>\n    Graph<int> dag(const Graph<T>& g) const\
    \ {\n        std::vector<std::pair<int, int>> edges;\n        for (int v = 0;\
    \ v < g.size(); v++) {\n            for (const auto& e : g[v]) {\n           \
    \     if (!e.alive) continue;\n                int a = comp[e.from], b = comp[e.to];\n\
    \                if (a != b) edges.emplace_back(a, b);\n            }\n      \
    \  }\n        std::sort(edges.begin(), edges.end());\n        edges.erase(std::unique(edges.begin(),\
    \ edges.end()), edges.end());\n\n        Graph<int> result(count);\n        for\
    \ (auto [a, b] : edges) result.add_directed_edge(a, b);\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> ord(n, -1), low(n,\
    \ 0), comp(n, -1), stack;\n    std::vector<char> in_stack(n, false);\n    std::vector<std::vector<int>>\
    \ groups;\n    int now = 0;\n\n    auto dfs = [&](auto self, int v) -> void {\n\
    \        ord[v] = low[v] = now++;\n        stack.push_back(v);\n        in_stack[v]\
    \ = true;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            int to = e.to;\n            if (ord[to] == -1) {\n              \
    \  self(self, to);\n                low[v] = std::min(low[v], low[to]);\n    \
    \        } else if (in_stack[to]) {\n                low[v] = std::min(low[v],\
    \ ord[to]);\n            }\n        }\n\n        if (low[v] != ord[v]) return;\n\
    \        std::vector<int> group;\n        while (true) {\n            int u =\
    \ stack.back();\n            stack.pop_back();\n            in_stack[u] = false;\n\
    \            group.push_back(u);\n            if (u == v) break;\n        }\n\
    \        groups.push_back(std::move(group));\n    };\n\n    for (int v = 0; v\
    \ < n; v++) {\n        if (ord[v] == -1) dfs(dfs, v);\n    }\n\n    std::reverse(groups.begin(),\
    \ groups.end());\n    for (int i = 0; i < int(groups.size()); i++) {\n       \
    \ for (int v : groups[i]) comp[v] = i;\n    }\n\n    return SccResult{int(groups.size()),\
    \ std::move(comp), std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\
    \n\n\n\n#line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<bool> negative;\n    T inf;\n    bool has_negative_cycle;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    bool affected_by_negative_cycle(int\
    \ v) const {\n        assert(0 <= v && v < int(negative.size()));\n        return\
    \ negative[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        assert(!affected_by_negative_cycle(t));\n        std::vector<int> result;\n\
    \        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g,\
    \ const std::vector<int>& sources,\n                                  T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    BellmanFordResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.negative.assign(n, false);\n\
    \    result.inf = inf;\n    result.has_negative_cycle = false;\n\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n\
    \    }\n\n    std::vector<int> relaxed_vertices;\n    for (int iter = 0; iter\
    \ < n; iter++) {\n        bool updated = false;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (result.dist[v] == inf) continue;\n            for (const\
    \ auto& e : g[v]) {\n                if (!e.alive) continue;\n               \
    \ T nd = result.dist[v] + e.cost;\n                if (result.dist[e.to] <= nd)\
    \ continue;\n                result.dist[e.to] = nd;\n                result.parent[e.to]\
    \ = v;\n                result.parent_edge[e.to] = e.id;\n                updated\
    \ = true;\n                if (iter == n - 1) relaxed_vertices.push_back(e.to);\n\
    \            }\n        }\n        if (!updated) break;\n    }\n\n    std::queue<int>\
    \ que;\n    for (int v : relaxed_vertices) {\n        if (result.negative[v])\
    \ continue;\n        result.negative[v] = true;\n        que.push(v);\n    }\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.negative[e.to]) continue;\n            result.negative[e.to]\
    \ = true;\n            que.push(e.to);\n        }\n    }\n\n    for (bool x :\
    \ result.negative) result.has_negative_cycle = result.has_negative_cycle || x;\n\
    \    return result;\n}\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const\
    \ Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return\
    \ bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n#line 8 \"graph/bfs.hpp\"\
    \n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ BfsResult {\n    std::vector<int> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n\n    bool reachable(int v) const {\n        assert(0 <= v &&\
    \ v < int(dist.size()));\n        return dist[v] != -1;\n    }\n\n    std::vector<int>\
    \ path(int t) const {\n        assert(reachable(t));\n        std::vector<int>\
    \ result;\n        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n\
    \        std::reverse(result.begin(), result.end());\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, const std::vector<int>&\
    \ sources) {\n    int n = g.size();\n    BfsResult result;\n    result.dist.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \n    std::queue<int> que;\n    for (int s : sources) {\n        assert(0 <= s\
    \ && s < n);\n        if (result.dist[s] != -1) continue;\n        result.dist[s]\
    \ = 0;\n        que.push(s);\n    }\n\n    while (!que.empty()) {\n        int\
    \ v = que.front();\n        que.pop();\n        for (const auto& e : g[v]) {\n\
    \            if (!e.alive) continue;\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dag_shortest_path.hpp\"\
    \n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\n\n#line 1 \"graph/topological_sort.hpp\"\
    \n\n\n\n#line 7 \"graph/topological_sort.hpp\"\n\n#line 9 \"graph/topological_sort.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::optional<std::vector<int>>\
    \ topological_sort(const Graph<T>& g) {\n    int n = g.size();\n    std::vector<int>\
    \ indeg(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e\
    \ : g[v]) {\n            if (!e.alive) continue;\n            indeg[e.to]++;\n\
    \        }\n    }\n\n    std::queue<int> que;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (indeg[v] == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n\
    \    order.reserve(n);\n    while (!que.empty()) {\n        int v = que.front();\n\
    \        que.pop();\n        order.push_back(v);\n        for (const auto& e :\
    \ g[v]) {\n            if (!e.alive) continue;\n            indeg[e.to]--;\n \
    \           if (indeg[e.to] == 0) que.push(e.to);\n        }\n    }\n\n    if\
    \ (int(order.size()) != n) return std::nullopt;\n    return order;\n}\n\ntemplate\
    \ <class T>\nbool is_dag(const Graph<T>& g) {\n    return topological_sort(g).has_value();\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_shortest_path.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagShortestPathResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> topological_order;\n    T inf;\n\n    bool\
    \ reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, const std::vector<int>& sources,\
    \ T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n   \
    \ auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\n\
    \    DagShortestPathResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.topological_order =\
    \ *order;\n    result.inf = inf;\n\n    for (int s : sources) {\n        assert(0\
    \ <= s && s < n);\n        if (result.dist[s] == T(0)) continue;\n        result.dist[s]\
    \ = T(0);\n    }\n\n    for (int v : *order) {\n        if (result.dist[v] ==\
    \ inf) continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            T nd = result.dist[v] + e.cost;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n        }\n    }\n\n   \
    \ return result;\n}\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return dag_shortest_path(g, std::vector<int>{s}, inf);\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dijkstra.hpp\"\
    \n\n\n\n#line 11 \"graph/dijkstra.hpp\"\n\n#line 13 \"graph/dijkstra.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DijkstraResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    T inf;\n\n    bool reachable(int v) const {\n        assert(0\
    \ <= v && v < int(dist.size()));\n        return dist[v] != inf;\n    }\n\n  \
    \  std::vector<int> path(int t) const {\n        assert(reachable(t));\n     \
    \   std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T> dijkstra(const\
    \ Graph<T>& g, const std::vector<int>& sources,\n                           T\
    \ inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    DijkstraResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using P =\
    \ std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           T nd = d + e.cost;\n            if (result.dist[e.to] <= nd) continue;\n\
    \            result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n \
    \           result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))\
    \ {\n    return dijkstra(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8\
    \ \"graph/warshall_floyd.hpp\"\n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::vector<std::vector<T>>\
    \ warshall_floyd(std::vector<std::vector<T>> dist,\n                         \
    \                  T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n\
    \ = int(dist.size());\n    for (int k = 0; k < n; k++) {\n        for (int i =\
    \ 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n           \
    \ for (int j = 0; j < n; j++) {\n                if (dist[k][j] == inf) continue;\n\
    \                T nd = dist[i][k] + dist[k][j];\n                if (nd < dist[i][j])\
    \ dist[i][j] = nd;\n            }\n        }\n    }\n    return dist;\n}\n\ntemplate\
    \ <class T>\nstd::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    std::vector<std::vector<T>>\
    \ dist(n, std::vector<T>(n, inf));\n    for (int i = 0; i < n; i++) dist[i][i]\
    \ = T(0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (e.cost < dist[e.from][e.to])\
    \ dist[e.from][e.to] = e.cost;\n        }\n    }\n    return warshall_floyd(std::move(dist),\
    \ inf);\n}\n\ntemplate <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/zero_one_bfs.hpp\"\
    \n\n\n\n#line 6 \"graph/zero_one_bfs.hpp\"\n#include <deque>\n#line 9 \"graph/zero_one_bfs.hpp\"\
    \n\n#line 11 \"graph/zero_one_bfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct ZeroOneBfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    int inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nZeroOneBfsResult\
    \ zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources,\n         \
    \                     int inf = std::numeric_limits<int>::max() / 2) {\n    int\
    \ n = g.size();\n    ZeroOneBfsResult result;\n    result.dist.assign(n, inf);\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n   \
    \ result.inf = inf;\n\n    std::deque<int> deq;\n    for (int s : sources) {\n\
    \        assert(0 <= s && s < n);\n        if (result.dist[s] == 0) continue;\n\
    \        result.dist[s] = 0;\n        deq.push_back(s);\n    }\n\n    while (!deq.empty())\
    \ {\n        int v = deq.front();\n        deq.pop_front();\n        for (const\
    \ auto& e : g[v]) {\n            if (!e.alive) continue;\n            int w;\n\
    \            if (e.cost == T(0)) {\n                w = 0;\n            } else\
    \ {\n                assert(e.cost == T(1));\n                w = 1;\n       \
    \     }\n            int nd = result.dist[v] + w;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n            if (w == 0)\
    \ {\n                deq.push_front(e.to);\n            } else {\n           \
    \     deq.push_back(e.to);\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int\
    \ s, int inf = std::numeric_limits<int>::max() / 2) {\n    return zero_one_bfs(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 10 \"graph/shortest_path.hpp\"\n\n\n#line 10 \"graph/directed.hpp\"\n\
    \n\n#line 1 \"graph/grid.hpp\"\n\n\n\n#include <array>\n#line 8 \"graph/grid.hpp\"\
    \n\n#line 10 \"graph/grid.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ Grid {\n   private:\n    int _h;\n    int _w;\n\n   public:\n    static constexpr\
    \ std::array<int, 4> di4 = {-1, 0, 1, 0};\n    static constexpr std::array<int,\
    \ 4> dj4 = {0, 1, 0, -1};\n    static constexpr std::array<int, 8> di8 = {-1,\
    \ -1, -1, 0, 0, 1, 1, 1};\n    static constexpr std::array<int, 8> dj8 = {-1,\
    \ 0, 1, -1, 1, -1, 0, 1};\n\n    Grid() : _h(0), _w(0) {}\n    Grid(int h, int\
    \ w) : _h(h), _w(w) {\n        assert(0 <= h);\n        assert(0 <= w);\n    }\n\
    \n    int height() const {\n        return _h;\n    }\n\n    int width() const\
    \ {\n        return _w;\n    }\n\n    int size() const {\n        return _h *\
    \ _w;\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    bool inside(int i, int j) const {\n        return 0 <= i && i < _h && 0\
    \ <= j && j < _w;\n    }\n\n    int id(int i, int j) const {\n        assert(inside(i,\
    \ j));\n        return i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v)\
    \ const {\n        assert(0 <= v && v < size());\n        return {v / _w, v %\
    \ _w};\n    }\n\n    std::vector<std::pair<int, int>> adj4(int i, int j) const\
    \ {\n        assert(inside(i, j));\n        std::vector<std::pair<int, int>> result;\n\
    \        result.reserve(4);\n        for (int k = 0; k < 4; k++) {\n         \
    \   int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni, nj)) result.emplace_back(ni,\
    \ nj);\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj8(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(8);\n        for (int k = 0; k < 8; k++)\
    \ {\n            int ni = i + di8[k], nj = j + dj8[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<int> adj4_ids(int v) const {\n        auto [i, j] = pos(v);\n\
    \        std::vector<int> result;\n        result.reserve(4);\n        for (auto\
    \ [ni, nj] : adj4(i, j)) result.push_back(id(ni, nj));\n        return result;\n\
    \    }\n\n    std::vector<int> adj8_ids(int v) const {\n        auto [i, j] =\
    \ pos(v);\n        std::vector<int> result;\n        result.reserve(8);\n    \
    \    for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni, nj));\n        return\
    \ result;\n    }\n\n    Graph<int> graph4() const {\n        return graph4([](int,\
    \ int) { return true; });\n    }\n\n    Graph<int> graph8() const {\n        return\
    \ graph8([](int, int) { return true; });\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph4(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj4(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph8(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj8(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/undirected.hpp\"\n\n\n\n#line 1 \"\
    graph/bipartite.hpp\"\n\n\n\n#line 8 \"graph/bipartite.hpp\"\n\n#line 10 \"graph/bipartite.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct BipartiteResult {\n    bool\
    \ is_bipartite;\n    std::vector<int> color;\n    std::vector<int> left_vertices;\n\
    \    std::vector<int> right_vertices;\n    std::vector<int> left_id;\n    std::vector<int>\
    \ right_id;\n};\n\ntemplate <class T>\nBipartiteResult bipartite(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite\
    \ = true;\n    result.color.assign(n, -1);\n    result.left_id.assign(n, -1);\n\
    \    result.right_id.assign(n, -1);\n\n    std::vector<std::vector<int>> adjacency(n);\n\
    \    for (const auto& e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n\
    \        adjacency[e.to].push_back(e.from);\n    }\n\n    std::queue<int> que;\n\
    \    for (int s = 0; s < n; s++) {\n        if (result.color[s] != -1) continue;\n\
    \        result.color[s] = 0;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop();\n            for\
    \ (int to : adjacency[v]) {\n                if (result.color[to] == -1) {\n \
    \                   result.color[to] = result.color[v] ^ 1;\n                \
    \    que.push(to);\n                } else if (result.color[to] == result.color[v])\
    \ {\n                    result.is_bipartite = false;\n                    return\
    \ result;\n                }\n            }\n        }\n    }\n\n    for (int\
    \ v = 0; v < n; v++) {\n        if (result.color[v] == 0) {\n            result.left_id[v]\
    \ = int(result.left_vertices.size());\n            result.left_vertices.push_back(v);\n\
    \        } else {\n            result.right_id[v] = int(result.right_vertices.size());\n\
    \            result.right_vertices.push_back(v);\n        }\n    }\n\n    return\
    \ result;\n}\n\ntemplate <class T>\nbool is_bipartite(const Graph<T>& g) {\n \
    \   return bipartite(g).is_bipartite;\n}\n\nstruct BipartiteVertexSet {\n    std::vector<int>\
    \ left;\n    std::vector<int> right;\n\n    int size() const {\n        return\
    \ int(left.size() + right.size());\n    }\n};\n\nstruct BipartiteMatching {\n\
    \    struct Edge {\n        int left;\n        int right;\n        int id;\n \
    \       bool alive;\n    };\n\n    struct Pair {\n        int left;\n        int\
    \ right;\n        int edge_id;\n    };\n\n   private:\n    int _left_size;\n \
    \   int _right_size;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<std::vector<int>> _radj;\n    std::vector<int> _left_match;\n\
    \    std::vector<int> _right_match;\n    std::vector<int> _left_match_edge;\n\
    \    std::vector<int> _right_match_edge;\n    bool _calculated;\n\n    void invalidate()\
    \ {\n        _calculated = false;\n    }\n\n    void ensure_matching() {\n   \
    \     if (!_calculated) max_matching();\n    }\n\n   public:\n    BipartiteMatching()\
    \ : BipartiteMatching(0, 0) {}\n\n    BipartiteMatching(int left_size, int right_size)\n\
    \        : _left_size(left_size),\n          _right_size(right_size),\n      \
    \    _adj(left_size),\n          _radj(right_size),\n          _left_match(left_size,\
    \ -1),\n          _right_match(right_size, -1),\n          _left_match_edge(left_size,\
    \ -1),\n          _right_match_edge(right_size, -1),\n          _calculated(false)\
    \ {\n        assert(0 <= left_size);\n        assert(0 <= right_size);\n    }\n\
    \n    int left_size() const {\n        return _left_size;\n    }\n\n    int right_size()\
    \ const {\n        return _right_size;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int add_edge(int left, int right)\
    \ {\n        assert(0 <= left && left < _left_size);\n        assert(0 <= right\
    \ && right < _right_size);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{left,\
    \ right, id, true});\n        _adj[left].push_back(id);\n        _radj[right].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        _left_match.assign(_left_size,\
    \ -1);\n        _right_match.assign(_right_size, -1);\n        _left_match_edge.assign(_left_size,\
    \ -1);\n        _right_match_edge.assign(_right_size, -1);\n\n        std::vector<int>\
    \ dist(_left_size);\n        auto bfs = [&]() -> bool {\n            std::queue<int>\
    \ que;\n            bool found = false;\n            for (int l = 0; l < _left_size;\
    \ l++) {\n                if (_left_match[l] == -1) {\n                    dist[l]\
    \ = 0;\n                    que.push(l);\n                } else {\n         \
    \           dist[l] = -1;\n                }\n            }\n\n            while\
    \ (!que.empty()) {\n                int l = que.front();\n                que.pop();\n\
    \                for (int id : _adj[l]) {\n                    const auto& e =\
    \ _edges[id];\n                    if (!e.alive) continue;\n                 \
    \   int next_left = _right_match[e.right];\n                    if (next_left\
    \ == -1) {\n                        found = true;\n                    } else\
    \ if (dist[next_left] == -1) {\n                        dist[next_left] = dist[l]\
    \ + 1;\n                        que.push(next_left);\n                    }\n\
    \                }\n            }\n            return found;\n        };\n\n \
    \       auto dfs = [&](auto self, int l) -> bool {\n            for (int id :\
    \ _adj[l]) {\n                const auto& e = _edges[id];\n                if\
    \ (!e.alive) continue;\n                int next_left = _right_match[e.right];\n\
    \                if (next_left != -1 && (dist[next_left] != dist[l] + 1 || !self(self,\
    \ next_left))) {\n                    continue;\n                }\n         \
    \       _left_match[l] = e.right;\n                _right_match[e.right] = l;\n\
    \                _left_match_edge[l] = id;\n                _right_match_edge[e.right]\
    \ = id;\n                return true;\n            }\n            dist[l] = -1;\n\
    \            return false;\n        };\n\n        int result = 0;\n        while\
    \ (bfs()) {\n            for (int l = 0; l < _left_size; l++) {\n            \
    \    if (_left_match[l] == -1 && dfs(dfs, l)) result++;\n            }\n     \
    \   }\n\n        _calculated = true;\n        return result;\n    }\n\n    int\
    \ matching_size() {\n        ensure_matching();\n        int result = 0;\n   \
    \     for (int right : _left_match) {\n            if (right != -1) result++;\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> left_match()\
    \ {\n        ensure_matching();\n        return _left_match;\n    }\n\n    std::vector<int>\
    \ right_match() {\n        ensure_matching();\n        return _right_match;\n\
    \    }\n\n    std::vector<Pair> matching() {\n        ensure_matching();\n   \
    \     std::vector<Pair> result;\n        for (int l = 0; l < _left_size; l++)\
    \ {\n            if (_left_match[l] != -1) result.push_back(Pair{l, _left_match[l],\
    \ _left_match_edge[l]});\n        }\n        return result;\n    }\n\n    BipartiteVertexSet\
    \ minimum_vertex_cover() {\n        ensure_matching();\n\n        std::vector<char>\
    \ visited_left(_left_size, false), visited_right(_right_size, false);\n      \
    \  std::queue<int> que;\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match[l] == -1) {\n                visited_left[l] = true;\n\
    \                que.push(l);\n            }\n        }\n\n        while (!que.empty())\
    \ {\n            int l = que.front();\n            que.pop();\n            for\
    \ (int id : _adj[l]) {\n                const auto& e = _edges[id];\n        \
    \        if (!e.alive || _left_match_edge[l] == id || visited_right[e.right])\
    \ continue;\n                visited_right[e.right] = true;\n                int\
    \ next_left = _right_match[e.right];\n                if (next_left != -1 && !visited_left[next_left])\
    \ {\n                    visited_left[next_left] = true;\n                   \
    \ que.push(next_left);\n                }\n            }\n        }\n\n      \
    \  BipartiteVertexSet result;\n        for (int l = 0; l < _left_size; l++) {\n\
    \            if (!visited_left[l]) result.left.push_back(l);\n        }\n    \
    \    for (int r = 0; r < _right_size; r++) {\n            if (visited_right[r])\
    \ result.right.push_back(r);\n        }\n        return result;\n    }\n\n   \
    \ BipartiteVertexSet maximum_independent_set() {\n        auto cover = minimum_vertex_cover();\n\
    \        std::vector<char> in_left_cover(_left_size, false), in_right_cover(_right_size,\
    \ false);\n        for (int l : cover.left) in_left_cover[l] = true;\n       \
    \ for (int r : cover.right) in_right_cover[r] = true;\n\n        BipartiteVertexSet\
    \ result;\n        for (int l = 0; l < _left_size; l++) {\n            if (!in_left_cover[l])\
    \ result.left.push_back(l);\n        }\n        for (int r = 0; r < _right_size;\
    \ r++) {\n            if (!in_right_cover[r]) result.right.push_back(r);\n   \
    \     }\n        return result;\n    }\n\n    std::optional<std::vector<int>>\
    \ minimum_edge_cover() {\n        ensure_matching();\n\n        std::vector<int>\
    \ result;\n        std::vector<char> covered_left(_left_size, false), covered_right(_right_size,\
    \ false);\n        std::vector<char> used_edge(_edges.size(), false);\n\n    \
    \    auto use_edge = [&](int id) {\n            if (used_edge[id]) return;\n \
    \           used_edge[id] = true;\n            result.push_back(id);\n       \
    \     covered_left[_edges[id].left] = true;\n            covered_right[_edges[id].right]\
    \ = true;\n        };\n\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match_edge[l] != -1) use_edge(_left_match_edge[l]);\n     \
    \   }\n\n        for (int l = 0; l < _left_size; l++) {\n            if (covered_left[l])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[l])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      for (int r = 0; r < _right_size; r++) {\n            if (covered_right[r])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _radj[r])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct BipartiteMatchingGraph {\n    BipartiteResult\
    \ parts;\n    BipartiteMatching matching;\n    std::vector<int> original_edge_id;\n\
    \n    int left_vertex(int left) const {\n        assert(0 <= left && left < int(parts.left_vertices.size()));\n\
    \        return parts.left_vertices[left];\n    }\n\n    int right_vertex(int\
    \ right) const {\n        assert(0 <= right && right < int(parts.right_vertices.size()));\n\
    \        return parts.right_vertices[right];\n    }\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>&\
    \ g) {\n    auto parts = bipartite(g);\n    if (!parts.is_bipartite) return std::nullopt;\n\
    \n    BipartiteMatchingGraph result;\n    result.parts = parts;\n    result.matching\
    \ = BipartiteMatching(int(parts.left_vertices.size()), int(parts.right_vertices.size()));\n\
    \n    for (const auto& e : g.edges()) {\n        int left, right;\n        if\
    \ (parts.color[e.from] == 0) {\n            left = parts.left_id[e.from];\n  \
    \          right = parts.right_id[e.to];\n        } else {\n            left =\
    \ parts.left_id[e.to];\n            right = parts.right_id[e.from];\n        }\n\
    \        int id = result.matching.add_edge(left, right);\n        if (int(result.original_edge_id.size())\
    \ <= id) result.original_edge_id.resize(id + 1);\n        result.original_edge_id[id]\
    \ = e.id;\n    }\n\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/connected_components.hpp\"\n\n\n\n#line 6 \"graph/connected_components.hpp\"\
    \n\n#line 1 \"data_structure/dsu.hpp\"\n\n\n\n#line 5 \"data_structure/dsu.hpp\"\
    \n#include <numeric>\n#line 7 \"data_structure/dsu.hpp\"\n\nnamespace m1une {\n\
    namespace data_structure {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i]\
    \ is the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ConnectedComponents {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n};\n\ntemplate <class T>\nConnectedComponents connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    m1une::data_structure::Dsu dsu(n);\n\
    \    for (const auto& e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents\
    \ result;\n    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n,\
    \ -1);\n    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n\
    \        if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader]\
    \ = int(result.groups.size());\n            result.groups.push_back({});\n   \
    \     }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 1 \"graph/general_matching.hpp\"\n\n\n\n#line 9 \"graph/general_matching.hpp\"\
    \n\n#line 11 \"graph/general_matching.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct GeneralMatching {\n    struct Edge {\n        int from;\n      \
    \  int to;\n        int id;\n        bool alive;\n\n        int other(int v) const\
    \ {\n            assert(v == from || v == to);\n            return from ^ to ^\
    \ v;\n        }\n    };\n\n    struct Pair {\n        int from;\n        int to;\n\
    \        int edge_id;\n    };\n\n   private:\n    int _n;\n    std::vector<Edge>\
    \ _edges;\n    std::vector<std::vector<int>> _adj;\n    std::vector<int> _mate;\n\
    \    std::vector<int> _mate_edge;\n    bool _calculated;\n\n    void invalidate()\
    \ {\n        _calculated = false;\n    }\n\n    void ensure_matching() {\n   \
    \     if (!_calculated) max_matching();\n    }\n\n    int lca(int a, int b, const\
    \ std::vector<int>& base, const std::vector<int>& parent) const {\n        std::vector<char>\
    \ used(_n, false);\n        while (true) {\n            a = base[a];\n       \
    \     used[a] = true;\n            if (_mate[a] == -1) break;\n            a =\
    \ parent[_mate[a]];\n        }\n        while (true) {\n            b = base[b];\n\
    \            if (used[b]) return b;\n            b = parent[_mate[b]];\n     \
    \   }\n    }\n\n    void mark_path(int v, int b, int child, int child_edge, std::vector<int>&\
    \ base, std::vector<int>& parent,\n                   std::vector<int>& parent_edge,\
    \ std::vector<char>& blossom) const {\n        while (base[v] != b) {\n      \
    \      blossom[base[v]] = true;\n            blossom[base[_mate[v]]] = true;\n\
    \            parent[v] = child;\n            parent_edge[v] = child_edge;\n\n\
    \            int matched = _mate[v];\n            int next_v = parent[matched];\n\
    \            int next_edge = parent_edge[matched];\n            child = matched;\n\
    \            child_edge = next_edge;\n            v = next_v;\n        }\n   \
    \ }\n\n    int find_augmenting_path(int root, std::vector<int>& parent, std::vector<int>&\
    \ parent_edge) const {\n        std::vector<char> used(_n, false), blossom(_n,\
    \ false);\n        std::vector<int> base(_n);\n        std::queue<int> que;\n\n\
    \        parent.assign(_n, -1);\n        parent_edge.assign(_n, -1);\n       \
    \ for (int i = 0; i < _n; i++) base[i] = i;\n\n        used[root] = true;\n  \
    \      que.push(root);\n        while (!que.empty()) {\n            int v = que.front();\n\
    \            que.pop();\n            for (int id : _adj[v]) {\n              \
    \  const auto& e = _edges[id];\n                if (!e.alive) continue;\n    \
    \            int u = e.other(v);\n                if (base[v] == base[u] || _mate[v]\
    \ == u) continue;\n\n                if (u == root || (_mate[u] != -1 && parent[_mate[u]]\
    \ != -1)) {\n                    int cur_base = lca(v, u, base, parent);\n   \
    \                 std::fill(blossom.begin(), blossom.end(), false);\n        \
    \            mark_path(v, cur_base, u, id, base, parent, parent_edge, blossom);\n\
    \                    mark_path(u, cur_base, v, id, base, parent, parent_edge,\
    \ blossom);\n                    for (int i = 0; i < _n; i++) {\n            \
    \            if (!blossom[base[i]]) continue;\n                        base[i]\
    \ = cur_base;\n                        if (!used[i]) {\n                     \
    \       used[i] = true;\n                            que.push(i);\n          \
    \              }\n                    }\n                } else if (parent[u]\
    \ == -1) {\n                    parent[u] = v;\n                    parent_edge[u]\
    \ = id;\n                    if (_mate[u] == -1) return u;\n                 \
    \   int next = _mate[u];\n                    used[next] = true;\n           \
    \         que.push(next);\n                }\n            }\n        }\n     \
    \   return -1;\n    }\n\n   public:\n    GeneralMatching() : GeneralMatching(0)\
    \ {}\n\n    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n,\
    \ -1), _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int from, int to) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        _mate.assign(_n,\
    \ -1);\n        _mate_edge.assign(_n, -1);\n\n        int result = 0;\n      \
    \  std::vector<int> parent, parent_edge;\n        for (int root = 0; root < _n;\
    \ root++) {\n            if (_mate[root] != -1) continue;\n            int finish\
    \ = find_augmenting_path(root, parent, parent_edge);\n            if (finish ==\
    \ -1) continue;\n\n            result++;\n            while (finish != -1) {\n\
    \                int prev = parent[finish];\n                int next = _mate[prev];\n\
    \                int edge_id = parent_edge[finish];\n                _mate[finish]\
    \ = prev;\n                _mate[prev] = finish;\n                _mate_edge[finish]\
    \ = edge_id;\n                _mate_edge[prev] = edge_id;\n                finish\
    \ = next;\n            }\n        }\n\n        _calculated = true;\n        return\
    \ result;\n    }\n\n    int matching_size() {\n        ensure_matching();\n  \
    \      int result = 0;\n        for (int v = 0; v < _n; v++) {\n            if\
    \ (v < _mate[v]) result++;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ mate() {\n        ensure_matching();\n        return _mate;\n    }\n\n    std::vector<int>\
    \ mate_edge() {\n        ensure_matching();\n        return _mate_edge;\n    }\n\
    \n    std::vector<Pair> matching() {\n        ensure_matching();\n        std::vector<Pair>\
    \ result;\n        for (int v = 0; v < _n; v++) {\n            if (v < _mate[v])\
    \ result.push_back(Pair{v, _mate[v], _mate_edge[v]});\n        }\n        return\
    \ result;\n    }\n\n    std::optional<std::vector<int>> minimum_edge_cover() {\n\
    \        ensure_matching();\n\n        std::vector<int> result;\n        std::vector<char>\
    \ covered(_n, false), used_edge(_edges.size(), false);\n\n        auto use_edge\
    \ = [&](int id) {\n            if (used_edge[id]) return;\n            used_edge[id]\
    \ = true;\n            result.push_back(id);\n            covered[_edges[id].from]\
    \ = true;\n            covered[_edges[id].to] = true;\n        };\n\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (v < _mate[v]) use_edge(_mate_edge[v]);\n\
    \        }\n\n        for (int v = 0; v < _n; v++) {\n            if (covered[v])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[v])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct GeneralMatchingGraph {\n    GeneralMatching\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralMatchingGraph make_general_matching(const Graph<T>& g) {\n    GeneralMatchingGraph\
    \ result;\n    result.matching = GeneralMatching(g.size());\n    for (const auto&\
    \ e : g.edges()) {\n        int id = result.matching.add_edge(e.from, e.to);\n\
    \        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id\
    \ + 1);\n        result.original_edge_id[id] = e.id;\n    }\n    return result;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/kruskal.hpp\"\
    \n\n\n\n#line 6 \"graph/kruskal.hpp\"\n\n#line 9 \"graph/kruskal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct MinimumSpanningForest\
    \ {\n    T cost;\n    std::vector<Edge<T>> edges;\n    int components;\n\n   \
    \ bool is_spanning_tree(int n) const {\n        return components <= 1 && int(edges.size())\
    \ == std::max(0, n - 1);\n    }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T>\
    \ kruskal(const Graph<T>& g) {\n    int n = g.size();\n    auto edges = g.edges();\n\
    \    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {\n\
    \        return a.cost < b.cost;\n    });\n\n    m1une::data_structure::Dsu dsu(n);\n\
    \    MinimumSpanningForest<T> result;\n    result.cost = T(0);\n    result.components\
    \ = n;\n\n    for (const auto& e : edges) {\n        if (dsu.same(e.from, e.to))\
    \ continue;\n        dsu.merge(e.from, e.to);\n        result.cost += e.cost;\n\
    \        result.edges.push_back(e);\n        result.components--;\n    }\n\n \
    \   return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line\
    \ 1 \"graph/lowlink.hpp\"\n\n\n\n#line 6 \"graph/lowlink.hpp\"\n\n#line 8 \"graph/lowlink.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct LowLinkResult\
    \ {\n    std::vector<int> ord;\n    std::vector<int> low;\n    std::vector<int>\
    \ articulation;\n    std::vector<Edge<T>> bridges;\n    std::vector<int> bridge_ids;\n\
    };\n\ntemplate <class T>\nLowLinkResult<T> lowlink(const Graph<T>& g) {\n    int\
    \ n = g.size();\n    LowLinkResult<T> result;\n    result.ord.assign(n, -1);\n\
    \    result.low.assign(n, -1);\n    int now = 0;\n\n    auto dfs = [&](auto self,\
    \ int v, int parent_edge) -> void {\n        result.ord[v] = result.low[v] = now++;\n\
    \        int child_count = 0;\n        bool is_articulation = false;\n\n     \
    \   for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n      \
    \      if (e.id == parent_edge) continue;\n            int to = e.to;\n      \
    \      if (result.ord[to] == -1) {\n                child_count++;\n         \
    \       self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
    \ result.low[to]);\n                if (parent_edge != -1 && result.ord[v] <=\
    \ result.low[to]) is_articulation = true;\n                if (result.ord[v] <\
    \ result.low[to]) {\n                    result.bridges.push_back(e);\n      \
    \              result.bridge_ids.push_back(e.id);\n                }\n       \
    \     } else {\n                result.low[v] = std::min(result.low[v], result.ord[to]);\n\
    \            }\n        }\n\n        if (parent_edge == -1 && child_count >= 2)\
    \ is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/maximum_clique.hpp\"\
    \n\n\n\n#line 7 \"graph/maximum_clique.hpp\"\n\n#line 9 \"graph/maximum_clique.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct MaximumCliqueResult {\n   \
    \ std::vector<int> vertices;\n\n    int size() const {\n        return int(vertices.size());\n\
    \    }\n\n    bool empty() const {\n        return vertices.empty();\n    }\n\
    };\n\nstruct MaximumIndependentSetResult {\n    std::vector<int> vertices;\n\n\
    \    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
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
    \  // namespace m1une\n\n\n#line 14 \"graph/undirected.hpp\"\n\n\n#line 10 \"\
    graph/all.hpp\"\n\n\n#line 11 \"verify/graph/graph_algorithms.test.cpp\"\n\nusing\
    \ m1une::graph::Graph;\n\nvoid test_graph_container() {\n    Graph<int> g(2);\n\
    \    assert(g.size() == 2);\n    int added = g.add_vertex();\n    assert(added\
    \ == 2);\n    int e0 = g.add_directed_edge(0, 1, 4);\n    int e1 = g.add_edge(1,\
    \ 2, 5);\n    assert(e0 == 0);\n    assert(e1 == 1);\n    assert(g.edge_count()\
    \ == 2);\n    assert(g[1].size() == 1);\n    assert(g.edges().size() == 2);\n\
    \    auto rev = g.reversed();\n    assert(rev[1][0].to == 0);\n}\n\nvoid test_edge_alive()\
    \ {\n    Graph<int> g(4);\n    int e01 = g.add_edge(0, 1);\n    int e12 = g.add_edge(1,\
    \ 2);\n    int e23 = g.add_edge(2, 3);\n    (void)e01;\n    (void)e23;\n\n   \
    \ assert(g.edge_count() == 3);\n    assert(g.edges().size() == 3);\n    auto res\
    \ = m1une::graph::bfs(g, 0);\n    assert(res.dist[3] == 3);\n\n    g.erase_edge(e12);\n\
    \    assert(!g.is_edge_alive(e12));\n    assert(g.edges().size() == 2);\n    assert(g.edges(true).size()\
    \ == 3);\n    auto cut = m1une::graph::bfs(g, 0);\n    assert(!cut.reachable(3));\n\
    \n    auto rev = g.reversed();\n    assert(!rev.is_edge_alive(e12));\n    assert(rev.edges().size()\
    \ == 2);\n\n    g.revive_edge(e12);\n    assert(g.is_edge_alive(e12));\n    auto\
    \ restored = m1une::graph::bfs(g, 0);\n    assert(restored.dist[3] == 3);\n}\n\
    \nvoid test_bfs() {\n    Graph<int> g(5);\n    g.add_directed_edge(0, 1);\n  \
    \  g.add_directed_edge(0, 2);\n    g.add_directed_edge(1, 3);\n    g.add_directed_edge(2,\
    \ 3);\n    g.add_directed_edge(3, 4);\n\n    auto res = m1une::graph::bfs(g, 0);\n\
    \    assert(res.dist[0] == 0);\n    assert(res.dist[3] == 2);\n    assert(res.dist[4]\
    \ == 3);\n    auto path = res.path(4);\n    assert(path.front() == 0);\n    assert(path.back()\
    \ == 4);\n    assert(path.size() == 4);\n}\n\nvoid test_dijkstra() {\n    Graph<long\
    \ long> g(5);\n    g.add_directed_edge(0, 1, 4);\n    g.add_directed_edge(0, 2,\
    \ 1);\n    g.add_directed_edge(2, 1, 2);\n    g.add_directed_edge(1, 3, 1);\n\
    \    g.add_directed_edge(2, 3, 7);\n    g.add_directed_edge(3, 4, 3);\n\n    auto\
    \ res = m1une::graph::dijkstra(g, 0);\n    assert(res.dist[1] == 3);\n    assert(res.dist[4]\
    \ == 7);\n    assert((res.path(4) == std::vector<int>{0, 2, 1, 3, 4}));\n}\n\n\
    void test_zero_one_bfs() {\n    Graph<int> g(6);\n    g.add_directed_edge(0, 1,\
    \ 1);\n    g.add_directed_edge(0, 2, 0);\n    g.add_directed_edge(2, 1, 0);\n\
    \    g.add_directed_edge(1, 3, 1);\n    g.add_directed_edge(2, 3, 1);\n    g.add_directed_edge(3,\
    \ 4, 0);\n\n    auto res = m1une::graph::zero_one_bfs(g, 0);\n    assert(res.dist[0]\
    \ == 0);\n    assert(res.dist[1] == 0);\n    assert(res.dist[3] == 1);\n    assert(res.dist[4]\
    \ == 1);\n    assert(!res.reachable(5));\n    assert((res.path(4) == std::vector<int>{0,\
    \ 2, 3, 4}));\n\n    auto multi = m1une::graph::zero_one_bfs(g, std::vector<int>{1,\
    \ 5});\n    assert(multi.dist[1] == 0);\n    assert(multi.dist[4] == 1);\n   \
    \ assert(multi.dist[5] == 0);\n}\n\nvoid test_bellman_ford() {\n    Graph<long\
    \ long> g(5);\n    g.add_directed_edge(0, 1, 1);\n    g.add_directed_edge(1, 2,\
    \ -3);\n    g.add_directed_edge(2, 3, 1);\n    g.add_directed_edge(3, 1, 1);\n\
    \    g.add_directed_edge(0, 4, 5);\n\n    auto res = m1une::graph::bellman_ford(g,\
    \ 0);\n    assert(res.has_negative_cycle);\n    assert(res.affected_by_negative_cycle(1));\n\
    \    assert(res.affected_by_negative_cycle(2));\n    assert(res.affected_by_negative_cycle(3));\n\
    \    assert(!res.affected_by_negative_cycle(4));\n    assert(res.dist[4] == 5);\n\
    }\n\nvoid test_dag_shortest_path() {\n    Graph<long long> g(6);\n    g.add_directed_edge(0,\
    \ 1, 2);\n    g.add_directed_edge(0, 2, 5);\n    g.add_directed_edge(1, 2, -4);\n\
    \    g.add_directed_edge(1, 4, 10);\n    g.add_directed_edge(2, 3, 3);\n    g.add_directed_edge(3,\
    \ 4, 1);\n\n    auto res = m1une::graph::dag_shortest_path(g, 0);\n    assert(res.has_value());\n\
    \    assert(res->dist[0] == 0);\n    assert(res->dist[2] == -2);\n    assert(res->dist[4]\
    \ == 2);\n    assert(!res->reachable(5));\n    assert((res->path(4) == std::vector<int>{0,\
    \ 1, 2, 3, 4}));\n    assert(res->topological_order.size() == 6);\n\n    auto\
    \ multi = m1une::graph::dag_shortest_path(g, std::vector<int>{1, 5});\n    assert(multi.has_value());\n\
    \    assert(multi->dist[4] == 0);\n    assert(multi->dist[5] == 0);\n\n    g.add_directed_edge(4,\
    \ 1, 1);\n    auto cyclic = m1une::graph::dag_shortest_path(g, 0);\n    assert(!cyclic.has_value());\n\
    }\n\nvoid test_warshall_floyd() {\n    Graph<long long> g(4);\n    g.add_directed_edge(0,\
    \ 1, 3);\n    g.add_directed_edge(1, 2, 4);\n    g.add_directed_edge(0, 2, 10);\n\
    \    g.add_directed_edge(2, 3, -2);\n\n    auto dist = m1une::graph::warshall_floyd(g);\n\
    \    assert(dist[0][2] == 7);\n    assert(dist[0][3] == 5);\n    assert(!m1une::graph::has_negative_cycle(dist));\n\
    \n    bool changed = m1une::graph::warshall_floyd_add_directed_edge(dist, 3, 1,\
    \ 1LL);\n    assert(changed);\n    assert(dist[0][1] == 3);\n    assert(dist[2][1]\
    \ == -1);\n    assert(dist[3][2] == 5);\n\n    changed = m1une::graph::warshall_floyd_add_directed_edge(dist,\
    \ 0, 2, 100LL);\n    assert(!changed);\n\n    Graph<long long> undirected(4);\n\
    \    undirected.add_edge(0, 1, 10);\n    undirected.add_edge(1, 2, 10);\n    undirected.add_edge(2,\
    \ 3, 10);\n    auto udist = m1une::graph::warshall_floyd(undirected);\n    changed\
    \ = m1une::graph::warshall_floyd_add_undirected_edge(udist, 0, 3, 1LL);\n    assert(changed);\n\
    \    assert(udist[0][3] == 1);\n    assert(udist[3][0] == 1);\n    assert(udist[1][3]\
    \ == 11);\n}\n\nvoid test_topological_sort() {\n    Graph<int> g(4);\n    g.add_directed_edge(0,\
    \ 1);\n    g.add_directed_edge(0, 2);\n    g.add_directed_edge(1, 3);\n    g.add_directed_edge(2,\
    \ 3);\n\n    auto order = m1une::graph::topological_sort(g);\n    assert(order.has_value());\n\
    \    std::vector<int> pos(4);\n    for (int i = 0; i < 4; i++) pos[(*order)[i]]\
    \ = i;\n    for (int v = 0; v < 4; v++) {\n        for (const auto& e : g[v])\
    \ assert(pos[e.from] < pos[e.to]);\n    }\n\n    g.add_directed_edge(3, 0);\n\
    \    assert(!m1une::graph::is_dag(g));\n}\n\nvoid test_scc() {\n    Graph<int>\
    \ g(4);\n    g.add_directed_edge(0, 1);\n    g.add_directed_edge(1, 0);\n    g.add_directed_edge(1,\
    \ 2);\n    g.add_directed_edge(2, 3);\n    g.add_directed_edge(3, 2);\n\n    auto\
    \ scc = m1une::graph::strongly_connected_components(g);\n    assert(scc.count\
    \ == 2);\n    assert(scc.same(0, 1));\n    assert(scc.same(2, 3));\n    assert(!scc.same(0,\
    \ 2));\n    auto dag = scc.dag(g);\n    assert(dag.size() == 2);\n    assert(dag.edge_count()\
    \ == 1);\n}\n\nvoid test_lowlink() {\n    Graph<int> g(5);\n    g.add_edge(0,\
    \ 1);\n    g.add_edge(1, 2);\n    g.add_edge(2, 0);\n    int b0 = g.add_edge(1,\
    \ 3);\n    int b1 = g.add_edge(3, 4);\n\n    auto res = m1une::graph::lowlink(g);\n\
    \    assert((res.articulation == std::vector<int>{1, 3}));\n    assert((res.bridge_ids\
    \ == std::vector<int>{b0, b1}));\n}\n\nvoid test_bipartite_and_components() {\n\
    \    Graph<int> square(4);\n    square.add_edge(0, 1);\n    square.add_edge(1,\
    \ 2);\n    square.add_edge(2, 3);\n    square.add_edge(3, 0);\n    auto bp = m1une::graph::bipartite(square);\n\
    \    assert(bp.is_bipartite);\n    assert(bp.color[0] == bp.color[2]);\n    assert((bp.left_vertices\
    \ == std::vector<int>{0, 2}));\n    assert((bp.right_vertices == std::vector<int>{1,\
    \ 3}));\n    assert(bp.left_id[2] == 1);\n    assert(bp.right_id[3] == 1);\n \
    \   auto built = m1une::graph::make_bipartite_matching(square);\n    assert(built.has_value());\n\
    \    assert(built->matching.left_size() == 2);\n    assert(built->matching.right_size()\
    \ == 2);\n    assert(built->matching.max_matching() == 2);\n    for (const auto&\
    \ p : built->matching.matching()) {\n        int u = built->left_vertex(p.left);\n\
    \        int v = built->right_vertex(p.right);\n        assert(bp.color[u] ==\
    \ 0);\n        assert(bp.color[v] == 1);\n        assert(square.is_edge_alive(built->original_edge(p.edge_id)));\n\
    \    }\n\n    Graph<int> triangle(3);\n    triangle.add_edge(0, 1);\n    triangle.add_edge(1,\
    \ 2);\n    triangle.add_edge(2, 0);\n    assert(!m1une::graph::is_bipartite(triangle));\n\
    \    assert(!m1une::graph::make_bipartite_matching(triangle).has_value());\n\n\
    \    Graph<int> cc_graph(5);\n    cc_graph.add_edge(0, 1);\n    cc_graph.add_edge(2,\
    \ 3);\n    auto cc = m1une::graph::connected_components(cc_graph);\n    assert(cc.count\
    \ == 3);\n    assert(cc.same(0, 1));\n    assert(cc.same(2, 3));\n    assert(!cc.same(0,\
    \ 2));\n\n    Graph<int> directed(2);\n    directed.add_directed_edge(1, 0);\n\
    \    assert(m1une::graph::is_bipartite(directed));\n    auto weak = m1une::graph::connected_components(directed);\n\
    \    assert(weak.count == 1);\n\n    m1une::graph::BipartiteMatching bm(3, 2);\n\
    \    int e00 = bm.add_edge(0, 0);\n    int e10 = bm.add_edge(1, 0);\n    int e11\
    \ = bm.add_edge(1, 1);\n    int e21 = bm.add_edge(2, 1);\n    assert(bm.left_size()\
    \ == 3);\n    assert(bm.right_size() == 2);\n    assert(bm.edge_count() == 4);\n\
    \    assert(bm.get_edge(e10).left == 1);\n    assert(bm.max_matching() == 2);\n\
    \    assert(bm.matching_size() == 2);\n    auto pairs = bm.matching();\n    assert(pairs.size()\
    \ == 2);\n    auto left_match = bm.left_match();\n    auto right_match = bm.right_match();\n\
    \    for (const auto& p : pairs) {\n        assert(left_match[p.left] == p.right);\n\
    \        assert(right_match[p.right] == p.left);\n    }\n\n    auto cover = bm.minimum_vertex_cover();\n\
    \    assert(cover.left.empty());\n    assert((cover.right == std::vector<int>{0,\
    \ 1}));\n    assert(cover.size() == 2);\n    auto independent = bm.maximum_independent_set();\n\
    \    assert((independent.left == std::vector<int>{0, 1, 2}));\n    assert(independent.right.empty());\n\
    \n    auto edge_cover = bm.minimum_edge_cover();\n    assert(edge_cover.has_value());\n\
    \    assert(edge_cover->size() == 3);\n    std::vector<bool> covered_left(3, false),\
    \ covered_right(2, false);\n    for (int id : *edge_cover) {\n        auto edge\
    \ = bm.get_edge(id);\n        covered_left[edge.left] = true;\n        covered_right[edge.right]\
    \ = true;\n    }\n    assert((covered_left == std::vector<bool>{true, true, true}));\n\
    \    assert((covered_right == std::vector<bool>{true, true}));\n\n    bm.erase_edge(e11);\n\
    \    bm.erase_edge(e21);\n    assert(!bm.is_edge_alive(e21));\n    assert(bm.edges().size()\
    \ == 2);\n    assert(bm.edges(true).size() == 4);\n    assert(bm.max_matching()\
    \ == 1);\n    bm.revive_edge(e21);\n    assert(bm.max_matching() == 2);\n\n  \
    \  m1une::graph::BipartiteMatching isolated(1, 1);\n    assert(!isolated.minimum_edge_cover().has_value());\n\
    \n    (void)e00;\n}\n\nvoid test_general_matching() {\n    m1une::graph::GeneralMatching\
    \ blossom(6);\n    int e01 = blossom.add_edge(0, 1);\n    int e12 = blossom.add_edge(1,\
    \ 2);\n    int e23 = blossom.add_edge(2, 3);\n    int e34 = blossom.add_edge(3,\
    \ 4);\n    int e40 = blossom.add_edge(4, 0);\n    int e15 = blossom.add_edge(1,\
    \ 5);\n    (void)e12;\n    (void)e23;\n    (void)e34;\n    (void)e40;\n\n    assert(blossom.size()\
    \ == 6);\n    assert(blossom.edge_count() == 6);\n    assert(blossom.get_edge(e01).other(0)\
    \ == 1);\n    assert(blossom.max_matching() == 3);\n    assert(blossom.matching_size()\
    \ == 3);\n    auto mate = blossom.mate();\n    auto mate_edge = blossom.mate_edge();\n\
    \    for (int v = 0; v < 6; v++) {\n        assert(mate[v] != -1);\n        assert(mate[mate[v]]\
    \ == v);\n        assert(mate_edge[v] != -1);\n    }\n    auto pairs = blossom.matching();\n\
    \    assert(pairs.size() == 3);\n    for (const auto& p : pairs) {\n        assert(mate[p.from]\
    \ == p.to);\n        assert(mate[p.to] == p.from);\n    }\n\n    auto edge_cover\
    \ = blossom.minimum_edge_cover();\n    assert(edge_cover.has_value());\n    assert(edge_cover->size()\
    \ == 3);\n    std::vector<bool> covered(6, false);\n    for (int id : *edge_cover)\
    \ {\n        auto edge = blossom.get_edge(id);\n        covered[edge.from] = true;\n\
    \        covered[edge.to] = true;\n    }\n    assert((covered == std::vector<bool>{true,\
    \ true, true, true, true, true}));\n\n    blossom.erase_edge(e15);\n    assert(!blossom.is_edge_alive(e15));\n\
    \    assert(blossom.edges().size() == 5);\n    assert(blossom.edges(true).size()\
    \ == 6);\n    assert(blossom.max_matching() == 2);\n    assert(!blossom.minimum_edge_cover().has_value());\n\
    \    blossom.revive_edge(e15);\n    assert(blossom.max_matching() == 3);\n\n \
    \   m1une::graph::GeneralMatching path(3);\n    path.add_edge(0, 1);\n    path.add_edge(1,\
    \ 2);\n    auto path_cover = path.minimum_edge_cover();\n    assert(path_cover.has_value());\n\
    \    assert(path_cover->size() == 2);\n\n    m1une::graph::GeneralMatching isolated(1);\n\
    \    assert(!isolated.minimum_edge_cover().has_value());\n\n    Graph<int> g(4);\n\
    \    int g01 = g.add_edge(0, 1);\n    int g12 = g.add_edge(1, 2);\n    int g20\
    \ = g.add_edge(2, 0);\n    int g23 = g.add_edge(2, 3);\n    (void)g01;\n    (void)g12;\n\
    \    (void)g20;\n    auto built = m1une::graph::make_general_matching(g);\n  \
    \  assert(built.matching.max_matching() == 2);\n    for (const auto& p : built.matching.matching())\
    \ {\n        assert(g.is_edge_alive(built.original_edge(p.edge_id)));\n    }\n\
    \    assert(g.is_edge_alive(g23));\n}\n\nvoid test_maximum_clique_and_independent_set()\
    \ {\n    Graph<int> g(7);\n    int removed_clique_edge = -1;\n    for (int i =\
    \ 0; i < 4; i++) {\n        for (int j = i + 1; j < 4; j++) {\n            int\
    \ id = g.add_edge(i, j);\n            if (i == 0 && j == 2) removed_clique_edge\
    \ = id;\n        }\n    }\n    g.add_edge(4, 0);\n    g.add_edge(4, 1);\n    g.add_edge(5,\
    \ 1);\n    g.add_edge(5, 2);\n\n    auto clique = m1une::graph::maximum_clique(g);\n\
    \    assert(clique.size() == 4);\n    assert((clique.vertices == std::vector<int>{0,\
    \ 1, 2, 3}));\n    assert(m1une::graph::is_clique(g, clique.vertices));\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 4);\n\n    auto independent = m1une::graph::maximum_independent_set(g);\n\
    \    assert(independent.size() == 4);\n    assert((independent.vertices == std::vector<int>{3,\
    \ 4, 5, 6}));\n    assert(m1une::graph::is_independent_set(g, independent.vertices));\n\
    \    assert(m1une::graph::maximum_independent_set_size(g) == 4);\n\n    assert(!m1une::graph::is_clique(g,\
    \ std::vector<int>{0, 2, 4}));\n    assert(!m1une::graph::is_independent_set(g,\
    \ std::vector<int>{4, 0}));\n\n    g.erase_edge(removed_clique_edge);\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 3);\n    g.revive_edge(removed_clique_edge);\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 4);\n\n    Graph<int> directed(3);\n    directed.add_directed_edge(0, 1);\n\
    \    directed.add_directed_edge(1, 2);\n    auto directed_clique = m1une::graph::maximum_clique(directed);\n\
    \    auto directed_independent = m1une::graph::maximum_independent_set(directed);\n\
    \    assert(directed_clique.size() == 2);\n    assert(directed_independent.size()\
    \ == 2);\n    assert((directed_independent.vertices == std::vector<int>{0, 2}));\n\
    \n    Graph<int> empty(4);\n    assert(m1une::graph::maximum_clique_size(empty)\
    \ == 1);\n    assert(m1une::graph::maximum_independent_set_size(empty) == 4);\n\
    \n    Graph<int> none(0);\n    assert(m1une::graph::maximum_clique(none).empty());\n\
    \    assert(m1une::graph::maximum_independent_set(none).empty());\n}\n\nvoid test_cycle_detection()\
    \ {\n    Graph<int> dg(3);\n    dg.add_directed_edge(0, 1);\n    dg.add_directed_edge(1,\
    \ 2);\n    dg.add_directed_edge(2, 0);\n    auto directed = m1une::graph::find_directed_cycle(dg);\n\
    \    assert(!directed.empty());\n    assert(directed.vertices.front() == directed.vertices.back());\n\
    \    assert(directed.edge_ids.size() + 1 == directed.vertices.size());\n\n   \
    \ Graph<int> ug(4);\n    ug.add_edge(0, 1);\n    ug.add_edge(1, 2);\n    ug.add_edge(2,\
    \ 0);\n    ug.add_edge(2, 3);\n    auto undirected = m1une::graph::find_undirected_cycle(ug);\n\
    \    assert(!undirected.empty());\n    assert(undirected.vertices.front() == undirected.vertices.back());\n\
    }\n\nvoid test_kruskal() {\n    Graph<long long> g(4);\n    g.add_edge(0, 1, 1);\n\
    \    g.add_edge(1, 2, 2);\n    g.add_edge(2, 3, 3);\n    g.add_edge(0, 3, 10);\n\
    \    g.add_edge(0, 2, 4);\n\n    auto mst = m1une::graph::kruskal(g);\n    assert(mst.cost\
    \ == 6);\n    assert(mst.edges.size() == 3);\n    assert(mst.components == 1);\n\
    \    assert(mst.is_spanning_tree(g.size()));\n}\n\nvoid test_grid() {\n    m1une::graph::Grid\
    \ grid(3, 4);\n    assert(grid.height() == 3);\n    assert(grid.width() == 4);\n\
    \    assert(grid.size() == 12);\n    assert(grid.inside(2, 3));\n    assert(!grid.inside(3,\
    \ 0));\n    assert(grid.id(2, 3) == 11);\n    assert(grid.pos(6) == std::make_pair(1,\
    \ 2));\n\n    auto adj4 = grid.adj4(0, 0);\n    assert((adj4 == std::vector<std::pair<int,\
    \ int>>{{0, 1}, {1, 0}}));\n\n    auto adj8 = grid.adj8(1, 1);\n    assert(adj8.size()\
    \ == 8);\n    auto adj4_ids = grid.adj4_ids(grid.id(1, 1));\n    std::set<int>\
    \ expected_ids = {grid.id(0, 1), grid.id(1, 2), grid.id(2, 1), grid.id(1, 0)};\n\
    \    assert(std::set<int>(adj4_ids.begin(), adj4_ids.end()) == expected_ids);\n\
    \n    std::vector<std::string> s = {\n        \"....\",\n        \".##.\",\n \
    \       \"....\",\n    };\n    auto passable = [&](int i, int j) {\n        return\
    \ s[i][j] != '#';\n    };\n\n    auto g4 = grid.graph4(passable);\n    assert(g4.size()\
    \ == grid.size());\n    assert(g4[grid.id(1, 1)].empty());\n    auto res = m1une::graph::bfs(g4,\
    \ grid.id(0, 0));\n    assert(res.dist[grid.id(2, 3)] == 5);\n    assert(res.dist[grid.id(1,\
    \ 1)] == -1);\n\n    auto g8 = grid.graph8(passable);\n    auto res8 = m1une::graph::bfs(g8,\
    \ grid.id(0, 0));\n    assert(res8.dist[grid.id(2, 3)] == 4);\n\n    auto all4\
    \ = grid.graph4();\n    assert(all4.edge_count() == 17);\n}\n\nvoid test_max_flow()\
    \ {\n    m1une::graph::MaxFlow<long long> mf(4);\n    int e0 = mf.add_edge(0,\
    \ 1, 2);\n    int e1 = mf.add_edge(0, 2, 1);\n    int e2 = mf.add_edge(1, 2, 1);\n\
    \    int e3 = mf.add_edge(1, 3, 1);\n    int e4 = mf.add_edge(2, 3, 2);\n    (void)e1;\n\
    \    (void)e2;\n    (void)e3;\n    (void)e4;\n\n    assert(mf.size() == 4);\n\
    \    assert(mf.edge_count() == 5);\n    assert(mf.max_flow(0, 3) == 3);\n    auto\
    \ edges = mf.edges();\n    long long outgoing = 0;\n    for (const auto& e : edges)\
    \ {\n        if (e.from == 0) outgoing += e.flow;\n        assert(0 <= e.flow\
    \ && e.flow <= e.cap);\n    }\n    assert(outgoing == 3);\n    assert(mf.get_edge(e0).cap\
    \ == 2);\n\n    auto cut = mf.min_cut(0);\n    assert(cut[0]);\n    assert(!cut[3]);\n\
    \n    mf.change_edge(e0, 3, 1);\n    auto changed = mf.get_edge(e0);\n    assert(changed.cap\
    \ == 3);\n    assert(changed.flow == 1);\n}\n\nvoid test_bounded_flow() {\n  \
    \  m1une::graph::BoundedFlow<long long> st(4);\n    int a = st.add_edge(0, 1,\
    \ 1, 3);\n    int b = st.add_edge(0, 2, 0, 2);\n    int c = st.add_edge(1, 3,\
    \ 1, 2);\n    int d = st.add_edge(2, 3, 0, 2);\n    int e = st.add_edge(1, 2,\
    \ 0, 1);\n    (void)a;\n    (void)b;\n    (void)c;\n    (void)d;\n    (void)e;\n\
    \n    auto exact = st.feasible_st_flow(0, 3, 3);\n    assert(exact.has_value());\n\
    \    std::vector<long long> balance(4, 0);\n    for (const auto& edge : exact->edges)\
    \ {\n        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);\n   \
    \     balance[edge.from] += edge.flow;\n        balance[edge.to] -= edge.flow;\n\
    \    }\n    assert((balance == std::vector<long long>{3, 0, 0, -3}));\n\n    auto\
    \ too_much = st.feasible_st_flow(0, 3, 6);\n    assert(!too_much.has_value());\n\
    \n    m1une::graph::BoundedFlow<long long> bf(3);\n    int f01 = bf.add_edge(0,\
    \ 1, 1, 3);\n    int f02 = bf.add_edge(0, 2, 0, 4);\n    bf.add_edge(1, 2, 0,\
    \ 2);\n    bf.add_supply(0, 4);\n    bf.add_demand(1, 1);\n    bf.add_demand(2,\
    \ 3);\n    assert(bf.balance(0) == 4);\n    auto bflow = bf.feasible_flow();\n\
    \    assert(bflow.has_value());\n    assert(bflow->get_edge(f01).flow >= 1);\n\
    \    assert(bflow->get_edge(f02).flow >= 0);\n    std::vector<long long> b_balance(3,\
    \ 0);\n    for (const auto& edge : bflow->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        b_balance[edge.from] += edge.flow;\n\
    \        b_balance[edge.to] -= edge.flow;\n    }\n    assert((b_balance == std::vector<long\
    \ long>{4, -1, -3}));\n\n    m1une::graph::BoundedFlow<long long> negative(2);\n\
    \    int neg = negative.add_edge(0, 1, -5, 5);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.feasible_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n\n    m1une::graph::BoundedFlow<long long> impossible(2);\n    impossible.add_edge(0,\
    \ 1, 0, 1);\n    impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n\
    \    assert(!impossible.feasible_flow().has_value());\n\n    m1une::graph::BFlow<long\
    \ long> alias(1);\n    assert(alias.size() == 1);\n}\n\nvoid test_bounded_min_cost_flow()\
    \ {\n    m1une::graph::BoundedMinCostFlow<long long, long long> st(3);\n    int\
    \ e01 = st.add_edge(0, 1, 1, 3, 2);\n    int e12 = st.add_edge(1, 2, 1, 3, 1);\n\
    \    int e02 = st.add_edge(0, 2, 0, 3, 10);\n\n    auto exact = st.min_cost_st_flow(0,\
    \ 2, 3);\n    assert(exact.has_value());\n    assert(exact->cost == 9);\n    assert(exact->flow(e01)\
    \ == 3);\n    assert(exact->flow(e12) == 3);\n    assert(exact->flow(e02) == 0);\n\
    \    std::vector<long long> balance(3, 0);\n    for (const auto& edge : exact->edges)\
    \ {\n        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);\n   \
    \     balance[edge.from] += edge.flow;\n        balance[edge.to] -= edge.flow;\n\
    \    }\n    assert((balance == std::vector<long long>{3, 0, -3}));\n\n    m1une::graph::BoundedMinCostFlow<long\
    \ long, long long> bf(3);\n    int p01 = bf.add_edge(0, 1, 0, 2, 1);\n    int\
    \ p12 = bf.add_edge(1, 2, 0, 2, 1);\n    int p02 = bf.add_edge(0, 2, 0, 2, 5);\n\
    \    bf.add_supply(0, 2);\n    bf.add_demand(2, 2);\n    auto bflow = bf.min_cost_flow();\n\
    \    assert(bflow.has_value());\n    assert(bflow->cost == 4);\n    assert(bflow->flow(p01)\
    \ == 2);\n    assert(bflow->flow(p12) == 2);\n    assert(bflow->flow(p02) == 0);\n\
    \n    m1une::graph::BoundedMinCostFlow<long long, long long> negative(2);\n  \
    \  int neg = negative.add_edge(0, 1, -5, 5, 2);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.min_cost_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n    assert(negative_flow->cost == -6);\n\n    m1une::graph::BoundedMinCostFlow<long\
    \ long, long long> cycle(2);\n    int c01 = cycle.add_edge(0, 1, 0, 1, -5);\n\
    \    int c10 = cycle.add_edge(1, 0, 0, 1, 3);\n    auto circulation = cycle.min_cost_flow();\n\
    \    assert(circulation.has_value());\n    assert(circulation->flow(c01) == 1);\n\
    \    assert(circulation->flow(c10) == 1);\n    assert(circulation->cost == -2);\n\
    \n    m1une::graph::BoundedMinCostFlow<long long, long long> impossible(2);\n\
    \    impossible.add_edge(0, 1, 0, 1, 0);\n    impossible.add_supply(0, 2);\n \
    \   impossible.add_demand(1, 2);\n    assert(!impossible.min_cost_flow().has_value());\n\
    \n    m1une::graph::BMinCostFlow<long long, long long> alias(1);\n    assert(alias.size()\
    \ == 1);\n}\n\nvoid test_min_cost_flow() {\n    m1une::graph::MinCostFlow<long\
    \ long, long long> mcf(4);\n    mcf.add_edge(0, 1, 2, 1);\n    mcf.add_edge(0,\
    \ 2, 1, 2);\n    mcf.add_edge(1, 2, 1, 0);\n    mcf.add_edge(1, 3, 1, 3);\n  \
    \  mcf.add_edge(2, 3, 2, 1);\n\n    auto result = mcf.flow(0, 3, 2);\n    assert(result.first\
    \ == 2);\n    assert(result.second == 5);\n    auto edges = mcf.edges();\n   \
    \ long long total_source_flow = 0;\n    for (const auto& e : edges) {\n      \
    \  if (e.from == 0) total_source_flow += e.flow;\n        assert(0 <= e.flow &&\
    \ e.flow <= e.cap);\n    }\n    assert(total_source_flow == 2);\n\n    m1une::graph::MinCostFlow<long\
    \ long, long long> negative(3);\n    negative.add_edge(0, 1, 1, -5);\n    negative.add_edge(1,\
    \ 2, 1, 2);\n    negative.add_edge(0, 2, 1, 10);\n    auto slope = negative.slope(0,\
    \ 2, 2);\n    assert((slope == std::vector<std::pair<long long, long long>>{{0,\
    \ 0}, {1, -3}, {2, 7}}));\n}\n\nint main() {\n    test_graph_container();\n  \
    \  test_edge_alive();\n    test_bfs();\n    test_dijkstra();\n    test_zero_one_bfs();\n\
    \    test_bellman_ford();\n    test_dag_shortest_path();\n    test_warshall_floyd();\n\
    \    test_topological_sort();\n    test_scc();\n    test_lowlink();\n    test_bipartite_and_components();\n\
    \    test_general_matching();\n    test_maximum_clique_and_independent_set();\n\
    \    test_cycle_detection();\n    test_kruskal();\n    test_grid();\n    test_max_flow();\n\
    \    test_bounded_flow();\n    test_bounded_min_cost_flow();\n    test_min_cost_flow();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <set>\n#include <string>\n#include\
    \ <vector>\n\n#include \"graph/all.hpp\"\n\nusing m1une::graph::Graph;\n\nvoid\
    \ test_graph_container() {\n    Graph<int> g(2);\n    assert(g.size() == 2);\n\
    \    int added = g.add_vertex();\n    assert(added == 2);\n    int e0 = g.add_directed_edge(0,\
    \ 1, 4);\n    int e1 = g.add_edge(1, 2, 5);\n    assert(e0 == 0);\n    assert(e1\
    \ == 1);\n    assert(g.edge_count() == 2);\n    assert(g[1].size() == 1);\n  \
    \  assert(g.edges().size() == 2);\n    auto rev = g.reversed();\n    assert(rev[1][0].to\
    \ == 0);\n}\n\nvoid test_edge_alive() {\n    Graph<int> g(4);\n    int e01 = g.add_edge(0,\
    \ 1);\n    int e12 = g.add_edge(1, 2);\n    int e23 = g.add_edge(2, 3);\n    (void)e01;\n\
    \    (void)e23;\n\n    assert(g.edge_count() == 3);\n    assert(g.edges().size()\
    \ == 3);\n    auto res = m1une::graph::bfs(g, 0);\n    assert(res.dist[3] == 3);\n\
    \n    g.erase_edge(e12);\n    assert(!g.is_edge_alive(e12));\n    assert(g.edges().size()\
    \ == 2);\n    assert(g.edges(true).size() == 3);\n    auto cut = m1une::graph::bfs(g,\
    \ 0);\n    assert(!cut.reachable(3));\n\n    auto rev = g.reversed();\n    assert(!rev.is_edge_alive(e12));\n\
    \    assert(rev.edges().size() == 2);\n\n    g.revive_edge(e12);\n    assert(g.is_edge_alive(e12));\n\
    \    auto restored = m1une::graph::bfs(g, 0);\n    assert(restored.dist[3] ==\
    \ 3);\n}\n\nvoid test_bfs() {\n    Graph<int> g(5);\n    g.add_directed_edge(0,\
    \ 1);\n    g.add_directed_edge(0, 2);\n    g.add_directed_edge(1, 3);\n    g.add_directed_edge(2,\
    \ 3);\n    g.add_directed_edge(3, 4);\n\n    auto res = m1une::graph::bfs(g, 0);\n\
    \    assert(res.dist[0] == 0);\n    assert(res.dist[3] == 2);\n    assert(res.dist[4]\
    \ == 3);\n    auto path = res.path(4);\n    assert(path.front() == 0);\n    assert(path.back()\
    \ == 4);\n    assert(path.size() == 4);\n}\n\nvoid test_dijkstra() {\n    Graph<long\
    \ long> g(5);\n    g.add_directed_edge(0, 1, 4);\n    g.add_directed_edge(0, 2,\
    \ 1);\n    g.add_directed_edge(2, 1, 2);\n    g.add_directed_edge(1, 3, 1);\n\
    \    g.add_directed_edge(2, 3, 7);\n    g.add_directed_edge(3, 4, 3);\n\n    auto\
    \ res = m1une::graph::dijkstra(g, 0);\n    assert(res.dist[1] == 3);\n    assert(res.dist[4]\
    \ == 7);\n    assert((res.path(4) == std::vector<int>{0, 2, 1, 3, 4}));\n}\n\n\
    void test_zero_one_bfs() {\n    Graph<int> g(6);\n    g.add_directed_edge(0, 1,\
    \ 1);\n    g.add_directed_edge(0, 2, 0);\n    g.add_directed_edge(2, 1, 0);\n\
    \    g.add_directed_edge(1, 3, 1);\n    g.add_directed_edge(2, 3, 1);\n    g.add_directed_edge(3,\
    \ 4, 0);\n\n    auto res = m1une::graph::zero_one_bfs(g, 0);\n    assert(res.dist[0]\
    \ == 0);\n    assert(res.dist[1] == 0);\n    assert(res.dist[3] == 1);\n    assert(res.dist[4]\
    \ == 1);\n    assert(!res.reachable(5));\n    assert((res.path(4) == std::vector<int>{0,\
    \ 2, 3, 4}));\n\n    auto multi = m1une::graph::zero_one_bfs(g, std::vector<int>{1,\
    \ 5});\n    assert(multi.dist[1] == 0);\n    assert(multi.dist[4] == 1);\n   \
    \ assert(multi.dist[5] == 0);\n}\n\nvoid test_bellman_ford() {\n    Graph<long\
    \ long> g(5);\n    g.add_directed_edge(0, 1, 1);\n    g.add_directed_edge(1, 2,\
    \ -3);\n    g.add_directed_edge(2, 3, 1);\n    g.add_directed_edge(3, 1, 1);\n\
    \    g.add_directed_edge(0, 4, 5);\n\n    auto res = m1une::graph::bellman_ford(g,\
    \ 0);\n    assert(res.has_negative_cycle);\n    assert(res.affected_by_negative_cycle(1));\n\
    \    assert(res.affected_by_negative_cycle(2));\n    assert(res.affected_by_negative_cycle(3));\n\
    \    assert(!res.affected_by_negative_cycle(4));\n    assert(res.dist[4] == 5);\n\
    }\n\nvoid test_dag_shortest_path() {\n    Graph<long long> g(6);\n    g.add_directed_edge(0,\
    \ 1, 2);\n    g.add_directed_edge(0, 2, 5);\n    g.add_directed_edge(1, 2, -4);\n\
    \    g.add_directed_edge(1, 4, 10);\n    g.add_directed_edge(2, 3, 3);\n    g.add_directed_edge(3,\
    \ 4, 1);\n\n    auto res = m1une::graph::dag_shortest_path(g, 0);\n    assert(res.has_value());\n\
    \    assert(res->dist[0] == 0);\n    assert(res->dist[2] == -2);\n    assert(res->dist[4]\
    \ == 2);\n    assert(!res->reachable(5));\n    assert((res->path(4) == std::vector<int>{0,\
    \ 1, 2, 3, 4}));\n    assert(res->topological_order.size() == 6);\n\n    auto\
    \ multi = m1une::graph::dag_shortest_path(g, std::vector<int>{1, 5});\n    assert(multi.has_value());\n\
    \    assert(multi->dist[4] == 0);\n    assert(multi->dist[5] == 0);\n\n    g.add_directed_edge(4,\
    \ 1, 1);\n    auto cyclic = m1une::graph::dag_shortest_path(g, 0);\n    assert(!cyclic.has_value());\n\
    }\n\nvoid test_warshall_floyd() {\n    Graph<long long> g(4);\n    g.add_directed_edge(0,\
    \ 1, 3);\n    g.add_directed_edge(1, 2, 4);\n    g.add_directed_edge(0, 2, 10);\n\
    \    g.add_directed_edge(2, 3, -2);\n\n    auto dist = m1une::graph::warshall_floyd(g);\n\
    \    assert(dist[0][2] == 7);\n    assert(dist[0][3] == 5);\n    assert(!m1une::graph::has_negative_cycle(dist));\n\
    \n    bool changed = m1une::graph::warshall_floyd_add_directed_edge(dist, 3, 1,\
    \ 1LL);\n    assert(changed);\n    assert(dist[0][1] == 3);\n    assert(dist[2][1]\
    \ == -1);\n    assert(dist[3][2] == 5);\n\n    changed = m1une::graph::warshall_floyd_add_directed_edge(dist,\
    \ 0, 2, 100LL);\n    assert(!changed);\n\n    Graph<long long> undirected(4);\n\
    \    undirected.add_edge(0, 1, 10);\n    undirected.add_edge(1, 2, 10);\n    undirected.add_edge(2,\
    \ 3, 10);\n    auto udist = m1une::graph::warshall_floyd(undirected);\n    changed\
    \ = m1une::graph::warshall_floyd_add_undirected_edge(udist, 0, 3, 1LL);\n    assert(changed);\n\
    \    assert(udist[0][3] == 1);\n    assert(udist[3][0] == 1);\n    assert(udist[1][3]\
    \ == 11);\n}\n\nvoid test_topological_sort() {\n    Graph<int> g(4);\n    g.add_directed_edge(0,\
    \ 1);\n    g.add_directed_edge(0, 2);\n    g.add_directed_edge(1, 3);\n    g.add_directed_edge(2,\
    \ 3);\n\n    auto order = m1une::graph::topological_sort(g);\n    assert(order.has_value());\n\
    \    std::vector<int> pos(4);\n    for (int i = 0; i < 4; i++) pos[(*order)[i]]\
    \ = i;\n    for (int v = 0; v < 4; v++) {\n        for (const auto& e : g[v])\
    \ assert(pos[e.from] < pos[e.to]);\n    }\n\n    g.add_directed_edge(3, 0);\n\
    \    assert(!m1une::graph::is_dag(g));\n}\n\nvoid test_scc() {\n    Graph<int>\
    \ g(4);\n    g.add_directed_edge(0, 1);\n    g.add_directed_edge(1, 0);\n    g.add_directed_edge(1,\
    \ 2);\n    g.add_directed_edge(2, 3);\n    g.add_directed_edge(3, 2);\n\n    auto\
    \ scc = m1une::graph::strongly_connected_components(g);\n    assert(scc.count\
    \ == 2);\n    assert(scc.same(0, 1));\n    assert(scc.same(2, 3));\n    assert(!scc.same(0,\
    \ 2));\n    auto dag = scc.dag(g);\n    assert(dag.size() == 2);\n    assert(dag.edge_count()\
    \ == 1);\n}\n\nvoid test_lowlink() {\n    Graph<int> g(5);\n    g.add_edge(0,\
    \ 1);\n    g.add_edge(1, 2);\n    g.add_edge(2, 0);\n    int b0 = g.add_edge(1,\
    \ 3);\n    int b1 = g.add_edge(3, 4);\n\n    auto res = m1une::graph::lowlink(g);\n\
    \    assert((res.articulation == std::vector<int>{1, 3}));\n    assert((res.bridge_ids\
    \ == std::vector<int>{b0, b1}));\n}\n\nvoid test_bipartite_and_components() {\n\
    \    Graph<int> square(4);\n    square.add_edge(0, 1);\n    square.add_edge(1,\
    \ 2);\n    square.add_edge(2, 3);\n    square.add_edge(3, 0);\n    auto bp = m1une::graph::bipartite(square);\n\
    \    assert(bp.is_bipartite);\n    assert(bp.color[0] == bp.color[2]);\n    assert((bp.left_vertices\
    \ == std::vector<int>{0, 2}));\n    assert((bp.right_vertices == std::vector<int>{1,\
    \ 3}));\n    assert(bp.left_id[2] == 1);\n    assert(bp.right_id[3] == 1);\n \
    \   auto built = m1une::graph::make_bipartite_matching(square);\n    assert(built.has_value());\n\
    \    assert(built->matching.left_size() == 2);\n    assert(built->matching.right_size()\
    \ == 2);\n    assert(built->matching.max_matching() == 2);\n    for (const auto&\
    \ p : built->matching.matching()) {\n        int u = built->left_vertex(p.left);\n\
    \        int v = built->right_vertex(p.right);\n        assert(bp.color[u] ==\
    \ 0);\n        assert(bp.color[v] == 1);\n        assert(square.is_edge_alive(built->original_edge(p.edge_id)));\n\
    \    }\n\n    Graph<int> triangle(3);\n    triangle.add_edge(0, 1);\n    triangle.add_edge(1,\
    \ 2);\n    triangle.add_edge(2, 0);\n    assert(!m1une::graph::is_bipartite(triangle));\n\
    \    assert(!m1une::graph::make_bipartite_matching(triangle).has_value());\n\n\
    \    Graph<int> cc_graph(5);\n    cc_graph.add_edge(0, 1);\n    cc_graph.add_edge(2,\
    \ 3);\n    auto cc = m1une::graph::connected_components(cc_graph);\n    assert(cc.count\
    \ == 3);\n    assert(cc.same(0, 1));\n    assert(cc.same(2, 3));\n    assert(!cc.same(0,\
    \ 2));\n\n    Graph<int> directed(2);\n    directed.add_directed_edge(1, 0);\n\
    \    assert(m1une::graph::is_bipartite(directed));\n    auto weak = m1une::graph::connected_components(directed);\n\
    \    assert(weak.count == 1);\n\n    m1une::graph::BipartiteMatching bm(3, 2);\n\
    \    int e00 = bm.add_edge(0, 0);\n    int e10 = bm.add_edge(1, 0);\n    int e11\
    \ = bm.add_edge(1, 1);\n    int e21 = bm.add_edge(2, 1);\n    assert(bm.left_size()\
    \ == 3);\n    assert(bm.right_size() == 2);\n    assert(bm.edge_count() == 4);\n\
    \    assert(bm.get_edge(e10).left == 1);\n    assert(bm.max_matching() == 2);\n\
    \    assert(bm.matching_size() == 2);\n    auto pairs = bm.matching();\n    assert(pairs.size()\
    \ == 2);\n    auto left_match = bm.left_match();\n    auto right_match = bm.right_match();\n\
    \    for (const auto& p : pairs) {\n        assert(left_match[p.left] == p.right);\n\
    \        assert(right_match[p.right] == p.left);\n    }\n\n    auto cover = bm.minimum_vertex_cover();\n\
    \    assert(cover.left.empty());\n    assert((cover.right == std::vector<int>{0,\
    \ 1}));\n    assert(cover.size() == 2);\n    auto independent = bm.maximum_independent_set();\n\
    \    assert((independent.left == std::vector<int>{0, 1, 2}));\n    assert(independent.right.empty());\n\
    \n    auto edge_cover = bm.minimum_edge_cover();\n    assert(edge_cover.has_value());\n\
    \    assert(edge_cover->size() == 3);\n    std::vector<bool> covered_left(3, false),\
    \ covered_right(2, false);\n    for (int id : *edge_cover) {\n        auto edge\
    \ = bm.get_edge(id);\n        covered_left[edge.left] = true;\n        covered_right[edge.right]\
    \ = true;\n    }\n    assert((covered_left == std::vector<bool>{true, true, true}));\n\
    \    assert((covered_right == std::vector<bool>{true, true}));\n\n    bm.erase_edge(e11);\n\
    \    bm.erase_edge(e21);\n    assert(!bm.is_edge_alive(e21));\n    assert(bm.edges().size()\
    \ == 2);\n    assert(bm.edges(true).size() == 4);\n    assert(bm.max_matching()\
    \ == 1);\n    bm.revive_edge(e21);\n    assert(bm.max_matching() == 2);\n\n  \
    \  m1une::graph::BipartiteMatching isolated(1, 1);\n    assert(!isolated.minimum_edge_cover().has_value());\n\
    \n    (void)e00;\n}\n\nvoid test_general_matching() {\n    m1une::graph::GeneralMatching\
    \ blossom(6);\n    int e01 = blossom.add_edge(0, 1);\n    int e12 = blossom.add_edge(1,\
    \ 2);\n    int e23 = blossom.add_edge(2, 3);\n    int e34 = blossom.add_edge(3,\
    \ 4);\n    int e40 = blossom.add_edge(4, 0);\n    int e15 = blossom.add_edge(1,\
    \ 5);\n    (void)e12;\n    (void)e23;\n    (void)e34;\n    (void)e40;\n\n    assert(blossom.size()\
    \ == 6);\n    assert(blossom.edge_count() == 6);\n    assert(blossom.get_edge(e01).other(0)\
    \ == 1);\n    assert(blossom.max_matching() == 3);\n    assert(blossom.matching_size()\
    \ == 3);\n    auto mate = blossom.mate();\n    auto mate_edge = blossom.mate_edge();\n\
    \    for (int v = 0; v < 6; v++) {\n        assert(mate[v] != -1);\n        assert(mate[mate[v]]\
    \ == v);\n        assert(mate_edge[v] != -1);\n    }\n    auto pairs = blossom.matching();\n\
    \    assert(pairs.size() == 3);\n    for (const auto& p : pairs) {\n        assert(mate[p.from]\
    \ == p.to);\n        assert(mate[p.to] == p.from);\n    }\n\n    auto edge_cover\
    \ = blossom.minimum_edge_cover();\n    assert(edge_cover.has_value());\n    assert(edge_cover->size()\
    \ == 3);\n    std::vector<bool> covered(6, false);\n    for (int id : *edge_cover)\
    \ {\n        auto edge = blossom.get_edge(id);\n        covered[edge.from] = true;\n\
    \        covered[edge.to] = true;\n    }\n    assert((covered == std::vector<bool>{true,\
    \ true, true, true, true, true}));\n\n    blossom.erase_edge(e15);\n    assert(!blossom.is_edge_alive(e15));\n\
    \    assert(blossom.edges().size() == 5);\n    assert(blossom.edges(true).size()\
    \ == 6);\n    assert(blossom.max_matching() == 2);\n    assert(!blossom.minimum_edge_cover().has_value());\n\
    \    blossom.revive_edge(e15);\n    assert(blossom.max_matching() == 3);\n\n \
    \   m1une::graph::GeneralMatching path(3);\n    path.add_edge(0, 1);\n    path.add_edge(1,\
    \ 2);\n    auto path_cover = path.minimum_edge_cover();\n    assert(path_cover.has_value());\n\
    \    assert(path_cover->size() == 2);\n\n    m1une::graph::GeneralMatching isolated(1);\n\
    \    assert(!isolated.minimum_edge_cover().has_value());\n\n    Graph<int> g(4);\n\
    \    int g01 = g.add_edge(0, 1);\n    int g12 = g.add_edge(1, 2);\n    int g20\
    \ = g.add_edge(2, 0);\n    int g23 = g.add_edge(2, 3);\n    (void)g01;\n    (void)g12;\n\
    \    (void)g20;\n    auto built = m1une::graph::make_general_matching(g);\n  \
    \  assert(built.matching.max_matching() == 2);\n    for (const auto& p : built.matching.matching())\
    \ {\n        assert(g.is_edge_alive(built.original_edge(p.edge_id)));\n    }\n\
    \    assert(g.is_edge_alive(g23));\n}\n\nvoid test_maximum_clique_and_independent_set()\
    \ {\n    Graph<int> g(7);\n    int removed_clique_edge = -1;\n    for (int i =\
    \ 0; i < 4; i++) {\n        for (int j = i + 1; j < 4; j++) {\n            int\
    \ id = g.add_edge(i, j);\n            if (i == 0 && j == 2) removed_clique_edge\
    \ = id;\n        }\n    }\n    g.add_edge(4, 0);\n    g.add_edge(4, 1);\n    g.add_edge(5,\
    \ 1);\n    g.add_edge(5, 2);\n\n    auto clique = m1une::graph::maximum_clique(g);\n\
    \    assert(clique.size() == 4);\n    assert((clique.vertices == std::vector<int>{0,\
    \ 1, 2, 3}));\n    assert(m1une::graph::is_clique(g, clique.vertices));\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 4);\n\n    auto independent = m1une::graph::maximum_independent_set(g);\n\
    \    assert(independent.size() == 4);\n    assert((independent.vertices == std::vector<int>{3,\
    \ 4, 5, 6}));\n    assert(m1une::graph::is_independent_set(g, independent.vertices));\n\
    \    assert(m1une::graph::maximum_independent_set_size(g) == 4);\n\n    assert(!m1une::graph::is_clique(g,\
    \ std::vector<int>{0, 2, 4}));\n    assert(!m1une::graph::is_independent_set(g,\
    \ std::vector<int>{4, 0}));\n\n    g.erase_edge(removed_clique_edge);\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 3);\n    g.revive_edge(removed_clique_edge);\n    assert(m1une::graph::maximum_clique_size(g)\
    \ == 4);\n\n    Graph<int> directed(3);\n    directed.add_directed_edge(0, 1);\n\
    \    directed.add_directed_edge(1, 2);\n    auto directed_clique = m1une::graph::maximum_clique(directed);\n\
    \    auto directed_independent = m1une::graph::maximum_independent_set(directed);\n\
    \    assert(directed_clique.size() == 2);\n    assert(directed_independent.size()\
    \ == 2);\n    assert((directed_independent.vertices == std::vector<int>{0, 2}));\n\
    \n    Graph<int> empty(4);\n    assert(m1une::graph::maximum_clique_size(empty)\
    \ == 1);\n    assert(m1une::graph::maximum_independent_set_size(empty) == 4);\n\
    \n    Graph<int> none(0);\n    assert(m1une::graph::maximum_clique(none).empty());\n\
    \    assert(m1une::graph::maximum_independent_set(none).empty());\n}\n\nvoid test_cycle_detection()\
    \ {\n    Graph<int> dg(3);\n    dg.add_directed_edge(0, 1);\n    dg.add_directed_edge(1,\
    \ 2);\n    dg.add_directed_edge(2, 0);\n    auto directed = m1une::graph::find_directed_cycle(dg);\n\
    \    assert(!directed.empty());\n    assert(directed.vertices.front() == directed.vertices.back());\n\
    \    assert(directed.edge_ids.size() + 1 == directed.vertices.size());\n\n   \
    \ Graph<int> ug(4);\n    ug.add_edge(0, 1);\n    ug.add_edge(1, 2);\n    ug.add_edge(2,\
    \ 0);\n    ug.add_edge(2, 3);\n    auto undirected = m1une::graph::find_undirected_cycle(ug);\n\
    \    assert(!undirected.empty());\n    assert(undirected.vertices.front() == undirected.vertices.back());\n\
    }\n\nvoid test_kruskal() {\n    Graph<long long> g(4);\n    g.add_edge(0, 1, 1);\n\
    \    g.add_edge(1, 2, 2);\n    g.add_edge(2, 3, 3);\n    g.add_edge(0, 3, 10);\n\
    \    g.add_edge(0, 2, 4);\n\n    auto mst = m1une::graph::kruskal(g);\n    assert(mst.cost\
    \ == 6);\n    assert(mst.edges.size() == 3);\n    assert(mst.components == 1);\n\
    \    assert(mst.is_spanning_tree(g.size()));\n}\n\nvoid test_grid() {\n    m1une::graph::Grid\
    \ grid(3, 4);\n    assert(grid.height() == 3);\n    assert(grid.width() == 4);\n\
    \    assert(grid.size() == 12);\n    assert(grid.inside(2, 3));\n    assert(!grid.inside(3,\
    \ 0));\n    assert(grid.id(2, 3) == 11);\n    assert(grid.pos(6) == std::make_pair(1,\
    \ 2));\n\n    auto adj4 = grid.adj4(0, 0);\n    assert((adj4 == std::vector<std::pair<int,\
    \ int>>{{0, 1}, {1, 0}}));\n\n    auto adj8 = grid.adj8(1, 1);\n    assert(adj8.size()\
    \ == 8);\n    auto adj4_ids = grid.adj4_ids(grid.id(1, 1));\n    std::set<int>\
    \ expected_ids = {grid.id(0, 1), grid.id(1, 2), grid.id(2, 1), grid.id(1, 0)};\n\
    \    assert(std::set<int>(adj4_ids.begin(), adj4_ids.end()) == expected_ids);\n\
    \n    std::vector<std::string> s = {\n        \"....\",\n        \".##.\",\n \
    \       \"....\",\n    };\n    auto passable = [&](int i, int j) {\n        return\
    \ s[i][j] != '#';\n    };\n\n    auto g4 = grid.graph4(passable);\n    assert(g4.size()\
    \ == grid.size());\n    assert(g4[grid.id(1, 1)].empty());\n    auto res = m1une::graph::bfs(g4,\
    \ grid.id(0, 0));\n    assert(res.dist[grid.id(2, 3)] == 5);\n    assert(res.dist[grid.id(1,\
    \ 1)] == -1);\n\n    auto g8 = grid.graph8(passable);\n    auto res8 = m1une::graph::bfs(g8,\
    \ grid.id(0, 0));\n    assert(res8.dist[grid.id(2, 3)] == 4);\n\n    auto all4\
    \ = grid.graph4();\n    assert(all4.edge_count() == 17);\n}\n\nvoid test_max_flow()\
    \ {\n    m1une::graph::MaxFlow<long long> mf(4);\n    int e0 = mf.add_edge(0,\
    \ 1, 2);\n    int e1 = mf.add_edge(0, 2, 1);\n    int e2 = mf.add_edge(1, 2, 1);\n\
    \    int e3 = mf.add_edge(1, 3, 1);\n    int e4 = mf.add_edge(2, 3, 2);\n    (void)e1;\n\
    \    (void)e2;\n    (void)e3;\n    (void)e4;\n\n    assert(mf.size() == 4);\n\
    \    assert(mf.edge_count() == 5);\n    assert(mf.max_flow(0, 3) == 3);\n    auto\
    \ edges = mf.edges();\n    long long outgoing = 0;\n    for (const auto& e : edges)\
    \ {\n        if (e.from == 0) outgoing += e.flow;\n        assert(0 <= e.flow\
    \ && e.flow <= e.cap);\n    }\n    assert(outgoing == 3);\n    assert(mf.get_edge(e0).cap\
    \ == 2);\n\n    auto cut = mf.min_cut(0);\n    assert(cut[0]);\n    assert(!cut[3]);\n\
    \n    mf.change_edge(e0, 3, 1);\n    auto changed = mf.get_edge(e0);\n    assert(changed.cap\
    \ == 3);\n    assert(changed.flow == 1);\n}\n\nvoid test_bounded_flow() {\n  \
    \  m1une::graph::BoundedFlow<long long> st(4);\n    int a = st.add_edge(0, 1,\
    \ 1, 3);\n    int b = st.add_edge(0, 2, 0, 2);\n    int c = st.add_edge(1, 3,\
    \ 1, 2);\n    int d = st.add_edge(2, 3, 0, 2);\n    int e = st.add_edge(1, 2,\
    \ 0, 1);\n    (void)a;\n    (void)b;\n    (void)c;\n    (void)d;\n    (void)e;\n\
    \n    auto exact = st.feasible_st_flow(0, 3, 3);\n    assert(exact.has_value());\n\
    \    std::vector<long long> balance(4, 0);\n    for (const auto& edge : exact->edges)\
    \ {\n        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);\n   \
    \     balance[edge.from] += edge.flow;\n        balance[edge.to] -= edge.flow;\n\
    \    }\n    assert((balance == std::vector<long long>{3, 0, 0, -3}));\n\n    auto\
    \ too_much = st.feasible_st_flow(0, 3, 6);\n    assert(!too_much.has_value());\n\
    \n    m1une::graph::BoundedFlow<long long> bf(3);\n    int f01 = bf.add_edge(0,\
    \ 1, 1, 3);\n    int f02 = bf.add_edge(0, 2, 0, 4);\n    bf.add_edge(1, 2, 0,\
    \ 2);\n    bf.add_supply(0, 4);\n    bf.add_demand(1, 1);\n    bf.add_demand(2,\
    \ 3);\n    assert(bf.balance(0) == 4);\n    auto bflow = bf.feasible_flow();\n\
    \    assert(bflow.has_value());\n    assert(bflow->get_edge(f01).flow >= 1);\n\
    \    assert(bflow->get_edge(f02).flow >= 0);\n    std::vector<long long> b_balance(3,\
    \ 0);\n    for (const auto& edge : bflow->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        b_balance[edge.from] += edge.flow;\n\
    \        b_balance[edge.to] -= edge.flow;\n    }\n    assert((b_balance == std::vector<long\
    \ long>{4, -1, -3}));\n\n    m1une::graph::BoundedFlow<long long> negative(2);\n\
    \    int neg = negative.add_edge(0, 1, -5, 5);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.feasible_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n\n    m1une::graph::BoundedFlow<long long> impossible(2);\n    impossible.add_edge(0,\
    \ 1, 0, 1);\n    impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n\
    \    assert(!impossible.feasible_flow().has_value());\n\n    m1une::graph::BFlow<long\
    \ long> alias(1);\n    assert(alias.size() == 1);\n}\n\nvoid test_bounded_min_cost_flow()\
    \ {\n    m1une::graph::BoundedMinCostFlow<long long, long long> st(3);\n    int\
    \ e01 = st.add_edge(0, 1, 1, 3, 2);\n    int e12 = st.add_edge(1, 2, 1, 3, 1);\n\
    \    int e02 = st.add_edge(0, 2, 0, 3, 10);\n\n    auto exact = st.min_cost_st_flow(0,\
    \ 2, 3);\n    assert(exact.has_value());\n    assert(exact->cost == 9);\n    assert(exact->flow(e01)\
    \ == 3);\n    assert(exact->flow(e12) == 3);\n    assert(exact->flow(e02) == 0);\n\
    \    std::vector<long long> balance(3, 0);\n    for (const auto& edge : exact->edges)\
    \ {\n        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);\n   \
    \     balance[edge.from] += edge.flow;\n        balance[edge.to] -= edge.flow;\n\
    \    }\n    assert((balance == std::vector<long long>{3, 0, -3}));\n\n    m1une::graph::BoundedMinCostFlow<long\
    \ long, long long> bf(3);\n    int p01 = bf.add_edge(0, 1, 0, 2, 1);\n    int\
    \ p12 = bf.add_edge(1, 2, 0, 2, 1);\n    int p02 = bf.add_edge(0, 2, 0, 2, 5);\n\
    \    bf.add_supply(0, 2);\n    bf.add_demand(2, 2);\n    auto bflow = bf.min_cost_flow();\n\
    \    assert(bflow.has_value());\n    assert(bflow->cost == 4);\n    assert(bflow->flow(p01)\
    \ == 2);\n    assert(bflow->flow(p12) == 2);\n    assert(bflow->flow(p02) == 0);\n\
    \n    m1une::graph::BoundedMinCostFlow<long long, long long> negative(2);\n  \
    \  int neg = negative.add_edge(0, 1, -5, 5, 2);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.min_cost_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n    assert(negative_flow->cost == -6);\n\n    m1une::graph::BoundedMinCostFlow<long\
    \ long, long long> cycle(2);\n    int c01 = cycle.add_edge(0, 1, 0, 1, -5);\n\
    \    int c10 = cycle.add_edge(1, 0, 0, 1, 3);\n    auto circulation = cycle.min_cost_flow();\n\
    \    assert(circulation.has_value());\n    assert(circulation->flow(c01) == 1);\n\
    \    assert(circulation->flow(c10) == 1);\n    assert(circulation->cost == -2);\n\
    \n    m1une::graph::BoundedMinCostFlow<long long, long long> impossible(2);\n\
    \    impossible.add_edge(0, 1, 0, 1, 0);\n    impossible.add_supply(0, 2);\n \
    \   impossible.add_demand(1, 2);\n    assert(!impossible.min_cost_flow().has_value());\n\
    \n    m1une::graph::BMinCostFlow<long long, long long> alias(1);\n    assert(alias.size()\
    \ == 1);\n}\n\nvoid test_min_cost_flow() {\n    m1une::graph::MinCostFlow<long\
    \ long, long long> mcf(4);\n    mcf.add_edge(0, 1, 2, 1);\n    mcf.add_edge(0,\
    \ 2, 1, 2);\n    mcf.add_edge(1, 2, 1, 0);\n    mcf.add_edge(1, 3, 1, 3);\n  \
    \  mcf.add_edge(2, 3, 2, 1);\n\n    auto result = mcf.flow(0, 3, 2);\n    assert(result.first\
    \ == 2);\n    assert(result.second == 5);\n    auto edges = mcf.edges();\n   \
    \ long long total_source_flow = 0;\n    for (const auto& e : edges) {\n      \
    \  if (e.from == 0) total_source_flow += e.flow;\n        assert(0 <= e.flow &&\
    \ e.flow <= e.cap);\n    }\n    assert(total_source_flow == 2);\n\n    m1une::graph::MinCostFlow<long\
    \ long, long long> negative(3);\n    negative.add_edge(0, 1, 1, -5);\n    negative.add_edge(1,\
    \ 2, 1, 2);\n    negative.add_edge(0, 2, 1, 10);\n    auto slope = negative.slope(0,\
    \ 2, 2);\n    assert((slope == std::vector<std::pair<long long, long long>>{{0,\
    \ 0}, {1, -3}, {2, 7}}));\n}\n\nint main() {\n    test_graph_container();\n  \
    \  test_edge_alive();\n    test_bfs();\n    test_dijkstra();\n    test_zero_one_bfs();\n\
    \    test_bellman_ford();\n    test_dag_shortest_path();\n    test_warshall_floyd();\n\
    \    test_topological_sort();\n    test_scc();\n    test_lowlink();\n    test_bipartite_and_components();\n\
    \    test_general_matching();\n    test_maximum_clique_and_independent_set();\n\
    \    test_cycle_detection();\n    test_kruskal();\n    test_grid();\n    test_max_flow();\n\
    \    test_bounded_flow();\n    test_bounded_min_cost_flow();\n    test_min_cost_flow();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - graph/all.hpp
  - graph/directed.hpp
  - graph/cycle_detection.hpp
  - graph/graph.hpp
  - graph/flow.hpp
  - graph/bounded_flow.hpp
  - graph/max_flow.hpp
  - graph/bounded_min_cost_flow.hpp
  - graph/min_cost_flow.hpp
  - graph/scc.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  - graph/grid.hpp
  - graph/undirected.hpp
  - graph/bipartite.hpp
  - graph/connected_components.hpp
  - data_structure/dsu.hpp
  - graph/general_matching.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/maximum_clique.hpp
  isVerificationFile: true
  path: verify/graph/graph_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-06-16 03:14:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/graph_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/graph_algorithms.test.cpp
- /verify/verify/graph/graph_algorithms.test.cpp.html
title: verify/graph/graph_algorithms.test.cpp
---
