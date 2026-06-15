#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
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

void test_edge_alive() {
    Graph<int> g(4);
    int e01 = g.add_edge(0, 1);
    int e12 = g.add_edge(1, 2);
    int e23 = g.add_edge(2, 3);
    (void)e01;
    (void)e23;

    assert(g.edge_count() == 3);
    assert(g.edges().size() == 3);
    auto res = m1une::graph::bfs(g, 0);
    assert(res.dist[3] == 3);

    g.erase_edge(e12);
    assert(!g.is_edge_alive(e12));
    assert(g.edges().size() == 2);
    assert(g.edges(true).size() == 3);
    auto cut = m1une::graph::bfs(g, 0);
    assert(!cut.reachable(3));

    auto rev = g.reversed();
    assert(!rev.is_edge_alive(e12));
    assert(rev.edges().size() == 2);

    g.revive_edge(e12);
    assert(g.is_edge_alive(e12));
    auto restored = m1une::graph::bfs(g, 0);
    assert(restored.dist[3] == 3);
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

void test_zero_one_bfs() {
    Graph<int> g(6);
    g.add_directed_edge(0, 1, 1);
    g.add_directed_edge(0, 2, 0);
    g.add_directed_edge(2, 1, 0);
    g.add_directed_edge(1, 3, 1);
    g.add_directed_edge(2, 3, 1);
    g.add_directed_edge(3, 4, 0);

    auto res = m1une::graph::zero_one_bfs(g, 0);
    assert(res.dist[0] == 0);
    assert(res.dist[1] == 0);
    assert(res.dist[3] == 1);
    assert(res.dist[4] == 1);
    assert(!res.reachable(5));
    assert((res.path(4) == std::vector<int>{0, 2, 3, 4}));

    auto multi = m1une::graph::zero_one_bfs(g, std::vector<int>{1, 5});
    assert(multi.dist[1] == 0);
    assert(multi.dist[4] == 1);
    assert(multi.dist[5] == 0);
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

void test_dag_shortest_path() {
    Graph<long long> g(6);
    g.add_directed_edge(0, 1, 2);
    g.add_directed_edge(0, 2, 5);
    g.add_directed_edge(1, 2, -4);
    g.add_directed_edge(1, 4, 10);
    g.add_directed_edge(2, 3, 3);
    g.add_directed_edge(3, 4, 1);

    auto res = m1une::graph::dag_shortest_path(g, 0);
    assert(res.has_value());
    assert(res->dist[0] == 0);
    assert(res->dist[2] == -2);
    assert(res->dist[4] == 2);
    assert(!res->reachable(5));
    assert((res->path(4) == std::vector<int>{0, 1, 2, 3, 4}));
    assert(res->topological_order.size() == 6);

    auto multi = m1une::graph::dag_shortest_path(g, std::vector<int>{1, 5});
    assert(multi.has_value());
    assert(multi->dist[4] == 0);
    assert(multi->dist[5] == 0);

    g.add_directed_edge(4, 1, 1);
    auto cyclic = m1une::graph::dag_shortest_path(g, 0);
    assert(!cyclic.has_value());
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

void test_grid() {
    m1une::graph::Grid grid(3, 4);
    assert(grid.height() == 3);
    assert(grid.width() == 4);
    assert(grid.size() == 12);
    assert(grid.inside(2, 3));
    assert(!grid.inside(3, 0));
    assert(grid.id(2, 3) == 11);
    assert(grid.pos(6) == std::make_pair(1, 2));

    auto adj4 = grid.adj4(0, 0);
    assert((adj4 == std::vector<std::pair<int, int>>{{0, 1}, {1, 0}}));

    auto adj8 = grid.adj8(1, 1);
    assert(adj8.size() == 8);
    auto adj4_ids = grid.adj4_ids(grid.id(1, 1));
    std::set<int> expected_ids = {grid.id(0, 1), grid.id(1, 2), grid.id(2, 1), grid.id(1, 0)};
    assert(std::set<int>(adj4_ids.begin(), adj4_ids.end()) == expected_ids);

    std::vector<std::string> s = {
        "....",
        ".##.",
        "....",
    };
    auto passable = [&](int i, int j) {
        return s[i][j] != '#';
    };

    auto g4 = grid.graph4(passable);
    assert(g4.size() == grid.size());
    assert(g4[grid.id(1, 1)].empty());
    auto res = m1une::graph::bfs(g4, grid.id(0, 0));
    assert(res.dist[grid.id(2, 3)] == 5);
    assert(res.dist[grid.id(1, 1)] == -1);

    auto g8 = grid.graph8(passable);
    auto res8 = m1une::graph::bfs(g8, grid.id(0, 0));
    assert(res8.dist[grid.id(2, 3)] == 4);

    auto all4 = grid.graph4();
    assert(all4.edge_count() == 17);
}

void test_max_flow() {
    m1une::graph::MaxFlow<long long> mf(4);
    int e0 = mf.add_edge(0, 1, 2);
    int e1 = mf.add_edge(0, 2, 1);
    int e2 = mf.add_edge(1, 2, 1);
    int e3 = mf.add_edge(1, 3, 1);
    int e4 = mf.add_edge(2, 3, 2);
    (void)e1;
    (void)e2;
    (void)e3;
    (void)e4;

    assert(mf.size() == 4);
    assert(mf.edge_count() == 5);
    assert(mf.max_flow(0, 3) == 3);
    auto edges = mf.edges();
    long long outgoing = 0;
    for (const auto& e : edges) {
        if (e.from == 0) outgoing += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(outgoing == 3);
    assert(mf.get_edge(e0).cap == 2);

    auto cut = mf.min_cut(0);
    assert(cut[0]);
    assert(!cut[3]);

    mf.change_edge(e0, 3, 1);
    auto changed = mf.get_edge(e0);
    assert(changed.cap == 3);
    assert(changed.flow == 1);
}

void test_min_cost_flow() {
    m1une::graph::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto result = mcf.flow(0, 3, 2);
    assert(result.first == 2);
    assert(result.second == 5);
    auto edges = mcf.edges();
    long long total_source_flow = 0;
    for (const auto& e : edges) {
        if (e.from == 0) total_source_flow += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(total_source_flow == 2);

    m1une::graph::MinCostFlow<long long, long long> negative(3);
    negative.add_edge(0, 1, 1, -5);
    negative.add_edge(1, 2, 1, 2);
    negative.add_edge(0, 2, 1, 10);
    auto slope = negative.slope(0, 2, 2);
    assert((slope == std::vector<std::pair<long long, long long>>{{0, 0}, {1, -3}, {2, 7}}));
}

int main() {
    test_graph_container();
    test_edge_alive();
    test_bfs();
    test_dijkstra();
    test_zero_one_bfs();
    test_bellman_ford();
    test_dag_shortest_path();
    test_warshall_floyd();
    test_topological_sort();
    test_scc();
    test_lowlink();
    test_bipartite_and_components();
    test_cycle_detection();
    test_kruskal();
    test_grid();
    test_max_flow();
    test_min_cost_flow();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
