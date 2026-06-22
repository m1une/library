#ifndef M1UNE_GEOMETRY_ANGLE_SORT_HPP
#define M1UNE_GEOMETRY_ANGLE_SORT_HPP 1

#include <algorithm>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

enum class AngleSortStart {
    NegativeXAxis,
    PositiveXAxis,
};

template <Coordinate T>
struct AngleLess {
    Point<T> origin;
    AngleSortStart start;

    constexpr explicit AngleLess(
        Point<T> origin_value = Point<T>(),
        AngleSortStart start_value = AngleSortStart::NegativeXAxis
    ) : origin(origin_value), start(start_value) {}

    constexpr bool operator()(
        const Point<T>& first,
        const Point<T>& second
    ) const {
        using W = wide_type<T>;
        W first_x = W(first.x) - W(origin.x);
        W first_y = W(first.y) - W(origin.y);
        W second_x = W(second.x) - W(origin.x);
        W second_y = W(second.y) - W(origin.y);
        W first_distance = first_x * first_x + first_y * first_y;
        W second_distance = second_x * second_x + second_y * second_y;

        // atan2(0, 0) is treated as angle zero.
        if (first_distance == 0) first_x = 1;
        if (second_distance == 0) second_x = 1;

        auto half = [this](W x, W y) {
            if (start == AngleSortStart::PositiveXAxis) {
                return y < 0 || (y == 0 && x < 0);
            }
            return y > 0 || (y == 0 && x < 0);
        };

        bool first_half = half(first_x, first_y);
        bool second_half = half(second_x, second_y);
        if (first_half != second_half) return first_half < second_half;

        W product = first_x * second_y - first_y * second_x;
        if (product != 0) return product > 0;

        return first_distance < second_distance;
    }
};

// Sorts points counterclockwise by angle around `origin`.
template <Coordinate T>
void sort_by_angle(
    std::vector<Point<T>>& points,
    Point<T> origin = Point<T>(),
    AngleSortStart start = AngleSortStart::NegativeXAxis
) {
    std::sort(points.begin(), points.end(), AngleLess<T>(origin, start));
}

// Returns a counterclockwise angle-sorted copy.
template <Coordinate T>
std::vector<Point<T>> angle_sorted(
    std::vector<Point<T>> points,
    Point<T> origin = Point<T>(),
    AngleSortStart start = AngleSortStart::NegativeXAxis
) {
    sort_by_angle(points, origin, start);
    return points;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_ANGLE_SORT_HPP
