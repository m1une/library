---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/larsch.hpp\"\n\n\n\n#include <cassert>\n#include <functional>\n\
    #include <memory>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nclass Larsch {\n\
    \    struct ReduceColumn;\n\n    struct ReduceRow {\n        int size;\n     \
    \   std::function<T(int, int)> value;\n        int current_row = 0;\n        int\
    \ boundary = 0;\n        std::unique_ptr<ReduceColumn> recursive;\n\n        explicit\
    \ ReduceRow(int size_) : size(size_) {\n            if (size / 2 != 0) recursive\
    \ = std::make_unique<ReduceColumn>(size / 2);\n        }\n\n        void set_value(std::function<T(int,\
    \ int)> value_) {\n            value = std::move(value_);\n            if (recursive)\
    \ {\n                recursive->set_value(\n                    [&](int row, int\
    \ column) { return value(row * 2 + 1, column); });\n            }\n        }\n\
    \n        int next_argmin() {\n            int row = current_row++;\n        \
    \    if (row % 2 == 0) {\n                int previous = boundary;\n         \
    \       int next = row + 1 == size ? size - 1 : recursive->next_argmin();\n  \
    \              boundary = next;\n                int best = previous;\n      \
    \          for (int column = previous + 1; column <= next; column++) {\n     \
    \               if (value(row, column) < value(row, best)) best = column;\n  \
    \              }\n                return best;\n            }\n            return\
    \ value(row, boundary) <= value(row, row) ? boundary : row;\n        }\n    };\n\
    \n    struct ReduceColumn {\n        int size;\n        std::function<T(int, int)>\
    \ value;\n        int current_row = 0;\n        std::vector<int> columns;\n  \
    \      ReduceRow recursive;\n\n        explicit ReduceColumn(int size_) : size(size_),\
    \ recursive(size_) {}\n\n        void set_value(std::function<T(int, int)> value_)\
    \ {\n            value = std::move(value_);\n            recursive.set_value(\n\
    \                [&](int row, int column) { return value(row, columns[column]);\
    \ });\n        }\n\n        int next_argmin() {\n            int row = current_row++;\n\
    \            int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row\
    \ * 2;\n            for (int column = first; column <= last; column++) {\n   \
    \             while (int(columns.size()) != row &&\n                       value(int(columns.size())\
    \ - 1, columns.back()) >\n                           value(int(columns.size())\
    \ - 1, column)) {\n                    columns.pop_back();\n                }\n\
    \                if (int(columns.size()) != size) columns.push_back(column);\n\
    \            }\n            return columns[recursive.next_argmin()];\n       \
    \ }\n    };\n\n    int _size;\n    int _processed = 0;\n    std::unique_ptr<ReduceRow>\
    \ _base;\n\n   public:\n    template <class Value>\n    explicit Larsch(int size,\
    \ Value value)\n        : _size(size), _base(std::make_unique<ReduceRow>(size))\
    \ {\n        assert(size >= 0);\n        _base->set_value(std::function<T(int,\
    \ int)>(std::move(value)));\n    }\n\n    int size() const {\n        return _size;\n\
    \    }\n\n    int processed_rows() const {\n        return _processed;\n    }\n\
    \n    bool finished() const {\n        return _processed == _size;\n    }\n\n\
    \    int next_argmin() {\n        assert(!finished());\n        _processed++;\n\
    \        return _base->next_argmin();\n    }\n};\n\ntemplate <class T>\nstruct\
    \ LarschShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\ntemplate <class Cost>\nauto larsch_shortest_path(int vertex_count,\
    \ Cost cost)\n    -> LarschShortestPathResult<\n        std::decay_t<std::invoke_result_t<Cost,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;\n\
    \    assert(vertex_count >= 0);\n\n    LarschShortestPathResult<T> result;\n \
    \   result.distance.assign(vertex_count, T());\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count <= 1) return result;\n\n    Larsch<T> optimizer(vertex_count\
    \ - 1, [&](int row, int column) {\n        return result.distance[column] + cost(column,\
    \ row + 1);\n    });\n    for (int vertex = 1; vertex < vertex_count; vertex++)\
    \ {\n        int parent = optimizer.next_argmin();\n        result.parent[vertex]\
    \ = parent;\n        result.distance[vertex] = result.distance[parent] + cost(parent,\
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MONGE_LARSCH_HPP\n#define M1UNE_MONGE_LARSCH_HPP 1\n\n#include\
    \ <cassert>\n#include <functional>\n#include <memory>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace monge {\n\
    \ntemplate <class T>\nclass Larsch {\n    struct ReduceColumn;\n\n    struct ReduceRow\
    \ {\n        int size;\n        std::function<T(int, int)> value;\n        int\
    \ current_row = 0;\n        int boundary = 0;\n        std::unique_ptr<ReduceColumn>\
    \ recursive;\n\n        explicit ReduceRow(int size_) : size(size_) {\n      \
    \      if (size / 2 != 0) recursive = std::make_unique<ReduceColumn>(size / 2);\n\
    \        }\n\n        void set_value(std::function<T(int, int)> value_) {\n  \
    \          value = std::move(value_);\n            if (recursive) {\n        \
    \        recursive->set_value(\n                    [&](int row, int column) {\
    \ return value(row * 2 + 1, column); });\n            }\n        }\n\n       \
    \ int next_argmin() {\n            int row = current_row++;\n            if (row\
    \ % 2 == 0) {\n                int previous = boundary;\n                int next\
    \ = row + 1 == size ? size - 1 : recursive->next_argmin();\n                boundary\
    \ = next;\n                int best = previous;\n                for (int column\
    \ = previous + 1; column <= next; column++) {\n                    if (value(row,\
    \ column) < value(row, best)) best = column;\n                }\n            \
    \    return best;\n            }\n            return value(row, boundary) <= value(row,\
    \ row) ? boundary : row;\n        }\n    };\n\n    struct ReduceColumn {\n   \
    \     int size;\n        std::function<T(int, int)> value;\n        int current_row\
    \ = 0;\n        std::vector<int> columns;\n        ReduceRow recursive;\n\n  \
    \      explicit ReduceColumn(int size_) : size(size_), recursive(size_) {}\n\n\
    \        void set_value(std::function<T(int, int)> value_) {\n            value\
    \ = std::move(value_);\n            recursive.set_value(\n                [&](int\
    \ row, int column) { return value(row, columns[column]); });\n        }\n\n  \
    \      int next_argmin() {\n            int row = current_row++;\n           \
    \ int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row * 2;\n \
    \           for (int column = first; column <= last; column++) {\n           \
    \     while (int(columns.size()) != row &&\n                       value(int(columns.size())\
    \ - 1, columns.back()) >\n                           value(int(columns.size())\
    \ - 1, column)) {\n                    columns.pop_back();\n                }\n\
    \                if (int(columns.size()) != size) columns.push_back(column);\n\
    \            }\n            return columns[recursive.next_argmin()];\n       \
    \ }\n    };\n\n    int _size;\n    int _processed = 0;\n    std::unique_ptr<ReduceRow>\
    \ _base;\n\n   public:\n    template <class Value>\n    explicit Larsch(int size,\
    \ Value value)\n        : _size(size), _base(std::make_unique<ReduceRow>(size))\
    \ {\n        assert(size >= 0);\n        _base->set_value(std::function<T(int,\
    \ int)>(std::move(value)));\n    }\n\n    int size() const {\n        return _size;\n\
    \    }\n\n    int processed_rows() const {\n        return _processed;\n    }\n\
    \n    bool finished() const {\n        return _processed == _size;\n    }\n\n\
    \    int next_argmin() {\n        assert(!finished());\n        _processed++;\n\
    \        return _base->next_argmin();\n    }\n};\n\ntemplate <class T>\nstruct\
    \ LarschShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\ntemplate <class Cost>\nauto larsch_shortest_path(int vertex_count,\
    \ Cost cost)\n    -> LarschShortestPathResult<\n        std::decay_t<std::invoke_result_t<Cost,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;\n\
    \    assert(vertex_count >= 0);\n\n    LarschShortestPathResult<T> result;\n \
    \   result.distance.assign(vertex_count, T());\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count <= 1) return result;\n\n    Larsch<T> optimizer(vertex_count\
    \ - 1, [&](int row, int column) {\n        return result.distance[column] + cost(column,\
    \ row + 1);\n    });\n    for (int vertex = 1; vertex < vertex_count; vertex++)\
    \ {\n        int parent = optimizer.next_argmin();\n        result.parent[vertex]\
    \ = parent;\n        result.distance[vertex] = result.distance[parent] + cost(parent,\
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONGE_LARSCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/larsch.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/larsch.hpp
layout: document
title: LARSCH
---

