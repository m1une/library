#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "ds/range_query/wavelet_matrix_sum.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

namespace {

void test_value_sums() {
    std::vector<long long> values;
    values.push_back(std::numeric_limits<long long>::min());
    values.push_back(-5);
    values.push_back(0);
    values.push_back(-5);
    values.push_back(std::numeric_limits<long long>::max());

    m1une::ds::WaveletMatrixSum<long long, __int128_t> matrix(values);
    assert(matrix.size() == 5);
    assert(!matrix.empty());
    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);

    [[maybe_unused]] __int128_t total = 0;
    for (long long value : values) total += value;
    assert(matrix.range_sum(0, 5) == total);
    assert(matrix.range_sum(0, 5, 0LL) ==
           __int128_t(std::numeric_limits<long long>::min()) - 10);
    assert(matrix.range_sum(0, 5, -5LL, 1LL) == -10);
    assert(matrix.sum_k_smallest(0, 5, 0) == 0);
    assert(matrix.sum_k_smallest(0, 5, 3) ==
           __int128_t(std::numeric_limits<long long>::min()) - 10);
    assert(matrix.sum_k_largest(0, 5, 2) ==
           __int128_t(std::numeric_limits<long long>::max()));
    assert(matrix.sum_k_largest(0, 5, 5) == total);
}

void test_weighted_ties() {
    std::vector<int> values;
    values.push_back(4);
    values.push_back(1);
    values.push_back(4);
    values.push_back(2);
    std::vector<long long> weights;
    weights.push_back(10);
    weights.push_back(20);
    weights.push_back(30);
    weights.push_back(40);

    m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);
    assert(matrix.range_sum(0, 4) == 100);
    assert(matrix.range_sum(0, 4, 2) == 20);
    assert(matrix.range_sum(0, 4, 2, 5) == 80);
    assert(matrix.sum_k_smallest(0, 4, 3) == 70);
    assert(matrix.sum_k_largest(0, 4, 1) == 30);
    assert(matrix.sum_k_largest(0, 4, 2) == 40);
}

void test_randomized() {
    std::uint64_t state = 23;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 70; trial++) {
        int n = int(random() % 70);
        std::vector<int> values(n);
        std::vector<long long> weights(n);
        for (int i = 0; i < n; i++) {
            values[i] = int(random() % 61) - 30;
            weights[i] = static_cast<long long>(random() % 101) - 50;
        }
        m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);

        for (int query = 0; query < 500; query++) {
            int l = int(random() % std::uint64_t(n + 1));
            int r = int(random() % std::uint64_t(n + 1));
            if (r < l) std::swap(l, r);
            int lower = int(random() % 81) - 40;
            int upper = int(random() % 81) - 40;
            if (upper < lower) std::swap(lower, upper);

            [[maybe_unused]] long long total = 0;
            [[maybe_unused]] long long below = 0;
            [[maybe_unused]] long long between = 0;
            std::vector<std::pair<int, int>> order;
            for (int i = l; i < r; i++) {
                total += weights[i];
                if (values[i] < upper) below += weights[i];
                if (lower <= values[i] && values[i] < upper) {
                    between += weights[i];
                }
                order.emplace_back(values[i], i);
            }
            std::stable_sort(order.begin(), order.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;
            });

            assert(matrix.range_sum(l, r) == total);
            assert(matrix.range_freq(l, r, upper) ==
                   int(std::count_if(
                       values.begin() + l,
                       values.begin() + r,
                       [upper](int value) { return value < upper; }
                   )));
            assert(matrix.range_sum(l, r, upper) == below);
            assert(matrix.range_sum(l, r, lower, upper) == between);

            [[maybe_unused]] long long smallest_sum = 0;
            [[maybe_unused]] long long largest_sum = 0;
            for (int k = 0; k <= int(order.size()); k++) {
                assert(matrix.sum_k_smallest(l, r, k) == smallest_sum);
                assert(matrix.sum_k_largest(l, r, k) == largest_sum);
                if (k < int(order.size())) {
                    smallest_sum += weights[order[k].second];
                    largest_sum += weights[order[order.size() - 1 - k].second];
                }
            }
        }
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_value_sums();
    test_weighted_ties();
    test_randomized();

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    m1une::ds::WaveletMatrixSum<long long> matrix(values);
    for (int query = 0; query < q; query++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << matrix.kth_smallest(l, r, k) << '\n';
    }
}
