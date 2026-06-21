#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-10L;
}

void test_intersections() {
    Circle<long long> circle;
    circle.center = P(0, 0);
    circle.radius = 5;

    Ray<long long> secant;
    secant.origin = P(-10, 0);
    secant.through = P(-9, 0);
    auto points = circle_ray_intersections(circle, secant);
    assert(points.size() == 2);
    assert(close(points[0].x, -5));
    assert(close(points[1].x, 5));
    assert(intersects(circle, secant));
    assert(intersects(secant, circle));

    Ray<long long> inside;
    inside.origin = P(0, 0);
    inside.through = P(1, 0);
    points = circle_ray_intersections(circle, inside);
    assert(points.size() == 1);
    assert(close(points[0].x, 5));

    Ray<long long> tangent;
    tangent.origin = P(-10, 5);
    tangent.through = P(-9, 5);
    points = circle_ray_intersections(circle, tangent);
    assert(points.size() == 1);
    assert(close(points[0].x, 0));
    assert(close(points[0].y, 5));

    Ray<long long> away;
    away.origin = P(10, 0);
    away.through = P(11, 0);
    assert(circle_ray_intersections(circle, away).empty());
    assert(!intersects(circle, away));
    assert(!first_circle_ray_intersection(circle, away).has_value());

    Ray<long long> boundary;
    boundary.origin = P(5, 0);
    boundary.through = P(6, 0);
    points = circle_ray_intersections(circle, boundary);
    assert(points.size() == 1);
    assert(close(points[0].x, 5));

    Circle<long long> point_circle;
    point_circle.center = P(2, 0);
    point_circle.radius = 0;
    points = circle_ray_intersections(point_circle, inside);
    assert(points.size() == 1);
    assert(close(points[0].x, 2));
}

void test_reflection() {
    Circle<long long> circle;
    circle.center = P(0, 0);
    circle.radius = 5;

    Ray<long long> vertical;
    vertical.origin = P(0, 10);
    vertical.through = P(0, 5);
    Ray<long double> vertical_out =
        reflected_ray(vertical, P(0, 5), circle);
    assert(close(vertical_out.origin.x, 0));
    assert(close(vertical_out.origin.y, 5));
    assert(close(vertical_out.through.x, 0));
    assert(close(vertical_out.through.y, 10));

    Ray<long long> oblique;
    oblique.origin = P(-2, 7);
    oblique.through = P(0, 5);
    Ray<long double> oblique_out =
        reflected_ray(oblique, P(0, 5), circle);
    assert(close(oblique_out.through.x, 2));
    assert(close(oblique_out.through.y, 7));

    Point<long double> incoming_direction =
        Point<long double>(oblique.through) -
        Point<long double>(oblique.origin);
    Point<long double> outgoing_direction =
        oblique_out.through - oblique_out.origin;
    assert(close(norm(incoming_direction), norm(outgoing_direction)));
}

void test_randomized_against_lines() {
    std::uint64_t state = 0x987654321abcdefULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 10000; ++trial) {
        Circle<long double> circle;
        circle.center = Point<long double>(
            static_cast<long double>(
                static_cast<long long>(random() % 21) - 10
            ),
            static_cast<long double>(
                static_cast<long long>(random() % 21) - 10
            )
        );
        circle.radius = static_cast<long double>(random() % 8);

        Ray<long double> ray;
        ray.origin = Point<long double>(
            static_cast<long double>(
                static_cast<long long>(random() % 31) - 15
            ),
            static_cast<long double>(
                static_cast<long long>(random() % 31) - 15
            )
        );
        do {
            ray.through = Point<long double>(
                static_cast<long double>(
                    static_cast<long long>(random() % 31) - 15
                ),
                static_cast<long double>(
                    static_cast<long long>(random() % 31) - 15
                )
            );
        } while (ray.origin == ray.through);

        Line<long double> line{ray.origin, ray.through};
        auto line_points = circle_line_intersections(circle, line);
        Point<long double> direction = ray.through - ray.origin;
        std::vector<Point<long double>> expected;
        for (const Point<long double>& point : line_points) {
            if (dot(point - ray.origin, direction) >= -1e-10L) {
                expected.push_back(point);
            }
        }
        std::sort(
            expected.begin(),
            expected.end(),
            [&](const auto& first, const auto& second) {
                return dot(first - ray.origin, direction) <
                       dot(second - ray.origin, direction);
            }
        );

        auto actual = circle_ray_intersections(circle, ray);
        assert(actual.size() == expected.size());
        for (std::size_t index = 0; index < actual.size(); ++index) {
            assert(close(actual[index].x, expected[index].x));
            assert(close(actual[index].y, expected[index].y));
        }
    }
}

}  // namespace

int main() {
    test_intersections();
    test_reflection();
    test_randomized_against_lines();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
