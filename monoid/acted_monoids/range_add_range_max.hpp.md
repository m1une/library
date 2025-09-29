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
    path: monoid/monoids/add_monoid.hpp
    title: monoid/monoids/add_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/max_monoid.hpp
    title: monoid/monoids/max_monoid.hpp
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
  bundledCode: "#line 1 \"monoid/acted_monoids/range_add_range_max.hpp\"\n\n\n\n#line\
    \ 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <functional>\n#include <type_traits>\n\
    \n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 6 \"monoid/monoid.hpp\"\n#include\
    \ <concepts>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation, auto\
    \ identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept monoid_concept = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 8 \"monoid/acted_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <monoid_concept Data, monoid_concept Act, auto mapping>\n\
    struct acted_monoid {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\
    \n    using data_type = typename Data::value_type;\n    using act_type = typename\
    \ Act::value_type;\n\n    static_assert(std::is_convertible_v<decltype(mapping),\
    \ std::function<data_type(act_type, data_type)>>,\n                  \"mapping\
    \ must work as data_type(data_type, act_type)\");\n\n    static constexpr auto\
    \ data_op = Data::op;\n    static constexpr auto data_id = Data::id;\n    static\
    \ constexpr bool data_is_commutative = Data::is_commutative;\n    static constexpr\
    \ auto act_op = Act::op;\n    static constexpr auto act_id = Act::id;\n    static\
    \ constexpr bool act_is_commutative = Act::is_commutative;\n    static constexpr\
    \ auto apply = mapping;\n};\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/add_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoids/add_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing add_monoid = monoid<T, [](T a, T b) { return a + b; }, []()\
    \ { return T(0); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/max_monoid.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <limits>\n\n#line 8 \"monoid/monoids/max_monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing max_monoid =\n    monoid<T,\
    \ [](T a, T b) { return std::max(a, b); }, []() { return std::numeric_limits<T>::min();\
    \ }, true>;\n\n}  // namespace m1une\n\n\n#line 7 \"monoid/acted_monoids/range_add_range_max.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing range_add_range_max_monoid\
    \ = acted_monoid<max_monoid<T>, add_monoid<T>, [](T a, T x) { return a + x; }>;\n\
    \n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP

    #define M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP 1


    #include "../acted_monoid.hpp"

    #include "../monoids/add_monoid.hpp"

    #include "../monoids/max_monoid.hpp"


    namespace m1une {


    template <typename T>

    using range_add_range_max_monoid = acted_monoid<max_monoid<T>, add_monoid<T>,
    [](T a, T x) { return a + x; }>;


    }  // namespace m1une


    #endif  // M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP

    '
  dependsOn:
  - monoid/acted_monoid.hpp
  - monoid/monoid.hpp
  - monoid/monoids/add_monoid.hpp
  - monoid/monoid.hpp
  - monoid/monoids/max_monoid.hpp
  isVerificationFile: false
  path: monoid/acted_monoids/range_add_range_max.hpp
  requiredBy:
  - monoid/prim_acted_monoids.hpp
  timestamp: '2025-09-29 17:45:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/acted_monoids/range_add_range_max.hpp
layout: document
redirect_from:
- /library/monoid/acted_monoids/range_add_range_max.hpp
- /library/monoid/acted_monoids/range_add_range_max.hpp.html
title: monoid/acted_monoids/range_add_range_max.hpp
---
