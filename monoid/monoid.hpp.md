---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/monoids/add_monoid.hpp
    title: monoid/monoids/add_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/affine_monoid.hpp
    title: monoid/monoids/affine_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/affine_right_monoid.hpp
    title: monoid/monoids/affine_right_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/and_monoid.hpp
    title: monoid/monoids/and_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/max_monoid.hpp
    title: monoid/monoids/max_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/min_monoid.hpp
    title: monoid/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/mul_monoid.hpp
    title: monoid/monoids/mul_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/or_monoid.hpp
    title: monoid/monoids/or_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/prim_monoids.hpp
    title: monoid/monoids/prim_monoids.hpp
  - icon: ':warning:'
    path: monoid/monoids/xor_monoid.hpp
    title: monoid/monoids/xor_monoid.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <type_traits>\n\nnamespace m1une {\ntemplate <typename T, auto operation, auto\
    \ identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_HPP\n#define M1UNE_MONOID_HPP 1\n\n#include <functional>\n\
    #include <type_traits>\n\nnamespace m1une {\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_MONOID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/monoid.hpp
  requiredBy:
  - monoid/monoids/affine_right_monoid.hpp
  - monoid/monoids/prim_monoids.hpp
  - monoid/monoids/min_monoid.hpp
  - monoid/monoids/and_monoid.hpp
  - monoid/monoids/max_monoid.hpp
  - monoid/monoids/mul_monoid.hpp
  - monoid/monoids/xor_monoid.hpp
  - monoid/monoids/or_monoid.hpp
  - monoid/monoids/affine_monoid.hpp
  - monoid/monoids/add_monoid.hpp
  timestamp: '2025-09-28 19:25:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoid.hpp
- /library/monoid/monoid.hpp.html
title: monoid/monoid.hpp
---
