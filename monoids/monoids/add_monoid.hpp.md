---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoids/monoid.hpp
    title: monoids/monoid.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoids/monoids/prim_monoids.hpp
    title: monoids/monoids/prim_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/monoids/add_monoid.hpp\"\n\n\n\n#line 1 \"monoids/monoid.hpp\"\
    \n\n\n\n#include <functional>\n#include <type_traits>\n\nnamespace m1une {\ntemplate\
    \ <typename T, auto operation, auto identity, bool commutative>\nstruct monoid\
    \ {\n    static_assert(std::is_convertible_v<decltype(operation), std::function<T(T,\
    \ T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n#line 5 \"monoids/monoids/add_monoid.hpp\"\n\nnamespace\
    \ m1une {\ntemplate <typename T>\nusing add_monoid = monoid<T, [](T a, T b) {\
    \ return a + b; }, []() { return T(0); }, true>;\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_ADD_MONOID_HPP

    #define M1UNE_ADD_MONOID_HPP 1


    #include "../monoid.hpp"


    namespace m1une {

    template <typename T>

    using add_monoid = monoid<T, [](T a, T b) { return a + b; }, []() { return T(0);
    }, true>;

    }  // namespace m1une


    #endif  // M1UNE_ADD_MONOID_HPP

    '
  dependsOn:
  - monoids/monoid.hpp
  isVerificationFile: false
  path: monoids/monoids/add_monoid.hpp
  requiredBy:
  - monoids/monoids/prim_monoids.hpp
  timestamp: '2025-09-28 19:13:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoids/monoids/add_monoid.hpp
layout: document
redirect_from:
- /library/monoids/monoids/add_monoid.hpp
- /library/monoids/monoids/add_monoid.hpp.html
title: monoids/monoids/add_monoid.hpp
---
