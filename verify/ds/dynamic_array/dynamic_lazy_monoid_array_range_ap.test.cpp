#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/dynamic_array/dynamic_lazy_monoid_array.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "acted_monoid/range_ap_add_range_sum.hpp"

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;
using Node = AM::value_type;
using Array = m1une::ds::DynamicLazyMonoidArray<AM>;

std::vector<long long> sums(std::vector<Node> a) {
    std::vector<long long> res;
    res.reserve(a.size());
    for (Node x : a) res.push_back(x.sum);
    return res;
}

long long sum_range(const std::vector<long long>& a, int l, int r) {
    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);
}

void assert_all_ranges(Array& a, const std::vector<long long>& expected) {
    assert(sums(a.to_vector()) == expected);
    assert(a.all_prod().sum == sum_range(expected, 0, int(expected.size())));
    for (int l = 0; l <= int(expected.size()); l++) {
        for (int r = l; r <= int(expected.size()); r++) {
            assert(a.prod(l, r).sum == sum_range(expected, l, r));
        }
    }
}

int main() {
    {
        Array a(std::vector<long long>{0, 0, 0, 0});
        a.apply(1, 4, {2, 3});
        a.insert(2, AM::make(100));
        assert_all_ranges(a, {0, 3, 100, 5, 7});

        a.apply(1, 5, {10, 0});
        assert_all_ranges(a, {0, 3, 110, 25, 37});
    }
    {
        Array a(std::vector<long long>{0, 0, 0, 0, 0});
        a.apply(0, 5, {1, 0});
        a.insert(2, AM::make(100));
        assert_all_ranges(a, {0, 1, 100, 2, 3, 4});
    }
    {
        Array a(std::vector<long long>{0, 0, 0, 0});
        a.apply(0, 4, {1, 0});
        a.reverse();
        a.insert(1, AM::make(9));
        a.apply(1, 4, {2, 1});
        assert_all_ranges(a, {3, 10, 5, 6, 0});
    }

    std::mt19937 rng(3);
    Array a;
    std::vector<long long> expected;
    for (int step = 0; step < 500; step++) {
        int op = int(rng() % 6);
        if (op == 0 || expected.empty()) {
            int pos = int(rng() % (expected.size() + 1));
            long long value = int(rng() % 101) - 50;
            a.insert(pos, AM::make(value));
            expected.insert(expected.begin() + pos, value);
        } else if (op == 1) {
            int pos = int(rng() % expected.size());
            a.erase(pos);
            expected.erase(expected.begin() + pos);
        } else if (op == 2) {
            int l = int(rng() % (expected.size() + 1));
            int r = int(rng() % (expected.size() + 1));
            if (l > r) std::swap(l, r);
            long long coef = int(rng() % 11) - 5;
            long long add = int(rng() % 21) - 10;
            a.apply(l, r, {coef, add});
            for (int i = l; i < r; i++) expected[i] += coef * (i - l) + add;
        } else if (op == 3) {
            int l = int(rng() % (expected.size() + 1));
            int r = int(rng() % (expected.size() + 1));
            if (l > r) std::swap(l, r);
            a.reverse(l, r);
            std::reverse(expected.begin() + l, expected.begin() + r);
        } else if (op == 4) {
            int l = int(rng() % (expected.size() + 1));
            int m = int(rng() % (expected.size() + 1));
            int r = int(rng() % (expected.size() + 1));
            if (l > m) std::swap(l, m);
            if (m > r) std::swap(m, r);
            if (l > m) std::swap(l, m);
            a.rotate(l, m, r);
            std::rotate(expected.begin() + l, expected.begin() + m, expected.begin() + r);
        } else {
            int pos = int(rng() % expected.size());
            long long value = int(rng() % 101) - 50;
            a.set(pos, AM::make(value));
            expected[pos] = value;
        }
        assert_all_ranges(a, expected);
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
