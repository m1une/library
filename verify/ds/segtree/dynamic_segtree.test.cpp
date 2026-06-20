#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../../ds/segtree/dynamic_segtree.hpp"

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

void test_library_features() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::DynamicSegtree<Sum>;

    Seg empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.all_prod() == 0);

    Seg seg(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL);
    assert(!seg.empty());
    assert(seg.left_bound() == -1'000'000'000'000'000'000LL);
    assert(seg.right_bound() == 1'000'000'000'000'000'000LL);
    assert(seg.size() == 2'000'000'000'000'000'000ULL);

    seg.reserve(256);
    seg.set(-3, 2);
    seg.set(2, 4);
    seg.set(7, 1);

    assert(seg.get(-3) == 2);
    assert(seg[-2] == 0);
    assert(seg.prod(-4, 3) == 6);
    assert(seg.prod(3, 7) == 0);
    assert(seg.all_prod() == 7);
    assert(seg.max_right(-8, [](long long x) { return x <= 5; }) == 2);
    assert(seg.min_left(8, [](long long x) { return x <= 4; }) == 3);

    [[maybe_unused]] std::size_t nodes = seg.node_count();
    seg.set(-3, 5);
    assert(seg.node_count() == nodes);
    assert(seg.all_prod() == 10);

    seg.clear();
    assert(seg.node_count() == 0);
    assert(seg.all_prod() == 0);
    assert(seg.get(-3) == 0);

    m1une::ds::DynamicSegtree<Concat, int> text(-4, 5);
    text.set(2, "b");
    text.set(-1, "a");
    assert(text.prod(-4, 5) == "ab");

    Seg extreme(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());
    extreme.set(std::numeric_limits<long long>::min(), 3);
    extreme.set(std::numeric_limits<long long>::max() - 1, 4);
    assert(extreme.size() == std::numeric_limits<unsigned long long>::max());
    assert(extreme.get(std::numeric_limits<long long>::min()) == 3);
    assert(extreme.get(std::numeric_limits<long long>::max() - 1) == 4);
    assert(extreme.all_prod() == 7);

    constexpr int left = -37;
    constexpr int right = 42;
    m1une::ds::DynamicSegtree<Sum, int> small(left, right);
    std::vector<long long> a(right - left);
    auto value_at = [&a](int p) -> long long& {
        return a[std::size_t(p - left)];
    };
    std::uint64_t state = 1;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int step = 0; step < 2000; step++) {
        int p = left + int(random() % a.size());
        long long x = static_cast<long long>(random() % 10);
        small.set(p, x);
        value_at(p) = x;

        int l = left + int(random() % (a.size() + 1));
        int r = left + int(random() % (a.size() + 1));
        if (r < l) std::swap(l, r);
        [[maybe_unused]] long long expected = 0;
        for (int i = l; i < r; i++) expected += value_at(i);
        assert(small.prod(l, r) == expected);

        long long limit = static_cast<long long>(random() % 100);
        int max_right = l;
        long long sum = 0;
        while (max_right < right && sum + value_at(max_right) <= limit) {
            sum += value_at(max_right);
            max_right++;
        }
        assert(small.max_right(l, [limit](long long value) { return value <= limit; }) == max_right);

        int min_left = r;
        sum = 0;
        while (left < min_left && value_at(min_left - 1) + sum <= limit) {
            min_left--;
            sum += value_at(min_left);
        }
        assert(small.min_left(r, [limit](long long value) { return value <= limit; }) == min_left);
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_library_features();

    int n, q;
    std::cin >> n >> q;

    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::DynamicSegtree<Sum, int> seg(n);
    seg.reserve(std::size_t(2) * std::size_t(n));

    for (int i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        seg.set(i, x);
    }

    for (int query = 0; query < q; query++) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int p;
            long long x;
            std::cin >> p >> x;
            seg.set(p, seg.get(p) + x);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.prod(l, r) << '\n';
        }
    }
}
