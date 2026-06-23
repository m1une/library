# Data structures

Choose a category by the operation you need during a contest.

| Category | Headers |
| --- | --- |
| [`dsu/`](dsu/) | `dsu.hpp`, `dsu_monoid.hpp`, `potentialized_dsu.hpp`, `persistent_dsu.hpp` |
| [`segtree/`](segtree/) | Dense, dynamic, lazy, dual, Beats, and persistent segment-tree variants |
| [`range_query/`](range_query/) | SWAG, Mo's algorithm, range inversions, square-root decomposition, Fenwick tree, sqrt/sparse tables, and wavelet matrices |
| [`dynamic_array/`](dynamic_array/) | Dynamic and persistent implicit-treap arrays, with optional monoid or lazy aggregation |
| [`ordered_set/`](ordered_set/) | Ordered sets, multisets, and binary tries for integer xor queries and monoid aggregates |
| [`dynamic_tree/`](dynamic_tree/) | Link-cut tree, path-oriented variants, and rake-compress link-cut tree |
| [`dynamic_connectivity/`](dynamic_connectivity/) | Online and offline fully dynamic undirected connectivity |
| [`heap/`](heap/) | Pairing-based meldable priority queue |
| [`hash_table/`](hash_table/) | `hash_map.hpp`, `hash_set.hpp`, and their shared implementation |

Include headers from the repository root:

```cpp
#include "ds/segtree/segtree.hpp"
```
