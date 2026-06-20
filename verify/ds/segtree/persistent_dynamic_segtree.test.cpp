#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/segtree/persistent_dynamic_segtree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../../../monoid/add.hpp"

namespace {

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& a, const value_type& b) {
        return a + b;
    }
};

void test_versions() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;

    Seg base(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL, 0);
    base.reserve(4096);
    Seg first = base.set(-3, 2);
    Seg second = first.set(2, 4);
    Seg branch = base.set(7, 10);

    assert(base.size() == 2'000'000'000'000'000'000ULL);
    assert(base.node_count() == branch.node_count());
    assert(base.all_prod() == 0);
    assert(first.all_prod() == 2);
    assert(second.all_prod() == 6);
    assert(branch.all_prod() == 10);
    assert(base.get(-3) == 0);
    assert(first.get(-3) == 2);
    assert(second.get(2) == 4);
    assert(branch.get(7) == 10);
    assert(second.prod(-4, 3) == 6);
    assert(second.max_right(-8, [](long long x) { return x <= 3; }) == 2);
    assert(second.min_left(8, [](long long x) { return x <= 4; }) == -2);
}

void test_uniform_and_non_commutative() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum, int>;

    Seg uniform(-5, 6, 3);
    assert(uniform.all_prod() == 33);
    assert(uniform.prod(-2, 4) == 18);
    Seg changed = uniform.set(0, 10);
    assert(uniform.all_prod() == 33);
    assert(changed.all_prod() == 40);

    m1une::ds::PersistentDynamicSegtree<Concat, int> text(-2, 3, "x");
    auto first = text.set(1, "a");
    auto second = first.set(-1, "b");
    assert(text.all_prod() == "xxxxx");
    assert(first.all_prod() == "xxxax");
    assert(second.all_prod() == "xbxax");
}

void test_extreme_coordinates() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;

    constexpr long long left = std::numeric_limits<long long>::min();
    constexpr long long right = std::numeric_limits<long long>::max();
    Seg base(left, right);
    Seg first = base.set(left, 3);
    Seg second = first.set(right - 1, 4);

    assert(base.size() == std::numeric_limits<unsigned long long>::max());
    assert(base.all_prod() == 0);
    assert(first.get(left) == 3);
    assert(second.get(right - 1) == 4);
    assert(second.all_prod() == 7);
}

void test_randomized() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum, int>;
    constexpr int left = -29;
    constexpr int right = 37;

    std::vector<Seg> versions;
    versions.emplace_back(left, right, 1);
    std::vector<std::vector<long long>> expected(
        1,
        std::vector<long long>(right - left, 1)
    );

    std::uint64_t state = 13;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int step = 0; step < 1500; step++) {
        std::size_t from = std::size_t(random() % versions.size());
        int p = left + int(random() % expected[from].size());
        long long x = static_cast<long long>(random() % 20);

        versions.push_back(versions[from].set(p, x));
        expected.push_back(expected[from]);
        expected.back()[std::size_t(p - left)] = x;

        std::size_t check = std::size_t(random() % versions.size());
        int l = left + int(random() % (expected[check].size() + 1));
        int r = left + int(random() % (expected[check].size() + 1));
        if (r < l) std::swap(l, r);
        long long sum = 0;
        for (int i = l; i < r; i++) {
            sum += expected[check][std::size_t(i - left)];
        }
        assert(versions[check].prod(l, r) == sum);

        long long limit = static_cast<long long>(random() % 100);
        int start = left + int(random() % (expected[check].size() + 1));
        int max_right = start;
        sum = 0;
        while (
            max_right < right &&
            sum + expected[check][std::size_t(max_right - left)] <= limit
        ) {
            sum += expected[check][std::size_t(max_right - left)];
            max_right++;
        }
        assert(versions[check].max_right(start, [limit](long long value) {
            return value <= limit;
        }) == max_right);

        int finish = left + int(random() % (expected[check].size() + 1));
        int min_left = finish;
        sum = 0;
        while (
            left < min_left &&
            expected[check][std::size_t(min_left - 1 - left)] + sum <= limit
        ) {
            min_left--;
            sum += expected[check][std::size_t(min_left - left)];
        }
        assert(versions[check].min_left(finish, [limit](long long value) {
            return value <= limit;
        }) == min_left);
    }
}

}  // namespace

int main() {
    test_versions();
    test_uniform_and_non_commutative();
    test_extreme_coordinates();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
