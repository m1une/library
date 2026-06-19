---
title: Static Rolling Hash
documentation_of: ../../string/rolling_hash.hpp
---

## Overview

A robust data structure that precomputes the hash values of a string's prefixes to answer substring hash queries in $O(1)$ time. It uses `__int128_t` internally to safely prevent integer overflow.

In addition to standard substring hashes, this class supports advanced operations such as finding the Longest Common Prefix (LCP), lexicographical comparison, and string repetition in $O(\log N)$ time. It also provides static helpers for calculating hashes dynamically and powering the `monoid::RollingHash`.

## Template Parameters

* `Base`: The hash base. Default is `10007`.
* `Mod`: The modulo for the hash. Default is `(1LL << 61) - 1` (a Mersenne prime for extreme collision resistance).

## Instance Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `RollingHash(const std::string& s)` | Builds prefix hashes and base powers for `s`, and keeps a copy for character comparisons. | $O(N)$ time and space |
| `long long get(int l, int r) const` | Returns the hash of substring `[l, r)`. | $O(1)$ |
| `long long concat(int l1, int r1, int l2, int r2) const` | Returns the hash of `[l1, r1)` followed by `[l2, r2)`. | $O(1)$ |
| `int lcp(int l1, int r1, int l2, int r2) const` | Returns the longest common prefix length of two substrings. | $O(\log(\min(r1 - l1, r2 - l2)))$ |
| `int compare(int l1, int r1, int l2, int r2) const` | Lexicographically compares two substrings. Returns `-1`, `0`, or `1`. | $O(\log N)$ |
| `long long repeat(int l, int r, long long k) const` | Returns the hash of substring `[l, r)` repeated `k` times. | $O(\log k)$ |

## Static Helper Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `static long long compute_hash(const std::string& str)` | Computes the hash of `str` without building prefix arrays. | $O(N)$ time, $O(1)$ auxiliary space |
| `static constexpr long long combine(long long h1, long long h2, long long base_power2)` | Returns the hash of a left string with hash `h1` followed by a right string with hash `h2`. `base_power2` is $Base^{\text{right length}} \bmod Mod$. | $O(1)$ |
| `static constexpr long long repeat_hash(long long h, long long p, long long k)` | Returns the hash of a string with hash `h` repeated `k` times. `p` is $Base^{\text{string length}} \bmod Mod$. | $O(\log k)$ |

## Example

```cpp
#include "string/rolling_hash.hpp"
#include <iostream>
#include <string>

using RH = m1une::string::RollingHash<10007, 998244353>;

int main() {
    std::string S = "abracadabra";
    RH rh(S);

    // Basic substring hash
    std::cout << (rh.get(0, 3) == rh.get(7, 10)) << "\n"; // Output: 1 (True, "abr" == "abr")

    // LCP of S[0..4] ("abrac") and S[7..11] ("abra")
    std::cout << rh.lcp(0, 5, 7, 11) << "\n"; // Output: 4

    // Lexicographical compare ("abrac" > "abra")
    std::cout << rh.compare(0, 5, 7, 11) << "\n"; // Output: 1

    // Substring repetition (Hash of "abr" repeated 100 times)
    long long repeated = rh.repeat(0, 3, 100);

    // Static compute hash (O(1) space)
    long long pattern = RH::compute_hash("cad");
    std::cout << repeated << " " << pattern << "\n";

    return 0;
}
```
