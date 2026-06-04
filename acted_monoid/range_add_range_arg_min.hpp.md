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
  bundledCode: "#line 1 \"acted_monoid/range_add_range_arg_min.hpp\"\n\n\n\n#line\
    \ 1 \"monoid/arg_min.hpp\"\n\n\n\n#include <limits>\n#include <utility>\n#include\
    \ <functional>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for finding\
    \ the optimal value (minimum by default) and its corresponding index.\n// Ties\
    \ are broken by choosing the smaller index.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct ArgMin {\n    using value_type = std::pair<T,\
    \ int>;\n\n    // The identity element uses the Id value and an invalid index.\n\
    \    static constexpr value_type id() {\n        return {Id, -1};\n    }\n\n \
    \   // Merges two elements based on the Compare functor.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (Compare()(a.first,\
    \ b.first)) return a;\n        if (Compare()(b.first, a.first)) return b;\n  \
    \      return (a.second < b.second) ? a : b;\n    }\n\n    // Helper to create\
    \ a leaf node.\n    static constexpr value_type make(const T& val, int index)\
    \ {\n        return {val, index};\n    }\n};\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 7 \"acted_monoid/range_add_range_arg_min.hpp\"\n\n\
    namespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct RangeAddRangeArgMin {\n    using BaseMonoid\
    \ = m1une::monoid::ArgMin<T, Id, Compare>;\n    using value_type = typename BaseMonoid::value_type;\n\
    \    using operator_type = T;\n\n    // Value Monoid (ArgMin)\n    static constexpr\
    \ value_type id() { return BaseMonoid::id(); }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return BaseMonoid::op(a,\
    \ b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() { return T(0); }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.second == -1) return x; // Do not apply to the identity\
    \ element\n        return {x.first + f, x.second};\n    }\n\n    // Helper for\
    \ initializing a leaf node\n    static constexpr value_type make(const T& val,\
    \ int index) {\n        return BaseMonoid::make(val, index);\n    }\n};\n\n} \
    \ // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\
    \ 1\n\n#include \"../monoid/arg_min.hpp\"\n#include <limits>\n#include <functional>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id =\
    \ std::numeric_limits<T>::max(), typename Compare = std::less<T>>\nstruct RangeAddRangeArgMin\
    \ {\n    using BaseMonoid = m1une::monoid::ArgMin<T, Id, Compare>;\n    using\
    \ value_type = typename BaseMonoid::value_type;\n    using operator_type = T;\n\
    \n    // Value Monoid (ArgMin)\n    static constexpr value_type id() { return\
    \ BaseMonoid::id(); }\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        return BaseMonoid::op(a, b);\n    }\n\n    //\
    \ Operator Monoid (Add)\n    static constexpr operator_type op_id() { return T(0);\
    \ }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        if (x.second == -1) return x; // Do not apply to the identity element\n\
    \        return {x.first + f, x.second};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val, int index) {\n\
    \        return BaseMonoid::make(val, index);\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP\n"
  dependsOn:
  - monoid/arg_min.hpp
  isVerificationFile: false
  path: acted_monoid/range_add_range_arg_min.hpp
  requiredBy: []
  timestamp: '2026-06-04 17:50:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_arg_min.hpp
layout: document
title: Range Add Range ArgMin
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and its **corresponding index** in a range.

Adding a uniform constant to a range shifts all elements by the same amount, meaning the relative ordering remains unchanged. Thus, the index of the minimum (or maximum) element is perfectly preserved after range additions. This is highly useful in sweepline algorithms or resource allocation problems where you need to identify *where* the minimum value is located.

By reusing `m1une::monoid::ArgMin`, this structure resolves ties by prioritizing the smaller index.

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
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Initial min is 4 at index 1 (ties broken by smaller index)
    auto q1 = seg.prod(0, N);
    std::cout << "Min: " << q1.first << ", Index: " << q1.second << "\n"; // Output: Min: 4, Index: 1

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4 at index 3
    auto q2 = seg.prod(0, N);
    std::cout << "Min: " << q2.first << ", Index: " << q2.second << "\n"; // Output: Min: 4, Index: 3

    return 0;
}
```
