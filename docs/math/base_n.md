---
title: Base-N Numbers
documentation_of: ../../math/base_n.hpp
---

## Overview

This header converts nonnegative integers to and from positional base-$N$
digits. Digits are stored most-significant first, matching the way numerals are
normally written.

The digit representation is independent of text formatting, so bases greater
than 36 are supported. For example, base 1000 simply uses integer digits from
`0` through `999`.

## Functions

```cpp
template <std::integral Integer>
std::vector<int> to_base_n(Integer value, int base);

template <std::integral Integer, class DigitSequence>
std::optional<Integer> checked_from_base_n(
    const DigitSequence& digits,
    int base);

template <std::integral Integer, class DigitSequence>
Integer from_base_n(
    const DigitSequence& digits,
    int base);
```

`Integer` may be any standard integral type except `bool`. `base` must be at
least 2, and `to_base_n` requires a nonnegative value.

`DigitSequence` must be iterable and contain integral values other than
`bool`. Leading zeroes are accepted, and an empty digit sequence represents
zero.

| Function | Description | Complexity |
| --- | --- | --- |
| `to_base_n(value, base)` | Returns the canonical most-significant-first digits. Zero becomes `{0}`. | $O(D)$ time and memory. |
| `checked_from_base_n<Integer>(digits, base)` | Returns the represented value, or `nullopt` for an invalid digit or overflow. | $O(D)$ time and $O(1)$ memory. |
| `from_base_n<Integer>(digits, base)` | Returns the represented value; validity and representability are required. | $O(D)$ time and $O(1)$ memory. |

Here $D$ is the number of digits. A digit is valid exactly when it belongs to
`[0, base)`.

## Example

```cpp
#include "math/base_n.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> digits = m1une::math::to_base_n(255, 16);
    for (int digit : digits) std::cout << digit << " ";
    std::cout << "\n"; // 15 15

    long long value = m1une::math::from_base_n<long long>(digits, 16);
    std::cout << value << "\n"; // 255
}
```
