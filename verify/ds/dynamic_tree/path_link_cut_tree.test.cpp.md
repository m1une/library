---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_tree/path_link_cut_tree.hpp
    title: Path Link-Cut Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
  bundledCode: "#line 1 \"verify/ds/dynamic_tree/path_link_cut_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <string>\n#include <vector>\n\n#line 1 \"ds/dynamic_tree/path_link_cut_tree.hpp\"\
    \n\n\n\n#line 5 \"ds/dynamic_tree/path_link_cut_tree.hpp\"\n#include <concepts>\n\
    #include <type_traits>\n#include <utility>\n#line 9 \"ds/dynamic_tree/path_link_cut_tree.hpp\"\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/dynamic_tree/path_link_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\n\
    template <typename T>\nstruct Add {\n    using value_type = T;\n\n    // Returns\
    \ the identity element for addition, which is 0.\n    static constexpr T id()\
    \ {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return a + b;\n    }\n\n \
    \   static constexpr T inv(const T& x) {\n        return -x;\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n#line 10 \"verify/ds/dynamic_tree/path_link_cut_tree.test.cpp\"\
    \n\nstruct StringConcat {\n    using value_type = std::string;\n\n    static std::string\
    \ id() {\n        return \"\";\n    }\n\n    static std::string op(const std::string&\
    \ a, const std::string& b) {\n        return a + b;\n    }\n};\n\nvoid test_vertex_sum()\
    \ {\n    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long long>> lct(std::vector<int>{1,\
    \ 2, 3, 4, 5});\n\n    assert(lct.size() == 5);\n    assert(!lct.empty());\n \
    \   assert(lct[2] == 3);\n    assert(lct.link(0, 1));\n    assert(lct.link(1,\
    \ 2));\n    assert(lct.link(1, 3));\n    assert(lct.link(3, 4));\n    assert(!lct.link(0,\
    \ 4));\n\n    assert(lct.connected(0, 4));\n    assert(lct.same(2, 4));\n    assert(lct.prod(0,\
    \ 2) == 6);\n    assert(lct.path_prod(2, 4) == 14);\n    assert(lct.path_size(2,\
    \ 4) == 4);\n    assert(lct.kth_vertex(2, 4, 0) == 2);\n    assert(lct.kth_vertex(2,\
    \ 4, 1) == 1);\n    assert(lct.kth_vertex(2, 4, 2) == 3);\n    assert(lct.kth_vertex(2,\
    \ 4, 3) == 4);\n\n    lct.set(1, 10);\n    assert(lct.get(1) == 10);\n    assert(lct.prod(2,\
    \ 4) == 22);\n\n    assert(!lct.cut(0, 2));\n    assert(lct.cut(1, 3));\n    assert(!lct.connected(2,\
    \ 4));\n    assert(lct.link(2, 4));\n    assert(lct.prod(0, 3) == 23);\n\n   \
    \ lct.evert(0);\n    assert(lct.component_root(3) == 0);\n    assert(lct.lca(2,\
    \ 3) == 2);\n}\n\nvoid test_path_order() {\n    m1une::ds::PathLinkCutTree<StringConcat>\
    \ lct(std::vector<std::string>{\"a\", \"b\", \"c\", \"d\"});\n    assert(lct.link(0,\
    \ 1));\n    assert(lct.link(1, 2));\n    assert(lct.link(1, 3));\n\n    assert(lct.prod(0,\
    \ 2) == \"abc\");\n    assert(lct.prod(2, 0) == \"cba\");\n    assert(lct.prod(3,\
    \ 2) == \"dbc\");\n    lct.set(1, \"B\");\n    assert(lct.prod(0, 3) == \"aBd\"\
    );\n}\n\nvoid test_edge_nodes() {\n    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long\
    \ long>> lct(3);\n\n    int e01 = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1,\
    \ 2, 7);\n    assert(e01 == 0);\n    assert(e12 == 1);\n    assert(lct.edge_count()\
    \ == 2);\n    assert(lct.edge_alive(e01));\n    assert((lct.edge_endpoints(e01)\
    \ == std::pair<int, int>(0, 1)));\n    assert(lct.get_edge(e01) == 5);\n    assert(lct.link_edge(0,\
    \ 2, 100) == -1);\n    assert(lct.prod(0, 2) == 12);\n\n    lct.set_edge(e01,\
    \ 10);\n    assert(lct.prod(0, 2) == 17);\n    lct.set_edge(e12, 20);\n    assert(lct.get_edge(e12)\
    \ == 20);\n    assert(lct.prod(0, 2) == 30);\n    assert(lct.cut_edge(e01));\n\
    \    assert(!lct.edge_alive(e01));\n    assert(!lct.cut_edge(e01));\n    assert(!lct.connected(0,\
    \ 2));\n    int e02 = lct.link_edge(0, 2, 1);\n    assert(e02 == 2);\n    assert(lct.prod(0,\
    \ 1) == 21);\n}\n\nint main() {\n    test_vertex_sum();\n    test_path_order();\n\
    \    test_edge_nodes();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <string>\n#include <vector>\n\n#include \"ds/dynamic_tree/path_link_cut_tree.hpp\"\
    \n#include \"monoid/add.hpp\"\n\nstruct StringConcat {\n    using value_type =\
    \ std::string;\n\n    static std::string id() {\n        return \"\";\n    }\n\
    \n    static std::string op(const std::string& a, const std::string& b) {\n  \
    \      return a + b;\n    }\n};\n\nvoid test_vertex_sum() {\n    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long\
    \ long>> lct(std::vector<int>{1, 2, 3, 4, 5});\n\n    assert(lct.size() == 5);\n\
    \    assert(!lct.empty());\n    assert(lct[2] == 3);\n    assert(lct.link(0, 1));\n\
    \    assert(lct.link(1, 2));\n    assert(lct.link(1, 3));\n    assert(lct.link(3,\
    \ 4));\n    assert(!lct.link(0, 4));\n\n    assert(lct.connected(0, 4));\n   \
    \ assert(lct.same(2, 4));\n    assert(lct.prod(0, 2) == 6);\n    assert(lct.path_prod(2,\
    \ 4) == 14);\n    assert(lct.path_size(2, 4) == 4);\n    assert(lct.kth_vertex(2,\
    \ 4, 0) == 2);\n    assert(lct.kth_vertex(2, 4, 1) == 1);\n    assert(lct.kth_vertex(2,\
    \ 4, 2) == 3);\n    assert(lct.kth_vertex(2, 4, 3) == 4);\n\n    lct.set(1, 10);\n\
    \    assert(lct.get(1) == 10);\n    assert(lct.prod(2, 4) == 22);\n\n    assert(!lct.cut(0,\
    \ 2));\n    assert(lct.cut(1, 3));\n    assert(!lct.connected(2, 4));\n    assert(lct.link(2,\
    \ 4));\n    assert(lct.prod(0, 3) == 23);\n\n    lct.evert(0);\n    assert(lct.component_root(3)\
    \ == 0);\n    assert(lct.lca(2, 3) == 2);\n}\n\nvoid test_path_order() {\n   \
    \ m1une::ds::PathLinkCutTree<StringConcat> lct(std::vector<std::string>{\"a\"\
    , \"b\", \"c\", \"d\"});\n    assert(lct.link(0, 1));\n    assert(lct.link(1,\
    \ 2));\n    assert(lct.link(1, 3));\n\n    assert(lct.prod(0, 2) == \"abc\");\n\
    \    assert(lct.prod(2, 0) == \"cba\");\n    assert(lct.prod(3, 2) == \"dbc\"\
    );\n    lct.set(1, \"B\");\n    assert(lct.prod(0, 3) == \"aBd\");\n}\n\nvoid\
    \ test_edge_nodes() {\n    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long\
    \ long>> lct(3);\n\n    int e01 = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1,\
    \ 2, 7);\n    assert(e01 == 0);\n    assert(e12 == 1);\n    assert(lct.edge_count()\
    \ == 2);\n    assert(lct.edge_alive(e01));\n    assert((lct.edge_endpoints(e01)\
    \ == std::pair<int, int>(0, 1)));\n    assert(lct.get_edge(e01) == 5);\n    assert(lct.link_edge(0,\
    \ 2, 100) == -1);\n    assert(lct.prod(0, 2) == 12);\n\n    lct.set_edge(e01,\
    \ 10);\n    assert(lct.prod(0, 2) == 17);\n    lct.set_edge(e12, 20);\n    assert(lct.get_edge(e12)\
    \ == 20);\n    assert(lct.prod(0, 2) == 30);\n    assert(lct.cut_edge(e01));\n\
    \    assert(!lct.edge_alive(e01));\n    assert(!lct.cut_edge(e01));\n    assert(!lct.connected(0,\
    \ 2));\n    int e02 = lct.link_edge(0, 2, 1);\n    assert(e02 == 2);\n    assert(lct.prod(0,\
    \ 1) == 21);\n}\n\nint main() {\n    test_vertex_sum();\n    test_path_order();\n\
    \    test_edge_nodes();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_tree/path_link_cut_tree.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
- /verify/verify/ds/dynamic_tree/path_link_cut_tree.test.cpp.html
title: verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
---
