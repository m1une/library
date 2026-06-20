#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "ds/segtree/dynamic_lazy_segtree.hpp"

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

void test_range_add() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::DynamicLazySegtree<AM>;

    Seg seg(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL, AM::make(0));
    assert(seg.size() == 2'000'000'000'000'000'000ULL);
    assert(seg.node_count() == 0);
    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);

    seg.reserve(1024);
    seg.apply(-3, 5, 2);
    assert(seg.prod(-10, 10).sum == 16);
    assert(seg.get(-3).sum == 2);
    assert(seg.get(5).sum == 0);

    [[maybe_unused]] std::size_t nodes = seg.node_count();
    seg.set(0, AM::make(10));
    assert(seg.all_prod().sum == 24);
    assert(seg.max_right(-10, [](const AM::value_type& x) { return x.sum <= 5; }) == -1);
    assert(seg.min_left(10, [](const AM::value_type& x) { return x.sum <= 5; }) == 3);
    assert(seg.node_count() >= nodes);

    seg.clear();
    assert(seg.node_count() == 0);
    assert(seg.all_prod().sum == 0);
    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);
}

void test_arithmetic_progression() {
    using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;
    m1une::ds::DynamicLazySegtree<AM, int> seg(-20, 21, AM::make(0));

    AM::operator_type first;
    first.first = 2;
    first.second = 3;
    seg.apply(-5, 6, first);
    for (int p = -5; p < 6; p++) {
        assert(seg.get(p).sum == 2LL * (p + 5) + 3);
    }

    AM::operator_type second;
    second.first = -1;
    second.second = 4;
    seg.apply(-2, 4, second);
    [[maybe_unused]] long long expected = 0;
    for (int p = -20; p < 21; p++) {
        long long value = 0;
        if (-5 <= p && p < 6) value += 2LL * (p + 5) + 3;
        if (-2 <= p && p < 4) value += -(p + 2) + 4;
        expected += value;
    }
    assert(seg.all_prod().sum == expected);
}

void test_randomized() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    constexpr int left = -31;
    constexpr int right = 38;
    m1une::ds::DynamicLazySegtree<AM, int> seg(left, right, AM::make(0));
    std::vector<long long> a(right - left);

    std::uint64_t state = 1;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto value_at = [&a](int p) -> long long& {
        return a[std::size_t(p - left)];
    };

    for (int step = 0; step < 3000; step++) {
        int type = int(random() % 4);
        int l = left + int(random() % (a.size() + 1));
        int r = left + int(random() % (a.size() + 1));
        if (r < l) std::swap(l, r);

        if (type == 0) {
            long long x = static_cast<long long>(random() % 11);
            seg.apply(l, r, x);
            for (int p = l; p < r; p++) value_at(p) += x;
        } else if (type == 1) {
            int p = left + int(random() % a.size());
            long long x = static_cast<long long>(random() % 30);
            seg.set(p, AM::make(x));
            value_at(p) = x;
        } else {
            [[maybe_unused]] long long expected = 0;
            for (int p = l; p < r; p++) expected += value_at(p);
            assert(seg.prod(l, r).sum == expected);
        }

        long long limit = static_cast<long long>(random() % 150);
        int start = left + int(random() % (a.size() + 1));
        int max_right = start;
        long long sum = 0;
        while (max_right < right && sum + value_at(max_right) <= limit) {
            sum += value_at(max_right);
            max_right++;
        }
        assert(seg.max_right(start, [limit](const AM::value_type& x) {
            return x.sum <= limit;
        }) == max_right);

        int finish = left + int(random() % (a.size() + 1));
        int min_left = finish;
        sum = 0;
        while (left < min_left && value_at(min_left - 1) + sum <= limit) {
            min_left--;
            sum += value_at(min_left);
        }
        assert(seg.min_left(finish, [limit](const AM::value_type& x) {
            return x.sum <= limit;
        }) == min_left);
    }
}

void test_affine_order() {
    using mint = m1une::math::modint998244353;
    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;
    constexpr int n = 37;
    m1une::ds::DynamicLazySegtree<AM, int> seg(0, n, AM::make(1));
    std::vector<mint> a(n, 1);

    std::uint64_t state = 11;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int step = 0; step < 1200; step++) {
        int l = int(random() % (n + 1));
        int r = int(random() % (n + 1));
        if (r < l) std::swap(l, r);
        mint b = mint(int(random() % 7));
        mint c = mint(int(random() % 7));
        AM::operator_type f;
        f.first = b;
        f.second = c;
        seg.apply(l, r, f);
        for (int p = l; p < r; p++) a[p] = b * a[p] + c;

        int ql = int(random() % (n + 1));
        int qr = int(random() % (n + 1));
        if (qr < ql) std::swap(ql, qr);
        mint expected = 0;
        for (int p = ql; p < qr; p++) expected += a[p];
        assert(seg.prod(ql, qr).sum == expected);
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_range_add();
    test_arithmetic_progression();
    test_randomized();
    test_affine_order();

    using mint = m1une::math::modint998244353;
    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;

    int n, q;
    std::cin >> n >> q;
    m1une::ds::DynamicLazySegtree<AM, int> seg(0, n, AM::make(0));
    seg.reserve(std::size_t(4) * std::size_t(n + q));

    for (int i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        seg.set(i, AM::make(mint(x)));
    }

    for (int query = 0; query < q; query++) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int l, r;
            long long b, c;
            std::cin >> l >> r >> b >> c;
            AM::operator_type f;
            f.first = mint(b);
            f.second = mint(c);
            seg.apply(l, r, f);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.prod(l, r).sum << '\n';
        }
    }
}
