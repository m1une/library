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
  bundledCode: "#line 1 \"acted_monoid/range_ap_update_range_sum.hpp\"\n\n\n\n#include\
    \ <optional>\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeApUpdateRangeSumNode {\n    T sum;\n\
    \    long long size;\n    T idx_sum;\n};\n\ntemplate <typename T>\nstruct RangeApUpdateRangeSum\
    \ {\n    using value_type = RangeApUpdateRangeSumNode<T>;\n    using operator_type\
    \ = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b\n\n  \
    \  // Value Monoid (Sum)\n    static constexpr value_type id() {\n        return\
    \ {T(0), 0, T(0)};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size, a.idx_sum\
    \ + b.idx_sum};\n    }\n\n    // Operator Monoid (Update)\n    static constexpr\
    \ operator_type op_id() {\n        return std::nullopt;\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      // Prioritize the newer operation (f) over the older one (g)\n        return\
    \ f.has_value() ? f : g;\n    }\n\n    // Mapping: sum = a * idx_sum + b * size\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f.has_value() || x.size == 0) return x;\n        return {f.value().first\
    \ * x.idx_sum + f.value().second * T(x.size), x.size, x.idx_sum};\n    }\n\n \
    \   // Helper for initializing a leaf node\n    // Crucial: You MUST pass the\
    \ 0-based index `idx` during initialization.\n    static constexpr value_type\
    \ make(const T& val, long long idx) {\n        return {val, 1, T(idx)};\n    }\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\
    \ 1\n\n#include <optional>\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T>\nstruct RangeApUpdateRangeSumNode {\n\
    \    T sum;\n    long long size;\n    T idx_sum;\n};\n\ntemplate <typename T>\n\
    struct RangeApUpdateRangeSum {\n    using value_type = RangeApUpdateRangeSumNode<T>;\n\
    \    using operator_type = std::optional<std::pair<T, T>>;  // {a, b} for setting\
    \ to a * i + b\n\n    // Value Monoid (Sum)\n    static constexpr value_type id()\
    \ {\n        return {T(0), 0, T(0)};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size, a.idx_sum + b.idx_sum};\n    }\n\n    // Operator Monoid (Update)\n\
    \    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        // Prioritize the newer operation (f) over the\
    \ older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    // Mapping:\
    \ sum = a * idx_sum + b * size\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (!f.has_value() || x.size\
    \ == 0) return x;\n        return {f.value().first * x.idx_sum + f.value().second\
    \ * T(x.size), x.size, x.idx_sum};\n    }\n\n    // Helper for initializing a\
    \ leaf node\n    // Crucial: You MUST pass the 0-based index `idx` during initialization.\n\
    \    static constexpr value_type make(const T& val, long long idx) {\n       \
    \ return {val, 1, T(idx)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_update_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_ap_update_range_sum.hpp
layout: document
title: Range AP Update Range Sum
---

## Overview

An Acted Monoid that supports overwriting a range with an arithmetic progression, alongside range sum queries.

The operator replaces existing elements with $f(i) = a \cdot i + b$, where $i$ is the original global 0-based index of the array element.

### Important Usage Note

Similar to `RangeApAddRangeSum`, the node state (`value_type`) tracks the sum of the indices (`idx_sum`) it covers, enabling $O(1)$ block updates. 

When initializing the leaf nodes, you **must provide the index** of the element to the `make(val, idx)` helper. The `operator_type` relies on `std::optional` to safely designate the "no operation" state.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Overwrite the range [0, 3) with f(i) = 3 * i + 1
    // index 0: 3(0) + 1 = 1
    // index 1: 3(1) + 1 = 4
    // index 2: 3(2) + 1 = 7
    // Array becomes: {1, 4, 7, 40, 50}
    seg.apply(0, 3, std::optional<std::pair<long long, long long>>({3, 1}));

    // Query sum of range [0, 3) -> 1 + 4 + 7 = 12
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
