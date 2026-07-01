---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/levenshtein_distance.test.cpp
    title: verify/string/levenshtein_distance.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/levenshtein_distance.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \nnamespace levenshtein_distance_detail {\n\ntemplate <class RowSequence, class\
    \ ColumnSequence>\nint solve(const RowSequence& rows, const ColumnSequence& columns)\
    \ {\n    int row_count = int(rows.size());\n    int column_count = int(columns.size());\n\
    \    std::vector<int> distance(column_count + 1);\n    for (int column = 0; column\
    \ <= column_count; column++) distance[column] = column;\n\n    for (int row =\
    \ 1; row <= row_count; row++) {\n        int diagonal = distance[0];\n       \
    \ distance[0] = row;\n        for (int column = 1; column <= column_count; column++)\
    \ {\n            int above = distance[column];\n            int substitution =\
    \ diagonal + (rows[row - 1] == columns[column - 1] ? 0 : 1);\n            distance[column]\
    \ =\n                std::min({above + 1, distance[column - 1] + 1, substitution});\n\
    \            diagonal = above;\n        }\n    }\n    return distance[column_count];\n\
    }\n\ntemplate <class RowSequence, class ColumnSequence>\nint solve_bounded(const\
    \ RowSequence& rows, const ColumnSequence& columns,\n                  int max_distance)\
    \ {\n    int row_count = int(rows.size());\n    int column_count = int(columns.size());\n\
    \    assert(column_count <= row_count);\n    if (row_count - column_count > max_distance)\
    \ return max_distance + 1;\n    if (max_distance >= row_count) return solve(rows,\
    \ columns);\n\n    int infinity = max_distance + 1;\n    int previous_left = 0;\n\
    \    int previous_right = std::min(column_count, max_distance);\n    std::vector<int>\
    \ previous(previous_right + 1);\n    for (int column = 0; column <= previous_right;\
    \ column++) previous[column] = column;\n    std::vector<int> current;\n\n    for\
    \ (int row = 1; row <= row_count; row++) {\n        int current_left = std::max(0,\
    \ row - max_distance);\n        int current_right = int(std::min<long long>(column_count,\n\
    \                                                    static_cast<long long>(row)\
    \ + max_distance));\n        current.assign(current_right - current_left + 1,\
    \ infinity);\n\n        for (int column = current_left; column <= current_right;\
    \ column++) {\n            int best = infinity;\n            if (previous_left\
    \ <= column && column <= previous_right) {\n                best = std::min(best,\
    \ previous[column - previous_left] + 1);\n            }\n            if (current_left\
    \ < column) {\n                best = std::min(best, current[column - current_left\
    \ - 1] + 1);\n            }\n            if (0 < column && previous_left <= column\
    \ - 1 && column - 1 <= previous_right) {\n                int substitution = previous[column\
    \ - 1 - previous_left] +\n                                   (rows[row - 1] ==\
    \ columns[column - 1] ? 0 : 1);\n                best = std::min(best, substitution);\n\
    \            }\n            current[column - current_left] = std::min(best, infinity);\n\
    \        }\n\n        previous.swap(current);\n        previous_left = current_left;\n\
    \        previous_right = current_right;\n    }\n    return previous[column_count\
    \ - previous_left];\n}\n\n}  // namespace levenshtein_distance_detail\n\n// Returns\
    \ the minimum number of insertions, deletions, and substitutions\n// needed to\
    \ transform first into second.\ntemplate <class Sequence1, class Sequence2>\n\
    int levenshtein_distance(const Sequence1& first, const Sequence2& second) {\n\
    \    if (first.size() < second.size()) {\n        return levenshtein_distance_detail::solve(second,\
    \ first);\n    }\n    return levenshtein_distance_detail::solve(first, second);\n\
    }\n\n// Returns the exact distance when it is at most max_distance, and\n// max_distance\
    \ + 1 otherwise.\ntemplate <class Sequence1, class Sequence2>\nint levenshtein_distance(const\
    \ Sequence1& first, const Sequence2& second,\n                         int max_distance)\
    \ {\n    assert(0 <= max_distance);\n    if (first.size() < second.size()) {\n\
    \        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);\n\
    \    }\n    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP\n#define M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace string {\n\nnamespace levenshtein_distance_detail {\n\ntemplate\
    \ <class RowSequence, class ColumnSequence>\nint solve(const RowSequence& rows,\
    \ const ColumnSequence& columns) {\n    int row_count = int(rows.size());\n  \
    \  int column_count = int(columns.size());\n    std::vector<int> distance(column_count\
    \ + 1);\n    for (int column = 0; column <= column_count; column++) distance[column]\
    \ = column;\n\n    for (int row = 1; row <= row_count; row++) {\n        int diagonal\
    \ = distance[0];\n        distance[0] = row;\n        for (int column = 1; column\
    \ <= column_count; column++) {\n            int above = distance[column];\n  \
    \          int substitution = diagonal + (rows[row - 1] == columns[column - 1]\
    \ ? 0 : 1);\n            distance[column] =\n                std::min({above +\
    \ 1, distance[column - 1] + 1, substitution});\n            diagonal = above;\n\
    \        }\n    }\n    return distance[column_count];\n}\n\ntemplate <class RowSequence,\
    \ class ColumnSequence>\nint solve_bounded(const RowSequence& rows, const ColumnSequence&\
    \ columns,\n                  int max_distance) {\n    int row_count = int(rows.size());\n\
    \    int column_count = int(columns.size());\n    assert(column_count <= row_count);\n\
    \    if (row_count - column_count > max_distance) return max_distance + 1;\n \
    \   if (max_distance >= row_count) return solve(rows, columns);\n\n    int infinity\
    \ = max_distance + 1;\n    int previous_left = 0;\n    int previous_right = std::min(column_count,\
    \ max_distance);\n    std::vector<int> previous(previous_right + 1);\n    for\
    \ (int column = 0; column <= previous_right; column++) previous[column] = column;\n\
    \    std::vector<int> current;\n\n    for (int row = 1; row <= row_count; row++)\
    \ {\n        int current_left = std::max(0, row - max_distance);\n        int\
    \ current_right = int(std::min<long long>(column_count,\n                    \
    \                                static_cast<long long>(row) + max_distance));\n\
    \        current.assign(current_right - current_left + 1, infinity);\n\n     \
    \   for (int column = current_left; column <= current_right; column++) {\n   \
    \         int best = infinity;\n            if (previous_left <= column && column\
    \ <= previous_right) {\n                best = std::min(best, previous[column\
    \ - previous_left] + 1);\n            }\n            if (current_left < column)\
    \ {\n                best = std::min(best, current[column - current_left - 1]\
    \ + 1);\n            }\n            if (0 < column && previous_left <= column\
    \ - 1 && column - 1 <= previous_right) {\n                int substitution = previous[column\
    \ - 1 - previous_left] +\n                                   (rows[row - 1] ==\
    \ columns[column - 1] ? 0 : 1);\n                best = std::min(best, substitution);\n\
    \            }\n            current[column - current_left] = std::min(best, infinity);\n\
    \        }\n\n        previous.swap(current);\n        previous_left = current_left;\n\
    \        previous_right = current_right;\n    }\n    return previous[column_count\
    \ - previous_left];\n}\n\n}  // namespace levenshtein_distance_detail\n\n// Returns\
    \ the minimum number of insertions, deletions, and substitutions\n// needed to\
    \ transform first into second.\ntemplate <class Sequence1, class Sequence2>\n\
    int levenshtein_distance(const Sequence1& first, const Sequence2& second) {\n\
    \    if (first.size() < second.size()) {\n        return levenshtein_distance_detail::solve(second,\
    \ first);\n    }\n    return levenshtein_distance_detail::solve(first, second);\n\
    }\n\n// Returns the exact distance when it is at most max_distance, and\n// max_distance\
    \ + 1 otherwise.\ntemplate <class Sequence1, class Sequence2>\nint levenshtein_distance(const\
    \ Sequence1& first, const Sequence2& second,\n                         int max_distance)\
    \ {\n    assert(0 <= max_distance);\n    if (first.size() < second.size()) {\n\
    \        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);\n\
    \    }\n    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/levenshtein_distance.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-01 21:56:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/levenshtein_distance.test.cpp
