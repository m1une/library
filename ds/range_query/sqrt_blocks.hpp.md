---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sqrt_blocks.test.cpp
    title: verify/ds/range_query/sqrt_blocks.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/sqrt_blocks.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <utility>\n#include <vector>\n\n\
    namespace m1une {\nnamespace ds {\n\n// Square-root decomposition framework with\
    \ user-defined per-block state.\ntemplate <class T, class Block>\nstruct SqrtBlocks\
    \ {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n \
    \   std::vector<T> _values;\n    std::vector<Block> _blocks;\n\n    void initialize_blocks(int\
    \ requested_block_size) {\n        if (requested_block_size > 0) {\n         \
    \   _block_size = requested_block_size;\n        } else {\n            _block_size\
    \ = std::max(\n                1,\n                int(std::ceil(std::sqrt(static_cast<long\
    \ double>(_n))))\n            );\n        }\n        _block_count = _n == 0 ?\
    \ 0 : 1 + (_n - 1) / _block_size;\n        _blocks.resize(_block_count);\n   \
    \     for (int block_index = 0; block_index < _block_count; ++block_index) {\n\
    \            rebuild(block_index);\n        }\n    }\n\n   public:\n    SqrtBlocks()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtBlocks(std::vector<T>\
    \ values, int block_size = -1)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks(block_size);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        int left = block_index\
    \ * _block_size;\n        return {left, std::min(_n, left + _block_size)};\n \
    \   }\n\n    const std::vector<T>& values() const {\n        return _values;\n\
    \    }\n\n    const Block& block(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        return _blocks[block_index];\n\
    \    }\n\n    Block& block(int block_index) {\n        assert(0 <= block_index\
    \ && block_index < _block_count);\n        return _blocks[block_index];\n    }\n\
    \n    // Rebuilds the cached state from raw values. This does not push first.\n\
    \    void rebuild(int block_index) {\n        auto [left, right] = block_range(block_index);\n\
    \        _blocks[block_index].build(_values, left, right);\n    }\n\n    // Materializes\
    \ this block's optional lazy state into raw values.\n    void push(int block_index)\
    \ {\n        assert(0 <= block_index && block_index < _block_count);\n       \
    \ if constexpr (requires(\n            Block& current,\n            std::vector<T>&\
    \ values,\n            int left,\n            int right\n        ) {\n       \
    \     current.push(values, left, right);\n        }) {\n            auto [left,\
    \ right] = block_range(block_index);\n            _blocks[block_index].push(_values,\
    \ left, right);\n        }\n    }\n\n    T get(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        const Block& current = _blocks[block_of(index)];\n\
    \        if constexpr (requires(\n            const Block& candidate,\n      \
    \      const T& raw,\n            int position\n        ) {\n            candidate.value(raw,\
    \ position);\n        }) {\n            return current.value(_values[index], index);\n\
    \        } else if constexpr (requires(const Block& candidate, const T& raw) {\n\
    \            candidate.value(raw);\n        }) {\n            return current.value(_values[index]);\n\
    \        } else {\n            return _values[index];\n        }\n    }\n\n  \
    \  T operator[](int index) const {\n        return get(index);\n    }\n\n    void\
    \ set(int index, T value) {\n        assert(0 <= index && index < _n);\n     \
    \   int block_index = block_of(index);\n        push(block_index);\n        _values[index]\
    \ = std::move(value);\n        rebuild(block_index);\n    }\n\n    template <class\
    \ F>\n    void apply_point(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        int block_index = block_of(index);\n        push(block_index);\n\
    \        f(_values[index]);\n        rebuild(block_index);\n    }\n\n    template\
    \ <class Full, class Partial>\n    void update_range(int left, int right, Full\
    \ full, Partial partial) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        while (left < right) {\n            int block_index = left\
    \ / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                push(block_index);\n\
    \                partial(\n                    left,\n                    segment_right,\n\
    \                    block_index,\n                    _values,\n            \
    \        _blocks[block_index]\n                );\n                rebuild(block_index);\n\
    \            }\n            left = segment_right;\n        }\n    }\n\n    template\
    \ <class Full, class Partial>\n    void query_range(int left, int right, Full\
    \ full, Partial partial) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        while (left < right) {\n            int block_index =\
    \ left / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                partial(left,\
    \ segment_right, block_index, _blocks[block_index]);\n            }\n        \
    \    left = segment_right;\n        }\n    }\n};\n\n}  // namespace ds\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP\n#define M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Square-root decomposition\
    \ framework with user-defined per-block state.\ntemplate <class T, class Block>\n\
    struct SqrtBlocks {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n\
    \    std::vector<T> _values;\n    std::vector<Block> _blocks;\n\n    void initialize_blocks(int\
    \ requested_block_size) {\n        if (requested_block_size > 0) {\n         \
    \   _block_size = requested_block_size;\n        } else {\n            _block_size\
    \ = std::max(\n                1,\n                int(std::ceil(std::sqrt(static_cast<long\
    \ double>(_n))))\n            );\n        }\n        _block_count = _n == 0 ?\
    \ 0 : 1 + (_n - 1) / _block_size;\n        _blocks.resize(_block_count);\n   \
    \     for (int block_index = 0; block_index < _block_count; ++block_index) {\n\
    \            rebuild(block_index);\n        }\n    }\n\n   public:\n    SqrtBlocks()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtBlocks(std::vector<T>\
    \ values, int block_size = -1)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks(block_size);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        int left = block_index\
    \ * _block_size;\n        return {left, std::min(_n, left + _block_size)};\n \
    \   }\n\n    const std::vector<T>& values() const {\n        return _values;\n\
    \    }\n\n    const Block& block(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        return _blocks[block_index];\n\
    \    }\n\n    Block& block(int block_index) {\n        assert(0 <= block_index\
    \ && block_index < _block_count);\n        return _blocks[block_index];\n    }\n\
    \n    // Rebuilds the cached state from raw values. This does not push first.\n\
    \    void rebuild(int block_index) {\n        auto [left, right] = block_range(block_index);\n\
    \        _blocks[block_index].build(_values, left, right);\n    }\n\n    // Materializes\
    \ this block's optional lazy state into raw values.\n    void push(int block_index)\
    \ {\n        assert(0 <= block_index && block_index < _block_count);\n       \
    \ if constexpr (requires(\n            Block& current,\n            std::vector<T>&\
    \ values,\n            int left,\n            int right\n        ) {\n       \
    \     current.push(values, left, right);\n        }) {\n            auto [left,\
    \ right] = block_range(block_index);\n            _blocks[block_index].push(_values,\
    \ left, right);\n        }\n    }\n\n    T get(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        const Block& current = _blocks[block_of(index)];\n\
    \        if constexpr (requires(\n            const Block& candidate,\n      \
    \      const T& raw,\n            int position\n        ) {\n            candidate.value(raw,\
    \ position);\n        }) {\n            return current.value(_values[index], index);\n\
    \        } else if constexpr (requires(const Block& candidate, const T& raw) {\n\
    \            candidate.value(raw);\n        }) {\n            return current.value(_values[index]);\n\
    \        } else {\n            return _values[index];\n        }\n    }\n\n  \
    \  T operator[](int index) const {\n        return get(index);\n    }\n\n    void\
    \ set(int index, T value) {\n        assert(0 <= index && index < _n);\n     \
    \   int block_index = block_of(index);\n        push(block_index);\n        _values[index]\
    \ = std::move(value);\n        rebuild(block_index);\n    }\n\n    template <class\
    \ F>\n    void apply_point(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        int block_index = block_of(index);\n        push(block_index);\n\
    \        f(_values[index]);\n        rebuild(block_index);\n    }\n\n    template\
    \ <class Full, class Partial>\n    void update_range(int left, int right, Full\
    \ full, Partial partial) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        while (left < right) {\n            int block_index = left\
    \ / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                push(block_index);\n\
    \                partial(\n                    left,\n                    segment_right,\n\
    \                    block_index,\n                    _values,\n            \
    \        _blocks[block_index]\n                );\n                rebuild(block_index);\n\
    \            }\n            left = segment_right;\n        }\n    }\n\n    template\
    \ <class Full, class Partial>\n    void query_range(int left, int right, Full\
    \ full, Partial partial) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        while (left < right) {\n            int block_index =\
    \ left / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                partial(left,\
    \ segment_right, block_index, _blocks[block_index]);\n            }\n        \
    \    left = segment_right;\n        }\n    }\n};\n\n}  // namespace ds\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/sqrt_blocks.hpp
  requiredBy: []
  timestamp: '2026-06-27 19:54:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sqrt_blocks.test.cpp
