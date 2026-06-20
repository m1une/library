#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/graph.hpp"
#include "../../tree/sparse_table_lca.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    m1une::graph::Graph<> g(N);
    for (int i = 1; i < N; ++i) {
        int p;
        cin >> p;
        g.add_edge(p, i);
    }
    m1une::tree::SparseTableLca<> lca(g, 0);
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << '\n';
    }
}
