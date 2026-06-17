---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_linked_cut_tree.hpp
    title: Lazy Linked-Cut Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/data_structure/lazy_linked_cut_tree.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size};\n\
    \    }\n    static constexpr value_type inverse(const value_type& x) {\n     \
    \   return {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n    static\
    \ constexpr operator_type op_id() {\n        return 0;\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f + g;\n    }\n\n    // Mapping (sum + f * size)\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        return\
    \ {x.sum + f * x.size, x.size};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n\
    #line 1 \"data_structure/lazy_linked_cut_tree.hpp\"\n\n\n\n#line 5 \"data_structure/lazy_linked_cut_tree.hpp\"\
    \n#include <concepts>\n#include <type_traits>\n#line 9 \"data_structure/lazy_linked_cut_tree.hpp\"\
    \n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \ && requires(typename AM::value_type a) {\n    { AM::inverse(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 11 \"data_structure/lazy_linked_cut_tree.hpp\"\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <m1une::acted_monoid::IsCommutativeActedGroup\
    \ ActedMonoid>\nstruct LazyLinkedCutTree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        int left = -1;\n        int right = -1;\n        int parent\
    \ = -1;\n        bool rev = false;\n        int size = 1;\n        int virtual_size\
    \ = 0;\n        int rake_size = 0;\n        int all_size = 1;\n        T value\
    \ = ActedMonoid::id();\n        T prod = ActedMonoid::id();\n        T rev_prod\
    \ = ActedMonoid::id();\n        T virtual_prod = ActedMonoid::id();\n        T\
    \ rake_prod = ActedMonoid::id();\n        T all_prod = ActedMonoid::id();\n  \
    \      F lazy = ActedMonoid::op_id();\n    };\n\n    struct EdgeInfo {\n     \
    \   int u = -1;\n        int v = -1;\n        int node = -1;\n        bool alive\
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
    \ ? 0 : _nodes[node].size;\n    }\n\n    int child_all_size(int node) const {\n\
    \        return node == -1 ? 0 : _nodes[node].all_size;\n    }\n\n    int child_rake_size(int\
    \ node) const {\n        return node == -1 ? 0 : _nodes[node].rake_size;\n   \
    \ }\n\n    T child_prod(int node) const {\n        return node == -1 ? ActedMonoid::id()\
    \ : _nodes[node].prod;\n    }\n\n    T child_rev_prod(int node) const {\n    \
    \    return node == -1 ? ActedMonoid::id() : _nodes[node].rev_prod;\n    }\n\n\
    \    T child_all_prod(int node) const {\n        return node == -1 ? ActedMonoid::id()\
    \ : _nodes[node].all_prod;\n    }\n\n    T child_rake_prod(int node) const {\n\
    \        return node == -1 ? ActedMonoid::id() : _nodes[node].rake_prod;\n   \
    \ }\n\n    T node_subtree_prod(int node) const {\n        const Node& x = _nodes[node];\n\
    \        return ActedMonoid::op(x.value, x.virtual_prod);\n    }\n\n    int node_subtree_size(int\
    \ node) const {\n        return 1 + _nodes[node].virtual_size;\n    }\n\n    bool\
    \ is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.rake_size\
    \ = x.virtual_size + child_rake_size(x.left) + child_rake_size(x.right);\n   \
    \     x.all_size = x.size + x.rake_size;\n        x.prod = ActedMonoid::op(ActedMonoid::op(child_prod(x.left),\
    \ x.value), child_prod(x.right));\n        x.rev_prod = ActedMonoid::op(ActedMonoid::op(child_rev_prod(x.right),\
    \ x.value), child_rev_prod(x.left));\n        x.rake_prod = ActedMonoid::op(ActedMonoid::op(child_rake_prod(x.left),\
    \ x.virtual_prod),\n                                      child_rake_prod(x.right));\n\
    \        x.all_prod = ActedMonoid::op(x.prod, x.rake_prod);\n    }\n\n    void\
    \ add_virtual_child(int node, int child) {\n        if (child == -1) return;\n\
    \        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedMonoid::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedMonoid::op(x.virtual_prod, ActedMonoid::inverse(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ apply_operator(int node, const F& f) {\n        if (node == -1) return;\n  \
    \      Node& x = _nodes[node];\n        x.value = ActedMonoid::mapping(f, x.value);\n\
    \        x.prod = ActedMonoid::mapping(f, x.prod);\n        x.rev_prod = ActedMonoid::mapping(f,\
    \ x.rev_prod);\n        x.all_prod = ActedMonoid::op(x.prod, x.rake_prod);\n \
    \       x.lazy = ActedMonoid::op_comp(f, x.lazy);\n    }\n\n    void push(int\
    \ node) {\n        if (node == -1) return;\n        Node& x = _nodes[node];\n\
    \        if (x.rev) {\n            apply_reverse(x.left);\n            apply_reverse(x.right);\n\
    \            x.rev = false;\n        }\n        apply_operator(x.left, x.lazy);\n\
    \        apply_operator(x.right, x.lazy);\n        x.lazy = ActedMonoid::op_id();\n\
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
    \    }\n\n   public:\n    LazyLinkedCutTree() = default;\n\n    explicit LazyLinkedCutTree(int\
    \ n) {\n        assert(0 <= n);\n        _nodes.reserve(n);\n        for (int\
    \ i = 0; i < n; i++) add_vertex();\n    }\n\n    explicit LazyLinkedCutTree(const\
    \ std::vector<T>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n    }\n\n \
    \   explicit LazyLinkedCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { ActedMonoid::make(x); } ||\n        requires(U x, int i)\
    \ { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    explicit LazyLinkedCutTree(const std::vector<U>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = ActedMonoid::id()) {\n        Node node;\n\
    \        node.value = value;\n        node.prod = value;\n        node.rev_prod\
    \ = value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
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
    \        if (component_root(v) == u) return false;\n        access(v);\n     \
    \   _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = ActedMonoid::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
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
    \     access(u);\n        return access(v);\n    }\n\n    T subtree_prod(int root,\
    \ int v) {\n        check_vertex(root);\n        check_vertex(v);\n        assert(connected(root,\
    \ v));\n        evert(root);\n        access(v);\n        return node_subtree_prod(v);\n\
    \    }\n\n    T subtree_prod(int v) {\n        check_vertex(v);\n        access(v);\n\
    \        return node_subtree_prod(v);\n    }\n\n    int subtree_size(int root,\
    \ int v) {\n        check_vertex(root);\n        check_vertex(v);\n        assert(connected(root,\
    \ v));\n        evert(root);\n        access(v);\n        return node_subtree_size(v);\n\
    \    }\n\n    int subtree_size(int v) {\n        check_vertex(v);\n        access(v);\n\
    \        return node_subtree_size(v);\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n#line 11 \"verify/data_structure/lazy_linked_cut_tree.test.cpp\"\
    \n\nusing AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node\
    \ = AddSum::value_type;\n\nvoid test_vertex_path_and_subtree_updates() {\n   \
    \ m1une::data_structure::LazyLinkedCutTree<AddSum> lct(std::vector<long long>{1,\
    \ 2, 3, 4, 5});\n\n    assert(lct.link(0, 1));\n    assert(lct.link(1, 2));\n\
    \    assert(lct.link(1, 3));\n    assert(lct.link(3, 4));\n\n    Node subtree\
    \ = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 14);\n    assert(subtree.size\
    \ == 4);\n    assert(lct.subtree_size(0, 1) == 4);\n\n    lct.apply(2, 4, 10);\n\
    \    Node path = lct.path_prod(2, 4);\n    assert(path.sum == 54);\n    assert(path.size\
    \ == 4);\n    subtree = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 54);\n\
    \    assert(subtree.size == 4);\n    assert(lct.get(0).sum == 1);\n    assert(lct.subtree_prod(1,\
    \ 3).sum == 29);\n\n    lct.apply(0, 3, 5);\n    subtree = lct.subtree_prod(0,\
    \ 1);\n    assert(subtree.sum == 64);\n    assert(subtree.size == 4);\n    assert(lct.path_prod(2,\
    \ 4).sum == 64);\n\n    subtree = lct.subtree_prod(2, 1);\n    assert(subtree.sum\
    \ == 57);\n    assert(subtree.size == 4);\n}\n\nvoid test_edge_path_and_subtree_updates()\
    \ {\n    m1une::data_structure::LazyLinkedCutTree<AddSum> lct(3);\n\n    int e01\
    \ = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1, 2, 7);\n    assert(e01\
    \ == 0);\n    assert(e12 == 1);\n\n    Node full = lct.subtree_prod(0, 0);\n \
    \   assert(full.sum == 12);\n    assert(full.size == 2);\n    Node child = lct.subtree_prod(0,\
    \ 1);\n    assert(child.sum == 7);\n    assert(child.size == 1);\n    assert(lct.subtree_size(0,\
    \ 1) == 3);\n\n    lct.apply(0, 2, 3);\n    assert(lct.path_prod(0, 2).sum ==\
    \ 18);\n    assert(lct.subtree_prod(0, 1).sum == 10);\n\n    lct.apply(1, 2, 2);\n\
    \    assert(lct.get_edge(e01).sum == 8);\n    assert(lct.get_edge(e12).sum ==\
    \ 12);\n    assert(lct.subtree_prod(0, 0).sum == 20);\n\n    assert(lct.cut_edge(e01));\n\
    \    assert(!lct.connected(0, 2));\n}\n\nbool naive_connected(const std::vector<std::vector<int>>&\
    \ adj, int s, int t) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[s] = s;\n    stack.push_back(s);\n    for (int it = 0; it\
    \ < int(stack.size()); it++) {\n        int v = stack[it];\n        if (v == t)\
    \ return true;\n        for (int to : adj[v]) {\n            if (parent[to] !=\
    \ -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    return false;\n}\n\nstd::vector<int> naive_path_vertices(const\
    \ std::vector<std::vector<int>>& adj, int s, int t) {\n    std::vector<int> parent(adj.size(),\
    \ -1);\n    std::vector<int> stack;\n    parent[s] = s;\n    stack.push_back(s);\n\
    \    for (int it = 0; it < int(stack.size()); it++) {\n        int v = stack[it];\n\
    \        if (v == t) break;\n        for (int to : adj[v]) {\n            if (parent[to]\
    \ != -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    assert(parent[t] != -1);\n    std::vector<int> path;\n\
    \    for (int v = t; v != s; v = parent[v]) path.push_back(v);\n    path.push_back(s);\n\
    \    return path;\n}\n\nlong long naive_path_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int s, int t) {\n    long long res\
    \ = 0;\n    for (int v : naive_path_vertices(adj, s, t)) res += value[v];\n  \
    \  return res;\n}\n\nlong long naive_subtree_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int root,\n                      \
    \      int v) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[root] = root;\n    stack.push_back(root);\n    for (int it\
    \ = 0; it < int(stack.size()); it++) {\n        int x = stack[it];\n        for\
    \ (int to : adj[x]) {\n            if (parent[to] != -1) continue;\n         \
    \   parent[to] = x;\n            stack.push_back(to);\n        }\n    }\n    assert(parent[v]\
    \ != -1);\n\n    long long res = 0;\n    stack.clear();\n    stack.push_back(v);\n\
    \    while (!stack.empty()) {\n        int x = stack.back();\n        stack.pop_back();\n\
    \        res += value[x];\n        for (int to : adj[x]) {\n            if (to\
    \ == parent[x]) continue;\n            stack.push_back(to);\n        }\n    }\n\
    \    return res;\n}\n\nvoid test_random_vertex_path_updates() {\n    constexpr\
    \ int n = 8;\n    std::vector<long long> initial;\n    std::vector<long long>\
    \ value;\n    for (int i = 0; i < n; i++) {\n        initial.push_back(i + 1);\n\
    \        value.push_back(i + 1);\n    }\n    m1une::data_structure::LazyLinkedCutTree<AddSum>\
    \ lct(initial);\n    std::vector<std::vector<int>> adj(n);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    std::mt19937 rng(2);\n\n    for (int step = 0; step < 700;\
    \ step++) {\n        int op = int(rng() % 6);\n        int u = int(rng() % n);\n\
    \        int v = int(rng() % n);\n        if (op == 0) {\n            if (u !=\
    \ v && !naive_connected(adj, u, v)) {\n                assert(lct.link(u, v));\n\
    \                adj[u].push_back(v);\n                adj[v].push_back(u);\n\
    \                edges.emplace_back(u, v);\n            }\n        } else if (op\
    \ == 1) {\n            if (!edges.empty()) {\n                int id = int(rng()\
    \ % edges.size());\n                auto [a, b] = edges[id];\n               \
    \ assert(lct.cut(a, b));\n                for (int i = 0; i < int(adj[a].size());\
    \ i++) {\n                    if (adj[a][i] == b) {\n                        adj[a][i]\
    \ = adj[a].back();\n                        adj[a].pop_back();\n             \
    \           break;\n                    }\n                }\n               \
    \ for (int i = 0; i < int(adj[b].size()); i++) {\n                    if (adj[b][i]\
    \ == a) {\n                        adj[b][i] = adj[b].back();\n              \
    \          adj[b].pop_back();\n                        break;\n              \
    \      }\n                }\n                edges[id] = edges.back();\n     \
    \           edges.pop_back();\n            }\n        } else if (op == 2) {\n\
    \            long long x = int(rng() % 200) - 100;\n            value[u] = x;\n\
    \            lct.set(u, x);\n        } else if (u != v && naive_connected(adj,\
    \ u, v)) {\n            if (op == 3) {\n                long long add = int(rng()\
    \ % 21) - 10;\n                lct.apply(u, v, add);\n                for (int\
    \ x : naive_path_vertices(adj, u, v)) value[x] += add;\n            } else if\
    \ (op == 4) {\n                assert(lct.path_prod(u, v).sum == naive_path_sum(adj,\
    \ value, u, v));\n            } else {\n                assert(lct.subtree_prod(u,\
    \ v).sum == naive_subtree_sum(adj, value, u, v));\n                assert(lct.subtree_prod(v,\
    \ u).sum == naive_subtree_sum(adj, value, v, u));\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    test_vertex_path_and_subtree_updates();\n    test_edge_path_and_subtree_updates();\n\
    \    test_random_vertex_path_updates();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#include \"acted_monoid/range_add_range_sum.hpp\"\n#include \"data_structure/lazy_linked_cut_tree.hpp\"\
    \n\nusing AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node\
    \ = AddSum::value_type;\n\nvoid test_vertex_path_and_subtree_updates() {\n   \
    \ m1une::data_structure::LazyLinkedCutTree<AddSum> lct(std::vector<long long>{1,\
    \ 2, 3, 4, 5});\n\n    assert(lct.link(0, 1));\n    assert(lct.link(1, 2));\n\
    \    assert(lct.link(1, 3));\n    assert(lct.link(3, 4));\n\n    Node subtree\
    \ = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 14);\n    assert(subtree.size\
    \ == 4);\n    assert(lct.subtree_size(0, 1) == 4);\n\n    lct.apply(2, 4, 10);\n\
    \    Node path = lct.path_prod(2, 4);\n    assert(path.sum == 54);\n    assert(path.size\
    \ == 4);\n    subtree = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 54);\n\
    \    assert(subtree.size == 4);\n    assert(lct.get(0).sum == 1);\n    assert(lct.subtree_prod(1,\
    \ 3).sum == 29);\n\n    lct.apply(0, 3, 5);\n    subtree = lct.subtree_prod(0,\
    \ 1);\n    assert(subtree.sum == 64);\n    assert(subtree.size == 4);\n    assert(lct.path_prod(2,\
    \ 4).sum == 64);\n\n    subtree = lct.subtree_prod(2, 1);\n    assert(subtree.sum\
    \ == 57);\n    assert(subtree.size == 4);\n}\n\nvoid test_edge_path_and_subtree_updates()\
    \ {\n    m1une::data_structure::LazyLinkedCutTree<AddSum> lct(3);\n\n    int e01\
    \ = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1, 2, 7);\n    assert(e01\
    \ == 0);\n    assert(e12 == 1);\n\n    Node full = lct.subtree_prod(0, 0);\n \
    \   assert(full.sum == 12);\n    assert(full.size == 2);\n    Node child = lct.subtree_prod(0,\
    \ 1);\n    assert(child.sum == 7);\n    assert(child.size == 1);\n    assert(lct.subtree_size(0,\
    \ 1) == 3);\n\n    lct.apply(0, 2, 3);\n    assert(lct.path_prod(0, 2).sum ==\
    \ 18);\n    assert(lct.subtree_prod(0, 1).sum == 10);\n\n    lct.apply(1, 2, 2);\n\
    \    assert(lct.get_edge(e01).sum == 8);\n    assert(lct.get_edge(e12).sum ==\
    \ 12);\n    assert(lct.subtree_prod(0, 0).sum == 20);\n\n    assert(lct.cut_edge(e01));\n\
    \    assert(!lct.connected(0, 2));\n}\n\nbool naive_connected(const std::vector<std::vector<int>>&\
    \ adj, int s, int t) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[s] = s;\n    stack.push_back(s);\n    for (int it = 0; it\
    \ < int(stack.size()); it++) {\n        int v = stack[it];\n        if (v == t)\
    \ return true;\n        for (int to : adj[v]) {\n            if (parent[to] !=\
    \ -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    return false;\n}\n\nstd::vector<int> naive_path_vertices(const\
    \ std::vector<std::vector<int>>& adj, int s, int t) {\n    std::vector<int> parent(adj.size(),\
    \ -1);\n    std::vector<int> stack;\n    parent[s] = s;\n    stack.push_back(s);\n\
    \    for (int it = 0; it < int(stack.size()); it++) {\n        int v = stack[it];\n\
    \        if (v == t) break;\n        for (int to : adj[v]) {\n            if (parent[to]\
    \ != -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    assert(parent[t] != -1);\n    std::vector<int> path;\n\
    \    for (int v = t; v != s; v = parent[v]) path.push_back(v);\n    path.push_back(s);\n\
    \    return path;\n}\n\nlong long naive_path_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int s, int t) {\n    long long res\
    \ = 0;\n    for (int v : naive_path_vertices(adj, s, t)) res += value[v];\n  \
    \  return res;\n}\n\nlong long naive_subtree_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int root,\n                      \
    \      int v) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[root] = root;\n    stack.push_back(root);\n    for (int it\
    \ = 0; it < int(stack.size()); it++) {\n        int x = stack[it];\n        for\
    \ (int to : adj[x]) {\n            if (parent[to] != -1) continue;\n         \
    \   parent[to] = x;\n            stack.push_back(to);\n        }\n    }\n    assert(parent[v]\
    \ != -1);\n\n    long long res = 0;\n    stack.clear();\n    stack.push_back(v);\n\
    \    while (!stack.empty()) {\n        int x = stack.back();\n        stack.pop_back();\n\
    \        res += value[x];\n        for (int to : adj[x]) {\n            if (to\
    \ == parent[x]) continue;\n            stack.push_back(to);\n        }\n    }\n\
    \    return res;\n}\n\nvoid test_random_vertex_path_updates() {\n    constexpr\
    \ int n = 8;\n    std::vector<long long> initial;\n    std::vector<long long>\
    \ value;\n    for (int i = 0; i < n; i++) {\n        initial.push_back(i + 1);\n\
    \        value.push_back(i + 1);\n    }\n    m1une::data_structure::LazyLinkedCutTree<AddSum>\
    \ lct(initial);\n    std::vector<std::vector<int>> adj(n);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    std::mt19937 rng(2);\n\n    for (int step = 0; step < 700;\
    \ step++) {\n        int op = int(rng() % 6);\n        int u = int(rng() % n);\n\
    \        int v = int(rng() % n);\n        if (op == 0) {\n            if (u !=\
    \ v && !naive_connected(adj, u, v)) {\n                assert(lct.link(u, v));\n\
    \                adj[u].push_back(v);\n                adj[v].push_back(u);\n\
    \                edges.emplace_back(u, v);\n            }\n        } else if (op\
    \ == 1) {\n            if (!edges.empty()) {\n                int id = int(rng()\
    \ % edges.size());\n                auto [a, b] = edges[id];\n               \
    \ assert(lct.cut(a, b));\n                for (int i = 0; i < int(adj[a].size());\
    \ i++) {\n                    if (adj[a][i] == b) {\n                        adj[a][i]\
    \ = adj[a].back();\n                        adj[a].pop_back();\n             \
    \           break;\n                    }\n                }\n               \
    \ for (int i = 0; i < int(adj[b].size()); i++) {\n                    if (adj[b][i]\
    \ == a) {\n                        adj[b][i] = adj[b].back();\n              \
    \          adj[b].pop_back();\n                        break;\n              \
    \      }\n                }\n                edges[id] = edges.back();\n     \
    \           edges.pop_back();\n            }\n        } else if (op == 2) {\n\
    \            long long x = int(rng() % 200) - 100;\n            value[u] = x;\n\
    \            lct.set(u, x);\n        } else if (u != v && naive_connected(adj,\
    \ u, v)) {\n            if (op == 3) {\n                long long add = int(rng()\
    \ % 21) - 10;\n                lct.apply(u, v, add);\n                for (int\
    \ x : naive_path_vertices(adj, u, v)) value[x] += add;\n            } else if\
    \ (op == 4) {\n                assert(lct.path_prod(u, v).sum == naive_path_sum(adj,\
    \ value, u, v));\n            } else {\n                assert(lct.subtree_prod(u,\
    \ v).sum == naive_subtree_sum(adj, value, u, v));\n                assert(lct.subtree_prod(v,\
    \ u).sum == naive_subtree_sum(adj, value, v, u));\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    test_vertex_path_and_subtree_updates();\n    test_edge_path_and_subtree_updates();\n\
    \    test_random_vertex_path_updates();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - acted_monoid/range_add_range_sum.hpp
  - data_structure/lazy_linked_cut_tree.hpp
  - acted_monoid/concept.hpp
  isVerificationFile: true
  path: verify/data_structure/lazy_linked_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-17 21:02:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/lazy_linked_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/lazy_linked_cut_tree.test.cpp
- /verify/verify/data_structure/lazy_linked_cut_tree.test.cpp.html
title: verify/data_structure/lazy_linked_cut_tree.test.cpp
---
