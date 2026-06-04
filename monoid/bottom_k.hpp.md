---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/top_k.hpp
    title: Top K Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/bottom_k.hpp\"\n\n\n\n#line 1 \"monoid/top_k.hpp\"\
    \n\n\n\n#include <vector>\n#include <algorithm>\n#include <functional>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the top/bottom K elements\
    \ in a range.\n// The elements must be stored in the order defined by the Compare\
    \ functor.\n// Default Compare is std::greater<T> (i.e., descending order for\
    \ Top K).\ntemplate <typename T, int K, typename Compare = std::greater<T>>\n\
    struct TopK {\n    using value_type = std::vector<T>;\n\n    // The identity element\
    \ is an empty vector.\n    static constexpr value_type id() { \n        return\
    \ std::vector<T>(); \n    }\n\n    // Merges two sorted vectors and keeps only\
    \ the first K elements.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        value_type res;\n        res.reserve(std::min(K,\
    \ (int)(a.size() + b.size())));\n        \n        int i = 0, j = 0;\n       \
    \ while (res.size() < (std::size_t)K && (i < (int)a.size() || j < (int)b.size()))\
    \ {\n            if (i == (int)a.size()) {\n                res.push_back(b[j++]);\n\
    \            } else if (j == (int)b.size()) {\n                res.push_back(a[i++]);\n\
    \            } else if (Compare()(a[i], b[j])) { \n                res.push_back(a[i++]);\n\
    \            } else {\n                res.push_back(b[j++]);\n            }\n\
    \        }\n        return res;\n    }\n\n    // Helper to securely create a leaf\
    \ node from a single value.\n    static constexpr value_type make(const T& val)\
    \ {\n        return {val};\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 6 \"monoid/bottom_k.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for finding the bottom K (smallest) elements in a range.\n//\
    \ Defined as a type alias of TopK using std::less.\ntemplate <typename T, int\
    \ K>\nusing BottomK = TopK<T, K, std::less<T>>;\n\n}  // namespace monoid\n} \
    \ // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_BOTTOM_K_HPP

    #define M1UNE_MONOID_BOTTOM_K_HPP 1


    #include "top_k.hpp"

    #include <functional>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the bottom K (smallest) elements in a range.

    // Defined as a type alias of TopK using std::less.

    template <typename T, int K>

    using BottomK = TopK<T, K, std::less<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_BOTTOM_K_HPP

    '
  dependsOn:
  - monoid/top_k.hpp
  isVerificationFile: false
  path: monoid/bottom_k.hpp
  requiredBy: []
  timestamp: '2026-06-04 16:59:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/bottom_k.hpp
layout: document
title: Bottom K Monoid
---

## Overview

A monoid that maintains the Bottom $K$ (smallest) elements in a range, stored in ascending order. The underlying `value_type` is `std::vector<T>`. Merging two nodes takes $O(K)$ time, so $K$ should be relatively small (e.g., $K \le 10$).

This is defined as a type alias of `TopK` using `std::less`. For the maximum counterpart, see `monoid/top_k.hpp`.

## Initialization

Since the state is a `std::vector<T>`, you can use the `make(val)` helper to automatically wrap a single array element into a vector of size 1.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/bottom_k.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Bottom 3 elements
using Bottom3M = m1une::monoid::BottomK<long long, 3>;

int main() {
    std::vector<long long> A = {50, 10, 40, 20, 30};
    int N = A.size();

    std::vector<Bottom3M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Bottom3M::make(A[i]);
    }

    m1une::data_structure::Segtree<Bottom3M> seg(init_data);

    // Get the bottom 3 elements in the range [0, 4) -> {10, 20, 40}
    std::vector<long long> bottom3 = seg.prod(0, 4);
    
    for (long long x : bottom3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
```
