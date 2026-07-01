#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../fps/convolution_ll.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#ifndef NDEBUG
namespace {

std::vector<long long> naive(const std::vector<long long>& first,
                             const std::vector<long long>& second) {
    if (first.empty() || second.empty()) return {};
    std::vector<__int128> wide(first.size() + second.size() - 1);
    for (int i = 0; i < int(first.size()); i++) {
        for (int j = 0; j < int(second.size()); j++) {
            wide[i + j] += static_cast<__int128>(first[i]) * second[j];
        }
    }
    std::vector<long long> result(wide.size());
    for (int i = 0; i < int(wide.size()); i++) {
        assert(std::numeric_limits<long long>::min() <= wide[i]);
        assert(wide[i] <= std::numeric_limits<long long>::max());
        result[i] = static_cast<long long>(wide[i]);
    }
    return result;
}

void fixed_tests() {
    using m1une::fps::convolution_ll;
    assert(convolution_ll({}, std::vector<long long>{1}).empty());
    assert(convolution_ll(std::vector<long long>{1, -2, 3},
                          std::vector<long long>{4, 5}) ==
           std::vector<long long>({4, -3, 2, 15}));
    assert(convolution_ll(std::vector<long long>{std::numeric_limits<long long>::max()},
                          std::vector<long long>{1}) ==
           std::vector<long long>({std::numeric_limits<long long>::max()}));
    assert(convolution_ll(std::vector<long long>{std::numeric_limits<long long>::min()},
                          std::vector<long long>{1}) ==
           std::vector<long long>({std::numeric_limits<long long>::min()}));
    assert(convolution_ll(
               std::vector<long long>{std::numeric_limits<long long>::max(),
                                      std::numeric_limits<long long>::max()},
               std::vector<long long>{1, -1}) ==
           std::vector<long long>({std::numeric_limits<long long>::max(), 0,
                                   -std::numeric_limits<long long>::max()}));
}

void randomized_tests() {
    std::mt19937_64 random(123456789);
    for (int trial = 0; trial < 3000; trial++) {
        int first_size = int(random() % 100);
        int second_size = int(random() % 100);
        std::vector<long long> first(first_size);
        std::vector<long long> second(second_size);
        for (long long& value : first) value = int(random() % 2000001) - 1000000;
        for (long long& value : second) value = int(random() % 2000001) - 1000000;
        assert(m1une::fps::convolution_ll(first, second) == naive(first, second));
    }
}

}  // namespace
#endif

int main() {
#ifndef NDEBUG
    fixed_tests();
    randomized_tests();
#endif

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
