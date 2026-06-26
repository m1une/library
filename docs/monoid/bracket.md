---
title: Bracket Monoid
documentation_of: ../../monoid/bracket.hpp
---

## Overview

A monoid for processing bracket sequences (parentheses matching). It maintains the number of successfully matched pairs, as well as the count of unmatched closing `)` and opening `(` brackets.

A sequence is considered a "valid bracket sequence" if both `unmatched_right` and `unmatched_left` are `0`.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/bracket.hpp"
#include <iostream>
#include <string>
#include <vector>

using BracketM = m1une::monoid::Bracket;

int main() {
    std::string S = "())(()()";
    int N = S.size();

    std::vector<BracketM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = BracketM::make(S[i]);
    }

    m1une::ds::Segtree<BracketM> seg(init_data);

    // Query range [3, 8) -> "(()()"
    auto res = seg.prod(3, 8);

    std::cout << "Matched Pairs: " << res.matched << "\n"; // Output: 2
    std::cout << "Unmatched '(': " << res.unmatched_left << "\n"; // Output: 1
    std::cout << "Unmatched ')': " << res.unmatched_right << "\n"; // Output: 0

    return 0;
}
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
