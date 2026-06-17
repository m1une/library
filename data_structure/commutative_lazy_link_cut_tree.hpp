#ifndef M1UNE_COMMUTATIVE_LAZY_LINK_CUT_TREE_HPP
#define M1UNE_COMMUTATIVE_LAZY_LINK_CUT_TREE_HPP 1

#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

#include "acted_monoid/concept.hpp"

namespace m1une {
namespace data_structure {

template <m1une::acted_monoid::IsCommutativeActedGroup ActedMonoid>
struct CommutativeLazyLinkCutTree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node {
        int left = -1;
        int right = -1;
        int parent = -1;
        bool rev = false;
        int size = 1;
        int virtual_size = 0;
        int rake_size = 0;
        int all_size = 1;
        T value = ActedMonoid::id();
        T prod = ActedMonoid::id();
        T rev_prod = ActedMonoid::id();
        T virtual_prod = ActedMonoid::id();
        T rake_prod = ActedMonoid::id();
        T all_prod = ActedMonoid::id();
        F lazy = ActedMonoid::op_id();
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
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    static T make_node_value(const U& value, int index) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else if constexpr (requires(U x, int i) { ActedMonoid::make(x, i); }) {
            return ActedMonoid::make(value, index);
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

    int child_rake_size(int node) const {
        return node == -1 ? 0 : _nodes[node].rake_size;
    }

    T child_prod(int node) const {
        return node == -1 ? ActedMonoid::id() : _nodes[node].prod;
    }

    T child_rev_prod(int node) const {
        return node == -1 ? ActedMonoid::id() : _nodes[node].rev_prod;
    }

    T child_all_prod(int node) const {
        return node == -1 ? ActedMonoid::id() : _nodes[node].all_prod;
    }

    T child_rake_prod(int node) const {
        return node == -1 ? ActedMonoid::id() : _nodes[node].rake_prod;
    }

    T node_subtree_prod(int node) const {
        const Node& x = _nodes[node];
        return ActedMonoid::op(x.value, x.virtual_prod);
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
        x.rake_size = x.virtual_size + child_rake_size(x.left) + child_rake_size(x.right);
        x.all_size = x.size + x.rake_size;
        x.prod = ActedMonoid::op(ActedMonoid::op(child_prod(x.left), x.value), child_prod(x.right));
        x.rev_prod = ActedMonoid::op(ActedMonoid::op(child_rev_prod(x.right), x.value), child_rev_prod(x.left));
        x.rake_prod = ActedMonoid::op(ActedMonoid::op(child_rake_prod(x.left), x.virtual_prod),
                                      child_rake_prod(x.right));
        x.all_prod = ActedMonoid::op(x.prod, x.rake_prod);
    }

    void add_virtual_child(int node, int child) {
        if (child == -1) return;
        Node& x = _nodes[node];
        x.virtual_size += _nodes[child].all_size;
        x.virtual_prod = ActedMonoid::op(x.virtual_prod, _nodes[child].all_prod);
    }

    void remove_virtual_child(int node, int child) {
        if (child == -1) return;
        Node& x = _nodes[node];
        x.virtual_size -= _nodes[child].all_size;
        x.virtual_prod = ActedMonoid::op(x.virtual_prod, ActedMonoid::inverse(_nodes[child].all_prod));
    }

    void apply_reverse(int node) {
        if (node == -1) return;
        Node& x = _nodes[node];
        std::swap(x.left, x.right);
        std::swap(x.prod, x.rev_prod);
        x.rev = !x.rev;
    }

    void apply_operator(int node, const F& f) {
        if (node == -1) return;
        Node& x = _nodes[node];
        x.value = ActedMonoid::mapping(f, x.value);
        x.prod = ActedMonoid::mapping(f, x.prod);
        x.rev_prod = ActedMonoid::mapping(f, x.rev_prod);
        x.all_prod = ActedMonoid::op(x.prod, x.rake_prod);
        x.lazy = ActedMonoid::op_comp(f, x.lazy);
    }

    void push(int node) {
        if (node == -1) return;
        Node& x = _nodes[node];
        if (x.rev) {
            apply_reverse(x.left);
            apply_reverse(x.right);
            x.rev = false;
        }
        apply_operator(x.left, x.lazy);
        apply_operator(x.right, x.lazy);
        x.lazy = ActedMonoid::op_id();
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
    CommutativeLazyLinkCutTree() = default;

    explicit CommutativeLazyLinkCutTree(int n) {
        assert(0 <= n);
        _nodes.reserve(n);
        for (int i = 0; i < n; i++) add_vertex();
    }

    explicit CommutativeLazyLinkCutTree(const std::vector<T>& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);
    }

    explicit CommutativeLazyLinkCutTree(std::vector<T>&& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit CommutativeLazyLinkCutTree(const std::vector<U>& values) {
        _nodes.reserve(values.size());
        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i], i));
    }

    int size() const {
        return int(_nodes.size());
    }

    bool empty() const {
        return _nodes.empty();
    }

    int add_vertex(const T& value = ActedMonoid::id()) {
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
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
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

    T get(int v) {
        check_vertex(v);
        access(v);
        return _nodes[v].value;
    }

    T operator[](int v) {
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
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set(int v, const U& value) {
        set(v, make_node_value(value, v));
    }

    void apply(int v, const F& f) {
        check_vertex(v);
        access(v);
        _nodes[v].value = ActedMonoid::mapping(f, _nodes[v].value);
        update(v);
    }

    void apply(int u, int v, const F& f) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        apply_operator(v, f);
    }

    void evert(int v) {
        check_vertex(v);
        access(v);
        apply_reverse(v);
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

    bool connected(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return true;
        return component_root(u) == component_root(v);
    }

    bool same(int u, int v) {
        return connected(u, v);
    }

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

    int link_edge(int u, int v, const T& value = ActedMonoid::id()) {
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
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    int link_edge(int u, int v, const U& value) {
        check_vertex(u);
        check_vertex(v);
        if (u == v || connected(u, v)) return -1;
        return link_edge(u, v, make_node_value(value, size()));
    }

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

    bool cut_edge(int edge_id) {
        check_edge(edge_id);
        EdgeInfo& edge = _edges[edge_id];
        if (!edge.alive) return false;
        bool ok1 = cut(edge.u, edge.node);
        bool ok2 = cut(edge.node, edge.v);
        if (ok1 && ok2) edge.alive = false;
        return ok1 && ok2;
    }

    T get_edge(int edge_id) {
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
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set_edge(int edge_id, const U& value) {
        set(edge_node(edge_id), make_node_value(value, edge_node(edge_id)));
    }

    void apply_edge(int edge_id, const F& f) {
        apply(edge_node(edge_id), f);
    }

    T prod(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        return _nodes[v].prod;
    }

    T path_prod(int u, int v) {
        return prod(u, v);
    }

    int path_size(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        assert(connected(u, v));
        evert(u);
        access(v);
        return _nodes[v].size;
    }

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

    T subtree_prod(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(connected(root, v));
        evert(root);
        access(v);
        return node_subtree_prod(v);
    }

    T subtree_prod(int v) {
        check_vertex(v);
        access(v);
        return node_subtree_prod(v);
    }

    int subtree_size(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(connected(root, v));
        evert(root);
        access(v);
        return node_subtree_size(v);
    }

    int subtree_size(int v) {
        check_vertex(v);
        access(v);
        return node_subtree_size(v);
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_COMMUTATIVE_LAZY_LINK_CUT_TREE_HPP
