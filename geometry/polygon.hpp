#ifndef M1UNE_GEOMETRY_POLYGON_HPP
#define M1UNE_GEOMETRY_POLYGON_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <vector>

#include "convex_hull.hpp"
#include "ray.hpp"

namespace m1une {
namespace geometry {

enum class PointInPolygon {
    Outside = 0,
    Boundary = 1,
    Inside = 2,
};

namespace polygon_detail {

inline bool close(
    const Point<long double>& first,
    const Point<long double>& second,
    long double eps
) {
    return geometry::distance(first, second) <= eps;
}

inline void push_unique(
    std::vector<Point<long double>>& points,
    const Point<long double>& point,
    long double eps
) {
    for (const Point<long double>& existing : points) {
        if (close(existing, point, eps)) return;
    }
    points.push_back(point);
}

inline std::vector<Point<long double>> clean_convex_polygon(
    std::vector<Point<long double>> polygon,
    long double eps
) {
    if (polygon.empty()) return polygon;

    std::vector<Point<long double>> deduplicated;
    for (const Point<long double>& point : polygon) {
        if (
            deduplicated.empty() ||
            !close(deduplicated.back(), point, eps)
        ) {
            deduplicated.push_back(point);
        }
    }
    if (
        deduplicated.size() >= 2 &&
        close(deduplicated.front(), deduplicated.back(), eps)
    ) {
        deduplicated.pop_back();
    }
    if (deduplicated.size() <= 2) return deduplicated;

    bool changed = true;
    while (changed && deduplicated.size() >= 3) {
        changed = false;
        std::vector<Point<long double>> cleaned;
        std::size_t size = deduplicated.size();
        for (std::size_t index = 0; index < size; ++index) {
            const Point<long double>& previous =
                deduplicated[(index + size - 1) % size];
            const Point<long double>& current = deduplicated[index];
            const Point<long double>& next =
                deduplicated[(index + 1) % size];
            if (
                orientation(previous, current, next, eps) == 0 &&
                dot(current - previous, next - current) >= -eps
            ) {
                changed = true;
            } else {
                cleaned.push_back(current);
            }
        }
        deduplicated = std::move(cleaned);
    }
    return deduplicated;
}

template <Coordinate T>
std::vector<Point<T>> normalize_convex_polygon(
    std::vector<Point<T>> polygon
) {
    if (
        polygon.size() >= 2 &&
        polygon.front() == polygon.back()
    ) {
        polygon.pop_back();
    }
    if (polygon.size() <= 1) return polygon;
    if (polygon.size() >= 3 && polygon_area2(polygon) < 0) {
        std::reverse(polygon.begin(), polygon.end());
    }

    auto start = std::min_element(
        polygon.begin(),
        polygon.end(),
        [](const Point<T>& first, const Point<T>& second) {
            if (first.y != second.y) return first.y < second.y;
            return first.x < second.x;
        }
    );
    std::rotate(polygon.begin(), start, polygon.end());

    if (polygon.size() <= 2) return polygon;
    std::vector<Point<T>> cleaned;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& previous = polygon[(index + size - 1) % size];
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        if (
            orientation(previous, current, next) != 0 ||
            dot(current - previous, next - current) < 0
        ) {
            cleaned.push_back(current);
        }
    }
    return cleaned;
}

template <Coordinate T>
std::vector<Point<T>> clean_polygon_vertices(
    std::vector<Point<T>> polygon,
    long double eps
) {
    if (
        polygon.size() >= 2 &&
        polygon.front() == polygon.back()
    ) {
        polygon.pop_back();
    }

    std::vector<Point<T>> deduplicated;
    for (const Point<T>& point : polygon) {
        if (deduplicated.empty() || deduplicated.back() != point) {
            deduplicated.push_back(point);
        }
    }
    if (
        deduplicated.size() >= 2 &&
        deduplicated.front() == deduplicated.back()
    ) {
        deduplicated.pop_back();
    }

    bool changed = true;
    while (changed && deduplicated.size() >= 3) {
        changed = false;
        std::vector<Point<T>> cleaned;
        std::size_t size = deduplicated.size();
        for (std::size_t index = 0; index < size; ++index) {
            const Point<T>& previous =
                deduplicated[(index + size - 1) % size];
            const Point<T>& current = deduplicated[index];
            const Point<T>& next =
                deduplicated[(index + 1) % size];
            if (
                orientation(previous, current, next, eps) == 0 &&
                sign<T>(dot(current - previous, next - current), eps) >= 0
            ) {
                changed = true;
            } else {
                cleaned.push_back(current);
            }
        }
        deduplicated = std::move(cleaned);
    }
    return deduplicated;
}

template <Coordinate T>
bool in_ccw_triangle(
    const Point<T>& point,
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps
) {
    return
        orientation(first, second, point, eps) >= 0 &&
        orientation(second, third, point, eps) >= 0 &&
        orientation(third, first, point, eps) >= 0;
}

}  // namespace polygon_detail

template <Coordinate T>
wide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {
    wide_type<T> result = 0;
    std::size_t n = polygon.size();
    for (std::size_t i = 0; i < n; i++) {
        result += cross(polygon[i], polygon[(i + 1) % n]);
    }
    return result;
}

template <Coordinate T>
long double polygon_area(const std::vector<Point<T>>& polygon) {
    return std::fabs(static_cast<long double>(polygon_area2(polygon))) / 2;
}

template <Coordinate T>
std::optional<Point<long double>> polygon_centroid(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    if (polygon.size() < 3) return std::nullopt;

    wide_type<T> signed_area2 = polygon_area2(polygon);
    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;

    long double x_numerator = 0;
    long double y_numerator = 0;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        long double weight = static_cast<long double>(cross(current, next));
        x_numerator +=
            (static_cast<long double>(current.x) +
             static_cast<long double>(next.x)) *
            weight;
        y_numerator +=
            (static_cast<long double>(current.y) +
             static_cast<long double>(next.y)) *
            weight;
    }
    long double denominator =
        3.0L * static_cast<long double>(signed_area2);
    return Point<long double>(
        x_numerator / denominator,
        y_numerator / denominator
    );
}

