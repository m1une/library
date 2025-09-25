#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../data_structure/persistent_treap.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

// Fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> a(N);
    std::vector<int> distinct_elements;

    for (int i = 0; i < N; ++i) {
        std::cin >> a[i];
        distinct_elements.push_back(a[i]);
    }

    // Coordinate Compression
    std::sort(distinct_elements.begin(), distinct_elements.end());
    distinct_elements.erase(std::unique(distinct_elements.begin(), distinct_elements.end()), distinct_elements.end());

    auto get_compressed_rank = [&](int val) {
        return std::lower_bound(distinct_elements.begin(), distinct_elements.end(), val) - distinct_elements.begin();
    };

    // Build a persistent treap for each prefix of the array
    std::vector<m1une::persistent_treap<int>> versions(N + 1);
    for (int i = 0; i < N; ++i) {
        versions[i + 1] = versions[i].insert(get_compressed_rank(a[i]));
    }

    for (int q = 0; q < Q; ++q) {
        int l, r, k;
        std::cin >> l >> r >> k;

        // Meguru-style Binary Search
        // We are looking for the smallest rank 'ok' such that the number of elements
        // in a[l..r-1] with rank <= 'ok' is strictly greater than k.
        int ng = -1;                            // 'ng' is a rank that is always "not good enough"
        int ok = distinct_elements.size() - 1;  // 'ok' is a rank that is "good enough"

        while (std::abs(ok - ng) > 1) {
            int mid = ng + (ok - ng) / 2;

            // Count elements in the range a[l..r-1] with a compressed rank <= mid
            int count_le = versions[r].order_of_key(mid + 1) - versions[l].order_of_key(mid + 1);

            if (count_le > k) {
                // mid is a possible answer, try for a smaller one
                ok = mid;
            } else {
                // mid is not the answer, we need a larger rank
                ng = mid;
            }
        }

        // The answer is the original value corresponding to the 'ok' rank
        std::cout << distinct_elements[ok] << "\n";
    }

    return 0;
}
