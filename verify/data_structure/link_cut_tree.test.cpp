#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "data_structure/link_cut_tree.hpp"
#include "monoid/add.hpp"

void test_vertex_subtree_sum() {
    m1une::data_structure::LinkCutTree<m1une::monoid::Add<long long>> lct(std::vector<int>{1, 2, 3, 4, 5});

    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    assert(lct.path_prod(2, 4) == 14);
    assert(lct.subtree_prod(0, 1) == 14);
    assert(lct.subtree_size(0, 1) == 4);
    assert(lct.subtree_prod(1, 3) == 9);

    lct.set(3, 40);
    assert(lct.path_prod(2, 4) == 50);
    assert(lct.subtree_prod(0, 1) == 50);
    assert(lct.subtree_prod(1, 3) == 45);

    assert(lct.cut(1, 3));
    assert(lct.subtree_prod(0, 1) == 5);
    assert(!lct.connected(2, 4));
    assert(lct.link(2, 4));
    assert(lct.subtree_prod(0, 1) == 50);
    assert(lct.subtree_prod(0, 2) == 48);
}

void test_edge_nodes_subtree() {
    m1une::data_structure::LinkCutTree<m1une::monoid::Add<long long>> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);

    assert(lct.path_prod(0, 2) == 12);
    assert(lct.subtree_prod(0, 0) == 12);
    assert(lct.subtree_prod(0, 1) == 7);
    assert(lct.subtree_size(0, 1) == 3);
    assert(lct.subtree_size(0, lct.edge_node(e12)) == 2);

    lct.set_edge(e12, 20);
    assert(lct.path_prod(0, 2) == 25);
    assert(lct.subtree_prod(0, 1) == 20);

    assert(lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
}

void test_rooted_tree_utility_apis() {
    m1une::data_structure::LinkCutTree<m1une::monoid::Add<long long>> lct(std::vector<int>{1, 2, 3, 4, 5});

    assert(lct.link_parent(1, 0));
    assert(lct.link_parent(2, 0));
    assert(lct.link_parent(3, 2));
    assert(lct.link_parent(4, 2));

    assert(lct.root(4) == 0);
    lct.reroot(0);

    assert(lct.component_prod(0) == 15);
    assert(lct.component_size(0) == 5);

    assert(lct.child_toward(0, 4) == 2);
    assert(lct.child_toward(2, 4) == 4);
    assert(lct.child_toward(4, 0) == 2);

    assert(lct.branch_prod(0, 4) == 12);
    assert(lct.branch_size(0, 4) == 3);

    assert(lct.parent(0, 4) == 2);
    assert(lct.parent(0, 2) == 0);
    assert(lct.parent(0, 0) == -1);

    assert(lct.subtree_prod(0, 2) == 12);
    assert(lct.subtree_size(0, 2) == 3);

    assert(lct.subtree_prod_excluding_child(0, 2, 4) == 7);
    assert(lct.subtree_size_excluding_child(0, 2, 4) == 2);

    lct.reroot(0);
    assert(lct.cut_parent(4));

    assert(!lct.connected(4, 0));
    assert(lct.component_prod(0) == 10);
    assert(lct.component_size(0) == 4);
    assert(lct.component_prod(4) == 5);
    assert(lct.component_size(4) == 1);

    m1une::data_structure::LinkCutTree<m1une::monoid::Add<long long>> lct2(std::vector<int>{1, 2, 3, 4, 5});
    assert(lct2.link_parent(1, 0));
    assert(lct2.link_parent(2, 0));
    assert(lct2.link_parent(3, 2));
    assert(lct2.link_parent(4, 2));
    lct2.reroot(0);

    assert(lct2.cut_parent(2));
    assert(!lct2.connected(2, 0));
    assert(lct2.component_prod(0) == 3);
    assert(lct2.component_size(0) == 2);
    assert(lct2.component_prod(2) == 12);
    assert(lct2.component_size(2) == 3);
}

