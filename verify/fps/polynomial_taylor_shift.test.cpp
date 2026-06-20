#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include <iostream>

#include "../../fps/formal_power_series.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    mint shift;
    std::cin >> n >> shift;
    Fps a(n);
    for (mint& value : a) std::cin >> value;
    Fps result = a.taylor_shift(shift);
    for (int i = 0; i < n; i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
