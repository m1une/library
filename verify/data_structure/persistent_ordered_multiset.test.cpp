#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "data_structure/persistent_ordered_multiset.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();

    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> a(N);
    std::vector<int> xs;
    xs.reserve(N);
    for (int i = 0; i < N; i++) {
        std::cin >> a[i];
        xs.push_back(a[i]);
    }

    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

    auto rank = [&](int value) { return int(std::lower_bound(xs.begin(), xs.end(), value) - xs.begin()); };

    std::vector<m1une::data_structure::PersistentOrderedMultiset<int>> versions(N + 1);
    for (int i = 0; i < N; i++) {
        versions[i + 1] = versions[i].insert(rank(a[i]));
    }

    while (Q--) {
        int l, r, k;
        std::cin >> l >> r >> k;

        int ok = int(xs.size()) - 1;
        int ng = -1;
        while (ok - ng > 1) {
            int mid = (ok + ng) / 2;
            int count_le = versions[r].count_less_equal(mid) - versions[l].count_less_equal(mid);
            if (count_le > k) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        std::cout << xs[ok] << '\n';
    }
}
