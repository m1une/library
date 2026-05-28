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
  bundledCode: "#line 1 \"monoid/xor.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate <typename T>\nstruct Xor\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for bitwise\
    \ XOR, which is 0.\n    static constexpr T id() { return T(0); }\n\n    // Returns\
    \ the bitwise XOR of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) { return a ^ b; }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_MONOID_XOR_HPP\n#define M1UNE_MONOID_XOR_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate\
    \ <typename T>\nstruct Xor {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for bitwise XOR, which is 0.\n    static constexpr T id() {\
    \ return T(0); }\n\n    // Returns the bitwise XOR of a and b.\n    static constexpr\
    \ T op(const T& a, const T& b) { return a ^ b; }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_XOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/xor.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:31:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/xor.hpp
layout: document
redirect_from:
- /library/monoid/xor.hpp
- /library/monoid/xor.hpp.html
title: monoid/xor.hpp
---
