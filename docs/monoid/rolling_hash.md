---
title: Rolling Hash Monoid
documentation_of: ../../monoid/rolling_hash.hpp
---

## Overview

A monoid for maintaining a dynamic rolling hash of a string on a Segment Tree. This allows you to update characters in $O(\log N)$ and query the hash of any substring in $O(\log N)$.

## Important Usage Note (Initialization)

When initializing the Segment Tree, you must convert each character of the string into the `value_type` pair: `{hash_value, base_power}`. 
For a single character, the string length is 1, so the `base_power` must be exactly `Base % Mod`.

### Example

```cpp
#include "monoid/rolling_hash.hpp"
#include <string>
#include <vector>

// Define the monoid with Base = 10007, Mod = 998244353
using RH = m1une::monoid::RollingHash<10007, 998244353>;

int main() {
    std::string S = "abracadabra";
    int N = S.length();

    // 1. Initialize leaf nodes
    std::vector<RH::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // S[i] acts as the hash value for a single character.
        // 10007 is Base^1 % Mod.
        init_data[i] = {S[i], 10007}; 
    }

    // 2. Build the Segment Tree (assuming m1une::Segtree is available)
    // m1une::Segtree<RH> seg(init_data);

    // 3. Point Update: Change S[1] ('b') to 'x'
    // seg.set(1, {'x', 10007});

    return 0;
}
```
