#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../../../ds/segtree/segtree_beats.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

namespace {

void test_randomized() {
    std::uint64_t state = 1201;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; ++trial) {
        int size = int(random() % 100);
        std::vector<long long> values(size);
        for (long long& value : values) {
            value = static_cast<long long>(random() % 201) - 100;
        }
        m1une::ds::SegtreeBeats<long long> seg(values);

        for (int operation = 0; operation < 1000; ++operation) {
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (right < left) std::swap(left, right);
            int type = int(random() % 8);
            long long value =
                static_cast<long long>(random() % 101) - 50;

            if (type == 0) {
                seg.chmin(left, right, value);
                for (int index = left; index < right; ++index) {
                    values[index] = std::min(values[index], value);
                }
            } else if (type == 1) {
                seg.chmax(left, right, value);
                for (int index = left; index < right; ++index) {
                    values[index] = std::max(values[index], value);
                }
            } else if (type == 2) {
                seg.add(left, right, value);
                for (int index = left; index < right; ++index) {
                    values[index] += value;
                }
            } else if (type == 3 && left < right) {
                [[maybe_unused]] long long expected =
                    *std::min_element(
                        values.begin() + left,
                        values.begin() + right
                    );
                assert(seg.min(left, right) == expected);
            } else if (type == 4 && left < right) {
                [[maybe_unused]] long long expected =
                    *std::max_element(
                        values.begin() + left,
                        values.begin() + right
                    );
                assert(seg.max(left, right) == expected);
            } else if (type == 5 && size != 0) {
                int index = int(random() % size);
                seg.set(index, value);
                values[index] = value;
            } else {
                [[maybe_unused]] long long expected = std::accumulate(
                    values.begin() + left,
                    values.begin() + right,
                    0LL
                );
                assert(seg.sum(left, right) == expected);
            }

            assert(seg.to_vector() == values);
            assert(
                seg.all_sum()
                == std::accumulate(values.begin(), values.end(), 0LL)
            );
            if (!values.empty()) {
                assert(
                    seg.all_min()
                    == *std::min_element(values.begin(), values.end())
                );
                assert(
                    seg.all_max()
                    == *std::max_element(values.begin(), values.end())
                );
            }
        }
    }
}

}  // namespace

int main() {
    test_randomized();

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;
    m1une::ds::SegtreeBeats<long long> seg(values);

    while (q--) {
        int type, left, right;
        std::cin >> type >> left >> right;
        if (type == 0) {
            long long value;
            std::cin >> value;
            seg.chmin(left, right, value);
        } else if (type == 1) {
            long long value;
            std::cin >> value;
            seg.chmax(left, right, value);
        } else if (type == 2) {
            long long value;
            std::cin >> value;
            seg.add(left, right, value);
        } else {
            std::cout << seg.sum(left, right) << '\n';
        }
    }
}
