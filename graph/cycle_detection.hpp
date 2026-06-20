#ifndef M1UNE_GRAPH_CYCLE_DETECTION_HPP
#define M1UNE_GRAPH_CYCLE_DETECTION_HPP 1

#include <algorithm>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct Cycle {
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    bool empty() const {
        return vertices.empty();
    }
};

inline Cycle restore_cycle(int from, int to, int closing_edge, const std::vector<int>& parent,
                           const std::vector<int>& parent_edge) {
    Cycle result;
    result.vertices.push_back(to);

    std::vector<int> middle_vertices;
    std::vector<int> middle_edges;
    for (int v = from; v != to; v = parent[v]) {
        middle_vertices.push_back(v);
        middle_edges.push_back(parent_edge[v]);
    }
    std::reverse(middle_vertices.begin(), middle_vertices.end());
    std::reverse(middle_edges.begin(), middle_edges.end());

    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());
    result.vertices.push_back(to);
    result.edge_ids.insert(result.edge_ids.end(), middle_edges.begin(), middle_edges.end());
    result.edge_ids.push_back(closing_edge);
    return result;
}

template <class T>
Cycle find_directed_cycle(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);
    Cycle result;

    auto dfs = [&](auto self, int v) -> bool {
        color[v] = 1;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (color[e.to] == 0) {
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                if (self(self, e.to)) return true;
            } else if (color[e.to] == 1) {
                result = restore_cycle(v, e.to, e.id, parent, parent_edge);
                return true;
            }
        }
        color[v] = 2;
        return false;
    };

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(dfs, v)) break;
    }
    return result;
}

template <class T>
Cycle find_undirected_cycle(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);
    Cycle result;

    auto dfs = [&](auto self, int v, int pe) -> bool {
        color[v] = 1;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (e.id == pe) continue;
            if (color[e.to] == 0) {
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                if (self(self, e.to, e.id)) return true;
            } else if (color[e.to] == 1) {
                result = restore_cycle(v, e.to, e.id, parent, parent_edge);
                return true;
            }
        }
        color[v] = 2;
        return false;
    };

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(dfs, v, -1)) break;
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_CYCLE_DETECTION_HPP
