---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/power.hpp\"\n\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n    \n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n    \n    // 3. Must\
    \ have a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) }\
    \ -> std::same_as<typename M::value_type>;\n};\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 5 \"monoid/power.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Computes a^n (a * a * ... * a, n times) for an element 'a' in\
    \ Monoid 'M'.\n// Uses binary exponentiation to achieve O(log n) time complexity.\n\
    // The template parameter 'M' is constrained by the 'IsMonoid' concept.\ntemplate\
    \ <IsMonoid M>\nconstexpr typename M::value_type power(typename M::value_type\
    \ a, long long n) {\n    typename M::value_type res = M::id();\n    while (n >\
    \ 0) {\n        if (n & 1) {\n            res = M::op(res, a);\n        }\n  \
    \      a = M::op(a, a);\n        n >>= 1;\n    }\n    return res;\n}\n\n}  //\
    \ namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_POWER_HPP\n#define M1UNE_MONOID_POWER_HPP 1\n\n#include\
    \ \"concept.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\n// Computes a^n\
    \ (a * a * ... * a, n times) for an element 'a' in Monoid 'M'.\n// Uses binary\
    \ exponentiation to achieve O(log n) time complexity.\n// The template parameter\
    \ 'M' is constrained by the 'IsMonoid' concept.\ntemplate <IsMonoid M>\nconstexpr\
    \ typename M::value_type power(typename M::value_type a, long long n) {\n    typename\
    \ M::value_type res = M::id();\n    while (n > 0) {\n        if (n & 1) {\n  \
    \          res = M::op(res, a);\n        }\n        a = M::op(a, a);\n       \
    \ n >>= 1;\n    }\n    return res;\n}\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_POWER_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: monoid/power.hpp
  requiredBy: []
  timestamp: '2026-05-28 18:13:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/power.hpp
layout: document
redirect_from:
- /library/monoid/power.hpp
- /library/monoid/power.hpp.html
title: monoid/power.hpp
---
