#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "data_structure/persistent_dsu.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

struct NaiveDsu {
    std::vector<int> parent_or_size;

    explicit NaiveDsu(int n = 0) : parent_or_size(n, -1) {}

    int leader(int a) const {
        while (parent_or_size[a] >= 0) a = parent_or_size[a];
        return a;
    }

    bool same(int a, int b) const {
        return leader(a) == leader(b);
    }

    int group_size(int a) const {
        return -parent_or_size[leader(a)];
    }

    NaiveDsu merge(int a, int b) const {
        NaiveDsu res = *this;
        int x = res.leader(a), y = res.leader(b);
        if (x == y) return res;
        if (-res.parent_or_size[x] < -res.parent_or_size[y]) std::swap(x, y);
        res.parent_or_size[x] += res.parent_or_size[y];
        res.parent_or_size[y] = x;
        return res;
    }

    std::vector<std::vector<int>> groups() const {
        int n = int(parent_or_size.size());
        std::vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
        for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);
        result.erase(std::remove_if(result.begin(), result.end(), [](const std::vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }
};

int main() {
    using Dsu = m1une::data_structure::PersistentDsu;

    Dsu dsu(5);
    Dsu a = dsu.merge(0, 1);
    Dsu b = a.merge(2, 3);
    Dsu c = b.merge(1, 2);
    Dsu d = c.merge(3, 4);

    assert(dsu.size() == 5);
    assert(!dsu.empty());
    assert(dsu.same(0, 1) == false);
    assert(a.same(0, 1) == true);
    assert(a.same(0, 2) == false);
    assert(b.same(2, 3) == true);
    assert(c.same(0, 3) == true);
    assert(c.same(0, 4) == false);
    assert(d.same(0, 4) == true);
    assert(d.group_size(0) == 5);
    assert(d.size(0) == 5);
    assert(a.group_size(0) == 2);
    assert(dsu.group_size(0) == 1);
    assert(dsu.groups() == (std::vector<std::vector<int>>{{0}, {1}, {2}, {3}, {4}}));
    assert(c.groups() == (std::vector<std::vector<int>>{{0, 1, 2, 3}, {4}}));

    Dsu empty;
    assert(empty.size() == 0);
    assert(empty.empty());

    std::mt19937 rng(0);
    constexpr int N = 30;
    std::vector<std::pair<Dsu, NaiveDsu>> versions;
    versions.push_back({Dsu(N), NaiveDsu(N)});

    for (int step = 0; step < 500; step++) {
        int id = int(rng() % versions.size());
        const Dsu cur = versions[id].first;
        const NaiveDsu expected = versions[id].second;

        for (int i = 0; i < N; i++) {
            assert(cur.group_size(i) == expected.group_size(i));
            assert(cur.get(i) == expected.parent_or_size[i]);
            for (int j = 0; j < N; j++) {
                assert(cur.same(i, j) == expected.same(i, j));
            }
        }
        assert(cur.groups() == expected.groups());

        int u = int(rng() % N);
        int v = int(rng() % N);
        Dsu next = cur.merge(u, v);
        NaiveDsu next_expected = expected.merge(u, v);

        for (int i = 0; i < N; i++) {
            assert(cur.group_size(i) == expected.group_size(i));
            assert(next.group_size(i) == next_expected.group_size(i));
            assert(next.get(i) == next_expected.parent_or_size[i]);
        }

        versions.push_back({next, next_expected});
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
