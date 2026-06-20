#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Node = AM::value_type;
using Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;

struct StringNoopActedMonoid {
    using value_type = std::string;
    using operator_type = int;

    static std::string id() {
        return "";
    }

    static std::string op(const std::string& a, const std::string& b) {
        return a + b;
    }

    static int op_id() {
        return 0;
    }

    static int op_comp(int f, int g) {
        return f + g;
    }

    static std::string mapping(int, const std::string& x) {
        return x;
    }
};

std::vector<Node> make_nodes(const std::vector<long long>& a) {
    std::vector<Node> res;
    res.reserve(a.size());
    for (long long x : a) res.push_back(AM::make(x));
    return res;
}

std::vector<long long> sums(const std::vector<Node>& a) {
    std::vector<long long> res;
    res.reserve(a.size());
    for (Node x : a) res.push_back(x.sum);
    return res;
}

long long sum_range(const std::vector<long long>& a, int l, int r) {
    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);
}

int main() {
    using StringArray = m1une::ds::PersistentDynamicLazyMonoidArray<StringNoopActedMonoid>;
    StringArray s = {"a", "b", "c", "d"};
    StringArray sr = s.reverse(1, 4);
    assert(s.prod(0, 4) == "abcd");
    assert(sr.to_vector() == (std::vector<std::string>{"a", "d", "c", "b"}));
    assert(sr.prod(1, 4) == "dcb");

    Array a(std::vector<long long>{1, 2, 3, 4, 5});
    Array b = a.apply(1, 4, 10);
    Array c = b.reverse(1, 5);
    Array d = c.insert(2, AM::make(100));
    Array e = d.set(0, AM::make(-1));
    Array f = e.erase(3);

    assert(sums(a.to_vector()) == (std::vector<long long>{1, 2, 3, 4, 5}));
    assert(sums(b.to_vector()) == (std::vector<long long>{1, 12, 13, 14, 5}));
    assert(sums(c.to_vector()) == (std::vector<long long>{1, 5, 14, 13, 12}));
    assert(sums(d.to_vector()) == (std::vector<long long>{1, 5, 100, 14, 13, 12}));
    assert(sums(e.to_vector()) == (std::vector<long long>{-1, 5, 100, 14, 13, 12}));
    assert(sums(f.to_vector()) == (std::vector<long long>{-1, 5, 100, 13, 12}));
    assert(b.prod(0, 5).sum == 45);
    assert(c.prod(1, 4).sum == 32);
    assert(f.all_prod().sum == 129);
    assert(f.get(2).sum == 100);
    assert(f.front().sum == -1);
    assert(f.back().sum == 12);

    auto [left, right] = f.split(3);
    assert(sums(left.to_vector()) == (std::vector<long long>{-1, 5, 100}));
    assert(sums(right.to_vector()) == (std::vector<long long>{13, 12}));
    assert(sums(left.append(right).to_vector()) == sums(f.to_vector()));
    assert(sums(f.split_off(4).to_vector()) == (std::vector<long long>{12}));
    assert(f.clear().empty());

    std::mt19937 rng(2);
    std::vector<std::pair<Array, std::vector<long long>>> versions;
    versions.push_back({Array(), {}});
    for (int step = 0; step < 300; step++) {
        int id = int(rng() % versions.size());
        Array cur = versions[id].first;
        std::vector<long long> expected = versions[id].second;
        assert(sums(cur.to_vector()) == expected);

        Array next = cur;
        std::vector<long long> next_expected = expected;
        int op = int(rng() % 9);
        if (op == 0 || next_expected.empty()) {
            int pos = int(rng() % (next_expected.size() + 1));
            long long value = int(rng() % 100) - 50;
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
            next = cur.erase(l, r);
            next_expected.erase(next_expected.begin() + l, next_expected.begin() + r);
        } else if (op == 3) {
            int pos = int(rng() % next_expected.size());
            long long value = int(rng() % 100) - 50;
            next = cur.set(pos, AM::make(value));
            next_expected[pos] = value;
        } else if (op == 4) {
            int l = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > r) std::swap(l, r);
            long long add = int(rng() % 41) - 20;
            next = cur.apply(l, r, add);
            for (int i = l; i < r; i++) next_expected[i] += add;
        } else if (op == 5) {
            int l = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > r) std::swap(l, r);
            next = cur.reverse(l, r);
            std::reverse(next_expected.begin() + l, next_expected.begin() + r);
        } else if (op == 6) {
            int l = int(rng() % (next_expected.size() + 1));
            int m = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > m) std::swap(l, m);
            if (m > r) std::swap(m, r);
            if (l > m) std::swap(l, m);
            next = cur.rotate(l, m, r);
            std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin() + r);
        } else if (op == 7 && next_expected.size() < 80) {
            int other_id = int(rng() % versions.size());
            next = cur.append(versions[other_id].first);
            next_expected.insert(next_expected.end(), versions[other_id].second.begin(), versions[other_id].second.end());
        } else {
            next = cur.reverse();
            std::reverse(next_expected.begin(), next_expected.end());
        }

        assert(sums(cur.to_vector()) == expected);
        assert(sums(next.to_vector()) == next_expected);
        assert(next.all_prod().sum == sum_range(next_expected, 0, int(next_expected.size())));
        for (int l = 0; l <= int(next_expected.size()); l++) {
            for (int r = l; r <= int(next_expected.size()); r++) {
                assert(next.prod(l, r).sum == sum_range(next_expected, l, r));
            }
        }
        if (!next_expected.empty()) {
            int pos = int(rng() % next_expected.size());
            assert(next[pos].sum == next_expected[pos]);
        }
        int split_pos = int(rng() % (next_expected.size() + 1));
        auto [prefix, suffix] = next.split(split_pos);
        assert(sums(prefix.to_vector()) == std::vector<long long>(next_expected.begin(), next_expected.begin() + split_pos));
        assert(sums(suffix.to_vector()) == std::vector<long long>(next_expected.begin() + split_pos, next_expected.end()));

        if (next_expected.size() <= 100) versions.push_back({next, next_expected});
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
