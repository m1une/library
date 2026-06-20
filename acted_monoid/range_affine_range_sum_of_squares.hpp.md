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
  bundledCode: "#line 1 \"acted_monoid/range_affine_range_sum_of_squares.hpp\"\n\n\
    \n\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAffineRangeSumOfSquaresNode {\n    T sum_sq;\n   \
    \ T sum;\n    long long size;\n};\n\n// Designed to work with standard scalars\
    \ or Modint types\ntemplate <typename T>\nstruct RangeAffineRangeSumOfSquares\
    \ {\n    using value_type = RangeAffineRangeSumOfSquaresNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;  // {a, b} for f(x) = a*x + b\n\n    // Value Monoid (Sum\
    \ of Squares, Sum, Size)\n    static constexpr value_type id() {\n        return\
    \ {T(0), T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum_sq + b.sum_sq, a.sum + b.sum,\
    \ a.size + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n  \
    \  // f(x) = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1\
    \ = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n \
    \       return {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first * g.first,\
    \ f.first * g.second + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i\
    \ + b)^2 = a^2 \\sum x_i^2 + 2ab \\sum x_i + b^2 * size\n    // \\sum (a*x_i +\
    \ b)   = a \\sum x_i + b * size\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.size == 0) return x;\n\
    \        T a = f.first;\n        T b = f.second;\n        T sz = static_cast<T>(x.size);\n\
    \n        return {a * a * x.sum_sq + T(2) * a * b * x.sum + b * b * sz, a * x.sum\
    \ + b * sz, x.size};\n    }\n\n    // Helper for initializing a leaf node\n  \
    \  static constexpr value_type make(const T& val) {\n        return {val * val,\
    \ val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP\n#define\
    \ M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP 1\n\n#include <utility>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeAffineRangeSumOfSquaresNode {\n    T sum_sq;\n    T sum;\n    long long\
    \ size;\n};\n\n// Designed to work with standard scalars or Modint types\ntemplate\
    \ <typename T>\nstruct RangeAffineRangeSumOfSquares {\n    using value_type =\
    \ RangeAffineRangeSumOfSquaresNode<T>;\n    using operator_type = std::pair<T,\
    \ T>;  // {a, b} for f(x) = a*x + b\n\n    // Value Monoid (Sum of Squares, Sum,\
    \ Size)\n    static constexpr value_type id() {\n        return {T(0), T(0), 0};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum_sq + b.sum_sq, a.sum + b.sum, a.size + b.size};\n\
    \    }\n\n    // Operator Monoid (Affine Composition)\n    // f(x) = a1*x + b1,\
    \ g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x + (a1*b2\
    \ + b1)\n    static constexpr operator_type op_id() {\n        return {T(1), T(0)};\n\
    \    }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return {f.first * g.first, f.first * g.second +\
    \ f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b)^2 = a^2 \\sum\
    \ x_i^2 + 2ab \\sum x_i + b^2 * size\n    // \\sum (a*x_i + b)   = a \\sum x_i\
    \ + b * size\n    static constexpr value_type mapping(const operator_type& f,\
    \ const value_type& x) {\n        if (x.size == 0) return x;\n        T a = f.first;\n\
    \        T b = f.second;\n        T sz = static_cast<T>(x.size);\n\n        return\
    \ {a * a * x.sum_sq + T(2) * a * b * x.sum + b * b * sz, a * x.sum + b * sz, x.size};\n\
    \    }\n\n    // Helper for initializing a leaf node\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val * val, val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_affine_range_sum_of_squares.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_affine_range_sum_of_squares.hpp
layout: document
title: Range Affine Range Sum of Squares
---

## Overview

An Acted Monoid representing Range Affine Transformations ($f(x) = ax + b$) and Range Sum of Squares queries. This is an incredibly powerful structure for calculating expected values, variances, or quadratic constraints over dynamic arrays in $O(\log N)$ time.

### Mathematical Mechanism

When an affine transformation $f(x) = ax + b$ is applied to a range, the new sum of squares is expanded algebraically:
$$\sum (ax_i + b)^2 = a^2 \left(\sum x_i^2\right) + 2ab \left(\sum x_i\right) + b^2 \cdot \text{size}$$

To support this $O(1)$ mapping operation, the node state (`value_type`) tracks three properties of the segment: the sum of squares (`sum_sq`), the standard sum (`sum`), and the `size`.

## Template Parameters

* `T`: The underlying numerical type. This is often used with a modular arithmetic struct (e.g., `Modint`) to prevent overflow, but standard `long long` works if numbers are small.

## Operator Details

The `operator_type` is an `std::pair<T, T>` representing `{a, b}` in $f(x) = ax + b$.
This allows you to perform multiple types of range operations seamlessly:
* **Range Add $C$:** Use `{1, C}`
* **Range Multiply $C$:** Use `{C, 0}`
* **Range Assign/Overwrite $C$:** Use `{0, C}` (the $a=0$ coefficient completely zeroes out the old sum, effectively replacing the entire segment).

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_sum_of_squares.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeSumOfSquares<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Initial sum of squares for [0, 3): 1^2 + 2^2 + 3^2 = 14
    std::cout << "Initial Sum_Sq: " << seg.prod(0, 3).sum_sq << "\n"; // Output: 14

    // Apply affine function: f(x) = 2x + 1 to range [0, 2)
    // 1 -> 2(1)+1 = 3
    // 2 -> 2(2)+1 = 5
    // Array becomes: {3, 5, 3}
    seg.apply(0, 2, {2, 1});

    // New sum of squares for [0, 3): 3^2 + 5^2 + 3^2 = 9 + 25 + 9 = 43
    std::cout << "Updated Sum_Sq: " << seg.prod(0, 3).sum_sq << "\n"; // Output: 43

    return 0;
}
```
