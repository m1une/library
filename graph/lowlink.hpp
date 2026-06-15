#ifndef M1UNE_GRAPH_LOWLINK_HPP
#define M1UNE_GRAPH_LOWLINK_HPP 1

#include <algorithm>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct LowLinkResult {
    std::vector<int> ord;
    std::vector<int> low;
    std::vector<int> articulation;
    std::vector<Edge<T>> bridges;
    std::vector<int> bridge_ids;
};

template <class T>
LowLinkResult<T> lowlink(const Graph<T>& g) {
    int n = g.size();
    LowLinkResult<T> result;
    result.ord.assign(n, -1);
    result.low.assign(n, -1);
    int now = 0;

    auto dfs = [&](auto self, int v, int parent_edge) -> void {
        result.ord[v] = result.low[v] = now++;
        int child_count = 0;
        bool is_articulation = false;

        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (e.id == parent_edge) continue;
            int to = e.to;
            if (result.ord[to] == -1) {
                child_count++;
                self(self, to, e.id);
                result.low[v] = std::min(result.low[v], result.low[to]);
                if (parent_edge != -1 && result.ord[v] <= result.low[to]) is_articulation = true;
                if (result.ord[v] < result.low[to]) {
                    result.bridges.push_back(e);
                    result.bridge_ids.push_back(e.id);
                }
            } else {
                result.low[v] = std::min(result.low[v], result.ord[to]);
            }
        }

        if (parent_edge == -1 && child_count >= 2) is_articulation = true;
        if (is_articulation) result.articulation.push_back(v);
    };

    for (int v = 0; v < n; v++) {
        if (result.ord[v] == -1) dfs(dfs, v, -1);
    }
    std::sort(result.articulation.begin(), result.articulation.end());
    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_LOWLINK_HPP
