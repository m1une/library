---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_tree/link_cut_tree.hpp
    title: Link-Cut Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/all.hpp
    title: Dynamic Connectivity
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
    title: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_connectivity/online_dynamic_connectivity.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate\
    \ <typename T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for addition, which is 0.\n    static constexpr T id() {\n\
    \        return T(0);\n    }\n\n    // Returns the sum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return a + b;\n    }\n\n \
    \   static constexpr T inv(const T& x) {\n        return -x;\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/dynamic_tree/link_cut_tree.hpp\"\
    \n\n\n\n#line 5 \"ds/dynamic_tree/link_cut_tree.hpp\"\n#include <concepts>\n#include\
    \ <type_traits>\n#line 9 \"ds/dynamic_tree/link_cut_tree.hpp\"\n\n#line 1 \"monoid/concept.hpp\"\
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
    \ 11 \"ds/dynamic_tree/link_cut_tree.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nstruct LinkCutTree\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    struct Node\
    \ {\n        int left = -1;\n        int right = -1;\n        int parent = -1;\n\
    \        bool rev = false;\n        int size = 1;\n        int virtual_size =\
    \ 0;\n        int all_size = 1;\n        T value = Group::id();\n        T prod\
    \ = Group::id();\n        T rev_prod = Group::id();\n        T virtual_prod =\
    \ Group::id();\n        T all_prod = Group::id();\n    };\n\n    struct EdgeInfo\
    \ {\n        int u = -1;\n        int v = -1;\n        int node = -1;\n      \
    \  bool alive = false;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo>\
    \ _edges;\n    std::vector<int> _path_buffer;\n\n    static T make_node_value(const\
    \ T& value, int) {\n        return value;\n    }\n\n    static T make_node_value(T&&\
    \ value, int) {\n        return std::move(value);\n    }\n\n    template <class\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { Group::make(x);\
    \ } ||\n        requires(U x, int i) { Group::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { Group::make(x); }) {\n            return Group::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Group::make(x, i); }) {\n\
    \            return Group::make(value, index);\n        } else {\n           \
    \ return static_cast<T>(value);\n        }\n    }\n\n    int child_size(int node)\
    \ const {\n        return node == -1 ? 0 : _nodes[node].size;\n    }\n\n    int\
    \ child_all_size(int node) const {\n        return node == -1 ? 0 : _nodes[node].all_size;\n\
    \    }\n\n    T child_prod(int node) const {\n        return node == -1 ? Group::id()\
    \ : _nodes[node].prod;\n    }\n\n    T child_rev_prod(int node) const {\n    \
    \    return node == -1 ? Group::id() : _nodes[node].rev_prod;\n    }\n\n    T\
    \ child_all_prod(int node) const {\n        return node == -1 ? Group::id() :\
    \ _nodes[node].all_prod;\n    }\n\n    T node_subtree_prod(int node) const {\n\
    \        const Node& x = _nodes[node];\n        return Group::op(x.value, x.virtual_prod);\n\
    \    }\n\n    int node_subtree_size(int node) const {\n        return 1 + _nodes[node].virtual_size;\n\
    \    }\n\n    bool is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.all_size\
    \ = 1 + x.virtual_size + child_all_size(x.left) + child_all_size(x.right);\n \
    \       x.prod = Group::op(Group::op(child_prod(x.left), x.value), child_prod(x.right));\n\
    \        x.rev_prod = Group::op(Group::op(child_rev_prod(x.right), x.value), child_rev_prod(x.left));\n\
    \        x.all_prod = Group::op(Group::op(child_all_prod(x.left), x.value),\n\
    \                                Group::op(x.virtual_prod, child_all_prod(x.right)));\n\
    \    }\n\n    void add_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = Group::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = Group::op(x.virtual_prod, Group::inv(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ push(int node) {\n        if (node == -1 || !_nodes[node].rev) return;\n   \
    \     apply_reverse(_nodes[node].left);\n        apply_reverse(_nodes[node].right);\n\
    \        _nodes[node].rev = false;\n    }\n\n    void push_to(int node) {\n  \
    \      _path_buffer.clear();\n        int cur = node;\n        _path_buffer.push_back(cur);\n\
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
    \ {\n            splay(cur);\n            add_virtual_child(cur, _nodes[cur].right);\n\
    \            remove_virtual_child(cur, last);\n            _nodes[cur].right =\
    \ last;\n            if (last != -1) _nodes[last].parent = cur;\n            update(cur);\n\
    \            last = cur;\n        }\n        splay(node);\n        return last;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < int(_nodes.size()));\n\
    \    }\n\n    void check_edge(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    LinkCutTree() =\
    \ default;\n\n    explicit LinkCutTree(int n) {\n        assert(0 <= n);\n   \
    \     _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit LinkCutTree(const std::vector<T>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n\
    \    }\n\n    explicit LinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Group::make(x); } ||\n        requires(U x, int i) { Group::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LinkCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Group::id()) {\n        Node node;\n    \
    \    node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x,\
    \ int i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
    \ size()));\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        check_edge(edge_id);\n\
    \        return _edges[edge_id].alive;\n    }\n\n    int edge_node(int edge_id)\
    \ const {\n        check_edge(edge_id);\n        return _edges[edge_id].node;\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  check_edge(edge_id);\n        return {_edges[edge_id].u, _edges[edge_id].v};\n\
    \    }\n\n    const T& get(int v) const {\n        check_vertex(v);\n        return\
    \ _nodes[v].value;\n    }\n\n    const T& operator[](int v) const {\n        return\
    \ get(v);\n    }\n\n    void set(int v, const T& value) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = value;\n        update(v);\n  \
    \  }\n\n    void set(int v, T&& value) {\n        check_vertex(v);\n        access(v);\n\
    \        _nodes[v].value = std::move(value);\n        update(v);\n    }\n\n  \
    \  template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>)\
    \ && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x, int\
    \ i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n   \
    \ void set(int v, const U& value) {\n        set(v, make_node_value(value, v));\n\
    \    }\n\n    // Makes `v` the represented root of its component.\n    void evert(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        apply_reverse(v);\n\
    \    }\n\n    // Alias for `evert(v)`; changes the represented root to `v`.\n\
    \    void reroot(int v) {\n        evert(v);\n    }\n\n    // Returns the current\
    \ represented root of `v`'s component.\n    int component_root(int v) {\n    \
    \    check_vertex(v);\n        access(v);\n        int cur = v;\n        push(cur);\n\
    \        while (_nodes[cur].left != -1) {\n            cur = _nodes[cur].left;\n\
    \            push(cur);\n        }\n        splay(cur);\n        return cur;\n\
    \    }\n\n    // Alias for `component_root(v)`.\n    int root(int v) {\n     \
    \   return component_root(v);\n    }\n\n    bool connected(int u, int v) {\n \
    \       check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ true;\n        return component_root(u) == component_root(v);\n    }\n\n   \
    \ bool same(int u, int v) {\n        return connected(u, v);\n    }\n\n    //\
    \ Links two components. Internally calls `evert(u)`, so the represented root may\
    \ change.\n    bool link(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v) return false;\n        evert(u);\n        if (component_root(v)\
    \ == u) return false;\n        access(v);\n        _nodes[u].parent = v;\n   \
    \     add_virtual_child(v, u);\n        update(v);\n        return true;\n   \
    \ }\n\n    // Links `child` under `parent`. This is the same operation as `link(child,\
    \ parent)`;\n    // it internally calls `evert(child)`, so that side's represented\
    \ root may change.\n    bool link_parent(int child, int parent) {\n        return\
    \ link(child, parent);\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = Group::id()) {\n        check_vertex(u);\n        check_vertex(v);\n     \
    \   if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { Group::make(x); } ||\n        requires(U x, int i) { Group::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int link_edge(int u,\
    \ int v, const U& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        return link_edge(u,\
    \ v, make_node_value(value, size()));\n    }\n\n    // Cuts edge `(u, v)`. Internally\
    \ calls `evert(u)`, so the represented root may change.\n    bool cut(int u, int\
    \ v) {\n        check_vertex(u);\n        check_vertex(v);\n        if (u == v)\
    \ return false;\n        evert(u);\n        access(v);\n        if (_nodes[v].left\
    \ != u || _nodes[u].right != -1) return false;\n        _nodes[v].left = -1;\n\
    \        _nodes[u].parent = -1;\n        update(v);\n        return true;\n  \
    \  }\n\n    // Cuts the parent edge of `v` in the current represented-root orientation.\n\
    \    // Unlike `cut(u, v)`, this does not call `evert`.\n    bool cut_parent(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        int left = _nodes[v].left;\n\
    \        if (left == -1) return false;\n        _nodes[v].left = -1;\n       \
    \ _nodes[left].parent = -1;\n        update(v);\n        return true;\n    }\n\
    \n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n        EdgeInfo&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        bool\
    \ ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node, edge.v);\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    const T& get_edge(int edge_id) const {\n        return get(edge_node(edge_id));\n\
    \    }\n\n    void set_edge(int edge_id, const T& value) {\n        set(edge_node(edge_id),\
    \ value);\n    }\n\n    void set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id),\
    \ std::move(value));\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x,\
    \ int i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    // Returns the path\
    \ product from `u` to `v`. Internally calls `evert(u)`,\n    // so the represented\
    \ root may change.\n    T prod(int u, int v) {\n        check_vertex(u);\n   \
    \     check_vertex(v);\n        assert(connected(u, v));\n        evert(u);\n\
    \        access(v);\n        return _nodes[v].prod;\n    }\n\n    // Alias for\
    \ `prod(u, v)`. Internally calls `evert(u)`,\n    // so the represented root may\
    \ change.\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    // Returns the number of vertices on path `u`-`v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    int path_size(int u, int v) {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        return _nodes[v].size;\n\
    \    }\n\n    // Returns the `k`-th vertex on path `u`-`v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    int kth_vertex(int u, int v,\
    \ int k) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        assert(0 <= k && k < _nodes[v].size);\n\
    \n        int cur = v;\n        while (true) {\n            push(cur);\n     \
    \       int left_size = child_size(_nodes[cur].left);\n            if (k < left_size)\
    \ {\n                cur = _nodes[cur].left;\n            } else if (k == left_size)\
    \ {\n                splay(cur);\n                return cur;\n            } else\
    \ {\n                k -= left_size + 1;\n                cur = _nodes[cur].right;\n\
    \            }\n        }\n    }\n\n    int lca(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (!connected(u, v)) return -1;\n        if\
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n\n\
    \    // Returns the aggregate of `v`'s subtree when the represented tree is rooted\
    \ at `root`.\n    // Internally calls `evert(root)`, so the represented root may\
    \ change.\n    T subtree_prod(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(connected(root, v));\n        evert(root);\n\
    \        access(v);\n        return node_subtree_prod(v);\n    }\n\n    // Returns\
    \ the aggregate of `v`'s subtree with respect to the current represented root.\n\
    \    T subtree_prod(int v) {\n        check_vertex(v);\n        access(v);\n \
    \       return node_subtree_prod(v);\n    }\n\n    // Returns the size of `v`'s\
    \ subtree when the represented tree is rooted at `root`.\n    // Internally calls\
    \ `evert(root)`, so the represented root may change.\n    int subtree_size(int\
    \ root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n    \
    \    assert(connected(root, v));\n        evert(root);\n        access(v);\n \
    \       return node_subtree_size(v);\n    }\n\n    // Returns the size of `v`'s\
    \ subtree with respect to the current represented root.\n    int subtree_size(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        return node_subtree_size(v);\n\
    \    }\n\n    // Returns the aggregate of the whole connected component containing\
    \ `v`.\n    T component_prod(int v) {\n        int r = root(v);\n        return\
    \ subtree_prod(r, r);\n    }\n\n    // Returns the number of vertices in the connected\
    \ component containing `v`.\n    int component_size(int v) {\n        int r =\
    \ root(v);\n        return subtree_size(r, r);\n    }\n\n    // Returns the child\
    \ of `root` that lies on path `root`-`v`.\n    int child_toward(int root, int\
    \ v) {\n        check_vertex(root);\n        check_vertex(v);\n        assert(root\
    \ != v);\n        assert(connected(root, v));\n        return kth_vertex(root,\
    \ v, 1);\n    }\n\n    // Returns the aggregate of the entire branch of `root`\
    \ that contains `v`.\n    T branch_prod(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(root != v);\n        int child = child_toward(root,\
    \ v);\n        return subtree_prod(root, child);\n    }\n\n    // Returns the\
    \ size of the entire branch of `root` that contains `v`.\n    int branch_size(int\
    \ root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n    \
    \    assert(root != v);\n        int child = child_toward(root, v);\n        return\
    \ subtree_size(root, child);\n    }\n\n    // Returns the parent of `v` when rooted\
    \ at `root`, or `-1` if `v == root`.\n    int parent(int root, int v) {\n    \
    \    check_vertex(root);\n        check_vertex(v);\n        if (root == v) return\
    \ -1;\n        assert(connected(root, v));\n        int d = path_size(root, v);\n\
    \        assert(2 <= d);\n        return kth_vertex(root, v, d - 2);\n    }\n\n\
    \    // Returns `v`'s rooted subtree aggregate excluding the child-side subtree.\n\
    \    T subtree_prod_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        T whole = subtree_prod(root, v);\n        T sub = subtree_prod(root,\
    \ child);\n        return Group::op(whole, Group::inv(sub));\n    }\n\n    //\
    \ Returns `v`'s rooted subtree size excluding the child-side subtree.\n    int\
    \ subtree_size_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        return subtree_size(root, v) - subtree_size(root, child);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/dynamic_connectivity/online_dynamic_connectivity.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct OnlineDynamicConnectivity {\n\
    \   private:\n    using Forest = LinkCutTree<m1une::monoid::Add<int>>;\n\n   \
    \ struct Edge {\n        int u;\n        int v;\n        bool alive;\n       \
    \ bool tree;\n        int previous_u = -1;\n        int next_u = -1;\n       \
    \ int previous_v = -1;\n        int next_v = -1;\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    int _active_edge_count = 0;\n    Forest _forest;\n  \
    \  std::vector<Edge> _edges;\n    std::vector<int> _tree_head;\n    std::vector<int>\
    \ _non_tree_head;\n    std::vector<std::uint32_t> _visited;\n    std::vector<std::uint32_t>\
    \ _edge_visited;\n    std::uint32_t _visit_token = 0;\n    std::vector<int> _stack;\n\
    \    std::vector<int> _component;\n\n    int endpoint_side(const Edge& edge, int\
    \ v) const {\n        return edge.u == v ? 0 : 1;\n    }\n\n    int& previous(Edge&\
    \ edge, int side) {\n        return side == 0 ? edge.previous_u : edge.previous_v;\n\
    \    }\n\n    int& next(Edge& edge, int side) {\n        return side == 0 ? edge.next_u\
    \ : edge.next_v;\n    }\n\n    int next(const Edge& edge, int side) const {\n\
    \        return side == 0 ? edge.next_u : edge.next_v;\n    }\n\n    void insert_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int old_head = head[v];\n        previous(edge, side) = -1;\n       \
    \ next(edge, side) = old_head;\n        if (old_head != -1) {\n            Edge&\
    \ old_edge = _edges[old_head];\n            previous(old_edge, endpoint_side(old_edge,\
    \ v)) = edge_id;\n        }\n        head[v] = edge_id;\n    }\n\n    void erase_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int previous_id = previous(edge, side);\n        int next_id = next(edge,\
    \ side);\n        if (previous_id == -1) {\n            head[v] = next_id;\n \
    \       } else {\n            Edge& previous_edge = _edges[previous_id];\n   \
    \         next(previous_edge, endpoint_side(previous_edge, v)) = next_id;\n  \
    \      }\n        if (next_id != -1) {\n            Edge& next_edge = _edges[next_id];\n\
    \            previous(next_edge, endpoint_side(next_edge, v)) = previous_id;\n\
    \        }\n        previous(edge, side) = -1;\n        next(edge, side) = -1;\n\
    \    }\n\n    void insert_incident(std::vector<int>& head, int edge_id) {\n  \
    \      const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n        int\
    \ v = edge.v;\n        insert_one(head, edge_id, u, 0);\n        if (u != v) insert_one(head,\
    \ edge_id, v, 1);\n    }\n\n    void erase_incident(std::vector<int>& head, int\
    \ edge_id) {\n        const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n\
    \        int v = edge.v;\n        erase_one(head, edge_id, u, 0);\n        if\
    \ (u != v) erase_one(head, edge_id, v, 1);\n    }\n\n    void make_tree_edge(int\
    \ edge_id) {\n        Edge& edge = _edges[edge_id];\n        assert(edge.alive\
    \ && !edge.tree && edge.u != edge.v);\n        erase_incident(_non_tree_head,\
    \ edge_id);\n        bool linked = _forest.link(edge.u, edge.v);\n        assert(linked);\n\
    \        edge.tree = true;\n        insert_incident(_tree_head, edge_id);\n  \
    \      _component_count--;\n    }\n\n    void collect_component(int start) {\n\
    \        _visit_token++;\n        if (_visit_token == 0) {\n            std::fill(_visited.begin(),\
    \ _visited.end(), 0);\n            std::fill(_edge_visited.begin(), _edge_visited.end(),\
    \ 0);\n            _visit_token = 1;\n        }\n        _stack.clear();\n   \
    \     _component.clear();\n        _visited[start] = _visit_token;\n        _stack.push_back(start);\n\
    \        while (!_stack.empty()) {\n            int v = _stack.back();\n     \
    \       _stack.pop_back();\n            _component.push_back(v);\n           \
    \ for (int edge_id = _tree_head[v]; edge_id != -1;) {\n                const Edge&\
    \ edge = _edges[edge_id];\n                int edge_side = endpoint_side(edge,\
    \ v);\n                edge_id = next(edge, edge_side);\n                int to\
    \ = edge.u ^ edge.v ^ v;\n                if (_visited[to] == _visit_token) continue;\n\
    \                _visited[to] = _visit_token;\n                _stack.push_back(to);\n\
    \            }\n        }\n    }\n\n    void reconnect(int u, int v) {\n     \
    \   int start = _forest.component_size(u) <= _forest.component_size(v) ? u : v;\n\
    \        collect_component(start);\n        int replacement = -1;\n        for\
    \ (int x : _component) {\n            for (int edge_id = _non_tree_head[x]; edge_id\
    \ != -1;) {\n                const Edge& edge = _edges[edge_id];\n           \
    \     int edge_side = endpoint_side(edge, x);\n                int current_edge\
    \ = edge_id;\n                edge_id = next(edge, edge_side);\n             \
    \   if (_edge_visited[current_edge] == _visit_token) continue;\n             \
    \   _edge_visited[current_edge] = _visit_token;\n                if (_visited[edge.u]\
    \ != _visit_token || _visited[edge.v] != _visit_token) {\n                   \
    \ replacement = current_edge;\n                    break;\n                }\n\
    \            }\n            if (replacement != -1) break;\n        }\n       \
    \ if (replacement != -1) make_tree_edge(replacement);\n    }\n\n   public:\n \
    \   OnlineDynamicConnectivity() : OnlineDynamicConnectivity(0) {}\n\n    explicit\
    \ OnlineDynamicConnectivity(int n)\n        : _n(n),\n          _component_count(n),\n\
    \          _forest(n),\n          _tree_head(n, -1),\n          _non_tree_head(n,\
    \ -1),\n          _visited(n, 0) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int active_edge_count() const\
    \ {\n        return _active_edge_count;\n    }\n\n    int component_count() const\
    \ {\n        return _component_count;\n    }\n\n    void reserve_edges(int count)\
    \ {\n        assert(0 <= count);\n        _edges.reserve(count);\n        _edge_visited.reserve(count);\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n        return _edges[edge_id].alive;\n \
    \   }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n       \
    \ assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return {_edges[edge_id].u,\
    \ _edges[edge_id].v};\n    }\n\n    bool connected(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        return _forest.connected(u,\
    \ v);\n    }\n\n    bool same(int u, int v) {\n        return connected(u, v);\n\
    \    }\n\n    int component_size(int v) {\n        assert(0 <= v && v < _n);\n\
    \        return _forest.component_size(v);\n    }\n\n    int add_edge(int u, int\
    \ v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        bool is_tree = u != v && _forest.link(u, v);\n        int edge_id = int(_edges.size());\n\
    \        Edge edge;\n        edge.u = u;\n        edge.v = v;\n        edge.alive\
    \ = true;\n        edge.tree = is_tree;\n        _edges.push_back(edge);\n   \
    \     _edge_visited.push_back(0);\n        _active_edge_count++;\n        if (is_tree)\
    \ {\n            insert_incident(_tree_head, edge_id);\n            _component_count--;\n\
    \        } else {\n            insert_incident(_non_tree_head, edge_id);\n   \
    \     }\n        return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n\
    \        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        Edge&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        edge.alive\
    \ = false;\n        _active_edge_count--;\n        if (!edge.tree) {\n       \
    \     erase_incident(_non_tree_head, edge_id);\n            return true;\n   \
    \     }\n\n        erase_incident(_tree_head, edge_id);\n        bool cut = _forest.cut(edge.u,\
    \ edge.v);\n        assert(cut);\n        _component_count++;\n        reconnect(edge.u,\
    \ edge.v);\n        return true;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP\n#define M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../../monoid/add.hpp\"\n#include\
    \ \"../dynamic_tree/link_cut_tree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \nstruct OnlineDynamicConnectivity {\n   private:\n    using Forest = LinkCutTree<m1une::monoid::Add<int>>;\n\
    \n    struct Edge {\n        int u;\n        int v;\n        bool alive;\n   \
    \     bool tree;\n        int previous_u = -1;\n        int next_u = -1;\n   \
    \     int previous_v = -1;\n        int next_v = -1;\n    };\n\n    int _n;\n\
    \    int _component_count;\n    int _active_edge_count = 0;\n    Forest _forest;\n\
    \    std::vector<Edge> _edges;\n    std::vector<int> _tree_head;\n    std::vector<int>\
    \ _non_tree_head;\n    std::vector<std::uint32_t> _visited;\n    std::vector<std::uint32_t>\
    \ _edge_visited;\n    std::uint32_t _visit_token = 0;\n    std::vector<int> _stack;\n\
    \    std::vector<int> _component;\n\n    int endpoint_side(const Edge& edge, int\
    \ v) const {\n        return edge.u == v ? 0 : 1;\n    }\n\n    int& previous(Edge&\
    \ edge, int side) {\n        return side == 0 ? edge.previous_u : edge.previous_v;\n\
    \    }\n\n    int& next(Edge& edge, int side) {\n        return side == 0 ? edge.next_u\
    \ : edge.next_v;\n    }\n\n    int next(const Edge& edge, int side) const {\n\
    \        return side == 0 ? edge.next_u : edge.next_v;\n    }\n\n    void insert_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int old_head = head[v];\n        previous(edge, side) = -1;\n       \
    \ next(edge, side) = old_head;\n        if (old_head != -1) {\n            Edge&\
    \ old_edge = _edges[old_head];\n            previous(old_edge, endpoint_side(old_edge,\
    \ v)) = edge_id;\n        }\n        head[v] = edge_id;\n    }\n\n    void erase_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int previous_id = previous(edge, side);\n        int next_id = next(edge,\
    \ side);\n        if (previous_id == -1) {\n            head[v] = next_id;\n \
    \       } else {\n            Edge& previous_edge = _edges[previous_id];\n   \
    \         next(previous_edge, endpoint_side(previous_edge, v)) = next_id;\n  \
    \      }\n        if (next_id != -1) {\n            Edge& next_edge = _edges[next_id];\n\
    \            previous(next_edge, endpoint_side(next_edge, v)) = previous_id;\n\
    \        }\n        previous(edge, side) = -1;\n        next(edge, side) = -1;\n\
    \    }\n\n    void insert_incident(std::vector<int>& head, int edge_id) {\n  \
    \      const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n        int\
    \ v = edge.v;\n        insert_one(head, edge_id, u, 0);\n        if (u != v) insert_one(head,\
    \ edge_id, v, 1);\n    }\n\n    void erase_incident(std::vector<int>& head, int\
    \ edge_id) {\n        const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n\
    \        int v = edge.v;\n        erase_one(head, edge_id, u, 0);\n        if\
    \ (u != v) erase_one(head, edge_id, v, 1);\n    }\n\n    void make_tree_edge(int\
    \ edge_id) {\n        Edge& edge = _edges[edge_id];\n        assert(edge.alive\
    \ && !edge.tree && edge.u != edge.v);\n        erase_incident(_non_tree_head,\
    \ edge_id);\n        bool linked = _forest.link(edge.u, edge.v);\n        assert(linked);\n\
    \        edge.tree = true;\n        insert_incident(_tree_head, edge_id);\n  \
    \      _component_count--;\n    }\n\n    void collect_component(int start) {\n\
    \        _visit_token++;\n        if (_visit_token == 0) {\n            std::fill(_visited.begin(),\
    \ _visited.end(), 0);\n            std::fill(_edge_visited.begin(), _edge_visited.end(),\
    \ 0);\n            _visit_token = 1;\n        }\n        _stack.clear();\n   \
    \     _component.clear();\n        _visited[start] = _visit_token;\n        _stack.push_back(start);\n\
    \        while (!_stack.empty()) {\n            int v = _stack.back();\n     \
    \       _stack.pop_back();\n            _component.push_back(v);\n           \
    \ for (int edge_id = _tree_head[v]; edge_id != -1;) {\n                const Edge&\
    \ edge = _edges[edge_id];\n                int edge_side = endpoint_side(edge,\
    \ v);\n                edge_id = next(edge, edge_side);\n                int to\
    \ = edge.u ^ edge.v ^ v;\n                if (_visited[to] == _visit_token) continue;\n\
    \                _visited[to] = _visit_token;\n                _stack.push_back(to);\n\
    \            }\n        }\n    }\n\n    void reconnect(int u, int v) {\n     \
    \   int start = _forest.component_size(u) <= _forest.component_size(v) ? u : v;\n\
    \        collect_component(start);\n        int replacement = -1;\n        for\
    \ (int x : _component) {\n            for (int edge_id = _non_tree_head[x]; edge_id\
    \ != -1;) {\n                const Edge& edge = _edges[edge_id];\n           \
    \     int edge_side = endpoint_side(edge, x);\n                int current_edge\
    \ = edge_id;\n                edge_id = next(edge, edge_side);\n             \
    \   if (_edge_visited[current_edge] == _visit_token) continue;\n             \
    \   _edge_visited[current_edge] = _visit_token;\n                if (_visited[edge.u]\
    \ != _visit_token || _visited[edge.v] != _visit_token) {\n                   \
    \ replacement = current_edge;\n                    break;\n                }\n\
    \            }\n            if (replacement != -1) break;\n        }\n       \
    \ if (replacement != -1) make_tree_edge(replacement);\n    }\n\n   public:\n \
    \   OnlineDynamicConnectivity() : OnlineDynamicConnectivity(0) {}\n\n    explicit\
    \ OnlineDynamicConnectivity(int n)\n        : _n(n),\n          _component_count(n),\n\
    \          _forest(n),\n          _tree_head(n, -1),\n          _non_tree_head(n,\
    \ -1),\n          _visited(n, 0) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int active_edge_count() const\
    \ {\n        return _active_edge_count;\n    }\n\n    int component_count() const\
    \ {\n        return _component_count;\n    }\n\n    void reserve_edges(int count)\
    \ {\n        assert(0 <= count);\n        _edges.reserve(count);\n        _edge_visited.reserve(count);\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n        return _edges[edge_id].alive;\n \
    \   }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n       \
    \ assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return {_edges[edge_id].u,\
    \ _edges[edge_id].v};\n    }\n\n    bool connected(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        return _forest.connected(u,\
    \ v);\n    }\n\n    bool same(int u, int v) {\n        return connected(u, v);\n\
    \    }\n\n    int component_size(int v) {\n        assert(0 <= v && v < _n);\n\
    \        return _forest.component_size(v);\n    }\n\n    int add_edge(int u, int\
    \ v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        bool is_tree = u != v && _forest.link(u, v);\n        int edge_id = int(_edges.size());\n\
    \        Edge edge;\n        edge.u = u;\n        edge.v = v;\n        edge.alive\
    \ = true;\n        edge.tree = is_tree;\n        _edges.push_back(edge);\n   \
    \     _edge_visited.push_back(0);\n        _active_edge_count++;\n        if (is_tree)\
    \ {\n            insert_incident(_tree_head, edge_id);\n            _component_count--;\n\
    \        } else {\n            insert_incident(_non_tree_head, edge_id);\n   \
    \     }\n        return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n\
    \        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        Edge&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        edge.alive\
    \ = false;\n        _active_edge_count--;\n        if (!edge.tree) {\n       \
    \     erase_incident(_non_tree_head, edge_id);\n            return true;\n   \
    \     }\n\n        erase_incident(_tree_head, edge_id);\n        bool cut = _forest.cut(edge.u,\
    \ edge.v);\n        assert(cut);\n        _component_count++;\n        reconnect(edge.u,\
    \ edge.v);\n        return true;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP\n"
  dependsOn:
  - monoid/add.hpp
  - ds/dynamic_tree/link_cut_tree.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/dynamic_connectivity/online_dynamic_connectivity.hpp
  requiredBy:
  - ds/dynamic_connectivity/all.hpp
  timestamp: '2026-06-23 11:30:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
