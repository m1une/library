#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <bits/stdc++.h>
using namespace std;

#include "ds/union_find/persistent_dsu.hpp"
using namespace m1une::ds;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<PersistentDsu> dsus;
    dsus.push_back(PersistentDsu(N));
    while (Q--) {
        int t, k, u, v;
        cin >> t >> k >> u >> v;
        if (t == 0) {
            dsus.push_back(dsus[k + 1].merge(u, v));
        } else {
            cout << int(dsus[k + 1].same(u, v)) << '\n';
            dsus.push_back(PersistentDsu(0));
        }
    }
}
