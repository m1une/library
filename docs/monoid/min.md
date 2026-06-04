---
title: Min Monoid
documentation_of: ../../monoid/min.hpp
---

## Overview

A monoid representing the Minimum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Minimum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::max()`.

## Properties

* **Operation**: `std::min(a, b)`
* **Identity Element**: `Id`