documentation_of: ds/dynamic_connectivity/online_dynamic_connectivity.hpp
layout: document
title: Online Dynamic Connectivity
---

## Overview

`OnlineDynamicConnectivity` maintains connectivity in an undirected multigraph
while edges are inserted and erased. Every operation is processed immediately;
the complete operation sequence does not need to be known in advance.

The structure maintains a spanning forest with a link-cut tree. Non-tree edges
are stored in intrusive per-vertex lists, so insertion, deletion, and promotion
between edge classes do not allocate or perform balanced-tree operations. When
a tree edge is erased, it enumerates the smaller resulting tree and searches
its incident non-tree edges for a replacement.

Parallel edges and self-loops are supported. Edges are erased by the id returned
from `add_edge`, so parallel copies remain distinct.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `OnlineDynamicConnectivity()` | Creates an empty graph. | `O(1)` |
| `OnlineDynamicConnectivity(int n)` | Creates `n` isolated vertices. | `O(N)` |
| `int size() const` | Returns the number of vertices. | `O(1)` |
| `int edge_count() const` | Returns the number of edge ids ever created. | `O(1)` |
| `int active_edge_count() const` | Returns the number of currently active edges. | `O(1)` |
| `int component_count() const` | Returns the current number of connected components. | `O(1)` |
| `void reserve_edges(int count)` | Reserves storage for edge ids. | `O(M)` when reallocation occurs |
| `bool edge_alive(int id) const` | Returns whether edge `id` is active. | `O(1)` |
| `pair<int, int> edge_endpoints(int id) const` | Returns the endpoints of edge `id`. | `O(1)` |
| `bool connected(int u, int v)` | Returns whether `u` and `v` are connected. | Amortized `O(log N)` |
| `bool same(int u, int v)` | Alias for `connected`. | Amortized `O(log N)` |
| `int component_size(int v)` | Returns the number of vertices in `v`'s component. | Amortized `O(log N)` |
| `int add_edge(int u, int v)` | Inserts an edge and returns its id. | Amortized `O(log N)` |
| `bool erase_edge(int id)` | Erases an active edge. Returns false if it was already erased. | See below |

Deleting a non-tree edge costs logarithmic set maintenance. If a tree edge is
deleted, let `S` be the smaller resulting component and let `I` be the number
of non-tree-edge incidences touching vertices of `S`. Replacement search costs
`O(|S| + I + log N)`.

This deterministic strategy is compact and fast for typical sparse competitive
programming workloads. When all operations are known beforehand, prefer
`OfflineDynamicConnectivity`, whose deletion handling has a stronger batch
bound.

## Example

```cpp
#include "ds/dynamic_connectivity/online_dynamic_connectivity.hpp"
#include <iostream>

int main() {
    m1une::ds::OnlineDynamicConnectivity graph(4);
    int e01 = graph.add_edge(0, 1);
    int e12 = graph.add_edge(1, 2);
    int e02 = graph.add_edge(0, 2);

    std::cout << graph.connected(0, 2) << '\n';  // 1
    graph.erase_edge(e12);
    std::cout << graph.connected(0, 2) << '\n';  // 1, through e02
    graph.erase_edge(e02);
    std::cout << graph.connected(0, 2) << '\n';  // 0

    graph.erase_edge(e01);
}
```
