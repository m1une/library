#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

#include "graph/graph.hpp"
#include "tree/all.hpp"

using m1une::graph::Graph;

template <class Hld>
std::vector<int> expand_segments(const Hld& hld, const std::vector<m1une::tree::HldPathSegment>& segments) {
    std::vector<int> result;
    for (auto seg : segments) {
        if (seg.reversed) {
            for (int i = seg.r - 1; i >= seg.l; i--) result.push_back(hld.order[i]);
        } else {
            for (int i = seg.l; i < seg.r; i++) result.push_back(hld.order[i]);
        }
    }
    return result;
}

Graph<long long> sample_tree() {
    Graph<long long> g(7);
    g.add_edge(0, 1, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(1, 3, 4);
    g.add_edge(1, 4, 1);
    g.add_edge(2, 5, 6);
    g.add_edge(5, 6, 2);
    return g;
}

void test_rooted_tree() {
    auto g = sample_tree();
    m1une::tree::RootedTree<long long> tree(g, 0);

    assert(tree.size() == 7);
    assert(!tree.empty());
    assert(tree.root == 0);
    assert(tree.parent[0] == -1);
    assert(tree.parent[3] == 1);
    assert(tree.depth[6] == 3);
    assert(tree.dist[6] == 10);
    assert(tree.subtree_size[0] == 7);
    assert(tree.subtree_size[1] == 3);
    assert(tree.is_ancestor(1, 4));
    assert(!tree.is_ancestor(2, 4));
    assert(tree.in_subtree(4, 1));

    assert(tree.kth_ancestor(6, 0) == 6);
    assert(tree.kth_ancestor(6, 1) == 5);
    assert(tree.kth_ancestor(6, 3) == 0);
    assert(tree.kth_ancestor(6, 4) == -1);
    assert(tree.lca(3, 4) == 1);
    assert(tree.lca(3, 6) == 0);
    assert(tree.dist_edges(3, 6) == 5);
    assert(tree.dist_cost(3, 6) == 17);
    assert(tree.jump(3, 6, 0) == 3);
    assert(tree.jump(3, 6, 1) == 1);
    assert(tree.jump(3, 6, 2) == 0);
    assert(tree.jump(3, 6, 3) == 2);
    assert(tree.jump(3, 6, 5) == 6);
    assert(tree.jump(3, 6, 6) == -1);

    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};
    assert(tree.path(3, 6) == expected_path);
    std::vector<int> expected_edges = {2, 0, 1, 4, 5};
    assert(tree.path_edges(3, 6) == expected_edges);

    auto [l, r] = tree.subtree_range(1);
    assert(r - l == 3);
    auto sub = tree.subtree_vertices(1);
    std::sort(sub.begin(), sub.end());
    assert((sub == std::vector<int>{1, 3, 4}));
}

void test_hld() {
    auto g = sample_tree();
    m1une::tree::HeavyLightDecomposition<long long> hld(g, 0);

    assert(hld.size() == 7);
    assert(hld.root == 0);
    assert(hld.lca(3, 4) == 1);
    assert(hld.lca(3, 6) == 0);
    assert(hld.dist_edges(3, 6) == 5);
    assert(hld.dist_cost(3, 6) == 17);
    assert(hld.kth_ancestor(6, 2) == 2);
    assert(hld.kth_ancestor(6, 4) == -1);
    assert(hld.jump(3, 6, 4) == 5);

    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};
    assert(expand_segments(hld, hld.path_segments(3, 6)) == expected_path);
    std::vector<int> expected_edge_vertices = {3, 1, 2, 5, 6};
    assert(expand_segments(hld, hld.path_segments(3, 6, true)) == expected_edge_vertices);

    int segment_count = 0;
    hld.for_each_path(3, 6, [&](int l, int r, bool) {
        assert(l < r);
        segment_count++;
    });
    assert(segment_count == int(hld.path_segments(3, 6).size()));

    auto [vl, vr] = hld.subtree_range(1);
    std::vector<int> subtree;
    for (int i = vl; i < vr; i++) subtree.push_back(hld.order[i]);
    std::sort(subtree.begin(), subtree.end());
    assert((subtree == std::vector<int>{1, 3, 4}));

    auto [el, er] = hld.subtree_range(1, true);
    std::vector<int> edge_subtree;
    for (int i = el; i < er; i++) edge_subtree.push_back(hld.order[i]);
    std::sort(edge_subtree.begin(), edge_subtree.end());
    assert((edge_subtree == std::vector<int>{3, 4}));
}

void test_diameter() {
    auto g = sample_tree();
    auto diameter = m1une::tree::tree_diameter(g);

    assert(!diameter.empty());
    assert(diameter.cost == 17);
    assert(diameter.edge_count == 5);
    assert(diameter.from == diameter.vertices.front());
    assert(diameter.to == diameter.vertices.back());
    std::set<int> endpoints = {diameter.from, diameter.to};
    assert((endpoints == std::set<int>{3, 6}));

    g.erase_edge(1);
    auto split = m1une::tree::tree_diameter(g);
    assert(split.cost == 8);
    assert(split.edge_count == 2);
}

void test_rerooting() {
    auto g = sample_tree();
    auto component_size = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return a + b; },
        [](int acc, int) { return acc + 1; },
        [](int dp, const auto&) { return dp; });
    assert(component_size == std::vector<int>(7, 7));

    auto eccentricity_edges = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return std::max(a, b); },
        [](int acc, int) { return acc; },
        [](int dp, const auto&) { return dp + 1; });
    assert(eccentricity_edges[0] == 3);
    assert(eccentricity_edges[3] == 5);
    assert(eccentricity_edges[6] == 5);

    auto eccentricity_cost = m1une::tree::rerooting_dp(
        g,
        0LL,
        [](long long a, long long b) { return std::max(a, b); },
        [](long long acc, int) { return acc; },
        [](long long dp, const auto& e) { return dp + e.cost; });
    assert(eccentricity_cost[0] == 10);
    assert(eccentricity_cost[3] == 17);
    assert(eccentricity_cost[6] == 17);
}

void test_centroid_decomposition() {
    auto g = sample_tree();
    m1une::tree::CentroidDecomposition<long long> cd(g);

    assert(cd.size() == 7);
    assert(!cd.empty());
    assert(cd.root() == 0);
    assert(cd.roots == std::vector<int>{0});
    assert(cd.parent[cd.root()] == -1);
    assert(cd.depth[cd.root()] == 0);
    assert(cd.order.size() == 7);

    int child_count = 0;
    for (const auto& ch : cd.children) child_count += int(ch.size());
    assert(child_count == 6);
    for (int v = 0; v < 7; v++) {
        if (v == cd.root()) continue;
        assert(cd.parent[v] != -1);
        assert(cd.depth[v] == cd.depth[cd.parent[v]] + 1);
    }
}

void test_forest() {
    Graph<int> g(4);
    g.add_edge(0, 1, 5);
    g.add_edge(2, 3, 7);

    auto diameter = m1une::tree::tree_diameter(g);
    assert(diameter.cost == 7);
    assert(diameter.edge_count == 1);

    auto component_size = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return a + b; },
        [](int acc, int) { return acc + 1; },
        [](int dp, const auto&) { return dp; });
    assert(component_size == std::vector<int>(4, 2));

    m1une::tree::CentroidDecomposition<int> cd(g);
    assert(cd.roots.size() == 2);
    assert(cd.order.size() == 4);
}

int main() {
    test_rooted_tree();
    test_hld();
    test_diameter();
    test_rerooting();
    test_centroid_decomposition();
    test_forest();

    long long a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
