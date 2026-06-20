# Data structures

Choose a category by the operation you need during a contest.

| Category | Headers |
| --- | --- |
| [`dsu/`](dsu/) | `dsu.hpp`, `dsu_monoid.hpp`, `potentialized_dsu.hpp`, `persistent_dsu.hpp` |
| [`segtree/`](segtree/) | `segtree.hpp`, `lazy_segtree.hpp`, `dual_segtree.hpp`, and their persistent variants |
| [`range_query/`](range_query/) | `fenwick_tree.hpp`, `sparse_table.hpp`, `disjoint_sparse_table.hpp` |
| [`dynamic_array/`](dynamic_array/) | Dynamic and persistent implicit-treap arrays, with optional monoid or lazy aggregation |
| [`ordered_set/`](ordered_set/) | Ordered sets, multisets, and a binary trie for integer xor queries |
| [`dynamic_tree/`](dynamic_tree/) | Link-cut tree, path-oriented variants, and rake-compress link-cut tree |
| [`hash_table/`](hash_table/) | `hash_map.hpp`, `hash_set.hpp`, and their shared implementation |

Include headers from the repository root:

```cpp
#include "ds/segtree/segtree.hpp"
```
