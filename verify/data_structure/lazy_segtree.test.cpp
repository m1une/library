#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "data_structure/lazy_segtree.hpp"

#include <bits/stdc++.h>

#include "acted_monoid/range_affine_range_sum.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;

using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;

using namespace std;
using ll = long long;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    m1une::data_structure::LazySegtree<AM> seg(a);
    for (int q = 0; q < Q; ++q) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            ll l, r;
            cin >> l >> r;
            auto prd = seg.prod(l, r);
            cout << prd.sum << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
