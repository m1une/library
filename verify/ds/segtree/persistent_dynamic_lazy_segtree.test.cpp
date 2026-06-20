#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/segtree/persistent_dynamic_lazy_segtree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"
#include "acted_monoid/range_affine_range_sum.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include "math/modint.hpp"

namespace {

void test_versions() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM, int>;

    Seg base(-30, 40, AM::make(0));
    base.reserve(20000);
    Seg first = base.apply(-10, 20, 3);
    Seg second = first.set(0, AM::make(100));
    Seg branch = base.apply(5, 15, 7);

    assert(base.all_prod().sum == 0);
    assert(first.all_prod().sum == 90);
    assert(second.all_prod().sum == 187);
    assert(branch.all_prod().sum == 70);
    assert(first.get(0).sum == 3);
    assert(second.get(0).sum == 100);
    assert(branch.get(0).sum == 0);
    assert(second.max_right(-30, [](const AM::value_type& x) {
        return x.sum <= 20;
    }) == -4);
    assert(second.min_left(40, [](const AM::value_type& x) {
        return x.sum <= 20;
    }) == 14);
    assert(base.node_count() == branch.node_count());
}

void test_arithmetic_progression() {
    using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM, int>;

    Seg base(-20, 21, AM::make(0));
    AM::operator_type f;
    f.first = 3;
    f.second = 2;
    Seg next = base.apply(-7, 8, f);

    assert(base.all_prod().sum == 0);
    for (int p = -7; p < 8; p++) {
        assert(next.get(p).sum == 3LL * (p + 7) + 2);
    }
}

void test_randomized() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM, int>;
    constexpr int left = -17;
    constexpr int right = 24;

    std::vector<Seg> versions;
    versions.emplace_back(left, right, AM::make(0));
    std::vector<std::vector<long long>> expected(1, std::vector<long long>(right - left));

    std::uint64_t state = 5;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int step = 0; step < 800; step++) {
        std::size_t from = std::size_t(random() % versions.size());
        std::vector<long long> next = expected[from];
        int l = left + int(random() % (next.size() + 1));
        int r = left + int(random() % (next.size() + 1));
        if (r < l) std::swap(l, r);

        Seg tree = versions[from];
        if (random() & 1) {
            long long x = static_cast<long long>(random() % 10);
            tree = tree.apply(l, r, x);
            for (int p = l; p < r; p++) next[std::size_t(p - left)] += x;
        } else {
            int p = left + int(random() % next.size());
            long long x = static_cast<long long>(random() % 30);
            tree = tree.set(p, AM::make(x));
            next[std::size_t(p - left)] = x;
        }
        versions.push_back(tree);
        expected.push_back(next);

        std::size_t check = std::size_t(random() % versions.size());
        int ql = left + int(random() % (next.size() + 1));
        int qr = left + int(random() % (next.size() + 1));
        if (qr < ql) std::swap(ql, qr);
        [[maybe_unused]] long long sum = 0;
        for (int p = ql; p < qr; p++) sum += expected[check][std::size_t(p - left)];
        assert(versions[check].prod(ql, qr).sum == sum);
    }
}

void test_affine_order() {
    using mint = m1une::math::modint998244353;
    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM, int>;

    Seg base(0, 20, AM::make(1));
    AM::operator_type first;
    first.first = mint(2);
    first.second = mint(3);
    Seg version1 = base.apply(2, 18, first);

    AM::operator_type second;
    second.first = mint(5);
    second.second = mint(7);
    Seg version2 = version1.apply(8, 14, second);

    assert(base.get(10).sum == mint(1));
    assert(version1.get(10).sum == mint(5));
    assert(version2.get(10).sum == mint(32));
    assert(version2.get(4).sum == mint(5));
}

}  // namespace

int main() {
    test_versions();
    test_arithmetic_progression();
    test_randomized();
    test_affine_order();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
