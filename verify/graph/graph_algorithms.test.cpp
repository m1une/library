#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "graph/all.hpp"

using m1une::graph::Graph;

void test_graph_container() {
    Graph<int> g(2);
    assert(g.size() == 2);
    int added = g.add_vertex();
    assert(added == 2);
    int e0 = g.add_directed_edge(0, 1, 4);
    int e1 = g.add_edge(1, 2, 5);
    assert(e0 == 0);
    assert(e1 == 1);
    assert(g.edge_count() == 2);
    assert(g[1].size() == 1);
    assert(g.edges().size() == 2);
    auto rev = g.reversed();
    assert(rev[1][0].to == 0);
}

void test_bfs() {
    Graph<int> g(5);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 3);
    g.add_directed_edge(2, 3);
    g.add_directed_edge(3, 4);

    auto res = m1une::graph::bfs(g, 0);
    assert(res.dist[0] == 0);
    assert(res.dist[3] == 2);
    assert(res.dist[4] == 3);
    auto path = res.path(4);
    assert(path.front() == 0);
    assert(path.back() == 4);
    assert(path.size() == 4);
}

void test_dijkstra() {
    Graph<long long> g(5);
    g.add_directed_edge(0, 1, 4);
    g.add_directed_edge(0, 2, 1);
    g.add_directed_edge(2, 1, 2);
    g.add_directed_edge(1, 3, 1);
    g.add_directed_edge(2, 3, 7);
    g.add_directed_edge(3, 4, 3);

    auto res = m1une::graph::dijkstra(g, 0);
    assert(res.dist[1] == 3);
    assert(res.dist[4] == 7);
    assert((res.path(4) == std::vector<int>{0, 2, 1, 3, 4}));
}

void test_bellman_ford() {
    Graph<long long> g(5);
    g.add_directed_edge(0, 1, 1);
    g.add_directed_edge(1, 2, -3);
    g.add_directed_edge(2, 3, 1);
    g.add_directed_edge(3, 1, 1);
    g.add_directed_edge(0, 4, 5);

    auto res = m1une::graph::bellman_ford(g, 0);
    assert(res.has_negative_cycle);
    assert(res.affected_by_negative_cycle(1));
    assert(res.affected_by_negative_cycle(2));
    assert(res.affected_by_negative_cycle(3));
    assert(!res.affected_by_negative_cycle(4));
    assert(res.dist[4] == 5);
}

void test_warshall_floyd() {
    Graph<long long> g(4);
    g.add_directed_edge(0, 1, 3);
    g.add_directed_edge(1, 2, 4);
    g.add_directed_edge(0, 2, 10);
    g.add_directed_edge(2, 3, -2);

    auto dist = m1une::graph::warshall_floyd(g);
    assert(dist[0][2] == 7);
    assert(dist[0][3] == 5);
    assert(!m1une::graph::has_negative_cycle(dist));

    bool changed = m1une::graph::warshall_floyd_add_directed_edge(dist, 3, 1, 1LL);
    assert(changed);
    assert(dist[0][1] == 3);
    assert(dist[2][1] == -1);
    assert(dist[3][2] == 5);

    changed = m1une::graph::warshall_floyd_add_directed_edge(dist, 0, 2, 100LL);
    assert(!changed);

    Graph<long long> undirected(4);
    undirected.add_edge(0, 1, 10);
    undirected.add_edge(1, 2, 10);
    undirected.add_edge(2, 3, 10);
    auto udist = m1une::graph::warshall_floyd(undirected);
    changed = m1une::graph::warshall_floyd_add_undirected_edge(udist, 0, 3, 1LL);
    assert(changed);
    assert(udist[0][3] == 1);
    assert(udist[3][0] == 1);
    assert(udist[1][3] == 11);
}

void test_topological_sort() {
    Graph<int> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 3);
    g.add_directed_edge(2, 3);

    auto order = m1une::graph::topological_sort(g);
    assert(order.has_value());
    std::vector<int> pos(4);
    for (int i = 0; i < 4; i++) pos[(*order)[i]] = i;
    for (int v = 0; v < 4; v++) {
        for (const auto& e : g[v]) assert(pos[e.from] < pos[e.to]);
    }

    g.add_directed_edge(3, 0);
    assert(!m1une::graph::is_dag(g));
}

void test_scc() {
    Graph<int> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 0);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 3);
    g.add_directed_edge(3, 2);

    auto scc = m1une::graph::strongly_connected_components(g);
    assert(scc.count == 2);
    assert(scc.same(0, 1));
    assert(scc.same(2, 3));
    assert(!scc.same(0, 2));
    auto dag = scc.dag(g);
    assert(dag.size() == 2);
    assert(dag.edge_count() == 1);
}

void test_lowlink() {
    Graph<int> g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    int b0 = g.add_edge(1, 3);
    int b1 = g.add_edge(3, 4);

    auto res = m1une::graph::lowlink(g);
    assert((res.articulation == std::vector<int>{1, 3}));
    assert((res.bridge_ids == std::vector<int>{b0, b1}));
}

void test_bipartite_and_components() {
    Graph<int> square(4);
    square.add_edge(0, 1);
    square.add_edge(1, 2);
    square.add_edge(2, 3);
    square.add_edge(3, 0);
    auto bp = m1une::graph::bipartite(square);
    assert(bp.is_bipartite);
    assert(bp.color[0] == bp.color[2]);

    Graph<int> triangle(3);
    triangle.add_edge(0, 1);
    triangle.add_edge(1, 2);
    triangle.add_edge(2, 0);
    assert(!m1une::graph::is_bipartite(triangle));

    Graph<int> cc_graph(5);
    cc_graph.add_edge(0, 1);
    cc_graph.add_edge(2, 3);
    auto cc = m1une::graph::connected_components(cc_graph);
    assert(cc.count == 3);
    assert(cc.same(0, 1));
    assert(cc.same(2, 3));
    assert(!cc.same(0, 2));

    Graph<int> directed(2);
    directed.add_directed_edge(1, 0);
    assert(m1une::graph::is_bipartite(directed));
    auto weak = m1une::graph::connected_components(directed);
    assert(weak.count == 1);
}

void test_cycle_detection() {
    Graph<int> dg(3);
    dg.add_directed_edge(0, 1);
    dg.add_directed_edge(1, 2);
    dg.add_directed_edge(2, 0);
    auto directed = m1une::graph::find_directed_cycle(dg);
    assert(!directed.empty());
    assert(directed.vertices.front() == directed.vertices.back());
    assert(directed.edge_ids.size() + 1 == directed.vertices.size());

    Graph<int> ug(4);
    ug.add_edge(0, 1);
    ug.add_edge(1, 2);
    ug.add_edge(2, 0);
    ug.add_edge(2, 3);
    auto undirected = m1une::graph::find_undirected_cycle(ug);
    assert(!undirected.empty());
    assert(undirected.vertices.front() == undirected.vertices.back());
}

void test_kruskal() {
    Graph<long long> g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(0, 3, 10);
    g.add_edge(0, 2, 4);

    auto mst = m1une::graph::kruskal(g);
    assert(mst.cost == 6);
    assert(mst.edges.size() == 3);
    assert(mst.components == 1);
    assert(mst.is_spanning_tree(g.size()));
}

int main() {
    test_graph_container();
    test_bfs();
    test_dijkstra();
    test_bellman_ford();
    test_warshall_floyd();
    test_topological_sort();
    test_scc();
    test_lowlink();
    test_bipartite_and_components();
    test_cycle_detection();
    test_kruskal();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
