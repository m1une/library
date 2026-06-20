#ifndef M1UNE_TREE_DIAMETER_HPP
#define M1UNE_TREE_DIAMETER_HPP 1

#include <algorithm>
#include <vector>

#include "../graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct TreeDiameter {
    T cost;
    int edge_count;
    int from;
    int to;
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    bool empty() const {
        return vertices.empty();
    }
};

namespace internal {

template <class T>
struct FarthestResult {
    int vertex;
    std::vector<char> seen;
    std::vector<T> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
};

template <class T>
FarthestResult<T> farthest_from(const m1une::graph::Graph<T>& g, int start) {
    int n = g.size();
    FarthestResult<T> result;
    result.vertex = start;
    result.seen.assign(n, false);
    result.dist.assign(n, T(0));
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);

    std::vector<int> stack = {start};
    result.seen[start] = true;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (result.dist[result.vertex] < result.dist[v]) result.vertex = v;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (result.seen[e.to]) continue;
            result.seen[e.to] = true;
            result.dist[e.to] = result.dist[v] + e.cost;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            stack.push_back(e.to);
        }
    }
    return result;
}

}  // namespace internal

template <class T>
TreeDiameter<T> tree_diameter(const m1une::graph::Graph<T>& g) {
    int n = g.size();
    TreeDiameter<T> best;
    best.cost = T(0);
    best.edge_count = 0;
    best.from = -1;
    best.to = -1;
    if (n == 0) return best;

    std::vector<char> done(n, false);
    for (int start = 0; start < n; start++) {
        if (done[start]) continue;
        auto first = internal::farthest_from(g, start);
        for (int v = 0; v < n; v++) {
            if (first.seen[v]) done[v] = true;
        }
        auto second = internal::farthest_from(g, first.vertex);
        int a = first.vertex;
        int b = second.vertex;
        T cost = second.dist[b];
        if (best.from != -1 && !(best.cost < cost)) continue;

        best.cost = cost;
        best.from = a;
        best.to = b;
        best.vertices.clear();
        best.edge_ids.clear();
        for (int v = b; v != -1; v = second.parent[v]) {
            best.vertices.push_back(v);
            if (v != a) best.edge_ids.push_back(second.parent_edge[v]);
        }
        std::reverse(best.vertices.begin(), best.vertices.end());
        std::reverse(best.edge_ids.begin(), best.edge_ids.end());
        best.edge_count = int(best.edge_ids.size());
    }

    return best;
}

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_DIAMETER_HPP
