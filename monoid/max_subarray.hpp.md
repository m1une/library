---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/min_subarray.hpp
    title: monoid/min_subarray.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/max_subarray.hpp\"\n\n\n\n#line 1 \"monoid/min_subarray.hpp\"\
    \n\n\n\n#include <functional>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Node for managing the optimal subarray sum.\ntemplate <typename\
    \ T>\nstruct SubarrayNode {\n    T sum;\n    T pre;\n    T suf;\n    T opt; //\
    \ Holds the optimal value (e.g., min or max)\n};\n\n// Monoid for finding the\
    \ minimum subarray sum in a range.\n// Uses a comparison functor (Compare) to\
    \ determine the optimal value.\n// Can be reused for maximum subarray sum by changing\
    \ the Compare functor.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()\
    \ / 2, typename Compare = std::less<T>>\nstruct MinSubarray {\n    using value_type\
    \ = SubarrayNode<T>;\n\n    // The identity element contains values that do not\
    \ affect the result.\n    static constexpr value_type id() {\n        return {T(0),\
    \ Id, Id, Id};\n    }\n\n    // Merges two subarray nodes.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.opt\
    \ == Id) return b;\n        if (b.opt == Id) return a;\n\n        // Lambda to\
    \ select the optimal value according to the comparison functor.\n        auto\
    \ get_opt = [](const T& x, const T& y) {\n            return Compare()(x, y) ?\
    \ x : y;\n        };\n\n        return {\n            a.sum + b.sum,\n       \
    \     get_opt(a.pre, a.sum + b.pre),\n            get_opt(b.suf, a.suf + b.sum),\n\
    \            get_opt(get_opt(a.opt, b.opt), a.suf + b.pre)\n        };\n    }\n\
    \n    // Helper to securely create a leaf node from a single value.\n    // Set\
    \ `allow_empty = true` if empty subarrays (sum = 0) are valid answers.\n    static\
    \ constexpr value_type make(const T& val, bool allow_empty = false) {\n      \
    \  if (allow_empty) {\n            T opt_val = Compare()(val, T(0)) ? val : T(0);\n\
    \            return {val, opt_val, opt_val, opt_val};\n        }\n        return\
    \ {val, val, val, val};\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 7 \"monoid/max_subarray.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Monoid for finding the maximum subarray sum in a range.\n// Defined\
    \ as a type alias of MinSubarray using std::greater.\ntemplate <typename T, T\
    \ Id = std::numeric_limits<T>::lowest() / 2>\nusing MaxSubarray = MinSubarray<T,\
    \ Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_MAX_SUBARRAY_HPP

    #define M1UNE_MONOID_MAX_SUBARRAY_HPP 1


    #include "min_subarray.hpp"

    #include <functional>

    #include <limits>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum subarray sum in a range.

    // Defined as a type alias of MinSubarray using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest() / 2>

    using MaxSubarray = MinSubarray<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_MAX_SUBARRAY_HPP

    '
  dependsOn:
  - monoid/min_subarray.hpp
  isVerificationFile: false
  path: monoid/max_subarray.hpp
  requiredBy: []
  timestamp: '2026-06-04 16:59:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max_subarray.hpp
layout: document
title: Max Subarray Monoid
---

## Overview

A monoid for finding the maximum contiguous subarray sum within a range.
The underlying state is `m1une::monoid::SubarrayNode<T>`, which holds 4 values:
1. `sum`: The sum of the entire segment.
2. `pre`: The maximum prefix sum.
3. `suf`: The maximum suffix sum.
4. `opt`: The maximum subarray sum inside the segment.

## Initialization

To initialize a leaf node for a single value $x$, use the `make(val, allow_empty)` method.

* **If empty subarrays are NOT allowed (Standard):**
  Use `make(x)` or `make(x, false)`. At least 1 element must be chosen.
* **If empty subarrays ARE allowed (Max is bounded below by 0):**
  Use `make(x, true)`.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/max_subarray.hpp"
#include <iostream>
#include <vector>

using MaxSubM = m1une::monoid::MaxSubarray<long long>;

int main() {
    std::vector<long long> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int N = A.size();

    std::vector<MaxSubM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Standard initialization (At least 1 element must be chosen)
        init_data[i] = MaxSubM::make(A[i]);
    }

    m1une::data_structure::Segtree<MaxSubM> seg(init_data);

    // Max subarray sum in the whole array is 6 (from "4, -1, 2, 1")
    auto node = seg.prod(0, N);
    std::cout << "Max Subarray Sum: " << node.opt << "\n"; 

    return 0;
}
```