documentation_of: string/levenshtein_distance.hpp
layout: document
title: Levenshtein Distance
---

## Overview

`levenshtein_distance(first, second)` returns the minimum number of single-element
edits needed to transform one sequence into the other. Each insertion, deletion,
or substitution costs one.

The function works with indexable sequences such as `std::string` and
`std::vector<int>`. Both sequences must provide `size()` and equality-comparable
elements.

## Function

```cpp
template <class Sequence1, class Sequence2>
int levenshtein_distance(
    const Sequence1& first,
    const Sequence2& second);

template <class Sequence1, class Sequence2>
int levenshtein_distance(
    const Sequence1& first,
    const Sequence2& second,
    int max_distance);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `levenshtein_distance(first, second)` | Returns the unit-cost edit distance. | $O(NM)$ time and $O(\min(N,M))$ memory. |
| `levenshtein_distance(first, second, max_distance)` | Returns the distance if it is at most $K$; otherwise returns $K+1$. | $O((K+1)(N+M))$ time and $O(\min(N,M,K)+1)$ memory. |

Empty sequences are supported. In particular, the distance from an empty
sequence to a sequence of length $N$ is $N$.

Use the bounded overload when only distances up to `max_distance` matter, or
when the distance is known to be at most that value. It evaluates only the
width-$2K+1$ diagonal band that can contain an edit sequence of at most $K$
operations. `max_distance` must be nonnegative.

## Example

```cpp
#include "string/levenshtein_distance.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "kitten";
    std::string second = "sitting";

    std::cout << m1une::string::levenshtein_distance(first, second, 3) << "\n";
    // 3: substitute k -> s, substitute e -> i, then insert g.
}
```
