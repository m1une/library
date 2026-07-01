#ifndef M1UNE_GEOMETRY_CONVEX_HULL_HPP
#define M1UNE_GEOMETRY_CONVEX_HULL_HPP 1

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

// Returns the convex hull counterclockwise from its lexicographically smallest
// point. The first point is not repeated at the end.
template <Coordinate T>
std::vector<Point<T>> convex_hull(
    std::vector<Point<T>> points,
    bool include_collinear = false
) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    std::size_t size = points.size();
    if (size <= 1) return points;

    std::vector<Point<T>> hull;
    hull.reserve(2 * size);
    auto should_pop = [include_collinear](
        const Point<T>& first,
        const Point<T>& second,
        const Point<T>& third
    ) {
        int turn = orientation(first, second, third);
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
    for (std::size_t index = size - 1; index-- > 0;) {
        const Point<T>& point = points[index];
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

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CONVEX_HULL_HPP
