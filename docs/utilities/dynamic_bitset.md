---
title: Dynamic Bitset
documentation_of: ../../utilities/dynamic_bitset.hpp
---

## Overview

A data structure representing a dynamically-sized array of bits. Unlike `std::bitset`, whose size must be defined as a template parameter at compile-time, `DynamicBitset` wraps a `std::vector<uint64_t>` to allow the size to be determined at runtime. 

It retains the performance benefits of packing bits into 64-bit words, enabling fast bulk operations (processing 64 bits per CPU cycle) and hardware-accelerated set-bit counting (`popcount`).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `DynamicBitset()` | Initializes an empty bitset of size 0. | $O(1)$ |
| `explicit DynamicBitset(int n, bool val = false)` | Initializes a bitset of size `n`. If `val` is `true`, all bits are set to `1`; otherwise `0`. | $O(N / 64)$ |
| `int size() const` | Returns the logical number of bits in the bitset. | $O(1)$ |
| `bool test(int i) const` | Returns the boolean value of the bit at index `i`. | $O(1)$ |
| `void set(int i)` | Sets the bit at index `i` to `true`. | $O(1)$ |
| `void set()` | Sets all bits to `true`. | $O(N / 64)$ |
| `void reset(int i)` | Sets the bit at index `i` to `false`. | $O(1)$ |
| `void reset()` | Sets all bits to `false`. | $O(N / 64)$ |
| `void flip(int i)` | Flips the bit at index `i`. | $O(1)$ |
| `void flip()` | Flips all bits. | $O(N / 64)$ |
| `int count() const` | Returns the total number of bits set to `true`. | $O(N / 64)$ |
| `bool any() const` | Returns `true` if at least one bit is set to `true`. | $O(N / 64)$ |
| `bool all() const` | Returns `true` if all bits are set to `true`. | $O(N / 64)$ |
| `bool none() const` | Returns `true` if no bits are set to `true`. | $O(N / 64)$ |
| `operator&=`, `operator|=`, `operator^=`, `operator~` | Performs bulk bitwise operations between two bitsets of the same size. | $O(N / 64)$ |

## Example

```cpp
#include "utilities/dynamic_bitset.hpp"
#include <iostream>

int main() {
    // Create a bitset of size 100, initialized to false (0)
    m1une::utilities::DynamicBitset bs(100);

    bs.set(10);
    bs.set(25);
    bs.flip(50);

    std::cout << bs.count() << "\n";       // Output: 3
    std::cout << bs.test(10) << "\n";      // Output: 1 (true)
    std::cout << bs.test(99) << "\n";      // Output: 0 (false)

    // Create another bitset of size 100, initialized to true (1)
    m1une::utilities::DynamicBitset bs2(100, true);
    bs2.reset(10);

    // Bitwise operations
    m1une::utilities::DynamicBitset bs3 = bs & bs2;
    
    std::cout << bs3.test(10) << "\n";     // Output: 0 (since it was reset in bs2)
    std::cout << bs3.count() << "\n";      // Output: 2

    return 0;
}
```
