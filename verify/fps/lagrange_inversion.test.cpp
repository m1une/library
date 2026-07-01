#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>

#include "../../fps/lagrange_inversion.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

Fps naive_multiply(const Fps& a, const Fps& b, int degree) {
    Fps result(degree);
    for (int i = 0; i < int(a.size()) && i < degree; i++) {
        for (int j = 0; j < int(b.size()) && i + j < degree; j++) {
            result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

Fps naive_compose(const Fps& outer, const Fps& inner, int degree) {
    Fps result(degree);
    Fps power(degree);
    if (degree != 0) power[0] = 1;
    for (int i = 0; i < int(outer.size()) && i < degree; i++) {
        for (int j = 0; j < degree; j++) result[j] += outer[i] * power[j];
        power = naive_multiply(power, inner, degree);
    }
    return result;
}

Fps naive_implicit_series(const Fps& phi, int degree) {
    Fps w(degree);
    for (int iteration = 0; iteration < degree; iteration++) {
        Fps composed = naive_compose(phi, w, degree - 1);
        Fps next(degree);
        for (int i = 1; i < degree; i++) next[i] = composed[i - 1];
        w = std::move(next);
    }
    return w;
}

void test_lagrange_inversion() {
    Fps catalan_phi = {1, 2, 1};
    mint catalan[] = {1, 1, 2, 5, 14, 42, 132};
    for (int n = 1; n <= 6; n++) {
        assert(m1une::fps::lagrange_inversion_coefficient(catalan_phi, n) == catalan[n]);
    }
    const int large_n = 128;
    mint central_binomial = 1;
    for (int i = 1; i <= large_n; i++) {
        central_binomial *= mint(large_n + i) / mint(i);
    }
    mint large_catalan = central_binomial / mint(large_n + 1);
    assert(m1une::fps::lagrange_inversion_coefficient(catalan_phi, large_n) == large_catalan);

    std::mt19937 random(123456789);
    for (int test = 0; test < 100; test++) {
        const int degree = 12;
        Fps phi(degree);
        phi[0] = 1 + random() % 100;
        for (int i = 1; i < degree; i++) phi[i] = random() % 100;
        Fps w = naive_implicit_series(phi, degree);

        Fps outer(degree);
        for (mint& value : outer) value = random() % 100;
        Fps composed = naive_compose(outer, w, degree);

        for (int n = 1; n < degree; n++) {
            assert(m1une::fps::lagrange_inversion_coefficient(phi, n) == w[n]);
            assert(m1une::fps::lagrange_burmann_coefficient(phi, outer, n) == composed[n]);
        }
        assert(m1une::fps::lagrange_burmann_coefficient(phi, outer, 0) == outer[0]);

        Fps f = phi.inv(degree) << 1;
        f.resize(degree);
        for (int n = 0; n < degree; n++) {
            assert(m1une::fps::compositional_inverse_coefficient(f, n) == w[n]);
        }
    }
}

int main() {
    test_lagrange_inversion();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
