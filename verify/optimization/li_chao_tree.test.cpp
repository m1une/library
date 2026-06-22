#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include "../../optimization/li_chao_tree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

namespace {

struct SegmentLine {
    int left;
    int right;
    long long slope;
    long long intercept;
};

template <m1une::optimization::LineOptimization Objective>
void check(const std::vector<SegmentLine>& lines) {
    m1une::optimization::LiChaoTree<long long, Objective> tree(-64, 65);
    for (const SegmentLine& line : lines) {
        if (line.left == -64 && line.right == 65) {
            tree.add_line(line.slope, line.intercept);
        } else {
            tree.add_segment(
                line.left,
                line.right,
                line.slope,
                line.intercept
            );
        }
    }

    for (long long x = -64; x < 65; ++x) {
        std::optional<__int128_t> expected;
        for (const SegmentLine& line : lines) {
            if (x < line.left || line.right <= x) continue;
            __int128_t value =
                __int128_t(line.slope) * x + line.intercept;
            if (
                !expected
                || (
                    Objective
                        == m1une::optimization::LineOptimization::Minimize
                    ? value < *expected
                    : *expected < value
                )
            ) {
                expected = value;
            }
        }
        assert(tree.query(x) == expected);
        if (expected) assert(tree.get(x) == *expected);
    }
}

void test_randomized() {
    std::uint64_t state = 1013;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        int count = int(random() % 50);
        std::vector<SegmentLine> lines;
        for (int index = 0; index < count; ++index) {
            int left = int(random() % 129) - 64;
            int right = int(random() % 129) - 64;
            if (right < left) std::swap(left, right);
            if (random() % 3 == 0) {
                left = -64;
                right = 65;
            }
            lines.push_back(SegmentLine{
                left,
                right,
                static_cast<long long>(random() % 101) - 50,
                static_cast<long long>(random() % 201) - 100,
            });
        }
        check<m1une::optimization::LineOptimization::Minimize>(lines);
        check<m1une::optimization::LineOptimization::Maximize>(lines);
    }
}

}  // namespace

int main() {
    test_randomized();

    int line_count, query_count;
    std::cin >> line_count >> query_count;
    constexpr long long left = -1'000'000'000LL;
    constexpr long long right = 1'000'000'001LL;
    m1une::optimization::MinLiChaoTree<long long> tree(left, right);
    for (int index = 0; index < line_count; ++index) {
        long long slope, intercept;
        std::cin >> slope >> intercept;
        tree.add_line(slope, intercept);
    }

    while (query_count--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            long long slope, intercept;
            std::cin >> slope >> intercept;
            tree.add_line(slope, intercept);
        } else {
            long long x;
            std::cin >> x;
            std::cout << static_cast<long long>(tree.get(x)) << '\n';
        }
    }
}
