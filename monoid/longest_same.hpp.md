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
  bundledCode: "#line 1 \"monoid/longest_same.hpp\"\n\n\n\n#include <algorithm>\n\n\
    namespace m1une {\nnamespace monoid {\n\ntemplate <typename T>\nstruct LongestSameNode\
    \ {\n    int len;\n    int max_len;\n    T l_val;\n    int l_len;\n    T r_val;\n\
    \    int r_len;\n};\n\n// Monoid for finding the maximum length of a contiguous\
    \ subarray\n// where all elements have the same value.\ntemplate <typename T>\n\
    struct LongestSame {\n    using value_type = LongestSameNode<T>;\n\n    // The\
    \ identity element represents an empty array.\n    static constexpr value_type\
    \ id() {\n        return {0, 0, T(), 0, T(), 0};\n    }\n\n    // Merges two segments.\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        if (a.len == 0) return b;\n        if (b.len == 0) return a;\n\n\
    \        value_type res;\n        res.len = a.len + b.len;\n        res.max_len\
    \ = std::max(a.max_len, b.max_len);\n\n        if (a.r_val == b.l_val) {\n   \
    \         res.max_len = std::max(res.max_len, a.r_len + b.l_len);\n        }\n\
    \n        res.l_val = a.l_val;\n        res.l_len = a.l_len;\n        if (a.len\
    \ == a.l_len && a.l_val == b.l_val) {\n            res.l_len += b.l_len;\n   \
    \     }\n\n        res.r_val = b.r_val;\n        res.r_len = b.r_len;\n      \
    \  if (b.len == b.r_len && b.r_val == a.r_val) {\n            res.r_len += a.r_len;\n\
    \        }\n\n        return res;\n    }\n\n    // Helper to securely create a\
    \ leaf node from a single value.\n    static constexpr value_type make(const T&\
    \ val) {\n        return {1, 1, val, 1, val, 1};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_LONGEST_SAME_HPP\n#define M1UNE_MONOID_LONGEST_SAME_HPP\
    \ 1\n\n#include <algorithm>\n\nnamespace m1une {\nnamespace monoid {\n\ntemplate\
    \ <typename T>\nstruct LongestSameNode {\n    int len;\n    int max_len;\n   \
    \ T l_val;\n    int l_len;\n    T r_val;\n    int r_len;\n};\n\n// Monoid for\
    \ finding the maximum length of a contiguous subarray\n// where all elements have\
    \ the same value.\ntemplate <typename T>\nstruct LongestSame {\n    using value_type\
    \ = LongestSameNode<T>;\n\n    // The identity element represents an empty array.\n\
    \    static constexpr value_type id() {\n        return {0, 0, T(), 0, T(), 0};\n\
    \    }\n\n    // Merges two segments.\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        if (a.len == 0) return b;\n \
    \       if (b.len == 0) return a;\n\n        value_type res;\n        res.len\
    \ = a.len + b.len;\n        res.max_len = std::max(a.max_len, b.max_len);\n\n\
    \        if (a.r_val == b.l_val) {\n            res.max_len = std::max(res.max_len,\
    \ a.r_len + b.l_len);\n        }\n\n        res.l_val = a.l_val;\n        res.l_len\
    \ = a.l_len;\n        if (a.len == a.l_len && a.l_val == b.l_val) {\n        \
    \    res.l_len += b.l_len;\n        }\n\n        res.r_val = b.r_val;\n      \
    \  res.r_len = b.r_len;\n        if (b.len == b.r_len && b.r_val == a.r_val) {\n\
    \            res.r_len += a.r_len;\n        }\n\n        return res;\n    }\n\n\
    \    // Helper to securely create a leaf node from a single value.\n    static\
    \ constexpr value_type make(const T& val) {\n        return {1, 1, val, 1, val,\
    \ 1};\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_MONOID_LONGEST_SAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/longest_same.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/longest_same.hpp
layout: document
title: Longest Same Monoid
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements have the same value.

## Initialization

When initializing a segment tree from an array of elements, you should use the `make` helper method to correctly build the leaf nodes.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/longest_same.hpp"
#include <iostream>
#include <vector>

using LSM = m1une::monoid::LongestSame<long long>;

int main() {
    std::vector<long long> A = {2, 2, 5, 5, 5, 2, 2};
    int N = A.size();

    std::vector<LSM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = LSM::make(A[i]);
    }

    m1une::ds::Segtree<LSM> seg(init_data);

    // Get the maximum length of consecutive identical elements in range [0, 7)
    auto res = seg.prod(0, N);
    std::cout << "Max Length: " << res.max_len << "\n"; // Output: 3 (because of "5, 5, 5")

    return 0;
}
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
