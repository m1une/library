#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include <cstdint>
#include <iostream>

#include "math/prime_factorization.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        uint64_t value;
        std::cin >> value;
        std::cout << (m1une::math::is_prime(value) ? "Yes" : "No") << '\n';
    }
}
