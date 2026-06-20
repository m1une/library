#ifndef M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP
#define M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP 1

#include <cassert>
#include <utility>
#include <variant>
#include <vector>

namespace m1une {
namespace ds {

// Maintains a dynamic forest whose tree DP uses two different aggregate types.
// Point is a commutative group for virtual children, while Path is an ordered
// preferred-path cluster and does not need an inverse.
template <class TreeDPInfo>
struct RakeCompressLinkCutTree {
    using Point = typename TreeDPInfo::Point;
    using Path = typename TreeDPInfo::Path;
    using VertexValue = typename TreeDPInfo::VertexValue;
    using EdgeValue = typename TreeDPInfo::EdgeValue;
    using VertexId = int;
    using EdgeId = int;

   private:
    struct Node {
        int left = -1;
        int right = -1;
        int parent = -1;
        bool rev = false;
        std::variant<VertexValue, EdgeValue> value;
        Point virtual_prod;
        Path prod;
        Path rev_prod;

        explicit Node(const VertexValue& vertex_value)
            : value(std::in_place_index<0>, vertex_value),
              virtual_prod(Point::id()),
              prod(TreeDPInfo::make_vertex_path(virtual_prod, vertex_value)),
              rev_prod(prod) {}

        explicit Node(std::in_place_index_t<1>, const EdgeValue& edge_value)
            : value(std::in_place_index<1>, edge_value),
              virtual_prod(Point::id()),
              prod(TreeDPInfo::make_edge_path(virtual_prod, edge_value)),
              rev_prod(prod) {}
    };

    struct OriginalEdge {
        VertexId u = -1;
        VertexId v = -1;
        int node = -1;
        bool alive = false;
    };

    std::vector<Node> _nodes;
    std::vector<int> _vertex_nodes;
    std::vector<OriginalEdge> _edges;
    std::vector<int> _path_buffer;

    bool is_splay_root(int node) const {
        int parent = _nodes[node].parent;
        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);
    }

    void update(int node) {
        Node& x = _nodes[node];
        Path self = x.value.index() == 0
            ? TreeDPInfo::make_vertex_path(x.virtual_prod, std::get<0>(x.value))
            : TreeDPInfo::make_edge_path(x.virtual_prod, std::get<1>(x.value));
        x.prod = self;
        x.rev_prod = self;

        if (x.left != -1) {
            x.prod = TreeDPInfo::compress(_nodes[x.left].prod, x.prod);
            x.rev_prod = TreeDPInfo::compress(x.rev_prod, _nodes[x.left].rev_prod);
        }
        if (x.right != -1) {
            x.prod = TreeDPInfo::compress(x.prod, _nodes[x.right].prod);
            x.rev_prod = TreeDPInfo::compress(_nodes[x.right].rev_prod, x.rev_prod);
        }
    }

