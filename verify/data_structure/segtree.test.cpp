#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "data_structure/segtree.hpp"
#include "monoid/add.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();
    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    m1une::data_structure::Segtree<m1une::monoid::Add<long long>> seg(a);
    assert(seg.size() == n);
    assert(seg.empty() == (n == 0));
    assert(seg.to_vector() == a);
    for (int i = 0; i < n; i++) assert(seg[i] == a[i]);

    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int p;
            long long x;
            std::cin >> p >> x;
            seg.set(p, seg.get(p) + x);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.prod(l, r) << "\n";
        }
    }

    return 0;
}
