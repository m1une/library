---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/monoid.hpp
    title: monoid/monoid.hpp
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
  bundledCode: "#line 1 \"monoid/monoids/affine_monoid.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n#include <type_traits>\n\
    \nnamespace m1une {\ntemplate <typename T, auto operation, auto identity, bool\
    \ commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n#line 7 \"monoid/monoids/affine_monoid.hpp\"\n\nnamespace\
    \ m1une {\ntemplate <typename T>\nusing affine_monoid = monoid<std::pair<T, T>,\n\
    \                             [](std::pair<T, T> f, std::pair<T, T> g) {\n   \
    \                              return std::pair<T, T>(f.first * g.first, f.second\
    \ * g.first + g.second);\n                             },\n                  \
    \           []() { return std::pair<T, T>(1, 0); }, false>;\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_AFFINE_MONOID_HPP\n#define M1UNE_AFFINE_MONOID_HPP 1\n\n#include\
    \ <utility>\n\n#include \"../monoid.hpp\"\n\nnamespace m1une {\ntemplate <typename\
    \ T>\nusing affine_monoid = monoid<std::pair<T, T>,\n                        \
    \     [](std::pair<T, T> f, std::pair<T, T> g) {\n                           \
    \      return std::pair<T, T>(f.first * g.first, f.second * g.first + g.second);\n\
    \                             },\n                             []() { return std::pair<T,\
    \ T>(1, 0); }, false>;\n}  // namespace m1une\n\n#endif  // M1UNE_AFFINE_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/affine_monoid.hpp
  requiredBy:
  - monoid/monoids/prim_monoids.hpp
  timestamp: '2025-09-28 19:25:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/affine_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/affine_monoid.hpp
- /library/monoid/monoids/affine_monoid.hpp.html
title: monoid/monoids/affine_monoid.hpp
---
