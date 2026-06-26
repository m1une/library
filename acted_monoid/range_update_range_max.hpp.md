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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_max.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct RangeUpdateRangeMax {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Max)\n    static constexpr value_type\
    \ id() {\n        return Id;\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return std::max(a, b);\n    }\n\
    \n    // Operator Monoid (Update)\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        // Prioritize the newer\
    \ operation (f) over the older one (g)\n        return f.has_value() ? f : g;\n\
    \    }\n\n    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x == id()) return x;\n\
    \        return f.value();\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct RangeUpdateRangeMax {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Max)\n    static constexpr value_type\
    \ id() {\n        return Id;\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return std::max(a, b);\n    }\n\
    \n    // Operator Monoid (Update)\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        // Prioritize the newer\
    \ operation (f) over the older one (g)\n        return f.has_value() ? f : g;\n\
    \    }\n\n    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x == id()) return x;\n\
    \        return f.value();\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_update_range_max.hpp
layout: document
title: Range Update Range Max
---

## Overview

An Acted Monoid representing Range Update (overwrite) operations and Range Maximum queries.

### Important Usage Note

Similar to `RangeUpdateRangeMin`, this implementation uses `std::optional<T>` as the `operator_type` to safely represent the state of "no operation" (the identity element of the operator monoid).

- A valid update operation with value $v$ is represented as `std::optional<T>(v)`.
- The identity operator (no operation) is represented as `std::nullopt`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMax<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 100 -> {10, 100, 100, 100, 50}
    seg.apply(1, 4, std::optional<long long>(100));

    // Get max of [0, 2) -> max(10, 100) = 100
    std::cout << seg.prod(0, 2) << "\n";

    return 0;
}
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
