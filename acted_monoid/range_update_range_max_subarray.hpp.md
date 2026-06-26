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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_max_subarray.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <optional>\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeUpdateRangeMaxSubarrayNode {\n    T\
    \ sum, pref, suff, max_sub;\n    long long size;\n};\n\n// Acted Monoid for Range\
    \ Assignment (Update) and Max Contiguous Subarray Sum.\n// Note: This implementation\
    \ assumes empty subarrays are allowed (max sum is at least 0).\ntemplate <typename\
    \ T>\nstruct RangeUpdateRangeMaxSubarray {\n    using value_type = RangeUpdateRangeMaxSubarrayNode<T>;\n\
    \    using operator_type = std::optional<T>;\n\n    static constexpr value_type\
    \ id() {\n        return {T(0), T(0), T(0), T(0), 0};\n    }\n\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.size\
    \ == 0) return b;\n        if (b.size == 0) return a;\n        value_type res;\n\
    \        res.sum = a.sum + b.sum;\n        res.pref = std::max(a.pref, a.sum +\
    \ b.pref);\n        res.suff = std::max(b.suff, b.sum + a.suff);\n        res.max_sub\
    \ = std::max({a.max_sub, b.max_sub, a.suff + b.pref});\n        res.size = a.size\
    \ + b.size;\n        return res;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return std::nullopt;\n    }\n\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ ? f : g;  // left-biased because new updates override old ones\n    }\n\n  \
    \  static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f || x.size == 0) return x;\n        value_type res;\n  \
    \      res.sum = (*f) * x.size;\n        T max_val = std::max(T(0), res.sum);\n\
    \        // If empty subarrays are NOT allowed, change to: T max_val = (*f) >\
    \ 0 ? res.sum : (*f);\n        res.pref = res.suff = res.max_sub = max_val;\n\
    \        res.size = x.size;\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        T max_val = std::max(T(0), val);\n\
    \        return {val, max_val, max_val, max_val, 1};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\
    \ 1\n\n#include <algorithm>\n#include <optional>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T>\nstruct RangeUpdateRangeMaxSubarrayNode\
    \ {\n    T sum, pref, suff, max_sub;\n    long long size;\n};\n\n// Acted Monoid\
    \ for Range Assignment (Update) and Max Contiguous Subarray Sum.\n// Note: This\
    \ implementation assumes empty subarrays are allowed (max sum is at least 0).\n\
    template <typename T>\nstruct RangeUpdateRangeMaxSubarray {\n    using value_type\
    \ = RangeUpdateRangeMaxSubarrayNode<T>;\n    using operator_type = std::optional<T>;\n\
    \n    static constexpr value_type id() {\n        return {T(0), T(0), T(0), T(0),\
    \ 0};\n    }\n\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        if (a.size == 0) return b;\n        if (b.size ==\
    \ 0) return a;\n        value_type res;\n        res.sum = a.sum + b.sum;\n  \
    \      res.pref = std::max(a.pref, a.sum + b.pref);\n        res.suff = std::max(b.suff,\
    \ b.sum + a.suff);\n        res.max_sub = std::max({a.max_sub, b.max_sub, a.suff\
    \ + b.pref});\n        res.size = a.size + b.size;\n        return res;\n    }\n\
    \n    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f ? f : g;  // left-biased because new updates\
    \ override old ones\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f || x.size == 0) return x;\n      \
    \  value_type res;\n        res.sum = (*f) * x.size;\n        T max_val = std::max(T(0),\
    \ res.sum);\n        // If empty subarrays are NOT allowed, change to: T max_val\
    \ = (*f) > 0 ? res.sum : (*f);\n        res.pref = res.suff = res.max_sub = max_val;\n\
    \        res.size = x.size;\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        T max_val = std::max(T(0), val);\n\
    \        return {val, max_val, max_val, max_val, 1};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_max_subarray.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_update_range_max_subarray.hpp
layout: document
title: Range Update Range Max Subarray
---

## Overview

An Acted Monoid for answering Maximum Contiguous Subarray Sum queries subject to Range Assignment (Set/Update) operations.

It maintains the total sum, prefix max, suffix max, and maximum subarray sum for each segment tree node. This represents a classic competitive programming pattern (e.g., CSES "Hotel Queries" variations or AtCoder Library practice).

### Usage Notes

* `operator_type` uses `std::optional<T>`, where `std::nullopt` represents no operation.
* By default, it allows picking an empty subarray (the minimum possible answer is `0`).

## Example

```cpp
using AM = m1une::acted_monoid::RangeUpdateRangeMaxSubarray<long long>;
// seg.prod(l, r).max_sub will give the maximum subarray sum in range [l, r)
// seg.apply(l, r, 5) will set all elements in [l, r) to 5.
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
