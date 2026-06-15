#ifndef M1UNE_GRAPH_SCC_HPP
#define M1UNE_GRAPH_SCC_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct SccResult {
    int count;
    std::vector<int> comp;
    std::vector<std::vector<int>> groups;

    bool same(int u, int v) const {
        assert(0 <= u && u < int(comp.size()));
        assert(0 <= v && v < int(comp.size()));
        return comp[u] == comp[v];
    }

    template <class T>
    Graph<int> dag(const Graph<T>& g) const {
        std::vector<std::pair<int, int>> edges;
        for (int v = 0; v < g.size(); v++) {
            for (const auto& e : g[v]) {
                int a = comp[e.from], b = comp[e.to];
                if (a != b) edges.emplace_back(a, b);
            }
        }
        std::sort(edges.begin(), edges.end());
        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());

        Graph<int> result(count);
        for (auto [a, b] : edges) result.add_directed_edge(a, b);
        return result;
    }
};

template <class T>
SccResult strongly_connected_components(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> ord(n, -1), low(n, 0), comp(n, -1), stack;
    std::vector<char> in_stack(n, false);
    std::vector<std::vector<int>> groups;
    int now = 0;

    auto dfs = [&](auto self, int v) -> void {
        ord[v] = low[v] = now++;
        stack.push_back(v);
        in_stack[v] = true;

        for (const auto& e : g[v]) {
            int to = e.to;
            if (ord[to] == -1) {
                self(self, to);
                low[v] = std::min(low[v], low[to]);
            } else if (in_stack[to]) {
                low[v] = std::min(low[v], ord[to]);
            }
        }

        if (low[v] != ord[v]) return;
        std::vector<int> group;
        while (true) {
            int u = stack.back();
            stack.pop_back();
            in_stack[u] = false;
            group.push_back(u);
            if (u == v) break;
        }
        groups.push_back(std::move(group));
    };

    for (int v = 0; v < n; v++) {
        if (ord[v] == -1) dfs(dfs, v);
    }

    std::reverse(groups.begin(), groups.end());
    for (int i = 0; i < int(groups.size()); i++) {
        for (int v : groups[i]) comp[v] = i;
    }

    return SccResult{int(groups.size()), std::move(comp), std::move(groups)};
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_SCC_HPP
