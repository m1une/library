#ifndef M1UNE_SHIFTED_ARRAY_HPP
#define M1UNE_SHIFTED_ARRAY_HPP 1

#include <stdexcept>
#include <vector>

namespace m1une {
// bool is not allowed
// if you want to use bool, use char instead
template <typename T>
struct shifted_array {
   private:
    long long _offset;
    long long _step;
    int _size;
    std::vector<T> _data;

   public:
    // make an array with indices from L to R (including both L and R)
    // [L, R] (closed interval)
    shifted_array(long long L, long long R, T init_value = T(),
                  long long step = 1)
        : _offset(L),
          _step(step),
          _size((R - L) / step + 1),
          _data(_size, init_value) {
        if (step <= 0) {
            throw std::invalid_argument("Step must be positive");
        }
        if (L > R) {
            throw std::invalid_argument(
                "Left bound must be less than or equal to right bound");
        }
    }
    T &operator[](long long i) {
        int index = (i - _offset) / _step;
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    };
    const T &operator[](long long i) const {
        int index = (i - _offset) / _step;
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    };
    long long index(long long i) const {
        int index = (i - _offset) / _step;
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return index;
    }
};

}  // namespace m1une

#endif  // M1UNE_SHIFTED_ARRAY_HPP
