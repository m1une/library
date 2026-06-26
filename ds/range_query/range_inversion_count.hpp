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
    int _value_count;
    std::vector<int> _rank;
    std::vector<std::vector<int>> _boundary_less;
    std::vector<std::vector<int>> _local_inversion;
    std::vector<std::vector<int>> _sorted_suffix;
    std::vector<std::vector<int>> _sorted_prefix;
    std::vector<long long> _block_inversion;
    std::vector<std::vector<long long>> _full_block_inversion;

    int block_start(int block) const {
        return block * _block_size;
    }

    int block_end(int block) const {
        return std::min(_n, block_start(block) + _block_size);
    }

    int local_index(int block, int offset, int length) const {
        int block_length = block_end(block) - block_start(block);
        return offset * (block_length + 1)
               - offset * (offset - 1) / 2
               + length;
    }

    long long local_query(int left, int right) const {
        if (right - left <= 1) return 0;
        int block = left / _block_size;
        int offset = left - block_start(block);
        return _local_inversion[block][
            local_index(block, offset, right - left)
        ];
    }

    int count_less_blocks(int first_block, int last_block, int rank) const {
        if (first_block >= last_block) return 0;
        return _boundary_less[last_block][rank]
               - _boundary_less[first_block][rank];
    }

    int count_greater_blocks(int first_block, int last_block, int rank) const {
        int length = block_start(last_block) - block_start(first_block);
        return length - count_less_blocks(first_block, last_block, rank + 1);
    }

    static long long cross_inversions(
        const std::vector<int>& left,
        const std::vector<int>& right
    ) {
        long long result = 0;
        int smaller = 0;
        for (int value : left) {
            while (smaller < int(right.size()) && right[smaller] < value) {
                ++smaller;
            }
            result += smaller;
        }
        return result;
    }

    void build_local_data() {
        _local_inversion.resize(_block_count);
        _sorted_suffix.resize(_n);
        _sorted_prefix.resize(_n + 1);
        _block_inversion.assign(_block_count, 0);

        for (int block = 0; block < _block_count; ++block) {
            int start = block_start(block);
            int end = block_end(block);
            int length = end - start;
            std::vector<int> greater(length * length, 0);
            _local_inversion[block].assign(length * (length + 3) / 2, 0);

            for (int right = 0; right < length; ++right) {
                int count = 0;
                for (int left = right - 1; 0 <= left; --left) {
                    count += _rank[start + left] > _rank[start + right];
                    greater[left * length + right] = count;
                }
            }

            for (int left = 0; left < length; ++left) {
                long long inversions = 0;
                for (int right = left; right < length; ++right) {
                    inversions += greater[left * length + right];
                    _local_inversion[block][
                        local_index(block, left, right - left + 1)
                    ] =
                        int(inversions);
                }
            }
            _block_inversion[block] =
                _local_inversion[block][local_index(block, 0, length)];

            std::vector<int> sorted;
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

    void build_boundary_counts() {
        _boundary_less.assign(
            _block_count + 1,
            std::vector<int>(_value_count + 1, 0)
        );
        std::vector<int> frequency(_value_count, 0);
        for (int block = 0; block <= _block_count; ++block) {
            int boundary = std::min(_n, block_start(block));
            if (block != 0) {
                int previous = block_start(block - 1);
                for (int index = previous; index < boundary; ++index) {
                    frequency[_rank[index]]++;
                }
            }
            int count = 0;
            for (int rank = 0; rank < _value_count; ++rank) {
                _boundary_less[block][rank] = count;
                count += frequency[rank];
            }
            _boundary_less[block][_value_count] = count;
        }
    }

    void build_full_block_inversions() {
        _full_block_inversion.assign(
            _block_count + 1,
            std::vector<long long>(_block_count + 1, 0)
        );
        for (int first = 0; first < _block_count; ++first) {
            long long inversions = 0;
            for (int last = first; last < _block_count; ++last) {
                int prior_length = block_start(last) - block_start(first);
                for (
                    int index = block_start(last);
                    index < block_end(last);
                    ++index
                ) {
                    int less_equal =
                        count_less_blocks(first, last, _rank[index] + 1);
                    inversions += prior_length - less_equal;
                }
                inversions += _block_inversion[last];
                _full_block_inversion[first][last + 1] = inversions;
            }
        }
    }

   public:
    RangeInversionCount()
        : _n(0), _block_size(1), _block_count(0), _value_count(0) {}

    explicit RangeInversionCount(const std::vector<T>& values)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _value_count(0) {
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
        _value_count = int(sorted.size());
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
        build_boundary_counts();
        build_full_block_inversions();
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
            return local_query(left, right);
        }

        int first_full = (left + _block_size - 1) / _block_size;
        int last_full = right / _block_size;
        int left_end = std::min(right, block_start(first_full));
        int right_start = std::max(left_end, block_start(last_full));

        long long result = _full_block_inversion[first_full][last_full];
        result += local_query(left, left_end);
        result += local_query(right_start, right);

        for (int index = left; index < left_end; ++index) {
            result += count_less_blocks(first_full, last_full, _rank[index]);
        }

        for (int index = right_start; index < right; ++index) {
            result += count_greater_blocks(first_full, last_full, _rank[index]);
        }

        if (left < left_end && right_start < right) {
            result += cross_inversions(
                _sorted_suffix[left],
                _sorted_prefix[right]
            );
        }
        return result;
    }

    long long inversion_count(int left, int right) const {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_RANGE_INVERSION_COUNT_HPP
