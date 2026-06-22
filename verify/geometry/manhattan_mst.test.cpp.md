---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_mst.hpp
    title: Manhattan Minimum Spanning Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/manhattanmst
    links:
    - https://judge.yosupo.jp/problem/manhattanmst
  bundledCode: "#line 1 \"verify/geometry/manhattan_mst.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/manhattanmst\"\n\n#line 1 \"geometry/manhattan_mst.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <limits>\n#include <map>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i]\
    \ is the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n\
    #line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
    \ && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
    \ wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;\n\
    \ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\n    constexpr\
    \ Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value) : x(x_value),\
    \ y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr Point(const\
    \ Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
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
    \ m1une\n\n\n#line 15 \"geometry/manhattan_mst.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <class T>\nstruct ManhattanMstEdge {\n    int from;\n\
    \    int to;\n    T cost;\n};\n\ntemplate <class T>\nstruct ManhattanMst {\n \
    \   T cost;\n    std::vector<ManhattanMstEdge<T>> edges;\n};\n\n// Returns O(n)\
    \ edges containing a Manhattan minimum spanning tree.\ntemplate <std::integral\
    \ T>\nstd::vector<ManhattanMstEdge<wide_type<T>>> manhattan_mst_edges(const std::vector<Point<T>>&\
    \ points) {\n    using W = wide_type<T>;\n    assert(points.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \    int n = int(points.size());\n    std::vector<Point<W>> transformed;\n   \
    \ transformed.reserve(points.size());\n    for (const auto& point : points) {\n\
    \        transformed.emplace_back(W(point.x), W(point.y));\n    }\n\n    std::vector<int>\
    \ order(n);\n    std::iota(order.begin(), order.end(), 0);\n    std::vector<ManhattanMstEdge<W>>\
    \ edges;\n    edges.reserve(std::size_t(4) * points.size());\n\n    for (int direction\
    \ = 0; direction < 4; direction++) {\n        std::sort(order.begin(), order.end(),\
    \ [&transformed](int i, int j) {\n            W first = transformed[i].x + transformed[i].y;\n\
    \            W second = transformed[j].x + transformed[j].y;\n            if (first\
    \ != second) return first < second;\n            if (transformed[i].x != transformed[j].x)\
    \ {\n                return transformed[i].x < transformed[j].x;\n           \
    \ }\n            return i < j;\n        });\n\n        std::map<W, int> sweep;\n\
    \        for (int i : order) {\n            auto it = sweep.lower_bound(-transformed[i].y);\n\
    \            while (it != sweep.end()) {\n                int j = it->second;\n\
    \                if (transformed[i].x - transformed[j].x < transformed[i].y -\
    \ transformed[j].y) {\n                    break;\n                }\n\n     \
    \           W dx = W(points[i].x) - W(points[j].x);\n                W dy = W(points[i].y)\
    \ - W(points[j].y);\n                if (dx < 0) dx = -dx;\n                if\
    \ (dy < 0) dy = -dy;\n                edges.push_back(ManhattanMstEdge<W>{i, j,\
    \ dx + dy});\n                it = sweep.erase(it);\n            }\n         \
    \   sweep[-transformed[i].y] = i;\n        }\n\n        for (auto& point : transformed)\
    \ {\n            if (direction & 1) {\n                point.x = -point.x;\n \
    \           } else {\n                std::swap(point.x, point.y);\n         \
    \   }\n        }\n    }\n    return edges;\n}\n\n// Returns a Manhattan minimum\
    \ spanning tree.\ntemplate <std::integral T>\nManhattanMst<wide_type<T>> manhattan_mst(const\
    \ std::vector<Point<T>>& points) {\n    using W = wide_type<T>;\n    auto candidates\
    \ = manhattan_mst_edges(points);\n    std::sort(candidates.begin(), candidates.end(),\
    \ [](const auto& a, const auto& b) { return a.cost < b.cost; });\n\n    m1une::ds::Dsu\
    \ dsu(int(points.size()));\n    ManhattanMst<W> result;\n    result.cost = W(0);\n\
    \    result.edges.reserve(points.empty() ? 0 : points.size() - 1);\n    for (const\
    \ auto& edge : candidates) {\n        if (dsu.same(edge.from, edge.to)) continue;\n\
    \        dsu.merge(edge.from, edge.to);\n        result.cost += edge.cost;\n \
    \       result.edges.push_back(edge);\n        if (result.edges.size() + 1 ==\
    \ points.size()) break;\n    }\n    assert(points.empty() || result.edges.size()\
    \ + 1 == points.size());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/geometry/manhattan_mst.test.cpp\"\n\
    \n#line 7 \"verify/geometry/manhattan_mst.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 11 \"verify/geometry/manhattan_mst.test.cpp\"\n\n#line 13\
    \ \"verify/geometry/manhattan_mst.test.cpp\"\n\nnamespace {\n\nusing Point = m1une::geometry::Point<long\
    \ long>;\nusing Wide = __int128_t;\n\nWide distance(const Point& a, const Point&\
    \ b) {\n    Wide dx = Wide(a.x) - Wide(b.x);\n    Wide dy = Wide(a.y) - Wide(b.y);\n\
    \    if (dx < 0) dx = -dx;\n    if (dy < 0) dy = -dy;\n    return dx + dy;\n}\n\
    \nWide brute_force_cost(const std::vector<Point>& points) {\n    struct Edge {\n\
    \        int from;\n        int to;\n        Wide cost;\n    };\n\n    std::vector<Edge>\
    \ edges;\n    for (int i = 0; i < int(points.size()); i++) {\n        for (int\
    \ j = 0; j < i; j++) {\n            edges.push_back(Edge{i, j, distance(points[i],\
    \ points[j])});\n        }\n    }\n    std::sort(edges.begin(), edges.end(), [](const\
    \ Edge& a, const Edge& b) {\n        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu\
    \ dsu(int(points.size()));\n    Wide result = 0;\n    for (const auto& edge :\
    \ edges) {\n        if (dsu.same(edge.from, edge.to)) continue;\n        dsu.merge(edge.from,\
    \ edge.to);\n        result += edge.cost;\n    }\n    return result;\n}\n\nvoid\
    \ check(const std::vector<Point>& points) {\n    auto candidates = m1une::geometry::manhattan_mst_edges(points);\n\
    \    assert(candidates.size() <= 4 * points.size());\n    for (const auto& edge\
    \ : candidates) {\n        assert(0 <= edge.from && edge.from < int(points.size()));\n\
    \        assert(0 <= edge.to && edge.to < int(points.size()));\n        assert(edge.cost\
    \ == distance(points[edge.from], points[edge.to]));\n    }\n\n    auto mst = m1une::geometry::manhattan_mst(points);\n\
    \    assert(mst.cost == brute_force_cost(points));\n    assert(mst.edges.size()\
    \ == (points.empty() ? 0 : points.size() - 1));\n\n    m1une::ds::Dsu dsu(int(points.size()));\n\
    \    Wide selected_cost = 0;\n    for (const auto& edge : mst.edges) {\n     \
    \   assert(!dsu.same(edge.from, edge.to));\n        dsu.merge(edge.from, edge.to);\n\
    \        selected_cost += edge.cost;\n    }\n    assert(selected_cost == mst.cost);\n\
    }\n\nvoid test_fixed() {\n    check({});\n    check({Point(4, -7)});\n    check({Point(0,\
    \ 0), Point(0, 0), Point(3, -2), Point(-5, 4)});\n    check({\n        Point(std::numeric_limits<long\
    \ long>::min(), 0),\n        Point(std::numeric_limits<long long>::max(), 0),\n\
    \    });\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 91;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 5000;\
    \ trial++) {\n        int n = int(random() % 15);\n        std::vector<Point>\
    \ points;\n        points.reserve(n);\n        for (int i = 0; i < n; i++) {\n\
    \            points.emplace_back(\n                static_cast<long long>(random()\
    \ % 31) - 15,\n                static_cast<long long>(random() % 31) - 15\n  \
    \          );\n        }\n        check(points);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<Point> points;\n    points.reserve(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        long long x, y;\n        std::cin >> x >> y;\n\
    \        points.emplace_back(x, y);\n    }\n\n    auto mst = m1une::geometry::manhattan_mst(points);\n\
    \    std::cout << static_cast<long long>(mst.cost) << '\\n';\n    for (const auto&\
    \ edge : mst.edges) {\n        std::cout << edge.from << ' ' << edge.to << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/manhattanmst\"\n\n#include\
    \ \"../../geometry/manhattan_mst.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#include \"../../ds/dsu/dsu.hpp\"\n\nnamespace {\n\nusing Point = m1une::geometry::Point<long\
    \ long>;\nusing Wide = __int128_t;\n\nWide distance(const Point& a, const Point&\
    \ b) {\n    Wide dx = Wide(a.x) - Wide(b.x);\n    Wide dy = Wide(a.y) - Wide(b.y);\n\
    \    if (dx < 0) dx = -dx;\n    if (dy < 0) dy = -dy;\n    return dx + dy;\n}\n\
    \nWide brute_force_cost(const std::vector<Point>& points) {\n    struct Edge {\n\
    \        int from;\n        int to;\n        Wide cost;\n    };\n\n    std::vector<Edge>\
    \ edges;\n    for (int i = 0; i < int(points.size()); i++) {\n        for (int\
    \ j = 0; j < i; j++) {\n            edges.push_back(Edge{i, j, distance(points[i],\
    \ points[j])});\n        }\n    }\n    std::sort(edges.begin(), edges.end(), [](const\
    \ Edge& a, const Edge& b) {\n        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu\
    \ dsu(int(points.size()));\n    Wide result = 0;\n    for (const auto& edge :\
    \ edges) {\n        if (dsu.same(edge.from, edge.to)) continue;\n        dsu.merge(edge.from,\
    \ edge.to);\n        result += edge.cost;\n    }\n    return result;\n}\n\nvoid\
    \ check(const std::vector<Point>& points) {\n    auto candidates = m1une::geometry::manhattan_mst_edges(points);\n\
    \    assert(candidates.size() <= 4 * points.size());\n    for (const auto& edge\
    \ : candidates) {\n        assert(0 <= edge.from && edge.from < int(points.size()));\n\
    \        assert(0 <= edge.to && edge.to < int(points.size()));\n        assert(edge.cost\
    \ == distance(points[edge.from], points[edge.to]));\n    }\n\n    auto mst = m1une::geometry::manhattan_mst(points);\n\
    \    assert(mst.cost == brute_force_cost(points));\n    assert(mst.edges.size()\
    \ == (points.empty() ? 0 : points.size() - 1));\n\n    m1une::ds::Dsu dsu(int(points.size()));\n\
    \    Wide selected_cost = 0;\n    for (const auto& edge : mst.edges) {\n     \
    \   assert(!dsu.same(edge.from, edge.to));\n        dsu.merge(edge.from, edge.to);\n\
    \        selected_cost += edge.cost;\n    }\n    assert(selected_cost == mst.cost);\n\
    }\n\nvoid test_fixed() {\n    check({});\n    check({Point(4, -7)});\n    check({Point(0,\
    \ 0), Point(0, 0), Point(3, -2), Point(-5, 4)});\n    check({\n        Point(std::numeric_limits<long\
    \ long>::min(), 0),\n        Point(std::numeric_limits<long long>::max(), 0),\n\
    \    });\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 91;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 5000;\
    \ trial++) {\n        int n = int(random() % 15);\n        std::vector<Point>\
    \ points;\n        points.reserve(n);\n        for (int i = 0; i < n; i++) {\n\
    \            points.emplace_back(\n                static_cast<long long>(random()\
    \ % 31) - 15,\n                static_cast<long long>(random() % 31) - 15\n  \
    \          );\n        }\n        check(points);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<Point> points;\n    points.reserve(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        long long x, y;\n        std::cin >> x >> y;\n\
    \        points.emplace_back(x, y);\n    }\n\n    auto mst = m1une::geometry::manhattan_mst(points);\n\
    \    std::cout << static_cast<long long>(mst.cost) << '\\n';\n    for (const auto&\
    \ edge : mst.edges) {\n        std::cout << edge.from << ' ' << edge.to << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - geometry/manhattan_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/point.hpp
  - ds/dsu/dsu.hpp
  isVerificationFile: true
  path: verify/geometry/manhattan_mst.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 01:30:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/manhattan_mst.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/manhattan_mst.test.cpp
- /verify/verify/geometry/manhattan_mst.test.cpp.html
title: verify/geometry/manhattan_mst.test.cpp
---
