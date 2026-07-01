---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: matrix/all.hpp
    title: Matrix Bundle
  - icon: ':heavy_check_mark:'
    path: matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: matrix/matrix.hpp
    title: Dense Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/matrix/matrix.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#include <cstdint>\n#include <iostream>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matrix/all.hpp\"\n\n\n\n#line 1 \"matrix/linear_algebra.hpp\"\
    \n\n\n\n#include <optional>\n#line 6 \"matrix/linear_algebra.hpp\"\n#include <vector>\n\
    \n#line 1 \"matrix/matrix.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #line 9 \"matrix/matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\ntemplate\
    \ <class T>\nclass Matrix {\n   private:\n    int _rows;\n    int _cols;\n   \
    \ std::vector<T> _data;\n\n    static std::size_t storage_size(int rows, int cols)\
    \ {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        return std::size_t(rows)\
    \ * std::size_t(cols);\n    }\n\n   public:\n    using value_type = T;\n\n   \
    \ Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int rows, int cols, const T&\
    \ value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows, cols),\
    \ value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n       \
    \ : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        assert(_data.size() == std::size_t(rows)\
    \ * std::size_t(cols));\n    }\n\n    explicit Matrix(const std::vector<std::vector<T>>&\
    \ values)\n        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),\n\
    \          _data(storage_size(_rows, _cols)) {\n        for (int row = 0; row\
    \ < _rows; row++) {\n            assert(int(values[std::size_t(row)].size()) ==\
    \ _cols);\n            for (int col = 0; col < _cols; col++) {\n             \
    \   (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n        \
    \    }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n  \
    \  }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"matrix/linear_algebra.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nconstexpr T default_epsilon()\
    \ {\n    if constexpr (std::is_floating_point_v<T>) {\n        return T(1e-10);\n\
    \    } else {\n        return T();\n    }\n}\n\nnamespace detail {\n\ntemplate\
    \ <class T>\nT matrix_abs(T value) {\n    return value < T() ? T() - value : value;\n\
    }\n\ntemplate <class T>\nbool is_zero(const T& value, const T& eps) {\n    if\
    \ constexpr (std::is_floating_point_v<T>) {\n        return matrix_abs(value)\
    \ <= eps;\n    } else {\n        (void)eps;\n        return value == T();\n  \
    \  }\n}\n\ntemplate <class T>\nint choose_pivot(const Matrix<T>& matrix, int first_row,\
    \ int col, const T& eps) {\n    int pivot = -1;\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (int row = first_row; row < matrix.rows(); row++) {\n       \
    \     if (is_zero(matrix[row][col], eps)) continue;\n            if (pivot ==\
    \ -1 || matrix_abs(matrix[pivot][col]) < matrix_abs(matrix[row][col])) {\n   \
    \             pivot = row;\n            }\n        }\n    } else {\n        for\
    \ (int row = first_row; row < matrix.rows(); row++) {\n            if (!is_zero(matrix[row][col],\
    \ eps)) {\n                pivot = row;\n                break;\n            }\n\
    \        }\n    }\n    return pivot;\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ row_reduce(Matrix<T>& matrix, int pivot_col_limit, const T& eps,\n         \
    \                   bool reduced) {\n    std::vector<int> pivot_columns;\n   \
    \ int pivot_row = 0;\n    for (int col = 0; col < pivot_col_limit && pivot_row\
    \ < matrix.rows(); col++) {\n        int pivot = choose_pivot(matrix, pivot_row,\
    \ col, eps);\n        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row,\
    \ pivot);\n\n        const T pivot_value = matrix[pivot_row][col];\n        if\
    \ (reduced) {\n            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j]\
    \ /= pivot_value;\n        }\n\n        const int first_row = reduced ? 0 : pivot_row\
    \ + 1;\n        for (int row = first_row; row < matrix.rows(); row++) {\n    \
    \        if (row == pivot_row || is_zero(matrix[row][col], eps)) continue;\n \
    \           T factor = matrix[row][col];\n            if (!reduced) factor /=\
    \ pivot_value;\n            matrix[row][col] = T();\n            for (int j =\
    \ col + 1; j < matrix.cols(); j++) {\n                matrix[row][j] -= factor\
    \ * matrix[pivot_row][j];\n            }\n        }\n\n        pivot_columns.push_back(col);\n\
    \        pivot_row++;\n    }\n\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (T& value : matrix.data()) {\n            if (is_zero(value,\
    \ eps)) value = T();\n        }\n    }\n    return pivot_columns;\n}\n\n}  //\
    \ namespace detail\n\ntemplate <class T>\nstruct RowReduction {\n    Matrix<T>\
    \ matrix;\n    std::vector<int> pivot_columns;\n\n    int rank() const {\n   \
    \     return int(pivot_columns.size());\n    }\n};\n\ntemplate <class T>\nRowReduction<T>\
    \ reduced_row_echelon_form(Matrix<T> matrix,\n                               \
    \          T eps = default_epsilon<T>()) {\n    RowReduction<T> result;\n    result.pivot_columns\
    \ = detail::row_reduce(matrix, matrix.cols(), eps, true);\n    result.matrix =\
    \ std::move(matrix);\n    return result;\n}\n\ntemplate <class T>\nint matrix_rank(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    return int(detail::row_reduce(matrix,\
    \ matrix.cols(), eps, false).size());\n}\n\ntemplate <class T>\nT determinant(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    assert(matrix.rows() == matrix.cols());\n\
    \    const int size = matrix.rows();\n    T result = T(1);\n    bool negate =\
    \ false;\n\n    for (int col = 0; col < size; col++) {\n        int pivot = detail::choose_pivot(matrix,\
    \ col, col, eps);\n        if (pivot == -1) return T();\n        if (pivot !=\
    \ col) {\n            matrix.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        const T pivot_value = matrix[col][col];\n        result\
    \ *= pivot_value;\n        for (int row = col + 1; row < size; row++) {\n    \
    \        if (detail::is_zero(matrix[row][col], eps)) continue;\n            const\
    \ T factor = matrix[row][col] / pivot_value;\n            matrix[row][col] = T();\n\
    \            for (int j = col + 1; j < size; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[col][j];\n            }\n        }\n    }\n    return negate\
    \ ? T() - result : result;\n}\n\ntemplate <class T>\nstd::optional<Matrix<T>>\
    \ inverse(const Matrix<T>& matrix,\n                                 T eps = default_epsilon<T>())\
    \ {\n    assert(matrix.rows() == matrix.cols());\n    const int size = matrix.rows();\n\
    \    Matrix<T> augmented(size, size * 2);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) {\n            augmented[row][col]\
    \ = matrix[row][col];\n        }\n        augmented[row][size + row] = T(1);\n\
    \    }\n\n    const std::vector<int> pivots = detail::row_reduce(augmented, size,\
    \ eps, true);\n    if (int(pivots.size()) != size) return std::nullopt;\n\n  \
    \  Matrix<T> result(size, size);\n    for (int row = 0; row < size; row++) {\n\
    \        for (int col = 0; col < size; col++) {\n            result[row][col]\
    \ = augmented[row][size + col];\n        }\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nstruct LinearSystemResult {\n    bool consistent = false;\n    std::vector<T>\
    \ particular_solution;\n    std::vector<std::vector<T>> nullspace_basis;\n   \
    \ std::vector<int> pivot_columns;\n\n    int rank() const {\n        return int(pivot_columns.size());\n\
    \    }\n\n    int nullity() const {\n        return consistent ? int(nullspace_basis.size())\
    \ : 0;\n    }\n\n    bool has_unique_solution() const {\n        return consistent\
    \ && nullspace_basis.empty();\n    }\n};\n\ntemplate <class T>\nLinearSystemResult<T>\
    \ solve_linear_system(const Matrix<T>& coefficients,\n                       \
    \                   const std::vector<T>& constants,\n                       \
    \                   T eps = default_epsilon<T>()) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    Matrix<T> augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            augmented[row][col]\
    \ = coefficients[row][col];\n        }\n        augmented[row][variable_count]\
    \ = constants[std::size_t(row)];\n    }\n\n    LinearSystemResult<T> result;\n\
    \    result.pivot_columns =\n        detail::row_reduce(augmented, variable_count,\
    \ eps, true);\n\n    for (int row = result.rank(); row < equation_count; row++)\
    \ {\n        bool zero_left = true;\n        for (int col = 0; col < variable_count;\
    \ col++) {\n            if (!detail::is_zero(augmented[row][col], eps)) {\n  \
    \              zero_left = false;\n                break;\n            }\n   \
    \     }\n        if (zero_left && !detail::is_zero(augmented[row][variable_count],\
    \ eps)) {\n            return result;\n        }\n    }\n\n    result.consistent\
    \ = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ T());\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] = augmented[row][variable_count];\n\
    \    }\n\n    for (int free_col = 0; free_col < variable_count; free_col++) {\n\
    \        if (is_pivot[std::size_t(free_col)]) continue;\n        std::vector<T>\
    \ direction(static_cast<std::size_t>(variable_count));\n        direction[std::size_t(free_col)]\
    \ = T(1);\n        for (int row = 0; row < result.rank(); row++) {\n         \
    \   const int pivot_col = result.pivot_columns[std::size_t(row)];\n          \
    \  direction[std::size_t(pivot_col)] = T() - augmented[row][free_col];\n     \
    \   }\n        result.nullspace_basis.push_back(std::move(direction));\n    }\n\
    \    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n\
    #line 6 \"matrix/all.hpp\"\n\n\n#line 5 \"verify/matrix/matrix.test.cpp\"\n\n\
    #line 7 \"verify/matrix/matrix.test.cpp\"\n#include <cmath>\n#line 11 \"verify/matrix/matrix.test.cpp\"\
    \n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\nusing m1une::matrix::Matrix;\n\
    \ntemplate <class T>\nvoid assert_product_is_identity(const Matrix<T>& first,\
    \ const Matrix<T>& second) {\n    assert(first.rows() == first.cols());\n    assert(first\
    \ * second == Matrix<T>::identity(first.rows()));\n}\n\nvoid test_construction_and_arithmetic()\
    \ {\n    Matrix<long long> first(2, 3);\n    long long value = 1;\n    for (int\
    \ row = 0; row < first.rows(); row++) {\n        for (int col = 0; col < first.cols();\
    \ col++) first[row][col] = value++;\n    }\n\n    Matrix<long long> second(3,\
    \ 2);\n    second[0][0] = 7;\n    second[0][1] = 8;\n    second[1][0] = 9;\n \
    \   second[1][1] = 10;\n    second[2][0] = 11;\n    second[2][1] = 12;\n\n   \
    \ Matrix<long long> product = first * second;\n    assert(product.rows() == 2);\n\
    \    assert(product.cols() == 2);\n    assert(product[0][0] == 58);\n    assert(product[0][1]\
    \ == 64);\n    assert(product[1][0] == 139);\n    assert(product[1][1] == 154);\n\
    \n    Matrix<long long> transposed = first.transposed();\n    assert(transposed.rows()\
    \ == 3);\n    assert(transposed.cols() == 2);\n    assert(transposed[2][1] ==\
    \ 6);\n\n    Matrix<long long> sum = first + first;\n    assert(sum[1][2] == 12);\n\
    \    assert((sum - first) == first);\n    assert((first * 3LL)[1][1] == 15);\n\
    \n    std::vector<long long> column = {1, 2, 3};\n    std::vector<long long> column_product\
    \ = first * column;\n    assert(column_product == std::vector<long long>({14,\
    \ 32}));\n    std::vector<long long> row = {2, -1};\n    std::vector<long long>\
    \ row_product = row * first;\n    assert(row_product == std::vector<long long>({-2,\
    \ -1, 0}));\n\n    Matrix<long long> flat(2, 2, std::vector<long long>({1, 2,\
    \ 3, 4}));\n    assert(flat[1][0] == 3);\n    Matrix<long long> zero_inner_left(2,\
    \ 0);\n    Matrix<long long> zero_inner_right(0, 3);\n    Matrix<long long> zero_product\
    \ = zero_inner_left * zero_inner_right;\n    assert(zero_product == Matrix<long\
    \ long>(2, 3));\n}\n\nvoid test_power() {\n    Matrix<mint> fibonacci(2, 2);\n\
    \    fibonacci[0][0] = 1;\n    fibonacci[0][1] = 1;\n    fibonacci[1][0] = 1;\n\
    \    assert(fibonacci.pow(0) == Matrix<mint>::identity(2));\n    Matrix<mint>\
    \ tenth = fibonacci.pow(10);\n    assert(tenth[0][1] == mint(55));\n    assert(tenth[0][0]\
    \ == mint(89));\n}\n\nvoid test_row_reduction() {\n    Matrix<mint> matrix(3,\
    \ 4);\n    matrix[0][0] = 1;\n    matrix[0][1] = 2;\n    matrix[0][2] = 1;\n \
    \   matrix[0][3] = 4;\n    matrix[1][0] = 2;\n    matrix[1][1] = 4;\n    matrix[1][2]\
    \ = 2;\n    matrix[1][3] = 8;\n    matrix[2][1] = 1;\n    matrix[2][2] = 1;\n\
    \    matrix[2][3] = 3;\n\n    assert(m1une::matrix::matrix_rank(matrix) == 2);\n\
    \    auto reduced = m1une::matrix::reduced_row_echelon_form(matrix);\n    assert(reduced.rank()\
    \ == 2);\n    assert(reduced.pivot_columns == std::vector<int>({0, 1}));\n   \
    \ assert(reduced.matrix[0][0] == mint(1));\n    assert(reduced.matrix[0][1] ==\
    \ mint(0));\n    assert(reduced.matrix[1][0] == mint(0));\n    assert(reduced.matrix[1][1]\
    \ == mint(1));\n}\n\nvoid test_determinant_and_inverse() {\n    Matrix<mint> matrix(3,\
    \ 3);\n    matrix[0][0] = 2;\n    matrix[0][1] = 1;\n    matrix[0][2] = 3;\n \
    \   matrix[1][0] = 1;\n    matrix[1][2] = 4;\n    matrix[2][0] = 5;\n    matrix[2][1]\
    \ = 2;\n    matrix[2][2] = 1;\n    assert(m1une::matrix::determinant(matrix) ==\
    \ mint(9));\n\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    assert_product_is_identity(matrix, *inv);\n\n    Matrix<mint> singular(2,\
    \ 2);\n    singular[0][0] = 1;\n    singular[0][1] = 2;\n    singular[1][0] =\
    \ 2;\n    singular[1][1] = 4;\n    assert(m1une::matrix::determinant(singular)\
    \ == mint(0));\n    assert(!m1une::matrix::inverse(singular).has_value());\n \
    \   assert(m1une::matrix::determinant(Matrix<mint>(0, 0)) == mint(1));\n}\n\n\
    void test_linear_systems() {\n    Matrix<mint> unique(2, 2);\n    unique[0][0]\
    \ = 2;\n    unique[0][1] = 1;\n    unique[1][0] = 1;\n    unique[1][1] = 3;\n\
    \    auto solved = m1une::matrix::solve_linear_system(unique, std::vector<mint>({5,\
    \ 7}));\n    assert(solved.consistent);\n    assert(solved.has_unique_solution());\n\
    \    assert(unique * solved.particular_solution == std::vector<mint>({5, 7}));\n\
    \n    Matrix<mint> underdetermined(2, 3);\n    underdetermined[0][0] = 1;\n  \
    \  underdetermined[0][1] = 1;\n    underdetermined[0][2] = 1;\n    underdetermined[1][0]\
    \ = 2;\n    underdetermined[1][1] = 2;\n    underdetermined[1][2] = 2;\n    auto\
    \ many =\n        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 6}));\n    assert(many.consistent);\n    assert(many.rank() == 1);\n    assert(many.nullity()\
    \ == 2);\n    assert(underdetermined * many.particular_solution == std::vector<mint>({3,\
    \ 6}));\n    for (const auto& direction : many.nullspace_basis) {\n        assert(underdetermined\
    \ * direction == std::vector<mint>({0, 0}));\n    }\n\n    auto none =\n     \
    \   m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 7}));\n    assert(!none.consistent);\n\n    Matrix<mint> no_equations(0, 3);\n\
    \    auto unconstrained =\n        m1une::matrix::solve_linear_system(no_equations,\
    \ std::vector<mint>());\n    assert(unconstrained.consistent);\n    assert(unconstrained.rank()\
    \ == 0);\n    assert(unconstrained.nullity() == 3);\n\n    Matrix<mint> no_variables(2,\
    \ 0);\n    auto empty_solution =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 0}));\n    assert(empty_solution.has_unique_solution());\n\
    \    auto impossible =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 1}));\n    assert(!impossible.consistent);\n}\n\nvoid\
    \ test_floating_point() {\n    Matrix<double> matrix(2, 2);\n    matrix[0][0]\
    \ = 1e-14;\n    matrix[0][1] = 1;\n    matrix[1][0] = 1;\n    matrix[1][1] = 1;\n\
    \    assert(m1une::matrix::matrix_rank(matrix) == 2);\n    assert(std::fabs(m1une::matrix::determinant(matrix)\
    \ + 1.0) < 1e-9);\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    Matrix<double> product = matrix * *inv;\n    for (int row = 0; row < 2; row++)\
    \ {\n        for (int col = 0; col < 2; col++) {\n            const double expected\
    \ = row == col ? 1.0 : 0.0;\n            assert(std::fabs(product[row][col] -\
    \ expected) < 1e-9);\n        }\n    }\n}\n\nvoid test_randomized_exact() {\n\
    \    std::uint64_t state = 0x81a5b4c3d2e1f097ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        const\
    \ int size = 1 + int(random() % 6);\n        Matrix<mint> lower = Matrix<mint>::identity(size);\n\
    \        Matrix<mint> upper = Matrix<mint>::identity(size);\n        for (int\
    \ row = 0; row < size; row++) {\n            lower[row][row] = mint(1 + int(random()\
    \ % 100));\n            upper[row][row] = mint(1 + int(random() % 100));\n   \
    \         for (int col = 0; col < row; col++) {\n                lower[row][col]\
    \ = mint(int(random() % 21) - 10);\n            }\n            for (int col =\
    \ row + 1; col < size; col++) {\n                upper[row][col] = mint(int(random()\
    \ % 21) - 10);\n            }\n        }\n        Matrix<mint> matrix = lower\
    \ * upper;\n        auto inv = m1une::matrix::inverse(matrix);\n        assert(inv.has_value());\n\
    \        assert_product_is_identity(matrix, *inv);\n        assert(m1une::matrix::matrix_rank(matrix)\
    \ == size);\n        mint expected_determinant = 1;\n        for (int i = 0; i\
    \ < size; i++) {\n            expected_determinant *= lower[i][i] * upper[i][i];\n\
    \        }\n        assert(m1une::matrix::determinant(matrix) == expected_determinant);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_construction_and_arithmetic();\n\
    \    test_power();\n    test_row_reduction();\n    test_determinant_and_inverse();\n\
    \    test_linear_systems();\n    test_floating_point();\n    test_randomized_exact();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/modint.hpp\"\n#include \"../../matrix/all.hpp\"\n\n#include <cassert>\n\
    #include <cmath>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \nnamespace {\n\nusing mint = m1une::math::modint998244353;\nusing m1une::matrix::Matrix;\n\
    \ntemplate <class T>\nvoid assert_product_is_identity(const Matrix<T>& first,\
    \ const Matrix<T>& second) {\n    assert(first.rows() == first.cols());\n    assert(first\
    \ * second == Matrix<T>::identity(first.rows()));\n}\n\nvoid test_construction_and_arithmetic()\
    \ {\n    Matrix<long long> first(2, 3);\n    long long value = 1;\n    for (int\
    \ row = 0; row < first.rows(); row++) {\n        for (int col = 0; col < first.cols();\
    \ col++) first[row][col] = value++;\n    }\n\n    Matrix<long long> second(3,\
    \ 2);\n    second[0][0] = 7;\n    second[0][1] = 8;\n    second[1][0] = 9;\n \
    \   second[1][1] = 10;\n    second[2][0] = 11;\n    second[2][1] = 12;\n\n   \
    \ Matrix<long long> product = first * second;\n    assert(product.rows() == 2);\n\
    \    assert(product.cols() == 2);\n    assert(product[0][0] == 58);\n    assert(product[0][1]\
    \ == 64);\n    assert(product[1][0] == 139);\n    assert(product[1][1] == 154);\n\
    \n    Matrix<long long> transposed = first.transposed();\n    assert(transposed.rows()\
    \ == 3);\n    assert(transposed.cols() == 2);\n    assert(transposed[2][1] ==\
    \ 6);\n\n    Matrix<long long> sum = first + first;\n    assert(sum[1][2] == 12);\n\
    \    assert((sum - first) == first);\n    assert((first * 3LL)[1][1] == 15);\n\
    \n    std::vector<long long> column = {1, 2, 3};\n    std::vector<long long> column_product\
    \ = first * column;\n    assert(column_product == std::vector<long long>({14,\
    \ 32}));\n    std::vector<long long> row = {2, -1};\n    std::vector<long long>\
    \ row_product = row * first;\n    assert(row_product == std::vector<long long>({-2,\
    \ -1, 0}));\n\n    Matrix<long long> flat(2, 2, std::vector<long long>({1, 2,\
    \ 3, 4}));\n    assert(flat[1][0] == 3);\n    Matrix<long long> zero_inner_left(2,\
    \ 0);\n    Matrix<long long> zero_inner_right(0, 3);\n    Matrix<long long> zero_product\
    \ = zero_inner_left * zero_inner_right;\n    assert(zero_product == Matrix<long\
    \ long>(2, 3));\n}\n\nvoid test_power() {\n    Matrix<mint> fibonacci(2, 2);\n\
    \    fibonacci[0][0] = 1;\n    fibonacci[0][1] = 1;\n    fibonacci[1][0] = 1;\n\
    \    assert(fibonacci.pow(0) == Matrix<mint>::identity(2));\n    Matrix<mint>\
    \ tenth = fibonacci.pow(10);\n    assert(tenth[0][1] == mint(55));\n    assert(tenth[0][0]\
    \ == mint(89));\n}\n\nvoid test_row_reduction() {\n    Matrix<mint> matrix(3,\
    \ 4);\n    matrix[0][0] = 1;\n    matrix[0][1] = 2;\n    matrix[0][2] = 1;\n \
    \   matrix[0][3] = 4;\n    matrix[1][0] = 2;\n    matrix[1][1] = 4;\n    matrix[1][2]\
    \ = 2;\n    matrix[1][3] = 8;\n    matrix[2][1] = 1;\n    matrix[2][2] = 1;\n\
    \    matrix[2][3] = 3;\n\n    assert(m1une::matrix::matrix_rank(matrix) == 2);\n\
    \    auto reduced = m1une::matrix::reduced_row_echelon_form(matrix);\n    assert(reduced.rank()\
    \ == 2);\n    assert(reduced.pivot_columns == std::vector<int>({0, 1}));\n   \
    \ assert(reduced.matrix[0][0] == mint(1));\n    assert(reduced.matrix[0][1] ==\
    \ mint(0));\n    assert(reduced.matrix[1][0] == mint(0));\n    assert(reduced.matrix[1][1]\
    \ == mint(1));\n}\n\nvoid test_determinant_and_inverse() {\n    Matrix<mint> matrix(3,\
    \ 3);\n    matrix[0][0] = 2;\n    matrix[0][1] = 1;\n    matrix[0][2] = 3;\n \
    \   matrix[1][0] = 1;\n    matrix[1][2] = 4;\n    matrix[2][0] = 5;\n    matrix[2][1]\
    \ = 2;\n    matrix[2][2] = 1;\n    assert(m1une::matrix::determinant(matrix) ==\
    \ mint(9));\n\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    assert_product_is_identity(matrix, *inv);\n\n    Matrix<mint> singular(2,\
    \ 2);\n    singular[0][0] = 1;\n    singular[0][1] = 2;\n    singular[1][0] =\
    \ 2;\n    singular[1][1] = 4;\n    assert(m1une::matrix::determinant(singular)\
    \ == mint(0));\n    assert(!m1une::matrix::inverse(singular).has_value());\n \
    \   assert(m1une::matrix::determinant(Matrix<mint>(0, 0)) == mint(1));\n}\n\n\
    void test_linear_systems() {\n    Matrix<mint> unique(2, 2);\n    unique[0][0]\
    \ = 2;\n    unique[0][1] = 1;\n    unique[1][0] = 1;\n    unique[1][1] = 3;\n\
    \    auto solved = m1une::matrix::solve_linear_system(unique, std::vector<mint>({5,\
    \ 7}));\n    assert(solved.consistent);\n    assert(solved.has_unique_solution());\n\
    \    assert(unique * solved.particular_solution == std::vector<mint>({5, 7}));\n\
    \n    Matrix<mint> underdetermined(2, 3);\n    underdetermined[0][0] = 1;\n  \
    \  underdetermined[0][1] = 1;\n    underdetermined[0][2] = 1;\n    underdetermined[1][0]\
    \ = 2;\n    underdetermined[1][1] = 2;\n    underdetermined[1][2] = 2;\n    auto\
    \ many =\n        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 6}));\n    assert(many.consistent);\n    assert(many.rank() == 1);\n    assert(many.nullity()\
    \ == 2);\n    assert(underdetermined * many.particular_solution == std::vector<mint>({3,\
    \ 6}));\n    for (const auto& direction : many.nullspace_basis) {\n        assert(underdetermined\
    \ * direction == std::vector<mint>({0, 0}));\n    }\n\n    auto none =\n     \
    \   m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 7}));\n    assert(!none.consistent);\n\n    Matrix<mint> no_equations(0, 3);\n\
    \    auto unconstrained =\n        m1une::matrix::solve_linear_system(no_equations,\
    \ std::vector<mint>());\n    assert(unconstrained.consistent);\n    assert(unconstrained.rank()\
    \ == 0);\n    assert(unconstrained.nullity() == 3);\n\n    Matrix<mint> no_variables(2,\
    \ 0);\n    auto empty_solution =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 0}));\n    assert(empty_solution.has_unique_solution());\n\
    \    auto impossible =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 1}));\n    assert(!impossible.consistent);\n}\n\nvoid\
    \ test_floating_point() {\n    Matrix<double> matrix(2, 2);\n    matrix[0][0]\
    \ = 1e-14;\n    matrix[0][1] = 1;\n    matrix[1][0] = 1;\n    matrix[1][1] = 1;\n\
    \    assert(m1une::matrix::matrix_rank(matrix) == 2);\n    assert(std::fabs(m1une::matrix::determinant(matrix)\
    \ + 1.0) < 1e-9);\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    Matrix<double> product = matrix * *inv;\n    for (int row = 0; row < 2; row++)\
    \ {\n        for (int col = 0; col < 2; col++) {\n            const double expected\
    \ = row == col ? 1.0 : 0.0;\n            assert(std::fabs(product[row][col] -\
    \ expected) < 1e-9);\n        }\n    }\n}\n\nvoid test_randomized_exact() {\n\
    \    std::uint64_t state = 0x81a5b4c3d2e1f097ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        const\
    \ int size = 1 + int(random() % 6);\n        Matrix<mint> lower = Matrix<mint>::identity(size);\n\
    \        Matrix<mint> upper = Matrix<mint>::identity(size);\n        for (int\
    \ row = 0; row < size; row++) {\n            lower[row][row] = mint(1 + int(random()\
    \ % 100));\n            upper[row][row] = mint(1 + int(random() % 100));\n   \
    \         for (int col = 0; col < row; col++) {\n                lower[row][col]\
    \ = mint(int(random() % 21) - 10);\n            }\n            for (int col =\
    \ row + 1; col < size; col++) {\n                upper[row][col] = mint(int(random()\
    \ % 21) - 10);\n            }\n        }\n        Matrix<mint> matrix = lower\
    \ * upper;\n        auto inv = m1une::matrix::inverse(matrix);\n        assert(inv.has_value());\n\
    \        assert_product_is_identity(matrix, *inv);\n        assert(m1une::matrix::matrix_rank(matrix)\
    \ == size);\n        mint expected_determinant = 1;\n        for (int i = 0; i\
    \ < size; i++) {\n            expected_determinant *= lower[i][i] * upper[i][i];\n\
    \        }\n        assert(m1une::matrix::determinant(matrix) == expected_determinant);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_construction_and_arithmetic();\n\
    \    test_power();\n    test_row_reduction();\n    test_determinant_and_inverse();\n\
    \    test_linear_systems();\n    test_floating_point();\n    test_randomized_exact();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/modint.hpp
  - matrix/all.hpp
  - matrix/linear_algebra.hpp
  - matrix/matrix.hpp
  isVerificationFile: true
  path: verify/matrix/matrix.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matrix/matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/matrix/matrix.test.cpp
- /verify/verify/matrix/matrix.test.cpp.html
title: verify/matrix/matrix.test.cpp
---
