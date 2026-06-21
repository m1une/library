---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/static_top_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 12 \"tree/static_top_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\nnamespace internal {\n\nenum class StaticTopTreeNodeType {\n    Compress,\n\
    \    Rake,\n    AddEdge,\n    AddVertex,\n};\n\n}  // namespace internal\n\ntemplate\
    \ <class T, class Vertex, class Path, class Point, class Compress, class Rake,\
    \ class AddEdge,\n          class AddVertex>\nstruct StaticTopTree {\n    using\
    \ cost_type = T;\n    using vertex_type = Vertex;\n    using path_type = Path;\n\
    \    using point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n\
    \n   private:\n    struct Node {\n        internal::StaticTopTreeNodeType type;\n\
    \        int left = -1;\n        int right = -1;\n        int parent = -1;\n \
    \       int vertex = -1;\n        edge_type edge;\n        int size = 0;\n   \
    \     int height = 1;\n        std::optional<Path> path;\n        std::optional<Point>\
    \ point;\n    };\n\n    int _n;\n    int _root;\n    int _root_node;\n    Point\
    \ _point_id;\n    Compress _compress;\n    Rake _rake;\n    AddEdge _add_edge;\n\
    \    AddVertex _add_vertex;\n    std::vector<Vertex> _values;\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _vertex_node;\n    std::vector<int> _edge_node;\n\
    \    std::vector<int> _parent;\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _heavy;\n    std::vector<edge_type> _heavy_edge;\n    std::vector<std::vector<edge_type>>\
    \ _children;\n\n    const Path& path_value(int node) const {\n        assert(0\
    \ <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path.has_value());\n\
    \        return *_nodes[node].path;\n    }\n\n    const Point& point_value(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].point.has_value());\n        return *_nodes[node].point;\n\
    \    }\n\n    void set_parent(int child, int parent) {\n        if (child != -1)\
    \ _nodes[child].parent = parent;\n    }\n\n    void recompute(int node) {\n  \
    \      auto& x = _nodes[node];\n        if (x.type == internal::StaticTopTreeNodeType::Compress)\
    \ {\n            x.path = _compress(path_value(x.left), path_value(x.right), x.edge);\n\
    \        } else if (x.type == internal::StaticTopTreeNodeType::Rake) {\n     \
    \       x.point = _rake(point_value(x.left), point_value(x.right));\n        }\
    \ else if (x.type == internal::StaticTopTreeNodeType::AddEdge) {\n           \
    \ x.point = _add_edge(path_value(x.left), x.edge);\n        } else {\n       \
    \     const Point& side = x.left == -1 ? _point_id : point_value(x.left);\n  \
    \          x.path = _add_vertex(side, _values[x.vertex], x.vertex);\n        }\n\
    \    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Compress;\n\
    \        node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddVertex;\n\
    \        node.left = side;\n        node.vertex = vertex;\n        node.size =\
    \ 1 + (side == -1 ? 0 : _nodes[side].size);\n        node.height = 1 + (side ==\
    \ -1 ? 0 : _nodes[side].height);\n        int id = new_node(std::move(node));\n\
    \        _vertex_node[vertex] = id;\n        return id;\n    }\n\n    int weighted_split(const\
    \ std::vector<int>& nodes, int l, int r) const {\n        int total = 0;\n   \
    \     for (int i = l; i < r; i++) total += _nodes[nodes[i]].size;\n        int\
    \ left_sum = 0;\n        for (int i = l; i + 1 < r; i++) {\n            left_sum\
    \ += _nodes[nodes[i]].size;\n            if (2 * left_sum >= total) return i +\
    \ 1;\n        }\n        return r - 1;\n    }\n\n    int build_rake(const std::vector<int>&\
    \ nodes, int l, int r) {\n        if (l == r) return -1;\n        if (l + 1 ==\
    \ r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n        return\
    \ new_rake(build_rake(nodes, l, m), build_rake(nodes, m, r));\n    }\n\n    int\
    \ build_compress(const std::vector<int>& nodes, const std::vector<edge_type>&\
    \ edges, int l, int r) {\n        if (l + 1 == r) return nodes[l];\n        int\
    \ m = weighted_split(nodes, l, r);\n        return new_compress(build_compress(nodes,\
    \ edges, l, m), build_compress(nodes, edges, m, r), edges[m - 1]);\n    }\n\n\
    \    int build_vertex(int v) {\n        std::vector<int> side_nodes;\n       \
    \ for (const auto& e : _children[v]) {\n            if (e.to == _heavy[v]) continue;\n\
    \            int child_path = build_path(e.to);\n            side_nodes.push_back(new_add_edge(child_path,\
    \ e));\n        }\n        return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    StaticTopTree(const m1une::graph::Graph<T>& g, const\
    \ std::vector<Vertex>& values, Point point_id,\n                  Compress compress,\
    \ Rake rake, AddEdge add_edge, AddVertex add_vertex, int root = 0)\n        :\
    \ _n(g.size()),\n          _root(_n == 0 ? -1 : root),\n          _root_node(-1),\n\
    \          _point_id(std::move(point_id)),\n          _compress(std::move(compress)),\n\
    \          _rake(std::move(rake)),\n          _add_edge(std::move(add_edge)),\n\
    \          _add_vertex(std::move(add_vertex)),\n          _values(values) {\n\
    \        build(g, root);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root = 0) {\n        _n = g.size();\n        _root = _n == 0 ? -1 : root;\n\
    \        assert(int(_values.size()) == _n);\n        _nodes.clear();\n       \
    \ _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(), -1);\n\
    \        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n     \
    \   _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n   \
    \     _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n ==\
    \ 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& all_prod() const {\n        assert(_root_node != -1);\n        return\
    \ path_value(_root_node);\n    }\n\n    const Path& query() const {\n        return\
    \ all_prod();\n    }\n};\n\ntemplate <class T, class Vertex, class Point, class\
    \ Compress, class Rake, class AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, Compress, Rake, AddEdge,\n              AddVertex,\
    \ int)\n    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point,\
    \ Vertex, int>, Point, Compress, Rake,\n                     AddEdge, AddVertex>;\n\
    \ntemplate <class T, class Vertex, class Point, class Compress, class Rake, class\
    \ AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&, const\
    \ std::vector<Vertex>&, Point, Compress, Rake, AddEdge, AddVertex)\n    -> StaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress,\
    \ Rake,\n                     AddEdge, AddVertex>;\n\n}  // namespace tree\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_STATIC_TOP_TREE_HPP\n#define M1UNE_TREE_STATIC_TOP_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\n#include \"../graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nenum class\
    \ StaticTopTreeNodeType {\n    Compress,\n    Rake,\n    AddEdge,\n    AddVertex,\n\
    };\n\n}  // namespace internal\n\ntemplate <class T, class Vertex, class Path,\
    \ class Point, class Compress, class Rake, class AddEdge,\n          class AddVertex>\n\
    struct StaticTopTree {\n    using cost_type = T;\n    using vertex_type = Vertex;\n\
    \    using path_type = Path;\n    using point_type = Point;\n    using edge_type\
    \ = m1une::graph::Edge<T>;\n\n   private:\n    struct Node {\n        internal::StaticTopTreeNodeType\
    \ type;\n        int left = -1;\n        int right = -1;\n        int parent =\
    \ -1;\n        int vertex = -1;\n        edge_type edge;\n        int size = 0;\n\
    \        int height = 1;\n        std::optional<Path> path;\n        std::optional<Point>\
    \ point;\n    };\n\n    int _n;\n    int _root;\n    int _root_node;\n    Point\
    \ _point_id;\n    Compress _compress;\n    Rake _rake;\n    AddEdge _add_edge;\n\
    \    AddVertex _add_vertex;\n    std::vector<Vertex> _values;\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _vertex_node;\n    std::vector<int> _edge_node;\n\
    \    std::vector<int> _parent;\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _heavy;\n    std::vector<edge_type> _heavy_edge;\n    std::vector<std::vector<edge_type>>\
    \ _children;\n\n    const Path& path_value(int node) const {\n        assert(0\
    \ <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path.has_value());\n\
    \        return *_nodes[node].path;\n    }\n\n    const Point& point_value(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].point.has_value());\n        return *_nodes[node].point;\n\
    \    }\n\n    void set_parent(int child, int parent) {\n        if (child != -1)\
    \ _nodes[child].parent = parent;\n    }\n\n    void recompute(int node) {\n  \
    \      auto& x = _nodes[node];\n        if (x.type == internal::StaticTopTreeNodeType::Compress)\
    \ {\n            x.path = _compress(path_value(x.left), path_value(x.right), x.edge);\n\
    \        } else if (x.type == internal::StaticTopTreeNodeType::Rake) {\n     \
    \       x.point = _rake(point_value(x.left), point_value(x.right));\n        }\
    \ else if (x.type == internal::StaticTopTreeNodeType::AddEdge) {\n           \
    \ x.point = _add_edge(path_value(x.left), x.edge);\n        } else {\n       \
    \     const Point& side = x.left == -1 ? _point_id : point_value(x.left);\n  \
    \          x.path = _add_vertex(side, _values[x.vertex], x.vertex);\n        }\n\
    \    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Compress;\n\
    \        node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddVertex;\n\
    \        node.left = side;\n        node.vertex = vertex;\n        node.size =\
    \ 1 + (side == -1 ? 0 : _nodes[side].size);\n        node.height = 1 + (side ==\
    \ -1 ? 0 : _nodes[side].height);\n        int id = new_node(std::move(node));\n\
    \        _vertex_node[vertex] = id;\n        return id;\n    }\n\n    int weighted_split(const\
    \ std::vector<int>& nodes, int l, int r) const {\n        int total = 0;\n   \
    \     for (int i = l; i < r; i++) total += _nodes[nodes[i]].size;\n        int\
    \ left_sum = 0;\n        for (int i = l; i + 1 < r; i++) {\n            left_sum\
    \ += _nodes[nodes[i]].size;\n            if (2 * left_sum >= total) return i +\
    \ 1;\n        }\n        return r - 1;\n    }\n\n    int build_rake(const std::vector<int>&\
    \ nodes, int l, int r) {\n        if (l == r) return -1;\n        if (l + 1 ==\
    \ r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n        return\
    \ new_rake(build_rake(nodes, l, m), build_rake(nodes, m, r));\n    }\n\n    int\
    \ build_compress(const std::vector<int>& nodes, const std::vector<edge_type>&\
    \ edges, int l, int r) {\n        if (l + 1 == r) return nodes[l];\n        int\
    \ m = weighted_split(nodes, l, r);\n        return new_compress(build_compress(nodes,\
    \ edges, l, m), build_compress(nodes, edges, m, r), edges[m - 1]);\n    }\n\n\
    \    int build_vertex(int v) {\n        std::vector<int> side_nodes;\n       \
    \ for (const auto& e : _children[v]) {\n            if (e.to == _heavy[v]) continue;\n\
    \            int child_path = build_path(e.to);\n            side_nodes.push_back(new_add_edge(child_path,\
    \ e));\n        }\n        return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    StaticTopTree(const m1une::graph::Graph<T>& g, const\
    \ std::vector<Vertex>& values, Point point_id,\n                  Compress compress,\
    \ Rake rake, AddEdge add_edge, AddVertex add_vertex, int root = 0)\n        :\
    \ _n(g.size()),\n          _root(_n == 0 ? -1 : root),\n          _root_node(-1),\n\
    \          _point_id(std::move(point_id)),\n          _compress(std::move(compress)),\n\
    \          _rake(std::move(rake)),\n          _add_edge(std::move(add_edge)),\n\
    \          _add_vertex(std::move(add_vertex)),\n          _values(values) {\n\
    \        build(g, root);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root = 0) {\n        _n = g.size();\n        _root = _n == 0 ? -1 : root;\n\
    \        assert(int(_values.size()) == _n);\n        _nodes.clear();\n       \
    \ _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(), -1);\n\
    \        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n     \
    \   _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n   \
    \     _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n ==\
    \ 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& all_prod() const {\n        assert(_root_node != -1);\n        return\
    \ path_value(_root_node);\n    }\n\n    const Path& query() const {\n        return\
    \ all_prod();\n    }\n};\n\ntemplate <class T, class Vertex, class Point, class\
    \ Compress, class Rake, class AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, Compress, Rake, AddEdge,\n              AddVertex,\
    \ int)\n    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point,\
    \ Vertex, int>, Point, Compress, Rake,\n                     AddEdge, AddVertex>;\n\
    \ntemplate <class T, class Vertex, class Point, class Compress, class Rake, class\
    \ AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&, const\
    \ std::vector<Vertex>&, Point, Compress, Rake, AddEdge, AddVertex)\n    -> StaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress,\
    \ Rake,\n                     AddEdge, AddVertex>;\n\n}  // namespace tree\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_TREE_STATIC_TOP_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/static_top_tree.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/static_top_tree.hpp
