---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/general_matching.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <optional>\n#include <queue>\n#include <vector>\n\
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
    \ m1une\n\n\n#line 11 \"graph/general_matching.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct GeneralMatching {\n    struct Edge {\n        int from;\n\
    \        int to;\n        int id;\n        bool alive;\n\n        int other(int\
    \ v) const {\n            assert(v == from || v == to);\n            return from\
    \ ^ to ^ v;\n        }\n    };\n\n    struct Pair {\n        int from;\n     \
    \   int to;\n        int edge_id;\n    };\n\n   private:\n    int _n;\n    std::vector<Edge>\
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
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_GENERAL_MATCHING_HPP\n#define M1UNE_GRAPH_GENERAL_MATCHING_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <queue>\n#include <vector>\n\n#include \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\nstruct GeneralMatching {\n    struct Edge {\n      \
    \  int from;\n        int to;\n        int id;\n        bool alive;\n\n      \
    \  int other(int v) const {\n            assert(v == from || v == to);\n     \
    \       return from ^ to ^ v;\n        }\n    };\n\n    struct Pair {\n      \
    \  int from;\n        int to;\n        int edge_id;\n    };\n\n   private:\n \
    \   int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
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
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_GENERAL_MATCHING_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/general_matching.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-16 03:05:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/general_matching.hpp
layout: document
title: General Matching
---

## Overview

`GeneralMatching` finds a maximum-cardinality matching in a general undirected
graph. Unlike `BipartiteMatching`, the graph does not need to be bipartite:
odd cycles are allowed.

A matching is a set of edges where no two selected edges share a vertex.
Maximum-cardinality matching means the solver maximizes the number of selected
edges. This is unweighted matching; edge costs are not used.

The implementation uses Edmonds' blossom algorithm. The key idea is that an
odd cycle can block a simple augmenting-path search. Blossom contraction treats
such an odd cycle as one temporary super-vertex, searches for an augmenting
path in the contracted graph, then expands the cycle when augmenting the
matching.

## Graph Orientation

Undirected only. An edge added by `add_edge(from, to)` connects `from` and
`to` symmetrically.

The helper `make_general_matching(g)` accepts a `Graph<T>` and ignores edge
direction: every active edge becomes one undirected matching edge.

Self-loops are not valid matching edges.

## How to Use It

Use `GeneralMatching gm(n)` when you already have vertex ids `0..n-1`, then
add undirected edges with `add_edge(from, to)`.

Call `max_matching()` to compute the maximum matching. After that, use
`matching()`, `mate()`, or `mate_edge()` to inspect the result.

Use `minimum_edge_cover()` when you want the smallest set of edges that covers
every vertex. It starts from a maximum matching and adds one incident edge for
each uncovered vertex. If an isolated vertex exists, no edge cover exists and
the method returns `std::nullopt`.

Use `make_general_matching(g)` when your graph is already stored as `Graph<T>`.
The returned `GeneralMatchingGraph` keeps the mapping from matching edge ids
back to the original `Graph<T>` edge ids.

## Fields

`GeneralMatching::Edge` contains these fields:

| Field / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `from` | `int` | One endpoint. |
| `to` | `int` | The other endpoint. |
| `id` | `int` | Edge id returned by `add_edge`. |
| `alive` | `bool` | Whether this edge is currently usable. |
| `other` | `int other(int v) const` | Returns the opposite endpoint of `v`. |

`GeneralMatching::Pair` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | One matched endpoint. |
| `to` | `int` | The other matched endpoint. |
| `edge_id` | `int` | Edge id used by this matched pair. |

`GeneralMatchingGraph` contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `matching` | `GeneralMatching` | Matching graph using the same vertex ids as the original graph. |
| `original_edge_id` | `std::vector<int>` | `original_edge_id[e]` is the original `Graph<T>` edge id for matching edge `e`. |
| `original_edge` | `int original_edge(int edge_id) const` | Converts a matching edge id back to the original graph edge id. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `GeneralMatching()` | Creates an empty matching graph. | $O(1)$ |
| Constructor | `explicit GeneralMatching(int n)` | Creates a matching graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of registered edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to)` | Adds an undirected edge and returns its id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges(bool include_inactive = false) const` | Returns active edges, or all edges if `include_inactive` is true. | $O(M)$ |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Sets whether edge `id` is usable. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks edge `id` unusable. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks edge `id` usable again. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether edge `id` is usable. | $O(1)$ |
| `max_matching` | `int max_matching()` | Computes and stores a maximum matching. | $O(N^3)$ |
| `matching_size` | `int matching_size()` | Returns the current maximum matching size, computing it if needed. | $O(N^3)$ if not computed |
| `mate` | `std::vector<int> mate()` | Returns the matched vertex of each vertex, or `-1`. | $O(N^3)$ if not computed |
| `mate_edge` | `std::vector<int> mate_edge()` | Returns the matched edge id of each vertex, or `-1`. | $O(N^3)$ if not computed |
| `matching` | `std::vector<Pair> matching()` | Returns matched pairs and edge ids. | $O(N^3)$ if not computed |
| `minimum_edge_cover` | `std::optional<std::vector<int>> minimum_edge_cover()` | Returns edge ids of a minimum edge cover, or `std::nullopt` if an isolated vertex exists. | $O(N^3)$ if not computed |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `make_general_matching` | `template <class T> GeneralMatchingGraph make_general_matching(const Graph<T>& g)` | Builds a `GeneralMatching` from active edges of `g` and stores original edge-id mapping. | $O(N+M)$ |

## Example

```cpp
#include "graph/general_matching.hpp"
#include <iostream>

int main() {
    m1une::graph::GeneralMatching gm(6);
    gm.add_edge(0, 1);
    gm.add_edge(1, 2);
    gm.add_edge(2, 3);
    gm.add_edge(3, 4);
    gm.add_edge(4, 0);
    gm.add_edge(1, 5);

    std::cout << gm.max_matching() << "\n";  // 3
    for (auto p : gm.matching()) {
        std::cout << p.from << " " << p.to << "\n";
    }
}
```
