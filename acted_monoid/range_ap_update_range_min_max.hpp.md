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
  bundledCode: "#line 1 \"acted_monoid/range_ap_update_range_min_max.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <limits>\n#include <optional>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeApUpdateRangeMinMaxNode {\n    T min_val;\n    T max_val;\n    long long\
    \ size;\n};\n\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct RangeApUpdateRangeMinMax\
    \ {\n    using value_type = RangeApUpdateRangeMinMaxNode<T>;\n    using operator_type\
    \ = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b\n\n  \
    \  // Value Monoid (Min & Max)\n    static constexpr value_type id() {\n     \
    \   return {MinId, MaxId, 0};\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        if (a.size == 0) return b;\n\
    \        if (b.size == 0) return a;\n        return {std::min(a.min_val, b.min_val),\
    \ std::max(a.max_val, b.max_val), a.size + b.size};\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() {\n        return\
    \ std::nullopt;\n    }\n\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        // Newer operation (f) completely overwrites\
    \ the older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return mapping(f, x, 0);\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x, long long ord) {\n        if (!f.has_value()\
    \ || x.min_val == MinId) return x;\n\n        T a = f.value().first;\n       \
    \ T b = f.value().second;\n        T val_left = a * static_cast<T>(ord) + b;\n\
    \        T val_right = a * static_cast<T>(ord + x.size - 1) + b;\n\n        return\
    \ {std::min(val_left, val_right), std::max(val_left, val_right), x.size};\n  \
    \  }\n\n    static constexpr operator_type op_shift(const operator_type& f, long\
    \ long ord) {\n        if (!f.has_value()) return f;\n        return std::pair<T,\
    \ T>{f.value().first, f.value().second + f.value().first * T(ord)};\n    }\n\n\
    \    static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        if (!f.has_value()) return f;\n        return std::pair<T,\
    \ T>{-f.value().first, f.value().second + f.value().first * T(size - 1)};\n  \
    \  }\n\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <optional>\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeApUpdateRangeMinMaxNode {\n    T min_val;\n    T max_val;\n\
    \    long long size;\n};\n\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct RangeApUpdateRangeMinMax\
    \ {\n    using value_type = RangeApUpdateRangeMinMaxNode<T>;\n    using operator_type\
    \ = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b\n\n  \
    \  // Value Monoid (Min & Max)\n    static constexpr value_type id() {\n     \
    \   return {MinId, MaxId, 0};\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        if (a.size == 0) return b;\n\
    \        if (b.size == 0) return a;\n        return {std::min(a.min_val, b.min_val),\
    \ std::max(a.max_val, b.max_val), a.size + b.size};\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() {\n        return\
    \ std::nullopt;\n    }\n\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        // Newer operation (f) completely overwrites\
    \ the older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return mapping(f, x, 0);\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x, long long ord) {\n        if (!f.has_value()\
    \ || x.min_val == MinId) return x;\n\n        T a = f.value().first;\n       \
    \ T b = f.value().second;\n        T val_left = a * static_cast<T>(ord) + b;\n\
    \        T val_right = a * static_cast<T>(ord + x.size - 1) + b;\n\n        return\
    \ {std::min(val_left, val_right), std::max(val_left, val_right), x.size};\n  \
    \  }\n\n    static constexpr operator_type op_shift(const operator_type& f, long\
    \ long ord) {\n        if (!f.has_value()) return f;\n        return std::pair<T,\
    \ T>{f.value().first, f.value().second + f.value().first * T(ord)};\n    }\n\n\
    \    static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        if (!f.has_value()) return f;\n        return std::pair<T,\
    \ T>{-f.value().first, f.value().second + f.value().first * T(size - 1)};\n  \
    \  }\n\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_update_range_min_max.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:20:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_ap_update_range_min_max.hpp
layout: document
title: Range AP Update Range Min Max
---

## Overview

An acted monoid that overwrites a range with an arithmetic progression and
queries the minimum and maximum values in a range.

The operator replaces existing elements with a linear function $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Mathematical Mechanism

Unlike AP Addition (which cannot support Min/Max queries because the sum of an arbitrary curve and a line is unpredictable), AP **Update** completely overwrites the segment data with a perfectly straight line.

Because a linear function is monotonic, the minimum and maximum values over any continuous range occur at the boundary endpoints. Therefore, by storing the segment `size`, the new Min/Max can be computed in $O(1)$ time by evaluating the local endpoints.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `MinId`: The identity element for the minimum operation. Defaults to `std::numeric_limits<T>::max()`.
* `MaxId`: The identity element for the maximum operation. Defaults to `std::numeric_limits<T>::lowest()`.

## Data Structure

* `using value_type = RangeApUpdateRangeMinMaxNode<T>;`
  The state maintained in each segment tree node:
  * `min_val`: The minimum scalar within the range.
  * `max_val`: The maximum scalar within the range.
  * `size`: The number of elements in the range.
* `using operator_type = std::optional<std::pair<T, T>>;`
  An optional pair representing the linear coefficient and addend `{a, b}` for the overwrite function $f(i) = a \cdot i + b$.

## Element Creation

Leaf nodes are initialized with `make(val)` or by constructing a data structure directly from raw values.

### `static constexpr value_type make(const T& val)`

* **Parameters:**
  * `val`: The initial scalar value of the element.
* **Returns:** A fully initialized single-element node.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_min_max.hpp"
#include <iostream>
#include <vector>
#include <optional>
#include <utility>

using AM = m1une::acted_monoid::RangeApUpdateRangeMinMax<long long>;

int main() {
    std::vector<long long> A = {10, 5, 20, 15, 30};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite the range [1, 5) with f(i) = -3 * i + 100, where i is local to [1, 5)
    // Array conceptually becomes: {10, 100, 97, 94, 91}
    seg.apply(1, 5, std::optional<std::pair<long long, long long>>({-3, 100}));

    // Query Min/Max of range [2, 5) -> Elements: {97, 94, 91}
    auto q = seg.prod(2, 5);
    std::cout << "Min: " << q.min_val << "\n"; // Output: 91
    std::cout << "Max: " << q.max_val << "\n"; // Output: 97

    return 0;
}
```
