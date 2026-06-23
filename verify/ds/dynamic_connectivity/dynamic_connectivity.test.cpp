#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#include "../../../ds/dynamic_connectivity/all.hpp"

struct NaiveDynamicGraph {
    struct Edge {
        int u;
        int v;
        bool alive;
    };

    int n;
    std::vector<Edge> edges;

    explicit NaiveDynamicGraph(int n) : n(n) {}

    int add_edge(int u, int v) {
        int id = int(edges.size());
        edges.push_back(Edge{u, v, true});
        return id;
    }

    bool erase_edge(int id) {
        if (!edges[id].alive) return false;
        edges[id].alive = false;
        return true;
    }

    std::vector<int> component(int start) const {
        std::vector<std::vector<int>> graph(n);
        for (const Edge& edge : edges) {
            if (!edge.alive || edge.u == edge.v) continue;
            graph[edge.u].push_back(edge.v);
            graph[edge.v].push_back(edge.u);
        }
        std::vector<int> visited(n, false);
        std::queue<int> queue;
        std::vector<int> vertices;
        visited[start] = true;
        queue.push(start);
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            vertices.push_back(v);
            for (int to : graph[v]) {
                if (visited[to]) continue;
                visited[to] = true;
                queue.push(to);
            }
        }
        return vertices;
    }

    bool connected(int u, int v) const {
        std::vector<int> vertices = component(u);
        for (int x : vertices) {
            if (x == v) return true;
        }
        return false;
    }

    int component_count() const {
        std::vector<bool> visited(n, false);
        int result = 0;
        for (int v = 0; v < n; v++) {
            if (visited[v]) continue;
            result++;
            for (int x : component(v)) visited[x] = true;
        }
        return result;
    }
};

void test_online_basic() {
    m1une::ds::OnlineDynamicConnectivity graph(4);
    graph.reserve_edges(8);
    int e01 = graph.add_edge(0, 1);
    int e12 = graph.add_edge(1, 2);
    int e02 = graph.add_edge(0, 2);
    int loop = graph.add_edge(3, 3);
    assert(graph.connected(0, 2));
    assert(graph.component_size(0) == 3);
    assert(graph.component_count() == 2);
    assert(graph.active_edge_count() == 4);

    assert(graph.erase_edge(e12));
    assert(graph.connected(0, 2));
    assert(graph.erase_edge(e02));
    assert(!graph.connected(0, 2));
    assert(graph.component_count() == 3);
    assert(!graph.erase_edge(e02));
    assert(graph.erase_edge(loop));
    assert(graph.erase_edge(e01));
    assert(graph.component_count() == 4);
}

void test_offline_basic() {
    m1une::ds::OfflineDynamicConnectivity graph(3);
    graph.reserve_edges(8);
    graph.reserve_queries(8);
    int e01 = graph.add_edge(0, 1);
    int q0 = graph.add_query(0, 2);
    int e12 = graph.add_edge(1, 2);
    int q1 = graph.add_query(0, 2);
    assert(graph.erase_edge(e01));
    int q2 = graph.add_query(0, 2);
    assert(!graph.erase_edge(e01));
    int parallel = graph.add_edge(1, 2);
    int q3 = graph.add_query(1, 2);
    assert(graph.erase_edge(e12));
    int q4 = graph.add_query(1, 2);
    assert(graph.erase_edge(parallel));
    int q5 = graph.add_query(1, 2);

    std::vector<bool> answer = graph.solve();
    assert(!answer[q0]);
    assert(answer[q1]);
    assert(!answer[q2]);
    assert(answer[q3]);
    assert(answer[q4]);
    assert(!answer[q5]);
    assert(answer == graph.solve());

    int restored = graph.add_edge(0, 2);
    int q6 = graph.add_query(0, 2);
    answer = graph.solve();
    assert(answer[q6]);
    assert(graph.erase_edge(restored));
}

void test_online_random() {
    std::mt19937 random(123456789);
    for (int test = 0; test < 80; test++) {
        int n = 1 + random() % 15;
        m1une::ds::OnlineDynamicConnectivity graph(n);
        NaiveDynamicGraph naive(n);
        std::vector<int> active;
        for (int operation = 0; operation < 1000; operation++) {
            int type = random() % 5;
            if (type <= 1 || active.empty()) {
                int u = random() % n;
                int v = random() % n;
                int id = graph.add_edge(u, v);
                assert(id == naive.add_edge(u, v));
                active.push_back(id);
            } else if (type == 2) {
                int index = random() % active.size();
                int id = active[index];
                std::swap(active[index], active.back());
                active.pop_back();
                assert(graph.erase_edge(id));
                assert(naive.erase_edge(id));
            } else {
                int u = random() % n;
                int v = random() % n;
                assert(graph.connected(u, v) == naive.connected(u, v));
                assert(graph.component_size(u) == int(naive.component(u).size()));
            }
            assert(graph.active_edge_count() == int(active.size()));
            assert(graph.component_count() == naive.component_count());
        }
    }
}

void test_offline_random() {
    std::mt19937 random(987654321);
    for (int test = 0; test < 100; test++) {
        int n = 1 + random() % 12;
        m1une::ds::OfflineDynamicConnectivity graph(n);
        NaiveDynamicGraph naive(n);
        std::vector<int> active;
        std::vector<bool> expected;
        for (int operation = 0; operation < 500; operation++) {
            int type = random() % 4;
            if (type == 0 || active.empty()) {
                int u = random() % n;
                int v = random() % n;
                int id = graph.add_edge(u, v);
                assert(id == naive.add_edge(u, v));
                active.push_back(id);
            } else if (type == 1) {
                int index = random() % active.size();
                int id = active[index];
                std::swap(active[index], active.back());
                active.pop_back();
                assert(graph.erase_edge(id));
                assert(naive.erase_edge(id));
            } else {
                int u = random() % n;
                int v = random() % n;
                assert(graph.add_query(u, v) == int(expected.size()));
                expected.push_back(naive.connected(u, v));
            }
        }
        assert(graph.solve() == expected);
    }
}

int main() {
    test_online_basic();
    test_offline_basic();
    test_online_random();
    test_offline_random();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
