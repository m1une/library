---
title: Bracket Monoid
documentation_of: ../../monoid/bracket.hpp
---

## Overview

A monoid for processing bracket sequences (parentheses matching). It maintains the number of successfully matched pairs, as well as the count of unmatched closing `)` and opening `(` brackets.

A sequence is considered a "valid bracket sequence" if both `unmatched_right` and `unmatched_left` are `0`.

## Example

```cpp
#include "data_structure/segtree.hpp"
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

    m1une::data_structure::Segtree<BracketM> seg(init_data);

    // Query range [3, 8) -> "(()()"
    auto res = seg.prod(3, 8);
    
    std::cout << "Matched Pairs: " << res.matched << "\n"; // Output: 2
    std::cout << "Unmatched '(': " << res.unmatched_left << "\n"; // Output: 1
    std::cout << "Unmatched ')': " << res.unmatched_right << "\n"; // Output: 0

    return 0;
}
```
