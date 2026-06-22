---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  - icon: ':heavy_check_mark:'
    path: optimization/li_chao_tree.hpp
    title: Li Chao Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/convex_hull_trick.test.cpp
    title: verify/optimization/convex_hull_trick.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/li_chao_tree.test.cpp
    title: verify/optimization/li_chao_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/project_selection.test.cpp
    title: verify/optimization/project_selection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/simplex.test.cpp
    title: verify/optimization/simplex.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/slope_trick.test.cpp
    title: verify/optimization/slope_trick.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"optimization/convex_hull_trick.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstddef>\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace optimization {\n\nenum class\
    \ LineOptimization {\n    Minimize,\n    Maximize,\n};\n\ntemplate <std::signed_integral\
    \ T>\nusing line_wide_type = __int128_t;\n\ntemplate <std::signed_integral T>\n\
    struct LinearFunction {\n    using value_type = line_wide_type<T>;\n\n    value_type\
    \ slope;\n    value_type intercept;\n\n    constexpr LinearFunction() : slope(0),\
    \ intercept(0) {}\n\n    constexpr LinearFunction(T slope_value, T intercept_value)\
    \ : slope(slope_value), intercept(intercept_value) {}\n\n    constexpr value_type\
    \ operator()(T x) const {\n        return slope * value_type(x) + intercept;\n\
    \    }\n};\n\n// Convex hull trick for lines inserted in nondecreasing slope order.\n\
    template <std::signed_integral T, LineOptimization Objective = LineOptimization::Minimize>\n\
    struct ConvexHullTrick {\n    using Line = LinearFunction<T>;\n    using value_type\
    \ = typename Line::value_type;\n\n   private:\n    std::vector<Line> _lines;\n\
    \n    static bool better(value_type first, value_type second) {\n        if constexpr\
    \ (Objective == LineOptimization::Minimize) {\n            return first < second;\n\
    \        } else {\n            return second < first;\n        }\n    }\n\n  \
    \  static bool redundant(const Line& first, const Line& middle, const Line& last)\
    \ {\n        value_type left = (first.intercept - middle.intercept) * (last.slope\
    \ - middle.slope);\n        value_type right = (middle.intercept - last.intercept)\
    \ * (middle.slope - first.slope);\n        if constexpr (Objective == LineOptimization::Minimize)\
    \ {\n            return left <= right;\n        } else {\n            return right\
    \ <= left;\n        }\n    }\n\n   public:\n    ConvexHullTrick() = default;\n\
    \n    int size() const {\n        return int(_lines.size());\n    }\n\n    bool\
    \ empty() const {\n        return _lines.empty();\n    }\n\n    const std::vector<Line>&\
    \ lines() const {\n        return _lines;\n    }\n\n    void reserve(std::size_t\
    \ line_capacity) {\n        _lines.reserve(line_capacity);\n    }\n\n    void\
    \ clear() {\n        _lines.clear();\n    }\n\n    // Slopes must be inserted\
    \ in nondecreasing order.\n    void add_line(T slope, T intercept) {\n       \
    \ Line line(slope, intercept);\n        if (!_lines.empty()) {\n            assert(_lines.back().slope\
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
    \n}  // namespace optimization\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP\n#define M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <optional>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace optimization\
    \ {\n\nenum class LineOptimization {\n    Minimize,\n    Maximize,\n};\n\ntemplate\
    \ <std::signed_integral T>\nusing line_wide_type = __int128_t;\n\ntemplate <std::signed_integral\
    \ T>\nstruct LinearFunction {\n    using value_type = line_wide_type<T>;\n\n \
    \   value_type slope;\n    value_type intercept;\n\n    constexpr LinearFunction()\
    \ : slope(0), intercept(0) {}\n\n    constexpr LinearFunction(T slope_value, T\
    \ intercept_value) : slope(slope_value), intercept(intercept_value) {}\n\n   \
    \ constexpr value_type operator()(T x) const {\n        return slope * value_type(x)\
    \ + intercept;\n    }\n};\n\n// Convex hull trick for lines inserted in nondecreasing\
    \ slope order.\ntemplate <std::signed_integral T, LineOptimization Objective =\
    \ LineOptimization::Minimize>\nstruct ConvexHullTrick {\n    using Line = LinearFunction<T>;\n\
    \    using value_type = typename Line::value_type;\n\n   private:\n    std::vector<Line>\
    \ _lines;\n\n    static bool better(value_type first, value_type second) {\n \
    \       if constexpr (Objective == LineOptimization::Minimize) {\n           \
    \ return first < second;\n        } else {\n            return second < first;\n\
    \        }\n    }\n\n    static bool redundant(const Line& first, const Line&\
    \ middle, const Line& last) {\n        value_type left = (first.intercept - middle.intercept)\
    \ * (last.slope - middle.slope);\n        value_type right = (middle.intercept\
    \ - last.intercept) * (middle.slope - first.slope);\n        if constexpr (Objective\
    \ == LineOptimization::Minimize) {\n            return left <= right;\n      \
    \  } else {\n            return right <= left;\n        }\n    }\n\n   public:\n\
    \    ConvexHullTrick() = default;\n\n    int size() const {\n        return int(_lines.size());\n\
    \    }\n\n    bool empty() const {\n        return _lines.empty();\n    }\n\n\
    \    const std::vector<Line>& lines() const {\n        return _lines;\n    }\n\
    \n    void reserve(std::size_t line_capacity) {\n        _lines.reserve(line_capacity);\n\
    \    }\n\n    void clear() {\n        _lines.clear();\n    }\n\n    // Slopes\
    \ must be inserted in nondecreasing order.\n    void add_line(T slope, T intercept)\
    \ {\n        Line line(slope, intercept);\n        if (!_lines.empty()) {\n  \
    \          assert(_lines.back().slope <= line.slope);\n        }\n\n        if\
    \ (!_lines.empty() && _lines.back().slope == line.slope) {\n            if (!better(line.intercept,\
    \ _lines.back().intercept)) return;\n            _lines.pop_back();\n        }\n\
    \n        while (_lines.size() >= 2 && redundant(_lines[_lines.size() - 2], _lines.back(),\
    \ line)) {\n            _lines.pop_back();\n        }\n        _lines.push_back(line);\n\
    \    }\n\n    std::optional<value_type> try_query(T x) const {\n        if (_lines.empty())\
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
    \n}  // namespace optimization\n}  // namespace m1une\n\n#endif  // M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: optimization/convex_hull_trick.hpp
  requiredBy:
  - optimization/all.hpp
  - optimization/li_chao_tree.hpp
  timestamp: '2026-06-23 02:47:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/slope_trick.test.cpp
  - verify/optimization/li_chao_tree.test.cpp
  - verify/optimization/convex_hull_trick.test.cpp
  - verify/optimization/simplex.test.cpp
documentation_of: optimization/convex_hull_trick.hpp
layout: document
title: Convex Hull Trick
---

## Overview

`ConvexHullTrick<T, Objective>` maintains linear functions

$$
f(x)=ax+b
$$

and answers minimum or maximum queries. Slopes must be inserted in
nondecreasing order, but query coordinates may arrive in any order.

The structure removes redundant lines as they are inserted and binary-searches
the remaining hull.

## Types

```cpp
enum class LineOptimization {
    Minimize,
    Maximize,
};
```

The convenient aliases are:

* `MinConvexHullTrick<T>`
* `MaxConvexHullTrick<T>`

`T` must be a signed integral type. Coefficients and query coordinates use `T`.
Evaluation and hull cross products use `line_wide_type<T>`, which is
`__int128_t`.

All intermediate products used to remove lines must fit the widened type.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `add_line(slope, intercept)` | Adds a line. Slopes must be nondecreasing. | Amortized $O(1)$ |
| `query(x)` | Returns the optimum at `x`; requires a nonempty hull. | $O(\log N)$ |
| `try_query(x)` | Returns the optimum, or `nullopt` when empty. | $O(\log N)$ |
| `lines()` | Returns the remaining hull lines. | $O(1)$ |
| `size()`, `empty()` | Return hull size and emptiness. | $O(1)$ |
| `reserve(capacity)` | Reserves line storage. | $O(N)$ |
| `clear()` | Removes every line. | $O(N)$ |

For equal slopes, only the better intercept is retained.

## Example

```cpp
#include "optimization/convex_hull_trick.hpp"

#include <iostream>

int main() {
    m1une::optimization::MinConvexHullTrick<long long> cht;
    cht.add_line(-2, 5);
    cht.add_line(0, 1);
    cht.add_line(3, -4);

    long long answer = static_cast<long long>(cht.query(2));
    std::cout << answer << "\n";
}
```
