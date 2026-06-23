#ifndef M1UNE_GRAPH_NAMORI_HPP
#define M1UNE_GRAPH_NAMORI_HPP 1

#include <cassert>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct NamoriDecomposition {
    int component_count;
    std::vector<std::vector<int>> cycles;
    std::vector<std::vector<int>> cycle_edge_ids;
    std::vector<std::vector<T>> cycle_edge_costs;

    std::vector<bool> on_cycle;
    std::vector<int> component;
    std::vector<int> cycle_root;
    std::vector<int> cycle_position;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> depth;
    std::vector<T> dist_to_cycle;
    std::vector<std::vector<int>> children;

    bool same_component(int u, int v) const {
        assert(0 <= u && u < int(component.size()));
        assert(0 <= v && v < int(component.size()));
        return component[u] == component[v];
    }

    bool same_tree(int u, int v) const {
        assert(0 <= u && u < int(cycle_root.size()));
        assert(0 <= v && v < int(cycle_root.size()));
        return cycle_root[u] == cycle_root[v];
    }
};

template <class T>
std::optional<NamoriDecomposition<T>> namori_decomposition(const Graph<T>& graph) {
    int n = graph.size();
    NamoriDecomposition<T> result;
    result.component_count = 0;
    result.on_cycle.assign(n, false);
    result.component.assign(n, -1);
    result.cycle_root.assign(n, -1);
    result.cycle_position.assign(n, -1);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.depth.assign(n, 0);
    result.dist_to_cycle.assign(n, T(0));
    result.children.assign(n, {});
    if (n == 0) return result;

    std::vector<int> degree(n, 0);
    for (int v = 0; v < n; v++) {
        for (const auto& edge : graph[v]) {
            if (edge.alive) degree[v]++;
        }
    }

    std::queue<int> queue;
    std::vector<bool> removed(n, false);
    for (int v = 0; v < n; v++) {
        if (degree[v] <= 1) queue.push(v);
    }
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        if (removed[v] || degree[v] > 1) continue;
        removed[v] = true;
        for (const auto& edge : graph[v]) {
            if (!edge.alive || removed[edge.to]) continue;
            degree[edge.to]--;
            if (degree[edge.to] == 1) queue.push(edge.to);
        }
    }

    for (int v = 0; v < n; v++) {
        result.on_cycle[v] = !removed[v];
    }
    for (int v = 0; v < n; v++) {
        if (!result.on_cycle[v]) continue;
        int cycle_degree = 0;
        for (const auto& edge : graph[v]) {
            if (edge.alive && result.on_cycle[edge.to]) cycle_degree++;
        }
        if (cycle_degree != 2) return std::nullopt;
    }

    std::vector<bool> cycle_visited(n, false);
    for (int start = 0; start < n; start++) {
        if (!result.on_cycle[start] || cycle_visited[start]) continue;
        int component_id = int(result.cycles.size());
        std::vector<int> vertices;
        std::vector<int> edge_ids;
        std::vector<T> edge_costs;

        int current = start;
        int previous_edge = -1;
        while (true) {
            if (cycle_visited[current]) return std::nullopt;
            cycle_visited[current] = true;
            vertices.push_back(current);

            int next_vertex = -1;
            int next_edge = -1;
            T next_cost = T(0);
            for (const auto& edge : graph[current]) {
                if (!edge.alive || !result.on_cycle[edge.to] || edge.id == previous_edge) continue;
                next_vertex = edge.to;
                next_edge = edge.id;
                next_cost = edge.cost;
                break;
            }
            if (next_edge == -1) return std::nullopt;
            edge_ids.push_back(next_edge);
            edge_costs.push_back(next_cost);
            if (next_vertex == start) break;
            previous_edge = next_edge;
            current = next_vertex;
            if (int(vertices.size()) > n) return std::nullopt;
        }

        for (int position = 0; position < int(vertices.size()); position++) {
            int v = vertices[position];
            result.component[v] = component_id;
            result.cycle_root[v] = v;
            result.cycle_position[v] = position;
        }
        result.cycles.push_back(std::move(vertices));
        result.cycle_edge_ids.push_back(std::move(edge_ids));
        result.cycle_edge_costs.push_back(std::move(edge_costs));
    }
    if (result.cycles.empty()) return std::nullopt;

    std::vector<int> stack;
    stack.reserve(n);
    for (const auto& cycle : result.cycles) {
        for (int v : cycle) stack.push_back(v);
    }
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        for (const auto& edge : graph[v]) {
            if (!edge.alive || result.on_cycle[edge.to] || edge.id == result.parent_edge[v]) continue;
            int to = edge.to;
            if (result.component[to] != -1) continue;
            result.component[to] = result.component[v];
            result.cycle_root[to] = result.cycle_root[v];
            result.cycle_position[to] = result.cycle_position[v];
            result.parent[to] = v;
            result.parent_edge[to] = edge.id;
            result.depth[to] = result.depth[v] + 1;
            result.dist_to_cycle[to] = result.dist_to_cycle[v] + edge.cost;
            result.children[v].push_back(to);
            stack.push_back(to);
        }
    }
    for (int v = 0; v < n; v++) {
        if (result.component[v] == -1) return std::nullopt;
    }

    result.component_count = int(result.cycles.size());
    return result;
}

template <class T>
std::optional<NamoriDecomposition<T>> decompose_namori(const Graph<T>& graph) {
    return namori_decomposition(graph);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_NAMORI_HPP
