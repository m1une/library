---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_max.hpp
    title: monoid/acted_monoids/range_add_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_min.hpp
    title: monoid/acted_monoids/range_add_range_min.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_sum.hpp
    title: monoid/acted_monoids/range_add_range_sum.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_sum.hpp
    title: monoid/acted_monoids/range_update_range_sum.hpp
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/add_monoid.hpp\"\n\n\n\n#line 1 \"monoid/monoid.hpp\"\
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
    };\n\n}  // namespace m1une\n\n\n#line 5 \"monoid/monoids/add_monoid.hpp\"\n\n\
    namespace m1une {\n\ntemplate <typename T>\nusing add_monoid = monoid<T, [](T\
    \ a, T b) { return a + b; }, []() { return T(0); }, true>;\n\n}  // namespace\
    \ m1une\n\n\n"
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
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/add_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_add_range_sum.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/acted_monoids/range_add_range_min.hpp
  - monoid/acted_monoids/range_add_range_max.hpp
  - monoid/prim_acted_monoids.hpp
  - monoid/prim_monoids.hpp
  timestamp: '2025-09-29 17:50:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/add_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/add_monoid.hpp
- /library/monoid/monoids/add_monoid.hpp.html
title: monoid/monoids/add_monoid.hpp
---
