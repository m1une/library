#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../ds/ordered_set/persistent_ordered_set.hpp"

#include <cassert>
#include <iostream>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();

    m1une::ds::PersistentOrderedSet<int> pointer_test = {1, 3, 5};
    const int* stable_pointer = pointer_test.lower_bound(3);
    auto pointer_test_next = pointer_test;
    for (int x = 10; x < 1000; x++) pointer_test_next = pointer_test_next.insert(x);
    assert(stable_pointer && *stable_pointer == 3);

    int N, Q;
    std::cin >> N >> Q;

    m1une::ds::PersistentOrderedSet<int> st;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        st = st.insert(a);
    }

    while (Q--) {
        int type, x;
        std::cin >> type >> x;

        if (type == 0) {
            st = st.insert(x);
        } else if (type == 1) {
            st = st.erase(x);
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
