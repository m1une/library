---
title: String Hash
documentation_of: ../../string/string_hash.hpp
---

## Overview

This header computes a compact whole-string hash using two polynomial hashes.
It is useful when strings are treated as indivisible values rather than when
arbitrary substring queries are required.

For substring hashing, longest-common-prefix queries, and comparisons, use
`RollingHash` instead.

## Hash Value

```cpp
struct StringHash {
    uint32_t first;
    uint32_t second;
    uint32_t first_power;
    uint32_t second_power;
    size_t length;
};
```

`first` and `second` are hashes modulo two different primes. The power fields
allow two known hashes to be concatenated in constant time. Equality compares
both hashes and the string length.

As with every non-cryptographic hash, equality of hashes is not a mathematical
proof that strings are equal. Using two independent moduli makes accidental
collisions unlikely in competitive-programming applications.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `hash_string(value)` | Returns the double hash of a string or string view. | $O(N)$ |
| `concat_string_hash(left, right)` | Returns the hash of the represented concatenation. | $O(1)$ |

Characters are interpreted as unsigned bytes and shifted by one, so embedded
null bytes and bytes with values from 128 through 255 are handled consistently.

The implementation is `constexpr`, permitting hashes of compile-time string
literals.

## Unordered Containers

`StringHasher` can hash `std::string`, `std::string_view`, C strings, and
`StringHash` values:

```cpp
std::unordered_set<std::string, m1une::string::StringHasher> words;
```

For standard strings this provides a deterministic double-polynomial hash.
It is intended for convenience and collision resistance, not cryptographic or
adversarial security.

## Example

```cpp
#include "string/string_hash.hpp"

#include <iostream>

int main() {
    constexpr auto hello = m1une::string::hash_string("hello");
    constexpr auto space = m1une::string::hash_string(" ");
    constexpr auto world = m1une::string::hash_string("world");

    constexpr auto left =
        m1une::string::concat_string_hash(hello, space);
    constexpr auto sentence =
        m1une::string::concat_string_hash(left, world);

    std::cout << (sentence == m1une::string::hash_string("hello world"))
              << "\n";
}
```
