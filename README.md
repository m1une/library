[![Actions Status](https://github.com/m1une/library/workflows/verify/badge.svg)](https://github.com/m1une/library/actions)  [![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=m1une's+library+&color=brightgreen&logo=github)](https://m1une.github.io/library/)

# m1une's library

C++20 library for competitive programming by [m1une](https://atcoder.jp/users/m1une).

This repository is organized as header-only building blocks. Data structures live in
`data_structure/`, and reusable algebraic definitions live in `monoid/` and
`acted_monoid/` so they can be combined without rewriting boilerplate during a
contest.

## Structure

| Directory | Contents |
| --- | --- |
| `graph/` | General graph container and algorithms for shortest paths, components, cycles, DAGs, lowlink, and MST. |
| `flow/` | Flow-network algorithms such as max flow, min-cost flow, and bounded flow. |
| `data_structure/` | Segment trees, sparse table, DSU, ordered sets, hash tables, and related containers. |
| `monoid/` | Reusable monoids for generic data structures such as `Segtree`. |
| `acted_monoid/` | Acted monoids for lazy propagation data structures such as `LazySegtree`. |
| `math/`, `string/`, `utilities/` | Standalone helpers. |
| `verify/` | Online Judge Verify Helper tests. |
| `docs/` | Markdown documentation for the public headers. |

## Usage

Include headers directly from the repository root and compile with C++20:

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/add.hpp"
```

Most generic data structures are parameterized by a monoid or acted monoid, so prefer the ready-made definitions in `monoid/` and `acted_monoid/` when possible.

```cpp
using Sum = m1une::monoid::Add<long long>;
m1une::data_structure::Segtree<Sum> seg(std::vector<long long>{1, 2, 3, 4});

seg.set(1, 10);
long long answer = seg.prod(0, 3);  // 1 + 10 + 3
```

## Documentation Conventions

* Ranges are half-open: `[l, r)` includes `l` and excludes `r`.
* Indices are zero-based.
* `prod(l, r)` means "fold the values in `[l, r)` with the selected monoid".
* Lazy segment trees use acted monoids: the value monoid describes queries, and
  the operator monoid describes updates.
* Some monoids store metadata in their `value_type`. When a monoid provides
  `make(value)` or `make(value, index)`, the data structures use it automatically
  while building from a vector of another type.

## Verification

The repository is configured for `online-judge-verify-helper`. Locally, the core verification files can also be compiled with:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -I. verify/data_structure/segtree.test.cpp
```
