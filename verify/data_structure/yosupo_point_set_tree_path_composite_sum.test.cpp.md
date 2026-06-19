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
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum
    links:
    - https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum
  bundledCode: "#line 1 \"verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 1 \"data_structure/rake_compress_link_cut_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#line 7 \"data_structure/rake_compress_link_cut_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// Maintains a dynamic forest\
    \ whose tree DP uses two different aggregate types.\n// Point is a commutative\
    \ group for virtual children, while Path is an ordered\n// preferred-path cluster\
    \ and does not need an inverse.\ntemplate <class TreeDPInfo>\nstruct RakeCompressLinkCutTree\
    \ {\n    using Point = typename TreeDPInfo::Point;\n    using Path = typename\
    \ TreeDPInfo::Path;\n    using Vertex = typename TreeDPInfo::Vertex;\n\n   private:\n\
    \    struct Node {\n        int left = -1;\n        int right = -1;\n        int\
    \ parent = -1;\n        bool rev = false;\n        Vertex value;\n        Point\
    \ virtual_prod;\n        Path prod;\n        Path rev_prod;\n\n        explicit\
    \ Node(const Vertex& vertex)\n            : value(vertex),\n              virtual_prod(Point::id()),\n\
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
    \ m1une\n\n\n#line 8 \"verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\ntemplate <class T>\nstruct PointSetTreePathCompositeSum\
    \ {\n    struct Point {\n        T s;\n        T x;\n\n        static Point id()\
    \ {\n            return Point{T(0), T(0)};\n        }\n\n        Point inv() const\
    \ {\n            return Point{T(0) - s, T(0) - x};\n        }\n    };\n\n    struct\
    \ Path {\n        T a;\n        T b;\n        T s;\n        T x;\n    };\n\n \
    \   struct Vertex {\n        bool is_vertex;\n        T x;\n        T y;\n   \
    \ };\n\n    static Path add_vertex(const Point& d, const Vertex& u) {\n      \
    \  if (u.is_vertex) return Path{T(1), T(0), d.s + u.x, d.x + T(1)};\n        return\
    \ Path{u.x, u.y, d.s * u.x + d.x * u.y, d.x};\n    }\n\n    static Point add_edge(const\
    \ Path& path) {\n        return Point{path.s, path.x};\n    }\n\n    static Point\
    \ rake(const Point& a, const Point& b) {\n        return Point{a.s + b.s, a.x\
    \ + b.x};\n    }\n\n    static Path compress(const Path& parent_side, const Path&\
    \ child_side) {\n        return Path{\n            parent_side.a * child_side.a,\n\
    \            parent_side.a * child_side.b + parent_side.b,\n            parent_side.s\
    \ + parent_side.a * child_side.s + parent_side.b * child_side.x,\n           \
    \ parent_side.x + child_side.x\n        };\n    }\n};\n\nint main() {\n    using\
    \ TreeDP = PointSetTreePathCompositeSum<mint>;\n    using Vertex = typename TreeDP::Vertex;\n\
    \    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\n \
    \   std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n\n    LCT lct;\n    std::vector<int> vertex_node(n);\n\
    \    for (int i = 0; i < n; i++) {\n        mint a;\n        std::cin >> a;\n\
    \        vertex_node[i] = lct.add_vertex(Vertex{true, a, mint(0)});\n    }\n\n\
    \    std::vector<int> edge_id(n - 1);\n    for (int i = 0; i + 1 < n; i++) {\n\
    \        int u, v;\n        mint b, c;\n        std::cin >> u >> v >> b >> c;\n\
    \        edge_id[i] = lct.link_edge(\n            vertex_node[u], vertex_node[v],\
    \ Vertex{false, b, c}\n        );\n    }\n\n    for (int i = 0; i < q; i++) {\n\
    \        int type;\n        std::cin >> type;\n        if (type == 0) {\n    \
    \        int w;\n            mint x;\n            std::cin >> w >> x;\n      \
    \      lct.set(vertex_node[w], Vertex{true, x, mint(0)});\n        } else if (type\
    \ == 1) {\n            int e;\n            mint y, z;\n            std::cin >>\
    \ e >> y >> z;\n            lct.set_edge(edge_id[e], Vertex{false, y, z});\n \
    \       } else {\n            int w;\n            std::cin >> w;\n           \
    \ std::cout << lct.component_prod(vertex_node[w]).s << '\\n';\n        }\n   \
    \ }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"data_structure/rake_compress_link_cut_tree.hpp\"\
    \n#include \"math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \ntemplate <class T>\nstruct PointSetTreePathCompositeSum {\n    struct Point\
    \ {\n        T s;\n        T x;\n\n        static Point id() {\n            return\
    \ Point{T(0), T(0)};\n        }\n\n        Point inv() const {\n            return\
    \ Point{T(0) - s, T(0) - x};\n        }\n    };\n\n    struct Path {\n       \
    \ T a;\n        T b;\n        T s;\n        T x;\n    };\n\n    struct Vertex\
    \ {\n        bool is_vertex;\n        T x;\n        T y;\n    };\n\n    static\
    \ Path add_vertex(const Point& d, const Vertex& u) {\n        if (u.is_vertex)\
    \ return Path{T(1), T(0), d.s + u.x, d.x + T(1)};\n        return Path{u.x, u.y,\
    \ d.s * u.x + d.x * u.y, d.x};\n    }\n\n    static Point add_edge(const Path&\
    \ path) {\n        return Point{path.s, path.x};\n    }\n\n    static Point rake(const\
    \ Point& a, const Point& b) {\n        return Point{a.s + b.s, a.x + b.x};\n \
    \   }\n\n    static Path compress(const Path& parent_side, const Path& child_side)\
    \ {\n        return Path{\n            parent_side.a * child_side.a,\n       \
    \     parent_side.a * child_side.b + parent_side.b,\n            parent_side.s\
    \ + parent_side.a * child_side.s + parent_side.b * child_side.x,\n           \
    \ parent_side.x + child_side.x\n        };\n    }\n};\n\nint main() {\n    using\
    \ TreeDP = PointSetTreePathCompositeSum<mint>;\n    using Vertex = typename TreeDP::Vertex;\n\
    \    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;\n\n \
    \   std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n\n    LCT lct;\n    std::vector<int> vertex_node(n);\n\
    \    for (int i = 0; i < n; i++) {\n        mint a;\n        std::cin >> a;\n\
    \        vertex_node[i] = lct.add_vertex(Vertex{true, a, mint(0)});\n    }\n\n\
    \    std::vector<int> edge_id(n - 1);\n    for (int i = 0; i + 1 < n; i++) {\n\
    \        int u, v;\n        mint b, c;\n        std::cin >> u >> v >> b >> c;\n\
    \        edge_id[i] = lct.link_edge(\n            vertex_node[u], vertex_node[v],\
    \ Vertex{false, b, c}\n        );\n    }\n\n    for (int i = 0; i < q; i++) {\n\
    \        int type;\n        std::cin >> type;\n        if (type == 0) {\n    \
    \        int w;\n            mint x;\n            std::cin >> w >> x;\n      \
    \      lct.set(vertex_node[w], Vertex{true, x, mint(0)});\n        } else if (type\
    \ == 1) {\n            int e;\n            mint y, z;\n            std::cin >>\
    \ e >> y >> z;\n            lct.set_edge(edge_id[e], Vertex{false, y, z});\n \
    \       } else {\n            int w;\n            std::cin >> w;\n           \
    \ std::cout << lct.component_prod(vertex_node[w]).s << '\\n';\n        }\n   \
    \ }\n}\n"
  dependsOn:
  - data_structure/rake_compress_link_cut_tree.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 15:58:28+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
- /verify/verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp.html
title: verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
---
