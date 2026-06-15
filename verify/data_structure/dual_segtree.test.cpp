#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "data_structure/dual_segtree.hpp"

#include <bits/stdc++.h>

#include "math/modint.hpp"
#include "monoid/affine.hpp"

using mint = m1une::math::modint998244353;
using Affine = m1une::monoid::Affine<mint>;

using namespace std;
using ll = long long;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<Affine::value_type> a(N);
    for (int i = 0; i < N; ++i) {
        ll x;
        cin >> x;
        a[i] = {0, x};
    }

    m1une::data_structure::DualSegtree<Affine> seg(a);
    assert(seg.size() == N);
    assert(seg.empty() == (N == 0));
    auto values = seg.to_vector();
    assert(int(values.size()) == N);
    for (int i = 0; i < N; i++) {
        assert(values[i].second == a[i].second);
    }
    for (int q = 0; q < Q; ++q) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            ll i;
            cin >> i;
            cout << seg.get(i).second << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
