#ifndef M1UNE_TREE_STATIC_TOP_TREE_HPP
#define M1UNE_TREE_STATIC_TOP_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "../graph/graph.hpp"

namespace m1une {
namespace tree {

namespace internal {

enum class StaticTopTreeNodeType {
    Compress,
    Rake,
    AddEdge,
    AddVertex,
};

}  // namespace internal

template <class T, class Vertex, class Path, class Point, class Compress, class Rake, class AddEdge,
          class AddVertex>
struct StaticTopTree {
    using cost_type = T;
    using vertex_type = Vertex;
    using path_type = Path;
    using point_type = Point;
    using edge_type = m1une::graph::Edge<T>;

   private:
    struct Node {
        internal::StaticTopTreeNodeType type;
        int left = -1;
        int right = -1;
        int parent = -1;
        int vertex = -1;
        edge_type edge;
        int size = 0;
        int height = 1;
        std::optional<Path> path;
        std::optional<Point> point;
    };

    int _n;
    int _root;
    int _root_node;
    Point _point_id;
    Compress _compress;
    Rake _rake;
    AddEdge _add_edge;
    AddVertex _add_vertex;
    std::vector<Vertex> _values;
    std::vector<Node> _nodes;
    std::vector<int> _vertex_node;
    std::vector<int> _edge_node;
    std::vector<int> _parent;
    std::vector<int> _subtree_size;
    std::vector<int> _heavy;
    std::vector<edge_type> _heavy_edge;
    std::vector<std::vector<edge_type>> _children;

    const Path& path_value(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
        assert(_nodes[node].path.has_value());
        return *_nodes[node].path;
    }

    const Point& point_value(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
        assert(_nodes[node].point.has_value());
        return *_nodes[node].point;
    }

    void set_parent(int child, int parent) {
        if (child != -1) _nodes[child].parent = parent;
    }

    void recompute(int node) {
        auto& x = _nodes[node];
        if (x.type == internal::StaticTopTreeNodeType::Compress) {
            x.path = _compress(path_value(x.left), path_value(x.right), x.edge);
        } else if (x.type == internal::StaticTopTreeNodeType::Rake) {
            x.point = _rake(point_value(x.left), point_value(x.right));
        } else if (x.type == internal::StaticTopTreeNodeType::AddEdge) {
            x.point = _add_edge(path_value(x.left), x.edge);
        } else {
            const Point& side = x.left == -1 ? _point_id : point_value(x.left);
            x.path = _add_vertex(side, _values[x.vertex], x.vertex);
        }
    }

    int new_node(Node node) {
        int id = int(_nodes.size());
        _nodes.push_back(std::move(node));
        set_parent(_nodes[id].left, id);
        set_parent(_nodes[id].right, id);
        recompute(id);
        return id;
    }

    int new_compress(int left, int right, edge_type edge) {
        Node node;
        node.type = internal::StaticTopTreeNodeType::Compress;
        node.left = left;
        node.right = right;
        node.edge = edge;
        node.size = _nodes[left].size + _nodes[right].size;
        node.height = std::max(_nodes[left].height, _nodes[right].height) + 1;
        int id = new_node(std::move(node));
        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id] = id;
        return id;
    }

    int new_rake(int left, int right) {
        Node node;
        node.type = internal::StaticTopTreeNodeType::Rake;
        node.left = left;
        node.right = right;
        node.size = _nodes[left].size + _nodes[right].size;
        node.height = std::max(_nodes[left].height, _nodes[right].height) + 1;
        return new_node(std::move(node));
    }

    int new_add_edge(int child, edge_type edge) {
        Node node;
        node.type = internal::StaticTopTreeNodeType::AddEdge;
        node.left = child;
        node.edge = edge;
        node.size = _nodes[child].size;
        node.height = _nodes[child].height + 1;
        int id = new_node(std::move(node));
        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id] = id;
        return id;
    }

    int new_add_vertex(int side, int vertex) {
        Node node;
        node.type = internal::StaticTopTreeNodeType::AddVertex;
        node.left = side;
        node.vertex = vertex;
        node.size = 1 + (side == -1 ? 0 : _nodes[side].size);
        node.height = 1 + (side == -1 ? 0 : _nodes[side].height);
        int id = new_node(std::move(node));
        _vertex_node[vertex] = id;
        return id;
    }

    int weighted_split(const std::vector<int>& nodes, int l, int r) const {
        int total = 0;
        for (int i = l; i < r; i++) total += _nodes[nodes[i]].size;
        int left_sum = 0;
        for (int i = l; i + 1 < r; i++) {
            left_sum += _nodes[nodes[i]].size;
            if (2 * left_sum >= total) return i + 1;
        }
        return r - 1;
    }

    int build_rake(const std::vector<int>& nodes, int l, int r) {
        if (l == r) return -1;
        if (l + 1 == r) return nodes[l];
        int m = weighted_split(nodes, l, r);
        return new_rake(build_rake(nodes, l, m), build_rake(nodes, m, r));
    }

