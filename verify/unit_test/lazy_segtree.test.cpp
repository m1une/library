#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>

#include "data_structure/segtree/lazy_segtree.hpp"
#include "monoid/acted_monoids/range_affine_range_sum.hpp"

#include "atcoder/modint.hpp"

using namespace std;
using namespace m1une;

using mint = atcoder::modint998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    lazy_segment_tree<range_affine_range_sum_monoid<mint>> seg(N);
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        seg.set(i, {mint(a), 1});
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, {mint(b), mint(c)});
        } else {
            int l, r;
            cin >> l >> r;
            mint ans = seg.prod(l, r).value;
            cout << ans.val() << endl;
        }
    }
}
