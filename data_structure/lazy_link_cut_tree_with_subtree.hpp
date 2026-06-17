#ifndef M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP
#define M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP 1

#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

#include "data_structure/lazy_link_cut_tree.hpp"

namespace m1une {
namespace data_structure {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct LazyLinkCutTreeWithSubtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct ForestEdge {
        int u = -1;
        int v = -1;
        bool alive = false;
    };

    LazyLinkCutTree<ActedMonoid> _lct;
    std::vector<ForestEdge> _forest_edges;
    std::vector<std::vector<int>> _adj;

    void ensure_forest_size() {
        if (int(_adj.size()) < _lct.size()) _adj.resize(_lct.size());
    }

    void add_forest_edge(int u, int v) {
        ensure_forest_size();
        int edge_id = int(_forest_edges.size());
        _forest_edges.push_back(ForestEdge{u, v, true});
        _adj[u].push_back(edge_id);
        _adj[v].push_back(edge_id);
    }

    bool remove_forest_edge(int u, int v) {
        for (int edge_id : _adj[u]) {
            ForestEdge& edge = _forest_edges[edge_id];
            if (!edge.alive) continue;
            if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
                edge.alive = false;
                return true;
            }
        }
        return false;
    }

    int other_endpoint(int edge_id, int v) const {
        const ForestEdge& edge = _forest_edges[edge_id];
        return edge.u == v ? edge.v : edge.u;
    }

    void check_vertex(int v) const {
        assert(0 <= v && v < _lct.size());
    }

    int parent_in_rooted_tree(int root, int v) {
        check_vertex(root);
        check_vertex(v);
        assert(_lct.connected(root, v));
        if (root == v) return -1;

        std::vector<int> parent(_lct.size(), -1);
        std::vector<int> stack;
        parent[root] = root;
        stack.push_back(root);

        for (int it = 0; it < int(stack.size()); it++) {
            int x = stack[it];
            for (int edge_id : _adj[x]) {
                const ForestEdge& edge = _forest_edges[edge_id];
                if (!edge.alive) continue;
                int to = other_endpoint(edge_id, x);
                if (parent[to] != -1) continue;
                parent[to] = x;
                if (to == v) return x;
                stack.push_back(to);
            }
        }

        assert(false);
        return -1;
    }

   public:
    LazyLinkCutTreeWithSubtree() = default;

    explicit LazyLinkCutTreeWithSubtree(int n) : _lct(n), _adj(n) {
        assert(0 <= n);
    }

    explicit LazyLinkCutTreeWithSubtree(const std::vector<T>& values) : _lct(values), _adj(values.size()) {}

