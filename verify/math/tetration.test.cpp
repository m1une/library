#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/tetration.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

uint64_t minimum(uint64_t first, uint64_t second) {
    return first < second ? first : second;
}

uint64_t brute_pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {
    if (limit == 0) return 0;
    if (exponent == 0) return 1 < limit ? 1 : limit;
    if (base == 0) return 0;

    __uint128_t result = 1;
    for (uint64_t i = 0; i < exponent; i++) {
        result *= base;
        if (result >= limit) return limit;
    }
    return uint64_t(result);
}

uint64_t brute_tetration_bounded(uint64_t base, uint64_t height, uint64_t limit) {
    if (limit == 0) return 0;
    if (height == 0) return minimum(1, limit);
    if (height == 1) return minimum(base, limit);

    uint64_t exponent = brute_tetration_bounded(base, height - 1, limit);
    return brute_pow_bounded(base, exponent, limit);
}

uint64_t brute_tower_bounded(
    const std::vector<uint64_t>& bases,
    int index,
    uint64_t limit
) {
    if (limit == 0) return 0;
    if (index == int(bases.size())) return minimum(1, limit);
    if (index + 1 == int(bases.size())) return minimum(bases[index], limit);

    uint64_t exponent = brute_tower_bounded(bases, index + 1, limit);
    return brute_pow_bounded(bases[index], exponent, limit);
}

void test_fixed_cases() {
    assert(m1une::math::tetration_mod(2ULL, 0, 1000) == 1);
    assert(m1une::math::tetration_mod(2ULL, 1, 1000) == 2);
    assert(m1une::math::tetration_mod(2ULL, 4, 1000) == 536);
    assert(m1une::math::tetration_mod(3ULL, 3, 100) == 87);
    assert(m1une::math::tetration_mod(0ULL, 0, 1000) == 1);
    assert(m1une::math::tetration_mod(0ULL, 1, 1000) == 0);
    assert(m1une::math::tetration_mod(0ULL, 2, 1000) == 1);
    assert(m1une::math::tetration_mod(0ULL, 3, 1000) == 0);
    assert(m1une::math::tetration_mod(7ULL, 100, 1) == 0);
    assert(m1une::math::tetration_bounded(2ULL, 5, 1000000) == 1000000);

    std::vector<unsigned long long> empty;
    assert(m1une::math::power_tower_mod(empty, 37) == 1);
    assert(m1une::math::power_tower_bounded(empty, 10) == 1);

    std::vector<unsigned long long> zero_zero;
    zero_zero.push_back(0);
    zero_zero.push_back(0);
    assert(m1une::math::power_tower_mod(zero_zero, 1000) == 1);

    std::vector<unsigned long long> two_zero;
    two_zero.push_back(2);
    two_zero.push_back(0);
    assert(m1une::math::power_tower_mod(two_zero, 1000) == 1);

    std::vector<unsigned long long> two_three_four;
    two_three_four.push_back(2);
    two_three_four.push_back(3);
    two_three_four.push_back(4);
    assert(m1une::math::power_tower_mod(two_three_four, 1000) == 352);
}

void test_tetration_against_bruteforce() {
    const uint64_t cap = 1000000;
    for (uint64_t base = 0; base <= 8; base++) {
        for (uint64_t height = 0; height <= 7; height++) {
            for (uint64_t limit = 0; limit <= 1000; limit++) {
                uint64_t expected = brute_tetration_bounded(base, height, limit);
                uint64_t actual = m1une::math::tetration_bounded(base, height, limit);
                assert(actual == expected);
            }
            uint64_t exact = brute_tetration_bounded(base, height, cap);
            if (exact == cap) continue;
            for (uint64_t mod = 1; mod <= 257; mod++) {
                assert(m1une::math::tetration_mod(base, height, mod) == exact % mod);
            }
        }
    }
}

void enumerate_towers(
    int length,
    int position,
    std::vector<uint64_t>& bases
) {
    if (position == length) {
        const uint64_t cap = 1000000;
        for (uint64_t limit = 0; limit <= 300; limit++) {
            uint64_t expected = brute_tower_bounded(bases, 0, limit);
            uint64_t actual = m1une::math::power_tower_bounded(bases, limit);
            assert(actual == expected);
        }

        uint64_t exact = brute_tower_bounded(bases, 0, cap);
        if (exact == cap) return;
        for (uint64_t mod = 1; mod <= 127; mod++) {
            assert(m1une::math::power_tower_mod(bases, mod) == exact % mod);
        }
        return;
    }

    for (uint64_t base = 0; base <= 4; base++) {
        bases[position] = base;
        enumerate_towers(length, position + 1, bases);
    }
}

void test_power_tower_against_bruteforce() {
    for (int length = 0; length <= 5; length++) {
        std::vector<uint64_t> bases(length);
        enumerate_towers(length, 0, bases);
    }
}

}  // namespace

int main() {
    test_fixed_cases();
    test_tetration_against_bruteforce();
    test_power_tower_against_bruteforce();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
