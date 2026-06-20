#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <cstdint>
#include <iostream>
#include <vector>

#include "math/prime_factorization.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        uint64_t value;
        std::cin >> value;
        std::vector<uint64_t> factors = m1une::math::prime_factors(value);
        std::cout << factors.size();
        for (uint64_t factor : factors) std::cout << ' ' << factor;
        std::cout << '\n';
    }
}
