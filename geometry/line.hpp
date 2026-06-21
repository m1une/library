#ifndef M1UNE_GEOMETRY_LINE_HPP
#define M1UNE_GEOMETRY_LINE_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <optional>

#include "point.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct Line {
    Point<T> a;
    Point<T> b;
};

template <Coordinate T>
struct Segment {
    Point<T> a;
    Point<T> b;
};

template <Coordinate T>
bool on_line(
    const Line<T>& line,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    assert(line.a != line.b);
    return orientation(line.a, line.b, point, eps) == 0;
}

template <Coordinate T>
bool parallel(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {
    using W = wide_type<T>;
    W first_x = W(first.b.x) - W(first.a.x);
    W first_y = W(first.b.y) - W(first.a.y);
    W second_x = W(second.b.x) - W(second.a.x);
    W second_y = W(second.b.y) - W(second.a.y);
    return sign<T>(first_x * second_y - first_y * second_x, eps) == 0;
}

template <Coordinate T>
bool orthogonal(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {
    using W = wide_type<T>;
    W first_x = W(first.b.x) - W(first.a.x);
    W first_y = W(first.b.y) - W(first.a.y);
    W second_x = W(second.b.x) - W(second.a.x);
    W second_y = W(second.b.y) - W(second.a.y);
    return sign<T>(first_x * second_x + first_y * second_y, eps) == 0;
}

template <Coordinate T>
Point<long double> projection(const Line<T>& line, const Point<T>& point) {
    assert(line.a != line.b);
    Point<long double> a(line.a);
    Point<long double> direction(
        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)
    );
    Point<long double> offset(
        static_cast<long double>(point.x) - a.x,
        static_cast<long double>(point.y) - a.y
    );
    long double ratio = dot(offset, direction) / dot(direction, direction);
    return a + direction * ratio;
}

template <Coordinate T>
Point<long double> reflection(const Line<T>& line, const Point<T>& point) {
    Point<long double> projected = projection(line, point);
    return projected * 2.0L - Point<long double>(point);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Point<T>& point) {
    assert(line.a != line.b);
    Point<long double> direction(
        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)
    );
    Point<long double> offset(
        static_cast<long double>(point.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(point.y) - static_cast<long double>(line.a.y)
    );
    return std::fabsl(cross(direction, offset)) / norm(direction);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Line<T>& line) {
    return distance(line, point);
}

template <Coordinate T>
bool intersects(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    return !parallel(first, second, eps) || on_line(first, second.a, eps);
}

template <Coordinate T>
long double distance(const Line<T>& first, const Line<T>& second) {
    return intersects(first, second) ? 0 : distance(first, second.a);
}

template <Coordinate T>
bool on_segment(
    const Segment<T>& segment,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    if (orientation(segment.a, segment.b, point, eps) != 0) return false;
    using W = wide_type<T>;
    W px = W(point.x);
    W py = W(point.y);
    W min_x = std::min(W(segment.a.x), W(segment.b.x));
    W max_x = std::max(W(segment.a.x), W(segment.b.x));
    W min_y = std::min(W(segment.a.y), W(segment.b.y));
    W max_y = std::max(W(segment.a.y), W(segment.b.y));
    if constexpr (std::integral<T>) {
        return min_x <= px && px <= max_x && min_y <= py && py <= max_y;
    } else {
        return min_x - eps <= px && px <= max_x + eps &&
               min_y - eps <= py && py <= max_y + eps;
    }
}

template <Coordinate T>
bool intersects(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    int abc = orientation(first.a, first.b, second.a, eps);
    int abd = orientation(first.a, first.b, second.b, eps);
    int cda = orientation(second.a, second.b, first.a, eps);
    int cdb = orientation(second.a, second.b, first.b, eps);

    if (abc == 0 && on_segment(first, second.a, eps)) return true;
    if (abd == 0 && on_segment(first, second.b, eps)) return true;
    if (cda == 0 && on_segment(second, first.a, eps)) return true;
    if (cdb == 0 && on_segment(second, first.b, eps)) return true;
    return abc * abd < 0 && cda * cdb < 0;
}

template <Coordinate T>
bool intersects(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    int first_side = orientation(line.a, line.b, segment.a, eps);
    int second_side = orientation(line.a, line.b, segment.b, eps);
    return first_side == 0 || second_side == 0 || first_side != second_side;
}

template <Coordinate T>
bool intersects(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return intersects(line, segment, eps);
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Point<T>& point) {
    Point<long double> a(segment.a);
    Point<long double> b(segment.b);
    Point<long double> p(point);
    Point<long double> direction = b - a;
    long double length_squared = dot(direction, direction);
    if (length_squared == 0) return geometry::distance(segment.a, point);
    long double ratio = dot(p - a, direction) / length_squared;
    ratio = std::clamp(ratio, 0.0L, 1.0L);
    Point<long double> closest = a + direction * ratio;
    return geometry::distance(closest, p);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Segment<T>& segment) {
    return distance(segment, point);
}

template <Coordinate T>
long double distance(const Segment<T>& first, const Segment<T>& second) {
    if (intersects(first, second)) return 0;
    return std::min({
        distance(first, second.a),
        distance(first, second.b),
        distance(second, first.a),
        distance(second, first.b),
    });
}

template <Coordinate T>
long double distance(const Line<T>& line, const Segment<T>& segment) {
    if (intersects(line, segment)) return 0;
    return std::min(distance(line, segment.a), distance(line, segment.b));
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Line<T>& line) {
    return distance(line, segment);
}

template <Coordinate T>
std::optional<Point<long double>> line_intersection(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    assert(first.a != first.b);
    assert(second.a != second.b);
    Point<long double> p(first.a);
    Point<long double> q(second.a);
    Point<long double> r = Point<long double>(first.b) - p;
    Point<long double> s = Point<long double>(second.b) - q;
    long double denominator = cross(r, s);
    if (std::fabsl(denominator) <= eps) return std::nullopt;
    long double ratio = cross(q - p, s) / denominator;
    return p + r * ratio;
}

template <Coordinate T>
std::optional<Point<long double>> line_segment_intersection(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(line.a != line.b);
    if (segment.a == segment.b) {
        if (on_line(line, segment.a, eps)) {
            return Point<long double>(segment.a);
        }
        return std::nullopt;
    }
    if (!intersects(line, segment, eps)) return std::nullopt;
    Line<T> supporting_line{segment.a, segment.b};
    return line_intersection(line, supporting_line, eps);
}

template <Coordinate T>
std::optional<Point<long double>> line_segment_intersection(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return line_segment_intersection(line, segment, eps);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_LINE_HPP