    int build_compress(const std::vector<int>& nodes, const std::vector<edge_type>& edges, int l, int r) {
        if (l + 1 == r) return nodes[l];
        int m = weighted_split(nodes, l, r);
        return new_compress(build_compress(nodes, edges, l, m), build_compress(nodes, edges, m, r), edges[m - 1]);
    }

    int build_vertex(int v) {
        std::vector<int> side_nodes;
        for (const auto& e : _children[v]) {
            if (e.to == _heavy[v]) continue;
            int child_path = build_path(e.to);
            side_nodes.push_back(new_add_edge(child_path, e));
        }
        return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())), v);
    }

    int build_path(int start) {
        std::vector<int> path_nodes;
        std::vector<edge_type> path_edges;
        for (int v = start; v != -1; v = _heavy[v]) {
            path_nodes.push_back(build_vertex(v));
            if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);
        }
        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));
    }

    void recompute_up(int node) {
        while (node != -1) {
            recompute(node);
            node = _nodes[node].parent;
        }
    }

   public:
    StaticTopTree(const m1une::graph::Graph<T>& g, const std::vector<Vertex>& values, Point point_id,
                  Compress compress, Rake rake, AddEdge add_edge, AddVertex add_vertex, int root = 0)
        : _n(g.size()),
          _root(_n == 0 ? -1 : root),
          _root_node(-1),
          _point_id(std::move(point_id)),
          _compress(std::move(compress)),
          _rake(std::move(rake)),
          _add_edge(std::move(add_edge)),
          _add_vertex(std::move(add_vertex)),
          _values(values) {
        build(g, root);
    }

    void build(const m1une::graph::Graph<T>& g, int root = 0) {
        _n = g.size();
        _root = _n == 0 ? -1 : root;
        assert(int(_values.size()) == _n);
        _nodes.clear();
        _vertex_node.assign(_n, -1);
        _edge_node.assign(g.edge_count(), -1);
        _parent.assign(_n, -2);
        _subtree_size.assign(_n, 1);
        _heavy.assign(_n, -1);
        _heavy_edge.assign(_n, edge_type());
        _children.assign(_n, {});
        _root_node = -1;

        if (_n == 0) return;
        assert(0 <= root && root < _n);
        assert(int(g.edges().size()) == _n - 1);

        std::vector<int> order;
        order.reserve(_n);
        std::vector<int> stack = {root};
        _parent[root] = -1;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            order.push_back(v);
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                if (_parent[e.to] != -2) continue;
                _parent[e.to] = v;
                _children[v].push_back(e);
                stack.push_back(e.to);
            }
        }
        assert(int(order.size()) == _n);

        for (int i = int(order.size()) - 1; i >= 0; i--) {
            int v = order[i];
            for (const auto& e : _children[v]) {
                _subtree_size[v] += _subtree_size[e.to];
                if (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {
                    _heavy[v] = e.to;
                    _heavy_edge[v] = e;
                }
            }
        }

        _root_node = build_path(root);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int root() const {
        return _root;
    }

    int node_count() const {
        return int(_nodes.size());
    }

    int height() const {
        return _root_node == -1 ? 0 : _nodes[_root_node].height;
    }

    const Vertex& get(int v) const {
        assert(0 <= v && v < _n);
        return _values[v];
    }

    const Vertex& operator[](int v) const {
        return get(v);
    }

    void set(int v, const Vertex& value) {
        assert(0 <= v && v < _n);
        assert(_vertex_node[v] != -1);
        _values[v] = value;
        recompute_up(_vertex_node[v]);
    }

    void set(int v, Vertex&& value) {
        assert(0 <= v && v < _n);
        assert(_vertex_node[v] != -1);
        _values[v] = std::move(value);
        recompute_up(_vertex_node[v]);
    }

    void set_edge_cost(int edge_id, T cost) {
        assert(0 <= edge_id && edge_id < int(_edge_node.size()));
        int node = _edge_node[edge_id];
        assert(node != -1);
        _nodes[node].edge.cost = cost;
        recompute_up(node);
    }

    const Path& all_prod() const {
        assert(_root_node != -1);
        return path_value(_root_node);
    }

    const Path& query() const {
        return all_prod();
    }
};

template <class T, class Vertex, class Point, class Compress, class Rake, class AddEdge, class AddVertex>
StaticTopTree(const m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, Compress, Rake, AddEdge,
              AddVertex, int)
    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress, Rake,
                     AddEdge, AddVertex>;

template <class T, class Vertex, class Point, class Compress, class Rake, class AddEdge, class AddVertex>
StaticTopTree(const m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, Compress, Rake, AddEdge, AddVertex)
    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress, Rake,
                     AddEdge, AddVertex>;

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_STATIC_TOP_TREE_HPP
