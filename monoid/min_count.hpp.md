---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: acted_monoid/range_add_range_min_count.hpp
    title: Range Add Range Min Count
  - icon: ':warning:'
    path: monoid/max_count.hpp
    title: MaxCount Monoid
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/min_count.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <limits>\n#include <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Monoid for finding the optimal value and its frequency in a range.\n// Uses\
    \ a comparison functor (Compare) to determine the optimal value (default is less,\
    \ i.e., minimum).\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct MinCount {\n    using value_type =\
    \ std::pair<T, int>;\n\n    // The identity element has the specified Id value\
    \ and a count of 0.\n    static constexpr value_type id() {\n        return {Id,\
    \ 0};\n    }\n\n    // Combines two elements, updating the optimal value and summing\
    \ the counts if they are equal.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (Compare()(a.first, b.first)) return a;\n\
    \        if (Compare()(b.first, a.first)) return b;\n        return {a.first,\
    \ a.second + b.second};\n    }\n\n    // Helper to securely create a leaf node\
    \ from a single value.\n    static constexpr value_type make(const T& val, int\
    \ count = 1) {\n        return {val, count};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_COUNT_HPP\n#define M1UNE_MONOID_MIN_COUNT_HPP 1\n\
    \n#include <functional>\n#include <limits>\n#include <utility>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for finding the optimal value and its frequency\
    \ in a range.\n// Uses a comparison functor (Compare) to determine the optimal\
    \ value (default is less, i.e., minimum).\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct MinCount {\n    using value_type =\
    \ std::pair<T, int>;\n\n    // The identity element has the specified Id value\
    \ and a count of 0.\n    static constexpr value_type id() {\n        return {Id,\
    \ 0};\n    }\n\n    // Combines two elements, updating the optimal value and summing\
    \ the counts if they are equal.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (Compare()(a.first, b.first)) return a;\n\
    \        if (Compare()(b.first, a.first)) return b;\n        return {a.first,\
    \ a.second + b.second};\n    }\n\n    // Helper to securely create a leaf node\
    \ from a single value.\n    static constexpr value_type make(const T& val, int\
    \ count = 1) {\n        return {val, count};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_MIN_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min_count.hpp
  requiredBy:
  - acted_monoid/range_add_range_min_count.hpp
  - monoid/max_count.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/min_count.hpp
layout: document
title: MinCount Monoid
---

## Overview

A monoid for finding both the **minimum value** and **the frequency (count) of that minimum value** in a range. The underlying `value_type` is `std::pair<T, int>`, where `first` is the value and `second` is the count.

## Initialization

When initializing a segment tree from an array of elements, use the `make(val)` method to construct a leaf node with a default count of 1.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/min_count.hpp"
#include <iostream>
#include <vector>

using MinCountM = m1une::monoid::MinCount<long long>;

int main() {
    std::vector<long long> A = {3, 1, 4, 1, 5, 1, 9};
    int N = A.size();

    std::vector<MinCountM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinCountM::make(A[i]);
    }

    m1une::ds::Segtree<MinCountM> seg(init_data);

    // Query the range [0, 5) -> Elements: {3, 1, 4, 1, 5}
    // Minimum is 1, it appears 2 times.
    auto [min_val, count] = seg.prod(0, 5);
    std::cout << "Min: " << min_val << ", Count: " << count << "\n"; // Output: Min: 1, Count: 2

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
