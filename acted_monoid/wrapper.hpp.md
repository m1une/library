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
  bundledCode: "#line 1 \"acted_monoid/wrapper.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\n// Wrapper struct to generate an Acted Monoid using Non-Type\
    \ Template Parameters (NTTP).\n// Useful for quickly defining acted monoids using\
    \ custom functions or constexpr lambdas during contests.\ntemplate <typename T,\
    \ typename E, auto Op, auto Id, auto OpComp, auto OpId, auto Mapping>\nstruct\
    \ Wrapper {\n    using value_type = T;\n    using operator_type = E;\n\n    //\
    \ Returns the identity element of the value monoid.\n    static constexpr T id()\
    \ {\n        return Id();\n    }\n\n    // Returns the result of the value monoid\
    \ binary operation.\n    static constexpr T op(const T& a, const T& b) {\n   \
    \     return Op(a, b);\n    }\n\n    // Returns the identity element of the operator\
    \ monoid.\n    static constexpr E op_id() {\n        return OpId();\n    }\n\n\
    \    // Composes two operations f and g (corresponds to f(g(x))).\n    static\
    \ constexpr E op_comp(const E& f, const E& g) {\n        return OpComp(f, g);\n\
    \    }\n\n    // Applies the operator f onto the value x.\n    static constexpr\
    \ T mapping(const E& f, const T& x) {\n        return Mapping(f, x);\n    }\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_WRAPPER_HPP\n#define M1UNE_ACTED_MONOID_WRAPPER_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Wrapper struct to generate\
    \ an Acted Monoid using Non-Type Template Parameters (NTTP).\n// Useful for quickly\
    \ defining acted monoids using custom functions or constexpr lambdas during contests.\n\
    template <typename T, typename E, auto Op, auto Id, auto OpComp, auto OpId, auto\
    \ Mapping>\nstruct Wrapper {\n    using value_type = T;\n    using operator_type\
    \ = E;\n\n    // Returns the identity element of the value monoid.\n    static\
    \ constexpr T id() {\n        return Id();\n    }\n\n    // Returns the result\
    \ of the value monoid binary operation.\n    static constexpr T op(const T& a,\
    \ const T& b) {\n        return Op(a, b);\n    }\n\n    // Returns the identity\
    \ element of the operator monoid.\n    static constexpr E op_id() {\n        return\
    \ OpId();\n    }\n\n    // Composes two operations f and g (corresponds to f(g(x))).\n\
    \    static constexpr E op_comp(const E& f, const E& g) {\n        return OpComp(f,\
    \ g);\n    }\n\n    // Applies the operator f onto the value x.\n    static constexpr\
    \ T mapping(const E& f, const T& x) {\n        return Mapping(f, x);\n    }\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_WRAPPER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/wrapper.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/wrapper.hpp
layout: document
title: Acted Monoid Wrapper
---

## Overview

`Wrapper` provides a convenient way to define an Acted Monoid inline without writing a separate `struct`. This is particularly useful during contests when you need to combine custom mapping logic quickly.

It uses Non-Type Template Parameters (NTTP) introduced in C++20, allowing you to pass `constexpr` functions or lambdas directly as template arguments.

## Template Parameters

- `typename T`: The type of the value element (`value_type`).
- `typename E`: The type of the operator element (`operator_type`).
- `auto Op`: A function or lambda for the value monoid operation (`T op(T, T)`).
- `auto Id`: A function or lambda returning the value identity (`T id()`).
- `auto OpComp`: A function or lambda for operator composition (`E op_comp(E, E)`).
- `auto OpId`: A function or lambda returning the operator identity (`E op_id()`).
- `auto Mapping`: A function or lambda for mapping the operator onto the value (`T mapping(E, T)`).

## Example

```cpp
#include "acted_monoid/wrapper.hpp"

// Definition of Range Add Range Min using Wrapper
constexpr long long INF = std::numeric_limits<long long>::max();
using RangeAddRangeMin = m1une::acted_monoid::Wrapper<
    long long,
    long long,
    [](long long a, long long b) { return std::min(a, b); },
    []() { return INF; },
    [](long long f, long long g) { return f + g; },
    []() { return 0LL; },
    [](long long f, long long x) { return x == INF ? INF : x + f; }
>;
```
