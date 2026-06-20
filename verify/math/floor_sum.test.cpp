#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#include <iostream>

#include "../../math/number_theory.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        long long n, mod, a, b;
        std::cin >> n >> mod >> a >> b;
        std::cout << m1une::math::floor_sum(n, mod, a, b) << '\n';
    }
}
