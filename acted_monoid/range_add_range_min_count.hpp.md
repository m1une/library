---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/min_count.hpp
    title: MinCount Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_min_count.hpp\"\n\n\n\n#line\
    \ 1 \"monoid/min_count.hpp\"\n\n\n\n#include <utility>\n#include <limits>\n#include\
    \ <functional>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for finding\
    \ the optimal value and its frequency in a range.\n// Uses a comparison functor\
    \ (Compare) to determine the optimal value (default is less, i.e., minimum).\n\
    template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare =\
    \ std::less<T>>\nstruct MinCount {\n    using value_type = std::pair<T, int>;\n\
    \n    // The identity element has the specified Id value and a count of 0.\n \
    \   static constexpr value_type id() {\n        return {Id, 0};\n    }\n\n   \
    \ // Combines two elements, updating the optimal value and summing the counts\
    \ if they are equal.\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        if (Compare()(a.first, b.first)) return a;\n\
    \        if (Compare()(b.first, a.first)) return b;\n        return {a.first,\
    \ a.second + b.second};\n    }\n\n    // Helper to securely create a leaf node\
    \ from a single value.\n    static constexpr value_type make(const T& val, int\
    \ count = 1) {\n        return {val, count};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 7 \"acted_monoid/range_add_range_min_count.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id\
    \ = std::numeric_limits<T>::max(), typename Compare = std::less<T>>\nstruct RangeAddRangeMinCount\
    \ {\n    using BaseMonoid = m1une::monoid::MinCount<T, Id, Compare>;\n    using\
    \ value_type = typename BaseMonoid::value_type; // std::pair<T, int>\n    using\
    \ operator_type = T;\n\n    // Value Monoid (Min Count)\n    static constexpr\
    \ value_type id() { return BaseMonoid::id(); }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return BaseMonoid::op(a,\
    \ b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() { return T(0); }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.second == 0) return x; // Do not apply to the identity element\n\
    \        return {x.first + f, x.second};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val, int count =\
    \ 1) {\n        return BaseMonoid::make(val, count);\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP\
    \ 1\n\n#include \"../monoid/min_count.hpp\"\n#include <limits>\n#include <functional>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id =\
    \ std::numeric_limits<T>::max(), typename Compare = std::less<T>>\nstruct RangeAddRangeMinCount\
    \ {\n    using BaseMonoid = m1une::monoid::MinCount<T, Id, Compare>;\n    using\
    \ value_type = typename BaseMonoid::value_type; // std::pair<T, int>\n    using\
    \ operator_type = T;\n\n    // Value Monoid (Min Count)\n    static constexpr\
    \ value_type id() { return BaseMonoid::id(); }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return BaseMonoid::op(a,\
    \ b);\n    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type\
    \ op_id() { return T(0); }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return f + g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.second == 0) return x; // Do not apply to the identity element\n\
    \        return {x.first + f, x.second};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val, int count =\
    \ 1) {\n        return BaseMonoid::make(val, count);\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP\n"
  dependsOn:
  - monoid/min_count.hpp
  isVerificationFile: false
  path: acted_monoid/range_add_range_min_count.hpp
  requiredBy: []
  timestamp: '2026-06-04 18:10:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_add_range_min_count.hpp
layout: document
title: Range Add Range Min Count
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and **its frequency (count)** in a range.

Adding a uniform constant to a range shifts all elements by the same amount. Because relative differences remain unchanged, the count of the minimum element stays exactly the same, allowing the mapping operation to be performed in $O(1)$ time.

By reusing `m1une::monoid::MinCount`, this structure can easily be converted to **Range Add Range Max Count** by passing `std::greater<T>` as the comparison functor.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min_count.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMinCount<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Initial min is 4, appearing 2 times
    auto q1 = seg.prod(0, N);
    std::cout << "Min: " << q1.first << ", Count: " << q1.second << "\n"; // Output: Min: 4, Count: 2

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4, appearing 1 time
    auto q2 = seg.prod(0, N);
    std::cout << "Min: " << q2.first << ", Count: " << q2.second << "\n"; // Output: Min: 4, Count: 1

    return 0;
}