    explicit LazyLinkCutTreeWithSubtree(std::vector<T>&& values) : _lct(std::move(values)) {
        _adj.resize(_lct.size());
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit LazyLinkCutTreeWithSubtree(const std::vector<U>& values) : _lct(values), _adj(values.size()) {}

    int size() const {
        return _lct.size();
    }

    bool empty() const {
        return _lct.empty();
    }

    int add_vertex(const T& value = ActedMonoid::id()) {
        int v = _lct.add_vertex(value);
        ensure_forest_size();
        return v;
    }

    int add_vertex(T&& value) {
        int v = _lct.add_vertex(std::move(value));
        ensure_forest_size();
        return v;
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    int add_vertex(const U& value) {
        int v = _lct.add_vertex(value);
        ensure_forest_size();
        return v;
    }

    int edge_count() const {
        return _lct.edge_count();
    }

    bool edge_alive(int edge_id) const {
        return _lct.edge_alive(edge_id);
    }

    int edge_node(int edge_id) const {
        return _lct.edge_node(edge_id);
    }

    std::pair<int, int> edge_endpoints(int edge_id) const {
        return _lct.edge_endpoints(edge_id);
    }

    T get(int v) {
        return _lct.get(v);
    }

    T operator[](int v) {
        return get(v);
    }

    void set(int v, const T& value) {
        _lct.set(v, value);
    }

    void set(int v, T&& value) {
        _lct.set(v, std::move(value));
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set(int v, const U& value) {
        _lct.set(v, value);
    }

    void apply(int v, const F& f) {
        _lct.apply(v, f);
    }

    void apply(int u, int v, const F& f) {
        _lct.apply(u, v, f);
    }

    void evert(int v) {
        _lct.evert(v);
    }

    int component_root(int v) {
        return _lct.component_root(v);
    }

    bool connected(int u, int v) {
        return _lct.connected(u, v);
    }

    bool same(int u, int v) {
        return connected(u, v);
    }

    bool link(int u, int v) {
        bool ok = _lct.link(u, v);
        if (ok) add_forest_edge(u, v);
        return ok;
    }

    int link_edge(int u, int v, const T& value = ActedMonoid::id()) {
        int edge_id = _lct.link_edge(u, v, value);
        if (edge_id == -1) return -1;
        int node = _lct.edge_node(edge_id);
        ensure_forest_size();
        add_forest_edge(u, node);
        add_forest_edge(node, v);
        return edge_id;
    }

    int link_edge(int u, int v, T&& value) {
        int edge_id = _lct.link_edge(u, v, std::move(value));
        if (edge_id == -1) return -1;
        int node = _lct.edge_node(edge_id);
        ensure_forest_size();
        add_forest_edge(u, node);
        add_forest_edge(node, v);
        return edge_id;
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    int link_edge(int u, int v, const U& value) {
        int edge_id = _lct.link_edge(u, v, value);
        if (edge_id == -1) return -1;
        int node = _lct.edge_node(edge_id);
        ensure_forest_size();
        add_forest_edge(u, node);
        add_forest_edge(node, v);
        return edge_id;
    }

    bool cut(int u, int v) {
        bool ok = _lct.cut(u, v);
        if (ok) remove_forest_edge(u, v);
        return ok;
    }

    bool cut_edge(int edge_id) {
        int node = _lct.edge_node(edge_id);
        auto [u, v] = _lct.edge_endpoints(edge_id);
        bool ok = _lct.cut_edge(edge_id);
        if (ok) {
            remove_forest_edge(u, node);
            remove_forest_edge(node, v);
        }
        return ok;
    }

    T get_edge(int edge_id) {
        return _lct.get_edge(edge_id);
    }

    void set_edge(int edge_id, const T& value) {
        _lct.set_edge(edge_id, value);
    }

    void set_edge(int edge_id, T&& value) {
        _lct.set_edge(edge_id, std::move(value));
    }

    template <class U>
    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    void set_edge(int edge_id, const U& value) {
        _lct.set_edge(edge_id, value);
    }

    void apply_edge(int edge_id, const F& f) {
        _lct.apply_edge(edge_id, f);
    }

    T prod(int u, int v) {
        return _lct.prod(u, v);
    }

    T path_prod(int u, int v) {
        return prod(u, v);
    }

    int path_size(int u, int v) {
        return _lct.path_size(u, v);
    }

    int kth_vertex(int u, int v, int k) {
        return _lct.kth_vertex(u, v, k);
    }

    int lca(int u, int v) {
        return _lct.lca(u, v);
    }

    std::vector<int> subtree_vertices(int root, int v) {
        int blocked_parent = parent_in_rooted_tree(root, v);
        std::vector<int> res;
        std::vector<std::pair<int, int>> stack;
        stack.emplace_back(v, blocked_parent);

        while (!stack.empty()) {
            auto [x, parent] = stack.back();
            stack.pop_back();
            res.push_back(x);

            const std::vector<int>& edges = _adj[x];
            for (int i = int(edges.size()) - 1; i >= 0; i--) {
                int edge_id = edges[i];
                const ForestEdge& edge = _forest_edges[edge_id];
                if (!edge.alive) continue;
                int to = other_endpoint(edge_id, x);
                if (to == parent) continue;
                stack.emplace_back(to, x);
            }
        }

        return res;
    }

    std::vector<int> subtree_vertices(int v) {
        return subtree_vertices(component_root(v), v);
    }

    int subtree_size(int root, int v) {
        return int(subtree_vertices(root, v).size());
    }

    int subtree_size(int v) {
        return int(subtree_vertices(v).size());
    }

    T subtree_prod(int root, int v) {
        T res = ActedMonoid::id();
        for (int x : subtree_vertices(root, v)) {
            res = ActedMonoid::op(res, _lct.get(x));
        }
        return res;
    }

    T subtree_prod(int v) {
        return subtree_prod(component_root(v), v);
    }

    void apply_subtree(int root, int v, const F& f) {
        std::vector<int> vertices = subtree_vertices(root, v);
        for (int x : vertices) _lct.apply(x, f);
    }

    void apply_subtree(int v, const F& f) {
        apply_subtree(component_root(v), v, f);
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_LAZY_LINK_CUT_TREE_WITH_SUBTREE_HPP
