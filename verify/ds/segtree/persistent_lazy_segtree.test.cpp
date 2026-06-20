#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/segtree/persistent_lazy_segtree.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../../acted_monoid/range_add_range_sum.hpp"

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentLazySegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});
    Seg seg1 = seg.apply(1, 4, 10);
    Seg seg2 = seg1.set(2, AM::make(100));
    Seg seg3 = seg2.apply(0, 5, -1);

    auto check = [](const Seg& tree, const std::vector<long long>& a) {
        assert(tree.size() == int(a.size()));
        assert(tree.empty() == a.empty());
        auto values = tree.to_vector();
        assert(int(values.size()) == int(a.size()));
        auto middle = tree.to_vector(1, 4);
        assert(int(middle.size()) == 3);
        long long total = 0;
        for (long long x : a) total += x;
        assert(tree.all_prod().sum == total);
        for (int l = 0; l <= int(a.size()); l++) {
            long long sum = 0;
            for (int r = l; r <= int(a.size()); r++) {
                assert(tree.prod(l, r).sum == sum);
                if (r < int(a.size())) sum += a[r];
            }
        }
        for (int i = 0; i < int(a.size()); i++) {
            assert(tree.get(i).sum == a[i]);
            assert(tree[i].sum == a[i]);
            assert(values[i].sum == a[i]);
            if (1 <= i && i < 4) assert(middle[i - 1].sum == a[i]);
        }
    };

    check(seg, {1, 2, 3, 4, 5});
    check(seg1, {1, 12, 13, 14, 5});
    check(seg2, {1, 12, 100, 14, 5});
    check(seg3, {0, 11, 99, 13, 4});

    assert(seg.prod(0, 5).sum == 15);
    assert(seg1.prod(0, 5).sum == 45);
    assert(seg2.prod(0, 5).sum == 132);
    assert(seg3.prod(0, 5).sum == 127);
    assert(seg.get(2).sum == 3);
    assert(seg1.get(2).sum == 13);
    assert(seg2.get(2).sum == 100);
    assert(seg3.get(2).sum == 99);
    assert(seg1.max_right(0, [](const AM::value_type& x) { return x.sum <= 26; }) == 3);
    assert(seg1.min_left(5, [](const AM::value_type& x) { return x.sum <= 19; }) == 3);

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
