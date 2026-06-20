#ifndef M1UNE_LINK_CUT_TREE_HPP
#define M1UNE_LINK_CUT_TREE_HPP 1

#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsCommutativeGroup Group>
struct LinkCutTree {
    using T = typename Group::value_type;

   private:
    struct Node {
        int left = -1;
        int right = -1;
        int parent = -1;
        bool rev = false;
        int size = 1;
        int virtual_size = 0;
        int all_size = 1;
        T value = Group::id();
        T prod = Group::id();
        T rev_prod = Group::id();
        T virtual_prod = Group::id();
        T all_prod = Group::id();
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

    static T make_node_value(const T& value, int) {
        return value;
    }

    static T make_node_value(T&& value, int) {
        return std::move(value);
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    static T make_node_value(const U& value, int index) {
        if constexpr (requires(U x) { Group::make(x); }) {
            return Group::make(value);
        } else if constexpr (requires(U x, int i) { Group::make(x, i); }) {
            return Group::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    int child_size(int node) const {
        return node == -1 ? 0 : _nodes[node].size;
    }

    int child_all_size(int node) const {
        return node == -1 ? 0 : _nodes[node].all_size;
    }

    T child_prod(int node) const {
        return node == -1 ? Group::id() : _nodes[node].prod;
    }

    T child_rev_prod(int node) const {
        return node == -1 ? Group::id() : _nodes[node].rev_prod;
    }

    T child_all_prod(int node) const {
        return node == -1 ? Group::id() : _nodes[node].all_prod;
    }

    T node_subtree_prod(int node) const {
        const Node& x = _nodes[node];
        return Group::op(x.value, x.virtual_prod);
    }

    int node_subtree_size(int node) const {
        return 1 + _nodes[node].virtual_size;
    }

    bool is_splay_root(int node) const {
        int parent = _nodes[node].parent;
        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);
    }

    void update(int node) {
        Node& x = _nodes[node];
        x.size = 1 + child_size(x.left) + child_size(x.right);
        x.all_size = 1 + x.virtual_size + child_all_size(x.left) + child_all_size(x.right);
        x.prod = Group::op(Group::op(child_prod(x.left), x.value), child_prod(x.right));
        x.rev_prod = Group::op(Group::op(child_rev_prod(x.right), x.value), child_rev_prod(x.left));
        x.all_prod = Group::op(Group::op(child_all_prod(x.left), x.value),
                                Group::op(x.virtual_prod, child_all_prod(x.right)));
    }

    void add_virtual_child(int node, int child) {
        if (child == -1) return;
        Node& x = _nodes[node];
        x.virtual_size += _nodes[child].all_size;
        x.virtual_prod = Group::op(x.virtual_prod, _nodes[child].all_prod);
    }

    void remove_virtual_child(int node, int child) {
        if (child == -1) return;
        Node& x = _nodes[node];
        x.virtual_size -= _nodes[child].all_size;
        x.virtual_prod = Group::op(x.virtual_prod, Group::inv(_nodes[child].all_prod));
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
    LinkCutTree() = default;

    explicit LinkCutTree(int n) {
        assert(0 <= n);
        _nodes.reserve(n);
        for (int i = 0; i < n; i++) add_vertex();
    }

    explicit LinkCutTree(const std::vector<T>& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);
    }

    explicit LinkCutTree(std::vector<T>&& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit LinkCutTree(const std::vector<U>& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i], i));
    }

    int size() const {
        return int(_nodes.size());
    }

    bool empty() const {
        return _nodes.empty();
    }

    int add_vertex(const T& value = Group::id()) {
        Node node;
        node.value = value;
        node.prod = value;
        node.rev_prod = value;
        node.all_prod = value;
        _nodes.push_back(std::move(node));
        return int(_nodes.size()) - 1;
    }

