---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':x:'
    path: geometry/circle.hpp
    title: Circles
  - icon: ':x:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':x:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':x:'
    path: geometry/polygon.hpp
    title: Polygons and Convex Hull
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/geometry/geometry_algorithms.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"geometry/all.hpp\"\
    \n\n\n\n#line 1 \"geometry/circle.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <vector>\n\n#line 1 \"geometry/line.hpp\"\
    \n\n\n\n#line 7 \"geometry/line.hpp\"\n#include <optional>\n\n#line 1 \"geometry/point.hpp\"\
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
    \ norm(const Point<T>& point) {\n    return std::hypotl(\n        static_cast<long\
    \ double>(point.x),\n        static_cast<long double>(point.y)\n    );\n}\n\n\
    template <Coordinate T>\nlong double distance(const Point<T>& a, const Point<T>&\
    \ b) {\n    return std::hypotl(\n        static_cast<long double>(a.x) - static_cast<long\
    \ double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long double>(b.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nconstexpr int sign(wide_type<T> value,\
    \ long double eps = 1e-12L) {\n    if constexpr (std::integral<T>) {\n       \
    \ return (value > 0) - (value < 0);\n    } else {\n        return (value > eps)\
    \ - (value < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nconstexpr int orientation(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>& c,\n    long\
    \ double eps = 1e-12L\n) {\n    return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr bool collinear(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return orientation(a, b, c, eps) == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long\
    \ double> rotate(const Point<T>& point, long double angle) {\n    long double\
    \ cosine = std::cos(angle);\n    long double sine = std::sin(angle);\n    return\
    \ Point<long double>(\n        static_cast<long double>(point.x) * cosine -\n\
    \            static_cast<long double>(point.y) * sine,\n        static_cast<long\
    \ double>(point.x) * sine +\n            static_cast<long double>(point.y) * cosine\n\
    \    );\n}\n\ntemplate <Coordinate T>\nPoint<long double> normalized(const Point<T>&\
    \ point) {\n    long double length = norm(point);\n    assert(length != 0);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) / length,\n\
    \        static_cast<long double>(point.y) / length\n    );\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/line.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Line {\n  \
    \  Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nstruct Segment\
    \ {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nbool parallel(const\
    \ Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y\
    \ = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n\
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x *\
    \ second_y - first_y * second_x, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool\
    \ orthogonal(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L)\
    \ {\n    using W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n\
    \    W first_y = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x)\
    \ - W(second.a.x);\n    W second_y = W(second.b.y) - W(second.a.y);\n    return\
    \ sign<T>(first_x * second_x + first_y * second_y, eps) == 0;\n}\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> projection(const Line<T>& line, const Point<T>& point)\
    \ {\n    assert(line.a != line.b);\n    Point<long double> a(line.a);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - a.x,\n        static_cast<long double>(point.y) - a.y\n \
    \   );\n    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    return a + direction * ratio;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ reflection(const Line<T>& line, const Point<T>& point) {\n    Point<long double>\
    \ projected = projection(line, point);\n    return projected * 2.0L - Point<long\
    \ double>(point);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>&\
    \ line, const Point<T>& point) {\n    assert(line.a != line.b);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - static_cast<long double>(line.a.x),\n        static_cast<long\
    \ double>(point.y) - static_cast<long double>(line.a.y)\n    );\n    return std::fabsl(cross(direction,\
    \ offset)) / norm(direction);\n}\n\ntemplate <Coordinate T>\nbool on_segment(\n\
    \    const Segment<T>& segment,\n    const Point<T>& point,\n    long double eps\
    \ = 1e-12L\n) {\n    if (orientation(segment.a, segment.b, point, eps) != 0) return\
    \ false;\n    using W = wide_type<T>;\n    W px = W(point.x);\n    W py = W(point.y);\n\
    \    W min_x = std::min(W(segment.a.x), W(segment.b.x));\n    W max_x = std::max(W(segment.a.x),\
    \ W(segment.b.x));\n    W min_y = std::min(W(segment.a.y), W(segment.b.y));\n\
    \    W max_y = std::max(W(segment.a.y), W(segment.b.y));\n    if constexpr (std::integral<T>)\
    \ {\n        return min_x <= px && px <= max_x && min_y <= py && py <= max_y;\n\
    \    } else {\n        return min_x - eps <= px && px <= max_x + eps &&\n    \
    \           min_y - eps <= py && py <= max_y + eps;\n    }\n}\n\ntemplate <Coordinate\
    \ T>\nbool intersects(\n    const Segment<T>& first,\n    const Segment<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    int abc = orientation(first.a, first.b,\
    \ second.a, eps);\n    int abd = orientation(first.a, first.b, second.b, eps);\n\
    \    int cda = orientation(second.a, second.b, first.a, eps);\n    int cdb = orientation(second.a,\
    \ second.b, first.b, eps);\n\n    if (abc == 0 && on_segment(first, second.a,\
    \ eps)) return true;\n    if (abd == 0 && on_segment(first, second.b, eps)) return\
    \ true;\n    if (cda == 0 && on_segment(second, first.a, eps)) return true;\n\
    \    if (cdb == 0 && on_segment(second, first.b, eps)) return true;\n    return\
    \ abc * abd < 0 && cda * cdb < 0;\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Segment<T>& segment, const Point<T>& point) {\n    Point<long double> a(segment.a);\n\
    \    Point<long double> b(segment.b);\n    Point<long double> p(point);\n    Point<long\
    \ double> direction = b - a;\n    long double length_squared = dot(direction,\
    \ direction);\n    if (length_squared == 0) return geometry::distance(segment.a,\
    \ point);\n    long double ratio = dot(p - a, direction) / length_squared;\n \
    \   ratio = std::clamp(ratio, 0.0L, 1.0L);\n    Point<long double> closest = a\
    \ + direction * ratio;\n    return geometry::distance(closest, p);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Segment<T>& first, const Segment<T>&\
    \ second) {\n    if (intersects(first, second)) return 0;\n    return std::min({\n\
    \        distance(first, second.a),\n        distance(first, second.b),\n    \
    \    distance(second, first.a),\n        distance(second, first.b),\n    });\n\
    }\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> line_intersection(\n\
    \    const Line<T>& first,\n    const Line<T>& second,\n    long double eps =\
    \ 1e-12L\n) {\n    assert(first.a != first.b);\n    assert(second.a != second.b);\n\
    \    Point<long double> p(first.a);\n    Point<long double> q(second.a);\n   \
    \ Point<long double> r = Point<long double>(first.b) - p;\n    Point<long double>\
    \ s = Point<long double>(second.b) - q;\n    long double denominator = cross(r,\
    \ s);\n    if (std::fabsl(denominator) <= eps) return std::nullopt;\n    long\
    \ double ratio = cross(q - p, s) / denominator;\n    return p + r * ratio;\n}\n\
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/circle.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct\
    \ Circle {\n    Point<T> center;\n    T radius;\n};\n\nenum class CircleRelation\
    \ {\n    Separate,\n    ExternallyTangent,\n    Intersecting,\n    InternallyTangent,\n\
    \    Contained,\n    Coincident,\n};\n\ntemplate <Coordinate T>\nCircleRelation\
    \ circle_relation(\n    const Circle<T>& first,\n    const Circle<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius\
    \ >= 0);\n    long double d = geometry::distance(first.center, second.center);\n\
    \    long double r1 = static_cast<long double>(first.radius);\n    long double\
    \ r2 = static_cast<long double>(second.radius);\n    long double sum = r1 + r2;\n\
    \    long double difference = std::fabsl(r1 - r2);\n    if (d <= eps && difference\
    \ <= eps) return CircleRelation::Coincident;\n    if (sum < d - eps) return CircleRelation::Separate;\n\
    \    if (std::fabsl(d - sum) <= eps) return CircleRelation::ExternallyTangent;\n\
    \    if (d < difference - eps) return CircleRelation::Contained;\n    if (std::fabsl(d\
    \ - difference) <= eps) return CircleRelation::InternallyTangent;\n    return\
    \ CircleRelation::Intersecting;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> circle_line_intersections(\n    const Circle<T>& circle,\n    const\
    \ Line<T>& line,\n    long double eps = 1e-12L\n) {\n    assert(circle.radius\
    \ >= 0);\n    assert(line.a != line.b);\n    Point<long double> foot = projection(line,\
    \ circle.center);\n    long double radius = static_cast<long double>(circle.radius);\n\
    \    long double distance_to_line = geometry::distance(line, circle.center);\n\
    \    if (radius < distance_to_line - eps) return {};\n\n    Point<long double>\
    \ direction =\n        Point<long double>(line.b) - Point<long double>(line.a);\n\
    \    direction = normalized(direction);\n    long double offset_squared =\n  \
    \      std::max(0.0L, radius * radius - distance_to_line * distance_to_line);\n\
    \    long double offset = std::sqrt(offset_squared);\n    if (offset <= eps) return\
    \ {foot};\n\n    Point<long double> first = foot - direction * offset;\n    Point<long\
    \ double> second = foot + direction * offset;\n    if (second < first) std::swap(first,\
    \ second);\n    return {first, second};\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> circle_intersections(\n    const Circle<T>& first,\n    const Circle<T>&\
    \ second,\n    long double eps = 1e-12L\n) {\n    assert(first.radius >= 0);\n\
    \    assert(second.radius >= 0);\n    CircleRelation relation = circle_relation(first,\
    \ second, eps);\n    if (\n        relation == CircleRelation::Separate ||\n \
    \       relation == CircleRelation::Contained ||\n        relation == CircleRelation::Coincident\n\
    \    ) {\n        return {};\n    }\n\n    Point<long double> c1(first.center);\n\
    \    Point<long double> c2(second.center);\n    Point<long double> direction =\
    \ c2 - c1;\n    long double d = norm(direction);\n    long double r1 = static_cast<long\
    \ double>(first.radius);\n    long double r2 = static_cast<long double>(second.radius);\n\
    \    long double along = (r1 * r1 - r2 * r2 + d * d) / (2 * d);\n    long double\
    \ height_squared = std::max(0.0L, r1 * r1 - along * along);\n    Point<long double>\
    \ unit = direction / d;\n    Point<long double> base = c1 + unit * along;\n  \
    \  long double height = std::sqrt(height_squared);\n    if (height <= eps) return\
    \ {base};\n\n    Point<long double> perpendicular(-unit.y, unit.x);\n    Point<long\
    \ double> a = base - perpendicular * height;\n    Point<long double> b = base\
    \ + perpendicular * height;\n    if (b < a) std::swap(a, b);\n    return {a, b};\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 1 \"geometry/polygon.hpp\"\
    \n\n\n\n#line 7 \"geometry/polygon.hpp\"\n\n#line 9 \"geometry/polygon.hpp\"\n\
    \nnamespace m1une {\nnamespace geometry {\n\nenum class PointInPolygon {\n   \
    \ Outside = 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\ntemplate <Coordinate\
    \ T>\nwide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {\n   \
    \ wide_type<T> result = 0;\n    int n = int(polygon.size());\n    for (int i =\
    \ 0; i < n; i++) {\n        result += cross(polygon[i], polygon[(i + 1) % n]);\n\
    \    }\n    return result;\n}\n\ntemplate <Coordinate T>\nlong double polygon_area(const\
    \ std::vector<Point<T>>& polygon) {\n    return std::fabsl(static_cast<long double>(polygon_area2(polygon)))\
    \ / 2;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> convex_hull(\n   \
    \ std::vector<Point<T>> points,\n    bool include_collinear = false\n) {\n   \
    \ std::sort(points.begin(), points.end());\n    points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n    int n = int(points.size());\n    if (n <=\
    \ 1) return points;\n\n    std::vector<Point<T>> hull;\n    hull.reserve(2 * n);\n\
    \    auto should_pop = [include_collinear](\n        const Point<T>& a,\n    \
    \    const Point<T>& b,\n        const Point<T>& c\n    ) {\n        int turn\
    \ = orientation(a, b, c);\n        return include_collinear ? turn < 0 : turn\
    \ <= 0;\n    };\n\n    for (const Point<T>& point : points) {\n        while (\n\
    \            hull.size() >= 2 &&\n            should_pop(hull[hull.size() - 2],\
    \ hull.back(), point)\n        ) {\n            hull.pop_back();\n        }\n\
    \        hull.push_back(point);\n    }\n\n    std::size_t lower_size = hull.size();\n\
    \    for (int i = n - 2; i >= 0; i--) {\n        const Point<T>& point = points[i];\n\
    \        while (\n            hull.size() > lower_size &&\n            should_pop(hull[hull.size()\
    \ - 2], hull.back(), point)\n        ) {\n            hull.pop_back();\n     \
    \   }\n        hull.push_back(point);\n    }\n    hull.pop_back();\n\n    if (include_collinear\
    \ && hull.size() == 2 * points.size() - 2) {\n        hull = std::move(points);\n\
    \    }\n    return hull;\n}\n\ntemplate <Coordinate T>\nPointInPolygon point_in_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    bool inside = false;\n    int n = int(polygon.size());\n\
    \    for (int i = 0; i < n; i++) {\n        const Point<T>& a = polygon[i];\n\
    \        const Point<T>& b = polygon[(i + 1) % n];\n        if (on_segment(Segment<T>{a,\
    \ b}, point, eps)) {\n            return PointInPolygon::Boundary;\n        }\n\
    \n        if (a.y <= point.y) {\n            if (point.y < b.y && orientation(a,\
    \ b, point, eps) > 0) {\n                inside = !inside;\n            }\n  \
    \      } else if (b.y <= point.y && orientation(a, b, point, eps) < 0) {\n   \
    \         inside = !inside;\n        }\n    }\n    return inside ? PointInPolygon::Inside\
    \ : PointInPolygon::Outside;\n}\n\ntemplate <Coordinate T>\nwide_type<T> convex_diameter2(const\
    \ std::vector<Point<T>>& polygon) {\n    int n = int(polygon.size());\n    if\
    \ (n <= 1) return 0;\n    if (n == 2) return distance2(polygon[1], polygon[0]);\n\
    \n    wide_type<T> result = 0;\n    int opposite = 1;\n    for (int i = 0; i <\
    \ n; i++) {\n        int next = (i + 1) % n;\n        while (true) {\n       \
    \     int candidate = (opposite + 1) % n;\n            auto current_area = cross(polygon[i],\
    \ polygon[next], polygon[opposite]);\n            auto candidate_area = cross(polygon[i],\
    \ polygon[next], polygon[candidate]);\n            if (candidate_area <= current_area)\
    \ break;\n            opposite = candidate;\n        }\n        result = std::max(result,\
    \ distance2(polygon[i], polygon[opposite]));\n        result = std::max(result,\
    \ distance2(polygon[next], polygon[opposite]));\n    }\n    return result;\n}\n\
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 8 \"geometry/all.hpp\"\
    \n\n\n#line 4 \"verify/geometry/geometry_algorithms.test.cpp\"\n\n#line 8 \"verify/geometry/geometry_algorithms.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 11 \"verify/geometry/geometry_algorithms.test.cpp\"\
    \n\nnamespace {\n\nbool close(long double a, long double b) {\n    return std::fabsl(a\
    \ - b) <= 1e-10L;\n}\n\nvoid test_basic() {\n    using namespace m1une::geometry;\n\
    \    using P = Point<long long>;\n\n    P a(0, 0);\n    P b(3, 0);\n    P c(1,\
    \ 2);\n    assert(cross(a, b, c) == 6);\n    assert(orientation(a, b, c) == 1);\n\
    \    assert(orientation(a, c, b) == -1);\n    assert(collinear(a, P(1, 0), b));\n\
    \n    Segment<long long> first;\n    first.a = P(0, 0);\n    first.b = P(4, 4);\n\
    \    Segment<long long> second;\n    second.a = P(0, 4);\n    second.b = P(4,\
    \ 0);\n    assert(intersects(first, second));\n    assert(close(distance(first,\
    \ second), 0));\n\n    Line<long long> horizontal;\n    horizontal.a = P(0, 0);\n\
    \    horizontal.b = P(4, 0);\n    [[maybe_unused]] Point<long double> projected\
    \ = projection(horizontal, P(2, 3));\n    assert(close(projected.x, 2));\n   \
    \ assert(close(projected.y, 0));\n\n    Line<long long> diagonal1;\n    diagonal1.a\
    \ = P(0, 0);\n    diagonal1.b = P(2, 2);\n    Line<long long> diagonal2;\n   \
    \ diagonal2.a = P(0, 2);\n    diagonal2.b = P(2, 0);\n    [[maybe_unused]] auto\
    \ crossing = line_intersection(diagonal1, diagonal2);\n    assert(crossing.has_value());\n\
    \    assert(close(crossing->x, 1));\n    assert(close(crossing->y, 1));\n\n  \
    \  std::vector<P> square;\n    square.emplace_back(0, 0);\n    square.emplace_back(2,\
    \ 0);\n    square.emplace_back(2, 2);\n    square.emplace_back(0, 2);\n    assert(polygon_area2(square)\
    \ == 8);\n    assert(point_in_polygon(square, P(1, 1)) == PointInPolygon::Inside);\n\
    \    assert(point_in_polygon(square, P(0, 1)) == PointInPolygon::Boundary);\n\
    \    assert(point_in_polygon(square, P(3, 1)) == PointInPolygon::Outside);\n \
    \   assert(convex_diameter2(square) == 8);\n\n    Circle<long double> circle;\n\
    \    circle.center = Point<long double>(0, 0);\n    circle.radius = 2;\n    Line<long\
    \ double> line;\n    line.a = Point<long double>(-3, 0);\n    line.b = Point<long\
    \ double>(3, 0);\n    auto intersections = circle_line_intersections(circle, line);\n\
    \    assert(intersections.size() == 2);\n    assert(close(intersections[0].x,\
    \ -2));\n    assert(close(intersections[1].x, 2));\n\n    Circle<long double>\
    \ other;\n    other.center = Point<long double>(3, 0);\n    other.radius = 2;\n\
    \    assert(circle_relation(circle, other) == CircleRelation::Intersecting);\n\
    \    auto circle_points = circle_intersections(circle, other);\n    assert(circle_points.size()\
    \ == 2);\n    for ([[maybe_unused]] const auto& point : circle_points) {\n   \
    \     assert(close(distance(point, circle.center), circle.radius));\n        assert(close(distance(point,\
    \ other.center), other.radius));\n    }\n\n    std::vector<P> collinear_points;\n\
    \    collinear_points.emplace_back(2, 0);\n    collinear_points.emplace_back(0,\
    \ 0);\n    collinear_points.emplace_back(1, 0);\n    assert(convex_hull(collinear_points).size()\
    \ == 2);\n    assert(convex_hull(collinear_points, true) == std::vector<P>({P(0,\
    \ 0), P(1, 0), P(2, 0)}));\n}\n\nvoid test_randomized_hulls() {\n    using namespace\
    \ m1une::geometry;\n    using P = Point<long long>;\n    std::uint64_t state =\
    \ 41;\n    auto random = [&state]() {\n        state ^= state << 7;\n        state\
    \ ^= state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 3000; trial++) {\n        int n = int(random() % 30);\n        std::vector<P>\
    \ points;\n        for (int i = 0; i < n; i++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 31) - 15,\n               \
    \ static_cast<long long>(random() % 31) - 15\n            );\n        }\n    \
    \    std::vector<P> hull = convex_hull(points);\n        if (hull.size() >= 3)\
    \ {\n            assert(polygon_area2(hull) > 0);\n            for (int i = 0;\
    \ i < int(hull.size()); i++) {\n                assert(orientation(\n        \
    \            hull[i],\n                    hull[(i + 1) % hull.size()],\n    \
    \                hull[(i + 2) % hull.size()]\n                ) > 0);\n      \
    \      }\n\n            auto expected_diameter = wide_type<long long>(0);\n  \
    \          for (const P& a : hull) {\n                for (const P& b : hull)\
    \ {\n                    expected_diameter = std::max(expected_diameter, distance2(a,\
    \ b));\n                }\n            }\n            assert(convex_diameter2(hull)\
    \ == expected_diameter);\n        }\n\n        for ([[maybe_unused]] const P&\
    \ point : points) {\n            if (hull.size() >= 3) {\n                assert(point_in_polygon(hull,\
    \ point) != PointInPolygon::Outside);\n            } else if (hull.size() == 2)\
    \ {\n                Segment<long long> segment;\n                segment.a =\
    \ hull[0];\n                segment.b = hull[1];\n                assert(on_segment(segment,\
    \ point));\n            } else if (hull.size() == 1) {\n                assert(point\
    \ == hull[0]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_basic();\n    test_randomized_hulls();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    geometry/all.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nnamespace {\n\n\
    bool close(long double a, long double b) {\n    return std::fabsl(a - b) <= 1e-10L;\n\
    }\n\nvoid test_basic() {\n    using namespace m1une::geometry;\n    using P =\
    \ Point<long long>;\n\n    P a(0, 0);\n    P b(3, 0);\n    P c(1, 2);\n    assert(cross(a,\
    \ b, c) == 6);\n    assert(orientation(a, b, c) == 1);\n    assert(orientation(a,\
    \ c, b) == -1);\n    assert(collinear(a, P(1, 0), b));\n\n    Segment<long long>\
    \ first;\n    first.a = P(0, 0);\n    first.b = P(4, 4);\n    Segment<long long>\
    \ second;\n    second.a = P(0, 4);\n    second.b = P(4, 0);\n    assert(intersects(first,\
    \ second));\n    assert(close(distance(first, second), 0));\n\n    Line<long long>\
    \ horizontal;\n    horizontal.a = P(0, 0);\n    horizontal.b = P(4, 0);\n    [[maybe_unused]]\
    \ Point<long double> projected = projection(horizontal, P(2, 3));\n    assert(close(projected.x,\
    \ 2));\n    assert(close(projected.y, 0));\n\n    Line<long long> diagonal1;\n\
    \    diagonal1.a = P(0, 0);\n    diagonal1.b = P(2, 2);\n    Line<long long> diagonal2;\n\
    \    diagonal2.a = P(0, 2);\n    diagonal2.b = P(2, 0);\n    [[maybe_unused]]\
    \ auto crossing = line_intersection(diagonal1, diagonal2);\n    assert(crossing.has_value());\n\
    \    assert(close(crossing->x, 1));\n    assert(close(crossing->y, 1));\n\n  \
    \  std::vector<P> square;\n    square.emplace_back(0, 0);\n    square.emplace_back(2,\
    \ 0);\n    square.emplace_back(2, 2);\n    square.emplace_back(0, 2);\n    assert(polygon_area2(square)\
    \ == 8);\n    assert(point_in_polygon(square, P(1, 1)) == PointInPolygon::Inside);\n\
    \    assert(point_in_polygon(square, P(0, 1)) == PointInPolygon::Boundary);\n\
    \    assert(point_in_polygon(square, P(3, 1)) == PointInPolygon::Outside);\n \
    \   assert(convex_diameter2(square) == 8);\n\n    Circle<long double> circle;\n\
    \    circle.center = Point<long double>(0, 0);\n    circle.radius = 2;\n    Line<long\
    \ double> line;\n    line.a = Point<long double>(-3, 0);\n    line.b = Point<long\
    \ double>(3, 0);\n    auto intersections = circle_line_intersections(circle, line);\n\
    \    assert(intersections.size() == 2);\n    assert(close(intersections[0].x,\
    \ -2));\n    assert(close(intersections[1].x, 2));\n\n    Circle<long double>\
    \ other;\n    other.center = Point<long double>(3, 0);\n    other.radius = 2;\n\
    \    assert(circle_relation(circle, other) == CircleRelation::Intersecting);\n\
    \    auto circle_points = circle_intersections(circle, other);\n    assert(circle_points.size()\
    \ == 2);\n    for ([[maybe_unused]] const auto& point : circle_points) {\n   \
    \     assert(close(distance(point, circle.center), circle.radius));\n        assert(close(distance(point,\
    \ other.center), other.radius));\n    }\n\n    std::vector<P> collinear_points;\n\
    \    collinear_points.emplace_back(2, 0);\n    collinear_points.emplace_back(0,\
    \ 0);\n    collinear_points.emplace_back(1, 0);\n    assert(convex_hull(collinear_points).size()\
    \ == 2);\n    assert(convex_hull(collinear_points, true) == std::vector<P>({P(0,\
    \ 0), P(1, 0), P(2, 0)}));\n}\n\nvoid test_randomized_hulls() {\n    using namespace\
    \ m1une::geometry;\n    using P = Point<long long>;\n    std::uint64_t state =\
    \ 41;\n    auto random = [&state]() {\n        state ^= state << 7;\n        state\
    \ ^= state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 3000; trial++) {\n        int n = int(random() % 30);\n        std::vector<P>\
    \ points;\n        for (int i = 0; i < n; i++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 31) - 15,\n               \
    \ static_cast<long long>(random() % 31) - 15\n            );\n        }\n    \
    \    std::vector<P> hull = convex_hull(points);\n        if (hull.size() >= 3)\
    \ {\n            assert(polygon_area2(hull) > 0);\n            for (int i = 0;\
    \ i < int(hull.size()); i++) {\n                assert(orientation(\n        \
    \            hull[i],\n                    hull[(i + 1) % hull.size()],\n    \
    \                hull[(i + 2) % hull.size()]\n                ) > 0);\n      \
    \      }\n\n            auto expected_diameter = wide_type<long long>(0);\n  \
    \          for (const P& a : hull) {\n                for (const P& b : hull)\
    \ {\n                    expected_diameter = std::max(expected_diameter, distance2(a,\
    \ b));\n                }\n            }\n            assert(convex_diameter2(hull)\
    \ == expected_diameter);\n        }\n\n        for ([[maybe_unused]] const P&\
    \ point : points) {\n            if (hull.size() >= 3) {\n                assert(point_in_polygon(hull,\
    \ point) != PointInPolygon::Outside);\n            } else if (hull.size() == 2)\
    \ {\n                Segment<long long> segment;\n                segment.a =\
    \ hull[0];\n                segment.b = hull[1];\n                assert(on_segment(segment,\
    \ point));\n            } else if (hull.size() == 1) {\n                assert(point\
    \ == hull[0]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_basic();\n    test_randomized_hulls();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - geometry/all.hpp
  - geometry/circle.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  - geometry/polygon.hpp
  isVerificationFile: true
  path: verify/geometry/geometry_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 03:01:41+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/geometry/geometry_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/geometry_algorithms.test.cpp
- /verify/verify/geometry/geometry_algorithms.test.cpp.html
title: verify/geometry/geometry_algorithms.test.cpp
---
