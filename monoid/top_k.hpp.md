---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/bottom_k.hpp
    title: Bottom K Monoid
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/top_k.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <functional>\n#include <vector>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for finding the top/bottom K elements in a range.\n// The elements must\
    \ be stored in the order defined by the Compare functor.\n// Default Compare is\
    \ std::greater<T> (i.e., descending order for Top K).\ntemplate <typename T, int\
    \ K, typename Compare = std::greater<T>>\nstruct TopK {\n    using value_type\
    \ = std::vector<T>;\n\n    // The identity element is an empty vector.\n    static\
    \ constexpr value_type id() {\n        return std::vector<T>();\n    }\n\n   \
    \ // Merges two sorted vectors and keeps only the first K elements.\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  value_type res;\n        res.reserve(std::min(K, (int)(a.size() + b.size())));\n\
    \n        int i = 0, j = 0;\n        while (res.size() < (std::size_t)K && (i\
    \ < (int)a.size() || j < (int)b.size())) {\n            if (i == (int)a.size())\
    \ {\n                res.push_back(b[j++]);\n            } else if (j == (int)b.size())\
    \ {\n                res.push_back(a[i++]);\n            } else if (Compare()(a[i],\
    \ b[j])) {\n                res.push_back(a[i++]);\n            } else {\n   \
    \             res.push_back(b[j++]);\n            }\n        }\n        return\
    \ res;\n    }\n\n    // Helper to securely create a leaf node from a single value.\n\
    \    static constexpr value_type make(const T& val) {\n        return {val};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_TOP_K_HPP\n#define M1UNE_MONOID_TOP_K_HPP 1\n\n#include\
    \ <algorithm>\n#include <functional>\n#include <vector>\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for finding the top/bottom K elements in a range.\n\
    // The elements must be stored in the order defined by the Compare functor.\n\
    // Default Compare is std::greater<T> (i.e., descending order for Top K).\ntemplate\
    \ <typename T, int K, typename Compare = std::greater<T>>\nstruct TopK {\n   \
    \ using value_type = std::vector<T>;\n\n    // The identity element is an empty\
    \ vector.\n    static constexpr value_type id() {\n        return std::vector<T>();\n\
    \    }\n\n    // Merges two sorted vectors and keeps only the first K elements.\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        value_type res;\n        res.reserve(std::min(K, (int)(a.size() +\
    \ b.size())));\n\n        int i = 0, j = 0;\n        while (res.size() < (std::size_t)K\
    \ && (i < (int)a.size() || j < (int)b.size())) {\n            if (i == (int)a.size())\
    \ {\n                res.push_back(b[j++]);\n            } else if (j == (int)b.size())\
    \ {\n                res.push_back(a[i++]);\n            } else if (Compare()(a[i],\
    \ b[j])) {\n                res.push_back(a[i++]);\n            } else {\n   \
    \             res.push_back(b[j++]);\n            }\n        }\n        return\
    \ res;\n    }\n\n    // Helper to securely create a leaf node from a single value.\n\
    \    static constexpr value_type make(const T& val) {\n        return {val};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_TOP_K_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/top_k.hpp
  requiredBy:
  - monoid/bottom_k.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/top_k.hpp
layout: document
title: Top K Monoid
---

## Overview

A monoid that maintains the Top $K$ (largest) elements in a range. The underlying `value_type` is `std::vector<T>`. Merging two nodes takes $O(K)$ time, so $K$ should be relatively small (e.g., $K \le 10$).

## Initialization

Since the state is a `std::vector<T>`, you can use the `make(val)` helper to automatically wrap a single array element into a vector of size 1.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/top_k.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 3 elements
using Top3M = m1une::monoid::TopK<long long, 3>;

int main() {
    std::vector<long long> A = {10, 50, 20, 40, 30};
    int N = A.size();

    std::vector<Top3M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top3M::make(A[i]);
    }

    m1une::ds::Segtree<Top3M> seg(init_data);

    // Get the top 3 elements in the range [0, 4) -> {50, 40, 20}
    std::vector<long long> top3 = seg.prod(0, 4);

    for (long long x : top3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

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
