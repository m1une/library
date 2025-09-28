---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoids/monoids/add_monoid.hpp
    title: monoids/monoids/add_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/affine_monoid.hpp
    title: monoids/monoids/affine_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/and_monoid.hpp
    title: monoids/monoids/and_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/max_monoid.hpp
    title: monoids/monoids/max_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/min_monoid.hpp
    title: monoids/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/mul_monoid.hpp
    title: monoids/monoids/mul_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/or_monoid.hpp
    title: monoids/monoids/or_monoid.hpp
  - icon: ':warning:'
    path: monoids/monoids/prim_monoids.hpp
    title: monoids/monoids/prim_monoids.hpp
  - icon: ':warning:'
    path: monoids/monoids/xor_monoid.hpp
    title: monoids/monoids/xor_monoid.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/monoid.hpp\"\n\n\n\n#include <functional>\n#include\
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
  path: monoids/monoid.hpp
  requiredBy:
  - monoids/monoids/prim_monoids.hpp
  - monoids/monoids/min_monoid.hpp
  - monoids/monoids/and_monoid.hpp
  - monoids/monoids/max_monoid.hpp
  - monoids/monoids/mul_monoid.hpp
  - monoids/monoids/xor_monoid.hpp
  - monoids/monoids/or_monoid.hpp
  - monoids/monoids/affine_monoid.hpp
  - monoids/monoids/add_monoid.hpp
  timestamp: '2025-09-28 19:13:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoids/monoid.hpp
layout: document
redirect_from:
- /library/monoids/monoid.hpp
- /library/monoids/monoid.hpp.html
title: monoids/monoid.hpp
---
