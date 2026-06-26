#ifndef M1UNE_DS_FENWICK_TREE_HPP
#define M1UNE_DS_FENWICK_TREE_HPP 1

#include <cassert>
#include <vector>

namespace m1une {
namespace ds {

template <typename T>
struct FenwickTree {
   private:
    int _n;
    int _max_power;
    std::vector<T> _data;

    static int max_power_leq(int n) {
        int result = 1;
        while (result <= n / 2) result <<= 1;
        return result;
    }

    T prefix_sum(int r) const {
        T result{};
        const T* data = _data.data();
        while (r > 0) {
            result += data[r];
            r -= r & -r;
        }
        return result;
    }

   public:
    FenwickTree() : _n(0), _max_power(0) {}

    explicit FenwickTree(int n)
        : _n(n), _max_power(max_power_leq(n > 0 ? n : 1)), _data(n + 1, T{}) {}

    explicit FenwickTree(const std::vector<T>& a)
        : _n(int(a.size())),
          _max_power(max_power_leq(_n > 0 ? _n : 1)),
          _data(a.size() + 1, T{}) {
        for (int i = 1; i <= _n; ++i) {
            _data[i] += a[i - 1];
            const int p = i + (i & -i);
            if (p <= _n) {
                _data[p] += _data[i];
            }
        }
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    // Adds `x` to the element at zero-based index `p`.
    void add(int p, const T& x) {
        assert(0 <= p && p < _n);
        ++p;
        T* data = _data.data();
        while (p <= _n) {
            data[p] += x;
            p += p & -p;
        }
    }

    // Returns the sum of elements in the range [0, r).
    T sum(int r) const {
        assert(0 <= r && r <= _n);
        return prefix_sum(r);
    }

    // Returns the sum of elements in the range [l, r).
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return prefix_sum(r) - prefix_sum(l);
    }

    // Returns the minimum index `r` such that the sum of [0, r) >= w.
    // Requires all elements in the tree to be non-negative.
    int lower_bound(T w) const {
        if (w <= 0) return 0;
        int x = 0;
        const T* data = _data.data();
        for (int k = _max_power; k > 0; k >>= 1) {
            if (x + k <= _n && data[x + k] < w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x + 1;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_FENWICK_TREE_HPP
