#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
#include "../../../ds/dsu/dsu.hpp"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    m1une::ds::Dsu dsu(N);
    for (int q = 0; q < Q; ++q) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            dsu.merge(u, v);
        } else {
            cout << (int)dsu.same(u, v) << '\n';
        }
    }
}
