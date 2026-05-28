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
  bundledCode: "#line 1 \"monoid/min.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Monoid for minimum (Range Minimum).\n\
    // The identity element defaults to the maximum possible value of type T, but\
    \ can be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct Min {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for minimum.\n    static constexpr T id() { return Id; }\n\n    // Returns the\
    \ minimum of a and b.\n    static constexpr T op(const T& a, const T& b) { return\
    \ std::min(a, b); }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_HPP\n#define M1UNE_MONOID_MIN_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for minimum (Range Minimum).\n// The identity element defaults to the\
    \ maximum possible value of type T, but can be overridden.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max()>\nstruct Min {\n    using value_type\
    \ = T;\n\n    // Returns the identity element for minimum.\n    static constexpr\
    \ T id() { return Id; }\n\n    // Returns the minimum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) { return std::min(a, b); }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:31:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/min.hpp
layout: document
redirect_from:
- /library/monoid/min.hpp
- /library/monoid/min.hpp.html
title: monoid/min.hpp
---
