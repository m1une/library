---
title: Dynamic Bitset
documentation_of: ../../utilities/dynamic_bitset.hpp
---

## Overview

`DynamicBitset` is a dynamically-sized packed bit array. Unlike `std::bitset`, whose size must be a compile-time constant, `DynamicBitset` stores bits in `std::vector<uint64_t>`, so the logical size can be decided at runtime.

Bits are packed into 64-bit blocks. Single-bit access is constant time, while bulk operations scan one machine word at a time. The implementation keeps unused bits in the last block cleared, so `popcount()`, `all()`, `topbit()`, and bitwise operations operate only on the logical bit range.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `DynamicBitset()` | Initializes an empty bitset of size `0`. | $O(1)$ |
| `explicit DynamicBitset(int n, bool val = false)` | Initializes a bitset of size `n`. If `val` is `true`, all logical bits are set to `1`; otherwise they are set to `0`. | $O(N / 64)$ |
| `int size() const` | Returns the logical number of bits. | $O(1)$ |
| `bool test(int i) const` | Returns whether bit `i` is set. | $O(1)$ |
| `void set(int i)` | Sets bit `i` to `true`. | $O(1)$ |
| `void set()` | Sets all logical bits to `true`. | $O(N / 64)$ |
| `void reset(int i)` | Sets bit `i` to `false`. | $O(1)$ |
| `void reset()` | Sets all bits to `false`. | $O(N / 64)$ |
| `void flip(int i)` | Flips bit `i`. | $O(1)$ |
| `void flip()` | Flips all logical bits. | $O(N / 64)$ |
| `int popcount() const` | Returns the number of set bits. This replaces the old `count()` name. | $O(N / 64)$ |
| `int lowbit() const` | Returns the smallest index `i` such that bit `i` is set, or `-1` if no bit is set. | $O(N / 64)$ |
| `int topbit() const` | Returns the largest index `i` such that bit `i` is set, or `-1` if no bit is set. | $O(N / 64)$ |
| `bool any() const` | Returns `true` if at least one bit is set. | $O(N / 64)$ |
| `bool all() const` | Returns `true` if all logical bits are set. For size `0`, this returns `true`. | $O(N / 64)$ |
| `bool none() const` | Returns `true` if no bit is set. | $O(N / 64)$ |
| `operator&=`, `operator|=`, `operator^=` | Performs an in-place bitwise operation with another bitset of the same size. | $O(N / 64)$ |
| `operator&`, `operator|`, `operator^`, `operator~` | Returns the result of a bitwise operation. | $O(N / 64)$ |

## Notes

- `count()` was renamed to `popcount()` to make the operation explicit and consistent with CPU terminology.
- `lowbit()` and `topbit()` return bit indices, not bit masks.
- The implementation uses `__builtin_popcountll`, `__builtin_ctzll`, and `__builtin_clzll`, so it targets GCC/Clang-compatible competitive-programming environments.
- Unused high bits in the last 64-bit block are always cleared after operations that may touch them.

## Example

```cpp
#include "utilities/dynamic_bitset.hpp"
#include <iostream>

int main() {
    m1une::utilities::DynamicBitset bs(100);

    bs.set(10);
    bs.set(25);
    bs.flip(50);

    std::cout << bs.popcount() << "\n";  // 3
    std::cout << bs.lowbit() << "\n";    // 10
    std::cout << bs.topbit() << "\n";    // 50
    std::cout << bs.test(99) << "\n";   // 0

    m1une::utilities::DynamicBitset bs2(100, true);
    bs2.reset(10);

    m1une::utilities::DynamicBitset bs3 = bs & bs2;

    std::cout << bs3.test(10) << "\n";      // 0
    std::cout << bs3.popcount() << "\n";    // 2
    std::cout << (~bs3).popcount() << "\n"; // 98

    return 0;
}
```
