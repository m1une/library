#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../../ds/range_query/wavelet_matrix.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

namespace {

void test_edge_cases() {
    m1une::ds::WaveletMatrix<long long> empty;
    assert(empty.empty());
    assert(empty.size() == 0);

    std::vector<long long> values;
    values.push_back(std::numeric_limits<long long>::min());
    values.push_back(-5);
    values.push_back(0);
    values.push_back(-5);
    values.push_back(std::numeric_limits<long long>::max());

    m1une::ds::WaveletMatrix<long long> matrix(values);
    assert(matrix.size() == 5);
    assert(!matrix.empty());
    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);
    assert(matrix.rank(-5, 5) == 2);
    assert(matrix.rank(-5, 1, 4) == 2);
    assert(matrix.kth_smallest(0, 5, 0) == std::numeric_limits<long long>::min());
    assert(matrix.kth_largest(0, 5, 0) == std::numeric_limits<long long>::max());
    assert(matrix.range_freq(0, 5, 0) == 3);
    assert(matrix.range_freq(0, 5, -5, 1) == 3);
    assert(matrix.prev_value(0, 5, -5).value() == std::numeric_limits<long long>::min());
    assert(matrix.next_value(0, 5, 1).value() == std::numeric_limits<long long>::max());
    assert(!matrix.prev_value(0, 5, std::numeric_limits<long long>::min()));
    assert(
        matrix.next_value(0, 5, std::numeric_limits<long long>::max()).value() ==
        std::numeric_limits<long long>::max()
    );
    assert(!matrix.next_value(1, 4, std::numeric_limits<long long>::max()));

    std::vector<unsigned int> unsigned_values;
    unsigned_values.push_back(0);
    unsigned_values.push_back(std::numeric_limits<unsigned int>::max());
    unsigned_values.push_back(7);
    m1une::ds::WaveletMatrix<unsigned int> unsigned_matrix(unsigned_values);
    assert(unsigned_matrix.kth_smallest(0, 3, 2) == std::numeric_limits<unsigned int>::max());
}

void test_randomized() {
    std::uint64_t state = 17;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 80; trial++) {
        int n = int(random() % 80);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 101) - 50;
        m1une::ds::WaveletMatrix<int> matrix(values);

        for (int query = 0; query < 500; query++) {
            int l = int(random() % std::uint64_t(n + 1));
            int r = int(random() % std::uint64_t(n + 1));
            if (r < l) std::swap(l, r);
            int x = int(random() % 121) - 60;
            int y = int(random() % 121) - 60;
            if (y < x) std::swap(x, y);

            [[maybe_unused]] int rank = 0;
            [[maybe_unused]] int below = 0;
            [[maybe_unused]] int between = 0;
            std::optional<int> previous;
            std::optional<int> next;
            std::vector<int> sorted;
            for (int i = l; i < r; i++) {
                sorted.push_back(values[i]);
                if (values[i] == x) rank++;
                if (values[i] < x) below++;
                if (x <= values[i] && values[i] < y) between++;
                if (values[i] < x && (!previous || *previous < values[i])) {
                    previous = values[i];
                }
                if (x <= values[i] && (!next || values[i] < *next)) {
                    next = values[i];
                }
            }
            std::sort(sorted.begin(), sorted.end());

            assert(matrix.rank(x, l, r) == rank);
            assert(matrix.range_freq(l, r, x) == below);
            assert(matrix.range_freq(l, r, x, y) == between);
            assert(matrix.prev_value(l, r, x) == previous);
            assert(matrix.next_value(l, r, x) == next);
            for (int k = 0; k < int(sorted.size()); k++) {
                assert(matrix.kth_smallest(l, r, k) == sorted[k]);
                assert(matrix.kth_largest(l, r, k) == sorted[sorted.size() - 1 - k]);
            }
        }
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_edge_cases();
    test_randomized();

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    m1une::ds::WaveletMatrix<long long> matrix(values);
    for (int query = 0; query < q; query++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << matrix.kth_smallest(l, r, k) << '\n';
    }
}
