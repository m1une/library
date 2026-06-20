---
title: Manacher Algorithm
documentation_of: ../../string/manacher.hpp
---

## Overview

`manacher(sequence)` finds every maximal odd- and even-length palindrome in
linear time. The result also answers whether any substring is a palindrome in
$O(1)$.

The function is generic over indexable sequences with comparable elements.

## Result

`ManacherResult` contains:

| Member / Method | Meaning | Complexity |
| --- | --- | --- |
| `odd[i]` | Radius including center `i`; palindrome `[i - odd[i] + 1, i + odd[i])`. | Access $O(1)$ |
| `even[i]` | Radius centered between `i - 1` and `i`; palindrome `[i - even[i], i + even[i])`. | Access $O(1)$ |
| `size()` | Returns the original sequence length. | $O(1)$ |
| `empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `is_palindrome(l, r)` | Returns whether `[l, r)` is a palindrome. | $O(1)$ |
| `longest_length()` | Returns the longest palindromic substring length. | $O(N)$ |

Construction takes $O(N)$ time and space.

## Example

```cpp
#include "string/manacher.hpp"

#include <iostream>
#include <string>

int main() {
    auto palindromes = m1une::string::manacher(std::string("abacaba"));

    std::cout << palindromes.longest_length() << "\n";      // 7
    std::cout << palindromes.is_palindrome(1, 6) << "\n";   // 1
    std::cout << palindromes.is_palindrome(0, 4) << "\n";   // 0
}
```
