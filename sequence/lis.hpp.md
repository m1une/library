---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/sequence/sequence_algorithms.test.cpp
    title: verify/sequence/sequence_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"sequence/lis.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <iterator>\n#include <vector>\n\nnamespace m1une {\nnamespace sequence {\n\n\
    // Returns the zero-based indices of a longest increasing subsequence.\n// If\
    \ `strict` is false, equal adjacent values are also allowed.\ntemplate <typename\
    \ T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict = true) {\n  \
    \  const int n = int(a.size());\n    std::vector<T> tails;\n    std::vector<int>\
    \ tail_positions;\n    std::vector<int> predecessor(n, -1);\n    tails.reserve(n);\n\
    \    tail_positions.reserve(n);\n\n    for (int i = 0; i < n; ++i) {\n       \
    \ auto it = strict ? std::lower_bound(tails.begin(), tails.end(), a[i])\n    \
    \                     : std::upper_bound(tails.begin(), tails.end(), a[i]);\n\
    \        const int length = int(std::distance(tails.begin(), it));\n\n       \
    \ if (it == tails.end()) {\n            tails.push_back(a[i]);\n            tail_positions.push_back(i);\n\
    \        } else {\n            *it = a[i];\n            tail_positions[length]\
    \ = i;\n        }\n\n        if (length > 0) {\n            predecessor[i] = tail_positions[length\
    \ - 1];\n        }\n    }\n\n    if (tail_positions.empty()) return {};\n\n  \
    \  std::vector<int> result;\n    result.reserve(tail_positions.size());\n    int\
    \ current = tail_positions.back();\n    while (current != -1) {\n        result.push_back(current);\n\
    \        current = predecessor[current];\n    }\n    std::reverse(result.begin(),\
    \ result.end());\n    return result;\n}\n\n}  // namespace sequence\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_SEQUENCE_LIS_HPP\n#define M1UNE_SEQUENCE_LIS_HPP 1\n\n#include\
    \ <algorithm>\n#include <iterator>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ sequence {\n\n// Returns the zero-based indices of a longest increasing subsequence.\n\
    // If `strict` is false, equal adjacent values are also allowed.\ntemplate <typename\
    \ T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict = true) {\n  \
    \  const int n = int(a.size());\n    std::vector<T> tails;\n    std::vector<int>\
    \ tail_positions;\n    std::vector<int> predecessor(n, -1);\n    tails.reserve(n);\n\
    \    tail_positions.reserve(n);\n\n    for (int i = 0; i < n; ++i) {\n       \
    \ auto it = strict ? std::lower_bound(tails.begin(), tails.end(), a[i])\n    \
    \                     : std::upper_bound(tails.begin(), tails.end(), a[i]);\n\
    \        const int length = int(std::distance(tails.begin(), it));\n\n       \
    \ if (it == tails.end()) {\n            tails.push_back(a[i]);\n            tail_positions.push_back(i);\n\
    \        } else {\n            *it = a[i];\n            tail_positions[length]\
    \ = i;\n        }\n\n        if (length > 0) {\n            predecessor[i] = tail_positions[length\
    \ - 1];\n        }\n    }\n\n    if (tail_positions.empty()) return {};\n\n  \
    \  std::vector<int> result;\n    result.reserve(tail_positions.size());\n    int\
    \ current = tail_positions.back();\n    while (current != -1) {\n        result.push_back(current);\n\
    \        current = predecessor[current];\n    }\n    std::reverse(result.begin(),\
    \ result.end());\n    return result;\n}\n\n}  // namespace sequence\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_SEQUENCE_LIS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: sequence/lis.hpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/sequence/sequence_algorithms.test.cpp
documentation_of: sequence/lis.hpp
layout: document
title: Longest Increasing Subsequence (LIS)
---

## Overview

Returns the zero-based indices of a longest increasing subsequence. The indices
can be used to recover the values or to align the result with parallel arrays.

The implementation uses a tails array and predecessor links. It uses
`std::lower_bound` for a strict subsequence and `std::upper_bound` for a
non-decreasing subsequence.

## Template Parameters

* `T`: Element type. Values must be comparable using `<`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> lis(const std::vector<T>& a, bool strict = true)` | Returns the indices of the LIS. If `strict` is `true`, finds a strictly increasing sequence. If `false`, allows adjacent elements in the sequence to be equal (non-decreasing). | $O(N \log N)$ time, $O(N)$ space |

## Example

```cpp
#include "sequence/lis.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    const std::vector<int> lis_indices = m1une::sequence::lis(a);

    std::cout << "LIS length: " << lis_indices.size() << "\n"; // Output: 4

    std::cout << "Indices: ";
    for (int idx : lis_indices) std::cout << idx << " ";
    std::cout << "\n";

    std::cout << "Values: ";
    for (int idx : lis_indices) std::cout << a[idx] << " ";
    std::cout << "\n";

    const std::vector<int> non_decreasing = m1une::sequence::lis(a, false);
    std::cout << "Non-decreasing length: " << non_decreasing.size() << "\n";

    return 0;
}
```
