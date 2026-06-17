#ifndef M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP
#define M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP 1

#include <vector>
#include <cassert>

namespace m1une {
namespace data_structure {

template <typename T>
struct FenwickTree {
   private:
    int _n;
    std::vector<T> data;

   public:
    FenwickTree() : _n(0) {}
    
    explicit FenwickTree(int n) : _n(n), data(n + 1, 0) {}
    
    explicit FenwickTree(const std::vector<T>& a) : _n(a.size()), data(a.size() + 1, 0) {
        // Initialize in O(N) time
        for (int i = 1; i <= _n; i++) {
            data[i] += a[i - 1];
            int p = i + (i & -i);
            if (p <= _n) {
                data[p] += data[i];
            }
        }
    }

    // Adds 'x' to the element at index 'p' (0-indexed)
    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p] += x;
            p += p & -p;
        }
    }

    // Returns the sum of elements in the range [0, r)
    T sum(int r) const {
        assert(0 <= r && r <= _n);
        T s = 0;
        while (r > 0) {
            s += data[r];
            r -= r & -r;
        }
        return s;
    }

    // Returns the sum of elements in the range [l, r)
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    // Returns the minimum index `r` such that the sum of [0, r) >= w.
    // Requires all elements in the tree to be non-negative.
    int lower_bound(T w) const {
        if (w <= 0) return 0;
        int x = 0;
        int k = 1;
        while (k <= _n) k <<= 1;
        for (k >>= 1; k > 0; k >>= 1) {
            if (x + k <= _n && data[x + k] < w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x + 1;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP
