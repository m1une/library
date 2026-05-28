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

### `RollingHash(const std::string& s)`
Constructs the prefix hashes and base powers. Keeps a copy of the string for character comparisons.
* **Parameters:**
  * `s`: The target string to be hashed.
* **Complexity:** $O(N)$ time and space, where $N$ is the length of `s`.

### `long long get(int l, int r) const`
Returns the hash value of the substring $S[l \dots r-1]$.
* **Parameters:**
  * `l`: The starting index of the substring (0-indexed, inclusive).
  * `r`: The ending index of the substring (0-indexed, exclusive). Must satisfy $0 \le l \le r \le |S|$.
* **Returns:** The hash value of the specified substring.
* **Complexity:** $O(1)$ time.

### `long long concat(int l1, int r1, int l2, int r2) const`
Returns the hash of a new string formed by concatenating substring $S[l1 \dots r1-1]$ and substring $S[l2 \dots r2-1]$.
* **Parameters:**
  * `l1, r1`: The [inclusive, exclusive) bounds for the first substring.
  * `l2, r2`: The [inclusive, exclusive) bounds for the second substring.
* **Returns:** The hash value of the concatenated string.
* **Complexity:** $O(1)$ time.

### `int lcp(int l1, int r1, int l2, int r2) const`
Finds the length of the Longest Common Prefix (LCP) between two substrings.
* **Parameters:**
  * `l1, r1`: The bounds for the first substring.
  * `l2, r2`: The bounds for the second substring.
* **Returns:** The integer length of the longest common prefix.
* **Complexity:** $O(\log(\min(r1-l1, r2-l2)))$ time using binary search.

### `int compare(int l1, int r1, int l2, int r2) const`
Lexicographically compares two substrings $S[l1 \dots r1-1]$ and $S[l2 \dots r2-1]$.
* **Parameters:** Same as `lcp`.
* **Returns:** * `-1`: If the first substring is strictly smaller.
  * `0`: If both substrings are exactly equal.
  * `1`: If the first substring is strictly larger.
* **Complexity:** $O(\log N)$ time.

### `long long repeat(int l, int r, long long k) const`
Returns the hash of the substring $S[l \dots r-1]$ repeated `k` times.
* **Parameters:**
  * `l, r`: The bounds for the substring to be repeated.
  * `k`: The number of times the substring should be repeated.
* **Returns:** The hash value of the repeated string.
* **Complexity:** $O(\log k)$ time.

## Static Helper Methods

### `static long long compute_hash(const std::string& str)`
Computes the hash of a string without building the prefix arrays. Useful for obtaining the hash of a pattern string quickly.
* **Parameters:** `str`: The target string.
* **Returns:** The hash value of `str`.
* **Complexity:** $O(N)$ time, $O(1)$ auxiliary space.

### `static constexpr long long combine(long long h1, long long h2, long long base_power2)`
Safely combines two hashes. Equivalent to appending a string with hash `h2` to the right of a string with hash `h1`.
* **Parameters:**
  * `h1`: The hash of the left string.
  * `h2`: The hash of the right string.
  * `base_power2`: The value of $Base^{\text{length of the right string}} \pmod{Mod}$.
* **Returns:** The combined hash value.

### `static constexpr long long repeat_hash(long long h, long long p, long long k)`
Returns the combined hash of a string repeated `k` times.
* **Parameters:**
  * `h`: The hash of the string to be repeated.
  * `p`: The value of $Base^{\text{length of the string}} \pmod{Mod}$.
  * `k`: The number of repetitions.
* **Returns:** The hash value of the repeated string.
* 
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
