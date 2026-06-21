#ifndef M1UNE_GEOMETRY_POINT_HPP
#define M1UNE_GEOMETRY_POINT_HPP 1

#include <cmath>
#include <concepts>
#include <cassert>
#include <type_traits>

namespace m1une {
namespace geometry {

template <typename T>
concept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>, bool>;

template <Coordinate T>
using wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;

template <Coordinate T>
struct Point {
    T x;
    T y;

    constexpr Point() : x(0), y(0) {}
    constexpr Point(T x_value, T y_value) : x(x_value), y(y_value) {}

    template <Coordinate U>
    explicit constexpr Point(const Point<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    constexpr Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Point& operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Point operator+() const {
        return *this;
    }

    constexpr Point operator-() const {
        return Point(-x, -y);
    }

    friend constexpr Point operator+(Point left, const Point& right) {
        return left += right;
    }

    friend constexpr Point operator-(Point left, const Point& right) {
        return left -= right;
    }

    friend constexpr bool operator==(const Point&, const Point&) = default;

    friend constexpr bool operator<(const Point& left, const Point& right) {
        if (left.x != right.x) return left.x < right.x;
        return left.y < right.y;
    }
};

template <Coordinate T, typename Scalar>
requires std::is_arithmetic_v<Scalar>
constexpr auto operator*(const Point<T>& point, Scalar scalar) {
    using Result = std::common_type_t<T, Scalar>;
    return Point<Result>(
        Result(point.x) * Result(scalar),
        Result(point.y) * Result(scalar)
    );
}

template <typename Scalar, Coordinate T>
requires std::is_arithmetic_v<Scalar>
constexpr auto operator*(Scalar scalar, const Point<T>& point) {
    return point * scalar;
}

template <Coordinate T, typename Scalar>
requires std::is_arithmetic_v<Scalar>
constexpr auto operator/(const Point<T>& point, Scalar scalar) {
    using Result = std::common_type_t<T, Scalar>;
    return Point<Result>(
        Result(point.x) / Result(scalar),
        Result(point.y) / Result(scalar)
    );
}

template <Coordinate T>
constexpr wide_type<T> dot(const Point<T>& a, const Point<T>& b) {
    using W = wide_type<T>;
    return W(a.x) * W(b.x) + W(a.y) * W(b.y);
}

template <Coordinate T>
constexpr wide_type<T> cross(const Point<T>& a, const Point<T>& b) {
    using W = wide_type<T>;
    return W(a.x) * W(b.y) - W(a.y) * W(b.x);
}

template <Coordinate T>
constexpr wide_type<T> cross(
    const Point<T>& origin,
    const Point<T>& a,
    const Point<T>& b
) {
    using W = wide_type<T>;
    W ax = W(a.x) - W(origin.x);
    W ay = W(a.y) - W(origin.y);
    W bx = W(b.x) - W(origin.x);
    W by = W(b.y) - W(origin.y);
    return ax * by - ay * bx;
}

template <Coordinate T>
constexpr wide_type<T> norm2(const Point<T>& point) {
    return dot(point, point);
}

template <Coordinate T>
constexpr wide_type<T> distance2(const Point<T>& a, const Point<T>& b) {
    using W = wide_type<T>;
    W dx = W(a.x) - W(b.x);
    W dy = W(a.y) - W(b.y);
    return dx * dx + dy * dy;
}

template <Coordinate T>
long double norm(const Point<T>& point) {
    return std::hypotl(
        static_cast<long double>(point.x),
        static_cast<long double>(point.y)
    );
}

template <Coordinate T>
long double distance(const Point<T>& a, const Point<T>& b) {
    return std::hypotl(
        static_cast<long double>(a.x) - static_cast<long double>(b.x),
        static_cast<long double>(a.y) - static_cast<long double>(b.y)
    );
}

template <Coordinate T, typename M, typename N>
requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>
constexpr Point<long double> internal_division_point(
    const Point<T>& a,
    const Point<T>& b,
    M m,
    N n
) {
    long double first_ratio = static_cast<long double>(m);
    long double second_ratio = static_cast<long double>(n);
    long double denominator = first_ratio + second_ratio;
    assert(denominator != 0);
    Point<long double> first(a);
    Point<long double> direction = Point<long double>(b) - first;
    return first + direction * (first_ratio / denominator);
}

template <Coordinate T, typename M, typename N>
requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>
constexpr Point<long double> external_division_point(
    const Point<T>& a,
    const Point<T>& b,
    M m,
    N n
) {
    long double first_ratio = static_cast<long double>(m);
    long double second_ratio = static_cast<long double>(n);
    long double denominator = first_ratio - second_ratio;
    assert(denominator != 0);
    Point<long double> first(a);
    Point<long double> direction = Point<long double>(b) - first;
    return first + direction * (first_ratio / denominator);
}

template <Coordinate T>
constexpr int sign(wide_type<T> value, long double eps = 1e-12L) {
    if constexpr (std::integral<T>) {
        return (value > 0) - (value < 0);
    } else {
        return (value > eps) - (value < -eps);
    }
}

template <Coordinate T>
constexpr int orientation(
    const Point<T>& a,
    const Point<T>& b,
    const Point<T>& c,
    long double eps = 1e-12L
) {
    return sign<T>(cross(a, b, c), eps);
}

template <Coordinate T>
constexpr bool collinear(
    const Point<T>& a,
    const Point<T>& b,
    const Point<T>& c,
    long double eps = 1e-12L
) {
    return orientation(a, b, c, eps) == 0;
}

template <Coordinate T>
Point<long double> rotate(const Point<T>& point, long double angle) {
    long double cosine = std::cos(angle);
    long double sine = std::sin(angle);
    return Point<long double>(
        static_cast<long double>(point.x) * cosine -
            static_cast<long double>(point.y) * sine,
        static_cast<long double>(point.x) * sine +
            static_cast<long double>(point.y) * cosine
    );
}

template <Coordinate T>
Point<long double> normalized(const Point<T>& point) {
    long double length = norm(point);
    assert(length != 0);
    return Point<long double>(
        static_cast<long double>(point.x) / length,
        static_cast<long double>(point.y) / length
    );
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_POINT_HPP
