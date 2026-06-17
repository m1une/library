#ifndef M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP
#define M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace tree {

struct HldPathSegment {
    int l;
    int r;
    bool reversed;
};

template <class T = int>
struct HeavyLightDecomposition {
    using cost_type = T;
    using edge_type = m1une::graph::Edge<T>;

    int root;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> depth;
    std::vector<T> dist;
    std::vector<int> subtree_size;
    std::vector<int> heavy;
    std::vector<int> head;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> order;

   private:
    int _n;

    void check_vertex(int v) const {
        assert(0 <= v && v < _n);
        assert(tin[v] != -1);
    }

    static void add_segment(std::vector<HldPathSegment>& result, int l, int r, bool reversed) {
        if (l < r) result.push_back({l, r, reversed});
    }

   public:
    HeavyLightDecomposition() : root(-1), _n(0) {}
    explicit HeavyLightDecomposition(const m1une::graph::Graph<T>& g, int root_ = 0) {
        build(g, root_);
    }

    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {
        _n = g.size();
        root = _n == 0 ? -1 : root_;
        parent.assign(_n, -2);
        parent_edge.assign(_n, -1);
        depth.assign(_n, 0);
        dist.assign(_n, T(0));
        subtree_size.assign(_n, 1);
        heavy.assign(_n, -1);
        head.assign(_n, -1);
        tin.assign(_n, -1);
        tout.assign(_n, -1);
        order.clear();
        order.reserve(_n);
        if (_n == 0) return;
        assert(0 <= root && root < _n);

        std::vector<int> dfs_order;
        dfs_order.reserve(_n);
        std::vector<int> stack = {root};
        parent[root] = -1;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            dfs_order.push_back(v);
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                if (parent[e.to] != -2) continue;
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                depth[e.to] = depth[v] + 1;
                dist[e.to] = dist[v] + e.cost;
                stack.push_back(e.to);
            }
        }

        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {
            int v = dfs_order[i];
            if (parent[v] == -1) continue;
            int p = parent[v];
            subtree_size[p] += subtree_size[v];
            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p] = v;
        }

        order.assign(dfs_order.size(), -1);
        int timer = 0;
        std::vector<std::pair<int, int>> starts = {std::pair<int, int>{root, root}};
        while (!starts.empty()) {
            auto [start, h] = starts.back();
            starts.pop_back();
            for (int v = start; v != -1; v = heavy[v]) {
                head[v] = h;
                tin[v] = timer;
                order[timer++] = v;
                for (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {
                    if (!it->alive) continue;
                    int to = it->to;
                    if (parent[to] != v || to == heavy[v]) continue;
                    starts.push_back({to, to});
                }
            }
        }
        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {
            int v = dfs_order[i];
            tout[v] = tin[v] + subtree_size[v];
        }
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

    int lca(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) std::swap(u, v);
            u = parent[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    int dist_edges(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    T dist_cost(int u, int v) const {
        int w = lca(u, v);
        return dist[u] + dist[v] - dist[w] - dist[w];
    }

    int kth_ancestor(int v, int k) const {
        check_vertex(v);
        assert(0 <= k);
        while (v != -1) {
            int h = head[v];
            int len = depth[v] - depth[h];
            if (k <= len) return order[tin[v] - k];
            k -= len + 1;
            v = parent[h];
        }
        return -1;
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

    std::pair<int, int> subtree_range(int v, bool edge = false) const {
        check_vertex(v);
        return {tin[v] + (edge ? 1 : 0), tout[v]};
    }

    std::vector<HldPathSegment> path_segments(int u, int v, bool edge = false) const {
        check_vertex(u);
        check_vertex(v);
        std::vector<HldPathSegment> result, down;
        while (head[u] != head[v]) {
            if (depth[head[u]] >= depth[head[v]]) {
                add_segment(result, tin[head[u]], tin[u] + 1, true);
                u = parent[head[u]];
            } else {
                add_segment(down, tin[head[v]], tin[v] + 1, false);
                v = parent[head[v]];
            }
        }

        if (depth[u] >= depth[v]) {
            add_segment(result, tin[v] + (edge ? 1 : 0), tin[u] + 1, true);
        } else {
            add_segment(down, tin[u] + (edge ? 1 : 0), tin[v] + 1, false);
        }
        std::reverse(down.begin(), down.end());
        result.insert(result.end(), down.begin(), down.end());
        return result;
    }

    template <class F>
    void for_each_path(int u, int v, F f, bool edge = false) const {
        for (auto seg : path_segments(u, v, edge)) f(seg.l, seg.r, seg.reversed);
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP
