---
title: Monoid Wrapper
documentation_of: ../../monoid/wrapper.hpp
---

## Overview

An adapter struct that easily generates a monoid from given functions or `constexpr` lambdas using C++20 Non-Type Template Parameters (NTTP). This is extremely useful in competitive programming contests to define custom monoids (e.g., for Segment Trees) with minimal boilerplate code.

## Template Parameters

* `T`: The underlying data type of the monoid.
* `Op`: A callable object (function pointer or stateless lambda) that takes two arguments of type `T` and returns a value of type `T`.
* `Id`: A callable object (function pointer or stateless lambda) that takes no arguments and returns the identity element of type `T`.

## Methods

* `static constexpr T id()`
  Invokes `Id()` and returns the identity element.

* `static constexpr T op(const T& a, const T& b)`
  Invokes `Op(a, b)` and returns the combined result.

## Example

```cpp
#include "monoid/wrapper.hpp"

// Define the operation and identity as constexpr lambdas
constexpr auto xor_op = [](int a, int b) { return a ^ b; };
constexpr auto xor_id = []() { return 0; };

// Create the Monoid type
using XorMonoid = m1une::monoid::Wrapper<int, xor_op, xor_id>;

// Now `XorMonoid` can be passed to data structures like Segtree
// Segtree<XorMonoid> seg(n);
```
