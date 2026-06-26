#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../../math/bitwise_convolution.hpp"
#include "../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using m1une::math::bitwise_and_convolution;
using m1une::math::bitwise_or_convolution;
using m1une::math::bitwise_xor_convolution;

template <typename T, typename Operation>
std::vector<T> naive(
    const std::vector<T>& first,
    const std::vector<T>& second,
    Operation operation
) {
    if (first.empty() || second.empty()) return {};
    std::size_t size = 1;
    while (size < first.size() || size < second.size()) size <<= 1;
    std::vector<T> result(size);
    for (std::size_t i = 0; i < first.size(); ++i) {
        for (std::size_t j = 0; j < second.size(); ++j) {
            result[operation(i, j)] += first[i] * second[j];
        }
    }
    return result;
}

void test_transforms() {
    std::vector<long long> original{3, -1, 4, 1, 5, -9, 2, 6};

    std::vector<long long> values = original;
    m1une::math::subset_zeta_transform(values);
    m1une::math::subset_mobius_transform(values);
    assert(values == original);

    values = original;
    m1une::math::superset_zeta_transform(values);
    m1une::math::superset_mobius_transform(values);
    assert(values == original);

    values = original;
    m1une::math::walsh_hadamard_transform(values);
    m1une::math::walsh_hadamard_transform(values, true);
    assert(values == original);
}

template <typename T>
void check_convolutions(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    assert(
        bitwise_or_convolution(first, second) ==
        naive(first, second, [](std::size_t i, std::size_t j) {
            return i | j;
        })
    );
    assert(
        bitwise_and_convolution(first, second) ==
        naive(first, second, [](std::size_t i, std::size_t j) {
            return i & j;
        })
    );
    assert(
        bitwise_xor_convolution(first, second) ==
        naive(first, second, [](std::size_t i, std::size_t j) {
            return i ^ j;
        })
    );
}

void test_randomized() {
    std::uint64_t state = 0x1234fedcba98765ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        std::size_t first_size = random() % 18;
        std::size_t second_size = random() % 18;
        std::vector<long long> first(first_size);
        std::vector<long long> second(second_size);
        for (long long& value : first) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        for (long long& value : second) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        check_convolutions(first, second);
    }
}

void test_modint() {
    using mint = m1une::math::modint998244353;
    std::vector<mint> first;
    std::vector<mint> second;
    for (int value = 0; value < 13; ++value) {
        first.emplace_back(value * value - 7);
    }
    for (int value = 0; value < 9; ++value) {
        second.emplace_back(value * 3 + 1);
    }
    check_convolutions(first, second);
}

}  // namespace

int main() {
    test_transforms();
    test_randomized();
    test_modint();

    int n;
    std::cin >> n;
    int size = 1 << n;
    using mint = m1une::math::modint998244353;
    std::vector<mint> a(size), b(size);
    for (int i = 0; i < size; i++) {
        long long x;
        std::cin >> x;
        a[i] = x;
    }
    for (int i = 0; i < size; i++) {
        long long x;
        std::cin >> x;
        b[i] = x;
    }
    std::vector<mint> c = bitwise_xor_convolution(a, b);
    for (int i = 0; i < size; i++) {
        if (i) std::cout << ' ';
        std::cout << c[i].val();
    }
    std::cout << '\n';
}
