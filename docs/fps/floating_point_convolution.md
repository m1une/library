---
title: Floating-Point Convolution
documentation_of: ../../fps/floating_point_convolution.hpp
---

## Overview

This header computes polynomial convolution using the complex fast Fourier
transform.

It supports real coefficients of type `float`, `double`, or `long double`, and
complex coefficients using `std::complex` of those types.

## Functions

```cpp
convolution_fft(first, second);
```

For real inputs, the result is a vector of the same real type. For complex
inputs, the result is a vector of the same complex type.

```cpp
convolution_round(first, second);
```

For integral inputs, this performs a `long double` FFT and rounds every
coefficient to the nearest integer of the input type.

If either input is empty, the result is empty. Otherwise, its size is
`first.size() + second.size() - 1`.

## Complexity

Let $N$ be the output size rounded up to a power of two.

* Time: $O(N\log N)$
* Additional memory: $O(N)$

## Accuracy

FFT convolution is approximate. Error grows with transform length and
coefficient magnitude.

`convolution_round` is correct only when numerical error remains below one
half and every exact coefficient is representable by the output integer type.
For exact modular convolution, use `fps/convolution.hpp`.

Using `long double` generally improves accuracy, although its precision is
platform-dependent.

## Example

```cpp
#include "fps/floating_point_convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<double> first = {1.5, 2.0};
    std::vector<double> second = {3.0, -1.0};

    auto result = m1une::fps::convolution_fft(first, second);
    for (double value : result) std::cout << value << "\n";
}
```
