---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/uniform_matroid.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace matroid {\n\nclass UniformMatroid\
    \ {\n   private:\n    int _ground_size;\n    int _rank;\n\n   public:\n    UniformMatroid()\
    \ : _ground_size(0), _rank(0) {}\n    UniformMatroid(int ground_size, int rank)\
    \ : _ground_size(ground_size), _rank(rank) {\n        assert(0 <= rank && rank\
    \ <= ground_size);\n    }\n\n    int size() const {\n        return _ground_size;\n\
    \    }\n\n    int rank() const {\n        return _rank;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        return int(subset.size()) <= _rank;\n\
    \    }\n\n    bool operator()(const std::vector<int>& subset) const {\n      \
    \  return independent(subset);\n    }\n};\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATROID_UNIFORM_MATROID_HPP\n#define M1UNE_MATROID_UNIFORM_MATROID_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\nclass UniformMatroid {\n   private:\n    int _ground_size;\n    int _rank;\n\
    \n   public:\n    UniformMatroid() : _ground_size(0), _rank(0) {}\n    UniformMatroid(int\
    \ ground_size, int rank) : _ground_size(ground_size), _rank(rank) {\n        assert(0\
    \ <= rank && rank <= ground_size);\n    }\n\n    int size() const {\n        return\
    \ _ground_size;\n    }\n\n    int rank() const {\n        return _rank;\n    }\n\
    \n    bool independent(const std::vector<int>& subset) const {\n        return\
    \ int(subset.size()) <= _rank;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n#endif  // M1UNE_MATROID_UNIFORM_MATROID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/uniform_matroid.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/matroid/matroids.test.cpp
documentation_of: matroid/uniform_matroid.hpp
layout: document
title: Uniform Matroid
---

## Overview

`UniformMatroid` represents the uniform matroid $U_{r,n}$. Its ground set is
`{0, 1, ..., n - 1}`, and a subset is independent exactly when it contains at
most $r$ elements.

Oracle inputs must contain distinct valid ground-set indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `UniformMatroid(int ground_size, int rank)` | Constructs $U_{r,n}$. Requires `0 <= rank <= ground_size`. | $O(1)$ |
| `int size() const` | Returns the ground-set size. | $O(1)$ |
| `int rank() const` | Returns $r$. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Tests whether `subset.size() <= rank()`. | $O(1)$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(1)$ |

## Example

```cpp
#include "matroid/uniform_matroid.hpp"
#include <vector>

m1une::matroid::UniformMatroid matroid(5, 2);
bool ok = matroid(std::vector<int>{1, 4}); // true
```
