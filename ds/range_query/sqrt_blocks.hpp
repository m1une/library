#ifndef M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP
#define M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Square-root decomposition framework with user-defined per-block state.
template <class T, class Block>
struct SqrtBlocks {
   private:
    int _n;
    int _block_size;
    int _block_count;
    std::vector<T> _values;
    std::vector<Block> _blocks;

    void initialize_blocks(int requested_block_size) {
        if (requested_block_size > 0) {
            _block_size = requested_block_size;
        } else {
            _block_size = std::max(
                1,
                int(std::ceil(std::sqrt(static_cast<long double>(_n))))
            );
        }
        _block_count = _n == 0 ? 0 : 1 + (_n - 1) / _block_size;
        _blocks.resize(_block_count);
        for (int block_index = 0; block_index < _block_count; ++block_index) {
            rebuild(block_index);
        }
    }

   public:
    SqrtBlocks()
        : _n(0), _block_size(1), _block_count(0) {}

    explicit SqrtBlocks(std::vector<T> values, int block_size = -1)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _values(std::move(values)) {
        initialize_blocks(block_size);
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

    std::pair<int, int> block_range(int block_index) const {
        assert(0 <= block_index && block_index < _block_count);
        int left = block_index * _block_size;
        return {left, std::min(_n, left + _block_size)};
    }

    const std::vector<T>& values() const {
        return _values;
    }

    const Block& block(int block_index) const {
        assert(0 <= block_index && block_index < _block_count);
        return _blocks[block_index];
    }

    Block& block(int block_index) {
        assert(0 <= block_index && block_index < _block_count);
        return _blocks[block_index];
    }

    // Rebuilds the cached state from raw values. This does not push first.
    void rebuild(int block_index) {
        auto [left, right] = block_range(block_index);
        _blocks[block_index].build(_values, left, right);
    }

    // Materializes this block's optional lazy state into raw values.
    void push(int block_index) {
        assert(0 <= block_index && block_index < _block_count);
        if constexpr (requires(
            Block& current,
            std::vector<T>& values,
            int left,
            int right
        ) {
            current.push(values, left, right);
        }) {
            auto [left, right] = block_range(block_index);
            _blocks[block_index].push(_values, left, right);
        }
    }

    T get(int index) const {
        assert(0 <= index && index < _n);
        const Block& current = _blocks[block_of(index)];
        if constexpr (requires(
            const Block& candidate,
            const T& raw,
            int position
        ) {
            candidate.value(raw, position);
        }) {
            return current.value(_values[index], index);
        } else if constexpr (requires(const Block& candidate, const T& raw) {
            candidate.value(raw);
        }) {
            return current.value(_values[index]);
        } else {
            return _values[index];
        }
    }

    T operator[](int index) const {
        return get(index);
    }

    void set(int index, T value) {
        assert(0 <= index && index < _n);
        int block_index = block_of(index);
        push(block_index);
        _values[index] = std::move(value);
        rebuild(block_index);
    }

    template <class F>
    void apply_point(int index, F f) {
        assert(0 <= index && index < _n);
        int block_index = block_of(index);
        push(block_index);
        f(_values[index]);
        rebuild(block_index);
    }

    template <class Full, class Partial>
    void update_range(int left, int right, Full full, Partial partial) {
        assert(0 <= left && left <= right && right <= _n);
        while (left < right) {
            int block_index = left / _block_size;
            auto [block_left, block_right] = block_range(block_index);
            int segment_right = std::min(right, block_right);
            if (left == block_left && segment_right == block_right) {
                full(block_index, _blocks[block_index]);
            } else {
                push(block_index);
                partial(
                    left,
                    segment_right,
                    block_index,
                    _values,
                    _blocks[block_index]
                );
                rebuild(block_index);
            }
            left = segment_right;
        }
    }

    template <class Full, class Partial>
    void query_range(int left, int right, Full full, Partial partial) const {
        assert(0 <= left && left <= right && right <= _n);
        while (left < right) {
            int block_index = left / _block_size;
            auto [block_left, block_right] = block_range(block_index);
            int segment_right = std::min(right, block_right);
            if (left == block_left && segment_right == block_right) {
                full(block_index, _blocks[block_index]);
            } else {
                partial(left, segment_right, block_index, _blocks[block_index]);
            }
            left = segment_right;
        }
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_SQRT_BLOCKS_HPP
