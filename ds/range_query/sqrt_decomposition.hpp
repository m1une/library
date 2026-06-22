#ifndef M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP
#define M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// Mutable square-root decomposition for point assignments and range products.
template <m1une::monoid::IsMonoid Monoid>
struct SqrtDecomposition {
    using T = typename Monoid::value_type;

   private:
    int _n;
    int _block_size;
    int _block_count;
    std::vector<T> _values;
    std::vector<T> _block_product;

    template <class U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {
            return Monoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    void initialize_blocks() {
        if (_n == 0) {
            _block_size = 1;
            _block_count = 0;
            _block_product.clear();
            return;
        }
        _block_size = std::max(
            1,
            int(std::sqrt(static_cast<long double>(_n)))
        );
        while (1LL * _block_size * _block_size < _n) ++_block_size;
        _block_count = (_n + _block_size - 1) / _block_size;
        _block_product.assign(_block_count, Monoid::id());
        for (int block = 0; block < _block_count; ++block) {
            rebuild_block(block);
        }
    }

    void rebuild_block(int block) {
        assert(0 <= block && block < _block_count);
        int left = block * _block_size;
        int right = std::min(_n, left + _block_size);
        T product = Monoid::id();
        for (int index = left; index < right; ++index) {
            product = Monoid::op(product, _values[index]);
        }
        _block_product[block] = std::move(product);
    }

   public:
    SqrtDecomposition()
        : _n(0), _block_size(1), _block_count(0) {}

    explicit SqrtDecomposition(int n)
        : _n(n), _block_size(1), _block_count(0), _values(n, Monoid::id()) {
        assert(0 <= n);
        initialize_blocks();
    }

    explicit SqrtDecomposition(const std::vector<T>& values)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _values(values) {
        initialize_blocks();
    }

    explicit SqrtDecomposition(std::vector<T>&& values)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _values(std::move(values)) {
        initialize_blocks();
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Monoid::make(x); } ||
        requires(U x, int i) { Monoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit SqrtDecomposition(const std::vector<U>& values)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _values(values.size(), Monoid::id()) {
        for (int index = 0; index < _n; ++index) {
            _values[index] = make_value(values[index], index);
        }
        initialize_blocks();
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int block_size() const {
        return _block_size;
    }

    int block_count() const {
        return _block_count;
    }

    int block_of(int index) const {
        assert(0 <= index && index < _n);
        return index / _block_size;
    }

    std::pair<int, int> block_range(int block) const {
        assert(0 <= block && block < _block_count);
        int left = block * _block_size;
        return {left, std::min(_n, left + _block_size)};
    }

    const std::vector<T>& values() const {
        return _values;
    }

    const std::vector<T>& block_products() const {
        return _block_product;
    }

    const T& get(int index) const {
        assert(0 <= index && index < _n);
        return _values[index];
    }

    const T& operator[](int index) const {
        return get(index);
    }

    // Assigns one element and rebuilds its block.
    void set(int index, T value) {
        assert(0 <= index && index < _n);
        _values[index] = std::move(value);
        rebuild_block(block_of(index));
    }

    // Returns the ordered monoid product over [left, right).
    T prod(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        T result = Monoid::id();
        while (left < right && left % _block_size != 0) {
            result = Monoid::op(result, _values[left++]);
        }
        while (left + _block_size <= right) {
            result = Monoid::op(
                result,
                _block_product[left / _block_size]
            );
            left += _block_size;
        }
        while (left < right) {
            result = Monoid::op(result, _values[left++]);
        }
        return result;
    }

    T all_prod() const {
        T result = Monoid::id();
        for (const T& product : _block_product) {
            result = Monoid::op(result, product);
        }
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP
