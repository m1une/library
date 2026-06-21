---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/yosupo_zalgorithm.test.cpp
    title: verify/string/yosupo_zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/z_algorithm.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\n// Returns z[i] = LCP(sequence,\
    \ sequence[i..]).\ntemplate <class Sequence>\nstd::vector<int> z_algorithm(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return\
    \ {};\n\n    std::vector<int> z(n);\n    z[0] = n;\n    int left = 0;\n    int\
    \ right = 0;\n    for (int i = 1; i < n; i++) {\n        if (i < right) z[i] =\
    \ std::min(right - i, z[i - left]);\n        while (i + z[i] < n && sequence[z[i]]\
    \ == sequence[i + z[i]]) {\n            z[i]++;\n        }\n        if (right\
    \ < i + z[i]) {\n            left = i;\n            right = i + z[i];\n      \
    \  }\n    }\n    return z;\n}\n\n}  // namespace string\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_STRING_Z_ALGORITHM_HPP\n#define M1UNE_STRING_Z_ALGORITHM_HPP\
    \ 1\n\n#include <algorithm>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ string {\n\n// Returns z[i] = LCP(sequence, sequence[i..]).\ntemplate <class\
    \ Sequence>\nstd::vector<int> z_algorithm(const Sequence& sequence) {\n    int\
    \ n = int(sequence.size());\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ z(n);\n    z[0] = n;\n    int left = 0;\n    int right = 0;\n    for (int i\
    \ = 1; i < n; i++) {\n        if (i < right) z[i] = std::min(right - i, z[i -\
    \ left]);\n        while (i + z[i] < n && sequence[z[i]] == sequence[i + z[i]])\
    \ {\n            z[i]++;\n        }\n        if (right < i + z[i]) {\n       \
    \     left = i;\n            right = i + z[i];\n        }\n    }\n    return z;\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_Z_ALGORITHM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-21 02:43:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/yosupo_zalgorithm.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/z_algorithm.hpp
layout: document
title: Z Algorithm
---

## Overview

`z_algorithm(sequence)` returns the longest common prefix length between the
whole sequence and every suffix. It is useful for exact pattern matching,
periodicity, borders, and comparing a fixed prefix against all positions.

The function is generic over indexable sequences such as `std::string` and
`std::vector<int>`.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> z_algorithm(const Sequence& sequence)` | Returns `z[i] = LCP(sequence, sequence[i..])`. For a non-empty sequence, `z[0]` equals its length. | $O(N)$ |

An empty sequence returns an empty vector.

## Example

```cpp
#include "string/z_algorithm.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "ababa";
    auto z = m1une::string::z_algorithm(text);

    for (int length : z) std::cout << length << " ";
    std::cout << "\n"; // 5 0 3 0 1
}
```
