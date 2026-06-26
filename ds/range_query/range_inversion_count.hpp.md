---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_inversion_count.test.cpp
    title: verify/ds/range_query/range_inversion_count.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/range_inversion_count.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Static range inversion counts with O(N sqrt N)\
    \ preprocessing and\n// O(sqrt N log N) queries.\ntemplate <class T>\nstruct RangeInversionCount\
    \ {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n \
    \   int _value_count;\n    std::vector<int> _rank;\n    std::vector<std::vector<int>>\
    \ _boundary_less;\n    std::vector<std::vector<int>> _local_inversion;\n    std::vector<long\
    \ long> _block_inversion;\n    std::vector<std::vector<long long>> _full_block_inversion;\n\
    \n    int block_start(int block) const {\n        return block * _block_size;\n\
    \    }\n\n    int block_end(int block) const {\n        return std::min(_n, block_start(block)\
    \ + _block_size);\n    }\n\n    int local_index(int block, int offset, int length)\
    \ const {\n        int block_length = block_end(block) - block_start(block);\n\
    \        return offset * (block_length + 1)\n               - offset * (offset\
    \ - 1) / 2\n               + length;\n    }\n\n    long long local_query(int left,\
    \ int right) const {\n        if (right - left <= 1) return 0;\n        int block\
    \ = left / _block_size;\n        int offset = left - block_start(block);\n   \
    \     return _local_inversion[block][\n            local_index(block, offset,\
    \ right - left)\n        ];\n    }\n\n    int count_less_blocks(int first_block,\
    \ int last_block, int rank) const {\n        if (first_block >= last_block) return\
    \ 0;\n        return _boundary_less[last_block][rank]\n               - _boundary_less[first_block][rank];\n\
    \    }\n\n    int count_greater_blocks(int first_block, int last_block, int rank)\
    \ const {\n        int length = block_start(last_block) - block_start(first_block);\n\
    \        return length - count_less_blocks(first_block, last_block, rank + 1);\n\
    \    }\n\n    void build_local_data() {\n        _local_inversion.resize(_block_count);\n\
    \        _block_inversion.assign(_block_count, 0);\n\n        for (int block =\
    \ 0; block < _block_count; ++block) {\n            int start = block_start(block);\n\
    \            int end = block_end(block);\n            int length = end - start;\n\
    \            std::vector<int> greater(length * length, 0);\n            _local_inversion[block].assign(length\
    \ * (length + 3) / 2, 0);\n\n            for (int right = 0; right < length; ++right)\
    \ {\n                int count = 0;\n                for (int left = right - 1;\
    \ 0 <= left; --left) {\n                    count += _rank[start + left] > _rank[start\
    \ + right];\n                    greater[left * length + right] = count;\n   \
    \             }\n            }\n\n            for (int left = 0; left < length;\
    \ ++left) {\n                long long inversions = 0;\n                for (int\
    \ right = left; right < length; ++right) {\n                    inversions +=\
    \ greater[left * length + right];\n                    _local_inversion[block][\n\
    \                        local_index(block, left, right - left + 1)\n        \
    \            ] =\n                        int(inversions);\n                }\n\
    \            }\n            _block_inversion[block] =\n                _local_inversion[block][local_index(block,\
    \ 0, length)];\n        }\n    }\n\n    void build_boundary_counts() {\n     \
    \   _boundary_less.assign(\n            _block_count + 1,\n            std::vector<int>(_value_count\
    \ + 1, 0)\n        );\n        std::vector<int> frequency(_value_count, 0);\n\
    \        for (int block = 0; block <= _block_count; ++block) {\n            int\
    \ boundary = std::min(_n, block_start(block));\n            if (block != 0) {\n\
    \                int previous = block_start(block - 1);\n                for (int\
    \ index = previous; index < boundary; ++index) {\n                    frequency[_rank[index]]++;\n\
    \                }\n            }\n            int count = 0;\n            for\
    \ (int rank = 0; rank < _value_count; ++rank) {\n                _boundary_less[block][rank]\
    \ = count;\n                count += frequency[rank];\n            }\n       \
    \     _boundary_less[block][_value_count] = count;\n        }\n    }\n\n    void\
    \ build_full_block_inversions() {\n        _full_block_inversion.assign(\n   \
    \         _block_count + 1,\n            std::vector<long long>(_block_count +\
    \ 1, 0)\n        );\n        for (int first = 0; first < _block_count; ++first)\
    \ {\n            long long inversions = 0;\n            for (int last = first;\
    \ last < _block_count; ++last) {\n                int prior_length = block_start(last)\
    \ - block_start(first);\n                for (\n                    int index\
    \ = block_start(last);\n                    index < block_end(last);\n       \
    \             ++index\n                ) {\n                    int less_equal\
    \ =\n                        count_less_blocks(first, last, _rank[index] + 1);\n\
    \                    inversions += prior_length - less_equal;\n              \
    \  }\n                inversions += _block_inversion[last];\n                _full_block_inversion[first][last\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0), _value_count(0) {}\n\n    explicit\
    \ RangeInversionCount(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _value_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _value_count = int(sorted.size());\n        _rank.resize(_n);\n        for\
    \ (int index = 0; index < _n; ++index) {\n            _rank[index] = int(\n  \
    \              std::lower_bound(\n                    sorted.begin(),\n      \
    \              sorted.end(),\n                    values[index]\n            \
    \    ) - sorted.begin()\n            );\n        }\n\n        build_local_data();\n\
    \        build_boundary_counts();\n        build_full_block_inversions();\n  \
    \  }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    // Returns the number of pairs (i, j)\
    \ with\n    // left <= i < j < right and values[i] > values[j].\n    long long\
    \ query(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        if (right - left <= 1) return 0;\n\n        int left_block\
    \ = left / _block_size;\n        int right_block = (right - 1) / _block_size;\n\
    \        if (left_block == right_block) {\n            return local_query(left,\
    \ right);\n        }\n\n        int first_full = (left + _block_size - 1) / _block_size;\n\
    \        int last_full = right / _block_size;\n        int left_end = std::min(right,\
    \ block_start(first_full));\n        int right_start = std::max(left_end, block_start(last_full));\n\
    \n        long long result = _full_block_inversion[first_full][last_full];\n \
    \       result += local_query(left, left_end);\n        result += local_query(right_start,\
    \ right);\n\n        for (int index = left; index < left_end; ++index) {\n   \
    \         result += count_less_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        for (int index = right_start; index < right; ++index) {\n\
    \            result += count_greater_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        if (left < left_end && right_start < right) {\n        \
    \    std::vector<int> right_values;\n            right_values.reserve(right -\
    \ right_start);\n            for (int index = right_start; index < right; ++index)\
    \ {\n                right_values.push_back(_rank[index]);\n            }\n  \
    \          std::sort(right_values.begin(), right_values.end());\n            for\
    \ (int index = left; index < left_end; ++index) {\n                result += std::lower_bound(\n\
    \                    right_values.begin(),\n                    right_values.end(),\n\
    \                    _rank[index]\n                ) - right_values.begin();\n\
    \            }\n        }\n        return result;\n    }\n\n    long long inversion_count(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\n#define M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Static range inversion counts with O(N\
    \ sqrt N) preprocessing and\n// O(sqrt N log N) queries.\ntemplate <class T>\n\
    struct RangeInversionCount {\n   private:\n    int _n;\n    int _block_size;\n\
    \    int _block_count;\n    int _value_count;\n    std::vector<int> _rank;\n \
    \   std::vector<std::vector<int>> _boundary_less;\n    std::vector<std::vector<int>>\
    \ _local_inversion;\n    std::vector<long long> _block_inversion;\n    std::vector<std::vector<long\
    \ long>> _full_block_inversion;\n\n    int block_start(int block) const {\n  \
    \      return block * _block_size;\n    }\n\n    int block_end(int block) const\
    \ {\n        return std::min(_n, block_start(block) + _block_size);\n    }\n\n\
    \    int local_index(int block, int offset, int length) const {\n        int block_length\
    \ = block_end(block) - block_start(block);\n        return offset * (block_length\
    \ + 1)\n               - offset * (offset - 1) / 2\n               + length;\n\
    \    }\n\n    long long local_query(int left, int right) const {\n        if (right\
    \ - left <= 1) return 0;\n        int block = left / _block_size;\n        int\
    \ offset = left - block_start(block);\n        return _local_inversion[block][\n\
    \            local_index(block, offset, right - left)\n        ];\n    }\n\n \
    \   int count_less_blocks(int first_block, int last_block, int rank) const {\n\
    \        if (first_block >= last_block) return 0;\n        return _boundary_less[last_block][rank]\n\
    \               - _boundary_less[first_block][rank];\n    }\n\n    int count_greater_blocks(int\
    \ first_block, int last_block, int rank) const {\n        int length = block_start(last_block)\
    \ - block_start(first_block);\n        return length - count_less_blocks(first_block,\
    \ last_block, rank + 1);\n    }\n\n    void build_local_data() {\n        _local_inversion.resize(_block_count);\n\
    \        _block_inversion.assign(_block_count, 0);\n\n        for (int block =\
    \ 0; block < _block_count; ++block) {\n            int start = block_start(block);\n\
    \            int end = block_end(block);\n            int length = end - start;\n\
    \            std::vector<int> greater(length * length, 0);\n            _local_inversion[block].assign(length\
    \ * (length + 3) / 2, 0);\n\n            for (int right = 0; right < length; ++right)\
    \ {\n                int count = 0;\n                for (int left = right - 1;\
    \ 0 <= left; --left) {\n                    count += _rank[start + left] > _rank[start\
    \ + right];\n                    greater[left * length + right] = count;\n   \
    \             }\n            }\n\n            for (int left = 0; left < length;\
    \ ++left) {\n                long long inversions = 0;\n                for (int\
    \ right = left; right < length; ++right) {\n                    inversions +=\
    \ greater[left * length + right];\n                    _local_inversion[block][\n\
    \                        local_index(block, left, right - left + 1)\n        \
    \            ] =\n                        int(inversions);\n                }\n\
    \            }\n            _block_inversion[block] =\n                _local_inversion[block][local_index(block,\
    \ 0, length)];\n        }\n    }\n\n    void build_boundary_counts() {\n     \
    \   _boundary_less.assign(\n            _block_count + 1,\n            std::vector<int>(_value_count\
    \ + 1, 0)\n        );\n        std::vector<int> frequency(_value_count, 0);\n\
    \        for (int block = 0; block <= _block_count; ++block) {\n            int\
    \ boundary = std::min(_n, block_start(block));\n            if (block != 0) {\n\
    \                int previous = block_start(block - 1);\n                for (int\
    \ index = previous; index < boundary; ++index) {\n                    frequency[_rank[index]]++;\n\
    \                }\n            }\n            int count = 0;\n            for\
    \ (int rank = 0; rank < _value_count; ++rank) {\n                _boundary_less[block][rank]\
    \ = count;\n                count += frequency[rank];\n            }\n       \
    \     _boundary_less[block][_value_count] = count;\n        }\n    }\n\n    void\
    \ build_full_block_inversions() {\n        _full_block_inversion.assign(\n   \
    \         _block_count + 1,\n            std::vector<long long>(_block_count +\
    \ 1, 0)\n        );\n        for (int first = 0; first < _block_count; ++first)\
    \ {\n            long long inversions = 0;\n            for (int last = first;\
    \ last < _block_count; ++last) {\n                int prior_length = block_start(last)\
    \ - block_start(first);\n                for (\n                    int index\
    \ = block_start(last);\n                    index < block_end(last);\n       \
    \             ++index\n                ) {\n                    int less_equal\
    \ =\n                        count_less_blocks(first, last, _rank[index] + 1);\n\
    \                    inversions += prior_length - less_equal;\n              \
    \  }\n                inversions += _block_inversion[last];\n                _full_block_inversion[first][last\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0), _value_count(0) {}\n\n    explicit\
    \ RangeInversionCount(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _value_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _value_count = int(sorted.size());\n        _rank.resize(_n);\n        for\
    \ (int index = 0; index < _n; ++index) {\n            _rank[index] = int(\n  \
    \              std::lower_bound(\n                    sorted.begin(),\n      \
    \              sorted.end(),\n                    values[index]\n            \
    \    ) - sorted.begin()\n            );\n        }\n\n        build_local_data();\n\
    \        build_boundary_counts();\n        build_full_block_inversions();\n  \
    \  }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    // Returns the number of pairs (i, j)\
    \ with\n    // left <= i < j < right and values[i] > values[j].\n    long long\
    \ query(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        if (right - left <= 1) return 0;\n\n        int left_block\
    \ = left / _block_size;\n        int right_block = (right - 1) / _block_size;\n\
    \        if (left_block == right_block) {\n            return local_query(left,\
    \ right);\n        }\n\n        int first_full = (left + _block_size - 1) / _block_size;\n\
    \        int last_full = right / _block_size;\n        int left_end = std::min(right,\
    \ block_start(first_full));\n        int right_start = std::max(left_end, block_start(last_full));\n\
    \n        long long result = _full_block_inversion[first_full][last_full];\n \
    \       result += local_query(left, left_end);\n        result += local_query(right_start,\
    \ right);\n\n        for (int index = left; index < left_end; ++index) {\n   \
    \         result += count_less_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        for (int index = right_start; index < right; ++index) {\n\
    \            result += count_greater_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        if (left < left_end && right_start < right) {\n        \
    \    std::vector<int> right_values;\n            right_values.reserve(right -\
    \ right_start);\n            for (int index = right_start; index < right; ++index)\
    \ {\n                right_values.push_back(_rank[index]);\n            }\n  \
    \          std::sort(right_values.begin(), right_values.end());\n            for\
    \ (int index = left; index < left_end; ++index) {\n                result += std::lower_bound(\n\
    \                    right_values.begin(),\n                    right_values.end(),\n\
    \                    _rank[index]\n                ) - right_values.begin();\n\
    \            }\n        }\n        return result;\n    }\n\n    long long inversion_count(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/range_inversion_count.hpp
  requiredBy: []
  timestamp: '2026-06-27 03:28:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/range_inversion_count.test.cpp
documentation_of: ds/range_query/range_inversion_count.hpp
layout: document
title: Static Range Inversion Count
---

## Overview

`RangeInversionCount<T>` preprocesses a static array and answers inversion
counts for arbitrary subarrays.

For a query `[left, right)`, it returns the number of pairs `(i, j)` satisfying

$$
\mathrm{left}\le i<j<\mathrm{right}
\quad\text{and}\quad
a_i>a_j.
$$

Equal values are not inversions.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N\sqrt N)$ time and memory |
| `query(left, right)` | $O(\sqrt N\log N)$ |

The values only need equality and `<` comparisons. They are compressed during
construction.

## How It Works

The array is divided into blocks of approximately $\sqrt N$ elements.
Preprocessing stores:

* inversion counts for every range of complete blocks,
* cumulative value-rank counts at block boundaries,
* inversion counts for all ranges contained in one block.

A query begins with the precomputed answer for the complete blocks contained in
the range. The two partial boundary blocks contribute their internal inversions
from the local table. Their cross inversions against complete blocks are counted
through rank-count tables, and cross inversions between the two partial blocks
are counted by sorting the right boundary piece used by the query.

## Methods

| Method | Description |
| --- | --- |
| `RangeInversionCount(values)` | Builds the static structure. |
| `query(left, right)` | Returns inversions in `[left, right)`. |
| `inversion_count(left, right)` | Alias of `query`. |
| `size()`, `empty()` | Return the array size and whether it is empty. |
| `block_size()` | Returns the selected decomposition block size. |

## Example

```cpp
#include "ds/range_query/range_inversion_count.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {3, 1, 4, 1, 5};
    m1une::ds::RangeInversionCount<int> inversions(values);

    std::cout << inversions.query(0, 5) << "\n"; // 3
    std::cout << inversions.query(1, 4) << "\n"; // 1
}
```
