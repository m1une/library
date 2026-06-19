---
title: BigInt
documentation_of: ../../utilities/bigint.hpp
---

## Overview

An arbitrary-precision signed integer for competitive programming. Digits are
stored in base $10^9$ blocks.

It supports arithmetic, comparisons, and standard stream input and output.

## Methods

| Method / Operator | Description | Complexity |
| --- | --- | --- |
| `BigInt()` | Initializes the value to `0`. | $O(1)$ |
| `BigInt(long long v)` | Initializes the BigInt from a standard 64-bit integer. | $O(1)$ |
| `BigInt(const std::string& s)` | Parses a base-10 string (with optional `+`/`-` prefix). | $O(N)$ |
| `std::string to_string() const` | Converts the BigInt back to a base-10 string. | $O(N)$ |
| `BigInt abs() const` | Returns the absolute value of the BigInt. | $O(N)$ |
| `operator+`, `operator+=` | Adds two BigInts. | $O(N)$ |
| `operator-`, `operator-=` | Subtracts one BigInt from another. | $O(N)$ |
| `operator*`, `operator*=` | Multiplies two BigInts (Standard Long Multiplication). | $O(N \cdot M)$ |
| `operator/`, `operator/=` | Divides the BigInt by another (Integer division). | $O(N \cdot M)$ |
| `operator%`, `operator%=` | Calculates the remainder of division by another BigInt. | $O(N \cdot M)$ |
| `divmod(a, b)` | Returns `std::pair<BigInt, BigInt>` containing `{a / b, a % b}`. | $O(N \cdot M)$ |
| Relational Operators | `<, >, <=, >=, ==, !=` are all fully supported. | $O(N)$ |
| Stream Operators | `<<` (output) and `>>` (input) integration. | $O(N)$ |

Here, $N$ and $M$ denote the number of base-$10^9$ blocks in the operands.
Division by zero throws `std::domain_error`.

## Example

```cpp
#include "utilities/bigint.hpp"
#include <iostream>

using m1une::utilities::BigInt;

int main() {
    BigInt a("12345678901234567890");
    BigInt b = 987654321;

    BigInt sum = a + b;
    BigInt diff = a - b;
    BigInt prod = a * b;

    // std::pair<BigInt, BigInt>
    auto [quotient, remainder] = divmod(a, b);

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Difference: " << diff << "\n";
    std::cout << "Product: " << prod << "\n";
    std::cout << "Quotient: " << quotient << " R: " << remainder << "\n";

    if (a > b) {
        std::cout << "A is larger!\n";
    }

    return 0;
}
```
