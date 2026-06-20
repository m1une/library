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
    \    long long size;\n    T ord_sum;\n};\n\ntemplate <typename T>\nstruct RangeApUpdateRangeSum\
    \ {\n    using value_type = RangeApUpdateRangeSumNode<T>;\n    using operator_type\
    \ = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b\n\n  \
    \  // Value Monoid (Sum)\n    static constexpr value_type id() {\n        return\
    \ {T(0), 0, T(0)};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size, a.ord_sum\
    \ + b.ord_sum + T(a.size) * T(b.size)};\n    }\n\n    // Operator Monoid (Update)\n\
    \    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        // Prioritize the newer operation (f) over the\
    \ older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        return\
    \ mapping(f, x, 0);\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x, long long ord) {\n        if (!f.has_value() || x.size\
    \ == 0) return x;\n        return {f.value().first * (x.ord_sum + T(ord) * T(x.size))\
    \ + f.value().second * T(x.size), x.size,\n                x.ord_sum};\n    }\n\
    \n    static constexpr operator_type op_shift(const operator_type& f, long long\
    \ ord) {\n        if (!f.has_value()) return f;\n        return std::pair<T, T>{f.value().first,\
    \ f.value().second + f.value().first * T(ord)};\n    }\n\n    static constexpr\
    \ operator_type op_reverse(const operator_type& f, long long size) {\n       \
    \ if (!f.has_value()) return f;\n        return std::pair<T, T>{-f.value().first,\
    \ f.value().second + f.value().first * T(size - 1)};\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1, T(0)};\n    }\n};\n\
    \n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\
    \ 1\n\n#include <optional>\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T>\nstruct RangeApUpdateRangeSumNode {\n\
    \    T sum;\n    long long size;\n    T ord_sum;\n};\n\ntemplate <typename T>\n\
    struct RangeApUpdateRangeSum {\n    using value_type = RangeApUpdateRangeSumNode<T>;\n\
    \    using operator_type = std::optional<std::pair<T, T>>;  // {a, b} for setting\
    \ to a * i + b\n\n    // Value Monoid (Sum)\n    static constexpr value_type id()\
    \ {\n        return {T(0), 0, T(0)};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size, a.ord_sum + b.ord_sum + T(a.size) * T(b.size)};\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() {\n        return\
    \ std::nullopt;\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        // Prioritize the newer operation (f)\
    \ over the older one (g)\n        return f.has_value() ? f : g;\n    }\n\n   \
    \ static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        return mapping(f, x, 0);\n    }\n\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x, long long ord) {\n    \
    \    if (!f.has_value() || x.size == 0) return x;\n        return {f.value().first\
    \ * (x.ord_sum + T(ord) * T(x.size)) + f.value().second * T(x.size), x.size,\n\
    \                x.ord_sum};\n    }\n\n    static constexpr operator_type op_shift(const\
    \ operator_type& f, long long ord) {\n        if (!f.has_value()) return f;\n\
    \        return std::pair<T, T>{f.value().first, f.value().second + f.value().first\
    \ * T(ord)};\n    }\n\n    static constexpr operator_type op_reverse(const operator_type&\
    \ f, long long size) {\n        if (!f.has_value()) return f;\n        return\
    \ std::pair<T, T>{-f.value().first, f.value().second + f.value().first * T(size\
    \ - 1)};\n    }\n\n    static constexpr value_type make(const T& val) {\n    \
    \    return {val, 1, T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_update_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:20:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_ap_update_range_sum.hpp
layout: document
title: Range AP Update Range Sum
---

## Overview

An Acted Monoid that supports overwriting a range with an arithmetic progression, alongside range sum queries.

The operator replaces existing elements with $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Important Usage Note

Similar to `RangeApAddRangeSum`, the node state (`value_type`) tracks `size` and the sum of relative orders (`ord_sum`), enabling $O(1)$ block updates.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`. The `operator_type` relies on `std::optional` to safely designate the "no operation" state.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite the range [0, 3) with f(i) = 3 * i + 1, where i is local to [0, 3)
    // Array becomes: {1, 4, 7, 40, 50}
    seg.apply(0, 3, std::optional<std::pair<long long, long long>>({3, 1}));

    // Query sum of range [0, 3) -> 1 + 4 + 7 = 12
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
