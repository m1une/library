#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

#include <bits/stdc++.h>
using namespace std;

#include "graph/graph.hpp"
#include "graph/general_matching.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    m1une::graph::GeneralMatching gm(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        gm.add_edge(u, v);
    }
    cout << gm.max_matching() << '\n';
    for (auto p : gm.matching()) {
        cout << p.from << ' ' << p.to << '\n';
    }
}
