#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "../../string/rolling_hash.hpp"
#include <iostream>
#include <string>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

using RH = m1une::string::RollingHash<10007, 2305843009213693951LL>;

int main() {
    fast_io();
    std::string T, P;
    std::cin >> T >> P;

    if (T.size() < P.size()) return 0;

    RH rh(T);

    long long p_hash = RH::compute_hash(P);

    int n = T.size(), m = P.size();
    for (int i = 0; i <= n - m; ++i) {
        if (rh.get(i, i + m) == p_hash) {
            std::cout << i << "\n";
        }
    }

    return 0;
}
