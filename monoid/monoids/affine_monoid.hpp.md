---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/unit_test/segtree.test.cpp
    title: verify/unit_test/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/affine_monoid.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n#include <type_traits>\n\
    #include <concepts>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 7 \"monoid/monoids/affine_monoid.hpp\"\n\
    \nnamespace m1une {\n\n// Affine transformation f(x) = ax + b is represented as\
    \ (a, b)\n// perform f first, then g\n// op(f, g)(x) = g(f(x))\ntemplate <typename\
    \ T>\nusing affine_monoid = monoid<std::pair<T, T>,\n                        \
    \     [](std::pair<T, T> f, std::pair<T, T> g) {\n                           \
    \      return std::pair<T, T>(f.first * g.first, f.second * g.first + g.second);\n\
    \                             },\n                             []() { return std::pair<T,\
    \ T>(1, 0); }, false>;\n\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_AFFINE_MONOID_HPP\n#define M1UNE_AFFINE_MONOID_HPP 1\n\n#include\
    \ <utility>\n\n#include \"../monoid.hpp\"\n\nnamespace m1une {\n\n// Affine transformation\
    \ f(x) = ax + b is represented as (a, b)\n// perform f first, then g\n// op(f,\
    \ g)(x) = g(f(x))\ntemplate <typename T>\nusing affine_monoid = monoid<std::pair<T,\
    \ T>,\n                             [](std::pair<T, T> f, std::pair<T, T> g) {\n\
    \                                 return std::pair<T, T>(f.first * g.first, f.second\
    \ * g.first + g.second);\n                             },\n                  \
    \           []() { return std::pair<T, T>(1, 0); }, false>;\n\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_AFFINE_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/affine_monoid.hpp
  requiredBy:
  - monoid/prim_monoids.hpp
  timestamp: '2025-09-29 17:50:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/unit_test/segtree.test.cpp
documentation_of: monoid/monoids/affine_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/affine_monoid.hpp
- /library/monoid/monoids/affine_monoid.hpp.html
title: monoid/monoids/affine_monoid.hpp
---
