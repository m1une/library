#ifndef M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP
#define M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP 1

#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

// Maintains a dynamic forest whose tree DP uses two different aggregate types.
// Point is a commutative group for virtual children, while Path is an ordered
// preferred-path cluster and does not need an inverse.
template <class TreeDPInfo>
struct RakeCompressLinkCutTree {
    using Point = typename TreeDPInfo::Point;
    using Path = typename TreeDPInfo::Path;
    using Vertex = typename TreeDPInfo::Vertex;

   private:
    struct Node {
        int left = -1;
        int right = -1;
        int parent = -1;
        bool rev = false;
        Vertex value;
        Point virtual_prod;
        Path prod;
        Path rev_prod;

        explicit Node(const Vertex& vertex)
            : value(vertex),
              virtual_prod(Point::id()),
              prod(TreeDPInfo::add_vertex(virtual_prod, value)),
              rev_prod(prod) {}
    };

    struct EdgeInfo {
        int u = -1;
        int v = -1;
        int node = -1;
        bool alive = false;
    };

    std::vector<Node> _nodes;
    std::vector<EdgeInfo> _edges;
    std::vector<int> _path_buffer;

    bool is_splay_root(int node) const {
        int parent = _nodes[node].parent;
        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);
    }

    void update(int node) {
        Node& x = _nodes[node];
        Path self = TreeDPInfo::add_vertex(x.virtual_prod, x.value);
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
        Point contribution = TreeDPInfo::add_edge(_nodes[child].prod);
        _nodes[node].virtual_prod = TreeDPInfo::rake(_nodes[node].virtual_prod, contribution);
    }

    void remove_virtual_child(int node, int child) {
        if (child == -1) return;
        Point contribution = TreeDPInfo::add_edge(_nodes[child].prod);
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

    void check_vertex(int v) const {
        assert(0 <= v && v < int(_nodes.size()));
    }

    void check_edge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
    }

   public:
    RakeCompressLinkCutTree() = default;

    explicit RakeCompressLinkCutTree(const std::vector<Vertex>& values) {
        _nodes.reserve(values.size());
        for (const Vertex& value : values) add_vertex(value);
    }

    int size() const {
        return int(_nodes.size());
    }

    bool empty() const {
        return _nodes.empty();
    }

    int add_vertex(const Vertex& vertex) {
        _nodes.emplace_back(vertex);
        return int(_nodes.size()) - 1;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    bool edge_alive(int edge_id) const {
        check_edge(edge_id);
        return _edges[edge_id].alive;
    }

    int edge_node(int edge_id) const {
        check_edge(edge_id);
        return _edges[edge_id].node;
    }

    std::pair<int, int> edge_endpoints(int edge_id) const {
        check_edge(edge_id);
        return {_edges[edge_id].u, _edges[edge_id].v};
    }

    const Vertex& get(int v) const {
        check_vertex(v);
        return _nodes[v].value;
    }

    const Vertex& operator[](int v) const {
        return get(v);
    }

    void set(int v, const Vertex& vertex) {
        check_vertex(v);
        access(v);
        _nodes[v].value = vertex;
        update(v);
    }

    // Makes v the represented root of its component.
    void evert(int v) {
        check_vertex(v);
        access(v);
        apply_reverse(v);
    }

    void reroot(int v) {
        evert(v);
    }

    int component_root(int v) {
        check_vertex(v);
        access(v);
        int cur = v;
        push(cur);
        while (_nodes[cur].left != -1) {
            cur = _nodes[cur].left;
            push(cur);
        }
        splay(cur);
        return cur;
    }

    int root(int v) {
        return component_root(v);
    }

    bool connected(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return true;
        return component_root(u) == component_root(v);
    }

    bool same(int u, int v) {
        return connected(u, v);
    }

    // Links two different components and returns whether an edge was added.
    bool link(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return false;
        evert(u);
        if (component_root(v) == u) return false;
        access(v);
        _nodes[u].parent = v;
        add_virtual_child(v, u);
        update(v);
        return true;
    }

    bool link_parent(int child, int parent) {
        return link(child, parent);
    }

    int link_edge(int u, int v, const Vertex& edge_vertex) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        int edge_id = int(_edges.size());
        int node = add_vertex(edge_vertex);
        _edges.push_back(EdgeInfo{u, v, node, true});
        bool ok1 = link(u, node);
        bool ok2 = link(node, v);
        assert(ok1 && ok2);
        return edge_id;
    }

    // Cuts the represented-tree edge (u, v), if it exists.
    bool cut(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return false;
        evert(u);
        access(v);
        if (_nodes[v].left != u || _nodes[u].right != -1) return false;
        _nodes[v].left = -1;
        _nodes[u].parent = -1;
        update(v);
        return true;
    }

    // Cuts the parent edge of v in the current represented-root orientation.
    bool cut_parent(int v) {
        check_vertex(v);
        access(v);
        int left = _nodes[v].left;
        if (left == -1) return false;
        _nodes[v].left = -1;
        _nodes[left].parent = -1;
        update(v);
        return true;
    }

    bool cut_edge(int edge_id) {
        check_edge(edge_id);
        EdgeInfo& edge = _edges[edge_id];
        if (!edge.alive) return false;
        bool ok1 = cut(edge.u, edge.node);
        bool ok2 = cut(edge.node, edge.v);
        if (ok1 && ok2) edge.alive = false;
        return ok1 && ok2;
    }

    const Vertex& get_edge(int edge_id) const {
        return get(edge_node(edge_id));
    }

    void set_edge(int edge_id, const Vertex& edge_vertex) {
        set(edge_node(edge_id), edge_vertex);
    }

    // Reroots the represented tree at v and returns its whole-tree cluster.
    Path component_prod(int v) {
        evert(v);
        return _nodes[v].prod;
    }

    Path query_component(int v) {
        return component_prod(v);
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_RAKE_COMPRESS_LINK_CUT_TREE_HPP
