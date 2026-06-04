---
title: Affine Transformation
documentation_of: ../../math/affine.hpp
---

## Overview

A simple mathematical utility function to evaluate a linear/affine function $f(x) = ax + b$.

## Parameters

* `std::pair<T, T> f`: A pair representing the coefficients of the affine function, where `f.first` is the multiplier ($a$) and `f.second` is the addend ($b$).
* `T x`: The input value to evaluate.

## Returns

The result of the affine transformation: $a \times x + b$.
