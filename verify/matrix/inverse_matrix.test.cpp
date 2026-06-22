#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../math/modint.hpp"
#include "../../matrix/linear_algebra.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    int n;
    std::cin >> n;
    m1une::matrix::Matrix<mint> matrix(n, n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) std::cin >> matrix[row][col];
    }

    auto result = m1une::matrix::inverse(matrix);
    if (!result.has_value()) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (col > 0) std::cout << ' ';
            std::cout << (*result)[row][col];
        }
        std::cout << '\n';
    }
}
