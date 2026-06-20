---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix.hpp
    title: Wavelet Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/range_query/wavelet_matrix.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A static wavelet matrix for integral values.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nstruct\
    \ WaveletMatrix {\n    using value_type = T;\n    using unsigned_type = std::make_unsigned_t<T>;\n\
    \n   private:\n    static constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (bit_width - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector\
    \ {\n        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\
    \n        BitVector() = default;\n\n        explicit BitVector(int n)\n      \
    \      : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
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
    \ m1une\n\n\n#line 4 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 8 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n#include\
    \ <iostream>\n#line 12 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n\nnamespace\
    \ {\n\nvoid test_edge_cases() {\n    m1une::ds::WaveletMatrix<long long> empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n\n    std::vector<long\
    \ long> values;\n    values.push_back(std::numeric_limits<long long>::min());\n\
    \    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n    assert(matrix.rank(-5,\
    \ 5) == 2);\n    assert(matrix.rank(-5, 1, 4) == 2);\n    assert(matrix.kth_smallest(0,\
    \ 5, 0) == std::numeric_limits<long long>::min());\n    assert(matrix.kth_largest(0,\
    \ 5, 0) == std::numeric_limits<long long>::max());\n    assert(matrix.range_freq(0,\
    \ 5, 0) == 3);\n    assert(matrix.range_freq(0, 5, -5, 1) == 3);\n    assert(matrix.prev_value(0,\
    \ 5, -5).value() == std::numeric_limits<long long>::min());\n    assert(matrix.next_value(0,\
    \ 5, 1).value() == std::numeric_limits<long long>::max());\n    assert(!matrix.prev_value(0,\
    \ 5, std::numeric_limits<long long>::min()));\n    assert(\n        matrix.next_value(0,\
    \ 5, std::numeric_limits<long long>::max()).value() ==\n        std::numeric_limits<long\
    \ long>::max()\n    );\n    assert(!matrix.next_value(1, 4, std::numeric_limits<long\
    \ long>::max()));\n\n    std::vector<unsigned int> unsigned_values;\n    unsigned_values.push_back(0);\n\
    \    unsigned_values.push_back(std::numeric_limits<unsigned int>::max());\n  \
    \  unsigned_values.push_back(7);\n    m1une::ds::WaveletMatrix<unsigned int> unsigned_matrix(unsigned_values);\n\
    \    assert(unsigned_matrix.kth_smallest(0, 3, 2) == std::numeric_limits<unsigned\
    \ int>::max());\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 17;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 80; trial++) {\n        int n = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 101) -\
    \ 50;\n        m1une::ds::WaveletMatrix<int> matrix(values);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int l = int(random() % std::uint64_t(n\
    \ + 1));\n            int r = int(random() % std::uint64_t(n + 1));\n        \
    \    if (r < l) std::swap(l, r);\n            int x = int(random() % 121) - 60;\n\
    \            int y = int(random() % 121) - 60;\n            if (y < x) std::swap(x,\
    \ y);\n\n            [[maybe_unused]] int rank = 0;\n            [[maybe_unused]]\
    \ int below = 0;\n            [[maybe_unused]] int between = 0;\n            std::optional<int>\
    \ previous;\n            std::optional<int> next;\n            std::vector<int>\
    \ sorted;\n            for (int i = l; i < r; i++) {\n                sorted.push_back(values[i]);\n\
    \                if (values[i] == x) rank++;\n                if (values[i] <\
    \ x) below++;\n                if (x <= values[i] && values[i] < y) between++;\n\
    \                if (values[i] < x && (!previous || *previous < values[i])) {\n\
    \                    previous = values[i];\n                }\n              \
    \  if (x <= values[i] && (!next || values[i] < *next)) {\n                   \
    \ next = values[i];\n                }\n            }\n            std::sort(sorted.begin(),\
    \ sorted.end());\n\n            assert(matrix.rank(x, l, r) == rank);\n      \
    \      assert(matrix.range_freq(l, r, x) == below);\n            assert(matrix.range_freq(l,\
    \ r, x, y) == between);\n            assert(matrix.prev_value(l, r, x) == previous);\n\
    \            assert(matrix.next_value(l, r, x) == next);\n            for (int\
    \ k = 0; k < int(sorted.size()); k++) {\n                assert(matrix.kth_smallest(l,\
    \ r, k) == sorted[k]);\n                assert(matrix.kth_largest(l, r, k) ==\
    \ sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_edge_cases();\n    test_randomized();\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<long long> values(n);\n    for (long long& value\
    \ : values) std::cin >> value;\n\n    m1une::ds::WaveletMatrix<long long> matrix(values);\n\
    \    for (int query = 0; query < q; query++) {\n        int l, r, k;\n       \
    \ std::cin >> l >> r >> k;\n        std::cout << matrix.kth_smallest(l, r, k)\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"ds/range_query/wavelet_matrix.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n#include\
    \ <optional>\n#include <vector>\n\nnamespace {\n\nvoid test_edge_cases() {\n \
    \   m1une::ds::WaveletMatrix<long long> empty;\n    assert(empty.empty());\n \
    \   assert(empty.size() == 0);\n\n    std::vector<long long> values;\n    values.push_back(std::numeric_limits<long\
    \ long>::min());\n    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n    assert(matrix.rank(-5,\
    \ 5) == 2);\n    assert(matrix.rank(-5, 1, 4) == 2);\n    assert(matrix.kth_smallest(0,\
    \ 5, 0) == std::numeric_limits<long long>::min());\n    assert(matrix.kth_largest(0,\
    \ 5, 0) == std::numeric_limits<long long>::max());\n    assert(matrix.range_freq(0,\
    \ 5, 0) == 3);\n    assert(matrix.range_freq(0, 5, -5, 1) == 3);\n    assert(matrix.prev_value(0,\
    \ 5, -5).value() == std::numeric_limits<long long>::min());\n    assert(matrix.next_value(0,\
    \ 5, 1).value() == std::numeric_limits<long long>::max());\n    assert(!matrix.prev_value(0,\
    \ 5, std::numeric_limits<long long>::min()));\n    assert(\n        matrix.next_value(0,\
    \ 5, std::numeric_limits<long long>::max()).value() ==\n        std::numeric_limits<long\
    \ long>::max()\n    );\n    assert(!matrix.next_value(1, 4, std::numeric_limits<long\
    \ long>::max()));\n\n    std::vector<unsigned int> unsigned_values;\n    unsigned_values.push_back(0);\n\
    \    unsigned_values.push_back(std::numeric_limits<unsigned int>::max());\n  \
    \  unsigned_values.push_back(7);\n    m1une::ds::WaveletMatrix<unsigned int> unsigned_matrix(unsigned_values);\n\
    \    assert(unsigned_matrix.kth_smallest(0, 3, 2) == std::numeric_limits<unsigned\
    \ int>::max());\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 17;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 80; trial++) {\n        int n = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 101) -\
    \ 50;\n        m1une::ds::WaveletMatrix<int> matrix(values);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int l = int(random() % std::uint64_t(n\
    \ + 1));\n            int r = int(random() % std::uint64_t(n + 1));\n        \
    \    if (r < l) std::swap(l, r);\n            int x = int(random() % 121) - 60;\n\
    \            int y = int(random() % 121) - 60;\n            if (y < x) std::swap(x,\
    \ y);\n\n            [[maybe_unused]] int rank = 0;\n            [[maybe_unused]]\
    \ int below = 0;\n            [[maybe_unused]] int between = 0;\n            std::optional<int>\
    \ previous;\n            std::optional<int> next;\n            std::vector<int>\
    \ sorted;\n            for (int i = l; i < r; i++) {\n                sorted.push_back(values[i]);\n\
    \                if (values[i] == x) rank++;\n                if (values[i] <\
    \ x) below++;\n                if (x <= values[i] && values[i] < y) between++;\n\
    \                if (values[i] < x && (!previous || *previous < values[i])) {\n\
    \                    previous = values[i];\n                }\n              \
    \  if (x <= values[i] && (!next || values[i] < *next)) {\n                   \
    \ next = values[i];\n                }\n            }\n            std::sort(sorted.begin(),\
    \ sorted.end());\n\n            assert(matrix.rank(x, l, r) == rank);\n      \
    \      assert(matrix.range_freq(l, r, x) == below);\n            assert(matrix.range_freq(l,\
    \ r, x, y) == between);\n            assert(matrix.prev_value(l, r, x) == previous);\n\
    \            assert(matrix.next_value(l, r, x) == next);\n            for (int\
    \ k = 0; k < int(sorted.size()); k++) {\n                assert(matrix.kth_smallest(l,\
    \ r, k) == sorted[k]);\n                assert(matrix.kth_largest(l, r, k) ==\
    \ sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_edge_cases();\n    test_randomized();\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<long long> values(n);\n    for (long long& value\
    \ : values) std::cin >> value;\n\n    m1une::ds::WaveletMatrix<long long> matrix(values);\n\
    \    for (int query = 0; query < q; query++) {\n        int l, r, k;\n       \
    \ std::cin >> l >> r >> k;\n        std::cout << matrix.kth_smallest(l, r, k)\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/wavelet_matrix.hpp
  isVerificationFile: true
  path: verify/ds/range_query/wavelet_matrix.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 02:25:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/wavelet_matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/wavelet_matrix.test.cpp
- /verify/verify/ds/range_query/wavelet_matrix.test.cpp.html
title: verify/ds/range_query/wavelet_matrix.test.cpp
---
