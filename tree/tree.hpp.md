---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: tree/diameter.hpp
    title: Tree Diameter
  - icon: ':heavy_check_mark:'
    path: tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/tree.hpp\"\n\n\n\n#line 1 \"tree/diameter.hpp\"\n\n\
    \n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\
    \n\n#include <cassert>\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ m1une\n\n\n#line 8 \"tree/diameter.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\ntemplate <class T = int>\nstruct TreeDiameter {\n    T cost;\n    int edge_count;\n\
    \    int from;\n    int to;\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n  \
    \  }\n};\n\nnamespace internal {\n\ntemplate <class T>\nstruct FarthestResult\
    \ {\n    int vertex;\n    std::vector<char> seen;\n    std::vector<T> dist;\n\
    \    std::vector<int> parent;\n    std::vector<int> parent_edge;\n};\n\ntemplate\
    \ <class T>\nFarthestResult<T> farthest_from(const m1une::graph::Graph<T>& g,\
    \ int start) {\n    int n = g.size();\n    FarthestResult<T> result;\n    result.vertex\
    \ = start;\n    result.seen.assign(n, false);\n    result.dist.assign(n, T(0));\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\n \
    \   std::vector<int> stack = {start};\n    result.seen[start] = true;\n    while\
    \ (!stack.empty()) {\n        int v = stack.back();\n        stack.pop_back();\n\
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
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"tree/rooted_tree.hpp\"\n\n\n\n#line\
    \ 7 \"tree/rooted_tree.hpp\"\n\n#line 9 \"tree/rooted_tree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct RootedTree {\n\
    \    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n  \
    \  int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
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
    \n\n#line 1 \"ds/range_query/sparse_table.hpp\"\n\n\n\n#include <bit>\n#line 6\
    \ \"ds/range_query/sparse_table.hpp\"\n#include <concepts>\n#line 9 \"ds/range_query/sparse_table.hpp\"\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/range_query/sparse_table.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A Sparse Table utilizing C++20 Concepts\
    \ for type safety.\n// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n\
    // [IMPORTANT] For O(1) range queries to work correctly, the monoid operation\
    \ MUST be idempotent.\n// i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max,\
    \ GCD, Bitwise AND/OR).\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n\
    \    std::vector<std::vector<T>> _st;\n\n   public:\n    // Constructs an empty\
    \ sparse table.\n    SparseTable() : _n(0) {}\n\n    // Constructs a sparse table\
    \ from an existing vector in O(N log N) time.\n    explicit SparseTable(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       // Compute the maximum power of 2 needed\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Initialize\
    \ the base level\n        for (int i = 0; i < _n; i++) {\n            _st[0][i]\
    \ = v[i];\n        }\n\n        // Build the sparse table\n        for (int k\
    \ = 1; k < max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++)\
    \ {\n                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 <<\
    \ (k - 1))]);\n            }\n        }\n    }\n    explicit SparseTable(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n        int max_log\
    \ = std::bit_width((unsigned int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\
    \n        for (int i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n\
    \        }\n\n        for (int k = 1; k < max_log; k++) {\n            for (int\
    \ i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k\
    \ - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\
    \n    // Constructs a sparse table from a vector of a different type U.\n    //\
    \ It automatically adapts to the Monoid's initialization requirements:\n    //\
    \ 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index) if the\
    \ monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit SparseTable(const std::vector<U>& v) : _n(int(v.size())) {\n\
    \        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Compile-time\
    \ branching based on the available make() signature\n        for (int i = 0; i\
    \ < _n; i++) {\n            if constexpr (requires(U x) { Monoid::make(x); })\
    \ {\n                _st[0][i] = Monoid::make(v[i]);\n            } else if constexpr\
    \ (requires(U x, int idx) { Monoid::make(x, idx); }) {\n                _st[0][i]\
    \ = Monoid::make(v[i], i);\n            } else {\n                _st[0][i] =\
    \ static_cast<T>(v[i]);\n            }\n        }\n        for (int k = 1; k <\
    \ max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++) {\n  \
    \              _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k -\
    \ 1))]);\n            }\n        }\n    }\n\n    // Returns the product (result\
    \ of the monoid operation) in the range [l, r) in O(1) time.\n    // Requires\
    \ the monoid operation to be idempotent.\n    T prod(int l, int r) const {\n \
    \       assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return Monoid::id();\n\
    \n        // Calculate the largest power of 2 less than or equal to the interval\
    \ length\n        int k = std::bit_width((unsigned int)(r - l)) - 1;\n       \
    \ return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 12 \"tree/sparse_table_lca.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct SparseTableLca\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<int> first;\n    std::vector<int> euler;\n\n   private:\n   \
    \ struct RmqNode {\n        int depth;\n        int vertex;\n    };\n\n    struct\
    \ RmqMonoid {\n        using value_type = RmqNode;\n\n        static value_type\
    \ id() {\n            return {std::numeric_limits<int>::max(), -1};\n        }\n\
    \n        static value_type op(const value_type& a, const value_type& b) {\n \
    \           if (a.depth != b.depth) return a.depth < b.depth ? a : b;\n      \
    \      return a.vertex < b.vertex ? a : b;\n        }\n    };\n\n    int _n;\n\
    \    m1une::ds::SparseTable<RmqMonoid> _st;\n\n    void check_vertex(int v) const\
    \ {\n        assert(0 <= v && v < _n);\n        assert(first[v] != -1);\n    }\n\
    \n   public:\n    SparseTableLca() : root(-1), _n(0) {}\n    explicit SparseTableLca(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g, root_);\n    }\n\
    \n    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n\
    \ = g.size();\n        root = _n == 0 ? -1 : root_;\n        parent.assign(_n,\
    \ -2);\n        parent_edge.assign(_n, -1);\n        depth.assign(_n, 0);\n  \
    \      dist.assign(_n, T(0));\n        subtree_size.assign(_n, 0);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        first.assign(_n, -1);\n        euler.clear();\n        euler.reserve(std::max(0,\
    \ 2 * _n - 1));\n        _st = m1une::ds::SparseTable<RmqMonoid>();\n\n      \
    \  if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n        std::vector<int>\
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
    \        for (int v : euler) rmq.push_back({depth[v], v});\n        _st = m1une::ds::SparseTable<RmqMonoid>(std::move(rmq));\n\
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
    \ m1une\n\n\n#line 7 \"tree/tree.hpp\"\n\n\n"
  code: '#ifndef M1UNE_TREE_TREE_HPP

    #define M1UNE_TREE_TREE_HPP 1


    #include "diameter.hpp"

    #include "rooted_tree.hpp"

    #include "sparse_table_lca.hpp"


    #endif  // M1UNE_TREE_TREE_HPP

    '
  dependsOn:
  - tree/diameter.hpp
  - graph/graph.hpp
  - tree/rooted_tree.hpp
  - tree/sparse_table_lca.hpp
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: tree/tree.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/tree.hpp
layout: document
title: Tree
---

## Overview

`tree/tree.hpp` is a small tree bundle containing the core rooted-tree helpers,
the sparse-table LCA helper, and the diameter routine.

For the full tree toolbox, include `tree/all.hpp`.

## Included Headers

| Header | Contents |
| --- | --- |
| `tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `tree/diameter.hpp` | Weighted tree/forest diameter path. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included helper pages for public interfaces and complexities.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/tree.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    m1une::tree::RootedTree tree(g, 0);
    std::cout << tree.lca(0, 2) << "\n";
}
```
