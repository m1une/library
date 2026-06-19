---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_link_cut_tree.test.cpp
    title: verify/data_structure/lazy_link_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/lazy_link_cut_tree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 11 \"data_structure/lazy_link_cut_tree.hpp\"\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <m1une::acted_monoid::IsCommutativeActedGroup\
    \ ActedGroup>\nstruct LazyLinkCutTree {\n    using T = typename ActedGroup::value_type;\n\
    \    using F = typename ActedGroup::operator_type;\n\n   private:\n    struct\
    \ Node {\n        int left = -1;\n        int right = -1;\n        int parent\
    \ = -1;\n        bool rev = false;\n        int size = 1;\n        int virtual_size\
    \ = 0;\n        int rake_size = 0;\n        int all_size = 1;\n        T value\
    \ = ActedGroup::id();\n        T prod = ActedGroup::id();\n        T rev_prod\
    \ = ActedGroup::id();\n        T virtual_prod = ActedGroup::id();\n        T rake_prod\
    \ = ActedGroup::id();\n        T all_prod = ActedGroup::id();\n        F lazy\
    \ = ActedGroup::op_id();\n    };\n\n    struct EdgeInfo {\n        int u = -1;\n\
    \        int v = -1;\n        int node = -1;\n        bool alive = false;\n  \
    \  };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo> _edges;\n  \
    \  std::vector<int> _path_buffer;\n\n    static T make_node_value(const T& value,\
    \ int) {\n        return value;\n    }\n\n    static T make_node_value(T&& value,\
    \ int) {\n        return std::move(value);\n    }\n\n    template <class U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedGroup::make(x);\
    \ } ||\n        requires(U x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { ActedGroup::make(x); }) {\n            return\
    \ ActedGroup::make(value);\n        } else if constexpr (requires(U x, int i)\
    \ { ActedGroup::make(x, i); }) {\n            return ActedGroup::make(value, index);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    int child_size(int node) const {\n        return node == -1 ? 0 : _nodes[node].size;\n\
    \    }\n\n    int child_all_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].all_size;\n    }\n\n    int child_rake_size(int node) const\
    \ {\n        return node == -1 ? 0 : _nodes[node].rake_size;\n    }\n\n    T child_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].prod;\n\
    \    }\n\n    T child_rev_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rev_prod;\n    }\n\n    T child_all_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].all_prod;\n\
    \    }\n\n    T child_rake_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rake_prod;\n    }\n\n    T node_subtree_prod(int\
    \ node) const {\n        const Node& x = _nodes[node];\n        return ActedGroup::op(x.value,\
    \ x.virtual_prod);\n    }\n\n    int node_subtree_size(int node) const {\n   \
    \     return 1 + _nodes[node].virtual_size;\n    }\n\n    bool is_splay_root(int\
    \ node) const {\n        int parent = _nodes[node].parent;\n        return parent\
    \ == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);\n  \
    \  }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n       \
    \ x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.rake_size\
    \ = x.virtual_size + child_rake_size(x.left) + child_rake_size(x.right);\n   \
    \     x.all_size = x.size + x.rake_size;\n        x.prod = ActedGroup::op(ActedGroup::op(child_prod(x.left),\
    \ x.value), child_prod(x.right));\n        x.rev_prod = ActedGroup::op(ActedGroup::op(child_rev_prod(x.right),\
    \ x.value), child_rev_prod(x.left));\n        x.rake_prod = ActedGroup::op(ActedGroup::op(child_rake_prod(x.left),\
    \ x.virtual_prod),\n                                      child_rake_prod(x.right));\n\
    \        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n    }\n\n    void\
    \ add_virtual_child(int node, int child) {\n        if (child == -1) return;\n\
    \        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, ActedGroup::inv(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ apply_operator(int node, const F& f) {\n        if (node == -1) return;\n  \
    \      Node& x = _nodes[node];\n        x.value = ActedGroup::mapping(f, x.value);\n\
    \        x.prod = ActedGroup::mapping(f, x.prod);\n        x.rev_prod = ActedGroup::mapping(f,\
    \ x.rev_prod);\n        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n  \
    \      x.lazy = ActedGroup::op_comp(f, x.lazy);\n    }\n\n    void push(int node)\
    \ {\n        if (node == -1) return;\n        Node& x = _nodes[node];\n      \
    \  if (x.rev) {\n            apply_reverse(x.left);\n            apply_reverse(x.right);\n\
    \            x.rev = false;\n        }\n        apply_operator(x.left, x.lazy);\n\
    \        apply_operator(x.right, x.lazy);\n        x.lazy = ActedGroup::op_id();\n\
    \    }\n\n    void push_to(int node) {\n        _path_buffer.clear();\n      \
    \  int cur = node;\n        _path_buffer.push_back(cur);\n        while (!is_splay_root(cur))\
    \ {\n            cur = _nodes[cur].parent;\n            _path_buffer.push_back(cur);\n\
    \        }\n        for (int i = int(_path_buffer.size()) - 1; i >= 0; i--) push(_path_buffer[i]);\n\
    \    }\n\n    void rotate(int node) {\n        int parent = _nodes[node].parent;\n\
    \        int grand = _nodes[parent].parent;\n        bool is_right = _nodes[parent].right\
    \ == node;\n        int middle = is_right ? _nodes[node].left : _nodes[node].right;\n\
    \n        if (!is_splay_root(parent)) {\n            if (_nodes[grand].left ==\
    \ parent) {\n                _nodes[grand].left = node;\n            } else {\n\
    \                _nodes[grand].right = node;\n            }\n        }\n     \
    \   _nodes[node].parent = grand;\n\n        if (is_right) {\n            _nodes[node].left\
    \ = parent;\n            _nodes[parent].right = middle;\n        } else {\n  \
    \          _nodes[node].right = parent;\n            _nodes[parent].left = middle;\n\
    \        }\n        if (middle != -1) _nodes[middle].parent = parent;\n      \
    \  _nodes[parent].parent = node;\n\n        update(parent);\n        update(node);\n\
    \    }\n\n    void splay(int node) {\n        push_to(node);\n        while (!is_splay_root(node))\
    \ {\n            int parent = _nodes[node].parent;\n            int grand = _nodes[parent].parent;\n\
    \            if (!is_splay_root(parent)) {\n                bool zig_zig = (_nodes[parent].left\
    \ == node) == (_nodes[grand].left == parent);\n                rotate(zig_zig\
    \ ? parent : node);\n            }\n            rotate(node);\n        }\n   \
    \ }\n\n    int access(int node) {\n        int last = -1;\n        for (int cur\
    \ = node; cur != -1; cur = _nodes[cur].parent) {\n            splay(cur);\n  \
    \          add_virtual_child(cur, _nodes[cur].right);\n            remove_virtual_child(cur,\
    \ last);\n            _nodes[cur].right = last;\n            if (last != -1) _nodes[last].parent\
    \ = cur;\n            update(cur);\n            last = cur;\n        }\n     \
    \   splay(node);\n        return last;\n    }\n\n    void check_vertex(int v)\
    \ const {\n        assert(0 <= v && v < int(_nodes.size()));\n    }\n\n    void\
    \ check_edge(int edge_id) const {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n\
    \    }\n\n   public:\n    LazyLinkCutTree() = default;\n\n    explicit LazyLinkCutTree(int\
    \ n) {\n        assert(0 <= n);\n        _nodes.reserve(n);\n        for (int\
    \ i = 0; i < n; i++) add_vertex();\n    }\n\n    explicit LazyLinkCutTree(const\
    \ std::vector<T>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n    }\n\n \
    \   explicit LazyLinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   explicit LazyLinkCutTree(const std::vector<U>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = ActedGroup::id()) {\n        Node node;\n\
    \        node.value = value;\n        node.prod = value;\n        node.rev_prod\
    \ = value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
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
    \ && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        set(v, make_node_value(value,\
    \ v));\n    }\n\n    // Applies `f` to one vertex.\n    void apply(int v, const\
    \ F& f) {\n        check_vertex(v);\n        access(v);\n        _nodes[v].value\
    \ = ActedGroup::mapping(f, _nodes[v].value);\n        update(v);\n    }\n\n  \
    \  // Applies `f` to the path from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    void apply(int u, int v, const\
    \ F& f) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        apply_operator(v, f);\n\
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
    \ = ActedGroup::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
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
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   int link_edge(int u, int v, const U& value) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v || connected(u, v)) return -1;\n\
    \        return link_edge(u, v, make_node_value(value, size()));\n    }\n\n  \
    \  // Cuts edge `(u, v)`. Internally calls `evert(u)`, so the represented root\
    \ may change.\n    bool cut(int u, int v) {\n        check_vertex(u);\n      \
    \  check_vertex(v);\n        if (u == v) return false;\n        evert(u);\n  \
    \      access(v);\n        if (_nodes[v].left != u || _nodes[u].right != -1) return\
    \ false;\n        _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n     \
    \   update(v);\n        return true;\n    }\n\n    // Cuts the parent edge of\
    \ `v` in the current represented-root orientation.\n    // Unlike `cut(u, v)`,\
    \ this does not call `evert`.\n    bool cut_parent(int v) {\n        check_vertex(v);\n\
    \        access(v);\n        int left = _nodes[v].left;\n        if (left == -1)\
    \ return false;\n        _nodes[v].left = -1;\n        _nodes[left].parent = -1;\n\
    \        update(v);\n        return true;\n    }\n\n    bool cut_edge(int edge_id)\
    \ {\n        check_edge(edge_id);\n        EdgeInfo& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        bool ok1 = cut(edge.u, edge.node);\n\
    \        bool ok2 = cut(edge.node, edge.v);\n        if (ok1 && ok2) edge.alive\
    \ = false;\n        return ok1 && ok2;\n    }\n\n    T get_edge(int edge_id) {\n\
    \        return get(edge_node(edge_id));\n    }\n\n    void set_edge(int edge_id,\
    \ const T& value) {\n        set(edge_node(edge_id), value);\n    }\n\n    void\
    \ set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id), std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    void apply_edge(int\
    \ edge_id, const F& f) {\n        apply(edge_node(edge_id), f);\n    }\n\n   \
    \ // Returns the path product from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    T prod(int u, int v) {\n    \
    \    check_vertex(u);\n        check_vertex(v);\n        assert(connected(u, v));\n\
    \        evert(u);\n        access(v);\n        return _nodes[v].prod;\n    }\n\
    \n    // Alias for `prod(u, v)`. Internally calls `evert(u)`,\n    // so the represented\
    \ root may change.\n    T path_prod(int u, int v) {\n        return prod(u, v);\n\
    \    }\n\n    // Returns the number of vertices on path `u`-`v`. Internally calls\
    \ `evert(u)`,\n    // so the represented root may change.\n    int path_size(int\
    \ u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
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
    \ child);\n        return ActedGroup::op(whole, ActedGroup::inv(sub));\n    }\n\
    \n    // Returns `v`'s rooted subtree size excluding the child-side subtree.\n\
    \    int subtree_size_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        return subtree_size(root, v) - subtree_size(root, child);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_LAZY_LINK_CUT_TREE_HPP\n#define M1UNE_LAZY_LINK_CUT_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"acted_monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace data_structure {\n\ntemplate <m1une::acted_monoid::IsCommutativeActedGroup\
    \ ActedGroup>\nstruct LazyLinkCutTree {\n    using T = typename ActedGroup::value_type;\n\
    \    using F = typename ActedGroup::operator_type;\n\n   private:\n    struct\
    \ Node {\n        int left = -1;\n        int right = -1;\n        int parent\
    \ = -1;\n        bool rev = false;\n        int size = 1;\n        int virtual_size\
    \ = 0;\n        int rake_size = 0;\n        int all_size = 1;\n        T value\
    \ = ActedGroup::id();\n        T prod = ActedGroup::id();\n        T rev_prod\
    \ = ActedGroup::id();\n        T virtual_prod = ActedGroup::id();\n        T rake_prod\
    \ = ActedGroup::id();\n        T all_prod = ActedGroup::id();\n        F lazy\
    \ = ActedGroup::op_id();\n    };\n\n    struct EdgeInfo {\n        int u = -1;\n\
    \        int v = -1;\n        int node = -1;\n        bool alive = false;\n  \
    \  };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo> _edges;\n  \
    \  std::vector<int> _path_buffer;\n\n    static T make_node_value(const T& value,\
    \ int) {\n        return value;\n    }\n\n    static T make_node_value(T&& value,\
    \ int) {\n        return std::move(value);\n    }\n\n    template <class U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedGroup::make(x);\
    \ } ||\n        requires(U x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { ActedGroup::make(x); }) {\n            return\
    \ ActedGroup::make(value);\n        } else if constexpr (requires(U x, int i)\
    \ { ActedGroup::make(x, i); }) {\n            return ActedGroup::make(value, index);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    int child_size(int node) const {\n        return node == -1 ? 0 : _nodes[node].size;\n\
    \    }\n\n    int child_all_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].all_size;\n    }\n\n    int child_rake_size(int node) const\
    \ {\n        return node == -1 ? 0 : _nodes[node].rake_size;\n    }\n\n    T child_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].prod;\n\
    \    }\n\n    T child_rev_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rev_prod;\n    }\n\n    T child_all_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].all_prod;\n\
    \    }\n\n    T child_rake_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rake_prod;\n    }\n\n    T node_subtree_prod(int\
    \ node) const {\n        const Node& x = _nodes[node];\n        return ActedGroup::op(x.value,\
    \ x.virtual_prod);\n    }\n\n    int node_subtree_size(int node) const {\n   \
    \     return 1 + _nodes[node].virtual_size;\n    }\n\n    bool is_splay_root(int\
    \ node) const {\n        int parent = _nodes[node].parent;\n        return parent\
    \ == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);\n  \
    \  }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n       \
    \ x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.rake_size\
    \ = x.virtual_size + child_rake_size(x.left) + child_rake_size(x.right);\n   \
    \     x.all_size = x.size + x.rake_size;\n        x.prod = ActedGroup::op(ActedGroup::op(child_prod(x.left),\
    \ x.value), child_prod(x.right));\n        x.rev_prod = ActedGroup::op(ActedGroup::op(child_rev_prod(x.right),\
    \ x.value), child_rev_prod(x.left));\n        x.rake_prod = ActedGroup::op(ActedGroup::op(child_rake_prod(x.left),\
    \ x.virtual_prod),\n                                      child_rake_prod(x.right));\n\
    \        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n    }\n\n    void\
    \ add_virtual_child(int node, int child) {\n        if (child == -1) return;\n\
    \        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, ActedGroup::inv(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ apply_operator(int node, const F& f) {\n        if (node == -1) return;\n  \
    \      Node& x = _nodes[node];\n        x.value = ActedGroup::mapping(f, x.value);\n\
    \        x.prod = ActedGroup::mapping(f, x.prod);\n        x.rev_prod = ActedGroup::mapping(f,\
    \ x.rev_prod);\n        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n  \
    \      x.lazy = ActedGroup::op_comp(f, x.lazy);\n    }\n\n    void push(int node)\
    \ {\n        if (node == -1) return;\n        Node& x = _nodes[node];\n      \
    \  if (x.rev) {\n            apply_reverse(x.left);\n            apply_reverse(x.right);\n\
    \            x.rev = false;\n        }\n        apply_operator(x.left, x.lazy);\n\
    \        apply_operator(x.right, x.lazy);\n        x.lazy = ActedGroup::op_id();\n\
    \    }\n\n    void push_to(int node) {\n        _path_buffer.clear();\n      \
    \  int cur = node;\n        _path_buffer.push_back(cur);\n        while (!is_splay_root(cur))\
    \ {\n            cur = _nodes[cur].parent;\n            _path_buffer.push_back(cur);\n\
    \        }\n        for (int i = int(_path_buffer.size()) - 1; i >= 0; i--) push(_path_buffer[i]);\n\
    \    }\n\n    void rotate(int node) {\n        int parent = _nodes[node].parent;\n\
    \        int grand = _nodes[parent].parent;\n        bool is_right = _nodes[parent].right\
    \ == node;\n        int middle = is_right ? _nodes[node].left : _nodes[node].right;\n\
    \n        if (!is_splay_root(parent)) {\n            if (_nodes[grand].left ==\
    \ parent) {\n                _nodes[grand].left = node;\n            } else {\n\
    \                _nodes[grand].right = node;\n            }\n        }\n     \
    \   _nodes[node].parent = grand;\n\n        if (is_right) {\n            _nodes[node].left\
    \ = parent;\n            _nodes[parent].right = middle;\n        } else {\n  \
    \          _nodes[node].right = parent;\n            _nodes[parent].left = middle;\n\
    \        }\n        if (middle != -1) _nodes[middle].parent = parent;\n      \
    \  _nodes[parent].parent = node;\n\n        update(parent);\n        update(node);\n\
    \    }\n\n    void splay(int node) {\n        push_to(node);\n        while (!is_splay_root(node))\
    \ {\n            int parent = _nodes[node].parent;\n            int grand = _nodes[parent].parent;\n\
    \            if (!is_splay_root(parent)) {\n                bool zig_zig = (_nodes[parent].left\
    \ == node) == (_nodes[grand].left == parent);\n                rotate(zig_zig\
    \ ? parent : node);\n            }\n            rotate(node);\n        }\n   \
    \ }\n\n    int access(int node) {\n        int last = -1;\n        for (int cur\
    \ = node; cur != -1; cur = _nodes[cur].parent) {\n            splay(cur);\n  \
    \          add_virtual_child(cur, _nodes[cur].right);\n            remove_virtual_child(cur,\
    \ last);\n            _nodes[cur].right = last;\n            if (last != -1) _nodes[last].parent\
    \ = cur;\n            update(cur);\n            last = cur;\n        }\n     \
    \   splay(node);\n        return last;\n    }\n\n    void check_vertex(int v)\
    \ const {\n        assert(0 <= v && v < int(_nodes.size()));\n    }\n\n    void\
    \ check_edge(int edge_id) const {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n\
    \    }\n\n   public:\n    LazyLinkCutTree() = default;\n\n    explicit LazyLinkCutTree(int\
    \ n) {\n        assert(0 <= n);\n        _nodes.reserve(n);\n        for (int\
    \ i = 0; i < n; i++) add_vertex();\n    }\n\n    explicit LazyLinkCutTree(const\
    \ std::vector<T>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n    }\n\n \
    \   explicit LazyLinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   explicit LazyLinkCutTree(const std::vector<U>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = ActedGroup::id()) {\n        Node node;\n\
    \        node.value = value;\n        node.prod = value;\n        node.rev_prod\
    \ = value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
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
    \ && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        set(v, make_node_value(value,\
    \ v));\n    }\n\n    // Applies `f` to one vertex.\n    void apply(int v, const\
    \ F& f) {\n        check_vertex(v);\n        access(v);\n        _nodes[v].value\
    \ = ActedGroup::mapping(f, _nodes[v].value);\n        update(v);\n    }\n\n  \
    \  // Applies `f` to the path from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    void apply(int u, int v, const\
    \ F& f) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        apply_operator(v, f);\n\
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
    \ = ActedGroup::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
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
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   int link_edge(int u, int v, const U& value) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v || connected(u, v)) return -1;\n\
    \        return link_edge(u, v, make_node_value(value, size()));\n    }\n\n  \
    \  // Cuts edge `(u, v)`. Internally calls `evert(u)`, so the represented root\
    \ may change.\n    bool cut(int u, int v) {\n        check_vertex(u);\n      \
    \  check_vertex(v);\n        if (u == v) return false;\n        evert(u);\n  \
    \      access(v);\n        if (_nodes[v].left != u || _nodes[u].right != -1) return\
    \ false;\n        _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n     \
    \   update(v);\n        return true;\n    }\n\n    // Cuts the parent edge of\
    \ `v` in the current represented-root orientation.\n    // Unlike `cut(u, v)`,\
    \ this does not call `evert`.\n    bool cut_parent(int v) {\n        check_vertex(v);\n\
    \        access(v);\n        int left = _nodes[v].left;\n        if (left == -1)\
    \ return false;\n        _nodes[v].left = -1;\n        _nodes[left].parent = -1;\n\
    \        update(v);\n        return true;\n    }\n\n    bool cut_edge(int edge_id)\
    \ {\n        check_edge(edge_id);\n        EdgeInfo& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        bool ok1 = cut(edge.u, edge.node);\n\
    \        bool ok2 = cut(edge.node, edge.v);\n        if (ok1 && ok2) edge.alive\
    \ = false;\n        return ok1 && ok2;\n    }\n\n    T get_edge(int edge_id) {\n\
    \        return get(edge_node(edge_id));\n    }\n\n    void set_edge(int edge_id,\
    \ const T& value) {\n        set(edge_node(edge_id), value);\n    }\n\n    void\
    \ set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id), std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    void apply_edge(int\
    \ edge_id, const F& f) {\n        apply(edge_node(edge_id), f);\n    }\n\n   \
    \ // Returns the path product from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    T prod(int u, int v) {\n    \
    \    check_vertex(u);\n        check_vertex(v);\n        assert(connected(u, v));\n\
    \        evert(u);\n        access(v);\n        return _nodes[v].prod;\n    }\n\
    \n    // Alias for `prod(u, v)`. Internally calls `evert(u)`,\n    // so the represented\
    \ root may change.\n    T path_prod(int u, int v) {\n        return prod(u, v);\n\
    \    }\n\n    // Returns the number of vertices on path `u`-`v`. Internally calls\
    \ `evert(u)`,\n    // so the represented root may change.\n    int path_size(int\
    \ u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
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
    \ child);\n        return ActedGroup::op(whole, ActedGroup::inv(sub));\n    }\n\
    \n    // Returns `v`'s rooted subtree size excluding the child-side subtree.\n\
    \    int subtree_size_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        return subtree_size(root, v) - subtree_size(root, child);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_LAZY_LINK_CUT_TREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/lazy_link_cut_tree.hpp
  requiredBy: []
  timestamp: '2026-06-18 03:38:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/lazy_link_cut_tree.test.cpp