layout: document
title: Static Top Tree
---

## Overview

`m1une::tree::StaticTopTree` builds a fixed binary expression tree over a rooted
tree. After preprocessing, changing one vertex payload or one edge cost only
requires recomputing the clusters on the path to the expression root.

Use it for dynamic tree DP problems where:

* The tree shape is fixed.
* Vertex payloads or edge costs change.
* After each update, you need the DP value for the whole tree rooted at `root`.

This is the online-update counterpart of many one-root tree DPs. If the tree
does not change and there are no updates, ordinary DFS DP or `rerooting_dp` is
usually simpler.

The input uses `m1une::graph::Graph<T>` and should be an undirected connected
tree built with `add_edge`. Inactive edges are ignored while building.

## Cluster Types

The structure uses two user-defined cluster types:

| Type | Meaning |
| --- | --- |
| `Path` | A vertical cluster whose top boundary is an ancestor and whose bottom boundary is a descendant on one heavy path. |
| `Point` | A collection of side subtrees attached to the same path vertex. |

The library balances and recomputes these clusters. You provide the four
operations that describe your DP.

More precisely:

* A `Path` cluster represents a connected part of the original tree that has a
  distinguished top boundary vertex and bottom boundary vertex. These two
  boundary vertices lie on one heavy path. The cluster also includes side
  subtrees that have already been attached to vertices on that path.
