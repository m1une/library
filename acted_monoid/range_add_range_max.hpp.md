---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_max.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::lowest()>\nstruct RangeAddRangeMax {\n   \
    \ using value_type = T;\n    using operator_type = T;\n\n    // Value Monoid (Max)\n\
    \    static constexpr value_type id() {\n        return Id;\n    }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return std::max(a, b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr\
    \ operator_type op_id() {\n        return 0;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    // Mapping\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x == id()) return x; \
    \ // Do not apply the operator to the identity element\n        return x + f;\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct RangeAddRangeMax {\n    using value_type = T;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Max)\n    static constexpr value_type id() {\n\
    \        return Id;\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return std::max(a, b);\n    }\n\n    // Operator\
    \ Monoid (Add)\n    static constexpr operator_type op_id() {\n        return 0;\n\
    \    }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        if (x == id()) return x;  // Do not apply the operator to the identity\
    \ element\n        return x + f;\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_max.hpp
layout: document
title: Range Add Range Max
---

## Overview

An Acted Monoid representing Range Addition operations and Range Maximum queries.

It uses `std::numeric_limits<T>::lowest()` as the default identity element for the Value Monoid to correctly handle negative maximum values.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMax<long long>;

int main() {
    std::vector<long long> A = {1, 5, 2, 8, 3};
    m1une::ds::LazySegtree<AM> seg(A);

    // Get the maximum value in [1, 4) -> max(5, 2, 8) = 8
    std::cout << seg.prod(1, 4) << "\n";

    // Add 10 to range [1, 3) -> {1, 15, 12, 8, 3}
    seg.apply(1, 3, 10);

    // Get the maximum value in [1, 4) -> max(15, 12, 8) = 15
    std::cout << seg.prod(1, 4) << "\n";

    return 0;
}
```