documentation_of: data_structure/lazy_link_cut_tree.hpp
layout: document
title: Lazy Link-Cut Tree
---

## Overview

`m1une::data_structure::LazyLinkCutTree<ActedGroup>` maintains a dynamic
forest. It supports linking two trees, cutting edges, rerooting represented
trees, querying path products, applying lazy updates on paths, and querying
rooted subtree products and sizes.

The value is stored on link-cut-tree vertices. If you need edge values, create
one extra link-cut-tree vertex for each original edge and connect it between the
two endpoints. The `link_edge` helper does this for you.

The values must form a commutative group. The structure keeps a cached aggregate
of virtual child subtrees, while path lazy propagation updates only
preferred-path vertices. Path operations and subtree queries are amortized
$O(\log N)$.

## Template Parameter

`ActedGroup` must satisfy
`m1une::acted_monoid::IsCommutativeActedGroup`:

```cpp
struct AG {
    using value_type = T;
    using operator_type = F;

    static T id();
    static T op(const T& a, const T& b);
    static T inv(const T& x);

    static F op_id();
    static F op_comp(const F& f, const F& g);

    static T mapping(const F& f, const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inv(x)` must satisfy `op(x, inv(x)) == id()`. As with
`LazyPathLinkCutTree`, `mapping` must distribute over `op`.

