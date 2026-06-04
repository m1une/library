---
title: Acted Monoid Wrapper
documentation_of: ../../acted_monoid/wrapper.hpp
---

## Overview

`Wrapper` provides a convenient way to define an Acted Monoid inline without writing a separate `struct`. This is particularly useful during contests when you need to combine custom mapping logic quickly.

It uses Non-Type Template Parameters (NTTP) introduced in C++20, allowing you to pass `constexpr` functions or lambdas directly as template arguments.

## Template Parameters

- `typename T`: The type of the value element (`value_type`).
- `typename E`: The type of the operator element (`operator_type`).
- `auto Op`: A function or lambda for the value monoid operation (`T op(T, T)`).
- `auto Id`: A function or lambda returning the value identity (`T id()`).
- `auto OpComp`: A function or lambda for operator composition (`E op_comp(E, E)`).
- `auto OpId`: A function or lambda returning the operator identity (`E op_id()`).
- `auto Mapping`: A function or lambda for mapping the operator onto the value (`T mapping(E, T)`).

## Example

```cpp
#include "acted_monoid/wrapper.hpp"

// Definition of Range Add Range Min using Wrapper
constexpr long long INF = std::numeric_limits<long long>::max();
using RangeAddRangeMin = m1une::acted_monoid::Wrapper<
    long long,
    long long,
    [](long long a, long long b) { return std::min(a, b); },
    []() { return INF; },
    [](long long f, long long g) { return f + g; },
    []() { return 0LL; },
    [](long long f, long long x) { return x == INF ? INF : x + f; }
>;
```
