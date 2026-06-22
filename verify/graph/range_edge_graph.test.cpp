#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../graph/all.hpp"

using RangeEdgeGraph = m1une::graph::RangeEdgeGraph<long long>;

void test_basic() {
    RangeEdgeGraph range_graph(6);
    assert(range_graph.size() == 6);
    for (int i = 0; i < 6; i++) assert(range_graph.point_vertex(i) == i);

    range_graph.add_point_to_point(0, 1, 4);
    range_graph.add_point_to_range(1, 2, 5, 3);
    range_graph.add_range_to_point(2, 4, 5, 2);
    int auxiliary = range_graph.add_range_to_range(0, 2, 4, 6, 7);
    assert(auxiliary >= 6);

    auto result = m1une::graph::dijkstra(range_graph.graph(), 0);
    std::vector<long long> expected = {0, 4, 7, 7, 7, 7};
    for (int i = 0; i < 6; i++) assert(result.dist[i] == expected[i]);
}

void test_empty_ranges() {
    RangeEdgeGraph range_graph(3);
    int vertices = range_graph.graph().size();
    int edges = range_graph.graph().edge_count();
    range_graph.add_point_to_range(0, 1, 1, 5);
    range_graph.add_range_to_point(2, 2, 1, 5);
    assert(range_graph.add_range_to_range(0, 0, 0, 3, 5) == -1);
    assert(range_graph.add_range_to_range(0, 3, 2, 2, 5) == -1);
    assert(range_graph.graph().size() == vertices);
    assert(range_graph.graph().edge_count() == edges);

    RangeEdgeGraph empty(0);
    assert(empty.size() == 0);
    assert(empty.graph().size() == 0);
    assert(empty.from_range_nodes(0, 0).empty());
    assert(empty.to_range_nodes(0, 0).empty());
}

void test_cover_nodes() {
    RangeEdgeGraph range_graph(9);
    auto from_nodes = range_graph.from_range_nodes(2, 8);
    auto to_nodes = range_graph.to_range_nodes(2, 8);
    assert(from_nodes.size() == to_nodes.size());

    std::vector<int> covered(9, 0);
    for (const auto& node : from_nodes) {
        assert(2 <= node.left && node.left < node.right && node.right <= 8);
        for (int i = node.left; i < node.right; i++) covered[i]++;
    }
    for (int i = 0; i < 9; i++) assert(covered[i] == (2 <= i && i < 8));

    int auxiliary = range_graph.add_vertex();
    for (const auto& node : from_nodes) {
        long long cost = 20 - node.right;
        range_graph.graph().add_directed_edge(node.vertex, auxiliary, cost);
    }
    for (const auto& node : range_graph.to_range_nodes(0, 2)) {
        range_graph.graph().add_directed_edge(auxiliary, node.vertex, node.left);
    }

    auto result = m1une::graph::dijkstra(range_graph.graph(), 4);
    assert(result.dist[0] == 14);
    assert(result.dist[1] == 14);
}

void test_against_naive_graph() {
    constexpr long long inf = std::numeric_limits<long long>::max() / 4;
    for (int n = 1; n <= 12; n++) {
        for (int test = 0; test < 60; test++) {
            RangeEdgeGraph range_graph(n);
            m1une::graph::Graph<long long> naive(n);

            for (int query = 0; query < 25; query++) {
                int type = (test * 7 + query * 11 + n) % 4;
                int a = (test * 3 + query * 5 + 1) % n;
                int b = (test * 13 + query * 7 + 2) % n;
                int c = (test * 5 + query * 3 + 3) % n;
                int d = (test * 11 + query * 2 + 4) % n;
                int left = std::min(a, b);
                int right = std::max(a, b) + 1;
                int to_left = std::min(c, d);
                int to_right = std::max(c, d) + 1;
                long long cost = (test * 5 + query * 7 + n) % 17;

                if (type == 0) {
                    range_graph.add_point_to_point(a, c, cost);
                    naive.add_directed_edge(a, c, cost);
                } else if (type == 1) {
                    range_graph.add_point_to_range(a, to_left, to_right, cost);
                    for (int to = to_left; to < to_right; to++) {
                        naive.add_directed_edge(a, to, cost);
                    }
                } else if (type == 2) {
                    range_graph.add_range_to_point(left, right, c, cost);
                    for (int from = left; from < right; from++) {
                        naive.add_directed_edge(from, c, cost);
                    }
                } else {
                    range_graph.add_range_to_range(left, right, to_left, to_right, cost);
                    for (int from = left; from < right; from++) {
                        for (int to = to_left; to < to_right; to++) {
                            naive.add_directed_edge(from, to, cost);
                        }
                    }
                }
            }

            for (int source = 0; source < n; source++) {
                auto actual = m1une::graph::dijkstra(range_graph.graph(), source, inf);
                auto expected = m1une::graph::dijkstra(naive, source, inf);
                for (int target = 0; target < n; target++) {
                    assert(actual.dist[target] == expected.dist[target]);
                }
            }
        }
    }
}

int main() {
    test_basic();
    test_empty_ranges();
    test_cover_nodes();
    test_against_naive_graph();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
