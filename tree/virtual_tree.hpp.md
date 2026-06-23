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
  bundledCode: "#line 1 \"tree/virtual_tree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
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
    \ m1une\n\n\n#line 1 \"tree/sparse_table_lca.hpp\"\n\n\n\n#line 6 \"tree/sparse_table_lca.hpp\"\
    \n#include <limits>\n#line 9 \"tree/sparse_table_lca.hpp\"\n\n#line 1 \"ds/range_query/sparse_table.hpp\"\
    \n\n\n\n#include <bit>\n#line 6 \"ds/range_query/sparse_table.hpp\"\n#include\
    \ <concepts>\n#line 9 \"ds/range_query/sparse_table.hpp\"\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ group monoids.\n// A type satisfying this concept must also obey commutativity\
    \ and inverse laws.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 11 \"ds/range_query/sparse_table.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A Sparse Table utilizing C++20 Concepts for type safety.\n// It requires\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"tree/sparse_table_lca.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct SparseTableLca\
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
    \ m1une\n\n\n#line 11 \"tree/virtual_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T = int>\nstruct VirtualTreeResult {\n    std::vector<int>\
    \ vertex;\n    std::vector<int> parent;\n    std::vector<int> parent_edge_count;\n\
    \    std::vector<T> parent_cost;\n    std::vector<std::vector<int>> children;\n\
    \    std::vector<bool> is_key;\n\n    int size() const {\n        return int(vertex.size());\n\
    \    }\n\n    bool empty() const {\n        return vertex.empty();\n    }\n\n\
    \    int edge_count() const {\n        return vertex.empty() ? 0 : int(vertex.size())\
    \ - 1;\n    }\n\n    int root() const {\n        return vertex.empty() ? -1 :\
    \ 0;\n    }\n\n    int root_vertex() const {\n        return vertex.empty() ?\
    \ -1 : vertex[0];\n    }\n};\n\ntemplate <class T = int>\nstruct VirtualTree {\n\
    \    using cost_type = T;\n    using result_type = VirtualTreeResult<T>;\n\n \
    \  private:\n    SparseTableLca<T> _lca;\n    std::vector<int> _key;\n    std::vector<int>\
    \ _vertices;\n    std::vector<int> _stack;\n\n   public:\n    VirtualTree() =\
    \ default;\n\n    explicit VirtualTree(const m1une::graph::Graph<T>& graph, int\
    \ root = 0) : _lca(graph, root) {}\n\n    void build_lca(const m1une::graph::Graph<T>&\
    \ graph, int root = 0) {\n        _lca.build(graph, root);\n    }\n\n    int original_size()\
    \ const {\n        return _lca.size();\n    }\n\n    const SparseTableLca<T>&\
    \ lca_data() const {\n        return _lca;\n    }\n\n    result_type build(std::vector<int>\
    \ key_vertices) {\n        result_type result;\n        if (key_vertices.empty())\
    \ return result;\n\n        auto by_tin = [&](int u, int v) { return _lca.tin[u]\
    \ < _lca.tin[v]; };\n        for (int v : key_vertices) {\n            assert(0\
    \ <= v && v < _lca.size());\n            assert(_lca.tin[v] != -1);\n        }\n\
    \        std::sort(key_vertices.begin(), key_vertices.end(), by_tin);\n      \
    \  key_vertices.erase(std::unique(key_vertices.begin(), key_vertices.end()), key_vertices.end());\n\
    \n        _key = key_vertices;\n        _vertices = key_vertices;\n        _vertices.reserve(2\
    \ * _key.size());\n        for (int i = 1; i < int(_key.size()); i++) {\n    \
    \        _vertices.push_back(_lca.lca(_key[i - 1], _key[i]));\n        }\n   \
    \     std::sort(_vertices.begin(), _vertices.end(), by_tin);\n        _vertices.erase(std::unique(_vertices.begin(),\
    \ _vertices.end()), _vertices.end());\n\n        int n = int(_vertices.size());\n\
    \        result.vertex = _vertices;\n        result.parent.assign(n, -1);\n  \
    \      result.parent_edge_count.assign(n, 0);\n        result.parent_cost.assign(n,\
    \ T(0));\n        result.children.assign(n, {});\n        result.is_key.assign(n,\
    \ false);\n\n        int key_index = 0;\n        for (int i = 0; i < n; i++) {\n\
    \            while (key_index < int(_key.size()) && _lca.tin[_key[key_index]]\
    \ < _lca.tin[_vertices[i]]) {\n                key_index++;\n            }\n \
    \           if (key_index < int(_key.size()) && _key[key_index] == _vertices[i])\
    \ result.is_key[i] = true;\n        }\n\n        _stack.clear();\n        _stack.reserve(n);\n\
    \        for (int i = 0; i < n; i++) {\n            while (!_stack.empty() &&\
    \ !_lca.is_ancestor(_vertices[_stack.back()], _vertices[i])) {\n             \
    \   _stack.pop_back();\n            }\n            if (!_stack.empty()) {\n  \
    \              int p = _stack.back();\n                result.parent[i] = p;\n\
    \                result.parent_edge_count[i] = _lca.depth[_vertices[i]] - _lca.depth[_vertices[p]];\n\
    \                result.parent_cost[i] = _lca.dist[_vertices[i]] - _lca.dist[_vertices[p]];\n\
    \                result.children[p].push_back(i);\n            }\n           \
    \ _stack.push_back(i);\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_VIRTUAL_TREE_HPP\n#define M1UNE_TREE_VIRTUAL_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../graph/graph.hpp\"\n#include \"sparse_table_lca.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct VirtualTreeResult\
    \ {\n    std::vector<int> vertex;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge_count;\n    std::vector<T> parent_cost;\n    std::vector<std::vector<int>>\
    \ children;\n    std::vector<bool> is_key;\n\n    int size() const {\n       \
    \ return int(vertex.size());\n    }\n\n    bool empty() const {\n        return\
    \ vertex.empty();\n    }\n\n    int edge_count() const {\n        return vertex.empty()\
    \ ? 0 : int(vertex.size()) - 1;\n    }\n\n    int root() const {\n        return\
    \ vertex.empty() ? -1 : 0;\n    }\n\n    int root_vertex() const {\n        return\
    \ vertex.empty() ? -1 : vertex[0];\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ VirtualTree {\n    using cost_type = T;\n    using result_type = VirtualTreeResult<T>;\n\
    \n   private:\n    SparseTableLca<T> _lca;\n    std::vector<int> _key;\n    std::vector<int>\
    \ _vertices;\n    std::vector<int> _stack;\n\n   public:\n    VirtualTree() =\
    \ default;\n\n    explicit VirtualTree(const m1une::graph::Graph<T>& graph, int\
    \ root = 0) : _lca(graph, root) {}\n\n    void build_lca(const m1une::graph::Graph<T>&\
    \ graph, int root = 0) {\n        _lca.build(graph, root);\n    }\n\n    int original_size()\
    \ const {\n        return _lca.size();\n    }\n\n    const SparseTableLca<T>&\
    \ lca_data() const {\n        return _lca;\n    }\n\n    result_type build(std::vector<int>\
    \ key_vertices) {\n        result_type result;\n        if (key_vertices.empty())\
    \ return result;\n\n        auto by_tin = [&](int u, int v) { return _lca.tin[u]\
    \ < _lca.tin[v]; };\n        for (int v : key_vertices) {\n            assert(0\
    \ <= v && v < _lca.size());\n            assert(_lca.tin[v] != -1);\n        }\n\
    \        std::sort(key_vertices.begin(), key_vertices.end(), by_tin);\n      \
    \  key_vertices.erase(std::unique(key_vertices.begin(), key_vertices.end()), key_vertices.end());\n\
    \n        _key = key_vertices;\n        _vertices = key_vertices;\n        _vertices.reserve(2\
    \ * _key.size());\n        for (int i = 1; i < int(_key.size()); i++) {\n    \
    \        _vertices.push_back(_lca.lca(_key[i - 1], _key[i]));\n        }\n   \
    \     std::sort(_vertices.begin(), _vertices.end(), by_tin);\n        _vertices.erase(std::unique(_vertices.begin(),\
    \ _vertices.end()), _vertices.end());\n\n        int n = int(_vertices.size());\n\
    \        result.vertex = _vertices;\n        result.parent.assign(n, -1);\n  \
    \      result.parent_edge_count.assign(n, 0);\n        result.parent_cost.assign(n,\
    \ T(0));\n        result.children.assign(n, {});\n        result.is_key.assign(n,\
    \ false);\n\n        int key_index = 0;\n        for (int i = 0; i < n; i++) {\n\
    \            while (key_index < int(_key.size()) && _lca.tin[_key[key_index]]\
    \ < _lca.tin[_vertices[i]]) {\n                key_index++;\n            }\n \
    \           if (key_index < int(_key.size()) && _key[key_index] == _vertices[i])\
    \ result.is_key[i] = true;\n        }\n\n        _stack.clear();\n        _stack.reserve(n);\n\
    \        for (int i = 0; i < n; i++) {\n            while (!_stack.empty() &&\
    \ !_lca.is_ancestor(_vertices[_stack.back()], _vertices[i])) {\n             \
    \   _stack.pop_back();\n            }\n            if (!_stack.empty()) {\n  \
    \              int p = _stack.back();\n                result.parent[i] = p;\n\
    \                result.parent_edge_count[i] = _lca.depth[_vertices[i]] - _lca.depth[_vertices[p]];\n\
    \                result.parent_cost[i] = _lca.dist[_vertices[i]] - _lca.dist[_vertices[p]];\n\
    \                result.children[p].push_back(i);\n            }\n           \
    \ _stack.push_back(i);\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_VIRTUAL_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  - tree/sparse_table_lca.hpp
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: tree/virtual_tree.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-23 11:34:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/virtual_tree.hpp
layout: document
title: Virtual Tree
---

## Overview

`VirtualTree<T>` preprocesses a rooted weighted tree and repeatedly builds the
minimal rooted tree containing a selected set of key vertices and all LCAs
needed to connect them.

If there are `K` distinct key vertices, the result contains at most `2K - 1`
vertices. Construction takes `O(K log K)` time for sorting; LCA queries are
`O(1)` through an internal `SparseTableLca`.

This is useful for tree DP when each query mentions only a small subset of the
original vertices.

## Result Representation

`build(keys)` returns `VirtualTreeResult<T>`. Every result array is indexed by a
compressed virtual-tree index.

| Field | Meaning |
| --- | --- |
| `vertex[i]` | Original-tree vertex represented by compressed index `i`. |
| `parent[i]` | Compressed parent index, or `-1` for the virtual root. |
| `parent_edge_count[i]` | Number of original edges from `parent[i]` to `i`. |
| `parent_cost[i]` | Original weighted path cost from `parent[i]` to `i`. |
| `children[i]` | Compressed child indices. |
| `is_key[i]` | Whether this original vertex appeared in the input key set. |

Vertices are stored in original-tree preorder. Therefore every parent appears
before its children, and the root has compressed index zero for a nonempty
result.

Duplicate keys are removed. An empty key set produces an empty result.

`result.size()` and `result.edge_count()` return the compressed vertex and edge
counts. `result.root()` returns compressed index zero, while
`result.root_vertex()` returns its original-tree vertex id. Both root methods
return `-1` for an empty result.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `VirtualTree()` | Creates an uninitialized builder. | `O(1)` |
| `VirtualTree(graph, root)` | Preprocesses the original tree. | `O(N log N)` |
| `void build_lca(graph, root)` | Replaces the original tree and preprocesses it. | `O(N log N)` |
| `int original_size() const` | Returns the original number of vertices. | `O(1)` |
| `const SparseTableLca<T>& lca_data() const` | Exposes original rooted-tree metadata. | `O(1)` |
| `result_type build(keys)` | Builds a virtual tree for the selected vertices. | `O(K log K)` |

All selected vertices must belong to the component reached from the
preprocessing root.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/virtual_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<long long> graph(5);
    graph.add_edge(0, 1, 3);
    graph.add_edge(0, 2, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(1, 4, 2);

    m1une::tree::VirtualTree<long long> builder(graph, 0);
    auto tree = builder.build(std::vector<int>{2, 3, 4});

    for (int i = 0; i < tree.size(); i++) {
        std::cout << tree.vertex[i] << ' ' << tree.parent[i] << ' '
                  << tree.parent_cost[i] << '\n';
    }
}
```