    int add_vertex(T&& value) {
        Node node;
        node.value = std::move(value);
        node.prod = node.value;
        node.rev_prod = node.value;
        node.all_prod = node.value;
        _nodes.push_back(std::move(node));
        return int(_nodes.size()) - 1;
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    int add_vertex(const U& value) {
        return add_vertex(make_node_value(value, size()));
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

    const T& get(int v) const {
        check_vertex(v);
        return _nodes[v].value;
    }

    const T& operator[](int v) const {
        return get(v);
    }

    void set(int v, const T& value) {
        check_vertex(v);
        access(v);
        _nodes[v].value = value;
        update(v);
    }

    void set(int v, T&& value) {
        check_vertex(v);
        access(v);
        _nodes[v].value = std::move(value);
        update(v);
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set(int v, const U& value) {
        set(v, make_node_value(value, v));
    }

    // Makes `v` the represented root of its component.
    void evert(int v) {
        check_vertex(v);
        access(v);
        apply_reverse(v);
    }

    // Alias for `evert(v)`; changes the represented root to `v`.
    void reroot(int v) {
        evert(v);
    }

    // Returns the current represented root of `v`'s component.
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

    // Alias for `component_root(v)`.
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

    // Links two components. Internally calls `evert(u)`, so the represented root may change.
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

    // Links `child` under `parent`. This is the same operation as `link(child, parent)`;
    // it internally calls `evert(child)`, so that side's represented root may change.
    bool link_parent(int child, int parent) {
        return link(child, parent);
    }

    int link_edge(int u, int v, const T& value = Group::id()) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        int edge_id = int(_edges.size());
        int node = add_vertex(value);
        _edges.push_back(EdgeInfo{u, v, node, true});
        bool ok1 = link(u, node);
        bool ok2 = link(node, v);
        assert(ok1 && ok2);
        return edge_id;
    }

    int link_edge(int u, int v, T&& value) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        int edge_id = int(_edges.size());
        int node = add_vertex(std::move(value));
        _edges.push_back(EdgeInfo{u, v, node, true});
        bool ok1 = link(u, node);
        bool ok2 = link(node, v);
        assert(ok1 && ok2);
        return edge_id;
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    int link_edge(int u, int v, const U& value) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        return link_edge(u, v, make_node_value(value, size()));
    }

    // Cuts edge `(u, v)`. Internally calls `evert(u)`, so the represented root may change.
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

    // Cuts the parent edge of `v` in the current represented-root orientation.
    // Unlike `cut(u, v)`, this does not call `evert`.
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

    const T& get_edge(int edge_id) const {
        return get(edge_node(edge_id));
    }

    void set_edge(int edge_id, const T& value) {
        set(edge_node(edge_id), value);
    }

    void set_edge(int edge_id, T&& value) {
        set(edge_node(edge_id), std::move(value));
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { Group::make(x); } ||
        requires(U x, int i) { Group::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set_edge(int edge_id, const U& value) {
        set(edge_node(edge_id), make_node_value(value, edge_node(edge_id)));
    }

    // Returns the path product from `u` to `v`. Internally calls `evert(u)`,
    // so the represented root may change.
    T prod(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        return _nodes[v].prod;
    }

    // Alias for `prod(u, v)`. Internally calls `evert(u)`,
    // so the represented root may change.
    T path_prod(int u, int v) {
        return prod(u, v);
    }

    // Returns the number of vertices on path `u`-`v`. Internally calls `evert(u)`,
    // so the represented root may change.
    int path_size(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        return _nodes[v].size;
    }

    // Returns the `k`-th vertex on path `u`-`v`. Internally calls `evert(u)`,
    // so the represented root may change.
    int kth_vertex(int u, int v, int k) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        assert(0 <= k && k < _nodes[v].size);

        int cur = v;
        while (true) {
            push(cur);
            int left_size = child_size(_nodes[cur].left);
            if (k < left_size) {
                cur = _nodes[cur].left;
            } else if (k == left_size) {
                splay(cur);
                return cur;
            } else {
                k -= left_size + 1;
                cur = _nodes[cur].right;
            }
        }
    }

    int lca(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (!connected(u, v)) return -1;
        if (u == v) return u;
        access(u);
        return access(v);
    }

    // Returns the aggregate of `v`'s subtree when the represented tree is rooted at `root`.
    // Internally calls `evert(root)`, so the represented root may change.
    T subtree_prod(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(connected(root, v));
        evert(root);
        access(v);
        return node_subtree_prod(v);
    }

    // Returns the aggregate of `v`'s subtree with respect to the current represented root.
    T subtree_prod(int v) {
        check_vertex(v);
        access(v);
        return node_subtree_prod(v);
    }

    // Returns the size of `v`'s subtree when the represented tree is rooted at `root`.
    // Internally calls `evert(root)`, so the represented root may change.
    int subtree_size(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(connected(root, v));
        evert(root);
        access(v);
        return node_subtree_size(v);
    }

    // Returns the size of `v`'s subtree with respect to the current represented root.
    int subtree_size(int v) {
        check_vertex(v);
        access(v);
        return node_subtree_size(v);
    }

    // Returns the aggregate of the whole connected component containing `v`.
    T component_prod(int v) {
        int r = root(v);
        return subtree_prod(r, r);
    }

    // Returns the number of vertices in the connected component containing `v`.
    int component_size(int v) {
        int r = root(v);
        return subtree_size(r, r);
    }

    // Returns the child of `root` that lies on path `root`-`v`.
    int child_toward(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(root != v);
        assert(connected(root, v));
        return kth_vertex(root, v, 1);
    }

    // Returns the aggregate of the entire branch of `root` that contains `v`.
    T branch_prod(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(root != v);
        int child = child_toward(root, v);
        return subtree_prod(root, child);
    }

    // Returns the size of the entire branch of `root` that contains `v`.
    int branch_size(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(root != v);
        int child = child_toward(root, v);
        return subtree_size(root, child);
    }

    // Returns the parent of `v` when rooted at `root`, or `-1` if `v == root`.
    int parent(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        if (root == v) return -1;
        assert(connected(root, v));
        int d = path_size(root, v);
        assert(2 <= d);
        return kth_vertex(root, v, d - 2);
    }

    // Returns `v`'s rooted subtree aggregate excluding the child-side subtree.
    T subtree_prod_excluding_child(int root, int v, int child) {
        check_vertex(root);
        check_vertex(v);
        check_vertex(child);
        assert(parent(root, child) == v);
        T whole = subtree_prod(root, v);
        T sub = subtree_prod(root, child);
        return Group::op(whole, Group::inv(sub));
    }

    // Returns `v`'s rooted subtree size excluding the child-side subtree.
    int subtree_size_excluding_child(int root, int v, int child) {
        check_vertex(root);
        check_vertex(v);
        check_vertex(child);
        assert(parent(root, child) == v);
        return subtree_size(root, v) - subtree_size(root, child);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_LINK_CUT_TREE_HPP
