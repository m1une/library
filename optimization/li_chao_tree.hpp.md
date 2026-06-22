---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/convex_hull_trick.hpp
    title: Convex Hull Trick
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"optimization/li_chao_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstddef>\n#include <limits>\n#include <numeric>\n\
    #include <optional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"optimization/convex_hull_trick.hpp\"\n\n\n\n#line 10 \"optimization/convex_hull_trick.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\nenum class LineOptimization\
    \ {\n    Minimize,\n    Maximize,\n};\n\ntemplate <std::signed_integral T>\nusing\
    \ line_wide_type = __int128_t;\n\ntemplate <std::signed_integral T>\nstruct LinearFunction\
    \ {\n    using value_type = line_wide_type<T>;\n\n    value_type slope;\n    value_type\
    \ intercept;\n\n    constexpr LinearFunction() : slope(0), intercept(0) {}\n\n\
    \    constexpr LinearFunction(T slope_value, T intercept_value) : slope(slope_value),\
    \ intercept(intercept_value) {}\n\n    constexpr value_type operator()(T x) const\
    \ {\n        return slope * value_type(x) + intercept;\n    }\n};\n\n// Convex\
    \ hull trick for lines inserted in nondecreasing slope order.\ntemplate <std::signed_integral\
    \ T, LineOptimization Objective = LineOptimization::Minimize>\nstruct ConvexHullTrick\
    \ {\n    using Line = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\
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
    \n}  // namespace optimization\n}  // namespace m1une\n\n\n#line 15 \"optimization/li_chao_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\n// Dynamic Li Chao tree over\
    \ an integral half-open coordinate domain.\ntemplate <std::signed_integral T,\
    \ LineOptimization Objective = LineOptimization::Minimize>\nstruct LiChaoTree\
    \ {\n    using Line = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\
    \n   private:\n    struct Node {\n        Line line;\n        bool has_line;\n\
    \        int left;\n        int right;\n\n        Node() : has_line(false), left(-1),\
    \ right(-1) {}\n\n        explicit Node(Line value) : line(std::move(value)),\
    \ has_line(true), left(-1), right(-1) {}\n    };\n\n    T _left;\n    T _right;\n\
    \    int _root;\n    std::vector<Node> _nodes;\n\n    static bool better(value_type\
    \ first, value_type second) {\n        if constexpr (Objective == LineOptimization::Minimize)\
    \ {\n            return first < second;\n        } else {\n            return\
    \ second < first;\n        }\n    }\n\n    int new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int new_node(Line line)\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(std::move(line));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_line_node(int node, T left, T right, Line line) {\n\
    \        if (node == -1) return new_node(std::move(line));\n        if (!_nodes[node].has_line)\
    \ {\n            _nodes[node].line = std::move(line);\n            _nodes[node].has_line\
    \ = true;\n            return node;\n        }\n\n        T middle = std::midpoint(left,\
    \ right);\n        bool left_better = better(line(left), _nodes[node].line(left));\n\
    \        bool middle_better = better(line(middle), _nodes[node].line(middle));\n\
    \        if (middle_better) std::swap(line, _nodes[node].line);\n        if (middle\
    \ == left) return node;\n\n        if (left_better != middle_better) {\n     \
    \       int child = add_line_node(_nodes[node].left, left, middle, std::move(line));\n\
    \            _nodes[node].left = child;\n        } else {\n            int child\
    \ = add_line_node(_nodes[node].right, middle, right, std::move(line));\n     \
    \       _nodes[node].right = child;\n        }\n        return node;\n    }\n\n\
    \    int add_segment_node(int node, T left, T right, T query_left, T query_right,\
    \ const Line& line) {\n        if (query_right <= left || right <= query_left)\
    \ return node;\n        if (query_left <= left && right <= query_right) {\n  \
    \          return add_line_node(node, left, right, line);\n        }\n       \
    \ if (node == -1) node = new_node();\n\n        T middle = std::midpoint(left,\
    \ right);\n        if (middle == left) return add_line_node(node, left, right,\
    \ line);\n        int left_child = add_segment_node(_nodes[node].left, left, middle,\
    \ query_left, query_right, line);\n        int right_child = add_segment_node(_nodes[node].right,\
    \ middle, right, query_left, query_right, line);\n        _nodes[node].left =\
    \ left_child;\n        _nodes[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    LiChaoTree() : _left(0), _right(0), _root(-1) {}\n\n\
    \    LiChaoTree(T left, T right) : _left(left), _right(right), _root(-1) {\n \
    \       assert(left <= right);\n    }\n\n    T left_bound() const {\n        return\
    \ _left;\n    }\n\n    T right_bound() const {\n        return _right;\n    }\n\
    \n    bool empty() const {\n        return _root == -1;\n    }\n\n    std::size_t\
    \ node_count() const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _root = -1;\n        _nodes.clear();\n    }\n\n    void add_line(T\
    \ slope, T intercept) {\n        assert(_left < _right);\n        _root = add_line_node(_root,\
    \ _left, _right, Line(slope, intercept));\n    }\n\n    void add_segment(T segment_left,\
    \ T segment_right, T slope, T intercept) {\n        assert(_left <= segment_left\
    \ && segment_left <= segment_right && segment_right <= _right);\n        if (segment_left\
    \ == segment_right) return;\n        _root = add_segment_node(_root, _left, _right,\
    \ segment_left, segment_right, Line(slope, intercept));\n    }\n\n    // Returns\
    \ nullopt when no inserted line covers x.\n    std::optional<value_type> query(T\
    \ x) const {\n        assert(_left <= x && x < _right);\n        std::optional<value_type>\
    \ result;\n        int node = _root;\n        T left = _left;\n        T right\
    \ = _right;\n        while (node != -1) {\n            if (_nodes[node].has_line)\
    \ {\n                value_type candidate = _nodes[node].line(x);\n          \
    \      if (!result || better(candidate, *result)) {\n                    result\
    \ = candidate;\n                }\n            }\n\n            T middle = std::midpoint(left,\
    \ right);\n            if (middle == left) break;\n            if (x < middle)\
    \ {\n                node = _nodes[node].left;\n                right = middle;\n\
    \            } else {\n                node = _nodes[node].right;\n          \
    \      left = middle;\n            }\n        }\n        return result;\n    }\n\
    \n    value_type get(T x) const {\n        std::optional<value_type> result =\
    \ query(x);\n        assert(result.has_value());\n        return result.value_or(value_type());\n\
    \    }\n};\n\ntemplate <std::signed_integral T>\nusing MinLiChaoTree = LiChaoTree<T,\
    \ LineOptimization::Minimize>;\n\ntemplate <std::signed_integral T>\nusing MaxLiChaoTree\
    \ = LiChaoTree<T, LineOptimization::Maximize>;\n\n}  // namespace optimization\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP\n#define M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <numeric>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"convex_hull_trick.hpp\"\n\nnamespace m1une {\n\
    namespace optimization {\n\n// Dynamic Li Chao tree over an integral half-open\
    \ coordinate domain.\ntemplate <std::signed_integral T, LineOptimization Objective\
    \ = LineOptimization::Minimize>\nstruct LiChaoTree {\n    using Line = LinearFunction<T>;\n\
    \    using value_type = typename Line::value_type;\n\n   private:\n    struct\
    \ Node {\n        Line line;\n        bool has_line;\n        int left;\n    \
    \    int right;\n\n        Node() : has_line(false), left(-1), right(-1) {}\n\n\
    \        explicit Node(Line value) : line(std::move(value)), has_line(true), left(-1),\
    \ right(-1) {}\n    };\n\n    T _left;\n    T _right;\n    int _root;\n    std::vector<Node>\
    \ _nodes;\n\n    static bool better(value_type first, value_type second) {\n \
    \       if constexpr (Objective == LineOptimization::Minimize) {\n           \
    \ return first < second;\n        } else {\n            return second < first;\n\
    \        }\n    }\n\n    int new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    int new_node(Line line) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(std::move(line));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_line_node(int node, T left, T right, Line line) {\n\
    \        if (node == -1) return new_node(std::move(line));\n        if (!_nodes[node].has_line)\
    \ {\n            _nodes[node].line = std::move(line);\n            _nodes[node].has_line\
    \ = true;\n            return node;\n        }\n\n        T middle = std::midpoint(left,\
    \ right);\n        bool left_better = better(line(left), _nodes[node].line(left));\n\
    \        bool middle_better = better(line(middle), _nodes[node].line(middle));\n\
    \        if (middle_better) std::swap(line, _nodes[node].line);\n        if (middle\
    \ == left) return node;\n\n        if (left_better != middle_better) {\n     \
    \       int child = add_line_node(_nodes[node].left, left, middle, std::move(line));\n\
    \            _nodes[node].left = child;\n        } else {\n            int child\
    \ = add_line_node(_nodes[node].right, middle, right, std::move(line));\n     \
    \       _nodes[node].right = child;\n        }\n        return node;\n    }\n\n\
    \    int add_segment_node(int node, T left, T right, T query_left, T query_right,\
    \ const Line& line) {\n        if (query_right <= left || right <= query_left)\
    \ return node;\n        if (query_left <= left && right <= query_right) {\n  \
    \          return add_line_node(node, left, right, line);\n        }\n       \
    \ if (node == -1) node = new_node();\n\n        T middle = std::midpoint(left,\
    \ right);\n        if (middle == left) return add_line_node(node, left, right,\
    \ line);\n        int left_child = add_segment_node(_nodes[node].left, left, middle,\
    \ query_left, query_right, line);\n        int right_child = add_segment_node(_nodes[node].right,\
    \ middle, right, query_left, query_right, line);\n        _nodes[node].left =\
    \ left_child;\n        _nodes[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    LiChaoTree() : _left(0), _right(0), _root(-1) {}\n\n\
    \    LiChaoTree(T left, T right) : _left(left), _right(right), _root(-1) {\n \
    \       assert(left <= right);\n    }\n\n    T left_bound() const {\n        return\
    \ _left;\n    }\n\n    T right_bound() const {\n        return _right;\n    }\n\
    \n    bool empty() const {\n        return _root == -1;\n    }\n\n    std::size_t\
    \ node_count() const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _root = -1;\n        _nodes.clear();\n    }\n\n    void add_line(T\
    \ slope, T intercept) {\n        assert(_left < _right);\n        _root = add_line_node(_root,\
    \ _left, _right, Line(slope, intercept));\n    }\n\n    void add_segment(T segment_left,\
    \ T segment_right, T slope, T intercept) {\n        assert(_left <= segment_left\
    \ && segment_left <= segment_right && segment_right <= _right);\n        if (segment_left\
    \ == segment_right) return;\n        _root = add_segment_node(_root, _left, _right,\
    \ segment_left, segment_right, Line(slope, intercept));\n    }\n\n    // Returns\
    \ nullopt when no inserted line covers x.\n    std::optional<value_type> query(T\
    \ x) const {\n        assert(_left <= x && x < _right);\n        std::optional<value_type>\
    \ result;\n        int node = _root;\n        T left = _left;\n        T right\
    \ = _right;\n        while (node != -1) {\n            if (_nodes[node].has_line)\
    \ {\n                value_type candidate = _nodes[node].line(x);\n          \
    \      if (!result || better(candidate, *result)) {\n                    result\
    \ = candidate;\n                }\n            }\n\n            T middle = std::midpoint(left,\
    \ right);\n            if (middle == left) break;\n            if (x < middle)\
    \ {\n                node = _nodes[node].left;\n                right = middle;\n\
    \            } else {\n                node = _nodes[node].right;\n          \
    \      left = middle;\n            }\n        }\n        return result;\n    }\n\
    \n    value_type get(T x) const {\n        std::optional<value_type> result =\
    \ query(x);\n        assert(result.has_value());\n        return result.value_or(value_type());\n\
    \    }\n};\n\ntemplate <std::signed_integral T>\nusing MinLiChaoTree = LiChaoTree<T,\
    \ LineOptimization::Minimize>;\n\ntemplate <std::signed_integral T>\nusing MaxLiChaoTree\
    \ = LiChaoTree<T, LineOptimization::Maximize>;\n\n}  // namespace optimization\n\
    }  // namespace m1une\n\n#endif  // M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP\n"
  dependsOn:
  - optimization/convex_hull_trick.hpp
  isVerificationFile: false
  path: optimization/li_chao_tree.hpp
  requiredBy:
  - optimization/all.hpp
  timestamp: '2026-06-23 02:47:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/slope_trick.test.cpp
  - verify/optimization/li_chao_tree.test.cpp
  - verify/optimization/simplex.test.cpp
