---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/longest_true.hpp\"\n\n\n\n#include <algorithm>\n\n\
    namespace m1une {\nnamespace monoid {\n\nstruct LongestTrueNode {\n    int len;\n\
    \    int max_len;\n    int l_len;\n    int r_len;\n};\n\n// Monoid for finding\
    \ the maximum length of a contiguous subarray\n// where all elements satisfy a\
    \ certain condition (i.e., are \"true\").\nstruct LongestTrue {\n    using value_type\
    \ = LongestTrueNode;\n\n    // The identity element represents an empty array.\n\
    \    static constexpr value_type id() {\n        return {0, 0, 0, 0};\n    }\n\
    \n    // Merges two segments.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (a.len == 0) return b;\n        if (b.len\
    \ == 0) return a;\n\n        value_type res;\n        res.len = a.len + b.len;\n\
    \        res.max_len = std::max({a.max_len, b.max_len, a.r_len + b.l_len});\n\
    \        \n        res.l_len = a.l_len;\n        if (a.len == a.l_len) res.l_len\
    \ += b.l_len;\n        \n        res.r_len = b.r_len;\n        if (b.len == b.r_len)\
    \ res.r_len += a.r_len;\n\n        return res;\n    }\n\n    // Helper to securely\
    \ create a leaf node from a boolean condition.\n    static constexpr value_type\
    \ make(bool val) {\n        return {1, val ? 1 : 0, val ? 1 : 0, val ? 1 : 0};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_LONGEST_TRUE_HPP\n#define M1UNE_MONOID_LONGEST_TRUE_HPP\
    \ 1\n\n#include <algorithm>\n\nnamespace m1une {\nnamespace monoid {\n\nstruct\
    \ LongestTrueNode {\n    int len;\n    int max_len;\n    int l_len;\n    int r_len;\n\
    };\n\n// Monoid for finding the maximum length of a contiguous subarray\n// where\
    \ all elements satisfy a certain condition (i.e., are \"true\").\nstruct LongestTrue\
    \ {\n    using value_type = LongestTrueNode;\n\n    // The identity element represents\
    \ an empty array.\n    static constexpr value_type id() {\n        return {0,\
    \ 0, 0, 0};\n    }\n\n    // Merges two segments.\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        if (a.len == 0) return\
    \ b;\n        if (b.len == 0) return a;\n\n        value_type res;\n        res.len\
    \ = a.len + b.len;\n        res.max_len = std::max({a.max_len, b.max_len, a.r_len\
    \ + b.l_len});\n        \n        res.l_len = a.l_len;\n        if (a.len == a.l_len)\
    \ res.l_len += b.l_len;\n        \n        res.r_len = b.r_len;\n        if (b.len\
    \ == b.r_len) res.r_len += a.r_len;\n\n        return res;\n    }\n\n    // Helper\
    \ to securely create a leaf node from a boolean condition.\n    static constexpr\
    \ value_type make(bool val) {\n        return {1, val ? 1 : 0, val ? 1 : 0, val\
    \ ? 1 : 0};\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MONOID_LONGEST_TRUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/longest_true.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:11:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/longest_true.hpp
layout: document
title: Longest True Monoid
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements satisfy a specific condition (e.g., all elements are `true` or equal to a target value).

## Initialization

Convert your target elements into booleans and use the `make` method to initialize the leaf nodes.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/longest_true.hpp"
#include <iostream>
#include <vector>

using LTM = m1une::monoid::LongestTrue;

int main() {
    std::vector<long long> A = {1, 3, 3, 4, 3, 3, 3, 1};
    int N = A.size();
    long long target = 3;

    std::vector<LTM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Only set to true if the element matches the target
        init_data[i] = LTM::make(A[i] == target);
    }

    m1une::data_structure::Segtree<LTM> seg(init_data);

    auto res = seg.prod(0, N);
    std::cout << "Max Length of " << target << "s: " << res.max_len << "\n"; // Output: 3

    return 0;
}
```
