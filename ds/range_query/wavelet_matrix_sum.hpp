#ifndef M1UNE_WAVELET_MATRIX_SUM_HPP
#define M1UNE_WAVELET_MATRIX_SUM_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// A static wavelet matrix with additive weights.
// By default, each value is also used as its weight.
template <std::integral T, typename Sum = T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
struct WaveletMatrixSum {
    using value_type = T;
    using sum_type = Sum;
    using unsigned_type = std::make_unsigned_t<T>;

   private:
    static constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;
    static constexpr unsigned_type sign_mask = [] {
        if constexpr (std::signed_integral<T>) {
            return unsigned_type(1) << (bit_width - 1);
        } else {
            return unsigned_type(0);
        }
    }();

    struct BitVector {
        std::vector<std::uint64_t> bits;
        std::vector<int> prefix;

        BitVector() = default;

        explicit BitVector(int n)
            : bits((std::size_t(n) + 63) >> 6, 0),
              prefix(bits.size() + 1, 0) {}

        void set(int p) {
            bits[std::size_t(p) >> 6] |= std::uint64_t(1) << (p & 63);
        }

        void build() {
            for (std::size_t i = 0; i < bits.size(); i++) {
                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);
            }
        }

        bool get(int p) const {
            return (bits[std::size_t(p) >> 6] >> (p & 63)) & 1;
        }

        int rank1(int r) const {
            std::size_t word = std::size_t(r) >> 6;
            int offset = r & 63;
            int result = prefix[word];
            if (offset != 0) {
                result += std::popcount(
                    bits[word] & ((std::uint64_t(1) << offset) - 1)
                );
            }
            return result;
        }

