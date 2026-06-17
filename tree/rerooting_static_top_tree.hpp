#ifndef M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP
#define M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace tree {

namespace internal {

enum class RerootingStaticTopTreeNodeType {
    Compress,
    Rake,
    AddEdge,
    AddVertex,
};

enum class RerootingStaticTopTreeStepType {
    CompressLower,
    CompressUpper,
    AddEdge,
    RakeLeft,
    RakeRight,
    AddVertex,
};

}  // namespace internal

template <class T, class Vertex, class Path, class Point, class CompressDown, class CompressUp, class Rake,
          class AddEdgeDown, class AddEdgeUp, class AddVertex>
struct RerootingStaticTopTree {
    using cost_type = T;
    using vertex_type = Vertex;
    using path_type = Path;
    using point_type = Point;
    using edge_type = m1une::graph::Edge<T>;
    using node_type = internal::RerootingStaticTopTreeNodeType;
    using step_type = internal::RerootingStaticTopTreeStepType;

    struct Node {
        node_type type;
        int left = -1;
        int right = -1;
        int parent = -1;
        int vertex = -1;
        edge_type edge;
        int size = 0;
        int height = 1;
        std::optional<Path> path_down;
        std::optional<Path> path_up;
        std::optional<Point> point;
    };

    struct RerootingStep {
        step_type type;
        int node = -1;
        int sibling = -1;
        int vertex = -1;
        edge_type edge;
    };

   private:
    int _n;
    int _root;
    int _root_node;
    Point _point_id;
    CompressDown _compress_down;
    CompressUp _compress_up;
    Rake _rake;
    AddEdgeDown _add_edge_down;
    AddEdgeUp _add_edge_up;
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

    static edge_type reversed_edge(edge_type e) {
        std::swap(e.from, e.to);
        return e;
    }

    const Path& node_path_down(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
        assert(_nodes[node].path_down.has_value());
        return *_nodes[node].path_down;
    }

    const Path& node_path_up(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
        assert(_nodes[node].path_up.has_value());
        return *_nodes[node].path_up;
    }

    const Point& node_point(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
        assert(_nodes[node].point.has_value());
        return *_nodes[node].point;
    }

    void set_parent(int child, int parent) {
        if (child != -1) _nodes[child].parent = parent;
    }

    void recompute(int node) {
        auto& x = _nodes[node];
        if (x.type == node_type::Compress) {
            x.path_down = _compress_down(node_path_down(x.left), node_path_down(x.right), x.edge);
            x.path_up = _compress_up(node_path_up(x.right), node_path_up(x.left), reversed_edge(x.edge));
        } else if (x.type == node_type::Rake) {
            x.point = _rake(node_point(x.left), node_point(x.right));
        } else if (x.type == node_type::AddEdge) {
            x.point = _add_edge_down(node_path_down(x.left), x.edge);
        } else {
            const Point& side = x.left == -1 ? _point_id : node_point(x.left);
            Path path = _add_vertex(side, _values[x.vertex], x.vertex);
            x.path_down = path;
            x.path_up = std::move(path);
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
        node.type = node_type::Compress;
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
        node.type = node_type::Rake;
        node.left = left;
        node.right = right;
        node.size = _nodes[left].size + _nodes[right].size;
        node.height = std::max(_nodes[left].height, _nodes[right].height) + 1;
        return new_node(std::move(node));
    }

    int new_add_edge(int child, edge_type edge) {
        Node node;
        node.type = node_type::AddEdge;
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
        node.type = node_type::AddVertex;
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
    RerootingStaticTopTree(const m1une::graph::Graph<T>& g, const std::vector<Vertex>& values, Point point_id,
                           CompressDown compress_down, CompressUp compress_up, Rake rake,
                           AddEdgeDown add_edge_down, AddEdgeUp add_edge_up, AddVertex add_vertex, int root = 0)
        : _n(g.size()),
          _root(_n == 0 ? -1 : root),
          _root_node(-1),
          _point_id(std::move(point_id)),
          _compress_down(std::move(compress_down)),
          _compress_up(std::move(compress_up)),
          _rake(std::move(rake)),
          _add_edge_down(std::move(add_edge_down)),
          _add_edge_up(std::move(add_edge_up)),
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

    int root_node() const {
        return _root_node;
    }

    int node_count() const {
        return int(_nodes.size());
    }

    int height() const {
        return _root_node == -1 ? 0 : _nodes[_root_node].height;
    }

    const std::vector<Node>& nodes() const {
        return _nodes;
    }

    const Node& node(int id) const {
        assert(0 <= id && id < int(_nodes.size()));
        return _nodes[id];
    }

    int parent_node(int id) const {
        return node(id).parent;
    }

    int vertex_node(int v) const {
        assert(0 <= v && v < _n);
        return _vertex_node[v];
    }

    int local_point_node(int v) const {
        int id = vertex_node(v);
        assert(_nodes[id].type == node_type::AddVertex);
        return _nodes[id].left;
    }

    const Point& local_point(int v) const {
        int point_node = local_point_node(v);
        return point_node == -1 ? _point_id : node_point(point_node);
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

    const Path& path_down(int node_id) const {
        return node_path_down(node_id);
    }

    const Path& path_up(int node_id) const {
        return node_path_up(node_id);
    }

    const Point& point(int node_id) const {
        return node_point(node_id);
    }

    const Path& all_prod_down() const {
        assert(_root_node != -1);
        return path_down(_root_node);
    }

    const Path& all_prod_up() const {
        assert(_root_node != -1);
        return path_up(_root_node);
    }

    const Point& point_id() const {
        return _point_id;
    }

    template <class F>
    void for_each_rerooting_step(int v, F&& f) const {
        assert(0 <= v && v < _n);
        int cur = _vertex_node[v];
        assert(cur != -1);
        while (_nodes[cur].parent != -1) {
            int par = _nodes[cur].parent;
            const auto& p = _nodes[par];
            RerootingStep step;
            step.node = par;
            if (p.type == node_type::Compress) {
                step.edge = p.edge;
                if (p.left == cur) {
                    step.type = step_type::CompressLower;
                    step.sibling = p.right;
                } else {
                    assert(p.right == cur);
                    step.type = step_type::CompressUpper;
                    step.sibling = p.left;
                }
            } else if (p.type == node_type::Rake) {
                if (p.left == cur) {
                    step.type = step_type::RakeRight;
                    step.sibling = p.right;
                } else {
                    assert(p.right == cur);
                    step.type = step_type::RakeLeft;
                    step.sibling = p.left;
                }
            } else if (p.type == node_type::AddEdge) {
                assert(p.left == cur);
                step.type = step_type::AddEdge;
                step.edge = p.edge;
            } else {
                assert(p.type == node_type::AddVertex);
                assert(p.left == cur);
                step.type = step_type::AddVertex;
                step.vertex = p.vertex;
            }
            f(step);
            cur = par;
        }
    }

    std::vector<RerootingStep> rerooting_steps(int v) const {
        std::vector<RerootingStep> result;
        int cur = vertex_node(v);
        int depth = 0;
        while (_nodes[cur].parent != -1) {
            cur = _nodes[cur].parent;
            depth++;
        }
        result.reserve(depth);
        for_each_rerooting_step(v, [&](const RerootingStep& step) {
            result.push_back(step);
        });
        return result;
    }

    template <class Folder>
    auto fold_rerooting(int v, Folder folder) const {
        folder.start(v, _values[v], local_point(v));
        for_each_rerooting_step(v, [&](const RerootingStep& step) {
            if (step.type == step_type::CompressLower) {
                folder.compress_lower(path_down(step.sibling), step.edge);
            } else if (step.type == step_type::CompressUpper) {
                folder.compress_upper(path_up(step.sibling), reversed_edge(step.edge));
            } else if (step.type == step_type::AddEdge) {
                folder.add_edge(reversed_edge(step.edge));
            } else if (step.type == step_type::RakeLeft) {
                folder.rake_left(point(step.sibling));
            } else if (step.type == step_type::RakeRight) {
                folder.rake_right(point(step.sibling));
            } else {
                folder.add_vertex(step.vertex, _values[step.vertex]);
            }
        });
        return folder.result();
    }

    Path compress_down(const Path& upper, const Path& lower, edge_type edge) const {
        return _compress_down(upper, lower, edge);
    }

    Path compress_up(const Path& lower, const Path& upper, edge_type edge) const {
        return _compress_up(lower, upper, edge);
    }

    Point rake(const Point& left, const Point& right) const {
        return _rake(left, right);
    }

    Point add_edge_down(const Path& path, edge_type edge) const {
        return _add_edge_down(path, edge);
    }

    Point add_edge_up(const Path& path, edge_type edge) const {
        return _add_edge_up(path, edge);
    }

    Path add_vertex(const Point& side, const Vertex& value, int vertex) const {
        return _add_vertex(side, value, vertex);
    }

    static edge_type reverse_edge(edge_type edge) {
        return reversed_edge(edge);
    }
};

template <class T, class Vertex, class Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,
          class AddEdgeUp, class AddVertex>
RerootingStaticTopTree(const m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,
                       Rake, AddEdgeDown, AddEdgeUp, AddVertex, int)
    -> RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,
                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;

template <class T, class Vertex, class Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,
          class AddEdgeUp, class AddVertex>
RerootingStaticTopTree(const m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,
                       Rake, AddEdgeDown, AddEdgeUp, AddVertex)
    -> RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,
                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_REROOTING_STATIC_TOP_TREE_HPP
