---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoids/monoid.hpp
    title: monoids/monoid.hpp
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
    path: monoids/monoids/xor_monoid.hpp
    title: monoids/monoids/xor_monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/monoids/prim_monoids.hpp\"\n\n\n\n#line 1 \"monoids/monoids/add_monoid.hpp\"\
    \n\n\n\n#line 1 \"monoids/monoid.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <type_traits>\n\nnamespace m1une {\ntemplate <typename T, auto operation, auto\
    \ identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n#line 5 \"monoids/monoids/add_monoid.hpp\"\n\nnamespace\
    \ m1une {\ntemplate <typename T>\nusing add_monoid = monoid<T, [](T a, T b) {\
    \ return a + b; }, []() { return T(0); }, true>;\n}  // namespace m1une\n\n\n\
    #line 1 \"monoids/monoids/mul_monoid.hpp\"\n\n\n\n#line 5 \"monoids/monoids/mul_monoid.hpp\"\
    \n\nnamespace m1une {\ntemplate <typename T>\nusing mul_monoid = monoid<T, [](T\
    \ a, T b) { return a * b; }, []() { return T(1); }, true>;\n}  // namespace m1une\n\
    \n\n#line 1 \"monoids/monoids/min_monoid.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <limits>\n\n#line 8 \"monoids/monoids/min_monoid.hpp\"\n\nnamespace m1une {\n\
    template <typename T>\nusing min_monoid =\n    monoid<T, [](T a, T b) { return\
    \ std::min(a, b); }, []() { return std::numeric_limits<T>::max(); }, true>;\n\
    }  // namespace m1une\n\n\n#line 1 \"monoids/monoids/max_monoid.hpp\"\n\n\n\n\
    #line 6 \"monoids/monoids/max_monoid.hpp\"\n\n#line 8 \"monoids/monoids/max_monoid.hpp\"\
    \n\nnamespace m1une {\ntemplate <typename T>\nusing max_monoid =\n    monoid<T,\
    \ [](T a, T b) { return std::max(a, b); }, []() { return std::numeric_limits<T>::min();\
    \ }, true>;\n}  // namespace m1une\n\n\n#line 1 \"monoids/monoids/and_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoids/monoids/and_monoid.hpp\"\n\nnamespace m1une {\ntemplate\
    \ <typename T>\nusing and_monoid =\n    monoid<T, [](T a, T b) { return a & b;\
    \ }, []() { return ~T(0); }, true>;\n}  // namespace m1une\n\n\n#line 1 \"monoids/monoids/or_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoids/monoids/or_monoid.hpp\"\n\nnamespace m1une {\ntemplate\
    \ <typename T>\nusing or_monoid =\n    monoid<T, [](T a, T b) { return a | b;\
    \ }, []() { return T(0); }, true>;\n}  // namespace m1une\n\n\n#line 1 \"monoids/monoids/xor_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoids/monoids/xor_monoid.hpp\"\n\nnamespace m1une {\ntemplate\
    \ <typename T>\nusing xor_monoid =\n    monoid<T, [](T a, T b) { return a ^ b;\
    \ }, []() { return T(0); }, true>;\n}  // namespace m1une\n\n\n#line 1 \"monoids/monoids/affine_monoid.hpp\"\
    \n\n\n\n#include <utility>\n\n#line 7 \"monoids/monoids/affine_monoid.hpp\"\n\n\
    namespace m1une {\ntemplate <typename T>\nusing affine_monoid = monoid<std::pair<T,\
    \ T>,\n                             [](std::pair<T, T> f, std::pair<T, T> g) {\n\
    \                                 return std::pair<T, T>(f.first * g.first, f.second\
    \ * g.first + g.second);\n                             },\n                  \
    \           []() { return std::pair<T, T>(1, 0); }, false>;\n}  // namespace m1une\n\
    \n\n#line 12 \"monoids/monoids/prim_monoids.hpp\"\n\n\n"
  code: '#ifndef M1UNE_PRIM_MONOIDS_HPP

    #define M1UNE_PRIM_MONOIDS_HPP 1


    #include "add_monoid.hpp"

    #include "mul_monoid.hpp"

    #include "min_monoid.hpp"

    #include "max_monoid.hpp"

    #include "and_monoid.hpp"

    #include "or_monoid.hpp"

    #include "xor_monoid.hpp"

    #include "affine_monoid.hpp"


    #endif  // M1UNE_PRIM_MONOIDS_HPP

    '
  dependsOn:
  - monoids/monoids/add_monoid.hpp
  - monoids/monoid.hpp
  - monoids/monoids/mul_monoid.hpp
  - monoids/monoids/min_monoid.hpp
  - monoids/monoids/max_monoid.hpp
  - monoids/monoids/and_monoid.hpp
  - monoids/monoids/or_monoid.hpp
  - monoids/monoids/xor_monoid.hpp
  - monoids/monoids/affine_monoid.hpp
  isVerificationFile: false
  path: monoids/monoids/prim_monoids.hpp
  requiredBy: []
  timestamp: '2025-09-28 19:13:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoids/monoids/prim_monoids.hpp
layout: document
redirect_from:
- /library/monoids/monoids/prim_monoids.hpp
- /library/monoids/monoids/prim_monoids.hpp.html
title: monoids/monoids/prim_monoids.hpp
---
