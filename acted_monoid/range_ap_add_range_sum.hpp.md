---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n    T\
    \ ord_sum;\n};\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n    using\
    \ value_type = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T,\
    \ T>;  // {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static\
    \ constexpr value_type id() {\n        return {T(0), 0, T(0)};\n    }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.sum + b.sum, a.size + b.size, a.ord_sum + b.ord_sum + T(a.size) *\
    \ T(b.size)};\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), T(0)};\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return {f.first\
    \ + g.first, f.second + g.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return mapping(f, x, 0);\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x, long long ord) {\n        return {x.sum + f.first * (x.ord_sum\
    \ + T(ord) * T(x.size)) + f.second * T(x.size), x.size, x.ord_sum};\n    }\n\n\
    \    static constexpr operator_type op_shift(const operator_type& f, long long\
    \ ord) {\n        return {f.first, f.second + f.first * T(ord)};\n    }\n\n  \
    \  static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        return {-f.first, f.second + f.first * T(size - 1)};\n    }\n\
    \n    static constexpr value_type make(const T& val) {\n        return {val, 1,\
    \ T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\
    \ 1\n\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n\
    \    T ord_sum;\n};\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n  \
    \  using value_type = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T,\
    \ T>;  // {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static\
    \ constexpr value_type id() {\n        return {T(0), 0, T(0)};\n    }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.sum + b.sum, a.size + b.size, a.ord_sum + b.ord_sum + T(a.size) *\
    \ T(b.size)};\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), T(0)};\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return {f.first\
    \ + g.first, f.second + g.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return mapping(f, x, 0);\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x, long long ord) {\n        return {x.sum + f.first * (x.ord_sum\
    \ + T(ord) * T(x.size)) + f.second * T(x.size), x.size, x.ord_sum};\n    }\n\n\
    \    static constexpr operator_type op_shift(const operator_type& f, long long\
    \ ord) {\n        return {f.first, f.second + f.first * T(ord)};\n    }\n\n  \
    \  static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        return {-f.first, f.second + f.first * T(size - 1)};\n    }\n\
    \n    static constexpr value_type make(const T& val) {\n        return {val, 1,\
    \ T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    #endif  // M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_add_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:20:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
  - verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  - verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
documentation_of: acted_monoid/range_ap_add_range_sum.hpp
layout: document
title: Range AP Add Range Sum
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries.

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Important Usage Note

The node state (`value_type`) stores `size` and the sum of relative orders (`ord_sum`) it covers. This makes it usable in dynamic arrays where global indices change after insertions, deletions, and reversals.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add f(i) = 2 * i + 5 to the range [1, 4), where i is local to [1, 4)
    // Array becomes: {0, 5, 7, 9, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 5 + 7 + 9 + 0 = 21
    std::cout << seg.prod(0, 5).sum << "\n";

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
