---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/monoids/prim_monoids.hpp
    title: monoid/monoids/prim_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/xor_monoid.hpp\"\n\n\n\n#line 1 \"monoid/monoid.hpp\"\
    \n\n\n\n#include <functional>\n#include <type_traits>\n\nnamespace m1une {\ntemplate\
    \ <typename T, auto operation, auto identity, bool commutative>\nstruct monoid\
    \ {\n    static_assert(std::is_convertible_v<decltype(operation), std::function<T(T,\
    \ T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n#line 5 \"monoid/monoids/xor_monoid.hpp\"\n\nnamespace\
    \ m1une {\ntemplate <typename T>\nusing xor_monoid =\n    monoid<T, [](T a, T\
    \ b) { return a ^ b; }, []() { return T(0); }, true>;\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_XOR_MONOID_HPP\n#define M1UNE_XOR_MONOID_HPP 1\n\n#include\
    \ \"../monoid.hpp\"\n\nnamespace m1une {\ntemplate <typename T>\nusing xor_monoid\
    \ =\n    monoid<T, [](T a, T b) { return a ^ b; }, []() { return T(0); }, true>;\n\
    }  // namespace m1une\n\n#endif  // M1UNE_XOR_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/xor_monoid.hpp
  requiredBy:
  - monoid/monoids/prim_monoids.hpp
  timestamp: '2025-09-28 19:25:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/xor_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/xor_monoid.hpp
- /library/monoid/monoids/xor_monoid.hpp.html
title: monoid/monoids/xor_monoid.hpp
---
