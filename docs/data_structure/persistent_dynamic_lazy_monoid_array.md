---
title: Persistent Dynamic Lazy Monoid Array
documentation_of: ../../data_structure/persistent_dynamic_lazy_monoid_array.hpp
---

## Overview

`PersistentDynamicLazyMonoidArray` is a path-copying implicit treap for dynamic sequences with lazy range actions and range product queries. Updates return a new sequence and keep previous versions unchanged.

It supports insertion, deletion, reversal, rotation, point assignment, range application, range products, splitting, and concatenation.

## Template Parameters

* `ActedMonoid`: An acted monoid satisfying `m1une::acted_monoid::IsActedMonoid`.

## Main Operations

* `insert`, `push_back`, `push_front`, `append`
  Return a version with values inserted. Expected $O(\log N)$ for one value and expected $O(M + \log N)$ for a vector.

* `erase`, `pop_back`, `pop_front`
  Return a version with values removed. Expected $O(\log N)$.

* `set`
  Returns a version with one value replaced. Expected $O(\log N)$.

* `apply`
  Returns a version with an operator applied to one value or a half-open range. Expected $O(\log N)$.

* `reverse`, `rotate`
  Return versions with sequence order changed. Expected $O(\log N)$; whole-sequence `reverse()` is $O(1)$.

* `prod`, `all_prod`
  Return acted-monoid products over a range or the whole sequence. Expected $O(\log N)$ for `prod`, $O(1)$ for `all_prod`.

* `split`, `split_off`
  Return persistent split versions. Expected $O(\log N)$.

* `to_vector`
  Dumps a range or the whole sequence without mutating the version. $O(K + \log N)$ for a range, $O(N)$ for all values.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/persistent_dynamic_lazy_monoid_array.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::data_structure::PersistentDynamicLazyMonoidArray<AM>;

int main() {
    Array a(std::vector<long long>{1, 2, 3, 4, 5});
    auto b = a.apply(1, 4, 10);
    auto c = b.reverse(1, 5);

    // a is still {1, 2, 3, 4, 5}
    // c is {1, 5, 14, 13, 12}
    long long sum = c.prod(0, 5).sum;
}
```
