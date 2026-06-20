#ifndef M1UNE_GRAPH_BELLMAN_FORD_HPP
#define M1UNE_GRAPH_BELLMAN_FORD_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct BellmanFordResult {
    std::vector<T> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<bool> negative;
    T inf;
    bool has_negative_cycle;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != inf;
    }

    bool affected_by_negative_cycle(int v) const {
        assert(0 <= v && v < int(negative.size()));
        return negative[v];
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        assert(!affected_by_negative_cycle(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

template <class T>
BellmanFordResult<T> bellman_ford(const Graph<T>& g, const std::vector<int>& sources,
                                  T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = g.size();
    BellmanFordResult<T> result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.negative.assign(n, false);
    result.inf = inf;
    result.has_negative_cycle = false;

    for (int s : sources) {
        assert(0 <= s && s < n);
        result.dist[s] = T(0);
    }

    std::vector<int> relaxed_vertices;
    for (int iter = 0; iter < n; iter++) {
        bool updated = false;
        for (int v = 0; v < n; v++) {
            if (result.dist[v] == inf) continue;
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                T nd = result.dist[v] + e.cost;
                if (result.dist[e.to] <= nd) continue;
                result.dist[e.to] = nd;
                result.parent[e.to] = v;
                result.parent_edge[e.to] = e.id;
                updated = true;
                if (iter == n - 1) relaxed_vertices.push_back(e.to);
            }
        }
        if (!updated) break;
    }

    std::queue<int> que;
    for (int v : relaxed_vertices) {
        if (result.negative[v]) continue;
        result.negative[v] = true;
        que.push(v);
    }
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (result.negative[e.to]) continue;
            result.negative[e.to] = true;
            que.push(e.to);
        }
    }

    for (bool x : result.negative) result.has_negative_cycle = result.has_negative_cycle || x;
    return result;
}

template <class T>
BellmanFordResult<T> bellman_ford(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {
    return bellman_ford(g, std::vector<int>{s}, inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BELLMAN_FORD_HPP
