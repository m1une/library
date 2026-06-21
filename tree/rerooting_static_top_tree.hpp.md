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
  bundledCode: "#line 1 \"tree/rerooting_static_top_tree.hpp\"\n\n\n\n#include <algorithm>\n\
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
    \ m1une\n\n\n#line 12 \"tree/rerooting_static_top_tree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\nnamespace internal {\n\nenum class RerootingStaticTopTreeNodeType\
    \ {\n    Compress,\n    Rake,\n    AddEdge,\n    AddVertex,\n};\n\nenum class\
    \ RerootingStaticTopTreeStepType {\n    CompressLower,\n    CompressUpper,\n \
    \   AddEdge,\n    RakeLeft,\n    RakeRight,\n    AddVertex,\n};\n\n}  // namespace\
    \ internal\n\ntemplate <class T, class Vertex, class Path, class Point, class\
    \ CompressDown, class CompressUp, class Rake,\n          class AddEdgeDown, class\
    \ AddEdgeUp, class AddVertex>\nstruct RerootingStaticTopTree {\n    using cost_type\
    \ = T;\n    using vertex_type = Vertex;\n    using path_type = Path;\n    using\
    \ point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n    using\
    \ node_type = internal::RerootingStaticTopTreeNodeType;\n    using step_type =\
    \ internal::RerootingStaticTopTreeStepType;\n\n    struct Node {\n        node_type\
    \ type;\n        int left = -1;\n        int right = -1;\n        int parent =\
    \ -1;\n        int vertex = -1;\n        edge_type edge;\n        int size = 0;\n\
    \        int height = 1;\n        std::optional<Path> path_down;\n        std::optional<Path>\
    \ path_up;\n        std::optional<Point> point;\n    };\n\n    struct RerootingStep\
    \ {\n        step_type type;\n        int node = -1;\n        int sibling = -1;\n\
    \        int vertex = -1;\n        edge_type edge;\n    };\n\n   private:\n  \
    \  int _n;\n    int _root;\n    int _root_node;\n    Point _point_id;\n    CompressDown\
    \ _compress_down;\n    CompressUp _compress_up;\n    Rake _rake;\n    AddEdgeDown\
    \ _add_edge_down;\n    AddEdgeUp _add_edge_up;\n    AddVertex _add_vertex;\n \
    \   std::vector<Vertex> _values;\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _vertex_node;\n    std::vector<int> _edge_node;\n    std::vector<int> _parent;\n\
    \    std::vector<int> _subtree_size;\n    std::vector<int> _heavy;\n    std::vector<edge_type>\
    \ _heavy_edge;\n    std::vector<std::vector<edge_type>> _children;\n\n    static\
    \ edge_type reversed_edge(edge_type e) {\n        std::swap(e.from, e.to);\n \
    \       return e;\n    }\n\n    const Path& node_path_down(int node) const {\n\
    \        assert(0 <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path_down.has_value());\n\
    \        return *_nodes[node].path_down;\n    }\n\n    const Path& node_path_up(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].path_up.has_value());\n        return *_nodes[node].path_up;\n\
    \    }\n\n    const Point& node_point(int node) const {\n        assert(0 <= node\
    \ && node < int(_nodes.size()));\n        assert(_nodes[node].point.has_value());\n\
    \        return *_nodes[node].point;\n    }\n\n    void set_parent(int child,\
    \ int parent) {\n        if (child != -1) _nodes[child].parent = parent;\n   \
    \ }\n\n    void recompute(int node) {\n        auto& x = _nodes[node];\n     \
    \   if (x.type == node_type::Compress) {\n            x.path_down = _compress_down(node_path_down(x.left),\
    \ node_path_down(x.right), x.edge);\n            x.path_up = _compress_up(node_path_up(x.right),\
    \ node_path_up(x.left), reversed_edge(x.edge));\n        } else if (x.type ==\
    \ node_type::Rake) {\n            x.point = _rake(node_point(x.left), node_point(x.right));\n\
    \        } else if (x.type == node_type::AddEdge) {\n            x.point = _add_edge_down(node_path_down(x.left),\
    \ x.edge);\n        } else {\n            const Point& side = x.left == -1 ? _point_id\
    \ : node_point(x.left);\n            Path path = _add_vertex(side, _values[x.vertex],\
    \ x.vertex);\n            x.path_down = path;\n            x.path_up = std::move(path);\n\
    \        }\n    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = node_type::Compress;\n    \
    \    node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = node_type::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = node_type::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = node_type::AddVertex;\n        node.left\
    \ = side;\n        node.vertex = vertex;\n        node.size = 1 + (side == -1\
    \ ? 0 : _nodes[side].size);\n        node.height = 1 + (side == -1 ? 0 : _nodes[side].height);\n\
    \        int id = new_node(std::move(node));\n        _vertex_node[vertex] = id;\n\
    \        return id;\n    }\n\n    int weighted_split(const std::vector<int>& nodes,\
    \ int l, int r) const {\n        int total = 0;\n        for (int i = l; i < r;\
    \ i++) total += _nodes[nodes[i]].size;\n        int left_sum = 0;\n        for\
    \ (int i = l; i + 1 < r; i++) {\n            left_sum += _nodes[nodes[i]].size;\n\
    \            if (2 * left_sum >= total) return i + 1;\n        }\n        return\
    \ r - 1;\n    }\n\n    int build_rake(const std::vector<int>& nodes, int l, int\
    \ r) {\n        if (l == r) return -1;\n        if (l + 1 == r) return nodes[l];\n\
    \        int m = weighted_split(nodes, l, r);\n        return new_rake(build_rake(nodes,\
    \ l, m), build_rake(nodes, m, r));\n    }\n\n    int build_compress(const std::vector<int>&\
    \ nodes, const std::vector<edge_type>& edges, int l, int r) {\n        if (l +\
    \ 1 == r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n   \
    \     return new_compress(build_compress(nodes, edges, l, m), build_compress(nodes,\
    \ edges, m, r), edges[m - 1]);\n    }\n\n    int build_vertex(int v) {\n     \
    \   std::vector<int> side_nodes;\n        for (const auto& e : _children[v]) {\n\
    \            if (e.to == _heavy[v]) continue;\n            int child_path = build_path(e.to);\n\
    \            side_nodes.push_back(new_add_edge(child_path, e));\n        }\n \
    \       return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    RerootingStaticTopTree(const m1une::graph::Graph<T>&\
    \ g, const std::vector<Vertex>& values, Point point_id,\n                    \
    \       CompressDown compress_down, CompressUp compress_up, Rake rake,\n     \
    \                      AddEdgeDown add_edge_down, AddEdgeUp add_edge_up, AddVertex\
    \ add_vertex, int root = 0)\n        : _n(g.size()),\n          _root(_n == 0\
    \ ? -1 : root),\n          _root_node(-1),\n          _point_id(std::move(point_id)),\n\
    \          _compress_down(std::move(compress_down)),\n          _compress_up(std::move(compress_up)),\n\
    \          _rake(std::move(rake)),\n          _add_edge_down(std::move(add_edge_down)),\n\
    \          _add_edge_up(std::move(add_edge_up)),\n          _add_vertex(std::move(add_vertex)),\n\
    \          _values(values) {\n        build(g, root);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root = 0) {\n        _n = g.size();\n       \
    \ _root = _n == 0 ? -1 : root;\n        assert(int(_values.size()) == _n);\n \
    \       _nodes.clear();\n        _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(),\
    \ -1);\n        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n\
    \        _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n\
    \        _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
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
    \ _root;\n    }\n\n    int root_node() const {\n        return _root_node;\n \
    \   }\n\n    int node_count() const {\n        return int(_nodes.size());\n  \
    \  }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(int id) const {\n        assert(0 <= id && id <\
    \ int(_nodes.size()));\n        return _nodes[id];\n    }\n\n    int parent_node(int\
    \ id) const {\n        return node(id).parent;\n    }\n\n    int vertex_node(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _vertex_node[v];\n\
    \    }\n\n    int local_point_node(int v) const {\n        int id = vertex_node(v);\n\
    \        assert(_nodes[id].type == node_type::AddVertex);\n        return _nodes[id].left;\n\
    \    }\n\n    const Point& local_point(int v) const {\n        int point_node\
    \ = local_point_node(v);\n        return point_node == -1 ? _point_id : node_point(point_node);\n\
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
    \ Path& path_down(int node_id) const {\n        return node_path_down(node_id);\n\
    \    }\n\n    const Path& path_up(int node_id) const {\n        return node_path_up(node_id);\n\
    \    }\n\n    const Point& point(int node_id) const {\n        return node_point(node_id);\n\
    \    }\n\n    const Path& all_prod_down() const {\n        assert(_root_node !=\
    \ -1);\n        return path_down(_root_node);\n    }\n\n    const Path& all_prod_up()\
    \ const {\n        assert(_root_node != -1);\n        return path_up(_root_node);\n\
    \    }\n\n    const Point& point_id() const {\n        return _point_id;\n   \
    \ }\n\n    template <class F>\n    void for_each_rerooting_step(int v, F&& f)\
    \ const {\n        assert(0 <= v && v < _n);\n        int cur = _vertex_node[v];\n\
    \        assert(cur != -1);\n        while (_nodes[cur].parent != -1) {\n    \
    \        int par = _nodes[cur].parent;\n            const auto& p = _nodes[par];\n\
    \            RerootingStep step;\n            step.node = par;\n            if\
    \ (p.type == node_type::Compress) {\n                step.edge = p.edge;\n   \
    \             if (p.left == cur) {\n                    step.type = step_type::CompressLower;\n\
    \                    step.sibling = p.right;\n                } else {\n     \
    \               assert(p.right == cur);\n                    step.type = step_type::CompressUpper;\n\
    \                    step.sibling = p.left;\n                }\n            }\
    \ else if (p.type == node_type::Rake) {\n                if (p.left == cur) {\n\
    \                    step.type = step_type::RakeRight;\n                    step.sibling\
    \ = p.right;\n                } else {\n                    assert(p.right ==\
    \ cur);\n                    step.type = step_type::RakeLeft;\n              \
    \      step.sibling = p.left;\n                }\n            } else if (p.type\
    \ == node_type::AddEdge) {\n                assert(p.left == cur);\n         \
    \       step.type = step_type::AddEdge;\n                step.edge = p.edge;\n\
    \            } else {\n                assert(p.type == node_type::AddVertex);\n\
    \                assert(p.left == cur);\n                step.type = step_type::AddVertex;\n\
    \                step.vertex = p.vertex;\n            }\n            f(step);\n\
    \            cur = par;\n        }\n    }\n\n    std::vector<RerootingStep> rerooting_steps(int\
    \ v) const {\n        std::vector<RerootingStep> result;\n        int cur = vertex_node(v);\n\
    \        int depth = 0;\n        while (_nodes[cur].parent != -1) {\n        \
    \    cur = _nodes[cur].parent;\n            depth++;\n        }\n        result.reserve(depth);\n\
    \        for_each_rerooting_step(v, [&](const RerootingStep& step) {\n       \
    \     result.push_back(step);\n        });\n        return result;\n    }\n\n\
    \    template <class Folder>\n    auto fold_rerooting(int v, Folder folder) const\
    \ {\n        folder.start(v, _values[v], local_point(v));\n        for_each_rerooting_step(v,\
    \ [&](const RerootingStep& step) {\n            if (step.type == step_type::CompressLower)\
    \ {\n                folder.compress_lower(path_down(step.sibling), step.edge);\n\
    \            } else if (step.type == step_type::CompressUpper) {\n           \
    \     folder.compress_upper(path_up(step.sibling), reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::AddEdge) {\n                folder.add_edge(reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::RakeLeft) {\n                folder.rake_left(point(step.sibling));\n\
    \            } else if (step.type == step_type::RakeRight) {\n               \
    \ folder.rake_right(point(step.sibling));\n            } else {\n            \
    \    folder.add_vertex(step.vertex, _values[step.vertex]);\n            }\n  \
    \      });\n        return folder.result();\n    }\n\n    Path compress_down(const\
    \ Path& upper, const Path& lower, edge_type edge) const {\n        return _compress_down(upper,\
    \ lower, edge);\n    }\n\n    Path compress_up(const Path& lower, const Path&\
    \ upper, edge_type edge) const {\n        return _compress_up(lower, upper, edge);\n\
    \    }\n\n    Point rake(const Point& left, const Point& right) const {\n    \
    \    return _rake(left, right);\n    }\n\n    Point add_edge_down(const Path&\
    \ path, edge_type edge) const {\n        return _add_edge_down(path, edge);\n\
    \    }\n\n    Point add_edge_up(const Path& path, edge_type edge) const {\n  \
    \      return _add_edge_up(path, edge);\n    }\n\n    Path add_vertex(const Point&\
    \ side, const Vertex& value, int vertex) const {\n        return _add_vertex(side,\
    \ value, vertex);\n    }\n\n    static edge_type reverse_edge(edge_type edge)\
    \ {\n        return reversed_edge(edge);\n    }\n};\n\ntemplate <class T, class\
    \ Vertex, class Point, class CompressDown, class CompressUp, class Rake, class\
    \ AddEdgeDown,\n          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const\
    \ m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n\
    \                       Rake, AddEdgeDown, AddEdgeUp, AddVertex, int)\n    ->\
    \ RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex,\
    \ int>, Point, CompressDown,\n                              CompressUp, Rake,\
    \ AddEdgeDown, AddEdgeUp, AddVertex>;\n\ntemplate <class T, class Vertex, class\
    \ Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,\n\
    \          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n             \
    \          Rake, AddEdgeDown, AddEdgeUp, AddVertex)\n    -> RerootingStaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,\n\
    \                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP\n#define M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\n#include \"../graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nenum class\
    \ RerootingStaticTopTreeNodeType {\n    Compress,\n    Rake,\n    AddEdge,\n \
    \   AddVertex,\n};\n\nenum class RerootingStaticTopTreeStepType {\n    CompressLower,\n\
    \    CompressUpper,\n    AddEdge,\n    RakeLeft,\n    RakeRight,\n    AddVertex,\n\
    };\n\n}  // namespace internal\n\ntemplate <class T, class Vertex, class Path,\
    \ class Point, class CompressDown, class CompressUp, class Rake,\n          class\
    \ AddEdgeDown, class AddEdgeUp, class AddVertex>\nstruct RerootingStaticTopTree\
    \ {\n    using cost_type = T;\n    using vertex_type = Vertex;\n    using path_type\
    \ = Path;\n    using point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n\
    \    using node_type = internal::RerootingStaticTopTreeNodeType;\n    using step_type\
    \ = internal::RerootingStaticTopTreeStepType;\n\n    struct Node {\n        node_type\
    \ type;\n        int left = -1;\n        int right = -1;\n        int parent =\
    \ -1;\n        int vertex = -1;\n        edge_type edge;\n        int size = 0;\n\
    \        int height = 1;\n        std::optional<Path> path_down;\n        std::optional<Path>\
    \ path_up;\n        std::optional<Point> point;\n    };\n\n    struct RerootingStep\
    \ {\n        step_type type;\n        int node = -1;\n        int sibling = -1;\n\
    \        int vertex = -1;\n        edge_type edge;\n    };\n\n   private:\n  \
    \  int _n;\n    int _root;\n    int _root_node;\n    Point _point_id;\n    CompressDown\
    \ _compress_down;\n    CompressUp _compress_up;\n    Rake _rake;\n    AddEdgeDown\
    \ _add_edge_down;\n    AddEdgeUp _add_edge_up;\n    AddVertex _add_vertex;\n \
    \   std::vector<Vertex> _values;\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _vertex_node;\n    std::vector<int> _edge_node;\n    std::vector<int> _parent;\n\
    \    std::vector<int> _subtree_size;\n    std::vector<int> _heavy;\n    std::vector<edge_type>\
    \ _heavy_edge;\n    std::vector<std::vector<edge_type>> _children;\n\n    static\
    \ edge_type reversed_edge(edge_type e) {\n        std::swap(e.from, e.to);\n \
    \       return e;\n    }\n\n    const Path& node_path_down(int node) const {\n\
    \        assert(0 <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path_down.has_value());\n\
    \        return *_nodes[node].path_down;\n    }\n\n    const Path& node_path_up(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].path_up.has_value());\n        return *_nodes[node].path_up;\n\
    \    }\n\n    const Point& node_point(int node) const {\n        assert(0 <= node\
    \ && node < int(_nodes.size()));\n        assert(_nodes[node].point.has_value());\n\
    \        return *_nodes[node].point;\n    }\n\n    void set_parent(int child,\
    \ int parent) {\n        if (child != -1) _nodes[child].parent = parent;\n   \
    \ }\n\n    void recompute(int node) {\n        auto& x = _nodes[node];\n     \
    \   if (x.type == node_type::Compress) {\n            x.path_down = _compress_down(node_path_down(x.left),\
    \ node_path_down(x.right), x.edge);\n            x.path_up = _compress_up(node_path_up(x.right),\
    \ node_path_up(x.left), reversed_edge(x.edge));\n        } else if (x.type ==\
    \ node_type::Rake) {\n            x.point = _rake(node_point(x.left), node_point(x.right));\n\
    \        } else if (x.type == node_type::AddEdge) {\n            x.point = _add_edge_down(node_path_down(x.left),\
    \ x.edge);\n        } else {\n            const Point& side = x.left == -1 ? _point_id\
    \ : node_point(x.left);\n            Path path = _add_vertex(side, _values[x.vertex],\
    \ x.vertex);\n            x.path_down = path;\n            x.path_up = std::move(path);\n\
    \        }\n    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = node_type::Compress;\n    \
    \    node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = node_type::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = node_type::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = node_type::AddVertex;\n        node.left\
    \ = side;\n        node.vertex = vertex;\n        node.size = 1 + (side == -1\
    \ ? 0 : _nodes[side].size);\n        node.height = 1 + (side == -1 ? 0 : _nodes[side].height);\n\
    \        int id = new_node(std::move(node));\n        _vertex_node[vertex] = id;\n\
    \        return id;\n    }\n\n    int weighted_split(const std::vector<int>& nodes,\
    \ int l, int r) const {\n        int total = 0;\n        for (int i = l; i < r;\
    \ i++) total += _nodes[nodes[i]].size;\n        int left_sum = 0;\n        for\
    \ (int i = l; i + 1 < r; i++) {\n            left_sum += _nodes[nodes[i]].size;\n\
    \            if (2 * left_sum >= total) return i + 1;\n        }\n        return\
    \ r - 1;\n    }\n\n    int build_rake(const std::vector<int>& nodes, int l, int\
    \ r) {\n        if (l == r) return -1;\n        if (l + 1 == r) return nodes[l];\n\
    \        int m = weighted_split(nodes, l, r);\n        return new_rake(build_rake(nodes,\
    \ l, m), build_rake(nodes, m, r));\n    }\n\n    int build_compress(const std::vector<int>&\
    \ nodes, const std::vector<edge_type>& edges, int l, int r) {\n        if (l +\
    \ 1 == r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n   \
    \     return new_compress(build_compress(nodes, edges, l, m), build_compress(nodes,\
    \ edges, m, r), edges[m - 1]);\n    }\n\n    int build_vertex(int v) {\n     \
    \   std::vector<int> side_nodes;\n        for (const auto& e : _children[v]) {\n\
    \            if (e.to == _heavy[v]) continue;\n            int child_path = build_path(e.to);\n\
    \            side_nodes.push_back(new_add_edge(child_path, e));\n        }\n \
    \       return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    RerootingStaticTopTree(const m1une::graph::Graph<T>&\
    \ g, const std::vector<Vertex>& values, Point point_id,\n                    \
    \       CompressDown compress_down, CompressUp compress_up, Rake rake,\n     \
    \                      AddEdgeDown add_edge_down, AddEdgeUp add_edge_up, AddVertex\
    \ add_vertex, int root = 0)\n        : _n(g.size()),\n          _root(_n == 0\
    \ ? -1 : root),\n          _root_node(-1),\n          _point_id(std::move(point_id)),\n\
    \          _compress_down(std::move(compress_down)),\n          _compress_up(std::move(compress_up)),\n\
    \          _rake(std::move(rake)),\n          _add_edge_down(std::move(add_edge_down)),\n\
    \          _add_edge_up(std::move(add_edge_up)),\n          _add_vertex(std::move(add_vertex)),\n\
    \          _values(values) {\n        build(g, root);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root = 0) {\n        _n = g.size();\n       \
    \ _root = _n == 0 ? -1 : root;\n        assert(int(_values.size()) == _n);\n \
    \       _nodes.clear();\n        _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(),\
    \ -1);\n        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n\
    \        _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n\
    \        _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
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
    \ _root;\n    }\n\n    int root_node() const {\n        return _root_node;\n \
    \   }\n\n    int node_count() const {\n        return int(_nodes.size());\n  \
    \  }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(int id) const {\n        assert(0 <= id && id <\
    \ int(_nodes.size()));\n        return _nodes[id];\n    }\n\n    int parent_node(int\
    \ id) const {\n        return node(id).parent;\n    }\n\n    int vertex_node(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _vertex_node[v];\n\
    \    }\n\n    int local_point_node(int v) const {\n        int id = vertex_node(v);\n\
    \        assert(_nodes[id].type == node_type::AddVertex);\n        return _nodes[id].left;\n\
    \    }\n\n    const Point& local_point(int v) const {\n        int point_node\
    \ = local_point_node(v);\n        return point_node == -1 ? _point_id : node_point(point_node);\n\
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
    \ Path& path_down(int node_id) const {\n        return node_path_down(node_id);\n\
    \    }\n\n    const Path& path_up(int node_id) const {\n        return node_path_up(node_id);\n\
    \    }\n\n    const Point& point(int node_id) const {\n        return node_point(node_id);\n\
    \    }\n\n    const Path& all_prod_down() const {\n        assert(_root_node !=\
    \ -1);\n        return path_down(_root_node);\n    }\n\n    const Path& all_prod_up()\
    \ const {\n        assert(_root_node != -1);\n        return path_up(_root_node);\n\
    \    }\n\n    const Point& point_id() const {\n        return _point_id;\n   \
    \ }\n\n    template <class F>\n    void for_each_rerooting_step(int v, F&& f)\
    \ const {\n        assert(0 <= v && v < _n);\n        int cur = _vertex_node[v];\n\
    \        assert(cur != -1);\n        while (_nodes[cur].parent != -1) {\n    \
    \        int par = _nodes[cur].parent;\n            const auto& p = _nodes[par];\n\
    \            RerootingStep step;\n            step.node = par;\n            if\
    \ (p.type == node_type::Compress) {\n                step.edge = p.edge;\n   \
    \             if (p.left == cur) {\n                    step.type = step_type::CompressLower;\n\
    \                    step.sibling = p.right;\n                } else {\n     \
    \               assert(p.right == cur);\n                    step.type = step_type::CompressUpper;\n\
    \                    step.sibling = p.left;\n                }\n            }\
    \ else if (p.type == node_type::Rake) {\n                if (p.left == cur) {\n\
    \                    step.type = step_type::RakeRight;\n                    step.sibling\
    \ = p.right;\n                } else {\n                    assert(p.right ==\
    \ cur);\n                    step.type = step_type::RakeLeft;\n              \
    \      step.sibling = p.left;\n                }\n            } else if (p.type\
    \ == node_type::AddEdge) {\n                assert(p.left == cur);\n         \
    \       step.type = step_type::AddEdge;\n                step.edge = p.edge;\n\
    \            } else {\n                assert(p.type == node_type::AddVertex);\n\
    \                assert(p.left == cur);\n                step.type = step_type::AddVertex;\n\
    \                step.vertex = p.vertex;\n            }\n            f(step);\n\
    \            cur = par;\n        }\n    }\n\n    std::vector<RerootingStep> rerooting_steps(int\
    \ v) const {\n        std::vector<RerootingStep> result;\n        int cur = vertex_node(v);\n\
    \        int depth = 0;\n        while (_nodes[cur].parent != -1) {\n        \
    \    cur = _nodes[cur].parent;\n            depth++;\n        }\n        result.reserve(depth);\n\
    \        for_each_rerooting_step(v, [&](const RerootingStep& step) {\n       \
    \     result.push_back(step);\n        });\n        return result;\n    }\n\n\
    \    template <class Folder>\n    auto fold_rerooting(int v, Folder folder) const\
    \ {\n        folder.start(v, _values[v], local_point(v));\n        for_each_rerooting_step(v,\
    \ [&](const RerootingStep& step) {\n            if (step.type == step_type::CompressLower)\
    \ {\n                folder.compress_lower(path_down(step.sibling), step.edge);\n\
    \            } else if (step.type == step_type::CompressUpper) {\n           \
    \     folder.compress_upper(path_up(step.sibling), reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::AddEdge) {\n                folder.add_edge(reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::RakeLeft) {\n                folder.rake_left(point(step.sibling));\n\
    \            } else if (step.type == step_type::RakeRight) {\n               \
    \ folder.rake_right(point(step.sibling));\n            } else {\n            \
    \    folder.add_vertex(step.vertex, _values[step.vertex]);\n            }\n  \
    \      });\n        return folder.result();\n    }\n\n    Path compress_down(const\
    \ Path& upper, const Path& lower, edge_type edge) const {\n        return _compress_down(upper,\
    \ lower, edge);\n    }\n\n    Path compress_up(const Path& lower, const Path&\
    \ upper, edge_type edge) const {\n        return _compress_up(lower, upper, edge);\n\
    \    }\n\n    Point rake(const Point& left, const Point& right) const {\n    \
    \    return _rake(left, right);\n    }\n\n    Point add_edge_down(const Path&\
    \ path, edge_type edge) const {\n        return _add_edge_down(path, edge);\n\
    \    }\n\n    Point add_edge_up(const Path& path, edge_type edge) const {\n  \
    \      return _add_edge_up(path, edge);\n    }\n\n    Path add_vertex(const Point&\
    \ side, const Vertex& value, int vertex) const {\n        return _add_vertex(side,\
    \ value, vertex);\n    }\n\n    static edge_type reverse_edge(edge_type edge)\
    \ {\n        return reversed_edge(edge);\n    }\n};\n\ntemplate <class T, class\
    \ Vertex, class Point, class CompressDown, class CompressUp, class Rake, class\
    \ AddEdgeDown,\n          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const\
    \ m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n\
    \                       Rake, AddEdgeDown, AddEdgeUp, AddVertex, int)\n    ->\
    \ RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex,\
    \ int>, Point, CompressDown,\n                              CompressUp, Rake,\
    \ AddEdgeDown, AddEdgeUp, AddVertex>;\n\ntemplate <class T, class Vertex, class\
    \ Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,\n\
    \          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n             \
    \          Rake, AddEdgeDown, AddEdgeUp, AddVertex)\n    -> RerootingStaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,\n\
    \                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/rerooting_static_top_tree.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/rerooting_static_top_tree.hpp
layout: document
title: Rerooting Static Top Tree
---

## Overview

`m1une::tree::RerootingStaticTopTree` is the bidirectional cluster engine used
for static-top-tree solutions to dynamic rerooting DP problems.

Compared with `StaticTopTree`, it stores each path cluster in both directions:

* `path_down`: the cluster viewed from the ancestor-side boundary toward the
  descendant-side boundary.
* `path_up`: the same cluster viewed from the descendant-side boundary toward
  the ancestor-side boundary.

This is the extra information needed when a query asks for the DP value with an
arbitrary vertex `v` as the root. After removing `v`, the remaining connected
components can be represented by $O(\log N)$ static-top-tree clusters. Some of
those clusters are viewed in the original rooted direction, and some are viewed
in the reverse direction. Therefore forward and backward transitions are kept
separate.

This header maintains the decomposition and the cached directional cluster
values under vertex-value and edge-cost updates. It also exposes the
$O(\log N)$ rerooting walk around a query vertex with
`for_each_rerooting_step(v, f)` and `rerooting_steps(v)`.

There is deliberately no universal `prod(v)` member. For many static-top-tree
applications, `Path` is not just a plain subtree DP value; it may be a
directional transformation, a small automaton, or another problem-specific
object. The library therefore supplies the ordered clusters needed to reroot at
`v`, while your DP code decides how those clusters are folded and how the final
answer is read.

## Cluster Types

The structure uses three user-facing types:

| Type | Meaning |
| --- | --- |
| `Vertex` | Stored value of one original vertex. |
| `Path` | A connected cluster with two boundary vertices on one heavy path. |
| `Point` | A collection of completed side components attached to one boundary vertex. |

A `Path` cluster has an original orientation: top boundary first, bottom
boundary second. In the rooted tree, the top boundary is closer to `root`.

For one path cluster:

* `path_down` means "view the cluster starting from the top boundary".
* `path_up` means "view the cluster starting from the bottom boundary".

A `Point` cluster has only one boundary vertex, so it does not have a down/up
pair. It is the aggregate contribution of several independent components
attached to that one boundary.

## Operations

The constructor receives:

```cpp
RerootingStaticTopTree(
    g,
    values,
    point_id,
    compress_down,
    compress_up,
    rake,
    add_edge_down,
    add_edge_up,
    add_vertex,
    root
);
```

The callbacks are:

| Callback | Signature | Meaning |
| --- | --- | --- |
| `compress_down` | `Path compress_down(Path upper, Path lower, Edge e)` | Concatenate two adjacent path clusters in the rooted direction. `e` goes from `upper`'s bottom boundary to `lower`'s top boundary. |
| `compress_up` | `Path compress_up(Path lower, Path upper, Edge e)` | Concatenate the same two clusters in reverse. `e` goes from `lower`'s top boundary to `upper`'s bottom boundary, usually `reverse_edge(original_e)`. |
| `rake` | `Point rake(Point a, Point b)` | Merge two independent point clusters attached to the same boundary vertex. |
| `add_edge_down` | `Point add_edge_down(Path child, Edge e)` | Convert a child path into a point contribution viewed from the parent side. `e.from` is the parent-side boundary and `e.to` is the path top boundary. |
| `add_edge_up` | `Point add_edge_up(Path parent_side, Edge e)` | Convert a path into a point contribution viewed from the child side. `e.from` is the child-side boundary and `e.to` is the path bottom boundary. |
| `add_vertex` | `Path add_vertex(Point side, Vertex value, int v)` | Insert original vertex `v` and its side contributions, making a one-vertex path. |

`point_id` is the identity for `rake`.

In code examples, `const auto& e` is just a generic-lambda shorthand for the
edge type `m1une::graph::Edge<T>`. You can spell it explicitly, for example
`const m1une::graph::Edge<long long>& e`, if the graph cost type is
`long long`.

The important detail is that `compress_up` and `add_edge_up` are not just
aliases for the downward functions. They receive the path states in the opposite
order and receive an edge whose direction is also opposite. If your DP stores
direction-sensitive data, such as prefix/suffix values, hashes, affine
functions, or ordered endpoint states, the backward formulas are often different
from the forward formulas.

For a symmetric DP, the code may look almost the same, but it is still safer to
write the two callbacks separately:

```cpp
auto compress_down = [](Path upper, Path lower, const auto& e) {
    // Start from upper's top boundary, traverse upper downward,
    // cross e, then traverse lower downward.
};
auto compress_up = [](Path lower, Path upper, const auto& e) {
    // Start from lower's bottom boundary, traverse lower upward,
    // cross e, then traverse upper upward.
};
```

## What Is Stored

Internally the structure is a binary expression tree. Each expression node is
one of:

| Node type | Output | Stored value |
| --- | --- | --- |
| `AddVertex` | `Path` | `path_down` and `path_up` for one original vertex plus its raked side components. |
| `AddEdge` | `Point` | A child path converted through one rooted tree edge. |
| `Rake` | `Point` | The rake of two point clusters at the same boundary. |
| `Compress` | `Path` | The concatenation of two path clusters. |

For a `Compress` node with left child `upper`, right child `lower`, and edge
`e` from `upper` to `lower`, the cached values are:

```cpp
path_down = compress_down(upper.path_down, lower.path_down, e);
path_up = compress_up(lower.path_up, upper.path_up, reverse_edge(e));
```

For an `AddEdge` node built from a rooted child edge `e`, the cached point is:

```cpp
point = add_edge_down(child.path_down, e);
```

The upward edge conversion is not cached in `AddEdge`, because the rooted build
only needs the downward side contribution. It is exposed as `add_edge_up` for
rerooting query code that peels clusters from the opposite direction.

`all_prod_down()` is the whole tree viewed from `root` toward the bottom of the
root heavy path. `all_prod_up()` is the same whole-tree cluster viewed from that
bottom boundary back toward `root`. The bottom boundary is determined by the
heavy paths chosen during construction; it is not an arbitrary query vertex.

## Rerooting Steps

For a query vertex `v`, start with the original vertex node:

```cpp
int cur = stt.vertex_node(v);
Point side = stt.local_point(v);
```

`local_point(v)` is the raked contribution of the non-heavy child components
already stored inside the `AddVertex` node of `v`. If there are no such
components, it returns `point_id()`.

For low-level access, you can process the raw step stream:

```cpp
stt.for_each_rerooting_step(v, [&](const auto& step) {
    using Step = decltype(stt)::step_type;
    if (step.type == Step::CompressLower) {
        // The current path cluster was the upper/left child.
        // step.sibling is the lower/right path cluster.
        // stt.path_down(step.sibling) is viewed from the current side.
    } else if (step.type == Step::CompressUpper) {
        // The current path cluster was the lower/right child.
        // step.sibling is the upper/left path cluster.
        // stt.path_up(step.sibling) is viewed from the current side.
    } else if (step.type == Step::AddEdge) {
        // Leaving a child path through step.edge.
        // step.edge is oriented parent -> child; reverse it when viewing upward.
    } else if (step.type == Step::RakeLeft) {
        // A point sibling before the current rake range.
    } else if (step.type == Step::RakeRight) {
        // A point sibling after the current rake range.
    } else {
        // Reached an AddVertex node. step.vertex is that original vertex.
    }
});
```

The same data can be materialized with `rerooting_steps(v)` if storing the walk
is more convenient than visiting it online.

Each step has these fields:

| Field | Meaning |
| --- | --- |
| `type` | One of `CompressLower`, `CompressUpper`, `AddEdge`, `RakeLeft`, `RakeRight`, `AddVertex`. |
| `node` | The expression-tree parent node reached by this step. |
| `sibling` | The sibling cluster for compress/rake steps, otherwise `-1`. |
| `vertex` | The original vertex for an `AddVertex` step, otherwise `-1`. |
| `edge` | The rooted tree edge for compress/add-edge steps. |

This removes the error-prone part of rerooting queries: finding the sibling
clusters and keeping their order straight. The folder you write for a problem
only needs to say what each step means for that DP.

For ordinary use, prefer `fold_rerooting(v, folder)`. It performs this dispatch
for you and passes already-oriented cluster values to the folder. The effective
folder method signatures are:

| Folder method | Signature | Called when |
| --- | --- | --- |
| `start` | `void start(int v, const Vertex& value, const Point& local_point)` | Before processing the walk from `v`. |
| `compress_lower` | `void compress_lower(const Path& path, Edge edge)` | A lower path sibling is attached below the current path. |
| `compress_upper` | `void compress_upper(const Path& path, Edge edge)` | An upper path sibling is attached above the current path. |
| `add_edge` | `void add_edge(Edge edge)` | The walk leaves a child path and moves toward its parent vertex. |
| `rake_left` | `void rake_left(const Point& point)` | A point sibling appears before the current rake range. |
| `rake_right` | `void rake_right(const Point& point)` | A point sibling appears after the current rake range. |
| `add_vertex` | `void add_vertex(int vertex, const Vertex& value)` | The walk reaches a parent `AddVertex` node. |
| `result` | `Answer result() const` | Returns the query answer after the walk. |

Here `Edge` is the structure's `edge_type`, and `Answer` is the return type of
`fold_rerooting`. The methods may take small arguments by value instead of by
`const` reference if that is more convenient.

Here `compress_upper` and `add_edge` receive reversed edges, so the edge is
oriented in the direction the rerooting walk is moving.

## Public Members

| Method | Description | Complexity |
| --- | --- | --- |
| `RerootingStaticTopTree(...)` | Builds the expression tree. | $O(N \log N)$ callback work |
| `int size()` | Number of original vertices. | $O(1)$ |
| `bool empty()` | Whether the original tree is empty. | $O(1)$ |
| `int root()` | Root used to orient the static decomposition. | $O(1)$ |
| `int root_node()` | Expression-tree node id of the whole-tree path cluster. | $O(1)$ |
| `int node_count()` | Number of expression-tree nodes. | $O(1)$ |
| `int height()` | Height of the expression tree. Updates are proportional to this. | $O(1)$ |
| `const std::vector<Node>& nodes()` | All expression-tree nodes. | $O(1)$ |
| `const Node& node(id)` | One expression-tree node. | $O(1)$ |
| `int parent_node(id)` | Parent expression node, or `-1` at the root. | $O(1)$ |
| `int vertex_node(v)` | The `AddVertex` node corresponding to original vertex `v`. | $O(1)$ |
| `int local_point_node(v)` | Rake node stored inside `AddVertex(v)`, or `-1`. | $O(1)$ |
| `const Point& local_point(v)` | Raked non-heavy child contribution stored at `v`, or `point_id()`. | $O(1)$ |
| `const Vertex& get(v)` | Stored value of original vertex `v`. | $O(1)$ |
| `void set(v, value)` | Update one vertex value and recompute ancestors. | $O(\text{height})$ |
| `void set_edge_cost(edge_id, cost)` | Update one edge cost and recompute ancestors. | $O(\text{height})$ |
| `const Path& path_down(node_id)` | Downward path value of a path-output node. | $O(1)$ |
| `const Path& path_up(node_id)` | Upward path value of a path-output node. | $O(1)$ |
| `const Point& point(node_id)` | Point value of a point-output node. | $O(1)$ |
| `const Path& all_prod_down()` | Whole-tree downward path value. | $O(1)$ |
| `const Path& all_prod_up()` | Whole-tree upward path value. | $O(1)$ |
| `const Point& point_id()` | Identity point value for `rake`. | $O(1)$ |
| `for_each_rerooting_step(v, f)` | Visits rerooting steps from `vertex_node(v)` to `root_node()`. | $O(\text{height})$ |
| `std::vector<RerootingStep> rerooting_steps(v)` | Returns the same rerooting steps as a vector. | $O(\text{height})$ |
| `fold_rerooting(v, folder)` | Runs the rerooting walk and calls the folder methods above. | $O(\text{height})$ |
| `compress_down(...)`, `compress_up(...)` | Public wrappers around the directional path callbacks. | Callback cost |
| `rake(...)` | Public wrapper around the point merge callback. | Callback cost |
| `add_edge_down(...)`, `add_edge_up(...)` | Public wrappers around the directional edge callbacks. | Callback cost |
| `add_vertex(...)` | Public wrapper around the vertex callback. | Callback cost |
| `static reverse_edge(edge)` | Returns a copy of `edge` with `from` and `to` swapped. | $O(1)$ |

Calling `path_down` or `path_up` on a point-output node, or `point` on a
path-output node, is a logic error and is checked by `assert`.

## Using It In Problems

For a rerooting-style static top tree solution:

1. Define `Point` as the DP aggregate for independent neighbor components
   attached to one vertex.
2. Define `Path` as the information needed to move that aggregate through a
   chain of vertices in both directions.
3. Implement the downward operations exactly as in an ordinary static top tree.
4. Implement the upward operations with the reverse argument order and reversed
   edge direction.
5. For a query vertex `v`, initialize the query state from `local_point(v)`,
   then process `for_each_rerooting_step(v, f)`. The siblings encountered on
   this walk form the $O(\log N)$ clusters needed for the rerooted answer.

The final fold depends on the DP. For example, a DP that stores path clusters
as functions usually applies the collected functions to a point state; a DP
that stores endpoint states may keep separate accumulators for the parent side
and child side before the final `add_vertex`. In problems such as ABC460 G,
the folder keeps the same-color component contribution around the query vertex
and reads the component sum after applying the steps.

## Example: ABC460 G - Vertex Flip Query

ABC460 G asks for dynamic updates on a colored, weighted tree:

* flip one vertex color,
* add to one vertex weight,
* for a vertex `v`, output the sum of weights in the connected component of
  `v` after deleting all vertices whose color differs from `color[v]`.

This can be seen as a rerooting DP query. If the tree is rooted at `v`, the
answer is the contribution of all neighbor-side components that can connect to
`v` through vertices of the same color.

One convenient state is:

```cpp
struct Vertex {
    long long weight;
    int color;
};

struct Point {
    long long sum[2];
};

struct Path {
    int first_color, last_color;
    long long first_sum, last_sum;
    bool connected;
};
```

The meaning is:

| State | Meaning |
| --- | --- |
| `Point::sum[c]` | For side components attached to a boundary vertex, total contribution reachable if the boundary vertex has color `c`. |
| `Path::first_color` | Color of the first boundary in the current orientation. |
| `Path::last_color` | Color of the last boundary in the current orientation. |
| `Path::first_sum` | Same-color component sum containing the first boundary, inside this path cluster. |
| `Path::last_sum` | Same-color component sum containing the last boundary, inside this path cluster. |
| `Path::connected` | Whether the first and last boundaries are in the same same-color component. |

The cluster operations are short:

```cpp
auto compress = [](Path a, Path b, const auto&) {
    bool join = a.last_color == b.first_color;
    Path res{a.first_color, b.last_color, a.first_sum, b.last_sum, false};
    if (join && a.connected) res.first_sum += b.first_sum;
    if (join && b.connected) res.last_sum += a.last_sum;
    res.connected = a.connected && b.connected && join;
    return res;
};

auto rake = [](Point a, Point b) {
    return Point{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]};
};

auto add_edge = [](Path path, const auto&) {
    Point res{};
    res.sum[path.first_color] = path.first_sum;
    return res;
};

auto add_vertex = [](Point side, Vertex value, int) {
    long long sum = value.weight + side.sum[value.color];
    return Path{value.color, value.color, sum, sum, true};
};
```

Here `compress` is orientation-relative, so it can be used for both
`compress_down` and `compress_up`. Likewise `add_edge` can be used for both
edge directions because the graph edge itself does not change the component
value; only endpoint colors decide whether the component can pass through the
next vertex.

Build the structure like this:

```cpp
auto stt = m1une::tree::RerootingStaticTopTree(
    g,
    values,
    Point{0, 0},
    compress,
    compress,
    rake,
    add_edge,
    add_edge,
    add_vertex
);
```

For query type `3 v`, define a folder and pass it to `fold_rerooting`. The
folder keeps the component containing the original query vertex and grows it
while the library climbs from `vertex_node(v)` to the expression root.

```cpp
using Stt = decltype(stt);

struct QueryFolder {
    const Stt& stt;
    int color = 0;
    long long answer = 0;
    bool touches_top = false;
    bool touches_bottom = false;
    bool pending_open = false;
    Point pending{};

    void start(int, const Vertex& value, const Point& local) {
        color = value.color;
        answer = value.weight + local.sum[color];
        touches_top = true;
        touches_bottom = true;
        pending_open = false;
        pending = stt.point_id();
    }

    void compress_lower(const Path& lower, Stt::edge_type) {
        bool connect = touches_bottom && lower.first_color == color;
        if (connect) answer += lower.first_sum;
        touches_bottom = connect && lower.connected;
    }

    void compress_upper(const Path& upper, Stt::edge_type) {
        bool connect = touches_top && upper.first_color == color;
        if (connect) answer += upper.first_sum;
        touches_top = connect && upper.connected;
    }

    void add_edge(Stt::edge_type) {
        pending_open = touches_top;
        pending = stt.point_id();
    }

    void rake_left(const Point& point) {
        if (pending_open) pending = stt.rake(point, pending);
    }

    void rake_right(const Point& point) {
        if (pending_open) pending = stt.rake(pending, point);
    }

    void add_vertex(int, const Vertex& value) {
        if (pending_open && value.color == color) {
            answer += value.weight + pending.sum[color];
            touches_top = true;
            touches_bottom = true;
        } else {
            touches_top = false;
            touches_bottom = false;
        }
        pending_open = false;
        pending = stt.point_id();
    }

    long long result() const {
        return answer;
    }
};

auto query = [&](int v) {
    return stt.fold_rerooting(v, QueryFolder{stt});
};
```

The flags have these roles:

| Variable | Meaning |
| --- | --- |
| `touches_top` | The query component reaches the current path cluster's top boundary. |
| `touches_bottom` | The query component reaches the current path cluster's bottom boundary. |
| `pending_open` | We have moved from a child path into a parent-side point/rake cluster, and the component can still reach the parent vertex. |
| `pending` | Other side components of that parent vertex collected while climbing through `Rake` nodes. |

For updates, keep the external `values` array in sync and call `set`:

```cpp
// type 1: flip color
values[v].color ^= 1;
stt.set(v, values[v]);

// type 2: add weight
values[v].weight += x;
stt.set(v, values[v]);

// type 3: answer
std::cout << query(v) << '\n';
```

The input vertices in ABC460 G are 1-indexed, so decrement `v` before using
these snippets.

The total complexity is $O(N \log N)$ construction callback work and
$O(\log N)$ per update/query, assuming the static top tree height is logarithmic.
The verification test `test_rerooting_static_top_tree_vertex_component`
contains a small brute-force-checked version of this pattern.

The library guarantees that the cluster values you read during that fold are
kept up to date after `set` and `set_edge_cost`.

## Example: Directional Distance Aggregates

This example stores, for a path cluster:

* `count`: number of vertices in the cluster.
* `sum`: sum of distances from the current viewing boundary.
* `length`: distance between the two path boundaries.

The downward and upward formulas have the same shape for distances, but the
argument names and edge direction are intentionally different.

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

auto compress_down = [](Path upper, Path lower, const auto& e) {
    long long shift = upper.length + e.cost;
    return Path{
        upper.count + lower.count,
        upper.sum + lower.sum + lower.count * shift,
        upper.length + e.cost + lower.length
    };
};

auto compress_up = [](Path lower, Path upper, const auto& e) {
    long long shift = lower.length + e.cost;
    return Path{
        lower.count + upper.count,
        lower.sum + upper.sum + upper.count * shift,
        lower.length + e.cost + upper.length
    };
};

auto rake = [](Point a, Point b) {
    return Point{a.count + b.count, a.sum + b.sum};
};

auto add_edge_down = [](Path child, const auto& e) {
    return Point{child.count, child.sum + child.count * e.cost};
};

auto add_edge_up = [](Path parent_side, const auto& e) {
    return Point{parent_side.count, parent_side.sum + parent_side.count * e.cost};
};

auto add_vertex = [](Point side, long long weight, int) {
    return Path{side.count + weight, side.sum, 0};
};

auto stt = m1une::tree::RerootingStaticTopTree(
    g,
    weights,
    Point{0, 0},
    compress_down,
    compress_up,
    rake,
    add_edge_down,
    add_edge_up,
    add_vertex
);
```

For this DP, `stt.all_prod_down().sum` is the sum of distances from the build
root to all weighted vertices. `stt.all_prod_up().sum` is the sum of distances
from the bottom boundary of the root heavy path to all weighted vertices.

## Notes

The input graph should be an undirected connected tree built with `add_edge`.
Inactive edges are ignored during construction.

If the tree topology or the build root changes, rebuild the structure. Vertex
values and edge costs can be updated with `set` and `set_edge_cost`.
