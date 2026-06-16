---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
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
    path: tree/rooted_tree.hpp
    title: Rooted Tree
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
    \ cost, id));\n        _edge_positions.push_back({{from, idx}});\n        return\
    \ id;\n    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.push_back({{u, u_idx}, {v, v_idx}});\n\
    \        return id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n\
    \        assert(0 <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
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
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {{root, root}};\n\
    \        while (!starts.empty()) {\n            auto [start, h] = starts.back();\n\
    \            starts.pop_back();\n            for (int v = start; v != -1; v =\
    \ heavy[v]) {\n                head[v] = h;\n                tin[v] = timer;\n\
    \                order[timer++] = v;\n                for (auto it = g[v].rbegin();\
    \ it != g[v].rend(); ++it) {\n                    if (!it->alive) continue;\n\
    \                    int to = it->to;\n                    if (parent[to] != v\
    \ || to == heavy[v]) continue;\n                    starts.push_back({to, to});\n\
    \                }\n            }\n        }\n        for (int i = int(dfs_order.size())\
    \ - 1; i >= 0; i--) {\n            int v = dfs_order[i];\n            tout[v]\
    \ = tin[v] + subtree_size[v];\n        }\n    }\n\n    int size() const {\n  \
    \      return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    bool is_ancestor(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        return tin[u] <= tin[v] && tout[v] <= tout[u];\n\
    \    }\n\n    int lca(int u, int v) const {\n        check_vertex(u);\n      \
    \  check_vertex(v);\n        while (head[u] != head[v]) {\n            if (depth[head[u]]\
    \ < depth[head[v]]) std::swap(u, v);\n            u = parent[head[u]];\n     \
    \   }\n        return depth[u] < depth[v] ? u : v;\n    }\n\n    int dist_edges(int\
    \ u, int v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v]\
    \ - 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int\
    \ w = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    int kth_ancestor(int v, int k) const {\n        check_vertex(v);\n     \
    \   assert(0 <= k);\n        while (v != -1) {\n            int h = head[v];\n\
    \            int len = depth[v] - depth[h];\n            if (k <= len) return\
    \ order[tin[v] - k];\n            k -= len + 1;\n            v = parent[h];\n\
    \        }\n        return -1;\n    }\n\n    int jump(int from, int to, int k)\
    \ const {\n        check_vertex(from);\n        check_vertex(to);\n        assert(0\
    \ <= k);\n        int w = lca(from, to);\n        int up_len = depth[from] - depth[w];\n\
    \        int down_len = depth[to] - depth[w];\n        if (up_len + down_len <\
    \ k) return -1;\n        if (k <= up_len) return kth_ancestor(from, k);\n    \
    \    return kth_ancestor(to, down_len - (k - up_len));\n    }\n\n    std::pair<int,\
    \ int> subtree_range(int v, bool edge = false) const {\n        check_vertex(v);\n\
    \        return {tin[v] + (edge ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment>\
    \ path_segments(int u, int v, bool edge = false) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        std::vector<HldPathSegment> result, down;\n\
    \        while (head[u] != head[v]) {\n            if (depth[head[u]] >= depth[head[v]])\
    \ {\n                add_segment(result, tin[head[u]], tin[u] + 1, true);\n  \
    \              u = parent[head[u]];\n            } else {\n                add_segment(down,\
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
    \ answer;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"tree/rooted_tree.hpp\"\
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
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"tree/tree.hpp\"\
    \n\n\n\n#line 6 \"tree/tree.hpp\"\n\n\n#line 10 \"tree/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_TREE_ALL_HPP

    #define M1UNE_TREE_ALL_HPP 1


    #include "tree/centroid_decomposition.hpp"

    #include "tree/diameter.hpp"

    #include "tree/heavy_light_decomposition.hpp"

    #include "tree/rerooting_dp.hpp"

    #include "tree/rooted_tree.hpp"

    #include "tree/tree.hpp"


    #endif  // M1UNE_TREE_ALL_HPP

    '
  dependsOn:
  - tree/centroid_decomposition.hpp
  - graph/graph.hpp
  - tree/diameter.hpp
  - tree/heavy_light_decomposition.hpp
  - tree/rerooting_dp.hpp
  - tree/rooted_tree.hpp
  - tree/tree.hpp
  isVerificationFile: false
  path: tree/all.hpp
  requiredBy: []
  timestamp: '2026-06-17 02:13:15+09:00'
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
| `tree/heavy_light_decomposition.hpp` | HLD order, path segments, subtree ranges, LCA, and jumps. |
| `tree/diameter.hpp` | Weighted tree/forest diameter path. |
| `tree/rerooting_dp.hpp` | Generic rerooting DP helper. |
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
