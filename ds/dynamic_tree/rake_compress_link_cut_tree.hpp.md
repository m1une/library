---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/rake_compress_link_cut_tree.test.cpp
    title: verify/ds/dynamic_tree/rake_compress_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/yosupo_point_set_tree_path_composite_sum.test.cpp
    title: verify/ds/dynamic_tree/yosupo_point_set_tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_tree/rake_compress_link_cut_tree.hpp\"\n\n\n\n\
    #include <cassert>\n#include <utility>\n#include <variant>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Maintains a dynamic forest whose tree\
    \ DP uses two different aggregate types.\n// Point is a commutative group for\
    \ virtual children, while Path is an ordered\n// preferred-path cluster and does\
    \ not need an inverse.\ntemplate <class TreeDPInfo>\nstruct RakeCompressLinkCutTree\
    \ {\n    using Point = typename TreeDPInfo::Point;\n    using Path = typename\
    \ TreeDPInfo::Path;\n    using VertexValue = typename TreeDPInfo::VertexValue;\n\
    \    using EdgeValue = typename TreeDPInfo::EdgeValue;\n    using VertexId = int;\n\
    \    using EdgeId = int;\n\n   private:\n    struct Node {\n        int left =\
    \ -1;\n        int right = -1;\n        int parent = -1;\n        bool rev = false;\n\
    \        std::variant<VertexValue, EdgeValue> value;\n        Point virtual_prod;\n\
    \        Path prod;\n        Path rev_prod;\n\n        explicit Node(const VertexValue&\
    \ vertex_value)\n            : value(std::in_place_index<0>, vertex_value),\n\
    \              virtual_prod(Point::id()),\n              prod(TreeDPInfo::make_vertex_path(virtual_prod,\
    \ vertex_value)),\n              rev_prod(prod) {}\n\n        explicit Node(std::in_place_index_t<1>,\
    \ const EdgeValue& edge_value)\n            : value(std::in_place_index<1>, edge_value),\n\
    \              virtual_prod(Point::id()),\n              prod(TreeDPInfo::make_edge_path(virtual_prod,\
    \ edge_value)),\n              rev_prod(prod) {}\n    };\n\n    struct OriginalEdge\
    \ {\n        VertexId u = -1;\n        VertexId v = -1;\n        int node = -1;\n\
    \        bool alive = false;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _vertex_nodes;\n    std::vector<OriginalEdge> _edges;\n    std::vector<int>\
    \ _path_buffer;\n\n    bool is_splay_root(int node) const {\n        int parent\
    \ = _nodes[node].parent;\n        return parent == -1 || (_nodes[parent].left\
    \ != node && _nodes[parent].right != node);\n    }\n\n    void update(int node)\
    \ {\n        Node& x = _nodes[node];\n        Path self = x.value.index() == 0\n\
    \            ? TreeDPInfo::make_vertex_path(x.virtual_prod, std::get<0>(x.value))\n\
    \            : TreeDPInfo::make_edge_path(x.virtual_prod, std::get<1>(x.value));\n\
    \        x.prod = self;\n        x.rev_prod = self;\n\n        if (x.left != -1)\
    \ {\n            x.prod = TreeDPInfo::compress(_nodes[x.left].prod, x.prod);\n\
    \            x.rev_prod = TreeDPInfo::compress(x.rev_prod, _nodes[x.left].rev_prod);\n\
    \        }\n        if (x.right != -1) {\n            x.prod = TreeDPInfo::compress(x.prod,\
    \ _nodes[x.right].prod);\n            x.rev_prod = TreeDPInfo::compress(_nodes[x.right].rev_prod,\
    \ x.rev_prod);\n        }\n    }\n\n    void add_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);\n\
    \        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod,\
    \ contribution);\n    }\n\n    void remove_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);\n\
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
    \    }\n\n    void check_node(int node) const {\n        assert(0 <= node && node\
    \ < int(_nodes.size()));\n    }\n\n    void check_vertex(VertexId vertex) const\
    \ {\n        assert(0 <= vertex && vertex < int(_vertex_nodes.size()));\n    }\n\
    \n    void check_edge(EdgeId edge_id) const {\n        assert(0 <= edge_id &&\
    \ edge_id < int(_edges.size()));\n    }\n\n    int vertex_node(VertexId vertex)\
    \ const {\n        check_vertex(vertex);\n        return _vertex_nodes[vertex];\n\
    \    }\n\n    int add_edge_node(const EdgeValue& edge_value) {\n        _nodes.emplace_back(std::in_place_index<1>,\
    \ edge_value);\n        return int(_nodes.size()) - 1;\n    }\n\n    void set_vertex_node_value(int\
    \ node, const VertexValue& vertex_value) {\n        check_node(node);\n      \
    \  access(node);\n        _nodes[node].value.template emplace<0>(vertex_value);\n\
    \        update(node);\n    }\n\n    void set_edge_node_value(int node, const\
    \ EdgeValue& edge_value) {\n        check_node(node);\n        access(node);\n\
    \        _nodes[node].value.template emplace<1>(edge_value);\n        update(node);\n\
    \    }\n\n    void evert_node(int node) {\n        check_node(node);\n       \
    \ access(node);\n        apply_reverse(node);\n    }\n\n    int component_root_node(int\
    \ node) {\n        check_node(node);\n        access(node);\n        int cur =\
    \ node;\n        push(cur);\n        while (_nodes[cur].left != -1) {\n      \
    \      cur = _nodes[cur].left;\n            push(cur);\n        }\n        splay(cur);\n\
    \        return cur;\n    }\n\n    bool connected_nodes(int u, int v) {\n    \
    \    if (u == v) return true;\n        return component_root_node(u) == component_root_node(v);\n\
    \    }\n\n    bool link_nodes(int u, int v) {\n        check_node(u);\n      \
    \  check_node(v);\n        if (u == v) return false;\n        evert_node(u);\n\
    \        if (component_root_node(v) == u) return false;\n        access(v);\n\
    \        _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    bool cut_nodes(int u, int v) {\n        check_node(u);\n\
    \        check_node(v);\n        if (u == v) return false;\n        evert_node(u);\n\
    \        access(v);\n        if (_nodes[v].left != u || _nodes[u].right != -1)\
    \ return false;\n        _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n\
    \        update(v);\n        return true;\n    }\n\n   public:\n    RakeCompressLinkCutTree()\
    \ = default;\n\n    explicit RakeCompressLinkCutTree(const std::vector<VertexValue>&\
    \ values) {\n        _nodes.reserve(values.size());\n        _vertex_nodes.reserve(values.size());\n\
    \        for (const VertexValue& value : values) add_vertex(value);\n    }\n\n\
    \    int vertex_count() const {\n        return int(_vertex_nodes.size());\n \
    \   }\n\n    bool empty() const {\n        return _vertex_nodes.empty();\n   \
    \ }\n\n    VertexId add_vertex(const VertexValue& vertex_value) {\n        VertexValue\
    \ value = vertex_value;\n        int node = int(_nodes.size());\n        _nodes.emplace_back(value);\n\
    \        _vertex_nodes.push_back(node);\n        return int(_vertex_nodes.size())\
    \ - 1;\n    }\n\n    const VertexValue& get_vertex(VertexId vertex) const {\n\
    \        return std::get<0>(_nodes[vertex_node(vertex)].value);\n    }\n\n   \
    \ void set_vertex(VertexId vertex, const VertexValue& vertex_value) {\n      \
    \  set_vertex_node_value(vertex_node(vertex), vertex_value);\n    }\n\n    int\
    \ edge_count() const {\n        return int(_edges.size());\n    }\n\n    bool\
    \ edge_alive(EdgeId edge_id) const {\n        check_edge(edge_id);\n        return\
    \ _edges[edge_id].alive;\n    }\n\n    std::pair<VertexId, VertexId> edge_endpoints(EdgeId\
    \ edge_id) const {\n        check_edge(edge_id);\n        return {_edges[edge_id].u,\
    \ _edges[edge_id].v};\n    }\n\n    const EdgeValue& get_edge(EdgeId edge_id)\
    \ const {\n        check_edge(edge_id);\n        return std::get<1>(_nodes[_edges[edge_id].node].value);\n\
    \    }\n\n    void set_edge(EdgeId edge_id, const EdgeValue& edge_value) {\n \
    \       check_edge(edge_id);\n        set_edge_node_value(_edges[edge_id].node,\
    \ edge_value);\n    }\n\n    EdgeId add_edge(VertexId u, VertexId v, const EdgeValue&\
    \ edge_value) {\n        check_vertex(u);\n        check_vertex(v);\n        if\
    \ (u == v || connected(u, v)) return -1;\n        EdgeValue value = edge_value;\n\
    \        int edge_id = int(_edges.size());\n        int node = add_edge_node(value);\n\
    \        _edges.push_back(OriginalEdge{u, v, node, true});\n        bool ok1 =\
    \ link_nodes(vertex_node(u), node);\n        bool ok2 = link_nodes(node, vertex_node(v));\n\
    \        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    bool cut_edge(EdgeId\
    \ edge_id) {\n        check_edge(edge_id);\n        OriginalEdge& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        bool ok1 = cut_nodes(vertex_node(edge.u),\
    \ edge.node);\n        bool ok2 = cut_nodes(edge.node, vertex_node(edge.v));\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    void reroot(VertexId vertex) {\n        evert_node(vertex_node(vertex));\n\
    \    }\n\n    bool connected(VertexId u, VertexId v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        return connected_nodes(vertex_node(u), vertex_node(v));\n\
    \    }\n\n    // Reroots the represented tree at vertex and returns its whole-tree\
    \ cluster.\n    Path component_prod(VertexId vertex) {\n        int node = vertex_node(vertex);\n\
    \        evert_node(node);\n        return _nodes[node].prod;\n    }\n\n    Path\
    \ query_component(VertexId vertex) {\n        return component_prod(vertex);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP\n#define M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <utility>\n#include <variant>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Maintains a dynamic forest whose tree\
    \ DP uses two different aggregate types.\n// Point is a commutative group for\
    \ virtual children, while Path is an ordered\n// preferred-path cluster and does\
    \ not need an inverse.\ntemplate <class TreeDPInfo>\nstruct RakeCompressLinkCutTree\
    \ {\n    using Point = typename TreeDPInfo::Point;\n    using Path = typename\
    \ TreeDPInfo::Path;\n    using VertexValue = typename TreeDPInfo::VertexValue;\n\
    \    using EdgeValue = typename TreeDPInfo::EdgeValue;\n    using VertexId = int;\n\
    \    using EdgeId = int;\n\n   private:\n    struct Node {\n        int left =\
    \ -1;\n        int right = -1;\n        int parent = -1;\n        bool rev = false;\n\
    \        std::variant<VertexValue, EdgeValue> value;\n        Point virtual_prod;\n\
    \        Path prod;\n        Path rev_prod;\n\n        explicit Node(const VertexValue&\
    \ vertex_value)\n            : value(std::in_place_index<0>, vertex_value),\n\
    \              virtual_prod(Point::id()),\n              prod(TreeDPInfo::make_vertex_path(virtual_prod,\
    \ vertex_value)),\n              rev_prod(prod) {}\n\n        explicit Node(std::in_place_index_t<1>,\
    \ const EdgeValue& edge_value)\n            : value(std::in_place_index<1>, edge_value),\n\
    \              virtual_prod(Point::id()),\n              prod(TreeDPInfo::make_edge_path(virtual_prod,\
    \ edge_value)),\n              rev_prod(prod) {}\n    };\n\n    struct OriginalEdge\
    \ {\n        VertexId u = -1;\n        VertexId v = -1;\n        int node = -1;\n\
    \        bool alive = false;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _vertex_nodes;\n    std::vector<OriginalEdge> _edges;\n    std::vector<int>\
    \ _path_buffer;\n\n    bool is_splay_root(int node) const {\n        int parent\
    \ = _nodes[node].parent;\n        return parent == -1 || (_nodes[parent].left\
    \ != node && _nodes[parent].right != node);\n    }\n\n    void update(int node)\
    \ {\n        Node& x = _nodes[node];\n        Path self = x.value.index() == 0\n\
    \            ? TreeDPInfo::make_vertex_path(x.virtual_prod, std::get<0>(x.value))\n\
    \            : TreeDPInfo::make_edge_path(x.virtual_prod, std::get<1>(x.value));\n\
    \        x.prod = self;\n        x.rev_prod = self;\n\n        if (x.left != -1)\
    \ {\n            x.prod = TreeDPInfo::compress(_nodes[x.left].prod, x.prod);\n\
    \            x.rev_prod = TreeDPInfo::compress(x.rev_prod, _nodes[x.left].rev_prod);\n\
    \        }\n        if (x.right != -1) {\n            x.prod = TreeDPInfo::compress(x.prod,\
    \ _nodes[x.right].prod);\n            x.rev_prod = TreeDPInfo::compress(_nodes[x.right].rev_prod,\
    \ x.rev_prod);\n        }\n    }\n\n    void add_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);\n\
    \        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod,\
    \ contribution);\n    }\n\n    void remove_virtual_child(int node, int child)\
    \ {\n        if (child == -1) return;\n        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);\n\
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
    \    }\n\n    void check_node(int node) const {\n        assert(0 <= node && node\
    \ < int(_nodes.size()));\n    }\n\n    void check_vertex(VertexId vertex) const\
    \ {\n        assert(0 <= vertex && vertex < int(_vertex_nodes.size()));\n    }\n\
    \n    void check_edge(EdgeId edge_id) const {\n        assert(0 <= edge_id &&\
    \ edge_id < int(_edges.size()));\n    }\n\n    int vertex_node(VertexId vertex)\
    \ const {\n        check_vertex(vertex);\n        return _vertex_nodes[vertex];\n\
    \    }\n\n    int add_edge_node(const EdgeValue& edge_value) {\n        _nodes.emplace_back(std::in_place_index<1>,\
    \ edge_value);\n        return int(_nodes.size()) - 1;\n    }\n\n    void set_vertex_node_value(int\
    \ node, const VertexValue& vertex_value) {\n        check_node(node);\n      \
    \  access(node);\n        _nodes[node].value.template emplace<0>(vertex_value);\n\
    \        update(node);\n    }\n\n    void set_edge_node_value(int node, const\
    \ EdgeValue& edge_value) {\n        check_node(node);\n        access(node);\n\
    \        _nodes[node].value.template emplace<1>(edge_value);\n        update(node);\n\
    \    }\n\n    void evert_node(int node) {\n        check_node(node);\n       \
    \ access(node);\n        apply_reverse(node);\n    }\n\n    int component_root_node(int\
    \ node) {\n        check_node(node);\n        access(node);\n        int cur =\
    \ node;\n        push(cur);\n        while (_nodes[cur].left != -1) {\n      \
    \      cur = _nodes[cur].left;\n            push(cur);\n        }\n        splay(cur);\n\
    \        return cur;\n    }\n\n    bool connected_nodes(int u, int v) {\n    \
    \    if (u == v) return true;\n        return component_root_node(u) == component_root_node(v);\n\
    \    }\n\n    bool link_nodes(int u, int v) {\n        check_node(u);\n      \
    \  check_node(v);\n        if (u == v) return false;\n        evert_node(u);\n\
    \        if (component_root_node(v) == u) return false;\n        access(v);\n\
    \        _nodes[u].parent = v;\n        add_virtual_child(v, u);\n        update(v);\n\
    \        return true;\n    }\n\n    bool cut_nodes(int u, int v) {\n        check_node(u);\n\
    \        check_node(v);\n        if (u == v) return false;\n        evert_node(u);\n\
    \        access(v);\n        if (_nodes[v].left != u || _nodes[u].right != -1)\
    \ return false;\n        _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n\
    \        update(v);\n        return true;\n    }\n\n   public:\n    RakeCompressLinkCutTree()\
    \ = default;\n\n    explicit RakeCompressLinkCutTree(const std::vector<VertexValue>&\
    \ values) {\n        _nodes.reserve(values.size());\n        _vertex_nodes.reserve(values.size());\n\
    \        for (const VertexValue& value : values) add_vertex(value);\n    }\n\n\
    \    int vertex_count() const {\n        return int(_vertex_nodes.size());\n \
    \   }\n\n    bool empty() const {\n        return _vertex_nodes.empty();\n   \
    \ }\n\n    VertexId add_vertex(const VertexValue& vertex_value) {\n        VertexValue\
    \ value = vertex_value;\n        int node = int(_nodes.size());\n        _nodes.emplace_back(value);\n\
    \        _vertex_nodes.push_back(node);\n        return int(_vertex_nodes.size())\
    \ - 1;\n    }\n\n    const VertexValue& get_vertex(VertexId vertex) const {\n\
    \        return std::get<0>(_nodes[vertex_node(vertex)].value);\n    }\n\n   \
    \ void set_vertex(VertexId vertex, const VertexValue& vertex_value) {\n      \
    \  set_vertex_node_value(vertex_node(vertex), vertex_value);\n    }\n\n    int\
    \ edge_count() const {\n        return int(_edges.size());\n    }\n\n    bool\
    \ edge_alive(EdgeId edge_id) const {\n        check_edge(edge_id);\n        return\
    \ _edges[edge_id].alive;\n    }\n\n    std::pair<VertexId, VertexId> edge_endpoints(EdgeId\
    \ edge_id) const {\n        check_edge(edge_id);\n        return {_edges[edge_id].u,\
    \ _edges[edge_id].v};\n    }\n\n    const EdgeValue& get_edge(EdgeId edge_id)\
    \ const {\n        check_edge(edge_id);\n        return std::get<1>(_nodes[_edges[edge_id].node].value);\n\
    \    }\n\n    void set_edge(EdgeId edge_id, const EdgeValue& edge_value) {\n \
    \       check_edge(edge_id);\n        set_edge_node_value(_edges[edge_id].node,\
    \ edge_value);\n    }\n\n    EdgeId add_edge(VertexId u, VertexId v, const EdgeValue&\
    \ edge_value) {\n        check_vertex(u);\n        check_vertex(v);\n        if\
    \ (u == v || connected(u, v)) return -1;\n        EdgeValue value = edge_value;\n\
    \        int edge_id = int(_edges.size());\n        int node = add_edge_node(value);\n\
    \        _edges.push_back(OriginalEdge{u, v, node, true});\n        bool ok1 =\
    \ link_nodes(vertex_node(u), node);\n        bool ok2 = link_nodes(node, vertex_node(v));\n\
    \        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    bool cut_edge(EdgeId\
    \ edge_id) {\n        check_edge(edge_id);\n        OriginalEdge& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        bool ok1 = cut_nodes(vertex_node(edge.u),\
    \ edge.node);\n        bool ok2 = cut_nodes(edge.node, vertex_node(edge.v));\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    void reroot(VertexId vertex) {\n        evert_node(vertex_node(vertex));\n\
    \    }\n\n    bool connected(VertexId u, VertexId v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        return connected_nodes(vertex_node(u), vertex_node(v));\n\
    \    }\n\n    // Reroots the represented tree at vertex and returns its whole-tree\
    \ cluster.\n    Path component_prod(VertexId vertex) {\n        int node = vertex_node(vertex);\n\
    \        evert_node(node);\n        return _nodes[node].prod;\n    }\n\n    Path\
    \ query_component(VertexId vertex) {\n        return component_prod(vertex);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dynamic_tree/rake_compress_link_cut_tree.hpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_tree/rake_compress_link_cut_tree.test.cpp
  - verify/ds/dynamic_tree/yosupo_point_set_tree_path_composite_sum.test.cpp
documentation_of: ds/dynamic_tree/rake_compress_link_cut_tree.hpp
layout: document
title: Rake-Compress Link-Cut Tree
---

## Overview

`m1une::ds::RakeCompressLinkCutTree<TreeDPInfo>` maintains a
dynamic forest together with a tree DP. It separates the two aggregates needed
by subtree-aware link-cut trees:

* `Point` is a commutative group used to rake independent virtual children.
* `Path` is an ordered cluster used to compress a preferred path.

Only `Point` needs an inverse. In particular, affine functions on a path do not
need to be invertible, and `Path` does not need an identity or inverse.

All dynamic-forest operations take amortized $O(\log N)$ time. Internally, each
original edge is represented by a hidden helper node, but helper-node ids and
operations are not exposed by the public API.

## Complexity Notation

* `N` is the number of original vertices plus currently allocated helper nodes.

## Two Interface Layers

The public interface describes only the original forest:

* `add_vertex`, `get_vertex`, and `set_vertex` use original vertex ids.
* `add_edge`, `get_edge`, `set_edge`, and `cut_edge` use original edge ids.
* `reroot`, `connected`, and `component_prod` accept original vertex ids.

The class names these roles `VertexId` and `EdgeId` (both aliases of `int` for
contest ergonomics). Internal link-cut-tree node ids are private and have no
public alias or accessor.

`TreeDPInfo` also keeps original vertex data and original edge data separate.
This removes the need for a tagged union such as `NodeValue{is_vertex, ...}`.

## Tree DP Interface

`TreeDPInfo` provides four types:

```cpp
using Point = ...;
using Path = ...;
using VertexValue = ...;
using EdgeValue = ...;
```

These types separate local original-tree data from the two aggregate levels:

![Relationship between original-tree values, Point, and Path](../assets/rake_compress_link_cut_tree_types.png)

The four panels show the operations on explicit before-and-after tree
drawings. `rake` merges independent virtual branches at the same attachment
node, `make_vertex_path` or `make_edge_path` inserts the matching original-tree
value, `compress` concatenates adjacent ordered `Path` clusters, and
`to_point` converts a child branch from `Path` form into a `Point`
contribution. These callbacks change the aggregate representation, not the
original-tree topology.

### `VertexValue` and `EdgeValue`

`VertexValue` is the local data stored on an original vertex. `EdgeValue` is
the local data stored on an original edge. Neither is an aggregate.

`make_vertex_path(point, vertex_value)` combines an original vertex with its
already-aggregated virtual children. `make_edge_path(point, edge_value)` does
the analogous operation for an original edge's hidden helper node.

### `Point`

`Point` represents zero or more independent child-side clusters attached at
the same path node. These are the virtual children: represented-tree edges
which are not currently part of the preferred path.

Their order has no meaning, so `rake` must be associative and commutative.
`Point::id()` represents no virtual children. `Point::inv()` lets `access`
remove a child contribution when that child enters the preferred path.

Conceptually, a node maintains:

```cpp
Point virtual_children = Point::id();
virtual_children = rake(virtual_children, to_point(child_path));
```

`Point` does not include the local original-tree object at the attachment node.

### `Path`

`Path` represents an ordered, nonempty preferred-path cluster. It contains the
nodes on that path together with all `Point` contributions raked into those
nodes. Its two ends have an order: the parent-side end comes before the
child-side end in the current represented-root orientation.

`compress(parent_side, child_side)` concatenates two adjacent path clusters in
that order. It must be associative, but does not need to be commutative.
Reversing a represented path may change the aggregate, so each link-cut-tree
node maintains both the forward and reverse `Path` products.

When a branch is part of the preferred path, its summary is a `Path` because
its order matters. When that branch becomes a virtual child, it must be stored
in the parent's unordered `Point` aggregate instead. `to_point(path)` performs
this conversion:

```cpp
Point branch = to_point(child_path);
virtual_children = rake(virtual_children, branch);
```

`to_point` does not modify the original forest. It only changes the DP
representation of an existing child branch.

A `Path` needs neither an identity nor an inverse.

At a link-cut-tree node, the aggregate is formed schematically as:

```cpp
Path self = make_vertex_path(virtual_children, vertex_value);
// or make_edge_path(virtual_children, edge_value) at a hidden edge node
Path whole = self;
if (left_path_exists) whole = compress(left_path, whole);
if (right_path_exists) whole = compress(whole, right_path);
```

`Point` provides:

```cpp
static Point id();
Point inv() const;
```

`TreeDPInfo` provides:

```cpp
static Path make_vertex_path(
    const Point& virtual_children,
    const VertexValue& vertex_value
);
static Path make_edge_path(
    const Point& virtual_children,
    const EdgeValue& edge_value
);
static Point to_point(const Path& path);
static Point rake(const Point& a, const Point& b);
static Path compress(const Path& parent_side, const Path& child_side);
```

The operations have the following meanings:

* `rake(a, b)` merges independent virtual-subtree contributions. It must be
  associative and commutative.
* `compress(p, c)` joins an upper parent-side path cluster with a lower
  child-side path cluster. It must be associative, but need not be commutative.
* `make_vertex_path(point, value)` adds one original vertex to its virtual
  children.
* `make_edge_path(point, value)` adds one original edge to its child-side
  contribution.
* `to_point(path)` converts an ordered branch summary into the unordered
  `Point` value that can be raked with other virtual children.

The inverse of `to_point(path)` is used only when `access` changes a preferred
child back into a virtual child or vice versa.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `VertexId add_vertex(vertex_value)` | Adds an isolated original vertex and returns its vertex id. | Amortized $O(1)$ |
| `const VertexValue& get_vertex(VertexId v)` | Returns original vertex `v`'s value. | $O(1)$ |
| `void set_vertex(VertexId v, value)` | Replaces original vertex `v`'s value. | Amortized $O(\log N)$ |
| `EdgeId add_edge(VertexId u, VertexId v, edge_value)` | Adds an original edge and returns its edge id, or `-1` if it would make a cycle. | Amortized $O(\log N)$ |
| `const EdgeValue& get_edge(EdgeId e)` | Returns original edge `e`'s value. | $O(1)$ |
| `void set_edge(EdgeId e, value)` | Replaces original edge `e`'s value. | Amortized $O(\log N)$ |
| `bool cut_edge(EdgeId e)` | Removes original edge `e`. | Amortized $O(\log N)$ |
| `void reroot(VertexId v)` | Makes original vertex `v` the represented root. | Amortized $O(\log N)$ |
| `bool connected(VertexId u, VertexId v)` | Tests whether two original vertices are connected. | Amortized $O(\log N)$ |
| `Path component_prod(VertexId v)` | Reroots at original vertex `v` and returns the whole-component cluster. | Amortized $O(\log N)$ |

`query_component(v)` is an alias for `component_prod(v)`.

`vertex_count()` returns the number of original vertices. `edge_count()` returns
the number of edge ids issued so far, including cut edges. `edge_alive(e)` and
`edge_endpoints(e)` inspect an original edge.

## Hidden Edge Nodes

Internally, `add_edge(u, v, value)` subdivides the original edge with one
helper node. That node lets the link-cut tree put edge data on the same
preferred-path machinery as vertex data. Its id is deliberately not exposed:
all public operations continue to use the original vertex id or original edge
id.

## Example

The following DP stores an integer on every original vertex and an affine
function $f(t) = at + b$ on every original edge. The query returns the sum of
all vertex values after each value is transported toward the chosen root by the
edge functions on its path.

```cpp
#include <iostream>

#include "ds/dynamic_tree/rake_compress_link_cut_tree.hpp"

struct AffineTreeSum {
    struct Point {
        long long sum;
        long long count;

        static Point id() {
            return Point{0, 0};
        }

        Point inv() const {
            return Point{-sum, -count};
        }
    };

    struct Path {
        long long a;
        long long b;
        long long sum;
        long long count;
    };

    struct VertexValue {
        long long value;
    };

    struct EdgeValue {
        long long a;
        long long b;
    };

    static Path make_vertex_path(
        const Point& children,
        const VertexValue& vertex
    ) {
        return Path{1, 0, children.sum + vertex.value, children.count + 1};
    }

    static Path make_edge_path(
        const Point& children,
        const EdgeValue& edge
    ) {
        return Path{
            edge.a,
            edge.b,
            children.sum * edge.a + children.count * edge.b,
            children.count
        };
    }

    static Point to_point(const Path& path) {
        return Point{path.sum, path.count};
    }

    static Point rake(const Point& x, const Point& y) {
        return Point{x.sum + y.sum, x.count + y.count};
    }

    static Path compress(const Path& parent, const Path& child) {
        return Path{
            parent.a * child.a,
            parent.a * child.b + parent.b,
            parent.sum + parent.a * child.sum + parent.b * child.count,
            parent.count + child.count
        };
    }
};

int main() {
    using LCT =
        m1une::ds::RakeCompressLinkCutTree<AffineTreeSum>;

    LCT lct;
    int u = lct.add_vertex(AffineTreeSum::VertexValue{2});
    int v = lct.add_vertex(AffineTreeSum::VertexValue{3});
    int w = lct.add_vertex(AffineTreeSum::VertexValue{5});

    // u --(t -> 2t + 1)--> v --(t -> 3t)--> w
    int uv = lct.add_edge(u, v, AffineTreeSum::EdgeValue{2, 1});
    lct.add_edge(v, w, AffineTreeSum::EdgeValue{3, 0});

    long long rooted_at_u = lct.component_prod(u).sum;
    long long rooted_at_w = lct.component_prod(w).sum;
    std::cout << rooted_at_u << '\n';  // 40
    std::cout << rooted_at_w << '\n';  // 29

    lct.set_vertex(v, AffineTreeSum::VertexValue{7});
    lct.set_edge(uv, AffineTreeSum::EdgeValue{0, 4});
}
```

`compress(parent, child)` is ordered: reversing its arguments generally
changes the result. The affine coefficient may be zero because only `Point`
requires an inverse.

## Notes

`component_prod(v)` changes the represented root to `v`. Its returned `Path`
contains the whole component, including all virtual branches attached to the
preferred path exposed by rerooting.

The structure assumes that the supplied rake/compress operations describe a
valid associative tree DP. It does not require affine coefficients or other
path transitions to be invertible.
