---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/extra_utilities.test.cpp
    title: verify/utilities/extra_utilities.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/chmin_chmax.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\ntemplate <typename T, typename U>\nbool chmin(T& a, const U&\
    \ b) {\n    if (b < a) {\n        a = b;\n        return true;\n    }\n    return\
    \ false;\n}\n\ntemplate <typename T, typename U>\nbool chmax(T& a, const U& b)\
    \ {\n    if (a < b) {\n        a = b;\n        return true;\n    }\n    return\
    \ false;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CHMIN_CHMAX_HPP\n#define M1UNE_CHMIN_CHMAX_HPP 1\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\ntemplate <typename T, typename U>\nbool chmin(T&\
    \ a, const U& b) {\n    if (b < a) {\n        a = b;\n        return true;\n \
    \   }\n    return false;\n}\n\ntemplate <typename T, typename U>\nbool chmax(T&\
    \ a, const U& b) {\n    if (a < b) {\n        a = b;\n        return true;\n \
    \   }\n    return false;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\
    \n#endif  // M1UNE_CHMIN_CHMAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/chmin_chmax.hpp
  requiredBy: []
  timestamp: '2026-06-16 01:13:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/extra_utilities.test.cpp
documentation_of: utilities/chmin_chmax.hpp
layout: document
title: Chmin Chmax
---

## Overview

Small update helpers for dynamic programming and relaxation code. Each function updates the first argument only when the new value improves it, and returns whether the update happened.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `bool chmin(T& a, const U& b)` | Sets `a = b` if `b < a`. | $O(1)$ |
| `bool chmax(T& a, const U& b)` | Sets `a = b` if `a < b`. | $O(1)$ |

## Example

```cpp
#include "utilities/chmin_chmax.hpp"

int main() {
    int best = 100;
    bool updated = m1une::utilities::chmin(best, 42);
}
```
