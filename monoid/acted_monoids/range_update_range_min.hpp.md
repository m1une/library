---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/acted_monoid.hpp
    title: monoid/acted_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':warning:'
    path: monoid/monoids/min_monoid.hpp
    title: monoid/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/update_monoid.hpp
    title: monoid/monoids/update_monoid.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/acted_monoids/range_update_range_min.hpp\"\n\n\n\n\
    #line 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <functional>\n#include <type_traits>\n\
    \n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 6 \"monoid/monoid.hpp\"\n#include\
    \ <concepts>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation, auto\
    \ identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 8 \"monoid/acted_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <Monoid Data, Monoid Act, auto mapping>\nstruct acted_monoid\
    \ {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\n    using data_type\
    \ = typename Data::value_type;\n    using act_type = typename Act::value_type;\n\
    \n    static_assert(std::is_convertible_v<decltype(mapping), std::function<data_type(act_type,\
    \ data_type)>>,\n                  \"mapping must work as data_type(data_type,\
    \ act_type)\");\n\n    static constexpr auto data_op = Data::op;\n    static constexpr\
    \ auto data_id = Data::id;\n    static constexpr bool data_is_commutative = Data::is_commutative;\n\
    \    static constexpr auto act_op = Act::op;\n    static constexpr auto act_id\
    \ = Act::id;\n    static constexpr bool act_is_commutative = Act::is_commutative;\n\
    \    static constexpr auto apply = mapping;\n};\n\n}  // namespace m1une\n\n\n\
    #line 1 \"monoid/monoids/min_monoid.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <limits>\n\n#line 8 \"monoid/monoids/min_monoid.hpp\"\n\nnamespace m1une {\n\
    \ntemplate <typename T>\nusing min_monoid =\n    monoid<T, [](T a, T b) { return\
    \ std::min(a, b); }, []() { return std::numeric_limits<T>::max(); }, true>;\n\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/monoids/update_monoid.hpp\"\n\n\n\n\
    #line 5 \"monoid/monoids/update_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T, T identity>\nusing update_monoid = monoid<T,\n                \
    \             [](T a, T b) {\n                                 if (b == identity)\
    \ return a;\n                                 return b;\n                    \
    \         },\n                             []() { return identity; }, false>;\n\
    \n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_update_range_min.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T, T identity>\nusing range_update_range_max\
    \ = acted_monoid<min_monoid<T>, update_monoid<T, identity>, [](T x, T a) {\n \
    \   if (a == identity) return x;\n    return a;\n}>;\n\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP\n#define M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP\
    \ 1\n\n#include \"../acted_monoid.hpp\"\n#include \"../monoids/min_monoid.hpp\"\
    \n#include \"../monoids/update_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename\
    \ T, T identity>\nusing range_update_range_max = acted_monoid<min_monoid<T>, update_monoid<T,\
    \ identity>, [](T x, T a) {\n    if (a == identity) return x;\n    return a;\n\
    }>;\n\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP\n"
  dependsOn:
  - monoid/acted_monoid.hpp
  - monoid/monoid.hpp
  - monoid/monoids/min_monoid.hpp
  - monoid/monoid.hpp
  - monoid/monoids/update_monoid.hpp
  isVerificationFile: false
  path: monoid/acted_monoids/range_update_range_min.hpp
  requiredBy:
  - monoid/prim_acted_monoids.hpp
  timestamp: '2025-09-29 17:50:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/acted_monoids/range_update_range_min.hpp
layout: document
redirect_from:
- /library/monoid/acted_monoids/range_update_range_min.hpp
- /library/monoid/acted_monoids/range_update_range_min.hpp.html
title: monoid/acted_monoids/range_update_range_min.hpp
---
