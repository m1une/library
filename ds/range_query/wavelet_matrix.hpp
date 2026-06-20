#ifndef M1UNE_WAVELET_MATRIX_HPP
#define M1UNE_WAVELET_MATRIX_HPP 1

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

// A static wavelet matrix for integral values.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
struct WaveletMatrix {
    using value_type = T;
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

   public:
    WaveletMatrix() : _n(0), _matrix(bit_width), _zero_count(bit_width, 0) {}

    explicit WaveletMatrix(const std::vector<T>& values)
        : _n(int(values.size())),
          _matrix(),
          _zero_count(bit_width, 0) {
        std::vector<unsigned_type> current(_n);
        std::vector<unsigned_type> next(_n);
        for (int i = 0; i < _n; i++) current[i] = encode(values[i]);

        _matrix.reserve(bit_width);
        for (int level = 0; level < bit_width; level++) {
            _matrix.emplace_back(_n);
            for (int i = 0; i < _n; i++) {
                if (bit(current[i], level)) _matrix.back().set(i);
            }
            _matrix.back().build();

            int zeros = _matrix.back().rank0(_n);
            _zero_count[level] = zeros;
            int zero_pos = 0;
            int one_pos = zeros;
            for (unsigned_type value : current) {
                if (bit(value, level)) {
                    next[one_pos++] = value;
                } else {
                    next[zero_pos++] = value;
                }
            }
            current.swap(next);
        }
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_WAVELET_MATRIX_HPP
