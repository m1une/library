---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/max_subarray.hpp
    title: Max Subarray Monoid
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/min_subarray.hpp\"\n\n\n\n#include <functional>\n\
    #include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n// Node for managing\
    \ the optimal subarray sum.\ntemplate <typename T>\nstruct SubarrayNode {\n  \
    \  T sum;\n    T pre;\n    T suf;\n    T opt;  // Holds the optimal value (e.g.,\
    \ min or max)\n};\n\n// Monoid for finding the minimum subarray sum in a range.\n\
    // Uses a comparison functor (Compare) to determine the optimal value.\n// Can\
    \ be reused for maximum subarray sum by changing the Compare functor.\ntemplate\
    \ <typename T, T Id = std::numeric_limits<T>::max() / 2, typename Compare = std::less<T>>\n\
    struct MinSubarray {\n    using value_type = SubarrayNode<T>;\n\n    // The identity\
    \ element contains values that do not affect the result.\n    static constexpr\
    \ value_type id() {\n        return {T(0), Id, Id, Id};\n    }\n\n    // Merges\
    \ two subarray nodes.\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        if (a.opt == Id) return b;\n        if (b.opt\
    \ == Id) return a;\n\n        // Lambda to select the optimal value according\
    \ to the comparison functor.\n        auto get_opt = [](const T& x, const T& y)\
    \ { return Compare()(x, y) ? x : y; };\n\n        return {a.sum + b.sum, get_opt(a.pre,\
    \ a.sum + b.pre), get_opt(b.suf, a.suf + b.sum),\n                get_opt(get_opt(a.opt,\
    \ b.opt), a.suf + b.pre)};\n    }\n\n    // Helper to securely create a leaf node\
    \ from a single value.\n    // Set `allow_empty = true` if empty subarrays (sum\
    \ = 0) are valid answers.\n    static constexpr value_type make(const T& val,\
    \ bool allow_empty = false) {\n        if (allow_empty) {\n            T opt_val\
    \ = Compare()(val, T(0)) ? val : T(0);\n            return {val, opt_val, opt_val,\
    \ opt_val};\n        }\n        return {val, val, val, val};\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_SUBARRAY_HPP\n#define M1UNE_MONOID_MIN_SUBARRAY_HPP\
    \ 1\n\n#include <functional>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Node for managing the optimal subarray sum.\ntemplate <typename\
    \ T>\nstruct SubarrayNode {\n    T sum;\n    T pre;\n    T suf;\n    T opt;  //\
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
    \ get_opt = [](const T& x, const T& y) { return Compare()(x, y) ? x : y; };\n\n\
    \        return {a.sum + b.sum, get_opt(a.pre, a.sum + b.pre), get_opt(b.suf,\
    \ a.suf + b.sum),\n                get_opt(get_opt(a.opt, b.opt), a.suf + b.pre)};\n\
    \    }\n\n    // Helper to securely create a leaf node from a single value.\n\
    \    // Set `allow_empty = true` if empty subarrays (sum = 0) are valid answers.\n\
    \    static constexpr value_type make(const T& val, bool allow_empty = false)\
    \ {\n        if (allow_empty) {\n            T opt_val = Compare()(val, T(0))\
    \ ? val : T(0);\n            return {val, opt_val, opt_val, opt_val};\n      \
    \  }\n        return {val, val, val, val};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_MIN_SUBARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min_subarray.hpp
  requiredBy:
  - monoid/max_subarray.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/min_subarray.hpp
layout: document
title: Min Subarray Monoid
---

## Overview

A monoid for finding the minimum contiguous subarray sum within a range.
The underlying state is `m1une::monoid::SubarrayNode<T>`, which holds 4 values:
1. `sum`: The sum of the entire segment.
2. `pre`: The minimum prefix sum.
3. `suf`: The minimum suffix sum.
4. `opt`: The minimum subarray sum inside the segment.

## Initialization

To initialize a leaf node for a single value $x$, use the `make(val, allow_empty)` method.

* **If empty subarrays are NOT allowed (Standard):**
  Use `make(x)` or `make(x, false)`. At least 1 element must be chosen.
* **If empty subarrays ARE allowed (Min is bounded above by 0):**
  Use `make(x, true)`.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/min_subarray.hpp"
#include <iostream>
#include <vector>

using MinSubM = m1une::monoid::MinSubarray<long long>;

int main() {
    std::vector<long long> A = {2, -1, 3, -4, 1, -2, -1, 5, -4};
    int N = A.size();

    std::vector<MinSubM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Standard initialization (At least 1 element must be chosen)
        init_data[i] = MinSubM::make(A[i]);
    }

    m1une::data_structure::Segtree<MinSubM> seg(init_data);

    // Min subarray sum in the whole array is -7 (from "-4, 1, -2, -1")
    auto node = seg.prod(0, N);
    std::cout << "Min Subarray Sum: " << node.opt << "\n"; 

    return 0;
}
```