## Overview

LARSCH finds row minima of an implicit lower-triangular totally monotone matrix
online. For row `i`, only columns `0` through `i` are candidates.

Unlike ordinary SMAWK, rows are produced in increasing order. Matrix entries in
later columns may therefore depend on answers already computed for earlier
rows. This supports dynamic programs such as

$$
dp[i] = \min_{0 \le j < i}\left(dp[j] + cost(j,i)\right)
$$

in linear time when the resulting triangular transition matrix is totally
monotone.

The algorithm is due to Larmore and Schieber:
[On-line dynamic programming with applications to the prediction of RNA
secondary structure](https://doi.org/10.1016/0196-6774(91)90016-R).

## Sequential Matrix Interface

```cpp
template <class T>
class Larsch;
```

Construct it with the number of rows and a callback:

```cpp
m1une::monge::Larsch<long long> optimizer(
    row_count,
    [&](int row, int column) {
        return matrix_value(row, column);
    });
```

Then call `next_argmin()` exactly once for each row, in order.

| Method | Meaning |
| --- | --- |
| `size()` | Total row count. |
| `processed_rows()` | Number of answers already returned. |
| `finished()` | Whether every row was processed. |
| `next_argmin()` | Returns the leftmost minimum column of the next row. |

When evaluating entry `(row, column)`, `column <= row`. More importantly,
entries using column `j + 1` are not accessed before row `j` has been answered.
This is the online guarantee that permits callbacks to depend on earlier DP
values.

## Monge DAG Shortest Paths

The convenience function

```cpp
template <class Cost>
auto larsch_shortest_path(int vertex_count, Cost cost);
```

solves the complete forward DAG recurrence:

$$
dist[0] = 0,\qquad
dist[i] = \min_{0 \le j < i}(dist[j] + cost(j,i)).
$$

It returns `LarschShortestPathResult<T>`:

| Member | Meaning |
| --- | --- |
| `distance[i]` | Minimum distance from vertex `0` to `i`. |
| `parent[i]` | Leftmost predecessor attaining that distance, or `-1` for vertex `0`. |

## Requirement

The lower-triangular matrix queried by the algorithm must be totally monotone
for minima. For the shortest-path helper, the matrix

$$
A(i,j) = dist[j] + cost(j,i+1),\qquad 0 \le j \le i
$$

must have that property. A Monge edge-cost function is the standard sufficient
condition.

The implementation does not verify total monotonicity.

## Complexity

Both interfaces use $O(N)$ callback evaluations, $O(N)$ time, and $O(N)$ memory,
assuming each callback evaluation takes $O(1)$.

## Example

```cpp
#include "monge/larsch.hpp"
#include <vector>

int main() {
    std::vector<long long> position = {0, 2, 5, 9, 14};
    auto result = m1une::monge::larsch_shortest_path(
        int(position.size()),
        [&](int from, int to) {
            long long distance = position[to] - position[from];
            return distance * distance + 3;
        });
}
```
