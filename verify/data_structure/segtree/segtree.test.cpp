#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "data_structure/segtree/segtree.hpp"

#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "math/affine.hpp"
#include "monoid/monoids/affine_monoid.hpp"

using mint = atcoder::modint998244353;
using namespace std;
using namespace m1une;

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();
    int N, Q;
    cin >> N >> Q;
    vector<pair<mint, mint>> f(N);
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        f[i] = {a, b};
    }
    segment_tree<affine_monoid<mint>> seg(f);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            seg.set(p, {c, d});
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            cout << affine(seg.prod(l, r), mint(x)).val() << "\n";
        }
    }
}
