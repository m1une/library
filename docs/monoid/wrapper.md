---
title: Monoid Wrapper
documentation_of: ../../monoid/wrapper.hpp
---

## Overview

An adapter struct that easily generates a monoid from given functions or stateless lambdas using C++20 Non-Type Template Parameters (NTTP). This is extremely useful in competitive programming contests to define custom monoids (e.g., for Segment Trees) with minimal boilerplate code.

## Template Parameters

* `T`: The underlying data type of the monoid.
* `Op`: A callable object (function pointer or stateless lambda) that takes two arguments of type `T` and returns a value of type `T`.
* `Id`: A callable object (function pointer or stateless lambda) that takes no arguments and returns the identity element of type `T`.

## Example

In C++20, you can pass lambdas directly in the template arguments. This allows you to define a monoid completely inline.

```cpp
#include "monoid/wrapper.hpp"

// Define a Monoid for XOR sum inline
using XorMonoid = m1une::monoid::Wrapper<int, [](int a, int b) { return a ^ b; }, []() { return 0; }>;

// Now `XorMonoid` can be passed to data structures like Segtree
// Segtree<XorMonoid> seg(n);
```

You can also define the lambdas separately if the operations are complex:

```cpp
constexpr auto custom_op = [](long long a, long long b) { return a + b; };
constexpr auto custom_id = []() { return 0LL; };
using CustomMonoid = m1une::monoid::Wrapper<long long, custom_op, custom_id>;
```
