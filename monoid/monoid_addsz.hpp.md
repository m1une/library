---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_sum.hpp
    title: monoid/acted_monoids/range_add_range_sum.hpp
  - icon: ':x:'
    path: monoid/acted_monoids/range_affine_range_sum.hpp
    title: monoid/acted_monoids/range_affine_range_sum.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_sum.hpp
    title: monoid/acted_monoids/range_update_range_sum.hpp
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/unit_test/lazy_segtree.test.cpp
    title: verify/unit_test/lazy_segtree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoid_addsz.hpp\"\n\n\n\n#include <concepts>\n\n\
    #line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 5 \"monoid/monoid.hpp\"\n#include <functional>\n\
    #include <type_traits>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(operation), T, T>, \"operation must work as T(T, T)\");\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(identity)>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires(typename T::value_type v) {\n\
    \    typename T::value_type;\n    { T::op(v, v) } -> std::same_as<typename T::value_type>;\n\
    \    { T::id() } -> std::same_as<typename T::value_type>;\n    { T::is_commutative\
    \ } -> std::convertible_to<bool>;\n};\n\n}  // namespace m1une\n\n\n#line 7 \"\
    monoid/monoid_addsz.hpp\"\n\nnamespace m1une {\n\ntemplate <typename T>\nstruct\
    \ value_and_size {\n    T value;\n    int size;\n};\n\ntemplate <Monoid M>\nusing\
    \ monoid_addsz = monoid<value_and_size<typename M::value_type>,\n            \
    \                [](value_and_size<typename M::value_type> a, value_and_size<typename\
    \ M::value_type> b) {\n                                return value_and_size<typename\
    \ M::value_type>{M::op(a.value, b.value), a.size + b.size};\n                \
    \            },\n                            []() { return value_and_size<typename\
    \ M::value_type>{M::id(), 0}; }, M::is_commutative>;\n\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MONOID_ADDSZ_HPP\n#define M1UNE_MONOID_ADDSZ_HPP 1\n\n#include\
    \ <concepts>\n\n#include \"monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename\
    \ T>\nstruct value_and_size {\n    T value;\n    int size;\n};\n\ntemplate <Monoid\
    \ M>\nusing monoid_addsz = monoid<value_and_size<typename M::value_type>,\n  \
    \                          [](value_and_size<typename M::value_type> a, value_and_size<typename\
    \ M::value_type> b) {\n                                return value_and_size<typename\
    \ M::value_type>{M::op(a.value, b.value), a.size + b.size};\n                \
    \            },\n                            []() { return value_and_size<typename\
    \ M::value_type>{M::id(), 0}; }, M::is_commutative>;\n\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MONOID_ADDSZ_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoid_addsz.hpp
  requiredBy:
  - monoid/acted_monoids/range_add_range_sum.hpp
  - monoid/acted_monoids/range_affine_range_sum.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/prim_acted_monoids.hpp
  timestamp: '2025-10-01 15:41:05+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/unit_test/lazy_segtree.test.cpp
documentation_of: monoid/monoid_addsz.hpp
layout: document
redirect_from:
- /library/monoid/monoid_addsz.hpp
- /library/monoid/monoid_addsz.hpp.html
title: monoid/monoid_addsz.hpp
---
