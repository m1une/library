#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include <iostream>
#include <vector>

#include "../../fps/multipoint_evaluation.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Fps polynomial(n);
    std::vector<mint> points(m);
    for (mint& value : polynomial) std::cin >> value;
    for (mint& point : points) std::cin >> point;
    std::vector<mint> result = m1une::fps::multipoint_evaluate(polynomial, points);
    for (int i = 0; i < m; i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
