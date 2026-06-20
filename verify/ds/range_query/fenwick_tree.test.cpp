#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../../ds/range_query/fenwick_tree.hpp"

void test_fenwick_tree() {
    const std::vector<long long> values = {1, 2, 3};
    m1une::ds::FenwickTree<long long> tree(values);

    assert(tree.size() == 3);
    assert(!tree.empty());
    assert(tree.sum(0) == 0);
    assert(tree.sum(3) == 6);
    assert(tree.sum(1, 3) == 5);
    assert(tree.lower_bound(0) == 0);
    assert(tree.lower_bound(1) == 1);
    assert(tree.lower_bound(3) == 2);
    assert(tree.lower_bound(6) == 3);
    assert(tree.lower_bound(7) == 4);

    m1une::ds::FenwickTree<long long> empty;
    assert(empty.empty());
    assert(empty.lower_bound(1) == 1);
}

int main() {
    test_fenwick_tree();

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) {
        std::cin >> value;
    }

    m1une::ds::FenwickTree<long long> tree(values);
    for (int query = 0; query < q; ++query) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int p;
            long long x;
            std::cin >> p >> x;
            tree.add(p, x);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << tree.sum(l, r) << '\n';
        }
    }
}