* A `Point` cluster represents zero or more completed child subtrees attached to
  one vertex of a heavy path. It has only one boundary: the parent-side vertex
  where those side subtrees attach.

The final value `all_prod()` is a `Path` cluster whose top boundary is `root`
and whose covered vertices are the whole tree.

## How This Implementation Builds the Tree

This implementation first roots the original tree at `root`, then chooses the
heavy child of each vertex as the child with largest subtree size. It then builds
a binary expression tree from four kinds of nodes:

| Internal node kind | Output type | Meaning |
| --- | --- | --- |
| `AddVertex` | `Path` | Make a one-vertex path cluster from a vertex payload and all raked side children. |
| `AddEdge` | `Point` | Attach a child path through one tree edge, turning it into a side contribution. |
| `Rake` | `Point` | Merge two side contributions attached to the same path vertex. |
| `Compress` | `Path` | Concatenate two adjacent path clusters along a heavy path. |

For every original vertex `v`:

1. Each light child subtree is built recursively as a `Path`.
2. That child path is converted to a side contribution with `AddEdge`.
3. All side contributions of `v` are merged with `Rake`.
4. The vertex payload and merged side contribution are converted into a one-vertex
   `Path` with `AddVertex`.

For every heavy path, these one-vertex `Path` clusters are merged from top to
bottom with `Compress`.

