#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "data_structure/ordered_multiset.hpp"

#include <iostream>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();

    int N, Q;
    std::cin >> N >> Q;

    m1une::data_structure::OrderedMultiset<int> ms;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        ms.insert(a);
    }

    while (Q--) {
        int type, x;
        std::cin >> type >> x;

        if (type == 0) {
            if (!ms.contains(x)) ms.insert(x);
        } else if (type == 1) {
            if (ms.contains(x)) ms.erase_one(x);
        } else if (type == 2) {
            if (ms.size() < x) {
                std::cout << -1 << '\n';
            } else {
                std::cout << ms.kth(x - 1) << '\n';
            }
        } else if (type == 3) {
            std::cout << ms.count_less_equal(x) << '\n';
        } else if (type == 4) {
            const int* ans = ms.max_le(x);
            std::cout << (ans ? *ans : -1) << '\n';
        } else {
            const int* ans = ms.min_ge(x);
            std::cout << (ans ? *ans : -1) << '\n';
        }
    }
}
