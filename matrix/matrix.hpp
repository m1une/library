#ifndef M1UNE_MATRIX_MATRIX_HPP
#define M1UNE_MATRIX_MATRIX_HPP 1

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace m1une {
namespace matrix {

template <class T>
class Matrix {
   private:
    int _rows;
    int _cols;
    std::vector<T> _data;

    static std::size_t storage_size(int rows, int cols) {
        assert(rows >= 0);
        assert(cols >= 0);
        return std::size_t(rows) * std::size_t(cols);
    }

   public:
    using value_type = T;

    Matrix() : _rows(0), _cols(0) {}

    Matrix(int rows, int cols, const T& value = T())
        : _rows(rows), _cols(cols), _data(storage_size(rows, cols), value) {}

    Matrix(int rows, int cols, std::vector<T> values)
        : _rows(rows), _cols(cols), _data(std::move(values)) {
        assert(rows >= 0);
        assert(cols >= 0);
        assert(_data.size() == std::size_t(rows) * std::size_t(cols));
    }

    explicit Matrix(const std::vector<std::vector<T>>& values)
        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),
          _data(storage_size(_rows, _cols)) {
        for (int row = 0; row < _rows; row++) {
            assert(int(values[std::size_t(row)].size()) == _cols);
            for (int col = 0; col < _cols; col++) {
                (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];
            }
        }
    }

    int rows() const {
        return _rows;
    }

    int cols() const {
        return _cols;
    }

    bool empty() const {
        return _rows == 0 || _cols == 0;
    }

    std::vector<T>& data() {
        return _data;
    }

    const std::vector<T>& data() const {
        return _data;
    }

    T* operator[](int row) {
        assert(0 <= row && row < _rows);
        return _data.data() + std::size_t(row) * std::size_t(_cols);
    }

    const T* operator[](int row) const {
        assert(0 <= row && row < _rows);
        return _data.data() + std::size_t(row) * std::size_t(_cols);
    }

    T& operator()(int row, int col) {
        assert(0 <= col && col < _cols);
        return (*this)[row][col];
    }

    const T& operator()(int row, int col) const {
        assert(0 <= col && col < _cols);
        return (*this)[row][col];
    }

    static Matrix identity(int size) {
        assert(size >= 0);
        Matrix result(size, size);
        for (int i = 0; i < size; i++) result[i][i] = T(1);
        return result;
    }

    Matrix transposed() const {
        Matrix result(_cols, _rows);
        for (int row = 0; row < _rows; row++) {
            for (int col = 0; col < _cols; col++) {
                result[col][row] = (*this)[row][col];
            }
        }
        return result;
    }

    void swap_rows(int first, int second) {
        assert(0 <= first && first < _rows);
        assert(0 <= second && second < _rows);
        if (first == second) return;
        for (int col = 0; col < _cols; col++) {
            std::swap((*this)[first][col], (*this)[second][col]);
        }
    }

    Matrix& operator+=(const Matrix& rhs) {
        assert(_rows == rhs._rows && _cols == rhs._cols);
        for (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];
        return *this;
    }

    Matrix& operator-=(const Matrix& rhs) {
        assert(_rows == rhs._rows && _cols == rhs._cols);
        for (std::size_t i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];
        return *this;
    }

    Matrix& operator*=(const T& scalar) {
        for (T& value : _data) value *= scalar;
        return *this;
    }

    Matrix& operator/=(const T& scalar) {
        for (T& value : _data) value /= scalar;
        return *this;
    }

    Matrix& operator*=(const Matrix& rhs) {
        return *this = *this * rhs;
    }

    Matrix operator+() const {
        return *this;
    }

    Matrix operator-() const {
        Matrix result = *this;
        for (T& value : result._data) value = T() - value;
        return result;
    }

    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
        return lhs += rhs;
    }

    friend Matrix operator-(Matrix lhs, const Matrix& rhs) {
        return lhs -= rhs;
    }

    friend Matrix operator*(Matrix lhs, const T& rhs) {
        return lhs *= rhs;
    }

    friend Matrix operator*(const T& lhs, Matrix rhs) {
        return rhs *= lhs;
    }

    friend Matrix operator/(Matrix lhs, const T& rhs) {
        return lhs /= rhs;
    }

    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        assert(lhs._cols == rhs._rows);
        Matrix result(lhs._rows, rhs._cols);
        for (int row = 0; row < lhs._rows; row++) {
            T* output = result[row];
            for (int middle = 0; middle < lhs._cols; middle++) {
                const T coefficient = lhs[row][middle];
                if (coefficient == T()) continue;
                const T* input = rhs[middle];
                for (int col = 0; col < rhs._cols; col++) {
                    output[col] += coefficient * input[col];
                }
            }
        }
        return result;
    }

    friend std::vector<T> operator*(const Matrix& lhs, const std::vector<T>& rhs) {
        assert(lhs._cols == int(rhs.size()));
        std::vector<T> result(std::size_t(lhs._rows));
        for (int row = 0; row < lhs._rows; row++) {
            T value = T();
            for (int col = 0; col < lhs._cols; col++) {
                value += lhs[row][col] * rhs[std::size_t(col)];
            }
            result[std::size_t(row)] = value;
        }
        return result;
    }

    friend std::vector<T> operator*(const std::vector<T>& lhs, const Matrix& rhs) {
        assert(int(lhs.size()) == rhs._rows);
        std::vector<T> result(std::size_t(rhs._cols));
        for (int row = 0; row < rhs._rows; row++) {
            if (lhs[std::size_t(row)] == T()) continue;
            for (int col = 0; col < rhs._cols; col++) {
                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];
            }
        }
        return result;
    }

    bool operator==(const Matrix& rhs) const {
        return _rows == rhs._rows && _cols == rhs._cols && _data == rhs._data;
    }

    bool operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }

    Matrix pow(std::uint64_t exponent) const {
        assert(_rows == _cols);
        Matrix result = identity(_rows);
        Matrix base = *this;
        while (exponent > 0) {
            if (exponent & 1) result *= base;
            exponent >>= 1;
            if (exponent > 0) base *= base;
        }
        return result;
    }
};

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_MATRIX_HPP
