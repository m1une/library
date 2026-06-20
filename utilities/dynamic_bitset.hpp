#ifndef M1UNE_UTILITIES_DYNAMIC_BITSET_HPP
#define M1UNE_UTILITIES_DYNAMIC_BITSET_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace m1une {
namespace utilities {

struct DynamicBitset {
   private:
    static constexpr int BITS_PER_BLOCK = 64;
    static constexpr uint64_t FULL_BLOCK = ~uint64_t{0};

    int _n;
    std::vector<uint64_t> blocks;

    static int block_count(int n) {
        assert(n >= 0);
        return (n + BITS_PER_BLOCK - 1) >> 6;
    }

    uint64_t tail_mask() const {
        const int rem = _n & (BITS_PER_BLOCK - 1);
        return rem == 0 ? FULL_BLOCK : ((uint64_t{1} << rem) - 1);
    }

    // Keep unused bits in the last block equal to zero.
    void clean() {
        if (!blocks.empty()) blocks.back() &= tail_mask();
    }

   public:
    DynamicBitset() : _n(0), blocks() {}

    explicit DynamicBitset(int n, bool val = false) : _n(n), blocks(block_count(n), val ? FULL_BLOCK : 0) {
        if (val) clean();
    }

    // Returns the logical number of bits.
    int size() const {
        return _n;
    }

    // Returns whether the bit at index i is set.
    bool test(int i) const {
        assert(0 <= i && i < _n);
        return (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) & 1;
    }

    // Sets the bit at index i to true.
    void set(int i) {
        assert(0 <= i && i < _n);
        blocks[i >> 6] |= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));
    }

    // Sets all bits to true.
    void set() {
        std::fill(blocks.begin(), blocks.end(), FULL_BLOCK);
        clean();
    }

    // Sets the bit at index i to false.
    void reset(int i) {
        assert(0 <= i && i < _n);
        blocks[i >> 6] &= ~(uint64_t{1} << (i & (BITS_PER_BLOCK - 1)));
    }

    // Sets all bits to false.
    void reset() {
        std::fill(blocks.begin(), blocks.end(), uint64_t{0});
    }

    // Flips the bit at index i.
    void flip(int i) {
        assert(0 <= i && i < _n);
        blocks[i >> 6] ^= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));
    }

    // Flips all bits.
    void flip() {
        for (uint64_t& block : blocks) block = ~block;
        clean();
    }

    // Returns the number of set bits.
    int popcount() const {
        int res = 0;
        for (uint64_t block : blocks) res += __builtin_popcountll(block);
        return res;
    }

    // Returns the index of the least significant set bit, or -1 if no bit is set.
    int lowbit() const {
        const int m = static_cast<int>(blocks.size());
        for (int i = 0; i < m; ++i) {
            if (blocks[i] != 0) return (i << 6) + __builtin_ctzll(blocks[i]);
        }
        return -1;
    }

    // Returns the index of the most significant set bit, or -1 if no bit is set.
    int topbit() const {
        for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i) {
            if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK - 1 - __builtin_clzll(blocks[i]));
        }
        return -1;
    }

    // Returns whether at least one bit is set.
    bool any() const {
        for (uint64_t block : blocks) {
            if (block != 0) return true;
        }
        return false;
    }

    // Returns whether every logical bit is set.
    bool all() const {
        if (_n == 0) return true;

        const int m = static_cast<int>(blocks.size());
        for (int i = 0; i + 1 < m; ++i) {
            if (blocks[i] != FULL_BLOCK) return false;
        }
        return blocks.back() == tail_mask();
    }

    // Returns whether no bit is set.
    bool none() const {
        return !any();
    }

    DynamicBitset& operator&=(const DynamicBitset& other) {
        assert(_n == other._n);
        const std::size_t m = blocks.size();
        for (std::size_t i = 0; i < m; ++i) blocks[i] &= other.blocks[i];
        return *this;
    }

    DynamicBitset& operator|=(const DynamicBitset& other) {
        assert(_n == other._n);
        const std::size_t m = blocks.size();
        for (std::size_t i = 0; i < m; ++i) blocks[i] |= other.blocks[i];
        return *this;
    }

    DynamicBitset& operator^=(const DynamicBitset& other) {
        assert(_n == other._n);
        const std::size_t m = blocks.size();
        for (std::size_t i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];
        return *this;
    }

    DynamicBitset operator~() const {
        DynamicBitset res = *this;
        res.flip();
        return res;
    }

    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs) {
        lhs &= rhs;
        return lhs;
    }

    friend DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset& rhs) {
        lhs |= rhs;
        return lhs;
    }

    friend DynamicBitset operator^(DynamicBitset lhs, const DynamicBitset& rhs) {
        lhs ^= rhs;
        return lhs;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_DYNAMIC_BITSET_HPP
