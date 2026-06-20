---
title: Suffix Array and LCP Array
documentation_of: ../../string/suffix_array.hpp
---

## Overview

A suffix array lists every suffix starting position in lexicographic order.
Together with the LCP array, it is useful for substring counting, repeated
substrings, lexicographic queries, and offline pattern matching.

The implementation uses counting-sorted doubling and runs in
$O(N \log N)$. `lcp_array` uses Kasai's algorithm and runs in $O(N)$.

`suffix_array` supports `std::string` and other indexable sequences whose
elements are sortable. String bytes are compared as unsigned characters.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> suffix_array(const Sequence& sequence)` | Returns suffix starting positions in lexicographic order. | $O(N \log N)$ |
| `vector<int> lcp_array(const Sequence& sequence, const vector<int>& sa)` | Returns LCP lengths of adjacent suffixes. The result has length `max(N - 1, 0)`. | $O(N)$ |

For `lcp = lcp_array(s, sa)`, `lcp[i]` is the longest common prefix length of
suffixes `s[sa[i]..]` and `s[sa[i + 1]..]`.

## Example

```cpp
#include "string/suffix_array.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    auto suffixes = m1une::string::suffix_array(text);
    auto lcp = m1une::string::lcp_array(text, suffixes);

    for (int position : suffixes) std::cout << position << " ";
    std::cout << "\n"; // 5 3 1 0 4 2
}
```