The `Rake` and `Compress` trees are balanced by subtree sizes. This is what
makes a single vertex or edge-cost update recompute only a logarithmic number of
clusters in typical use.

For example, if the rooted tree is:

```text
0
|- 1
|  |- 3
|  `- 4
`- 2
```

and the heavy path is `0 -> 1 -> 3`, then conceptually:

```text
Path(2) --AddEdge--> side contribution attached to 0
Path(4) --AddEdge--> side contribution attached to 1

AddVertex(0 side, values[0]) gives one-vertex Path(0)
AddVertex(1 side, values[1]) gives one-vertex Path(1)
AddVertex(3 side, values[3]) gives one-vertex Path(3)

Compress(Path(0), Path(1), edge 0-1)
Compress(result, Path(3), edge 1-3)
```

The actual expression tree may be parenthesized differently because it is
balanced, but the meaning is this top-to-bottom concatenation.

## Operations

The constructor receives:

```cpp
StaticTopTree(
    g,
    values,
    point_id,
    compress,
    rake,
    add_edge,
    add_vertex,
    root
);
```

The constructor arguments are:

| Argument | Meaning |
| --- | --- |
| `g` | The fixed tree shape. It must be an undirected connected `m1une::graph::Graph<T>` with `g.size()` vertices and `g.size() - 1` edges. |
| `values` | The initial payload of each original vertex. Its type is `std::vector<Vertex>`, it must have size `g.size()`, and `values[v]` is passed to `add_vertex(side, values[v], v)`. These payloads are returned by `get(v)` and updated by `set(v, value)`. |
| `point_id` | The identity element of the `Point` type for `rake`. It represents "no side subtrees" and is used for vertices with no light children. This is not a vertex id; it is a DP value such as `0`, `Point{0, 0}`, or any other neutral `Point` state. |
| `compress`, `rake`, `add_edge`, `add_vertex` | The four DP callbacks described below. |
| `root` | The original vertex used as the tree root. It defaults to `0`. |

