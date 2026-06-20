---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix_sum.hpp
    title: Wavelet Matrix with Sums
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
  bundledCode: "#line 1 \"verify/ds/range_query/wavelet_matrix_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/range_query/wavelet_matrix_sum.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A static wavelet matrix with additive weights.\n// By\
    \ default, each value is also used as its weight.\ntemplate <std::integral T,\
    \ typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nstruct\
    \ WaveletMatrixSum {\n    using value_type = T;\n    using sum_type = Sum;\n \
    \   using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static\
    \ constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n    static\
    \ constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
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
    \ _zero_count;\n    std::vector<std::vector<Sum>> _zero_prefix;\n    std::vector<Sum>\
    \ _original_prefix;\n    std::vector<Sum> _final_prefix;\n\n    static unsigned_type\
    \ encode(T value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    static bool bit(unsigned_type value, int level) {\n       \
    \ return (value >> (bit_width - 1 - level)) & unsigned_type(1);\n    }\n\n   \
    \ Sum zero_sum(int level, int l, int r) const {\n        return _zero_prefix[level][r]\
    \ - _zero_prefix[level][l];\n    }\n\n    Sum sum_less_encoded(int l, int r, unsigned_type\
    \ upper) const {\n        Sum result{};\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            int l0 = _matrix[level].rank0(l);\n            int r0\
    \ = _matrix[level].rank0(r);\n            if (bit(upper, level)) {\n         \
    \       result = result + zero_sum(level, l, r);\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n    int count_less_encoded(int\
    \ l, int r, unsigned_type upper) const {\n        int result = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n    void build(const std::vector<T>&\
    \ values, const std::vector<Sum>& weights) {\n        assert(values.size() ==\
    \ weights.size());\n\n        std::vector<unsigned_type> current_keys(_n);\n \
    \       std::vector<unsigned_type> next_keys(_n);\n        std::vector<Sum> current_weights(weights);\n\
    \        std::vector<Sum> next_weights(_n);\n        for (int i = 0; i < _n; i++)\
    \ current_keys[i] = encode(values[i]);\n\n        _original_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _original_prefix[i\
    \ + 1] = _original_prefix[i] + weights[i];\n        }\n\n        _matrix.reserve(bit_width);\n\
    \        _zero_prefix.reserve(bit_width);\n        for (int level = 0; level <\
    \ bit_width; level++) {\n            _matrix.emplace_back(_n);\n            _zero_prefix.emplace_back(std::size_t(_n)\
    \ + 1, Sum{});\n            for (int i = 0; i < _n; i++) {\n                bool\
    \ one = bit(current_keys[i], level);\n                if (one) _matrix.back().set(i);\n\
    \                _zero_prefix.back()[i + 1] = _zero_prefix.back()[i];\n      \
    \          if (!one) {\n                    _zero_prefix.back()[i + 1] =\n   \
    \                     _zero_prefix.back()[i + 1] + current_weights[i];\n     \
    \           }\n            }\n            _matrix.back().build();\n\n        \
    \    int zeros = _matrix.back().rank0(_n);\n            _zero_count[level] = zeros;\n\
    \            int zero_pos = 0;\n            int one_pos = zeros;\n           \
    \ for (int i = 0; i < _n; i++) {\n                if (bit(current_keys[i], level))\
    \ {\n                    next_keys[one_pos] = current_keys[i];\n             \
    \       next_weights[one_pos] = current_weights[i];\n                    one_pos++;\n\
    \                } else {\n                    next_keys[zero_pos] = current_keys[i];\n\
    \                    next_weights[zero_pos] = current_weights[i];\n          \
    \          zero_pos++;\n                }\n            }\n            current_keys.swap(next_keys);\n\
    \            current_weights.swap(next_weights);\n        }\n\n        _final_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _final_prefix[i\
    \ + 1] = _final_prefix[i] + current_weights[i];\n        }\n    }\n\n   public:\n\
    \    WaveletMatrixSum()\n        : _n(0),\n          _matrix(bit_width),\n   \
    \       _zero_count(bit_width, 0),\n          _zero_prefix(bit_width, std::vector<Sum>(1,\
    \ Sum{})),\n          _original_prefix(1, Sum{}),\n          _final_prefix(1,\
    \ Sum{}) {}\n\n    explicit WaveletMatrixSum(const std::vector<T>& values)\n \
    \       requires std::convertible_to<T, Sum>\n        : _n(int(values.size())),\n\
    \          _matrix(),\n          _zero_count(bit_width, 0) {\n        std::vector<Sum>\
    \ weights;\n        weights.reserve(values.size());\n        for (T value : values)\
    \ weights.push_back(static_cast<Sum>(value));\n        build(values, weights);\n\
    \    }\n\n    WaveletMatrixSum(\n        const std::vector<T>& values,\n     \
    \   const std::vector<Sum>& weights\n    ) : _n(int(values.size())),\n       \
    \ _matrix(),\n        _zero_count(bit_width, 0) {\n        build(values, weights);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    T access(int p) const {\n   \
    \     assert(0 <= p && p < _n);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            bool one = _matrix[level].get(p);\n\
    \            if (one) {\n                key |= unsigned_type(1) << (bit_width\
    \ - 1 - level);\n                p = _zero_count[level] + _matrix[level].rank1(p);\n\
    \            } else {\n                p = _matrix[level].rank0(p);\n        \
    \    }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ p) const {\n        return access(p);\n    }\n\n    int rank(T value, int r)\
    \ const {\n        assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n\
    \    }\n\n    int rank(T value, int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        unsigned_type key = encode(value);\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            if (bit(key, level))\
    \ {\n                l = _zero_count[level] + _matrix[level].rank1(l);\n     \
    \           r = _zero_count[level] + _matrix[level].rank1(r);\n            } else\
    \ {\n                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
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
    \ kth_smallest(l, r, count);\n    }\n\n    Sum range_sum(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        return _original_prefix[r]\
    \ - _original_prefix[l];\n    }\n\n    Sum range_sum(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        return sum_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    Sum range_sum(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return Sum{};\n        return range_sum(l, r, upper) - range_sum(l, r,\
    \ lower);\n    }\n\n    Sum sum_k_smallest(int l, int r, int k) const {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k <= r - l);\n\
    \        Sum result{};\n        for (int level = 0; level < bit_width; level++)\
    \ {\n            int l0 = _matrix[level].rank0(l);\n            int r0 = _matrix[level].rank0(r);\n\
    \            int zeros = r0 - l0;\n            if (k < zeros) {\n            \
    \    l = l0;\n                r = r0;\n            } else {\n                result\
    \ = result + zero_sum(level, l, r);\n                k -= zeros;\n           \
    \     l = _zero_count[level] + _matrix[level].rank1(l);\n                r = _zero_count[level]\
    \ + _matrix[level].rank1(r);\n            }\n        }\n        return result\
    \ + (_final_prefix[l + k] - _final_prefix[l]);\n    }\n\n    Sum sum_k_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k <= r - l);\n        return range_sum(l, r) - sum_k_smallest(l,\
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n\
    #line 4 \"verify/ds/range_query/wavelet_matrix_sum.test.cpp\"\n\n#include <algorithm>\n\
    #line 8 \"verify/ds/range_query/wavelet_matrix_sum.test.cpp\"\n#include <iostream>\n\
    #line 10 \"verify/ds/range_query/wavelet_matrix_sum.test.cpp\"\n#include <numeric>\n\
    #line 13 \"verify/ds/range_query/wavelet_matrix_sum.test.cpp\"\n\nnamespace {\n\
    \nvoid test_value_sums() {\n    std::vector<long long> values;\n    values.push_back(std::numeric_limits<long\
    \ long>::min());\n    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrixSum<long\
    \ long, __int128_t> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n\n    [[maybe_unused]]\
    \ __int128_t total = 0;\n    for (long long value : values) total += value;\n\
    \    assert(matrix.range_sum(0, 5) == total);\n    assert(matrix.range_sum(0,\
    \ 5, 0LL) ==\n           __int128_t(std::numeric_limits<long long>::min()) - 10);\n\
    \    assert(matrix.range_sum(0, 5, -5LL, 1LL) == -10);\n    assert(matrix.sum_k_smallest(0,\
    \ 5, 0) == 0);\n    assert(matrix.sum_k_smallest(0, 5, 3) ==\n           __int128_t(std::numeric_limits<long\
    \ long>::min()) - 10);\n    assert(matrix.sum_k_largest(0, 5, 2) ==\n        \
    \   __int128_t(std::numeric_limits<long long>::max()));\n    assert(matrix.sum_k_largest(0,\
    \ 5, 5) == total);\n}\n\nvoid test_weighted_ties() {\n    std::vector<int> values;\n\
    \    values.push_back(4);\n    values.push_back(1);\n    values.push_back(4);\n\
    \    values.push_back(2);\n    std::vector<long long> weights;\n    weights.push_back(10);\n\
    \    weights.push_back(20);\n    weights.push_back(30);\n    weights.push_back(40);\n\
    \n    m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);\n \
    \   assert(matrix.range_sum(0, 4) == 100);\n    assert(matrix.range_sum(0, 4,\
    \ 2) == 20);\n    assert(matrix.range_sum(0, 4, 2, 5) == 80);\n    assert(matrix.sum_k_smallest(0,\
    \ 4, 3) == 70);\n    assert(matrix.sum_k_largest(0, 4, 1) == 30);\n    assert(matrix.sum_k_largest(0,\
    \ 4, 2) == 40);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 23;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 70; trial++) {\n        int n = int(random() % 70);\n        std::vector<int>\
    \ values(n);\n        std::vector<long long> weights(n);\n        for (int i =\
    \ 0; i < n; i++) {\n            values[i] = int(random() % 61) - 30;\n       \
    \     weights[i] = static_cast<long long>(random() % 101) - 50;\n        }\n \
    \       m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);\n\
    \n        for (int query = 0; query < 500; query++) {\n            int l = int(random()\
    \ % std::uint64_t(n + 1));\n            int r = int(random() % std::uint64_t(n\
    \ + 1));\n            if (r < l) std::swap(l, r);\n            int lower = int(random()\
    \ % 81) - 40;\n            int upper = int(random() % 81) - 40;\n            if\
    \ (upper < lower) std::swap(lower, upper);\n\n            [[maybe_unused]] long\
    \ long total = 0;\n            [[maybe_unused]] long long below = 0;\n       \
    \     [[maybe_unused]] long long between = 0;\n            std::vector<std::pair<int,\
    \ int>> order;\n            for (int i = l; i < r; i++) {\n                total\
    \ += weights[i];\n                if (values[i] < upper) below += weights[i];\n\
    \                if (lower <= values[i] && values[i] < upper) {\n            \
    \        between += weights[i];\n                }\n                order.emplace_back(values[i],\
    \ i);\n            }\n            std::stable_sort(order.begin(), order.end(),\
    \ [](const auto& a, const auto& b) {\n                return a.first < b.first;\n\
    \            });\n\n            assert(matrix.range_sum(l, r) == total);\n   \
    \         assert(matrix.range_freq(l, r, upper) ==\n                   int(std::count_if(\n\
    \                       values.begin() + l,\n                       values.begin()\
    \ + r,\n                       [upper](int value) { return value < upper; }\n\
    \                   )));\n            assert(matrix.range_sum(l, r, upper) ==\
    \ below);\n            assert(matrix.range_sum(l, r, lower, upper) == between);\n\
    \n            [[maybe_unused]] long long smallest_sum = 0;\n            [[maybe_unused]]\
    \ long long largest_sum = 0;\n            for (int k = 0; k <= int(order.size());\
    \ k++) {\n                assert(matrix.sum_k_smallest(l, r, k) == smallest_sum);\n\
    \                assert(matrix.sum_k_largest(l, r, k) == largest_sum);\n     \
    \           if (k < int(order.size())) {\n                    smallest_sum +=\
    \ weights[order[k].second];\n                    largest_sum += weights[order[order.size()\
    \ - 1 - k].second];\n                }\n            }\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_value_sums();\n    test_weighted_ties();\n    test_randomized();\n\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) std::cin >> value;\n\n    m1une::ds::WaveletMatrixSum<long\
    \ long> matrix(values);\n    for (int query = 0; query < q; query++) {\n     \
    \   int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout << matrix.kth_smallest(l,\
    \ r, k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/range_query/wavelet_matrix_sum.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nvoid\
    \ test_value_sums() {\n    std::vector<long long> values;\n    values.push_back(std::numeric_limits<long\
    \ long>::min());\n    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrixSum<long\
    \ long, __int128_t> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n\n    [[maybe_unused]]\
    \ __int128_t total = 0;\n    for (long long value : values) total += value;\n\
    \    assert(matrix.range_sum(0, 5) == total);\n    assert(matrix.range_sum(0,\
    \ 5, 0LL) ==\n           __int128_t(std::numeric_limits<long long>::min()) - 10);\n\
    \    assert(matrix.range_sum(0, 5, -5LL, 1LL) == -10);\n    assert(matrix.sum_k_smallest(0,\
    \ 5, 0) == 0);\n    assert(matrix.sum_k_smallest(0, 5, 3) ==\n           __int128_t(std::numeric_limits<long\
    \ long>::min()) - 10);\n    assert(matrix.sum_k_largest(0, 5, 2) ==\n        \
    \   __int128_t(std::numeric_limits<long long>::max()));\n    assert(matrix.sum_k_largest(0,\
    \ 5, 5) == total);\n}\n\nvoid test_weighted_ties() {\n    std::vector<int> values;\n\
    \    values.push_back(4);\n    values.push_back(1);\n    values.push_back(4);\n\
    \    values.push_back(2);\n    std::vector<long long> weights;\n    weights.push_back(10);\n\
    \    weights.push_back(20);\n    weights.push_back(30);\n    weights.push_back(40);\n\
    \n    m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);\n \
    \   assert(matrix.range_sum(0, 4) == 100);\n    assert(matrix.range_sum(0, 4,\
    \ 2) == 20);\n    assert(matrix.range_sum(0, 4, 2, 5) == 80);\n    assert(matrix.sum_k_smallest(0,\
    \ 4, 3) == 70);\n    assert(matrix.sum_k_largest(0, 4, 1) == 30);\n    assert(matrix.sum_k_largest(0,\
    \ 4, 2) == 40);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 23;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 70; trial++) {\n        int n = int(random() % 70);\n        std::vector<int>\
    \ values(n);\n        std::vector<long long> weights(n);\n        for (int i =\
    \ 0; i < n; i++) {\n            values[i] = int(random() % 61) - 30;\n       \
    \     weights[i] = static_cast<long long>(random() % 101) - 50;\n        }\n \
    \       m1une::ds::WaveletMatrixSum<int, long long> matrix(values, weights);\n\
    \n        for (int query = 0; query < 500; query++) {\n            int l = int(random()\
    \ % std::uint64_t(n + 1));\n            int r = int(random() % std::uint64_t(n\
    \ + 1));\n            if (r < l) std::swap(l, r);\n            int lower = int(random()\
    \ % 81) - 40;\n            int upper = int(random() % 81) - 40;\n            if\
    \ (upper < lower) std::swap(lower, upper);\n\n            [[maybe_unused]] long\
    \ long total = 0;\n            [[maybe_unused]] long long below = 0;\n       \
    \     [[maybe_unused]] long long between = 0;\n            std::vector<std::pair<int,\
    \ int>> order;\n            for (int i = l; i < r; i++) {\n                total\
    \ += weights[i];\n                if (values[i] < upper) below += weights[i];\n\
    \                if (lower <= values[i] && values[i] < upper) {\n            \
    \        between += weights[i];\n                }\n                order.emplace_back(values[i],\
    \ i);\n            }\n            std::stable_sort(order.begin(), order.end(),\
    \ [](const auto& a, const auto& b) {\n                return a.first < b.first;\n\
    \            });\n\n            assert(matrix.range_sum(l, r) == total);\n   \
    \         assert(matrix.range_freq(l, r, upper) ==\n                   int(std::count_if(\n\
    \                       values.begin() + l,\n                       values.begin()\
    \ + r,\n                       [upper](int value) { return value < upper; }\n\
    \                   )));\n            assert(matrix.range_sum(l, r, upper) ==\
    \ below);\n            assert(matrix.range_sum(l, r, lower, upper) == between);\n\
    \n            [[maybe_unused]] long long smallest_sum = 0;\n            [[maybe_unused]]\
    \ long long largest_sum = 0;\n            for (int k = 0; k <= int(order.size());\
    \ k++) {\n                assert(matrix.sum_k_smallest(l, r, k) == smallest_sum);\n\
    \                assert(matrix.sum_k_largest(l, r, k) == largest_sum);\n     \
    \           if (k < int(order.size())) {\n                    smallest_sum +=\
    \ weights[order[k].second];\n                    largest_sum += weights[order[order.size()\
    \ - 1 - k].second];\n                }\n            }\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_value_sums();\n    test_weighted_ties();\n    test_randomized();\n\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) std::cin >> value;\n\n    m1une::ds::WaveletMatrixSum<long\
    \ long> matrix(values);\n    for (int query = 0; query < q; query++) {\n     \
    \   int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout << matrix.kth_smallest(l,\
    \ r, k) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/wavelet_matrix_sum.hpp
  isVerificationFile: true
  path: verify/ds/range_query/wavelet_matrix_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/wavelet_matrix_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/wavelet_matrix_sum.test.cpp
- /verify/verify/ds/range_query/wavelet_matrix_sum.test.cpp.html
title: verify/ds/range_query/wavelet_matrix_sum.test.cpp
---
