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
    assert((bp.left_vertices == std::vector<int>{0, 2}));
    assert((bp.right_vertices == std::vector<int>{1, 3}));
    assert(bp.left_id[2] == 1);
    assert(bp.right_id[3] == 1);
    auto built = m1une::graph::make_bipartite_matching(square);
    assert(built.has_value());
    assert(built->matching.left_size() == 2);
    assert(built->matching.right_size() == 2);
    assert(built->matching.max_matching() == 2);
    for (const auto& p : built->matching.matching()) {
        int u = built->left_vertex(p.left);
        int v = built->right_vertex(p.right);
        assert(bp.color[u] == 0);
        assert(bp.color[v] == 1);
        assert(square.is_edge_alive(built->original_edge(p.edge_id)));
    }

    Graph<int> triangle(3);
    triangle.add_edge(0, 1);
    triangle.add_edge(1, 2);
    triangle.add_edge(2, 0);
    assert(!m1une::graph::is_bipartite(triangle));
    assert(!m1une::graph::make_bipartite_matching(triangle).has_value());

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

    m1une::graph::BipartiteMatching bm(3, 2);
    int e00 = bm.add_edge(0, 0);
    int e10 = bm.add_edge(1, 0);
    int e11 = bm.add_edge(1, 1);
    int e21 = bm.add_edge(2, 1);
    assert(bm.left_size() == 3);
    assert(bm.right_size() == 2);
    assert(bm.edge_count() == 4);
    assert(bm.get_edge(e10).left == 1);
    assert(bm.max_matching() == 2);
    assert(bm.matching_size() == 2);
    auto pairs = bm.matching();
    assert(pairs.size() == 2);
    auto left_match = bm.left_match();
    auto right_match = bm.right_match();
    for (const auto& p : pairs) {
        assert(left_match[p.left] == p.right);
        assert(right_match[p.right] == p.left);
    }

    auto cover = bm.minimum_vertex_cover();
    assert(cover.left.empty());
    assert((cover.right == std::vector<int>{0, 1}));
    assert(cover.size() == 2);
    auto independent = bm.maximum_independent_set();
    assert((independent.left == std::vector<int>{0, 1, 2}));
    assert(independent.right.empty());

    auto edge_cover = bm.minimum_edge_cover();
    assert(edge_cover.has_value());
    assert(edge_cover->size() == 3);
    std::vector<bool> covered_left(3, false), covered_right(2, false);
    for (int id : *edge_cover) {
        auto edge = bm.get_edge(id);
        covered_left[edge.left] = true;
        covered_right[edge.right] = true;
    }
    assert((covered_left == std::vector<bool>{true, true, true}));
    assert((covered_right == std::vector<bool>{true, true}));

    bm.erase_edge(e11);
    bm.erase_edge(e21);
    assert(!bm.is_edge_alive(e21));
    assert(bm.edges().size() == 2);
    assert(bm.edges(true).size() == 4);
    assert(bm.max_matching() == 1);
    bm.revive_edge(e21);
    assert(bm.max_matching() == 2);

    m1une::graph::BipartiteMatching isolated(1, 1);
    assert(!isolated.minimum_edge_cover().has_value());

    (void)e00;
}

