#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "math/all.hpp"

long long floor_div(long long numerator, long long denominator) {
    long long quotient = numerator / denominator;
    if (numerator % denominator < 0) quotient--;
    return quotient;
}

void test_number_theory() {
    using m1une::math::crt;
    using m1une::math::floor_sum;
    using m1une::math::inv_gcd;
    using m1une::math::inv_mod;
    using m1une::math::pow_mod;

    assert(pow_mod(-2, 5, 13) == 7);
    assert(pow_mod(123, 0, 1) == 0);
    assert(inv_mod(3, 11) == 4);

    const auto inverse = inv_gcd(6, 15);
    assert(inverse.first == 3);
    assert((6 * inverse.second - inverse.first) % 15 == 0);

    const auto solution = crt(
        std::vector<long long>{2, 3, 2},
        std::vector<long long>{3, 5, 7}
    );
    assert(solution.first == 23);
    assert(solution.second == 105);
    const auto inconsistent = crt(
        std::vector<long long>{0, 1},
        std::vector<long long>{2, 4}
    );
    assert(inconsistent.second == 0);

    for (long long first_mod = 1; first_mod <= 12; first_mod++) {
        for (long long second_mod = 1; second_mod <= 12; second_mod++) {
            const long long combined_mod = std::lcm(first_mod, second_mod);
            for (long long first_remainder = -5; first_remainder <= 5;
                 first_remainder++) {
                for (long long second_remainder = -5; second_remainder <= 5;
                     second_remainder++) {
                    long long expected = -1;
                    for (long long value = 0; value < combined_mod; value++) {
                        if (
                            (value - first_remainder) % first_mod == 0 &&
                            (value - second_remainder) % second_mod == 0
                        ) {
                            expected = value;
                            break;
                        }
                    }
                    const auto actual = crt(
                        std::vector<long long>{first_remainder, second_remainder},
                        std::vector<long long>{first_mod, second_mod}
                    );
                    if (expected == -1) {
                        assert(actual.second == 0);
                    } else {
                        assert(actual.first == expected);
                        assert(actual.second == combined_mod);
                    }
                }
            }
        }
    }

    for (long long n = 0; n <= 15; n++) {
        for (long long mod = 1; mod <= 15; mod++) {
            for (long long a = -15; a <= 15; a++) {
                for (long long b = -15; b <= 15; b++) {
                    long long expected = 0;
                    for (long long i = 0; i < n; i++) {
                        expected += floor_div(a * i + b, mod);
                    }
                    assert(floor_sum(n, mod, a, b) == expected);
                }
            }
        }
    }
}

void test_prime_sieve() {
    m1une::math::PrimeSieve sieve(100);
    assert(sieve.primes().size() == 25);
    assert(sieve.is_prime(97));
    assert(!sieve.is_prime(1));
    assert(sieve.min_prime_factor(91) == 7);

    std::vector<std::pair<int, int>> factors_72;
    factors_72.emplace_back(2, 3);
    factors_72.emplace_back(3, 2);
    assert(sieve.factorize(72) == factors_72);

    std::vector<std::pair<int, int>> factors_90;
    factors_90.emplace_back(2, 1);
    factors_90.emplace_back(3, 2);
    factors_90.emplace_back(5, 1);
    assert(sieve.factorize(90) == factors_90);

    const std::vector<int> expected_divisors = {1, 2, 3, 4, 6, 12};
    assert(sieve.divisors(12) == expected_divisors);
    assert(sieve.totient(36) == 12);
    assert(sieve.mobius(30) == -1);
    assert(sieve.mobius(12) == 0);
    assert(sieve.totient_table()[36] == 12);
    assert(sieve.mobius_table()[30] == -1);
}

void test_large_factorization() {
    using m1une::math::divisors;
    using m1une::math::euler_phi;
    using m1une::math::is_prime;
    using m1une::math::mobius;
    using m1une::math::prime_factorize;

    assert(is_prime(2));
    assert(is_prime(18446744073709551557ULL));
    assert(!is_prime(341550071728321ULL));

    const uint64_t semiprime = 1000000007ULL * 1000000009ULL;
    const auto factors = prime_factorize(semiprime);
    assert(factors.size() == 2);
    assert((factors[0] == std::pair<uint64_t, int>(1000000007ULL, 1)));
    assert((factors[1] == std::pair<uint64_t, int>(1000000009ULL, 1)));

    const std::vector<uint64_t> expected_divisors = {1, 2, 3, 4, 6, 9, 12, 18, 36};
    assert(divisors(36) == expected_divisors);
    assert(euler_phi(36) == 12);
    assert(mobius(30) == -1);
    assert(mobius(12) == 0);

    m1une::math::PrimeSieve sieve(10000);
    for (int value = 1; value <= sieve.limit(); value++) {
        const auto small_factors = sieve.factorize(value);
        const auto large_factors = prime_factorize(value);
        assert(small_factors.size() == large_factors.size());
        for (int i = 0; i < int(small_factors.size()); i++) {
            assert(uint64_t(small_factors[i].first) == large_factors[i].first);
            assert(small_factors[i].second == large_factors[i].second);
        }
    }
}

void test_combinatorics() {
    using Mint = m1une::math::modint998244353;
    m1une::math::Combinatorics<Mint> combinations(20);

    assert(combinations.factorial(5) == Mint(120));
    assert(combinations.inverse(5) * Mint(5) == Mint(1));
    assert(combinations.binom(10, 3) == Mint(120));
    assert(combinations.binom(3, 5) == Mint(0));
    assert(combinations.perm(5, 3) == Mint(60));
    assert(combinations.multiset(3, 4) == Mint(15));
    assert(combinations.multiset(0, 0) == Mint(1));

    combinations.ensure(100);
    assert(combinations.binom(100, 0) == Mint(1));
    assert(combinations.binom(100, 100) == Mint(1));
}

int main() {
    test_number_theory();
    test_prime_sieve();
    test_large_factorization();
    test_combinatorics();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
