#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"

#include "../../../ds/dsu/persistent_potentialized_dsu.hpp"
#include "../../../monoid/add.hpp"
#include "../../../monoid/xor.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

template <class Group>
struct NaivePotentializedDsu {
    using T = typename Group::value_type;

    std::vector<int> parent_or_size;
    std::vector<T> diff_to_parent;

    explicit NaivePotentializedDsu(int n = 0) : parent_or_size(n, -1), diff_to_parent(n, Group::id()) {}

    std::pair<int, T> leader_and_potential(int a) const {
        T res = Group::id();
        while (parent_or_size[a] >= 0) {
            res = Group::op(diff_to_parent[a], res);
            a = parent_or_size[a];
        }
        return {a, res};
    }

    int leader(int a) const {
        return leader_and_potential(a).first;
    }

    bool same(int a, int b) const {
        return leader(a) == leader(b);
    }

    int group_size(int a) const {
        return -parent_or_size[leader(a)];
    }

    T potential(int a) const {
        return leader_and_potential(a).second;
    }

    T diff(int a, int b) const {
        assert(same(a, b));
        return Group::op(Group::inv(potential(a)), potential(b));
    }

    std::pair<NaivePotentializedDsu, bool> merge(int a, int b, const T& w) const {
        NaivePotentializedDsu res = *this;
        auto [x, pa] = res.leader_and_potential(a);
        auto [y, pb] = res.leader_and_potential(b);
        if (x == y) return {res, Group::op(Group::inv(pa), pb) == w};

        int sx = -res.parent_or_size[x];
        int sy = -res.parent_or_size[y];
        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
            y_from_x = Group::inv(y_from_x);
        }
        res.parent_or_size[x] += res.parent_or_size[y];
        res.parent_or_size[y] = x;
        res.diff_to_parent[y] = y_from_x;
        return {res, true};
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

void self_test() {
    using Add = m1une::monoid::Add<long long>;
    using AddDsu = m1une::ds::PersistentPotentializedDsu<Add>;

    AddDsu base(5);
    auto [a, ok1] = base.merge(0, 1, 3);
    auto [b, ok2] = a.merge(1, 2, 4);
    auto [c, ok3] = b.merge(3, 4, -2);
    auto [d, ok4] = b.merge(2, 3, 5);
    auto [bad, ok_bad] = b.merge(0, 2, 8);

    assert(ok1);
    assert(ok2);
    assert(ok3);
    assert(ok4);
    assert(!ok_bad);
    assert(base.size() == 5);
    assert(!base.empty());
    assert(!base.same(0, 2));
    assert(a.same(0, 1));
    assert(!a.same(0, 2));
    assert(b.diff(0, 2) == 7);
    assert(b.diff(2, 0) == -7);
    assert(c.diff(3, 4) == -2);
    assert(!c.same(0, 4));
    assert(d.diff(0, 3) == 12);
    assert(bad.diff(0, 2) == 7);
    assert(d.group_size(0) == 4);
    assert(d.size(0) == 4);
    assert(base.group_size(0) == 1);
    assert(base.parent_or_size(0) == -1);

    std::vector<std::vector<int>> base_groups;
    base_groups.emplace_back(std::vector<int>{0});
    base_groups.emplace_back(std::vector<int>{1});
    base_groups.emplace_back(std::vector<int>{2});
    base_groups.emplace_back(std::vector<int>{3});
    base_groups.emplace_back(std::vector<int>{4});
    assert(base.groups() == base_groups);

    using Xor = m1une::monoid::Xor<int>;
    m1une::ds::PersistentPotentializedDsu<Xor> xor_base(4);
    auto [xor_a, xor_ok1] = xor_base.merge(0, 1, 5);
    auto [xor_b, xor_ok2] = xor_a.merge(1, 2, 6);
    auto [xor_bad, xor_ok_bad] = xor_b.merge(0, 2, 2);
    assert(xor_ok1);
    assert(xor_ok2);
    assert(!xor_ok_bad);
    assert(xor_b.diff(0, 2) == (5 ^ 6));
    assert(xor_bad.diff(0, 2) == (5 ^ 6));

    AddDsu empty;
    assert(empty.size() == 0);
    assert(empty.empty());

    std::mt19937 rng(0);
    constexpr int N = 25;
    std::vector<std::pair<AddDsu, NaivePotentializedDsu<Add>>> versions;
    versions.emplace_back(AddDsu(N), NaivePotentializedDsu<Add>(N));

    for (int step = 0; step < 400; step++) {
        int id = int(rng() % versions.size());
        AddDsu cur = versions[id].first;
        NaivePotentializedDsu<Add> expected = versions[id].second;

        for (int i = 0; i < N; i++) {
            assert(cur.group_size(i) == expected.group_size(i));
            assert(cur.parent_or_size(i) == expected.parent_or_size[i]);
            for (int j = 0; j < N; j++) {
                assert(cur.same(i, j) == expected.same(i, j));
                if (cur.same(i, j)) assert(cur.diff(i, j) == expected.diff(i, j));
            }
        }
        assert(cur.groups() == expected.groups());

        int u = int(rng() % N);
        int v = int(rng() % N);
        long long w = int(rng() % 21) - 10;
        if (expected.same(u, v) && (rng() & 1)) w = expected.diff(u, v);

        auto [next, ok] = cur.merge(u, v, w);
        auto [next_expected, expected_ok] = expected.merge(u, v, w);
        assert(ok == expected_ok);

        for (int i = 0; i < N; i++) {
            assert(cur.group_size(i) == expected.group_size(i));
            assert(next.group_size(i) == next_expected.group_size(i));
            assert(next.parent_or_size(i) == next_expected.parent_or_size[i]);
        }

        versions.emplace_back(next, next_expected);
    }
}

int main() {
    self_test();

    using Add = m1une::monoid::Add<long long>;
    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    Dsu dsu(n);

    while (q--) {
        int type, x, y;
        std::cin >> type >> x >> y;
        if (type == 0) {
            long long z;
            std::cin >> z;
            auto [next, ok] = dsu.merge(x, y, z);
            (void)ok;
            dsu = next;
        } else {
            if (dsu.same(x, y)) {
                std::cout << dsu.diff(x, y) << '\n';
            } else {
                std::cout << "?\n";
            }
        }
    }
}
