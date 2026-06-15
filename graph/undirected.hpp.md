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
    title: Maximum Clique and Independent Set
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
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
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
    \n\n#line 1 \"data_structure/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #line 7 \"data_structure/dsu.hpp\"\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the\
    \ parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
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
    \  }\n\n    int lca(int a, int b, const std::vector<int>& base, const std::vector<int>&\
    \ parent) const {\n        std::vector<char> used(_n, false);\n        while (true)\
    \ {\n            a = base[a];\n            used[a] = true;\n            if (_mate[a]\
    \ == -1) break;\n            a = parent[_mate[a]];\n        }\n        while (true)\
    \ {\n            b = base[b];\n            if (used[b]) return b;\n          \
    \  b = parent[_mate[b]];\n        }\n    }\n\n    void mark_path(int v, int b,\
    \ int child, int child_edge, std::vector<int>& base, std::vector<int>& parent,\n\
    \                   std::vector<int>& parent_edge, std::vector<char>& blossom)\
    \ const {\n        while (base[v] != b) {\n            blossom[base[v]] = true;\n\
    \            blossom[base[_mate[v]]] = true;\n            parent[v] = child;\n\
    \            parent_edge[v] = child_edge;\n\n            int matched = _mate[v];\n\
    \            int next_v = parent[matched];\n            int next_edge = parent_edge[matched];\n\
    \            child = matched;\n            child_edge = next_edge;\n         \
    \   v = next_v;\n        }\n    }\n\n    int find_augmenting_path(int root, std::vector<int>&\
    \ parent, std::vector<int>& parent_edge) const {\n        std::vector<char> used(_n,\
    \ false), blossom(_n, false);\n        std::vector<int> base(_n);\n        std::queue<int>\
    \ que;\n\n        parent.assign(_n, -1);\n        parent_edge.assign(_n, -1);\n\
    \        for (int i = 0; i < _n; i++) base[i] = i;\n\n        used[root] = true;\n\
    \        que.push(root);\n        while (!que.empty()) {\n            int v =\
    \ que.front();\n            que.pop();\n            for (int id : _adj[v]) {\n\
    \                const auto& e = _edges[id];\n                if (!e.alive) continue;\n\
    \                int u = e.other(v);\n                if (base[v] == base[u] ||\
    \ _mate[v] == u) continue;\n\n                if (u == root || (_mate[u] != -1\
    \ && parent[_mate[u]] != -1)) {\n                    int cur_base = lca(v, u,\
    \ base, parent);\n                    std::fill(blossom.begin(), blossom.end(),\
    \ false);\n                    mark_path(v, cur_base, u, id, base, parent, parent_edge,\
    \ blossom);\n                    mark_path(u, cur_base, v, id, base, parent, parent_edge,\
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
    \  // namespace m1une\n\n\n#line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1\
    \ \"graph/bellman_ford.hpp\"\n\n\n\n#line 6 \"graph/bellman_ford.hpp\"\n#include\
    \ <limits>\n#line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\
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
    \n\n#line 10 \"graph/shortest_path.hpp\"\n\n\n#line 14 \"graph/undirected.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_UNDIRECTED_HPP

    #define M1UNE_GRAPH_UNDIRECTED_HPP 1


    #include "graph/bipartite.hpp"

    #include "graph/connected_components.hpp"

    #include "graph/cycle_detection.hpp"

    #include "graph/general_matching.hpp"

    #include "graph/graph.hpp"

    #include "graph/grid.hpp"

    #include "graph/kruskal.hpp"

    #include "graph/lowlink.hpp"

    #include "graph/maximum_clique.hpp"

    #include "graph/shortest_path.hpp"


    #endif  // M1UNE_GRAPH_UNDIRECTED_HPP

    '
  dependsOn:
  - graph/bipartite.hpp
  - graph/graph.hpp
  - graph/connected_components.hpp
  - data_structure/dsu.hpp
  - graph/cycle_detection.hpp
  - graph/general_matching.hpp
  - graph/grid.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/maximum_clique.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  isVerificationFile: false
  path: graph/undirected.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-16 03:14:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
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
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique and maximum independent set with bitset branch-and-bound. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |
