#ifndef M1UNE_GRAPH_DIJKSTRA_HPP
#define M1UNE_GRAPH_DIJKSTRA_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct DijkstraResult {
    std::vector<T> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
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
DijkstraResult<T> dijkstra(const Graph<T>& g, const std::vector<int>& sources,
                           T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = g.size();
    DijkstraResult<T> result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.inf = inf;

    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.dist[s] == T(0)) continue;
        result.dist[s] = T(0);
        que.emplace(T(0), s);
    }

    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (result.dist[v] != d) continue;
        for (const auto& e : g[v]) {
            T nd = d + e.cost;
            if (result.dist[e.to] <= nd) continue;
            result.dist[e.to] = nd;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            que.emplace(nd, e.to);
        }
    }

    return result;
}

template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {
    return dijkstra(g, std::vector<int>{s}, inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DIJKSTRA_HPP
