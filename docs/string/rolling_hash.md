---
title: Static Rolling Hash
documentation_of: ../../string/rolling_hash.hpp
---

## Overview

A robust data structure that precomputes the hash values of a string's prefixes to answer substring hash queries in $O(1)$ time. It uses `__int128_t` internally to safely prevent integer overflow. 

In addition to standard substring hashes, this class supports advanced operations such as finding the Longest Common Prefix (LCP), lexicographical comparison, and string repetition in $O(\log N)$ time. It also provides static helpers for calculating hashes dynamically and powering the `monoid::RollingHash`.

## Template Parameters

* `Base`: The hash base (e.g., 10007).
* `Mod`: The modulo for the hash (e.g., 998244353 or $2^{61}-1$).

## Instance Methods

* `RollingHash(const std::string& s)`
  Constructs the prefix hashes and base powers in $O(N)$ time.

* `long long get(int l, int r)`
  Returns the hash of the substring $S[l \dots r-1]$ in $O(1)$ time.

* `long long concat(int l1, int r1, int l2, int r2)`
  Returns the hash of the concatenated substrings $S[l1 \dots r1-1]$ and $S[l2 \dots r2-1]$.

* `int lcp(int l1, int r1, int l2, int r2)`
  Finds the length of the Longest Common Prefix between $S[l1 \dots r1-1]$ and $S[l2 \dots r2-1]$ using binary search in $O(\log N)$ time.

* `int compare(int l1, int r1, int l2, int r2)`
  Lexicographically compares two substrings in $O(\log N)$ time. Returns `-1` if the first is smaller, `0` if equal, and `1` if the first is larger.

* `long long repeat(int l, int r, long long k)`
  Returns the hash of the substring $S[l \dots r-1]$ repeated $k$ times in $O(\log K)$ time.

## Static Helper Methods

* `static long long compute_hash(const std::string& str)`
  Computes the hash of a string in $O(N)$ time and $O(1)$ space, without building the prefix arrays.

* `static constexpr long long combine(long long h1, long long h2, long long base_power2)`
  Safely combines two hashes.

* `static constexpr long long repeat_hash(long long h, long long p, long long k)`
  Returns the combined hash of a string (with hash `h` and base power `p`) repeated `k` times.

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

    return 0;
}
```
