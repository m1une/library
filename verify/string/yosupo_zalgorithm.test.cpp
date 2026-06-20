#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "string/z_algorithm.hpp"
#include <iostream>
#include <string>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();
    std::string S;
    std::cin >> S;
    std::vector<int> z = m1une::string::z_algorithm(S);
    for (int i = 0; i < int(z.size()); ++i) {
        std::cout << z[i] << (i + 1 == int(z.size()) ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}
