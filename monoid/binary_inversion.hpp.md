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
  bundledCode: "#line 1 \"monoid/binary_inversion.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace monoid {\n\ntemplate <typename T = long long>\nstruct BinaryInversionNode\
    \ {\n    long long zeros;\n    long long ones;\n    T inversions;\n};\n\n// Monoid\
    \ for counting zeros, ones, and inversions (1s before 0s) in a binary array.\n\
    template <typename T = long long>\nstruct BinaryInversion {\n    using value_type\
    \ = BinaryInversionNode<T>;\n\n    // The identity element has 0 zeros, 0 ones,\
    \ and 0 inversions.\n    static constexpr value_type id() {\n        return {0,\
    \ 0, 0};\n    }\n\n    // Merges two segments and calculates the new inversions.\n\
    \    // New inversions = left inversions + right inversions + (ones in left *\
    \ zeros in right)\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        return {\n            a.zeros + b.zeros,\n       \
    \     a.ones + b.ones,\n            a.inversions + b.inversions + a.ones * b.zeros\n\
    \        };\n    }\n\n    // Helper to securely create a leaf node from a value\
    \ (0 or 1).\n    static constexpr value_type make(int val) {\n        if (val\
    \ == 0) return {1, 0, 0};\n        return {0, 1, 0};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_BINARY_INVERSION_HPP\n#define M1UNE_MONOID_BINARY_INVERSION_HPP\
    \ 1\n\nnamespace m1une {\nnamespace monoid {\n\ntemplate <typename T = long long>\n\
    struct BinaryInversionNode {\n    long long zeros;\n    long long ones;\n    T\
    \ inversions;\n};\n\n// Monoid for counting zeros, ones, and inversions (1s before\
    \ 0s) in a binary array.\ntemplate <typename T = long long>\nstruct BinaryInversion\
    \ {\n    using value_type = BinaryInversionNode<T>;\n\n    // The identity element\
    \ has 0 zeros, 0 ones, and 0 inversions.\n    static constexpr value_type id()\
    \ {\n        return {0, 0, 0};\n    }\n\n    // Merges two segments and calculates\
    \ the new inversions.\n    // New inversions = left inversions + right inversions\
    \ + (ones in left * zeros in right)\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {\n            a.zeros\
    \ + b.zeros,\n            a.ones + b.ones,\n            a.inversions + b.inversions\
    \ + a.ones * b.zeros\n        };\n    }\n\n    // Helper to securely create a\
    \ leaf node from a value (0 or 1).\n    static constexpr value_type make(int val)\
    \ {\n        if (val == 0) return {1, 0, 0};\n        return {0, 1, 0};\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_BINARY_INVERSION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/binary_inversion.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:15:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/binary_inversion.hpp
layout: document
title: Binary Inversion Monoid
---

## Overview

A monoid for counting the number of `0`s, `1`s, and inversions (the number of pairs where `1` appears before `0`) in a binary array. 

## Initialization

Use the `make(val)` helper to initialize leaf nodes, passing either `0` or `1`.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/binary_inversion.hpp"
#include <iostream>
#include <vector>

using BinInv = m1une::monoid::BinaryInversion<long long>;

int main() {
    // Array: [1, 0, 1, 0, 0]
    std::vector<int> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<BinInv::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = BinInv::make(A[i]);
    }

    m1une::data_structure::Segtree<BinInv> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << "Zeros: " << res.zeros << "\n";
    std::cout << "Ones: " << res.ones << "\n";
    std::cout << "Inversions: " << res.inversions << "\n"; // Output: 5

    return 0;
}
```
