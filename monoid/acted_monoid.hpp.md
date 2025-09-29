---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: data_structure/segtree/lazysegtree.hpp
    title: Lazy Segment Tree
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
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <concepts>\n#include\
    \ <functional>\n#include <type_traits>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n\
    #line 7 \"monoid/monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename T, auto\
    \ operation, auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 9 \"monoid/acted_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <Monoid Data, Monoid Act, auto mapping>\nstruct acted_monoid\
    \ {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\n    using data_type\
    \ = typename Data::value_type;\n    using act_type = typename Act::value_type;\n\
    \n    static_assert(std::is_convertible_v<decltype(mapping), std::function<data_type(act_type,\
    \ data_type)>>,\n                  \"mapping must work as data_type(data_type,\
    \ act_type)\");\n\n    static constexpr auto data_op = Data::op;\n    static constexpr\
    \ auto data_id = Data::id;\n    static constexpr bool data_is_commutative = Data::is_commutative;\n\
    \    static constexpr auto act_op = Act::op;\n    static constexpr auto act_id\
    \ = Act::id;\n    static constexpr bool act_is_commutative = Act::is_commutative;\n\
    \    static constexpr auto apply = mapping;\n};\n\ntemplate <typename T>\nconcept\
    \ ActedMonoid = requires {\n    typename T::data_monoid;\n    typename T::act_monoid;\n\
    \    typename T::data_type;\n    typename T::act_type;\n    {\n        T::data_op\n\
    \    } -> std::convertible_to<std::function<typename T::data_type(typename T::data_type,\
    \ typename T::data_type)>>;\n    { T::data_id } -> std::convertible_to<std::function<typename\
    \ T::data_type()>>;\n    { T::data_is_commutative } -> std::convertible_to<bool>;\n\
    \    {\n        T::act_op\n    } -> std::convertible_to<std::function<typename\
    \ T::act_type(typename T::act_type, typename T::act_type)>>;\n    { T::act_id\
    \ } -> std::convertible_to<std::function<typename T::act_type()>>;\n    { T::act_is_commutative\
    \ } -> std::convertible_to<bool>;\n    {\n        T::apply\n    } -> std::convertible_to<std::function<typename\
    \ T::data_type(typename T::act_type, typename T::data_type)>>;\n};\n\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_HPP\n#define M1UNE_ACTED_MONOID_HPP 1\n\n#include\
    \ <concepts>\n#include <functional>\n#include <type_traits>\n\n#include \"monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <Monoid Data, Monoid Act, auto mapping>\nstruct\
    \ acted_monoid {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\
    \n    using data_type = typename Data::value_type;\n    using act_type = typename\
    \ Act::value_type;\n\n    static_assert(std::is_convertible_v<decltype(mapping),\
    \ std::function<data_type(act_type, data_type)>>,\n                  \"mapping\
    \ must work as data_type(data_type, act_type)\");\n\n    static constexpr auto\
    \ data_op = Data::op;\n    static constexpr auto data_id = Data::id;\n    static\
    \ constexpr bool data_is_commutative = Data::is_commutative;\n    static constexpr\
    \ auto act_op = Act::op;\n    static constexpr auto act_id = Act::id;\n    static\
    \ constexpr bool act_is_commutative = Act::is_commutative;\n    static constexpr\
    \ auto apply = mapping;\n};\n\ntemplate <typename T>\nconcept ActedMonoid = requires\
    \ {\n    typename T::data_monoid;\n    typename T::act_monoid;\n    typename T::data_type;\n\
    \    typename T::act_type;\n    {\n        T::data_op\n    } -> std::convertible_to<std::function<typename\
    \ T::data_type(typename T::data_type, typename T::data_type)>>;\n    { T::data_id\
    \ } -> std::convertible_to<std::function<typename T::data_type()>>;\n    { T::data_is_commutative\
    \ } -> std::convertible_to<bool>;\n    {\n        T::act_op\n    } -> std::convertible_to<std::function<typename\
    \ T::act_type(typename T::act_type, typename T::act_type)>>;\n    { T::act_id\
    \ } -> std::convertible_to<std::function<typename T::act_type()>>;\n    { T::act_is_commutative\
    \ } -> std::convertible_to<bool>;\n    {\n        T::apply\n    } -> std::convertible_to<std::function<typename\
    \ T::data_type(typename T::act_type, typename T::data_type)>>;\n};\n\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/acted_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_update_range_max.hpp
  - monoid/acted_monoids/range_add_range_sum.hpp
  - monoid/acted_monoids/range_update_range_min.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/acted_monoids/range_add_range_min.hpp
  - monoid/acted_monoids/range_add_range_max.hpp
  - monoid/prim_acted_monoids.hpp
  - monoid/prim_acted_monoids.hpp
  - data_structure/segtree/lazysegtree.hpp
  timestamp: '2025-09-29 18:09:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/acted_monoid.hpp
layout: document
redirect_from:
- /library/monoid/acted_monoid.hpp
- /library/monoid/acted_monoid.hpp.html
title: monoid/acted_monoid.hpp
---
