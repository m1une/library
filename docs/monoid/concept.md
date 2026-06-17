---
title: Monoid Concept
documentation_of: ../../monoid/concept.hpp
---

## Overview

`m1une::monoid::IsMonoid` is the C++20 concept used by generic data structures
such as `Segtree`. It checks that a type exposes the interface needed by the
library: a value type, an identity element, and a binary operation.

The concept checks the shape of the interface. The mathematical laws are still
the user's responsibility:

* `op` should be associative.
* `id()` should be a left and right identity for `op`.

## Concept Requirements

To satisfy `m1une::monoid::IsMonoid`, a type `M` must implement:

* `using value_type = T;`
  The type stored by the monoid.

* `static constexpr T id();`
  Returns the identity element.

* `static constexpr T op(const T& a, const T& b);`
  Combines two values.

## Commutative Group

`m1une::monoid::IsCommutativeGroup` extends `IsMonoid` with an inverse:

* `static constexpr T inv(const T& x);`
  Returns the inverse of `x` with respect to `op`.

The concept checks only that `inv` exists. The type should satisfy the
group laws, and `op` should be commutative.

## Example

```cpp
#include "monoid/concept.hpp"
#include <algorithm>

struct MinMonoid {
    using value_type = int;
    static constexpr int id() { return 1e9; }
    static constexpr int op(const int& a, const int& b) { return std::min(a, b); }
};

static_assert(m1une::monoid::IsMonoid<MinMonoid>);
```
