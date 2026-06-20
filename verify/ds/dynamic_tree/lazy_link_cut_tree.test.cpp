#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/dynamic_tree/lazy_link_cut_tree.hpp"

using AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Node = AddSum::value_type;

void test_vertex_path_and_subtree_updates() {
    m1une::ds::LazyLinkCutTree<AddSum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    Node subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 14);
    assert(subtree.size == 4);
    assert(lct.subtree_size(0, 1) == 4);

    lct.apply(2, 4, 10);
    Node path = lct.path_prod(2, 4);
    assert(path.sum == 54);
    assert(path.size == 4);
    subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 54);
    assert(subtree.size == 4);
    assert(lct.get(0).sum == 1);
    assert(lct.subtree_prod(1, 3).sum == 29);

    lct.apply(0, 3, 5);
    subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 64);
    assert(subtree.size == 4);
    assert(lct.path_prod(2, 4).sum == 64);

    subtree = lct.subtree_prod(2, 1);
    assert(subtree.sum == 57);
    assert(subtree.size == 4);
}

void test_edge_path_and_subtree_updates() {
    m1une::ds::LazyLinkCutTree<AddSum> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);

    Node full = lct.subtree_prod(0, 0);
    assert(full.sum == 12);
    assert(full.size == 2);
    Node child = lct.subtree_prod(0, 1);
    assert(child.sum == 7);
    assert(child.size == 1);
    assert(lct.subtree_size(0, 1) == 3);

    lct.apply(0, 2, 3);
    assert(lct.path_prod(0, 2).sum == 18);
    assert(lct.subtree_prod(0, 1).sum == 10);

    lct.apply(1, 2, 2);
    assert(lct.get_edge(e01).sum == 8);
    assert(lct.get_edge(e12).sum == 12);
    assert(lct.subtree_prod(0, 0).sum == 20);

    assert(lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
}

void test_rooted_tree_utility_apis() {
    m1une::ds::LazyLinkCutTree<AddSum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    assert(lct.link_parent(1, 0));
    assert(lct.link_parent(2, 0));
    assert(lct.link_parent(3, 2));
    assert(lct.link_parent(4, 2));

    assert(lct.root(4) == 0);
    lct.reroot(0);

    Node component = lct.component_prod(0);
    assert(component.sum == 15);
    assert(component.size == 5);
    assert(lct.component_size(0) == 5);

    assert(lct.child_toward(0, 4) == 2);
    assert(lct.child_toward(2, 4) == 4);
    assert(lct.child_toward(4, 0) == 2);

    Node branch = lct.branch_prod(0, 4);
    assert(branch.sum == 12);
    assert(branch.size == 3);
    assert(lct.branch_size(0, 4) == 3);

    assert(lct.parent(0, 4) == 2);
    assert(lct.parent(0, 2) == 0);
    assert(lct.parent(0, 0) == -1);

    Node subtree = lct.subtree_prod(0, 2);
    assert(subtree.sum == 12);
    assert(subtree.size == 3);
    assert(lct.subtree_size(0, 2) == 3);

    Node excluding = lct.subtree_prod_excluding_child(0, 2, 4);
    assert(excluding.sum == 7);
    assert(excluding.size == 2);
    assert(lct.subtree_size_excluding_child(0, 2, 4) == 2);

    lct.reroot(0);
    assert(lct.cut_parent(4));

    assert(!lct.connected(4, 0));
    component = lct.component_prod(0);
    assert(component.sum == 10);
    assert(component.size == 4);
    assert(lct.component_size(0) == 4);
    component = lct.component_prod(4);
    assert(component.sum == 5);
    assert(component.size == 1);
    assert(lct.component_size(4) == 1);

    m1une::ds::LazyLinkCutTree<AddSum> lct2(std::vector<long long>{1, 2, 3, 4, 5});
    assert(lct2.link_parent(1, 0));
    assert(lct2.link_parent(2, 0));
    assert(lct2.link_parent(3, 2));
    assert(lct2.link_parent(4, 2));
    lct2.apply(3, 4, 10);
    lct2.reroot(0);

    assert(lct2.cut_parent(2));
    assert(!lct2.connected(2, 0));
    component = lct2.component_prod(0);
    assert(component.sum == 3);
    assert(component.size == 2);
    assert(lct2.component_size(0) == 2);
    component = lct2.component_prod(2);
    assert(component.sum == 42);
    assert(component.size == 3);
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

std::vector<int> naive_path_vertices(const std::vector<std::vector<int>>& adj, int s, int t) {
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
    std::vector<int> path;
    for (int v = t; v != s; v = parent[v]) path.push_back(v);
    path.push_back(s);
    return path;
}

long long naive_path_sum(const std::vector<std::vector<int>>& adj, const std::vector<long long>& value, int s, int t) {
    long long res = 0;
    for (int v : naive_path_vertices(adj, s, t)) res += value[v];
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

void test_random_vertex_path_updates() {
    constexpr int n = 8;
    std::vector<long long> initial;
    std::vector<long long> value;
    for (int i = 0; i < n; i++) {
        initial.push_back(i + 1);
        value.push_back(i + 1);
    }
    m1une::ds::LazyLinkCutTree<AddSum> lct(initial);
    std::vector<std::vector<int>> adj(n);
    std::vector<std::pair<int, int>> edges;
    std::mt19937 rng(2);

    for (int step = 0; step < 700; step++) {
        int op = int(rng() % 6);
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
                long long add = int(rng() % 21) - 10;
                lct.apply(u, v, add);
                for (int x : naive_path_vertices(adj, u, v)) value[x] += add;
            } else if (op == 4) {
                assert(lct.path_prod(u, v).sum == naive_path_sum(adj, value, u, v));
            } else {
                assert(lct.subtree_prod(u, v).sum == naive_subtree_sum(adj, value, u, v));
                assert(lct.subtree_prod(v, u).sum == naive_subtree_sum(adj, value, v, u));
            }
        }
    }
}

int main() {
    test_vertex_path_and_subtree_updates();
    test_edge_path_and_subtree_updates();
    test_rooted_tree_utility_apis();
    test_random_vertex_path_updates();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
