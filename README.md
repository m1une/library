[![Actions Status](https://github.com/m1une/library/workflows/verify/badge.svg)](https://github.com/m1une/library/actions)  [![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=m1une's+library+&color=brightgreen&logo=github)](https://m1une.github.io/library/)

# m1une's library

C++20 library for competitive programming by [m1une](https://atcoder.jp/users/m1une).

## Structure

* `data_structure/`: segment trees, sparse table, DSU, ordered sets, and related containers.
* `monoid/`: reusable monoids for generic data structures.
* `acted_monoid/`: acted monoids for lazy segment trees.
* `math/`, `string/`, `utilities/`: standalone helpers.
* `verify/`: online-judge-verify-helper tests.
* `docs/`: generated documentation sources for the headers.

## Usage

Include headers directly from the repository root:

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/add.hpp"
```

Most generic data structures are parameterized by a monoid or acted monoid, so prefer the ready-made definitions in `monoid/` and `acted_monoid/` when possible.

## Verification

The repository is configured for `online-judge-verify-helper`. Locally, the core verification files can also be compiled with:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -I. verify/data_structure/segtree.test.cpp
```
