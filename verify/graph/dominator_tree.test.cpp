#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include "../../graph/dominator_tree.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../graph/graph.hpp"

namespace {

std::vector<int> brute_idom(
    const m1une::graph::Graph<>& graph,
    int root
) {
    int n = graph.size();
    std::vector<char> reachable(n, false);
    std::vector<int> stack = {root};
    reachable[root] = true;
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        for (const auto& edge : graph[current]) {
            if (!edge.alive || reachable[edge.to]) continue;
            reachable[edge.to] = true;
            stack.push_back(edge.to);
        }
    }

    std::vector<std::vector<char>> dominator(
        n,
        std::vector<char>(n, false)
    );
    for (int vertex = 0; vertex < n; ++vertex) {
        if (!reachable[vertex]) continue;
        if (vertex == root) {
            dominator[vertex][root] = true;
        } else {
            for (int candidate = 0; candidate < n; ++candidate) {
                dominator[vertex][candidate] = reachable[candidate];
            }
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int vertex = 0; vertex < n; ++vertex) {
            if (!reachable[vertex] || vertex == root) continue;
            std::vector<char> next(n, true);
            bool has_predecessor = false;
            for (int from = 0; from < n; ++from) {
                for (const auto& edge : graph[from]) {
                    if (
                        edge.alive &&
                        edge.to == vertex &&
                        reachable[from]
                    ) {
                        if (!has_predecessor) {
                            next = dominator[from];
                            has_predecessor = true;
                        } else {
                            for (int candidate = 0; candidate < n; ++candidate) {
                                next[candidate] =
                                    next[candidate]
                                    && dominator[from][candidate];
                            }
                        }
                    }
                }
            }
            next[vertex] = true;
            if (next != dominator[vertex]) {
                dominator[vertex] = std::move(next);
                changed = true;
            }
        }
    }

    std::vector<int> result(n, -1);
    result[root] = root;
    for (int vertex = 0; vertex < n; ++vertex) {
        if (!reachable[vertex] || vertex == root) continue;
        for (int candidate = 0; candidate < n; ++candidate) {
            if (
                candidate == vertex ||
                !dominator[vertex][candidate]
            ) {
                continue;
            }
            bool immediate = true;
            for (int other = 0; other < n; ++other) {
                if (
                    other == vertex ||
                    other == candidate ||
                    !dominator[vertex][other]
                ) {
                    continue;
                }
                if (dominator[other][candidate]) {
                    immediate = false;
                    break;
                }
            }
            if (immediate) {
                result[vertex] = candidate;
                break;
            }
        }
    }
    return result;
}

void test_randomized() {
    std::uint64_t state = 1601;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        int n = 1 + int(random() % 12);
        m1une::graph::Graph<> graph(n);
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < n; ++to) {
                if (random() % 5 == 0) {
                    graph.add_directed_edge(from, to);
                }
            }
        }
        int root = int(random() % n);
        auto actual = m1une::graph::dominator_tree(graph, root);
        auto expected = brute_idom(graph, root);
        assert(actual.immediate_dominator == expected);

        for (int vertex = 0; vertex < n; ++vertex) {
            assert(actual.reachable(vertex) == (expected[vertex] != -1));
            for (int ancestor = 0; ancestor < n; ++ancestor) {
                [[maybe_unused]] bool dominates = false;
                if (expected[vertex] != -1) {
                    for (
                        int current = vertex;
                        current != -1;
                        current = current == root
                            ? -1
                            : expected[current]
                    ) {
                        if (current == ancestor) dominates = true;
                    }
                }
                assert(actual.dominates(ancestor, vertex) == dominates);
            }
        }
    }
}

void test_long_path() {
    constexpr int n = 200000;
    m1une::graph::Graph<> graph(n);
    for (int vertex = 1; vertex < n; ++vertex) {
        graph.add_directed_edge(vertex - 1, vertex);
    }
    auto result = m1une::graph::dominator_tree(graph, 0);
    assert(result.immediate_dominator[n - 1] == n - 2);
    assert(result.dominates(0, n - 1));
}

}  // namespace

int main() {
    test_randomized();
    test_long_path();

    int n, m, root;
    std::cin >> n >> m >> root;
    m1une::graph::Graph<> graph(n);
    while (m--) {
        int from, to;
        std::cin >> from >> to;
        graph.add_directed_edge(from, to);
    }
    auto result = m1une::graph::dominator_tree(graph, root);
    for (int vertex = 0; vertex < n; ++vertex) {
        if (vertex) std::cout << ' ';
        std::cout << result.immediate_dominator[vertex];
    }
    std::cout << '\n';
}
