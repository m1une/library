---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':x:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':x:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':x:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':x:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':x:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':x:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':x:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':x:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':x:'
    path: graph/two_sat.hpp
    title: Two-Satisfiability
  - icon: ':x:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':x:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedRequiredBy:
  - icon: ':x:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/directed.hpp\"\n\n\n\n#line 1 \"graph/cycle_detection.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \n\n\n\n#line 6 \"graph/bellman_ford.hpp\"\n#include <limits>\n#include <queue>\n\
    #line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
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
    \n\n\n\n#line 7 \"graph/dag_shortest_path.hpp\"\n#include <optional>\n#line 9\
    \ \"graph/dag_shortest_path.hpp\"\n\n#line 1 \"graph/topological_sort.hpp\"\n\n\
    \n\n#line 7 \"graph/topological_sort.hpp\"\n\n#line 9 \"graph/topological_sort.hpp\"\
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
    \n\n\n\n#line 6 \"graph/dijkstra.hpp\"\n#include <functional>\n#line 11 \"graph/dijkstra.hpp\"\
    \n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T>\nstruct DijkstraResult {\n    std::vector<T> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    T inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, const std::vector<int>& sources,\n             \
    \              T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    DijkstraResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using\
    \ P = std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
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
    \n\n#line 10 \"graph/shortest_path.hpp\"\n\n\n#line 1 \"graph/two_sat.hpp\"\n\n\
    \n\n#line 5 \"graph/two_sat.hpp\"\n#include <cstddef>\n#line 9 \"graph/two_sat.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\n// A 2-SAT solver using iterative\
    \ strongly connected components.\nstruct TwoSat {\n   private:\n    struct Csr\
    \ {\n        std::vector<int> start;\n        std::vector<int> to;\n    };\n\n\
    \    int _n;\n    std::vector<std::pair<int, int>> _edges;\n    bool _solved;\n\
    \    bool _satisfiable;\n    std::vector<bool> _answer;\n\n    int node(int variable,\
    \ bool value) const {\n        assert(0 <= variable && variable < _n);\n     \
    \   return 2 * variable + int(value);\n    }\n\n    void add_edge(int from, int\
    \ to) {\n        _edges.emplace_back(from, to);\n        _solved = false;\n  \
    \      _answer.clear();\n    }\n\n    Csr build_csr(bool reverse) const {\n  \
    \      int vertices = 2 * _n;\n        Csr graph;\n        graph.start.assign(vertices\
    \ + 1, 0);\n        graph.to.resize(_edges.size());\n\n        for (auto [from,\
    \ to] : _edges) {\n            int source = reverse ? to : from;\n           \
    \ graph.start[source + 1]++;\n        }\n        for (int v = 0; v < vertices;\
    \ v++) {\n            graph.start[v + 1] += graph.start[v];\n        }\n\n   \
    \     std::vector<int> cursor = graph.start;\n        for (auto [from, to] : _edges)\
    \ {\n            int source = reverse ? to : from;\n            int target = reverse\
    \ ? from : to;\n            graph.to[cursor[source]++] = target;\n        }\n\
    \        return graph;\n    }\n\n   public:\n    TwoSat() : TwoSat(0) {}\n\n \
    \   explicit TwoSat(int n)\n        : _n(n), _solved(false), _satisfiable(false)\
    \ {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 10 \"graph/directed.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_DIRECTED_HPP

    #define M1UNE_GRAPH_DIRECTED_HPP 1


    #include "cycle_detection.hpp"

    #include "graph.hpp"

    #include "scc.hpp"

    #include "shortest_path.hpp"

    #include "topological_sort.hpp"

    #include "two_sat.hpp"


    #endif  // M1UNE_GRAPH_DIRECTED_HPP

    '
  dependsOn:
  - graph/cycle_detection.hpp
  - graph/graph.hpp
  - graph/scc.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  - graph/two_sat.hpp
  isVerificationFile: false
  path: graph/directed.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/directed.hpp
layout: document
title: Directed Graph Algorithms
---

## Overview

`graph/directed.hpp` includes algorithms whose main interpretation is directed,
plus direction-respecting shortest paths.

Use this header when the input edges are one-way, or when reachability/order
depends on edge direction.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | BFS, 0-1 BFS, DAG shortest path, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and directed cycle check. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/two_sat.hpp` | Implication graph | 2-SAT clauses, satisfiability, and one assignment. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_directed_cycle(g)` for directed graphs. |
