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
  bundledCode: "#line 1 \"monoid/wrapper.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Wrapper struct to generate a Monoid using Non-Type Template Parameters\
    \ (NTTP).\n// Useful for quickly defining monoids using custom functions or constexpr\
    \ lambdas during contests.\ntemplate <typename T, auto Op, auto Id>\nstruct Wrapper\
    \ {\n    using value_type = T;\n\n    // Returns the identity element by invoking\
    \ the provided `Id` function.\n    static constexpr T id() {\n        return Id();\n\
    \    }\n\n    // Returns the result of the binary operation by invoking the provided\
    \ `Op` function.\n    static constexpr T op(const T& a, const T& b) {\n      \
    \  return Op(a, b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MONOID_WRAPPER_HPP\n#define M1UNE_MONOID_WRAPPER_HPP 1\n\n\
    namespace m1une {\nnamespace monoid {\n\n// Wrapper struct to generate a Monoid\
    \ using Non-Type Template Parameters (NTTP).\n// Useful for quickly defining monoids\
    \ using custom functions or constexpr lambdas during contests.\ntemplate <typename\
    \ T, auto Op, auto Id>\nstruct Wrapper {\n    using value_type = T;\n\n    //\
    \ Returns the identity element by invoking the provided `Id` function.\n    static\
    \ constexpr T id() {\n        return Id();\n    }\n\n    // Returns the result\
    \ of the binary operation by invoking the provided `Op` function.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return Op(a, b);\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_WRAPPER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/wrapper.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:20:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/wrapper.hpp
layout: document
title: Monoid Wrapper
---

## Overview

An adapter struct that easily generates a monoid from given functions or stateless lambdas using C++20 Non-Type Template Parameters (NTTP). This is extremely useful in competitive programming contests to define custom monoids (e.g., for Segment Trees) with minimal boilerplate code.

## Template Parameters

* `T`: The underlying data type of the monoid.
* `Op`: A callable object (function pointer or stateless lambda) that takes two arguments of type `T` and returns a value of type `T`.
* `Id`: A callable object (function pointer or stateless lambda) that takes no arguments and returns the identity element of type `T`.

## Example

In C++20, you can pass lambdas directly in the template arguments. This allows you to define a monoid completely inline.

```cpp
#include "monoid/wrapper.hpp"

// Define a Monoid for XOR sum inline
using XorMonoid = m1une::monoid::Wrapper<int, [](int a, int b) { return a ^ b; }, []() { return 0; }>;

// Now `XorMonoid` can be passed to data structures like Segtree
// Segtree<XorMonoid> seg(n);
```

You can also define the lambdas separately if the operations are complex:

```cpp
constexpr auto custom_op = [](long long a, long long b) { return a + b; };
constexpr auto custom_id = []() { return 0LL; };
using CustomMonoid = m1une::monoid::Wrapper<long long, custom_op, custom_id>;
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
