#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../../ds/segtree/dynamic_dual_segtree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

#include "../../../math/modint.hpp"
#include "../../../monoid/add.hpp"
#include "../../../monoid/affine.hpp"

namespace {

void test_randomized() {
    using Add = m1une::monoid::Add<long long>;
    constexpr int left = -43;
    constexpr int right = 51;
    m1une::ds::DynamicDualSegtree<Add, int> seg(left, right, 7);
    std::vector<long long> a(right - left, 7);

    std::uint64_t state = 3;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto value_at = [&a](int p) -> long long& {
        return a[std::size_t(p - left)];
    };

    for (int step = 0; step < 4000; step++) {
        int type = int(random() % 3);
        if (type == 0) {
            int l = left + int(random() % (a.size() + 1));
            int r = left + int(random() % (a.size() + 1));
            if (r < l) std::swap(l, r);
            long long x = static_cast<long long>(random() % 21);
            seg.apply(l, r, x);
            for (int p = l; p < r; p++) value_at(p) += x;
        } else if (type == 1) {
            [[maybe_unused]] int p = left + int(random() % a.size());
            long long x = static_cast<long long>(random() % 100);
            seg.set(p, x);
            value_at(p) = x;
        } else {
            [[maybe_unused]] int p = left + int(random() % a.size());
            assert(seg.get(p) == value_at(p));
        }
    }

    for (int p = left; p < right; p++) assert(seg[p] == value_at(p));
    assert(seg.node_count() != 0);
    seg.clear();
    assert(seg.node_count() == 0);
    for (int p = left; p < right; p++) assert(seg.get(p) == 7);
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_randomized();

    using mint = m1une::math::modint998244353;
    using Affine = m1une::monoid::Affine<mint>;

    int n, q;
    std::cin >> n >> q;
    m1une::ds::DynamicDualSegtree<Affine, int> seg(0, n, Affine::id());
    seg.reserve(std::size_t(4) * std::size_t(n + q));

    for (int i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        Affine::value_type value;
        value.first = mint(0);
        value.second = mint(x);
        seg.set(i, value);
    }

    for (int query = 0; query < q; query++) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int l, r;
            long long b, c;
            std::cin >> l >> r >> b >> c;
            Affine::value_type f;
            f.first = mint(b);
            f.second = mint(c);
            seg.apply(l, r, f);
        } else {
            int p;
            std::cin >> p;
            std::cout << seg.get(p).second << '\n';
        }
    }
}
