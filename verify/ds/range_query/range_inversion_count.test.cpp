#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "../../../ds/range_query/range_inversion_count.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

[[maybe_unused]] long long brute(
    const std::vector<int>& values,
    int left,
    int right
) {
    long long result = 0;
    for (int first = left; first < right; ++first) {
        for (int second = first + 1; second < right; ++second) {
            result += values[first] > values[second];
        }
    }
    return result;
}

void test_randomized() {
    std::uint64_t state = 1511;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        int size = int(random() % 100);
        std::vector<int> values(size);
        for (int& value : values) value = int(random() % 20);
        m1une::ds::RangeInversionCount<int> structure(values);
        assert(structure.size() == size);

        for (int left = 0; left <= size; ++left) {
            for (int right = left; right <= size; ++right) {
                assert(
                    structure.query(left, right)
                    == brute(values, left, right)
                );
            }
        }
    }
}

}  // namespace

int main() {
    test_randomized();

    int n, query_count;
    std::cin >> n >> query_count;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;
    m1une::ds::RangeInversionCount<int> structure(values);
    while (query_count--) {
        int left, right;
        std::cin >> left >> right;
        std::cout << structure.query(left, right) << '\n';
    }
}
