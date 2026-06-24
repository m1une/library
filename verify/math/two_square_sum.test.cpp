#define PROBLEM "https://judge.yosupo.jp/problem/two_square_sum"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

#include "math/integer_arithmetic.hpp"
#include "math/two_square_sum.hpp"

std::vector<std::pair<uint64_t, uint64_t>> brute_two_square_sum(uint64_t value) {
    std::vector<std::pair<uint64_t, uint64_t>> result;
    for (uint64_t a = 0; a <= value / std::max<uint64_t>(a, 1); a++) {
        const uint64_t remaining = value - a * a;
        const uint64_t b = m1une::math::isqrt(remaining);
        if (b * b == remaining) result.emplace_back(a, b);
    }
    return result;
}

void check_two_square_sum(uint64_t value) {
    std::vector<std::pair<uint64_t, uint64_t>> expected =
        brute_two_square_sum(value);
    std::vector<std::pair<uint64_t, uint64_t>> actual =
        m1une::math::two_square_sum(value);

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(actual == expected);
    assert(m1une::math::represent_as_two_square_sum(value) == actual);
    assert(m1une::math::is_two_square_sum(value) == !expected.empty());

    for (const auto& pair : actual) {
        const uint64_t first = pair.first;
        const uint64_t second = pair.second;
        assert(first * first + second * second == value);
    }
}

void test_small_values() {
    for (uint64_t value = 0; value <= 1000; value++) {
        check_two_square_sum(value);
    }
}

void test_selected_large_values() {
    check_two_square_sum(1000000007ULL);
    check_two_square_sum(1000000009ULL);
    check_two_square_sum(9999999967ULL);
}

int main() {
    test_small_values();
    test_selected_large_values();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        uint64_t value;
        std::cin >> value;
        const std::vector<std::pair<uint64_t, uint64_t>> pairs =
            m1une::math::two_square_sum(value);

        std::cout << pairs.size() << '\n';
        for (const auto& pair : pairs) {
            std::cout << pair.first << ' ' << pair.second << '\n';
        }
    }
}
