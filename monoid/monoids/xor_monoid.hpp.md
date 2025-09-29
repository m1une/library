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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/xor_monoid.hpp\"\n\n\n\n#line 1 \"monoid/monoid.hpp\"\
    \n\n\n\n#include <functional>\n#include <type_traits>\n#include <concepts>\n\n\
    namespace m1une {\n\ntemplate <typename T, auto operation, auto identity, bool\
    \ commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 5 \"monoid/monoids/xor_monoid.hpp\"\n\n\
    namespace m1une {\n\ntemplate <typename T>\nusing xor_monoid = monoid<T, [](T\
    \ a, T b) { return a ^ b; }, []() { return T(0); }, true>;\n\n}  // namespace\
    \ m1une\n\n\n"
  code: '#ifndef M1UNE_XOR_MONOID_HPP

    #define M1UNE_XOR_MONOID_HPP 1


    #include "../monoid.hpp"


    namespace m1une {


    template <typename T>

    using xor_monoid = monoid<T, [](T a, T b) { return a ^ b; }, []() { return T(0);
    }, true>;


    }  // namespace m1une


    #endif  // M1UNE_XOR_MONOID_HPP

    '
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/xor_monoid.hpp
  requiredBy:
  - monoid/prim_monoids.hpp
  timestamp: '2025-09-29 17:50:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/xor_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/xor_monoid.hpp
- /library/monoid/monoids/xor_monoid.hpp.html
title: monoid/monoids/xor_monoid.hpp
---
