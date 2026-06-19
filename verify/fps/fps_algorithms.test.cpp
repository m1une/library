#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "fps/all.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;
using mint1e9 = m1une::math::modint1000000007;
using Fps = m1une::fps::FormalPowerSeries<mint>;

template <class Mint>
void assert_equal(const std::vector<Mint>& lhs, const std::vector<Mint>& rhs) {
    assert(lhs.size() == rhs.size());
    for (int i = 0; i < int(lhs.size()); i++) assert(lhs[i] == rhs[i]);
}

void test_convolution() {
    std::mt19937 rng(712367);
    for (int iteration = 0; iteration < 30; iteration++) {
        int n = 33 + int(rng() % 70);
        int m = 33 + int(rng() % 70);
        std::vector<mint> a(n), b(m);
        for (mint& value : a) value = mint(static_cast<uint32_t>(rng()));
        for (mint& value : b) value = mint(static_cast<uint32_t>(rng()));
        assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a, b));
    }

    std::vector<mint1e9> a(70), b(65);
    for (mint1e9& value : a) value = mint1e9(static_cast<uint32_t>(rng()));
    for (mint1e9& value : b) value = mint1e9(static_cast<uint32_t>(rng()));
    assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a, b));
}

void test_series_functions() {
    Fps f(96);
    f[0] = 1;
    for (int i = 1; i < int(f.size()); i++) f[i] = mint(i * i + 7);

    Fps inverse = f.inv();
    Fps identity = (f * inverse).pre(int(f.size()));
    assert(identity[0] == mint(1));
    for (int i = 1; i < int(identity.size()); i++) assert(identity[i] == mint(0));

    Fps logarithm = f.log();
    assert_equal(logarithm.exp(), f);
    assert_equal(f.derivative().integral().pre(int(f.size())) + Fps(1, f[0]), f);

    Fps cube = f.pow(3);
    assert_equal(cube, ((f * f) * f).pre(int(f.size())));

    Fps shifted(40);
    shifted[4] = 9;
    for (int i = 5; i < int(shifted.size()); i++) shifted[i] = mint(i + 11);
    auto root = (shifted * shifted).pre(70).sqrt(70);
    assert(root.has_value());
    assert_equal(((*root) * (*root)).pre(70), (shifted * shifted).pre(70));

    Fps beyond_precision(8);
    beyond_precision[5] = 1;
    auto zero_root = beyond_precision.sqrt(5);
    assert(zero_root.has_value());
    assert_equal(*zero_root, Fps(5));

    Fps odd_leading(8);
    odd_leading[3] = 1;
    assert(!odd_leading.sqrt(8).has_value());

    Fps zero(20);
    Fps one(20);
    one[0] = 1;
    assert_equal(zero.pow(0), one);
    assert_equal(zero.pow(7), zero);
}

void test_polynomial_operations() {
    Fps dividend(80), divisor(35);
    for (int i = 0; i < int(dividend.size()); i++) dividend[i] = mint(i * 17 + 3);
    for (int i = 0; i < int(divisor.size()); i++) divisor[i] = mint(i * 5 + 1);
    auto division = dividend.divmod(divisor);
    Fps restored = division.first * divisor + division.second;
    restored.resize(dividend.size());
    assert_equal(restored, dividend);
    assert(division.second.size() < divisor.size());

    mint shift = 12345;
    Fps translated = dividend.taylor_shift(shift);
    for (int x = 0; x < 10; x++) {
        assert(translated.evaluate(mint(x)) == dividend.evaluate(mint(x) + shift));
    }
}

void test_multipoint_and_recurrence() {
    Fps polynomial(70);
    for (int i = 0; i < int(polynomial.size()); i++) polynomial[i] = mint(i * i * 13 + 5);
    std::vector<mint> points(70);
    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);

    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);
    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));
    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);
    assert_equal(interpolated, polynomial);
    std::vector<mint> one_point(1, mint(42));
    std::vector<mint> one_value(1, mint(314));
    assert_equal(m1une::fps::polynomial_interpolate(one_point, one_value), Fps(1, mint(314)));
    assert(m1une::fps::multipoint_evaluate(Fps(), std::vector<mint>()).empty());

    std::vector<mint> initial(2);
    std::vector<mint> recurrence(2);
    initial[0] = 0;
    initial[1] = 1;
    recurrence[0] = 1;
    recurrence[1] = 1;
    mint previous = 0;
    mint current = 1;
    for (uint64_t index = 0; index < 200; index++) {
        mint expected = index == 0 ? previous : current;
        assert(m1une::fps::linear_recurrence_kth(initial, recurrence, index) == expected);
        if (index > 0) {
            mint next = previous + current;
            previous = current;
            current = next;
        }
    }
}

int main() {
    test_convolution();
    test_series_functions();
    test_polynomial_operations();
    test_multipoint_and_recurrence();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