## Construction

```cpp
LazyLinkCutTree<ActedGroup> lct;
LazyLinkCutTree<ActedGroup> lct(n);
LazyLinkCutTree<ActedGroup> lct(values);
```

* `LazyLinkCutTree(n)` creates `n` isolated vertices initialized with
  `ActedGroup::id()`.
* `LazyLinkCutTree(values)` creates one isolated vertex for each value.
* `add_vertex(value)` appends a new isolated vertex and returns its index.

Construction from `std::vector<U>` is supported when
`ActedGroup::make(value)`, `ActedGroup::make(value, index)`, or
`static_cast<T>(value)` is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Number of link-cut-tree vertices, including helper edge nodes. | $O(1)$ |
| `bool empty()` | Whether there are no vertices. | $O(1)$ |
| `int add_vertex(value)` | Adds one isolated vertex and returns its id. | Amortized $O(1)$ |
| `int edge_count()` | Number of edge helpers created by `link_edge`. | $O(1)$ |
| `bool edge_alive(edge_id)` | Whether the helper edge is currently linked. | $O(1)$ |
| `int edge_node(edge_id)` | Link-cut-tree vertex id storing this edge's value. | $O(1)$ |
| `std::pair<int, int> edge_endpoints(edge_id)` | Original endpoints passed to `link_edge`. | $O(1)$ |
| `T get(v)` | Pushes pending updates and returns the stored value of vertex `v`. | Amortized $O(\log N)$ |
| `T operator[](v)` | Alias for `get(v)`. | Amortized $O(\log N)$ |
| `void set(v, value)` | Updates the value of vertex `v`. | Amortized $O(\log N)$ |
| `void apply(v, f)` | Applies operator `f` to one vertex. | Amortized $O(\log N)$ |
| `void apply(u, v, f)` | Applies operator `f` to every link-cut-tree vertex on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `void evert(v)` | Makes `v` the represented root of its component. | Amortized $O(\log N)$ |
| `void reroot(v)` | Alias for `evert(v)`. | Amortized $O(\log N)$ |
| `int component_root(v)` | Returns the represented root of `v`'s component. | Amortized $O(\log N)$ |
| `int root(v)` | Alias for `component_root(v)`. | Amortized $O(\log N)$ |
| `bool connected(u, v)` | Returns whether `u` and `v` are in the same component. | Amortized $O(\log N)$ |
| `bool same(u, v)` | Alias for `connected(u, v)`. | Amortized $O(\log N)$ |
| `bool link(u, v)` | Adds edge `(u, v)` if they are in different components. Returns whether it was added. | Amortized $O(\log N)$ |
| `bool link_parent(child, parent)` | Rooted-tree spelling of `link(child, parent)`; after a successful link, the merged component keeps the original represented root of `parent`'s component. | Amortized $O(\log N)$ |
| `int link_edge(u, v, value)` | Adds an edge-value node between `u` and `v`. Returns an edge id, or `-1` if already connected. | Amortized $O(\log N)$ |
| `bool cut(u, v)` | Removes edge `(u, v)` if it exists. On success, the resulting components are rooted at `u` and `v`. | Amortized $O(\log N)$ |
| `bool cut_parent(v)` | Removes the current parent edge of `v` with respect to the represented root. On success, `v` becomes the root of the detached child-side component. | Amortized $O(\log N)$ |
| `bool cut_edge(edge_id)` | Removes a helper edge created by `link_edge`. On success, the endpoint components are rooted at the stored endpoints. | Amortized $O(\log N)$ |
| `T get_edge(edge_id)` | Pushes pending updates and returns the value stored in the helper edge node. | Amortized $O(\log N)$ |
| `void set_edge(edge_id, value)` | Updates the value stored in the helper edge node. | Amortized $O(\log N)$ |
| `void apply_edge(edge_id, f)` | Applies operator `f` to one helper edge node. | Amortized $O(\log N)$ |
| `T prod(u, v)` | Value product on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `T path_prod(u, v)` | Alias for `prod(u, v)`. | Amortized $O(\log N)$ |
| `int path_size(u, v)` | Number of link-cut-tree vertices on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `int kth_vertex(u, v, k)` | Returns the `k`-th vertex on the path from `u` to `v`, zero-indexed. | Amortized $O(\log N)$ |
| `int lca(u, v)` | Returns the LCA with respect to the current represented root, or `-1` if disconnected. | Amortized $O(\log N)$ |
| `T component_prod(v)` | Value product of the whole connected component containing `v`. | Amortized $O(\log N)$ |
| `int component_size(v)` | Number of link-cut-tree vertices in the component containing `v`. | Amortized $O(\log N)$ |
| `int child_toward(root, v)` | Child of `root` lying on the path from `root` to `v`; requires `root != v`. | Amortized $O(\log N)$ |
| `T branch_prod(root, v)` | Value product of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int branch_size(root, v)` | Size of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int parent(root, v)` | Parent of `v` when rooted at `root`, or `-1` if `root == v`. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Value product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod_excluding_child(root, v, child)` | Product of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |
| `int subtree_size_excluding_child(root, v, child)` | Size of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |

Path and rooted-subtree queries assert that the queried vertices are connected.
`child_toward(root, v)`, `branch_prod(root, v)`, and `branch_size(root, v)`
also assert `root != v`. The excluding-child helpers assert that `child` is a
child of `v` when the represented tree is rooted at `root`.

Unlike non-lazy `LinkCutTree::get`, `LazyLinkCutTree::get` is not `const`,
because it must expose the vertex and push pending lazy operations first.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::LazyLinkCutTree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    lct.apply(2, 4, 10);
    std::cout << lct.path_prod(2, 4).sum << "\n";     // 54
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 54

    lct.apply(0, 3, 5);
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 64
}
```

