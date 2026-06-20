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
    #include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct DynamicBitset {\n   private:\n\
    \    static constexpr int BITS_PER_BLOCK = 64;\n    static constexpr uint64_t\
    \ FULL_BLOCK = ~uint64_t{0};\n\n    int _n;\n    std::vector<uint64_t> blocks;\n\
    \n    static int block_count(int n) {\n        assert(n >= 0);\n        return\
    \ (n + BITS_PER_BLOCK - 1) >> 6;\n    }\n\n    uint64_t tail_mask() const {\n\
    \        const int rem = _n & (BITS_PER_BLOCK - 1);\n        return rem == 0 ?\
    \ FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n    }\n\n    // Keep unused bits in\
    \ the last block equal to zero.\n    void clean() {\n        if (!blocks.empty())\
    \ blocks.back() &= tail_mask();\n    }\n\n   public:\n    DynamicBitset() : _n(0),\
    \ blocks() {}\n\n    explicit DynamicBitset(int n, bool val = false) : _n(n),\
    \ blocks(block_count(n), val ? FULL_BLOCK : 0) {\n        if (val) clean();\n\
    \    }\n\n    // Returns the logical number of bits.\n    int size() const {\n\
    \        return _n;\n    }\n\n    // Returns whether the bit at index i is set.\n\
    \    bool test(int i) const {\n        assert(0 <= i && i < _n);\n        return\
    \ (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) & 1;\n    }\n\n    // Sets the\
    \ bit at index i to true.\n    void set(int i) {\n        assert(0 <= i && i <\
    \ _n);\n        blocks[i >> 6] |= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n\
    \    }\n\n    // Sets all bits to true.\n    void set() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), FULL_BLOCK);\n        clean();\n    }\n\n    // Sets the bit at\
    \ index i to false.\n    void reset(int i) {\n        assert(0 <= i && i < _n);\n\
    \        blocks[i >> 6] &= ~(uint64_t{1} << (i & (BITS_PER_BLOCK - 1)));\n   \
    \ }\n\n    // Sets all bits to false.\n    void reset() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), uint64_t{0});\n    }\n\n    // Flips the bit at index i.\n   \
    \ void flip(int i) {\n        assert(0 <= i && i < _n);\n        blocks[i >> 6]\
    \ ^= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n    }\n\n    // Flips all bits.\n\
    \    void flip() {\n        for (uint64_t& block : blocks) block = ~block;\n \
    \       clean();\n    }\n\n    // Returns the number of set bits.\n    int popcount()\
    \ const {\n        int res = 0;\n        for (uint64_t block : blocks) res +=\
    \ __builtin_popcountll(block);\n        return res;\n    }\n\n    // Returns the\
    \ index of the least significant set bit, or -1 if no bit is set.\n    int lowbit()\
    \ const {\n        const int m = static_cast<int>(blocks.size());\n        for\
    \ (int i = 0; i < m; ++i) {\n            if (blocks[i] != 0) return (i << 6) +\
    \ __builtin_ctzll(blocks[i]);\n        }\n        return -1;\n    }\n\n    //\
    \ Returns the index of the most significant set bit, or -1 if no bit is set.\n\
    \    int topbit() const {\n        for (int i = static_cast<int>(blocks.size())\
    \ - 1; i >= 0; --i) {\n            if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK\
    \ - 1 - __builtin_clzll(blocks[i]));\n        }\n        return -1;\n    }\n\n\
    \    // Returns whether at least one bit is set.\n    bool any() const {\n   \
    \     for (uint64_t block : blocks) {\n            if (block != 0) return true;\n\
    \        }\n        return false;\n    }\n\n    // Returns whether every logical\
    \ bit is set.\n    bool all() const {\n        if (_n == 0) return true;\n\n \
    \       const int m = static_cast<int>(blocks.size());\n        for (int i = 0;\
    \ i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK) return false;\n\
    \        }\n        return blocks.back() == tail_mask();\n    }\n\n    // Returns\
    \ whether no bit is set.\n    bool none() const {\n        return !any();\n  \
    \  }\n\n    DynamicBitset& operator&=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator|=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator^=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset operator~() const {\n        DynamicBitset res = *this;\n\
    \        res.flip();\n        return res;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs &= rhs;\n        return lhs;\n\
    \    }\n\n    friend DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset&\
    \ rhs) {\n        lhs |= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator^(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n\
    \        return lhs;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\n#define M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\n\
    struct DynamicBitset {\n   private:\n    static constexpr int BITS_PER_BLOCK =\
    \ 64;\n    static constexpr uint64_t FULL_BLOCK = ~uint64_t{0};\n\n    int _n;\n\
    \    std::vector<uint64_t> blocks;\n\n    static int block_count(int n) {\n  \
    \      assert(n >= 0);\n        return (n + BITS_PER_BLOCK - 1) >> 6;\n    }\n\
    \n    uint64_t tail_mask() const {\n        const int rem = _n & (BITS_PER_BLOCK\
    \ - 1);\n        return rem == 0 ? FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n\
    \    }\n\n    // Keep unused bits in the last block equal to zero.\n    void clean()\
    \ {\n        if (!blocks.empty()) blocks.back() &= tail_mask();\n    }\n\n   public:\n\
    \    DynamicBitset() : _n(0), blocks() {}\n\n    explicit DynamicBitset(int n,\
    \ bool val = false) : _n(n), blocks(block_count(n), val ? FULL_BLOCK : 0) {\n\
    \        if (val) clean();\n    }\n\n    // Returns the logical number of bits.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ bit at index i is set.\n    bool test(int i) const {\n        assert(0 <= i\
    \ && i < _n);\n        return (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) &\
    \ 1;\n    }\n\n    // Sets the bit at index i to true.\n    void set(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] |= uint64_t{1} << (i\
    \ & (BITS_PER_BLOCK - 1));\n    }\n\n    // Sets all bits to true.\n    void set()\
    \ {\n        std::fill(blocks.begin(), blocks.end(), FULL_BLOCK);\n        clean();\n\
    \    }\n\n    // Sets the bit at index i to false.\n    void reset(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] &= ~(uint64_t{1} <<\
    \ (i & (BITS_PER_BLOCK - 1)));\n    }\n\n    // Sets all bits to false.\n    void\
    \ reset() {\n        std::fill(blocks.begin(), blocks.end(), uint64_t{0});\n \
    \   }\n\n    // Flips the bit at index i.\n    void flip(int i) {\n        assert(0\
    \ <= i && i < _n);\n        blocks[i >> 6] ^= uint64_t{1} << (i & (BITS_PER_BLOCK\
    \ - 1));\n    }\n\n    // Flips all bits.\n    void flip() {\n        for (uint64_t&\
    \ block : blocks) block = ~block;\n        clean();\n    }\n\n    // Returns the\
    \ number of set bits.\n    int popcount() const {\n        int res = 0;\n    \
    \    for (uint64_t block : blocks) res += __builtin_popcountll(block);\n     \
    \   return res;\n    }\n\n    // Returns the index of the least significant set\
    \ bit, or -1 if no bit is set.\n    int lowbit() const {\n        const int m\
    \ = static_cast<int>(blocks.size());\n        for (int i = 0; i < m; ++i) {\n\
    \            if (blocks[i] != 0) return (i << 6) + __builtin_ctzll(blocks[i]);\n\
    \        }\n        return -1;\n    }\n\n    // Returns the index of the most\
    \ significant set bit, or -1 if no bit is set.\n    int topbit() const {\n   \
    \     for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i) {\n     \
    \       if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK - 1 - __builtin_clzll(blocks[i]));\n\
    \        }\n        return -1;\n    }\n\n    // Returns whether at least one bit\
    \ is set.\n    bool any() const {\n        for (uint64_t block : blocks) {\n \
    \           if (block != 0) return true;\n        }\n        return false;\n \
    \   }\n\n    // Returns whether every logical bit is set.\n    bool all() const\
    \ {\n        if (_n == 0) return true;\n\n        const int m = static_cast<int>(blocks.size());\n\
    \        for (int i = 0; i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK)\
    \ return false;\n        }\n        return blocks.back() == tail_mask();\n   \
    \ }\n\n    // Returns whether no bit is set.\n    bool none() const {\n      \
    \  return !any();\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator|=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator^=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset operator~() const {\n      \
    \  DynamicBitset res = *this;\n        res.flip();\n        return res;\n    }\n\
    \n    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs)\
    \ {\n        lhs &= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator|(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs |= rhs;\n\
    \        return lhs;\n    }\n\n    friend DynamicBitset operator^(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n        return lhs;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_UTILITIES_DYNAMIC_BITSET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/dynamic_bitset.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:03:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/dynamic_bitset.hpp
layout: document
title: Dynamic Bitset
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
