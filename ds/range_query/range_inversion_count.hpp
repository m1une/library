#ifndef M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP
#define M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace m1une {
namespace ds {

// Static range inversion counts with O(N sqrt N) preprocessing and
// O(sqrt N) queries.
template <class T>
struct RangeInversionCount {
   private:
    int _n;
    int _block_size;
    int _block_count;
    std::vector<int> _rank;
    std::vector<std::vector<int>> _boundary_less;
    std::vector<std::vector<long long>> _from_boundary;
    std::vector<std::vector<long long>> _local_inversion;
    std::vector<std::vector<int>> _sorted_suffix;
    std::vector<std::vector<int>> _sorted_prefix;
    std::vector<int> _greater_before_in_block;

    int block_start(int block) const {
        return block * _block_size;
    }

    int block_end(int block) const {
        return std::min(_n, block_start(block) + _block_size);
    }

    static long long cross_inversions(
        const std::vector<int>& left,
        const std::vector<int>& right
    ) {
        long long result = 0;
        std::size_t smaller = 0;
        for (int value : left) {
            while (smaller < right.size() && right[smaller] < value) {
                smaller++;
            }
            result += static_cast<long long>(smaller);
        }
        return result;
    }

    void build_local_data() {
        _local_inversion.resize(_n);
        _sorted_suffix.resize(_n);
        _sorted_prefix.resize(_n + 1);
        _greater_before_in_block.assign(_n, 0);

        for (int block = 0; block < _block_count; ++block) {
            int start = block_start(block);
            int end = block_end(block);
            int length = end - start;
            std::vector<std::vector<int>> greater(
                length,
                std::vector<int>(length, 0)
            );

            for (int right = 0; right < length; ++right) {
                int count = 0;
                for (int left = right - 1; 0 <= left; --left) {
                    count += _rank[start + left] > _rank[start + right];
                    greater[left][right] = count;
                }
                _greater_before_in_block[start + right] =
                    right == 0 ? 0 : greater[0][right];
            }

            for (int left = 0; left < length; ++left) {
                _local_inversion[start + left].assign(
                    length - left + 1,
                    0
                );
                long long inversions = 0;
                for (int right = left; right < length; ++right) {
                    inversions += greater[left][right];
                    _local_inversion[start + left][right - left + 1] =
                        inversions;
                }
            }

            std::vector<int> sorted;
            if (start == 0) _sorted_prefix[start] = sorted;
            for (int index = start; index < end; ++index) {
                sorted.insert(
                    std::upper_bound(
                        sorted.begin(),
                        sorted.end(),
                        _rank[index]
                    ),
                    _rank[index]
                );
                _sorted_prefix[index + 1] = sorted;
            }

            sorted.clear();
            for (int index = end - 1; start <= index; --index) {
                sorted.insert(
                    std::upper_bound(
                        sorted.begin(),
                        sorted.end(),
                        _rank[index]
                    ),
                    _rank[index]
                );
                _sorted_suffix[index] = sorted;
            }
        }
    }

    void build_boundary_counts(int value_count) {
        _boundary_less.assign(
            _block_count + 1,
            std::vector<int>(value_count + 1, 0)
        );
        std::vector<int> frequency(value_count, 0);
        for (int block = 0; block <= _block_count; ++block) {
            int boundary = std::min(_n, block_start(block));
            if (block != 0) {
                int previous = block_start(block - 1);
                for (int index = previous; index < boundary; ++index) {
                    frequency[_rank[index]]++;
                }
            }
            int count = 0;
            for (int rank = 0; rank < value_count; ++rank) {
                _boundary_less[block][rank] = count;
                count += frequency[rank];
            }
            _boundary_less[block][value_count] = count;
        }
    }

    void build_boundary_inversions() {
        _from_boundary.assign(
            _block_count + 1,
            std::vector<long long>(_n + 1, 0)
        );
        for (int first_block = 0; first_block < _block_count; ++first_block) {
            int start = block_start(first_block);
            long long inversions = 0;
            for (int index = start; index < _n; ++index) {
                int current_block = index / _block_size;
                int full_length =
                    block_start(current_block) - start;
                int less_equal =
                    _boundary_less[current_block][_rank[index] + 1]
                    - _boundary_less[first_block][_rank[index] + 1];
                int greater_in_full_blocks = full_length - less_equal;
                inversions +=
                    greater_in_full_blocks
                    + _greater_before_in_block[index];
                _from_boundary[first_block][index + 1] = inversions;
            }
        }
    }

   public:
    RangeInversionCount()
        : _n(0), _block_size(1), _block_count(0) {}

    explicit RangeInversionCount(const std::vector<T>& values)
        : _n(int(values.size())), _block_size(1), _block_count(0) {
        if (_n == 0) return;

        _block_size = std::max(
            1,
            int(std::sqrt(static_cast<long double>(_n)))
        );
        while (1LL * _block_size * _block_size < _n) ++_block_size;
        _block_count = (_n + _block_size - 1) / _block_size;

        std::vector<T> sorted = values;
        std::sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
        _rank.resize(_n);
        for (int index = 0; index < _n; ++index) {
            _rank[index] = int(
                std::lower_bound(
                    sorted.begin(),
                    sorted.end(),
                    values[index]
                ) - sorted.begin()
            );
        }

        build_local_data();
        build_boundary_counts(int(sorted.size()));
        build_boundary_inversions();
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

    // Returns the number of pairs (i, j) with
    // left <= i < j < right and values[i] > values[j].
    long long query(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        if (right - left <= 1) return 0;

        int left_block = left / _block_size;
        int right_block = (right - 1) / _block_size;
        if (left_block == right_block) {
            return _local_inversion[left][right - left];
        }

        int middle_left = block_end(left_block);
        int middle_block = left_block + 1;
        long long result = _local_inversion[left][middle_left - left];
        result += _from_boundary[middle_block][right];

        int trailing_block = (right - 1) / _block_size;
        for (int index = left; index < middle_left; ++index) {
            int rank = _rank[index];
            result +=
                _boundary_less[trailing_block][rank]
                - _boundary_less[middle_block][rank];
        }

        result += cross_inversions(
            _sorted_suffix[left],
            _sorted_prefix[right]
        );
        return result;
    }

    long long inversion_count(int left, int right) const {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP
