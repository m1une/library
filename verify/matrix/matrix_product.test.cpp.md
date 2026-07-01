---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product
    links:
    - https://judge.yosupo.jp/problem/matrix_product
  bundledCode: "#line 1 \"verify/matrix/matrix_product.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <iostream>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    constexpr ModInt(int\
    \ v) noexcept {\n        long long x = (long long)(v % (long long)(Modulus));\n\
    \        if (x < 0) x += Modulus;\n        _v = static_cast<uint32_t>(x);\n  \
    \  }\n\n    constexpr ModInt(long long v) noexcept {\n        long long x = (long\
    \ long)(v % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n       \
    \ _v = static_cast<uint32_t>(x);\n    }\n\n    constexpr ModInt(unsigned int v)\
    \ noexcept {\n        _v = static_cast<uint32_t>(v % Modulus);\n    }\n\n    constexpr\
    \ uint32_t val() const noexcept {\n        return _v;\n    }\n\n    constexpr\
    \ ModInt& operator++() noexcept {\n        _v++;\n        if (_v == Modulus) _v\
    \ = 0;\n        return *this;\n    }\n\n    constexpr ModInt& operator--() noexcept\
    \ {\n        if (_v == 0) _v = Modulus;\n        _v--;\n        return *this;\n\
    \    }\n\n    constexpr ModInt operator++(int) noexcept {\n        ModInt res\
    \ = *this;\n        ++*this;\n        return res;\n    }\n\n    constexpr ModInt\
    \ operator--(int) noexcept {\n        ModInt res = *this;\n        --*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt& operator+=(const ModInt&\
    \ rhs) noexcept {\n        _v += rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator-=(const ModInt&\
    \ rhs) noexcept {\n        _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt&\
    \ rhs) noexcept {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v\
    \ = static_cast<uint32_t>(z % Modulus);\n        return *this;\n    }\n\n    constexpr\
    \ ModInt& operator/=(const ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n\
    \    }\n\n    constexpr ModInt operator+(const ModInt& rhs) const noexcept {\n\
    \        return ModInt(*this) += rhs;\n    }\n    constexpr ModInt operator-(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) -= rhs;\n    }\n\
    \    constexpr ModInt operator*(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) *= rhs;\n    }\n    constexpr ModInt operator/(const ModInt& rhs)\
    \ const noexcept {\n        return ModInt(*this) /= rhs;\n    }\n\n    constexpr\
    \ bool operator==(const ModInt& rhs) const noexcept {\n        return _v == rhs._v;\n\
    \    }\n    constexpr bool operator!=(const ModInt& rhs) const noexcept {\n  \
    \      return _v != rhs._v;\n    }\n\n    constexpr ModInt pow(long long n) const\
    \ noexcept {\n        ModInt res = raw(1), x = *this;\n        while (n > 0) {\n\
    \            if (n & 1) res *= x;\n            x *= x;\n            n >>= 1;\n\
    \        }\n        return res;\n    }\n\n    constexpr ModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n\
    \            int64_t t = a / b;\n            a -= t * b;\n            std::swap(a,\
    \ b);\n            u -= t * v;\n            std::swap(u, v);\n        }\n    \
    \    if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matrix/matrix.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstddef>\n#line 8 \"matrix/matrix.hpp\"\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace matrix {\n\ntemplate <class T>\nclass Matrix {\n   private:\n \
    \   int _rows;\n    int _cols;\n    std::vector<T> _data;\n\n    static std::size_t\
    \ storage_size(int rows, int cols) {\n        assert(rows >= 0);\n        assert(cols\
    \ >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n\
    \    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int\
    \ rows, int cols, const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
    \ cols), value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n\
    \        : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 5 \"verify/matrix/matrix_product.test.cpp\"\
    \n\n#line 7 \"verify/matrix/matrix_product.test.cpp\"\n\nint main() {\n    using\
    \ mint = m1une::math::modint998244353;\n    int n, m, k;\n    std::cin >> n >>\
    \ m >> k;\n    m1une::matrix::Matrix<mint> first(n, m);\n    m1une::matrix::Matrix<mint>\
    \ second(m, k);\n    for (int row = 0; row < n; row++) {\n        for (int col\
    \ = 0; col < m; col++) std::cin >> first[row][col];\n    }\n    for (int row =\
    \ 0; row < m; row++) {\n        for (int col = 0; col < k; col++) std::cin >>\
    \ second[row][col];\n    }\n\n    auto product = first * second;\n    for (int\
    \ row = 0; row < n; row++) {\n        for (int col = 0; col < k; col++) {\n  \
    \          if (col > 0) std::cout << ' ';\n            std::cout << product[row][col];\n\
    \        }\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#include\
    \ \"../../math/modint.hpp\"\n#include \"../../matrix/matrix.hpp\"\n\n#include\
    \ <iostream>\n\nint main() {\n    using mint = m1une::math::modint998244353;\n\
    \    int n, m, k;\n    std::cin >> n >> m >> k;\n    m1une::matrix::Matrix<mint>\
    \ first(n, m);\n    m1une::matrix::Matrix<mint> second(m, k);\n    for (int row\
    \ = 0; row < n; row++) {\n        for (int col = 0; col < m; col++) std::cin >>\
    \ first[row][col];\n    }\n    for (int row = 0; row < m; row++) {\n        for\
    \ (int col = 0; col < k; col++) std::cin >> second[row][col];\n    }\n\n    auto\
    \ product = first * second;\n    for (int row = 0; row < n; row++) {\n       \
    \ for (int col = 0; col < k; col++) {\n            if (col > 0) std::cout << '\
    \ ';\n            std::cout << product[row][col];\n        }\n        std::cout\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - math/modint.hpp
  - matrix/matrix.hpp
  isVerificationFile: true
  path: verify/matrix/matrix_product.test.cpp
  requiredBy: []
  timestamp: '2026-06-22 14:42:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matrix/matrix_product.test.cpp
layout: document
redirect_from:
- /verify/verify/matrix/matrix_product.test.cpp
- /verify/verify/matrix/matrix_product.test.cpp.html
title: verify/matrix/matrix_product.test.cpp
---
