#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/random.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifndef NDEBUG
namespace {

struct Dsu {
    std::vector<int> parent;

    explicit Dsu(int size) : parent(size, -1) {}

    int leader(int vertex) {
        if (parent[vertex] < 0) return vertex;
        return parent[vertex] = leader(parent[vertex]);
    }

    bool merge(int first, int second) {
        first = leader(first);
        second = leader(second);
        if (first == second) return false;
        if (parent[second] < parent[first]) std::swap(first, second);
        parent[first] += parent[second];
        parent[second] = first;
        return true;
    }
};

void test_basic_generators() {
    m1une::utilities::Random first(123456);
    m1une::utilities::Random second(123456);
    assert(first.sequence(100, -10, 20) == second.sequence(100, -10, 20));
    assert(first.string(100, "abc") == second.string(100, "abc"));
    assert(first.permutation(100) == second.permutation(100));
    assert(first.tree(100) == second.tree(100));
    assert(first.graph(100, 300) == second.graph(100, 300));

    m1une::utilities::Random random(998244353);
    auto sequence = random.sequence(1000, -7LL, 11LL);
    assert(sequence.size() == 1000);
    for (long long value : sequence) assert(-7 <= value && value <= 11);

    std::string text = random.string(1000, "xyz");
    assert(text.size() == 1000);
    for (char character : text) assert(character == 'x' || character == 'y' || character == 'z');

    std::vector<int> permutation = random.permutation(100, 10);
    std::sort(permutation.begin(), permutation.end());
    for (int i = 0; i < 100; i++) assert(permutation[i] == i + 10);
}

void test_trees() {
    m1une::utilities::Random random(123);
    assert(random.tree(0).empty());
    assert(random.tree(1).empty());
    for (int size = 2; size <= 200; size++) {
        auto edges = random.tree(size);
        assert(int(edges.size()) == size - 1);
        Dsu dsu(size);
        for (auto [from, to] : edges) {
            assert(0 <= from && from < size);
            assert(0 <= to && to < size);
            assert(from != to);
            assert(dsu.merge(from, to));
        }
        int root = dsu.leader(0);
        for (int vertex = 1; vertex < size; vertex++) assert(dsu.leader(vertex) == root);
    }
}

void test_graphs() {
    m1une::utilities::Random random(456);
    for (int size = 2; size <= 50; size++) {
        int maximum = size * (size - 1) / 2;
        int edge_count = std::min(maximum, size * 3);
        auto edges = random.graph(size, edge_count);
        assert(int(edges.size()) == edge_count);
        std::set<std::pair<int, int>> unique;
        for (auto [from, to] : edges) {
            assert(0 <= from && from < to && to < size);
            unique.emplace(from, to);
        }
        assert(int(unique.size()) == edge_count);
    }

    auto complete = random.graph(20, 190);
    assert(complete.size() == 190);
    std::set<std::pair<int, int>> complete_unique(complete.begin(), complete.end());
    assert(complete_unique.size() == 190);

    auto directed = random.directed_graph(20, 300);
    std::set<std::pair<int, int>> directed_unique;
    for (auto [from, to] : directed) {
        assert(0 <= from && from < 20);
        assert(0 <= to && to < 20);
        assert(from != to);
        directed_unique.emplace(from, to);
    }
    assert(directed_unique.size() == directed.size());

    m1une::utilities::RandomGraphOptions options;
    options.allow_self_loops = true;
    auto looped_complete = random.graph(5, 15, options);
    std::set<std::pair<int, int>> looped_unique;
    for (auto [from, to] : looped_complete) {
        assert(0 <= from && from <= to && to < 5);
        looped_unique.emplace(from, to);
    }
    assert(looped_unique.size() == 15);

    options.directed = true;
    auto directed_looped_complete = random.graph(5, 25, options);
    std::set<std::pair<int, int>> directed_looped_unique(
        directed_looped_complete.begin(), directed_looped_complete.end());
    assert(directed_looped_unique.size() == 25);

    options.allow_parallel_edges = true;
    auto multigraph = random.graph(3, 1000, options);
    assert(multigraph.size() == 1000);
    for (auto [from, to] : multigraph) {
        assert(0 <= from && from < 3);
        assert(0 <= to && to < 3);
    }
}

void test_weighted_graphs_and_dags() {
    m1une::utilities::Random random(789);

    auto weighted_tree = random.weighted_tree(100, -50LL, 70LL);
    assert(weighted_tree.size() == 99);
    Dsu dsu(100);
    for (auto [from, to, weight] : weighted_tree) {
        assert(-50 <= weight && weight <= 70);
        assert(dsu.merge(from, to));
    }

    auto weighted_graph = random.weighted_graph(50, 300, -20, 30);
    assert(weighted_graph.size() == 300);
    std::set<std::pair<int, int>> graph_edges;
    for (auto [from, to, weight] : weighted_graph) {
        assert(0 <= from && from < to && to < 50);
        assert(-20 <= weight && weight <= 30);
        graph_edges.emplace(from, to);
    }
    assert(graph_edges.size() == 300);

    for (int size = 2; size <= 80; size++) {
        int maximum = size * (size - 1) / 2;
        int edge_count = std::min(maximum, size * 4);
        auto edges = random.dag(size, edge_count);
        assert(int(edges.size()) == edge_count);

        std::vector<std::vector<int>> adjacency(size);
        std::vector<int> indegree(size);
        std::set<std::pair<int, int>> unique;
        for (auto [from, to] : edges) {
            assert(0 <= from && from < size);
            assert(0 <= to && to < size);
            assert(from != to);
            adjacency[from].push_back(to);
            indegree[to]++;
            unique.emplace(from, to);
        }
        assert(int(unique.size()) == edge_count);

        std::vector<int> queue;
        for (int vertex = 0; vertex < size; vertex++) {
            if (indegree[vertex] == 0) queue.push_back(vertex);
        }
        for (int head = 0; head < int(queue.size()); head++) {
            for (int next : adjacency[queue[head]]) {
                if (--indegree[next] == 0) queue.push_back(next);
            }
        }
        assert(int(queue.size()) == size);
    }

    auto weighted_dag = random.weighted_dag(100, 500, 1U, 100U);
    assert(weighted_dag.size() == 500);
    for (auto [from, to, weight] : weighted_dag) {
        assert(0 <= from && from < 100);
        assert(0 <= to && to < 100);
        assert(from != to);
        assert(1 <= weight && weight <= 100);
    }

    m1une::utilities::RandomGraphOptions parallel_options;
    parallel_options.allow_parallel_edges = true;
    auto parallel_dag = random.dag(2, 100, parallel_options);
    assert(parallel_dag.size() == 100);
    for (auto edge : parallel_dag) assert(edge == parallel_dag.front());

    auto parallel_weighted_dag =
        random.weighted_dag(2, 100, -3, 7, parallel_options);
    assert(parallel_weighted_dag.size() == 100);
    for (auto [from, to, weight] : parallel_weighted_dag) {
        assert(from == std::get<0>(parallel_weighted_dag.front()));
        assert(to == std::get<1>(parallel_weighted_dag.front()));
        assert(-3 <= weight && weight <= 7);
    }

    parallel_options.allow_self_loops = true;
    auto parallel_directed = random.directed_graph(2, 100, parallel_options);
    assert(parallel_directed.size() == 100);
    auto parallel_weighted_directed =
        random.weighted_directed_graph(2, 100, 0LL, 10LL, parallel_options);
    assert(parallel_weighted_directed.size() == 100);
}

}  // namespace
#endif

int main() {
#ifndef NDEBUG
    test_basic_generators();
    test_trees();
    test_graphs();
    test_weighted_graphs_and_dags();
#endif

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
