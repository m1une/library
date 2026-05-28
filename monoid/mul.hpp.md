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
  bundledCode: "#line 1 \"monoid/mul.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for multiplication (Range Product).\ntemplate <typename T>\n\
    struct Mul {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for multiplication, which is 1.\n    static constexpr T id() { return T(1);\
    \ }\n\n    // Returns the product of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) { return a * b; }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MUL_HPP\n#define M1UNE_MONOID_MUL_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for multiplication (Range Product).\n\
    template <typename T>\nstruct Mul {\n    using value_type = T;\n\n    // Returns\
    \ the identity element for multiplication, which is 1.\n    static constexpr T\
    \ id() { return T(1); }\n\n    // Returns the product of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) { return a * b; }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MUL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/mul.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:31:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/mul.hpp
layout: document
redirect_from:
- /library/monoid/mul.hpp
- /library/monoid/mul.hpp.html
title: monoid/mul.hpp
---
