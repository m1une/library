---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: monoid/acted_monoid.hpp
    title: Acted Monoid
  - icon: ':x:'
    path: monoid/acted_monoid.hpp
    title: Acted Monoid
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
    path: monoid/acted_monoids/range_affine_range_minmax.hpp
    title: monoid/acted_monoids/range_affine_range_minmax.hpp
  - icon: ':x:'
    path: monoid/acted_monoids/range_affine_range_sum.hpp
    title: monoid/acted_monoids/range_affine_range_sum.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_max.hpp
    title: monoid/acted_monoids/range_update_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_min.hpp
    title: monoid/acted_monoids/range_update_range_min.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_sum.hpp
    title: monoid/acted_monoids/range_update_range_sum.hpp
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':x:'
    path: monoid/monoid_addsz.hpp
    title: monoid/monoid_addsz.hpp
  - icon: ':x:'
    path: monoid/monoids/add_monoid.hpp
    title: monoid/monoids/add_monoid.hpp
  - icon: ':question:'
    path: monoid/monoids/affine_monoid.hpp
    title: monoid/monoids/affine_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/max_monoid.hpp
    title: monoid/monoids/max_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/min_monoid.hpp
    title: monoid/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/minmax_monoid.hpp
    title: monoid/monoids/minmax_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/update_monoid.hpp
    title: monoid/monoids/update_monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/prim_acted_monoids.hpp\"\n\n\n\n#line 1 \"monoid/acted_monoid.hpp\"\
    \n\n\n\n#include <concepts>\n#include <functional>\n#include <type_traits>\n\n\
    #line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 7 \"monoid/monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <typename T, auto operation, auto identity, bool commutative>\n\
    struct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
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
    \ m1une\n\n\n#line 1 \"monoid/acted_monoids/range_add_range_min.hpp\"\n\n\n\n\
    #line 1 \"monoid/monoids/add_monoid.hpp\"\n\n\n\n#line 5 \"monoid/monoids/add_monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing add_monoid = monoid<T, [](T\
    \ a, T b) { return a + b; }, []() { return T(0); }, true>;\n\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/monoids/min_monoid.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\n#line 8 \"monoid/monoids/min_monoid.hpp\"\n\nnamespace m1une\
    \ {\n\ntemplate <typename T>\nusing min_monoid =\n    monoid<T, [](T a, T b) {\
    \ return std::min(a, b); }, []() { return std::numeric_limits<T>::max(); }, true>;\n\
    \n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_add_range_min.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing range_add_range_min_monoid\
    \ = acted_monoid<min_monoid<T>, add_monoid<T>, [](T a, T x) { return a + x; }>;\n\
    \n}  // namespace m1une\n\n\n#line 1 \"monoid/acted_monoids/range_add_range_max.hpp\"\
    \n\n\n\n#line 1 \"monoid/monoids/max_monoid.hpp\"\n\n\n\n#line 6 \"monoid/monoids/max_monoid.hpp\"\
    \n\n#line 8 \"monoid/monoids/max_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing max_monoid =\n    monoid<T, [](T a, T b) { return std::max(a,\
    \ b); }, []() { return std::numeric_limits<T>::min(); }, true>;\n\n}  // namespace\
    \ m1une\n\n\n#line 7 \"monoid/acted_monoids/range_add_range_max.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <typename T>\nusing range_add_range_max_monoid = acted_monoid<max_monoid<T>,\
    \ add_monoid<T>, [](T a, T x) { return a + x; }>;\n\n}  // namespace m1une\n\n\
    \n#line 1 \"monoid/acted_monoids/range_add_range_sum.hpp\"\n\n\n\n#line 1 \"monoid/monoid_addsz.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoid_addsz.hpp\"\n\n#line 7 \"monoid/monoid_addsz.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nstruct value_and_size {\n    T\
    \ value;\n    int size;\n};\n\ntemplate <Monoid M>\nusing monoid_addsz = monoid<value_and_size<typename\
    \ M::value_type>,\n                            [](value_and_size<typename M::value_type>\
    \ a, value_and_size<typename M::value_type> b) {\n                           \
    \     return value_and_size<typename M::value_type>{M::op(a.value, b.value), a.size\
    \ + b.size};\n                            },\n                            []()\
    \ { return value_and_size<typename M::value_type>{M::id(), 0}; }, M::is_commutative>;\n\
    \n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_add_range_sum.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing range_add_range_sum_monoid\
    \ =\n    acted_monoid<monoid_addsz<add_monoid<T>>, add_monoid<T>,\n          \
    \       [](T a, typename monoid_addsz<add_monoid<T>>::data_type x) {\n       \
    \              return typename monoid_addsz<add_monoid<T>>::data_type{x.value\
    \ + a * x.size, x.size};\n                 }>;\n\n}  // namespace m1une\n\n\n\
    #line 1 \"monoid/acted_monoids/range_update_range_min.hpp\"\n\n\n\n#line 1 \"\
    monoid/monoids/update_monoid.hpp\"\n\n\n\n#line 5 \"monoid/monoids/update_monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T, T identity>\nusing update_monoid\
    \ = monoid<T,\n                             [](T a, T b) {\n                 \
    \                if (b == identity) return a;\n                              \
    \   return b;\n                             },\n                             []()\
    \ { return identity; }, false>;\n\n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_update_range_min.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T, T identity>\nusing range_update_range_max\
    \ = acted_monoid<min_monoid<T>, update_monoid<T, identity>, [](T x, T a) {\n \
    \   if (a == identity) return x;\n    return a;\n}>;\n\n}  // namespace m1une\n\
    \n\n#line 1 \"monoid/acted_monoids/range_update_range_max.hpp\"\n\n\n\n#line 7\
    \ \"monoid/acted_monoids/range_update_range_max.hpp\"\n\nnamespace m1une {\n\n\
    template <typename T, T identity>\nusing range_update_range_max = acted_monoid<max_monoid<T>,\
    \ update_monoid<T, identity>, [](T x, T a) {\n    if (a == identity) return x;\n\
    \    return a;\n}>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/acted_monoids/range_update_range_sum.hpp\"\
    \n\n\n\n#line 8 \"monoid/acted_monoids/range_update_range_sum.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <typename T, T identity>\nusing range_update_range_sum_monoid\
    \ =\n    acted_monoid<monoid_addsz<add_monoid<T>>, update_monoid<T, identity>,\n\
    \                 [](T a, typename monoid_addsz<add_monoid<T>>::data_type x) {\n\
    \                     if (a == identity) return x;\n                     return\
    \ typename monoid_addsz<add_monoid<T>>::data_type{a * x.size, x.size};\n     \
    \            }>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/acted_monoids/range_affine_range_minmax.hpp\"\
    \n\n\n\n#line 1 \"monoid/monoids/affine_monoid.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 7 \"monoid/monoids/affine_monoid.hpp\"\n\nnamespace m1une {\n\n// Affine\
    \ transformation f(x) = ax + b is represented as (a, b)\n// perform f first, then\
    \ g\n// op(f, g)(x) = g(f(x))\ntemplate <typename T>\nusing affine_monoid = monoid<std::pair<T,\
    \ T>,\n                             [](std::pair<T, T> f, std::pair<T, T> g) {\n\
    \                                 return std::pair<T, T>(f.first * g.first, f.second\
    \ * g.first + g.second);\n                             },\n                  \
    \           []() { return std::pair<T, T>(1, 0); }, false>;\n\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/monoids/minmax_monoid.hpp\"\n\n\n\n#line 7 \"monoid/monoids/minmax_monoid.hpp\"\
    \n\n#line 9 \"monoid/monoids/minmax_monoid.hpp\"\n\nnamespace m1une {\n\n// Monoid\
    \ for storing both a minimum and maximum value.\n// The operation combines two\
    \ pairs by taking the component-wise min and max.\ntemplate <typename T>\nusing\
    \ minmax_monoid =\n    monoid<std::pair<T, T>,\n           [](std::pair<T, T>\
    \ a, std::pair<T, T> b) {\n               return std::pair<T, T>(std::min(a.first,\
    \ b.first), std::max(a.second, b.second));\n           },\n           []() { return\
    \ std::pair<T, T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest());\
    \ }, true>;\n\n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_affine_range_minmax.hpp\"\
    \n\nnamespace m1une {\n\n// Acted monoid for range affine transformations and\
    \ range min/max queries.\ntemplate <typename T>\nusing range_affine_range_minmax_monoid\
    \ =\n    acted_monoid<minmax_monoid<T>, affine_monoid<T>,\n                 [](typename\
    \ affine_monoid<T>::value_type f, typename minmax_monoid<T>::value_type x) {\n\
    \                     auto v1 = f.first * x.first + f.second;\n              \
    \       auto v2 = f.first * x.second + f.second;\n                     return\
    \ std::pair<T, T>(std::min(v1, v2), std::max(v1, v2));\n                 }>;\n\
    \n}  // namespace m1une\n\n\n#line 1 \"monoid/acted_monoids/range_affine_range_sum.hpp\"\
    \n\n\n\n#line 8 \"monoid/acted_monoids/range_affine_range_sum.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <typename T>\nusing range_affine_range_sum_monoid =\n  \
    \  acted_monoid<monoid_addsz<add_monoid<T>>, affine_monoid<T>,\n             \
    \    [](typename affine_monoid<T>::value_type f, typename monoid_addsz<add_monoid<T>>::value_type\
    \ x) {\n                     // f = (a, b) is the affine transformation\n    \
    \                 // x = {value, size} is the data (sum and size of the range)\n\
    \                     // Applying f to each element xi and summing up:\n     \
    \                // sum(a*xi + b) = a * sum(xi) + b * size\n                 \
    \    return typename monoid_addsz<add_monoid<T>>::value_type{f.first * x.value\
    \ + f.second * x.size,\n                                                     \
    \                        x.size};\n                 }>;\n\n}  // namespace m1une\n\
    \n\n#line 13 \"monoid/prim_acted_monoids.hpp\"\n\n\n"
  code: '#ifndef M1UNE_PRIM_ACTED_MONOIDS_HPP

    #define M1UNE_PRIM_ACTED_MONOIDS_HPP 1


    #include "acted_monoid.hpp"

    #include "acted_monoids/range_add_range_min.hpp"

    #include "acted_monoids/range_add_range_max.hpp"

    #include "acted_monoids/range_add_range_sum.hpp"

    #include "acted_monoids/range_update_range_min.hpp"

    #include "acted_monoids/range_update_range_max.hpp"

    #include "acted_monoids/range_update_range_sum.hpp"

    #include "acted_monoids/range_affine_range_minmax.hpp"

    #include "acted_monoids/range_affine_range_sum.hpp"


    #endif  // M1UNE_PRIM_ACTED_MONOIDS_HPP

    '
  dependsOn:
  - monoid/acted_monoid.hpp
  - monoid/monoid.hpp
  - monoid/acted_monoids/range_add_range_min.hpp
  - monoid/acted_monoid.hpp
  - monoid/monoids/add_monoid.hpp
  - monoid/monoid.hpp
  - monoid/monoids/min_monoid.hpp
  - monoid/acted_monoids/range_add_range_max.hpp
  - monoid/monoids/max_monoid.hpp
  - monoid/acted_monoids/range_add_range_sum.hpp
  - monoid/monoid_addsz.hpp
  - monoid/monoid.hpp
  - monoid/acted_monoids/range_update_range_min.hpp
  - monoid/monoids/update_monoid.hpp
  - monoid/acted_monoids/range_update_range_max.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/acted_monoids/range_affine_range_minmax.hpp
  - monoid/monoids/affine_monoid.hpp
  - monoid/monoids/minmax_monoid.hpp
  - monoid/acted_monoids/range_affine_range_sum.hpp
  isVerificationFile: false
  path: monoid/prim_acted_monoids.hpp
  requiredBy: []
  timestamp: '2025-09-29 19:36:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/prim_acted_monoids.hpp
layout: document
redirect_from:
- /library/monoid/prim_acted_monoids.hpp
- /library/monoid/prim_acted_monoids.hpp.html
title: monoid/prim_acted_monoids.hpp
---