template <Coordinate T>
std::optional<Point<long double>> polygon_center_of_gravity(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    return polygon_centroid(polygon, eps);
}

template <Coordinate T>
bool is_simple_polygon(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    if (polygon.size() < 3) return false;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& previous = polygon[(index + size - 1) % size];
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        if (current == next) return false;
        if (
            orientation(previous, current, next, eps) == 0 &&
            sign<T>(dot(current - previous, next - current), eps) < 0
        ) {
            return false;
        }
    }
    for (std::size_t first_index = 0; first_index < size; ++first_index) {
        Segment<T> first{
            polygon[first_index],
            polygon[(first_index + 1) % size]
        };
        for (
            std::size_t second_index = first_index + 1;
            second_index < size;
            ++second_index
        ) {
            bool adjacent =
                second_index == first_index + 1 ||
                (first_index == 0 && second_index + 1 == size);
            if (adjacent) continue;

            Segment<T> second{
                polygon[second_index],
                polygon[(second_index + 1) % size]
            };
            if (intersects(first, second, eps)) return false;
        }
    }
    return true;
}

template <Coordinate T>
std::optional<std::vector<std::array<Point<T>, 3>>> triangulate_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon =
        polygon_detail::clean_polygon_vertices(std::move(polygon), eps);
    if (polygon.size() < 3) return std::nullopt;

    wide_type<T> signed_area2 = polygon_area2(polygon);
    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;
    if (!is_simple_polygon(polygon, eps)) return std::nullopt;
    if (sign<T>(signed_area2, eps) < 0) {
        std::reverse(polygon.begin(), polygon.end());
    }

    std::vector<std::size_t> remaining(polygon.size());
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        remaining[index] = index;
    }

    std::vector<std::array<Point<T>, 3>> result;
    result.reserve(polygon.size() - 2);
    while (remaining.size() > 3) {
        bool found_ear = false;
        std::size_t size = remaining.size();
        for (std::size_t position = 0; position < size; ++position) {
            std::size_t previous_index =
                remaining[(position + size - 1) % size];
            std::size_t current_index = remaining[position];
            std::size_t next_index =
                remaining[(position + 1) % size];
            const Point<T>& previous = polygon[previous_index];
            const Point<T>& current = polygon[current_index];
            const Point<T>& next = polygon[next_index];
            if (orientation(previous, current, next, eps) <= 0) continue;

            bool contains_vertex = false;
            for (std::size_t other_index : remaining) {
                if (
                    other_index == previous_index ||
                    other_index == current_index ||
                    other_index == next_index
                ) {
                    continue;
                }
                if (
                    polygon_detail::in_ccw_triangle(
                        polygon[other_index],
                        previous,
                        current,
                        next,
                        eps
                    )
                ) {
                    contains_vertex = true;
                    break;
                }
            }
            if (contains_vertex) continue;

            std::array<Point<T>, 3> triangle;
            triangle[0] = previous;
            triangle[1] = current;
            triangle[2] = next;
            result.push_back(std::move(triangle));
            remaining.erase(
                remaining.begin() +
                static_cast<std::ptrdiff_t>(position)
            );
            found_ear = true;
            break;
        }
        if (!found_ear) return std::nullopt;
    }

    std::array<Point<T>, 3> triangle;
    triangle[0] = polygon[remaining[0]];
    triangle[1] = polygon[remaining[1]];
    triangle[2] = polygon[remaining[2]];
    if (orientation(triangle[0], triangle[1], triangle[2], eps) <= 0) {
        return std::nullopt;
    }
    result.push_back(std::move(triangle));
    return result;
}

