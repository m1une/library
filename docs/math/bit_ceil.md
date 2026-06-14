---
title: Bit Ceil
documentation_of: ../../math/bit_ceil.hpp
---

## Overview

A math utility function that calculates the smallest power of two that is greater than or equal to a given number `n`.

This is frequently used internally to determine the optimal underlying array size for complete binary tree structures (like Segment Trees) so that their length is perfectly aligned to a power of 2.

## Parameters

* `T n`: The target integer.

## Returns

The smallest power of 2 $\ge n$. If $n \le 1$, it returns $1$.
