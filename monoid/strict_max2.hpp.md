---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/strict_min2.hpp
    title: Strict Min 2 Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/strict_max2.hpp\"\n\n\n\n#include <functional>\n\
    #include <limits>\n\n#line 1 \"monoid/strict_min2.hpp\"\n\n\n\n#line 6 \"monoid/strict_min2.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\ntemplate <typename T>\nstruct StrictOpt2Node\
    \ {\n    T opt1;  // The strictly best value\n    T opt2;  // The strictly second-best\
    \ value\n};\n\n// Monoid for finding the strictly 1st and 2nd optimal (minimum\
    \ by default) values in a range.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct StrictMin2 {\n    using value_type\
    \ = StrictOpt2Node<T>;\n\n    // The identity element has both values set to Id.\n\
    \    static constexpr value_type id() {\n        return {Id, Id};\n    }\n\n \
    \   // Merges two elements, preserving the top 2 strictly unique values.\n   \
    \ static constexpr value_type op(const value_type& a, const value_type& b) {\n\
    \        auto update = [](T& m1, T& m2, T val) {\n            if (val == Id ||\
    \ val == m1 || val == m2) return;\n            if (m1 == Id || Compare()(val,\
    \ m1)) {\n                m2 = m1;\n                m1 = val;\n            } else\
    \ if (m2 == Id || Compare()(val, m2)) {\n                m2 = val;\n         \
    \   }\n        };\n\n        T m1 = Id, m2 = Id;\n        update(m1, m2, a.opt1);\n\
    \        update(m1, m2, a.opt2);\n        update(m1, m2, b.opt1);\n        update(m1,\
    \ m2, b.opt2);\n\n        return {m1, m2};\n    }\n\n    // Helper to securely\
    \ create a leaf node.\n    static constexpr value_type make(const T& val) {\n\
    \        return {val, Id};\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 8 \"monoid/strict_max2.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Monoid for finding the strictly 1st and 2nd maximum values in\
    \ a range.\n// Defined as a type alias of StrictMin2 using std::greater.\ntemplate\
    \ <typename T, T Id = std::numeric_limits<T>::lowest()>\nusing StrictMax2 = StrictMin2<T,\
    \ Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_STRICT_MAX2_HPP

    #define M1UNE_MONOID_STRICT_MAX2_HPP 1


    #include <functional>

    #include <limits>


    #include "monoid/strict_min2.hpp"


    namespace m1une {

    namespace monoid {


    // Monoid for finding the strictly 1st and 2nd maximum values in a range.

    // Defined as a type alias of StrictMin2 using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using StrictMax2 = StrictMin2<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_STRICT_MAX2_HPP

    '
  dependsOn:
  - monoid/strict_min2.hpp
  isVerificationFile: false
  path: monoid/strict_max2.hpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/strict_max2.hpp
layout: document
title: Strict Max 2 Monoid
---

## Overview

A monoid that maintains the strictly largest (`opt1`) and strictly second-largest (`opt2`) values in a contiguous subarray. If all elements in the range are the same, `opt2` will remain the identity element.

This is the maximum counterpart to `monoid/strict_min2.hpp`.

## Example

```cpp
#include "ds/segment_tree/segtree.hpp"
#include "monoid/strict_max2.hpp"
#include <iostream>
#include <vector>

using StrictMax2M = m1une::monoid::StrictMax2<long long>;

int main() {
    std::vector<long long> A = {8, 8, 5, 3, 8, 6};
    int N = A.size();

    std::vector<StrictMax2M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = StrictMax2M::make(A[i]);
    }

    m1une::ds::Segtree<StrictMax2M> seg(init_data);

    auto res = seg.prod(2, 6); // Range: [5, 3, 8, 6]

    std::cout << "1st Max: " << res.opt1 << "\n"; // Output: 8
    std::cout << "2nd Max: " << res.opt2 << "\n"; // Output: 6

    return 0;
}
```