`Vertex` is a user-defined payload type, independent of `Path` and `Point`.
It is the type stored in the `values` vector, not the integer id of a graph
vertex. The integer vertex id is the third argument `v` passed to
`add_vertex`.

For example:

* If each vertex has a weight, `Vertex` can be `long long` and `values[v]` is
  the weight of vertex `v`.
* If each vertex has several attributes, `Vertex` can be your own struct, such
  as `struct Vertex { int color; long long weight; };`.
* If the DP does not need any vertex payload, pass a dummy vector such as
  `std::vector<int>(g.size(), 0)` and ignore the `value` argument in
  `add_vertex`.

The three DP-related types are therefore:

| Type | Where it comes from | Role |
| --- | --- | --- |
| `Vertex` | The element type of `values` | Original per-vertex input payload. |
| `Point` | The type of `point_id` | Aggregate of side subtrees attached to one boundary vertex. |
| `Path` | The return type of `add_vertex` | Aggregate for a vertical path cluster. |

The callbacks are:

| Callback | Signature | Meaning |
| --- | --- | --- |
| `compress` | `Path compress(Path top, Path bottom, Edge e)` | Combines two vertical path clusters through the tree edge `e` from the bottom of `top` to the top of `bottom`. |
| `rake` | `Point rake(Point a, Point b)` | Combines independent side-subtree clusters attached to the same path vertex. |
| `add_edge` | `Point add_edge(Path child, Edge e)` | Converts a child path cluster into a side-subtree contribution viewed from its parent through edge `e`. |
| `add_vertex` | `Path add_vertex(Point side, Vertex value, int v)` | Adds original vertex `v` and its raked side subtrees, producing a path cluster whose top and bottom are both `v`. |

Here `Edge` is `m1une::graph::Edge<T>`. For both `compress` and `add_edge`,
`e.from` is the parent side and `e.to` is the child side in the rooted tree.

The expected algebraic behavior is:

* `rake(point_id, x) == x` and `rake(x, point_id) == x`.
* `rake` should be associative because side contributions are grouped in a
  balanced binary tree.
* `compress` should behave like path concatenation from top to bottom.
* `compress` does not need to be commutative. The first argument is always the
  upper path cluster, and the second argument is always the lower path cluster.
* `add_edge` sees a completed child `Path` and should shift it across `e.cost`
  or otherwise account for the edge from parent to child.
* `add_vertex` is where the original vertex payload is inserted.

## Designing a DP

A good way to design a static top tree DP is to write down what information is
needed at each boundary.

For `Path`, ask:

* If this cluster starts at its top boundary, what answer do I need for all
  vertices inside it?
* What extra information is needed to concatenate another path below it?

For `Point`, ask:

* If these side subtrees are attached to one parent-side vertex, what aggregate
  contribution do they make to that vertex?
* What is the empty contribution? That is `point_id`.

Then define the operations:

* `add_vertex(side, value, v)`: add vertex `v` and its payload `value` to the
  side contribution.
* `add_edge(child_path, e)`: view a completed child path from its parent through
  edge `e`.
* `rake(a, b)`: combine independent side subtrees.
* `compress(top, bottom, e)`: concatenate adjacent path clusters through edge
  `e`.

If the answer for the whole rooted tree is stored in the `Path` cluster viewed
from its top boundary, read it from `all_prod()`.

## Update Flow

`set(v, value)` updates the stored payload of one original vertex. The
corresponding `AddVertex` node is recomputed, then its parent expression node is
recomputed, and so on until the expression root.

