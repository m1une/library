---
title: Meldable Heap
documentation_of: ../../../ds/heap/meldable_heap.hpp
---

## Overview

`MeldableHeap<T, Compare>` is a pairing heap. It supports the usual priority
queue operations together with efficient destructive melding.

`PairingHeap<T, Compare>` is an alias of the same type.

## Priority Order

Comparator semantics match `std::priority_queue`:

* `std::less<T>` creates a max-heap.
* `std::greater<T>` creates a min-heap.

For a custom comparator, `top()` returns an element for which no other element
has higher priority according to that comparator.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `push(value)` | Inserts an element. | $O(1)$ |
| `emplace(args...)` | Constructs and inserts an element. | $O(1)$ |
| `top()` | Returns the highest-priority element. | $O(1)$ |
| `pop()` | Removes the highest-priority element. | Amortized $O(\log N)$ |
| `meld(std::move(other))` | Moves all elements from `other` into this heap. | $O(1)$ |
| `merge(std::move(other))` | Alias of `meld`. | $O(1)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether the heap is empty. | $O(1)$ |
| `clear()` | Removes all elements without recursive destruction. | $O(N)$ |
| `comparator()` | Returns the comparator. | $O(1)$ |

`top` and `pop` require a nonempty heap.

After melding, `other` is empty. Both heaps must use compatible comparator
states; the destination heap's comparator determines the merged ordering.

The heap is movable but not copyable. This makes ownership during melding
explicit and permits move-only element types.

## Example

```cpp
#include "ds/heap/meldable_heap.hpp"

#include <iostream>
#include <utility>

int main() {
    m1une::ds::MeldableHeap<int> first = {3, 1, 7};
    m1une::ds::MeldableHeap<int> second = {4, 6};

    first.meld(std::move(second));
    while (!first.empty()) {
        std::cout << first.top() << "\n";
        first.pop();
    }
}
```
