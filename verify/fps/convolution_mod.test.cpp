#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include <vector>

#include "fps/convolution.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<mint> a(n), b(m);
    for (mint& value : a) std::cin >> value;
    for (mint& value : b) std::cin >> value;
    std::vector<mint> result = m1une::fps::convolution(a, b);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
