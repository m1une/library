#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp"

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
using Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;

std::vector<long long> sums(const std::vector<Node>& a) {
    std::vector<long long> res;
    res.reserve(a.size());
    for (Node x : a) res.push_back(x.sum);
    return res;
}

long long sum_range(const std::vector<long long>& a, int l, int r) {
    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);
}

void assert_all_ranges(const Array& a, const std::vector<long long>& expected) {
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
        Array b = a.apply(1, 4, {2, 3});
        Array c = b.insert(2, AM::make(100));
        assert_all_ranges(a, {0, 0, 0, 0});
        assert_all_ranges(b, {0, 3, 5, 7});
        assert_all_ranges(c, {0, 3, 100, 5, 7});

        Array d = c.apply(1, 5, {10, 0});
        assert_all_ranges(c, {0, 3, 100, 5, 7});
        assert_all_ranges(d, {0, 3, 110, 25, 37});
    }
    {
        Array a(std::vector<long long>{0, 0, 0, 0, 0});
        Array b = a.apply(0, 5, {1, 0});
        Array c = b.insert(2, AM::make(100));
        assert_all_ranges(b, {0, 1, 2, 3, 4});
        assert_all_ranges(c, {0, 1, 100, 2, 3, 4});
    }
    {
        Array a(std::vector<long long>{0, 0, 0, 0});
        Array b = a.apply(0, 4, {1, 0}).reverse();
        Array c = b.insert(1, AM::make(9));
        Array d = c.apply(1, 4, {2, 1});
        assert_all_ranges(b, {3, 2, 1, 0});
        assert_all_ranges(c, {3, 9, 2, 1, 0});
        assert_all_ranges(d, {3, 10, 5, 6, 0});
    }

    std::mt19937 rng(4);
    std::vector<std::pair<Array, std::vector<long long>>> versions;
    versions.push_back({Array(), {}});
    for (int step = 0; step < 300; step++) {
        int id = int(rng() % versions.size());
        Array cur = versions[id].first;
        std::vector<long long> expected = versions[id].second;
        assert_all_ranges(cur, expected);

        Array next = cur;
        std::vector<long long> next_expected = expected;
        int op = int(rng() % 7);
        if (op == 0 || next_expected.empty()) {
            int pos = int(rng() % (next_expected.size() + 1));
            long long value = int(rng() % 101) - 50;
            next = cur.insert(pos, AM::make(value));
            next_expected.insert(next_expected.begin() + pos, value);
        } else if (op == 1) {
            int pos = int(rng() % next_expected.size());
            next = cur.erase(pos);
            next_expected.erase(next_expected.begin() + pos);
        } else if (op == 2) {
            int l = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > r) std::swap(l, r);
            long long coef = int(rng() % 11) - 5;
            long long add = int(rng() % 21) - 10;
            next = cur.apply(l, r, {coef, add});
            for (int i = l; i < r; i++) next_expected[i] += coef * (i - l) + add;
        } else if (op == 3) {
            int l = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > r) std::swap(l, r);
            next = cur.reverse(l, r);
            std::reverse(next_expected.begin() + l, next_expected.begin() + r);
        } else if (op == 4) {
            int l = int(rng() % (next_expected.size() + 1));
            int m = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > m) std::swap(l, m);
            if (m > r) std::swap(m, r);
            if (l > m) std::swap(l, m);
            next = cur.rotate(l, m, r);
            std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin() + r);
        } else if (op == 5) {
            int pos = int(rng() % next_expected.size());
            long long value = int(rng() % 101) - 50;
            next = cur.set(pos, AM::make(value));
            next_expected[pos] = value;
        } else {
            next = cur.reverse();
            std::reverse(next_expected.begin(), next_expected.end());
        }

        assert_all_ranges(cur, expected);
        assert_all_ranges(next, next_expected);
        if (next_expected.size() <= 80) versions.push_back({next, next_expected});
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
