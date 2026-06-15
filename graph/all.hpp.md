---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dsu.hpp
    title: Disjoint Set Union (DSU)
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
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/all.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include\
    \ <queue>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 6 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1) : from(from_),\
    \ to(to_), cost(cost_), id(id_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int\
    \ n) : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost\
    \ = T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        _g[u].push_back(edge_type(u, v, cost,\
    \ id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        return id;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges() const {\n\
    \        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (0 <= e.id && e.id < _edge_count) {\n                    if (used[e.id]) continue;\n\
    \                    used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        for (int v = 0; v < _n; v++) {\n            for (const auto& e : _g[v])\
    \ {\n                result._g[e.to].push_back(edge_type(e.to, e.from, e.cost,\
    \ e.id));\n            }\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 11 \"graph/bellman_ford.hpp\"\
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
    \ auto& e : g[v]) {\n                T nd = result.dist[v] + e.cost;\n       \
    \         if (result.dist[e.to] <= nd) continue;\n                result.dist[e.to]\
    \ = nd;\n                result.parent[e.to] = v;\n                result.parent_edge[e.to]\
    \ = e.id;\n                updated = true;\n                if (iter == n - 1)\
    \ relaxed_vertices.push_back(e.to);\n            }\n        }\n        if (!updated)\
    \ break;\n    }\n\n    std::queue<int> que;\n    for (int v : relaxed_vertices)\
    \ {\n        if (result.negative[v]) continue;\n        result.negative[v] = true;\n\
    \        que.push(v);\n    }\n    while (!que.empty()) {\n        int v = que.front();\n\
    \        que.pop();\n        for (const auto& e : g[v]) {\n            if (result.negative[e.to])\
    \ continue;\n            result.negative[e.to] = true;\n            que.push(e.to);\n\
    \        }\n    }\n\n    for (bool x : result.negative) result.has_negative_cycle\
    \ = result.has_negative_cycle || x;\n    return result;\n}\n\ntemplate <class\
    \ T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n\
    #line 8 \"graph/bfs.hpp\"\n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct BfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n\n    bool reachable(int v) const\
    \ {\n        assert(0 <= v && v < int(dist.size()));\n        return dist[v] !=\
    \ -1;\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nBfsResult bfs(const\
    \ Graph<T>& g, const std::vector<int>& sources) {\n    int n = g.size();\n   \
    \ BfsResult result;\n    result.dist.assign(n, -1);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n\n    std::queue<int> que;\n  \
    \  for (int s : sources) {\n        assert(0 <= s && s < n);\n        if (result.dist[s]\
    \ != -1) continue;\n        result.dist[s] = 0;\n        que.push(s);\n    }\n\
    \n    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/bipartite.hpp\"\
    \n\n\n\n#line 6 \"graph/bipartite.hpp\"\n\n#line 8 \"graph/bipartite.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n\
    \    std::vector<int> color;\n};\n\ntemplate <class T>\nBipartiteResult bipartite(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite\
    \ = true;\n    result.color.assign(n, -1);\n\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (const auto& e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n\
    \        adjacency[e.to].push_back(e.from);\n    }\n\n    std::queue<int> que;\n\
    \    for (int s = 0; s < n; s++) {\n        if (result.color[s] != -1) continue;\n\
    \        result.color[s] = 0;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop();\n            for\
    \ (int to : adjacency[v]) {\n                if (result.color[to] == -1) {\n \
    \                   result.color[to] = result.color[v] ^ 1;\n                \
    \    que.push(to);\n                } else if (result.color[to] == result.color[v])\
    \ {\n                    result.is_bipartite = false;\n                    return\
    \ result;\n                }\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nbool is_bipartite(const Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/connected_components.hpp\"\
    \n\n\n\n#line 6 \"graph/connected_components.hpp\"\n\n#line 1 \"data_structure/dsu.hpp\"\
    \n\n\n\n#line 5 \"data_structure/dsu.hpp\"\n#include <numeric>\n#line 7 \"data_structure/dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\nstruct Dsu {\n   private:\n\
    \    int _n;\n    // parent_or_size[i] is the parent of i if it's >= 0.\n    //\
    \ If it's < 0, then i is a root and -parent_or_size[i] is the size of the group.\n\
    \    std::vector<int> parent_or_size;\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        int x = leader(a),\
    \ y = leader(b);\n        if (x == y) return x;\n        // Union by size\n  \
    \      if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\n       \
    \ parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y] = x;\n  \
    \      return x;\n    }\n\n    // Returns true if 'a' and 'b' belong to the same\
    \ group.\n    bool same(int a, int b) {\n        return leader(a) == leader(b);\n\
    \    }\n\n    // Returns the leader (representative) of the group containing 'a'.\n\
    \    int leader(int a) {\n        if (parent_or_size[a] < 0) return a;\n     \
    \   // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
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
    #line 1 \"graph/cycle_detection.hpp\"\n\n\n\n#line 6 \"graph/cycle_detection.hpp\"\
    \n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int> edge_ids;\n\
    \n    bool empty() const {\n        return vertices.empty();\n    }\n};\n\ninline\
    \ Cycle restore_cycle(int from, int to, int closing_edge, const std::vector<int>&\
    \ parent,\n                           const std::vector<int>& parent_edge) {\n\
    \    Cycle result;\n    result.vertices.push_back(to);\n\n    std::vector<int>\
    \ middle_vertices;\n    std::vector<int> middle_edges;\n    for (int v = from;\
    \ v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n        middle_edges.push_back(parent_edge[v]);\n\
    \    }\n    std::reverse(middle_vertices.begin(), middle_vertices.end());\n  \
    \  std::reverse(middle_edges.begin(), middle_edges.end());\n\n    result.vertices.insert(result.vertices.end(),\
    \ middle_vertices.begin(), middle_vertices.end());\n    result.vertices.push_back(to);\n\
    \    result.edge_ids.insert(result.edge_ids.end(), middle_edges.begin(), middle_edges.end());\n\
    \    result.edge_ids.push_back(closing_edge);\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_directed_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (color[e.to] == 0)\
    \ {\n                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (e.id == pe) continue;\n\
    \            if (color[e.to] == 0) {\n                parent[e.to] = v;\n    \
    \            parent_edge[e.to] = e.id;\n                if (self(self, e.to, e.id))\
    \ return true;\n            } else if (color[e.to] == 1) {\n                result\
    \ = restore_cycle(v, e.to, e.id, parent, parent_edge);\n                return\
    \ true;\n            }\n        }\n        color[v] = 2;\n        return false;\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs,\
    \ v, -1)) break;\n    }\n    return result;\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/dijkstra.hpp\"\n\n\n\n#line 6 \"graph/dijkstra.hpp\"\
    \n#include <functional>\n#line 9 \"graph/dijkstra.hpp\"\n#include <utility>\n\
    #line 11 \"graph/dijkstra.hpp\"\n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DijkstraResult {\n\
    \    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
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
    \        for (const auto& e : g[v]) {\n            T nd = d + e.cost;\n      \
    \      if (result.dist[e.to] <= nd) continue;\n            result.dist[e.to] =\
    \ nd;\n            result.parent[e.to] = v;\n            result.parent_edge[e.to]\
    \ = e.id;\n            que.emplace(nd, e.to);\n        }\n    }\n\n    return\
    \ result;\n}\n\ntemplate <class T>\nDijkstraResult<T> dijkstra(const Graph<T>&\
    \ g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return dijkstra(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 1 \"graph/kruskal.hpp\"\n\n\n\n#line 6 \"graph/kruskal.hpp\"\n\n#line\
    \ 9 \"graph/kruskal.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T>\nstruct MinimumSpanningForest {\n    T cost;\n    std::vector<Edge<T>>\
    \ edges;\n    int components;\n\n    bool is_spanning_tree(int n) const {\n  \
    \      return components <= 1 && int(edges.size()) == std::max(0, n - 1);\n  \
    \  }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T> kruskal(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    auto edges = g.edges();\n    std::sort(edges.begin(),\
    \ edges.end(), [](const auto& a, const auto& b) {\n        return a.cost < b.cost;\n\
    \    });\n\n    m1une::data_structure::Dsu dsu(n);\n    MinimumSpanningForest<T>\
    \ result;\n    result.cost = T(0);\n    result.components = n;\n\n    for (const\
    \ auto& e : edges) {\n        if (dsu.same(e.from, e.to)) continue;\n        dsu.merge(e.from,\
    \ e.to);\n        result.cost += e.cost;\n        result.edges.push_back(e);\n\
    \        result.components--;\n    }\n\n    return result;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/lowlink.hpp\"\n\n\n\n#line\
    \ 6 \"graph/lowlink.hpp\"\n\n#line 8 \"graph/lowlink.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T>\nstruct LowLinkResult {\n    std::vector<int>\
    \ ord;\n    std::vector<int> low;\n    std::vector<int> articulation;\n    std::vector<Edge<T>>\
    \ bridges;\n    std::vector<int> bridge_ids;\n};\n\ntemplate <class T>\nLowLinkResult<T>\
    \ lowlink(const Graph<T>& g) {\n    int n = g.size();\n    LowLinkResult<T> result;\n\
    \    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n    int now = 0;\n\
    \n    auto dfs = [&](auto self, int v, int parent_edge) -> void {\n        result.ord[v]\
    \ = result.low[v] = now++;\n        int child_count = 0;\n        bool is_articulation\
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (e.id == parent_edge)\
    \ continue;\n            int to = e.to;\n            if (result.ord[to] == -1)\
    \ {\n                child_count++;\n                self(self, to, e.id);\n \
    \               result.low[v] = std::min(result.low[v], result.low[to]);\n   \
    \             if (parent_edge != -1 && result.ord[v] <= result.low[to]) is_articulation\
    \ = true;\n                if (result.ord[v] < result.low[to]) {\n           \
    \         result.bridges.push_back(e);\n                    result.bridge_ids.push_back(e.id);\n\
    \                }\n            } else {\n                result.low[v] = std::min(result.low[v],\
    \ result.ord[to]);\n            }\n        }\n\n        if (parent_edge == -1\
    \ && child_count >= 2) is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/scc.hpp\"\
    \n\n\n\n#line 8 \"graph/scc.hpp\"\n\n#line 10 \"graph/scc.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\nstruct SccResult {\n    int count;\n    std::vector<int>\
    \ comp;\n    std::vector<std::vector<int>> groups;\n\n    bool same(int u, int\
    \ v) const {\n        assert(0 <= u && u < int(comp.size()));\n        assert(0\
    \ <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n    }\n\n\
    \    template <class T>\n    Graph<int> dag(const Graph<T>& g) const {\n     \
    \   std::vector<std::pair<int, int>> edges;\n        for (int v = 0; v < g.size();\
    \ v++) {\n            for (const auto& e : g[v]) {\n                int a = comp[e.from],\
    \ b = comp[e.to];\n                if (a != b) edges.emplace_back(a, b);\n   \
    \         }\n        }\n        std::sort(edges.begin(), edges.end());\n     \
    \   edges.erase(std::unique(edges.begin(), edges.end()), edges.end());\n\n   \
    \     Graph<int> result(count);\n        for (auto [a, b] : edges) result.add_directed_edge(a,\
    \ b);\n        return result;\n    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> ord(n, -1), low(n,\
    \ 0), comp(n, -1), stack;\n    std::vector<char> in_stack(n, false);\n    std::vector<std::vector<int>>\
    \ groups;\n    int now = 0;\n\n    auto dfs = [&](auto self, int v) -> void {\n\
    \        ord[v] = low[v] = now++;\n        stack.push_back(v);\n        in_stack[v]\
    \ = true;\n\n        for (const auto& e : g[v]) {\n            int to = e.to;\n\
    \            if (ord[to] == -1) {\n                self(self, to);\n         \
    \       low[v] = std::min(low[v], low[to]);\n            } else if (in_stack[to])\
    \ {\n                low[v] = std::min(low[v], ord[to]);\n            }\n    \
    \    }\n\n        if (low[v] != ord[v]) return;\n        std::vector<int> group;\n\
    \        while (true) {\n            int u = stack.back();\n            stack.pop_back();\n\
    \            in_stack[u] = false;\n            group.push_back(u);\n         \
    \   if (u == v) break;\n        }\n        groups.push_back(std::move(group));\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (ord[v] == -1) dfs(dfs,\
    \ v);\n    }\n\n    std::reverse(groups.begin(), groups.end());\n    for (int\
    \ i = 0; i < int(groups.size()); i++) {\n        for (int v : groups[i]) comp[v]\
    \ = i;\n    }\n\n    return SccResult{int(groups.size()), std::move(comp), std::move(groups)};\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/topological_sort.hpp\"\
    \n\n\n\n#include <optional>\n#line 7 \"graph/topological_sort.hpp\"\n\n#line 9\
    \ \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T>\nstd::optional<std::vector<int>> topological_sort(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& e : g[v]) indeg[e.to]++;\n  \
    \  }\n\n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if\
    \ (indeg[v] == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   indeg[e.to]--;\n            if (indeg[e.to] == 0) que.push(e.to);\n      \
    \  }\n    }\n\n    if (int(order.size()) != n) return std::nullopt;\n    return\
    \ order;\n}\n\ntemplate <class T>\nbool is_dag(const Graph<T>& g) {\n    return\
    \ topological_sort(g).has_value();\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8 \"graph/warshall_floyd.hpp\"\
    \n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>>\
    \ dist,\n                                           T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    int n = int(dist.size());\n    for (int k = 0; k < n; k++) {\n\
    \        for (int i = 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n\
    \            for (int j = 0; j < n; j++) {\n                if (dist[k][j] ==\
    \ inf) continue;\n                T nd = dist[i][k] + dist[k][j];\n          \
    \      if (nd < dist[i][j]) dist[i][j] = nd;\n            }\n        }\n    }\n\
    \    return dist;\n}\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(const\
    \ Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    std::vector<std::vector<T>> dist(n, std::vector<T>(n, inf));\n    for (int\
    \ i = 0; i < n; i++) dist[i][i] = T(0);\n    for (int v = 0; v < n; v++) {\n \
    \       for (const auto& e : g[v]) {\n            if (e.cost < dist[e.from][e.to])\
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
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 16 \"graph/all.hpp\"\n\
    \n\n"
  code: '#ifndef M1UNE_GRAPH_ALL_HPP

    #define M1UNE_GRAPH_ALL_HPP 1


    #include "graph/bellman_ford.hpp"

    #include "graph/bfs.hpp"

    #include "graph/bipartite.hpp"

    #include "graph/connected_components.hpp"

    #include "graph/cycle_detection.hpp"

    #include "graph/dijkstra.hpp"

    #include "graph/graph.hpp"

    #include "graph/kruskal.hpp"

    #include "graph/lowlink.hpp"

    #include "graph/scc.hpp"

    #include "graph/topological_sort.hpp"

    #include "graph/warshall_floyd.hpp"


    #endif  // M1UNE_GRAPH_ALL_HPP

    '
  dependsOn:
  - graph/bellman_ford.hpp
  - graph/graph.hpp
  - graph/bfs.hpp
  - graph/bipartite.hpp
  - graph/connected_components.hpp
  - data_structure/dsu.hpp
  - graph/cycle_detection.hpp
  - graph/dijkstra.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/scc.hpp
  - graph/topological_sort.hpp
  - graph/warshall_floyd.hpp
  isVerificationFile: false
  path: graph/all.hpp
  requiredBy: []
  timestamp: '2026-06-16 01:54:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/all.hpp
layout: document
title: Graph All
---

## Overview

`graph/all.hpp` includes every general graph header in this directory. It is
convenient when writing quickly during a contest and you do not want to manage
individual graph includes.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/graph.hpp` | `Graph<T>` and `Edge<T>` adjacency-list container. |
| `graph/bfs.hpp` | Unweighted shortest paths. |
| `graph/dijkstra.hpp` | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Shortest paths with negative edges and negative-cycle marking. |
| `graph/warshall_floyd.hpp` | All-pairs shortest paths. |
| `graph/topological_sort.hpp` | DAG ordering and cycle check. |
| `graph/scc.hpp` | Strongly connected components and condensation DAG. |
| `graph/lowlink.hpp` | Articulation points and bridges in undirected graphs. |
| `graph/bipartite.hpp` | Two-colorability check. |
| `graph/connected_components.hpp` | Weak connected components. |
| `graph/cycle_detection.hpp` | Finds one directed or undirected cycle. |
| `graph/kruskal.hpp` | Minimum spanning forest. |

## Example

```cpp
#include "graph/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    auto dist = m1une::graph::dijkstra(g, 0).dist;
    std::cout << dist[1] << "\n";
}
```
