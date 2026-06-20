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
  bundledCode: "#line 1 \"monoid/permutation.hpp\"\n\n\n\n#include <array>\n#include\
    \ <numeric>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for Permutation\
    \ Composition.\n// Represents a permutation of fixed size N.\ntemplate <int N>\n\
    struct Permutation {\n    using value_type = std::array<int, N>;\n\n    // The\
    \ identity element is the identity permutation (0, 1, 2, ..., N-1).\n    static\
    \ constexpr value_type id() {\n        value_type res{};\n        std::iota(res.begin(),\
    \ res.end(), 0);\n        return res;\n    }\n\n    // Composes two permutations\
    \ (applies 'a' then 'b').\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        value_type res{};\n        for (int i = 0;\
    \ i < N; ++i) {\n            res[i] = b[a[i]];\n        }\n        return res;\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_PERMUTATION_HPP\n#define M1UNE_MONOID_PERMUTATION_HPP\
    \ 1\n\n#include <array>\n#include <numeric>\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for Permutation Composition.\n// Represents a permutation of\
    \ fixed size N.\ntemplate <int N>\nstruct Permutation {\n    using value_type\
    \ = std::array<int, N>;\n\n    // The identity element is the identity permutation\
    \ (0, 1, 2, ..., N-1).\n    static constexpr value_type id() {\n        value_type\
    \ res{};\n        std::iota(res.begin(), res.end(), 0);\n        return res;\n\
    \    }\n\n    // Composes two permutations (applies 'a' then 'b').\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  value_type res{};\n        for (int i = 0; i < N; ++i) {\n            res[i]\
    \ = b[a[i]];\n        }\n        return res;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_PERMUTATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/permutation.hpp
  requiredBy: []
  timestamp: '2026-05-28 18:13:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/permutation.hpp
layout: document
title: Permutation Monoid
---

## Overview

A monoid for representing and composing fixed-size permutations. The underlying `value_type` is `std::array<int, N>`.

When two permutations $A$ and $B$ are merged (i.e., `op(A, B)`), it corresponds to applying permutation $A$ first, followed by permutation $B$. That is, the resulting permutation $C$ satisfies $C[i] = B[A[i]]$.

## Example

```cpp
#include "ds/segment_tree/segtree.hpp"
#include "monoid/permutation.hpp"
#include <iostream>
#include <vector>

using Perm3 = m1une::monoid::Permutation<3>;

int main() {
    std::vector<Perm3::value_type> init_data = {
        {1, 2, 0}, // Swaps elements cyclically
        {0, 2, 1}  // Swaps index 1 and 2
    };

    m1une::ds::Segtree<Perm3> seg(init_data);

    // Get the composed permutation for the range [0, 2)
    auto res = seg.prod(0, 2);

    std::cout << "0 maps to: " << res[0] << "\n";
    std::cout << "1 maps to: " << res[1] << "\n";
    std::cout << "2 maps to: " << res[2] << "\n";

    return 0;
}
```
