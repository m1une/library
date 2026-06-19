#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "data_structure/disjoint_sparse_table.hpp"
#include "monoid/add.hpp"

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

    std::vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    m1une::data_structure::DisjointSparseTable<m1une::monoid::Add<long long>> dst(A);

    for (int q = 0; q < Q; ++q) {
        int l, r;
        std::cin >> l >> r;

        std::cout << dst.prod(l, r) << "\n";
    }

    return 0;
}
