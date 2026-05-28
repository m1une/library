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
  bundledCode: "#line 1 \"monoid/affine.hpp\"\n\n\n\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for affine transformations f(x) = ax\
    \ + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct Affine\
    \ {\n    using value_type = std::pair<T, T>;\n\n    // The identity transformation\
    \ is f(x) = 1*x + 0.\n    static constexpr value_type id() { \n        return\
    \ {T(1), T(0)}; \n    }\n\n    // Composes two affine transformations.\n    //\
    \ f(g(x)) where f = a, g = b.\n    // a.first * (b.first * x + b.second) + a.second\n\
    \    // = (a.first * b.first) * x + (a.first * b.second + a.second)\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) { \n     \
    \   return {a.first * b.first, a.first * b.second + a.second}; \n    }\n};\n\n\
    }  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_AFFINE_HPP\n#define M1UNE_MONOID_AFFINE_HPP 1\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for affine transformations\
    \ f(x) = ax + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct\
    \ Affine {\n    using value_type = std::pair<T, T>;\n\n    // The identity transformation\
    \ is f(x) = 1*x + 0.\n    static constexpr value_type id() { \n        return\
    \ {T(1), T(0)}; \n    }\n\n    // Composes two affine transformations.\n    //\
    \ f(g(x)) where f = a, g = b.\n    // a.first * (b.first * x + b.second) + a.second\n\
    \    // = (a.first * b.first) * x + (a.first * b.second + a.second)\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) { \n     \
    \   return {a.first * b.first, a.first * b.second + a.second}; \n    }\n};\n\n\
    }  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_AFFINE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/affine.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:38:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/affine.hpp
layout: document
title: Affine Monoid
---

## Overview

A monoid for composing affine transformations, expressed as $f(x) = ax + b$. 
The underlying `value_type` is `std::pair<T, T>`, where `first` represents $a$ (the multiplier) and `second` represents $b$ (the addend).

This is particularly useful when you have a sequence of operations like "multiply by $X$, then add $Y$" and you want to find the composite function of a range.

## Initialization

To initialize a single operation $f(x) = ax + b$, create a pair `{a, b}`.

* **Add $C$:** Use `{1, C}` (since $f(x) = 1 \cdot x + C$)
* **Multiply by $C$:** Use `{C, 0}` (since $f(x) = C \cdot x + 0$)
* **Assign $C$:** Use `{0, C}` (since $f(x) = 0 \cdot x + C = C$)

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/affine.hpp"
#include <iostream>

using AffineM = m1une::monoid::Affine<long long>;

int main() {
    // Operations:
    // 0: f(x) = 2x + 3
    // 1: f(x) = 1x + 5 (Add 5)
    // 2: f(x) = 3x + 0 (Multiply by 3)
    
    std::vector<std::pair<long long, long long>> ops = {
        {2, 3}, {1, 5}, {3, 0}
    };

    m1une::data_structure::Segtree<AffineM> seg(ops);

    // Get the composite function for the range [0, 2)
    // f(x) = 1 * (2x + 3) + 5 = 2x + 8
    auto [a, b] = seg.prod(0, 2);
    std::cout << "f(x) = " << a << "x + " << b << "\n"; // Output: 2x + 8

    return 0;
}
```
