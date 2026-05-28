#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../string/rolling_hash.hpp"
#include <iostream>
#include <string>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

using RH = m1une::string::RollingHash<10007, 2305843009213693951LL>;

int main() {
    fast_io();
    std::string S;
    std::cin >> S;
    int N = S.size();

    RH rh(S);

    for (int i = 0; i < N; ++i) {
        std::cout << rh.lcp(0, N, i, N) << (i == N - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}