    void add_virtual_child(int node, int child) {
        if (child == -1) return;
        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);
        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod, contribution);
    }

    void remove_virtual_child(int node, int child) {
        if (child == -1) return;
        Point contribution = TreeDPInfo::to_point(_nodes[child].prod);
        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod, contribution.inv());
    }

    void apply_reverse(int node) {
        if (node == -1) return;
        Node& x = _nodes[node];
        std::swap(x.left, x.right);
        std::swap(x.prod, x.rev_prod);
        x.rev = !x.rev;
    }

    void push(int node) {
        if (node == -1 || !_nodes[node].rev) return;
        apply_reverse(_nodes[node].left);
        apply_reverse(_nodes[node].right);
        _nodes[node].rev = false;
    }

    void push_to(int node) {
        _path_buffer.clear();
        int cur = node;
        _path_buffer.push_back(cur);
        while (!is_splay_root(cur)) {
            cur = _nodes[cur].parent;
            _path_buffer.push_back(cur);
        }
        for (int i = int(_path_buffer.size()) - 1; i >= 0; i--) push(_path_buffer[i]);
    }

    void rotate(int node) {
        int parent = _nodes[node].parent;
        int grand = _nodes[parent].parent;
        bool is_right = _nodes[parent].right == node;
        int middle = is_right ? _nodes[node].left : _nodes[node].right;

        if (!is_splay_root(parent)) {
            if (_nodes[grand].left == parent) {
                _nodes[grand].left = node;
            } else {
                _nodes[grand].right = node;
            }
        }
        _nodes[node].parent = grand;

        if (is_right) {
            _nodes[node].left = parent;
            _nodes[parent].right = middle;
        } else {
            _nodes[node].right = parent;
            _nodes[parent].left = middle;
        }
        if (middle != -1) _nodes[middle].parent = parent;
        _nodes[parent].parent = node;

        update(parent);
        update(node);
    }

    void splay(int node) {
        push_to(node);
        while (!is_splay_root(node)) {
            int parent = _nodes[node].parent;
            int grand = _nodes[parent].parent;
            if (!is_splay_root(parent)) {
                bool zig_zig = (_nodes[parent].left == node) == (_nodes[grand].left == parent);
                rotate(zig_zig ? parent : node);
            }
            rotate(node);
        }
    }

    int access(int node) {
        int last = -1;
        for (int cur = node; cur != -1; cur = _nodes[cur].parent) {
            splay(cur);
            add_virtual_child(cur, _nodes[cur].right);
            remove_virtual_child(cur, last);
            _nodes[cur].right = last;
            if (last != -1) _nodes[last].parent = cur;
            update(cur);
            last = cur;
        }
        splay(node);
        return last;
    }

    void check_node(int node) const {
        assert(0 <= node && node < int(_nodes.size()));
    }

    void check_vertex(VertexId vertex) const {
        assert(0 <= vertex && vertex < int(_vertex_nodes.size()));
    }

    void check_edge(EdgeId edge_id) const {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
    }

    int vertex_node(VertexId vertex) const {
        check_vertex(vertex);
        return _vertex_nodes[vertex];
    }

    int add_edge_node(const EdgeValue& edge_value) {
        _nodes.emplace_back(std::in_place_index<1>, edge_value);
        return int(_nodes.size()) - 1;
    }

    void set_vertex_node_value(int node, const VertexValue& vertex_value) {
        check_node(node);
        access(node);
        _nodes[node].value.template emplace<0>(vertex_value);
        update(node);
    }

    void set_edge_node_value(int node, const EdgeValue& edge_value) {
        check_node(node);
        access(node);
        _nodes[node].value.template emplace<1>(edge_value);
        update(node);
    }

    void evert_node(int node) {
        check_node(node);
        access(node);
        apply_reverse(node);
    }

    int component_root_node(int node) {
        check_node(node);
        access(node);
        int cur = node;
        push(cur);
        while (_nodes[cur].left != -1) {
            cur = _nodes[cur].left;
            push(cur);
        }
        splay(cur);
        return cur;
    }

    bool connected_nodes(int u, int v) {
        if (u == v) return true;
        return component_root_node(u) == component_root_node(v);
    }

    bool link_nodes(int u, int v) {
        check_node(u);
        check_node(v);
        if (u == v) return false;
        evert_node(u);
        if (component_root_node(v) == u) return false;
        access(v);
        _nodes[u].parent = v;
        add_virtual_child(v, u);
        update(v);
        return true;
    }

    bool cut_nodes(int u, int v) {
        check_node(u);
        check_node(v);
        if (u == v) return false;
        evert_node(u);
        access(v);
        if (_nodes[v].left != u || _nodes[u].right != -1) return false;
        _nodes[v].left = -1;
        _nodes[u].parent = -1;
        update(v);
        return true;
    }

   public:
    RakeCompressLinkCutTree() = default;

    explicit RakeCompressLinkCutTree(const std::vector<VertexValue>& values) {
        _nodes.reserve(values.size());
        _vertex_nodes.reserve(values.size());
        for (const VertexValue& value : values) add_vertex(value);
    }

    int vertex_count() const {
        return int(_vertex_nodes.size());
    }

    bool empty() const {
        return _vertex_nodes.empty();
    }

    VertexId add_vertex(const VertexValue& vertex_value) {
        VertexValue value = vertex_value;
        int node = int(_nodes.size());
        _nodes.emplace_back(value);
        _vertex_nodes.push_back(node);
        return int(_vertex_nodes.size()) - 1;
    }

    const VertexValue& get_vertex(VertexId vertex) const {
        return std::get<0>(_nodes[vertex_node(vertex)].value);
    }

    void set_vertex(VertexId vertex, const VertexValue& vertex_value) {
        set_vertex_node_value(vertex_node(vertex), vertex_value);
    }

    int edge_count() const {
        return int(_edges.size());
    }

    bool edge_alive(EdgeId edge_id) const {
        check_edge(edge_id);
        return _edges[edge_id].alive;
    }

    std::pair<VertexId, VertexId> edge_endpoints(EdgeId edge_id) const {
        check_edge(edge_id);
        return {_edges[edge_id].u, _edges[edge_id].v};
    }

    const EdgeValue& get_edge(EdgeId edge_id) const {
        check_edge(edge_id);
        return std::get<1>(_nodes[_edges[edge_id].node].value);
    }

    void set_edge(EdgeId edge_id, const EdgeValue& edge_value) {
        check_edge(edge_id);
        set_edge_node_value(_edges[edge_id].node, edge_value);
    }

    EdgeId add_edge(VertexId u, VertexId v, const EdgeValue& edge_value) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        EdgeValue value = edge_value;
        int edge_id = int(_edges.size());
        int node = add_edge_node(value);
        _edges.push_back(OriginalEdge{u, v, node, true});
        bool ok1 = link_nodes(vertex_node(u), node);
        bool ok2 = link_nodes(node, vertex_node(v));
        assert(ok1 && ok2);
        return edge_id;
    }

    bool cut_edge(EdgeId edge_id) {
        check_edge(edge_id);
        OriginalEdge& edge = _edges[edge_id];
        if (!edge.alive) return false;
        bool ok1 = cut_nodes(vertex_node(edge.u), edge.node);
        bool ok2 = cut_nodes(edge.node, vertex_node(edge.v));
        if (ok1 && ok2) edge.alive = false;
        return ok1 && ok2;
    }

    void reroot(VertexId vertex) {
        evert_node(vertex_node(vertex));
    }

    bool connected(VertexId u, VertexId v) {
        check_vertex(u);
        check_vertex(v);
        return connected_nodes(vertex_node(u), vertex_node(v));
    }

    // Reroots the represented tree at vertex and returns its whole-tree cluster.
    Path component_prod(VertexId vertex) {
        int node = vertex_node(vertex);
        evert_node(node);
        return _nodes[node].prod;
    }

    Path query_component(VertexId vertex) {
        return component_prod(vertex);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP
