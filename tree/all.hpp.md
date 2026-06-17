---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: tree/diameter.hpp
    title: Tree Diameter
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition
  - icon: ':heavy_check_mark:'
    path: tree/rerooting_dp.hpp
    title: Rerooting DP
  - icon: ':heavy_check_mark:'
    path: tree/rerooting_static_top_tree.hpp
    title: Rerooting Static Top Tree
  - icon: ':heavy_check_mark:'
    path: tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  - icon: ':heavy_check_mark:'
    path: tree/static_top_tree.hpp
    title: Static Top Tree
  - icon: ':heavy_check_mark:'
    path: tree/tree.hpp
    title: Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/all.hpp\"\n\n\n\n#line 1 \"tree/centroid_decomposition.hpp\"\
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
    \ m1une\n\n\n#line 8 \"tree/centroid_decomposition.hpp\"\n\nnamespace m1une {\n\
    namespace tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition {\n\
    \    int n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n    std::vector<int>\
    \ order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>> children;\n\
    \n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int> _work_parent;\n\
    \    std::vector<char> _removed;\n\n    void build_component(const m1une::graph::Graph<T>&\
    \ g, int start, int p, int d) {\n        std::vector<int> nodes;\n        std::vector<int>\
    \ stack = {start};\n        _work_parent[start] = -2;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      nodes.push_back(v);\n            for (const auto& e : g[v]) {\n       \
    \         if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ != -1) continue;\n                _work_parent[e.to] = v;\n                stack.push_back(e.to);\n\
    \            }\n        }\n\n        for (int v : nodes) _subtree_size[v] = 1;\n\
    \        for (int i = int(nodes.size()) - 1; i >= 0; i--) {\n            int v\
    \ = nodes[i];\n            if (_work_parent[v] >= 0) _subtree_size[_work_parent[v]]\
    \ += _subtree_size[v];\n        }\n\n        int total = int(nodes.size());\n\
    \        int centroid = start;\n        int best = total + 1;\n        for (int\
    \ v : nodes) {\n            int largest = total - _subtree_size[v];\n        \
    \    for (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to])\
    \ continue;\n                if (_work_parent[e.to] == v) largest = std::max(largest,\
    \ _subtree_size[e.to]);\n            }\n            if (largest < best) {\n  \
    \              best = largest;\n                centroid = v;\n            }\n\
    \        }\n\n        for (int v : nodes) _work_parent[v] = -1;\n\n        parent[centroid]\
    \ = p;\n        depth[centroid] = d;\n        order.push_back(centroid);\n   \
    \     if (p == -1) {\n            roots.push_back(centroid);\n        } else {\n\
    \            children[p].push_back(centroid);\n        }\n        _removed[centroid]\
    \ = true;\n\n        for (const auto& e : g[centroid]) {\n            if (!e.alive\
    \ || _removed[e.to]) continue;\n            build_component(g, e.to, centroid,\
    \ d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition() : n(0)\
    \ {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>& g) {\n\
    \        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>& g) {\n\
    \        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"tree/diameter.hpp\"\n\n\n\n#line\
    \ 6 \"tree/diameter.hpp\"\n\n#line 8 \"tree/diameter.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\ntemplate <class T = int>\nstruct TreeDiameter {\n   \
    \ T cost;\n    int edge_count;\n    int from;\n    int to;\n    std::vector<int>\
    \ vertices;\n    std::vector<int> edge_ids;\n\n    bool empty() const {\n    \
    \    return vertices.empty();\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ T>\nstruct FarthestResult {\n    int vertex;\n    std::vector<char> seen;\n\
    \    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n};\n\ntemplate <class T>\nFarthestResult<T> farthest_from(const\
    \ m1une::graph::Graph<T>& g, int start) {\n    int n = g.size();\n    FarthestResult<T>\
    \ result;\n    result.vertex = start;\n    result.seen.assign(n, false);\n   \
    \ result.dist.assign(n, T(0));\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n,\
    \ -1);\n\n    std::vector<int> stack = {start};\n    result.seen[start] = true;\n\
    \    while (!stack.empty()) {\n        int v = stack.back();\n        stack.pop_back();\n\
    \        if (result.dist[result.vertex] < result.dist[v]) result.vertex = v;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.seen[e.to]) continue;\n            result.seen[e.to] =\
    \ true;\n            result.dist[e.to] = result.dist[v] + e.cost;\n          \
    \  result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n  \
    \          stack.push_back(e.to);\n        }\n    }\n    return result;\n}\n\n\
    }  // namespace internal\n\ntemplate <class T>\nTreeDiameter<T> tree_diameter(const\
    \ m1une::graph::Graph<T>& g) {\n    int n = g.size();\n    TreeDiameter<T> best;\n\
    \    best.cost = T(0);\n    best.edge_count = 0;\n    best.from = -1;\n    best.to\
    \ = -1;\n    if (n == 0) return best;\n\n    std::vector<char> done(n, false);\n\
    \    for (int start = 0; start < n; start++) {\n        if (done[start]) continue;\n\
    \        auto first = internal::farthest_from(g, start);\n        for (int v =\
    \ 0; v < n; v++) {\n            if (first.seen[v]) done[v] = true;\n        }\n\
    \        auto second = internal::farthest_from(g, first.vertex);\n        int\
    \ a = first.vertex;\n        int b = second.vertex;\n        T cost = second.dist[b];\n\
    \        if (best.from != -1 && !(best.cost < cost)) continue;\n\n        best.cost\
    \ = cost;\n        best.from = a;\n        best.to = b;\n        best.vertices.clear();\n\
    \        best.edge_ids.clear();\n        for (int v = b; v != -1; v = second.parent[v])\
    \ {\n            best.vertices.push_back(v);\n            if (v != a) best.edge_ids.push_back(second.parent_edge[v]);\n\
    \        }\n        std::reverse(best.vertices.begin(), best.vertices.end());\n\
    \        std::reverse(best.edge_ids.begin(), best.edge_ids.end());\n        best.edge_count\
    \ = int(best.edge_ids.size());\n    }\n\n    return best;\n}\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"tree/heavy_light_decomposition.hpp\"\
    \n\n\n\n#line 8 \"tree/heavy_light_decomposition.hpp\"\n\n#line 10 \"tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nstruct HldPathSegment {\n    int l;\n\
    \    int r;\n    bool reversed;\n};\n\ntemplate <class T = int>\nstruct HeavyLightDecomposition\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy;\n    std::vector<int> head;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n        assert(tin[v] != -1);\n    }\n\n    static void add_segment(std::vector<HldPathSegment>&\
    \ result, int l, int r, bool reversed) {\n        if (l < r) result.push_back({l,\
    \ r, reversed});\n    }\n\n   public:\n    HeavyLightDecomposition() : root(-1),\
    \ _n(0) {}\n    explicit HeavyLightDecomposition(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n = g.size();\n      \
    \  root = _n == 0 ? -1 : root_;\n        parent.assign(_n, -2);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 1);\n        heavy.assign(_n, -1);\n        head.assign(_n,\
    \ -1);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        if (_n == 0) return;\n        assert(0 <=\
    \ root && root < _n);\n\n        std::vector<int> dfs_order;\n        dfs_order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        parent[root] = -1;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            dfs_order.push_back(v);\n            for (const auto& e : g[v]) {\n\
    \                if (!e.alive) continue;\n                if (parent[e.to] !=\
    \ -2) continue;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                stack.push_back(e.to);\n            }\n\
    \        }\n\n        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n\
    \            int v = dfs_order[i];\n            if (parent[v] == -1) continue;\n\
    \            int p = parent[v];\n            subtree_size[p] += subtree_size[v];\n\
    \            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p]\
    \ = v;\n        }\n\n        order.assign(dfs_order.size(), -1);\n        int\
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {std::pair<int,\
    \ int>{root, root}};\n        while (!starts.empty()) {\n            auto [start,\
    \ h] = starts.back();\n            starts.pop_back();\n            for (int v\
    \ = start; v != -1; v = heavy[v]) {\n                head[v] = h;\n          \
    \      tin[v] = timer;\n                order[timer++] = v;\n                for\
    \ (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {\n                    if\
    \ (!it->alive) continue;\n                    int to = it->to;\n             \
    \       if (parent[to] != v || to == heavy[v]) continue;\n                   \
    \ starts.push_back({to, to});\n                }\n            }\n        }\n \
    \       for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n            int\
    \ v = dfs_order[i];\n            tout[v] = tin[v] + subtree_size[v];\n       \
    \ }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    int lca(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        while (head[u]\
    \ != head[v]) {\n            if (depth[head[u]] < depth[head[v]]) std::swap(u,\
    \ v);\n            u = parent[head[u]];\n        }\n        return depth[u] <\
    \ depth[v] ? u : v;\n    }\n\n    int dist_edges(int u, int v) const {\n     \
    \   int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n \
    \   }\n\n    T dist_cost(int u, int v) const {\n        int w = lca(u, v);\n \
    \       return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   while (v != -1) {\n            int h = head[v];\n            int len = depth[v]\
    \ - depth[h];\n            if (k <= len) return order[tin[v] - k];\n         \
    \   k -= len + 1;\n            v = parent[h];\n        }\n        return -1;\n\
    \    }\n\n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::pair<int, int> subtree_range(int v, bool\
    \ edge = false) const {\n        check_vertex(v);\n        return {tin[v] + (edge\
    \ ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment> path_segments(int\
    \ u, int v, bool edge = false) const {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        std::vector<HldPathSegment> result, down;\n        while (head[u] !=\
    \ head[v]) {\n            if (depth[head[u]] >= depth[head[v]]) {\n          \
    \      add_segment(result, tin[head[u]], tin[u] + 1, true);\n                u\
    \ = parent[head[u]];\n            } else {\n                add_segment(down,\
    \ tin[head[v]], tin[v] + 1, false);\n                v = parent[head[v]];\n  \
    \          }\n        }\n\n        if (depth[u] >= depth[v]) {\n            add_segment(result,\
    \ tin[v] + (edge ? 1 : 0), tin[u] + 1, true);\n        } else {\n            add_segment(down,\
    \ tin[u] + (edge ? 1 : 0), tin[v] + 1, false);\n        }\n        std::reverse(down.begin(),\
    \ down.end());\n        result.insert(result.end(), down.begin(), down.end());\n\
    \        return result;\n    }\n\n    template <class F>\n    void for_each_path(int\
    \ u, int v, F f, bool edge = false) const {\n        for (auto seg : path_segments(u,\
    \ v, edge)) f(seg.l, seg.r, seg.reversed);\n    }\n};\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n\n#line 1 \"tree/rerooting_dp.hpp\"\n\n\n\n#line 5 \"\
    tree/rerooting_dp.hpp\"\n\n#line 7 \"tree/rerooting_dp.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\ntemplate <class T, class DP, class Merge, class AddVertex,\
    \ class AddEdge>\nstd::vector<DP> rerooting_dp(const m1une::graph::Graph<T>& g,\
    \ DP id, Merge merge, AddVertex add_vertex,\n                             AddEdge\
    \ add_edge) {\n    int n = g.size();\n    std::vector<int> parent(n, -2), parent_edge(n,\
    \ -1), order;\n    order.reserve(n);\n    for (int root = 0; root < n; root++)\
    \ {\n        if (parent[root] != -2) continue;\n        parent[root] = -1;\n \
    \       std::vector<int> stack = {root};\n        while (!stack.empty()) {\n \
    \           int v = stack.back();\n            stack.pop_back();\n           \
    \ order.push_back(v);\n            for (const auto& e : g[v]) {\n            \
    \    if (!e.alive) continue;\n                if (parent[e.to] != -2) continue;\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                stack.push_back(e.to);\n            }\n        }\n    }\n\n \
    \   std::vector<DP> down(n, id), outside(n, id), answer(n, id);\n    for (int\
    \ i = n - 1; i >= 0; i--) {\n        int v = order[i];\n        DP acc = id;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (parent[e.to] != v) continue;\n            acc = merge(acc, add_edge(down[e.to],\
    \ e));\n        }\n        down[v] = add_vertex(acc, v);\n    }\n\n    for (int\
    \ v : order) {\n        int d = int(g[v].size());\n        std::vector<DP> contrib(d,\
    \ id);\n        for (int i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n\
    \            if (!e.alive) continue;\n            if (parent[e.to] == v) {\n \
    \               contrib[i] = add_edge(down[e.to], e);\n            } else if (parent[v]\
    \ == e.to && parent_edge[v] == e.id) {\n                contrib[i] = add_edge(outside[v],\
    \ e);\n            }\n        }\n\n        std::vector<DP> pref(d + 1, id), suff(d\
    \ + 1, id);\n        for (int i = 0; i < d; i++) pref[i + 1] = merge(pref[i],\
    \ contrib[i]);\n        for (int i = d - 1; i >= 0; i--) suff[i] = merge(contrib[i],\
    \ suff[i + 1]);\n        answer[v] = add_vertex(pref[d], v);\n\n        for (int\
    \ i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n            if (!e.alive)\
    \ continue;\n            if (parent[e.to] != v) continue;\n            outside[e.to]\
    \ = add_vertex(merge(pref[i], suff[i + 1]), v);\n        }\n    }\n\n    return\
    \ answer;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"tree/rerooting_static_top_tree.hpp\"\
    \n\n\n\n#line 6 \"tree/rerooting_static_top_tree.hpp\"\n#include <optional>\n\
    #include <type_traits>\n#line 10 \"tree/rerooting_static_top_tree.hpp\"\n\n#line\
    \ 12 \"tree/rerooting_static_top_tree.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\nnamespace internal {\n\nenum class RerootingStaticTopTreeNodeType {\n \
    \   Compress,\n    Rake,\n    AddEdge,\n    AddVertex,\n};\n\nenum class RerootingStaticTopTreeStepType\
    \ {\n    CompressLower,\n    CompressUpper,\n    AddEdge,\n    RakeLeft,\n   \
    \ RakeRight,\n    AddVertex,\n};\n\n}  // namespace internal\n\ntemplate <class\
    \ T, class Vertex, class Path, class Point, class CompressDown, class CompressUp,\
    \ class Rake,\n          class AddEdgeDown, class AddEdgeUp, class AddVertex>\n\
    struct RerootingStaticTopTree {\n    using cost_type = T;\n    using vertex_type\
    \ = Vertex;\n    using path_type = Path;\n    using point_type = Point;\n    using\
    \ edge_type = m1une::graph::Edge<T>;\n    using node_type = internal::RerootingStaticTopTreeNodeType;\n\
    \    using step_type = internal::RerootingStaticTopTreeStepType;\n\n    struct\
    \ Node {\n        node_type type;\n        int left = -1;\n        int right =\
    \ -1;\n        int parent = -1;\n        int vertex = -1;\n        edge_type edge;\n\
    \        int size = 0;\n        int height = 1;\n        std::optional<Path> path_down;\n\
    \        std::optional<Path> path_up;\n        std::optional<Point> point;\n \
    \   };\n\n    struct RerootingStep {\n        step_type type;\n        int node\
    \ = -1;\n        int sibling = -1;\n        int vertex = -1;\n        edge_type\
    \ edge;\n    };\n\n   private:\n    int _n;\n    int _root;\n    int _root_node;\n\
    \    Point _point_id;\n    CompressDown _compress_down;\n    CompressUp _compress_up;\n\
    \    Rake _rake;\n    AddEdgeDown _add_edge_down;\n    AddEdgeUp _add_edge_up;\n\
    \    AddVertex _add_vertex;\n    std::vector<Vertex> _values;\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _vertex_node;\n    std::vector<int> _edge_node;\n\
    \    std::vector<int> _parent;\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _heavy;\n    std::vector<edge_type> _heavy_edge;\n    std::vector<std::vector<edge_type>>\
    \ _children;\n\n    static edge_type reversed_edge(edge_type e) {\n        std::swap(e.from,\
    \ e.to);\n        return e;\n    }\n\n    const Path& node_path_down(int node)\
    \ const {\n        assert(0 <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path_down.has_value());\n\
    \        return *_nodes[node].path_down;\n    }\n\n    const Path& node_path_up(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].path_up.has_value());\n        return *_nodes[node].path_up;\n\
    \    }\n\n    const Point& node_point(int node) const {\n        assert(0 <= node\
    \ && node < int(_nodes.size()));\n        assert(_nodes[node].point.has_value());\n\
    \        return *_nodes[node].point;\n    }\n\n    void set_parent(int child,\
    \ int parent) {\n        if (child != -1) _nodes[child].parent = parent;\n   \
    \ }\n\n    void recompute(int node) {\n        auto& x = _nodes[node];\n     \
    \   if (x.type == node_type::Compress) {\n            x.path_down = _compress_down(node_path_down(x.left),\
    \ node_path_down(x.right), x.edge);\n            x.path_up = _compress_up(node_path_up(x.right),\
    \ node_path_up(x.left), reversed_edge(x.edge));\n        } else if (x.type ==\
    \ node_type::Rake) {\n            x.point = _rake(node_point(x.left), node_point(x.right));\n\
    \        } else if (x.type == node_type::AddEdge) {\n            x.point = _add_edge_down(node_path_down(x.left),\
    \ x.edge);\n        } else {\n            const Point& side = x.left == -1 ? _point_id\
    \ : node_point(x.left);\n            Path path = _add_vertex(side, _values[x.vertex],\
    \ x.vertex);\n            x.path_down = path;\n            x.path_up = std::move(path);\n\
    \        }\n    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = node_type::Compress;\n    \
    \    node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = node_type::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = node_type::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = node_type::AddVertex;\n        node.left\
    \ = side;\n        node.vertex = vertex;\n        node.size = 1 + (side == -1\
    \ ? 0 : _nodes[side].size);\n        node.height = 1 + (side == -1 ? 0 : _nodes[side].height);\n\
    \        int id = new_node(std::move(node));\n        _vertex_node[vertex] = id;\n\
    \        return id;\n    }\n\n    int weighted_split(const std::vector<int>& nodes,\
    \ int l, int r) const {\n        int total = 0;\n        for (int i = l; i < r;\
    \ i++) total += _nodes[nodes[i]].size;\n        int left_sum = 0;\n        for\
    \ (int i = l; i + 1 < r; i++) {\n            left_sum += _nodes[nodes[i]].size;\n\
    \            if (2 * left_sum >= total) return i + 1;\n        }\n        return\
    \ r - 1;\n    }\n\n    int build_rake(const std::vector<int>& nodes, int l, int\
    \ r) {\n        if (l == r) return -1;\n        if (l + 1 == r) return nodes[l];\n\
    \        int m = weighted_split(nodes, l, r);\n        return new_rake(build_rake(nodes,\
    \ l, m), build_rake(nodes, m, r));\n    }\n\n    int build_compress(const std::vector<int>&\
    \ nodes, const std::vector<edge_type>& edges, int l, int r) {\n        if (l +\
    \ 1 == r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n   \
    \     return new_compress(build_compress(nodes, edges, l, m), build_compress(nodes,\
    \ edges, m, r), edges[m - 1]);\n    }\n\n    int build_vertex(int v) {\n     \
    \   std::vector<int> side_nodes;\n        for (const auto& e : _children[v]) {\n\
    \            if (e.to == _heavy[v]) continue;\n            int child_path = build_path(e.to);\n\
    \            side_nodes.push_back(new_add_edge(child_path, e));\n        }\n \
    \       return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    RerootingStaticTopTree(const m1une::graph::Graph<T>&\
    \ g, const std::vector<Vertex>& values, Point point_id,\n                    \
    \       CompressDown compress_down, CompressUp compress_up, Rake rake,\n     \
    \                      AddEdgeDown add_edge_down, AddEdgeUp add_edge_up, AddVertex\
    \ add_vertex, int root = 0)\n        : _n(g.size()),\n          _root(_n == 0\
    \ ? -1 : root),\n          _root_node(-1),\n          _point_id(std::move(point_id)),\n\
    \          _compress_down(std::move(compress_down)),\n          _compress_up(std::move(compress_up)),\n\
    \          _rake(std::move(rake)),\n          _add_edge_down(std::move(add_edge_down)),\n\
    \          _add_edge_up(std::move(add_edge_up)),\n          _add_vertex(std::move(add_vertex)),\n\
    \          _values(values) {\n        build(g, root);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root = 0) {\n        _n = g.size();\n       \
    \ _root = _n == 0 ? -1 : root;\n        assert(int(_values.size()) == _n);\n \
    \       _nodes.clear();\n        _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(),\
    \ -1);\n        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n\
    \        _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n\
    \        _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int root_node() const {\n        return _root_node;\n \
    \   }\n\n    int node_count() const {\n        return int(_nodes.size());\n  \
    \  }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(int id) const {\n        assert(0 <= id && id <\
    \ int(_nodes.size()));\n        return _nodes[id];\n    }\n\n    int parent_node(int\
    \ id) const {\n        return node(id).parent;\n    }\n\n    int vertex_node(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _vertex_node[v];\n\
    \    }\n\n    int local_point_node(int v) const {\n        int id = vertex_node(v);\n\
    \        assert(_nodes[id].type == node_type::AddVertex);\n        return _nodes[id].left;\n\
    \    }\n\n    const Point& local_point(int v) const {\n        int point_node\
    \ = local_point_node(v);\n        return point_node == -1 ? _point_id : node_point(point_node);\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& path_down(int node_id) const {\n        return node_path_down(node_id);\n\
    \    }\n\n    const Path& path_up(int node_id) const {\n        return node_path_up(node_id);\n\
    \    }\n\n    const Point& point(int node_id) const {\n        return node_point(node_id);\n\
    \    }\n\n    const Path& all_prod_down() const {\n        assert(_root_node !=\
    \ -1);\n        return path_down(_root_node);\n    }\n\n    const Path& all_prod_up()\
    \ const {\n        assert(_root_node != -1);\n        return path_up(_root_node);\n\
    \    }\n\n    const Point& point_id() const {\n        return _point_id;\n   \
    \ }\n\n    template <class F>\n    void for_each_rerooting_step(int v, F&& f)\
    \ const {\n        assert(0 <= v && v < _n);\n        int cur = _vertex_node[v];\n\
    \        assert(cur != -1);\n        while (_nodes[cur].parent != -1) {\n    \
    \        int par = _nodes[cur].parent;\n            const auto& p = _nodes[par];\n\
    \            RerootingStep step;\n            step.node = par;\n            if\
    \ (p.type == node_type::Compress) {\n                step.edge = p.edge;\n   \
    \             if (p.left == cur) {\n                    step.type = step_type::CompressLower;\n\
    \                    step.sibling = p.right;\n                } else {\n     \
    \               assert(p.right == cur);\n                    step.type = step_type::CompressUpper;\n\
    \                    step.sibling = p.left;\n                }\n            }\
    \ else if (p.type == node_type::Rake) {\n                if (p.left == cur) {\n\
    \                    step.type = step_type::RakeRight;\n                    step.sibling\
    \ = p.right;\n                } else {\n                    assert(p.right ==\
    \ cur);\n                    step.type = step_type::RakeLeft;\n              \
    \      step.sibling = p.left;\n                }\n            } else if (p.type\
    \ == node_type::AddEdge) {\n                assert(p.left == cur);\n         \
    \       step.type = step_type::AddEdge;\n                step.edge = p.edge;\n\
    \            } else {\n                assert(p.type == node_type::AddVertex);\n\
    \                assert(p.left == cur);\n                step.type = step_type::AddVertex;\n\
    \                step.vertex = p.vertex;\n            }\n            f(step);\n\
    \            cur = par;\n        }\n    }\n\n    std::vector<RerootingStep> rerooting_steps(int\
    \ v) const {\n        std::vector<RerootingStep> result;\n        int cur = vertex_node(v);\n\
    \        int depth = 0;\n        while (_nodes[cur].parent != -1) {\n        \
    \    cur = _nodes[cur].parent;\n            depth++;\n        }\n        result.reserve(depth);\n\
    \        for_each_rerooting_step(v, [&](const RerootingStep& step) {\n       \
    \     result.push_back(step);\n        });\n        return result;\n    }\n\n\
    \    template <class Folder>\n    auto fold_rerooting(int v, Folder folder) const\
    \ {\n        folder.start(v, _values[v], local_point(v));\n        for_each_rerooting_step(v,\
    \ [&](const RerootingStep& step) {\n            if (step.type == step_type::CompressLower)\
    \ {\n                folder.compress_lower(path_down(step.sibling), step.edge);\n\
    \            } else if (step.type == step_type::CompressUpper) {\n           \
    \     folder.compress_upper(path_up(step.sibling), reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::AddEdge) {\n                folder.add_edge(reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::RakeLeft) {\n                folder.rake_left(point(step.sibling));\n\
    \            } else if (step.type == step_type::RakeRight) {\n               \
    \ folder.rake_right(point(step.sibling));\n            } else {\n            \
    \    folder.add_vertex(step.vertex, _values[step.vertex]);\n            }\n  \
    \      });\n        return folder.result();\n    }\n\n    Path compress_down(const\
    \ Path& upper, const Path& lower, edge_type edge) const {\n        return _compress_down(upper,\
    \ lower, edge);\n    }\n\n    Path compress_up(const Path& lower, const Path&\
    \ upper, edge_type edge) const {\n        return _compress_up(lower, upper, edge);\n\
    \    }\n\n    Point rake(const Point& left, const Point& right) const {\n    \
    \    return _rake(left, right);\n    }\n\n    Point add_edge_down(const Path&\
    \ path, edge_type edge) const {\n        return _add_edge_down(path, edge);\n\
    \    }\n\n    Point add_edge_up(const Path& path, edge_type edge) const {\n  \
    \      return _add_edge_up(path, edge);\n    }\n\n    Path add_vertex(const Point&\
    \ side, const Vertex& value, int vertex) const {\n        return _add_vertex(side,\
    \ value, vertex);\n    }\n\n    static edge_type reverse_edge(edge_type edge)\
    \ {\n        return reversed_edge(edge);\n    }\n};\n\ntemplate <class T, class\
    \ Vertex, class Point, class CompressDown, class CompressUp, class Rake, class\
    \ AddEdgeDown,\n          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const\
    \ m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n\
    \                       Rake, AddEdgeDown, AddEdgeUp, AddVertex, int)\n    ->\
    \ RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex,\
    \ int>, Point, CompressDown,\n                              CompressUp, Rake,\
    \ AddEdgeDown, AddEdgeUp, AddVertex>;\n\ntemplate <class T, class Vertex, class\
    \ Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,\n\
    \          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n             \
    \          Rake, AddEdgeDown, AddEdgeUp, AddVertex)\n    -> RerootingStaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,\n\
    \                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"tree/rooted_tree.hpp\"\
    \n\n\n\n#line 7 \"tree/rooted_tree.hpp\"\n\n#line 9 \"tree/rooted_tree.hpp\"\n\
    \nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct RootedTree\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<std::vector<int>> up;\n\n   private:\n    int _n;\n    int _log;\n\
    \n    void check_vertex(int v) const {\n        assert(0 <= v && v < _n);\n  \
    \      assert(tin[v] != -1);\n    }\n\n   public:\n    RootedTree() : root(-1),\
    \ _n(0), _log(0) {}\n    explicit RootedTree(const m1une::graph::Graph<T>& g,\
    \ int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        _log = 1;\n        while ((1U << _log) <= (unsigned int)(std::max(1,\
    \ _n))) _log++;\n\n        parent.assign(_n, -1);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 0);\n        tin.assign(_n, -1);\n        tout.assign(_n,\
    \ -1);\n        order.clear();\n        order.reserve(_n);\n        up.assign(_log,\
    \ std::vector<int>(_n, -1));\n\n        if (_n == 0) return;\n        assert(0\
    \ <= root && root < _n);\n\n        struct Frame {\n            int v;\n     \
    \       int state;\n        };\n\n        std::vector<char> visited(_n, false);\n\
    \        std::vector<Frame> stack;\n        stack.push_back({root, 0});\n    \
    \    visited[root] = true;\n        int timer = 0;\n\n        while (!stack.empty())\
    \ {\n            Frame frame = stack.back();\n            stack.pop_back();\n\
    \            int v = frame.v;\n            if (frame.state == 0) {\n         \
    \       tin[v] = timer++;\n                order.push_back(v);\n             \
    \   up[0][v] = parent[v];\n                for (int k = 1; k < _log; k++) {\n\
    \                    int p = up[k - 1][v];\n                    up[k][v] = p ==\
    \ -1 ? -1 : up[k - 1][p];\n                }\n\n                stack.push_back({v,\
    \ 1});\n                const auto& adj = g[v];\n                for (int i =\
    \ int(adj.size()) - 1; i >= 0; i--) {\n                    const auto& e = adj[i];\n\
    \                    if (!e.alive) continue;\n                    if (visited[e.to])\
    \ continue;\n                    visited[e.to] = true;\n                    parent[e.to]\
    \ = v;\n                    parent_edge[e.to] = e.id;\n                    depth[e.to]\
    \ = depth[v] + 1;\n                    dist[e.to] = dist[v] + e.cost;\n      \
    \              stack.push_back({e.to, 0});\n                }\n            } else\
    \ {\n                subtree_size[v]++;\n                if (parent[v] != -1)\
    \ subtree_size[parent[v]] += subtree_size[v];\n                tout[v] = timer;\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ log() const {\n        return _log;\n    }\n\n    bool is_ancestor(int u, int\
    \ v) const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   int bit = 0;\n        while (k > 0 && v != -1) {\n            if (k & 1) {\n\
    \                if (_log <= bit) return -1;\n                v = up[bit][v];\n\
    \            }\n            k >>= 1;\n            bit++;\n        }\n        return\
    \ v;\n    }\n\n    int lca(int u, int v) const {\n        check_vertex(u);\n \
    \       check_vertex(v);\n        if (depth[u] < depth[v]) std::swap(u, v);\n\
    \        u = kth_ancestor(u, depth[u] - depth[v]);\n        if (u == v) return\
    \ u;\n        for (int k = _log - 1; k >= 0; k--) {\n            if (up[k][u]\
    \ != up[k][v]) {\n                u = up[k][u];\n                v = up[k][v];\n\
    \            }\n        }\n        return parent[u];\n    }\n\n    int dist_edges(int\
    \ u, int v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v]\
    \ - 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int\
    \ w = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::vector<int> path(int u, int v) const {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        int w = lca(u, v);\n\
    \        std::vector<int> a, b;\n        for (int x = u; x != w; x = parent[x])\
    \ a.push_back(x);\n        a.push_back(w);\n        for (int x = v; x != w; x\
    \ = parent[x]) b.push_back(x);\n        std::reverse(b.begin(), b.end());\n  \
    \      a.insert(a.end(), b.begin(), b.end());\n        return a;\n    }\n\n  \
    \  std::vector<int> path_edges(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        int w = lca(u, v);\n        std::vector<int>\
    \ a, b;\n        for (int x = u; x != w; x = parent[x]) a.push_back(parent_edge[x]);\n\
    \        for (int x = v; x != w; x = parent[x]) b.push_back(parent_edge[x]);\n\
    \        std::reverse(b.begin(), b.end());\n        a.insert(a.end(), b.begin(),\
    \ b.end());\n        return a;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ v) const {\n        check_vertex(v);\n        return {tin[v], tout[v]};\n  \
    \  }\n\n    std::vector<int> subtree_vertices(int v) const {\n        check_vertex(v);\n\
    \        return std::vector<int>(order.begin() + tin[v], order.begin() + tout[v]);\n\
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"tree/sparse_table_lca.hpp\"\
    \n\n\n\n#line 6 \"tree/sparse_table_lca.hpp\"\n#include <limits>\n#line 9 \"tree/sparse_table_lca.hpp\"\
    \n\n#line 1 \"data_structure/sparse_table.hpp\"\n\n\n\n#include <bit>\n#line 6\
    \ \"data_structure/sparse_table.hpp\"\n#include <concepts>\n#line 9 \"data_structure/sparse_table.hpp\"\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 11 \"data_structure/sparse_table.hpp\"\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\n// A Sparse Table utilizing C++20 Concepts for type safety.\n// It requires\
    \ a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n// [IMPORTANT] For\
    \ O(1) range queries to work correctly, the monoid operation MUST be idempotent.\n\
    // i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max, GCD, Bitwise AND/OR).\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable {\n    using T =\
    \ typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::vector<std::vector<T>>\
    \ _st;\n\n   public:\n    // Constructs an empty sparse table.\n    SparseTable()\
    \ : _n(0) {}\n\n    // Constructs a sparse table from an existing vector in O(N\
    \ log N) time.\n    explicit SparseTable(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        // Compute the maximum power of 2\
    \ needed\n        int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Initialize the base level\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = v[i];\n        }\n\n        //\
    \ Build the sparse table\n        for (int k = 1; k < max_log; k++) {\n      \
    \      for (int i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] =\
    \ Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n\
    \        }\n    }\n    explicit SparseTable(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0; i +\
    \ (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Constructs a sparse table from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit SparseTable(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Compile-time branching based on the available\
    \ make() signature\n        for (int i = 0; i < _n; i++) {\n            if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0;\
    \ i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Returns the product (result of the monoid operation) in the range [l, r) in\
    \ O(1) time.\n    // Requires the monoid operation to be idempotent.\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        if\
    \ (l == r) return Monoid::id();\n\n        // Calculate the largest power of 2\
    \ less than or equal to the interval length\n        int k = std::bit_width((unsigned\
    \ int)(r - l)) - 1;\n        return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n#line\
    \ 12 \"tree/sparse_table_lca.hpp\"\n\nnamespace m1une {\nnamespace tree {\n\n\
    template <class T = int>\nstruct SparseTableLca {\n    using cost_type = T;\n\
    \    using edge_type = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    std::vector<int> depth;\n  \
    \  std::vector<T> dist;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n    std::vector<int>\
    \ first;\n    std::vector<int> euler;\n\n   private:\n    struct RmqNode {\n \
    \       int depth;\n        int vertex;\n    };\n\n    struct RmqMonoid {\n  \
    \      using value_type = RmqNode;\n\n        static value_type id() {\n     \
    \       return {std::numeric_limits<int>::max(), -1};\n        }\n\n        static\
    \ value_type op(const value_type& a, const value_type& b) {\n            if (a.depth\
    \ != b.depth) return a.depth < b.depth ? a : b;\n            return a.vertex <\
    \ b.vertex ? a : b;\n        }\n    };\n\n    int _n;\n    m1une::data_structure::SparseTable<RmqMonoid>\
    \ _st;\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        assert(first[v] != -1);\n    }\n\n   public:\n    SparseTableLca() :\
    \ root(-1), _n(0) {}\n    explicit SparseTableLca(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n = g.size();\n      \
    \  root = _n == 0 ? -1 : root_;\n        parent.assign(_n, -2);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 0);\n        tin.assign(_n, -1);\n        tout.assign(_n,\
    \ -1);\n        order.clear();\n        order.reserve(_n);\n        first.assign(_n,\
    \ -1);\n        euler.clear();\n        euler.reserve(std::max(0, 2 * _n - 1));\n\
    \        _st = m1une::data_structure::SparseTable<RmqMonoid>();\n\n        if\
    \ (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n        std::vector<int>\
    \ it(_n, 0);\n        std::vector<char> visited(_n, false);\n        std::vector<int>\
    \ stack = {root};\n        visited[root] = true;\n        parent[root] = -1;\n\
    \n        int timer = 0;\n        tin[root] = timer++;\n        order.push_back(root);\n\
    \        first[root] = 0;\n        euler.push_back(root);\n\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            if (it[v] < int(g[v].size()))\
    \ {\n                const auto& e = g[v][it[v]++];\n                if (!e.alive)\
    \ continue;\n                if (visited[e.to]) continue;\n                visited[e.to]\
    \ = true;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                tin[e.to] = timer++;\n                order.push_back(e.to);\n\
    \                first[e.to] = int(euler.size());\n                euler.push_back(e.to);\n\
    \                stack.push_back(e.to);\n            } else {\n              \
    \  subtree_size[v]++;\n                if (parent[v] != -1) subtree_size[parent[v]]\
    \ += subtree_size[v];\n                tout[v] = timer;\n                stack.pop_back();\n\
    \                if (!stack.empty()) euler.push_back(stack.back());\n        \
    \    }\n        }\n\n        std::vector<RmqNode> rmq;\n        rmq.reserve(euler.size());\n\
    \        for (int v : euler) rmq.push_back({depth[v], v});\n        _st = m1une::data_structure::SparseTable<RmqMonoid>(std::move(rmq));\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int lca(int\
    \ u, int v) const {\n        check_vertex(u);\n        check_vertex(v);\n    \
    \    int l = first[u], r = first[v];\n        if (l > r) std::swap(l, r);\n  \
    \      return _st.prod(l, r + 1).vertex;\n    }\n\n    int dist_edges(int u, int\
    \ v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v] -\
    \ 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int w\
    \ = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    std::pair<int, int> subtree_range(int v) const {\n        check_vertex(v);\n\
    \        return {tin[v], tout[v]};\n    }\n};\n\n}  // namespace tree\n}  // namespace\
    \ m1une\n\n\n#line 1 \"tree/static_top_tree.hpp\"\n\n\n\n#line 10 \"tree/static_top_tree.hpp\"\
    \n\n#line 12 \"tree/static_top_tree.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\nnamespace internal {\n\nenum class StaticTopTreeNodeType {\n    Compress,\n\
    \    Rake,\n    AddEdge,\n    AddVertex,\n};\n\n}  // namespace internal\n\ntemplate\
    \ <class T, class Vertex, class Path, class Point, class Compress, class Rake,\
    \ class AddEdge,\n          class AddVertex>\nstruct StaticTopTree {\n    using\
    \ cost_type = T;\n    using vertex_type = Vertex;\n    using path_type = Path;\n\
    \    using point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n\
    \n   private:\n    struct Node {\n        internal::StaticTopTreeNodeType type;\n\
    \        int left = -1;\n        int right = -1;\n        int parent = -1;\n \
    \       int vertex = -1;\n        edge_type edge;\n        int size = 0;\n   \
    \     int height = 1;\n        std::optional<Path> path;\n        std::optional<Point>\
    \ point;\n    };\n\n    int _n;\n    int _root;\n    int _root_node;\n    Point\
    \ _point_id;\n    Compress _compress;\n    Rake _rake;\n    AddEdge _add_edge;\n\
    \    AddVertex _add_vertex;\n    std::vector<Vertex> _values;\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _vertex_node;\n    std::vector<int> _edge_node;\n\
    \    std::vector<int> _parent;\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _heavy;\n    std::vector<edge_type> _heavy_edge;\n    std::vector<std::vector<edge_type>>\
    \ _children;\n\n    const Path& path_value(int node) const {\n        assert(0\
    \ <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path.has_value());\n\
    \        return *_nodes[node].path;\n    }\n\n    const Point& point_value(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].point.has_value());\n        return *_nodes[node].point;\n\
    \    }\n\n    void set_parent(int child, int parent) {\n        if (child != -1)\
    \ _nodes[child].parent = parent;\n    }\n\n    void recompute(int node) {\n  \
    \      auto& x = _nodes[node];\n        if (x.type == internal::StaticTopTreeNodeType::Compress)\
    \ {\n            x.path = _compress(path_value(x.left), path_value(x.right), x.edge);\n\
    \        } else if (x.type == internal::StaticTopTreeNodeType::Rake) {\n     \
    \       x.point = _rake(point_value(x.left), point_value(x.right));\n        }\
    \ else if (x.type == internal::StaticTopTreeNodeType::AddEdge) {\n           \
    \ x.point = _add_edge(path_value(x.left), x.edge);\n        } else {\n       \
    \     const Point& side = x.left == -1 ? _point_id : point_value(x.left);\n  \
    \          x.path = _add_vertex(side, _values[x.vertex], x.vertex);\n        }\n\
    \    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Compress;\n\
    \        node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddVertex;\n\
    \        node.left = side;\n        node.vertex = vertex;\n        node.size =\
    \ 1 + (side == -1 ? 0 : _nodes[side].size);\n        node.height = 1 + (side ==\
    \ -1 ? 0 : _nodes[side].height);\n        int id = new_node(std::move(node));\n\
    \        _vertex_node[vertex] = id;\n        return id;\n    }\n\n    int weighted_split(const\
    \ std::vector<int>& nodes, int l, int r) const {\n        int total = 0;\n   \
    \     for (int i = l; i < r; i++) total += _nodes[nodes[i]].size;\n        int\
    \ left_sum = 0;\n        for (int i = l; i + 1 < r; i++) {\n            left_sum\
    \ += _nodes[nodes[i]].size;\n            if (2 * left_sum >= total) return i +\
    \ 1;\n        }\n        return r - 1;\n    }\n\n    int build_rake(const std::vector<int>&\
    \ nodes, int l, int r) {\n        if (l == r) return -1;\n        if (l + 1 ==\
    \ r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n        return\
    \ new_rake(build_rake(nodes, l, m), build_rake(nodes, m, r));\n    }\n\n    int\
    \ build_compress(const std::vector<int>& nodes, const std::vector<edge_type>&\
    \ edges, int l, int r) {\n        if (l + 1 == r) return nodes[l];\n        int\
    \ m = weighted_split(nodes, l, r);\n        return new_compress(build_compress(nodes,\
    \ edges, l, m), build_compress(nodes, edges, m, r), edges[m - 1]);\n    }\n\n\
    \    int build_vertex(int v) {\n        std::vector<int> side_nodes;\n       \
    \ for (const auto& e : _children[v]) {\n            if (e.to == _heavy[v]) continue;\n\
    \            int child_path = build_path(e.to);\n            side_nodes.push_back(new_add_edge(child_path,\
    \ e));\n        }\n        return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    StaticTopTree(const m1une::graph::Graph<T>& g, const\
    \ std::vector<Vertex>& values, Point point_id,\n                  Compress compress,\
    \ Rake rake, AddEdge add_edge, AddVertex add_vertex, int root = 0)\n        :\
    \ _n(g.size()),\n          _root(_n == 0 ? -1 : root),\n          _root_node(-1),\n\
    \          _point_id(std::move(point_id)),\n          _compress(std::move(compress)),\n\
    \          _rake(std::move(rake)),\n          _add_edge(std::move(add_edge)),\n\
    \          _add_vertex(std::move(add_vertex)),\n          _values(values) {\n\
    \        build(g, root);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root = 0) {\n        _n = g.size();\n        _root = _n == 0 ? -1 : root;\n\
    \        assert(int(_values.size()) == _n);\n        _nodes.clear();\n       \
    \ _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(), -1);\n\
    \        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n     \
    \   _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n   \
    \     _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n ==\
    \ 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& all_prod() const {\n        assert(_root_node != -1);\n        return\
    \ path_value(_root_node);\n    }\n\n    const Path& query() const {\n        return\
    \ all_prod();\n    }\n};\n\ntemplate <class T, class Vertex, class Point, class\
    \ Compress, class Rake, class AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, Compress, Rake, AddEdge,\n              AddVertex,\
    \ int)\n    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point,\
    \ Vertex, int>, Point, Compress, Rake,\n                     AddEdge, AddVertex>;\n\
    \ntemplate <class T, class Vertex, class Point, class Compress, class Rake, class\
    \ AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&, const\
    \ std::vector<Vertex>&, Point, Compress, Rake, AddEdge, AddVertex)\n    -> StaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress,\
    \ Rake,\n                     AddEdge, AddVertex>;\n\n}  // namespace tree\n}\
    \  // namespace m1une\n\n\n#line 1 \"tree/tree.hpp\"\n\n\n\n#line 7 \"tree/tree.hpp\"\
    \n\n\n#line 13 \"tree/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_TREE_ALL_HPP

    #define M1UNE_TREE_ALL_HPP 1


    #include "tree/centroid_decomposition.hpp"

    #include "tree/diameter.hpp"

    #include "tree/heavy_light_decomposition.hpp"

    #include "tree/rerooting_dp.hpp"

    #include "tree/rerooting_static_top_tree.hpp"

    #include "tree/rooted_tree.hpp"

    #include "tree/sparse_table_lca.hpp"

    #include "tree/static_top_tree.hpp"

    #include "tree/tree.hpp"


    #endif  // M1UNE_TREE_ALL_HPP

    '
  dependsOn:
  - tree/centroid_decomposition.hpp
  - graph/graph.hpp
  - tree/diameter.hpp
  - tree/heavy_light_decomposition.hpp
  - tree/rerooting_dp.hpp
  - tree/rerooting_static_top_tree.hpp
  - tree/rooted_tree.hpp
  - tree/sparse_table_lca.hpp
  - data_structure/sparse_table.hpp
  - monoid/concept.hpp
  - tree/static_top_tree.hpp
  - tree/tree.hpp
  isVerificationFile: false
  path: tree/all.hpp
  requiredBy: []
  timestamp: '2026-06-17 14:06:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/all.hpp
layout: document
title: Tree All
---

## Overview

`tree/all.hpp` includes every tree header in this directory. The algorithms use
`m1une::graph::Graph<T>` as their input container, so they compose with the
existing graph library.

## Included Headers

| Header | Contents |
| --- | --- |
| `tree/tree.hpp` | Core rooted tree and diameter bundle. |
| `tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `tree/heavy_light_decomposition.hpp` | HLD order, path segments, subtree ranges, LCA, and jumps. |
| `tree/diameter.hpp` | Weighted tree/forest diameter path. |
| `tree/rerooting_dp.hpp` | Generic rerooting DP helper. |
| `tree/static_top_tree.hpp` | Dynamic one-root tree DP on a fixed tree using static top-tree clusters. |
| `tree/rerooting_static_top_tree.hpp` | Bidirectional static top-tree clusters for dynamic rerooting-DP solutions. |
| `tree/centroid_decomposition.hpp` | Centroid decomposition for trees and forests. |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    auto diameter = m1une::tree::tree_diameter(g);
    std::cout << diameter.edge_count << "\n";
}
```
