#ifndef M1UNE_TREE_CENTROID_DECOMPOSITION_HPP
#define M1UNE_TREE_CENTROID_DECOMPOSITION_HPP 1

#include <algorithm>
#include <vector>

#include "../graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct CentroidDecomposition {
    int n;
    std::vector<int> parent;
    std::vector<int> depth;
    std::vector<int> order;
    std::vector<int> roots;
    std::vector<std::vector<int>> children;

   private:
    std::vector<int> _subtree_size;
    std::vector<int> _work_parent;
    std::vector<char> _removed;

    void build_component(const m1une::graph::Graph<T>& g, int start, int p, int d) {
        std::vector<int> nodes;
        std::vector<int> stack = {start};
        _work_parent[start] = -2;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            nodes.push_back(v);
            for (const auto& e : g[v]) {
                if (!e.alive || _removed[e.to]) continue;
                if (_work_parent[e.to] != -1) continue;
                _work_parent[e.to] = v;
                stack.push_back(e.to);
            }
        }

        for (int v : nodes) _subtree_size[v] = 1;
        for (int i = int(nodes.size()) - 1; i >= 0; i--) {
            int v = nodes[i];
            if (_work_parent[v] >= 0) _subtree_size[_work_parent[v]] += _subtree_size[v];
        }

        int total = int(nodes.size());
        int centroid = start;
        int best = total + 1;
        for (int v : nodes) {
            int largest = total - _subtree_size[v];
            for (const auto& e : g[v]) {
                if (!e.alive || _removed[e.to]) continue;
                if (_work_parent[e.to] == v) largest = std::max(largest, _subtree_size[e.to]);
            }
            if (largest < best) {
                best = largest;
                centroid = v;
            }
        }

        for (int v : nodes) _work_parent[v] = -1;

        parent[centroid] = p;
        depth[centroid] = d;
        order.push_back(centroid);
        if (p == -1) {
            roots.push_back(centroid);
        } else {
            children[p].push_back(centroid);
        }
        _removed[centroid] = true;

        for (const auto& e : g[centroid]) {
            if (!e.alive || _removed[e.to]) continue;
            build_component(g, e.to, centroid, d + 1);
        }
    }

   public:
    CentroidDecomposition() : n(0) {}
    explicit CentroidDecomposition(const m1une::graph::Graph<T>& g) {
        build(g);
    }

    void build(const m1une::graph::Graph<T>& g) {
        n = g.size();
        parent.assign(n, -1);
        depth.assign(n, -1);
        order.clear();
        order.reserve(n);
        roots.clear();
        children.assign(n, {});
        _subtree_size.assign(n, 0);
        _work_parent.assign(n, -1);
        _removed.assign(n, false);

        for (int v = 0; v < n; v++) {
            if (depth[v] == -1) build_component(g, v, -1, 0);
        }
    }

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    int root() const {
        return roots.empty() ? -1 : roots[0];
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_CENTROID_DECOMPOSITION_HPP
