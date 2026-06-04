---
title: Max Monoid
documentation_of: ../../monoid/max.hpp
---

## Overview

A monoid representing the Maximum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Maximum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::lowest()`.

## Properties

* **Operation**: `std::max(a, b)`
* **Identity Element**: `Id`
