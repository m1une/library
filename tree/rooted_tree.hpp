#ifndef M1UNE_TREE_ROOTED_TREE_HPP
#define M1UNE_TREE_ROOTED_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct RootedTree {
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
    std::vector<std::vector<int>> up;

   private:
    int _n;
    int _log;

    void check_vertex(int v) const {
        assert(0 <= v && v < _n);
        assert(tin[v] != -1);
    }

   public:
    RootedTree() : root(-1), _n(0), _log(0) {}
    explicit RootedTree(const m1une::graph::Graph<T>& g, int root_ = 0) {
        build(g, root_);
    }

    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {
        _n = g.size();
        root = _n == 0 ? -1 : root_;
        _log = 1;
        while ((1U << _log) <= (unsigned int)(std::max(1, _n))) _log++;

        parent.assign(_n, -1);
        parent_edge.assign(_n, -1);
        depth.assign(_n, 0);
        dist.assign(_n, T(0));
        subtree_size.assign(_n, 0);
        tin.assign(_n, -1);
        tout.assign(_n, -1);
        order.clear();
        order.reserve(_n);
        up.assign(_log, std::vector<int>(_n, -1));

        if (_n == 0) return;
        assert(0 <= root && root < _n);

        struct Frame {
            int v;
            int state;
        };

        std::vector<char> visited(_n, false);
        std::vector<Frame> stack;
        stack.push_back({root, 0});
        visited[root] = true;
        int timer = 0;

        while (!stack.empty()) {
            Frame frame = stack.back();
            stack.pop_back();
            int v = frame.v;
            if (frame.state == 0) {
                tin[v] = timer++;
                order.push_back(v);
                up[0][v] = parent[v];
                for (int k = 1; k < _log; k++) {
                    int p = up[k - 1][v];
                    up[k][v] = p == -1 ? -1 : up[k - 1][p];
                }

                stack.push_back({v, 1});
                const auto& adj = g[v];
                for (int i = int(adj.size()) - 1; i >= 0; i--) {
                    const auto& e = adj[i];
                    if (!e.alive) continue;
                    if (visited[e.to]) continue;
                    visited[e.to] = true;
                    parent[e.to] = v;
                    parent_edge[e.to] = e.id;
                    depth[e.to] = depth[v] + 1;
                    dist[e.to] = dist[v] + e.cost;
                    stack.push_back({e.to, 0});
                }
            } else {
                subtree_size[v]++;
                if (parent[v] != -1) subtree_size[parent[v]] += subtree_size[v];
                tout[v] = timer;
            }
        }
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int log() const {
        return _log;
    }

    bool is_ancestor(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    bool in_subtree(int v, int u) const {
        return is_ancestor(u, v);
    }

    int kth_ancestor(int v, int k) const {
        check_vertex(v);
        assert(0 <= k);
        int bit = 0;
        while (k > 0 && v != -1) {
            if (k & 1) {
                if (_log <= bit) return -1;
                v = up[bit][v];
            }
            k >>= 1;
            bit++;
        }
        return v;
    }

    int lca(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        if (depth[u] < depth[v]) std::swap(u, v);
        u = kth_ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int k = _log - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return parent[u];
    }

    int dist_edges(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    T dist_cost(int u, int v) const {
        int w = lca(u, v);
        return dist[u] + dist[v] - dist[w] - dist[w];
    }

    int jump(int from, int to, int k) const {
        check_vertex(from);
        check_vertex(to);
        assert(0 <= k);
        int w = lca(from, to);
        int up_len = depth[from] - depth[w];
        int down_len = depth[to] - depth[w];
        if (up_len + down_len < k) return -1;
        if (k <= up_len) return kth_ancestor(from, k);
        return kth_ancestor(to, down_len - (k - up_len));
    }

    std::vector<int> path(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        int w = lca(u, v);
        std::vector<int> a, b;
        for (int x = u; x != w; x = parent[x]) a.push_back(x);
        a.push_back(w);
        for (int x = v; x != w; x = parent[x]) b.push_back(x);
        std::reverse(b.begin(), b.end());
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }

    std::vector<int> path_edges(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        int w = lca(u, v);
        std::vector<int> a, b;
        for (int x = u; x != w; x = parent[x]) a.push_back(parent_edge[x]);
        for (int x = v; x != w; x = parent[x]) b.push_back(parent_edge[x]);
        std::reverse(b.begin(), b.end());
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }

    std::pair<int, int> subtree_range(int v) const {
        check_vertex(v);
        return {tin[v], tout[v]};
    }

    std::vector<int> subtree_vertices(int v) const {
        check_vertex(v);
        return std::vector<int>(order.begin() + tin[v], order.begin() + tout[v]);
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_ROOTED_TREE_HPP
