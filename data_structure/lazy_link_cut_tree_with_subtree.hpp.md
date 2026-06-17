---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_link_cut_tree.hpp
    title: Lazy Link-Cut Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
    title: verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/lazy_link_cut_tree_with_subtree.hpp\"\n\n\
    \n\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"data_structure/lazy_link_cut_tree.hpp\"\
    \n\n\n\n#line 9 \"data_structure/lazy_link_cut_tree.hpp\"\n\n#line 1 \"acted_monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\n// Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type\
    \ b, typename AM::operator_type f,\n                                 typename\
    \ AM::operator_type g) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \  // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 11 \"data_structure/lazy_link_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazyLinkCutTree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        int left = -1;\n        int right = -1;\n        int parent\
    \ = -1;\n        bool rev = false;\n        int size = 1;\n        T value = ActedMonoid::id();\n\
    \        T prod = ActedMonoid::id();\n        T rev_prod = ActedMonoid::id();\n\
    \        F lazy = ActedMonoid::op_id();\n    };\n\n    struct EdgeInfo {\n   \
    \     int u = -1;\n        int v = -1;\n        int node = -1;\n        bool alive\
    \ = false;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo>\
    \ _edges;\n    std::vector<int> _path_buffer;\n\n    static T make_node_value(const\
    \ T& value, int) {\n        return value;\n    }\n\n    static T make_node_value(T&&\
    \ value, int) {\n        return std::move(value);\n    }\n\n    template <class\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    static T make_node_value(const U& value,\
    \ int index) {\n        if constexpr (requires(U x) { ActedMonoid::make(x); })\
    \ {\n            return ActedMonoid::make(value);\n        } else if constexpr\
    \ (requires(U x, int i) { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int child_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].size;\n    }\n\n    bool is_splay_root(int node) const {\n\
    \        int parent = _nodes[node].parent;\n        return parent == -1 || (_nodes[parent].left\
    \ != node && _nodes[parent].right != node);\n    }\n\n    void update(int node)\
    \ {\n        Node& x = _nodes[node];\n        x.size = 1 + child_size(x.left)\
    \ + child_size(x.right);\n        T left_prod = x.left == -1 ? ActedMonoid::id()\
    \ : _nodes[x.left].prod;\n        T right_prod = x.right == -1 ? ActedMonoid::id()\
    \ : _nodes[x.right].prod;\n        T left_rev_prod = x.left == -1 ? ActedMonoid::id()\
    \ : _nodes[x.left].rev_prod;\n        T right_rev_prod = x.right == -1 ? ActedMonoid::id()\
    \ : _nodes[x.right].rev_prod;\n        x.prod = ActedMonoid::op(ActedMonoid::op(left_prod,\
    \ x.value), right_prod);\n        x.rev_prod = ActedMonoid::op(ActedMonoid::op(right_rev_prod,\
    \ x.value), left_rev_prod);\n    }\n\n    void apply_reverse(int node) {\n   \
    \     if (node == -1) return;\n        Node& x = _nodes[node];\n        std::swap(x.left,\
    \ x.right);\n        std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n\
    \    }\n\n    void apply_operator(int node, const F& f) {\n        if (node ==\
    \ -1) return;\n        Node& x = _nodes[node];\n        x.value = ActedMonoid::mapping(f,\
    \ x.value);\n        x.prod = ActedMonoid::mapping(f, x.prod);\n        x.rev_prod\
    \ = ActedMonoid::mapping(f, x.rev_prod);\n        x.lazy = ActedMonoid::op_comp(f,\
    \ x.lazy);\n    }\n\n    void push(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        if (x.rev) {\n            apply_reverse(x.left);\n\
    \            apply_reverse(x.right);\n            x.rev = false;\n        }\n\
    \        apply_operator(x.left, x.lazy);\n        apply_operator(x.right, x.lazy);\n\
    \        x.lazy = ActedMonoid::op_id();\n    }\n\n    void push_to(int node) {\n\
    \        _path_buffer.clear();\n        int cur = node;\n        _path_buffer.push_back(cur);\n\
    \        while (!is_splay_root(cur)) {\n            cur = _nodes[cur].parent;\n\
    \            _path_buffer.push_back(cur);\n        }\n        for (int i = int(_path_buffer.size())\
    \ - 1; i >= 0; i--) push(_path_buffer[i]);\n    }\n\n    void rotate(int node)\
    \ {\n        int parent = _nodes[node].parent;\n        int grand = _nodes[parent].parent;\n\
    \        bool is_right = _nodes[parent].right == node;\n        int middle = is_right\
    \ ? _nodes[node].left : _nodes[node].right;\n\n        if (!is_splay_root(parent))\
    \ {\n            if (_nodes[grand].left == parent) {\n                _nodes[grand].left\
    \ = node;\n            } else {\n                _nodes[grand].right = node;\n\
    \            }\n        }\n        _nodes[node].parent = grand;\n\n        if\
    \ (is_right) {\n            _nodes[node].left = parent;\n            _nodes[parent].right\
    \ = middle;\n        } else {\n            _nodes[node].right = parent;\n    \
    \        _nodes[parent].left = middle;\n        }\n        if (middle != -1) _nodes[middle].parent\
    \ = parent;\n        _nodes[parent].parent = node;\n\n        update(parent);\n\
    \        update(node);\n    }\n\n    void splay(int node) {\n        push_to(node);\n\
    \        while (!is_splay_root(node)) {\n            int parent = _nodes[node].parent;\n\
    \            int grand = _nodes[parent].parent;\n            if (!is_splay_root(parent))\
    \ {\n                bool zig_zig = (_nodes[parent].left == node) == (_nodes[grand].left\
    \ == parent);\n                rotate(zig_zig ? parent : node);\n            }\n\
    \            rotate(node);\n        }\n    }\n\n    int access(int node) {\n \
    \       int last = -1;\n        for (int cur = node; cur != -1; cur = _nodes[cur].parent)\
    \ {\n            splay(cur);\n            _nodes[cur].right = last;\n        \
    \    if (last != -1) _nodes[last].parent = cur;\n            update(cur);\n  \
    \          last = cur;\n        }\n        splay(node);\n        return last;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < int(_nodes.size()));\n\
    \    }\n\n    void check_edge(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    LazyLinkCutTree()\
    \ = default;\n\n    explicit LazyLinkCutTree(int n) {\n        assert(0 <= n);\n\
    \        _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit LazyLinkCutTree(const std::vector<T>& values) {\n     \
    \   _nodes.reserve(values.size());\n        for (int i = 0; i < int(values.size());\
    \ i++) add_vertex(values[i]);\n    }\n\n    explicit LazyLinkCutTree(std::vector<T>&&\
    \ values) {\n        _nodes.reserve(values.size());\n        for (int i = 0; i\
    \ < int(values.size()); i++) add_vertex(std::move(values[i]));\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LazyLinkCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = ActedMonoid::id()) {\n        Node node;\n\
    \        node.value = value;\n        node.prod = value;\n        node.rev_prod\
    \ = value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_vertex(T&& value) {\n        Node node;\n       \
    \ node.value = std::move(value);\n        node.prod = node.value;\n        node.rev_prod\
    \ = node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
    \ size()));\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        check_edge(edge_id);\n\
    \        return _edges[edge_id].alive;\n    }\n\n    int edge_node(int edge_id)\
    \ const {\n        check_edge(edge_id);\n        return _edges[edge_id].node;\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  check_edge(edge_id);\n        return {_edges[edge_id].u, _edges[edge_id].v};\n\
    \    }\n\n    T get(int v) {\n        check_vertex(v);\n        access(v);\n \
    \       return _nodes[v].value;\n    }\n\n    T operator[](int v) {\n        return\
    \ get(v);\n    }\n\n    void set(int v, const T& value) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = value;\n        update(v);\n  \
    \  }\n\n    void set(int v, T&& value) {\n        check_vertex(v);\n        access(v);\n\
    \        _nodes[v].value = std::move(value);\n        update(v);\n    }\n\n  \
    \  template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>)\
    \ && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        set(v, make_node_value(value,\
    \ v));\n    }\n\n    void apply(int v, const F& f) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = ActedMonoid::mapping(f, _nodes[v].value);\n\
    \        update(v);\n    }\n\n    void apply(int u, int v, const F& f) {\n   \
    \     check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        apply_operator(v, f);\n\
    \    }\n\n    void evert(int v) {\n        check_vertex(v);\n        access(v);\n\
    \        apply_reverse(v);\n    }\n\n    int component_root(int v) {\n       \
    \ check_vertex(v);\n        access(v);\n        int cur = v;\n        push(cur);\n\
    \        while (_nodes[cur].left != -1) {\n            cur = _nodes[cur].left;\n\
    \            push(cur);\n        }\n        splay(cur);\n        return cur;\n\
    \    }\n\n    bool connected(int u, int v) {\n        check_vertex(u);\n     \
    \   check_vertex(v);\n        if (u == v) return true;\n        return component_root(u)\
    \ == component_root(v);\n    }\n\n    bool same(int u, int v) {\n        return\
    \ connected(u, v);\n    }\n\n    bool link(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v) return false;\n        evert(u);\n\
    \        if (component_root(v) == u) return false;\n        _nodes[u].parent =\
    \ v;\n        return true;\n    }\n\n    int link_edge(int u, int v, const T&\
    \ value = ActedMonoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { ActedMonoid::make(x); } ||\n        requires(U x, int i)\
    \ { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    int link_edge(int u, int v, const U& value) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v || connected(u, v)) return -1;\n\
    \        return link_edge(u, v, make_node_value(value, size()));\n    }\n\n  \
    \  bool cut(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v) return false;\n        evert(u);\n        access(v);\n  \
    \      if (_nodes[v].left != u || _nodes[u].right != -1) return false;\n     \
    \   _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n        update(v);\n\
    \        return true;\n    }\n\n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n\
    \        EdgeInfo& edge = _edges[edge_id];\n        if (!edge.alive) return false;\n\
    \        bool ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node,\
    \ edge.v);\n        if (ok1 && ok2) edge.alive = false;\n        return ok1 &&\
    \ ok2;\n    }\n\n    T get_edge(int edge_id) {\n        return get(edge_node(edge_id));\n\
    \    }\n\n    void set_edge(int edge_id, const T& value) {\n        set(edge_node(edge_id),\
    \ value);\n    }\n\n    void set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id),\
    \ std::move(value));\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    void apply_edge(int\
    \ edge_id, const F& f) {\n        apply(edge_node(edge_id), f);\n    }\n\n   \
    \ T prod(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        assert(connected(u, v));\n        evert(u);\n        access(v);\n   \
    \     return _nodes[v].prod;\n    }\n\n    T path_prod(int u, int v) {\n     \
    \   return prod(u, v);\n    }\n\n    int path_size(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        assert(connected(u, v));\n        evert(u);\n\
    \        access(v);\n        return _nodes[v].size;\n    }\n\n    int kth_vertex(int\
    \ u, int v, int k) {\n        check_vertex(u);\n        check_vertex(v);\n   \
    \     assert(connected(u, v));\n        evert(u);\n        access(v);\n      \
    \  assert(0 <= k && k < _nodes[v].size);\n\n        int cur = v;\n        while\
    \ (true) {\n            push(cur);\n            int left_size = child_size(_nodes[cur].left);\n\
    \            if (k < left_size) {\n                cur = _nodes[cur].left;\n \
    \           } else if (k == left_size) {\n                splay(cur);\n      \
    \          return cur;\n            } else {\n                k -= left_size +\
    \ 1;\n                cur = _nodes[cur].right;\n            }\n        }\n   \
    \ }\n\n    int lca(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (!connected(u, v)) return -1;\n        if (u == v) return u;\n   \
    \     access(u);\n        return access(v);\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n#line 11 \"data_structure/lazy_link_cut_tree_with_subtree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazyLinkCutTreeWithSubtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ ForestEdge {\n        int u = -1;\n        int v = -1;\n        bool alive =\
    \ false;\n    };\n\n    LazyLinkCutTree<ActedMonoid> _lct;\n    std::vector<ForestEdge>\
    \ _forest_edges;\n    std::vector<std::vector<int>> _adj;\n\n    void ensure_forest_size()\
    \ {\n        if (int(_adj.size()) < _lct.size()) _adj.resize(_lct.size());\n \
    \   }\n\n    void add_forest_edge(int u, int v) {\n        ensure_forest_size();\n\
    \        int edge_id = int(_forest_edges.size());\n        _forest_edges.push_back(ForestEdge{u,\
    \ v, true});\n        _adj[u].push_back(edge_id);\n        _adj[v].push_back(edge_id);\n\
    \    }\n\n    bool remove_forest_edge(int u, int v) {\n        for (int edge_id\
    \ : _adj[u]) {\n            ForestEdge& edge = _forest_edges[edge_id];\n     \
    \       if (!edge.alive) continue;\n            if ((edge.u == u && edge.v ==\
    \ v) || (edge.u == v && edge.v == u)) {\n                edge.alive = false;\n\
    \                return true;\n            }\n        }\n        return false;\n\
    \    }\n\n    int other_endpoint(int edge_id, int v) const {\n        const ForestEdge&\
    \ edge = _forest_edges[edge_id];\n        return edge.u == v ? edge.v : edge.u;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < _lct.size());\n\
    \    }\n\n    int parent_in_rooted_tree(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(_lct.connected(root, v));\n        if\
    \ (root == v) return -1;\n\n        std::vector<int> parent(_lct.size(), -1);\n\
    \        std::vector<int> stack;\n        parent[root] = root;\n        stack.push_back(root);\n\
    \n        for (int it = 0; it < int(stack.size()); it++) {\n            int x\
    \ = stack[it];\n            for (int edge_id : _adj[x]) {\n                const\
    \ ForestEdge& edge = _forest_edges[edge_id];\n                if (!edge.alive)\
    \ continue;\n                int to = other_endpoint(edge_id, x);\n          \
    \      if (parent[to] != -1) continue;\n                parent[to] = x;\n    \
    \            if (to == v) return x;\n                stack.push_back(to);\n  \
    \          }\n        }\n\n        assert(false);\n        return -1;\n    }\n\
    \n   public:\n    LazyLinkCutTreeWithSubtree() = default;\n\n    explicit LazyLinkCutTreeWithSubtree(int\
    \ n) : _lct(n), _adj(n) {\n        assert(0 <= n);\n    }\n\n    explicit LazyLinkCutTreeWithSubtree(const\
    \ std::vector<T>& values) : _lct(values), _adj(values.size()) {}\n\n    explicit\
    \ LazyLinkCutTreeWithSubtree(std::vector<T>&& values) : _lct(std::move(values))\
    \ {\n        _adj.resize(_lct.size());\n    }\n\n    template <class U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit LazyLinkCutTreeWithSubtree(const std::vector<U>& values)\
    \ : _lct(values), _adj(values.size()) {}\n\n    int size() const {\n        return\
    \ _lct.size();\n    }\n\n    bool empty() const {\n        return _lct.empty();\n\
    \    }\n\n    int add_vertex(const T& value = ActedMonoid::id()) {\n        int\
    \ v = _lct.add_vertex(value);\n        ensure_forest_size();\n        return v;\n\
    \    }\n\n    int add_vertex(T&& value) {\n        int v = _lct.add_vertex(std::move(value));\n\
    \        ensure_forest_size();\n        return v;\n    }\n\n    template <class\
    \ U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n        requires(U\
    \ x) { ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int add_vertex(const\
    \ U& value) {\n        int v = _lct.add_vertex(value);\n        ensure_forest_size();\n\
    \        return v;\n    }\n\n    int edge_count() const {\n        return _lct.edge_count();\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        return _lct.edge_alive(edge_id);\n\
    \    }\n\n    int edge_node(int edge_id) const {\n        return _lct.edge_node(edge_id);\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  return _lct.edge_endpoints(edge_id);\n    }\n\n    T get(int v) {\n       \
    \ return _lct.get(v);\n    }\n\n    T operator[](int v) {\n        return get(v);\n\
    \    }\n\n    void set(int v, const T& value) {\n        _lct.set(v, value);\n\
    \    }\n\n    void set(int v, T&& value) {\n        _lct.set(v, std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        _lct.set(v, value);\n \
    \   }\n\n    void apply(int v, const F& f) {\n        _lct.apply(v, f);\n    }\n\
    \n    void apply(int u, int v, const F& f) {\n        _lct.apply(u, v, f);\n \
    \   }\n\n    void evert(int v) {\n        _lct.evert(v);\n    }\n\n    int component_root(int\
    \ v) {\n        return _lct.component_root(v);\n    }\n\n    bool connected(int\
    \ u, int v) {\n        return _lct.connected(u, v);\n    }\n\n    bool same(int\
    \ u, int v) {\n        return connected(u, v);\n    }\n\n    bool link(int u,\
    \ int v) {\n        bool ok = _lct.link(u, v);\n        if (ok) add_forest_edge(u,\
    \ v);\n        return ok;\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = ActedMonoid::id()) {\n        int edge_id = _lct.link_edge(u, v, value);\n\
    \        if (edge_id == -1) return -1;\n        int node = _lct.edge_node(edge_id);\n\
    \        ensure_forest_size();\n        add_forest_edge(u, node);\n        add_forest_edge(node,\
    \ v);\n        return edge_id;\n    }\n\n    int link_edge(int u, int v, T&& value)\
    \ {\n        int edge_id = _lct.link_edge(u, v, std::move(value));\n        if\
    \ (edge_id == -1) return -1;\n        int node = _lct.edge_node(edge_id);\n  \
    \      ensure_forest_size();\n        add_forest_edge(u, node);\n        add_forest_edge(node,\
    \ v);\n        return edge_id;\n    }\n\n    template <class U>\n    requires\
    \ (!std::same_as<std::remove_cvref_t<U>, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    int link_edge(int u, int v, const U& value)\
    \ {\n        int edge_id = _lct.link_edge(u, v, value);\n        if (edge_id ==\
    \ -1) return -1;\n        int node = _lct.edge_node(edge_id);\n        ensure_forest_size();\n\
    \        add_forest_edge(u, node);\n        add_forest_edge(node, v);\n      \
    \  return edge_id;\n    }\n\n    bool cut(int u, int v) {\n        bool ok = _lct.cut(u,\
    \ v);\n        if (ok) remove_forest_edge(u, v);\n        return ok;\n    }\n\n\
    \    bool cut_edge(int edge_id) {\n        int node = _lct.edge_node(edge_id);\n\
    \        auto [u, v] = _lct.edge_endpoints(edge_id);\n        bool ok = _lct.cut_edge(edge_id);\n\
    \        if (ok) {\n            remove_forest_edge(u, node);\n            remove_forest_edge(node,\
    \ v);\n        }\n        return ok;\n    }\n\n    T get_edge(int edge_id) {\n\
    \        return _lct.get_edge(edge_id);\n    }\n\n    void set_edge(int edge_id,\
    \ const T& value) {\n        _lct.set_edge(edge_id, value);\n    }\n\n    void\
    \ set_edge(int edge_id, T&& value) {\n        _lct.set_edge(edge_id, std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        _lct.set_edge(edge_id,\
    \ value);\n    }\n\n    void apply_edge(int edge_id, const F& f) {\n        _lct.apply_edge(edge_id,\
    \ f);\n    }\n\n    T prod(int u, int v) {\n        return _lct.prod(u, v);\n\
    \    }\n\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    int path_size(int u, int v) {\n        return _lct.path_size(u, v);\n  \
    \  }\n\n    int kth_vertex(int u, int v, int k) {\n        return _lct.kth_vertex(u,\
    \ v, k);\n    }\n\n    int lca(int u, int v) {\n        return _lct.lca(u, v);\n\
    \    }\n\n    std::vector<int> subtree_vertices(int root, int v) {\n        int\
    \ blocked_parent = parent_in_rooted_tree(root, v);\n        std::vector<int> res;\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.emplace_back(v,\
    \ blocked_parent);\n\n        while (!stack.empty()) {\n            auto [x, parent]\
    \ = stack.back();\n            stack.pop_back();\n            res.push_back(x);\n\
    \n            const std::vector<int>& edges = _adj[x];\n            for (int i\
    \ = int(edges.size()) - 1; i >= 0; i--) {\n                int edge_id = edges[i];\n\
    \                const ForestEdge& edge = _forest_edges[edge_id];\n          \
    \      if (!edge.alive) continue;\n                int to = other_endpoint(edge_id,\
    \ x);\n                if (to == parent) continue;\n                stack.emplace_back(to,\
    \ x);\n            }\n        }\n\n        return res;\n    }\n\n    std::vector<int>\
    \ subtree_vertices(int v) {\n        return subtree_vertices(component_root(v),\
    \ v);\n    }\n\n    int subtree_size(int root, int v) {\n        return int(subtree_vertices(root,\
    \ v).size());\n    }\n\n    int subtree_size(int v) {\n        return int(subtree_vertices(v).size());\n\
    \    }\n\n    T subtree_prod(int root, int v) {\n        T res = ActedMonoid::id();\n\
    \        for (int x : subtree_vertices(root, v)) {\n            res = ActedMonoid::op(res,\
    \ _lct.get(x));\n        }\n        return res;\n    }\n\n    T subtree_prod(int\
    \ v) {\n        return subtree_prod(component_root(v), v);\n    }\n\n    void\
    \ apply_subtree(int root, int v, const F& f) {\n        std::vector<int> vertices\
    \ = subtree_vertices(root, v);\n        for (int x : vertices) _lct.apply(x, f);\n\
    \    }\n\n    void apply_subtree(int v, const F& f) {\n        apply_subtree(component_root(v),\
    \ v, f);\n    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP\n#define M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"data_structure/lazy_link_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazyLinkCutTreeWithSubtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ ForestEdge {\n        int u = -1;\n        int v = -1;\n        bool alive =\
    \ false;\n    };\n\n    LazyLinkCutTree<ActedMonoid> _lct;\n    std::vector<ForestEdge>\
    \ _forest_edges;\n    std::vector<std::vector<int>> _adj;\n\n    void ensure_forest_size()\
    \ {\n        if (int(_adj.size()) < _lct.size()) _adj.resize(_lct.size());\n \
    \   }\n\n    void add_forest_edge(int u, int v) {\n        ensure_forest_size();\n\
    \        int edge_id = int(_forest_edges.size());\n        _forest_edges.push_back(ForestEdge{u,\
    \ v, true});\n        _adj[u].push_back(edge_id);\n        _adj[v].push_back(edge_id);\n\
    \    }\n\n    bool remove_forest_edge(int u, int v) {\n        for (int edge_id\
    \ : _adj[u]) {\n            ForestEdge& edge = _forest_edges[edge_id];\n     \
    \       if (!edge.alive) continue;\n            if ((edge.u == u && edge.v ==\
    \ v) || (edge.u == v && edge.v == u)) {\n                edge.alive = false;\n\
    \                return true;\n            }\n        }\n        return false;\n\
    \    }\n\n    int other_endpoint(int edge_id, int v) const {\n        const ForestEdge&\
    \ edge = _forest_edges[edge_id];\n        return edge.u == v ? edge.v : edge.u;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < _lct.size());\n\
    \    }\n\n    int parent_in_rooted_tree(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(_lct.connected(root, v));\n        if\
    \ (root == v) return -1;\n\n        std::vector<int> parent(_lct.size(), -1);\n\
    \        std::vector<int> stack;\n        parent[root] = root;\n        stack.push_back(root);\n\
    \n        for (int it = 0; it < int(stack.size()); it++) {\n            int x\
    \ = stack[it];\n            for (int edge_id : _adj[x]) {\n                const\
    \ ForestEdge& edge = _forest_edges[edge_id];\n                if (!edge.alive)\
    \ continue;\n                int to = other_endpoint(edge_id, x);\n          \
    \      if (parent[to] != -1) continue;\n                parent[to] = x;\n    \
    \            if (to == v) return x;\n                stack.push_back(to);\n  \
    \          }\n        }\n\n        assert(false);\n        return -1;\n    }\n\
    \n   public:\n    LazyLinkCutTreeWithSubtree() = default;\n\n    explicit LazyLinkCutTreeWithSubtree(int\
    \ n) : _lct(n), _adj(n) {\n        assert(0 <= n);\n    }\n\n    explicit LazyLinkCutTreeWithSubtree(const\
    \ std::vector<T>& values) : _lct(values), _adj(values.size()) {}\n\n    explicit\
    \ LazyLinkCutTreeWithSubtree(std::vector<T>&& values) : _lct(std::move(values))\
    \ {\n        _adj.resize(_lct.size());\n    }\n\n    template <class U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit LazyLinkCutTreeWithSubtree(const std::vector<U>& values)\
    \ : _lct(values), _adj(values.size()) {}\n\n    int size() const {\n        return\
    \ _lct.size();\n    }\n\n    bool empty() const {\n        return _lct.empty();\n\
    \    }\n\n    int add_vertex(const T& value = ActedMonoid::id()) {\n        int\
    \ v = _lct.add_vertex(value);\n        ensure_forest_size();\n        return v;\n\
    \    }\n\n    int add_vertex(T&& value) {\n        int v = _lct.add_vertex(std::move(value));\n\
    \        ensure_forest_size();\n        return v;\n    }\n\n    template <class\
    \ U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n        requires(U\
    \ x) { ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int add_vertex(const\
    \ U& value) {\n        int v = _lct.add_vertex(value);\n        ensure_forest_size();\n\
    \        return v;\n    }\n\n    int edge_count() const {\n        return _lct.edge_count();\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        return _lct.edge_alive(edge_id);\n\
    \    }\n\n    int edge_node(int edge_id) const {\n        return _lct.edge_node(edge_id);\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  return _lct.edge_endpoints(edge_id);\n    }\n\n    T get(int v) {\n       \
    \ return _lct.get(v);\n    }\n\n    T operator[](int v) {\n        return get(v);\n\
    \    }\n\n    void set(int v, const T& value) {\n        _lct.set(v, value);\n\
    \    }\n\n    void set(int v, T&& value) {\n        _lct.set(v, std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        _lct.set(v, value);\n \
    \   }\n\n    void apply(int v, const F& f) {\n        _lct.apply(v, f);\n    }\n\
    \n    void apply(int u, int v, const F& f) {\n        _lct.apply(u, v, f);\n \
    \   }\n\n    void evert(int v) {\n        _lct.evert(v);\n    }\n\n    int component_root(int\
    \ v) {\n        return _lct.component_root(v);\n    }\n\n    bool connected(int\
    \ u, int v) {\n        return _lct.connected(u, v);\n    }\n\n    bool same(int\
    \ u, int v) {\n        return connected(u, v);\n    }\n\n    bool link(int u,\
    \ int v) {\n        bool ok = _lct.link(u, v);\n        if (ok) add_forest_edge(u,\
    \ v);\n        return ok;\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = ActedMonoid::id()) {\n        int edge_id = _lct.link_edge(u, v, value);\n\
    \        if (edge_id == -1) return -1;\n        int node = _lct.edge_node(edge_id);\n\
    \        ensure_forest_size();\n        add_forest_edge(u, node);\n        add_forest_edge(node,\
    \ v);\n        return edge_id;\n    }\n\n    int link_edge(int u, int v, T&& value)\
    \ {\n        int edge_id = _lct.link_edge(u, v, std::move(value));\n        if\
    \ (edge_id == -1) return -1;\n        int node = _lct.edge_node(edge_id);\n  \
    \      ensure_forest_size();\n        add_forest_edge(u, node);\n        add_forest_edge(node,\
    \ v);\n        return edge_id;\n    }\n\n    template <class U>\n    requires\
    \ (!std::same_as<std::remove_cvref_t<U>, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    int link_edge(int u, int v, const U& value)\
    \ {\n        int edge_id = _lct.link_edge(u, v, value);\n        if (edge_id ==\
    \ -1) return -1;\n        int node = _lct.edge_node(edge_id);\n        ensure_forest_size();\n\
    \        add_forest_edge(u, node);\n        add_forest_edge(node, v);\n      \
    \  return edge_id;\n    }\n\n    bool cut(int u, int v) {\n        bool ok = _lct.cut(u,\
    \ v);\n        if (ok) remove_forest_edge(u, v);\n        return ok;\n    }\n\n\
    \    bool cut_edge(int edge_id) {\n        int node = _lct.edge_node(edge_id);\n\
    \        auto [u, v] = _lct.edge_endpoints(edge_id);\n        bool ok = _lct.cut_edge(edge_id);\n\
    \        if (ok) {\n            remove_forest_edge(u, node);\n            remove_forest_edge(node,\
    \ v);\n        }\n        return ok;\n    }\n\n    T get_edge(int edge_id) {\n\
    \        return _lct.get_edge(edge_id);\n    }\n\n    void set_edge(int edge_id,\
    \ const T& value) {\n        _lct.set_edge(edge_id, value);\n    }\n\n    void\
    \ set_edge(int edge_id, T&& value) {\n        _lct.set_edge(edge_id, std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        _lct.set_edge(edge_id,\
    \ value);\n    }\n\n    void apply_edge(int edge_id, const F& f) {\n        _lct.apply_edge(edge_id,\
    \ f);\n    }\n\n    T prod(int u, int v) {\n        return _lct.prod(u, v);\n\
    \    }\n\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    int path_size(int u, int v) {\n        return _lct.path_size(u, v);\n  \
    \  }\n\n    int kth_vertex(int u, int v, int k) {\n        return _lct.kth_vertex(u,\
    \ v, k);\n    }\n\n    int lca(int u, int v) {\n        return _lct.lca(u, v);\n\
    \    }\n\n    std::vector<int> subtree_vertices(int root, int v) {\n        int\
    \ blocked_parent = parent_in_rooted_tree(root, v);\n        std::vector<int> res;\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.emplace_back(v,\
    \ blocked_parent);\n\n        while (!stack.empty()) {\n            auto [x, parent]\
    \ = stack.back();\n            stack.pop_back();\n            res.push_back(x);\n\
    \n            const std::vector<int>& edges = _adj[x];\n            for (int i\
    \ = int(edges.size()) - 1; i >= 0; i--) {\n                int edge_id = edges[i];\n\
    \                const ForestEdge& edge = _forest_edges[edge_id];\n          \
    \      if (!edge.alive) continue;\n                int to = other_endpoint(edge_id,\
    \ x);\n                if (to == parent) continue;\n                stack.emplace_back(to,\
    \ x);\n            }\n        }\n\n        return res;\n    }\n\n    std::vector<int>\
    \ subtree_vertices(int v) {\n        return subtree_vertices(component_root(v),\
    \ v);\n    }\n\n    int subtree_size(int root, int v) {\n        return int(subtree_vertices(root,\
    \ v).size());\n    }\n\n    int subtree_size(int v) {\n        return int(subtree_vertices(v).size());\n\
    \    }\n\n    T subtree_prod(int root, int v) {\n        T res = ActedMonoid::id();\n\
    \        for (int x : subtree_vertices(root, v)) {\n            res = ActedMonoid::op(res,\
    \ _lct.get(x));\n        }\n        return res;\n    }\n\n    T subtree_prod(int\
    \ v) {\n        return subtree_prod(component_root(v), v);\n    }\n\n    void\
    \ apply_subtree(int root, int v, const F& f) {\n        std::vector<int> vertices\
    \ = subtree_vertices(root, v);\n        for (int x : vertices) _lct.apply(x, f);\n\
    \    }\n\n    void apply_subtree(int v, const F& f) {\n        apply_subtree(component_root(v),\
    \ v, f);\n    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\
    \n#endif  // M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP\n"
  dependsOn:
  - data_structure/lazy_link_cut_tree.hpp
  - acted_monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/lazy_link_cut_tree_with_subtree.hpp
  requiredBy: []
  timestamp: '2026-06-17 15:56:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
documentation_of: data_structure/lazy_link_cut_tree_with_subtree.hpp
layout: document
title: Lazy Link-Cut Tree With Subtree
---

## Overview

`m1une::data_structure::LazyLinkCutTreeWithSubtree<ActedMonoid>` is the subtree
query companion to `LazyLinkCutTree`. It keeps the same dynamic path query and
path update interface, and adds rooted subtree queries and subtree updates.

Path operations are delegated to `LazyLinkCutTree`. Subtree operations use an
explicit copy of the represented forest and visit vertices in deterministic
preorder, so they remain correct for arbitrary acted monoids. Pending path lazy
updates are pushed by reading each visited vertex before it is folded into a
subtree product.

## Template Parameter

`ActedMonoid` must satisfy `m1une::acted_monoid::IsActedMonoid`:

```cpp
struct AM {
    using value_type = T;
    using operator_type = F;

    static T id();
    static T op(const T& a, const T& b);

    static F op_id();
    static F op_comp(const F& f, const F& g);

    static T mapping(const F& f, const T& x);
};
```

## Construction

```cpp
LazyLinkCutTreeWithSubtree<ActedMonoid> lct;
LazyLinkCutTreeWithSubtree<ActedMonoid> lct(n);
LazyLinkCutTreeWithSubtree<ActedMonoid> lct(values);
```

Construction and `add_vertex` follow `LazyLinkCutTree`.

## Methods

All `LazyLinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries and updates: `prod`, `path_prod`, `path_size`, `kth_vertex`,
  `apply`, `apply_edge`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> subtree_vertices(root, v)` | Vertices in the subtree of `v` when the represented tree is rooted at `root`. | `O(C)` |
| `std::vector<int> subtree_vertices(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the rooted subtree. | `O(C)` |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `T subtree_prod(root, v)` | Acted-monoid value product of the rooted subtree. | `O(C + S log N)` |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | `O(C + S log N)` |
| `void apply_subtree(root, v, f)` | Applies `f` to every link-cut-tree vertex in the rooted subtree. | `O(C + S log N)` |
| `void apply_subtree(v, f)` | Uses the current represented root of `v`'s component. | `O(C + S log N)` |

Here `C` is the number of link-cut-tree vertices in the connected component and
`S` is the number of vertices in the requested subtree.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree_with_subtree.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::LazyLinkCutTreeWithSubtree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    lct.apply(2, 4, 10);
    std::cout << lct.path_prod(2, 4).sum << "\n";     // 54
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 54

    lct.apply_subtree(0, 1, 5);
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 74
}
```

## Notes

For non-commutative value monoids, subtree products use deterministic preorder:
visit the subtree root first, then active incident edges in link order.

The subtree layer is traversal-based by design. With the current acted-monoid
interface, a path lazy update cannot be applied to a cached subtree aggregate
without also updating virtual side subtrees that are not on the path. Visiting
the requested subtree keeps the semantics simple and correct for general acted
monoids.