void test_general_matching() {
    m1une::graph::GeneralMatching blossom(6);
    int e01 = blossom.add_edge(0, 1);
    int e12 = blossom.add_edge(1, 2);
    int e23 = blossom.add_edge(2, 3);
    int e34 = blossom.add_edge(3, 4);
    int e40 = blossom.add_edge(4, 0);
    int e15 = blossom.add_edge(1, 5);
    (void)e12;
    (void)e23;
    (void)e34;
    (void)e40;

    assert(blossom.size() == 6);
    assert(blossom.edge_count() == 6);
    assert(blossom.get_edge(e01).other(0) == 1);
    assert(blossom.max_matching() == 3);
    assert(blossom.matching_size() == 3);
    auto mate = blossom.mate();
    auto mate_edge = blossom.mate_edge();
    for (int v = 0; v < 6; v++) {
        assert(mate[v] != -1);
        assert(mate[mate[v]] == v);
        assert(mate_edge[v] != -1);
    }
    auto pairs = blossom.matching();
    assert(pairs.size() == 3);
    for (const auto& p : pairs) {
        assert(mate[p.from] == p.to);
        assert(mate[p.to] == p.from);
    }

    auto edge_cover = blossom.minimum_edge_cover();
    assert(edge_cover.has_value());
    assert(edge_cover->size() == 3);
    std::vector<bool> covered(6, false);
    for (int id : *edge_cover) {
        auto edge = blossom.get_edge(id);
        covered[edge.from] = true;
        covered[edge.to] = true;
    }
    assert((covered == std::vector<bool>{true, true, true, true, true, true}));

    blossom.erase_edge(e15);
    assert(!blossom.is_edge_alive(e15));
    assert(blossom.edges().size() == 5);
    assert(blossom.edges(true).size() == 6);
    assert(blossom.max_matching() == 2);
    assert(!blossom.minimum_edge_cover().has_value());
    blossom.revive_edge(e15);
    assert(blossom.max_matching() == 3);

    m1une::graph::GeneralMatching path(3);
    path.add_edge(0, 1);
    path.add_edge(1, 2);
    auto path_cover = path.minimum_edge_cover();
    assert(path_cover.has_value());
    assert(path_cover->size() == 2);

    m1une::graph::GeneralMatching isolated(1);
    assert(!isolated.minimum_edge_cover().has_value());

    Graph<int> g(4);
    int g01 = g.add_edge(0, 1);
    int g12 = g.add_edge(1, 2);
    int g20 = g.add_edge(2, 0);
    int g23 = g.add_edge(2, 3);
    (void)g01;
    (void)g12;
    (void)g20;
    auto built = m1une::graph::make_general_matching(g);
    assert(built.matching.max_matching() == 2);
    for (const auto& p : built.matching.matching()) {
        assert(g.is_edge_alive(built.original_edge(p.edge_id)));
    }
    assert(g.is_edge_alive(g23));
}

void test_maximum_clique_and_independent_set() {
    Graph<int> g(7);
    int removed_clique_edge = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int id = g.add_edge(i, j);
            if (i == 0 && j == 2) removed_clique_edge = id;
        }
    }
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(5, 1);
    g.add_edge(5, 2);

    auto clique = m1une::graph::maximum_clique(g);
    assert(clique.size() == 4);
    assert((clique.vertices == std::vector<int>{0, 1, 2, 3}));
    assert(m1une::graph::is_clique(g, clique.vertices));
    assert(m1une::graph::maximum_clique_size(g) == 4);

    auto independent = m1une::graph::maximum_independent_set(g);
    assert(independent.size() == 4);
    assert((independent.vertices == std::vector<int>{3, 4, 5, 6}));
    assert(m1une::graph::is_independent_set(g, independent.vertices));
    assert(m1une::graph::maximum_independent_set_size(g) == 4);

    assert(!m1une::graph::is_clique(g, std::vector<int>{0, 2, 4}));
    assert(!m1une::graph::is_independent_set(g, std::vector<int>{4, 0}));

    g.erase_edge(removed_clique_edge);
    assert(m1une::graph::maximum_clique_size(g) == 3);
    g.revive_edge(removed_clique_edge);
    assert(m1une::graph::maximum_clique_size(g) == 4);

    Graph<int> directed(3);
    directed.add_directed_edge(0, 1);
    directed.add_directed_edge(1, 2);
    auto directed_clique = m1une::graph::maximum_clique(directed);
    auto directed_independent = m1une::graph::maximum_independent_set(directed);
    assert(directed_clique.size() == 2);
    assert(directed_independent.size() == 2);
    assert((directed_independent.vertices == std::vector<int>{0, 2}));

    Graph<int> empty(4);
    assert(m1une::graph::maximum_clique_size(empty) == 1);
    assert(m1une::graph::maximum_independent_set_size(empty) == 4);

    Graph<int> none(0);
    assert(m1une::graph::maximum_clique(none).empty());
    assert(m1une::graph::maximum_independent_set(none).empty());
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

