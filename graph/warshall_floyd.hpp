#ifndef M1UNE_GRAPH_WARSHALL_FLOYD_HPP
#define M1UNE_GRAPH_WARSHALL_FLOYD_HPP 1

#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
std::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>> dist,
                                           T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = int(dist.size());
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == inf) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == inf) continue;
                T nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j]) dist[i][j] = nd;
            }
        }
    }
    return dist;
}

template <class T>
std::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = g.size();
    std::vector<std::vector<T>> dist(n, std::vector<T>(n, inf));
    for (int i = 0; i < n; i++) dist[i][i] = T(0);
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (e.cost < dist[e.from][e.to]) dist[e.from][e.to] = e.cost;
        }
    }
    return warshall_floyd(std::move(dist), inf);
}

template <class T>
bool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>& dist, int from, int to, T cost,
                                      T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = int(dist.size());
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);

    std::vector<T> to_from(n), from_to(n);
    for (int i = 0; i < n; i++) {
        to_from[i] = dist[i][from];
        from_to[i] = dist[to][i];
    }

    bool updated = false;
    for (int i = 0; i < n; i++) {
        if (to_from[i] == inf) continue;
        for (int j = 0; j < n; j++) {
            if (from_to[j] == inf) continue;
            T nd = to_from[i] + cost + from_to[j];
            if (nd < dist[i][j]) {
                dist[i][j] = nd;
                updated = true;
            }
        }
    }
    return updated;
}

template <class T>
bool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>& dist, int u, int v, T cost,
                                        T inf = std::numeric_limits<T>::max() / T(4)) {
    int n = int(dist.size());
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);

    std::vector<T> to_u(n), from_u(n), to_v(n), from_v(n);
    for (int i = 0; i < n; i++) {
        to_u[i] = dist[i][u];
        from_u[i] = dist[u][i];
        to_v[i] = dist[i][v];
        from_v[i] = dist[v][i];
    }

    bool updated = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (to_u[i] != inf && from_v[j] != inf) {
                T nd = to_u[i] + cost + from_v[j];
                if (nd < dist[i][j]) {
                    dist[i][j] = nd;
                    updated = true;
                }
            }
            if (to_v[i] != inf && from_u[j] != inf) {
                T nd = to_v[i] + cost + from_u[j];
                if (nd < dist[i][j]) {
                    dist[i][j] = nd;
                    updated = true;
                }
            }
        }
    }
    return updated;
}

template <class T>
bool has_negative_cycle(const std::vector<std::vector<T>>& dist) {
    int n = int(dist.size());
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < T(0)) return true;
    }
    return false;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_WARSHALL_FLOYD_HPP
