---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/wavelet_matrix_sum.test.cpp
    title: verify/ds/range_query/wavelet_matrix_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/wavelet_matrix_sum.hpp\"\n\n\n\n#include\
    \ <bit>\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet\
    \ matrix with additive weights.\n// By default, each value is also used as its\
    \ weight.\ntemplate <std::integral T, typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrixSum {\n    using value_type = T;\n    using sum_type\
    \ = Sum;\n    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n\
    \    static constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n\
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
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_WAVELET_MATRIX_SUM_HPP\n#define M1UNE_WAVELET_MATRIX_SUM_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet\
    \ matrix with additive weights.\n// By default, each value is also used as its\
    \ weight.\ntemplate <std::integral T, typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrixSum {\n    using value_type = T;\n    using sum_type\
    \ = Sum;\n    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n\
    \    static constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n\
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
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_WAVELET_MATRIX_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/wavelet_matrix_sum.hpp
  requiredBy: []
  timestamp: '2026-06-21 02:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/wavelet_matrix_sum.test.cpp
documentation_of: ds/range_query/wavelet_matrix_sum.hpp
layout: document
title: Wavelet Matrix with Sums
---

## Overview

`m1une::ds::WaveletMatrixSum` is a static wavelet matrix that stores an
additive weight for every value. It supports range order statistics together
with:

* total weight in an index range,
* total weight for values below a bound or inside a value interval, and
* total weight of the smallest or largest `k` values.

By default, each value is also its weight, producing ordinary sums of selected
values. A separate weight vector can instead represent costs, counts, or other
additive data.

Signed values are ordered across their full type range by an internal sign-bit
transform. No coordinate compression is required.

## Template Parameters

* `T`: A non-`bool` integral value type used for ordering.
* `Sum`: The weight and sum type. It defaults to `T`.

`Sum{}` must be the additive identity, and `Sum` must support addition and
subtraction. Choose a sufficiently wide type because arithmetic overflow is not
checked.

Let $B$ be the bit width of `T`.

## Construction

* `WaveletMatrixSum()`: creates an empty matrix.
* `WaveletMatrixSum(const vector<T>& values)`: uses each value as its own
  weight. This requires `T` to be convertible to `Sum`.
* `WaveletMatrixSum(const vector<T>& values, const vector<Sum>& weights)`:
  associates `weights[i]` with `values[i]`.

The value and weight vectors must have equal lengths. Construction takes
$O(NB)$ time and $O(NB)$ storage.

## Methods

All index and value intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(B)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(B)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(B)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(B)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value. | $O(B)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value. | $O(B)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper`. | $O(B)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)`. | $O(B)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(B)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(B)$ |
| `Sum range_sum(int l, int r)` | Returns the total weight in `[l, r)`. | $O(1)$ |
| `Sum range_sum(int l, int r, T upper)` | Sums weights whose values are less than `upper`. | $O(B)$ |
| `Sum range_sum(int l, int r, T lower, T upper)` | Sums weights whose values are in `[lower, upper)`. | $O(B)$ |
| `Sum sum_k_smallest(int l, int r, int k)` | Sums the weights of the smallest `k` values. | $O(B)$ |
| `Sum sum_k_largest(int l, int r, int k)` | Sums the weights of the largest `k` values. | $O(B)$ |

The `k` used by sum methods may range from `0` through `r - l`, inclusive. If
equal values have different weights, `sum_k_smallest` selects ties in original
index order, while `sum_k_largest` selects them in reverse original index order.

## Example

```cpp
#include "ds/range_query/wavelet_matrix_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrixSum<long long> matrix(values);

    std::cout << matrix.range_sum(0, 5, 0, 6) << "\n"; // 11
    std::cout << matrix.sum_k_smallest(0, 5, 3) << "\n"; // 4

    std::vector<int> keys = {4, 1, 4, 2};
    std::vector<long long> weights = {10, 20, 30, 40};
    m1une::ds::WaveletMatrixSum<int, long long> weighted(keys, weights);

    std::cout << weighted.range_sum(0, 4, 2, 5) << "\n"; // 80
}
```
