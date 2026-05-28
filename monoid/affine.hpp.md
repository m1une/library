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
redirect_from:
- /library/monoid/affine.hpp
- /library/monoid/affine.hpp.html
title: monoid/affine.hpp
---
