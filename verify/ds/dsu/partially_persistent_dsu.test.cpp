#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/dsu/partially_persistent_dsu.hpp"

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

    bool merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return false;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return true;
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
    using Dsu = m1une::ds::PartiallyPersistentDsu;

    Dsu dsu(5);
    assert(dsu.size() == 5);
    assert(!dsu.empty());
    assert(dsu.time() == 0);

    assert(dsu.merge(0, 1));
    int t1 = dsu.time();
    assert(dsu.merge(2, 3));
    int t2 = dsu.time();
    assert(!dsu.merge(1, 0));
    int t3 = dsu.time();
    assert(dsu.merge(1, 2));
    int t4 = dsu.time();

    assert(t1 == 1);
    assert(t2 == 2);
    assert(t3 == 3);
    assert(t4 == 4);
    assert(!dsu.same(0, 0, 1));
    assert(dsu.same(t1, 0, 1));
    assert(!dsu.same(t1, 0, 2));
    assert(dsu.same(t2, 2, 3));
    assert(!dsu.same(t3, 0, 3));
    assert(dsu.same(t4, 0, 3));
    assert(dsu.size(t1, 0) == 2);
    assert(dsu.size(t2, 0) == 2);
    assert(dsu.size(t2, 2) == 2);
    assert(dsu.size(t4, 0) == 4);
    assert(dsu.size(0) == 4);

    std::vector<std::vector<int>> initial_groups;
    initial_groups.emplace_back(std::vector<int>{0});
    initial_groups.emplace_back(std::vector<int>{1});
    initial_groups.emplace_back(std::vector<int>{2});
    initial_groups.emplace_back(std::vector<int>{3});
    initial_groups.emplace_back(std::vector<int>{4});
    assert(dsu.groups(0) == initial_groups);

    Dsu empty;
    assert(empty.size() == 0);
    assert(empty.empty());
    assert(empty.time() == 0);

    std::mt19937 rng(1);
    constexpr int N = 30;
    Dsu pp(N);
    std::vector<NaiveDsu> states;
    states.emplace_back(N);

    for (int step = 0; step < 500; step++) {
        int u = int(rng() % N);
        int v = int(rng() % N);
        NaiveDsu next = states.back();
        bool expected_merged = next.merge(u, v);
        bool merged = pp.merge(u, v);
        assert(merged == expected_merged);
        states.push_back(next);
        assert(pp.time() == int(states.size()) - 1);

        for (int iter = 0; iter < 5; iter++) {
            int t = int(rng() % states.size());
            const NaiveDsu& expected = states[t];
            for (int i = 0; i < N; i++) {
                assert(pp.group_size(t, i) == expected.group_size(i));
                for (int j = 0; j < N; j++) {
                    assert(pp.same(t, i, j) == expected.same(i, j));
                }
            }
            assert(pp.groups(t) == expected.groups());
        }
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
