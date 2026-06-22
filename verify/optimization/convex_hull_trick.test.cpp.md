---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/convex_hull_trick.hpp
    title: Convex Hull Trick
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
  bundledCode: "#line 1 \"verify/optimization/convex_hull_trick.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"optimization/convex_hull_trick.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <optional>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace optimization {\n\nenum class LineOptimization {\n    Minimize,\n   \
    \ Maximize,\n};\n\ntemplate <std::signed_integral T>\nusing line_wide_type = __int128_t;\n\
    \ntemplate <std::signed_integral T>\nstruct LinearFunction {\n    using value_type\
    \ = line_wide_type<T>;\n\n    value_type slope;\n    value_type intercept;\n\n\
    \    constexpr LinearFunction() : slope(0), intercept(0) {}\n\n    constexpr LinearFunction(T\
    \ slope_value, T intercept_value) : slope(slope_value), intercept(intercept_value)\
    \ {}\n\n    constexpr value_type operator()(T x) const {\n        return slope\
    \ * value_type(x) + intercept;\n    }\n};\n\n// Convex hull trick for lines inserted\
    \ in nondecreasing slope order.\ntemplate <std::signed_integral T, LineOptimization\
    \ Objective = LineOptimization::Minimize>\nstruct ConvexHullTrick {\n    using\
    \ Line = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\
    \n   private:\n    std::vector<Line> _lines;\n\n    static bool better(value_type\
    \ first, value_type second) {\n        if constexpr (Objective == LineOptimization::Minimize)\
    \ {\n            return first < second;\n        } else {\n            return\
    \ second < first;\n        }\n    }\n\n    static bool redundant(const Line& first,\
    \ const Line& middle, const Line& last) {\n        value_type left = (first.intercept\
    \ - middle.intercept) * (last.slope - middle.slope);\n        value_type right\
    \ = (middle.intercept - last.intercept) * (middle.slope - first.slope);\n    \
    \    if constexpr (Objective == LineOptimization::Minimize) {\n            return\
    \ left <= right;\n        } else {\n            return right <= left;\n      \
    \  }\n    }\n\n   public:\n    ConvexHullTrick() = default;\n\n    int size()\
    \ const {\n        return int(_lines.size());\n    }\n\n    bool empty() const\
    \ {\n        return _lines.empty();\n    }\n\n    const std::vector<Line>& lines()\
    \ const {\n        return _lines;\n    }\n\n    void reserve(std::size_t line_capacity)\
    \ {\n        _lines.reserve(line_capacity);\n    }\n\n    void clear() {\n   \
    \     _lines.clear();\n    }\n\n    // Slopes must be inserted in nondecreasing\
    \ order.\n    void add_line(T slope, T intercept) {\n        Line line(slope,\
    \ intercept);\n        if (!_lines.empty()) {\n            assert(_lines.back().slope\
    \ <= line.slope);\n        }\n\n        if (!_lines.empty() && _lines.back().slope\
    \ == line.slope) {\n            if (!better(line.intercept, _lines.back().intercept))\
    \ return;\n            _lines.pop_back();\n        }\n\n        while (_lines.size()\
    \ >= 2 && redundant(_lines[_lines.size() - 2], _lines.back(), line)) {\n     \
    \       _lines.pop_back();\n        }\n        _lines.push_back(line);\n    }\n\
    \n    std::optional<value_type> try_query(T x) const {\n        if (_lines.empty())\
    \ return std::nullopt;\n        int low = 0;\n        int high = int(_lines.size())\
    \ - 1;\n        while (low < high) {\n            int middle = low + (high - low)\
    \ / 2;\n            value_type first = _lines[middle](x);\n            value_type\
    \ second = _lines[middle + 1](x);\n            if (better(first, second) || first\
    \ == second) {\n                high = middle;\n            } else {\n       \
    \         low = middle + 1;\n            }\n        }\n        return _lines[low](x);\n\
    \    }\n\n    value_type query(T x) const {\n        assert(!empty());\n     \
    \   return *try_query(x);\n    }\n};\n\ntemplate <std::signed_integral T>\nusing\
    \ MinConvexHullTrick = ConvexHullTrick<T, LineOptimization::Minimize>;\n\ntemplate\
    \ <std::signed_integral T>\nusing MaxConvexHullTrick = ConvexHullTrick<T, LineOptimization::Maximize>;\n\
    \n}  // namespace optimization\n}  // namespace m1une\n\n\n#line 4 \"verify/optimization/convex_hull_trick.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/optimization/convex_hull_trick.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <limits>\n#line 11 \"verify/optimization/convex_hull_trick.test.cpp\"\
    \n\nnamespace {\n\nstruct Line {\n    long long slope;\n    long long intercept;\n\
    };\n\ntemplate <m1une::optimization::LineOptimization Objective>\nvoid check(const\
    \ std::vector<Line>& lines) {\n    m1une::optimization::ConvexHullTrick<long long,\
    \ Objective> cht;\n    for (const Line& line : lines) {\n        cht.add_line(line.slope,\
    \ line.intercept);\n    }\n\n    for (long long x = -100; x <= 100; ++x) {\n \
    \       __int128_t expected;\n        if constexpr (\n            Objective ==\
    \ m1une::optimization::LineOptimization::Minimize\n        ) {\n            expected\
    \ = std::numeric_limits<__int128_t>::max();\n        } else {\n            expected\
    \ = std::numeric_limits<__int128_t>::min();\n        }\n        for (const Line&\
    \ line : lines) {\n            __int128_t value =\n                __int128_t(line.slope)\
    \ * x + line.intercept;\n            if constexpr (\n                Objective\
    \ == m1une::optimization::LineOptimization::Minimize\n            ) {\n      \
    \          expected = std::min(expected, value);\n            } else {\n     \
    \           expected = std::max(expected, value);\n            }\n        }\n\
    \        assert(cht.query(x) == expected);\n    }\n}\n\nvoid test_fixed() {\n\
    \    m1une::optimization::MinConvexHullTrick<long long> empty;\n    assert(!empty.try_query(0).has_value());\n\
    \n    std::vector<Line> lines;\n    lines.push_back(Line{-3, 4});\n    lines.push_back(Line{-1,\
    \ 10});\n    lines.push_back(Line{-1, -5});\n    lines.push_back(Line{0, 2});\n\
    \    lines.push_back(Line{4, -7});\n    check<m1une::optimization::LineOptimization::Minimize>(lines);\n\
    \    check<m1une::optimization::LineOptimization::Maximize>(lines);\n}\n\nvoid\
    \ test_randomized() {\n    std::uint64_t state = 1009;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ int count = 1 + int(random() % 40);\n        std::vector<Line> lines;\n    \
    \    long long slope = -50;\n        for (int index = 0; index < count; ++index)\
    \ {\n            slope += int(random() % 4);\n            lines.push_back(Line{\n\
    \                slope,\n                static_cast<long long>(random() % 201)\
    \ - 100,\n            });\n        }\n        check<m1une::optimization::LineOptimization::Minimize>(lines);\n\
    \        check<m1une::optimization::LineOptimization::Maximize>(lines);\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../optimization/convex_hull_trick.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \nnamespace {\n\nstruct Line {\n    long long slope;\n    long long intercept;\n\
    };\n\ntemplate <m1une::optimization::LineOptimization Objective>\nvoid check(const\
    \ std::vector<Line>& lines) {\n    m1une::optimization::ConvexHullTrick<long long,\
    \ Objective> cht;\n    for (const Line& line : lines) {\n        cht.add_line(line.slope,\
    \ line.intercept);\n    }\n\n    for (long long x = -100; x <= 100; ++x) {\n \
    \       __int128_t expected;\n        if constexpr (\n            Objective ==\
    \ m1une::optimization::LineOptimization::Minimize\n        ) {\n            expected\
    \ = std::numeric_limits<__int128_t>::max();\n        } else {\n            expected\
    \ = std::numeric_limits<__int128_t>::min();\n        }\n        for (const Line&\
    \ line : lines) {\n            __int128_t value =\n                __int128_t(line.slope)\
    \ * x + line.intercept;\n            if constexpr (\n                Objective\
    \ == m1une::optimization::LineOptimization::Minimize\n            ) {\n      \
    \          expected = std::min(expected, value);\n            } else {\n     \
    \           expected = std::max(expected, value);\n            }\n        }\n\
    \        assert(cht.query(x) == expected);\n    }\n}\n\nvoid test_fixed() {\n\
    \    m1une::optimization::MinConvexHullTrick<long long> empty;\n    assert(!empty.try_query(0).has_value());\n\
    \n    std::vector<Line> lines;\n    lines.push_back(Line{-3, 4});\n    lines.push_back(Line{-1,\
    \ 10});\n    lines.push_back(Line{-1, -5});\n    lines.push_back(Line{0, 2});\n\
    \    lines.push_back(Line{4, -7});\n    check<m1une::optimization::LineOptimization::Minimize>(lines);\n\
    \    check<m1une::optimization::LineOptimization::Maximize>(lines);\n}\n\nvoid\
    \ test_randomized() {\n    std::uint64_t state = 1009;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ int count = 1 + int(random() % 40);\n        std::vector<Line> lines;\n    \
    \    long long slope = -50;\n        for (int index = 0; index < count; ++index)\
    \ {\n            slope += int(random() % 4);\n            lines.push_back(Line{\n\
    \                slope,\n                static_cast<long long>(random() % 201)\
    \ - 100,\n            });\n        }\n        check<m1une::optimization::LineOptimization::Minimize>(lines);\n\
    \        check<m1une::optimization::LineOptimization::Maximize>(lines);\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - optimization/convex_hull_trick.hpp
  isVerificationFile: true
  path: verify/optimization/convex_hull_trick.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:47:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/convex_hull_trick.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/convex_hull_trick.test.cpp
- /verify/verify/optimization/convex_hull_trick.test.cpp.html
title: verify/optimization/convex_hull_trick.test.cpp
---
