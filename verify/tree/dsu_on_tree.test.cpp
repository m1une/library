#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../tree/dsu_on_tree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

#include "../../graph/graph.hpp"

namespace {

void check(
    const m1une::graph::Graph<int>& graph,
    const std::vector<int>& color,
    int root
) {
    int n = graph.size();
    m1une::tree::DsuOnTree<int> dsu(graph, root);
    assert(dsu.size() == n);
    assert(dsu.root == root);

    std::vector<int> frequency(12, 0);
    std::vector<int> answer(n, 0);
    std::vector<int> active(n, 0);
    int distinct = 0;

    dsu.run(
        [&](int vertex) {
            assert(active[vertex] == 0);
            active[vertex] = 1;
            if (frequency[color[vertex]]++ == 0) distinct++;
        },
        [&](int vertex) {
            assert(active[vertex] == 1);
            active[vertex] = 0;
            if (--frequency[color[vertex]] == 0) distinct--;
        },
        [&](int vertex) {
            answer[vertex] = distinct;
            for (int index = 0; index < n; ++index) {
                [[maybe_unused]] bool in_subtree =
                    dsu.tin[vertex] <= dsu.tin[index]
                    && dsu.tin[index] < dsu.tout[vertex];
                assert(bool(active[index]) == in_subtree);
            }
        }
    );

    for (int vertex = 0; vertex < n; ++vertex) {
        std::set<int> expected;
        for (
            int index = dsu.tin[vertex];
            index < dsu.tout[vertex];
            ++index
        ) {
            expected.insert(color[dsu.order[index]]);
        }
        assert(answer[vertex] == int(expected.size()));
        assert(dsu.tout[vertex] - dsu.tin[vertex] == dsu.subtree_size[vertex]);
        if (dsu.heavy_child[vertex] != -1) {
            for ([[maybe_unused]] int child : dsu.children[vertex]) {
                assert(
                    dsu.subtree_size[child]
                    <= dsu.subtree_size[dsu.heavy_child[vertex]]
                );
            }
        }
    }
}

void test_empty() {
    m1une::graph::Graph<int> graph(0);
    m1une::tree::DsuOnTree<int> dsu(graph);
    assert(dsu.empty());
    dsu.run(
        [](int) { assert(false); },
        [](int) { assert(false); },
        [](int) { assert(false); }
    );
}

void test_randomized() {
    std::uint64_t state = 401;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2500; ++trial) {
        int n = 1 + int(random() % 60);
        m1une::graph::Graph<int> graph(n);
        for (int vertex = 1; vertex < n; ++vertex) {
            graph.add_edge(vertex, int(random() % vertex));
        }
        std::vector<int> color(n);
        for (int& value : color) value = int(random() % 12);
        check(graph, color, int(random() % n));
    }
}

void test_long_path() {
    constexpr int n = 200000;
    m1une::graph::Graph<int> graph(n);
    for (int vertex = 1; vertex < n; ++vertex) {
        graph.add_edge(vertex - 1, vertex);
    }

    m1une::tree::DsuOnTree<int> dsu(graph);
    int count = 0;
    std::vector<int> answer(n);
    dsu.run(
        [&](int) { count++; },
        [&](int) { count--; },
        [&](int vertex) { answer[vertex] = count; }
    );
    assert(answer[0] == n);
    assert(answer[n - 1] == 1);
}

}  // namespace

int main() {
    test_empty();
    test_randomized();
    test_long_path();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
