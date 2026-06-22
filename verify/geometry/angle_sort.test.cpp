#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../geometry/angle_sort.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;

long double argument(const Point& point, const Point& origin) {
    long double angle = std::atan2(
        static_cast<long double>(point.y) - origin.y,
        static_cast<long double>(point.x) - origin.x
    );
    if (point == origin) return 0;
    return angle;
}

void test_fixed() {
    std::vector<Point> points;
    points.emplace_back(-1, 0);
    points.emplace_back(0, 1);
    points.emplace_back(2, 0);
    points.emplace_back(0, 0);
    points.emplace_back(0, -1);
    points.emplace_back(1, 0);

    m1une::geometry::sort_by_angle(points);
    std::vector<Point> expected;
    expected.emplace_back(0, -1);
    expected.emplace_back(0, 0);
    expected.emplace_back(1, 0);
    expected.emplace_back(2, 0);
    expected.emplace_back(0, 1);
    expected.emplace_back(-1, 0);
    assert(points == expected);

    auto positive = m1une::geometry::angle_sorted(
        points,
        Point(0, 0),
        m1une::geometry::AngleSortStart::PositiveXAxis
    );
    expected.clear();
    expected.emplace_back(0, 0);
    expected.emplace_back(1, 0);
    expected.emplace_back(2, 0);
    expected.emplace_back(0, 1);
    expected.emplace_back(-1, 0);
    expected.emplace_back(0, -1);
    assert(positive == expected);
}

void test_randomized() {
    std::uint64_t state = 239;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        Point origin(
            static_cast<long long>(random() % 21) - 10,
            static_cast<long long>(random() % 21) - 10
        );
        int size = int(random() % 40);
        std::vector<Point> points;
        points.reserve(size);
        for (int index = 0; index < size; ++index) {
            points.emplace_back(
                static_cast<long long>(random() % 41) - 20,
                static_cast<long long>(random() % 41) - 20
            );
        }

        auto expected = points;
        std::sort(expected.begin(), expected.end(), [&origin](
            const Point& first,
            const Point& second
        ) {
            long double first_angle = argument(first, origin);
            long double second_angle = argument(second, origin);
            if (first_angle != second_angle) return first_angle < second_angle;
            return m1une::geometry::distance2(first, origin)
                   < m1une::geometry::distance2(second, origin);
        });

        m1une::geometry::sort_by_angle(points, origin);
        assert(points == expected);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (Point& point : points) std::cin >> point.x >> point.y;
    m1une::geometry::sort_by_angle(points);
    for (const Point& point : points) {
        std::cout << point.x << ' ' << point.y << '\n';
    }
}
