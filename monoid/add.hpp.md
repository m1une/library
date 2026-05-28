---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/segtree.test.cpp
    title: verify/data_structure/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for addition,\
    \ which is 0.\n    static constexpr T id() { return T(0); }\n\n    // Returns\
    \ the sum of a and b.\n    static constexpr T op(const T& a, const T& b) { return\
    \ a + b; }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_ADD_HPP\n#define M1UNE_MONOID_ADD_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate\
    \ <typename T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for addition, which is 0.\n    static constexpr T id() { return\
    \ T(0); }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) { return a + b; }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_ADD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/add.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:31:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/segtree.test.cpp
documentation_of: monoid/add.hpp
layout: document
redirect_from:
- /library/monoid/add.hpp
- /library/monoid/add.hpp.html
title: monoid/add.hpp
---
