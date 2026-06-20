#ifndef M1UNE_GEOMETRY_POLYGON_HPP
#define M1UNE_GEOMETRY_POLYGON_HPP 1

#include <algorithm>
#include <cmath>
#include <vector>

#include "line.hpp"

namespace m1une {
namespace geometry {

enum class PointInPolygon {
    Outside = 0,
    Boundary = 1,
    Inside = 2,
};

template <Coordinate T>
wide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {
    wide_type<T> result = 0;
    int n = int(polygon.size());
    for (int i = 0; i < n; i++) {
        result += cross(polygon[i], polygon[(i + 1) % n]);
    }
    return result;
}

template <Coordinate T>
long double polygon_area(const std::vector<Point<T>>& polygon) {
    return std::fabsl(static_cast<long double>(polygon_area2(polygon))) / 2;
}

template <Coordinate T>
std::vector<Point<T>> convex_hull(
    std::vector<Point<T>> points,
    bool include_collinear = false
) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    int n = int(points.size());
    if (n <= 1) return points;

    std::vector<Point<T>> hull;
    hull.reserve(2 * n);
    auto should_pop = [include_collinear](
        const Point<T>& a,
        const Point<T>& b,
        const Point<T>& c
    ) {
        int turn = orientation(a, b, c);
        return include_collinear ? turn < 0 : turn <= 0;
    };

    for (const Point<T>& point : points) {
        while (
            hull.size() >= 2 &&
            should_pop(hull[hull.size() - 2], hull.back(), point)
        ) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    std::size_t lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        const Point<T>& point = points[i];
        while (
            hull.size() > lower_size &&
            should_pop(hull[hull.size() - 2], hull.back(), point)
        ) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    hull.pop_back();

    if (include_collinear && hull.size() == 2 * points.size() - 2) {
        hull = std::move(points);
    }
    return hull;
}

template <Coordinate T>
PointInPolygon point_in_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    bool inside = false;
    int n = int(polygon.size());
    for (int i = 0; i < n; i++) {
        const Point<T>& a = polygon[i];
        const Point<T>& b = polygon[(i + 1) % n];
        if (on_segment(Segment<T>{a, b}, point, eps)) {
            return PointInPolygon::Boundary;
        }

        if (a.y <= point.y) {
            if (point.y < b.y && orientation(a, b, point, eps) > 0) {
                inside = !inside;
            }
        } else if (b.y <= point.y && orientation(a, b, point, eps) < 0) {
            inside = !inside;
        }
    }
    return inside ? PointInPolygon::Inside : PointInPolygon::Outside;
}

template <Coordinate T>
wide_type<T> convex_diameter2(const std::vector<Point<T>>& polygon) {
    int n = int(polygon.size());
    if (n <= 1) return 0;
    if (n == 2) return distance2(polygon[1], polygon[0]);

    wide_type<T> result = 0;
    int opposite = 1;
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        while (true) {
            int candidate = (opposite + 1) % n;
            auto current_area = cross(polygon[i], polygon[next], polygon[opposite]);
            auto candidate_area = cross(polygon[i], polygon[next], polygon[candidate]);
            if (candidate_area <= current_area) break;
            opposite = candidate;
        }
        result = std::max(result, distance2(polygon[i], polygon[opposite]));
        result = std::max(result, distance2(polygon[next], polygon[opposite]));
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_POLYGON_HPP
