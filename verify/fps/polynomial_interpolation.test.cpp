#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <iostream>
#include <vector>

#include "../../fps/multipoint_evaluation.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<mint> points(n), values(n);
    for (mint& point : points) std::cin >> point;
    for (mint& value : values) std::cin >> value;
    Fps result = m1une::fps::polynomial_interpolate(points, values);
    for (int i = 0; i < n; i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