documentation_of: optimization/li_chao_tree.hpp
layout: document
title: Li Chao Tree
---

## Overview

`LiChaoTree<T, Objective>` maintains linear functions over a fixed integral
coordinate domain. Unlike the monotone-slope convex hull trick, lines may be
inserted in any order.

It supports both lines over the complete domain and lines restricted to a
half-open coordinate segment.

## Construction

```cpp
LiChaoTree(T left, T right);
```

The coordinate domain is `[left, right)`. It is fixed at construction, but
nodes are allocated only where insertion visits, so a large integer domain is
practical.

The aliases `MinLiChaoTree<T>` and `MaxLiChaoTree<T>` select minimum and maximum
queries. `T` must be a signed integral type.

Evaluation uses the widened type described by `LinearFunction<T>` in
`convex_hull_trick.hpp`.

## Methods

Let $U$ be the number of integer coordinates in the domain.

| Method | Description | Complexity |
| --- | --- | --- |
| `add_line(slope, intercept)` | Adds a line over the complete domain. | $O(\log U)$ |
| `add_segment(l, r, slope, intercept)` | Adds a line only over `[l, r)`. | $O(\log^2 U)$ |
| `query(x)` | Returns the optimum at `x`, or `nullopt` if no line covers it. | $O(\log U)$ |
| `get(x)` | Returns the optimum and requires some line to cover `x`. | $O(\log U)$ |
| `left_bound()`, `right_bound()` | Return domain endpoints. | $O(1)$ |
| `node_count()` | Returns allocated node count. | $O(1)$ |
| `reserve(capacity)` | Reserves node storage. | $O(N)$ |
| `clear()` | Removes every line while retaining the domain. | $O(N)$ |

## Example

```cpp
#include "optimization/li_chao_tree.hpp"

#include <iostream>

int main() {
    m1une::optimization::MinLiChaoTree<long long> tree(-1000, 1001);
    tree.add_line(2, 3);
    tree.add_line(-1, 8);
    tree.add_segment(-10, 11, 0, -5);

    long long answer = static_cast<long long>(tree.get(4));
    std::cout << answer << "\n";
}
```
