#ifndef M1UNE_SHIFTED_ARRAY_HPP
#define M1UNE_SHIFTED_ARRAY_HPP 1

#include <stdexcept>
#include <vector>

namespace m1une {
namespace utilities {

// `bool` is not supported; use `char` for boolean-like arrays.
template <typename T>
struct ShiftedArray {
   private:
    long long _offset;
    long long _step;
    long long _size;
    std::vector<T> _data;

    static long long checked_size(long long L, long long R, long long step) {
        if (step <= 0) {
            throw std::invalid_argument("Step must be positive");
        }
        if (L > R) {
            throw std::invalid_argument("Left bound must be less than or equal to right bound");
        }
        return (R - L) / step + 1;
    }

    long long to_index(long long i) const {
        if (i < _offset) {
            throw std::out_of_range("Index out of range");
        }
        long long diff = i - _offset;
        if (diff % _step != 0) {
            throw std::out_of_range("Index is not aligned to the step");
        }
        long long index = diff / _step;
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return index;
    }

   public:
    // Creates an array on the closed interval [L, R] using the given step.
    ShiftedArray(long long L, long long R, T init_value = T(), long long step = 1)
        : _offset(L), _step(step), _size(checked_size(L, R, step)), _data(_size, init_value) {}

    T& operator[](long long i) {
        return _data[to_index(i)];
    }

    const T& operator[](long long i) const {
        return _data[to_index(i)];
    }

    long long index(long long i) const {
        return to_index(i);
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_SHIFTED_ARRAY_HPP
