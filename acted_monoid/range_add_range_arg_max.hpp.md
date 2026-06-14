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
  bundledCode: "#line 1 \"acted_monoid/range_add_range_arg_max.hpp\"\n\n\n\n#include\
    \ <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long size;\n\
    \    long long ord;\n};\n\n// Acted Monoid for Range Addition and Range Maximum\
    \ Value & Index queries.\ntemplate <typename T>\nstruct RangeAddRangeArgMax {\n\
    \    using value_type = RangeAddRangeArgMaxNode<T>;\n    using operator_type =\
    \ T;\n\n    static constexpr value_type id() {\n        return {std::numeric_limits<T>::lowest(),\
    \ 0, -1};\n    }\n\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        if (a.size == 0) return b;\n        if (b.size ==\
    \ 0) return a;\n        long long size = a.size + b.size;\n        if (a.max_val\
    \ >= b.max_val) return {a.max_val, size, a.ord};\n        return {b.max_val, size,\
    \ b.ord + a.size};\n    }\n\n    static constexpr operator_type op_id() {\n  \
    \      return T(0);\n    }\n\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.size == 0) return x;\n        return {x.max_val + f, x.size,\
    \ x.ord};\n    }\n\n    static constexpr value_type make(const T& val) {\n   \
    \     return {val, 1, 0};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\
    \ 1\n\n#include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long\
    \ size;\n    long long ord;\n};\n\n// Acted Monoid for Range Addition and Range\
    \ Maximum Value & Index queries.\ntemplate <typename T>\nstruct RangeAddRangeArgMax\
    \ {\n    using value_type = RangeAddRangeArgMaxNode<T>;\n    using operator_type\
    \ = T;\n\n    static constexpr value_type id() {\n        return {std::numeric_limits<T>::lowest(),\
    \ 0, -1};\n    }\n\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        if (a.size == 0) return b;\n        if (b.size ==\
    \ 0) return a;\n        long long size = a.size + b.size;\n        if (a.max_val\
    \ >= b.max_val) return {a.max_val, size, a.ord};\n        return {b.max_val, size,\
    \ b.ord + a.size};\n    }\n\n    static constexpr operator_type op_id() {\n  \
    \      return T(0);\n    }\n\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.size == 0) return x;\n        return {x.max_val + f, x.size,\
    \ x.ord};\n    }\n\n    static constexpr value_type make(const T& val) {\n   \
    \     return {val, 1, 0};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_arg_max.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:20:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_arg_max.hpp
layout: document
title: Range Add Range ArgMax
---

## Overview

An Acted Monoid to support Range Addition and queries for the Maximum Value and its relative order (ArgMax).

### Tie-breaking
If there are multiple maximum values in the queried range, the `op` function returns the earliest order.

## Example

```cpp
using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
m1une::data_structure::LazySegtree<AM> seg(A);
auto q = seg.prod(0, A.size());
std::cout << q.max_val << " " << q.ord << "\n";
```
