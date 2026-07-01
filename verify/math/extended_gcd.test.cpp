#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E"

#include "../../math/number_theory.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <tuple>

namespace {

#ifndef NDEBUG
void randomized_test() {
    for (long long a = -100; a <= 100; a++) {
        for (long long b = -100; b <= 100; b++) {
            const auto [gcd, x, y] = m1une::math::extended_gcd(a, b);
            assert(gcd == std::gcd(a, b));
            assert(static_cast<__int128>(a) * x + static_cast<__int128>(b) * y == gcd);
        }
    }

    const auto [gcd, x, y] = m1une::math::extended_gcd(
        std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());
    assert(gcd == 1);
    assert(static_cast<__int128>(std::numeric_limits<long long>::min()) * x +
               static_cast<__int128>(std::numeric_limits<long long>::max()) * y ==
           gcd);
}
#endif

__int128 floor_div(__int128 numerator, __int128 denominator) {
    __int128 quotient = numerator / denominator;
    if (numerator % denominator < 0) quotient--;
    return quotient;
}

std::pair<long long, long long> normalize_for_aoj(long long a, long long b,
                                                  long long gcd, long long x,
                                                  long long y) {
    __int128 x_step = b / gcd;
    __int128 y_step = a / gcd;
    __int128 first = floor_div(-static_cast<__int128>(x), x_step);
    __int128 second = floor_div(static_cast<__int128>(y), y_step);
    std::array<__int128, 6> candidates = {first - 1, first, first + 1,
                                          second - 1, second, second + 1};

    __int128 best_score = -1;
    __int128 best_x = 0;
    __int128 best_y = 0;
    for (__int128 shift : candidates) {
        __int128 candidate_x = x + shift * x_step;
        __int128 candidate_y = y - shift * y_step;
        __int128 score = (candidate_x < 0 ? -candidate_x : candidate_x) +
                         (candidate_y < 0 ? -candidate_y : candidate_y);
        bool candidate_ordered = candidate_x <= candidate_y;
        bool best_ordered = best_x <= best_y;
        if (best_score == -1 || score < best_score ||
            (score == best_score && candidate_ordered && !best_ordered) ||
            (score == best_score && candidate_ordered == best_ordered &&
             candidate_x < best_x)) {
            best_score = score;
            best_x = candidate_x;
            best_y = candidate_y;
        }
    }
    return {static_cast<long long>(best_x), static_cast<long long>(best_y)};
}

}  // namespace

int main() {
#ifndef NDEBUG
    randomized_test();
#endif

    long long a, b;
    std::cin >> a >> b;
    const auto [gcd, x, y] = m1une::math::extended_gcd(a, b);
    const auto answer = normalize_for_aoj(a, b, gcd, x, y);
    std::cout << answer.first << ' ' << answer.second << '\n';
}
