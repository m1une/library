#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <iostream>
#include <vector>

#include "math/prime_sieve.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, step, offset;
    std::cin >> n >> step >> offset;
    m1une::math::PrimeSieve sieve(n);
    const std::vector<int>& primes = sieve.primes();

    int selected_count = 0;
    if (offset < int(primes.size())) {
        selected_count = (int(primes.size()) - 1 - offset) / step + 1;
    }
    std::cout << primes.size() << ' ' << selected_count << '\n';
    for (int i = offset; i < int(primes.size()); i += step) {
        if (i != offset) std::cout << ' ';
        std::cout << primes[i];
    }
    std::cout << '\n';
}
