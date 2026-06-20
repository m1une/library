#ifndef M1UNE_GRAPH_KRUSKAL_HPP
#define M1UNE_GRAPH_KRUSKAL_HPP 1

#include <algorithm>
#include <vector>

#include "../ds/dsu/dsu.hpp"
#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct MinimumSpanningForest {
    T cost;
    std::vector<Edge<T>> edges;
    int components;

    bool is_spanning_tree(int n) const {
        return components <= 1 && int(edges.size()) == std::max(0, n - 1);
    }
};

template <class T>
MinimumSpanningForest<T> kruskal(const Graph<T>& g) {
    int n = g.size();
    auto edges = g.edges();
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return a.cost < b.cost;
    });

    m1une::ds::Dsu dsu(n);
    MinimumSpanningForest<T> result;
    result.cost = T(0);
    result.components = n;

    for (const auto& e : edges) {
        if (dsu.same(e.from, e.to)) continue;
        dsu.merge(e.from, e.to);
        result.cost += e.cost;
        result.edges.push_back(e);
        result.components--;
    }

    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_KRUSKAL_HPP
