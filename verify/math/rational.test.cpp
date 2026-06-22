#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/rational.hpp"

#include <cassert>
#include <compare>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>

namespace {

using Fraction = m1une::math::Rational<long long>;

void test_fixed() {
    constexpr Fraction zero;
    constexpr Fraction half(2, 4);
    constexpr Fraction negative(3, -6);
    static_assert(zero.numerator() == 0);
    static_assert(zero.denominator() == 1);
    static_assert(half == Fraction(1, 2));
    static_assert(negative == Fraction(-1, 2));
    static_assert(half + negative == 0);
    static_assert(Fraction(2, 3) + Fraction(5, 6) == Fraction(3, 2));
    static_assert(Fraction(2, 3) * Fraction(9, 4) == Fraction(3, 2));
    static_assert(Fraction(2, 3) / Fraction(4, 9) == Fraction(3, 2));
    static_assert(Fraction(-7, 3).floor() == -3);
    static_assert(Fraction(-7, 3).ceil() == -2);
    static_assert(Fraction(-7, 3).trunc() == -2);
    static_assert(Fraction(1, 3) < Fraction(1, 2));
    static_assert(m1une::math::abs(Fraction(-3, 4)) == Fraction(3, 4));

    [[maybe_unused]] Fraction large(
        std::numeric_limits<long long>::max(),
        std::numeric_limits<long long>::max() - 1
    );
    assert(large > 1);

    std::stringstream stream;
    stream << Fraction(-6, 8) << ' ' << Fraction(5);
    assert(stream.str() == "-3/4 5");
    Fraction first;
    Fraction second;
    stream.seekg(0);
    stream >> first >> second;
    assert(first == Fraction(-3, 4));
    assert(second == 5);
}

void test_randomized() {
    std::uint64_t state = 1301;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 100000; ++trial) {
        long long a = static_cast<long long>(random() % 2001) - 1000;
        long long b = 1 + static_cast<long long>(random() % 1000);
        long long c = static_cast<long long>(random() % 2001) - 1000;
        long long d = 1 + static_cast<long long>(random() % 1000);
        Fraction first(a, b);
        Fraction second(c, d);

        [[maybe_unused]] __int128_t left = __int128_t(a) * d;
        [[maybe_unused]] __int128_t right = __int128_t(c) * b;
        assert((first <=> second) == (left <=> right));

        [[maybe_unused]] Fraction sum = first + second;
        assert(
            __int128_t(sum.numerator()) * b * d
            == (__int128_t(a) * d + __int128_t(c) * b)
                * sum.denominator()
        );

        [[maybe_unused]] Fraction product = first * second;
        assert(
            __int128_t(product.numerator()) * b * d
            == __int128_t(a) * c * product.denominator()
        );

        if (c != 0) {
            [[maybe_unused]] Fraction quotient = first / second;
            assert(
                __int128_t(quotient.numerator()) * b * c
                == __int128_t(a) * d * quotient.denominator()
            );
        }
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
