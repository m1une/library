#ifndef M1UNE_GEOMETRY_RAY_HPP
#define M1UNE_GEOMETRY_RAY_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>

#include "line.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct Ray {
    Point<T> origin;
    Point<T> through;
};

namespace ray_detail {

template <Coordinate T>
struct Parameters {
    wide_type<T> denominator;
    wide_type<T> first_numerator;
    wide_type<T> second_numerator;
};

template <Coordinate T>
Parameters<T> parameters(
    const Point<T>& first_origin,
    const Point<T>& first_through,
    const Point<T>& second_origin,
    const Point<T>& second_through
) {
    using W = wide_type<T>;
    W first_x = W(first_through.x) - W(first_origin.x);
    W first_y = W(first_through.y) - W(first_origin.y);
    W second_x = W(second_through.x) - W(second_origin.x);
    W second_y = W(second_through.y) - W(second_origin.y);
    W offset_x = W(second_origin.x) - W(first_origin.x);
    W offset_y = W(second_origin.y) - W(first_origin.y);
    return Parameters<T>{
        first_x * second_y - first_y * second_x,
        offset_x * second_y - offset_y * second_x,
        offset_x * first_y - offset_y * first_x
    };
}

template <Coordinate T>
bool ratio_nonnegative(
    wide_type<T> numerator,
    wide_type<T> denominator,
    long double eps
) {
    int numerator_sign = sign<T>(numerator, eps);
    int denominator_sign = sign<T>(denominator, eps);
    return numerator_sign == 0 || numerator_sign == denominator_sign;
}

template <Coordinate T>
bool ratio_in_unit_interval(
    wide_type<T> numerator,
    wide_type<T> denominator,
    long double eps
) {
    if (sign<T>(denominator, eps) > 0) {
        return sign<T>(numerator, eps) >= 0 &&
               sign<T>(numerator - denominator, eps) <= 0;
    }
    return sign<T>(numerator, eps) <= 0 &&
           sign<T>(numerator - denominator, eps) >= 0;
}

template <Coordinate T>
Point<long double> point_at(
    const Ray<T>& ray,
    wide_type<T> numerator,
    wide_type<T> denominator
) {
    long double ratio =
        static_cast<long double>(numerator) /
        static_cast<long double>(denominator);
    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    return origin + direction * ratio;
}

}  // namespace ray_detail

template <Coordinate T>
bool on_ray(
    const Ray<T>& ray,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (orientation(ray.origin, ray.through, point, eps) != 0) return false;
    using W = wide_type<T>;
    W direction_x = W(ray.through.x) - W(ray.origin.x);
    W direction_y = W(ray.through.y) - W(ray.origin.y);
    W offset_x = W(point.x) - W(ray.origin.x);
    W offset_y = W(point.y) - W(ray.origin.y);
    return sign<T>(direction_x * offset_x + direction_y * offset_y, eps) >= 0;
}

template <Coordinate T>
Point<long double> projection(const Ray<T>& ray, const Point<T>& point) {
    assert(ray.origin != ray.through);
    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    Point<long double> offset = Point<long double>(point) - origin;
    long double ratio = dot(offset, direction) / dot(direction, direction);
    if (ratio < 0) ratio = 0;
    return origin + direction * ratio;
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Point<T>& point) {
    return geometry::distance(projection(ray, point), Point<long double>(point));
}

template <Coordinate T>
long double distance(const Point<T>& point, const Ray<T>& ray) {
    return distance(ray, point);
}

template <Coordinate T>
Ray<long double> reflection(const Line<T>& line, const Ray<T>& ray) {
    assert(ray.origin != ray.through);
    return Ray<long double>{
        reflection(line, ray.origin),
        reflection(line, ray.through)
    };
}

template <Coordinate T>
Ray<long double> reflected_ray(
    const Ray<T>& incoming,
    const Point<T>& hit,
    const Line<T>& mirror,
    long double eps = 1e-12L
) {
    assert(incoming.origin != incoming.through);
    assert(on_line(mirror, hit, eps));
    Point<T> translated = hit + (incoming.through - incoming.origin);
    return Ray<long double>{
        Point<long double>(hit),
        reflection(mirror, translated)
    };
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(line.a != line.b);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        line.a,
        line.b
    );
    if (sign<T>(values.denominator, eps) == 0) {
        return on_line(line, ray.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
        values.first_numerator,
        values.denominator,
        eps
    );
}

