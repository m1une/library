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
  bundledCode: "#line 1 \"acted_monoid/range_affine_range_min_max.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T>\nstruct RangeAffineRangeMinMaxNode {\n\
    \    T min_val;\n    T max_val;\n};\n\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct RangeAffineRangeMinMax {\n\
    \    using value_type = RangeAffineRangeMinMaxNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;\n\n    static constexpr value_type id() {\n        return\
    \ {MinId, MaxId};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {std::min(a.min_val, b.min_val), std::max(a.max_val,\
    \ b.max_val)};\n    }\n\n    static constexpr operator_type op_id() {\n      \
    \  return {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first * g.first,\
    \ f.first * g.second + f.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.min_val == MinId) return\
    \ x;\n\n        T v1 = f.first * x.min_val + f.second;\n        T v2 = f.first\
    \ * x.max_val + f.second;\n\n        if (f.first < 0) {\n            return {v2,\
    \ v1};\n        }\n        return {v1, v2};\n    }\n\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val, val};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAffineRangeMinMaxNode\
    \ {\n    T min_val;\n    T max_val;\n};\n\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct RangeAffineRangeMinMax {\n\
    \    using value_type = RangeAffineRangeMinMaxNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;\n\n    static constexpr value_type id() {\n        return\
    \ {MinId, MaxId};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {std::min(a.min_val, b.min_val), std::max(a.max_val,\
    \ b.max_val)};\n    }\n\n    static constexpr operator_type op_id() {\n      \
    \  return {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first * g.first,\
    \ f.first * g.second + f.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.min_val == MinId) return\
    \ x;\n\n        T v1 = f.first * x.min_val + f.second;\n        T v2 = f.first\
    \ * x.max_val + f.second;\n\n        if (f.first < 0) {\n            return {v2,\
    \ v1};\n        }\n        return {v1, v2};\n    }\n\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val, val};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_affine_range_min_max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_affine_range_min_max.hpp
layout: document
title: Range Affine Range Min Max
---

## Overview

An acted monoid that tracks the minimum and maximum values of a range while
supporting affine transformations $f(x) = ax + b$.

Negative scale factors reverse the ordering, so the mapping swaps the roles of
the previous minimum and maximum before applying the transformation.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`, `double`, or a custom floating type).
* `MinId`: The identity element for the minimum operation. Defaults to `std::numeric_limits<T>::max()`.
* `MaxId`: The identity element for the maximum operation. Defaults to `std::numeric_limits<T>::lowest()`.

## Data Structure

* `using value_type = RangeAffineRangeMinMaxNode<T>;`
  The compound state maintained in each segment tree node:
  * `min_val`: The minimum scalar within the range.
  * `max_val`: The maximum scalar within the range.
* `using operator_type = std::pair<T, T>;`
  A pair representing the linear coefficient and addend `{a, b}` for the function $f(x) = ax + b$.

## Element Creation

When building or updating individual elements, use the `make(val)` helper function to encapsulate the scalar into a node matching the value monoid specification.

### `static constexpr value_type make(const T& val)`

* **Parameters:**
  * `val`: The initial scalar value.
* **Returns:** A `RangeAffineRangeMinMaxNode` where both `min_val` and `max_val` are set to `val`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_min_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeMinMax<long long>;

int main() {
    std::vector<long long> A = {2, 5, 3, 8, 4};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Query range [0, 3) -> Elements: {2, 5, 3} -> Min: 2, Max: 5
    auto q1 = seg.prod(0, 3);
    std::cout << "Min: " << q1.min_val << ", Max: " << q1.max_val << "\n"; // Output: Min: 2, Max: 5

    // Apply negative affine transformation f(x) = -2x + 3 to range [0, 3)
    // New values inside range become:
    // 2 -> -2(2) + 3 = -1
    // 5 -> -2(5) + 3 = -7
    // 3 -> -2(3) + 3 = -3
    // Range is now: {-1, -7, -3}
    seg.apply(0, 3, {-2, 3});

    // Query range [0, 3) again -> Min should be -7, Max should be -1
    auto q2 = seg.prod(0, 3);
    std::cout << "Updated Min: " << q2.min_val << ", Updated Max: " << q2.max_val << "\n"; // Output: Min: -7, Max: -1

    return 0;
}
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
