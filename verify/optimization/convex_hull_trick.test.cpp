#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../optimization/convex_hull_trick.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

namespace {

struct Line {
    long long slope;
    long long intercept;
};

template <m1une::optimization::LineOptimization Objective>
void check(const std::vector<Line>& lines) {
    m1une::optimization::ConvexHullTrick<long long, Objective> cht;
    for (const Line& line : lines) {
        cht.add_line(line.slope, line.intercept);
    }

    for (long long x = -100; x <= 100; ++x) {
        __int128_t expected;
        if constexpr (
            Objective == m1une::optimization::LineOptimization::Minimize
        ) {
            expected = std::numeric_limits<__int128_t>::max();
        } else {
            expected = std::numeric_limits<__int128_t>::min();
        }
        for (const Line& line : lines) {
            __int128_t value =
                __int128_t(line.slope) * x + line.intercept;
            if constexpr (
                Objective == m1une::optimization::LineOptimization::Minimize
            ) {
                expected = std::min(expected, value);
            } else {
                expected = std::max(expected, value);
            }
        }
        assert(cht.query(x) == expected);
    }
}

void test_fixed() {
    m1une::optimization::MinConvexHullTrick<long long> empty;
    assert(!empty.try_query(0).has_value());

    std::vector<Line> lines;
    lines.push_back(Line{-3, 4});
    lines.push_back(Line{-1, 10});
    lines.push_back(Line{-1, -5});
    lines.push_back(Line{0, 2});
    lines.push_back(Line{4, -7});
    check<m1une::optimization::LineOptimization::Minimize>(lines);
    check<m1une::optimization::LineOptimization::Maximize>(lines);
}

void test_randomized() {
    std::uint64_t state = 1009;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        int count = 1 + int(random() % 40);
        std::vector<Line> lines;
        long long slope = -50;
        for (int index = 0; index < count; ++index) {
            slope += int(random() % 4);
            lines.push_back(Line{
                slope,
                static_cast<long long>(random() % 201) - 100,
            });
        }
        check<m1une::optimization::LineOptimization::Minimize>(lines);
        check<m1une::optimization::LineOptimization::Maximize>(lines);
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
