#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <bits/stdc++.h>
using namespace std;

#include "acted_monoid/range_affine_range_sum.hpp"
#include "data_structure/dynamic_lazy_monoid_array.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;
using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;
using Array = m1une::data_structure::DynamicLazyMonoidArray<AM>;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    Array ary(a);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, x;
            cin >> i >> x;
            ary.insert(i, AM::make(x));
        } else if (t == 1) {
            int i;
            cin >> i;
            ary.erase(i);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            ary.reverse(l, r);
        } else if (t == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            ary.apply(l, r, {b, c});
        } else {
            int l, r;
            cin >> l >> r;
            cout << ary.prod(l, r).sum << '\n';
        }
    }
}
