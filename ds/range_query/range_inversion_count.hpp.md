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
    \ preprocessing and\n// O(sqrt N) queries.\ntemplate <class T>\nstruct RangeInversionCount\
    \ {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n \
    \   std::vector<int> _rank;\n    std::vector<std::vector<int>> _boundary_less;\n\
    \    std::vector<std::vector<long long>> _from_boundary;\n    std::vector<std::vector<long\
    \ long>> _local_inversion;\n    std::vector<std::vector<int>> _sorted_suffix;\n\
    \    std::vector<std::vector<int>> _sorted_prefix;\n    std::vector<int> _greater_before_in_block;\n\
    \n    int block_start(int block) const {\n        return block * _block_size;\n\
    \    }\n\n    int block_end(int block) const {\n        return std::min(_n, block_start(block)\
    \ + _block_size);\n    }\n\n    static long long cross_inversions(\n        const\
    \ std::vector<int>& left,\n        const std::vector<int>& right\n    ) {\n  \
    \      long long result = 0;\n        std::size_t smaller = 0;\n        for (int\
    \ value : left) {\n            while (smaller < right.size() && right[smaller]\
    \ < value) {\n                smaller++;\n            }\n            result +=\
    \ static_cast<long long>(smaller);\n        }\n        return result;\n    }\n\
    \n    void build_local_data() {\n        _local_inversion.resize(_n);\n      \
    \  _sorted_suffix.resize(_n);\n        _sorted_prefix.resize(_n + 1);\n      \
    \  _greater_before_in_block.assign(_n, 0);\n\n        for (int block = 0; block\
    \ < _block_count; ++block) {\n            int start = block_start(block);\n  \
    \          int end = block_end(block);\n            int length = end - start;\n\
    \            std::vector<std::vector<int>> greater(\n                length,\n\
    \                std::vector<int>(length, 0)\n            );\n\n            for\
    \ (int right = 0; right < length; ++right) {\n                int count = 0;\n\
    \                for (int left = right - 1; 0 <= left; --left) {\n           \
    \         count += _rank[start + left] > _rank[start + right];\n             \
    \       greater[left][right] = count;\n                }\n                _greater_before_in_block[start\
    \ + right] =\n                    right == 0 ? 0 : greater[0][right];\n      \
    \      }\n\n            for (int left = 0; left < length; ++left) {\n        \
    \        _local_inversion[start + left].assign(\n                    length -\
    \ left + 1,\n                    0\n                );\n                long long\
    \ inversions = 0;\n                for (int right = left; right < length; ++right)\
    \ {\n                    inversions += greater[left][right];\n               \
    \     _local_inversion[start + left][right - left + 1] =\n                   \
    \     inversions;\n                }\n            }\n\n            std::vector<int>\
    \ sorted;\n            if (start == 0) _sorted_prefix[start] = sorted;\n     \
    \       for (int index = start; index < end; ++index) {\n                sorted.insert(\n\
    \                    std::upper_bound(\n                        sorted.begin(),\n\
    \                        sorted.end(),\n                        _rank[index]\n\
    \                    ),\n                    _rank[index]\n                );\n\
    \                _sorted_prefix[index + 1] = sorted;\n            }\n\n      \
    \      sorted.clear();\n            for (int index = end - 1; start <= index;\
    \ --index) {\n                sorted.insert(\n                    std::upper_bound(\n\
    \                        sorted.begin(),\n                        sorted.end(),\n\
    \                        _rank[index]\n                    ),\n              \
    \      _rank[index]\n                );\n                _sorted_suffix[index]\
    \ = sorted;\n            }\n        }\n    }\n\n    void build_boundary_counts(int\
    \ value_count) {\n        _boundary_less.assign(\n            _block_count + 1,\n\
    \            std::vector<int>(value_count + 1, 0)\n        );\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int block = 0; block <= _block_count;\
    \ ++block) {\n            int boundary = std::min(_n, block_start(block));\n \
    \           if (block != 0) {\n                int previous = block_start(block\
    \ - 1);\n                for (int index = previous; index < boundary; ++index)\
    \ {\n                    frequency[_rank[index]]++;\n                }\n     \
    \       }\n            int count = 0;\n            for (int rank = 0; rank < value_count;\
    \ ++rank) {\n                _boundary_less[block][rank] = count;\n          \
    \      count += frequency[rank];\n            }\n            _boundary_less[block][value_count]\
    \ = count;\n        }\n    }\n\n    void build_boundary_inversions() {\n     \
    \   _from_boundary.assign(\n            _block_count + 1,\n            std::vector<long\
    \ long>(_n + 1, 0)\n        );\n        for (int first_block = 0; first_block\
    \ < _block_count; ++first_block) {\n            int start = block_start(first_block);\n\
    \            long long inversions = 0;\n            for (int index = start; index\
    \ < _n; ++index) {\n                int current_block = index / _block_size;\n\
    \                int full_length =\n                    block_start(current_block)\
    \ - start;\n                int less_equal =\n                    _boundary_less[current_block][_rank[index]\
    \ + 1]\n                    - _boundary_less[first_block][_rank[index] + 1];\n\
    \                int greater_in_full_blocks = full_length - less_equal;\n    \
    \            inversions +=\n                    greater_in_full_blocks\n     \
    \               + _greater_before_in_block[index];\n                _from_boundary[first_block][index\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit RangeInversionCount(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())), _block_size(1), _block_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _rank.resize(_n);\n        for (int index = 0; index < _n; ++index) {\n\
    \            _rank[index] = int(\n                std::lower_bound(\n        \
    \            sorted.begin(),\n                    sorted.end(),\n            \
    \        values[index]\n                ) - sorted.begin()\n            );\n \
    \       }\n\n        build_local_data();\n        build_boundary_counts(int(sorted.size()));\n\
    \        build_boundary_inversions();\n    }\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int block_size() const {\n        return _block_size;\n    }\n\n\
    \    // Returns the number of pairs (i, j) with\n    // left <= i < j < right\
    \ and values[i] > values[j].\n    long long query(int left, int right) const {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (right\
    \ - left <= 1) return 0;\n\n        int left_block = left / _block_size;\n   \
    \     int right_block = (right - 1) / _block_size;\n        if (left_block ==\
    \ right_block) {\n            return _local_inversion[left][right - left];\n \
    \       }\n\n        int middle_left = block_end(left_block);\n        int middle_block\
    \ = left_block + 1;\n        long long result = _local_inversion[left][middle_left\
    \ - left];\n        result += _from_boundary[middle_block][right];\n\n       \
    \ int trailing_block = (right - 1) / _block_size;\n        for (int index = left;\
    \ index < middle_left; ++index) {\n            int rank = _rank[index];\n    \
    \        result +=\n                _boundary_less[trailing_block][rank]\n   \
    \             - _boundary_less[middle_block][rank];\n        }\n\n        result\
    \ += cross_inversions(\n            _sorted_suffix[left],\n            _sorted_prefix[right]\n\
    \        );\n        return result;\n    }\n\n    long long inversion_count(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\n#define M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Static range inversion counts with O(N\
    \ sqrt N) preprocessing and\n// O(sqrt N) queries.\ntemplate <class T>\nstruct\
    \ RangeInversionCount {\n   private:\n    int _n;\n    int _block_size;\n    int\
    \ _block_count;\n    std::vector<int> _rank;\n    std::vector<std::vector<int>>\
    \ _boundary_less;\n    std::vector<std::vector<long long>> _from_boundary;\n \
    \   std::vector<std::vector<long long>> _local_inversion;\n    std::vector<std::vector<int>>\
    \ _sorted_suffix;\n    std::vector<std::vector<int>> _sorted_prefix;\n    std::vector<int>\
    \ _greater_before_in_block;\n\n    int block_start(int block) const {\n      \
    \  return block * _block_size;\n    }\n\n    int block_end(int block) const {\n\
    \        return std::min(_n, block_start(block) + _block_size);\n    }\n\n   \
    \ static long long cross_inversions(\n        const std::vector<int>& left,\n\
    \        const std::vector<int>& right\n    ) {\n        long long result = 0;\n\
    \        std::size_t smaller = 0;\n        for (int value : left) {\n        \
    \    while (smaller < right.size() && right[smaller] < value) {\n            \
    \    smaller++;\n            }\n            result += static_cast<long long>(smaller);\n\
    \        }\n        return result;\n    }\n\n    void build_local_data() {\n \
    \       _local_inversion.resize(_n);\n        _sorted_suffix.resize(_n);\n   \
    \     _sorted_prefix.resize(_n + 1);\n        _greater_before_in_block.assign(_n,\
    \ 0);\n\n        for (int block = 0; block < _block_count; ++block) {\n      \
    \      int start = block_start(block);\n            int end = block_end(block);\n\
    \            int length = end - start;\n            std::vector<std::vector<int>>\
    \ greater(\n                length,\n                std::vector<int>(length,\
    \ 0)\n            );\n\n            for (int right = 0; right < length; ++right)\
    \ {\n                int count = 0;\n                for (int left = right - 1;\
    \ 0 <= left; --left) {\n                    count += _rank[start + left] > _rank[start\
    \ + right];\n                    greater[left][right] = count;\n             \
    \   }\n                _greater_before_in_block[start + right] =\n           \
    \         right == 0 ? 0 : greater[0][right];\n            }\n\n            for\
    \ (int left = 0; left < length; ++left) {\n                _local_inversion[start\
    \ + left].assign(\n                    length - left + 1,\n                  \
    \  0\n                );\n                long long inversions = 0;\n        \
    \        for (int right = left; right < length; ++right) {\n                 \
    \   inversions += greater[left][right];\n                    _local_inversion[start\
    \ + left][right - left + 1] =\n                        inversions;\n         \
    \       }\n            }\n\n            std::vector<int> sorted;\n           \
    \ if (start == 0) _sorted_prefix[start] = sorted;\n            for (int index\
    \ = start; index < end; ++index) {\n                sorted.insert(\n         \
    \           std::upper_bound(\n                        sorted.begin(),\n     \
    \                   sorted.end(),\n                        _rank[index]\n    \
    \                ),\n                    _rank[index]\n                );\n  \
    \              _sorted_prefix[index + 1] = sorted;\n            }\n\n        \
    \    sorted.clear();\n            for (int index = end - 1; start <= index; --index)\
    \ {\n                sorted.insert(\n                    std::upper_bound(\n \
    \                       sorted.begin(),\n                        sorted.end(),\n\
    \                        _rank[index]\n                    ),\n              \
    \      _rank[index]\n                );\n                _sorted_suffix[index]\
    \ = sorted;\n            }\n        }\n    }\n\n    void build_boundary_counts(int\
    \ value_count) {\n        _boundary_less.assign(\n            _block_count + 1,\n\
    \            std::vector<int>(value_count + 1, 0)\n        );\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int block = 0; block <= _block_count;\
    \ ++block) {\n            int boundary = std::min(_n, block_start(block));\n \
    \           if (block != 0) {\n                int previous = block_start(block\
    \ - 1);\n                for (int index = previous; index < boundary; ++index)\
    \ {\n                    frequency[_rank[index]]++;\n                }\n     \
    \       }\n            int count = 0;\n            for (int rank = 0; rank < value_count;\
    \ ++rank) {\n                _boundary_less[block][rank] = count;\n          \
    \      count += frequency[rank];\n            }\n            _boundary_less[block][value_count]\
    \ = count;\n        }\n    }\n\n    void build_boundary_inversions() {\n     \
    \   _from_boundary.assign(\n            _block_count + 1,\n            std::vector<long\
    \ long>(_n + 1, 0)\n        );\n        for (int first_block = 0; first_block\
    \ < _block_count; ++first_block) {\n            int start = block_start(first_block);\n\
    \            long long inversions = 0;\n            for (int index = start; index\
    \ < _n; ++index) {\n                int current_block = index / _block_size;\n\
    \                int full_length =\n                    block_start(current_block)\
    \ - start;\n                int less_equal =\n                    _boundary_less[current_block][_rank[index]\
    \ + 1]\n                    - _boundary_less[first_block][_rank[index] + 1];\n\
    \                int greater_in_full_blocks = full_length - less_equal;\n    \
    \            inversions +=\n                    greater_in_full_blocks\n     \
    \               + _greater_before_in_block[index];\n                _from_boundary[first_block][index\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit RangeInversionCount(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())), _block_size(1), _block_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _rank.resize(_n);\n        for (int index = 0; index < _n; ++index) {\n\
    \            _rank[index] = int(\n                std::lower_bound(\n        \
    \            sorted.begin(),\n                    sorted.end(),\n            \
    \        values[index]\n                ) - sorted.begin()\n            );\n \
    \       }\n\n        build_local_data();\n        build_boundary_counts(int(sorted.size()));\n\
    \        build_boundary_inversions();\n    }\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int block_size() const {\n        return _block_size;\n    }\n\n\
    \    // Returns the number of pairs (i, j) with\n    // left <= i < j < right\
    \ and values[i] > values[j].\n    long long query(int left, int right) const {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (right\
    \ - left <= 1) return 0;\n\n        int left_block = left / _block_size;\n   \
    \     int right_block = (right - 1) / _block_size;\n        if (left_block ==\
    \ right_block) {\n            return _local_inversion[left][right - left];\n \
    \       }\n\n        int middle_left = block_end(left_block);\n        int middle_block\
    \ = left_block + 1;\n        long long result = _local_inversion[left][middle_left\
    \ - left];\n        result += _from_boundary[middle_block][right];\n\n       \
    \ int trailing_block = (right - 1) / _block_size;\n        for (int index = left;\
    \ index < middle_left; ++index) {\n            int rank = _rank[index];\n    \
    \        result +=\n                _boundary_less[trailing_block][rank]\n   \
    \             - _boundary_less[middle_block][rank];\n        }\n\n        result\
    \ += cross_inversions(\n            _sorted_suffix[left],\n            _sorted_prefix[right]\n\
    \        );\n        return result;\n    }\n\n    long long inversion_count(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/range_inversion_count.hpp
  requiredBy: []
  timestamp: '2026-06-23 03:10:38+09:00'
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
| `query(left, right)` | $O(\sqrt N)$ |

The values only need equality and `<` comparisons. They are compressed during
construction.

## How It Works

The array is divided into blocks of approximately $\sqrt N$ elements.
Preprocessing stores:

* inversion counts from every block boundary to every right endpoint,
* cumulative value-rank counts at block boundaries,
* inversion counts for all ranges contained in one block,
* sorted prefixes and suffixes of each block.

A query begins with the answer from the first complete block boundary. The
remaining left fringe contributes its internal inversions, inversions against
complete blocks through rank-count tables, and inversions against the final
partial block through a linear merge of two sorted boundary pieces.

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
