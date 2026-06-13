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
    \ T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long index;\n\
    };\n\n// Acted Monoid for Range Addition and Range Maximum Value & Index queries.\n\
    template <typename T>\nstruct RangeAddRangeArgMax {\n    using value_type = RangeAddRangeArgMaxNode<T>;\n\
    \    using operator_type = T;\n\n    static constexpr value_type id() {\n    \
    \    return {std::numeric_limits<T>::lowest(), -1};\n    }\n\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        // >= gives\
    \ priority to the earlier (leftmost) index in case of a tie\n        if (a.max_val\
    \ >= b.max_val) return a;\n        return b;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return T(0);\n    }\n\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (x.index == -1) return x;\n        return\
    \ {x.max_val + f, x.index};\n    }\n\n    // Helper for initialization, requires\
    \ passing the index explicitly\n    static constexpr value_type make(const T&\
    \ val, long long index) {\n        return {val, index};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\
    \ 1\n\n#include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long\
    \ index;\n};\n\n// Acted Monoid for Range Addition and Range Maximum Value & Index\
    \ queries.\ntemplate <typename T>\nstruct RangeAddRangeArgMax {\n    using value_type\
    \ = RangeAddRangeArgMaxNode<T>;\n    using operator_type = T;\n\n    static constexpr\
    \ value_type id() {\n        return {std::numeric_limits<T>::lowest(), -1};\n\
    \    }\n\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        // >= gives priority to the earlier (leftmost) index in case of\
    \ a tie\n        if (a.max_val >= b.max_val) return a;\n        return b;\n  \
    \  }\n\n    static constexpr operator_type op_id() {\n        return T(0);\n \
    \   }\n\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f + g;\n    }\n\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        if (x.index\
    \ == -1) return x;\n        return {x.max_val + f, x.index};\n    }\n\n    //\
    \ Helper for initialization, requires passing the index explicitly\n    static\
    \ constexpr value_type make(const T& val, long long index) {\n        return {val,\
    \ index};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    #endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_arg_max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_arg_max.hpp
layout: document
title: Range Add Range ArgMax
---

## Overview

An Acted Monoid to support Range Addition and queries for the Maximum Value *and its Index* (ArgMax). 

### Tie-breaking
If there are multiple maximum values in the queried range, the `op` function is designed to return the leftmost index (smallest index) by prioritizing the left child using `>=`.

## Example
When initializing the segment tree, ensure you pass the index explicitly using the `make()` helper function.

```cpp
using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
std::vector<AM::value_type> init_nodes(N);
for(int i = 0; i < N; ++i) {
    init_nodes[i] = AM::make(A[i], i);
}
m1une::data_structure::LazySegtree<AM> seg(init_nodes);
```
