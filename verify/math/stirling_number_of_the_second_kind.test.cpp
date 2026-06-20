#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include <iostream>
#include <vector>

#include "../../math/combinatorial_sequences.hpp"
#include "../../math/modint.hpp"

using Mint = m1une::math::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    const std::vector<Mint> values =
        m1une::math::stirling_numbers_second_kind<Mint>(n);
    for (int i = 0; i <= n; i++) {
        if (i) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}
