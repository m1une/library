#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include <iostream>
#include <vector>

#include "../../../data_structure/bst/treap.hpp"

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();
    int N, Q;
    std::cin >> N >> Q;

    m1une::treap<int> tr;
    for (int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        tr.insert(a);
    }

    for (int q = 0; q < Q; ++q) {
        int type, k;
        std::cin >> type >> k;
        if (type == 0) {
            if (!tr.contains(k)) {
                tr.insert(k);
            }
        } else if (type == 1) {
            if (tr.contains(k)) {
                tr.erase(k);
            }
        } else if (type == 2) {
            // Find k-th smallest (0-indexed)
            if (tr.size() < k) {
                std::cout << -1 << "\n";
            } else {
                std::cout << tr.find_by_order(k - 1) << "\n";
            }
        } else if (type == 3) {
            // Find number of elements <= k
            // This is the same as the rank of k+1
            std::cout << tr.order_of_key(k + 1) << "\n";
        } else if (type == 4) {
            // Find largest element <= k (predecessor)
            int order = tr.order_of_key(k + 1);
            if (order == 0) {
                std::cout << -1 << "\n";
            } else {
                std::cout << tr.find_by_order(order - 1) << "\n";
            }
        } else if (type == 5) {
            // Find smallest element >= k (successor)
            auto res = tr.lower_bound(k);
            if (res) {
                std::cout << *res << "\n";
            } else {
                std::cout << -1 << "\n";
            }
        }
    }

    return 0;
}
