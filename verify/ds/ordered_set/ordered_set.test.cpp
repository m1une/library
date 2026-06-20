#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "ds/ordered_set/ordered_set.hpp"

#include <iostream>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();

    int N, Q;
    std::cin >> N >> Q;

    m1une::ds::OrderedSet<int> st;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        st.insert(a);
    }

    while (Q--) {
        int type, x;
        std::cin >> type >> x;

        if (type == 0) {
            st.insert(x);
        } else if (type == 1) {
            st.erase(x);
        } else if (type == 2) {
            if (st.size() < x) {
                std::cout << -1 << '\n';
            } else {
                std::cout << st.kth(x - 1) << '\n';
            }
        } else if (type == 3) {
            std::cout << st.count_less_equal(x) << '\n';
        } else if (type == 4) {
            const int* ans = st.max_le(x);
            std::cout << (ans ? *ans : -1) << '\n';
        } else {
            const int* ans = st.min_ge(x);
            std::cout << (ans ? *ans : -1) << '\n';
        }
    }
}
