#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/farthest_pair.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;
using Result = m1une::geometry::FarthestPair<long long>;

std::optional<Result> brute_force(const std::vector<Point>& points) {
    std::optional<Result> result;
    for (int first = 0; first < int(points.size()); ++first) {
        for (int second = first + 1; second < int(points.size()); ++second) {
            __int128_t squared =
                m1une::geometry::distance2(points[first], points[second]);
            if (
                !result.has_value() ||
                result->distance_squared < squared ||
                (
                    result->distance_squared == squared &&
                    std::pair(first, second) <
                        std::pair(result->first, result->second)
                )
            ) {
                result = Result{first, second, squared};
            }
        }
    }
    return result;
}

void check(const std::vector<Point>& points) {
    auto expected = brute_force(points);
    auto actual = m1une::geometry::farthest_pair(points);
    auto alias = m1une::geometry::furthest_pair(points);
    assert(actual.has_value() == expected.has_value());
    assert(alias.has_value() == actual.has_value());
    if (!expected.has_value()) return;
    assert(actual->first == expected->first);
    assert(actual->second == expected->second);
    assert(actual->distance_squared == expected->distance_squared);
    assert(alias->first == actual->first);
    assert(alias->second == actual->second);
    assert(alias->distance_squared == actual->distance_squared);
}

void test_fixed() {
    check({});
    check({Point(1, 2)});
    check({Point(4, -3), Point(4, -3), Point(4, -3)});
    check({Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)});
    check({
        Point(-5, 0),
        Point(-2, 0),
        Point(3, 0),
        Point(7, 0),
        Point(7, 0),
    });
}

void test_randomized() {
    std::uint64_t state = 173;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 6000; ++trial) {
        int size = int(random() % 25);
        std::vector<Point> points;
        points.reserve(size);
        for (int index = 0; index < size; ++index) {
            points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        check(points);
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
