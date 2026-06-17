---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/path_link_cut_tree.test.cpp
    title: verify/data_structure/path_link_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/path_link_cut_tree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"data_structure/path_link_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct PathLinkCutTree {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        int left = -1;\n        int right =\
    \ -1;\n        int parent = -1;\n        bool rev = false;\n        int size =\
    \ 1;\n        T value = Monoid::id();\n        T prod = Monoid::id();\n      \
    \  T rev_prod = Monoid::id();\n    };\n\n    struct EdgeInfo {\n        int u\
    \ = -1;\n        int v = -1;\n        int node = -1;\n        bool alive = false;\n\
    \    };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo> _edges;\n\
    \    std::vector<int> _path_buffer;\n\n    static T make_node_value(const T& value,\
    \ int) {\n        return value;\n    }\n\n    static T make_node_value(T&& value,\
    \ int) {\n        return std::move(value);\n    }\n\n    template <class U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { Monoid::make(x);\
    \ } ||\n        requires(U x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n\
    \            return Monoid::make(value, index);\n        } else {\n          \
    \  return static_cast<T>(value);\n        }\n    }\n\n    int child_size(int node)\
    \ const {\n        return node == -1 ? 0 : _nodes[node].size;\n    }\n\n    bool\
    \ is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        T left_prod\
    \ = x.left == -1 ? Monoid::id() : _nodes[x.left].prod;\n        T right_prod =\
    \ x.right == -1 ? Monoid::id() : _nodes[x.right].prod;\n        T left_rev_prod\
    \ = x.left == -1 ? Monoid::id() : _nodes[x.left].rev_prod;\n        T right_rev_prod\
    \ = x.right == -1 ? Monoid::id() : _nodes[x.right].rev_prod;\n        x.prod =\
    \ Monoid::op(Monoid::op(left_prod, x.value), right_prod);\n        x.rev_prod\
    \ = Monoid::op(Monoid::op(right_rev_prod, x.value), left_rev_prod);\n    }\n\n\
    \    void apply_reverse(int node) {\n        if (node == -1) return;\n       \
    \ Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n        std::swap(x.prod,\
    \ x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void push(int node) {\n\
    \        if (node == -1 || !_nodes[node].rev) return;\n        apply_reverse(_nodes[node].left);\n\
    \        apply_reverse(_nodes[node].right);\n        _nodes[node].rev = false;\n\
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
    \          _nodes[cur].right = last;\n            if (last != -1) _nodes[last].parent\
    \ = cur;\n            update(cur);\n            last = cur;\n        }\n     \
    \   splay(node);\n        return last;\n    }\n\n    void check_vertex(int v)\
    \ const {\n        assert(0 <= v && v < int(_nodes.size()));\n    }\n\n    void\
    \ check_edge(int edge_id) const {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n\
    \    }\n\n   public:\n    PathLinkCutTree() = default;\n\n    explicit PathLinkCutTree(int\
    \ n) {\n        assert(0 <= n);\n        _nodes.reserve(n);\n        for (int\
    \ i = 0; i < n; i++) add_vertex();\n    }\n\n    explicit PathLinkCutTree(const\
    \ std::vector<T>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n    }\n\n \
    \   explicit PathLinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit PathLinkCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Monoid::id()) {\n        Node node;\n   \
    \     node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_vertex(T&& value) {\n        Node node;\n       \
    \ node.value = std::move(value);\n        node.prod = node.value;\n        node.rev_prod\
    \ = node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
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
    \        if (component_root(v) == u) return false;\n        _nodes[u].parent =\
    \ v;\n        return true;\n    }\n\n    int link_edge(int u, int v, const T&\
    \ value = Monoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
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
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n};\n\
    \n}  // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PATH_LINK_CUT_TREE_HPP\n#define M1UNE_PATH_LINK_CUT_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct PathLinkCutTree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    struct Node {\n        int left = -1;\n        int right = -1;\n        int\
    \ parent = -1;\n        bool rev = false;\n        int size = 1;\n        T value\
    \ = Monoid::id();\n        T prod = Monoid::id();\n        T rev_prod = Monoid::id();\n\
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
    \ ? 0 : _nodes[node].size;\n    }\n\n    bool is_splay_root(int node) const {\n\
    \        int parent = _nodes[node].parent;\n        return parent == -1 || (_nodes[parent].left\
    \ != node && _nodes[parent].right != node);\n    }\n\n    void update(int node)\
    \ {\n        Node& x = _nodes[node];\n        x.size = 1 + child_size(x.left)\
    \ + child_size(x.right);\n        T left_prod = x.left == -1 ? Monoid::id() :\
    \ _nodes[x.left].prod;\n        T right_prod = x.right == -1 ? Monoid::id() :\
    \ _nodes[x.right].prod;\n        T left_rev_prod = x.left == -1 ? Monoid::id()\
    \ : _nodes[x.left].rev_prod;\n        T right_rev_prod = x.right == -1 ? Monoid::id()\
    \ : _nodes[x.right].rev_prod;\n        x.prod = Monoid::op(Monoid::op(left_prod,\
    \ x.value), right_prod);\n        x.rev_prod = Monoid::op(Monoid::op(right_rev_prod,\
    \ x.value), left_rev_prod);\n    }\n\n    void apply_reverse(int node) {\n   \
    \     if (node == -1) return;\n        Node& x = _nodes[node];\n        std::swap(x.left,\
    \ x.right);\n        std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n\
    \    }\n\n    void push(int node) {\n        if (node == -1 || !_nodes[node].rev)\
    \ return;\n        apply_reverse(_nodes[node].left);\n        apply_reverse(_nodes[node].right);\n\
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
    \ {\n            splay(cur);\n            _nodes[cur].right = last;\n        \
    \    if (last != -1) _nodes[last].parent = cur;\n            update(cur);\n  \
    \          last = cur;\n        }\n        splay(node);\n        return last;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < int(_nodes.size()));\n\
    \    }\n\n    void check_edge(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    PathLinkCutTree()\
    \ = default;\n\n    explicit PathLinkCutTree(int n) {\n        assert(0 <= n);\n\
    \        _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit PathLinkCutTree(const std::vector<T>& values) {\n     \
    \   _nodes.reserve(values.size());\n        for (int i = 0; i < int(values.size());\
    \ i++) add_vertex(values[i]);\n    }\n\n    explicit PathLinkCutTree(std::vector<T>&&\
    \ values) {\n        _nodes.reserve(values.size());\n        for (int i = 0; i\
    \ < int(values.size()); i++) add_vertex(std::move(values[i]));\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit PathLinkCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Monoid::id()) {\n        Node node;\n   \
    \     node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_vertex(T&& value) {\n        Node node;\n       \
    \ node.value = std::move(value);\n        node.prod = node.value;\n        node.rev_prod\
    \ = node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
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
    \        if (component_root(v) == u) return false;\n        _nodes[u].parent =\
    \ v;\n        return true;\n    }\n\n    int link_edge(int u, int v, const T&\
    \ value = Monoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
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
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n};\n\
    \n}  // namespace data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_PATH_LINK_CUT_TREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/path_link_cut_tree.hpp
  requiredBy: []
  timestamp: '2026-06-17 21:06:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/path_link_cut_tree.test.cpp
documentation_of: data_structure/path_link_cut_tree.hpp
layout: document
title: Path Link-Cut Tree
---

## Overview

`m1une::data_structure::PathLinkCutTree<Monoid>` maintains a dynamic forest. It
supports linking two trees, cutting an existing edge, rerooting a represented
tree, and querying a monoid product on a path.

The value is stored on vertices. If you need edge values, create one extra
link-cut-tree vertex for each original edge and connect it between the two
endpoints. The `link_edge` helper does this for you.

The implementation supports non-commutative monoids. `prod(u, v)` returns the
product in path order from `u` to `v`.

## Template Parameter

`Monoid` must satisfy `m1une::monoid::IsMonoid`:

```cpp
struct M {
    using value_type = T;
    static T id();
    static T op(const T& a, const T& b);
};
```

`op(a, b)` should be associative, and `id()` should be its identity.

## Construction

```cpp
PathLinkCutTree<Monoid> lct;
PathLinkCutTree<Monoid> lct(n);
PathLinkCutTree<Monoid> lct(values);
```

* `PathLinkCutTree(n)` creates `n` isolated vertices initialized with
  `Monoid::id()`.
* `PathLinkCutTree(values)` creates one isolated vertex for each value.
* `add_vertex(value)` appends a new isolated vertex and returns its index.

As with `Segtree`, construction from `std::vector<U>` is supported when
`Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Number of link-cut-tree vertices. | `O(1)` |
| `bool empty()` | Whether there are no vertices. | `O(1)` |
| `int add_vertex(value)` | Adds one isolated vertex and returns its id. | Amortized `O(1)` |
| `int edge_count()` | Number of edge helpers created by `link_edge`. | `O(1)` |
| `bool edge_alive(edge_id)` | Whether the helper edge is currently linked. | `O(1)` |
| `int edge_node(edge_id)` | Link-cut-tree vertex id storing this edge's value. | `O(1)` |
| `std::pair<int, int> edge_endpoints(edge_id)` | Original endpoints passed to `link_edge`. | `O(1)` |
| `const T& get(v)` | Returns the stored value of vertex `v`. | `O(1)` |
| `const T& operator[](v)` | Alias for `get(v)`. | `O(1)` |
| `void set(v, value)` | Updates the value of vertex `v`. | Amortized `O(log N)` |
| `void evert(v)` | Makes `v` the represented root of its tree. | Amortized `O(log N)` |
| `int component_root(v)` | Returns the represented root of `v`'s tree. | Amortized `O(log N)` |
| `bool connected(u, v)` | Returns whether `u` and `v` are in the same tree. | Amortized `O(log N)` |
| `bool same(u, v)` | Alias for `connected(u, v)`. | Amortized `O(log N)` |
| `bool link(u, v)` | Adds edge `(u, v)` if they are in different trees. Returns whether it was added. | Amortized `O(log N)` |
| `int link_edge(u, v, value)` | Adds an edge-value node between `u` and `v`. Returns an edge id, or `-1` if `u` and `v` are already connected. | Amortized `O(log N)` |
| `bool cut(u, v)` | Removes edge `(u, v)` if it exists. On success, the resulting trees are rooted at `u` and `v`. | Amortized `O(log N)` |
| `bool cut_edge(edge_id)` | Removes a helper edge created by `link_edge`. On success, the endpoint trees are rooted at the stored endpoints. | Amortized `O(log N)` |
| `const T& get_edge(edge_id)` | Returns the value stored in the helper edge node. | `O(1)` |
| `void set_edge(edge_id, value)` | Updates the value stored in the helper edge node. | Amortized `O(log N)` |
| `T prod(u, v)` | Returns the monoid product on the path from `u` to `v`. | Amortized `O(log N)` |
| `T path_prod(u, v)` | Alias for `prod(u, v)`. | Amortized `O(log N)` |
| `int path_size(u, v)` | Number of link-cut-tree vertices on the path from `u` to `v`. | Amortized `O(log N)` |
| `int kth_vertex(u, v, k)` | Returns the `k`-th vertex on the path from `u` to `v`, zero-indexed. | Amortized `O(log N)` |
| `int lca(u, v)` | Returns the LCA with respect to the current represented root, or `-1` if disconnected. | Amortized `O(log N)` |

`prod`, `path_size`, and `kth_vertex` require `u` and `v` to be connected.
This is checked by `assert`.

## Path Order

For non-commutative monoids, order matters. If the represented path is:

```text
u - a - b - v
```

then:

```cpp
lct.prod(u, v) == op(op(op(value[u], value[a]), value[b]), value[v])
lct.prod(v, u) == op(op(op(value[v], value[b]), value[a]), value[u])
```

Internally the structure keeps both the normal and reversed aggregate of every
splay subtree, so path reversal by `evert` is safe for non-commutative monoids.

## Represented Roots And LCA

`evert(v)` changes the represented root of the tree containing `v`.

The following public methods reroot internally:

* `link(u, v)` first reroots `u`'s tree at `u`. If it succeeds, the merged tree
  keeps the original represented root of `v`'s tree. If it returns `false`
  because `u` and `v` were already connected, that tree may be left rooted at
  `u`.
* `link_edge(u, v, value)` uses `link` twice. If it succeeds, the merged tree
  keeps the original represented root of `v`'s tree.
* `cut(u, v)` first reroots at `u`. If it succeeds, the tree containing `u` is
  rooted at `u`, and the tree containing `v` is rooted at `v`. If it returns
  `false` after `u != v`, `u`'s tree may still be left rooted at `u`.
* `cut_edge(edge_id)` uses `cut` twice. If it succeeds, the original `u`-side
  tree is rooted at the stored `u` endpoint, the original `v`-side tree is
  rooted at the stored `v` endpoint, and the helper edge node is isolated.
* `prod(u, v)`, `path_prod(u, v)`, `path_size(u, v)`, and
  `kth_vertex(u, v, k)` reroot at `u`, so the represented root becomes `u`.

Other public methods may expose or splay vertices, but they do not change the
represented root.

`lca(u, v)` is computed with respect to the current represented root. If the
root matters, call `evert(r)` immediately before `lca`:

```cpp
lct.evert(r);
int x = lct.lca(u, v);
```

## Example: Vertex Path Sum

```cpp
#include "data_structure/path_link_cut_tree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::PathLinkCutTree<Sum> lct(std::vector<long long>{1, 2, 3, 4});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);

    std::cout << lct.prod(2, 3) << "\n"; // 3 + 2 + 4 = 9

    lct.set(1, 10);
    std::cout << lct.prod(2, 3) << "\n"; // 3 + 10 + 4 = 17
}
```

## Example: Edge Path Sum

Store original vertices with identity values. `link_edge` creates one extra
link-cut-tree vertex for the edge value and links it between the two endpoints.

```cpp
using Sum = m1une::monoid::Add<long long>;
m1une::data_structure::PathLinkCutTree<Sum> lct(n);

int edge_id = lct.link_edge(u, v, weight);

long long distance = lct.prod(a, b);
lct.set_edge(edge_id, new_weight);
```

This also makes `cut` easy:

```cpp
lct.cut_edge(edge_id);
```

## Notes

All complexities are amortized. The represented forest must remain a forest:
`link(u, v)` returns `false` if `u` and `v` are already connected,
`link_edge(u, v, value)` returns `-1` in that case, and `cut(u, v)` returns
`false` if `(u, v)` is not an existing represented edge.

`size()` includes helper edge nodes created by `link_edge`. The original vertex
ids remain unchanged.

This implementation maintains path aggregates only. It does not maintain
subtree aggregates of the represented tree. For a variant with subtree-query
helpers, use `LinkCutTree`.

For path updates with lazy propagation, use `LazyPathLinkCutTree`.
