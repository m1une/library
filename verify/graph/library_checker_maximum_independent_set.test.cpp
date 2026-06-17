#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include <bits/stdc++.h>
using namespace std;

#include "graph/graph.hpp"
#include "graph/maximum_clique.hpp"

int main() {
    int N, M;
    cin >> N >> M;
    m1une::graph::Graph<> g(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    auto independent = m1une::graph::maximum_independent_set(g);
    cout << independent.size() << '\n';
    for (int x : independent.vertices) {
        cout << x << ' ';
    }
    cout << '\n';
}
