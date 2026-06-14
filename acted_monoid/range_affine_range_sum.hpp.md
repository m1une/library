---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dual_segtree.test.cpp
    title: verify/data_structure/dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_segtree.test.cpp
    title: verify/data_structure/lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n};\n\n\
    // Designed to accept Modint or similar types as T\ntemplate <typename T>\nstruct\
    \ RangeAffineRangeSum {\n    using value_type = RangeAffineRangeSumNode<T>;\n\
    \    using operator_type = std::pair<T, T>;  // {a, b} for ax + b\n\n    // Value\
    \ Monoid\n    static constexpr value_type id() {\n        return {T(0), 0};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n\n    // Operator\
    \ Monoid (Affine Composition)\n    // f(x) = a1*x + b1, g(x) = a2*x + b2\n   \
    \ // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr\
    \ operator_type op_id() {\n        return {T(1), T(0)};\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return {f.first * g.first, f.first * g.second + f.second};\n    }\n\n \
    \   // Mapping\n    // \\sum (a*x_i + b) = a * \\sum x_i + b * size\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return {f.first * x.sum + f.second * T(x.size), x.size};\n    }\n\n \
    \   // Helper for initializing a leaf node\n    static constexpr value_type make(const\
    \ T& val) {\n        return {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\
    \ 1\n\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n\
    };\n\n// Designed to accept Modint or similar types as T\ntemplate <typename T>\n\
    struct RangeAffineRangeSum {\n    using value_type = RangeAffineRangeSumNode<T>;\n\
    \    using operator_type = std::pair<T, T>;  // {a, b} for ax + b\n\n    // Value\
    \ Monoid\n    static constexpr value_type id() {\n        return {T(0), 0};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n\n    // Operator\
    \ Monoid (Affine Composition)\n    // f(x) = a1*x + b1, g(x) = a2*x + b2\n   \
    \ // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr\
    \ operator_type op_id() {\n        return {T(1), T(0)};\n    }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return {f.first * g.first, f.first * g.second + f.second};\n    }\n\n \
    \   // Mapping\n    // \\sum (a*x_i + b) = a * \\sum x_i + b * size\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return {f.first * x.sum + f.second * T(x.size), x.size};\n    }\n\n \
    \   // Helper for initializing a leaf node\n    static constexpr value_type make(const\
    \ T& val) {\n        return {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_affine_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/dual_segtree.test.cpp
  - verify/data_structure/lazy_segtree.test.cpp
documentation_of: acted_monoid/range_affine_range_sum.hpp
layout: document
title: Range Affine Range Sum
---

## Overview

An Acted Monoid representing Range Affine Transformations ($f(x) = ax + b$) and Range Sum queries. It is commonly used with modular arithmetic (`Modint`) or standard scalar types.

### Important Usage Note

When applying an affine transformation $f(x) = ax + b$ to a range of elements, the new sum becomes $a \times \text{sum} + b \times \text{size}$. Therefore, the `value_type` must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAffineRangeSumNode<T>`, which holds both the `sum` and the `size`.

When initializing a Lazy Segment Tree, you must initialize the leaf nodes with `size = 1`. Always use the helper function `make(val)` for this purpose.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeSum<long long>;

int main() {
    int N = 3;
    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        // Initialize each leaf with the value and size = 1
        init_nodes[i] = AM::make(i + 1); // Array: {1, 2, 3}
    }

    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Apply f(x) = 2x + 3 to range [0, 2) 
    // Elements become: (2*1 + 3) = 5, and (2*2 + 3) = 7 -> Array: {5, 7, 3}
    seg.apply(0, 2, {2, 3});

    // Get the sum of range [0, 3) -> 5 + 7 + 3 = 15
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
