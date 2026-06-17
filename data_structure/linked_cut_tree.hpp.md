---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/linked_cut_tree.test.cpp
    title: verify/data_structure/linked_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/linked_cut_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
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
    \ M::value_type a) {\n    { M::inverse(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"data_structure/linked_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Monoid>\nstruct LinkedCutTree {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        int left = -1;\n        int right =\
    \ -1;\n        int parent = -1;\n        bool rev = false;\n        int size =\
    \ 1;\n        int virtual_size = 0;\n        int all_size = 1;\n        T value\
    \ = Monoid::id();\n        T prod = Monoid::id();\n        T rev_prod = Monoid::id();\n\
    \        T virtual_prod = Monoid::id();\n        T all_prod = Monoid::id();\n\
    \    };\n\n    struct EdgeInfo {\n        int u = -1;\n        int v = -1;\n \
    \       int node = -1;\n        bool alive = false;\n    };\n\n    std::vector<Node>\
    \ _nodes;\n    std::vector<EdgeInfo> _edges;\n    std::vector<int> _path_buffer;\n\
    \n    static T make_node_value(const T& value, int) {\n        return value;\n\
    \    }\n\n    static T make_node_value(T&& value, int) {\n        return std::move(value);\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    static T make_node_value(const\
    \ U& value, int index) {\n        if constexpr (requires(U x) { Monoid::make(x);\
    \ }) {\n            return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int child_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].size;\n    }\n\n    int child_all_size(int node) const {\n\
    \        return node == -1 ? 0 : _nodes[node].all_size;\n    }\n\n    T child_prod(int\
    \ node) const {\n        return node == -1 ? Monoid::id() : _nodes[node].prod;\n\
    \    }\n\n    T child_rev_prod(int node) const {\n        return node == -1 ?\
    \ Monoid::id() : _nodes[node].rev_prod;\n    }\n\n    T child_all_prod(int node)\
    \ const {\n        return node == -1 ? Monoid::id() : _nodes[node].all_prod;\n\
    \    }\n\n    T node_subtree_prod(int node) const {\n        const Node& x = _nodes[node];\n\
    \        return Monoid::op(x.value, x.virtual_prod);\n    }\n\n    int node_subtree_size(int\
    \ node) const {\n        return 1 + _nodes[node].virtual_size;\n    }\n\n    bool\
    \ is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.all_size\
    \ = 1 + x.virtual_size + child_all_size(x.left) + child_all_size(x.right);\n \
    \       x.prod = Monoid::op(Monoid::op(child_prod(x.left), x.value), child_prod(x.right));\n\
    \        x.rev_prod = Monoid::op(Monoid::op(child_rev_prod(x.right), x.value),\
    \ child_rev_prod(x.left));\n        x.all_prod = Monoid::op(Monoid::op(child_all_prod(x.left),\
    \ x.value),\n                                Monoid::op(x.virtual_prod, child_all_prod(x.right)));\n\
    \    }\n\n    void add_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = Monoid::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = Monoid::op(x.virtual_prod, Monoid::inverse(_nodes[child].all_prod));\n\
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
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    LinkedCutTree()\
    \ = default;\n\n    explicit LinkedCutTree(int n) {\n        assert(0 <= n);\n\
    \        _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit LinkedCutTree(const std::vector<T>& values) {\n       \
    \ _nodes.reserve(values.size());\n        for (int i = 0; i < int(values.size());\
    \ i++) add_vertex(values[i]);\n    }\n\n    explicit LinkedCutTree(std::vector<T>&&\
    \ values) {\n        _nodes.reserve(values.size());\n        for (int i = 0; i\
    \ < int(values.size()); i++) add_vertex(std::move(values[i]));\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit LinkedCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Monoid::id()) {\n        Node node;\n   \
    \     node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
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
    \ && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U x, int\
    \ i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n  \
    \  void set(int v, const U& value) {\n        set(v, make_node_value(value, v));\n\
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
    \        if (component_root(v) == u) return false;\n        access(v);\n     \
    \   _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = Monoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n    \
    \    if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int link_edge(int u,\
    \ int v, const U& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        return link_edge(u,\
    \ v, make_node_value(value, size()));\n    }\n\n    bool cut(int u, int v) {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ false;\n        evert(u);\n        access(v);\n        if (_nodes[v].left !=\
    \ u || _nodes[u].right != -1) return false;\n        _nodes[v].left = -1;\n  \
    \      _nodes[u].parent = -1;\n        update(v);\n        return true;\n    }\n\
    \n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n        EdgeInfo&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        bool\
    \ ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node, edge.v);\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    const T& get_edge(int edge_id) const {\n        return get(edge_node(edge_id));\n\
    \    }\n\n    void set_edge(int edge_id, const T& value) {\n        set(edge_node(edge_id),\
    \ value);\n    }\n\n    void set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id),\
    \ std::move(value));\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    T prod(int u, int\
    \ v) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        return _nodes[v].prod;\n\
    \    }\n\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    int path_size(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        assert(connected(u, v));\n        evert(u);\n        access(v);\n   \
    \     return _nodes[v].size;\n    }\n\n    int kth_vertex(int u, int v, int k)\
    \ {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        assert(0 <= k && k < _nodes[v].size);\n\
    \n        int cur = v;\n        while (true) {\n            push(cur);\n     \
    \       int left_size = child_size(_nodes[cur].left);\n            if (k < left_size)\
    \ {\n                cur = _nodes[cur].left;\n            } else if (k == left_size)\
    \ {\n                splay(cur);\n                return cur;\n            } else\
    \ {\n                k -= left_size + 1;\n                cur = _nodes[cur].right;\n\
    \            }\n        }\n    }\n\n    int lca(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (!connected(u, v)) return -1;\n        if\
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n\n\
    \    T subtree_prod(int root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n\
    \        assert(connected(root, v));\n        evert(root);\n        access(v);\n\
    \        return node_subtree_prod(v);\n    }\n\n    T subtree_prod(int v) {\n\
    \        check_vertex(v);\n        access(v);\n        return node_subtree_prod(v);\n\
    \    }\n\n    int subtree_size(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(connected(root, v));\n        evert(root);\n\
    \        access(v);\n        return node_subtree_size(v);\n    }\n\n    int subtree_size(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        return node_subtree_size(v);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_LINKED_CUT_TREE_HPP\n#define M1UNE_LINKED_CUT_TREE_HPP 1\n\n\
    #include <cassert>\n#include <concepts>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\ntemplate <m1une::monoid::IsCommutativeGroup Monoid>\nstruct\
    \ LinkedCutTree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    struct Node {\n        int left = -1;\n        int right = -1;\n        int\
    \ parent = -1;\n        bool rev = false;\n        int size = 1;\n        int\
    \ virtual_size = 0;\n        int all_size = 1;\n        T value = Monoid::id();\n\
    \        T prod = Monoid::id();\n        T rev_prod = Monoid::id();\n        T\
    \ virtual_prod = Monoid::id();\n        T all_prod = Monoid::id();\n    };\n\n\
    \    struct EdgeInfo {\n        int u = -1;\n        int v = -1;\n        int\
    \ node = -1;\n        bool alive = false;\n    };\n\n    std::vector<Node> _nodes;\n\
    \    std::vector<EdgeInfo> _edges;\n    std::vector<int> _path_buffer;\n\n   \
    \ static T make_node_value(const T& value, int) {\n        return value;\n   \
    \ }\n\n    static T make_node_value(T&& value, int) {\n        return std::move(value);\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    static T make_node_value(const\
    \ U& value, int index) {\n        if constexpr (requires(U x) { Monoid::make(x);\
    \ }) {\n            return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int child_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].size;\n    }\n\n    int child_all_size(int node) const {\n\
    \        return node == -1 ? 0 : _nodes[node].all_size;\n    }\n\n    T child_prod(int\
    \ node) const {\n        return node == -1 ? Monoid::id() : _nodes[node].prod;\n\
    \    }\n\n    T child_rev_prod(int node) const {\n        return node == -1 ?\
    \ Monoid::id() : _nodes[node].rev_prod;\n    }\n\n    T child_all_prod(int node)\
    \ const {\n        return node == -1 ? Monoid::id() : _nodes[node].all_prod;\n\
    \    }\n\n    T node_subtree_prod(int node) const {\n        const Node& x = _nodes[node];\n\
    \        return Monoid::op(x.value, x.virtual_prod);\n    }\n\n    int node_subtree_size(int\
    \ node) const {\n        return 1 + _nodes[node].virtual_size;\n    }\n\n    bool\
    \ is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.all_size\
    \ = 1 + x.virtual_size + child_all_size(x.left) + child_all_size(x.right);\n \
    \       x.prod = Monoid::op(Monoid::op(child_prod(x.left), x.value), child_prod(x.right));\n\
    \        x.rev_prod = Monoid::op(Monoid::op(child_rev_prod(x.right), x.value),\
    \ child_rev_prod(x.left));\n        x.all_prod = Monoid::op(Monoid::op(child_all_prod(x.left),\
    \ x.value),\n                                Monoid::op(x.virtual_prod, child_all_prod(x.right)));\n\
    \    }\n\n    void add_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = Monoid::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = Monoid::op(x.virtual_prod, Monoid::inverse(_nodes[child].all_prod));\n\
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
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    LinkedCutTree()\
    \ = default;\n\n    explicit LinkedCutTree(int n) {\n        assert(0 <= n);\n\
    \        _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit LinkedCutTree(const std::vector<T>& values) {\n       \
    \ _nodes.reserve(values.size());\n        for (int i = 0; i < int(values.size());\
    \ i++) add_vertex(values[i]);\n    }\n\n    explicit LinkedCutTree(std::vector<T>&&\
    \ values) {\n        _nodes.reserve(values.size());\n        for (int i = 0; i\
    \ < int(values.size()); i++) add_vertex(std::move(values[i]));\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit LinkedCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Monoid::id()) {\n        Node node;\n   \
    \     node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
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
    \ && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U x, int\
    \ i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n  \
    \  void set(int v, const U& value) {\n        set(v, make_node_value(value, v));\n\
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
    \        if (component_root(v) == u) return false;\n        access(v);\n     \
    \   _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = Monoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n    \
    \    if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int link_edge(int u,\
    \ int v, const U& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        return link_edge(u,\
    \ v, make_node_value(value, size()));\n    }\n\n    bool cut(int u, int v) {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ false;\n        evert(u);\n        access(v);\n        if (_nodes[v].left !=\
    \ u || _nodes[u].right != -1) return false;\n        _nodes[v].left = -1;\n  \
    \      _nodes[u].parent = -1;\n        update(v);\n        return true;\n    }\n\
    \n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n        EdgeInfo&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        bool\
    \ ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node, edge.v);\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    const T& get_edge(int edge_id) const {\n        return get(edge_node(edge_id));\n\
    \    }\n\n    void set_edge(int edge_id, const T& value) {\n        set(edge_node(edge_id),\
    \ value);\n    }\n\n    void set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id),\
    \ std::move(value));\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    T prod(int u, int\
    \ v) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        return _nodes[v].prod;\n\
    \    }\n\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    int path_size(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        assert(connected(u, v));\n        evert(u);\n        access(v);\n   \
    \     return _nodes[v].size;\n    }\n\n    int kth_vertex(int u, int v, int k)\
    \ {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        assert(0 <= k && k < _nodes[v].size);\n\
    \n        int cur = v;\n        while (true) {\n            push(cur);\n     \
    \       int left_size = child_size(_nodes[cur].left);\n            if (k < left_size)\
    \ {\n                cur = _nodes[cur].left;\n            } else if (k == left_size)\
    \ {\n                splay(cur);\n                return cur;\n            } else\
    \ {\n                k -= left_size + 1;\n                cur = _nodes[cur].right;\n\
    \            }\n        }\n    }\n\n    int lca(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (!connected(u, v)) return -1;\n        if\
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n\n\
    \    T subtree_prod(int root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n\
    \        assert(connected(root, v));\n        evert(root);\n        access(v);\n\
    \        return node_subtree_prod(v);\n    }\n\n    T subtree_prod(int v) {\n\
    \        check_vertex(v);\n        access(v);\n        return node_subtree_prod(v);\n\
    \    }\n\n    int subtree_size(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(connected(root, v));\n        evert(root);\n\
    \        access(v);\n        return node_subtree_size(v);\n    }\n\n    int subtree_size(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        return node_subtree_size(v);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_LINKED_CUT_TREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/linked_cut_tree.hpp
  requiredBy: []
  timestamp: '2026-06-17 21:02:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/linked_cut_tree.test.cpp
documentation_of: data_structure/linked_cut_tree.hpp
layout: document
title: Linked-Cut Tree
---

## Overview

`m1une::data_structure::LinkedCutTree<Monoid>` is a link-cut tree with
the same path-query interface as `PathLinkCutTree`, plus rooted subtree queries.

The monoid operation must be commutative and must provide an inverse. This lets
the structure maintain aggregates of virtual child subtrees and update them in
constant time whenever `access` changes the preferred path. Path and subtree
queries are both amortized $O(\log N)$.

## Template Parameter

`Monoid` must satisfy `m1une::monoid::IsCommutativeGroup`:

```cpp
struct M {
    using value_type = T;
    static T id();
    static T op(const T& a, const T& b);
    static T inverse(const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inverse(x)` must satisfy `op(x, inverse(x)) == id()`.

## Construction

```cpp
LinkedCutTree<Monoid> lct;
LinkedCutTree<Monoid> lct(n);
LinkedCutTree<Monoid> lct(values);
```

Construction and `add_vertex` follow `PathLinkCutTree`.

## Methods

All `PathLinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries: `prod`, `path_prod`, `path_size`, `kth_vertex`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Group product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |

## Example

```cpp
#include "data_structure/linked_cut_tree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::LinkedCutTree<Sum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    std::cout << lct.path_prod(2, 4) << "\n";     // 3 + 2 + 4 + 5 = 14
    std::cout << lct.subtree_prod(0, 1) << "\n";  // 2 + 3 + 4 + 5 = 14
}
```

## Notes

`link_edge` creates helper vertices exactly like `PathLinkCutTree`; subtree sizes
and products include those helper vertices. Initialize original vertices with
the group identity when you want subtree products over edge values only.

This structure does not support non-commutative subtree products. A represented
subtree has no canonical linear order, and the virtual-child aggregate relies on
commutativity and `inverse`.
