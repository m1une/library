#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/segment_tree/persistent_segtree.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "monoid/add.hpp"

int main() {
    using Seg = m1une::ds::PersistentSegtree<m1une::monoid::Add<long long>>;

    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});
    Seg seg1 = seg.set(2, 10);
    Seg seg2 = seg1.set(0, -1);

    auto check = [](const Seg& tree, const std::vector<long long>& a) {
        assert(tree.size() == int(a.size()));
        assert(tree.empty() == a.empty());
        assert(tree.to_vector() == a);
        assert(tree.to_vector(1, 4) == std::vector<long long>(a.begin() + 1, a.begin() + 4));
        long long total = 0;
        for (long long x : a) total += x;
        assert(tree.all_prod() == total);
        for (int l = 0; l <= int(a.size()); l++) {
            long long sum = 0;
            for (int r = l; r <= int(a.size()); r++) {
                assert(tree.prod(l, r) == sum);
                if (r < int(a.size())) sum += a[r];
            }
        }
        for (int i = 0; i < int(a.size()); i++) {
            assert(tree.get(i) == a[i]);
            assert(tree[i] == a[i]);
        }
    };

    check(seg, {1, 2, 3, 4, 5});
    check(seg1, {1, 2, 10, 4, 5});
    check(seg2, {-1, 2, 10, 4, 5});

    assert(seg.prod(0, 5) == 15);
    assert(seg1.prod(0, 5) == 22);
    assert(seg2.prod(0, 5) == 20);
    assert(seg.get(2) == 3);
    assert(seg1.get(2) == 10);
    assert(seg2.get(0) == -1);
    assert(seg1.max_right(0, [](long long x) { return x <= 13; }) == 3);
    assert(seg1.min_left(5, [](long long x) { return x <= 9; }) == 3);

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
