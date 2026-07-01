#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/base_n.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <random>
#include <vector>

void fixed_tests() {
    using m1une::math::checked_from_base_n;
    using m1une::math::from_base_n;
    using m1une::math::to_base_n;

    assert(to_base_n(0, 2) == std::vector<int>({0}));
    assert(to_base_n(255, 16) == std::vector<int>({15, 15}));
    assert(to_base_n(1002003, 1000) == std::vector<int>({1, 2, 3}));
    assert(from_base_n<long long>(std::vector<int>({1, 2, 3}), 1000) == 1002003);
    assert(from_base_n<int>(std::vector<int>(), 10) == 0);
    assert(from_base_n<int>(std::vector<int>({0, 0, 7}), 10) == 7);

    assert(!checked_from_base_n<int>(std::vector<int>({1, -1}), 10).has_value());
    assert(!checked_from_base_n<int>(std::vector<int>({1, 10}), 10).has_value());
    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({2, 5, 6}), 10)
                .has_value());
    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({256}), 1000)
                .has_value());
    assert(checked_from_base_n<std::uint8_t>(std::vector<int>({2, 5, 5}), 10) ==
           std::optional<std::uint8_t>(255));
}

void randomized_tests() {
    std::mt19937_64 random(987654321);
    for (int trial = 0; trial < 100000; trial++) {
        std::uint64_t value = random();
        int base = int(random() % 1000000) + 2;
        std::vector<int> digits = m1une::math::to_base_n(value, base);
        assert(!digits.empty());
        assert(digits.size() == 1 || digits.front() != 0);
        for (int digit : digits) {
            (void)digit;
            assert(0 <= digit && digit < base);
        }
        assert(m1une::math::from_base_n<std::uint64_t>(digits, base) == value);
    }

    for (int base = 2; base <= 50; base++) {
        for (int value = 0; value <= 10000; value++) {
            std::vector<int> digits = m1une::math::to_base_n(value, base);
            assert(m1une::math::from_base_n<int>(digits, base) == value);
        }
    }

    std::vector<int> maximum_digits =
        m1une::math::to_base_n(std::numeric_limits<std::uint64_t>::max(), 2);
    assert(m1une::math::from_base_n<std::uint64_t>(maximum_digits, 2) ==
           std::numeric_limits<std::uint64_t>::max());
    maximum_digits.push_back(0);
    assert(!m1une::math::checked_from_base_n<std::uint64_t>(maximum_digits, 2)
                .has_value());
}

int main() {
    fixed_tests();
    randomized_tests();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