documentation_of: ds/range_query/sqrt_blocks.hpp
layout: document
title: Custom Square-Root Blocks
---

## Overview

`SqrtBlocks<T, Block>` is a framework for square-root decomposition with
custom per-block state. Unlike `SqrtDecomposition<Monoid>`, it does not compute
a monoid range product or define the answer to a query.

Each `Block` may maintain any useful state, such as a sorted vector, a lazy
tag, a bitset, or a small DP table. Callbacks describe how to process a full
block and how to process a partial segment. All indices are zero-based and all
ranges are half-open `[left, right)`.

## Template Parameters

| Parameter | Description |
| --- | --- |
| `T` | Type of each raw array element. |
| `Block` | Default-constructible custom block state. It must provide `build` and may provide `push` and `value`. |

## Required Block Interface

```cpp
void build(const std::vector<T>& values, int left, int right);
```

`build` reconstructs the block state from raw values in `[left, right)`. It is
called during construction and by every `rebuild`. A block with lazy state
should initialize that state in `build`.

## Optional Block Interface

```cpp
void push(std::vector<T>& values, int left, int right);
```

`push` materializes lazy state into raw values and clears that state. If this
method is absent, `SqrtBlocks::push` does nothing.

A block may provide either value accessor:

```cpp
T value(const T& raw) const;
T value(const T& raw, int index) const;
```

