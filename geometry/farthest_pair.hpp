#ifndef M1UNE_GEOMETRY_FARTHEST_PAIR_HPP
#define M1UNE_GEOMETRY_FARTHEST_PAIR_HPP 1

#include <algorithm>
#include <cstddef>
#include <map>
#include <optional>
#include <utility>
#include <vector>

#include "polygon.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct FarthestPair {
    int first;
    int second;
    wide_type<T> distance_squared;
};

// Returns two distinct original indices with maximum Euclidean distance.
template <Coordinate T>
std::optional<FarthestPair<T>> farthest_pair(
    const std::vector<Point<T>>& points
) {
    if (points.size() < 2) return std::nullopt;

    std::vector<Point<T>> hull = convex_hull(points);
    if (hull.size() == 1) {
        FarthestPair<T> result;
        result.first = 0;
        result.second = 1;
        result.distance_squared = 0;
        return result;
    }

    std::map<Point<T>, int> original_index;
    for (int index = 0; index < int(points.size()); ++index) {
        original_index.emplace(points[index], index);
    }

    std::vector<int> hull_index;
    hull_index.reserve(hull.size());
    for (const Point<T>& point : hull) {
        hull_index.push_back(original_index.find(point)->second);
    }

    std::optional<FarthestPair<T>> result;
    auto consider = [&result, &points](int first, int second) {
        if (second < first) std::swap(first, second);
        wide_type<T> squared = distance2(points[first], points[second]);
        if (
            !result.has_value() ||
            result->distance_squared < squared ||
            (
                result->distance_squared == squared &&
                std::pair(first, second) <
                    std::pair(result->first, result->second)
            )
        ) {
            result = FarthestPair<T>{first, second, squared};
        }
    };

    if (hull.size() == 2) {
        consider(hull_index[0], hull_index[1]);
        return result;
    }

    std::size_t opposite = 1;
    for (std::size_t index = 0; index < hull.size(); ++index) {
        std::size_t next = (index + 1) % hull.size();
        while (true) {
            std::size_t candidate = (opposite + 1) % hull.size();
            auto current_area = cross(
                hull[index],
                hull[next],
                hull[opposite]
            );
            auto candidate_area = cross(
                hull[index],
                hull[next],
                hull[candidate]
            );
            if (candidate_area <= current_area) break;
            opposite = candidate;
        }
        consider(hull_index[index], hull_index[opposite]);
        consider(hull_index[next], hull_index[opposite]);

        std::size_t candidate = (opposite + 1) % hull.size();
        auto current_area = cross(hull[index], hull[next], hull[opposite]);
        auto candidate_area = cross(hull[index], hull[next], hull[candidate]);
        if (candidate_area == current_area) {
            consider(hull_index[index], hull_index[candidate]);
            consider(hull_index[next], hull_index[candidate]);
        }
    }
    return result;
}

template <Coordinate T>
std::optional<FarthestPair<T>> furthest_pair(
    const std::vector<Point<T>>& points
) {
    return farthest_pair(points);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_FARTHEST_PAIR_HPP
