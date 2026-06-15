#ifndef M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP
#define M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct MaximumCliqueResult {
    std::vector<int> vertices;

    int size() const {
        return int(vertices.size());
    }

    bool empty() const {
        return vertices.empty();
    }
};

struct MaximumIndependentSetResult {
    std::vector<int> vertices;

    int size() const {
        return int(vertices.size());
    }

    bool empty() const {
        return vertices.empty();
    }
};

struct MinimumVertexCoverResult {
    std::vector<int> vertices;

    int size() const {
        return int(vertices.size());
    }

    bool empty() const {
        return vertices.empty();
    }
};

namespace detail {

struct MaximumIndependentSetBranching {
    int n;
    std::vector<std::vector<char>> adjacent;
    std::vector<std::vector<int>> graph;

    explicit MaximumIndependentSetBranching(const std::vector<std::vector<char>>& adjacent_)
        : n(int(adjacent_.size())), adjacent(adjacent_), graph(n) {
        for (int v = 0; v < n; v++) {
            for (int to = 0; to < n; to++) {
                if (adjacent[v][to]) graph[v].push_back(to);
            }
        }
    }

    std::vector<int> solve_path(const std::vector<int>& order) const {
        int m = int(order.size());
        if (m == 0) return {};

        std::vector<int> dp0(m, 0), dp1(m, 0);
        dp1[0] = 1;
        for (int i = 1; i < m; i++) {
            dp0[i] = std::max(dp0[i - 1], dp1[i - 1]);
            dp1[i] = dp0[i - 1] + 1;
        }

        std::vector<int> result;
        int state = (dp1[m - 1] > dp0[m - 1] ? 1 : 0);
        for (int i = m - 1; i >= 0; i--) {
            if (state == 1) {
                result.push_back(order[i]);
                state = 0;
            } else if (i > 0) {
                state = (dp1[i - 1] > dp0[i - 1] ? 1 : 0);
            }
        }
        return result;
    }

    std::vector<int> solve_cycle(const std::vector<int>& order) const {
        int m = int(order.size());
        if (m == 0) return {};
        if (m == 1) return {order[0]};

        std::vector<int> without_first(order.begin() + 1, order.end());
        auto result_without = solve_path(without_first);

        std::vector<int> result_with = {order[0]};
        if (m >= 4) {
            std::vector<int> middle(order.begin() + 2, order.end() - 1);
            auto middle_result = solve_path(middle);
            result_with.insert(result_with.end(), middle_result.begin(), middle_result.end());
        }

        return (result_with.size() > result_without.size() ? result_with : result_without);
    }

    std::vector<int> solve_degree_at_most_two(const std::vector<char>& active,
                                              const std::vector<int>& degree) const {
        std::vector<int> result;
        std::vector<char> visited(n, false);

        for (int s = 0; s < n; s++) {
            if (!active[s] || visited[s]) continue;

            std::vector<int> component;
            std::vector<int> stack = {s};
            visited[s] = true;
            for (int it = 0; it < int(stack.size()); it++) {
                int v = stack[it];
                component.push_back(v);
                for (int to : graph[v]) {
                    if (!active[to] || visited[to]) continue;
                    visited[to] = true;
                    stack.push_back(to);
                }
            }

            if (component.size() == 1) {
                result.push_back(component[0]);
                continue;
            }

            int endpoint = -1;
            for (int v : component) {
                if (degree[v] <= 1) {
                    endpoint = v;
                    break;
                }
            }

            std::vector<int> order;
            if (endpoint != -1) {
                int prev = -1, cur = endpoint;
                while (cur != -1) {
                    order.push_back(cur);
                    int next = -1;
                    for (int to : graph[cur]) {
                        if (active[to] && to != prev) {
                            next = to;
                            break;
                        }
                    }
                    prev = cur;
                    cur = next;
                }
                auto part = solve_path(order);
                result.insert(result.end(), part.begin(), part.end());
            } else {
                int start = component[0];
                int first = -1;
                for (int to : graph[start]) {
                    if (active[to]) {
                        first = to;
                        break;
                    }
                }
                assert(first != -1);

                order.push_back(start);
                int prev = start, cur = first;
                while (cur != start) {
                    order.push_back(cur);
                    int next = -1;
                    for (int to : graph[cur]) {
                        if (active[to] && to != prev) {
                            next = to;
                            break;
                        }
                    }
                    assert(next != -1);
                    prev = cur;
                    cur = next;
                }
                auto part = solve_cycle(order);
                result.insert(result.end(), part.begin(), part.end());
            }
        }

        return result;
    }