## Example: Rooted Tree Helpers

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::data_structure::LazyLinkCutTree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

// Rooted shape:
// 0
// +- 1
// +- 2
//    +- 3
//    +- 4
lct.link_parent(1, 0);
lct.link_parent(2, 0);
lct.link_parent(3, 2);
lct.link_parent(4, 2);
lct.reroot(0);

lct.apply(3, 4, 10);  // adds 10 to vertices 3, 2, and 4

long long whole = lct.component_prod(0).sum;       // 45
long long branch = lct.branch_prod(0, 4).sum;      // 42
int p = lct.parent(0, 4);                          // 2
int c = lct.child_toward(0, 4);                    // 2
long long without_4 = lct.subtree_prod_excluding_child(0, 2, 4).sum;  // 27

lct.cut_parent(4);  // cuts edge 2-4 without changing the represented root first
```

## Notes

`link_edge` creates helper vertices for edge values. Subtree sizes and products
include those helper vertices. Initialize original vertices with
`ActedGroup::id()` when you want subtree products over edge values only.

`evert(v)` and `reroot(v)` change the represented root of the component to `v`.

The following public methods reroot internally:

* `link(u, v)` first reroots `u`'s component at `u`. If it succeeds, the merged
  component keeps the original represented root of `v`'s component. If it
  returns `false` because `u` and `v` were already connected, that component may
  be left rooted at `u`.
* `link_parent(child, parent)` is the same operation as `link(child, parent)`.
  If it succeeds, it reroots the child-side component at `child`, attaches it
  under `parent`, and preserves the original represented root of the parent-side
  component.
* `link_edge(u, v, value)` uses `link` twice. If it succeeds, the merged
  component keeps the original represented root of `v`'s component.
* `cut(u, v)` first reroots at `u`. If it succeeds, the component containing
  `u` is rooted at `u`, and the component containing `v` is rooted at `v`. If it
  returns `false` after `u != v`, `u`'s component may still be left rooted at
  `u`.
* `cut_parent(v)` does not call `evert`. If it succeeds, the old represented
  root remains the root of the parent-side component, and `v` becomes the
  represented root of the detached child-side component.
* `cut_edge(edge_id)` uses `cut` twice. If it succeeds, the original `u`-side
  component is rooted at the stored `u` endpoint, the original `v`-side
  component is rooted at the stored `v` endpoint, and the helper edge node is
  isolated.
* `prod(u, v)`, `path_prod(u, v)`, `apply(u, v, f)`, `path_size(u, v)`, and
  `kth_vertex(u, v, k)` reroot at `u`, so the represented root becomes `u`.
* `subtree_prod(root, v)`, `subtree_size(root, v)`, `child_toward(root, v)`,
  `branch_prod(root, v)`, `branch_size(root, v)`, `parent(root, v)`,
  `subtree_prod_excluding_child(root, v, child)`, and
  `subtree_size_excluding_child(root, v, child)` reroot at `root`, so the
  represented root becomes `root`.

Other public methods may expose or splay vertices, but they do not change the
represented root. In particular, `lca(u, v)` uses the current represented root,
and `subtree_prod(v)` and `subtree_size(v)` use the current represented root.

This structure supports lazy path updates, but it does not provide subtree
updates. A path update must not touch virtual side subtrees, so the
implementation keeps preferred-path values and virtual-subtree aggregates as
separate cached values.

This structure does not support non-commutative subtree products. A represented
subtree has no canonical linear order, and the virtual-child aggregate relies on
commutativity and `inv`.
