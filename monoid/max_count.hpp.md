---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/min_count.hpp
    title: MinCount Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/max_count.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <limits>\n\n#line 1 \"monoid/min_count.hpp\"\n\n\n\n#line 6 \"monoid/min_count.hpp\"\
    \n#include <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for\
    \ finding the optimal value and its frequency in a range.\n// Uses a comparison\
    \ functor (Compare) to determine the optimal value (default is less, i.e., minimum).\n\
    template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare =\
    \ std::less<T>>\nstruct MinCount {\n    using value_type = std::pair<T, int>;\n\
    \n    // The identity element has the specified Id value and a count of 0.\n \
    \   static constexpr value_type id() {\n        return {Id, 0};\n    }\n\n   \
    \ // Combines two elements, updating the optimal value and summing the counts\
    \ if they are equal.\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        if (Compare()(a.first, b.first)) return a;\n\
    \        if (Compare()(b.first, a.first)) return b;\n        return {a.first,\
    \ a.second + b.second};\n    }\n\n    // Helper to securely create a leaf node\
    \ from a single value.\n    static constexpr value_type make(const T& val, int\
    \ count = 1) {\n        return {val, count};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 8 \"monoid/max_count.hpp\"\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for finding the maximum value and its frequency\
    \ in a range.\n// Defined as a type alias of MinCount using std::greater.\ntemplate\
    \ <typename T, T Id = std::numeric_limits<T>::lowest()>\nusing MaxCount = MinCount<T,\
    \ Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_MAX_COUNT_HPP

    #define M1UNE_MONOID_MAX_COUNT_HPP 1


    #include <functional>

    #include <limits>


    #include "min_count.hpp"


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum value and its frequency in a range.

    // Defined as a type alias of MinCount using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using MaxCount = MinCount<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_MAX_COUNT_HPP

    '
  dependsOn:
  - monoid/min_count.hpp
  isVerificationFile: false
  path: monoid/max_count.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max_count.hpp
layout: document
title: MaxCount Monoid
---

## Overview

A monoid for finding both the **maximum value** and **the frequency (count) of that maximum value** in a range. The underlying `value_type` is `std::pair<T, int>`, where `first` is the value and `second` is the count.

This is the maximum counterpart to `monoid/min_count.hpp`.

## Initialization

When initializing a segment tree from an array of elements, use the `make(val)` method to construct a leaf node with a default count of 1.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/max_count.hpp"
#include <iostream>
#include <vector>

using MaxCountM = m1une::monoid::MaxCount<long long>;

int main() {
    std::vector<long long> A = {3, 9, 4, 9, 5, 9, 1};
    int N = A.size();

    std::vector<MaxCountM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MaxCountM::make(A[i]);
    }

    m1une::ds::Segtree<MaxCountM> seg(init_data);

    // Query the range [0, 6) -> Elements: {3, 9, 4, 9, 5, 9}
    // Maximum is 9, it appears 3 times.
    auto [max_val, count] = seg.prod(0, 6);
    std::cout << "Max: " << max_val << ", Count: " << count << "\n"; // Output: Max: 9, Count: 3

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
