#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/all.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

bool close(long double a, long double b) {
    return std::fabs(a - b) <= 1e-10L;
}

void test_basic() {
    using namespace m1une::geometry;
    using P = Point<long long>;

    P a(0, 0);
    P b(3, 0);
    P c(1, 2);
    assert(cross(a, b, c) == 6);
    assert(orientation(a, b, c) == 1);
    assert(orientation(a, c, b) == -1);
    assert(collinear(a, P(1, 0), b));

    P division_start(0, 2);
    P division_end(10, 12);
    Point<long double> internal =
        internal_division_point(division_start, division_end, 2, 3);
    assert(close(internal.x, 4));
    assert(close(internal.y, 6));

    Point<long double> external_after =
        external_division_point(division_start, division_end, 2, 1);
    assert(close(external_after.x, 20));
    assert(close(external_after.y, 22));

    Point<long double> external_before =
        external_division_point(division_start, division_end, 1, 2);
    assert(close(external_before.x, -10));
    assert(close(external_before.y, -8));

    Segment<long long> first;
    first.a = P(0, 0);
    first.b = P(4, 4);
    Segment<long long> second;
    second.a = P(0, 4);
    second.b = P(4, 0);
    assert(intersects(first, second));
    assert(close(distance(first, second), 0));

    Line<long long> horizontal;
    horizontal.a = P(0, 0);
    horizontal.b = P(4, 0);
    [[maybe_unused]] Point<long double> projected = projection(horizontal, P(2, 3));
    assert(close(projected.x, 2));
    assert(close(projected.y, 0));

    Line<long long> diagonal1;
    diagonal1.a = P(0, 0);
    diagonal1.b = P(2, 2);
    Line<long long> diagonal2;
    diagonal2.a = P(0, 2);
    diagonal2.b = P(2, 0);
    [[maybe_unused]] auto crossing = line_intersection(diagonal1, diagonal2);
    assert(crossing.has_value());
    assert(close(crossing->x, 1));
    assert(close(crossing->y, 1));

    std::vector<P> square;
    square.emplace_back(0, 0);
    square.emplace_back(2, 0);
    square.emplace_back(2, 2);
    square.emplace_back(0, 2);
    assert(polygon_area2(square) == 8);
    assert(point_in_polygon(square, P(1, 1)) == PointInPolygon::Inside);
    assert(point_in_polygon(square, P(0, 1)) == PointInPolygon::Boundary);
    assert(point_in_polygon(square, P(3, 1)) == PointInPolygon::Outside);
    assert(convex_diameter2(square) == 8);

    Circle<long double> circle;
    circle.center = Point<long double>(0, 0);
    circle.radius = 2;
    Line<long double> line;
    line.a = Point<long double>(-3, 0);
    line.b = Point<long double>(3, 0);
    auto intersections = circle_line_intersections(circle, line);
    assert(intersections.size() == 2);
    assert(close(intersections[0].x, -2));
    assert(close(intersections[1].x, 2));

    Circle<long double> other;
    other.center = Point<long double>(3, 0);
    other.radius = 2;
    assert(circle_relation(circle, other) == CircleRelation::Intersecting);
    auto circle_points = circle_intersections(circle, other);
    assert(circle_points.size() == 2);
    for ([[maybe_unused]] const auto& point : circle_points) {
        assert(close(distance(point, circle.center), circle.radius));
        assert(close(distance(point, other.center), other.radius));
    }

    std::vector<P> collinear_points;
    collinear_points.emplace_back(2, 0);
    collinear_points.emplace_back(0, 0);
    collinear_points.emplace_back(1, 0);
    assert(convex_hull(collinear_points).size() == 2);
    assert(convex_hull(collinear_points, true) == std::vector<P>({P(0, 0), P(1, 0), P(2, 0)}));
}

void test_randomized_hulls() {
    using namespace m1une::geometry;
    using P = Point<long long>;
    std::uint64_t state = 41;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int n = int(random() % 30);
        std::vector<P> points;
        for (int i = 0; i < n; i++) {
            points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        std::vector<P> hull = convex_hull(points);
        if (hull.size() >= 3) {
            assert(polygon_area2(hull) > 0);
            for (std::size_t i = 0; i < hull.size(); i++) {
                assert(orientation(
                    hull[i],
                    hull[(i + 1) % hull.size()],
                    hull[(i + 2) % hull.size()]
                ) > 0);
            }

            auto expected_diameter = wide_type<long long>(0);
            for (const P& a : hull) {
                for (const P& b : hull) {
                    expected_diameter = std::max(expected_diameter, distance2(a, b));
                }
            }
            assert(convex_diameter2(hull) == expected_diameter);
        }

        for ([[maybe_unused]] const P& point : points) {
            if (hull.size() >= 3) {
                assert(point_in_polygon(hull, point) != PointInPolygon::Outside);
            } else if (hull.size() == 2) {
                Segment<long long> segment;
                segment.a = hull[0];
                segment.b = hull[1];
                assert(on_segment(segment, point));
            } else if (hull.size() == 1) {
                assert(point == hull[0]);
            }
        }
    }
}

}  // namespace

int main() {
    test_basic();
    test_randomized_hulls();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