`get` uses it to convert a raw element to its current logical value. If both
overloads exist, the overload receiving `index` is preferred. If neither
exists, `get` returns the raw value.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SqrtBlocks()` | Constructs an empty framework with block size 1. | $O(1)$ |
| `SqrtBlocks(std::vector<T> values, int block_size = -1)` | Builds all blocks. A non-positive block size selects approximately `ceil(sqrt(n))`. | $O(N + K C_{build})$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether there are no elements. | $O(1)$ |
| `int block_size() const` | Returns the selected block size. | $O(1)$ |
| `int block_count() const` | Returns the number of blocks. | $O(1)$ |
| `int block_of(int index) const` | Returns the block containing `index`. | $O(1)$ |
| `std::pair<int, int> block_range(int block) const` | Returns the block's half-open range. | $O(1)$ |
| `const std::vector<T>& values() const` | Returns a read-only view of raw values. | $O(1)$ |
| `const Block& block(int block) const` | Returns read-only block state. | $O(1)$ |
| `Block& block(int block)` | Returns mutable block state for custom operations. | $O(1)$ |
| `void rebuild(int block)` | Calls `build` from the block's current raw values. It does not push first. | $O(C_{build})$ |
| `void push(int block)` | Calls the optional `Block::push`. | $O(C_{push})$ |
| `T get(int index) const` | Returns the logical value, using optional `Block::value`. | $O(C_{value})$ |
| `T operator[](int index) const` | Equivalent to `get(index)`. | $O(C_{value})$ |
| `void set(int index, T value)` | Pushes the containing block, assigns the raw value, and rebuilds. | $O(C_{push} + C_{build})$ |
| `template <class F> void apply_point(int index, F f)` | Pushes, calls `f(values[index])`, and rebuilds. | $O(C_{push} + C_f + C_{build})$ |
| `template <class Full, class Partial> void update_range(int left, int right, Full full, Partial partial)` | Dispatches a range update to full and partial block callbacks. | See below. |
| `template <class Full, class Partial> void query_range(int left, int right, Full full, Partial partial) const` | Dispatches a const range query without pushing or rebuilding. | See below. |

For `update_range`, callback signatures are:

```cpp
full(block_index, Block& block);
partial(left, right, block_index, std::vector<T>& values, Block& block);
```

For `query_range`, callback signatures are:

```cpp
full(block_index, const Block& block);
partial(left, right, block_index, const Block& block);
```

The query callback can capture the `SqrtBlocks` object and call `get(index)`
while scanning a partial segment.

## Complexity

Let $B$ be the block size, $K$ the number of blocks, $F$ the number of full
blocks visited, $P$ the number of partial blocks, and $E$ the number of
elements in partial segments.

| Operation | Complexity |
| --- | --- |
| Construction | $O(K \cdot C_{build})$ for block construction, plus storing the input values |
| `get`, `operator[]` | $O(C_{value})$ |
| `set` | $O(C_{push} + C_{build})$ |
| `apply_point` | $O(C_{push} + C_f + C_{build})$ |
| `push`, `rebuild` | $O(C_{push})$, $O(C_{build})$ |
| `update_range` | $O(F C_{full} + E C_{partial} + P(C_{push} + C_{build}))$ |
| `query_range` | $O(F C_{full\ query} + E C_{partial\ query})$ |

The formulas assume the partial callback does $O(C_{partial})$ work per
element; replace that term with the callback's actual cost when it processes a
segment in another way. An update performs one push and rebuild for each
partial block. With the usual $B \approx \sqrt N$, there are $O(\sqrt N)$ full
blocks and at most $O(\sqrt N)$ partial elements.

## Example

This structure supports range addition and counts values smaller than `x`.

```cpp
#include "ds/range_query/sqrt_blocks.hpp"

