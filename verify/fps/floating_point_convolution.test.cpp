#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../fps/floating_point_convolution.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

template <class T>
std::vector<T> naive(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    if (first.empty() || second.empty()) return {};
    std::vector<T> result(first.size() + second.size() - 1);
    for (std::size_t i = 0; i < first.size(); ++i) {
        for (std::size_t j = 0; j < second.size(); ++j) {
            result[i + j] += first[i] * second[j];
        }
    }
    return result;
}

void test_fixed() {
    std::vector<double> first = {1.5, 2.0};
    std::vector<double> second = {3.0, -1.0};
    auto result = m1une::fps::convolution_fft(first, second);
    assert(std::fabs(result[0] - 4.5) < 1e-12);
    assert(std::fabs(result[1] - 4.5) < 1e-12);
    assert(std::fabs(result[2] + 2.0) < 1e-12);

    std::vector<std::complex<double>> complex_first;
    complex_first.emplace_back(1, 2);
    complex_first.emplace_back(3, -1);
    std::vector<std::complex<double>> complex_second;
    complex_second.emplace_back(-2, 1);
    complex_second.emplace_back(0, 4);
    auto complex_result =
        m1une::fps::convolution_fft(complex_first, complex_second);
    auto complex_expected = naive(complex_first, complex_second);
    for (std::size_t index = 0; index < complex_result.size(); ++index) {
        assert(std::abs(complex_result[index] - complex_expected[index]) < 1e-11);
    }

    std::vector<long long> integers = {1, -2, 3, 4};
    assert(
        m1une::fps::convolution_round(integers, integers)
        == naive(integers, integers)
    );
    assert(
        m1une::fps::convolution_fft(
            std::vector<double>(),
            std::vector<double>{1}
        ).empty()
    );
}

void test_randomized() {
    std::uint64_t state = 1409;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        int first_size = int(random() % 100);
        int second_size = int(random() % 100);
        std::vector<long double> first(first_size);
        std::vector<long double> second(second_size);
        for (long double& value : first) {
            value =
                (static_cast<long long>(random() % 2001) - 1000) / 100.0L;
        }
        for (long double& value : second) {
            value =
                (static_cast<long long>(random() % 2001) - 1000) / 100.0L;
        }
        auto actual = m1une::fps::convolution_fft(first, second);
        auto expected = naive(first, second);
        for (std::size_t index = 0; index < actual.size(); ++index) {
            long double magnitude = 0;
            for (std::size_t first_index = 0; first_index < first.size(); ++first_index) {
                if (index < first_index) continue;
                std::size_t second_index = index - first_index;
                if (second_index < second.size()) {
                    magnitude += std::fabs(
                        first[first_index] * second[second_index]
                    );
                }
            }
            [[maybe_unused]] long double tolerance =
                1e-12L * std::max(1.0L, magnitude);
            assert(std::fabs(actual[index] - expected[index]) <= tolerance);
        }

        std::vector<long long> integer_first(first_size);
        std::vector<long long> integer_second(second_size);
        for (long long& value : integer_first) {
            value = static_cast<long long>(random() % 2001) - 1000;
        }
        for (long long& value : integer_second) {
            value = static_cast<long long>(random() % 2001) - 1000;
        }
        assert(
            m1une::fps::convolution_round(integer_first, integer_second)
            == naive(integer_first, integer_second)
        );
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
