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
    \ left_idx;\n    long long right_idx;\n};\n\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct RangeApUpdateRangeMinMax\
    \ {\n    using value_type = RangeApUpdateRangeMinMaxNode<T>;\n    using operator_type\
    \ = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b\n\n  \
    \  // Value Monoid (Min & Max)\n    static constexpr value_type id() {\n     \
    \   return {MinId, MaxId, std::numeric_limits<long long>::max(), std::numeric_limits<long\
    \ long>::lowest()};\n    }\n\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (a.min_val == MinId) return b;\n     \
    \   if (b.min_val == MinId) return a;\n        return {std::min(a.min_val, b.min_val),\
    \ std::max(a.max_val, b.max_val), std::min(a.left_idx, b.left_idx),\n        \
    \        std::max(a.right_idx, b.right_idx)};\n    }\n\n    // Operator Monoid\
    \ (Update)\n    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        // Newer operation (f) completely overwrites the\
    \ older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f.has_value() || x.min_val == MinId) return x;\n\n      \
    \  T a = f.value().first;\n        T b = f.value().second;\n\n        // Evaluate\
    \ the linear function at the boundaries of the segment\n        T val_left = a\
    \ * static_cast<T>(x.left_idx) + b;\n        T val_right = a * static_cast<T>(x.right_idx)\
    \ + b;\n\n        return {std::min(val_left, val_right), std::max(val_left, val_right),\
    \ x.left_idx, x.right_idx};\n    }\n\n    // Helper for initializing a leaf node\n\
    \    // Crucial: You MUST pass the 0-based index `idx` during initialization.\n\
    \    static constexpr value_type make(const T& val, long long idx) {\n       \
    \ return {val, val, idx, idx};\n    }\n};\n\n}  // namespace acted_monoid\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <optional>\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeApUpdateRangeMinMaxNode {\n    T min_val;\n    T max_val;\n\
    \    long long left_idx;\n    long long right_idx;\n};\n\ntemplate <typename T,\
    \ T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>\n\
    struct RangeApUpdateRangeMinMax {\n    using value_type = RangeApUpdateRangeMinMaxNode<T>;\n\
    \    using operator_type = std::optional<std::pair<T, T>>;  // {a, b} for setting\
    \ to a * i + b\n\n    // Value Monoid (Min & Max)\n    static constexpr value_type\
    \ id() {\n        return {MinId, MaxId, std::numeric_limits<long long>::max(),\
    \ std::numeric_limits<long long>::lowest()};\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        if (a.min_val == MinId)\
    \ return b;\n        if (b.min_val == MinId) return a;\n        return {std::min(a.min_val,\
    \ b.min_val), std::max(a.max_val, b.max_val), std::min(a.left_idx, b.left_idx),\n\
    \                std::max(a.right_idx, b.right_idx)};\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() {\n        return\
    \ std::nullopt;\n    }\n\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        // Newer operation (f) completely overwrites\
    \ the older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f.has_value() || x.min_val == MinId) return x;\n\n      \
    \  T a = f.value().first;\n        T b = f.value().second;\n\n        // Evaluate\
    \ the linear function at the boundaries of the segment\n        T val_left = a\
    \ * static_cast<T>(x.left_idx) + b;\n        T val_right = a * static_cast<T>(x.right_idx)\
    \ + b;\n\n        return {std::min(val_left, val_right), std::max(val_left, val_right),\
    \ x.left_idx, x.right_idx};\n    }\n\n    // Helper for initializing a leaf node\n\
    \    // Crucial: You MUST pass the 0-based index `idx` during initialization.\n\
    \    static constexpr value_type make(const T& val, long long idx) {\n       \
    \ return {val, val, idx, idx};\n    }\n};\n\n}  // namespace acted_monoid\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_ap_update_range_min_max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_ap_update_range_min_max.hpp
layout: document
title: Range AP Update Range Min Max
---

## Overview

An exceptionally powerful Acted Monoid that supports overwriting a range with an Arithmetic Progression (AP) and querying both the **minimum** and **maximum** values in a range.

The operator replaces existing elements with a linear function $f(i) = a \cdot i + b$, where $i$ is the original global 0-based index of the array element.

### Mathematical Mechanism

Unlike AP Addition (which cannot support Min/Max queries because the sum of an arbitrary curve and a line is unpredictable), AP **Update** completely overwrites the segment data with a perfectly straight line. 

Because a linear function is monotonic, the minimum and maximum values over any continuous range will **always** strictly occur at the boundary endpoints (either `left_idx` or `right_idx`). 
Therefore, by storing the indices of the segment boundaries in the `value_type`, the new Min/Max can be computed in $O(1)$ time simply by evaluating $f(\text{left\_idx})$ and $f(\text{right\_idx})$.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `MinId`: The identity element for the minimum operation. Defaults to `std::numeric_limits<T>::max()`.
* `MaxId`: The identity element for the maximum operation. Defaults to `std::numeric_limits<T>::lowest()`.

## Data Structure

* `using value_type = RangeApUpdateRangeMinMaxNode<T>;`
  The state maintained in each segment tree node:
  * `min_val`: The minimum scalar within the range.
  * `max_val`: The maximum scalar within the range.
  * `left_idx`: The globally smallest index this node covers.
  * `right_idx`: The globally largest index this node covers.
* `using operator_type = std::optional<std::pair<T, T>>;`
  An optional pair representing the linear coefficient and addend `{a, b}` for the overwrite function $f(i) = a \cdot i + b$.

## Element Creation

When initializing the leaf nodes, you **must provide the global index** of the element to the `make(val, idx)` helper.

### `static constexpr value_type make(const T& val, long long idx)`
* **Parameters:**
  * `val`: The initial scalar value of the element.
  * `idx`: The 0-based global index of the element.
* **Returns:** A fully initialized node where boundaries and min/max values converge on a single element.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_min_max.hpp"
#include <iostream>
#include <vector>
#include <optional>
#include <utility>

using AM = m1une::acted_monoid::RangeApUpdateRangeMinMax<long long>;

int main() {
    std::vector<long long> A = {10, 5, 20, 15, 30};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Overwrite the range [1, 5) with a decreasing arithmetic progression: f(i) = -3 * i + 100
    // index 1: -3(1) + 100 = 97
    // index 2: -3(2) + 100 = 94
    // index 3: -3(3) + 100 = 91
    // index 4: -3(4) + 100 = 88
    // Array conceptually becomes: {10, 97, 94, 91, 88}
    seg.apply(1, 5, std::optional<std::pair<long long, long long>>({-3, 100}));

    // Query Min/Max of range [2, 5) -> Elements: {94, 91, 88}
    auto q = seg.prod(2, 5);
    std::cout << "Min: " << q.min_val << "\n"; // Output: 88
    std::cout << "Max: " << q.max_val << "\n"; // Output: 94

    return 0;
}
```
