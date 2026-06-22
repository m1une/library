#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/zeta_mobius_transform.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

void test_subset_transforms() {
    const std::vector<long long> original{3, -1, 4, 1, 5, -9, 2, 6};

    std::vector<long long> values = original;
    m1une::math::subset_zeta_transform(values);
    const std::vector<long long> expected_subset{
        3, 2, 7, 7, 8, -2, 14, 11
    };
    assert(values == expected_subset);
    m1une::math::subset_mobius_transform(values);
    assert(values == original);

    values = original;
    m1une::math::superset_zeta_transform(values);
    const std::vector<long long> expected_superset{
        11, -3, 13, 7, 4, -3, 8, 6
    };
    assert(values == expected_superset);
    m1une::math::superset_mobius_transform(values);
    assert(values == original);
}

std::vector<long long> naive_divisor_zeta(
    const std::vector<long long>& values
) {
    std::vector<long long> result = values;
    for (std::size_t value = 1; value < values.size(); ++value) {
        result[value] = 0;
        for (std::size_t divisor = 1; divisor <= value; ++divisor) {
            if (value % divisor == 0) result[value] += values[divisor];
        }
    }
    return result;
}

std::vector<long long> naive_multiple_zeta(
    const std::vector<long long>& values
) {
    std::vector<long long> result = values;
    for (std::size_t value = 1; value < values.size(); ++value) {
        result[value] = 0;
        for (
            std::size_t multiple = value;
            multiple < values.size();
            multiple += value
        ) {
            result[value] += values[multiple];
        }
    }
    return result;
}

void check(const std::vector<long long>& original) {
    std::vector<long long> values = original;
    m1une::math::divisor_zeta_transform(values);
    assert(values == naive_divisor_zeta(original));
    m1une::math::divisor_mobius_transform(values);
    assert(values == original);

    values = original;
    m1une::math::multiple_zeta_transform(values);
    assert(values == naive_multiple_zeta(original));
    m1une::math::multiple_mobius_transform(values);
    assert(values == original);
}

void test_randomized() {
    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; ++trial) {
        const std::size_t size = random() % 80;
        std::vector<long long> values(size);
        for (long long& value : values) {
            value = static_cast<long long>(random() % 101) - 50;
        }
        check(values);
    }
}

}  // namespace

int main() {
    test_subset_transforms();
    check(std::vector<long long>());
    check(std::vector<long long>{7});
    check(std::vector<long long>{7, -3});
    check(std::vector<long long>{11, 1, 2, 3, 4, 5, 6});
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
