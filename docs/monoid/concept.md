---
title: Monoid Concept
documentation_of: ../../monoid/concept.hpp
---

## Overview

Provides a C++20 `concept` to constrain template arguments for Monoids. This ensures that the given type satisfies the mathematical requirements of a monoid, enabling safer and more readable template instantiations (e.g., in Segment Trees).

## Concept Requirements

To satisfy `m1une::monoid::IsMonoid`, a struct `M` must implement the following:

* `using value_type = T;`
  An alias for the underlying type of the monoid.
  
* `static constexpr T id();`
  A static function returning the identity element of the monoid.
  
* `static constexpr T op(const T& a, const T& b);`
  A static function representing the associative binary operation.

## Example

```cpp
#include "monoid/concept.hpp"
#include <algorithm>

struct MinMonoid {
    using value_type = int;
    static constexpr int id() { return 1e9; }
    static constexpr int op(const int& a, const int& b) { return std::min(a, b); }
};

// This assertion will pass at compile time
static_assert(m1une::monoid::IsMonoid<MinMonoid>);
```
