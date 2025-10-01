---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_max.hpp
    title: monoid/acted_monoids/range_update_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_min.hpp
    title: monoid/acted_monoids/range_update_range_min.hpp
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
  bundledCode: "#line 1 \"monoid/monoids/update_monoid.hpp\"\n\n\n\n#line 1 \"monoid/monoid.hpp\"\
    \n\n\n\n#include <concepts>\n#include <functional>\n#include <type_traits>\n\n\
    namespace m1une {\n\ntemplate <typename T, auto operation, auto identity, bool\
    \ commutative>\nstruct monoid {\n    static_assert(std::is_invocable_r_v<T, decltype(operation),\
    \ T, T>, \"operation must work as T(T, T)\");\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(identity)>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires(typename T::value_type v) {\n\
    \    typename T::value_type;\n    { T::op(v, v) } -> std::same_as<typename T::value_type>;\n\
    \    { T::id() } -> std::same_as<typename T::value_type>;\n    { T::is_commutative\
    \ } -> std::convertible_to<bool>;\n};\n\n}  // namespace m1une\n\n\n#line 5 \"\
    monoid/monoids/update_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename\
    \ T, T identity>\nusing update_monoid = monoid<T,\n                          \
    \   [](T a, T b) {\n                                 if (b == identity) return\
    \ a;\n                                 return b;\n                           \
    \  },\n                             []() { return identity; }, false>;\n\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOIDS_UPDATE_MONOID_HPP\n#define M1UNE_MONOIDS_UPDATE_MONOID_HPP\
    \ 1\n\n#include \"../monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename T,\
    \ T identity>\nusing update_monoid = monoid<T,\n                             [](T\
    \ a, T b) {\n                                 if (b == identity) return a;\n \
    \                                return b;\n                             },\n\
    \                             []() { return identity; }, false>;\n\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOIDS_UPDATE_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/update_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_update_range_max.hpp
  - monoid/acted_monoids/range_update_range_min.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/prim_acted_monoids.hpp
  - monoid/prim_monoids.hpp
  timestamp: '2025-10-01 15:41:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/update_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/update_monoid.hpp
- /library/monoid/monoids/update_monoid.hpp.html
title: monoid/monoids/update_monoid.hpp
---
