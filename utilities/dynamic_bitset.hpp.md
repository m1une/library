---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/dynamic_bitset.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace m1une {\n\
    namespace utilities {\n\nstruct DynamicBitset {\n   private:\n    int _n;\n  \
    \  std::vector<uint64_t> blocks;\n    static constexpr int BITS_PER_BLOCK = 64;\n\
    \n    // Clears the extra bits in the last block so that bitwise operations and\
    \ counts remain accurate\n    void clean() {\n        if (_n % BITS_PER_BLOCK\
    \ != 0) {\n            blocks.back() &= (1ULL << (_n % BITS_PER_BLOCK)) - 1;\n\
    \        }\n    }\n\n   public:\n    DynamicBitset() : _n(0) {}\n\n    explicit\
    \ DynamicBitset(int n, bool val = false) : _n(n) {\n        blocks.assign((n +\
    \ BITS_PER_BLOCK - 1) / BITS_PER_BLOCK, val ? ~0ULL : 0ULL);\n        if (val)\
    \ clean();\n    }\n\n    // Returns the size of the bitset\n    int size() const\
    \ {\n        return _n;\n    }\n\n    // Test the bit at index 'i'\n    bool test(int\
    \ i) const {\n        assert(0 <= i && i < _n);\n        return (blocks[i / BITS_PER_BLOCK]\
    \ >> (i % BITS_PER_BLOCK)) & 1;\n    }\n\n    // Set the bit at index 'i' to true\n\
    \    void set(int i) {\n        assert(0 <= i && i < _n);\n        blocks[i /\
    \ BITS_PER_BLOCK] |= (1ULL << (i % BITS_PER_BLOCK));\n    }\n\n    // Set all\
    \ bits to true\n    void set() {\n        std::fill(blocks.begin(), blocks.end(),\
    \ ~0ULL);\n        clean();\n    }\n\n    // Reset the bit at index 'i' to false\n\
    \    void reset(int i) {\n        assert(0 <= i && i < _n);\n        blocks[i\
    \ / BITS_PER_BLOCK] &= ~(1ULL << (i % BITS_PER_BLOCK));\n    }\n\n    // Reset\
    \ all bits to false\n    void reset() {\n        std::fill(blocks.begin(), blocks.end(),\
    \ 0ULL);\n    }\n\n    // Flip the bit at index 'i'\n    void flip(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i / BITS_PER_BLOCK] ^= (1ULL\
    \ << (i % BITS_PER_BLOCK));\n    }\n\n    // Flip all bits\n    void flip() {\n\
    \        for (auto& block : blocks) {\n            block = ~block;\n        }\n\
    \        clean();\n    }\n\n    // Count the number of bits set to true\n    int\
    \ count() const {\n        int res = 0;\n        for (uint64_t block : blocks)\
    \ {\n            res += __builtin_popcountll(block);\n        }\n        return\
    \ res;\n    }\n\n    // Check if any bits are set to true\n    bool any() const\
    \ {\n        for (uint64_t block : blocks) {\n            if (block != 0) return\
    \ true;\n        }\n        return false;\n    }\n\n    // Check if all bits are\
    \ set to true\n    bool all() const {\n        return count() == _n;\n    }\n\n\
    \    // Check if no bits are set to true\n    bool none() const {\n        return\
    \ !any();\n    }\n\n    // Bitwise operators\n    DynamicBitset& operator&=(const\
    \ DynamicBitset& other) {\n        assert(_n == other._n);\n        for (size_t\
    \ i = 0; i < blocks.size(); ++i) {\n            blocks[i] &= other.blocks[i];\n\
    \        }\n        return *this;\n    }\n\n    DynamicBitset& operator|=(const\
    \ DynamicBitset& other) {\n        assert(_n == other._n);\n        for (size_t\
    \ i = 0; i < blocks.size(); ++i) {\n            blocks[i] |= other.blocks[i];\n\
    \        }\n        return *this;\n    }\n\n    DynamicBitset& operator^=(const\
    \ DynamicBitset& other) {\n        assert(_n == other._n);\n        for (size_t\
    \ i = 0; i < blocks.size(); ++i) {\n            blocks[i] ^= other.blocks[i];\n\
    \        }\n        return *this;\n    }\n\n    DynamicBitset operator~() const\
    \ {\n        DynamicBitset res = *this;\n        res.flip();\n        return res;\n\
    \    }\n\n    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset&\
    \ rhs) {\n        return lhs &= rhs;\n    }\n\n    friend DynamicBitset operator|(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        return lhs |= rhs;\n    }\n\n    friend\
    \ DynamicBitset operator^(DynamicBitset lhs, const DynamicBitset& rhs) {\n   \
    \     return lhs ^= rhs;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\n#define M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace utilities {\n\nstruct DynamicBitset\
    \ {\n   private:\n    int _n;\n    std::vector<uint64_t> blocks;\n    static constexpr\
    \ int BITS_PER_BLOCK = 64;\n\n    // Clears the extra bits in the last block so\
    \ that bitwise operations and counts remain accurate\n    void clean() {\n   \
    \     if (_n % BITS_PER_BLOCK != 0) {\n            blocks.back() &= (1ULL << (_n\
    \ % BITS_PER_BLOCK)) - 1;\n        }\n    }\n\n   public:\n    DynamicBitset()\
    \ : _n(0) {}\n\n    explicit DynamicBitset(int n, bool val = false) : _n(n) {\n\
    \        blocks.assign((n + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK, val ? ~0ULL\
    \ : 0ULL);\n        if (val) clean();\n    }\n\n    // Returns the size of the\
    \ bitset\n    int size() const {\n        return _n;\n    }\n\n    // Test the\
    \ bit at index 'i'\n    bool test(int i) const {\n        assert(0 <= i && i <\
    \ _n);\n        return (blocks[i / BITS_PER_BLOCK] >> (i % BITS_PER_BLOCK)) &\
    \ 1;\n    }\n\n    // Set the bit at index 'i' to true\n    void set(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i / BITS_PER_BLOCK] |= (1ULL\
    \ << (i % BITS_PER_BLOCK));\n    }\n\n    // Set all bits to true\n    void set()\
    \ {\n        std::fill(blocks.begin(), blocks.end(), ~0ULL);\n        clean();\n\
    \    }\n\n    // Reset the bit at index 'i' to false\n    void reset(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i / BITS_PER_BLOCK] &= ~(1ULL\
    \ << (i % BITS_PER_BLOCK));\n    }\n\n    // Reset all bits to false\n    void\
    \ reset() {\n        std::fill(blocks.begin(), blocks.end(), 0ULL);\n    }\n\n\
    \    // Flip the bit at index 'i'\n    void flip(int i) {\n        assert(0 <=\
    \ i && i < _n);\n        blocks[i / BITS_PER_BLOCK] ^= (1ULL << (i % BITS_PER_BLOCK));\n\
    \    }\n\n    // Flip all bits\n    void flip() {\n        for (auto& block :\
    \ blocks) {\n            block = ~block;\n        }\n        clean();\n    }\n\
    \n    // Count the number of bits set to true\n    int count() const {\n     \
    \   int res = 0;\n        for (uint64_t block : blocks) {\n            res +=\
    \ __builtin_popcountll(block);\n        }\n        return res;\n    }\n\n    //\
    \ Check if any bits are set to true\n    bool any() const {\n        for (uint64_t\
    \ block : blocks) {\n            if (block != 0) return true;\n        }\n   \
    \     return false;\n    }\n\n    // Check if all bits are set to true\n    bool\
    \ all() const {\n        return count() == _n;\n    }\n\n    // Check if no bits\
    \ are set to true\n    bool none() const {\n        return !any();\n    }\n\n\
    \    // Bitwise operators\n    DynamicBitset& operator&=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        for (size_t i = 0; i < blocks.size();\
    \ ++i) {\n            blocks[i] &= other.blocks[i];\n        }\n        return\
    \ *this;\n    }\n\n    DynamicBitset& operator|=(const DynamicBitset& other) {\n\
    \        assert(_n == other._n);\n        for (size_t i = 0; i < blocks.size();\
    \ ++i) {\n            blocks[i] |= other.blocks[i];\n        }\n        return\
    \ *this;\n    }\n\n    DynamicBitset& operator^=(const DynamicBitset& other) {\n\
    \        assert(_n == other._n);\n        for (size_t i = 0; i < blocks.size();\
    \ ++i) {\n            blocks[i] ^= other.blocks[i];\n        }\n        return\
    \ *this;\n    }\n\n    DynamicBitset operator~() const {\n        DynamicBitset\
    \ res = *this;\n        res.flip();\n        return res;\n    }\n\n    friend\
    \ DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs) {\n   \
    \     return lhs &= rhs;\n    }\n\n    friend DynamicBitset operator|(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        return lhs |= rhs;\n    }\n\n    friend\
    \ DynamicBitset operator^(DynamicBitset lhs, const DynamicBitset& rhs) {\n   \
    \     return lhs ^= rhs;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/dynamic_bitset.hpp
  requiredBy: []
  timestamp: '2026-06-18 03:50:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/dynamic_bitset.hpp
layout: document
title: Dynamic Bitset
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
