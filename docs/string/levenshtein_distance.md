---
title: Levenshtein Distance
documentation_of: ../../string/levenshtein_distance.hpp
---

## Overview

`levenshtein_distance(first, second)` returns the minimum number of single-element
edits needed to transform one sequence into the other. Each insertion, deletion,
or substitution costs one.

The function works with indexable sequences such as `std::string` and
`std::vector<int>`. Both sequences must provide `size()` and equality-comparable
elements.

## Function

```cpp
template <class Sequence1, class Sequence2>
int levenshtein_distance(
    const Sequence1& first,
    const Sequence2& second);

template <class Sequence1, class Sequence2>
int levenshtein_distance(
    const Sequence1& first,
    const Sequence2& second,
    int max_distance);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `levenshtein_distance(first, second)` | Returns the unit-cost edit distance. | $O(NM)$ time and $O(\min(N,M))$ memory. |
| `levenshtein_distance(first, second, max_distance)` | Returns the distance if it is at most $K$; otherwise returns $K+1$. | $O((K+1)(N+M))$ time and $O(\min(N,M,K)+1)$ memory. |

Empty sequences are supported. In particular, the distance from an empty
sequence to a sequence of length $N$ is $N$.

Use the bounded overload when only distances up to `max_distance` matter, or
when the distance is known to be at most that value. It evaluates only the
width-$2K+1$ diagonal band that can contain an edit sequence of at most $K$
operations. `max_distance` must be nonnegative.

## Example

```cpp
#include "string/levenshtein_distance.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "kitten";
    std::string second = "sitting";

    std::cout << m1une::string::levenshtein_distance(first, second, 3) << "\n";
    // 3: substitute k -> s, substitute e -> i, then insert g.
}
```
