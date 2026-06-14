---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/arg_min.hpp
    title: ArgMin Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_arg_min.hpp\"\n\n\n\n#include\
    \ <functional>\n#include <limits>\n\n#line 1 \"monoid/arg_min.hpp\"\n\n\n\n#line\
    \ 6 \"monoid/arg_min.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\ntemplate\
    \ <typename T>\nstruct ArgMinNode {\n    T value;\n    long long size;\n    long\
    \ long ord;\n};\n\n// Monoid for finding the optimal value (minimum by default)\
    \ and its relative order.\n// Ties are broken by choosing the earlier element.\n\
    template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare =\
    \ std::less<T>>\nstruct ArgMin {\n    using value_type = ArgMinNode<T>;\n\n  \
    \  static constexpr value_type id() {\n        return {Id, 0, -1};\n    }\n\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        if (a.size == 0) return b;\n        if (b.size == 0) return a;\n\
    \        long long size = a.size + b.size;\n        if (Compare()(a.value, b.value))\
    \ return {a.value, size, a.ord};\n        if (Compare()(b.value, a.value)) return\
    \ {b.value, size, b.ord + a.size};\n        return {a.value, size, a.ord};\n \
    \   }\n\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1, 0};\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\
    \n#line 8 \"acted_monoid/range_add_range_arg_min.hpp\"\n\nnamespace m1une {\n\
    namespace acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct RangeAddRangeArgMin {\n    using BaseMonoid\
    \ = m1une::monoid::ArgMin<T, Id, Compare>;\n    using value_type = typename BaseMonoid::value_type;\n\
    \    using operator_type = T;\n\n    // Value Monoid (ArgMin)\n    static constexpr\
    \ value_type id() {\n        return BaseMonoid::id();\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return BaseMonoid::op(a,\
    \ b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() {\n        return T(0);\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (x.size == 0) return x;\n        return\
    \ {x.value + f, x.size, x.ord};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return BaseMonoid::make(val);\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\
    \ 1\n\n#include <functional>\n#include <limits>\n\n#include \"../monoid/arg_min.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id\
    \ = std::numeric_limits<T>::max(), typename Compare = std::less<T>>\nstruct RangeAddRangeArgMin\
    \ {\n    using BaseMonoid = m1une::monoid::ArgMin<T, Id, Compare>;\n    using\
    \ value_type = typename BaseMonoid::value_type;\n    using operator_type = T;\n\
    \n    // Value Monoid (ArgMin)\n    static constexpr value_type id() {\n     \
    \   return BaseMonoid::id();\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return BaseMonoid::op(a, b);\n\
    \    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return T(0);\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (x.size == 0) return x;\n        return\
    \ {x.value + f, x.size, x.ord};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return BaseMonoid::make(val);\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\n"
  dependsOn:
  - monoid/arg_min.hpp
  isVerificationFile: false
  path: acted_monoid/range_add_range_arg_min.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:20:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_arg_min.hpp
layout: document
title: Range Add Range ArgMin
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and its **relative order** in a range.

Adding a uniform constant to a range shifts all elements by the same amount, meaning the relative ordering remains unchanged.

By reusing `m1une::monoid::ArgMin`, this structure resolves ties by prioritizing the earlier order.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`. To build a **Range Add Range ArgMax**, simply pass `std::greater<T>`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_arg_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeArgMin<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    m1une::data_structure::LazySegtree<AM> seg(A);

    // Initial min is 4 at order 1 (ties broken by earlier order)
    auto q1 = seg.prod(0, A.size());
    std::cout << "Min: " << q1.value << ", Order: " << q1.ord << "\n"; // Output: Min: 4, Order: 1

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4 at order 3
    auto q2 = seg.prod(0, A.size());
    std::cout << "Min: " << q2.value << ", Order: " << q2.ord << "\n"; // Output: Min: 4, Order: 3

    return 0;
}
```
