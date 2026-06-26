---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/longest_true.hpp
    title: Longest True Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_update_range_longest_true.hpp\"\n\n\n\
    \n#include <optional>\n\n#line 1 \"monoid/longest_true.hpp\"\n\n\n\n#include <algorithm>\n\
    \nnamespace m1une {\nnamespace monoid {\n\nstruct LongestTrueNode {\n    int len;\n\
    \    int max_len;\n    int l_len;\n    int r_len;\n};\n\n// Monoid for finding\
    \ the maximum length of a contiguous subarray\n// where all elements satisfy a\
    \ certain condition (i.e., are \"true\").\nstruct LongestTrue {\n    using value_type\
    \ = LongestTrueNode;\n\n    // The identity element represents an empty array.\n\
    \    static constexpr value_type id() {\n        return {0, 0, 0, 0};\n    }\n\
    \n    // Merges two segments.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (a.len == 0) return b;\n        if (b.len\
    \ == 0) return a;\n\n        value_type res;\n        res.len = a.len + b.len;\n\
    \        res.max_len = std::max({a.max_len, b.max_len, a.r_len + b.l_len});\n\n\
    \        res.l_len = a.l_len;\n        if (a.len == a.l_len) res.l_len += b.l_len;\n\
    \n        res.r_len = b.r_len;\n        if (b.len == b.r_len) res.r_len += a.r_len;\n\
    \n        return res;\n    }\n\n    // Helper to securely create a leaf node from\
    \ a boolean condition.\n    static constexpr value_type make(bool val) {\n   \
    \     return {1, val ? 1 : 0, val ? 1 : 0, val ? 1 : 0};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n#line 7 \"acted_monoid/range_update_range_longest_true.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\nstruct RangeUpdateRangeLongestTrue\
    \ {\n    using BaseMonoid = m1une::monoid::LongestTrue;\n    using value_type\
    \ = typename BaseMonoid::value_type;\n    using operator_type = std::optional<bool>;\n\
    \n    // Value Monoid\n    static constexpr value_type id() {\n        return\
    \ BaseMonoid::id();\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return BaseMonoid::op(a, b);\n    }\n\n \
    \   // Operator Monoid (Update/Overwrite)\n    static constexpr operator_type\
    \ op_id() {\n        return std::nullopt;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f.has_value()\
    \ ? f : g;\n    }\n\n    // Mapping\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (!f.has_value()) return\
    \ x;\n        bool v = f.value();\n\n        // If updating to 'true', the entire\
    \ length satisfies the condition.\n        // If updating to 'false', zero elements\
    \ satisfy the condition.\n        return {x.len, v ? x.len : 0, v ? x.len : 0,\
    \ v ? x.len : 0};\n    }\n\n    // Helper for initializing a leaf node\n    static\
    \ constexpr value_type make(bool val) {\n        return BaseMonoid::make(val);\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP\
    \ 1\n\n#include <optional>\n\n#include \"../monoid/longest_true.hpp\"\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\nstruct RangeUpdateRangeLongestTrue {\n\
    \    using BaseMonoid = m1une::monoid::LongestTrue;\n    using value_type = typename\
    \ BaseMonoid::value_type;\n    using operator_type = std::optional<bool>;\n\n\
    \    // Value Monoid\n    static constexpr value_type id() {\n        return BaseMonoid::id();\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return BaseMonoid::op(a, b);\n    }\n\n    // Operator Monoid\
    \ (Update/Overwrite)\n    static constexpr operator_type op_id() {\n        return\
    \ std::nullopt;\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return f.has_value() ? f : g;\n    }\n\
    \n    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value()) return x;\n        bool\
    \ v = f.value();\n\n        // If updating to 'true', the entire length satisfies\
    \ the condition.\n        // If updating to 'false', zero elements satisfy the\
    \ condition.\n        return {x.len, v ? x.len : 0, v ? x.len : 0, v ? x.len :\
    \ 0};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(bool val) {\n        return BaseMonoid::make(val);\n    }\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP\n"
  dependsOn:
  - monoid/longest_true.hpp
  isVerificationFile: false
  path: acted_monoid/range_update_range_longest_true.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_update_range_longest_true.hpp
layout: document
title: Range Update Range Longest True
---

## Overview

An Acted Monoid designed to solve "Hotel Queries" or contiguous memory allocation problems. It supports range overwrite operations (setting a block to all `true` or all `false`) and queries the **maximum contiguous length** of `true` values in a range.

Because updating an entire segment to `true` simply makes the contiguous length equal to the segment's total length (and updating to `false` makes it `0`), the mapping operation executes in $O(1)$ time by leveraging the `m1une::monoid::LongestTrueNode`.

## Data Structure

* `using value_type = m1une::monoid::LongestTrueNode;`
  The state maintained in each segment tree node:
  * `len`: Total length of the segment.
  * `max_len`: The longest contiguous block of `true`.
  * `l_len`: The length of the contiguous `true` block starting from the left edge.
  * `r_len`: The length of the contiguous `true` block starting from the right edge.
* `using operator_type = std::optional<bool>;`
  An optional boolean representing the overwrite operation. `std::nullopt` represents the identity operation.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_longest_true.hpp"
#include <iostream>
#include <vector>
#include <optional>

using AM = m1une::acted_monoid::RangeUpdateRangeLongestTrue;

int main() {
    // 1 implies the seat is empty (true), 0 implies occupied (false)
    std::vector<bool> A = {true, false, true, true, false, true};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Initial longest block of empty seats is 2 (indices 2 to 3)
    std::cout << "Max empty block: " << seg.all_prod().max_len << "\n"; // Output: 2

    // Free up seats in range [4, 6) -> {true, false, true, true, true, true}
    seg.apply(4, 6, std::optional<bool>(true));

    // The new longest contiguous block of empty seats is now 4 (indices 2 to 5)
    std::cout << "Max empty block: " << seg.all_prod().max_len << "\n"; // Output: 4

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
