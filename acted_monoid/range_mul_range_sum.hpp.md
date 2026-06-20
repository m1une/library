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
  bundledCode: "#line 1 \"acted_monoid/range_mul_range_sum.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\n// Acted Monoid for Range Multiplication\
    \ and Range Sum queries.\n// Operates natively on scalars or Modint classes without\
    \ needing to track segment size.\ntemplate <typename T>\nstruct RangeMulRangeSum\
    \ {\n    using value_type = T;\n    using operator_type = T;\n\n    // Value Monoid\
    \ (Sum)\n    static constexpr value_type id() {\n        return T(0);\n    }\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        return a + b;\n    }\n\n    // Operator Monoid (Multiply)\n    static\
    \ constexpr operator_type op_id() {\n        return T(1);\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f * g;\n    }\n\n    // Mapping: Distribution Property ( f * (a+b)\
    \ = f*a + f*b )\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return f * x;\n    }\n\n    // Helper for\
    \ initializing a leaf node\n    static constexpr value_type make(const T& val)\
    \ {\n        return val;\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Acted Monoid for Range\
    \ Multiplication and Range Sum queries.\n// Operates natively on scalars or Modint\
    \ classes without needing to track segment size.\ntemplate <typename T>\nstruct\
    \ RangeMulRangeSum {\n    using value_type = T;\n    using operator_type = T;\n\
    \n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n        return\
    \ T(0);\n    }\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        return a + b;\n    }\n\n    // Operator Monoid (Multiply)\n\
    \    static constexpr operator_type op_id() {\n        return T(1);\n    }\n \
    \   static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f * g;\n    }\n\n    // Mapping: Distribution Property\
    \ ( f * (a+b) = f*a + f*b )\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return f * x;\n    }\n\n    // Helper for\
    \ initializing a leaf node\n    static constexpr value_type make(const T& val)\
    \ {\n        return val;\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_mul_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_mul_range_sum.hpp
layout: document
title: Range Multiply Range Sum
---

## Overview

An Acted Monoid representing Range Multiplication operations and Range Sum queries.

Unlike Range Addition or Range Affine transformations, Range Multiplication distributes perfectly over addition: $C \times (A + B) = C \cdot A + C \cdot B$. Because of this mathematical property, the `value_type` does **not** need to store the `size` of the segment, making this monoid lighter in memory and faster to compute than the full `RangeAffineRangeSum`.

## Template Parameters

* `T`: The underlying numerical type. It is strongly recommended to use a modular arithmetic struct (e.g., `Modint`) to prevent overflow, as repeated multiplications grow exponentially.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_mul_range_sum.hpp"
#include <iostream>
#include <vector>

// Assuming a modular arithmetic type or standard long long for small bounds
using AM = m1une::acted_monoid::RangeMulRangeSum<long long>;

int main() {
    std::vector<long long> A = {2, 3, 4, 1};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        // Initializes leaf node
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Sum of range [0, 3) -> 2 + 3 + 4 = 9
    std::cout << "Initial Sum: " << seg.prod(0, 3) << "\n";

    // Multiply range [0, 2) by 5
    // Array becomes: {10, 15, 4, 1}
    seg.apply(0, 2, 5);

    // Sum of range [0, 3) -> 10 + 15 + 4 = 29
    std::cout << "Updated Sum: " << seg.prod(0, 3) << "\n";

    return 0;
}
```
