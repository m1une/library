---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/wavelet_matrix.test.cpp
    title: verify/ds/range_query/wavelet_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/wavelet_matrix.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <limits>\n\
    #include <optional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// A static wavelet matrix for integral\
    \ values.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrix {\n    using value_type = T;\n    using unsigned_type\
    \ = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr int bit_width\
    \ = std::numeric_limits<unsigned_type>::digits;\n    static constexpr unsigned_type\
    \ sign_mask = [] {\n        if constexpr (std::signed_integral<T>) {\n       \
    \     return unsigned_type(1) << (bit_width - 1);\n        } else {\n        \
    \    return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector {\n\
    \        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\n\
    \        BitVector() = default;\n\n        explicit BitVector(int n)\n       \
    \     : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    int _n;\n    std::vector<BitVector> _matrix;\n    std::vector<int>\
    \ _zero_count;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    static bool\
    \ bit(unsigned_type value, int level) {\n        return (value >> (bit_width -\
    \ 1 - level)) & unsigned_type(1);\n    }\n\n    int count_less_encoded(int l,\
    \ int r, unsigned_type upper) const {\n        int result = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix()\
    \ : _n(0), _matrix(bit_width), _zero_count(bit_width, 0) {}\n\n    explicit WaveletMatrix(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())),\n          _matrix(),\n\
    \          _zero_count(bit_width, 0) {\n        std::vector<unsigned_type> current(_n);\n\
    \        std::vector<unsigned_type> next(_n);\n        for (int i = 0; i < _n;\
    \ i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            _matrix.emplace_back(_n);\n\
    \            for (int i = 0; i < _n; i++) {\n                if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n            }\n            _matrix.back().build();\n\
    \n            int zeros = _matrix.back().rank0(_n);\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (unsigned_type value : current) {\n                if (bit(value,\
    \ level)) {\n                    next[one_pos++] = value;\n                } else\
    \ {\n                    next[zero_pos++] = value;\n                }\n      \
    \      }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            bool one = _matrix[level].get(p);\n            if (one)\
    \ {\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n   \
    \             p = _zero_count[level] + _matrix[level].rank1(p);\n            }\
    \ else {\n                p = _matrix[level].rank0(p);\n            }\n      \
    \  }\n        return decode(key);\n    }\n\n    T operator[](int p) const {\n\
    \        return access(p);\n    }\n\n    int rank(T value, int r) const {\n  \
    \      assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n    }\n\n\
    \    int rank(T value, int l, int r) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        unsigned_type key = encode(value);\n        for (int level\
    \ = 0; level < bit_width; level++) {\n            if (bit(key, level)) {\n   \
    \             l = _zero_count[level] + _matrix[level].rank1(l);\n            \
    \    r = _zero_count[level] + _matrix[level].rank1(r);\n            } else {\n\
    \                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
    \            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            int zeros = r0 - l0;\n\
    \            if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                l = _zero_count[level] + _matrix[level].rank1(l);\n\
    \                r = _zero_count[level] + _matrix[level].rank1(r);\n         \
    \   }\n        }\n        return decode(key);\n    }\n\n    T kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        return kth_smallest(l, r, r - l -\
    \ 1 - k);\n    }\n\n    int range_freq(int l, int r, T upper) const {\n      \
    \  assert(0 <= l && l <= r && r <= _n);\n        return count_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    int range_freq(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return 0;\n        return range_freq(l, r, upper) - range_freq(l, r,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, upper);\n        if (count == 0) return std::nullopt;\n        return kth_smallest(l,\
    \ r, count - 1);\n    }\n\n    std::optional<T> next_value(int l, int r, T lower)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, lower);\n        if (count == r - l) return std::nullopt;\n        return\
    \ kth_smallest(l, r, count);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_WAVELET_MATRIX_HPP\n#define M1UNE_WAVELET_MATRIX_HPP 1\n\n\
    #include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet\
    \ matrix for integral values.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrix {\n    using value_type = T;\n    using unsigned_type\
    \ = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr int bit_width\
    \ = std::numeric_limits<unsigned_type>::digits;\n    static constexpr unsigned_type\
    \ sign_mask = [] {\n        if constexpr (std::signed_integral<T>) {\n       \
    \     return unsigned_type(1) << (bit_width - 1);\n        } else {\n        \
    \    return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector {\n\
    \        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\n\
    \        BitVector() = default;\n\n        explicit BitVector(int n)\n       \
    \     : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    int _n;\n    std::vector<BitVector> _matrix;\n    std::vector<int>\
    \ _zero_count;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    static bool\
    \ bit(unsigned_type value, int level) {\n        return (value >> (bit_width -\
    \ 1 - level)) & unsigned_type(1);\n    }\n\n    int count_less_encoded(int l,\
    \ int r, unsigned_type upper) const {\n        int result = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix()\
    \ : _n(0), _matrix(bit_width), _zero_count(bit_width, 0) {}\n\n    explicit WaveletMatrix(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())),\n          _matrix(),\n\
    \          _zero_count(bit_width, 0) {\n        std::vector<unsigned_type> current(_n);\n\
    \        std::vector<unsigned_type> next(_n);\n        for (int i = 0; i < _n;\
    \ i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            _matrix.emplace_back(_n);\n\
    \            for (int i = 0; i < _n; i++) {\n                if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n            }\n            _matrix.back().build();\n\
    \n            int zeros = _matrix.back().rank0(_n);\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (unsigned_type value : current) {\n                if (bit(value,\
    \ level)) {\n                    next[one_pos++] = value;\n                } else\
    \ {\n                    next[zero_pos++] = value;\n                }\n      \
    \      }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            bool one = _matrix[level].get(p);\n            if (one)\
    \ {\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n   \
    \             p = _zero_count[level] + _matrix[level].rank1(p);\n            }\
    \ else {\n                p = _matrix[level].rank0(p);\n            }\n      \
    \  }\n        return decode(key);\n    }\n\n    T operator[](int p) const {\n\
    \        return access(p);\n    }\n\n    int rank(T value, int r) const {\n  \
    \      assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n    }\n\n\
    \    int rank(T value, int l, int r) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        unsigned_type key = encode(value);\n        for (int level\
    \ = 0; level < bit_width; level++) {\n            if (bit(key, level)) {\n   \
    \             l = _zero_count[level] + _matrix[level].rank1(l);\n            \
    \    r = _zero_count[level] + _matrix[level].rank1(r);\n            } else {\n\
    \                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
    \            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            int zeros = r0 - l0;\n\
    \            if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                l = _zero_count[level] + _matrix[level].rank1(l);\n\
    \                r = _zero_count[level] + _matrix[level].rank1(r);\n         \
    \   }\n        }\n        return decode(key);\n    }\n\n    T kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        return kth_smallest(l, r, r - l -\
    \ 1 - k);\n    }\n\n    int range_freq(int l, int r, T upper) const {\n      \
    \  assert(0 <= l && l <= r && r <= _n);\n        return count_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    int range_freq(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return 0;\n        return range_freq(l, r, upper) - range_freq(l, r,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, upper);\n        if (count == 0) return std::nullopt;\n        return kth_smallest(l,\
    \ r, count - 1);\n    }\n\n    std::optional<T> next_value(int l, int r, T lower)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, lower);\n        if (count == r - l) return std::nullopt;\n        return\
    \ kth_smallest(l, r, count);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_WAVELET_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/wavelet_matrix.hpp
  requiredBy: []
  timestamp: '2026-06-21 02:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/wavelet_matrix.test.cpp
documentation_of: ds/range_query/wavelet_matrix.hpp
layout: document
title: Wavelet Matrix
---

## Overview

`m1une::ds::WaveletMatrix` is a static data structure for integral sequences.
It supports access, occurrence counting, range order statistics, range
frequency queries, and predecessor/successor searches.

Each level uses a packed bitvector with constant-time prefix rank. Signed values
are ordered by flipping their sign bit internally, so negative values and the
full range of the selected integer type work without coordinate compression.

## Template Parameter

* `T`: A non-`bool` integral type.

The implementation uses every value bit. Let $B$ be the bit width of `T`, such
as 32 for `int` or 64 for `long long`.

## Construction

* `WaveletMatrix()`: creates an empty matrix.
* `WaveletMatrix(const std::vector<T>& values)`: builds from `values`.

Construction takes $O(NB)$ time and $O(NB)$ bits for level bitvectors, plus
rank metadata.

## Methods

All index ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(B)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(B)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(B)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(B)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value in `[l, r)`. | $O(B)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value in `[l, r)`. | $O(B)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper` in `[l, r)`. | $O(B)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)` within `[l, r)`. | $O(B)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(B)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(B)$ |

`kth_smallest` and `kth_largest` require `0 <= k < r - l`.

For range sums or weights attached to values, use `WaveletMatrixSum`.

## Example

```cpp
#include "ds/range_query/wavelet_matrix.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrix<long long> matrix(values);

    std::cout << matrix.kth_smallest(0, 5, 1) << "\n";  // 1
    std::cout << matrix.rank(5, 0, 4) << "\n";          // 2
    std::cout << matrix.range_freq(1, 5, 0, 6) << "\n"; // 3

    auto predecessor = matrix.prev_value(0, 5, 5);
    if (predecessor) std::cout << *predecessor << "\n"; // 1
}
```