`set_edge_cost(edge_id, cost)` updates the stored cost in the expression node
that owns that tree edge, then recomputes ancestors in the same way.

No tree topology changes happen during updates. Only cached cluster values are
recomputed.

The update cost is proportional to the height of the expression tree. The
balanced construction is intended to keep that height logarithmic for normal
tree shapes.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `StaticTopTree(g, values, point_id, compress, rake, add_edge, add_vertex, root)` | Builds the expression tree. | $O(N \log N)$ callback work |
| `int size()` | Returns the number of original vertices. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `int root()` | Returns the root used to orient the tree. | $O(1)$ |
| `int node_count()` | Returns the number of internal expression nodes. | $O(1)$ |
| `int height()` | Returns the height of the expression tree. | $O(1)$ |
| `const Vertex& get(v)` | Returns the stored vertex payload. | $O(1)$ |
| `const Vertex& operator[](v)` | Returns the stored vertex payload. | $O(1)$ |
| `void set(v, value)` | Updates the payload of vertex `v` and recomputes affected clusters. | $O(\text{height})$ |
| `void set_edge_cost(edge_id, cost)` | Updates one tree-edge cost and recomputes affected clusters. | $O(\text{height})$ |
| `const Path& all_prod()` | Returns the `Path` cluster for the whole rooted tree. | $O(1)$ |
| `const Path& query()` | Alias for `all_prod()`. | $O(1)$ |

The tree is static: adding/removing edges or changing the root requires
rebuilding.

## Example: Dynamic Vertex Sum

This example maintains the sum of all vertex values. This DP is intentionally
simple, so all four operations are easy to see.

```cpp
#include "graph/graph.hpp"
#include "tree/static_top_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    std::vector<long long> a = {10, 20, 30};

    auto stt = m1une::tree::StaticTopTree(
        g,
        a,
        0LL,
        [](long long top, long long bottom, const auto&) {
            return top + bottom;
        },
        [](long long x, long long y) {
            return x + y;
        },
        [](long long child, const auto&) {
            return child;
        },
        [](long long side, long long value, int) {
            return side + value;
        }
    );

    std::cout << stt.all_prod() << "\n"; // 60
    stt.set(1, 100);
    std::cout << stt.all_prod() << "\n"; // 140
}
```

## Example: Sum of Distances from the Root

This example maintains the sum of weighted distances from `root` to all
vertices. It supports edge-cost updates.

`Path` needs three fields:

* `count`: number of vertices in the path cluster.
* `sum`: sum of distances from the top boundary to all vertices in the cluster.
* `length`: distance from the top boundary to the bottom boundary.

`Point` only needs `count` and `sum`, because side clusters have one boundary.

The operations mean:

* `add_vertex`: the current vertex contributes one vertex at distance `0` from
  itself, so `count` increases by `1`.
* `add_edge`: a child cluster is viewed from its parent, so every distance
  inside that child cluster increases by `e.cost`.
* `rake`: side subtrees are independent, so counts and sums are added.
* `compress`: the lower path is viewed from the top path's top boundary. Every
  distance inside `bottom` increases by `top.length + e.cost`.

```cpp
struct Path {
    long long count;
    long long sum;
    long long length;
};

struct Point {
    long long count;
    long long sum;
};

auto stt = m1une::tree::StaticTopTree(
    g,
    std::vector<int>(n, 0),
    Point{0, 0},
    [](Path top, Path bottom, const auto& e) {
        long long shift = top.length + e.cost;
        return Path{
            top.count + bottom.count,
            top.sum + bottom.sum + bottom.count * shift,
            top.length + e.cost + bottom.length
        };
    },
    [](Point a, Point b) {
        return Point{a.count + b.count, a.sum + b.sum};
    },
    [](Path child, const auto& e) {
        return Point{child.count, child.sum + child.count * e.cost};
    },
    [](Point side, int, int) {
        return Path{side.count + 1, side.sum, 0};
    }
);

long long answer = stt.all_prod().sum;
```

## Notes

`StaticTopTree` computes the DP for one fixed root. It is not an all-roots
rerooting helper. For all-roots static answers, use `rerooting_dp`.

For edge values that are not stored in `Edge::cost`, store them in the child
vertex payload or in your own arrays captured by the callbacks, then call
`set(child, new_value)` when they change.
