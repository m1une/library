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
  bundledCode: "#line 1 \"acted_monoid/range_xor_range_sum.hpp\"\n\n\n\n#include <array>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, int BITS\
    \ = 30>\nstruct RangeXorRangeSumNode {\n    T sum;\n    std::array<int, BITS>\
    \ bit_count;\n    long long size;\n};\n\n// Acted Monoid for Range XOR updates\
    \ and Range Sum queries.\n// BITS defines the maximum bit length (default 30 for\
    \ standard integers, use 60 for long long).\ntemplate <typename T, int BITS =\
    \ 30>\nstruct RangeXorRangeSum {\n    using value_type = RangeXorRangeSumNode<T,\
    \ BITS>;\n    using operator_type = T;\n\n    static constexpr value_type id()\
    \ {\n        value_type res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n\
    \        res.size = 0;\n        return res;\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res;\n  \
    \      res.sum = a.sum + b.sum;\n        res.size = a.size + b.size;\n       \
    \ for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i]\
    \ + b.bit_count[i];\n        }\n        return res;\n    }\n\n    static constexpr\
    \ operator_type op_id() {\n        return T(0);\n    }\n\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f ^ g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (f == T(0) || x.size == 0) return x;\n\
    \        value_type res = x;\n        res.sum = T(0);\n        for (int i = 0;\
    \ i < BITS; ++i) {\n            if ((f >> i) & 1) {\n                res.bit_count[i]\
    \ = x.size - x.bit_count[i];\n            }\n            res.sum += static_cast<T>(res.bit_count[i])\
    \ * (T(1) << i);\n        }\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        value_type res;\n        res.sum =\
    \ val;\n        res.size = 1;\n        for (int i = 0; i < BITS; ++i) {\n    \
    \        res.bit_count[i] = ((val >> i) & 1) ? 1 : 0;\n        }\n        return\
    \ res;\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP\
    \ 1\n\n#include <array>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T, int BITS = 30>\nstruct RangeXorRangeSumNode {\n    T sum;\n   \
    \ std::array<int, BITS> bit_count;\n    long long size;\n};\n\n// Acted Monoid\
    \ for Range XOR updates and Range Sum queries.\n// BITS defines the maximum bit\
    \ length (default 30 for standard integers, use 60 for long long).\ntemplate <typename\
    \ T, int BITS = 30>\nstruct RangeXorRangeSum {\n    using value_type = RangeXorRangeSumNode<T,\
    \ BITS>;\n    using operator_type = T;\n\n    static constexpr value_type id()\
    \ {\n        value_type res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n\
    \        res.size = 0;\n        return res;\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res;\n  \
    \      res.sum = a.sum + b.sum;\n        res.size = a.size + b.size;\n       \
    \ for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i]\
    \ + b.bit_count[i];\n        }\n        return res;\n    }\n\n    static constexpr\
    \ operator_type op_id() {\n        return T(0);\n    }\n\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f ^ g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (f == T(0) || x.size == 0) return x;\n\
    \        value_type res = x;\n        res.sum = T(0);\n        for (int i = 0;\
    \ i < BITS; ++i) {\n            if ((f >> i) & 1) {\n                res.bit_count[i]\
    \ = x.size - x.bit_count[i];\n            }\n            res.sum += static_cast<T>(res.bit_count[i])\
    \ * (T(1) << i);\n        }\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        value_type res;\n        res.sum =\
    \ val;\n        res.size = 1;\n        for (int i = 0; i < BITS; ++i) {\n    \
    \        res.bit_count[i] = ((val >> i) & 1) ? 1 : 0;\n        }\n        return\
    \ res;\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_xor_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_xor_range_sum.hpp
layout: document
title: Range XOR Range Sum
---

## Overview

An Acted Monoid representing Range Bitwise XOR operations and Range Sum queries.

### Mathematical Mechanism

Because the XOR operation acts bit-by-bit, it does not distribute directly over addition ($C \oplus (A + B) \neq (C \oplus A) + (C \oplus B)$). To compute the new sum of a range after XORing by a value $f$, the segment tree node must independently track **how many times each bit is set** in its range.

If the $i$-th bit of $f$ is set, the new number of set bits at position $i$ within the segment becomes `size - old_bit_count`. The total sum is then re-evaluated based on the new bit counts.

## Template Parameters

* `T`: The underlying numerical type (e.g., `long long`).
* `BITS`: The maximum bit length to track. Defaults to `30` (sufficient for standard $10^9$ integers). If operating on `long long` values up to $10^{18}$, you should explicitly set this to `60`.

## Initialization

When initializing a Lazy Segment Tree, you must use the `make(val)` helper function so that the leaf nodes correctly initialize their internal bit count arrays and size.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_xor_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeXorRangeSum<long long, 30>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Get the sum of range [0, 4) -> 1 + 2 + 3 + 4 = 10
    std::cout << "Initial Sum: " << seg.prod(0, 4).sum << "\n";

    // XOR the range [0, 4) with 7
    // 1^7 = 6, 2^7 = 5, 3^7 = 4, 4^7 = 3
    // Array becomes: {6, 5, 4, 3, 5}
    seg.apply(0, 4, 7);

    // Get the new sum of range [0, 4) -> 6 + 5 + 4 + 3 = 18
    std::cout << "Updated Sum: " << seg.prod(0, 4).sum << "\n";

    return 0;
}
```
