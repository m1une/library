#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../math/modint.hpp"
#include "../../matrix/matrix.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    int n, m, k;
    std::cin >> n >> m >> k;
    m1une::matrix::Matrix<mint> first(n, m);
    m1une::matrix::Matrix<mint> second(m, k);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) std::cin >> first[row][col];
    }
    for (int row = 0; row < m; row++) {
        for (int col = 0; col < k; col++) std::cin >> second[row][col];
    }

    auto product = first * second;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < k; col++) {
            if (col > 0) std::cout << ' ';
            std::cout << product[row][col];
        }
        std::cout << '\n';
    }
}