void test_bounded_flow() {
    m1une::graph::BoundedFlow<long long> st(4);
    int a = st.add_edge(0, 1, 1, 3);
    int b = st.add_edge(0, 2, 0, 2);
    int c = st.add_edge(1, 3, 1, 2);
    int d = st.add_edge(2, 3, 0, 2);
    int e = st.add_edge(1, 2, 0, 1);
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;

    auto exact = st.feasible_st_flow(0, 3, 3);
    assert(exact.has_value());
    std::vector<long long> balance(4, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, 0, -3}));

    auto too_much = st.feasible_st_flow(0, 3, 6);
    assert(!too_much.has_value());

    m1une::graph::BoundedFlow<long long> bf(3);
    int f01 = bf.add_edge(0, 1, 1, 3);
    int f02 = bf.add_edge(0, 2, 0, 4);
    bf.add_edge(1, 2, 0, 2);
    bf.add_supply(0, 4);
    bf.add_demand(1, 1);
    bf.add_demand(2, 3);
    assert(bf.balance(0) == 4);
    auto bflow = bf.feasible_flow();
    assert(bflow.has_value());
    assert(bflow->get_edge(f01).flow >= 1);
    assert(bflow->get_edge(f02).flow >= 0);
    std::vector<long long> b_balance(3, 0);
    for (const auto& edge : bflow->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        b_balance[edge.from] += edge.flow;
        b_balance[edge.to] -= edge.flow;
    }
    assert((b_balance == std::vector<long long>{4, -1, -3}));

    m1une::graph::BoundedFlow<long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.feasible_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);

    m1une::graph::BoundedFlow<long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.feasible_flow().has_value());

    m1une::graph::BFlow<long long> alias(1);
    assert(alias.size() == 1);
}

void test_bounded_min_cost_flow() {
    m1une::graph::BoundedMinCostFlow<long long, long long> st(3);
    int e01 = st.add_edge(0, 1, 1, 3, 2);
    int e12 = st.add_edge(1, 2, 1, 3, 1);
    int e02 = st.add_edge(0, 2, 0, 3, 10);

    auto exact = st.min_cost_st_flow(0, 2, 3);
    assert(exact.has_value());
    assert(exact->cost == 9);
    assert(exact->flow(e01) == 3);
    assert(exact->flow(e12) == 3);
    assert(exact->flow(e02) == 0);
    std::vector<long long> balance(3, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, -3}));

    m1une::graph::BoundedMinCostFlow<long long, long long> bf(3);
    int p01 = bf.add_edge(0, 1, 0, 2, 1);
    int p12 = bf.add_edge(1, 2, 0, 2, 1);
    int p02 = bf.add_edge(0, 2, 0, 2, 5);
    bf.add_supply(0, 2);
    bf.add_demand(2, 2);
    auto bflow = bf.min_cost_flow();
    assert(bflow.has_value());
    assert(bflow->cost == 4);
    assert(bflow->flow(p01) == 2);
    assert(bflow->flow(p12) == 2);
    assert(bflow->flow(p02) == 0);

    m1une::graph::BoundedMinCostFlow<long long, long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5, 2);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.min_cost_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);
    assert(negative_flow->cost == -6);

    m1une::graph::BoundedMinCostFlow<long long, long long> cycle(2);
    int c01 = cycle.add_edge(0, 1, 0, 1, -5);
    int c10 = cycle.add_edge(1, 0, 0, 1, 3);
    auto circulation = cycle.min_cost_flow();
    assert(circulation.has_value());
    assert(circulation->flow(c01) == 1);
    assert(circulation->flow(c10) == 1);
    assert(circulation->cost == -2);

    m1une::graph::BoundedMinCostFlow<long long, long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1, 0);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.min_cost_flow().has_value());

    m1une::graph::BMinCostFlow<long long, long long> alias(1);
    assert(alias.size() == 1);
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
    test_general_matching();
    test_maximum_clique_and_independent_set();
    test_cycle_detection();
    test_kruskal();
    test_grid();
    test_max_flow();
    test_bounded_flow();
    test_bounded_min_cost_flow();
    test_min_cost_flow();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
