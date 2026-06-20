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
  bundledCode: "#line 1 \"acted_monoid/range_add_range_min.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max()>\nstruct RangeAddRangeMin {\n    using\
    \ value_type = T;\n    using operator_type = T;\n\n    // Value Monoid (Min)\n\
    \    static constexpr value_type id() {\n        return Id;\n    }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return std::min(a, b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr\
    \ operator_type op_id() {\n        return 0;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    // Mapping\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x == id()) return x; \
    \ // Do not apply the operator to the identity element\n        return x + f;\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct RangeAddRangeMin {\n    using value_type = T;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Min)\n    static constexpr value_type id() {\n\
    \        return Id;\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return std::min(a, b);\n    }\n\n    // Operator\
    \ Monoid (Add)\n    static constexpr operator_type op_id() {\n        return 0;\n\
    \    }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        if (x == id()) return x;  // Do not apply the operator to the identity\
    \ element\n        return x + f;\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_min.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_min.hpp
layout: document
title: Range Add Range Min
---

## Overview

An Acted Monoid representing Range Addition operations and Range Minimum queries. It safely handles the identity element to prevent wrapping or incorrect modifications on uninitialized values.

## Template Parameters

* `T`: The underlying scalar data type (e.g., `long long`, `int`).
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add -15 to all elements in range [1, 4) -> {10, 5, 15, 25, 50}
    seg.apply(1, 4, -15);

    // Get the minimum in range [0, 3) -> min(10, 5, 15) = 5
    std::cout << seg.prod(0, 3) << "\n";

    return 0;
}
```
