#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "data_structure/persistent_dual_segtree.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::data_structure::PersistentDualSegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});
    Seg seg1 = seg.apply(1, 4, 10);
    Seg seg2 = seg1.set(2, AM::make(100));
    Seg seg3 = seg2.apply(0, 5, -1);
    Seg seg4 = seg3.apply(3, 7);

    auto check = [](const Seg& tree, const std::vector<long long>& a) {
        assert(tree.size() == int(a.size()));
        assert(tree.empty() == a.empty());
        auto values = tree.to_vector();
        assert(int(values.size()) == int(a.size()));
        auto middle = tree.to_vector(1, 4);
        assert(int(middle.size()) == 3);
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
    check(seg4, {0, 11, 99, 20, 4});

    assert(seg.get(2).sum == 3);
    assert(seg1.get(2).sum == 13);
    assert(seg2.get(2).sum == 100);
    assert(seg3.get(2).sum == 99);
    assert(seg4.get(3).sum == 20);

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
