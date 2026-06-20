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
    m1une::math::Combinatorics<Mint> combinations(100);

    assert(combinations.factorial(5) == Mint(120));
    assert(combinations.inverse(5) * Mint(5) == Mint(1));
    assert(combinations.binom(10, 3) == Mint(120));
    assert(combinations.binom(3, 5) == Mint(0));
    assert(combinations.perm(5, 3) == Mint(60));
    assert(combinations.multiset(3, 4) == Mint(15));
    assert(combinations.multiset(0, 0) == Mint(1));
    assert(combinations.catalan(5) == Mint(42));

    assert(combinations.binom(100, 0) == Mint(1));
    assert(combinations.binom(100, 100) == Mint(1));
}

void test_combinatorial_sequences() {
    using Mint = m1une::math::modint998244353;

    const std::vector<Mint> catalan = m1une::math::catalan_numbers<Mint>(10);
    const std::vector<int> expected_catalan =
        {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796};
    for (int i = 0; i <= 10; i++) assert(catalan[i] == Mint(expected_catalan[i]));
    m1une::math::Combinatorics<Mint> catalan_combinations(100);
    const std::vector<Mint> more_catalan =
        m1une::math::catalan_numbers<Mint>(50);
    for (int i = 0; i <= 50; i++) {
        assert(more_catalan[i] == catalan_combinations.catalan(i));
    }

    const std::vector<Mint> bernoulli = m1une::math::bernoulli_numbers<Mint>(20);
    assert(bernoulli[0] == Mint(1));
    assert(bernoulli[1] * Mint(2) == Mint(-1));
    assert(bernoulli[2] * Mint(6) == Mint(1));
    assert(bernoulli[4] * Mint(30) == Mint(-1));
    assert(bernoulli[6] * Mint(42) == Mint(1));
    for (int i = 3; i <= 19; i += 2) assert(bernoulli[i] == Mint(0));

    m1une::math::Combinatorics<Mint> combinations(21);
    for (int n = 1; n <= 20; n++) {
        Mint sum = 0;
        for (int k = 0; k <= n; k++) {
            sum += combinations.binom(n + 1, k) * bernoulli[k];
        }
        assert(sum == Mint(0));
    }

    const std::vector<Mint> bell = m1une::math::bell_numbers<Mint>(10);
    const std::vector<int> expected_bell =
        {1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975};
    for (int i = 0; i <= 10; i++) assert(bell[i] == Mint(expected_bell[i]));

    const std::vector<Mint> stirling_zero =
        m1une::math::stirling_numbers_second_kind<Mint>(0);
    assert(stirling_zero == std::vector<Mint>{Mint(1)});
    const std::vector<Mint> stirling =
        m1une::math::stirling_numbers_second_kind<Mint>(5);
    const std::vector<int> expected_stirling = {0, 1, 15, 25, 10, 1};
    for (int i = 0; i <= 5; i++) {
        assert(stirling[i] == Mint(expected_stirling[i]));
    }
    std::vector<Mint> stirling_dp(1, Mint(1));
    const std::vector<Mint> more_bell = m1une::math::bell_numbers<Mint>(30);
    for (int n = 0; n <= 30; n++) {
        if (n > 0) {
            std::vector<Mint> next(n + 1);
            for (int k = 1; k <= n; k++) {
                next[k] = stirling_dp[k - 1];
                if (k < int(stirling_dp.size())) {
                    next[k] += Mint(k) * stirling_dp[k];
                }
            }
            stirling_dp = std::move(next);
        }
        const std::vector<Mint> row =
            m1une::math::stirling_numbers_second_kind<Mint>(n);
        assert(row == stirling_dp);
        Mint sum = 0;
        for (Mint value : row) sum += value;
        assert(sum == more_bell[n]);
    }

    const std::vector<Mint> partitions = m1une::math::partition_numbers<Mint>(100);
    const std::vector<int> expected_partitions =
        {1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42};
    for (int i = 0; i <= 10; i++) {
        assert(partitions[i] == Mint(expected_partitions[i]));
    }
    std::vector<Mint> partition_dp(101);
    partition_dp[0] = 1;
    for (int part = 1; part <= 100; part++) {
        for (int sum = part; sum <= 100; sum++) {
            partition_dp[sum] += partition_dp[sum - part];
        }
    }
    assert(partitions == partition_dp);

    const std::vector<Mint> derangements =
        m1une::math::derangement_numbers<Mint>(10);
    const std::vector<int> expected_derangements =
        {1, 0, 1, 2, 9, 44, 265, 1854, 14833, 133496, 1334961};
    for (int i = 0; i <= 10; i++) {
        assert(derangements[i] == Mint(expected_derangements[i]));
    }
    m1une::math::Combinatorics<Mint> derangement_combinations(30);
    const std::vector<Mint> more_derangements =
        m1une::math::derangement_numbers<Mint>(30);
    Mint alternating_sum = 1;
    for (int n = 0; n <= 30; n++) {
        if (n > 0) {
            const Mint term = derangement_combinations.inverse_factorial(n);
            alternating_sum += (n & 1) ? Mint(0) - term : term;
        }
        assert(
            more_derangements[n] ==
            derangement_combinations.factorial(n) * alternating_sum
        );
    }
}

int main() {
    test_number_theory();
    test_prime_sieve();
    test_large_factorization();
    test_combinatorics();
    test_combinatorial_sequences();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
