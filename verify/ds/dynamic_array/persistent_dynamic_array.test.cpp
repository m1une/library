#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/dynamic_array/persistent_dynamic_array.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

int main() {
    using Array = m1une::ds::PersistentDynamicArray<int>;

    Array a = {1, 2, 3, 4, 5};
    Array b = a.insert(2, 10);
    Array c = b.erase(4);
    Array d = c.reverse(1, 4);
    Array e = d.rotate(1, 3, 5);
    Array f = e.set(0, -1);
    Array g = f.push_front(-2).push_back(6);
    Array h = g.erase(2, 5);
    Array i = h.append(Array({7, 8}));

    assert(a.to_vector() == (std::vector<int>{1, 2, 3, 4, 5}));
    assert(b.to_vector() == (std::vector<int>{1, 2, 10, 3, 4, 5}));
    assert(c.to_vector() == (std::vector<int>{1, 2, 10, 3, 5}));
    assert(d.to_vector() == (std::vector<int>{1, 3, 10, 2, 5}));
    assert(e.to_vector() == (std::vector<int>{1, 2, 5, 3, 10}));
    assert(f.to_vector() == (std::vector<int>{-1, 2, 5, 3, 10}));
    assert(g.to_vector() == (std::vector<int>{-2, -1, 2, 5, 3, 10, 6}));
    assert(h.to_vector() == (std::vector<int>{-2, -1, 10, 6}));
    assert(i.to_vector() == (std::vector<int>{-2, -1, 10, 6, 7, 8}));

    assert(a.to_vector(1, 4) == (std::vector<int>{2, 3, 4}));
    assert(i.size() == 6);
    assert(!i.empty());
    assert(i.front() == -2);
    assert(i.back() == 8);
    assert(i[2] == 10);
    assert(i.get(3) == 6);

    auto [left, right] = i.split(3);
    assert(left.to_vector() == (std::vector<int>{-2, -1, 10}));
    assert(right.to_vector() == (std::vector<int>{6, 7, 8}));
    assert(i.split_off(4).to_vector() == (std::vector<int>{7, 8}));
    assert(left.append(right).to_vector() == i.to_vector());
    assert(i.clear().empty());

    Array base = {1, 2, 3};
    const int& stable_reference = base[1];
    Array pointer_growth = base;
    for (int x = 0; x < 1000; x++) pointer_growth = pointer_growth.push_back(x);
    Array j = base.append(base);
    assert(j.to_vector() == (std::vector<int>{1, 2, 3, 1, 2, 3}));
    assert(j.reverse().to_vector() == (std::vector<int>{3, 2, 1, 3, 2, 1}));
    assert(base.to_vector() == (std::vector<int>{1, 2, 3}));
    assert(stable_reference == 2);
    assert(pointer_growth.size() == 1003);

    std::mt19937 rng(0);
    std::vector<std::pair<Array, std::vector<int>>> versions;
    versions.push_back({Array(), {}});
    for (int step = 0; step < 300; step++) {
        int id = int(rng() % versions.size());
        const Array cur = versions[id].first;
        std::vector<int> expected = versions[id].second;
        assert(cur.to_vector() == expected);

        Array next = cur;
        std::vector<int> next_expected = expected;
        int op = int(rng() % 8);
        if (op == 0 || next_expected.empty()) {
            int pos = int(rng() % (next_expected.size() + 1));
            int val = int(rng() % 1000) - 500;
            next = cur.insert(pos, val);
            next_expected.insert(next_expected.begin() + pos, val);
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
            int val = int(rng() % 1000) - 500;
            next = cur.set(pos, val);
            next_expected[pos] = val;
        } else if (op == 4) {
            int l = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > r) std::swap(l, r);
            next = cur.reverse(l, r);
            std::reverse(next_expected.begin() + l, next_expected.begin() + r);
        } else if (op == 5) {
            int l = int(rng() % (next_expected.size() + 1));
            int m = int(rng() % (next_expected.size() + 1));
            int r = int(rng() % (next_expected.size() + 1));
            if (l > m) std::swap(l, m);
            if (m > r) std::swap(m, r);
            if (l > m) std::swap(l, m);
            next = cur.rotate(l, m, r);
            std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin() + r);
        } else if (op == 6 && next_expected.size() < 80) {
            int other_id = int(rng() % versions.size());
            next = cur.append(versions[other_id].first);
            next_expected.insert(next_expected.end(), versions[other_id].second.begin(), versions[other_id].second.end());
        } else {
            next = cur.reverse();
            std::reverse(next_expected.begin(), next_expected.end());
        }

        assert(cur.to_vector() == expected);
        assert(next.to_vector() == next_expected);
        if (!next_expected.empty()) {
            int pos = int(rng() % next_expected.size());
            assert(next[pos] == next_expected[pos]);
            assert(next.get(pos) == next_expected[pos]);
        }
        int split_pos = int(rng() % (next_expected.size() + 1));
        auto [prefix, suffix] = next.split(split_pos);
        assert(prefix.to_vector() == std::vector<int>(next_expected.begin(), next_expected.begin() + split_pos));
        assert(suffix.to_vector() == std::vector<int>(next_expected.begin() + split_pos, next_expected.end()));
        assert(prefix.append(suffix).to_vector() == next_expected);

        if (next_expected.size() <= 100) {
            versions.push_back({next, next_expected});
        }
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
