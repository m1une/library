---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/ray.hpp
    title: Rays
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/geometry/ray.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"geometry/ray.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <optional>\n\n#line 1 \"geometry/line.hpp\"\n\n\n\n#line 6 \"geometry/line.hpp\"\
    \n#include <cmath>\n#line 8 \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#line 5 \"geometry/point.hpp\"\n#include <concepts>\n#line 7 \"geometry/point.hpp\"\
    \n#include <type_traits>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>,\
    \ bool>;\n\ntemplate <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>,\
    \ __int128_t, long double>;\n\ntemplate <Coordinate T>\nstruct Point {\n    T\
    \ x;\n    T y;\n\n    constexpr Point() : x(0), y(0) {}\n    constexpr Point(T\
    \ x_value, T y_value) : x(x_value), y(y_value) {}\n\n    template <Coordinate\
    \ U>\n    explicit constexpr Point(const Point<U>& other)\n        : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)) {}\n\n    constexpr Point& operator+=(const Point&\
    \ other) {\n        x += other.x;\n        y += other.y;\n        return *this;\n\
    \    }\n\n    constexpr Point& operator-=(const Point& other) {\n        x -=\
    \ other.x;\n        y -= other.y;\n        return *this;\n    }\n\n    constexpr\
    \ Point operator+() const {\n        return *this;\n    }\n\n    constexpr Point\
    \ operator-() const {\n        return Point(-x, -y);\n    }\n\n    friend constexpr\
    \ Point operator+(Point left, const Point& right) {\n        return left += right;\n\
    \    }\n\n    friend constexpr Point operator-(Point left, const Point& right)\
    \ {\n        return left -= right;\n    }\n\n    friend constexpr bool operator==(const\
    \ Point&, const Point&) = default;\n\n    friend constexpr bool operator<(const\
    \ Point& left, const Point& right) {\n        if (left.x != right.x) return left.x\
    \ < right.x;\n        return left.y < right.y;\n    }\n};\n\ntemplate <Coordinate\
    \ T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(const\
    \ Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) * Result(scalar),\n\
    \        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate <typename Scalar,\
    \ Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(Scalar\
    \ scalar, const Point<T>& point) {\n    return point * scalar;\n}\n\ntemplate\
    \ <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) / Result(scalar),\n\
    \        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> dot(const Point<T>& a, const Point<T>& b) {\n    using\
    \ W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y) - W(a.y) * W(b.x);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n    const Point<T>&\
    \ origin,\n    const Point<T>& a,\n    const Point<T>& b\n) {\n    using W = wide_type<T>;\n\
    \    W ax = W(a.x) - W(origin.x);\n    W ay = W(a.y) - W(origin.y);\n    W bx\
    \ = W(b.x) - W(origin.x);\n    W by = W(b.y) - W(origin.y);\n    return ax * by\
    \ - ay * bx;\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> norm2(const\
    \ Point<T>& point) {\n    return dot(point, point);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr wide_type<T> distance2(const Point<T>& a, const Point<T>& b) {\n\
    \    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n    W dy = W(a.y) -\
    \ W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate T>\nlong double\
    \ norm(const Point<T>& point) {\n    return std::hypot(\n        static_cast<long\
    \ double>(point.x),\n        static_cast<long double>(point.y)\n    );\n}\n\n\
    template <Coordinate T>\nlong double distance(const Point<T>& a, const Point<T>&\
    \ b) {\n    return std::hypot(\n        static_cast<long double>(a.x) - static_cast<long\
    \ double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long double>(b.y)\n\
    \    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> internal_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio +\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T, typename M, typename N>\nrequires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\n\
    constexpr Point<long double> external_division_point(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    M m,\n    N n\n) {\n    long double first_ratio =\
    \ static_cast<long double>(m);\n    long double second_ratio = static_cast<long\
    \ double>(n);\n    long double denominator = first_ratio - second_ratio;\n   \
    \ assert(denominator != 0);\n    Point<long double> first(a);\n    Point<long\
    \ double> direction = Point<long double>(b) - first;\n    return first + direction\
    \ * (first_ratio / denominator);\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ sign(wide_type<T> value, long double eps = 1e-12L) {\n    if constexpr (std::integral<T>)\
    \ {\n        return (value > 0) - (value < 0);\n    } else {\n        return (value\
    \ > eps) - (value < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ orientation(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return sign<T>(cross(a, b, c), eps);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr bool collinear(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n\
    ) {\n    return orientation(a, b, c, eps) == 0;\n}\n\ntemplate <Coordinate T>\n\
    Point<long double> rotate(const Point<T>& point, long double angle) {\n    long\
    \ double cosine = std::cos(angle);\n    long double sine = std::sin(angle);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) * cosine\
    \ -\n            static_cast<long double>(point.y) * sine,\n        static_cast<long\
    \ double>(point.x) * sine +\n            static_cast<long double>(point.y) * cosine\n\
    \    );\n}\n\ntemplate <Coordinate T>\nPoint<long double> normalized(const Point<T>&\
    \ point) {\n    long double length = norm(point);\n    assert(length != 0);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) / length,\n\
    \        static_cast<long double>(point.y) / length\n    );\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/line.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Line {\n  \
    \  Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nstruct Segment\
    \ {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nbool on_line(\n\
    \    const Line<T>& line,\n    const Point<T>& point,\n    long double eps = 1e-12L\n\
    ) {\n    assert(line.a != line.b);\n    return orientation(line.a, line.b, point,\
    \ eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool parallel(const Line<T>& first,\
    \ const Line<T>& second, long double eps = 1e-12L) {\n    using W = wide_type<T>;\n\
    \    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y = W(first.b.y) -\
    \ W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n    W second_y\
    \ = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x * second_y - first_y\
    \ * second_x, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool orthogonal(const\
    \ Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y\
    \ = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n\
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x *\
    \ second_x + first_y * second_y, eps) == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long\
    \ double> projection(const Line<T>& line, const Point<T>& point) {\n    assert(line.a\
    \ != line.b);\n    Point<long double> a(line.a);\n    Point<long double> direction(\n\
    \        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),\n\
    \        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)\n\
    \    );\n    Point<long double> offset(\n        static_cast<long double>(point.x)\
    \ - a.x,\n        static_cast<long double>(point.y) - a.y\n    );\n    long double\
    \ ratio = dot(offset, direction) / dot(direction, direction);\n    return a +\
    \ direction * ratio;\n}\n\ntemplate <Coordinate T>\nPoint<long double> reflection(const\
    \ Line<T>& line, const Point<T>& point) {\n    Point<long double> projected =\
    \ projection(line, point);\n    return projected * 2.0L - Point<long double>(point);\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>& line, const\
    \ Point<T>& point) {\n    assert(line.a != line.b);\n    Point<long double> direction(\n\
    \        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),\n\
    \        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)\n\
    \    );\n    Point<long double> offset(\n        static_cast<long double>(point.x)\
    \ - static_cast<long double>(line.a.x),\n        static_cast<long double>(point.y)\
    \ - static_cast<long double>(line.a.y)\n    );\n    return std::fabs(cross(direction,\
    \ offset)) / norm(direction);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Point<T>& point, const Line<T>& line) {\n    return distance(line, point);\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Line<T>& first,\n  \
    \  const Line<T>& second,\n    long double eps = 1e-12L\n) {\n    return !parallel(first,\
    \ second, eps) || on_line(first, second.a, eps);\n}\n\ntemplate <Coordinate T>\n\
    long double distance(const Line<T>& first, const Line<T>& second) {\n    return\
    \ intersects(first, second) ? 0 : distance(first, second.a);\n}\n\ntemplate <Coordinate\
    \ T>\nbool on_segment(\n    const Segment<T>& segment,\n    const Point<T>& point,\n\
    \    long double eps = 1e-12L\n) {\n    if (orientation(segment.a, segment.b,\
    \ point, eps) != 0) return false;\n    using W = wide_type<T>;\n    W px = W(point.x);\n\
    \    W py = W(point.y);\n    W min_x = std::min(W(segment.a.x), W(segment.b.x));\n\
    \    W max_x = std::max(W(segment.a.x), W(segment.b.x));\n    W min_y = std::min(W(segment.a.y),\
    \ W(segment.b.y));\n    W max_y = std::max(W(segment.a.y), W(segment.b.y));\n\
    \    if constexpr (std::integral<T>) {\n        return min_x <= px && px <= max_x\
    \ && min_y <= py && py <= max_y;\n    } else {\n        return min_x - eps <=\
    \ px && px <= max_x + eps &&\n               min_y - eps <= py && py <= max_y\
    \ + eps;\n    }\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps = 1e-12L\n) {\n \
    \   int abc = orientation(first.a, first.b, second.a, eps);\n    int abd = orientation(first.a,\
    \ first.b, second.b, eps);\n    int cda = orientation(second.a, second.b, first.a,\
    \ eps);\n    int cdb = orientation(second.a, second.b, first.b, eps);\n\n    if\
    \ (abc == 0 && on_segment(first, second.a, eps)) return true;\n    if (abd ==\
    \ 0 && on_segment(first, second.b, eps)) return true;\n    if (cda == 0 && on_segment(second,\
    \ first.a, eps)) return true;\n    if (cdb == 0 && on_segment(second, first.b,\
    \ eps)) return true;\n    return abc * abd < 0 && cda * cdb < 0;\n}\n\ntemplate\
    \ <Coordinate T>\nbool intersects(\n    const Line<T>& line,\n    const Segment<T>&\
    \ segment,\n    long double eps = 1e-12L\n) {\n    int first_side = orientation(line.a,\
    \ line.b, segment.a, eps);\n    int second_side = orientation(line.a, line.b,\
    \ segment.b, eps);\n    return first_side == 0 || second_side == 0 || first_side\
    \ != second_side;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ segment,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    return\
    \ intersects(line, segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Segment<T>& segment, const Point<T>& point) {\n    Point<long double> a(segment.a);\n\
    \    Point<long double> b(segment.b);\n    Point<long double> p(point);\n    Point<long\
    \ double> direction = b - a;\n    long double length_squared = dot(direction,\
    \ direction);\n    if (length_squared == 0) return geometry::distance(segment.a,\
    \ point);\n    long double ratio = dot(p - a, direction) / length_squared;\n \
    \   ratio = std::clamp(ratio, 0.0L, 1.0L);\n    Point<long double> closest = a\
    \ + direction * ratio;\n    return geometry::distance(closest, p);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Point<T>& point, const Segment<T>&\
    \ segment) {\n    return distance(segment, point);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& first, const Segment<T>& second)\
    \ {\n    if (intersects(first, second)) return 0;\n    return std::min({\n   \
    \     distance(first, second.a),\n        distance(first, second.b),\n       \
    \ distance(second, first.a),\n        distance(second, first.b),\n    });\n}\n\
    \ntemplate <Coordinate T>\nlong double distance(const Line<T>& line, const Segment<T>&\
    \ segment) {\n    if (intersects(line, segment)) return 0;\n    return std::min(distance(line,\
    \ segment.a), distance(line, segment.b));\n}\n\ntemplate <Coordinate T>\nlong\
    \ double distance(const Segment<T>& segment, const Line<T>& line) {\n    return\
    \ distance(line, segment);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> line_intersection(\n    const Line<T>& first,\n    const Line<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.a != first.b);\n    assert(second.a\
    \ != second.b);\n    Point<long double> p(first.a);\n    Point<long double> q(second.a);\n\
    \    Point<long double> r = Point<long double>(first.b) - p;\n    Point<long double>\
    \ s = Point<long double>(second.b) - q;\n    long double denominator = cross(r,\
    \ s);\n    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(q - p, s) / denominator;\n    return p + r * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(line.a != line.b);\n    if (segment.a == segment.b)\
    \ {\n        if (on_line(line, segment.a, eps)) {\n            return Point<long\
    \ double>(segment.a);\n        }\n        return std::nullopt;\n    }\n    if\
    \ (!intersects(line, segment, eps)) return std::nullopt;\n    Line<T> supporting_line{segment.a,\
    \ segment.b};\n    return line_intersection(line, supporting_line, eps);\n}\n\n\
    template <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Segment<T>& segment,\n    const Line<T>& line,\n    long double eps\
    \ = 1e-12L\n) {\n    return line_segment_intersection(line, segment, eps);\n}\n\
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 9 \"geometry/ray.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct\
    \ Ray {\n    Point<T> origin;\n    Point<T> through;\n};\n\nnamespace ray_detail\
    \ {\n\ntemplate <Coordinate T>\nstruct Parameters {\n    wide_type<T> denominator;\n\
    \    wide_type<T> first_numerator;\n    wide_type<T> second_numerator;\n};\n\n\
    template <Coordinate T>\nParameters<T> parameters(\n    const Point<T>& first_origin,\n\
    \    const Point<T>& first_through,\n    const Point<T>& second_origin,\n    const\
    \ Point<T>& second_through\n) {\n    using W = wide_type<T>;\n    W first_x =\
    \ W(first_through.x) - W(first_origin.x);\n    W first_y = W(first_through.y)\
    \ - W(first_origin.y);\n    W second_x = W(second_through.x) - W(second_origin.x);\n\
    \    W second_y = W(second_through.y) - W(second_origin.y);\n    W offset_x =\
    \ W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
    \ - W(first_origin.y);\n    return Parameters<T>{\n        first_x * second_y\
    \ - first_y * second_x,\n        offset_x * second_y - offset_y * second_x,\n\
    \        offset_x * first_y - offset_y * first_x\n    };\n}\n\ntemplate <Coordinate\
    \ T>\nbool ratio_nonnegative(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    int numerator_sign = sign<T>(numerator, eps);\n\
    \    int denominator_sign = sign<T>(denominator, eps);\n    return numerator_sign\
    \ == 0 || numerator_sign == denominator_sign;\n}\n\ntemplate <Coordinate T>\n\
    bool ratio_in_unit_interval(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    if (sign<T>(denominator, eps) > 0) {\n        return\
    \ sign<T>(numerator, eps) >= 0 &&\n               sign<T>(numerator - denominator,\
    \ eps) <= 0;\n    }\n    return sign<T>(numerator, eps) <= 0 &&\n           sign<T>(numerator\
    \ - denominator, eps) >= 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ point_at(\n    const Ray<T>& ray,\n    wide_type<T> numerator,\n    wide_type<T>\
    \ denominator\n) {\n    long double ratio =\n        static_cast<long double>(numerator)\
    \ /\n        static_cast<long double>(denominator);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    return origin + direction * ratio;\n}\n\n}  // namespace ray_detail\n\
    \ntemplate <Coordinate T>\nbool on_ray(\n    const Ray<T>& ray,\n    const Point<T>&\
    \ point,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    if (orientation(ray.origin, ray.through, point, eps) != 0) return false;\n\
    \    using W = wide_type<T>;\n    W direction_x = W(ray.through.x) - W(ray.origin.x);\n\
    \    W direction_y = W(ray.through.y) - W(ray.origin.y);\n    W offset_x = W(point.x)\
    \ - W(ray.origin.x);\n    W offset_y = W(point.y) - W(ray.origin.y);\n    return\
    \ sign<T>(direction_x * offset_x + direction_y * offset_y, eps) >= 0;\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> projection(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    assert(ray.origin != ray.through);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    Point<long double> offset = Point<long double>(point) - origin;\n\
    \    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    if (ratio < 0) ratio = 0;\n    return origin + direction * ratio;\n}\n\n\
    template <Coordinate T>\nlong double distance(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    return geometry::distance(projection(ray, point), Point<long double>(point));\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& point, const\
    \ Ray<T>& ray) {\n    return distance(ray, point);\n}\n\ntemplate <Coordinate\
    \ T>\nRay<long double> reflection(const Line<T>& line, const Ray<T>& ray) {\n\
    \    assert(ray.origin != ray.through);\n    return Ray<long double>{\n      \
    \  reflection(line, ray.origin),\n        reflection(line, ray.through)\n    };\n\
    }\n\ntemplate <Coordinate T>\nRay<long double> reflected_ray(\n    const Ray<T>&\
    \ incoming,\n    const Point<T>& hit,\n    const Line<T>& mirror,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(incoming.origin != incoming.through);\n    assert(on_line(mirror,\
    \ hit, eps));\n    Point<T> translated = hit + (incoming.through - incoming.origin);\n\
    \    return Ray<long double>{\n        Point<long double>(hit),\n        reflection(mirror,\
    \ translated)\n    };\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n\
    \    assert(ray.origin != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        return on_line(line, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n        values.first_numerator,\n       \
    \ values.denominator,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nbool\
    \ intersects(\n    const Line<T>& line,\n    const Ray<T>& ray,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Ray<T>& ray, const Line<T>& line) {\n    return\
    \ intersects(ray, line) ? 0 : distance(line, ray.origin);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Line<T>& line, const Ray<T>& ray) {\n    return\
    \ distance(ray, line);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    if (segment.a == segment.b) return\
    \ on_ray(ray, segment.a, eps);\n\n    ray_detail::Parameters<T> values = ray_detail::parameters(\n\
    \        ray.origin,\n        ray.through,\n        segment.a,\n        segment.b\n\
    \    );\n    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(ray.origin,\
    \ ray.through, segment.a, eps) != 0) {\n            return false;\n        }\n\
    \        return on_ray(ray, segment.a, eps) ||\n               on_ray(ray, segment.b,\
    \ eps) ||\n               on_segment(segment, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n               values.first_numerator,\n\
    \               values.denominator,\n               eps\n           ) &&\n   \
    \        ray_detail::ratio_in_unit_interval<T>(\n               values.second_numerator,\n\
    \               values.denominator,\n               eps\n           );\n}\n\n\
    template <Coordinate T>\nbool intersects(\n    const Segment<T>& segment,\n  \
    \  const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return intersects(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Ray<T>&\
    \ ray, const Segment<T>& segment) {\n    if (intersects(ray, segment)) return\
    \ 0;\n    return std::min({\n        distance(ray, segment.a),\n        distance(ray,\
    \ segment.b),\n        distance(segment, ray.origin)\n    });\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& segment, const Ray<T>& ray) {\n \
    \   return distance(ray, segment);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Ray<T>& first,\n    const Ray<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(first.origin != first.through);\n    assert(second.origin != second.through);\n\
    \    ray_detail::Parameters<T> values = ray_detail::parameters(\n        first.origin,\n\
    \        first.through,\n        second.origin,\n        second.through\n    );\n\
    \    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(first.origin,\
    \ first.through, second.origin, eps) != 0) {\n            return false;\n    \
    \    }\n        return on_ray(first, second.origin, eps) ||\n               on_ray(second,\
    \ first.origin, eps);\n    }\n    return ray_detail::ratio_nonnegative<T>(\n \
    \              values.first_numerator,\n               values.denominator,\n \
    \              eps\n           ) &&\n           ray_detail::ratio_nonnegative<T>(\n\
    \               values.second_numerator,\n               values.denominator,\n\
    \               eps\n           );\n}\n\ntemplate <Coordinate T>\nlong double\
    \ distance(const Ray<T>& first, const Ray<T>& second) {\n    if (intersects(first,\
    \ second)) return 0;\n    return std::min(\n        distance(first, second.origin),\n\
    \        distance(second, first.origin)\n    );\n}\n\ntemplate <Coordinate T>\n\
    std::optional<Point<long double>> ray_line_intersection(\n    const Ray<T>& ray,\n\
    \    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin\
    \ != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (\n        sign<T>(values.denominator,\
    \ eps) == 0 ||\n        !ray_detail::ratio_nonnegative<T>(\n            values.first_numerator,\n\
    \            values.denominator,\n            eps\n        )\n    ) {\n      \
    \  return std::nullopt;\n    }\n    return ray_detail::point_at(\n        ray,\n\
    \        values.first_numerator,\n        values.denominator\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> ray_line_intersection(\n \
    \   const Line<T>& line,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    return ray_line_intersection(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Point<long double>> ray_segment_intersection(\n    const Ray<T>&\
    \ ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(ray.origin != ray.through);\n    if (segment.a == segment.b) {\n   \
    \     if (on_ray(ray, segment.a, eps)) {\n            return Point<long double>(segment.a);\n\
    \        }\n        return std::nullopt;\n    }\n\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        segment.a,\n        segment.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (orientation(ray.origin, ray.through, segment.a, eps)\
    \ != 0) {\n            return std::nullopt;\n        }\n        if (\n       \
    \     segment.a == ray.origin &&\n            !on_ray(ray, segment.b, eps)\n \
    \       ) {\n            return Point<long double>(ray.origin);\n        }\n \
    \       if (\n            segment.b == ray.origin &&\n            !on_ray(ray,\
    \ segment.a, eps)\n        ) {\n            return Point<long double>(ray.origin);\n\
    \        }\n        return std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_in_unit_interval<T>(\n  \
    \          values.second_numerator,\n            values.denominator,\n       \
    \     eps\n        )\n    ) {\n        return std::nullopt;\n    }\n    return\
    \ ray_detail::point_at(\n        ray,\n        values.first_numerator,\n     \
    \   values.denominator\n    );\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> ray_segment_intersection(\n    const Segment<T>& segment,\n    const\
    \ Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return ray_segment_intersection(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>>\
    \ ray_intersection(\n    const Ray<T>& first,\n    const Ray<T>& second,\n   \
    \ long double eps = 1e-12L\n) {\n    assert(first.origin != first.through);\n\
    \    assert(second.origin != second.through);\n    ray_detail::Parameters<T> values\
    \ = ray_detail::parameters(\n        first.origin,\n        first.through,\n \
    \       second.origin,\n        second.through\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (\n            first.origin != second.origin ||\n \
    \           orientation(\n                first.origin,\n                first.through,\n\
    \                second.through,\n                eps\n            ) != 0\n  \
    \      ) {\n            return std::nullopt;\n        }\n        using W = wide_type<T>;\n\
    \        W first_x = W(first.through.x) - W(first.origin.x);\n        W first_y\
    \ = W(first.through.y) - W(first.origin.y);\n        W second_x = W(second.through.x)\
    \ - W(second.origin.x);\n        W second_y = W(second.through.y) - W(second.origin.y);\n\
    \        if (sign<T>(first_x * second_x + first_y * second_y, eps) < 0) {\n  \
    \          return Point<long double>(first.origin);\n        }\n        return\
    \ std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_nonnegative<T>(\n       \
    \     values.second_numerator,\n            values.denominator,\n            eps\n\
    \        )\n    ) {\n        return std::nullopt;\n    }\n    return ray_detail::point_at(\n\
    \        first,\n        values.first_numerator,\n        values.denominator\n\
    \    );\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/geometry/ray.test.cpp\"\n\n#line 8 \"verify/geometry/ray.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n\nnamespace {\n\nusing namespace m1une::geometry;\n\
    using P = Point<long long>;\nusing IntegerRay = Ray<long long>;\nusing IntegerLine\
    \ = Line<long long>;\nusing IntegerSegment = Segment<long long>;\n\nbool close(long\
    \ double first, long double second) {\n    return std::fabs(first - second) <=\
    \ 1e-10L;\n}\n\nIntegerSegment long_segment(const IntegerRay& ray) {\n    P direction\
    \ = ray.through - ray.origin;\n    IntegerSegment result;\n    result.a = ray.origin;\n\
    \    result.b = ray.origin + direction * 1000;\n    return result;\n}\n\nvoid\
    \ test_line_segment() {\n    IntegerLine horizontal;\n    horizontal.a = P(0,\
    \ 0);\n    horizontal.b = P(1, 0);\n\n    IntegerSegment crossing;\n    crossing.a\
    \ = P(2, -3);\n    crossing.b = P(2, 4);\n    assert(intersects(horizontal, crossing));\n\
    \    assert(intersects(crossing, horizontal));\n    assert(close(distance(horizontal,\
    \ crossing), 0));\n    auto point = line_segment_intersection(horizontal, crossing);\n\
    \    assert(point.has_value());\n    assert(close(point->x, 2));\n    assert(close(point->y,\
    \ 0));\n\n    IntegerSegment above;\n    above.a = P(-1, 3);\n    above.b = P(4,\
    \ 3);\n    assert(!intersects(horizontal, above));\n    assert(close(distance(horizontal,\
    \ above), 3));\n    assert(close(distance(above, horizontal), 3));\n    assert(!line_segment_intersection(horizontal,\
    \ above).has_value());\n\n    IntegerSegment overlapping;\n    overlapping.a =\
    \ P(2, 0);\n    overlapping.b = P(5, 0);\n    assert(intersects(horizontal, overlapping));\n\
    \    assert(close(distance(horizontal, overlapping), 0));\n    assert(!line_segment_intersection(horizontal,\
    \ overlapping).has_value());\n\n    IntegerSegment point_segment;\n    point_segment.a\
    \ = P(7, 0);\n    point_segment.b = point_segment.a;\n    auto degenerate = line_segment_intersection(horizontal,\
    \ point_segment);\n    assert(degenerate.has_value());\n    assert(close(degenerate->x,\
    \ 7));\n}\n\nvoid test_ray_point_and_line() {\n    IntegerRay ray;\n    ray.origin\
    \ = P(0, 0);\n    ray.through = P(2, 0);\n\n    assert(on_ray(ray, P(0, 0)));\n\
    \    assert(on_ray(ray, P(5, 0)));\n    assert(!on_ray(ray, P(-1, 0)));\n    assert(!on_ray(ray,\
    \ P(1, 1)));\n    assert(close(distance(ray, P(-3, 4)), 5));\n    assert(close(distance(P(-3,\
    \ 4), ray), 5));\n\n    Point<long double> projected = projection(ray, P(-3, 4));\n\
    \    assert(close(projected.x, 0));\n    assert(close(projected.y, 0));\n\n  \
    \  IntegerLine ahead;\n    ahead.a = P(3, -2);\n    ahead.b = P(3, 2);\n    assert(intersects(ray,\
    \ ahead));\n    assert(close(distance(ray, ahead), 0));\n    auto hit = ray_line_intersection(ray,\
    \ ahead);\n    assert(hit.has_value());\n    assert(close(hit->x, 3));\n    assert(close(hit->y,\
    \ 0));\n\n    IntegerLine behind;\n    behind.a = P(-3, -2);\n    behind.b = P(-3,\
    \ 2);\n    assert(!intersects(ray, behind));\n    assert(close(distance(ray, behind),\
    \ 3));\n    assert(!ray_line_intersection(ray, behind).has_value());\n\n    IntegerLine\
    \ parallel_line;\n    parallel_line.a = P(0, 4);\n    parallel_line.b = P(1, 4);\n\
    \    assert(!intersects(ray, parallel_line));\n    assert(close(distance(ray,\
    \ parallel_line), 4));\n\n    IntegerLine supporting;\n    supporting.a = P(-10,\
    \ 0);\n    supporting.b = P(10, 0);\n    assert(intersects(ray, supporting));\n\
    \    assert(!ray_line_intersection(ray, supporting).has_value());\n}\n\nvoid test_ray_segment()\
    \ {\n    IntegerRay ray;\n    ray.origin = P(0, 0);\n    ray.through = P(1, 0);\n\
    \n    IntegerSegment crossing;\n    crossing.a = P(3, -2);\n    crossing.b = P(3,\
    \ 2);\n    assert(intersects(ray, crossing));\n    assert(intersects(crossing,\
    \ ray));\n    auto hit = ray_segment_intersection(ray, crossing);\n    assert(hit.has_value());\n\
    \    assert(close(hit->x, 3));\n    assert(close(hit->y, 0));\n\n    IntegerSegment\
    \ behind;\n    behind.a = P(-4, -2);\n    behind.b = P(-4, 2);\n    assert(!intersects(ray,\
    \ behind));\n    assert(close(distance(ray, behind), 4));\n\n    IntegerSegment\
    \ overlap;\n    overlap.a = P(-2, 0);\n    overlap.b = P(5, 0);\n    assert(intersects(ray,\
    \ overlap));\n    assert(!ray_segment_intersection(ray, overlap).has_value());\n\
    \n    IntegerSegment touching_origin;\n    touching_origin.a = P(-2, 0);\n   \
    \ touching_origin.b = P(0, 0);\n    auto endpoint_hit = ray_segment_intersection(ray,\
    \ touching_origin);\n    assert(endpoint_hit.has_value());\n    assert(close(endpoint_hit->x,\
    \ 0));\n    assert(close(endpoint_hit->y, 0));\n\n    IntegerSegment separated;\n\
    \    separated.a = P(-3, 4);\n    separated.b = P(-1, 4);\n    assert(!intersects(ray,\
    \ separated));\n    assert(close(distance(ray, separated), std::sqrt(17.0L)));\n\
    \    assert(close(distance(separated, ray), std::sqrt(17.0L)));\n}\n\nvoid test_ray_ray()\
    \ {\n    IntegerRay horizontal;\n    horizontal.origin = P(0, 0);\n    horizontal.through\
    \ = P(1, 0);\n\n    IntegerRay vertical;\n    vertical.origin = P(3, -2);\n  \
    \  vertical.through = P(3, -1);\n    assert(intersects(horizontal, vertical));\n\
    \    auto crossing = ray_intersection(horizontal, vertical);\n    assert(crossing.has_value());\n\
    \    assert(close(crossing->x, 3));\n    assert(close(crossing->y, 0));\n\n  \
    \  IntegerRay diverging;\n    diverging.origin = P(-2, 0);\n    diverging.through\
    \ = P(-3, 0);\n    assert(!intersects(horizontal, diverging));\n    assert(close(distance(horizontal,\
    \ diverging), 2));\n    assert(!ray_intersection(horizontal, diverging).has_value());\n\
    \n    IntegerRay facing;\n    facing.origin = P(4, 0);\n    facing.through = P(3,\
    \ 0);\n    assert(intersects(horizontal, facing));\n    assert(close(distance(horizontal,\
    \ facing), 0));\n    assert(!ray_intersection(horizontal, facing).has_value());\n\
    \n    IntegerRay opposite_at_origin;\n    opposite_at_origin.origin = P(0, 0);\n\
    \    opposite_at_origin.through = P(-1, 0);\n    auto origin_hit = ray_intersection(horizontal,\
    \ opposite_at_origin);\n    assert(origin_hit.has_value());\n    assert(close(origin_hit->x,\
    \ 0));\n    assert(close(origin_hit->y, 0));\n\n    IntegerRay offset;\n    offset.origin\
    \ = P(-2, 3);\n    offset.through = P(-3, 3);\n    assert(!intersects(horizontal,\
    \ offset));\n    assert(close(distance(horizontal, offset), std::sqrt(13.0L)));\n\
    }\n\nvoid test_randomized_against_long_segments() {\n    std::uint64_t state =\
    \ 0x18273645abcdefULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n    auto\
    \ random_point = [&]() {\n        return P(\n            static_cast<long long>(random()\
    \ % 11) - 5,\n            static_cast<long long>(random() % 11) - 5\n        );\n\
    \    };\n\n    for (int trial = 0; trial < 20000; ++trial) {\n        IntegerRay\
    \ first;\n        first.origin = random_point();\n        do {\n            first.through\
    \ = random_point();\n        } while (first.origin == first.through);\n\n    \
    \    IntegerRay second;\n        second.origin = random_point();\n        do {\n\
    \            second.through = random_point();\n        } while (second.origin\
    \ == second.through);\n\n        IntegerSegment segment;\n        segment.a =\
    \ random_point();\n        segment.b = random_point();\n\n        IntegerLine\
    \ line;\n        line.a = random_point();\n        do {\n            line.b =\
    \ random_point();\n        } while (line.a == line.b);\n\n        IntegerSegment\
    \ first_long = long_segment(first);\n        IntegerSegment second_long = long_segment(second);\n\
    \n        assert(intersects(first, segment) == intersects(first_long, segment));\n\
    \        assert(intersects(first, second) == intersects(first_long, second_long));\n\
    \        assert(intersects(first, line) == intersects(line, first_long));\n\n\
    \        assert(close(distance(first, segment), distance(first_long, segment)));\n\
    \        assert(close(distance(first, second), distance(first_long, second_long)));\n\
    \        assert(close(distance(first, line), distance(line, first_long)));\n\n\
    \        assert(intersects(first, segment) == intersects(segment, first));\n \
    \       assert(close(distance(first, segment), distance(segment, first)));\n \
    \       assert(close(distance(first, line), distance(line, first)));\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    test_line_segment();\n    test_ray_point_and_line();\n\
    \    test_ray_segment();\n    test_ray_ray();\n    test_randomized_against_long_segments();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/ray.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cmath>\n#include <cstdint>\n#include <iostream>\n\nnamespace {\n\nusing namespace\
    \ m1une::geometry;\nusing P = Point<long long>;\nusing IntegerRay = Ray<long long>;\n\
    using IntegerLine = Line<long long>;\nusing IntegerSegment = Segment<long long>;\n\
    \nbool close(long double first, long double second) {\n    return std::fabs(first\
    \ - second) <= 1e-10L;\n}\n\nIntegerSegment long_segment(const IntegerRay& ray)\
    \ {\n    P direction = ray.through - ray.origin;\n    IntegerSegment result;\n\
    \    result.a = ray.origin;\n    result.b = ray.origin + direction * 1000;\n \
    \   return result;\n}\n\nvoid test_line_segment() {\n    IntegerLine horizontal;\n\
    \    horizontal.a = P(0, 0);\n    horizontal.b = P(1, 0);\n\n    IntegerSegment\
    \ crossing;\n    crossing.a = P(2, -3);\n    crossing.b = P(2, 4);\n    assert(intersects(horizontal,\
    \ crossing));\n    assert(intersects(crossing, horizontal));\n    assert(close(distance(horizontal,\
    \ crossing), 0));\n    auto point = line_segment_intersection(horizontal, crossing);\n\
    \    assert(point.has_value());\n    assert(close(point->x, 2));\n    assert(close(point->y,\
    \ 0));\n\n    IntegerSegment above;\n    above.a = P(-1, 3);\n    above.b = P(4,\
    \ 3);\n    assert(!intersects(horizontal, above));\n    assert(close(distance(horizontal,\
    \ above), 3));\n    assert(close(distance(above, horizontal), 3));\n    assert(!line_segment_intersection(horizontal,\
    \ above).has_value());\n\n    IntegerSegment overlapping;\n    overlapping.a =\
    \ P(2, 0);\n    overlapping.b = P(5, 0);\n    assert(intersects(horizontal, overlapping));\n\
    \    assert(close(distance(horizontal, overlapping), 0));\n    assert(!line_segment_intersection(horizontal,\
    \ overlapping).has_value());\n\n    IntegerSegment point_segment;\n    point_segment.a\
    \ = P(7, 0);\n    point_segment.b = point_segment.a;\n    auto degenerate = line_segment_intersection(horizontal,\
    \ point_segment);\n    assert(degenerate.has_value());\n    assert(close(degenerate->x,\
    \ 7));\n}\n\nvoid test_ray_point_and_line() {\n    IntegerRay ray;\n    ray.origin\
    \ = P(0, 0);\n    ray.through = P(2, 0);\n\n    assert(on_ray(ray, P(0, 0)));\n\
    \    assert(on_ray(ray, P(5, 0)));\n    assert(!on_ray(ray, P(-1, 0)));\n    assert(!on_ray(ray,\
    \ P(1, 1)));\n    assert(close(distance(ray, P(-3, 4)), 5));\n    assert(close(distance(P(-3,\
    \ 4), ray), 5));\n\n    Point<long double> projected = projection(ray, P(-3, 4));\n\
    \    assert(close(projected.x, 0));\n    assert(close(projected.y, 0));\n\n  \
    \  IntegerLine ahead;\n    ahead.a = P(3, -2);\n    ahead.b = P(3, 2);\n    assert(intersects(ray,\
    \ ahead));\n    assert(close(distance(ray, ahead), 0));\n    auto hit = ray_line_intersection(ray,\
    \ ahead);\n    assert(hit.has_value());\n    assert(close(hit->x, 3));\n    assert(close(hit->y,\
    \ 0));\n\n    IntegerLine behind;\n    behind.a = P(-3, -2);\n    behind.b = P(-3,\
    \ 2);\n    assert(!intersects(ray, behind));\n    assert(close(distance(ray, behind),\
    \ 3));\n    assert(!ray_line_intersection(ray, behind).has_value());\n\n    IntegerLine\
    \ parallel_line;\n    parallel_line.a = P(0, 4);\n    parallel_line.b = P(1, 4);\n\
    \    assert(!intersects(ray, parallel_line));\n    assert(close(distance(ray,\
    \ parallel_line), 4));\n\n    IntegerLine supporting;\n    supporting.a = P(-10,\
    \ 0);\n    supporting.b = P(10, 0);\n    assert(intersects(ray, supporting));\n\
    \    assert(!ray_line_intersection(ray, supporting).has_value());\n}\n\nvoid test_ray_segment()\
    \ {\n    IntegerRay ray;\n    ray.origin = P(0, 0);\n    ray.through = P(1, 0);\n\
    \n    IntegerSegment crossing;\n    crossing.a = P(3, -2);\n    crossing.b = P(3,\
    \ 2);\n    assert(intersects(ray, crossing));\n    assert(intersects(crossing,\
    \ ray));\n    auto hit = ray_segment_intersection(ray, crossing);\n    assert(hit.has_value());\n\
    \    assert(close(hit->x, 3));\n    assert(close(hit->y, 0));\n\n    IntegerSegment\
    \ behind;\n    behind.a = P(-4, -2);\n    behind.b = P(-4, 2);\n    assert(!intersects(ray,\
    \ behind));\n    assert(close(distance(ray, behind), 4));\n\n    IntegerSegment\
    \ overlap;\n    overlap.a = P(-2, 0);\n    overlap.b = P(5, 0);\n    assert(intersects(ray,\
    \ overlap));\n    assert(!ray_segment_intersection(ray, overlap).has_value());\n\
    \n    IntegerSegment touching_origin;\n    touching_origin.a = P(-2, 0);\n   \
    \ touching_origin.b = P(0, 0);\n    auto endpoint_hit = ray_segment_intersection(ray,\
    \ touching_origin);\n    assert(endpoint_hit.has_value());\n    assert(close(endpoint_hit->x,\
    \ 0));\n    assert(close(endpoint_hit->y, 0));\n\n    IntegerSegment separated;\n\
    \    separated.a = P(-3, 4);\n    separated.b = P(-1, 4);\n    assert(!intersects(ray,\
    \ separated));\n    assert(close(distance(ray, separated), std::sqrt(17.0L)));\n\
    \    assert(close(distance(separated, ray), std::sqrt(17.0L)));\n}\n\nvoid test_ray_ray()\
    \ {\n    IntegerRay horizontal;\n    horizontal.origin = P(0, 0);\n    horizontal.through\
    \ = P(1, 0);\n\n    IntegerRay vertical;\n    vertical.origin = P(3, -2);\n  \
    \  vertical.through = P(3, -1);\n    assert(intersects(horizontal, vertical));\n\
    \    auto crossing = ray_intersection(horizontal, vertical);\n    assert(crossing.has_value());\n\
    \    assert(close(crossing->x, 3));\n    assert(close(crossing->y, 0));\n\n  \
    \  IntegerRay diverging;\n    diverging.origin = P(-2, 0);\n    diverging.through\
    \ = P(-3, 0);\n    assert(!intersects(horizontal, diverging));\n    assert(close(distance(horizontal,\
    \ diverging), 2));\n    assert(!ray_intersection(horizontal, diverging).has_value());\n\
    \n    IntegerRay facing;\n    facing.origin = P(4, 0);\n    facing.through = P(3,\
    \ 0);\n    assert(intersects(horizontal, facing));\n    assert(close(distance(horizontal,\
    \ facing), 0));\n    assert(!ray_intersection(horizontal, facing).has_value());\n\
    \n    IntegerRay opposite_at_origin;\n    opposite_at_origin.origin = P(0, 0);\n\
    \    opposite_at_origin.through = P(-1, 0);\n    auto origin_hit = ray_intersection(horizontal,\
    \ opposite_at_origin);\n    assert(origin_hit.has_value());\n    assert(close(origin_hit->x,\
    \ 0));\n    assert(close(origin_hit->y, 0));\n\n    IntegerRay offset;\n    offset.origin\
    \ = P(-2, 3);\n    offset.through = P(-3, 3);\n    assert(!intersects(horizontal,\
    \ offset));\n    assert(close(distance(horizontal, offset), std::sqrt(13.0L)));\n\
    }\n\nvoid test_randomized_against_long_segments() {\n    std::uint64_t state =\
    \ 0x18273645abcdefULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n    auto\
    \ random_point = [&]() {\n        return P(\n            static_cast<long long>(random()\
    \ % 11) - 5,\n            static_cast<long long>(random() % 11) - 5\n        );\n\
    \    };\n\n    for (int trial = 0; trial < 20000; ++trial) {\n        IntegerRay\
    \ first;\n        first.origin = random_point();\n        do {\n            first.through\
    \ = random_point();\n        } while (first.origin == first.through);\n\n    \
    \    IntegerRay second;\n        second.origin = random_point();\n        do {\n\
    \            second.through = random_point();\n        } while (second.origin\
    \ == second.through);\n\n        IntegerSegment segment;\n        segment.a =\
    \ random_point();\n        segment.b = random_point();\n\n        IntegerLine\
    \ line;\n        line.a = random_point();\n        do {\n            line.b =\
    \ random_point();\n        } while (line.a == line.b);\n\n        IntegerSegment\
    \ first_long = long_segment(first);\n        IntegerSegment second_long = long_segment(second);\n\
    \n        assert(intersects(first, segment) == intersects(first_long, segment));\n\
    \        assert(intersects(first, second) == intersects(first_long, second_long));\n\
    \        assert(intersects(first, line) == intersects(line, first_long));\n\n\
    \        assert(close(distance(first, segment), distance(first_long, segment)));\n\
    \        assert(close(distance(first, second), distance(first_long, second_long)));\n\
    \        assert(close(distance(first, line), distance(line, first_long)));\n\n\
    \        assert(intersects(first, segment) == intersects(segment, first));\n \
    \       assert(close(distance(first, segment), distance(segment, first)));\n \
    \       assert(close(distance(first, line), distance(line, first)));\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    test_line_segment();\n    test_ray_point_and_line();\n\
    \    test_ray_segment();\n    test_ray_ray();\n    test_randomized_against_long_segments();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: true
  path: verify/geometry/ray.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 12:04:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/ray.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/ray.test.cpp
- /verify/verify/geometry/ray.test.cpp.html
title: verify/geometry/ray.test.cpp
---
