#ifndef M1UNE_GRAPH_DAG_SHORTEST_PATH_HPP
#define M1UNE_GRAPH_DAG_SHORTEST_PATH_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <optional>
#include <vector>

#include "graph.hpp"
#include "topological_sort.hpp"

namespace m1une {
namespace graph {

template <class T>
struct DagShortestPathResult {
    std::vector<T> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> topological_order;
    T inf;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != inf;
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

template <class T>
std::optional<DagShortestPathResult<T>> dag_shortest_path(
    const Graph<T>& g, const std::vector<int>& sources, T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = g.size();
    auto order = topological_sort(g);
    if (!order) return std::nullopt;

    DagShortestPathResult<T> result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.topological_order = *order;
    result.inf = inf;

    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.dist[s] == T(0)) continue;
        result.dist[s] = T(0);
    }

    for (int v : *order) {
        if (result.dist[v] == inf) continue;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            T nd = result.dist[v] + e.cost;
            if (result.dist[e.to] <= nd) continue;
            result.dist[e.to] = nd;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
        }
    }

    return result;
}

template <class T>
std::optional<DagShortestPathResult<T>> dag_shortest_path(
    const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {
    return dag_shortest_path(g, std::vector<int>{s}, inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DAG_SHORTEST_PATH_HPP
