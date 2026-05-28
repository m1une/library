#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../data_structure/sparse_table.hpp"
#include "../../monoid/min.hpp"

#include <iostream>
#include <vector>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    int N, Q;
    std::cin >> N >> Q;

    std::vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    m1une::data_structure::SparseTable<m1une::monoid::Min<long long>> st(A);

    for (int q = 0; q < Q; ++q) {
        int l, r;
        std::cin >> l >> r;
        
        std::cout << st.prod(l, r) << "\n";
    }

    return 0;
}
