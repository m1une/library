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
  bundledCode: "#line 1 \"monoid/gcd.hpp\"\n\n\n\n#include <numeric>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for Greatest Common Divisor (Range\
    \ GCD).\ntemplate <typename T>\nstruct Gcd {\n    using value_type = T;\n\n  \
    \  // The identity element for GCD is 0.\n    static constexpr T id() { return\
    \ T(0); }\n\n    // Returns the greatest common divisor of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) { \n        return std::gcd(a, b); \n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_GCD_HPP\n#define M1UNE_MONOID_GCD_HPP 1\n\n#include\
    \ <numeric>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for Greatest\
    \ Common Divisor (Range GCD).\ntemplate <typename T>\nstruct Gcd {\n    using\
    \ value_type = T;\n\n    // The identity element for GCD is 0.\n    static constexpr\
    \ T id() { return T(0); }\n\n    // Returns the greatest common divisor of a and\
    \ b.\n    static constexpr T op(const T& a, const T& b) { \n        return std::gcd(a,\
    \ b); \n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_MONOID_GCD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/gcd.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:38:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/gcd.hpp
layout: document
redirect_from:
- /library/monoid/gcd.hpp
- /library/monoid/gcd.hpp.html
title: monoid/gcd.hpp
---