template <Coordinate T>
std::vector<std::array<Point<T>, 3>> triangulate_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon =
        polygon_detail::clean_polygon_vertices(std::move(polygon), eps);
    if (polygon.size() < 3) return {};
    if (sign<T>(polygon_area2(polygon), eps) < 0) {
        std::reverse(polygon.begin(), polygon.end());
    }

    std::vector<std::array<Point<T>, 3>> result;
    result.reserve(polygon.size() - 2);
    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {
        std::array<Point<T>, 3> triangle;
        triangle[0] = polygon[0];
        triangle[1] = polygon[index];
        triangle[2] = polygon[index + 1];
        result.push_back(std::move(triangle));
    }
    return result;
}

template <Coordinate T>
PointInPolygon point_in_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    bool inside = false;
    std::size_t n = polygon.size();
    for (std::size_t i = 0; i < n; i++) {
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
    std::size_t n = polygon.size();
    if (n <= 1) return 0;
    if (n == 2) return distance2(polygon[1], polygon[0]);

    wide_type<T> result = 0;
    std::size_t opposite = 1;
    for (std::size_t i = 0; i < n; i++) {
        std::size_t next = (i + 1) % n;
        while (true) {
            std::size_t candidate = (opposite + 1) % n;
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

template <Coordinate T>
std::vector<Point<long double>> ray_polygon_intersections(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(polygon.size() >= 3);
    std::vector<Point<long double>> result;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        Segment<T> edge{
            polygon[index],
            polygon[(index + 1) % size]
        };
        std::optional<Point<long double>> point =
            ray_segment_intersection(ray, edge, eps);
        if (point.has_value()) {
            polygon_detail::push_unique(result, *point, eps);
            continue;
        }
        if (
            orientation(ray.origin, ray.through, edge.a, eps) == 0 &&
            orientation(ray.origin, ray.through, edge.b, eps) == 0
        ) {
            if (on_ray(ray, edge.a, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(edge.a),
                    eps
                );
            }
            if (on_ray(ray, edge.b, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(edge.b),
                    eps
                );
            }
            if (on_segment(edge, ray.origin, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(ray.origin),
                    eps
                );
            }
        }
    }

    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    std::sort(
        result.begin(),
        result.end(),
        [&](const Point<long double>& first, const Point<long double>& second) {
            return dot(first - origin, direction) <
                   dot(second - origin, direction);
        }
    );
    return result;
}

template <Coordinate T>
std::optional<Point<long double>> first_ray_polygon_intersection(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    std::vector<Point<long double>> points =
        ray_polygon_intersections(ray, polygon, eps);
    if (points.empty()) return std::nullopt;
    return points.front();
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    assert(polygon.size() >= 3);
    if (point_in_polygon(polygon, ray.origin, eps) != PointInPolygon::Outside) {
        return true;
    }
    return !ray_polygon_intersections(ray, polygon, eps).empty();
}

template <Coordinate T>
bool intersects(
    const std::vector<Point<T>>& polygon,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, polygon, eps);
}

template <Coordinate T>
long double distance(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon
) {
    assert(polygon.size() >= 3);
    if (intersects(ray, polygon)) return 0;
    long double result = std::numeric_limits<long double>::infinity();
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        result = std::min(
            result,
            distance(
                ray,
                Segment<T>{
                    polygon[index],
                    polygon[(index + 1) % size]
                }
            )
        );
    }
    return result;
}

template <Coordinate T>
long double distance(
    const std::vector<Point<T>>& polygon,
    const Ray<T>& ray
) {
    return distance(ray, polygon);
}

template <Coordinate T>
bool intersects(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    assert(first.size() >= 3);
    assert(second.size() >= 3);
    std::size_t first_size = first.size();
    std::size_t second_size = second.size();
    for (
        std::size_t first_index = 0;
        first_index < first_size;
        ++first_index
    ) {
        Segment<T> first_edge{
            first[first_index],
            first[(first_index + 1) % first_size]
        };
        for (
            std::size_t second_index = 0;
            second_index < second_size;
            ++second_index
        ) {
            Segment<T> second_edge{
                second[second_index],
                second[(second_index + 1) % second_size]
            };
            if (intersects(first_edge, second_edge, eps)) return true;
        }
    }
    return
        point_in_polygon(first, second.front(), eps) !=
            PointInPolygon::Outside ||
        point_in_polygon(second, first.front(), eps) !=
            PointInPolygon::Outside;
}

