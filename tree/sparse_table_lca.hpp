#ifndef M1UNE_TREE_SPARSE_TABLE_LCA_HPP
#define M1UNE_TREE_SPARSE_TABLE_LCA_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "ds/range_query/sparse_table.hpp"
#include "graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct SparseTableLca {
    using cost_type = T;
    using edge_type = m1une::graph::Edge<T>;

    int root;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> depth;
    std::vector<T> dist;
    std::vector<int> subtree_size;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> order;
    std::vector<int> first;
    std::vector<int> euler;

   private:
    struct RmqNode {
        int depth;
        int vertex;
    };

    struct RmqMonoid {
        using value_type = RmqNode;

        static value_type id() {
            return {std::numeric_limits<int>::max(), -1};
        }

        static value_type op(const value_type& a, const value_type& b) {
            if (a.depth != b.depth) return a.depth < b.depth ? a : b;
            return a.vertex < b.vertex ? a : b;
        }
    };

    int _n;
    m1une::ds::SparseTable<RmqMonoid> _st;

    void check_vertex(int v) const {
        assert(0 <= v && v < _n);
        assert(first[v] != -1);
    }

   public:
    SparseTableLca() : root(-1), _n(0) {}
    explicit SparseTableLca(const m1une::graph::Graph<T>& g, int root_ = 0) {
        build(g, root_);
    }

    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {
        _n = g.size();
        root = _n == 0 ? -1 : root_;
        parent.assign(_n, -2);
        parent_edge.assign(_n, -1);
        depth.assign(_n, 0);
        dist.assign(_n, T(0));
        subtree_size.assign(_n, 0);
        tin.assign(_n, -1);
        tout.assign(_n, -1);
        order.clear();
        order.reserve(_n);
        first.assign(_n, -1);
        euler.clear();
        euler.reserve(std::max(0, 2 * _n - 1));
        _st = m1une::ds::SparseTable<RmqMonoid>();

        if (_n == 0) return;
        assert(0 <= root && root < _n);

        std::vector<int> it(_n, 0);
        std::vector<char> visited(_n, false);
        std::vector<int> stack = {root};
        visited[root] = true;
        parent[root] = -1;

        int timer = 0;
        tin[root] = timer++;
        order.push_back(root);
        first[root] = 0;
        euler.push_back(root);

        while (!stack.empty()) {
            int v = stack.back();
            if (it[v] < int(g[v].size())) {
                const auto& e = g[v][it[v]++];
                if (!e.alive) continue;
                if (visited[e.to]) continue;
                visited[e.to] = true;
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                depth[e.to] = depth[v] + 1;
                dist[e.to] = dist[v] + e.cost;
                tin[e.to] = timer++;
                order.push_back(e.to);
                first[e.to] = int(euler.size());
                euler.push_back(e.to);
                stack.push_back(e.to);
            } else {
                subtree_size[v]++;
                if (parent[v] != -1) subtree_size[parent[v]] += subtree_size[v];
                tout[v] = timer;
                stack.pop_back();
                if (!stack.empty()) euler.push_back(stack.back());
            }
        }

        std::vector<RmqNode> rmq;
        rmq.reserve(euler.size());
        for (int v : euler) rmq.push_back({depth[v], v});
        _st = m1une::ds::SparseTable<RmqMonoid>(std::move(rmq));
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    bool is_ancestor(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    bool in_subtree(int v, int u) const {
        return is_ancestor(u, v);
    }

    int lca(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        int l = first[u], r = first[v];
        if (l > r) std::swap(l, r);
        return _st.prod(l, r + 1).vertex;
    }

    int dist_edges(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    T dist_cost(int u, int v) const {
        int w = lca(u, v);
        return dist[u] + dist[v] - dist[w] - dist[w];
    }

    std::pair<int, int> subtree_range(int v) const {
        check_vertex(v);
        return {tin[v], tout[v]};
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_SPARSE_TABLE_LCA_HPP
