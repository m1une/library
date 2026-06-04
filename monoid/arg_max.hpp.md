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
  bundledCode: "#line 1 \"monoid/arg_max.hpp\"\n\n\n\n#line 1 \"monoid/arg_min.hpp\"\
    \n\n\n\n#include <limits>\n#include <utility>\n#include <functional>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the optimal value (minimum\
    \ by default) and its corresponding index.\n// Ties are broken by choosing the\
    \ smaller index.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct ArgMin {\n    using value_type = std::pair<T,\
    \ int>;\n\n    // The identity element uses the Id value and an invalid index.\n\
    \    static constexpr value_type id() {\n        return {Id, -1};\n    }\n\n \
    \   // Merges two elements based on the Compare functor.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (Compare()(a.first,\
    \ b.first)) return a;\n        if (Compare()(b.first, a.first)) return b;\n  \
    \      return (a.second < b.second) ? a : b;\n    }\n\n    // Helper to create\
    \ a leaf node.\n    static constexpr value_type make(const T& val, int index)\
    \ {\n        return {val, index};\n    }\n};\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 7 \"monoid/arg_max.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Monoid for finding the maximum value and its corresponding index.\n\
    // Defined as a type alias of ArgMin using std::greater.\ntemplate <typename T,\
    \ T Id = std::numeric_limits<T>::lowest()>\nusing ArgMax = ArgMin<T, Id, std::greater<T>>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_ARG_MAX_HPP

    #define M1UNE_MONOID_ARG_MAX_HPP 1


    #include "arg_min.hpp"

    #include <limits>

    #include <functional>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum value and its corresponding index.

    // Defined as a type alias of ArgMin using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using ArgMax = ArgMin<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_ARG_MAX_HPP

    '
  dependsOn:
  - monoid/arg_min.hpp
  isVerificationFile: false
  path: monoid/arg_max.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:23:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/arg_max.hpp
layout: document
title: ArgMax Monoid
---

## Overview

A monoid for finding both the maximum value and its index in a range. If there are multiple maximum values, it returns the one with the smallest index.

This is defined as a type alias of `ArgMin` using `std::greater`. For the minimum counterpart, see `monoid/arg_min.hpp`.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/arg_max.hpp"
#include <iostream>
#include <vector>

using ArgMaxM = m1une::monoid::ArgMax<long long>;

int main() {
    std::vector<long long> A = {4, 8, 5, 8, 2};
    int N = A.size();

    std::vector<ArgMaxM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = ArgMaxM::make(A[i], i);
    }

    m1une::data_structure::Segtree<ArgMaxM> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << "Max Value: " << res.first << "\n"; // Output: 8
    std::cout << "Index: " << res.second << "\n";    // Output: 1 (Index 1 is chosen over Index 3)

    return 0;
}
```