template <Coordinate T>
bool intersects(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, line, eps);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Line<T>& line) {
    return intersects(ray, line) ? 0 : distance(line, ray.origin);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Ray<T>& ray) {
    return distance(ray, line);
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (segment.a == segment.b) return on_ray(ray, segment.a, eps);

    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        segment.a,
        segment.b
    );
    if (sign<T>(values.denominator, eps) == 0) {
        if (orientation(ray.origin, ray.through, segment.a, eps) != 0) {
            return false;
        }
        return on_ray(ray, segment.a, eps) ||
               on_ray(ray, segment.b, eps) ||
               on_segment(segment, ray.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           ray_detail::ratio_in_unit_interval<T>(
               values.second_numerator,
               values.denominator,
               eps
           );
}

template <Coordinate T>
bool intersects(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, segment, eps);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Segment<T>& segment) {
    if (intersects(ray, segment)) return 0;
    return std::min({
        distance(ray, segment.a),
        distance(ray, segment.b),
        distance(segment, ray.origin)
    });
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Ray<T>& ray) {
    return distance(ray, segment);
}

template <Coordinate T>
bool intersects(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    assert(first.origin != first.through);
    assert(second.origin != second.through);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (sign<T>(values.denominator, eps) == 0) {
        if (orientation(first.origin, first.through, second.origin, eps) != 0) {
            return false;
        }
        return on_ray(first, second.origin, eps) ||
               on_ray(second, first.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           ray_detail::ratio_nonnegative<T>(
               values.second_numerator,
               values.denominator,
               eps
           );
}

template <Coordinate T>
long double distance(const Ray<T>& first, const Ray<T>& second) {
    if (intersects(first, second)) return 0;
    return std::min(
        distance(first, second.origin),
        distance(second, first.origin)
    );
}

template <Coordinate T>
std::optional<Point<long double>> ray_line_intersection(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(line.a != line.b);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        line.a,
        line.b
    );
    if (
        sign<T>(values.denominator, eps) == 0 ||
        !ray_detail::ratio_nonnegative<T>(
            values.first_numerator,
            values.denominator,
            eps
        )
    ) {
        return std::nullopt;
    }
    return ray_detail::point_at(
        ray,
        values.first_numerator,
        values.denominator
    );
}

template <Coordinate T>
std::optional<Point<long double>> ray_line_intersection(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return ray_line_intersection(ray, line, eps);
}

template <Coordinate T>
std::optional<Point<long double>> ray_segment_intersection(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (segment.a == segment.b) {
        if (on_ray(ray, segment.a, eps)) {
            return Point<long double>(segment.a);
        }
        return std::nullopt;
    }

    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        segment.a,
        segment.b
    );
    if (sign<T>(values.denominator, eps) == 0) {
        if (orientation(ray.origin, ray.through, segment.a, eps) != 0) {
            return std::nullopt;
        }
        if (
            segment.a == ray.origin &&
            !on_ray(ray, segment.b, eps)
        ) {
            return Point<long double>(ray.origin);
        }
        if (
            segment.b == ray.origin &&
            !on_ray(ray, segment.a, eps)
        ) {
            return Point<long double>(ray.origin);
        }
        return std::nullopt;
    }
    if (
        !ray_detail::ratio_nonnegative<T>(
            values.first_numerator,
            values.denominator,
            eps
        ) ||
        !ray_detail::ratio_in_unit_interval<T>(
            values.second_numerator,
            values.denominator,
            eps
        )
    ) {
        return std::nullopt;
    }
    return ray_detail::point_at(
        ray,
        values.first_numerator,
        values.denominator
    );
}

template <Coordinate T>
std::optional<Point<long double>> ray_segment_intersection(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return ray_segment_intersection(ray, segment, eps);
}

template <Coordinate T>
std::optional<Point<long double>> ray_intersection(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    assert(first.origin != first.through);
    assert(second.origin != second.through);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (sign<T>(values.denominator, eps) == 0) {
        if (
            first.origin != second.origin ||
            orientation(
                first.origin,
                first.through,
                second.through,
                eps
            ) != 0
        ) {
            return std::nullopt;
        }
        using W = wide_type<T>;
        W first_x = W(first.through.x) - W(first.origin.x);
        W first_y = W(first.through.y) - W(first.origin.y);
        W second_x = W(second.through.x) - W(second.origin.x);
        W second_y = W(second.through.y) - W(second.origin.y);
        if (sign<T>(first_x * second_x + first_y * second_y, eps) < 0) {
            return Point<long double>(first.origin);
        }
        return std::nullopt;
    }
    if (
        !ray_detail::ratio_nonnegative<T>(
            values.first_numerator,
            values.denominator,
            eps
        ) ||
        !ray_detail::ratio_nonnegative<T>(
            values.second_numerator,
            values.denominator,
            eps
        )
    ) {
        return std::nullopt;
    }
    return ray_detail::point_at(
        first,
        values.first_numerator,
        values.denominator
    );
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_RAY_HPP
