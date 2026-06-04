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
  bundledCode: "#line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n    T\
    \ idx_sum;\n};\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n    using\
    \ value_type = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T,\
    \ T>; // {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static\
    \ constexpr value_type id() { return {T(0), 0, T(0)}; }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size, a.idx_sum + b.idx_sum};\n    }\n\n    // Operator\
    \ Monoid (Add)\n    static constexpr operator_type op_id() { return {T(0), T(0)};\
    \ }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return {f.first + g.first, f.second + g.second};\n\
    \    }\n\n    // Mapping: sum += a * idx_sum + b * size\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        return\
    \ {\n            x.sum + f.first * x.idx_sum + f.second * T(x.size),\n       \
    \     x.size,\n            x.idx_sum\n        };\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    // Crucial: You MUST pass the 0-based index `idx` during initialization.\n\
    \    static constexpr value_type make(const T& val, long long idx) {\n       \
    \ return {val, 1, T(idx)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\
    \ 1\n\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n\
    \    T idx_sum;\n};\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n  \
    \  using value_type = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T,\
    \ T>; // {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static\
    \ constexpr value_type id() { return {T(0), 0, T(0)}; }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size, a.idx_sum + b.idx_sum};\n    }\n\n    // Operator\
    \ Monoid (Add)\n    static constexpr operator_type op_id() { return {T(0), T(0)};\
    \ }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return {f.first + g.first, f.second + g.second};\n\
    \    }\n\n    // Mapping: sum += a * idx_sum + b * size\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        return\
    \ {\n            x.sum + f.first * x.idx_sum + f.second * T(x.size),\n       \
    \     x.size,\n            x.idx_sum\n        };\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    // Crucial: You MUST pass the 0-based index `idx` during initialization.\n\
    \    static constexpr value_type make(const T& val, long long idx) {\n       \
    \ return {val, 1, T(idx)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_add_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-04 17:38:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_ap_add_range_sum.hpp
layout: document
title: Range AP Add Range Sum
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries. 

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the original global 0-based index of the array element.

### Important Usage Note

Because standard lazy segment trees do not pass array bounds downwards during propagation, the node state (`value_type`) must store the sum of the indices (`idx_sum`) it covers, along with the standard `size`. 

When initializing the leaf nodes, you **must provide the index** of the element to the `make(val, idx)` helper.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        // Pass both the initial value AND the current index 'i'
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Add f(i) = 2 * i + 5 to the range [1, 4)
    // index 1: 2(1) + 5 = 7
    // index 2: 2(2) + 5 = 9
    // index 3: 2(3) + 5 = 11
    // Array becomes: {0, 7, 9, 11, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 7 + 9 + 11 + 0 = 27
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
