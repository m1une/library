#ifndef M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP
#define M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// Static Sqrt Tree with O(1) monoid-product queries.
template <m1une::monoid::IsMonoid Monoid>
struct SqrtTree {
    using T = typename Monoid::value_type;

   private:
    int _n;
    std::size_t _padded_size;
    std::vector<T> _values;
    std::vector<int> _layers;
    std::vector<int> _layer_for_bit;
    std::vector<std::vector<T>> _prefix;
    std::vector<std::vector<T>> _suffix;
    std::vector<std::vector<T>> _between;

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

    void build_layers() {
        _layers.clear();
        _layer_for_bit.clear();
        if (_n <= 1) return;

        int exponent = std::bit_width(_padded_size) - 1;
        _layers.push_back(exponent);
        while (_layers.back() != 0) {
            int current = _layers.back();
            _layers.push_back(current == 1 ? 0 : (current + 1) / 2);
        }

        _layer_for_bit.assign(exponent, -1);
        for (int layer = 0; layer + 1 < int(_layers.size()); ++layer) {
            for (
                int bit = _layers[layer + 1];
                bit < _layers[layer];
                ++bit
            ) {
                _layer_for_bit[bit] = layer;
            }
        }
    }

    void build_level(int layer) {
        int node_exponent = _layers[layer];
        int block_exponent = _layers[layer + 1];
        std::size_t node_size = std::size_t(1) << node_exponent;
        std::size_t block_size = std::size_t(1) << block_exponent;
        std::size_t block_count = node_size / block_size;
        std::size_t node_count = _padded_size / node_size;

        _prefix[layer].assign(_padded_size, Monoid::id());
        _suffix[layer].assign(_padded_size, Monoid::id());
        _between[layer].assign(
            node_count * block_count * block_count,
            Monoid::id()
        );

        for (
            std::size_t block_start = 0;
            block_start < _padded_size;
            block_start += block_size
        ) {
            std::size_t block_end = block_start + block_size;
            _prefix[layer][block_start] = _values[block_start];
            for (
                std::size_t index = block_start + 1;
                index < block_end;
                ++index
            ) {
                _prefix[layer][index] = Monoid::op(
                    _prefix[layer][index - 1],
                    _values[index]
                );
            }

            _suffix[layer][block_end - 1] = _values[block_end - 1];
            for (std::size_t index = block_end - 1; block_start < index;) {
                --index;
                _suffix[layer][index] = Monoid::op(
                    _values[index],
                    _suffix[layer][index + 1]
                );
            }
        }

        for (std::size_t node = 0; node < node_count; ++node) {
            std::size_t node_start = node * node_size;
            std::size_t table_start =
                node * block_count * block_count;
            for (std::size_t first = 0; first < block_count; ++first) {
                T product = Monoid::id();
                for (std::size_t last = first; last < block_count; ++last) {
                    std::size_t block_end =
                        node_start + (last + 1) * block_size;
                    product = Monoid::op(
                        product,
                        _prefix[layer][block_end - 1]
                    );
                    _between[layer][
                        table_start + first * block_count + last
                    ] = product;
                }
            }
        }
    }

    void build() {
        if (_n == 0) {
            _padded_size = 0;
            _layers.clear();
            _layer_for_bit.clear();
            _prefix.clear();
            _suffix.clear();
            _between.clear();
            return;
        }

        _padded_size = std::bit_ceil(std::size_t(_n));
        _values.resize(_padded_size, Monoid::id());
        build_layers();
        int level_count = _layers.empty() ? 0 : int(_layers.size()) - 1;
        _prefix.resize(level_count);
        _suffix.resize(level_count);
        _between.resize(level_count);
        for (int layer = 0; layer < level_count; ++layer) {
            build_level(layer);
        }
    }

   public:
    SqrtTree() : _n(0), _padded_size(0) {}

    explicit SqrtTree(const std::vector<T>& values)
        : _n(int(values.size())),
          _padded_size(0),
          _values(values) {
        build();
    }

    explicit SqrtTree(std::vector<T>&& values)
        : _n(int(values.size())),
          _padded_size(0),
          _values(std::move(values)) {
        build();
    }

    template <class U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Monoid::make(x); } ||
        requires(U x, int i) { Monoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit SqrtTree(const std::vector<U>& values)
        : _n(int(values.size())),
          _padded_size(0),
          _values(values.size(), Monoid::id()) {
        for (int index = 0; index < _n; ++index) {
            _values[index] = make_value(values[index], index);
        }
        build();
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    // Returns the ordered monoid product over [left, right).
    T prod(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return Monoid::id();
        --right;
        if (left == right) return _values[left];

        std::size_t first = std::size_t(left);
        std::size_t last = std::size_t(right);
        int differing_bit = std::bit_width(first ^ last) - 1;
        int layer = _layer_for_bit[differing_bit];
        int node_exponent = _layers[layer];
        int block_exponent = _layers[layer + 1];
        std::size_t node_size = std::size_t(1) << node_exponent;
        std::size_t block_size = std::size_t(1) << block_exponent;
        std::size_t block_count = node_size / block_size;
        std::size_t node = first / node_size;
        std::size_t first_block = (first % node_size) / block_size;
        std::size_t last_block = (last % node_size) / block_size;

        T result = _suffix[layer][first];
        if (first_block + 1 < last_block) {
            std::size_t table_start =
                node * block_count * block_count;
            result = Monoid::op(
                result,
                _between[layer][
                    table_start
                    + (first_block + 1) * block_count
                    + (last_block - 1)
                ]
            );
        }
        return Monoid::op(result, _prefix[layer][last]);
    }

    T all_prod() const {
        return prod(0, _n);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP
