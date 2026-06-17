---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_link_cut_tree.test.cpp
    title: verify/data_structure/lazy_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
    title: verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_lazy_segtree.test.cpp
    title: verify/data_structure/persistent_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size};\n\
    \    }\n    static constexpr value_type inverse(const value_type& x) {\n     \
    \   return {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n    static\
    \ constexpr operator_type op_id() {\n        return 0;\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f + g;\n    }\n\n    // Mapping (sum + f * size)\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        return\
    \ {x.sum + f * x.size, x.size};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeAddRangeSumNode {\n    T sum;\n    long long size;\n};\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeSum {\n    using value_type = RangeAddRangeSumNode<T>;\n\
    \    using operator_type = T;\n\n    // Value Monoid (Sum)\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.sum + b.sum,\
    \ a.size + b.size};\n    }\n    static constexpr value_type inverse(const value_type&\
    \ x) {\n        return {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n\
    \    static constexpr operator_type op_id() {\n        return 0;\n    }\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    // Mapping (sum + f * size)\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return {x.sum + f * x.size, x.size};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-17 16:15:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/lazy_link_cut_tree_with_subtree.test.cpp
  - verify/data_structure/persistent_lazy_segtree.test.cpp
  - verify/data_structure/lazy_link_cut_tree.test.cpp
documentation_of: acted_monoid/range_add_range_sum.hpp
layout: document
title: Range Add Range Sum
---

## Overview

An Acted Monoid representing Range Addition operations and Range Sum queries.

### Important Usage Note

When adding a value $f$ to a range of sum $x$, the total sum increases by $f \times (\text{length of the range})$. Therefore, the `value_type` cannot just be an integer; it must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAddRangeSumNode<T>`, which holds both the `sum` and the `size`.

When initializing a data structure (like a Lazy Segment Tree) with this acted monoid, you must initialize the leaf nodes with `size = 1`. You can use the helper function `make(val)` for this purpose.

## Example

```cpp
// Assuming `lazy_segtree` is implemented
std::vector<m1une::acted_monoid::RangeAddRangeSumNode<long long>> init_nodes(N);
for (int i = 0; i < N; ++i) {
    // Initialize each leaf with the value and size = 1
    init_nodes[i] = m1une::acted_monoid::RangeAddRangeSum<long long>::make(A[i]);
}

lazy_segtree<RangeAddRangeSum<long long>> seg(init_nodes);
```
