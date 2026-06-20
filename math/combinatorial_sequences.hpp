#ifndef M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP
#define M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

#include "../fps/formal_power_series.hpp"
#include "combinatorics.hpp"

namespace m1une {
namespace math {

template <class Mint>
std::vector<Mint> catalan_numbers(int maximum) {
    assert(maximum >= 0);
    assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());

    std::vector<Mint> inverse(maximum + 2);
    inverse[1] = 1;
    for (int i = 2; i <= maximum + 1; i++) {
        inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod() % uint32_t(i)];
    }

    std::vector<Mint> result(maximum + 1);
    result[0] = 1;
    for (int n = 0; n < maximum; n++) {
        result[n + 1] = result[n] * Mint(2) * Mint(2LL * n + 1) * inverse[n + 2];
    }
    return result;
}

template <class Mint>
std::vector<Mint> bernoulli_numbers(int maximum) {
    assert(maximum >= 0);
    assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());

    using Fps = fps::FormalPowerSeries<Mint>;
    Combinatorics<Mint> combinations(maximum + 1);
    Fps denominator(maximum + 1);
    for (int i = 0; i <= maximum; i++) {
        denominator[i] = combinations.inverse_factorial(i + 1);
    }

    Fps generating_function = denominator.inv(maximum + 1);
    std::vector<Mint> result(maximum + 1);
    for (int i = 0; i <= maximum; i++) {
        result[i] = generating_function[i] * combinations.factorial(i);
    }
    return result;
}

template <class Mint>
std::vector<Mint> bell_numbers(int maximum) {
    assert(maximum >= 0);
    assert(static_cast<uint64_t>(maximum) < Mint::mod());

    using Fps = fps::FormalPowerSeries<Mint>;
    Combinatorics<Mint> combinations(maximum);
    Fps exponent(maximum + 1);
    for (int i = 1; i <= maximum; i++) {
        exponent[i] = combinations.inverse_factorial(i);
    }

    Fps generating_function = exponent.exp(maximum + 1);
    std::vector<Mint> result(maximum + 1);
    for (int i = 0; i <= maximum; i++) {
        result[i] = generating_function[i] * combinations.factorial(i);
    }
    return result;
}

template <class Mint>
std::vector<Mint> stirling_numbers_second_kind(int n) {
    assert(n >= 0);
    assert(static_cast<uint64_t>(n) < Mint::mod());

    Combinatorics<Mint> combinations(n);
    std::vector<Mint> powers(n + 1);
    std::vector<Mint> signs(n + 1);
    for (int i = 0; i <= n; i++) {
        powers[i] = Mint(i).pow(n) * combinations.inverse_factorial(i);
        signs[i] = combinations.inverse_factorial(i);
        if (i & 1) signs[i] = Mint(0) - signs[i];
    }

    std::vector<Mint> result = fps::convolution(powers, signs);
    result.resize(n + 1);
    return result;
}

template <class Mint>
std::vector<Mint> partition_numbers(int maximum) {
    assert(maximum >= 0);

    using Fps = fps::FormalPowerSeries<Mint>;
    Fps denominator(maximum + 1);
    denominator[0] = 1;
    for (long long k = 1;; k++) {
        const long long first = k * (3 * k - 1) / 2;
        const long long second = k * (3 * k + 1) / 2;
        if (first > maximum) break;

        const Mint sign = (k & 1) ? Mint(-1) : Mint(1);
        denominator[int(first)] += sign;
        if (second <= maximum) denominator[int(second)] += sign;
    }
    return denominator.inv(maximum + 1);
}

template <class Mint>
std::vector<Mint> derangement_numbers(int maximum) {
    assert(maximum >= 0);

    std::vector<Mint> result(maximum + 1);
    result[0] = 1;
    if (maximum >= 1) result[1] = 0;
    for (int n = 2; n <= maximum; n++) {
        result[n] = Mint(n - 1) * (result[n - 1] + result[n - 2]);
    }
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP
