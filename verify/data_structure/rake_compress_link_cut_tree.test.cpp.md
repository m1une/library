---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/rake_compress_link_cut_tree.hpp
    title: Rake-Compress Link-Cut Tree
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
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
  bundledCode: "#line 1 \"verify/data_structure/rake_compress_link_cut_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"data_structure/rake_compress_link_cut_tree.hpp\"\n\n\n\n#line 7 \"\
    data_structure/rake_compress_link_cut_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\n// Maintains a dynamic forest whose tree DP uses two different\
    \ aggregate types.\n// Point is a commutative group for virtual children, while\
    \ Path is an ordered\n// preferred-path cluster and does not need an inverse.\n\
    template <class TreeDPInfo>\nstruct RakeCompressLinkCutTree {\n    using Point\
    \ = typename TreeDPInfo::Point;\n    using Path = typename TreeDPInfo::Path;\n\
    \    using Vertex = typename TreeDPInfo::Vertex;\n\n   private:\n    struct Node\
    \ {\n        int left = -1;\n        int right = -1;\n        int parent = -1;\n\
    \        bool rev = false;\n        Vertex value;\n        Point virtual_prod;\n\
    \        Path prod;\n        Path rev_prod;\n\n        explicit Node(const Vertex&\
    \ vertex)\n            : value(vertex),\n              virtual_prod(Point::id()),\n\
    \              prod(TreeDPInfo::add_vertex(virtual_prod, value)),\n          \
    \    rev_prod(prod) {}\n    };\n\n    struct EdgeInfo {\n        int u = -1;\n\
    \        int v = -1;\n        int node = -1;\n        bool alive = false;\n  \
    \  };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo> _edges;\n  \
    \  std::vector<int> _path_buffer;\n\n    bool is_splay_root(int node) const {\n\
    \        int parent = _nodes[node].parent;\n        return parent == -1 || (_nodes[parent].left\
    \ != node && _nodes[parent].right != node);\n    }\n\n    void update(int node)\
    \ {\n        Node& x = _nodes[node];\n        Path self = TreeDPInfo::add_vertex(x.virtual_prod,\
    \ x.value);\n        x.prod = self;\n        x.rev_prod = self;\n\n        if\
    \ (x.left != -1) {\n            x.prod = TreeDPInfo::compress(_nodes[x.left].prod,\
    \ x.prod);\n            x.rev_prod = TreeDPInfo::compress(x.rev_prod, _nodes[x.left].rev_prod);\n\
    \        }\n        if (x.right != -1) {\n            x.prod = TreeDPInfo::compress(x.prod,\
    \ _nodes[x.right].prod);\n            x.rev_prod = TreeDPInfo::compress(_nodes[x.right].rev_prod,\
    \ x.rev_prod);\n        }\n    }\n\n    void add_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::add_edge(_nodes[child].prod);\n\
    \        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod,\
    \ contribution);\n    }\n\n    void remove_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::add_edge(_nodes[child].prod);\n\
    \        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod,\
    \ contribution.inv());\n    }\n\n    void apply_reverse(int node) {\n        if\
    \ (node == -1) return;\n        Node& x = _nodes[node];\n        std::swap(x.left,\
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
    \ {\n            splay(cur);\n            add_virtual_child(cur, _nodes[cur].right);\n\
    \            remove_virtual_child(cur, last);\n            _nodes[cur].right =\
    \ last;\n            if (last != -1) _nodes[last].parent = cur;\n            update(cur);\n\
    \            last = cur;\n        }\n        splay(node);\n        return last;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < int(_nodes.size()));\n\
    \    }\n\n    void check_edge(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    RakeCompressLinkCutTree()\
    \ = default;\n\n    explicit RakeCompressLinkCutTree(const std::vector<Vertex>&\
    \ values) {\n        _nodes.reserve(values.size());\n        for (const Vertex&\
    \ value : values) add_vertex(value);\n    }\n\n    int size() const {\n      \
    \  return int(_nodes.size());\n    }\n\n    bool empty() const {\n        return\
    \ _nodes.empty();\n    }\n\n    int add_vertex(const Vertex& vertex) {\n     \
    \   _nodes.emplace_back(vertex);\n        return int(_nodes.size()) - 1;\n   \
    \ }\n\n    int edge_count() const {\n        return int(_edges.size());\n    }\n\
    \n    bool edge_alive(int edge_id) const {\n        check_edge(edge_id);\n   \
    \     return _edges[edge_id].alive;\n    }\n\n    int edge_node(int edge_id) const\
    \ {\n        check_edge(edge_id);\n        return _edges[edge_id].node;\n    }\n\
    \n    std::pair<int, int> edge_endpoints(int edge_id) const {\n        check_edge(edge_id);\n\
    \        return {_edges[edge_id].u, _edges[edge_id].v};\n    }\n\n    const Vertex&\
    \ get(int v) const {\n        check_vertex(v);\n        return _nodes[v].value;\n\
    \    }\n\n    const Vertex& operator[](int v) const {\n        return get(v);\n\
    \    }\n\n    void set(int v, const Vertex& vertex) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = vertex;\n        update(v);\n \
    \   }\n\n    // Makes v the represented root of its component.\n    void evert(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        apply_reverse(v);\n\
    \    }\n\n    void reroot(int v) {\n        evert(v);\n    }\n\n    int component_root(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        int cur = v;\n \
    \       push(cur);\n        while (_nodes[cur].left != -1) {\n            cur\
    \ = _nodes[cur].left;\n            push(cur);\n        }\n        splay(cur);\n\
    \        return cur;\n    }\n\n    int root(int v) {\n        return component_root(v);\n\
    \    }\n\n    bool connected(int u, int v) {\n        check_vertex(u);\n     \
    \   check_vertex(v);\n        if (u == v) return true;\n        return component_root(u)\
    \ == component_root(v);\n    }\n\n    bool same(int u, int v) {\n        return\
    \ connected(u, v);\n    }\n\n    // Links two different components and returns\
    \ whether an edge was added.\n    bool link(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v) return false;\n        evert(u);\n\
    \        if (component_root(v) == u) return false;\n        access(v);\n     \
    \   _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    bool link_parent(int child, int parent) {\n\
    \        return link(child, parent);\n    }\n\n    int link_edge(int u, int v,\
    \ const Vertex& edge_vertex) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(edge_vertex);\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    // Cuts\
    \ the represented-tree edge (u, v), if it exists.\n    bool cut(int u, int v)\
    \ {\n        check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ false;\n        evert(u);\n        access(v);\n        if (_nodes[v].left !=\
    \ u || _nodes[u].right != -1) return false;\n        _nodes[v].left = -1;\n  \
    \      _nodes[u].parent = -1;\n        update(v);\n        return true;\n    }\n\
    \n    // Cuts the parent edge of v in the current represented-root orientation.\n\
    \    bool cut_parent(int v) {\n        check_vertex(v);\n        access(v);\n\
    \        int left = _nodes[v].left;\n        if (left == -1) return false;\n \
    \       _nodes[v].left = -1;\n        _nodes[left].parent = -1;\n        update(v);\n\
    \        return true;\n    }\n\n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n\
    \        EdgeInfo& edge = _edges[edge_id];\n        if (!edge.alive) return false;\n\
    \        bool ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node,\
    \ edge.v);\n        if (ok1 && ok2) edge.alive = false;\n        return ok1 &&\
    \ ok2;\n    }\n\n    const Vertex& get_edge(int edge_id) const {\n        return\
    \ get(edge_node(edge_id));\n    }\n\n    void set_edge(int edge_id, const Vertex&\
    \ edge_vertex) {\n        set(edge_node(edge_id), edge_vertex);\n    }\n\n   \
    \ // Reroots the represented tree at v and returns its whole-tree cluster.\n \
    \   Path component_prod(int v) {\n        evert(v);\n        return _nodes[v].prod;\n\
    \    }\n\n    Path query_component(int v) {\n        return component_prod(v);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#include <cstdint>\n#line 7 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr\
    \ uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr ModInt\
    \ raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n        return\
    \ x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    constexpr ModInt(int\
    \ v) noexcept {\n        long long x = (long long)(v % (long long)(Modulus));\n\
    \        if (x < 0) x += Modulus;\n        _v = static_cast<uint32_t>(x);\n  \
    \  }\n\n    constexpr ModInt(long long v) noexcept {\n        long long x = (long\
    \ long)(v % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n       \
    \ _v = static_cast<uint32_t>(x);\n    }\n\n    constexpr ModInt(unsigned int v)\
    \ noexcept {\n        _v = static_cast<uint32_t>(v % Modulus);\n    }\n\n    constexpr\
    \ uint32_t val() const noexcept {\n        return _v;\n    }\n\n    constexpr\
    \ ModInt& operator++() noexcept {\n        _v++;\n        if (_v == Modulus) _v\
    \ = 0;\n        return *this;\n    }\n\n    constexpr ModInt& operator--() noexcept\
    \ {\n        if (_v == 0) _v = Modulus;\n        _v--;\n        return *this;\n\
    \    }\n\n    constexpr ModInt operator++(int) noexcept {\n        ModInt res\
    \ = *this;\n        ++*this;\n        return res;\n    }\n\n    constexpr ModInt\
    \ operator--(int) noexcept {\n        ModInt res = *this;\n        --*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt& operator+=(const ModInt&\
    \ rhs) noexcept {\n        _v += rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator-=(const ModInt&\
    \ rhs) noexcept {\n        _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt&\
    \ rhs) noexcept {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v\
    \ = static_cast<uint32_t>(z % Modulus);\n        return *this;\n    }\n\n    constexpr\
    \ ModInt& operator/=(const ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n\
    \    }\n\n    constexpr ModInt operator+(const ModInt& rhs) const noexcept {\n\
    \        return ModInt(*this) += rhs;\n    }\n    constexpr ModInt operator-(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) -= rhs;\n    }\n\
    \    constexpr ModInt operator*(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) *= rhs;\n    }\n    constexpr ModInt operator/(const ModInt& rhs)\
    \ const noexcept {\n        return ModInt(*this) /= rhs;\n    }\n\n    constexpr\
    \ bool operator==(const ModInt& rhs) const noexcept {\n        return _v == rhs._v;\n\
    \    }\n    constexpr bool operator!=(const ModInt& rhs) const noexcept {\n  \
    \      return _v != rhs._v;\n    }\n\n    constexpr ModInt pow(long long n) const\
    \ noexcept {\n        ModInt res = raw(1), x = *this;\n        while (n > 0) {\n\
    \            if (n & 1) res *= x;\n            x *= x;\n            n >>= 1;\n\
    \        }\n        return res;\n    }\n\n    constexpr ModInt inv() const noexcept\
    \ {\n        int32_t a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n\
    \            int32_t t = a / b;\n            a -= t * b;\n            std::swap(a,\
    \ b);\n            u -= t * v;\n            std::swap(u, v);\n        }\n    \
    \    if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/data_structure/rake_compress_link_cut_tree.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\ntemplate <class T>\nstruct AffineTreeSum\
    \ {\n    struct Point {\n        T s;\n        T x;\n\n        Point() = delete;\n\
    \n        Point(T s_, T x_) : s(s_), x(x_) {}\n\n        static Point id() {\n\
    \            return Point{T(0), T(0)};\n        }\n\n        Point inv() const\
    \ {\n            return Point{T(0) - s, T(0) - x};\n        }\n    };\n\n    struct\
    \ Path {\n        T a;\n        T b;\n        T s;\n        T x;\n\n        Path()\
    \ = delete;\n\n        Path(T a_, T b_, T s_, T x_) : a(a_), b(b_), s(s_), x(x_)\
    \ {}\n    };\n\n    struct Vertex {\n        bool is_vertex;\n        T x;\n \
    \       T y;\n\n        Vertex() = delete;\n\n        Vertex(bool is_vertex_,\
    \ T x_, T y_) : is_vertex(is_vertex_), x(x_), y(y_) {}\n    };\n\n    static Path\
    \ add_vertex(const Point& d, const Vertex& u) {\n        if (u.is_vertex) return\
    \ Path{T(1), T(0), d.s + u.x, d.x + T(1)};\n        return Path{u.x, u.y, d.s\
    \ * u.x + d.x * u.y, d.x};\n    }\n\n    static Point add_edge(const Path& path)\
    \ {\n        return Point{path.s, path.x};\n    }\n\n    static Point rake(const\
    \ Point& a, const Point& b) {\n        return Point{a.s + b.s, a.x + b.x};\n \
    \   }\n\n    static Path compress(const Path& parent_side, const Path& child_side)\
    \ {\n        return Path{\n            parent_side.a * child_side.a,\n       \
    \     parent_side.a * child_side.b + parent_side.b,\n            parent_side.s\
    \ + parent_side.a * child_side.s + parent_side.b * child_side.x,\n           \
    \ parent_side.x + child_side.x\n        };\n    }\n};\n\nstruct Edge {\n    int\
    \ u;\n    int v;\n    mint a;\n    mint b;\n};\n\nstruct AdjEdge {\n    int to;\n\
    \    int id;\n};\n\nstd::pair<mint, int> naive_dfs(\n    int v,\n    int parent,\n\
    \    const std::vector<mint>& value,\n    const std::vector<Edge>& edges,\n  \
    \  const std::vector<std::vector<AdjEdge>>& graph\n) {\n    mint sum = value[v];\n\
    \    int count = 1;\n    for (const AdjEdge& e : graph[v]) {\n        if (e.to\
    \ == parent) continue;\n        auto child = naive_dfs(e.to, v, value, edges,\
    \ graph);\n        const Edge& edge = edges[e.id];\n        sum += edge.a * child.first\
    \ + edge.b * mint(child.second);\n        count += child.second;\n    }\n    return\
    \ {sum, count};\n}\n\nvoid test_random_updates() {\n    using TreeDP = AffineTreeSum<mint>;\n\
    \    using Vertex = typename TreeDP::Vertex;\n    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\
    \n    constexpr int n = 12;\n    std::mt19937 rng(712367);\n    std::vector<mint>\
    \ value(n);\n    std::vector<int> vertex_node(n);\n    std::vector<Edge> edges;\n\
    \    std::vector<std::vector<AdjEdge>> graph(n);\n    LCT lct;\n\n    for (int\
    \ i = 0; i < n; i++) {\n        value[i] = mint(int(rng() % 100));\n        vertex_node[i]\
    \ = lct.add_vertex(Vertex{true, value[i], mint(0)});\n    }\n\n    for (int v\
    \ = 1; v < n; v++) {\n        int parent = int(rng() % v);\n        mint a = mint(int(rng()\
    \ % 5));\n        mint b = mint(int(rng() % 100));\n        int id = int(edges.size());\n\
    \        edges.push_back(Edge{parent, v, a, b});\n        graph[parent].push_back(AdjEdge{v,\
    \ id});\n        graph[v].push_back(AdjEdge{parent, id});\n        assert(lct.link_edge(vertex_node[parent],\
    \ vertex_node[v], Vertex{false, a, b}) == id);\n    }\n\n    for (int step = 0;\
    \ step < 4000; step++) {\n        int type = int(rng() % 3);\n        if (type\
    \ == 0) {\n            int v = int(rng() % n);\n            value[v] = mint(int(rng()\
    \ % 1000));\n            lct.set(vertex_node[v], Vertex{true, value[v], mint(0)});\n\
    \        } else if (type == 1) {\n            int id = int(rng() % edges.size());\n\
    \            edges[id].a = mint(int(rng() % 5));\n            edges[id].b = mint(int(rng()\
    \ % 1000));\n            lct.set_edge(id, Vertex{false, edges[id].a, edges[id].b});\n\
    \        } else {\n            int root = int(rng() % n);\n            mint expected\
    \ = naive_dfs(root, -1, value, edges, graph).first;\n            assert(lct.component_prod(vertex_node[root]).s\
    \ == expected);\n        }\n    }\n}\n\nvoid test_cut_and_link() {\n    using\
    \ TreeDP = AffineTreeSum<mint>;\n    using Vertex = typename TreeDP::Vertex;\n\
    \    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\n \
    \   LCT lct;\n    int a = lct.add_vertex(Vertex{true, mint(2), mint(0)});\n  \
    \  int b = lct.add_vertex(Vertex{true, mint(3), mint(0)});\n    int c = lct.add_vertex(Vertex{true,\
    \ mint(5), mint(0)});\n    int e0 = lct.link_edge(a, b, Vertex{false, mint(0),\
    \ mint(7)});\n    int e1 = lct.link_edge(b, c, Vertex{false, mint(2), mint(1)});\n\
    \n    assert(lct.component_prod(a).s == mint(16));\n    assert(lct.component_prod(c).s\
    \ == mint(27));\n    assert(lct.cut_edge(e0));\n    assert(!lct.connected(a, c));\n\
    \    assert(lct.component_prod(a).s == mint(2));\n    assert(lct.component_prod(c).s\
    \ == mint(12));\n    assert(lct.link(a, lct.edge_node(e0)));\n    assert(lct.link(lct.edge_node(e0),\
    \ b));\n    assert(lct.connected(a, c));\n    assert(lct.component_prod(a).s ==\
    \ mint(16));\n    (void)e1;\n}\n\nint main() {\n    test_random_updates();\n \
    \   test_cut_and_link();\n\n    long long a, b;\n    std::cin >> a >> b;\n   \
    \ std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#include \"data_structure/rake_compress_link_cut_tree.hpp\"\n#include \"math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\ntemplate <class T>\nstruct AffineTreeSum\
    \ {\n    struct Point {\n        T s;\n        T x;\n\n        Point() = delete;\n\
    \n        Point(T s_, T x_) : s(s_), x(x_) {}\n\n        static Point id() {\n\
    \            return Point{T(0), T(0)};\n        }\n\n        Point inv() const\
    \ {\n            return Point{T(0) - s, T(0) - x};\n        }\n    };\n\n    struct\
    \ Path {\n        T a;\n        T b;\n        T s;\n        T x;\n\n        Path()\
    \ = delete;\n\n        Path(T a_, T b_, T s_, T x_) : a(a_), b(b_), s(s_), x(x_)\
    \ {}\n    };\n\n    struct Vertex {\n        bool is_vertex;\n        T x;\n \
    \       T y;\n\n        Vertex() = delete;\n\n        Vertex(bool is_vertex_,\
    \ T x_, T y_) : is_vertex(is_vertex_), x(x_), y(y_) {}\n    };\n\n    static Path\
    \ add_vertex(const Point& d, const Vertex& u) {\n        if (u.is_vertex) return\
    \ Path{T(1), T(0), d.s + u.x, d.x + T(1)};\n        return Path{u.x, u.y, d.s\
    \ * u.x + d.x * u.y, d.x};\n    }\n\n    static Point add_edge(const Path& path)\
    \ {\n        return Point{path.s, path.x};\n    }\n\n    static Point rake(const\
    \ Point& a, const Point& b) {\n        return Point{a.s + b.s, a.x + b.x};\n \
    \   }\n\n    static Path compress(const Path& parent_side, const Path& child_side)\
    \ {\n        return Path{\n            parent_side.a * child_side.a,\n       \
    \     parent_side.a * child_side.b + parent_side.b,\n            parent_side.s\
    \ + parent_side.a * child_side.s + parent_side.b * child_side.x,\n           \
    \ parent_side.x + child_side.x\n        };\n    }\n};\n\nstruct Edge {\n    int\
    \ u;\n    int v;\n    mint a;\n    mint b;\n};\n\nstruct AdjEdge {\n    int to;\n\
    \    int id;\n};\n\nstd::pair<mint, int> naive_dfs(\n    int v,\n    int parent,\n\
    \    const std::vector<mint>& value,\n    const std::vector<Edge>& edges,\n  \
    \  const std::vector<std::vector<AdjEdge>>& graph\n) {\n    mint sum = value[v];\n\
    \    int count = 1;\n    for (const AdjEdge& e : graph[v]) {\n        if (e.to\
    \ == parent) continue;\n        auto child = naive_dfs(e.to, v, value, edges,\
    \ graph);\n        const Edge& edge = edges[e.id];\n        sum += edge.a * child.first\
    \ + edge.b * mint(child.second);\n        count += child.second;\n    }\n    return\
    \ {sum, count};\n}\n\nvoid test_random_updates() {\n    using TreeDP = AffineTreeSum<mint>;\n\
    \    using Vertex = typename TreeDP::Vertex;\n    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\
    \n    constexpr int n = 12;\n    std::mt19937 rng(712367);\n    std::vector<mint>\
    \ value(n);\n    std::vector<int> vertex_node(n);\n    std::vector<Edge> edges;\n\
    \    std::vector<std::vector<AdjEdge>> graph(n);\n    LCT lct;\n\n    for (int\
    \ i = 0; i < n; i++) {\n        value[i] = mint(int(rng() % 100));\n        vertex_node[i]\
    \ = lct.add_vertex(Vertex{true, value[i], mint(0)});\n    }\n\n    for (int v\
    \ = 1; v < n; v++) {\n        int parent = int(rng() % v);\n        mint a = mint(int(rng()\
    \ % 5));\n        mint b = mint(int(rng() % 100));\n        int id = int(edges.size());\n\
    \        edges.push_back(Edge{parent, v, a, b});\n        graph[parent].push_back(AdjEdge{v,\
    \ id});\n        graph[v].push_back(AdjEdge{parent, id});\n        assert(lct.link_edge(vertex_node[parent],\
    \ vertex_node[v], Vertex{false, a, b}) == id);\n    }\n\n    for (int step = 0;\
    \ step < 4000; step++) {\n        int type = int(rng() % 3);\n        if (type\
    \ == 0) {\n            int v = int(rng() % n);\n            value[v] = mint(int(rng()\
    \ % 1000));\n            lct.set(vertex_node[v], Vertex{true, value[v], mint(0)});\n\
    \        } else if (type == 1) {\n            int id = int(rng() % edges.size());\n\
    \            edges[id].a = mint(int(rng() % 5));\n            edges[id].b = mint(int(rng()\
    \ % 1000));\n            lct.set_edge(id, Vertex{false, edges[id].a, edges[id].b});\n\
    \        } else {\n            int root = int(rng() % n);\n            mint expected\
    \ = naive_dfs(root, -1, value, edges, graph).first;\n            assert(lct.component_prod(vertex_node[root]).s\
    \ == expected);\n        }\n    }\n}\n\nvoid test_cut_and_link() {\n    using\
    \ TreeDP = AffineTreeSum<mint>;\n    using Vertex = typename TreeDP::Vertex;\n\
    \    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\n \
    \   LCT lct;\n    int a = lct.add_vertex(Vertex{true, mint(2), mint(0)});\n  \
    \  int b = lct.add_vertex(Vertex{true, mint(3), mint(0)});\n    int c = lct.add_vertex(Vertex{true,\
    \ mint(5), mint(0)});\n    int e0 = lct.link_edge(a, b, Vertex{false, mint(0),\
    \ mint(7)});\n    int e1 = lct.link_edge(b, c, Vertex{false, mint(2), mint(1)});\n\
    \n    assert(lct.component_prod(a).s == mint(16));\n    assert(lct.component_prod(c).s\
    \ == mint(27));\n    assert(lct.cut_edge(e0));\n    assert(!lct.connected(a, c));\n\
    \    assert(lct.component_prod(a).s == mint(2));\n    assert(lct.component_prod(c).s\
    \ == mint(12));\n    assert(lct.link(a, lct.edge_node(e0)));\n    assert(lct.link(lct.edge_node(e0),\
    \ b));\n    assert(lct.connected(a, c));\n    assert(lct.component_prod(a).s ==\
    \ mint(16));\n    (void)e1;\n}\n\nint main() {\n    test_random_updates();\n \
    \   test_cut_and_link();\n\n    long long a, b;\n    std::cin >> a >> b;\n   \
    \ std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - data_structure/rake_compress_link_cut_tree.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/data_structure/rake_compress_link_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 15:58:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/rake_compress_link_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/rake_compress_link_cut_tree.test.cpp
- /verify/verify/data_structure/rake_compress_link_cut_tree.test.cpp.html
title: verify/data_structure/rake_compress_link_cut_tree.test.cpp
---
