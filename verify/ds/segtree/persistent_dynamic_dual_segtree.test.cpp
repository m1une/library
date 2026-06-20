#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/segtree/persistent_dynamic_dual_segtree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

#include "../../../monoid/add.hpp"
#include "../../../monoid/update.hpp"

namespace {

void test_versions() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add, int>;

    Seg base(-50, 60, 5);
    base.reserve(20000);
    Seg first = base.apply(-10, 20, 3);
    Seg second = first.set(0, 100);
    Seg branch = base.apply(5, 15, 7);

    assert(base.get(0) == 5);
    assert(first.get(0) == 8);
    assert(second.get(0) == 100);
    assert(branch.get(0) == 5);
    assert(first.get(-20) == 5);
    assert(branch.get(10) == 12);
    assert(base.node_count() == branch.node_count());
}

void test_update_order() {
    using Update = m1une::monoid::Update<int>;
    using Seg = m1une::ds::PersistentDynamicDualSegtree<Update, int>;

    Seg base(-10, 11, std::optional<int>(1));
    Seg first = base.apply(-5, 6, std::optional<int>(2));
    Seg second = first.apply(-2, 3, std::optional<int>(4));

    assert(base.get(0).value() == 1);
    assert(first.get(0).value() == 2);
    assert(second.get(0).value() == 4);
    assert(second.get(4).value() == 2);
    assert(second.get(8).value() == 1);
}

void test_randomized() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add, int>;
    constexpr int left = -23;
    constexpr int right = 29;

    std::vector<Seg> versions;
    versions.emplace_back(left, right, 4);
    std::vector<std::vector<long long>> expected(
        1,
        std::vector<long long>(right - left, 4)
    );

    std::uint64_t state = 9;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int step = 0; step < 1200; step++) {
        std::size_t from = std::size_t(random() % versions.size());
        std::vector<long long> next = expected[from];
        Seg tree = versions[from];

        if (random() & 1) {
            int l = left + int(random() % (next.size() + 1));
            int r = left + int(random() % (next.size() + 1));
            if (r < l) std::swap(l, r);
            long long x = static_cast<long long>(random() % 20);
            tree = tree.apply(l, r, x);
            for (int p = l; p < r; p++) next[std::size_t(p - left)] += x;
        } else {
            int p = left + int(random() % next.size());
            long long x = static_cast<long long>(random() % 100);
            tree = tree.set(p, x);
            next[std::size_t(p - left)] = x;
        }

        versions.push_back(tree);
        expected.push_back(next);
        [[maybe_unused]] std::size_t check = std::size_t(random() % versions.size());
        [[maybe_unused]] int p = left + int(random() % next.size());
        assert(versions[check].get(p) == expected[check][std::size_t(p - left)]);
    }
}

}  // namespace

int main() {
    test_versions();
    test_update_order();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
