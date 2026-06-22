#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "../../../ds/range_query/mo.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../../ds/range_query/fenwick_tree.hpp"

namespace {

void test_randomized() {
    std::uint64_t state = 503;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2500; ++trial) {
        int n = int(random() % 60);
        int query_count = int(random() % 80);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 12);

        m1une::ds::Mo mo(n);
        mo.reserve(query_count);
        std::vector<std::pair<int, int>> ranges;
        for (int query = 0; query < query_count; ++query) {
            int left = int(random() % (n + 1));
            int right = int(random() % (n + 1));
            if (right < left) std::swap(left, right);
            assert(mo.add_query(left, right) == query);
            ranges.emplace_back(left, right);
        }

        std::vector<int> frequency(12);
        std::vector<int> actual(query_count);
        int distinct = 0;
        mo.run(
            [&](int index) {
                if (frequency[values[index]]++ == 0) distinct++;
            },
            [&](int index) {
                if (--frequency[values[index]] == 0) distinct--;
            },
            [&](int query_id) {
                actual[query_id] = distinct;
            }
        );

        for (int query = 0; query < query_count; ++query) {
            std::vector<char> seen(12);
            [[maybe_unused]] int expected = 0;
            for (
                int index = ranges[query].first;
                index < ranges[query].second;
                ++index
            ) {
                if (!seen[values[index]]) {
                    seen[values[index]] = true;
                    expected++;
                }
            }
            assert(actual[query] == expected);
        }
    }
}

std::vector<long long> inversion_queries(
    const std::vector<int>& values,
    const std::vector<std::pair<int, int>>& ranges
) {
    std::vector<int> sorted = values;
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

    std::vector<int> compressed(values.size());
    for (int index = 0; index < int(values.size()); ++index) {
        compressed[index] = int(
            std::lower_bound(sorted.begin(), sorted.end(), values[index])
            - sorted.begin()
        );
    }

    m1une::ds::Mo mo(int(values.size()));
    for (const auto& range : ranges) {
        mo.add_query(range.first, range.second);
    }

    m1une::ds::FenwickTree<int> frequency(int(sorted.size()));
    std::vector<long long> result(ranges.size());
    long long inversions = 0;
    int current_size = 0;

    mo.run(
        [&](int index) {
            int value = compressed[index];
            inversions += frequency.sum(value);
            frequency.add(value, 1);
            current_size++;
        },
        [&](int index) {
            int value = compressed[index];
            inversions += current_size - frequency.sum(value + 1);
            frequency.add(value, 1);
            current_size++;
        },
        [&](int index) {
            int value = compressed[index];
            frequency.add(value, -1);
            current_size--;
            inversions -= frequency.sum(value);
        },
        [&](int index) {
            int value = compressed[index];
            frequency.add(value, -1);
            current_size--;
            inversions -= current_size - frequency.sum(value + 1);
        },
        [&](int query_id) {
            result[query_id] = inversions;
        }
    );
    return result;
}

void test_directional_callbacks() {
    std::uint64_t state = 509;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; ++trial) {
        int n = 1 + int(random() % 45);
        int query_count = 1 + int(random() % 60);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 20);
        std::vector<std::pair<int, int>> ranges;
        for (int query = 0; query < query_count; ++query) {
            int left = int(random() % (n + 1));
            int right = int(random() % (n + 1));
            if (right < left) std::swap(left, right);
            ranges.emplace_back(left, right);
        }

        auto actual = inversion_queries(values, ranges);
        for (int query = 0; query < query_count; ++query) {
            [[maybe_unused]] long long expected = 0;
            for (int i = ranges[query].first; i < ranges[query].second; ++i) {
                for (int j = i + 1; j < ranges[query].second; ++j) {
                    expected += values[i] > values[j];
                }
            }
            assert(actual[query] == expected);
        }
    }
}

}  // namespace

int main() {
    test_randomized();
    test_directional_callbacks();

    int n, q;
    std::cin >> n >> q;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;
    std::vector<std::pair<int, int>> ranges(q);
    for (auto& range : ranges) {
        std::cin >> range.first >> range.second;
    }
    for (long long answer : inversion_queries(values, ranges)) {
        std::cout << answer << '\n';
    }
}
