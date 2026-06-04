---
title: GCD Monoid
documentation_of: ../../monoid/gcd.hpp
---

## Overview

A monoid representing the Greatest Common Divisor (GCD) operation. This is an idempotent monoid, meaning it can be safely used with a Sparse Table for $O(1)$ Range GCD queries.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: `std::gcd(a, b)`
* **Identity Element**: $0$ (Since $\gcd(x, 0) = x$)