    std::vector<int> solve(std::vector<char> active) const {
        int active_count = 0;
        int max_degree = -1;
        int branch_vertex = -1;
        std::vector<int> degree(n, 0);

        for (int v = 0; v < n; v++) {
            if (!active[v]) continue;
            active_count++;
            for (int to : graph[v]) {
                if (active[to]) degree[v]++;
            }
            if (degree[v] > max_degree) {
                max_degree = degree[v];
                branch_vertex = v;
            }
        }

        if (active_count == 0) return {};
        if (max_degree <= 2) {
            auto result = solve_degree_at_most_two(active, degree);
            std::sort(result.begin(), result.end());
            return result;
        }

        auto without = active;
        without[branch_vertex] = false;
        auto result_without = solve(without);

        auto with = active;
        with[branch_vertex] = false;
        for (int to : graph[branch_vertex]) with[to] = false;
        auto result_with = solve(with);
        result_with.push_back(branch_vertex);

        auto result = (result_with.size() > result_without.size() ? result_with : result_without);
        std::sort(result.begin(), result.end());
        return result;
    }

    std::vector<int> solve() const {
        std::vector<char> active(n, true);
        return solve(active);
    }
};

template <class T>
std::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>& g) {
    int n = g.size();
    std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));
    for (const auto& e : g.edges()) {
        if (e.from == e.to) continue;
        adjacent[e.from][e.to] = true;
        adjacent[e.to][e.from] = true;
    }
    return adjacent;
}

std::vector<std::vector<char>> complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent) {
    int n = int(adjacent.size());
    std::vector<std::vector<char>> complement(n, std::vector<char>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjacent[i][j]) continue;
            complement[i][j] = true;
            complement[j][i] = true;
        }
    }
    return complement;
}

}  // namespace detail

template <class T>
bool is_clique(const Graph<T>& g, const std::vector<int>& vertices) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    for (int v : vertices) {
        assert(0 <= v && v < g.size());
    }
    for (int i = 0; i < int(vertices.size()); i++) {
        for (int j = i + 1; j < int(vertices.size()); j++) {
            if (!adjacent[vertices[i]][vertices[j]]) return false;
        }
    }
    return true;
}

template <class T>
bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    for (int v : vertices) {
        assert(0 <= v && v < g.size());
    }
    for (int i = 0; i < int(vertices.size()); i++) {
        for (int j = i + 1; j < int(vertices.size()); j++) {
            if (adjacent[vertices[i]][vertices[j]]) return false;
        }
    }
    return true;
}

template <class T>
bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {
    std::vector<char> selected(g.size(), false);
    for (int v : vertices) {
        assert(0 <= v && v < g.size());
        selected[v] = true;
    }
    for (const auto& e : g.edges()) {
        if (e.from == e.to) continue;
        if (!selected[e.from] && !selected[e.to]) return false;
    }
    return true;
}

template <class T>
MaximumCliqueResult maximum_clique(const Graph<T>& g) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    auto complement = detail::complement_adjacency_matrix(adjacent);
    detail::MaximumIndependentSetBranching solver(complement);
    return MaximumCliqueResult{solver.solve()};
}

template <class T>
int maximum_clique_size(const Graph<T>& g) {
    return maximum_clique(g).size();
}

template <class T>
MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    detail::MaximumIndependentSetBranching solver(adjacent);
    return MaximumIndependentSetResult{solver.solve()};
}

template <class T>
int maximum_independent_set_size(const Graph<T>& g) {
    return maximum_independent_set(g).size();
}

template <class T>
MinimumVertexCoverResult minimum_vertex_cover(const Graph<T>& g) {
    auto independent = maximum_independent_set(g);
    std::vector<char> in_independent(g.size(), false);
    for (int v : independent.vertices) in_independent[v] = true;

    MinimumVertexCoverResult result;
    for (int v = 0; v < g.size(); v++) {
        if (!in_independent[v]) result.vertices.push_back(v);
    }
    return result;
}

template <class T>
int minimum_vertex_cover_size(const Graph<T>& g) {
    return minimum_vertex_cover(g).size();
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP
