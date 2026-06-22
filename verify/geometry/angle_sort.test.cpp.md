---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/angle_sort.hpp
    title: Angle Sort
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"verify/geometry/angle_sort.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\n#line 1 \"geometry/angle_sort.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#include <cmath>\n#include <concepts>\n#include <cassert>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace geometry {\n\ntemplate <typename T>\nconcept Coordinate\
    \ = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate\
    \ <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>, __int128_t,\
    \ long double>;\n\ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\
    \n    constexpr Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value)\
    \ : x(x_value), y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr\
    \ Point(const Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 8 \"geometry/angle_sort.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nenum class AngleSortStart {\n    NegativeXAxis,\n    PositiveXAxis,\n\
    };\n\ntemplate <Coordinate T>\nstruct AngleLess {\n    Point<T> origin;\n    AngleSortStart\
    \ start;\n\n    constexpr explicit AngleLess(\n        Point<T> origin_value =\
    \ Point<T>(),\n        AngleSortStart start_value = AngleSortStart::NegativeXAxis\n\
    \    ) : origin(origin_value), start(start_value) {}\n\n    constexpr bool operator()(\n\
    \        const Point<T>& first,\n        const Point<T>& second\n    ) const {\n\
    \        using W = wide_type<T>;\n        W first_x = W(first.x) - W(origin.x);\n\
    \        W first_y = W(first.y) - W(origin.y);\n        W second_x = W(second.x)\
    \ - W(origin.x);\n        W second_y = W(second.y) - W(origin.y);\n        W first_distance\
    \ = first_x * first_x + first_y * first_y;\n        W second_distance = second_x\
    \ * second_x + second_y * second_y;\n\n        // atan2(0, 0) is treated as angle\
    \ zero.\n        if (first_distance == 0) first_x = 1;\n        if (second_distance\
    \ == 0) second_x = 1;\n\n        auto half = [this](W x, W y) {\n            if\
    \ (start == AngleSortStart::PositiveXAxis) {\n                return y < 0 ||\
    \ (y == 0 && x < 0);\n            }\n            return y > 0 || (y == 0 && x\
    \ < 0);\n        };\n\n        bool first_half = half(first_x, first_y);\n   \
    \     bool second_half = half(second_x, second_y);\n        if (first_half !=\
    \ second_half) return first_half < second_half;\n\n        W product = first_x\
    \ * second_y - first_y * second_x;\n        if (product != 0) return product >\
    \ 0;\n\n        return first_distance < second_distance;\n    }\n};\n\n// Sorts\
    \ points counterclockwise by angle around `origin`.\ntemplate <Coordinate T>\n\
    void sort_by_angle(\n    std::vector<Point<T>>& points,\n    Point<T> origin =\
    \ Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n) {\n\
    \    std::sort(points.begin(), points.end(), AngleLess<T>(origin, start));\n}\n\
    \n// Returns a counterclockwise angle-sorted copy.\ntemplate <Coordinate T>\n\
    std::vector<Point<T>> angle_sorted(\n    std::vector<Point<T>> points,\n    Point<T>\
    \ origin = Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n\
    ) {\n    sort_by_angle(points, origin, start);\n    return points;\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n\n#line 4 \"verify/geometry/angle_sort.test.cpp\"\
    \n\n#line 8 \"verify/geometry/angle_sort.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 11 \"verify/geometry/angle_sort.test.cpp\"\n\nnamespace {\n\
    \nusing Point = m1une::geometry::Point<long long>;\n\nlong double argument(const\
    \ Point& point, const Point& origin) {\n    long double angle = std::atan2(\n\
    \        static_cast<long double>(point.y) - origin.y,\n        static_cast<long\
    \ double>(point.x) - origin.x\n    );\n    if (point == origin) return 0;\n  \
    \  return angle;\n}\n\nvoid test_fixed() {\n    std::vector<Point> points;\n \
    \   points.emplace_back(-1, 0);\n    points.emplace_back(0, 1);\n    points.emplace_back(2,\
    \ 0);\n    points.emplace_back(0, 0);\n    points.emplace_back(0, -1);\n    points.emplace_back(1,\
    \ 0);\n\n    m1une::geometry::sort_by_angle(points);\n    std::vector<Point> expected;\n\
    \    expected.emplace_back(0, -1);\n    expected.emplace_back(0, 0);\n    expected.emplace_back(1,\
    \ 0);\n    expected.emplace_back(2, 0);\n    expected.emplace_back(0, 1);\n  \
    \  expected.emplace_back(-1, 0);\n    assert(points == expected);\n\n    auto\
    \ positive = m1une::geometry::angle_sorted(\n        points,\n        Point(0,\
    \ 0),\n        m1une::geometry::AngleSortStart::PositiveXAxis\n    );\n    expected.clear();\n\
    \    expected.emplace_back(0, 0);\n    expected.emplace_back(1, 0);\n    expected.emplace_back(2,\
    \ 0);\n    expected.emplace_back(0, 1);\n    expected.emplace_back(-1, 0);\n \
    \   expected.emplace_back(0, -1);\n    assert(positive == expected);\n}\n\nvoid\
    \ test_randomized() {\n    std::uint64_t state = 239;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ Point origin(\n            static_cast<long long>(random() % 21) - 10,\n   \
    \         static_cast<long long>(random() % 21) - 10\n        );\n        int\
    \ size = int(random() % 40);\n        std::vector<Point> points;\n        points.reserve(size);\n\
    \        for (int index = 0; index < size; ++index) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 41) - 20,\n               \
    \ static_cast<long long>(random() % 41) - 20\n            );\n        }\n\n  \
    \      auto expected = points;\n        std::sort(expected.begin(), expected.end(),\
    \ [&origin](\n            const Point& first,\n            const Point& second\n\
    \        ) {\n            long double first_angle = argument(first, origin);\n\
    \            long double second_angle = argument(second, origin);\n          \
    \  if (first_angle != second_angle) return first_angle < second_angle;\n     \
    \       return m1une::geometry::distance2(first, origin)\n                   <\
    \ m1une::geometry::distance2(second, origin);\n        });\n\n        m1une::geometry::sort_by_angle(points,\
    \ origin);\n        assert(points == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<Point> points(n);\n    for (Point& point : points) std::cin\
    \ >> point.x >> point.y;\n    m1une::geometry::sort_by_angle(points);\n    for\
    \ (const Point& point : points) {\n        std::cout << point.x << ' ' << point.y\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n\n#include \"../../geometry/angle_sort.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <cstdint>\n#include <iostream>\n#include\
    \ <vector>\n\nnamespace {\n\nusing Point = m1une::geometry::Point<long long>;\n\
    \nlong double argument(const Point& point, const Point& origin) {\n    long double\
    \ angle = std::atan2(\n        static_cast<long double>(point.y) - origin.y,\n\
    \        static_cast<long double>(point.x) - origin.x\n    );\n    if (point ==\
    \ origin) return 0;\n    return angle;\n}\n\nvoid test_fixed() {\n    std::vector<Point>\
    \ points;\n    points.emplace_back(-1, 0);\n    points.emplace_back(0, 1);\n \
    \   points.emplace_back(2, 0);\n    points.emplace_back(0, 0);\n    points.emplace_back(0,\
    \ -1);\n    points.emplace_back(1, 0);\n\n    m1une::geometry::sort_by_angle(points);\n\
    \    std::vector<Point> expected;\n    expected.emplace_back(0, -1);\n    expected.emplace_back(0,\
    \ 0);\n    expected.emplace_back(1, 0);\n    expected.emplace_back(2, 0);\n  \
    \  expected.emplace_back(0, 1);\n    expected.emplace_back(-1, 0);\n    assert(points\
    \ == expected);\n\n    auto positive = m1une::geometry::angle_sorted(\n      \
    \  points,\n        Point(0, 0),\n        m1une::geometry::AngleSortStart::PositiveXAxis\n\
    \    );\n    expected.clear();\n    expected.emplace_back(0, 0);\n    expected.emplace_back(1,\
    \ 0);\n    expected.emplace_back(2, 0);\n    expected.emplace_back(0, 1);\n  \
    \  expected.emplace_back(-1, 0);\n    expected.emplace_back(0, -1);\n    assert(positive\
    \ == expected);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 239;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 5000; ++trial) {\n        Point origin(\n            static_cast<long long>(random()\
    \ % 21) - 10,\n            static_cast<long long>(random() % 21) - 10\n      \
    \  );\n        int size = int(random() % 40);\n        std::vector<Point> points;\n\
    \        points.reserve(size);\n        for (int index = 0; index < size; ++index)\
    \ {\n            points.emplace_back(\n                static_cast<long long>(random()\
    \ % 41) - 20,\n                static_cast<long long>(random() % 41) - 20\n  \
    \          );\n        }\n\n        auto expected = points;\n        std::sort(expected.begin(),\
    \ expected.end(), [&origin](\n            const Point& first,\n            const\
    \ Point& second\n        ) {\n            long double first_angle = argument(first,\
    \ origin);\n            long double second_angle = argument(second, origin);\n\
    \            if (first_angle != second_angle) return first_angle < second_angle;\n\
    \            return m1une::geometry::distance2(first, origin)\n              \
    \     < m1une::geometry::distance2(second, origin);\n        });\n\n        m1une::geometry::sort_by_angle(points,\
    \ origin);\n        assert(points == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<Point> points(n);\n    for (Point& point : points) std::cin\
    \ >> point.x >> point.y;\n    m1une::geometry::sort_by_angle(points);\n    for\
    \ (const Point& point : points) {\n        std::cout << point.x << ' ' << point.y\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  isVerificationFile: true
  path: verify/geometry/angle_sort.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 01:44:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/angle_sort.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/angle_sort.test.cpp
- /verify/verify/geometry/angle_sort.test.cpp.html
title: verify/geometry/angle_sort.test.cpp
---