template <Coordinate T>
long double distance(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second
) {
    assert(first.size() >= 3);
    assert(second.size() >= 3);
    if (intersects(first, second)) return 0;

    long double result = std::numeric_limits<long double>::infinity();
    std::size_t first_size = first.size();
    std::size_t second_size = second.size();
    for (
        std::size_t first_index = 0;
        first_index < first_size;
        ++first_index
    ) {
        Segment<T> first_edge{
            first[first_index],
            first[(first_index + 1) % first_size]
        };
        for (
            std::size_t second_index = 0;
            second_index < second_size;
            ++second_index
        ) {
            Segment<T> second_edge{
                second[second_index],
                second[(second_index + 1) % second_size]
            };
            result = std::min(result, distance(first_edge, second_edge));
        }
    }
    return result;
}

template <Coordinate T>
std::vector<Point<long double>> convex_polygon_intersection(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    assert(first.size() >= 3);
    assert(second.size() >= 3);
    std::vector<Point<long double>> subject;
    subject.reserve(first.size());
    for (const Point<T>& point : first) {
        subject.emplace_back(point);
    }
    if (polygon_area2(subject) < 0) {
        std::reverse(subject.begin(), subject.end());
    }

    std::vector<Point<long double>> clip;
    clip.reserve(second.size());
    for (const Point<T>& point : second) {
        clip.emplace_back(point);
    }
    if (polygon_area2(clip) < 0) {
        std::reverse(clip.begin(), clip.end());
    }

    std::size_t clip_size = clip.size();
    for (std::size_t clip_index = 0; clip_index < clip_size; ++clip_index) {
        Point<long double> clip_start = clip[clip_index];
        Point<long double> clip_end =
            clip[(clip_index + 1) % clip_size];
        std::vector<Point<long double>> input = std::move(subject);
        subject.clear();
        if (input.empty()) break;

        Point<long double> previous = input.back();
        int previous_side =
            orientation(clip_start, clip_end, previous, eps);
        for (const Point<long double>& current : input) {
            int current_side =
                orientation(clip_start, clip_end, current, eps);
            bool previous_inside = previous_side >= 0;
            bool current_inside = current_side >= 0;
            if (previous_inside != current_inside) {
                Line<long double> boundary{clip_start, clip_end};
                Line<long double> crossing{previous, current};
                std::optional<Point<long double>> point =
                    line_intersection(boundary, crossing, eps);
                if (point.has_value()) subject.push_back(*point);
            }
            if (current_inside) subject.push_back(current);
            previous = current;
            previous_side = current_side;
        }
    }
    return polygon_detail::clean_convex_polygon(
        std::move(subject),
        eps
    );
}

template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second
) {
    assert(!first.empty());
    assert(!second.empty());
    first = polygon_detail::normalize_convex_polygon(std::move(first));
    second = polygon_detail::normalize_convex_polygon(std::move(second));

    if (first.size() <= 2 || second.size() <= 2) {
        std::vector<Point<T>> sums;
        sums.reserve(first.size() * second.size());
        for (const Point<T>& first_point : first) {
            for (const Point<T>& second_point : second) {
                sums.push_back(first_point + second_point);
            }
        }
        return convex_hull(std::move(sums));
    }

    std::vector<Point<T>> first_edges;
    std::vector<Point<T>> second_edges;
    for (std::size_t index = 0; index < first.size(); ++index) {
        first_edges.push_back(
            first[(index + 1) % first.size()] - first[index]
        );
    }
    for (std::size_t index = 0; index < second.size(); ++index) {
        second_edges.push_back(
            second[(index + 1) % second.size()] - second[index]
        );
    }

    Point<T> current = first.front() + second.front();
    std::vector<Point<T>> result;
    result.reserve(first.size() + second.size());
    result.push_back(current);
    std::size_t first_index = 0;
    std::size_t second_index = 0;
    while (
        first_index < first_edges.size() ||
        second_index < second_edges.size()
    ) {
        Point<T> step;
        if (first_index == first_edges.size()) {
            step = second_edges[second_index++];
        } else if (second_index == second_edges.size()) {
            step = first_edges[first_index++];
        } else {
            auto turn = cross(
                first_edges[first_index],
                second_edges[second_index]
            );
            if (turn > 0) {
                step = first_edges[first_index++];
            } else if (turn < 0) {
                step = second_edges[second_index++];
            } else {
                step =
                    first_edges[first_index++] +
                    second_edges[second_index++];
            }
        }
        current += step;
        if (
            first_index < first_edges.size() ||
            second_index < second_edges.size()
        ) {
            result.push_back(current);
        }
    }
    return polygon_detail::normalize_convex_polygon(std::move(result));
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_POLYGON_HPP
