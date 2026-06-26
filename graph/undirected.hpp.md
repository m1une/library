---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
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
    path: graph/cow_game.hpp
    title: Cow Game (Difference Constraints)
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
    path: graph/maximum_clique.hpp
    title: Maximum Clique, Independent Set, and Vertex Cover
  - icon: ':heavy_check_mark:'
    path: graph/namori.hpp
    title: Namori Graph Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/undirected.hpp\"\n\n\n\n#line 1 \"graph/bipartite.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n#include <queue>\n#include <vector>\n\
    \n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n\
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
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
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
    \ m1une\n\n\n#line 10 \"graph/bipartite.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n    std::vector<int>\
    \ color;\n    std::vector<int> left_vertices;\n    std::vector<int> right_vertices;\n\
    \    std::vector<int> left_id;\n    std::vector<int> right_id;\n};\n\ntemplate\
    \ <class T>\nBipartiteResult bipartite(const Graph<T>& g) {\n    int n = g.size();\n\
    \    BipartiteResult result;\n    result.is_bipartite = true;\n    result.color.assign(n,\
    \ -1);\n    result.left_id.assign(n, -1);\n    result.right_id.assign(n, -1);\n\
    \n    std::vector<std::vector<int>> adjacency(n);\n    for (const auto& e : g.edges())\
    \ {\n        adjacency[e.from].push_back(e.to);\n        adjacency[e.to].push_back(e.from);\n\
    \    }\n\n    std::queue<int> que;\n    for (int s = 0; s < n; s++) {\n      \
    \  if (result.color[s] != -1) continue;\n        result.color[s] = 0;\n      \
    \  que.push(s);\n        while (!que.empty()) {\n            int v = que.front();\n\
    \            que.pop();\n            for (int to : adjacency[v]) {\n         \
    \       if (result.color[to] == -1) {\n                    result.color[to] =\
    \ result.color[v] ^ 1;\n                    que.push(to);\n                } else\
    \ if (result.color[to] == result.color[v]) {\n                    result.is_bipartite\
    \ = false;\n                    return result;\n                }\n          \
    \  }\n        }\n    }\n\n    for (int v = 0; v < n; v++) {\n        if (result.color[v]\
    \ == 0) {\n            result.left_id[v] = int(result.left_vertices.size());\n\
    \            result.left_vertices.push_back(v);\n        } else {\n          \
    \  result.right_id[v] = int(result.right_vertices.size());\n            result.right_vertices.push_back(v);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nbool is_bipartite(const\
    \ Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n}\n\nstruct BipartiteVertexSet\
    \ {\n    std::vector<int> left;\n    std::vector<int> right;\n\n    int size()\
    \ const {\n        return int(left.size() + right.size());\n    }\n};\n\nstruct\
    \ BipartiteMatching {\n    struct Edge {\n        int left;\n        int right;\n\
    \        int id;\n        bool alive;\n    };\n\n    struct Pair {\n        int\
    \ left;\n        int right;\n        int edge_id;\n    };\n\n   private:\n   \
    \ int _left_size;\n    int _right_size;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
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
    \n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu\
    \ {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent of i if\
    \ it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the\
    \ size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n   \
    \ Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\
    \n    // Merges the group containing 'a' with the group containing 'b'.\n    //\
    \ Returns the leader of the merged group.\n    int merge(int a, int b) {\n   \
    \     int x = leader(a), y = leader(b);\n        if (x == y) return x;\n     \
    \   // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
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
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ConnectedComponents {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n};\n\ntemplate <class T>\nConnectedComponents connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const\
    \ auto& e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
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
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (color[e.to] == 0) {\n                parent[e.to] = v;\n    \
    \            parent_edge[e.to] = e.id;\n                if (self(self, e.to))\
    \ return true;\n            } else if (color[e.to] == 1) {\n                result\
    \ = restore_cycle(v, e.to, e.id, parent, parent_edge);\n                return\
    \ true;\n            }\n        }\n        color[v] = 2;\n        return false;\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs,\
    \ v)) break;\n    }\n    return result;\n}\n\ntemplate <class T>\nCycle find_undirected_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v, int pe) -> bool {\n        color[v] = 1;\n        for (const auto& e\
    \ : g[v]) {\n            if (!e.alive) continue;\n            if (e.id == pe)\
    \ continue;\n            if (color[e.to] == 0) {\n                parent[e.to]\
    \ = v;\n                parent_edge[e.to] = e.id;\n                if (self(self,\
    \ e.to, e.id)) return true;\n            } else if (color[e.to] == 1) {\n    \
    \            result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n   \
    \             return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v, -1)) break;\n    }\n    return result;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/general_matching.hpp\"\
    \n\n\n\n#line 9 \"graph/general_matching.hpp\"\n\n#line 11 \"graph/general_matching.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct GeneralMatching {\n    struct\
    \ Edge {\n        int from;\n        int to;\n        int id;\n        bool alive;\n\
    \n        int other(int v) const {\n            assert(v == from || v == to);\n\
    \            return from ^ to ^ v;\n        }\n    };\n\n    struct Pair {\n \
    \       int from;\n        int to;\n        int edge_id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<int> _mate;\n    std::vector<int> _mate_edge;\n    bool\
    \ _calculated;\n\n    void invalidate() {\n        _calculated = false;\n    }\n\
    \n    void ensure_matching() {\n        if (!_calculated) max_matching();\n  \
    \  }\n\n    bool is_matched_edge(int id) const {\n        const auto& e = _edges[id];\n\
    \        return _mate[e.from] == e.to && _mate_edge[e.from] == id;\n    }\n\n\
    \    enum MatchingLabel : char {\n        even_label,\n        odd_label,\n  \
    \      unlabeled\n    };\n\n    struct MutablePartition {\n        std::vector<int>\
    \ parent;\n        std::vector<int> rank;\n        std::vector<int> representative;\n\
    \n        MutablePartition() = default;\n\n        explicit MutablePartition(int\
    \ n) {\n            reset(n);\n        }\n\n        void reset(int n) {\n    \
    \        parent.resize(n);\n            rank.assign(n, 0);\n            representative.resize(n);\n\
    \            for (int i = 0; i < n; i++) {\n                parent[i] = i;\n \
    \               representative[i] = i;\n            }\n        }\n\n        int\
    \ root(int v) {\n            if (parent[v] == v) return v;\n            return\
    \ parent[v] = root(parent[v]);\n        }\n\n        int operator()(int v) {\n\
    \            return representative[root(v)];\n        }\n\n        void unite(int\
    \ a, int b) {\n            int ra = root(a);\n            int rb = root(b);\n\
    \            if (ra == rb) return;\n            if (rank[ra] < rank[rb]) std::swap(ra,\
    \ rb);\n            parent[rb] = ra;\n            if (rank[ra] == rank[rb]) rank[ra]++;\n\
    \        }\n\n        void make_rep(int v) {\n            representative[root(v)]\
    \ = v;\n        }\n    };\n\n    struct EdgeBucketQueue {\n        std::vector<std::vector<int>>\
    \ bucket;\n        std::vector<int> head;\n\n        void reset(int n) {\n   \
    \         bucket.assign(n + 3, {});\n            head.assign(n + 3, 0);\n    \
    \    }\n\n        void insert(int edge_id, int key) {\n            if (key < 0\
    \ || int(bucket.size()) <= key) return;\n            bucket[key].push_back(edge_id);\n\
    \        }\n\n        int pop(int key) {\n            if (key < 0 || int(bucket.size())\
    \ <= key) return -1;\n            if (head[key] == int(bucket[key].size())) return\
    \ -1;\n            return bucket[key][head[key]++];\n        }\n    };\n\n   \
    \ struct NewMatchingPair {\n        int from;\n        int to;\n        int edge_id;\n\
    \    };\n\n    // General-graph shortest augmenting path phase solver.\n    struct\
    \ MicaliVaziraniSolver {\n        GeneralMatching& graph;\n        int n;\n  \
    \      int matching_size;\n        int delta;\n        int visit_token;\n    \
    \    int even_time_token;\n        MutablePartition base;\n        MutablePartition\
    \ delayed_base;\n        EdgeBucketQueue queue;\n        std::vector<MatchingLabel>\
    \ label;\n        std::vector<MatchingLabel> h_label;\n        std::vector<int>\
    \ parent;\n        std::vector<int> parent_edge;\n        std::vector<int> source_bridge;\n\
    \        std::vector<int> target_bridge;\n        std::vector<int> bridge_edge;\n\
    \        std::vector<int> lcp;\n        std::vector<int> path_mark_1;\n      \
    \  std::vector<int> path_mark_2;\n        std::vector<int> restore_vertex;\n \
    \       std::vector<int> restore_value;\n        std::vector<int> rep;\n     \
    \   std::vector<int> h_mate;\n        std::vector<char> is_h_edge;\n        std::vector<std::vector<int>>\
    \ contracted_into;\n        std::vector<int> h_parent_edge;\n        std::vector<int>\
    \ h_even_time;\n        std::vector<int> h_bridge_edge;\n        std::vector<int>\
    \ h_bridge_dir;\n\n        explicit MicaliVaziraniSolver(GeneralMatching& graph_)\n\
    \            : graph(graph_),\n              n(graph_._n),\n              matching_size(0),\n\
    \              delta(0),\n              visit_token(0),\n              even_time_token(0),\n\
    \              base(n),\n              delayed_base(n),\n              label(n,\
    \ unlabeled),\n              h_label(n, unlabeled),\n              parent(n, -1),\n\
    \              parent_edge(n, -1),\n              source_bridge(n, -1),\n    \
    \          target_bridge(n, -1),\n              bridge_edge(n, -1),\n        \
    \      lcp(n, 0),\n              path_mark_1(n, 0),\n              path_mark_2(n,\
    \ 0),\n              rep(n, -1),\n              h_mate(n, -1),\n             \
    \ is_h_edge(graph_._edges.size(), false),\n              contracted_into(n),\n\
    \              h_parent_edge(n, -1),\n              h_even_time(n, 0),\n     \
    \         h_bridge_edge(n, -1),\n              h_bridge_dir(n, 0) {}\n\n     \
    \   bool active(int edge_id) const {\n            return graph._edges[edge_id].alive;\n\
    \        }\n\n        int other(int edge_id, int v) const {\n            return\
    \ graph._edges[edge_id].other(v);\n        }\n\n        int edge_weight(int edge_id)\
    \ const {\n            return graph.is_matched_edge(edge_id) ? 2 : 0;\n      \
    \  }\n\n        void set_match(int edge_id) {\n            const auto& e = graph._edges[edge_id];\n\
    \            graph._mate[e.from] = e.to;\n            graph._mate[e.to] = e.from;\n\
    \            graph._mate_edge[e.from] = edge_id;\n            graph._mate_edge[e.to]\
    \ = edge_id;\n        }\n\n        void initialize_greedy_matching() {\n     \
    \       graph._mate.assign(n, -1);\n            graph._mate_edge.assign(n, -1);\n\
    \            matching_size = 0;\n            for (const auto& e : graph._edges)\
    \ {\n                if (!e.alive) continue;\n                if (graph._mate[e.from]\
    \ != -1 || graph._mate[e.to] != -1) continue;\n                set_match(e.id);\n\
    \                matching_size++;\n            }\n        }\n\n        void scan_edge(int\
    \ edge_id, int from) {\n            if (!active(edge_id)) return;\n          \
    \  int to = other(edge_id, from);\n            if (to == from || graph._mate[to]\
    \ == from || label[base(to)] == odd_label) return;\n            if (label[to]\
    \ == unlabeled) {\n                queue.insert(edge_id, lcp[from] + 2);\n   \
    \         } else {\n                queue.insert(edge_id, (lcp[from] + lcp[to])\
    \ / 2 + 1);\n            }\n        }\n\n        void shrink_path(int blossom_base,\
    \ int x, int y, int edge_id,\n                         std::vector<std::pair<int,\
    \ int>>& delayed_unions) {\n            int v = base(x);\n            while (v\
    \ != blossom_base) {\n                base.unite(v, blossom_base);\n         \
    \       delayed_unions.push_back({v, blossom_base});\n\n                v = graph._mate[v];\n\
    \                assert(v != -1);\n                base.unite(v, blossom_base);\n\
    \                delayed_unions.push_back({v, blossom_base});\n              \
    \  base.make_rep(blossom_base);\n\n                source_bridge[v] = x;\n   \
    \             target_bridge[v] = y;\n                bridge_edge[v] = edge_id;\n\
    \                restore_vertex.push_back(v);\n                restore_value.push_back(lcp[v]);\n\
    \                lcp[v] = lcp[x] + lcp[y] - lcp[graph._mate[v]] + 2;\n\n     \
    \           for (int id : graph._adj[v]) scan_edge(id, v);\n                assert(parent[v]\
    \ != -1);\n                v = base(parent[v]);\n            }\n            delayed_unions.push_back({blossom_base,\
    \ blossom_base});\n        }\n\n        void build_phase_graph() {\n         \
    \   std::fill(h_mate.begin(), h_mate.end(), -1);\n            std::fill(is_h_edge.begin(),\
    \ is_h_edge.end(), false);\n            for (auto& vertices : contracted_into)\
    \ vertices.clear();\n\n            for (int v = 0; v < n; v++) contracted_into[delayed_base(v)].push_back(v);\n\
    \n            for (const auto& e : graph._edges) {\n                if (!e.alive)\
    \ continue;\n                int u = e.from;\n                int v = e.to;\n\
    \                int uh = delayed_base(u);\n                int vh = delayed_base(v);\n\
    \                if (uh == vh) continue;\n                if (label[uh] == odd_label\
    \ && label[vh] == odd_label) continue;\n\n                int w = edge_weight(e.id);\n\
    \                bool even_odd =\n                    (label[uh] == even_label\
    \ && label[vh] == odd_label && lcp[v] == lcp[u] + 1 - w) ||\n                \
    \    (label[vh] == even_label && label[uh] == odd_label && lcp[u] == lcp[v] +\
    \ 1 - w);\n                bool unlabeled_unlabeled = label[uh] == unlabeled &&\
    \ label[vh] == unlabeled && w == 2;\n                bool even_unlabeled =\n \
    \                   (label[uh] == even_label && label[vh] == unlabeled && lcp[u]\
    \ == delta - 2) ||\n                    (label[vh] == even_label && label[uh]\
    \ == unlabeled && lcp[v] == delta - 2);\n                bool even_even = label[uh]\
    \ == even_label && label[vh] == even_label;\n                bool tight_even_even\
    \ = even_even && lcp[u] + lcp[v] == 2 * delta + w - 2;\n\n                if (even_odd\
    \ || unlabeled_unlabeled || even_unlabeled || tight_even_even) {\n           \
    \         is_h_edge[e.id] = true;\n                    if (w == 2) {\n       \
    \                 h_mate[uh] = vh;\n                        h_mate[vh] = uh;\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  bool phase_one() {\n            delta = 0;\n            base.reset(n);\n  \
    \          delayed_base.reset(n);\n            queue.reset(n);\n            std::fill(label.begin(),\
    \ label.end(), unlabeled);\n            std::fill(parent.begin(), parent.end(),\
    \ -1);\n            std::fill(parent_edge.begin(), parent_edge.end(), -1);\n \
    \           std::fill(source_bridge.begin(), source_bridge.end(), -1);\n     \
    \       std::fill(target_bridge.begin(), target_bridge.end(), -1);\n         \
    \   std::fill(bridge_edge.begin(), bridge_edge.end(), -1);\n            std::fill(lcp.begin(),\
    \ lcp.end(), 0);\n\n            for (int v = 0; v < n; v++) {\n              \
    \  if (graph._mate[v] == -1) label[v] = even_label;\n            }\n         \
    \   for (int v = 0; v < n; v++) {\n                if (label[v] != even_label)\
    \ continue;\n                for (int id : graph._adj[v]) scan_edge(id, v);\n\
    \            }\n\n            std::vector<std::pair<int, int>> delayed_unions;\n\
    \            while (delta <= n + 1) {\n                restore_vertex.clear();\n\
    \                restore_value.clear();\n\n                while (true) {\n  \
    \                  int edge_id = queue.pop(delta);\n                    if (edge_id\
    \ == -1) break;\n                    if (!active(edge_id)) continue;\n\n     \
    \               int x = graph._edges[edge_id].from;\n                    int y\
    \ = graph._edges[edge_id].to;\n                    if (label[base(x)] != even_label)\
    \ std::swap(x, y);\n                    if (label[base(x)] != even_label) continue;\n\
    \                    if (graph._mate[x] == y || base(x) == base(y) || label[base(y)]\
    \ == odd_label) continue;\n\n                    if (label[base(y)] == unlabeled)\
    \ {\n                        int z = graph._mate[y];\n                       \
    \ assert(z != -1);\n                        lcp[y] = lcp[x] + 1;\n           \
    \             lcp[z] = lcp[x] + 2;\n                        parent[y] = x;\n \
    \                       parent_edge[y] = edge_id;\n                        parent[z]\
    \ = y;\n                        parent_edge[z] = graph._mate_edge[z];\n      \
    \                  label[y] = odd_label;\n                        label[z] = even_label;\n\
    \                        for (int id : graph._adj[z]) scan_edge(id, z);\n    \
    \                    continue;\n                    }\n\n                    if\
    \ (label[base(y)] != even_label || lcp[x] + lcp[y] != 2 * delta - 2) continue;\n\
    \n                    ++visit_token;\n                    int hx = base(x);\n\
    \                    int hy = base(y);\n                    path_mark_1[hx] =\
    \ visit_token;\n                    path_mark_2[hy] = visit_token;\n         \
    \           while (path_mark_1[hy] != visit_token && path_mark_2[hx] != visit_token\
    \ &&\n                           (graph._mate[hx] != -1 || graph._mate[hy] !=\
    \ -1)) {\n                        if (graph._mate[hx] != -1) {\n             \
    \               assert(parent[graph._mate[hx]] != -1);\n                     \
    \       hx = base(parent[graph._mate[hx]]);\n                            path_mark_1[hx]\
    \ = visit_token;\n                        }\n                        if (graph._mate[hy]\
    \ != -1) {\n                            assert(parent[graph._mate[hy]] != -1);\n\
    \                            hy = base(parent[graph._mate[hy]]);\n           \
    \                 path_mark_2[hy] = visit_token;\n                        }\n\
    \                    }\n\n                    if (path_mark_1[hy] == visit_token\
    \ || path_mark_2[hx] == visit_token) {\n                        int blossom_base\
    \ = path_mark_1[hy] == visit_token ? hy : hx;\n                        shrink_path(blossom_base,\
    \ x, y, edge_id, delayed_unions);\n                        shrink_path(blossom_base,\
    \ y, x, edge_id, delayed_unions);\n                    } else {\n            \
    \            for (int i = int(restore_vertex.size()) - 1; i >= 0; i--) {\n   \
    \                         lcp[restore_vertex[i]] = restore_value[i];\n       \
    \                 }\n                        build_phase_graph();\n          \
    \              return true;\n                    }\n                }\n\n    \
    \            for (auto [a, b] : delayed_unions) {\n                    if (a ==\
    \ b) {\n                        delayed_base.make_rep(a);\n                  \
    \  } else {\n                        delayed_base.unite(a, b);\n             \
    \       }\n                }\n                delayed_unions.clear();\n      \
    \          delta++;\n            }\n            return false;\n        }\n\n \
    \       int next_h_vertex_through_edge(int edge_id, int current_h) const {\n \
    \           const auto& e = graph._edges[edge_id];\n            return rep[rep[e.from]\
    \ == current_h ? e.to : e.from];\n        }\n\n        int find_path_in_h(int\
    \ h_vertex) {\n            for (int v : contracted_into[h_vertex]) {\n       \
    \         for (int edge_id : graph._adj[v]) {\n                    if (!is_h_edge[edge_id])\
    \ continue;\n                    int uh = rep[other(edge_id, v)];\n          \
    \          if (h_mate[h_vertex] == uh) continue;\n\n                    if (h_label[uh]\
    \ == unlabeled) {\n                        int mate_uh = h_mate[uh];\n       \
    \                 h_label[uh] = odd_label;\n                        h_parent_edge[uh]\
    \ = edge_id;\n                        if (mate_uh == -1) return uh;\n\n      \
    \                  h_label[mate_uh] = even_label;\n                        h_even_time[mate_uh]\
    \ = even_time_token++;\n                        int found = find_path_in_h(mate_uh);\n\
    \                        if (found != -1) return found;\n                    }\
    \ else {\n                        int bh = delayed_base(h_vertex);\n         \
    \               int zh = delayed_base(uh);\n                        if (h_even_time[bh]\
    \ >= h_even_time[zh]) continue;\n\n                        std::vector<int> blossom_path;\n\
    \                        std::vector<int> blossom_vertices;\n                \
    \        while (zh != bh) {\n                            blossom_vertices.push_back(zh);\n\
    \                            zh = h_mate[zh];\n                            assert(zh\
    \ != -1);\n                            blossom_vertices.push_back(zh);\n     \
    \                       blossom_path.push_back(zh);\n                        \
    \    assert(h_parent_edge[zh] != -1);\n                            zh = delayed_base(next_h_vertex_through_edge(h_parent_edge[zh],\
    \ zh));\n                        }\n\n                        for (int x : blossom_vertices)\
    \ delayed_base.unite(x, bh);\n                        delayed_base.make_rep(bh);\n\
    \n                        std::reverse(blossom_path.begin(), blossom_path.end());\n\
    \                        for (int x : blossom_path) {\n                      \
    \      h_bridge_edge[x] = edge_id;\n                            h_bridge_dir[x]\
    \ = graph._edges[edge_id].to == v ? 1 : -1;\n                        }\n     \
    \                   for (int x : blossom_path) {\n                           \
    \ int found = find_path_in_h(x);\n                            if (found != -1)\
    \ return found;\n                        }\n                    }\n          \
    \      }\n            }\n            return -1;\n        }\n\n        void collect_path_in_h(std::vector<int>&\
    \ path, int from_h, int to_h) {\n            if (from_h == to_h) return;\n   \
    \         if (h_label[from_h] == even_label) {\n                int mate_from\
    \ = h_mate[from_h];\n                assert(mate_from != -1);\n              \
    \  int edge_id = h_parent_edge[mate_from];\n                assert(edge_id !=\
    \ -1);\n                path.push_back(edge_id);\n                collect_path_in_h(path,\
    \ next_h_vertex_through_edge(edge_id, mate_from), to_h);\n            } else {\n\
    \                int edge_id = h_bridge_edge[from_h];\n                assert(edge_id\
    \ != -1);\n                const auto& e = graph._edges[edge_id];\n          \
    \      int first = rep[h_bridge_dir[from_h] == 1 ? e.from : e.to];\n         \
    \       int second = rep[h_bridge_dir[from_h] == 1 ? e.to : e.from];\n       \
    \         collect_path_in_h(path, first, rep[h_mate[from_h]]);\n             \
    \   path.push_back(edge_id);\n                collect_path_in_h(path, second,\
    \ to_h);\n            }\n        }\n\n        void add_new_pair(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to, int edge_id) const {\n            const auto& e = graph._edges[edge_id];\n\
    \            assert(e.alive);\n            assert((e.from == from && e.to == to)\
    \ || (e.from == to && e.to == from));\n            pairs.push_back(NewMatchingPair{from,\
    \ to, edge_id});\n        }\n\n        void collect_path_in_graph(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to) {\n            if (from == to) return;\n          \
    \  if (label[from] == even_label) {\n                int mate_from = graph._mate[from];\n\
    \                assert(mate_from != -1);\n                int parent_of_mate\
    \ = parent[mate_from];\n                int edge_id = parent_edge[mate_from];\n\
    \                assert(parent_of_mate != -1 && edge_id != -1);\n            \
    \    add_new_pair(pairs, mate_from, parent_of_mate, edge_id);\n              \
    \  collect_path_in_graph(pairs, parent_of_mate, to);\n            } else {\n \
    \               assert(source_bridge[from] != -1 && target_bridge[from] != -1\
    \ && bridge_edge[from] != -1);\n                collect_path_in_graph(pairs, source_bridge[from],\
    \ graph._mate[from]);\n                add_new_pair(pairs, source_bridge[from],\
    \ target_bridge[from], bridge_edge[from]);\n                collect_path_in_graph(pairs,\
    \ target_bridge[from], to);\n            }\n        }\n\n        void augment_path(const\
    \ std::vector<int>& h_path) {\n            std::vector<NewMatchingPair> pairs;\n\
    \            for (int edge_id : h_path) {\n                const auto& e = graph._edges[edge_id];\n\
    \                add_new_pair(pairs, e.from, e.to, edge_id);\n               \
    \ collect_path_in_graph(pairs, e.from, rep[e.from]);\n                collect_path_in_graph(pairs,\
    \ e.to, rep[e.to]);\n            }\n\n            for (const auto& p : pairs)\
    \ {\n                if (graph._mate[p.from] != -1) {\n                    int\
    \ old = graph._mate[p.from];\n                    graph._mate[old] = -1;\n   \
    \                 graph._mate_edge[old] = -1;\n                }\n           \
    \     if (graph._mate[p.to] != -1) {\n                    int old = graph._mate[p.to];\n\
    \                    graph._mate[old] = -1;\n                    graph._mate_edge[old]\
    \ = -1;\n                }\n                graph._mate[p.from] = graph._mate[p.to]\
    \ = -1;\n                graph._mate_edge[p.from] = graph._mate_edge[p.to] = -1;\n\
    \            }\n            for (const auto& p : pairs) {\n                assert(graph._mate[p.from]\
    \ == -1 && graph._mate[p.to] == -1);\n                graph._mate[p.from] = p.to;\n\
    \                graph._mate[p.to] = p.from;\n                graph._mate_edge[p.from]\
    \ = p.edge_id;\n                graph._mate_edge[p.to] = p.edge_id;\n        \
    \    }\n            matching_size++;\n        }\n\n        void phase_two() {\n\
    \            std::fill(h_label.begin(), h_label.end(), unlabeled);\n         \
    \   std::fill(h_parent_edge.begin(), h_parent_edge.end(), -1);\n            std::fill(h_bridge_edge.begin(),\
    \ h_bridge_edge.end(), -1);\n            std::fill(h_bridge_dir.begin(), h_bridge_dir.end(),\
    \ 0);\n            for (int v = 0; v < n; v++) rep[v] = delayed_base(v);\n\n \
    \           std::vector<std::vector<int>> paths;\n            for (int h_vertex\
    \ = 0; h_vertex < n; h_vertex++) {\n                if (rep[h_vertex] != h_vertex)\
    \ continue;\n                if (h_label[h_vertex] != unlabeled || h_mate[h_vertex]\
    \ != -1) continue;\n\n                h_label[h_vertex] = even_label;\n      \
    \          h_even_time[h_vertex] = even_time_token++;\n                int free_h\
    \ = find_path_in_h(h_vertex);\n                if (free_h == -1) continue;\n\n\
    \                std::vector<int> path;\n                int edge_id = h_parent_edge[free_h];\n\
    \                assert(edge_id != -1);\n                path.push_back(edge_id);\n\
    \                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, free_h),\
    \ h_vertex);\n                paths.push_back(path);\n            }\n\n      \
    \      assert(!paths.empty());\n            for (const auto& path : paths) augment_path(path);\n\
    \            for (auto& vertices : contracted_into) vertices.clear();\n      \
    \  }\n\n        int solve() {\n            initialize_greedy_matching();\n   \
    \         while (phase_one()) phase_two();\n            return matching_size;\n\
    \        }\n    };\n\n   public:\n    GeneralMatching() : GeneralMatching(0) {}\n\
    \n    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n,\
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
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        MicaliVaziraniSolver\
    \ solver(*this);\n        int result = solver.solve();\n\n        _calculated\
    \ = true;\n        return result;\n    }\n\n    int matching_size() {\n      \
    \  ensure_matching();\n        int result = 0;\n        for (int v = 0; v < _n;\
    \ v++) {\n            if (v < _mate[v]) result++;\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n        return\
    \ _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (v < _mate[v]) result.push_back(Pair{v,\
    \ _mate[v], _mate_edge[v]});\n        }\n        return result;\n    }\n\n   \
    \ std::optional<std::vector<int>> minimum_edge_cover() {\n        ensure_matching();\n\
    \n        std::vector<int> result;\n        std::vector<char> covered(_n, false),\
    \ used_edge(_edges.size(), false);\n\n        auto use_edge = [&](int id) {\n\
    \            if (used_edge[id]) return;\n            used_edge[id] = true;\n \
    \           result.push_back(id);\n            covered[_edges[id].from] = true;\n\
    \            covered[_edges[id].to] = true;\n        };\n\n        for (int v\
    \ = 0; v < _n; v++) {\n            if (v < _mate[v]) use_edge(_mate_edge[v]);\n\
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
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/grid.hpp\"\
    \n\n\n\n#include <array>\n#line 8 \"graph/grid.hpp\"\n\n#line 10 \"graph/grid.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct Grid {\n   private:\n    int\
    \ _h;\n    int _w;\n\n   public:\n    static constexpr std::array<int, 4> di4\
    \ = {-1, 0, 1, 0};\n    static constexpr std::array<int, 4> dj4 = {0, 1, 0, -1};\n\
    \    static constexpr std::array<int, 8> di8 = {-1, -1, -1, 0, 0, 1, 1, 1};\n\
    \    static constexpr std::array<int, 8> dj8 = {-1, 0, 1, -1, 1, -1, 0, 1};\n\n\
    \    Grid() : _h(0), _w(0) {}\n    Grid(int h, int w) : _h(h), _w(w) {\n     \
    \   assert(0 <= h);\n        assert(0 <= w);\n    }\n\n    int height() const\
    \ {\n        return _h;\n    }\n\n    int width() const {\n        return _w;\n\
    \    }\n\n    int size() const {\n        return _h * _w;\n    }\n\n    bool empty()\
    \ const {\n        return size() == 0;\n    }\n\n    bool inside(int i, int j)\
    \ const {\n        return 0 <= i && i < _h && 0 <= j && j < _w;\n    }\n\n   \
    \ int id(int i, int j) const {\n        assert(inside(i, j));\n        return\
    \ i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v) const {\n        assert(0\
    \ <= v && v < size());\n        return {v / _w, v % _w};\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj4(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(4);\n        for (int k = 0; k < 4; k++)\
    \ {\n            int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<std::pair<int, int>> adj8(int i, int j) const {\n        assert(inside(i,\
    \ j));\n        std::vector<std::pair<int, int>> result;\n        result.reserve(8);\n\
    \        for (int k = 0; k < 8; k++) {\n            int ni = i + di8[k], nj =\
    \ j + dj8[k];\n            if (inside(ni, nj)) result.emplace_back(ni, nj);\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> adj4_ids(int\
    \ v) const {\n        auto [i, j] = pos(v);\n        std::vector<int> result;\n\
    \        result.reserve(4);\n        for (auto [ni, nj] : adj4(i, j)) result.push_back(id(ni,\
    \ nj));\n        return result;\n    }\n\n    std::vector<int> adj8_ids(int v)\
    \ const {\n        auto [i, j] = pos(v);\n        std::vector<int> result;\n \
    \       result.reserve(8);\n        for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni,\
    \ nj));\n        return result;\n    }\n\n    Graph<int> graph4() const {\n  \
    \      return graph4([](int, int) { return true; });\n    }\n\n    Graph<int>\
    \ graph8() const {\n        return graph8([](int, int) { return true; });\n  \
    \  }\n\n    template <class Passable>\n    Graph<int> graph4(Passable passable)\
    \ const {\n        Graph<int> g(size());\n        for (int i = 0; i < _h; i++)\
    \ {\n            for (int j = 0; j < _w; j++) {\n                if (!passable(i,\
    \ j)) continue;\n                int v = id(i, j);\n                for (auto\
    \ [ni, nj] : adj4(i, j)) {\n                    if (!passable(ni, nj)) continue;\n\
    \                    int to = id(ni, nj);\n                    if (v < to) g.add_edge(v,\
    \ to);\n                }\n            }\n        }\n        return g;\n    }\n\
    \n    template <class Passable>\n    Graph<int> graph8(Passable passable) const\
    \ {\n        Graph<int> g(size());\n        for (int i = 0; i < _h; i++) {\n \
    \           for (int j = 0; j < _w; j++) {\n                if (!passable(i, j))\
    \ continue;\n                int v = id(i, j);\n                for (auto [ni,\
    \ nj] : adj8(i, j)) {\n                    if (!passable(ni, nj)) continue;\n\
    \                    int to = id(ni, nj);\n                    if (v < to) g.add_edge(v,\
    \ to);\n                }\n            }\n        }\n        return g;\n    }\n\
    };\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/kruskal.hpp\"\
    \n\n\n\n#line 6 \"graph/kruskal.hpp\"\n\n#line 9 \"graph/kruskal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct MinimumSpanningForest\
    \ {\n    T cost;\n    std::vector<Edge<T>> edges;\n    int components;\n\n   \
    \ bool is_spanning_tree(int n) const {\n        return components <= 1 && int(edges.size())\
    \ == std::max(0, n - 1);\n    }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T>\
    \ kruskal(const Graph<T>& g) {\n    int n = g.size();\n    auto edges = g.edges();\n\
    \    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {\n\
    \        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu dsu(n);\n    MinimumSpanningForest<T>\
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
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            if (e.id == parent_edge) continue;\n            int to\
    \ = e.to;\n            if (result.ord[to] == -1) {\n                child_count++;\n\
    \                self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
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
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MinimumVertexCoverResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nnamespace detail {\n\nstruct MaximumIndependentSetBranching {\n\
    \    int n;\n    std::vector<std::vector<char>> adjacent;\n    std::vector<std::vector<int>>\
    \ graph;\n\n    explicit MaximumIndependentSetBranching(const std::vector<std::vector<char>>&\
    \ adjacent_)\n        : n(int(adjacent_.size())), adjacent(adjacent_), graph(n)\
    \ {\n        for (int v = 0; v < n; v++) {\n            for (int to = 0; to <\
    \ n; to++) {\n                if (adjacent[v][to]) graph[v].push_back(to);\n \
    \           }\n        }\n    }\n\n    std::vector<int> solve_path(const std::vector<int>&\
    \ order) const {\n        int m = int(order.size());\n        if (m == 0) return\
    \ {};\n\n        std::vector<int> dp0(m, 0), dp1(m, 0);\n        dp1[0] = 1;\n\
    \        for (int i = 1; i < m; i++) {\n            dp0[i] = std::max(dp0[i -\
    \ 1], dp1[i - 1]);\n            dp1[i] = dp0[i - 1] + 1;\n        }\n\n      \
    \  std::vector<int> result;\n        int state = (dp1[m - 1] > dp0[m - 1] ? 1\
    \ : 0);\n        for (int i = m - 1; i >= 0; i--) {\n            if (state ==\
    \ 1) {\n                result.push_back(order[i]);\n                state = 0;\n\
    \            } else if (i > 0) {\n                state = (dp1[i - 1] > dp0[i\
    \ - 1] ? 1 : 0);\n            }\n        }\n        return result;\n    }\n\n\
    \    std::vector<int> solve_cycle(const std::vector<int>& order) const {\n   \
    \     int m = int(order.size());\n        if (m == 0) return {};\n        if (m\
    \ == 1) return {order[0]};\n\n        std::vector<int> without_first(order.begin()\
    \ + 1, order.end());\n        auto result_without = solve_path(without_first);\n\
    \n        std::vector<int> result_with = {order[0]};\n        if (m >= 4) {\n\
    \            std::vector<int> middle(order.begin() + 2, order.end() - 1);\n  \
    \          auto middle_result = solve_path(middle);\n            result_with.insert(result_with.end(),\
    \ middle_result.begin(), middle_result.end());\n        }\n\n        return (result_with.size()\
    \ > result_without.size() ? result_with : result_without);\n    }\n\n    std::vector<int>\
    \ solve_degree_at_most_two(const std::vector<char>& active,\n                \
    \                              const std::vector<int>& degree) const {\n     \
    \   std::vector<int> result;\n        std::vector<char> visited(n, false);\n\n\
    \        for (int s = 0; s < n; s++) {\n            if (!active[s] || visited[s])\
    \ continue;\n\n            std::vector<int> component;\n            std::vector<int>\
    \ stack = {s};\n            visited[s] = true;\n            for (int it = 0; it\
    \ < int(stack.size()); it++) {\n                int v = stack[it];\n         \
    \       component.push_back(v);\n                for (int to : graph[v]) {\n \
    \                   if (!active[to] || visited[to]) continue;\n              \
    \      visited[to] = true;\n                    stack.push_back(to);\n       \
    \         }\n            }\n\n            if (component.size() == 1) {\n     \
    \           result.push_back(component[0]);\n                continue;\n     \
    \       }\n\n            int endpoint = -1;\n            for (int v : component)\
    \ {\n                if (degree[v] <= 1) {\n                    endpoint = v;\n\
    \                    break;\n                }\n            }\n\n            std::vector<int>\
    \ order;\n            if (endpoint != -1) {\n                int prev = -1, cur\
    \ = endpoint;\n                while (cur != -1) {\n                    order.push_back(cur);\n\
    \                    int next = -1;\n                    for (int to : graph[cur])\
    \ {\n                        if (active[to] && to != prev) {\n               \
    \             next = to;\n                            break;\n               \
    \         }\n                    }\n                    prev = cur;\n        \
    \            cur = next;\n                }\n                auto part = solve_path(order);\n\
    \                result.insert(result.end(), part.begin(), part.end());\n    \
    \        } else {\n                int start = component[0];\n               \
    \ int first = -1;\n                for (int to : graph[start]) {\n           \
    \         if (active[to]) {\n                        first = to;\n           \
    \             break;\n                    }\n                }\n             \
    \   assert(first != -1);\n\n                order.push_back(start);\n        \
    \        int prev = start, cur = first;\n                while (cur != start)\
    \ {\n                    order.push_back(cur);\n                    int next =\
    \ -1;\n                    for (int to : graph[cur]) {\n                     \
    \   if (active[to] && to != prev) {\n                            next = to;\n\
    \                            break;\n                        }\n             \
    \       }\n                    assert(next != -1);\n                    prev =\
    \ cur;\n                    cur = next;\n                }\n                auto\
    \ part = solve_cycle(order);\n                result.insert(result.end(), part.begin(),\
    \ part.end());\n            }\n        }\n\n        return result;\n    }\n\n\
    \    std::vector<int> solve(std::vector<char> active) const {\n        int active_count\
    \ = 0;\n        int max_degree = -1;\n        int branch_vertex = -1;\n      \
    \  std::vector<int> degree(n, 0);\n\n        for (int v = 0; v < n; v++) {\n \
    \           if (!active[v]) continue;\n            active_count++;\n         \
    \   for (int to : graph[v]) {\n                if (active[to]) degree[v]++;\n\
    \            }\n            if (degree[v] > max_degree) {\n                max_degree\
    \ = degree[v];\n                branch_vertex = v;\n            }\n        }\n\
    \n        if (active_count == 0) return {};\n        if (max_degree <= 2) {\n\
    \            auto result = solve_degree_at_most_two(active, degree);\n       \
    \     std::sort(result.begin(), result.end());\n            return result;\n \
    \       }\n\n        auto without = active;\n        without[branch_vertex] =\
    \ false;\n        auto result_without = solve(without);\n\n        auto with =\
    \ active;\n        with[branch_vertex] = false;\n        for (int to : graph[branch_vertex])\
    \ with[to] = false;\n        auto result_with = solve(with);\n        result_with.push_back(branch_vertex);\n\
    \n        auto result = (result_with.size() > result_without.size() ? result_with\
    \ : result_without);\n        std::sort(result.begin(), result.end());\n     \
    \   return result;\n    }\n\n    std::vector<int> solve() const {\n        std::vector<char>\
    \ active(n, true);\n        return solve(active);\n    }\n};\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<std::vector<char>> adjacent(n,\
    \ std::vector<char>(n, false));\n    for (const auto& e : g.edges()) {\n     \
    \   if (e.from == e.to) continue;\n        adjacent[e.from][e.to] = true;\n  \
    \      adjacent[e.to][e.from] = true;\n    }\n    return adjacent;\n}\n\nstd::vector<std::vector<char>>\
    \ complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent)\
    \ {\n    int n = int(adjacent.size());\n    std::vector<std::vector<char>> complement(n,\
    \ std::vector<char>(n, false));\n    for (int i = 0; i < n; i++) {\n        for\
    \ (int j = i + 1; j < n; j++) {\n            if (adjacent[i][j]) continue;\n \
    \           complement[i][j] = true;\n            complement[j][i] = true;\n \
    \       }\n    }\n    return complement;\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class T>\nbool is_clique(const Graph<T>& g, const std::vector<int>& vertices)\
    \ {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    for (int\
    \ v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n    for (int\
    \ i = 0; i < int(vertices.size()); i++) {\n        for (int j = i + 1; j < int(vertices.size());\
    \ j++) {\n            if (!adjacent[vertices[i]][vertices[j]]) return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {\n\
    \    std::vector<char> selected(g.size(), false);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        selected[v] = true;\n  \
    \  }\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        if (!selected[e.from] && !selected[e.to]) return false;\n    }\n    return\
    \ true;\n}\n\ntemplate <class T>\nMaximumCliqueResult maximum_clique(const Graph<T>&\
    \ g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    auto\
    \ complement = detail::complement_adjacency_matrix(adjacent);\n    detail::MaximumIndependentSetBranching\
    \ solver(complement);\n    return MaximumCliqueResult{solver.solve()};\n}\n\n\
    template <class T>\nint maximum_clique_size(const Graph<T>& g) {\n    return maximum_clique(g).size();\n\
    }\n\ntemplate <class T>\nMaximumIndependentSetResult maximum_independent_set(const\
    \ Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumIndependentSetBranching solver(adjacent);\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\ntemplate <class T>\nMinimumVertexCoverResult\
    \ minimum_vertex_cover(const Graph<T>& g) {\n    auto independent = maximum_independent_set(g);\n\
    \    std::vector<char> in_independent(g.size(), false);\n    for (int v : independent.vertices)\
    \ in_independent[v] = true;\n\n    MinimumVertexCoverResult result;\n    for (int\
    \ v = 0; v < g.size(); v++) {\n        if (!in_independent[v]) result.vertices.push_back(v);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nint minimum_vertex_cover_size(const\
    \ Graph<T>& g) {\n    return minimum_vertex_cover(g).size();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/namori.hpp\"\n\n\n\n#line\
    \ 9 \"graph/namori.hpp\"\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int\
    \ component_count;\n    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/shortest_path.hpp\"\n\n\n\n\
    #line 1 \"graph/bellman_ford.hpp\"\n\n\n\n#line 6 \"graph/bellman_ford.hpp\"\n\
    #include <limits>\n#line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\
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
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/cow_game.hpp\"\
    \n\n\n\n#line 7 \"graph/cow_game.hpp\"\n#include <type_traits>\n#line 10 \"graph/cow_game.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct CowGameConstraint\
    \ {\n    int from;\n    int to;\n    T upper_bound;\n};\n\ntemplate <class T>\n\
    struct CowGameSolution {\n    bool feasible = false;\n    std::vector<T> value;\n\
    \n    bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameUpperBounds {\n    bool feasible;\n    std::vector<T>\
    \ upper_bound;\n    T inf;\n\n    bool is_feasible() const {\n        return feasible;\n\
    \    }\n\n    bool bounded(int variable) const {\n        assert(0 <= variable\
    \ && variable < int(upper_bound.size()));\n        return feasible && upper_bound[variable]\
    \ != inf;\n    }\n};\n\ntemplate <class T>\nstruct CowGameDifferenceBounds {\n\
    \    bool feasible;\n    std::optional<T> lower_bound;\n    std::optional<T> upper_bound;\n\
    \n    bool is_feasible() const {\n        return feasible;\n    }\n\n    bool\
    \ bounded_below() const {\n        return feasible && lower_bound.has_value();\n\
    \    }\n\n    bool bounded_above() const {\n        return feasible && upper_bound.has_value();\n\
    \    }\n};\n\ntemplate <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"\
    graph/dag_shortest_path.hpp\"\n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\n\
    \n#line 1 \"graph/topological_sort.hpp\"\n\n\n\n#line 7 \"graph/topological_sort.hpp\"\
    \n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_shortest_path.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagShortestPathResult\
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
    \n\n#line 11 \"graph/shortest_path.hpp\"\n\n\n#line 15 \"graph/undirected.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_UNDIRECTED_HPP

    #define M1UNE_GRAPH_UNDIRECTED_HPP 1


    #include "bipartite.hpp"

    #include "connected_components.hpp"

    #include "cycle_detection.hpp"

    #include "general_matching.hpp"

    #include "graph.hpp"

    #include "grid.hpp"

    #include "kruskal.hpp"

    #include "lowlink.hpp"

    #include "maximum_clique.hpp"

    #include "namori.hpp"

    #include "shortest_path.hpp"


    #endif  // M1UNE_GRAPH_UNDIRECTED_HPP

    '
  dependsOn:
  - graph/bipartite.hpp
  - graph/graph.hpp
  - graph/connected_components.hpp
  - ds/dsu/dsu.hpp
  - graph/cycle_detection.hpp
  - graph/general_matching.hpp
  - graph/grid.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/maximum_clique.hpp
  - graph/namori.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/cow_game.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  isVerificationFile: false
  path: graph/undirected.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-23 12:19:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/undirected.hpp
layout: document
title: Undirected Graph Algorithms
---

## Overview

`graph/undirected.hpp` includes algorithms whose main interpretation is
undirected, plus the shortest-path bundle. In that bundle, use the
direction-respecting algorithms on graphs built with `add_edge`; the DAG
shortest-path helper is directed-only.

Use this header when edges represent two-way movement or an endpoint constraint
where direction should not matter.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Mixed shortest-path bundle | Use BFS, 0-1 BFS, Dijkstra, Bellman-Ford, and Warshall-Floyd on undirected graphs built with `add_edge`; DAG shortest path is directed-only. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/general_matching.hpp` | Undirected only | Maximum-cardinality matching and minimum edge cover in general undirected graphs. |
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique, maximum independent set, and minimum vertex cover with bitset branch-and-bound. |
| `graph/namori.hpp` | Undirected Namori graph | Ordered cycles and the trees attached to them. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
