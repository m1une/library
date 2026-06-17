#ifndef M1UNE_UTILITIES_DYNAMIC_BITSET_HPP
#define M1UNE_UTILITIES_DYNAMIC_BITSET_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

namespace m1une {
namespace utilities {

struct DynamicBitset {
   private:
    int _n;
    std::vector<uint64_t> blocks;
    static constexpr int BITS_PER_BLOCK = 64;

    // Clears the extra bits in the last block so that bitwise operations and counts remain accurate
    void clean() {
        if (_n % BITS_PER_BLOCK != 0) {
            blocks.back() &= (1ULL << (_n % BITS_PER_BLOCK)) - 1;
        }
    }

   public:
    DynamicBitset() : _n(0) {}

    explicit DynamicBitset(int n, bool val = false) : _n(n) {
        blocks.assign((n + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK, val ? ~0ULL : 0ULL);
        if (val) clean();
    }

    // Returns the size of the bitset
    int size() const {
        return _n;
    }

    // Test the bit at index 'i'
    bool test(int i) const {
        assert(0 <= i && i < _n);
        return (blocks[i / BITS_PER_BLOCK] >> (i % BITS_PER_BLOCK)) & 1;
    }

    // Set the bit at index 'i' to true
    void set(int i) {
        assert(0 <= i && i < _n);
        blocks[i / BITS_PER_BLOCK] |= (1ULL << (i % BITS_PER_BLOCK));
    }

    // Set all bits to true
    void set() {
        std::fill(blocks.begin(), blocks.end(), ~0ULL);
        clean();
    }

    // Reset the bit at index 'i' to false
    void reset(int i) {
        assert(0 <= i && i < _n);
        blocks[i / BITS_PER_BLOCK] &= ~(1ULL << (i % BITS_PER_BLOCK));
    }

    // Reset all bits to false
    void reset() {
        std::fill(blocks.begin(), blocks.end(), 0ULL);
    }

    // Flip the bit at index 'i'
    void flip(int i) {
        assert(0 <= i && i < _n);
        blocks[i / BITS_PER_BLOCK] ^= (1ULL << (i % BITS_PER_BLOCK));
    }

    // Flip all bits
    void flip() {
        for (auto& block : blocks) {
            block = ~block;
        }
        clean();
    }

    // Count the number of bits set to true
    int count() const {
        int res = 0;
        for (uint64_t block : blocks) {
            res += __builtin_popcountll(block);
        }
        return res;
    }

    // Check if any bits are set to true
    bool any() const {
        for (uint64_t block : blocks) {
            if (block != 0) return true;
        }
        return false;
    }

    // Check if all bits are set to true
    bool all() const {
        return count() == _n;
    }

    // Check if no bits are set to true
    bool none() const {
        return !any();
    }

    // Bitwise operators
    DynamicBitset& operator&=(const DynamicBitset& other) {
        assert(_n == other._n);
        for (size_t i = 0; i < blocks.size(); ++i) {
            blocks[i] &= other.blocks[i];
        }
        return *this;
    }

    DynamicBitset& operator|=(const DynamicBitset& other) {
        assert(_n == other._n);
        for (size_t i = 0; i < blocks.size(); ++i) {
            blocks[i] |= other.blocks[i];
        }
        return *this;
    }

    DynamicBitset& operator^=(const DynamicBitset& other) {
        assert(_n == other._n);
        for (size_t i = 0; i < blocks.size(); ++i) {
            blocks[i] ^= other.blocks[i];
        }
        return *this;
    }

    DynamicBitset operator~() const {
        DynamicBitset res = *this;
        res.flip();
        return res;
    }

    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs) {
        return lhs &= rhs;
    }

    friend DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset& rhs) {
        return lhs |= rhs;
    }

    friend DynamicBitset operator^(DynamicBitset lhs, const DynamicBitset& rhs) {
        return lhs ^= rhs;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_DYNAMIC_BITSET_HPP
