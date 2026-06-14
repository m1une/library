#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "data_structure/persistent_dynamic_monoid_array.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

struct StringMonoid {
    using value_type = std::string;

    static std::string id() {
        return "";
    }

    static std::string op(const std::string& a, const std::string& b) {
        return a + b;
    }
};

std::string join(const std::vector<std::string>& a, int l, int r) {
    std::string res;
    for (int i = l; i < r; i++) res += a[i];
    return res;
}

int main() {
    using Array = m1une::data_structure::PersistentDynamicMonoidArray<StringMonoid>;

    Array a = {"a", "b", "c", "d", "e"};
    Array b = a.insert(2, "X");
    Array c = b.reverse(1, 5);
    Array d = c.rotate(1, 3, 6);
    Array e = d.set(0, "Z");
    Array f = e.erase(2);

    assert(a.to_vector() == (std::vector<std::string>{"a", "b", "c", "d", "e"}));
    assert(b.to_vector() == (std::vector<std::string>{"a", "b", "X", "c", "d", "e"}));
    assert(c.to_vector() == (std::vector<std::string>{"a", "d", "c", "X", "b", "e"}));
    assert(d.to_vector() == (std::vector<std::string>{"a", "X", "b", "e", "d", "c"}));
    assert(e.to_vector() == (std::vector<std::string>{"Z", "X", "b", "e", "d", "c"}));
    assert(f.to_vector() == (std::vector<std::string>{"Z", "X", "e", "d", "c"}));
    assert(c.prod(0, c.size()) == "adcXbe");
    assert(c.prod(1, 5) == "dcXb");
    assert(f.all_prod() == "ZXedc");
    assert(f.get(2) == "e");
    assert(f.front() == "Z");
    assert(f.back() == "c");

    auto [left, right] = f.split(2);
    assert(left.to_vector() == (std::vector<std::string>{"Z", "X"}));
    assert(right.to_vector() == (std::vector<std::string>{"e", "d", "c"}));
    assert(left.append(right).to_vector() == f.to_vector());
    assert(f.split_off(3).to_vector() == (std::vector<std::string>{"d", "c"}));
    assert(f.clear().empty());

    std::mt19937 rng(1);
    std::vector<std::pair<Array, std::vector<std::string>>> versions;
    versions.push_back({Array(), {}});
    for (int step = 0; step < 300; step++) {
        int id = int(rng() % versions.size());
        Array cur = versions[id].first;
        std::vector<std::string> expected = versions[id].second;
        assert(cur.to_vector() == expected);

        Array next = cur;
        std::vector<std::string> next_expected = expected;
        int op = int(rng() % 8);
        if (op == 0 || next_expected.empty()) {
            int pos = int(rng() % (next_expected.size() + 1));
            std::string value(1, char('a' + int(rng() % 26)));
            next = cur.insert(pos, value);
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
            std::string value(1, char('A' + int(rng() % 26)));
            next = cur.set(pos, value);
            next_expected[pos] = value;
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
        assert(next.all_prod() == join(next_expected, 0, int(next_expected.size())));
        for (int l = 0; l <= int(next_expected.size()); l++) {
            for (int r = l; r <= int(next_expected.size()); r++) {
                assert(next.prod(l, r) == join(next_expected, l, r));
            }
        }
        if (!next_expected.empty()) {
            int pos = int(rng() % next_expected.size());
            assert(next[pos] == next_expected[pos]);
        }
        int split_pos = int(rng() % (next_expected.size() + 1));
        auto [prefix, suffix] = next.split(split_pos);
        assert(prefix.to_vector() == std::vector<std::string>(next_expected.begin(), next_expected.begin() + split_pos));
        assert(suffix.to_vector() == std::vector<std::string>(next_expected.begin() + split_pos, next_expected.end()));

        if (next_expected.size() <= 100) versions.push_back({next, next_expected});
    }

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
