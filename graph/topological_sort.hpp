#ifndef M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP
#define M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP 1

#include <optional>
#include <queue>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

template <class T>
std::optional<std::vector<int>> topological_sort(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> indeg(n, 0);
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            indeg[e.to]++;
        }
    }

    std::queue<int> que;
    for (int v = 0; v < n; v++) {
        if (indeg[v] == 0) que.push(v);
    }

    std::vector<int> order;
    order.reserve(n);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        order.push_back(v);
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            indeg[e.to]--;
            if (indeg[e.to] == 0) que.push(e.to);
        }
    }

    if (int(order.size()) != n) return std::nullopt;
    return order;
}

template <class T>
bool is_dag(const Graph<T>& g) {
    return topological_sort(g).has_value();
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP
