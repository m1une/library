#ifndef M1UNE_GEOMETRY_CIRCLE_HPP
#define M1UNE_GEOMETRY_CIRCLE_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

#include "line.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct Circle {
    Point<T> center;
    T radius;
};

enum class CircleRelation {
    Separate,
    ExternallyTangent,
    Intersecting,
    InternallyTangent,
    Contained,
    Coincident,
};

template <Coordinate T>
CircleRelation circle_relation(
    const Circle<T>& first,
    const Circle<T>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    long double d = geometry::distance(first.center, second.center);
    long double r1 = static_cast<long double>(first.radius);
    long double r2 = static_cast<long double>(second.radius);
    long double sum = r1 + r2;
    long double difference = std::fabsl(r1 - r2);
    if (d <= eps && difference <= eps) return CircleRelation::Coincident;
    if (sum < d - eps) return CircleRelation::Separate;
    if (std::fabsl(d - sum) <= eps) return CircleRelation::ExternallyTangent;
    if (d < difference - eps) return CircleRelation::Contained;
    if (std::fabsl(d - difference) <= eps) return CircleRelation::InternallyTangent;
    return CircleRelation::Intersecting;
}

template <Coordinate T>
std::vector<Point<long double>> circle_line_intersections(
    const Circle<T>& circle,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(line.a != line.b);
    Point<long double> foot = projection(line, circle.center);
    long double radius = static_cast<long double>(circle.radius);
    long double distance_to_line = geometry::distance(line, circle.center);
    if (radius < distance_to_line - eps) return {};

    Point<long double> direction =
        Point<long double>(line.b) - Point<long double>(line.a);
    direction = normalized(direction);
    long double offset_squared =
        std::max(0.0L, radius * radius - distance_to_line * distance_to_line);
    long double offset = std::sqrt(offset_squared);
    if (offset <= eps) return {foot};

    Point<long double> first = foot - direction * offset;
    Point<long double> second = foot + direction * offset;
    if (second < first) std::swap(first, second);
    return {first, second};
}

template <Coordinate T>
std::vector<Point<long double>> circle_intersections(
    const Circle<T>& first,
    const Circle<T>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    CircleRelation relation = circle_relation(first, second, eps);
    if (
        relation == CircleRelation::Separate ||
        relation == CircleRelation::Contained ||
        relation == CircleRelation::Coincident
    ) {
        return {};
    }

    Point<long double> c1(first.center);
    Point<long double> c2(second.center);
    Point<long double> direction = c2 - c1;
    long double d = norm(direction);
    long double r1 = static_cast<long double>(first.radius);
    long double r2 = static_cast<long double>(second.radius);
    long double along = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    long double height_squared = std::max(0.0L, r1 * r1 - along * along);
    Point<long double> unit = direction / d;
    Point<long double> base = c1 + unit * along;
    long double height = std::sqrt(height_squared);
    if (height <= eps) return {base};

    Point<long double> perpendicular(-unit.y, unit.x);
    Point<long double> a = base - perpendicular * height;
    Point<long double> b = base + perpendicular * height;
    if (b < a) std::swap(a, b);
    return {a, b};
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CIRCLE_HPP