#include <algorithm>
#include <utility>
#include <vector>

struct Block {
    std::vector<long long> sorted;
    long long lazy = 0;

    void build(const std::vector<long long>& a, int left, int right) {
        sorted.assign(a.begin() + left, a.begin() + right);
        std::sort(sorted.begin(), sorted.end());
        lazy = 0;
    }

    void push(std::vector<long long>& a, int left, int right) {
        for (int i = left; i < right; ++i) a[i] += lazy;
        lazy = 0;
    }

    long long value(const long long& raw) const {
        return raw + lazy;
    }
};

struct RangeAddCountLess {
    m1une::ds::SqrtBlocks<long long, Block> data;

    explicit RangeAddCountLess(std::vector<long long> values)
        : data(std::move(values)) {}

    void add(int left, int right, long long x) {
        data.update_range(
            left,
            right,
            [&](int, Block& block) { block.lazy += x; },
            [&](int l, int r, int, std::vector<long long>& a, Block&) {
                for (int i = l; i < r; ++i) a[i] += x;
            }
        );
    }

    int count_less(int left, int right, long long x) const {
        int answer = 0;
        data.query_range(
            left,
            right,
            [&](int, const Block& block) {
                answer += std::lower_bound(
                    block.sorted.begin(), block.sorted.end(), x - block.lazy
                ) - block.sorted.begin();
            },
            [&](int l, int r, int, const Block&) {
                for (int i = l; i < r; ++i) answer += data.get(i) < x;
            }
        );
        return answer;
    }
};
```

## Notes

* A full-block update calls `full` only. It does not rebuild afterward, so the
  callback may keep an efficient lazy tag or update other block state directly.
* A partial update automatically performs `push`, then `partial`, then
  `rebuild`. The partial callback may safely modify the supplied raw values.
* A const query never pushes, rebuilds, or otherwise mutates hidden state.
  Partial queries should use `get` when lazy state affects logical values.
* `values()` is intentionally read-only. Use the update operations to keep raw
  values and block state consistent.