bool naive_connected(const std::vector<std::vector<int>>& adj, int s, int t) {
    std::vector<int> parent(adj.size(), -1);
    std::vector<int> stack;
    parent[s] = s;
    stack.push_back(s);
    for (int it = 0; it < int(stack.size()); it++) {
        int v = stack[it];
        if (v == t) return true;
        for (int to : adj[v]) {
            if (parent[to] != -1) continue;
            parent[to] = v;
            stack.push_back(to);
        }
    }
    return false;
}

long long naive_path_sum(const std::vector<std::vector<int>>& adj, const std::vector<long long>& value, int s, int t) {
    std::vector<int> parent(adj.size(), -1);
    std::vector<int> stack;
    parent[s] = s;
    stack.push_back(s);
    for (int it = 0; it < int(stack.size()); it++) {
        int v = stack[it];
        if (v == t) break;
        for (int to : adj[v]) {
            if (parent[to] != -1) continue;
            parent[to] = v;
            stack.push_back(to);
        }
    }
    assert(parent[t] != -1);
    long long res = 0;
    for (int v = t; v != s; v = parent[v]) res += value[v];
    res += value[s];
    return res;
}

long long naive_subtree_sum(const std::vector<std::vector<int>>& adj, const std::vector<long long>& value, int root,
                            int v) {
    std::vector<int> parent(adj.size(), -1);
    std::vector<int> stack;
    parent[root] = root;
    stack.push_back(root);
    for (int it = 0; it < int(stack.size()); it++) {
        int x = stack[it];
        for (int to : adj[x]) {
            if (parent[to] != -1) continue;
            parent[to] = x;
            stack.push_back(to);
        }
    }
    assert(parent[v] != -1);

    long long res = 0;
    stack.clear();
    stack.push_back(v);
    while (!stack.empty()) {
        int x = stack.back();
        stack.pop_back();
        res += value[x];
        for (int to : adj[x]) {
            if (to == parent[x]) continue;
            stack.push_back(to);
        }
    }
    return res;
}

void test_random_vertex_sum() {
    constexpr int n = 8;
    std::vector<long long> value;
    for (int i = 0; i < n; i++) value.push_back(i + 1);
    m1une::data_structure::LinkCutTree<m1une::monoid::Add<long long>> lct(value);
    std::vector<std::vector<int>> adj(n);
    std::vector<std::pair<int, int>> edges;
    std::mt19937 rng(1);

    for (int step = 0; step < 600; step++) {
        int op = int(rng() % 5);
        int u = int(rng() % n);
        int v = int(rng() % n);
        if (op == 0) {
            if (u != v && !naive_connected(adj, u, v)) {
                assert(lct.link(u, v));
                adj[u].push_back(v);
                adj[v].push_back(u);
                edges.emplace_back(u, v);
            }
        } else if (op == 1) {
            if (!edges.empty()) {
                int id = int(rng() % edges.size());
                auto [a, b] = edges[id];
                assert(lct.cut(a, b));
                for (int i = 0; i < int(adj[a].size()); i++) {
                    if (adj[a][i] == b) {
                        adj[a][i] = adj[a].back();
                        adj[a].pop_back();
                        break;
                    }
                }
                for (int i = 0; i < int(adj[b].size()); i++) {
                    if (adj[b][i] == a) {
                        adj[b][i] = adj[b].back();
                        adj[b].pop_back();
                        break;
                    }
                }
                edges[id] = edges.back();
                edges.pop_back();
            }
        } else if (op == 2) {
            long long x = int(rng() % 200) - 100;
            value[u] = x;
            lct.set(u, x);
        } else if (u != v && naive_connected(adj, u, v)) {
            if (op == 3) {
                assert(lct.path_prod(u, v) == naive_path_sum(adj, value, u, v));
            } else {
                assert(lct.subtree_prod(u, v) == naive_subtree_sum(adj, value, u, v));
                assert(lct.subtree_prod(v, u) == naive_subtree_sum(adj, value, v, u));
            }
        }
    }
}

int main() {
    test_vertex_subtree_sum();
    test_edge_nodes_subtree();
    test_rooted_tree_utility_apis();
    test_random_vertex_sum();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