        int rank0(int r) const {
            return r - rank1(r);
        }
    };

    int _n;
    std::vector<BitVector> _matrix;
    std::vector<int> _zero_count;
    std::vector<std::vector<Sum>> _zero_prefix;
    std::vector<Sum> _original_prefix;
    std::vector<Sum> _final_prefix;

    static unsigned_type encode(T value) {
        unsigned_type bits;
        if constexpr (std::signed_integral<T>) {
            bits = std::bit_cast<unsigned_type>(value);
        } else {
            bits = value;
        }
        return bits ^ sign_mask;
    }

    static T decode(unsigned_type key) {
        unsigned_type bits = key ^ sign_mask;
        if constexpr (std::signed_integral<T>) {
            return std::bit_cast<T>(bits);
        } else {
            return bits;
        }
    }

    static bool bit(unsigned_type value, int level) {
        return (value >> (bit_width - 1 - level)) & unsigned_type(1);
    }

    Sum zero_sum(int level, int l, int r) const {
        return _zero_prefix[level][r] - _zero_prefix[level][l];
    }

    Sum sum_less_encoded(int l, int r, unsigned_type upper) const {
        Sum result{};
        for (int level = 0; level < bit_width; level++) {
            int l0 = _matrix[level].rank0(l);
            int r0 = _matrix[level].rank0(r);
            if (bit(upper, level)) {
                result = result + zero_sum(level, l, r);
                l = _zero_count[level] + _matrix[level].rank1(l);
                r = _zero_count[level] + _matrix[level].rank1(r);
            } else {
                l = l0;
                r = r0;
            }
        }
        return result;
    }

    int count_less_encoded(int l, int r, unsigned_type upper) const {
        int result = 0;
        for (int level = 0; level < bit_width; level++) {
            int l0 = _matrix[level].rank0(l);
            int r0 = _matrix[level].rank0(r);
            if (bit(upper, level)) {
                result += r0 - l0;
                l = _zero_count[level] + _matrix[level].rank1(l);
                r = _zero_count[level] + _matrix[level].rank1(r);
            } else {
                l = l0;
                r = r0;
            }
        }
        return result;
    }

    void build(const std::vector<T>& values, const std::vector<Sum>& weights) {
        assert(values.size() == weights.size());

        std::vector<unsigned_type> current_keys(_n);
        std::vector<unsigned_type> next_keys(_n);
        std::vector<Sum> current_weights(weights);
        std::vector<Sum> next_weights(_n);
        for (int i = 0; i < _n; i++) current_keys[i] = encode(values[i]);

        _original_prefix.assign(std::size_t(_n) + 1, Sum{});
        for (int i = 0; i < _n; i++) {
            _original_prefix[i + 1] = _original_prefix[i] + weights[i];
        }

        _matrix.reserve(bit_width);
        _zero_prefix.reserve(bit_width);
        for (int level = 0; level < bit_width; level++) {
            _matrix.emplace_back(_n);
            _zero_prefix.emplace_back(std::size_t(_n) + 1, Sum{});
            for (int i = 0; i < _n; i++) {
                bool one = bit(current_keys[i], level);
                if (one) _matrix.back().set(i);
                _zero_prefix.back()[i + 1] = _zero_prefix.back()[i];
                if (!one) {
                    _zero_prefix.back()[i + 1] =
                        _zero_prefix.back()[i + 1] + current_weights[i];
                }
            }
            _matrix.back().build();

            int zeros = _matrix.back().rank0(_n);
            _zero_count[level] = zeros;
            int zero_pos = 0;
            int one_pos = zeros;
            for (int i = 0; i < _n; i++) {
                if (bit(current_keys[i], level)) {
                    next_keys[one_pos] = current_keys[i];
                    next_weights[one_pos] = current_weights[i];
                    one_pos++;
                } else {
                    next_keys[zero_pos] = current_keys[i];
                    next_weights[zero_pos] = current_weights[i];
                    zero_pos++;
                }
            }
            current_keys.swap(next_keys);
            current_weights.swap(next_weights);
        }

        _final_prefix.assign(std::size_t(_n) + 1, Sum{});
        for (int i = 0; i < _n; i++) {
            _final_prefix[i + 1] = _final_prefix[i] + current_weights[i];
        }
    }

   public:
    WaveletMatrixSum()
        : _n(0),
          _matrix(bit_width),
          _zero_count(bit_width, 0),
          _zero_prefix(bit_width, std::vector<Sum>(1, Sum{})),
          _original_prefix(1, Sum{}),
          _final_prefix(1, Sum{}) {}

    explicit WaveletMatrixSum(const std::vector<T>& values)
        requires std::convertible_to<T, Sum>
        : _n(int(values.size())),
          _matrix(),
          _zero_count(bit_width, 0) {
        std::vector<Sum> weights;
        weights.reserve(values.size());
        for (T value : values) weights.push_back(static_cast<Sum>(value));
        build(values, weights);
    }

    WaveletMatrixSum(
        const std::vector<T>& values,
        const std::vector<Sum>& weights
    ) : _n(int(values.size())),
        _matrix(),
        _zero_count(bit_width, 0) {
        build(values, weights);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    T access(int p) const {
        assert(0 <= p && p < _n);
        unsigned_type key = 0;
        for (int level = 0; level < bit_width; level++) {
            bool one = _matrix[level].get(p);
            if (one) {
                key |= unsigned_type(1) << (bit_width - 1 - level);
                p = _zero_count[level] + _matrix[level].rank1(p);
            } else {
                p = _matrix[level].rank0(p);
            }
        }
        return decode(key);
    }

    T operator[](int p) const {
        return access(p);
    }

    int rank(T value, int r) const {
        assert(0 <= r && r <= _n);
        return rank(value, 0, r);
    }

    int rank(T value, int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        unsigned_type key = encode(value);
        for (int level = 0; level < bit_width; level++) {
            if (bit(key, level)) {
                l = _zero_count[level] + _matrix[level].rank1(l);
                r = _zero_count[level] + _matrix[level].rank1(r);
            } else {
                l = _matrix[level].rank0(l);
                r = _matrix[level].rank0(r);
            }
        }
        return r - l;
    }

    T kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k < r - l);
        unsigned_type key = 0;
        for (int level = 0; level < bit_width; level++) {
            int l0 = _matrix[level].rank0(l);
            int r0 = _matrix[level].rank0(r);
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                k -= zeros;
                key |= unsigned_type(1) << (bit_width - 1 - level);
                l = _zero_count[level] + _matrix[level].rank1(l);
                r = _zero_count[level] + _matrix[level].rank1(r);
            }
        }
        return decode(key);
    }

    T kth_largest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k < r - l);
        return kth_smallest(l, r, r - l - 1 - k);
    }

    int range_freq(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        return count_less_encoded(l, r, encode(upper));
    }

    int range_freq(int l, int r, T lower, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        if (upper <= lower) return 0;
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    std::optional<T> prev_value(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        int count = range_freq(l, r, upper);
        if (count == 0) return std::nullopt;
        return kth_smallest(l, r, count - 1);
    }

    std::optional<T> next_value(int l, int r, T lower) const {
        assert(0 <= l && l <= r && r <= _n);
        int count = range_freq(l, r, lower);
        if (count == r - l) return std::nullopt;
        return kth_smallest(l, r, count);
    }

    Sum range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return _original_prefix[r] - _original_prefix[l];
    }

    Sum range_sum(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum_less_encoded(l, r, encode(upper));
    }

    Sum range_sum(int l, int r, T lower, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        if (upper <= lower) return Sum{};
        return range_sum(l, r, upper) - range_sum(l, r, lower);
    }

    Sum sum_k_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k <= r - l);
        Sum result{};
        for (int level = 0; level < bit_width; level++) {
            int l0 = _matrix[level].rank0(l);
            int r0 = _matrix[level].rank0(r);
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                result = result + zero_sum(level, l, r);
                k -= zeros;
                l = _zero_count[level] + _matrix[level].rank1(l);
                r = _zero_count[level] + _matrix[level].rank1(r);
            }
        }
        return result + (_final_prefix[l + k] - _final_prefix[l]);
    }

    Sum sum_k_largest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k <= r - l);
        return range_sum(l, r) - sum_k_smallest(l, r, r - l - k);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_WAVELET_MATRIX_SUM_HPP
